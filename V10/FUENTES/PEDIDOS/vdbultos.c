/****
* VDBULTOS.C
*                                                    
* Propósito: Procesos y algoritmos en C propios del tratamiento de bultos
*                                            
* Autor  : FPD
* Fecha  : 28-3-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"


// Finaliza un bulto de pedido
// PARAM1: (ptr) puntero al bulto
// PARAM2: (param) parámetros del algoritmo
VDEXPORT int vdfinbulto(void *ptr,char *param) {
	int ret;
	char actpelin[LSWITCH]="";
    vdstatuss stfinbulto,stpedido;
	vdbultos bulto;
    vdbultocabs *buc=ptr;

    if ((ret=damestabreviada("vdfinbulto",param, 1, "#", NULL, "BUC", &stfinbulto, STBUCFINALIZADO))) return(ret);
    if ((ret=damestabreviada("vdfinbulto",param, 2, "#", NULL, "PEC", &stpedido, STPECENEXPED))) return(ret);
    if ((ret=piece(param,actpelin,"#",3)) < 0) *actpelin='N';

    BULTOprocfinbulto(buc->codbulto,stfinbulto.status,stpedido.status,actpelin,0,&bulto);
    if (bulto.ret) {
		v10log(LOGERROR,"vdfinbulto: Error ejecutando VDBULTO.FINBULTO(%s,%ld)\n",buc->codbulto,stfinbulto.status);
		return(ret);
	}

	buc->status=stfinbulto.status;
	v10log(LOGNORMAL,"vdfinbulto: Bulto finalizado. %s \n",BUClog(buc));
	return 0;
}



static int ejecutaalgoritmos(procesos *proceso,vdbultocabs *buc) {
    
    int ret;
	vdpedidocabs pec;
    
	ret=PECselvdpedidocab(buc->coddiv,buc->anoped,buc->codped,buc->seqped,&pec);
    ret=VDEXECejecuta(proceso,buc,"#","%s#%s#%s#%s#%s#%s#%s#%s#%s",
		            pec.tipopedido,pec.coddiv,pec.codage,pec.codareaexped,pec.backorder,
					buc->tipobulto,buc->tipovol,buc->tipocaja,pec.swtmiscelaneo);
    return(ret);
}

// Proceso que procesa bultos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los bultos
// PARAM2: tipo de comentario
// PARAM3: semáforo, se comprueba en el vdexec
VDEXPORT void vdprocesabultost(procesos *proceso) {
    int ret;
    vdbultocabs buc;
    char tipocomen[LTIPOCOMEN]=""; 
    vdstatuss sta;
    
    if ((ret=damestabreviada("vdprocesabultost",proceso->proc.param, 1, "#", NULL, "BUC", &sta, 0))) return;
    if (BUCbuscastatus(sta.status,&buc)) return;
    
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   

    do { 
        savepoint("vdprocesabultost");
        if ((ret=BUClock(&buc,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"vdprocesabultost:Error bloqueando cabecera de bulto. %s\n\t%s\n",BUClog(&buc),
                   ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdprocesabultost");        
            continue;
        }      
        v10log(LOGNORMAL,"vdprocesabultost: Procesando cabecera de bulto. %s\n",BUClog(&buc));

        ret=ejecutaalgoritmos(proceso,&buc);
        if (ret) {
            rollbacksavepoint("vdprocesabultost");
            buc.status=-buc.status;
            v10log(LOGERROR,"vdprocesabultost: ERROR %ld procesando bulto. %s \n",ret,BUClog(&buc));                    
        }
        ret=BUCactualizastatus(&buc,0);
        if (ret) {
            rollback();
            v10log(LOGERROR,"vdprocesabultost: ERROR %ld actualizando a estado %ld bulto. %s \n",ret,buc.status,BUClog(&buc));
        }               

        commit();
    }while (BUCnextstatus(&buc)==0);
}
