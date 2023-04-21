#include "eos.h"
static eoslineas *linea={0};

#define TRECONECTA 200
v10sockets *nuevo;
char servicio[MAXPATH];
int comprobandoconexion;
v10horas hultconex;
#define TIMEOUTTEST 200

void tratasocket(eoslineas *linea)
{
	verificasocket(linea->v10s);
	if (linea->v10s->status==STSOCKABIERTO && nuevo==NULL) {
		nuevo=creaservidor(servicio);
		escribe_log (LOGERROR,"Abierto servidor en espera %s\n",servicio);
	}
	if (nuevo) { 
		if (nuevo->status==STSOCKABIERTO) {
			if (comprobandoconexion==0) {
				escribe_log (LOGERROR,"Nueva conexion\n");
				if (linea->modotest) {
					comprobandoconexion=1;
					hultconex=damecent();
				}
				if (comprobandoconexion==0) {
					closesocket(linea->v10s->soc);
					linea->v10s->status=STSOCKCERRADO;
				}
			}
			if (comprobandoconexion==1) {
				if (damecent()-hultconex>TIMEOUTTEST) {
					escribe_log(LOGNORMAL,"Rechazada conexion por no ser test\n");
					liberav10socket(nuevo);
					nuevo=NULL;
					comprobandoconexion=0;
				} else {
					if (haycarsocket(nuevo)) {
						int ret;
						if ((ret=sigcarsocket(nuevo))==RESTRICTED) {
							comprobandoconexion=0;
							closesocket(linea->v10s->soc);
							linea->v10s->status=STSOCKCERRADO;
						} else {
							escribe_log(LOGNORMAL,"Rechazada conexion por no ser test %d %d\n",ret,RESTRICTED);
							liberav10socket(nuevo);
							nuevo=NULL;
							comprobandoconexion=0;
						}
					}
				}
			}
		}
	}
   if (linea->v10s->status==STSOCKCERRADO) {
       linea-> modifestrucpc=1;
       if (nuevo) {
          free(linea->v10s);
          linea->v10s=nuevo;
          nuevo=NULL;
		  comprobandoconexion=0;
		  linea->modotest=0;
        } else {
          reabreservidor(linea->v10s);
        }
    }
}

#ifdef __NETOS__

#include "watchdog.h"
void main_eos(int port)
{
	long espera=10;
#else
int main(int argc, char **argv)
{
   int port=0;
#endif
   v10horas hinicio,hfin,hconnect;
#ifdef __WIN32__
	struct timeval espera = {0, 0};
#endif
#ifdef __LINUX__
    int ident_sm;
	struct timespec espera = {0, 0};
#endif

#ifndef __NETOS__
   if (argc>1) port=atoi(argv[1]);
	//initv10log("EOS.LOG");
#endif

#ifdef __WIN32__
   linea=calloc(1,sizeof(eoslineas));
#endif
#ifdef __LINUX__
	if ((ident_sm=shmget(30000+port, sizeof(eoslineas), IPC_CREAT))<0) escribe_log (LOGERROR, "No se ha creado el segmento de memoria compartida\n");
	else escribe_log (LOGERROR, "Se ha creado el segmento de memoria compartida, %d\n", ident_sm);
	linea=shmat (ident_sm, NULL, 0);
	memset (linea, 0, sizeof(eoslineas));
#endif
    if (argc>1) port=atoi(argv[1]);

   linea->port=port;
   sprintf(servicio,"LINEA%d",linea->port);
   initlinea(linea);
   hconnect=damecent();

   while (1) {
#ifdef __WIN32__
         if (hay_tecla()) if (tecla()==A_F(10)) break;
#endif
#ifdef __NETOS__
		watchdogServicePeriodically();
#endif

         hinicio=damecent();
         if (linea->v10s==NULL && hinicio-hconnect>TRECONECTA) {
            sprintf(servicio,"LINEA%d",linea->port);
            linea->v10s=creaservidor(servicio);
            hconnect=hinicio;
         }
	 if (automatalinea(linea)) break;
	 tratasocket(linea);
 	 automatapc(linea);
         linea->bucles++;
         while ((hfin=damecent())-hinicio<linea->tciclo) {
#ifdef __WIN32__
            espera.tv_usec=(LONG)((linea->tciclo-(hfin-hinicio))*10000);
#endif
#ifdef __NETOS__
            espera=(linea->tciclo-(hfin-hinicio));
#endif
#ifdef __LINUX__
           espera.tv_nsec=(linea->tciclo-(hfin-hinicio))*10000;
#endif
#ifndef __NETOS__
			nanosleep (&espera, NULL);
#endif
          }
	}
#ifndef __NETOS__
	return( 0 );
#endif
}

#ifdef __WIN32__
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  initv10lib(hinst,hprev);
  trataparamstd(__argc,__argv,trataparammain,NULL);
  ret=main(__argc,__argv);
  return(ret);
}
#endif
