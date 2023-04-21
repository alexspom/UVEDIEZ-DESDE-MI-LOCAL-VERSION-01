/*
* Módulo : V10VIRTLISTA.C
* Objeto:  Tratamiento de listas virtuales indexadas por funcion
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"


int v10busca(void *lista,char *(*indexa)(void *,int),char *buffer,int *unico)
{
  int encontrado = -1;
  char *ptr;
  int i;

  for (i=0;(ptr=indexa(lista,i))!=NULL;i++) {
    while (*ptr && isspace(*ptr)) ptr++;
    if (strnicomp(ptr,buffer,strlen(buffer))==0) {
      if (unico==NULL) return(i);
      if (encontrado!=-1) {
        *unico=0;
        return(encontrado);
      }
      else encontrado=i;
    }
  }
  if (encontrado!=-1) {
    *unico=1;
    return(encontrado);
  }
  return(-1);
}
