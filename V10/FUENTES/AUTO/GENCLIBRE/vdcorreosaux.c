// Modulo generado automaticamente a partir de VDCORREOSAUX.DEF
//#***
//# VDCORREOS.DEF - Generación automática del código c SOLOQUERY sobre la tablas de correos
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 09-07-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=CORREOS;
//EXTRA=RET,V10LONG
//#EXTRA=CCO,V10CADENA,1000
//
//PROCEDURE=CORREODET,BEGIN 
//                       VDCORREOS.CORREODET(:VDCORRSMTP.ORDENADOR,
//                                           :VDCORRSMTP.CUENTA,
//                                           :VDCORRSMTP.PARA,
//                                           :VDCORRSMTP.CC,
//                                           :VDCORRSMTP.CCO,
//                                           :VDCORRSMTP.ASUNTO, 
//                    										   :VDCORRSMTP.CUERPO,                     										   
//                    										   :VDCORRSMTP.DIRECTORIO, 
//                    										   :VDCORRSMTP.FICHERO, 
//                    										   :VDCORRSMTP.PRIORIDAD, 
//                    										   :VDCORRSMTP.MIME,                     										                       										   
//                    										   :VDCORRSMTP.FECPLANIF, 
//                    										   :VDCORRSMTP.HORAPLANIF,
//                    										   :VDCOMEN.COMENTARIO,
//                                           :RET); 
//                   END;@    
//                   
//PROCEDURE=CORREO,BEGIN                       
//                       VDCORREOS.CORREO(:VDCORRSMTP.TIPOCORREO,
//                       									:VDCORRSMTP.ORDENADOR,
//                    										:VDCORRSMTP.ASUNTO, 
//                    										:VDCORRSMTP.CUERPO, 
//                    										:VDCORRSMTP.DIRECTORIO, 
//                    										:VDCORRSMTP.FICHERO, 
//                    										:VDCORRSMTP.PRIORIDAD, 
//                    										:VDCORRSMTP.MIME,                     										   
//                    										:VDCORRSMTP.FECPLANIF, 
//                    										:VDCORRSMTP.HORAPLANIF,
//                    										:VDCOMEN.COMENTARIO,
//                    										:RET); 
//                   END;@    
//                   
//PROCEDURE=ENVIACORREO,BEGIN                   
//															VDCORREOS.ENVIACORREO(:VDCORRSMTP.IDMSG,:VDCOMEN.COMENTARIO,:RET);
//											END;@                   
//                 
//                   

#include "vd.h"\

#define SELCORREODET "BEGIN  VDCORREOS.CORREODET(:ORDENADOR, :CUENTA, :PARA, :CC, :CCO, :ASUNTO,  :CUERPO,                     										    :DIRECTORIO,  :FICHERO,  :PRIORIDAD,  :MIME,                     										                       										    :FECPLANIF,  :HORAPLANIF, :COMENTARIO, :RET);  END;"
static v10cursors *vdselcorreodet;
#define SELCORREO "BEGIN                        VDCORREOS.CORREO(:TIPOCORREO, :ORDENADOR, :ASUNTO,  :CUERPO,  :DIRECTORIO,  :FICHERO,  :PRIORIDAD,  :MIME,                     										    :FECPLANIF,  :HORAPLANIF, :COMENTARIO, :RET);  END;"
static v10cursors *vdselcorreo;
#define SELENVIACORREO "BEGIN                    VDCORREOS.ENVIACORREO(:IDMSG,:COMENTARIO,:RET); END;"
static v10cursors *vdselenviacorreo;

static vdcorreoss svdcorreos;

static diccols colvdcorreos[]={ 
    {"RET",V10LONG,(int)&svdcorreos.ret,sizeof(svdcorreos.ret)},
    {"ORDENADOR",V10CADENA,(int)&svdcorreos.ordenador,sizeof(svdcorreos.ordenador)},
    {"CUENTA",V10CADENA,(int)&svdcorreos.cuenta,sizeof(svdcorreos.cuenta)},
    {"PARA",V10CADENA,(int)&svdcorreos.para,sizeof(svdcorreos.para)},
    {"CC",V10CADENA,(int)&svdcorreos.cc,sizeof(svdcorreos.cc)},
    {"CCO",V10CADENA,(int)&svdcorreos.cco,sizeof(svdcorreos.cco)},
    {"ASUNTO",V10CADENA,(int)&svdcorreos.asunto,sizeof(svdcorreos.asunto)},
    {"CUERPO",V10CADENA,(int)&svdcorreos.cuerpo,sizeof(svdcorreos.cuerpo)},
    {"DIRECTORIO",V10CADENA,(int)&svdcorreos.directorio,sizeof(svdcorreos.directorio)},
    {"FICHERO",V10CADENA,(int)&svdcorreos.fichero,sizeof(svdcorreos.fichero)},
    {"PRIORIDAD",V10LONG,(int)&svdcorreos.prioridad,sizeof(svdcorreos.prioridad)},
    {"MIME",V10CADENA,(int)&svdcorreos.mime,sizeof(svdcorreos.mime)},
    {"FECPLANIF",V10LONG,(int)&svdcorreos.fecplanif,sizeof(svdcorreos.fecplanif)},
    {"HORAPLANIF",V10CADENA,(int)&svdcorreos.horaplanif,sizeof(svdcorreos.horaplanif)},
    {"COMENTARIO",V10CADENA,(int)&svdcorreos.comentario,sizeof(svdcorreos.comentario)},
    {"TIPOCORREO",V10CADENA,(int)&svdcorreos.tipocorreo,sizeof(svdcorreos.tipocorreo)},
    {"IDMSG",V10LONG,(int)&svdcorreos.idmsg,sizeof(svdcorreos.idmsg)}
    };

