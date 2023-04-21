/*
* Módulo : v10trans.c
* Objeto:  Soporte para traduccion de aplicaciones
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

char idiomav10[LIDIOMAV10];

static char *v10trans(char *cadena)
{
    return(cadena);
}

static char *v10untrans(char *cadena)
{
    return(cadena);
}

char *(*v10translate)(char *cadena)=v10trans;
char *(*v10untranslate)(char *cadena)=v10untrans;

void setv10transdef(void)
{
    v10translate=v10trans;
    v10untranslate=v10untrans;
}

void setv10trans(char *(ftrans)(char *cadena),char *(funtrans)(char *cadena))
{
    v10translate=ftrans;
    v10untranslate=funtrans;
}