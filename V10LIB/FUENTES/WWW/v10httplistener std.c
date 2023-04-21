/*
* Módulo :  v10httpListener.c
* Objeto:   Servidor Listener de Conexiones de V10
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include <time.h>
#include "v10wwwform.h"
#include "process.h"

#define TIMEOUTHEBRA			10000	
#define TTIMEINIT					90000

servidorsockssls *v10nuevoservidor;

char ficheroconf[MAXPATH]="";

int eslistener=0;
v10httpsesiones s[MAXHTTPSESIONES];


void matahebra(int numsesion)
{
	v10httpsesiones *sactual=s+numsesion;

	if (sactual->v10server) v10sockssllibera(sactual->v10server);
	memset(sactual,0,sizeof(v10httpsesiones));
	sactual->status=STIDDLE;	
	v10log(LOGNORMAL,"Sesion %d: Fin hebra\n",numsesion);	

}


static char *damerandomsesion(char *idsesion)
{
	int i;
	srand((unsigned int)time(0));
	for (i=0;i<30;i++) {
		if (rand()%2==0) idsesion[i]=(char)((rand()%24)+65);
		else 
			if (rand()%3==0) idsesion[i]=(char)((rand()%26)+97);
			else
				idsesion[i]=(char)((rand()%10)+48);
	}
	idsesion[30]=0;
	return(idsesion);
}



static void v10atiendepeticion(void *param)
{
	int numsesion;
	v10sockssls *v10server;
	v10httpsesiones *sactual;
	v10horas timeout=damecent();

	numsesion=atoi((char *)param);	
	v10log(LOGNORMAL,"Sesion %d: Inicio hebra\n",numsesion);

	sactual=s+numsesion;
	v10server=sactual->v10server;
	do {
		if (v10server->v10sock->status==STSOCKREADY && v10socksslhaycar(v10server)) {
			if (recibecaracteres(v10server, sactual->peticion, sactual->buffer, &sactual->leidos)>0) {				
				sactual->ultrecepcion=damecent();
				if(tratapeticion(numsesion, v10server, sactual->peticion,NULL)) break;
			}	
		}
		if (v10server->v10sock->status==STSOCKROTA) {
			v10log(LOGNORMAL,"Sesion %d: Sesión rota\n",numsesion);
			break;
		}

		if (damecent() - timeout > TIMEOUTHEBRA) {
			v10log(LOGNORMAL,"Sesion %d: Fin por Timeout en recepcion de datos\n",numsesion);
			break; 
		}

		Sleep(1);
	} while((s+numsesion)->status!=STIDDLE && (s+numsesion)->status!=STFIN);

	matahebra(numsesion);	
}




static void v10recibepeticiones(void) 
{
	char aux[5]="";
	int numsesion;
	int servidoresperando=0;
	v10horas hultlect;
	v10httpsesiones *sactual;
	v10sockssls *v10server;
	char mipuertoservidor[6]="";

	v10configurahttp(ficheroconf);
	hultlect=damecent();
	v10initssl(v10httpconf.ssl, v10httpconf.sslkeyfile, v10httpconf.sslpassword, v10httpconf.dhfile, v10httpconf.ca_list);

	SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS	);

	memset(mipuertoservidor,0,6);
	strcpy(mipuertoservidor,(eslistener==1)?v10httpconf.v10puertoservidor:v10httpconf.v10puertomisc);

	v10nuevoservidor=v10socksslnuevoservidor(mipuertoservidor,0,NULL,NULL,NULL,NULL,NULL);
	v10log(LOGNORMAL,"Escuchando en puerto %s con protocolo %s\n",mipuertoservidor,(v10httpconf.ssl)?"HTTPS":"HTTP");
	do {
		Sleep(10);		
		if (damecent()-hultlect>v10httpconf.releeconfig) {
			v10configurahttp(ficheroconf);
			hultlect=damecent();
		}

		// reabre servidor si error	
		if (!v10nuevoservidor) {
			v10nuevoservidor=v10socksslnuevoservidor(mipuertoservidor,0,NULL,NULL,NULL,NULL,NULL);		
		} else
			if (v10nuevoservidor->servidorsock->status==STPIPEERRSSL) {
				v10socksslcierraservidor(v10nuevoservidor);
				v10nuevoservidor=v10socksslnuevoservidor(mipuertoservidor,0,NULL,NULL,NULL,NULL,NULL);
			}		

			v10server=v10sockssldameconexion(v10nuevoservidor);
			if (v10server!=NULL) {
				for (numsesion=0;numsesion<MAXHTTPSESIONES;numsesion++) {
					sactual=s+numsesion;			
					if (sactual->status==STIDDLE) {
						sactual->v10server=v10server;
						sactual->status=STCONNECTED;
						sactual->tid=(HANDLE)_beginthread(v10atiendepeticion,0,itoa(numsesion,aux,10));												
						break;
					}
				}
			}	
			if (hay_tecla() && tecla()==A_F(10)) break;				
	} while (1);
}


void capturahostname(int numsesion, char *peticion) {
	char *ptr,*ptr2;
	char cadena[MAXPATH]="";
	char buff[MAXCADENA]="",buff2[MAXCADENA]="";

	*s[numsesion].hostname=0;
	*s[numsesion].extraparam=0;

	//if (*s[numsesion].hostname) return;
	ptr=strstr(peticion,"&HOST=");
	ptr2=strstr(ptr+1,"&");
	if (ptr && (ptr2-ptr)>6) {
		strcopia(s[numsesion].hostname,ptr+6,ptr2 - (ptr+6));
		v10log(LOGNORMAL,"Se captura HOST en URL del cliente %s \n",s[numsesion].hostname);
	} else { // si no nos lo informan mediante parámetro, se intenta calcular por el socket
		struct sockaddr *origen;
		struct hostent *remoteHost;
		struct in_addr *addr;
		// si no puede obtener el nombre del equipo por DNS, guarda la IP
		origen=&(s[numsesion].v10server->v10sock->origen);
		addr=&((struct sockaddr_in *)origen)->sin_addr;
	    remoteHost = gethostbyaddr((char *)addr, 4, AF_INET);
	    sprintf(s[numsesion].hostname,"%d.%d.%d.%d\0",
			addr->S_un.S_un_b.s_b1,
			addr->S_un.S_un_b.s_b2,
			addr->S_un.S_un_b.s_b3,
			addr->S_un.S_un_b.s_b4);
		v10log(LOGNORMAL,"Se captura IP del cliente %s\n",s[numsesion].hostname);
		if (remoteHost && strcmp(strmay(remoteHost->h_name),"LOCALHOST")) {
			strcpy(s[numsesion].hostname,remoteHost->h_name);
			v10log(LOGNORMAL,"Se captura H_NAME del cliente %s\n",s[numsesion].hostname);
		}
	} 

	if (*v10httpconf.extra) sprintf(s[numsesion].extraparam,"%s ",v10httpconf.extra); 
	ptr=strstr(peticion,"&EXTRA=");
	if (ptr) {
		ptr2=strstr(ptr+1,"&");	
		if (ptr2 && (ptr2-ptr)>7) {
			strcopia(s[numsesion].extraparam+strlen(s[numsesion].extraparam),ptr+7,ptr2 - (ptr+7));
			v10evtoansi(s[numsesion].extraparam);
		}
	}
}



void creav10form(int numsesion)
{
	char idsesion[31]="",cpuerto[6]="",ordenador[MAXPATH]="";
	int puerto;
	char runv10form[MAXCADENA]="",cadpuerto[11]="",extra[MAXPATH]="";
	v10socks *verify;
	v10horas timeinit;
	v10httpsesiones *sactual=s+numsesion;


	ZeroMemory(&(sactual->si),sizeof(sactual->si));
	sactual->si.dwX=10;
	sactual->si.dwY=10;
	sactual->si.dwXSize=200;
	sactual->si.dwYSize=400;
	sactual->si.dwFlags=STARTF_USEPOSITION|STARTF_USESIZE|STARTF_FORCEONFEEDBACK;
	sactual->si.cb = sizeof(sactual->si);
	ZeroMemory( &(sactual->pi), sizeof(sactual->pi));

	puerto=v10damecon(atoi(v10httpconf.v10puertoinicial));			
	if (-1==puerto) {
		v10log(LOGNORMAL, "No hay puertos libres para crear otro proceso\n");
		return;
	}


	v10httpconf.v10puertov10form=puerto+atoi(v10httpconf.v10puertoinicial);
	itoa(v10httpconf.v10puertov10form,v10httpconf._v10puertov10form,6);

	// -DNDINAMICA.TXT 
	sprintf(runv10form,"%s -OU%s -LN%s.LOG -LM%d -FWFICHERO=%s -FWVISIBLE=%d -FWSESION=%s -FWPUERTO=%d -FWHOST=%s -FWTECLADO=%d %s",	
		v10httpconf.ficheroexe,
		v10httpconf.conexionBD,
		v10httpconf.hostname,
		v10httpconf.nivellog,
		ficheroconf,
		v10httpconf.visibleexe,
		damerandomsesion(idsesion), // cargarlo en la misma estructura del hijo
		v10httpconf.v10puertov10form, // cargar este valor pasado en la misma estructura del hijo
		sactual->hostname,
		v10httpconf.tecladovirtual,
		sactual->extraparam);	


	sprintf(sactual->puerto,"%d",v10httpconf.v10puertov10form);

	//Start the child process
	if (!CreateProcess( NULL, // No module name (use command line).
		runv10form,       // Command line.
		NULL,             // Process handle not inheritable.
		NULL,             // Thread handle not inheritable.
		FALSE,            // Set handle inheritance to FALSE.
		HIGH_PRIORITY_CLASS,  // No creation flags.
		NULL,             // Use parent's environment block.
		NULL,             // Use parent's starting directory.
		&sactual->si,     // Pointer to STARTUPINFO structure.
		&sactual->pi )    // Pointer to PROCESS_INFORMATION structure.
		)
	{
		v10log(LOGNORMAL, "Sesión %s no se puede establecer\n",idsesion);
		return;
	}
	v10log(LOGNORMAL,"Sesion %d: Arrancado Proceso v10form\n",numsesion);

	timeinit=damecent();

	v10log(LOGNORMAL,"Sesion %d: Intentando conectar con v10form en puerto %s\n",numsesion,s[numsesion].puerto);

	do {
		verify=v10socknuevocliente("127.0.0.1",s[numsesion].puerto,0,4096,NULL,NULL,NULL,NULL,NULL);
		if (!verify && (damecent()-timeinit>TTIMEINIT)) {		
			funcdebug(numsesion,s[numsesion].v10server,"Error al arrancar V10FORM");
			matahebra(numsesion);
			return;	
		}
		if (!verify) Sleep(100);
	} while (!verify);

	while (verify->status!=STSOCKREADY) Sleep(1);

	v10socklibera(verify);
	v10log(LOGNORMAL, "Sesión establecida\n");  
}


int v10runlistener(char *param_ficheroconf)
{
	eslistener=1;
	strcopia(ficheroconf,param_ficheroconf,strlen(param_ficheroconf));
	v10recibepeticiones();
	return(0);
}

int v10runserverfiles(char *param_ficheroconf)
{
	eslistener=0;
	strcopia(ficheroconf,param_ficheroconf,strlen(param_ficheroconf));
	v10recibepeticiones();
	return(0);
}




