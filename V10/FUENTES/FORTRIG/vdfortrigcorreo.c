#include "vd.h"

// envía un correo de un tipo
int vdcorreo(char *tipocorreo,
             char *asunto,
             char *cuerpo,
             char *mime,
             char *dir,
             char *fichero,
             int prioridad,
             long fecplanif,
             char *horaplanif,
             char *mensaje) {
    int ret;
    vdcorreoss corr;

    ret=CORREOSproccorreo(tipocorreo,damehostname(),asunto,cuerpo,dir,fichero,prioridad,mime,fecplanif,horaplanif,"",0,&corr);
    if (ret) {
        sprintf( mensaje,"%s"," vdcorreo: Error ejecutando PLSQL VDCORREOS.CORREO");
        v10log(LOGERROR,"%s",mensaje);
        return(-1);
    }
    
    if (corr.ret) strcpy(mensaje,corr.comentario);
    return(corr.ret);

}

// envía un correo sin tipo, pasándole cuenta y destinatarios
int vdcorreodet(char *cuenta,
                char *para,
                char *cc,
                char *cco,
                char *asunto,
                char *cuerpo,
                char *mime,
                char *dir,
                char *fichero,
                int prioridad,
                long fecplanif,
                char *horaplanif,
                char *mensaje) {
    int ret;
    vdcorreoss corr;

    ret=CORREOSproccorreodet(damehostname(),cuenta,para,cc,cco,asunto,cuerpo,dir,fichero,prioridad,mime,fecplanif,horaplanif,"",0,&corr);
    if (ret) {
        sprintf( mensaje," vdcorreo: Error ejecutando PLSQL VDCORREOS.CORREODET");
        v10log(LOGERROR,"%s",mensaje);
        return(-1);
    }
    
    if (corr.ret) strcpy(mensaje,corr.comentario);
    return(corr.ret);
}

// envía un correo de un tipo
int fcorreo(bloques *b,ftrigers *ft) {
    
    int ret;
    char msjerror[MAXCADENA];
    vdcorrsmtps smtp;

    if (ft->nparam<3) {                
        sprintf(msjerror,"%s: son obligatorios TIPOCORREO,ASUNTO Y CUERPO",ft->nombre);
        ponerrorbloque(b,msjerror); 
        return(-1);
    }     

    memset(&smtp,0,sizeof(smtp));
    
    dameparametro(b,ft,0, V10CADENA, smtp.tipocorreo);
    dameparametro(b,ft,1, V10CADENA, smtp.asunto);
    dameparametro(b,ft,2, V10CADENA, smtp.cuerpo);
    if (ft->nparam>3) {
        dameparametro(b,ft,3, V10CADENA, smtp.directorio);
        if (strlen(smtp.directorio)>0)
            if (smtp.directorio[strlen(smtp.directorio)-1]!='\\') strcat(smtp.directorio,"\\");
    }
    if (ft->nparam>4) dameparametro(b,ft,4, V10CADENA, smtp.fichero);
    if (ft->nparam>5) dameparametro(b,ft,5, V10LONG, &smtp.prioridad);
    if (ft->nparam>6) dameparametro(b,ft,6, V10LONG,   &smtp.fecplanif);
    if (ft->nparam>7) dameparametro(b,ft,7, V10CADENA, smtp.horaplanif);    

    ret=vdcorreo(smtp.tipocorreo,smtp.asunto,smtp.cuerpo,"",smtp.directorio,smtp.fichero,smtp.prioridad,smtp.fecplanif,smtp.horaplanif,msjerror);
    if (ret) ponerrorbloque(b,msjerror); 
    return(ret);
}


// envía un correo sin tipo, pasándole cuenta y destinatarios
int fcorreodet(bloques *b,ftrigers *ft) {
    
    int ret;
    char msjerror[MAXCADENA];
    vdcorrsmtps smtp;

    if (ft->nparam<6) {                
        sprintf(msjerror,"%s: son obligatorios CUENTA, PARA, CC, CCO, ASUNTO Y CUERPO",ft->nombre);
        ponerrorbloque(b,msjerror); 
        return(-1);
    }     

    memset(&smtp,0,sizeof(smtp));
    
    dameparametro(b,ft,0, V10CADENA, smtp.cuenta);
    dameparametro(b,ft,1, V10CADENA, smtp.para);
    dameparametro(b,ft,2, V10CADENA, smtp.cc);
    dameparametro(b,ft,3, V10CADENA, smtp.cco);
    dameparametro(b,ft,4, V10CADENA, smtp.asunto);
    dameparametro(b,ft,5, V10CADENA, smtp.cuerpo);
    if (ft->nparam>6) {
        dameparametro(b,ft,6, V10CADENA, smtp.directorio);
        if (strlen(smtp.directorio)>0)
            if (smtp.directorio[strlen(smtp.directorio)-1]!='\\') strcat(smtp.directorio,"\\");
    }
    if (ft->nparam>7) dameparametro(b,ft,7, V10CADENA, smtp.fichero);
    if (ft->nparam>8) dameparametro(b,ft,8, V10LONG, &smtp.prioridad);
    if (ft->nparam>9) dameparametro(b,ft,9, V10LONG,   &smtp.fecplanif);
    if (ft->nparam>10) dameparametro(b,ft,10, V10CADENA, smtp.horaplanif);    
    if (ft->nparam>11) dameparametro(b,ft,11, V10CADENA, smtp.mime);
    ret=vdcorreodet(smtp.cuenta,smtp.para,smtp.cc,smtp.cco,smtp.asunto,smtp.cuerpo,smtp.mime,smtp.directorio,smtp.fichero,smtp.prioridad,smtp.fecplanif,smtp.horaplanif,msjerror);
    if (ret) ponerrorbloque(b,msjerror); 
    return(ret);
}