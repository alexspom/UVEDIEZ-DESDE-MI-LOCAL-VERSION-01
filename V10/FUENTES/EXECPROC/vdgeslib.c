/*******************************************************************************
* Función  Gestión de la carga dinámica de procesos                            *
* Módulo  vdgeslib.c                                                     *
*                                                                              *
* Autoru555+uk  JCSR	                                                               *
* Revisado por:                                                                *
* Fecha 01-11-2007                                                             *
********************************************************************************

*******************************************************************************/

#include "vdexec.h"
#define MAXPROCESOS 20


static procesos sprocesos[MAXPROCESOS];
static int numprocesos=0;
static char usuariofijo[LCODOPE];
static int logdiferido=0;

int damelogdiferido(void)
{
    return(logdiferido);
}

char *dameusuariofijo(void)
{
    return(usuariofijo);
}


VDEXPORT procesos *dameprocesoi(int i) {
    if (i<numprocesos) return(sprocesos+i);
    return(NULL);
}

VDEXPORT int damenumprocesos(void) {
    return(numprocesos);
}


VDEXPORT int cargaproceso(char *nomproceso) 
{
    vdprocesoss vdproceso;
    procesos *ptrproceso=sprocesos+numprocesos;

    if (buscaproceso(nomproceso)!=NULL) return(0);

    if (0!=PROselvdprocesos (nomproceso,&vdproceso)) {
            v10log(LOGERROR,"Proceso %s no encontrado en tabla VDPROCESOS\n",nomproceso);
            return(-1);
    } else v10log(LOGNORMAL,"Proceso %s encontrado en tabla VDPROCESOS\n",nomproceso);
    
    ptrproceso->proc=vdproceso;        
    ptrproceso->fnproceso=damefundll(vdproceso.libproceso, vdproceso.funcionproc);
    v10log(LOGNORMAL,"Proceso %s cargado con función %s (Librería %s) direccion %p\n",
                            nomproceso,vdproceso.funcionproc,vdproceso.libproceso,ptrproceso->fnproceso);
	if (!ptrproceso->fnproceso) v10log(LOGERROR,"Función %s no encontrada en dll %s para proceso %s\n",
		                                     vdproceso.funcionproc, vdproceso.libproceso, vdproceso.proceso);
    numprocesos++;
    return(0);
}

VDEXPORT int cargaparamproceso(char *cadena) {
    
    if (*cadena=='T') return(cargaproceso(cadena+1));
    if (*cadena=='E') {
        switch (cadena[1]) {
           case 'U' :strcpy(usuariofijo,cadena+2);
                     break;
           case 'N' :quitalogoracle(atoi(cadena+2));
                     break;
           case 'D' :logdiferido=atoi(cadena+2);
                     break;
        }
    }
    return(0);
}



VDEXPORT procesos *buscaproceso(char *nomproceso)  
{
    int i;

    for(i=0;i<numprocesos;i++){
	    if (!strcmp(nomproceso,sprocesos[i].proc.proceso)) return(sprocesos+i);
    }
    return(NULL);
}

