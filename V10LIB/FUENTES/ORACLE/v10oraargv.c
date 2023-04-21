/*
* Módulo : V10ORAARGV.C
* Objeto:  Tratamiento de mensajes windows
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"
int actualizasid=0;
static char ficheroini[MAXPATH]="v10.ini";
static int reintentos=-1;

static char encripta[]="SON TODOS UNA BANDA DE LADRONES";


static int pasadehex(char nibble)
{
  if (nibble>'9') return(nibble-'A'+10);
     else          return(nibble-'0');
}

static void desencripta(char *valor)
{
  char *ptr,*ptr1=valor;
  int lon=0,i;
  for (ptr=valor;*ptr;ptr+=2) {
      *ptr1++=(char)(pasadehex(*ptr)*16+pasadehex(ptr[1]));
      lon++;
   }
  for (i=0;i<lon;i++) valor[i]=(char)(valor[i]^encripta[i]);
  valor[i]=0;
}


static void dameusuarioini(char *donde)
{
   FILE *entrada;
   char buffer[MAXCADENA],variable[MAXCADENA];
   v10log(LOGNORMAL,"Intentando abrir fichero %s\n",ficheroini);
   entrada=fopenpath(ficheroini,"r");
   if (entrada==NULL) return;
   if (es_blanco(donde)) strcpy(variable,"SESIONDEF");
      else               strcpy(variable,donde);
   strmay(variable);
   while (fgetss(buffer,sizeof(buffer),entrada)) {
         char *aux=strchr(buffer,'=');
         strmay(buffer);
         if (aux) {
            *aux=0;
            if (strcmp(buffer,variable)==0) {
               desencripta(aux+1);
               strcpy(donde,aux+1);
               break;
             }
          }
    }
   fclose(entrada);
}

static int conectaoracle(char *usuario)
{
    char user[MAXCADENA];
    int ret;
    strcpy(user,usuario);
    dameusuarioini(user);
    do {
       ret=loginne(user,"","");
       if (ret) {
          v10log(LOGERROR,"Error de conexion %d\n",ret);
          if (hay_tecla()) if (tecla()==A_F(10)) final(("Abortado por el usuario"));
          if (--reintentos==0) break;
          Sleep(1000);
       } else v10log(LOGNORMAL,"%s","Conectado a base de datos\n");
    } while (ret);
    return(ret);
}

dbdrivers *damedbdriver(char *cadena)
{
	char dll[MAXPATH],funcion[MAXPATH];
	dbdrivers *(*func)(void);
	dbdrivers *ret;
	piece(cadena,dll,";",1);
	piece(cadena,funcion,";",2);
	if (es_blanco(funcion)) strcpy(funcion,"damedbdriver");
    v10log(LOGNORMAL, "Cargando driver %s funcion %s\n", dll, funcion);
	func=damefundll(dll,funcion);
	if (func == NULL) {
		final(("no puedo cargar la libreria %s\n", dll)) ;
}
	ret=func();
	return(ret);
}


int trataparamoracle(char *param)
{
    int ret;
    switch (toupper(*param)) {
           case 'O':   switch (toupper(param[1])) {
                              case 'D':   if (es_blanco(param+2)) oradebug=255;
                                             else                 oradebug=strtol(param+2,NULL,16);
                                          break;
                              case 'R':   reintentos=atoi(param+2);
                                          break;
                              case 'T':   ORATECLA = atoi(param + 2);
                                  break;
                              case 'F':   strcpy(ficheroini,param+2);
                                          break;
                              case 'I':   ejecutaimmediato(param+2);
                                          break;
                              case 'U':   if ((ret=conectaoracle(param+2))!=0) final(("Error de conexion %d",ret));
                                          asignatecla(ALT('D'),toggleoradebug);
                                          break;
                              case 'C':   {int mascara;
                                           char *aux=strchr(param,',');
                                           mascara=atoi(param+2);
                                           if (aux) {
                                               anadecursordebug(mascara,aux+1);
                                           }
                                          }
                                          break;
                              case 'E':   reusaexcel=atoi(param+1);
                                          break;
							  case 'P':   actualizasid=1;
                                          break;
							  case 'B':   switch (toupper(param[2])) {
							                 case 'O': 
#ifndef __LINUX__
                                                 pondefaultdrv(damedbdriver("v10oracle;damedriveroracle"));
#else
                                                 pondefaultdrv(damedbdriver("libv10oraclelinux;damedriveroracle"));
#endif
												       break;
											 case 'P': pondefaultdrv(damedbdriver("v10postgres;damedriverpostgre"));
												       break;
                                             case 'X': pondefaultdrv(damedbdriver(param+3));
                                                 v10log(LOGNORMAL,"Cargando libreria %s\n",param);
                                                 break;
										  }
                       }
    }
    return(0);
}

