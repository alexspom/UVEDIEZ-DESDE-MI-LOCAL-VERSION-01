/*******************************************************************************
* M�dulo : VDRADMAIN.C                                                         *
* Funci�n: M�dulo principal del programa de radios                             *
*                                                                              *
* Autor  : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Hist�rico de cambios
* ====================
*******************************************************************************/
#include "vdradio.h"

raddrivers dr;
int MODIFRADIO;
char codrecursodef[LCODRECURSO];


static void vdinitradio(int argc,char *argv[])
{    
    v10usaansi=1;
    set_cursor(SINCURSOR);
    asignatecla(ALT('L'),(void *)editalog);
    initform();
    funcionproteccion=dameproteccionvd;
    inittrigersform("R");
    inittrigradio();
    cargadrivertelnet(&dr);
	ponprefijolog("");
}

static int trataparamradio(char *cadena) 
{
    if (*cadena=='R') {
        switch(cadena[1]) {
           case 'P': strcpy(dr.serviciotcp,cadena+2);
                     break;
            case 'N': dr.numports=atoi(cadena+2);
                if (dr.numports>MAXPORTRADIO) final(("Demasiados puertos %d maximo %d",dr.numports,MAXPORTRADIO))
                break;
           case 'I': if (atoi(cadena+2)==0) PRINSCAN=cadena[2];
                     else                   PRINSCAN=atoi(cadena+2);
                     break;
           case 'F': if (atoi(cadena+2)==0) FINSCAN=cadena[2];
                     else                   FINSCAN=atoi(cadena+2);
                     break;
           case 'S': CSUENA=atoi(cadena+2);
                     break;
           case 'T': strcpy(codrecursodef,cadena+2);
               break;
           case '2': if (atoi(cadena+2)==0) PRIN232=cadena[2];
                     else                   PRIN232=atoi(cadena+2);
                     break;
           case '3': if (atoi(cadena+2)==0) FIN232=cadena[2];
                     else                   FIN232=atoi(cadena+2);
                     break;
        }
    }
    return(0);
}

//#define milog(tipo, ...) {v10log(LOGNORMAL,"en funcion %s\n",__FUNCTION__);v10log(tipo,__VA_ARGS__);}

int main(int argc,char *argv[])
{
    initv10lib(v10hinst, v10hprev);
	trataparamstd(argc, argv, trataparammain, trataparamoracle, NULL);
	cargahandleoraerr(argv[0], argv, argc);
    v10usaansi=1;
    vdinitradio(argc,argv);
//    milog(LOGNORMAL,"PRUEBA DE LOG %d %s\n",1,"Cadena");
    trataparamstd(argc,argv,trataparamradio,NULL);
    dr.init();
    ejecutaimmediato("BEGIN VDUSER.SETUSER('VDRADIO');END;");
	if (actualizasid) funcactualizasid();
	defcapitaliza = FORMATOUPPER;
	initlogoracle();
	inittrigersform("R");
    leedefines("VDST.H");
    damecaracextracampo=leedefectocampo;
	damecaracextrabloque=leedefectobloque;
	CSUENA=damepropentero("SUENARAD");
    while (1) {
        int ret;
        ret=presentapantalla();
        if (ret==A_F(10)) break;
        Sleep(10);
    }
    return(0);
}

#ifndef __LINUX__
int PASCAL WinMain(HINSTANCE hinst,HINSTANCE hprev,
                   LPSTR cmd, int cmdshow)
{
    int ret;
	SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);
    ret=main(__argc,__argv);
    return(ret);
}
#endif