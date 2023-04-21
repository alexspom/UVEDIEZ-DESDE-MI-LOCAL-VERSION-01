/*
* Módulo :  V10ABORTA.C
* Objeto:   Funciones para abortar programa con mensaje
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"
unsigned long warning_time = 0;
static char file[MAXPATH];
static int line;
void (*prefinal)(char *error);  
void (*prewarning)(char *error);


void pon_puntero_error(char *fichero,int linea)
{
  strcpy(file,fichero);
  line=linea;
}


void STDv10error(char *formato,va_list lista_param_variable,short salir)
{
  windows v;
  char resul[200];
  static int ya_exit;
  unsigned timeout;
  void *triger;
  void *trigervivo;
  char *msgerror;

  if (ya_exit) return;
  trigervivo=dametrigervivo();
  pontrigervivo(NULL);
  dametimeoutteclado(&timeout,&triger);
  timeoutteclado(0,NULL);                               
  
  
  strcpy(resul," Causa: ");
  creaventana("ATENCION",&v,COLUMNASPANTALLA/2-35,LINEASPANTALLA/2-2,COLUMNASPANTALLA/2+34,LINEASPANTALLA/2+4,"ERROR");
  v.cursorx=22;
  v.cursory=0;
  formato=v10translate(formato);
  if (salir) {
    v.cursorx=22;
    escribec(&v,"!!!! ERROR !!!!\n\n");
  }
  else {
    v.cursorx=21;
    escribec(&v,"!!!! WARNING !!!!\n\n");
  }
  msgerror=resul+strlen(resul);
  vsprintf(resul+strlen(resul),formato,lista_param_variable);
  v10log(LOGERROR,"%s",msgerror);
  v10logch(LOGERROR,0,"\n",0);
  escribec(&v,resul);

  if (*file) {
    sprintf(resul,"\n\n Fichero: %s Linea: %d",file,line);
    escribec(&v,resul);
  }

  if (salir) {
    escribec(&v,"\n\n         Programa abortado, pulse cualquier tecla");
    if (prefinal) prefinal(resul);
    STDtecla();
    ya_exit=1;
  } else {
    if (!warning_time) {
      escribec(&v,"\n\n         Para continuar, pulse cualquier tecla");
      if (prewarning) prewarning(resul);
      STDtecla();
    }
    else {
      v10horas conta = gettime();

      while ((gettime()-conta < warning_time) && ((hay_tecla()==0)));
    }
  }
  liberaventana(&v);
  if (salir) exit(1);
  timeoutteclado(timeout,triger);
  pontrigervivo(trigervivo);
}

void mifinal(char *formato,...)
{
  va_list lista_param_variable;

  while (hay_tecla()) tecla();
  va_start(lista_param_variable,formato);  
  v10error(formato,lista_param_variable,1);
  va_end(lista_param_variable);
}

void miwarning(char *formato,...)
{
  va_list lista_param_variable;
  va_start(lista_param_variable,formato);
  v10error(formato,lista_param_variable,0);
  va_end(lista_param_variable);
}
