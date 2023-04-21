#include "info4.h"
#include <stdio.h>

static infolineas *linea={0};

#define TRECONECTA 200

int main(int argc,char *argv[]){
    int port=0;
    v10horas hinicio, hfin, hconnect;
    struct timeval espera = {0, 0};

    if (argc>1) port=atoi(argv[1]);
    initv10log("INFO4.LOG");

#ifdef WIN32
    linea=calloc(1,sizeof(infolineas));
#else
/*	if ((ident_sm=shmget(30000+port, sizeof(infolineas), IPC_CREAT))<0) 
        v10log (LOGERROR, "No se ha creado el segmento de memoria compartida\n");
	else v10log (LOGERROR, "Se ha creado el segmento de memoria compartida, %d\n", ident_sm);
	linea=shmat (ident_sm, NULL, 0);
	memset (linea, 0, sizeof(infolineas));*/
#endif

   linea->port=port;
   initlinea(linea);
   hconnect=damecent();
   while (1) {
         hinicio=damecent();
         if (linea->vds==NULL && hinicio-hconnect>TRECONECTA) {
            char servicio[MAXPATH];
            sprintf(servicio,"LINEA%d",linea->port);
            linea->vds=creaservidor(servicio);
            hconnect=hinicio;
         }
	     if (automatalinea(linea)) break;
 	     automatapc(linea);
         linea->bucles++;
         while ((hfin=damecent())-hinicio<linea->tciclo) {
            espera.tv_usec=(long)(linea->tciclo-(hfin-hinicio))*10000;
            nanosleep (&espera, NULL);
         }
	}
    
    return(0);
}

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret=0;
  v10hinst=hinst;
  v10hprev=hprev;
  COLUMNASPANTALLA=160;
  LINEASPANTALLA=55;
  trataparamstd(_argc,_argv,trataparampremain,NULL);
  initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,CW_USEDEFAULT,CW_USEDEFAULT,
                   0,0,COLUMNASPANTALLA,LINEASPANTALLA,ESTILOV10,0,NULL,0,0,NULL);
  trataparamstd(_argc,_argv,trataparammain,NULL);
  ret=main(_argc,_argv);
  return(ret);
}

