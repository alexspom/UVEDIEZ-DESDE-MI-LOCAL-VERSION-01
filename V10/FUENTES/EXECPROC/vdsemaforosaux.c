/*******************************************************************************
* Función  Rutinas auxiliares de tratamiento de semaforos                      *
* Módulo  vdsemaforosaux.c                                                     *
*                                                                              *
* Autor  JCSR	                                                               *
* Revisado por:                                                                *
* Fecha 01-11-2007                                                             *
********************************************************************************

*******************************************************************************/


#include "vdexec.h"

/*! \brief Activa un semáforo que está desactivado\n
           Si está desactivado devuelve SUCCESS, cualquier otro valor en caso contrario.
    \param semaforo Nombre del semáforo
	@ingroup Semaforos
*/
VDEXPORT int SEFactivasemaforo(char *semaforo)
{
    vdsemafoross sef;
    int ret;
     if((ret=SEFselsemaforolibre(semaforo,&sef))==0){
        *sef.activo='S';
        SEFactualizasemaforo(&sef,0);
    }
    return(ret);
}

VDEXPORT int SEFliberasemaforo(char *semaforo)
{
    vdsemafoross sef;
    int ret;
    if((ret=SEFselsemaforo(semaforo,&sef))==0){
        *sef.activo='N';
        SEFactualizasemaforo(&sef,0);
    }
    return(ret);
}

VDEXPORT int semaforoenverde (PTRPROCESOS *proc){
	int ret=1;
	if ((*proc)->proc.sema[0]) {
		if ((ret=SEFactivasemaforo((*proc)->proc.sema))==0){
			v10log(LOGERROR,"procesamovst - SEMAFORO %s ACTIVADO\n",(*proc)->proc.sema);
		}
		commit();
		ret=0;
	}
	return (ret);
}

VDEXPORT int liberasemaforo(PTRPROCESOS *proc){
	int ret=0;
	if ((*proc)->proc.sema) {
		ret=SEFliberasemaforo((*proc)->proc.sema);
		if (!ret)commit();
	}
	return (ret);
}