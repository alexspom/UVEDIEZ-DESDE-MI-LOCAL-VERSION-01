/*******************************************************************************
* Módulo : VDCORREOS.C                                                         *
* Función: Procesos y algoritmos para el envío de correos                      *
*                                                                              *
* Autor	 : Paco Guerrero                                                       *
* Revisado por:                                                                *
* Fecha  : 10-07-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "execproc/vdexec.h"


// ALGORITMO: Envío un correo del spool smtp
// PARAM1: (ptr) puntero al movto
// PARAM2: (param) parámetros del algoritmo
VDEXPORT int vdenviacorreo(void *ptr,char *param) {
    vdcorrsmtps *smtp=ptr;
    vdcorreoss corr;    

    memset(&corr,0,sizeof(corr));

    if (CORREOSprocenviacorreo(smtp->idmsg,"",0,&corr)) {
        v10log(LOGERROR,"%s","vdenviacorreo: Error al ejecutar PLSQL VDCORREOS.ENVIACORREO\n");
        return(-1);
    }
    if (corr.comentario) strcpy(smtp->comen,corr.comentario);
    return(corr.ret);
}  


// Proceso que busca correos pdtes para enviarlos
// Param 1. Estado en el que busca los correos
// Param 2. Estado en el que finaliza los correos enviados
VDEXPORT void vdprocesacorreosst(procesos *proceso)
{  
    int ret;  
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss stai,staf;
    vdcorrsmtps smtp;
    
    if ((ret=damestabreviada("vdbuscacorreosst",proceso->proc.param, 1, "#", NULL, "CSP", &stai, 0))) return;
    if ((ret=damestabreviada("vdbuscacorreosst",proceso->proc.param, 2, "#", NULL, "CSP", &staf, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",3);
    
    if (SMTPbuscastatus(stai.status,&smtp)) return;
    
    do {
        *smtp.comen=0;
        v10log(LOGNORMAL,"vdbuscacorreosst: Tratando mensaje con IDMSG=%ld de tipo %s\n",smtp.idmsg,smtp.tipocorreo);
        
        ret=VDEXECejecuta(proceso,&smtp,"#","%s#%s#%s#%s#%s#%s",
            smtp.fichero,
            smtp.directorio,
            smtp.adjunto,
            smtp.para,
            smtp.cuenta,
            smtp.tipocorreo);

        if (ret)  {
            v10log(LOGERROR,"vdbuscacorreosst: ERROR Enviado mensaje con IDMSG=%ld\n",smtp.idmsg);
            rollback();
            smtp.status = - smtp.status;
        } else {    
            smtp.status  = staf.status;
            cent2a(gettime(),0,':',smtp.horaenvio);
            smtp.fecenvio=damedate();         
            v10log(LOGNORMAL,"vdbuscacorreosst: Enviado mensaje con IDMSG=%ld\n",smtp.idmsg);
        }
        
        ret=SMTPactualizaenviado(&smtp,0);
        if (ret) {
            v10log(LOGERROR,"vdbuscacorreosst: ERROR Actualizando correo a estado %d\n",smtp.status);
            rollback();            
        }
        
        if (*smtp.comen) {
            if (*tipocomen==0) v10log(LOGERROR,"vdbuscacorreosst: NO SE PUEDEN TRATAR COMENTARIOS del Correo. %s\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",SMTPlog(&smtp));            
            else {
                if (smtp.codcomen==0) v10log(LOGERROR,"vdbuscacorreosst: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del mensaje. %s\n\tCODCOMEN del movto es 0\n",tipocomen,SMTPlog(&smtp));            
                else v10comen("VDCORRSMTP",smtp.codcomen,tipocomen,0,smtp.comen,NULL); 
            }
        }
        
        commit();
    } while (!SMTPnextstatus(&smtp));
}
