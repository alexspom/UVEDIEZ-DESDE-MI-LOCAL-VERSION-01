#include "infopc.h"

#define TRECONECTA 100

typedef struct {
           int alertas[MAXALERTAS];


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

static int calcstgloblin(ethlineas *lin)
{
  int i,st;
  int ndglob;
  ndglob=pdisplin(lin);
  st=0;
  for (i=0;i<lin->numdisp;i++) {
      displays *disp=damedisplayid(TIPOIDNUMDISP,ndglob+i);
      if (disp==NULL) continue;
      st|=disp->status[0];
    }
  return(st);
}


void presentainfo(void)
{
  lwsockets *sockmaster=NULL;
  horas  hconnect=0,hinicio;
  while (1) {
       hinicio=llevocent();
       if (sockmaster==NULL && hinicio-hconnect>TRECONECTA) {
          char servicio[MAXPATH];
          sprintf(servicio,"MASTER");
          sockmaster=creaservidor(servicio);
          hconnect=hinicio;
         }
       tickhleth();
       Sleep(10);
       if (hay_tecla()) if (tecla()==A_F(10)) break;;
    }
}

int main(int argc,char *argv[])
{
//   maxnivellog=1000;
   modotest=1;
   init_log("MASTER.LOG","MASTER.ERR");
   if (argc<2) initinfopick("192.168.0.29","127.0.0.1",NULL);
      else     initinfopick(argv[1],argc>2?argv[2]:NULL,argc>3?argv[3]:NULL,argc>4?argv[4]:NULL,argc>5?argv[5]:NULL);
   presentainfo();
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