#include "vdpedidos.h"
// graba el comentario en un pedido, de un tipo concreto
static void PECgrabacomentario(procesos *proceso, char *comen,char *tipocomen,vdpedidocabs *pec) {
    
    vdcomens com;
    char msjerror[MAXCADENA]="";
    memset(&com,0,sizeof(com));
    if (*comen) {
        if (*tipocomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de la Cabecera de Pedido. %s\n\tNO SE HA INDICADO TIPO\n",proceso->proc.proceso,PEClog(pec));            
        else {
            if (pec->codcomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s de la cabecera de Pedido. %s\n\tCODCOMEN del pedido es 0\n",proceso->proc.proceso,tipocomen,PEClog(pec));            
            else {
                strcopia(com.comentario,comen,strlen(comen));
                v10comenrelogin("VDPEDIDOCAB",pec->codcomen,tipocomen,0,com.comentario,msjerror);                 
          }
        }
    }    
}

static int ejecutaalgoritmos(procesos *proceso,vdpedidocabs *pec) 
{
    int ret;
    vdseriepreps spr;
	vdagencias ag;
	memset(&ag,0,sizeof(ag));
	memset(&spr,0,sizeof(spr));
	AGselcodage(pec->codage,&ag);
    SPRselvdserieprep(pec->codserieprep,&spr);
	ret=VDEXECejecuta(proceso,pec,"#","%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s",pec->tipopedido,pec->coddiv,pec->codage,ag.grupoage,pec->codareaexped,spr.swtpickinginv,pec->backorder,spr.swtpickingagr,pec->swtmiscelaneo,pec->swtanular,pec->sufijodoc);  
    return(ret);   
}


// PROCESO. Busca pedidos en un estado ordenados por prioridad, para ejecutar un algoritmo
// 1:   estado de los pedidos
// 2:   tipo de comentario del pedido
// 3:   resetear los comentarios del tipo para este pedido
VDEXPORT void vdbuscapedstprio(procesos *proceso) 
{
    int ret;
    char borracomentarios[2]="";    
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss sta;
    vdpedidocabs pec; 
    vdpedidos ped;
    if ((ret=damestabreviada("vdbuscapedstprio",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0))) return;
    if (PEDIDObuscastatusprio(sta.status,&ped)) return;
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';
    do { 
        PECselvdpedidocab(ped.coddiv,ped.anoped,ped.codped,ped.seqped,&pec);
        savepoint("vdbuscapedstprio");
        if ((ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL))){
            v10log(LOGERROR,"vdbuscapedstprio: Error bloqueando cabecera de pedidos. %s\n\t%s\n",PEClog(&pec),
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdbuscapedstprio");        
            continue;
        }      
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdbuscapedstprio: Procesando cabecera de pedido. %s\n",PEClog(&pec));
        ret=ejecutaalgoritmos(proceso,&pec);        
        if (ret) {
            rollbacksavepoint("vdbuscapedstprio");
            pec.status=-pec.status;
            ret=PECactualizastatus(&pec,0);
            if (ret) {
                 rollback();
                 v10log(LOGERROR,"vdbuscapedstprio: error %ld actualizado a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));               
             }  
            v10log(LOGERROR,"vdbuscapedstprio: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                             
        }
        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);       
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }
        commit();
    } while (PEDIDOnextstatusprio(&ped)==0);
}

// Proceso que busca pedidos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los pedidos
// PARAM2: tipo de comentario
// PARAM3: resetear los comentarios del tipo para este pedido
VDEXPORT void vdbuscapedst(procesos *proceso) 
{
    int ret;
    char borracomentarios[LSWITCH]="";    
    vdpedidocabs pec;
    char tipocomen[LTIPOCOMEN]=""; 
    vdstatuss sta;
    if ((ret=damestabreviada("vdbuscapedst",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0))) return;
    if (PECbuscastatus(sta.status,&pec)) return;
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';
    do { 
        savepoint("vdbuscapedst");
        if ((ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL))){
            v10log(LOGERROR,"vdbuscapedst: Error bloqueando cabecera de pedidos. %s\n\t%s\n",PEClog(&pec),
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdbuscapedst");        
            continue;
        }      
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdbuscapedst: Procesando cabecera de pedido. %s\n",PEClog(&pec));
        ret=ejecutaalgoritmos(proceso,&pec);        
        if (ret) {
            rollbacksavepoint("vdbuscapedst");
            pec.status=-pec.status;
            ret=PECactualizastatus(&pec,0);
            if (ret) {
                 rollback();
                 v10log(LOGERROR,"vdbuscapedst: error %ld actualizado a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));               
            }  
            v10log(LOGERROR,"vdbuscapedst: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                             
        }
        // siempre guarda el comentario
        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);       
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }
        commit();
    } while (PECnextstatus(&pec)==SUCCESS);
}


// Proceso que procesa pedidos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los pedidos
// PARAM2: tipo de comentario
// PARAM3: resetear los comentarios del tipo para este pedido
// PARAM4: semáforo, se comprueba en el vdexec
VDEXPORT void vdprocesapedst(procesos *proceso) 
{
    int ret;
    char borracomentarios[LSWITCH]="";    
    vdpedidocabs pec;
    char tipocomen[LTIPOCOMEN]=""; 
    vdstatuss sta;
    if (ret=damestabreviada("vdprocesapedst",proceso->proc.param, 1, "#", NULL, "PEC", &sta, 0)) return;
    if (PECbuscastatus(sta.status,&pec)) return;
    ret=numpieces(proceso->proc.param,"#");
    piece(proceso->proc.param,tipocomen,"#",2);   
    if ((ret=piece(proceso->proc.param,borracomentarios,"#",3)) < 0) *borracomentarios='N';
    do { 
        savepoint("vdprocesapedst");
        if ((ret=PEClock(&pec,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"vdprocesapedst:Error bloqueando cabecera de pedido. %s\n\t%s\n",PEClog(&pec),
                   ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdprocesapedst");        
            continue;
        }      
        *pec.comenpec=0;
        v10log(LOGNORMAL,"vdprocesapedst: Procesando cabecera de pedido. %s\n",PEClog(&pec));
        ret=ejecutaalgoritmos(proceso,&pec);
        if (ret) {
            rollbacksavepoint("vdprocesapedst");
            pec.status=-pec.status;
            v10log(LOGERROR,"vdprocesapedst: ERROR %ld procesando pedido. %s \n",ret,PEClog(&pec));                    
        }
        ret=PECactualizastatus(&pec,0);
        if (ret) {
            rollback();
            v10log(LOGERROR,"vdprocesapedst: ERROR %ld actualizando a estado %ld pedido. %s \n",ret,pec.status,PEClog(&pec));
        }               
        if (*pec.comenpec) {
            if (*borracomentarios=='S') v10deletecomenportipo(pec.codcomen, tipocomen, NULL);
            PECgrabacomentario(proceso, pec.comenpec,tipocomen,&pec);
        }
        commit();
    } while (PECnextstatus(&pec)==SUCCESS);
}
