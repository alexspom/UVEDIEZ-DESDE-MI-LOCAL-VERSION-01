/****
* VDSERIES.C
*                                                    
* Propósito: Procesos y algoritmos en C propios de series de preparación y expedición
*                                            
* Autor  : FGS
* Fecha  : 4-6-2008                                                        
******
*  Modificaciones:
****/
#include "vdpedidos.h"

static void SPRgrabacomentario(procesos *proceso, char *comen,char *tipocomen,vdseriepreps *spr) {
    
    vdcomens com;
    char msjerror[MAXCADENA]="";

    memset(&com,0,sizeof(com));

    if (*comen) {
        if (*tipocomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de la Serie de Preparación. %s\n\tNO SE HA INDICADO TIPO\n",proceso->proc.proceso,SPRlog(spr));            
        else {
            if (spr->codcomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s de la Serie de Preparación. %s\n\tCODCOMEN de la serie es 0\n",proceso->proc.proceso,tipocomen,SPRlog(spr));            
            else {
                strcopia(com.comentario,comen,strlen(comen));
                v10comenrelogin("VDSERIEPREP",spr->codcomen,tipocomen,0,com.comentario,msjerror);                 
          }
        }
    }    
}


static void SEXgrabacomentario(procesos *proceso, char *comen,char *tipocomen,vdserieexps *sex) {
    
    vdcomens com;
    char msjerror[MAXCADENA]="";

    memset(&com,0,sizeof(com));

    if (*comen) {
        if (*tipocomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de la Serie de Expedición. %s\n\tNO SE HA INDICADO TIPO\n",proceso->proc.proceso,SEXlog(sex));            
        else {
            if (sex->codcomen==0) v10log(LOGERROR,"%s: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s de la Serie de Expedición. %s\n\tCODCOMEN de la serie es 0\n",proceso->proc.proceso,tipocomen,SEXlog(sex));            
            else {
                strcopia(com.comentario,comen,strlen(comen));
                v10comenrelogin("VDSERIEEXP",sex->codcomen,tipocomen,0,com.comentario,msjerror);                 
          }
        }
    }    
}

static int SEXejecutaalgoritmos(procesos *proceso,vdserieexps *sex) {    
    int ret;    
    ret=VDEXECejecuta(proceso,sex,"#","%s",sex->codage);
    return(ret);
}


// algoritmo que se encarga de expedir toda la mercancia de los movtos de una serie de expedición
// si dá error, deja la serie en error (status=-status);
// PARAM1: estado al que pasa la serie cuando se expide con éxito
// PARAM2: concepto de los movtos de expedición de la serie
// PARAM3: ubicación sumidero donde se destruye la mercancia expedida


VDEXPORT int vdexpideserieexp(void *ptr,void *param) {
	int ret;
    vdstatuss stexpfinal,stpeclimite,stpecexpedido;
    char codconce[LCODCONCE]="",sumidero[LCODUBI]="";    
    vdserieexps *sex=ptr;
    vdseriess series;

    if (ret=damestabreviada("vdexpideserieexp",param, 1, "#", NULL, "SEX", &stexpfinal, 0)) return(ret);
    if (ret=damestabreviada("vdexpideserieexp",param, 2, "#", NULL, "PEC", &stpeclimite, 0)) return(ret);
    if (ret=damestabreviada("vdexpideserieexp",param, 3, "#", NULL, "PEC", &stpecexpedido, 0)) return(ret);  
    piece(param,codconce,"#",4);
    piece(param,sumidero,"#",5);

    if (SERIESprocexpideserie(sex->codserieexp,stexpfinal.status,stpeclimite.status, stpecexpedido.status, codconce,sumidero,"",0, &series)) {
        sprintf(sex->comensex,"%s","ERROR ejecutando PLSQL VDSERIES.EXPIDESERIE");
        v10log(LOGERROR,"%s",sex->comensex);
        return(-1);
    }
    
    strcpy(sex->comensex,series.comentario);
    return(series.ret);
}


// Proceso que procesa series de expedición en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de la serie
// PARAM2: tipo de comentario
VDEXPORT void vdprocesasexst(procesos *proceso) {
    int ret;
//   char msjerror[MAXCADENA]="",
	char tipocomen[LTIPOCOMEN]="";    
    vdserieexps sex;
    vdstatuss sta;
    
    if (ret=damestabreviada("vdprocesasexst",proceso->proc.param, 1, "#", NULL, "SEX", &sta, 0)) return;
    if (SEXbuscastatus(sta.status,&sex)) return;   
    piece(proceso->proc.param,tipocomen,"#",2);   

    do { 
        savepoint("vdprocesasexst");
        if (ret=SEXlock(&sex,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdprocesasexst:Error bloqueando serie de expedición. %s\n\t%s\n",SEXlog(&sex),
                   ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdprocesasexst");        
            continue;
        }      
        *sex.comensex=0;

        v10log(LOGNORMAL,"vdprocesasexst: Procesando Serie de Expedición. %s\n",SEXlog(&sex));

        ret=SEXejecutaalgoritmos(proceso,&sex);
        if (ret) {
            rollbacksavepoint("vdprocesasexst");
            sex.status=-sex.status;
            v10log(LOGERROR,"vdprocesasexst: ERROR %ld procesando serie de expedición. %s \n",ret,SEXlog(&sex));                                
            ret=SEXactualizastatus(&sex,0);
            if (ret) {
                rollbacksavepoint("vdprocesasexst");
                v10log(LOGERROR,"vdprocesasexst: ERROR %ld actualizando a estado %ld serie de expedición. %s \n",ret,sex.status,SEXlog(&sex));
            }
        }

        if (*sex.comensex)  SEXgrabacomentario(proceso, sex.comensex,tipocomen,&sex);
        commit();
    }while (SEXnextstatus(&sex)==SUCCESS);
}


static int SPRejecutaalgoritmos(procesos *proceso,vdseriepreps *spr) {    
    int ret;    
    ret=VDEXECejecuta(proceso,spr,"#","%s",spr->swtpickinginv);
    return(ret);
}

// Proceso que procesa series de preparación en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de la serie
// PARAM2: tipo de comentario
VDEXPORT void vdprocesasprst(procesos *proceso) {
    int ret;
    //char msjerror[MAXCADENA]="",
	char tipocomen[LTIPOCOMEN]="";    
    vdseriepreps spr;
    vdstatuss sta;
    
    if (ret=damestabreviada("vdprocesasprst",proceso->proc.param, 1, "#", NULL, "SPR", &sta, 0)) return;
    if (SPRbuscastatus(sta.status,&spr)) return;   
    piece(proceso->proc.param,tipocomen,"#",2);   

    do { 
        savepoint("vdprocesasprst");
        if (ret=SPRlock(&spr,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdprocesasprst:Error bloqueando serie de expedición. %s\n\t%s\n",SPRlog(&spr),
                   ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdprocesasprst");        
            continue;
        }      
        *spr.comenspr=0;

        v10log(LOGNORMAL,"vdprocesasprst: Procesando Serie de Preparación. %s\n",SPRlog(&spr));

        ret=SPRejecutaalgoritmos(proceso,&spr);
        if (ret) {
            rollbacksavepoint("vdprocesasprst");
            spr.status=-spr.status;
            v10log(LOGERROR,"vdprocesasprst: ERROR %ld procesando serie de preparación. %s \n",ret,SPRlog(&spr));                                
            ret=SPRactualizastatus(&spr,0);
            if (ret) {
                rollbacksavepoint("vdprocesasprst");
                v10log(LOGERROR,"vdprocesasprst: ERROR %ld actualizando a estado %ld serie de preparación. %s \n",ret,spr.status,SPRlog(&spr));
            }
        }

        if (*spr.comenspr)  SPRgrabacomentario(proceso, spr.comenspr,tipocomen,&spr);
        commit();
    }while (SPRnextstatus(&spr)==SUCCESS);
	
}