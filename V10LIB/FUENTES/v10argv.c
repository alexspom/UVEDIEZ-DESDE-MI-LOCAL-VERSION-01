/*
* Módulo : V10ARGV.C                                              
* Objeto:  Tratamiento de parametros de linea de comando
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

int MODODEBUG=0;
int MODOSERVICIO=0;
int servervisu=0;

int trataparammain(char *cadena)
{
    switch (toupper(*cadena)) {
          case 'L' :switch (toupper(cadena[1])) {
                       case 'F': filalog=atoi(cadena+2);
                                 break;
                       case 'N': initv10log(cadena+2);
                                 break;
                       case 'M': maxnivellog=atoi(cadena+2);
                                 break;
                       case 'L': logfun=atoi(cadena+2);
                                 break;
                       case 'A': logfile=atoi(cadena+2);
                                 break;
                    }
                    break;
          case 'S'  :switch(toupper(cadena[1])) {
                       case 'P': arrancaserverpantalla(cadena+2);
                                 break;
                       case 'L': arrancaserverlog(cadena+2);
                                 break;
					   case 'S': servervisu=atoi(cadena+2);
						         break;
                    }
                    break; 
    }
    return(0);
}

#ifndef __LINUX__
SHSTDAPI SetCurrentProcessExplicitAppUserModelID(_In_ PCSTR AppID);
#endif
int trataparampremain(char *cadena)
{
    switch (toupper(*cadena)) {
		  case 'D' :switch (toupper(cadena[1])) {
                       case 'N': initdinamica(cadena+2);
                                 break;
					   case 'F': precalculaficheros=atoi(cadena+2);
						         break;
                    }
                    break;
          case 'E' :switch (toupper(cadena[1])) {
                       case 'N': editorv10=cadena+2;
                                 break;
                       case 'M': editormonofichero=atoi(cadena+2);
                                 break;
                    }
                    break;
          case 'W' : switch (toupper(cadena[1])) {
                           case 'X': COLUMNASPANTALLA=atoi(cadena+2);
                                     break;
                           case 'Y':  LINEASPANTALLA=atoi(cadena+2);
                                     break;
                           case 'B' :V10BMP=cadena+2;
                               break;
                           case 'C' :menucerrar=0;
                               break;
                           case 'V' :strcpy(TITULOVENTANA,cadena+2);
                               break;
                           case 'I' :strcpy(idiomav10,cadena+2);
                               break;
                           case 'D' :MODODEBUG=atoi(cadena+2);
                               break;
                           case 'S' :MODOSERVICIO=atoi(cadena+2);
                               break;
                           case 'M' :MODOSHOW=SW_SHOWMINIMIZED;
							   break;
						   case 'E':_putenv(cadena + 2);
							   break;
#ifndef __LINUX__
						   case 'A':SetCurrentProcessExplicitAppUserModelID(cadena + 2);
							   break;
#endif
	          case 'G': singrafico = atoi(cadena + 2);
		          break;
                           case 'F': {char *aux;
                                      aux=strchr(cadena+2,',');
                                      if (aux) {
                                          *aux=0;
                                          cambiafontdefecto(cadena+2,-atoi(aux+1),0);
                                          *aux=',';
                                      } else cambiafontdefecto(cadena+2,-12,0);
                                     break;
                                     }
#ifdef __LINUX__		          
		                  case 'P': bitspixel = atoi(cadena + 2);
#endif		          
		                            break;
                     }
    }
    return(0);
}

int trataparamstd(int argc,char *argv[],...)
{
	int i,tratado=0;
 /* for (i=0;i<argc;i++) {
      va_list arg;
      int (*funcion)(char *param);
      if (*argv[i]!='-') continue;
	  va_start(arg,argv);
	  while ((funcion=va_arg(arg,void *))!=NULL) {
          if (funcion(argv[i]+1)) {
              if (tratado) v10log(LOGERROR,"Parametro %s ya tratado\n",argv[i]);
              tratado=1;
          }
	  }
  }*/
  
	int (*funcion)(char *param);
	va_list arg;
	va_start(arg,argv);
	while ((funcion=va_arg(arg,void *))!=NULL) {
		for (i=0;i<argc;i++) {
			if (*argv[i]!='-') continue;
			funcion(argv[i]+1);
		}
	}

  return(tratado);
}