#include "vdservisu.h"

#define MAXGRUPOS    50
#define MAXSERVICIOS 200
#define TMATANZA     200
static int numgrupos;
static int pausar = 0;
static v10horas iniciopause, finpause;
static char paradaoracle[MAXPATH] = "", arranqueoracle[MAXPATH] = "";
static long esperalogin = 0;
#define TRELOAD 100
#define TREVISA 100
static int ultpuertovisu;
static grs sgr[MAXGRUPOS];
static int treload = TRELOAD;
static int trevisa = TREVISA;
static int anadepath = 0;

#define CSETUSER "BEGIN VDUSER.SETUSER('VDSERVICIO');END;"
static v10cursors *vdsetuser;

static void initservicio(void)
{
	vdsetuser = abrecursor(CSETUSER);
}

static void ponuser(void)
{
	if (vdsetuser == NULL) initservicio();
	ejecutacursor(vdsetuser);
}

static int esservicio = 0;
static int numciclo = 0, modocierre = 0;

void servicios2char(char *cadena) {
	int ng, ns, cont = 0;
	grs *ptrgrupo;
	procservicios *ptr;

	*cadena = 0;
	for (ng = 0; ng<numgrupos; ng++) {
		ptrgrupo = sgr + ng;
		for (ns = 0; ns<ptrgrupo->numservicios; ns++) {
			ptr = ptrgrupo->proc + ns;
			if (*ptr->ser.visualizado == 'S') {
				if (cont>0) strcat(cadena, "#");
				sprintf(cadena + strlen(cadena), "%s;%c;%s;%c;%d;%d;%d;%d",
					ptrgrupo->gr.codgruposerv,
					*ptrgrupo->gr.arranque,
					ptr->ser.codservicio,
					*ptr->ser.activo,
					ptr->puertopant,
					ptr->puertolog,
					ptr->ser.pid,
					ptr->ser.status);
				cont++;
			}
		}
	}
	strcat(cadena, "$");
}

static void pontituloventana(procservicios *ptr, char *cad)  {
	char *ptr1, *ptr2;
	int off;
	ptr1 = strstr(cad, "-WV");
	if (ptr1) {
		ptr2 = strchr(ptr1 + 1, '-');
		if (ptr2) strcopia(ptr->tituloventana, ptr1 + 3, ptr2 - (ptr1 + 3));
		else strcpy(ptr->tituloventana, ptr1 + 3);
		trim(ptr->tituloventana);
		if (*ptr->tituloventana == '\"') *ptr->tituloventana = ' ';
		off = (int)strlen(ptr->tituloventana) - 1;
		if (*(ptr->tituloventana + off) == '\"') *(ptr->tituloventana + off) = ' ';
		ltrim(ptr->tituloventana);
		trim(ptr->tituloventana);

	}
}


static void traduceenv(char *cadena, char *destino)
{
	char *aux, *aux1, *var;
	strcpy(destino, "");
	while ((aux = strchr(cadena, '%')) != NULL) {
		*aux = 0;
		strcat(destino, cadena);
		cadena = aux + 1;
		if ((aux1 = strchr(cadena, '%')) != NULL) {
			*aux1 = 0;
			var = getenv(cadena);
			if (var) sprintf(destino + strlen(destino), "%s", var);
			*aux1 = '%';
			cadena = aux1 + 1;
		}
		else {
			sprintf(destino + strlen(destino), "%%%s", cadena);
			cadena += strlen(cadena);
		}
		*aux = '%';
	}
	strcat(destino, cadena);
}

static void v10putenv(char *cadena)
{
	char destino[MAXCADENA];
	traduceenv(cadena, destino);
	if (strlen(destino)>3000)
		v10log(LOGERROR, "Cadena %s es de longitud %d en putenv", destino, strlen(destino));
	_putenv(destino);
	v10log(LOGDEBUG, "Variable de entorno %s\n", destino);
}


