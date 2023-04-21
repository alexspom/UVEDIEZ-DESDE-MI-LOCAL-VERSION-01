#include "info4.h"

unsigned long version=0x30313038;

static void vlindisplayprintf(infolineas *linea,int disp,char *format,va_list arg)
{
  char cadena[MAXCADENA];
  infodisps *di;
  if (disp>linea->numdisp || disp<0) return;
  di=linea->disp+disp;
  vsprintf(cadena,format,arg);
  if (di->tipodisp) pad(cadena,di->tipodisp->digitos);
  strcpy(di->valor,cadena);
  linea->modifida=1;
}

void lindisplayprintf(infolineas *linea,int disp,char *format,...)
{
  va_list arg;
  va_start(arg,format);
  vlindisplayprintf(linea,disp,format,arg);
  va_end(arg);
}

void linponlucesdisplay(infolineas *linea,int disp,int luz,int valor)
{
  infodisps *di;
  if (disp>linea->numdisp || disp<0) return;
  di=linea->disp+disp;
  di->luces[luz]=(unsigned short)valor;
  linea->modifida=1;
}

