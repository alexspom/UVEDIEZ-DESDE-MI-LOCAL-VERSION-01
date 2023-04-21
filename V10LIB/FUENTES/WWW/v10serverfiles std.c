#include "v10wwwform.h"


int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
				   LPSTR cmd, int cmdshow)
{
	static char ficheroconf[MAXCADENA]="v10listener.cfg";
	HWND ventanaact;

	v10hinst=hinst;
	v10hprev=hprev;

	if (_argc>1) strcpy(ficheroconf,_argv[1]);
	sprintf(TITULOVENTANA,"Servidor de Ficheros V10 HTTP 1.1. Fichero configuracion: %s",ficheroconf);
	COLUMNASPANTALLA=99;
	ventanaact=FindWindow(NULL,TITULOVENTANA);
	if (ventanaact!=NULL) exit(0); // ya existe el programa
	initapptxt(hinst,hprev,SW_SHOWMINIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
		0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
	v10usaansi=1;
	usa_colores("PICVENT");
	initv10log("v10serverfiles.log");
//	v10runserverfiles(ficheroconf);
	__try {
        v10runserverfiles(ficheroconf);
    } __except(EXCEPTION_EXECUTE_HANDLER) {return -1;};
	return(0);
} 
