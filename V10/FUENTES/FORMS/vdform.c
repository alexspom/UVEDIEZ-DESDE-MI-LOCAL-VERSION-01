/*******************************************************************************
* Módulo : vdform.c                                                            *
* Función: Modulo principal de las pantallas de v10                            *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "v10wwwform.h"
#include "vdform.h"

char formdefecto[MAXCADENA];
char wheredefecto[MAXSQL];
char orderdefecto[MAXSQL];
char opcionesdefecto[MAXNOMBREV10];
char menudefecto[MAXPATH];
static void apilamenu(int dummy)
{
    pushtecla(S_F(10));
}
static int trataargform(char *cadena)
{
	static char user[LCODOPE];
	char password[LCODOPE];
	int ret;
    switch (toupper(*cadena)) {
          case 'F' :switch (toupper(cadena[1])) {
                       case 'C': strcpy(user,cadena+2);
                                 strcpy(vduser.codope,user);
								 ponuserdb();
                                 break;
                       case 'U': strcpy(user,cadena+2);
                                 break;
                       case 'P': strcpy(password,cadena+2);
						         ret=verificausr(user,password);
								 if (ret) {
									 mensajefcm(10,"password incorrecto");
									 strcpy(vduser.codope,"");
								 } else {
									 strcpy(vduser.codope,user);
								 }
                                 break;
					   case 'F':strcpy(formdefecto,cadena+2);
						        break;
					   case 'M':strcpy(menudefecto,cadena+2);
						        break;
					   case 'H':strcpy(wheredefecto,cadena+2);
						        break;
					   case 'O':strcpy(orderdefecto,cadena+2);
						        break;
					   case 'X':strcpy(opcionesdefecto,cadena+2);
						        break;
                    }
                    break;
	}
    return(0);
}

void ejecutadirecto(char *pantalla,char *where,char *order,char *opciones)
{
    forms *antform=formglobal;
	char destino[MAXCADENA];
    bloques *bn;
	int ret;
	formglobal=leeform(pantalla,opciones);
	if (formglobal==NULL) return;
	bn=formglobal->b[0];
	if (!es_blanco(where)) {
		strcpy(destino,where);
       if (*where=='+' ||*where=='-' ) {
           strcpy(destino,destino+1);
           if (bn->where) {
              strins(destino," AND ");
              strins(destino,bn->where);
            }
           v10log(LOGNORMAL,"WHERE modificada %s\n",destino);
        }
       if (bn->where) {
           free(bn->where);
        }
       bn->where=strdup(destino);
	   bn->pquery=1;
	}
	if (!es_blanco(order)) {
		if (bn->orderby) free(bn->orderby);
		bn->orderby=strdup(order);
		bn->pquery=1;
	}
	if (!fejecutaformaux) {
		ret=finputform(formglobal);	
	} else {
		fejecutaformaux(antform,formglobal,&ret);
	}
	liberaform(formglobal);
	formglobal=antform;
}
#define TWINVIEW 10

#define CSELPEND "SELECT SEQIMPRE FROM VDIMPRESPOOL WHERE ORDENADOR=VDUSER.GETHOSTNAME AND CODOPEINS=VDUSER.GETUSER AND STATUS=200"
static v10cursors *v10selpend;
void tratawinview(void)
{
	vdimprespools imsp;
	static long secimpre;
	int ret;
	static v10horas hult;
	if (damecent() - hult < TWINVIEW) return;
	hult = damecent();
	if (v10selpend == NULL) {
		v10selpend = abrecursordebug(CSELPEND,0);
		definetodo(v10selpend, &secimpre, sizeof(secimpre), V10LONG, NULL);
	}
	ret = ejefetchcursor(v10selpend);
	while (ret == 0) {
		ret = IMSPselvdimprespool(secimpre, &imsp);
		if (v10versionweb) {
			ponmensajepdf(imsp.fichero);
			encolatecla(1000);
		}
		imsp.status = 1000;
		IMSPactualizaimpreso(&imsp, 0);
		commit();
		ret = fetchcursor(v10selpend);
	}
}

void tratawinviewweb(void)
{
	vdimprespools imsp;
	static long secimpre;
	int ret;
	if (v10selpend == NULL) {
		v10selpend = abrecursor(CSELPEND);
		definetodo(v10selpend, &secimpre, sizeof(secimpre), V10LONG, NULL);
	}
	ret = ejefetchcursor(v10selpend);
	while (ret == 0) {
		ret = IMSPselvdimprespool(secimpre, &imsp);
		if (v10versionweb) {
			ponmensajepdf(imsp.fichero);
		}
		imsp.status = 1000;
		IMSPactualizaimpreso(&imsp, 0);
		commit();
		ret = fetchcursor(v10selpend);
	}
}
    

void vdinitform(int argc,char *argv[])
{
	double timeout=500;
    v10usaansi = 1;
   // printf("Path %s Pathv10 %s\n",getenv("PATH"),getenv("PATHV10"));
	trataparamstd(argc,argv,trataargform,NULL);
    set_cursor(SINCURSOR);
#ifndef __LINUX__
	asignatecla(F(1),(void *)v10help);
    inittrigexcel();
#endif
	asignatecla(MOUSEPOSM,apilamenu);
    asignatecla(ALT('L'), (void *)editalog);
	initform();
	declaratriger("WINVIEW", (void *)tratawinviewweb, NULL);
	funcionproteccion=dameproteccionvd;
	inittriguser();
	inittrigboton();
	inittrigersform("P");
    leedefines("VDST.H");
	inittrigcolores();	
    damecaracextracampo=leedefectocampo;
	damecaracextrabloque=leedefectobloque;
    defcapitaliza=FORMATOUPPER;
	initvdwhere();
    declarateclamenu("Menu", S_F(10));
    declarateclamenu("Consulta", F(2));
    defineteclaformdef(S_F(7), "FLLAMACOMENTARIO");
	while (es_blanco(vduser.codope)) pideusuario();
    protegidoform=9;
 	timeout=damepropentero("PAMAXIDDLE")*100;
    if (timeout==0) timeout=9999999999;
	if (!v10versionweb) declarav10timernt("INACTIVIDAD",(void (*)(v10timers *))reiniciaform,timeout,TIMERTIMEOUT,NULL);
	if (es_blanco(formdefecto)) {
		if (es_blanco(menudefecto)) strcpy(menudefecto,vduser.menuasociado);
		presentamenuform(menudefecto,"PROGRAMA DE PANTALLAS V10 SOLUCIONES","");
	} else {
		ejecutadirecto(formdefecto,wheredefecto,orderdefecto,opcionesdefecto);
	}
}


int main(int argc,char *argv[])
{
    printf("Inicio\n");
    trataparamstd(argc,argv,trataparampremain,NULL);
    printf("Premain\n");
    initv10lib(v10hinst,v10hprev);
    printf("eN LAS X\n");
    trataparamstd(argc,argv,trataparammain,NULL);
    trataparamstd(argc,argv,trataparamoracle,trataparamweb,NULL);
#ifndef __LINUX__
    if (v10versionweb) NUMEROICONO=102;
#endif
    ponv10traduce();
    v10formatdef=COMADECIMAL;
    cargahandleoraerr(argv[0],argv,argc);
    //tecla();
    if (v10versionweb) {
        v10runserverhttp();
        v10punterosweb(NULL,NULL,damepropentero("PAMAXIDDLE"));
        ponhostname(); // guarda en el paquete ORACLE el nombre de host        
        while (recibidologin==0) hay_tecla();
    } else {
        initlogoracle();
    }
	if (v10versionweb == 0) {
		pontrigervivo(tratawinview);
	}
 //   pontrigervivo(tratawinview);
    vdinitform(argc,argv);
    return(0);
}

#ifndef __LINUX__
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
    v10hinst=hinst;
    v10hprev=hprev;
	v10versionweb=0;
	onexit(ejecutaexit);
//	SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);
    ret=main(__argc,__argv);
    return(ret);
}
#endif