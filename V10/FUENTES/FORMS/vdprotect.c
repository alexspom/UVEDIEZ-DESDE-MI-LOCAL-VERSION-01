/*******************************************************************************
* Módulo : vdprotect.c                                                         *
* Función: Tratamiento de protecciones de campos                               *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdform.h"

#define CSELPROTECCION "SELECT :CADENA FROM DUAL WHERE VDUSER.TENGOPRIVILEGIO(:CADENA)=1"
static v10cursors *vdselproteccion;

static char cadprivilegio[MAXCADENA];

static void finprivilegio(void)
{
	liberacursor(vdselproteccion);
}

static void initprivilegio(void)
{
	vdselproteccion=abrecursordebug(CSELPROTECCION,0);
	definetodo(vdselproteccion,cadprivilegio,sizeof(cadprivilegio),V10CADENA,
		                       NULL);
	bindtodo(vdselproteccion,"CADENA",cadprivilegio,sizeof(cadprivilegio),V10CADENA,
		                     NULL);
	atexit(finprivilegio);
}

int dameproteccionvd(char *cadena)
{
	int ret;
	if (vdselproteccion==NULL) initprivilegio();
	strcpy(cadprivilegio,cadena);
	ret=ejefetchcursor(vdselproteccion);
    return(ret);
}
