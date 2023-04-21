/*
* Módulo : V10DLL.C                                             
* Objeto:  Tratamiento de funciones definidas en DLL
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXLIB 40

typedef struct {
          char *nombre;
          HINSTANCE  hinst;
        } librerias;

static librerias lib[MAXLIB];
static int numlib;

static void findll(void)
{
    int i;
    for (i=0;i<numlib;i++) {
        free(lib[i].nombre);
//        FreeLibrary(lib[i].hinst); Evita un bug realmente raro en la libreria
    }
}

void unloaddll(char *libreria)
{
    int i;
    for (i=0;i<numlib;i++) if (strcmp(libreria,lib[i].nombre)==0) break;
    if (i<numlib) {
        FreeLibrary(lib[i].hinst);
        lib[i].hinst=NULL;
    }
}



void *damefundllex(char *libreria,char *funcion,int decora)
{
    int i;
    void *fun;
    char nombre[MAXPATH];
    for (i=0;i<numlib;i++) if (strcmp(libreria,lib[i].nombre)==0) break;
    if (i==numlib) {
        HINSTANCE hinst;
        hinst=LoadLibrary(libreria);
        if (hinst==NULL) {
            v10log(LOGERROR,"No existe la libreria %s\n",libreria);
            return(NULL);
        }
        if (numlib==0) atexit(findll);
        lib[i].nombre=strdup(libreria);
        lib[i].hinst=hinst;
        numlib++;
    } else {
        if (lib[i].hinst==NULL) {
            lib[i].hinst=LoadLibrary(libreria);
        }
    }
    if (decora) sprintf(nombre,"_%s",funcion);
    else     strcpy(nombre,funcion);
    fun=GetProcAddress(lib[i].hinst,nombre);
    if (fun==NULL) v10log(LOGERROR,"No existe la funcion %s en la libreria %s\n",nombre,libreria);
    return(fun);
}

void *damefundll(char *libreria,char *funcion)
{
    return(damefundllex(libreria,funcion,0));
}