static diccionarios dvdcorreos[]={
    {colvdcorreos,17}
    };

diccionario dcorreos={dvdcorreos,1};

static char msgdebugcorreos[LCADENABIG];

static int init=0;


static void fin_vd_CORREOS(void)
{
    if(vdselcorreodet){
        liberacursor(vdselcorreodet);
        vdselcorreodet=NULL;
    }
    if(vdselcorreo){
        liberacursor(vdselcorreo);
        vdselcorreo=NULL;
    }
    if(vdselenviacorreo){
        liberacursor(vdselenviacorreo);
        vdselenviacorreo=NULL;
    }
}


static void init_selcorreodet(void)
{
    int nc;

    for(nc=0;nc<dvdcorreos[0].numcol;nc++) dvdcorreos[0].c[nc].offset-=(int)&svdcorreos;

    vdselcorreodet=abrecursor(SELCORREODET);
    definetodo(vdselcorreodet,NULL);
    bindtodo(vdselcorreodet,"ORDENADOR",svdcorreos.ordenador,sizeof(svdcorreos.ordenador),V10CADENA,
             "CUENTA",svdcorreos.cuenta,sizeof(svdcorreos.cuenta),V10CADENA,
             "PARA",svdcorreos.para,sizeof(svdcorreos.para),V10CADENA,
             "CC",svdcorreos.cc,sizeof(svdcorreos.cc),V10CADENA,
             "CCO",svdcorreos.cco,sizeof(svdcorreos.cco),V10CADENA,
             "ASUNTO",svdcorreos.asunto,sizeof(svdcorreos.asunto),V10CADENA,
             "CUERPO",svdcorreos.cuerpo,sizeof(svdcorreos.cuerpo),V10CADENA,
             "DIRECTORIO",svdcorreos.directorio,sizeof(svdcorreos.directorio),V10CADENA,
             "FICHERO",svdcorreos.fichero,sizeof(svdcorreos.fichero),V10CADENA,
             "PRIORIDAD",&svdcorreos.prioridad,sizeof(svdcorreos.prioridad),V10LONG,
             "MIME",svdcorreos.mime,sizeof(svdcorreos.mime),V10CADENA,
             "FECPLANIF",&svdcorreos.fecplanif,sizeof(svdcorreos.fecplanif),V10LONG,
             "HORAPLANIF",svdcorreos.horaplanif,sizeof(svdcorreos.horaplanif),V10CADENA,
             "COMENTARIO",svdcorreos.comentario,sizeof(svdcorreos.comentario),V10CADENA,
             "RET",&svdcorreos.ret,sizeof(svdcorreos.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CORREOS);
        init = 1;
    }
}

static void init_selcorreo(void)
{
    int nc;

    for(nc=0;nc<dvdcorreos[0].numcol;nc++) dvdcorreos[0].c[nc].offset-=(int)&svdcorreos;

    vdselcorreo=abrecursor(SELCORREO);
    definetodo(vdselcorreo,NULL);
    bindtodo(vdselcorreo,"TIPOCORREO",svdcorreos.tipocorreo,sizeof(svdcorreos.tipocorreo),V10CADENA,
             "ORDENADOR",svdcorreos.ordenador,sizeof(svdcorreos.ordenador),V10CADENA,
             "ASUNTO",svdcorreos.asunto,sizeof(svdcorreos.asunto),V10CADENA,
             "CUERPO",svdcorreos.cuerpo,sizeof(svdcorreos.cuerpo),V10CADENA,
             "DIRECTORIO",svdcorreos.directorio,sizeof(svdcorreos.directorio),V10CADENA,
             "FICHERO",svdcorreos.fichero,sizeof(svdcorreos.fichero),V10CADENA,
             "PRIORIDAD",&svdcorreos.prioridad,sizeof(svdcorreos.prioridad),V10LONG,
             "MIME",svdcorreos.mime,sizeof(svdcorreos.mime),V10CADENA,
             "FECPLANIF",&svdcorreos.fecplanif,sizeof(svdcorreos.fecplanif),V10LONG,
             "HORAPLANIF",svdcorreos.horaplanif,sizeof(svdcorreos.horaplanif),V10CADENA,
             "COMENTARIO",svdcorreos.comentario,sizeof(svdcorreos.comentario),V10CADENA,
             "RET",&svdcorreos.ret,sizeof(svdcorreos.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CORREOS);
        init = 1;
    }
}

