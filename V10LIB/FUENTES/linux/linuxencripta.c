/*******************************************************************************
* M�dulo : v10encripta.c                                                       *
* Funci�n: Bajo nivel de comunicacion con criptoapi de windows                 *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 10-01-2007                                                          *
********************************************************************************
* Hist�rico de cambios
* ====================
*
*******************************************************************************/
#include "v10.h"

#define MAXHEXA MAXCADENA



static int digitohexa(int a)
{
        int ret;
        if (a>9) ret=a-10+'A';
         else     ret=a+'0';
        return(ret);
}

static char *pasaahexa(char *origen,int len,char *destino)
{
        char mihexa[MAXPATH],*ptr;
        int i;
        if (destino==NULL) destino=mihexa;
        ptr=destino;
    for (i=0;i<len;i++) {
        *ptr++=digitohexa(origen[i]>>4);
                *ptr++=digitohexa(origen[i]&0xf);
        }
        *ptr=0;
        return(destino);
}

int damehash(char *origen,char *destino)
{
    char mihash[MAXCADENA]="";
    SHA1(origen,strlen(origen),
                 mihash);
    pasaahexa(mihash,20,destino);
    return(0);
}


