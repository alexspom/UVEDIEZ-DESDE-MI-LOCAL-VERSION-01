/***************************************************************************************
* M�dulo: VDEXEC.H                                                                     *
* Prop�sito: 	  			   *
* Autor:                                              *
* Fecha:                                                    *
*                                                                                      *
****************************************************************************************/
#ifndef __VDEXEC__H__
#define __VDEXEC__H__


#include "vd.h"

typedef struct PROCESOS {
    vdprocesoss proc;
    void (*fnproceso)(struct PROCESOS *);
    v10horas ultejecucion;
    long ejecuciones;
    int locksemaforo;
} procesos;


/* Funciones definidas en VDGESLIB.C */
VDEXPORT int damelogdiferido(void);
VDEXPORT char *dameusuariofijo(void);
VDEXPORT procesos *dameprocesoi(int i);
VDEXPORT int damenumprocesos(void);
VDEXPORT int cargaproceso(char *nomproceso);
VDEXPORT int cargaparamproceso(char *cadena);
VDEXPORT procesos *buscaproceso(char *nomproceso);

/* Funciones definidas en VDEJECUTAALGORITMOS.C */
VDEXPORT int VDEXECejecuta(procesos *proceso,void *ptrparam,char *sep,char *format,...);
VDEXPORT void VDEXECejecutaproceso(char *proceso);
VDEXPORT void dameparamproc(procesos *proceso, char *donde, int numparam);
VDEXPORT long dameparamproclong(procesos *proceso, int numparam);
VDEXPORT double dameparamprocdouble(procesos *proceso, int numparam);


/* Funciones definidas en VDINFOORA.C */
VDEXPORT int VDEXECsetusuario(char *usuario);

// Funciones definidas en VDDEMANDAS.C
// establece el estado al que pasa una cabecera de demanda en funci�n de su backorder
// y el estado de las l�neas de la misma.
int analizabackorderdemanda(vddemandacabs *demc);
// analiza el backorder de una l�nea, para determinar si se ha reservado correctamente 
// si es as� se pone a estado EJECUTADO (sustituir por RESERVADA)
int analizabackorderlineademanda(vddemandalins *deml);
// ALGORITMO. Finaliza una l�nea de demanda, con movtos finalizados,o anulada
VDEXPORT int vdfinalizademl(void *ptr,char *param);
// ejecuci�n de algoritmos (por discriminnate) de un proceso dado para una l�nea de demanda, desde un trigger s�ncrono
VDEXPORT int triggerdemlsync(char *nomproceso,vddemandalins *deml);
// PROCESO. busca una cabecera de demanda pasada y la procesa
VDEXPORT void vdbuscademc(procesos *proceso);
// PROCESO. busca las cabeceras de demandas en un estado dado, de diversos tipos
VDEXPORT void vdbuscademctipost(procesos *proceso);
// PROCESO. busca las l�neas de demanda en un estado dado
VDEXPORT void vdbuscademlst(procesos *proceso);

// Funciones en vdreservademandas.c
// ALGORITMO. Realiza la reserva de una l�nea de demanda de traslado por un flujo.
VDEXPORT int vdresdemlstd(void *ptr,char *param);
// ALGORITMO. Realiza la reserva de una l�nea de demanda de traslado por un flujo.
VDEXPORT int vdresdemlpedstd(void *ptr,char *param);

// funciones en vdlotes.c
VDEXPORT void vdprocesaloteshistst(procesos *proceso);

// funciones en vdcorreos.c
VDEXPORT void vdprocesacorreosst(procesos *proceso);
// Proceso que busca correos pdtes para enviarlos

#endif