static void init_selenviacorreo(void)
{
    int nc;

    for(nc=0;nc<dvdcorreos[0].numcol;nc++) dvdcorreos[0].c[nc].offset-=(int)&svdcorreos;

    vdselenviacorreo=abrecursor(SELENVIACORREO);
    definetodo(vdselenviacorreo,NULL);
    bindtodo(vdselenviacorreo,"IDMSG",&svdcorreos.idmsg,sizeof(svdcorreos.idmsg),V10LONG,
             "COMENTARIO",svdcorreos.comentario,sizeof(svdcorreos.comentario),V10CADENA,
             "RET",&svdcorreos.ret,sizeof(svdcorreos.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CORREOS);
        init = 1;
    }
}

diccionario *CORREOSdamediccionario(void)
{
    return(&dcorreos);
}

int CORREOSproccorreodet(char *ordenador,char *cuenta,char *para,char *cc,char *cco,char *asunto,char *cuerpo,char *directorio,char *fichero,long prioridad,char *mime,long fecplanif,char *horaplanif,char *comentario,long ret,vdcorreoss *correos)
{
    int vdret;
    if (vdselcorreodet==NULL) init_selcorreodet();
    memset(&svdcorreos,0,sizeof(svdcorreos));
    strcpy(svdcorreos.ordenador,ordenador);
    strcpy(svdcorreos.cuenta,cuenta);
    strcpy(svdcorreos.para,para);
    strcpy(svdcorreos.cc,cc);
    strcpy(svdcorreos.cco,cco);
    strcpy(svdcorreos.asunto,asunto);
    strcpy(svdcorreos.cuerpo,cuerpo);
    strcpy(svdcorreos.directorio,directorio);
    strcpy(svdcorreos.fichero,fichero);
    svdcorreos.prioridad=prioridad;
    strcpy(svdcorreos.mime,mime);
    svdcorreos.fecplanif=fecplanif;
    strcpy(svdcorreos.horaplanif,horaplanif);
    strcpy(svdcorreos.comentario,comentario);
    svdcorreos.ret=ret;
    vdret=ejecutacursor(vdselcorreodet);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CORREOSproccorreodet vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *correos=svdcorreos;
    return(vdret);
}

int CORREOSproccorreo(char *tipocorreo,char *ordenador,char *asunto,char *cuerpo,char *directorio,char *fichero,long prioridad,char *mime,long fecplanif,char *horaplanif,char *comentario,long ret,vdcorreoss *correos)
{
    int vdret;
    if (vdselcorreo==NULL) init_selcorreo();
    memset(&svdcorreos,0,sizeof(svdcorreos));
    strcpy(svdcorreos.tipocorreo,tipocorreo);
    strcpy(svdcorreos.ordenador,ordenador);
    strcpy(svdcorreos.asunto,asunto);
    strcpy(svdcorreos.cuerpo,cuerpo);
    strcpy(svdcorreos.directorio,directorio);
    strcpy(svdcorreos.fichero,fichero);
    svdcorreos.prioridad=prioridad;
    strcpy(svdcorreos.mime,mime);
    svdcorreos.fecplanif=fecplanif;
    strcpy(svdcorreos.horaplanif,horaplanif);
    strcpy(svdcorreos.comentario,comentario);
    svdcorreos.ret=ret;
    vdret=ejecutacursor(vdselcorreo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CORREOSproccorreo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *correos=svdcorreos;
    return(vdret);
}

int CORREOSprocenviacorreo(long idmsg,char *comentario,long ret,vdcorreoss *correos)
{
    int vdret;
    if (vdselenviacorreo==NULL) init_selenviacorreo();
    memset(&svdcorreos,0,sizeof(svdcorreos));
    svdcorreos.idmsg=idmsg;
    strcpy(svdcorreos.comentario,comentario);
    svdcorreos.ret=ret;
    vdret=ejecutacursor(vdselenviacorreo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CORREOSprocenviacorreo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *correos=svdcorreos;
    return(vdret);
}

char * CORREOSdebug(vdcorreoss *correos)
{
    debugestruct(&dcorreos,correos,msgdebugcorreos);
    return(msgdebugcorreos);
}

