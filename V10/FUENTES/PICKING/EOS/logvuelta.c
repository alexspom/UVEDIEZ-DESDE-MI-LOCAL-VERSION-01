#include "eos.h"
#include <stdio.h>


int main(int argc, char **argv)
{
   FILE *salida;
   salida=fopens("salida","a+");
   if (initpuerto232(4,115200,NOPARITY,8,ONESTOPBIT)!=0) final(("No puedo abrir puerto %d\n",5));
   while (1) {
         while (haycar232(4)) {
               int ret;
               ret=sig_carr(4);
               fprintf(salida,"%02x ",ret);
               if (ret==0xfe) fprintf(salida,"\n");
           }
         if (hay_tecla()) if (tecla()==A_F(10)) break;
         esperamensaje(1);
   }
   fclose(salida);
	return( 0 );
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