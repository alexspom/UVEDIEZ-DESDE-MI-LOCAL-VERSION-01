#include "infopc.h"

#define TMAXIMO 1000

void miescribelog(int nivel,char *format,...)
{
  va_list arg;
  va_start(arg,format);
#ifdef __WIN32__
  vescribe_log(nivel,format,arg);
#else
	printf ("%s/%s:", ordenador, puerto);
  vprintf(format,arg);
#endif
}

lwsockets *lws;

void sustituyerc(char *cadena)
{
  char *aux;
  while ((aux=strstr(cadena,"\\n"))!=NULL) {
        *aux='\n';
        strcpy(aux+1,aux+2);
     }
}     

int main(int argc,char *argv[])
{
   char buffer[MAXCADENA],*ptr=buffer;
   int ch;
	struct timeval espera = {0, 0};
   char *ordenador;
   horas hinicio=llevocent();
//    char *ordenador="127.0.0.1",*puerto="LOG0";
    if (argc>1) ordenador=argv[1];
	    else     ordenador="127.0.0.1";
    if (argc<3) final(("Uso: llamaatelnet ordenador \"comando\""));
   sprintf(buffer,"Visualizando log ORDENADOR %s",ordenador);
#ifdef __WIN32__
   SetWindowText(hwndpant,buffer);
   init_log_param("LOGRABBIT.LOG",1,1,NUMERO_COLUMNAS-2,50,"LOGRABBIT.ERR",1,52,NUMERO_COLUMNAS-2,1);
#endif
   lws=creacliente(ordenador,"23");
   while (lws->status!=STSOCKABIERTO) Sleep(1);
   strcpy(buffer,argv[2]);
   sustituyerc(buffer);
   printflwsocket(lws,"%s\n",buffer);
   while (lws->status==STSOCKABIERTO) {
#ifdef __WIN32__
       if (hay_tecla()) if (tecla()==A_F(10)) break;
#endif
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
      if (llevocent()-hinicio>TMAXIMO) break;
    }
   return(0);
}



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

