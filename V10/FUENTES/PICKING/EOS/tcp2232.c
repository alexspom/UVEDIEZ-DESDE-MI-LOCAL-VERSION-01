#include "eos.h"
#include <stdio.h>
#include <errno.h>

   char *ordenador="127.0.0.1";

v10sockets *v10s,*nuevo;
int port232;
//#define BAUDRATE 19200
#define BAUDRATETCP2232 B57600
void miescribelog(int nivel,char *format,...)
{
  va_list arg;
  va_start(arg,format);
  return;
#ifdef __WIN32__
  vescribe_log(nivel,format,arg);
#else
// 	printf ("%s/%s:", ordenador, puerto);
	printf ("%s/%d:", v10s->origen.sa_data, port232);
  vprintf(format,arg);
#endif
}


void init(char *servicio,int port)
{
  v10s=creaservidor(servicio);
  if (port>=0) if (initpuerto232(port,BAUDRATETCP2232,NOPARITY,8,ONESTOPBIT)!=0){
	 final(("No puedo abrir puerto %d\n",port+1));
	}
}


int main(int argc, char **argv)
{
	int ret;
#ifndef __WIN32__
	unsigned char buffer[MAXCADENA];
    int ident_sm;
#endif
	if (argc<3) {
		printf(("Uso tcp2232 puerto_tcp puerto232\n"));
		return(-1);
	}
	usleep(5000000);
        initv10log("TCP2232.LOG");
	port232=atoi(argv[2]);
	init(argv[1],port232);
#ifdef __LINUX__
	if ((ident_sm=shmget(30000+port232, sizeof(char), IPC_CREAT))<0) 
	  escribe_log (LOGERROR, "No se ha creado el segmento de memoria compartida\n");
	else escribe_log (LOGERROR, "Se ha creado el segmento de memoria compartida, %d\n", ident_sm);
// 	linea=shmat (ident_sm, NULL, 0);
// 	memset (linea, 0, sizeof(eoslineas));
#endif
	while (1) {
		verificasocket(v10s);
		if (v10s->status==STSOCKABIERTO && nuevo==NULL) {
		   nuevo=creaservidor(argv[1]);
		}
		if (nuevo) {
		  if (nuevo->status==STSOCKABIERTO) {
		     close(v10s->soc);
		     v10s->status=STSOCKCERRADO;
		   }
		}
		if (v10s->status==STSOCKCERRADO) {
		  if (nuevo) {
		     free(v10s);
		     v10s=nuevo;
		     nuevo=NULL;
		  } else {
		    reabreservidor(v10s);
		  }
		}
		if (port232>=0) {
#ifdef __WIN32__
			while (haycar232(port232)) {
				ret=sig_carr(port232);
				sendv10ssocket(v10s,&ret,1);
			}
#else
			ret=read(puerto232[port232], buffer, MAXCADENA);
			if (ret>0)
			  sendv10socket (v10s, buffer, ret);
// 			else if (errno!=11)
// 			  escribe_log(LOGDEBUG,"Error en Read File: %d %s %d \n", ret, strerror(errno), errno);
#endif
		}
		while (haycarsocket(v10s)) {
				int ret;
				ret=sigcarsocket(v10s);
				if (port232>=0) encolae(port232,ret);
				escribe_log(LOGNORMAL,"Recibido %c %d\n",ret,ret);
		}
#ifdef __WIN32__
		if (hay_tecla()) if (tecla()==A_F(10)) break;
#endif
		esperamensaje(1);
	}
	return( 0 );
}

#ifdef __WIN32__
#pragma warn -par
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hprev,
           LPSTR cmd, int cmdshow)
{
  int ret;
  lwhinst=hinst;
  lwhprev=hprev;
  NUMERO_COLUMNAS=160;
  NUMERO_LINEAS=55;
  strcpy(TITULOVENTANA,_argv[0]);
  initapptxt(hinst,hprev,SW_SHOWMAXIMIZED,TITULOVENTANA,DEFTEXTX,DEFTEXTY,
                   0,0,NUMERO_COLUMNAS,NUMERO_LINEAS,LWSTYLE,0,NULL,0,0,NULL);
  ret=main(_argc,_argv);
  return(ret);
}
#pragma warn +par
#endif
