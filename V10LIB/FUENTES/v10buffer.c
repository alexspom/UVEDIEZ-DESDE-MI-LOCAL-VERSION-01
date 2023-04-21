/*
* Módulo : V10BUFFER.C                                              
* Objeto:  Lectura de diferentes tipos de variable de un buffer
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXNUMBER 20

int BUFFERCONSP = 0;

double buffer2double(char *cadena,int lon,int dec,int sep)
{
  double ret;
  char buffer[MAXNUMBER];
  if (lon==0) return(0);
  if (BUFFERCONSP==0) lon--;
  strcopia(buffer,cadena,lon);
  ret=atof(buffer);
  if (sep==0 && dec) ret=ret/pow(10,dec);
  if (strlen(cadena)<lon) lon=strlen(cadena);
  strcpy(cadena,cadena+lon);
  return(ret);
}

long buffer2long(char *cadena,int lon)
{
  return((long)buffer2double(cadena,lon,0,0));
}

void buffer2cadena(char *cadena,char *donde,int lon)
{
  if (lon<=0) {
     if (donde) strcpy(donde,"");
     return;
   }
  if (donde) {
     strcopia(donde,cadena,lon-1);
     trim(donde);
   }
  if (BUFFERCONSP==0) lon--;
  if (strlen(cadena)<lon) lon=strlen(cadena);
  strcpy(cadena,cadena+lon);
}

v10dates buffer2fecha(char *cadena,int tipo)
{
  v10dates fecha;
  int lon=0;

  fecha=a2jul(tipo,cadena);
  switch (tipo) {
    case 0:return(0);
    case 1: lon=2+2+4+1;
	    break;
    case 2: lon=2+2+4+1;
	    break;
    case 3: lon=2+2+2+1;
	    break;
    case 7: lon=4+2+2+1;
	    break;
    case 4: lon=2+2+1;
	    break;
    case 5: lon=2+4+1;
	    break;
    case 6: lon=4+2+1;
	    break;
  }
  if (BUFFERCONSP==0) lon--;
  if (strlen(cadena)<lon) lon=strlen(cadena);
  strcpy(cadena,cadena+lon);
  return(fecha);
}


void buffer2hora(char *cadena,char *donde)
{
  buffer2cadena(cadena,donde,2+(BUFFERCONSP==0));
  if (*cadena==':') buffer2cadena(cadena,donde+2,1+(BUFFERCONSP==0));
  else donde[2]=':';
  buffer2cadena(cadena,donde+3,2+(BUFFERCONSP==0));
  if (*cadena==':') buffer2cadena(cadena,donde+5,1+(BUFFERCONSP==0));
  else donde[5]=':';
  buffer2cadena(cadena,donde+6,2+(BUFFERCONSP==0));
  if (BUFFERCONSP!=0) buffer2cadena(cadena,donde+8,1);
}
