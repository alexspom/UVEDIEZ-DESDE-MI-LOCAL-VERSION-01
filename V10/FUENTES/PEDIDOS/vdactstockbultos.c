/****
* VDACTSTOCKBULTOS.C
*                                                    
* Propósito: Proceso en C para la actualización de los bultos, al ejecutar los movimientos 
*                                            
* Autor  : RFD
* Fecha  : 30-4-2008                                                        
******
*  Modificaciones:
****/


#include "vdpedidos.h"


// Algoritmo que ejecuta el actualizador de stock destino y actualiza bultos
// parámetros
// PARAM1: (ptr) puntero al movimiento
// PARAM2: (param) parámetros del algoritmo, estado en el que dejar el bulto, en caso de que trate bultos
VDEXPORT int actstockbultos(void *ptr,char *param) {

	vdmovims *mov=ptr;  
    vdstatuss stabul,stamov;
	long statusmov;
	vdstkbuls stkbul;
    int ret;
    
	ret=numpieces(param,"#");
    if (ret < 2) {
        v10log(LOGERROR,"vdcreabultos: Número de parámetros incorrecto, recibe %d necesita 2\n", ret);
		return(-1);
	}
	statusmov=mov->status;
	if ((ret=damestabreviada("vdstockdest",param, 1, "#", "VDMOVIM", "MOV", &stamov, 0))) return(ret);
	savepoint("actstockbultos");
    ret=STKAUXactstockdest(mov,stamov.status);
	if (ret) {
		v10log(LOGERROR,"actstockbultos: Error actualizando stock destino en movimiento %ld",mov->codmov);
		return(ret);
	}
    if ((ret=damestabreviada("actstockbultos",param, 2, "#", NULL, "BUC", &stabul, 0))) return ret;

	ret=STKBULprocactstkbul(mov->codmov,stabul.status,0,&stkbul);
	if (stkbul.ret) {
		rollbacksavepoint("actstockbultos");
		v10log(LOGERROR,"actstockbultos: Error actualizando stock destino en movimiento %ld para bulto",mov->codmov);
	    mov->status=-statusmov;
		MOVactualizastatus(mov,NOVERIFICA);
    }
    return(ret);
}

