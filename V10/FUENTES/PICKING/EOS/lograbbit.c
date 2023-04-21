#include "infopc.h"

   char *ordenador="127.0.0.1",*puerto="LOG0";

void miescribelog(int nivel,char *format,...)
{
  va_list arg;
  va_start(arg,format);
  return;
#ifdef __WIN32__
  vescribe_log(nivel,format,arg);
#else
	printf ("%s/%s:", ordenador, puerto);
  vprintf(format,arg);
#endif
}

lwsockets *lws;

int main(int argc,char *argv[])
{
   char buffer[MAXCADENA],*ptr=buffer;
   int ch;
	struct timeval espera = {0, 0};
    if (argc>1) ordenador=argv[1];
    if (argc>2) puerto=argv[2];
   sprintf(buffer,"Visualizando log ORDENADOR %s PUERTO %s",ordenador,puerto);
#ifdef __WIN32__
   SetWindowText(hwndpant,buffer);
   init_log_param("LOGRABBIT.LOG",1,1,NUMERO_COLUMNAS-2,50,"LOGRABBIT.ERR",1,52,NUMERO_COLUMNAS-2,1);
#endif
   lws=creacliente(ordenador,puerto);
   while (1) {
#ifdef __WIN32__
       int ret;
       if (hay_tecla()) {
          ret=tecla();
          if (ret==A_F(10)) break;
          if (ret>='1' && ret<='9') sendlwsocket(lws,&ret,1);
        }
#endif
       if (lws->status==STSOCKCERRADO) {
          reabrecliente(lws);
       }
       if ((ch=sigcarsocket(lws))!=-1) {
          *ptr++=(char)ch;
          if (ch=='\n') {
             *ptr=0;
             escribe_log(LOGPROGRESO,buffer);
             ptr=buffer;
           }
        }
		else
            nanosleep (&espera, NULL);
    }
   return(0);
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