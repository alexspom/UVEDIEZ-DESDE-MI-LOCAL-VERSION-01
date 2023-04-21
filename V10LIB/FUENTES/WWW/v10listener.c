#include "v10wwwform.h"

int main(int argc,char *argv[])
{
	//HWND ventanaact;
	static char ficheroconf[MAXCADENA]="v10listener.cfg";
#ifdef __LINUX__
	signal(SIGCHLD, SIG_IGN);	
#endif	
	if (argc>1) strcpy(ficheroconf,argv[1]);
	sprintf(TITULOVENTANA,"Listener V10 HTTP 1.1. Fichero configuracion: %s",ficheroconf);
	COLUMNASPANTALLA=99;
	//ventanaact=FindWindow(NULL,TITULOVENTANA);
	//if (ventanaact!=NULL) exit(0); // ya existe el programa
    trataparamstd(argc,argv,trataparampremain,NULL);
    initv10lib(v10hinst,v10hprev);
    trataparamstd(argc,argv,trataparammain,NULL,NULL);
    {int i;
      for (i=0;i<argc;i++) v10log(LOGDEBUG,"Parametro %d %s\n",i,argv[i]); 
    }
	trataparamstd(argc, argv, trataparamoracle, NULL,NULL);
	v10usaansi=1;
	v10runlistener(ficheroconf);
}

#ifndef __LINUX__
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
				   LPSTR cmd, int cmdshow)
{

	v10hinst=hinst;
	v10hprev=hprev;
    main(__argc,__argv);
	return(0);
} 
#endif