static void ponentorno(char *cadena)
{
	char *aux, achar;
	char destino[MAXCADENA];
	if (*cadena == '+') cadena++;
	while (!es_blanco(cadena)) {
		aux = strstr(cadena, "\\n");
		if (aux == NULL) aux = strchr(cadena, ';');
		if (aux) {
			achar = *aux;
			*aux = 0;
		}
		strcpy(destino, resuelveconf(cadena, damehostname()));
		v10putenv(destino);
		if (aux) {
			*aux = achar;
			if (achar == '\\') cadena = aux + 2;
			else             cadena = aux + 1;
		}
		else cadena += strlen(cadena);
	}
}

static int mataservicio(procservicios *ptr, grs *ptrgrupo) {
	int ret = 0;
	DWORD err;

	ret = GetExitCodeProcess(ptr->pi.hProcess, &err);
	if (err == STILL_ACTIVE) { // si todavia esta activo, lo mata
		// tras esperar 0,8 segundos
		if (damecent() >= ptr->horamatanza) {
			v10log(LOGNORMAL, "Forzando matanza de servicio %s de grupo %s\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv);
			TerminateProcess(ptr->pi.hProcess, 0);
#ifndef __LINUX__			
			CloseHandle(ptr->pi.hProcess);
			CloseHandle(ptr->pi.hThread);
#endif
			ret = 0;
		}
		else return(-1); // que no intente arrancarlo
	}
	else {
		v10log(LOGNORMAL, "Muerte correcta y ordenada de servicio %s de grupo %s\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv);
		ret = 0;// ya no existe el proceso
	}
	ptr->pdtecheckterminate = 0;
	memset(&ptr->pi, 0, sizeof(ptr->pi));
	return(ret);
}

static void paraservicio(procservicios *ptr, grs *ptrgrupo)
{
	if (ptr->pdtecheckterminate == 1) return;

	if (ptr->pi.dwProcessId) {
		v10log(LOGNORMAL, "Deteniendo servicio %s de grupo %s\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv);
#ifndef __LINUX__	    
		{
			HWND wv10 = NULL;
			if (*ptr->tituloventana) wv10 = FindWindow(NULL, ptr->tituloventana);
			if (wv10) {
				long lparam = 0;
				ptr->pdtecheckterminate = 1; // le queda pendiente revisar si el proceso esta finalizado
				PostMessage(wv10, WM_CLOSE, 0, lparam);
				ptr->horamatanza = damecent() + TMATANZA;
				v10log(LOGNORMAL, "Pendiente revisar que se detenga servicio %s de grupo %s\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv);
			}
			else {
				/* AttachConsole(ptr->pi.dwProcessId); // attach to process console
				SetConsoleCtrlHandler(NULL,TRUE); // disable Control+C handling for our app
				GenerateConsoleCtrlEvent(CTRL_C_EVENT,0);
				ptr->horamatanza=damecent()+TMATANZA;
				ptr->pdtecheckterminate=1;*/

				TerminateProcess(ptr->pi.hProcess, 0);
				CloseHandle(ptr->pi.hProcess);
				CloseHandle(ptr->pi.hThread);
				memset(&ptr->pi, 0, sizeof(ptr->pi));
				ptr->pdtecheckterminate = 0;
			}
		}
#else
		pidetermina(ptr->pi.hProcess, 0);
		ptr->horamatanza = damecent() + TMATANZA;
		//memset(&ptr->pi, 0, sizeof(ptr->pi));		
		ptr->pdtecheckterminate = 1;
#endif	    
		memset(ptr->tituloventana, 0, MAXPATH);
		ptr->ser.status = STSERDETENIDO;
		ptr->ser.pid = 0;
		ptr->ser.sid = 0;
		ptr->ser.fecarranque = 0;
		SERactualizaestado(&ptr->ser, 0);
		commit();
	}
}

static void matagrupo(grs *ptrgrupo)
{
	int ns;
	for (ns = 0; ns<ptrgrupo->numservicios; ns++) {
		if ((ptrgrupo->proc + ns)->pdtecheckterminate)  mataservicio(ptrgrupo->proc + ns, ptrgrupo);
	}
}

static void paragrupo(grs *ptrgrupo)
{
	int ns;
	for (ns = 0; ns<ptrgrupo->numservicios; ns++) {
		paraservicio(ptrgrupo->proc + ns, ptrgrupo);
	}
}

#ifndef __LINUX__
#define SEMICOLON ';'
#else
#define SEMICOLON ':'
#endif

static void anadeavar(char *var, char *cadena)
{
	if (*cadena == '+' || *cadena == '@') cadena++;
	if (!es_blanco(cadena)) sprintf(var + strlen(var), "%s%c", cadena, SEMICOLON);
}

static void anadeaparam(char *param, char *cadena)
{
	if (*cadena == '+' || *cadena == '@') cadena++;
	if (!es_blanco(cadena)) sprintf(param + strlen(param), "%s ", cadena);
}

static int anaderesto(char *cadena)
{
	if (*cadena == '@') return 0;
	if (anadepath || *cadena == '+' || *cadena == 0) return (1);
	return 0;
}

//extern char *resuelveconf(char *cadena,char *instancia);
static int ejecutaservicio(procservicios *ptr, grs *ptrgrupo)
{
	int ret;
	char path[MAXCADENA], param[MAXCADENA], paramexp[MAXCADENA], cesperalogin[10] = "", *envpath, *antpath, *envpathv10, *antpathv10, *envlib, *antlib;
	STARTUPINFO si;
	vdserviciosauxs servaux;

	// planificación de la hora de PAUSE
	if (!strcmp(ptr->ser.ejecutable, "PAUSE")) {
		iniciopause = a2cent(ptr->ser.horainicio);
		finpause = a2cent(ptr->ser.horalimite);
		piece(ptr->ser.paramservicio, paradaoracle, "#", 1);
		piece(ptr->ser.paramservicio, arranqueoracle, "#", 2);
		piece(ptr->ser.paramservicio, cesperalogin, "#", 3); // cuanto tarda en hacer login desde que inicia el arranque
		esperalogin = atoi(cesperalogin);
		if (esperalogin == 0) esperalogin = 300; // por deefcto 5 minutos
		if (gettime() >= iniciopause && gettime()<finpause) pausar = 1;
		return(0);
	}

	envlib = getenv("LD_LIBRARY_PATH");
	if (envlib) antlib = strdup(envlib);
	else            antlib = "";
	memset(&si, 0, sizeof(si));
	if (*ptr->ser.envservicio == '+' || *ptr->ser.envservicio == 0) {
		if (*ptrgrupo->gr.envgrupo == '+' || *ptrgrupo->gr.envgrupo == 0) ponentorno(damepropcadenainst("ENV", damehostname()));
		ponentorno(ptrgrupo->gr.envgrupo);
	}
	ponentorno(ptr->ser.envservicio);
	envpath = getenv("PATH");
	antpath = strdup(envpath);
	sprintf(path, "PATH=");
	anadeavar(path, ptr->ser.pathservicio);
	if (anaderesto(ptr->ser.pathservicio)) {
		anadeavar(path, ptrgrupo->gr.pathgrupo);
		if (anaderesto(ptrgrupo->gr.pathgrupo)) {
			char *varpath;
			varpath = damepropcadenainst("PATH", damehostname());
			anadeavar(path, varpath);
			if (anaderesto(varpath)) {
				sprintf(path + strlen(path), "%s", envpath);
			}
		}
	}
	v10log(LOGNORMAL, "Poniendo PATH a  %s\n", path);
	v10putenv(path);
	envpathv10 = getenv("PATHV10");
	if (envpathv10) antpathv10 = strdup(envpathv10);
	else            antpathv10 = "";
	sprintf(path, "PATHV10=");
	anadeavar(path, ptr->ser.pathv10servicio);
	if (anaderesto(ptr->ser.pathv10servicio)) {
		anadeavar(path, ptrgrupo->gr.pathv10grupo);
		if (anaderesto(ptrgrupo->gr.pathv10grupo)) {
			char *varpath;
			varpath = damepropcadenainst("PATHV10", damehostname());
			anadeavar(path, varpath);
			if (anaderesto(varpath)) {
				sprintf(path + strlen(path), "%s", envpathv10);
			}
		}
	}
	v10log(LOGNORMAL, "Poniendo V10PATH a  %s\n", path);
	v10putenv(path);
	sprintf(param, "%s ", ptr->ser.ejecutable);
	anadeaparam(param, ptr->ser.paramservicio);
	if (anaderesto(ptr->ser.paramservicio)) {
		anadeaparam(param, ptrgrupo->gr.paramgrupo);
		if (anaderesto(ptrgrupo->gr.paramgrupo)) {
			anadeaparam(param, damepropcadenainst("PARAM", damehostname()));
		}
	}
	pontituloventana(ptr, param);
	if (*ptrgrupo->gr.arranque == 'A') strcat(param, " -OP");
	if (*ptr->ser.visualizado == 'S') {
		if (ptr->puertopant == 0) ptr->puertopant = ultpuertovisu++;
		sprintf(param + strlen(param), " -SP%d", ptr->puertopant);
		if (ptr->puertolog == 0)  ptr->puertolog = ultpuertovisu++;
		sprintf(param + strlen(param), " -SL%d", ptr->puertolog);
	}
	traduceenv(param, paramexp);
	strcpy(paramexp, resuelveconf(paramexp, damehostname()));
	v10log(LOGNORMAL, "Ejecutando %s\n", paramexp);
	ret = CreateProcess(NULL, paramexp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &ptr->pi);
	sprintf(path, "PATH=%s", antpath);
	v10putenv(path);
	if (antpath) free(antpath);
	sprintf(path, "PATHV10=%s", antpathv10);
	v10putenv(path);
	if (envpathv10) free(antpathv10);
	sprintf(path, "LD_LIBRARY_PATH=%s", antlib);
	v10putenv(path);
	if (envlib) free(antlib);
	if (ret == 0) {
#ifndef __LINUX__	   
		char mensaje[MAXCADENA];
		int err;
		err = GetLastError();
		dameerrsistema(err, mensaje);
		v10log(LOGERROR, "Error ejecutando servicio %s: %s\n", ptr->ser.codservicio, mensaje);
#else
		v10log(LOGERROR, "Error ejecutando servicio %s: %d\n", ptr->ser.codservicio, ret);
#endif	    
	}
	else {
		v10log(LOGNORMAL, "Ejecucion correcta de servicio %s de grupo %s: pid %ld\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv, ptr->pi.dwProcessId);
		ptr->ser.status = STSERENMARCHA;
		ptr->ser.pid = ptr->pi.dwProcessId;
		ptr->pdtecheckterminate = 0;
		switch (*ptrgrupo->gr.arranque) {
		case 'A':
			if (ptr->ser.fecarranque == 0) ptr->ser.fecarranque = damedate();
			ret = SERactualizaestado(&ptr->ser, 0);
			break;
		case 'P':
			ptr->ser.fecultejec = damedate();
			cent2a(gettime(), 0, ':', ptr->ser.horaultejec);
			ptr->ser.fecejec = 0; // limpia la fecha de siguiente planificación
			*ptr->ser.horaejec = 0;
			*ptr->ser.ejecutar = 'N';
			ret = SERactualizaplanif(&ptr->ser, 0);
			// planificar la nueva ejecución
			SERVICIOSAUXprocplanificaservicio(ptr->ser.codgruposerv, ptr->ser.codservicio, 0, &servaux);
		}
		commit();
	}
	return(0);
}

static int revisaservicio(procservicios *ptr, grs *ptrgrupo)
{
	int ret = 0;
	vdserviciosauxs servaux;

	if (damecent() - ptr->ultload>TRELOAD) {
		SERselcodservicio(ptrgrupo->gr.codgruposerv, ptr->ser.codservicio, &ptr->ser);
		ptr->ultload = damecent();
	}

	if (ptr->pdtecheckterminate) {	// este proceso esta pendiente de matarse	
		ret = mataservicio(ptr, ptrgrupo);
		if (ret) return(0);
	}

	if (*ptrgrupo->gr.arranque == 'A') { // grupo en modo arranque automática
		if (*ptr->ser.activo == 'S') {
			SERVICIOSAUXbuscaejecutableservicio(ptr->ser.codgruposerv, ptr->ser.codservicio, &servaux);
			if (servaux.ret == 1) { // tiene que arrancar el servicio
				if (ptr->pi.dwProcessId) {
					DWORD err;
					GetExitCodeProcess(ptr->pi.hProcess, &err);
					if (err != STILL_ACTIVE) {
						v10log(LOGNORMAL, "Servicio %s de grupo %s no se esta ejecutando\n", ptr->ser.codservicio, ptrgrupo->gr.codgruposerv);
#ifndef __LINUX__						
						CloseHandle(ptr->pi.hProcess);
						CloseHandle(ptr->pi.hThread);
#endif						
						memset(&ptr->pi, 0, sizeof(ptr->pi));
						ptr->ser.status = STSERDETENIDO;
						ptr->ser.pid = 0;
						ret = SERactualizaestado(&ptr->ser, 0);
						commit();
						ret = ejecutaservicio(ptr, ptrgrupo);
					}
				}
				else ret = ejecutaservicio(ptr, ptrgrupo);
			}
			else if (servaux.ret == -1) paraservicio(ptr, ptrgrupo); // tiene que parar el servicio            
		}
		else paraservicio(ptr, ptrgrupo);
	}


	if (*ptrgrupo->gr.arranque == 'P' && *ptr->ser.activo == 'S') {
		SERVICIOSAUXbuscaejecservplanif(ptr->ser.codgruposerv, ptr->ser.codservicio, numciclo == 1 ? "S" : "N", modocierre == 1 ? "S" : "N", &servaux);
		if (servaux.ret == 1) ret = ejecutaservicio(ptr, ptrgrupo);
	}

	return(ret);
}

static int revisagrupo(grs *ptrgrupo)
{
	int ns;
	int ret = 0;
	vdserviciosauxs servaux;

	if (damecent() - ptrgrupo->ultload>treload) {
		GRSselcodgruposerv(ptrgrupo->gr.codgruposerv, &ptrgrupo->gr);
		ptrgrupo->ultload = damecent();
	}
	// si el grupo de servicios es para arrancar o para planificar
	if (*ptrgrupo->gr.arranque == 'A' || *ptrgrupo->gr.arranque == 'P') {
		for (ns = 0; ns<ptrgrupo->numservicios; ns++) {
			procservicios *ptr = ptrgrupo->proc + ns;
			revisaservicio(ptr, ptrgrupo);
		}
		if (*ptrgrupo->gr.arranque == 'P') { // si el grupo es de tipo P, planifica tareas activas
			SERVICIOSAUXprocplanificagruposerv(ptrgrupo->gr.codgruposerv, &servaux);
			commit();
		}
	}
	else {
		paragrupo(ptrgrupo);
		matagrupo(ptrgrupo);
	}
	return(ret);
}

static int revisagrupos(void)
{
	int ng;
	int ret = 0;
	static int arrancavisu = 0;
	numciclo++;

	// solo lo hace la primera vez
	if (arrancavisu == 0) ultpuertovisu = servervisu + 1;
	// vuelve a guardar el usuario por si acaso se perdiese estado del paquete
	ponuser();
	for (ng = 0; ng<numgrupos; ng++) {
		ret = revisagrupo(sgr + ng);
	}
	if (arrancavisu == 0) { // inicia la hebra que se encarga de tratar los clientes visualiza
		_beginthread(tratavisualiza, 0, NULL);
		atexit(cierraservervisualiza);
		arrancavisu = 1;
	}
	return(ret);
}


static void liberagrupos(void)
{
	int ng;
	for (ng = 0; ng<numgrupos; ng++) {
		grs *ptrgrupo = sgr + ng;
		if (*ptrgrupo->gr.arranque == 'P') { // si es planificado
			modocierre = 1;
			revisagrupo(ptrgrupo); // ejecuta por última vez las tareas
		}
		else {
			paragrupo(ptrgrupo);
		}
		//free(ptrgrupo->proc);
	}
	Sleep(1000);
	for (ng = 0; ng<numgrupos; ng++) {
		grs *ptrgrupo = sgr + ng;
		matagrupo(ptrgrupo);
		free(ptrgrupo->proc);
	}
	numgrupos = 0;
}

char servername[MAXPATH];
char *nombreserver(void)
{
#ifndef __LINUX__	
	if (*servername == 0 && getenv("SERVERNAME")) strcpy(servername, getenv("SERVERNAME"));
	if (*servername == 0) strcpy(servername, getenv("COMPUTERNAME"));
#else
	gethostname(servername, sizeof(servername));
#endif
	return(servername);
}


static int cargagrupos(void)
{
	int ret;
	vdgruposervs gr;
	vdservicioss ser;
	ret = GRSbuscaordenador(nombreserver(), &gr);
	while (ret == 0) {
		grs *ptrgrupo = sgr + numgrupos;
		ptrgrupo->gr = gr;
		ptrgrupo->proc = calloc(MAXSERVICIOS, sizeof(procservicios));
		ret = SERbuscacodgruposerv(gr.codgruposerv, &ser);
		v10log(LOGNORMAL, "Cargando grupo %s\n", gr.codgruposerv);
		while (ret == 0) {
			v10log(LOGNORMAL, "    Cargando servicio %s\n", ser.codservicio);
			if (ser.status == 200 && ser.sid != 0 && ser.serial != 0) {
				ejecutaimmediatoparam("ALTER SYSTEM KILL SESSION '%ld,%ld'", ser.sid, ser.serial);
			}
			ptrgrupo->proc[ptrgrupo->numservicios].ser = ser;
			ptrgrupo->numservicios++;
			if (ser.fecarranque != 0) {
				ser.fecarranque = 0;
				SERactualizaestado(&ser, 0);
				commit();
			}
			ret = SERnextcodgruposerv(&ser);
		}
		numgrupos++;
		ret = GRSnextordenador(&gr);
	}
	atexit(liberagrupos);
	return(0);
}

static void modopause(void)
{
	char horainicio[10] = "", horalimite[10] = "";
	cent2a(iniciopause, 0, ':', horainicio);
	cent2a(finpause, 0, ':', horalimite);
	pausar = 0;
	v10log(LOGNORMAL, "%s", "modosuspension: \n");
	v10log(LOGNORMAL, "%s", "modosuspension: ****************************************************************************\n\n");
	v10log(LOGNORMAL, "%s", "modosuspension: Inicio modo PAUSE por periodo de pause de %s a %s ...\n\n", horainicio, horalimite);

	liberagrupos();
	logout();

	if (*paradaoracle) {
		v10log(LOGNORMAL, "modosuspension: Ejecutando programa en Modo Suspensión %s\n", paradaoracle);
		system(paradaoracle);
	}
	do {
		Sleep(10);
		if (hay_tecla()) {
			if (STDtecla() == esc) break;
		}
		if (gettime()>finpause) break;
	} while (1);

	v10log(LOGNORMAL, "%s", "modosuspension: Fin del modo PAUSE\n\n");
	v10log(LOGNORMAL, "%s", "modosuspension: ****************************************************************************\n\n");
	v10log(LOGNORMAL, "%s", "modosuspension: \n");

	if (*arranqueoracle) {
		v10log(LOGNORMAL, "modosuspension: Ejecutando programa al Salir de Modo Suspensión %s\n", arranqueoracle);
		system(arranqueoracle);
	}

	Sleep(esperalogin * 1000);
	relogin();
	initlogoracle();
	ponuser();
	esperalogin = 0;
	*paradaoracle = 0;
	*arranqueoracle = 0;
	cargagrupos();
}


static v10cursors *v10hayanterior;
#define CHAYANTERIOR " SELECT VDPLANIF.HAYANTERIOR FROM DUAL"

static int salirservicio = 0;
int main(int argc, char *argv[])
{
	v10horas ultciclo = 0;
	//    int ret;
	strcpy(TITULOVENTANA, "LANZADOR DE PROCESOS V10");
	initapptxt(v10hinst, v10hprev, SW_SHOWMINIMIZED, TITULOVENTANA, CW_USEDEFAULT, CW_USEDEFAULT,
		0, 0, COLUMNASPANTALLA, LINEASPANTALLA, ESTILOV10, 0, NULL, 0, 0, NULL);
	pintapantallav10("PROGRAMA DE MONITORIZACION DE SERVICIOS AUTOMATICOS EN V10");
	trataparamstd(argc, argv, trataparammain, trataparamoracle, NULL);
	quitalogoracle(damepropenteroinst("SINLOGORACLE", damehostname()));
	cargahandleoraerr(argv[0], argv, argc);
	if (esservicio == 0)  v10log(LOGNORMAL, "%s", "El programa se esta ejecutando en modo normal\n");
	else        v10log(LOGNORMAL, "%s", "El programa se esta ejecutando como servicio\n");
	initlogoracle();
	treload = damepropenteroinst("TRELOADSERV", damehostname());
	if (treload == 0) treload = TRELOAD;
	trevisa = damepropenteroinst("TREVISASERV", damehostname());
	if (trevisa == 0) trevisa = TREVISA;
	anadepath = damepropenteroinst("ANADEPATH", damehostname());
	asignatecla(ALT('L'), (void *)editalog);
	/*   v10hayanterior = abrecursor(CHAYANTERIOR);
	definetodo(v10hayanterior, &ret, sizeof(ret), V10INT, NULL);
	ejefetchcursor(v10hayanterior);
	if (ret) {
	v10log(LOGERROR, "Servicio ya se esta ejecutando\n");
	exit(1);
	}
	liberacursor(v10hayanterior);*/
	ponuser();
	cargagrupos();
	servervisu = damepropenteroinst("PORTVISU", damehostname());
	if (servervisu == 0) servervisu = 50000; // por defecto servervisu, si no se informa, vale 50000
	while (!salirservicio) { // se ejecuta cada decima de segundo para no chupar CPU
		if (damecent() - ultciclo > 10) {
			revisagrupos();
			ultciclo = damecent();
		}
		if (hay_tecla()) if (tecla() == A_F(10)) break;
		Sleep(100);
		if (pausar == 1) modopause();
	}
	liberagrupos();
	return(0);
}

#ifndef __LINUX__
static SERVICE_STATUS			svcStatus;
static SERVICE_STATUS_HANDLE	svcHandle;
static void muestraestadoservicio(DWORD estado, DWORD valorsalida, DWORD espera)
{
	static DWORD dwCheckPoint = 1;
	if (estado == SERVICE_START_PENDING) svcStatus.dwControlsAccepted = 0;
	else                                 svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	svcStatus.dwCurrentState = estado;
	svcStatus.dwWin32ExitCode = valorsalida;
	svcStatus.dwWaitHint = espera;
	if ((estado == SERVICE_RUNNING) || (estado == SERVICE_STOPPED)) svcStatus.dwCheckPoint = 0;
	else                                                             svcStatus.dwCheckPoint = dwCheckPoint++;
	SetServiceStatus(svcHandle, &svcStatus);
}

void WINAPI ServiceHandler(DWORD dwCtrlCode)
{
	switch (dwCtrlCode) {
	case SERVICE_CONTROL_STOP: salirservicio = 1;
		svcStatus.dwCurrentState = SERVICE_STOP_PENDING;
		break;
	case SERVICE_CONTROL_INTERROGATE: break;
	default: break;
	}
	muestraestadoservicio(svcStatus.dwCurrentState, 0, 0);
}

void WINAPI ServiceMain(DWORD argc, char **argv)
{
	esservicio = 1;
	svcHandle = RegisterServiceCtrlHandler("VDSERVICIO", ServiceHandler);
	svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	svcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;
	muestraestadoservicio(SERVICE_RUNNING, NO_ERROR, 3000);
	main(argc, argv);
	muestraestadoservicio(SERVICE_STOPPED, NO_ERROR, 0);
	return;
}
SERVICE_TABLE_ENTRY servicetable[] =
{
	{ "VDSERVICIO", (LPSERVICE_MAIN_FUNCTION)ServiceMain },
	{ NULL, NULL }
};


int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
	LPSTR cmd, int cmdshow)
{
	int ret;
	v10hinst = hinst;
	v10hprev = hprev;
	onexit(ejecutaexit);
	trataparamstd(__argc, __argv, trataparampremain, NULL);
	if (!StartServiceCtrlDispatcher(servicetable)) {
		esservicio = 0;
		ret = main(__argc, __argv);
		exit(-1);
	}
	else ret = 0;
	return(ret);
}
#endif
