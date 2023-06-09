/*******************************************************************************
* M�dulo : VDSTOCKS.C                                                           *
* Funci�n: Funciones, Procesos y Algoritmos del API de FUENTE y CONSUMO stock  *
*                                                                              *
* Autor	 : FGS                                                                 *
* Revisado por:                                                                *
* Fecha  : 16-07-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "execproc/vdexec.h"


// inserta un registro en la tabla vdstockfuente, para la creaci�n de stock
VDEXPORT int vdfuentestk(char *tipofuente,char *codubi,char *codmat,char *tipoconte,
                char *codart,char *codlot,double canthost,char *unidadeshost,
                double uniembhost,long embcont,char *tipoemba,double preciouni,
                char *bloqueos,char *bulto,char *marcastk,char *numeroserie,
                char *codrecep,double pesouni,char *codlotprov,char *caduci,
                char *retest,char *bloqlote,double potencia,char *swtprecio, char *muestreado, char *observ,char *msjerror,
                long *codmovout) {
    
    vdstkfteauxs stkfteaux;
    if (STKFTEAUXprocfuentestk(tipofuente,codubi,codmat,tipoconte,
                               codart,codlot,canthost,unidadeshost,uniembhost,embcont,tipoemba,preciouni,
                               bloqueos,bulto,marcastk,numeroserie,codrecep,
                               pesouni,codlotprov,caduci,retest,bloqlote,potencia,swtprecio,muestreado,
                               observ,"",0,&stkfteaux)) {
        v10log(LOGERROR,"%s\n","ERROR al ejecutar PLSQL VDSTK.FUENTESTK");
    }

    strcpy(msjerror,stkfteaux.comentario);
    return(stkfteaux.ret);
}

// ALGORITMO. Genera el stock para un registro de vdstockfuente
// PARAM 1: Concepto del movto de creaci�n de stock
// PARAM 2: Ubicaci�n fuente del movto de creaci�n de stock
// PARAM 3: si puede crear la matr�cula del stock (si no existe)
// PARAM 4: si puede crear el lote del stock (si no existe)
VDEXPORT int vdalgstockfuente(void *ptr,char *param) {
    vdstockfuentes *stkfte=ptr;
    vdstkfteauxs stkfteaux;
    char codconce[LCODCONCE]="",ubicodconce[LCODUBI]="",crearconte[2]="",crearlote[2]="",observ[LVDEXTRA]="";

    piece(param,codconce,"#",1);    // obligatorio
    piece(param,ubicodconce,"#",2); // obligatorio     
    piece(param,crearconte,"#",3);  // obligatorio
    piece(param,crearlote,"#",4);   // obligatorio
    piece(param,observ,"#",5);   
  
    if (STKFTEAUXproccreastk(stkfte->seqfuente,codconce,ubicodconce,crearconte,crearlote,observ,"",0,0,&stkfteaux)) {
        v10log(LOGERROR,"%s\n","ERROR al ejecutar PLSQL VDSTK.CREASTK");
    }
   
    strcpy(stkfte->comen,stkfteaux.comentario);
    if (stkfteaux.ret==0) {
        v10log(LOGNORMAL,"vdalgstockfuente: creado movto %ld para creaci�n de stock de secuencia de vdfuentestock %ld\n",stkfteaux.codmov,stkfte->seqfuente);
    }
    return(stkfteaux.ret);
}


static int ejecutaalgoritmos(procesos *proceso,vdstockfuentes *stkfte,vdclaseartics *cla) {
    
    int ret;
    vdubicas ubi;

    memset(&ubi,0,sizeof(ubi));
    UBIselvdubica(stkfte->codubi,&ubi);

    *cla->codclase=0;

    if (*cla->codclasif && CLAselcodartclasif(stkfte->codart,cla->codclasif,cla)) {
        v10log(LOGERROR,"ejecutaalgoritmos: Articulo %s no clasificado en Clasificaci�n %s\n",
            stkfte->codart,cla->codclasif);         
    }    
    
    ret=VDEXECejecuta(proceso,stkfte,"#","%s#%s#%s#%s#%s",
                      stkfte->codart,
                      cla->codclase,
                      stkfte->codubi,
                      ubi.codarea,
                      stkfte->tipofuente);
    
    return(ret);
}

// Proceso que busca registros en vdstockfuente pendientes de procesar, y los procesa
// par�metros:
// 1 Estado de los registros a tratar
// 2 Estado final de los registros tratados
// 3 Tipo de Comentario
// 4 Clasificaci�n para montar el discriminante
VDEXPORT void vdprocesastockfuente(procesos *proceso) {
    
    int ret;
    char tipocomen[LTIPOCOMEN]="";
    vdclaseartics cla;
    vdstatuss stai,staf;
    vdstockfuentes stkfte;
    
    memset(&cla,0,sizeof(cla));
    
    if ((ret=damestabreviada("vdprocesastockfuente",proceso->proc.param, 1, "#", NULL, "FTE", &stai, 0))) return;
    if ((ret=damestabreviada("vdprocesastockfuente",proceso->proc.param, 2, "#", NULL, "FTE", &staf, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",3);
    piece(proceso->proc.param,cla.codclasif,"#",4);
    
    if (FTEbuscastatus(stai.status,&stkfte)) return;
    
    do {        
        savepoint("vdprocesastockfuente");        

        v10log(LOGNORMAL,"vdprocesastockfuente: Tratando registro con secuencia %ld\n  "\
                         " para creaci�n de %s %s de Art�culo \'%s\' Lote \'%s\' en Matr�cula \'%s\' de Ubicaci�n \'%s\'\n",
                            stkfte.seqfuente,stkfte.cantidadhost,stkfte.unidadeshost,stkfte.codart,stkfte.codlot,
                            stkfte.codmat,stkfte.codubi);

        if ((ret=FTElock(&stkfte,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"Error bloqueando registro en vdstockfuente %ld\n\t%s\n",stkfte.seqfuente,
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            continue;
        }
        
        *stkfte.comen=0;
        v10log(LOGNORMAL,"vdprocesastockfuente: Procesando registro en vdstockfuente %ld \n",stkfte.seqfuente);
        ret=ejecutaalgoritmos(proceso,&stkfte,&cla);
        if (ret) {
            rollbacksavepoint("vdprocesastockfuente");
            stkfte.status=-stkfte.status;            
            v10log(LOGERROR,"vdprocesastockfuente: ERROR %ld procesando registro en vdstockfuente %ld \n",ret,stkfte.seqfuente);            
        } else stkfte.status=staf.status;
        
        ret=FTEactualizastatus(&stkfte,0);
        if (ret) {
            rollback();
            v10log(LOGERROR,"vdprocesastockfuente: registro en vdstockfuente %ld actualizado a estado %ld\n",stkfte.seqfuente,stkfte.status);
        }
        
        commit();
        
        // siempre guarda el comentario
        if (*stkfte.comen) {
            if (*tipocomen==0) v10log(LOGERROR,"vdprocesastockfuente: NO SE PUEDEN TRATAR COMENTARIOS del registro en vdstockfuente. %s\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",FTElog(&stkfte));            
            else {
                if (stkfte.codcomen==0) v10log(LOGERROR,"vdprocesastockfuente: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del registro en vdstockfuente. %s\n\tCODCOMEN del registro en vdstockfuente es 0\n",tipocomen,FTElog(&stkfte));            
                else v10comen("VDSTOCKFUENTE",stkfte.codcomen,tipocomen,0,stkfte.comen,NULL); 
            }
        }    
        
        commit();
        v10log(LOGNORMAL,"vdprocesastockfuente: Finalizado tratamiento de registro con secuencia %ld\n",stkfte.seqfuente);

    } while (0==FTEnextstatus(&stkfte));
    
}