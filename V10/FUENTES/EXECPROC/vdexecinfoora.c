/*******************************************************************************
* Función Ejecutor de algoritmos estándar                                      *
* Módulo  vdvdexecinfoora.c                                                    *
*                                                                              *
* Autor  JCSR	                                                               *
* Revisado por:                                                                *
* Fecha 01-11-2007                                                             *
********************************************************************************

*******************************************************************************/

#include "vd.h"

#define CSETUSERNAME "BEGIN VDUSER.SETUSER(:USUARIO);END;"
static v10cursors *vdsetusername;


#define LSETUSER  71

static char susuario[LSETUSER];



static void finselinfoora(void)
{
	liberacursor(vdsetusername);
	vdsetusername=NULL;
}


static void initselinfoora(void)
{
	vdsetusername=abrecursordebug(CSETUSERNAME,1024);
	bindtodo(vdsetusername,"USUARIO",susuario,sizeof(susuario),V10CADENA,
						NULL);

	atexit(finselinfoora);
}

VDEXPORT int VDEXECsetusuario(char *usuario)
{
	if (vdsetusername==NULL) initselinfoora();
	strncpy(susuario,usuario,sizeof(susuario));
	ejecutacursor(vdsetusername);
	return(0);
}


