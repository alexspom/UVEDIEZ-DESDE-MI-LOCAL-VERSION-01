#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include "infodll.h"
int es_blanco(char *dest)
{
  while (*dest) {
        if (*dest!=' ') return(0);
     }
  return(1);
} 
char *infodameversion(unsigned long version)
{
  static char cversion[sizeof(long)+2];
  cversion[4]=0;
  cversion[3]=(char)(version&0xff);
  cversion[2]=(char)((version>>8)&0xff);
  cversion[1]=(char)(((version>>16)&0xff)+128-'0');
  cversion[0]=(char)((version>>24)&0xff);
  return(cversion);
}

static void pruebadisplays(void)
{
   //Funcion periodica que es INDISPENSABLE llamar
   tickhleth();
   //Si hay una tecla pulsada
   if (haytecladisp()) {
      tecladisps tec;
	  //Recojo la tecla pulsada
      tecladisp(&tec);
//      printf("Recibida tecla %d de display %d\n",tec.boton,tec.serie);
      switch (tec.boton) {
		  // Si es la tecla F direcciono el display por numero de serie y escribo el numero de serie
          case TECLAFUNCION: displayprintf(tec.numdisp,"%s",infodameversion(tec.version));
                            togglelucesdisplay(tec.numdisp,TECLAACEPTA+2);
                            break;
          // Si es la tecla validar y el display esta en blanco pongo 8888 y enciendo luces 1,4,5 direcciono por numero de display
		  // Si no apago luces y pongo display en blanco
          case TECLAACEPTA: {displays *pdisp=damedisplay(tec.numdisp);
                             if (es_blanco(pdisp->valor))  {
                                displayprintf(tec.numdisp,"8888");
                                lucesdisplay(tec.numdisp,3,1);
                                lucesdisplay(tec.numdisp,4,1);
                                lucesdisplay(tec.numdisp,5,1);
                              } else {
                                displayprintf(tec.numdisp,"");
                                lucesdisplay(tec.numdisp,1,0);
                                lucesdisplay(tec.numdisp,2,0);
                                lucesdisplay(tec.numdisp,3,0);
                                lucesdisplay(tec.numdisp,4,0);
                                lucesdisplay(tec.numdisp,5,0);
                              }
                            break;
                            }
		  // si Pulsan mas pongo el numero de display
          case TECLAMAS:    displayprintf(tec.numdisp,"%d",tec.numdisp);
                            togglelucesdisplay(tec.numdisp,TECLAMAS+2);
                            break;
		  // Pulsan tecla menos pongo el numero de serie del display
          case TECLAMENOS:  displayprintf(tec.numdisp,"%d",tec.serie);
                            togglelucesdisplay(tec.numdisp,TECLAMENOS+2);
                            break;
       }
    }
}


int main(int argc,char *argv[])
{
   modotest=0; //Displays en modo normal
   // Si no recibo parametros trato de conectar con localhost
   // en otro caso conecto con los ehternet-box cuyas IP se pasan como parametros
   maxnivellog=3;
   TSTATLINEA=100;
   tipoidentdisp=TIPOIDNUMDISP;
   if (argc<2) initinfopick("127.0.0.1",NULL);
      else     initinfopick(argv[1],argc>2?argv[2]:NULL,argc>3?argv[3]:NULL,argc>4?argv[4]:NULL,argc>5?argv[5]:NULL);
	  while (1) {
		  pruebadisplays();
		  Sleep(1);
	  }
   return(0);
}
