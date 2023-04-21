/*
* Módulo : EOSPRINTF.C
* Objeto: Impresion en displays de la gama EOS
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/
#include "eos.h"

unsigned long version=0x30323230;

void vlindisplayprintf(eoslineas *linea,int disp,char *format,va_list arg)
{
    char cadena[MAXCADENA];
    eosdisps *di;
    if (disp>linea->numdisp || disp<0) return;
    di=linea->disp+disp;
    vsprintf(cadena,format,arg);
    if (di->tipodisp && di->version<0x30323030) pad(cadena,di->tipodisp->digitos);
    strcpy(di->valor,cadena);
    linea->modifida=1;
}

void lindisplayprintf(eoslineas *linea,int disp,char *format,...)
{
    va_list arg;
    va_start(arg,format);
    vlindisplayprintf(linea,disp,format,arg);
    va_end(arg);
}

void linponlucesdisplay(eoslineas *linea,int disp,int luz,int valor)
{
    eosdisps *di;
    if (valor>3) valor=3;
    if (disp>linea->numdisp || disp<0) return;
    di=linea->disp+disp;
    di->luces[luz]=(unsigned short)valor;
    linea->modifida=1;
}

