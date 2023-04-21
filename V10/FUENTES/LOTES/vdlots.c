/*******************************************************************************
* Módulo : VDLOTES.C                                                           *
* Función: Procesos y algoritmos para el cambio de calif. de lotes             *
*                                                                              *
* Autor	 : Paco Guerrero                                                       *
* Revisado por:                                                                *
* Fecha  : 22-07-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "execproc/vdexec.h"


VDEXPORT int algtrataloteshistst(void *ptr,char *param) {
    char comenmov[2]="N";
    vdloteshists *loh=ptr;
    vdarticulos art;

    piece(param,comenmov,"#",1);
    if (!strcmp(loh->bloqlotenuevo,loh->bloqloteactual)) {
        v10log(LOGNORMAL,"algtrataloteshistst: Secuencia %ld de registro de VDLOTESHIST no realiza cambios de calificaciones del stock\n",loh->seq);
        return(0);
    }

    if (ARTICULOproctrataloteshist(loh->seq,comenmov, &art)) {
        v10log(LOGERROR,"%s","Error ejecutando PLSQL VDART.TARTALOTEHIST");
        return(-1);
    }

    return(0);
}
  
static int ejecutaalgoritmos(procesos *proceso,vdloteshists *loh) {    
    int ret;
    ret=VDEXECejecuta(proceso,loh,"#","%s#%s",loh->codart,loh->codlot);    
    return(ret);
}


// Busca los cambios de propiedades de lotes en estado sin tratar
VDEXPORT void vdprocesaloteshistst(procesos *proceso)
{  
    int ret;  
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss staini,stafin;
    vdloteshists loh;
    
    if ((ret=damestabreviada("vdbuscaloteshistst",proceso->proc.param, 1, "#", NULL, "LOH", &staini, 0))) return;
    if ((ret=damestabreviada("vdbuscaloteshistst",proceso->proc.param, 2, "#", NULL, "LOH", &stafin, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",3);
    
    if (LOHbuscastatus(staini.status, &loh)) return;
    
    do {
        savepoint("vdbuscaloteshistst");
        
        if ((ret=LOHlock(&loh,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"Error bloqueando registro VDLOTESHIST  %ld\n\t%s\n",loh.seq,
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            continue;
        }
        
        *loh.comenloh=0;
        v10log(LOGNORMAL,"vdbuscamovst: Procesando registro de VDLOTESHIST con secuencia %ld \n",loh.seq);
        ret=ejecutaalgoritmos(proceso,&loh);
        if (ret) {
            rollbacksavepoint("vdbuscaloteshistst");
            loh.status=-loh.status;
            v10log(LOGERROR,"vdbuscaloteshistst: ERROR %ld procesando registro de VDLOTESHIST con secuencia %ld \n",ret,loh.seq);                        
        } else {
            loh.status=stafin.status;
            cent2a(gettime(),0,':',loh.horafin);
            loh.fecfin=damedate();
            strcpy(loh.modulofin,"vdbuscaloteshistst");
            strcpy(loh.accionfin,"proceso");
        }

        ret=LOHactualizatratado(&loh,0);
        if (ret) {
            rollback();
        }
        v10log(LOGERROR,"vdbuscaloteshistst: registro de VDLOTESHIST con secuencia %ld actualizado a estado %ld\n\n\n",loh.seq,loh.status);
        
        // siempre guarda el comentario
        if (*loh.comenloh) {
            if (*tipocomen==0) v10log(LOGERROR,"vdbuscaloteshistst: NO SE PUEDEN TRATAR COMENTARIOS del registro de VDLOTESHIST %ld\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",loh.seq);            
            else {
                if (loh.codcomen==0) v10log(LOGERROR,"vdbuscaloteshistst: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del registro de VDLOTESHIST %ld\n\tCODCOMEN del movto es 0\n",tipocomen,loh.seq);            
                else v10comen("VDLOTESHIST",loh.codcomen,tipocomen,0,loh.comenloh,NULL); 
            }
        }    
        
        commit();
    } while (0==LOHnextstatus(&loh));
}
