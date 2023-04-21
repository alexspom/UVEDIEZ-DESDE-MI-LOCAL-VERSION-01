/*
* Módulo : V10ATEXIT.C
* Objeto:  Fuerza que los atexit se ejecuten en orden correcto segun estandar C
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MAXATEXITS 300

static void *fatexit[MAXATEXITS];
static int numatexit;

int v10atexit(void (*fun)(void))
{
	if (numatexit>=MAXATEXITS-1) return(1);
	fatexit[numatexit++]=fun;
	return(0);
}

int ejecutaexit(void)
{
	int i;
	void (*fun)(void);
	for (i=numatexit-1;i>=0;i--) {
		fun=fatexit[i];
		(*fun)();
	}
    return(0);
}