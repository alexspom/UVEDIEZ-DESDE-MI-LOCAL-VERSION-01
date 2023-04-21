#include "v10wwwform.h"

int main(int argc,char *argv[])
{
	static char ficheroconf[MAXCADENA]="v10listener.cfg";
	//HWND ventanaact;     

	if (argc>1) strcpy(ficheroconf,argv[1]);
	sprintf(TITULOVENTANA,"Servidor de Ficheros V10 HTTP 1.1. Fichero configuracion: %s",ficheroconf);
	COLUMNASPANTALLA=99;
	//ventanaact=FindWindow(NULL,TITULOVENTANA);
	//if (ventanaact!=NULL) exit(0); // ya existe el programa
    trataparamstd(argc,argv,trataparampremain,NULL);
    initv10lib(v10hinst,v10hprev);
	trataparamstd(argc, argv, trataparammain, trataparamoracle, NULL);
	v10usaansi=1;
	usa_colores("PICVENT");
        v10runserverfiles(ficheroconf);
	return(0);
} 

#ifndef __LINUX__
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
				   LPSTR cmd, int cmdshow)
{
    main(__argc,__argv);
} 
#endif
