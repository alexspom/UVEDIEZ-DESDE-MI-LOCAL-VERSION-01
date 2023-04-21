// Modulo generado automaticamente a partir de VDIMPRESIONAUX.DEF
//#***
//# VDIMPRESION.DEF - Generación automática del código c SOLOQUERY para querys sobre tablas de impresión V10
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 23-05-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=IMPRE;
//EXTRA=RET,V10LONG
//EXTRA=NUMASIG,V10LONG
//
//CURSOR=CCUENTAASIGUSER SELECT COUNT(*) NUMASIG FROM VDIMPREASIG WHERE CODOPEASIG=VDUSER.GETUSER 
//                                                                AND (ORDENADOR=UPPER(:VDIMPRESPOOL.ORDENADOR) OR ORDENADOR='DEFECTO')
//                                                                AND TIPOIMPRE=:VDIMPRESPOOL.TIPOIMPRE AND 
//                                                                (DOCUMENTO=UPPER(:VDIMPRESPOOL.DOCUMENTO) OR DOCUMENTO='DEFECTO') 
//                                                                AND ACTIVO='S';
//                                                                
//CURSOR=CCUENTAASIG SELECT COUNT(*) NUMASIG FROM VDIMPREASIG WHERE CODOPEASIG='DEFECTO'
//                                                                AND (ORDENADOR=UPPER(:VDIMPRESPOOL.ORDENADOR) OR ORDENADOR='DEFECTO')
//                                                                AND TIPOIMPRE=:VDIMPRESPOOL.TIPOIMPRE AND 
//                                                                (DOCUMENTO=UPPER(:VDIMPRESPOOL.DOCUMENTO) OR DOCUMENTO='DEFECTO') 
//                                                                AND ACTIVO='S';
//
//PROCEDURE=SPOOL,BEGIN                       
//                  VDIMPRE.SPOOL(:VDIMPRESPOOL.ORDENADOR,:VDIMPRESPOOL.TIPOIMPRE,:VDIMPRESPOOL.CODIMPRE,:VDIMPRESPOOL.FICHERO,
//                                :VDIMPRESPOOL.DOCUMENTO,:VDIMPRESPOOL.PARAMS,:VDIMPRESPOOL.NUMCOPIAS, :VDIMPRESPOOL.FECPLANIF,
//                                :VDIMPRESPOOL.HORAPLANIF,:RET);
//                   END;@    
//
//PROCEDURE=AUDITA,BEGIN                       
//                  VDIMPRE.AUDITA(:VDIMPRESPOOL.ORDENADOR,:VDIMPRESPOOL.TIPOIMPRE,:VDIMPRESPOOL.CODIMPRE,:VDIMPRESPOOL.FICHERO,
//                                :VDIMPRESPOOL.DOCUMENTO,:VDIMPRESPOOL.PARAMS,:VDIMPRESPOOL.NUMCOPIAS, :VDIMPRESPOOL.FECPLANIF,
//                                :VDIMPRESPOOL.HORAPLANIF,:RET);
//                   END;@    
//
//
//

#include "vd.h"\

#define SELCCUENTAASIGUSER "SELECT COUNT(*) NUMASIG FROM VDIMPREASIG WHERE CODOPEASIG=VDUSER.GETUSER  AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND  (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO')  AND ACTIVO='S'"
static v10cursors *vdselccuentaasiguser;
#define SELCCUENTAASIG "SELECT COUNT(*) NUMASIG FROM VDIMPREASIG WHERE CODOPEASIG='DEFECTO' AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND  (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO')  AND ACTIVO='S'"
static v10cursors *vdselccuentaasig;
#define SELSPOOL "BEGIN                        VDIMPRE.SPOOL(:ORDENADOR,:TIPOIMPRE,:CODIMPRE,:FICHERO, :DOCUMENTO,:PARAMS,:NUMCOPIAS, :FECPLANIF, :HORAPLANIF,:RET); END;"
static v10cursors *vdselspool;
#define SELAUDITA "BEGIN                        VDIMPRE.AUDITA(:ORDENADOR,:TIPOIMPRE,:CODIMPRE,:FICHERO, :DOCUMENTO,:PARAMS,:NUMCOPIAS, :FECPLANIF, :HORAPLANIF,:RET); END;"
static v10cursors *vdselaudita;

static vdimpres svdimpre;

static diccols colvdimpre[]={ 
    {"RET",V10LONG,(int)&svdimpre.ret,sizeof(svdimpre.ret)},
    {"NUMASIG",V10LONG,(int)&svdimpre.numasig,sizeof(svdimpre.numasig)},
    {"ORDENADOR",V10CADENA,(int)&svdimpre.ordenador,sizeof(svdimpre.ordenador)},
    {"TIPOIMPRE",V10CADENA,(int)&svdimpre.tipoimpre,sizeof(svdimpre.tipoimpre)},
    {"DOCUMENTO",V10CADENA,(int)&svdimpre.documento,sizeof(svdimpre.documento)},
    {"CODIMPRE",V10CADENA,(int)&svdimpre.codimpre,sizeof(svdimpre.codimpre)},
    {"FICHERO",V10CADENA,(int)&svdimpre.fichero,sizeof(svdimpre.fichero)},
    {"PARAMS",V10CADENA,(int)&svdimpre.params,sizeof(svdimpre.params)},
    {"NUMCOPIAS",V10LONG,(int)&svdimpre.numcopias,sizeof(svdimpre.numcopias)},
    {"FECPLANIF",V10LONG,(int)&svdimpre.fecplanif,sizeof(svdimpre.fecplanif)},
    {"HORAPLANIF",V10CADENA,(int)&svdimpre.horaplanif,sizeof(svdimpre.horaplanif)}
    };

static diccionarios dvdimpre[]={
    {colvdimpre,11}
    };

diccionario dimpre={dvdimpre,1};

static char msgdebugimpre[LCADENABIG];

static int init=0;


static void fin_vd_IMPRE(void)
{
    if(vdselccuentaasiguser){
        liberacursor(vdselccuentaasiguser);
        vdselccuentaasiguser=NULL;
    }
    if(vdselccuentaasig){
        liberacursor(vdselccuentaasig);
        vdselccuentaasig=NULL;
    }
    if(vdselspool){
        liberacursor(vdselspool);
        vdselspool=NULL;
    }
    if(vdselaudita){
        liberacursor(vdselaudita);
        vdselaudita=NULL;
    }
}


static void init_selccuentaasiguser(void)
{
    int nc;

    for(nc=0;nc<dvdimpre[0].numcol;nc++) dvdimpre[0].c[nc].offset-=(int)&svdimpre;

    vdselccuentaasiguser=abrecursor(SELCCUENTAASIGUSER);
    definetodo(vdselccuentaasiguser,&svdimpre.numasig,sizeof(svdimpre.numasig),V10LONG,
               NULL);
    bindtodo(vdselccuentaasiguser,"ORDENADOR",svdimpre.ordenador,sizeof(svdimpre.ordenador),V10CADENA,
             "TIPOIMPRE",svdimpre.tipoimpre,sizeof(svdimpre.tipoimpre),V10CADENA,
             "DOCUMENTO",svdimpre.documento,sizeof(svdimpre.documento),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_IMPRE);
        init = 1;
    }
}

static void init_selccuentaasig(void)
{
    int nc;

    for(nc=0;nc<dvdimpre[0].numcol;nc++) dvdimpre[0].c[nc].offset-=(int)&svdimpre;

    vdselccuentaasig=abrecursor(SELCCUENTAASIG);
    definetodo(vdselccuentaasig,&svdimpre.numasig,sizeof(svdimpre.numasig),V10LONG,
               NULL);
    bindtodo(vdselccuentaasig,"ORDENADOR",svdimpre.ordenador,sizeof(svdimpre.ordenador),V10CADENA,
             "TIPOIMPRE",svdimpre.tipoimpre,sizeof(svdimpre.tipoimpre),V10CADENA,
             "DOCUMENTO",svdimpre.documento,sizeof(svdimpre.documento),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_IMPRE);
        init = 1;
    }
}

static void init_selspool(void)
{
    int nc;

    for(nc=0;nc<dvdimpre[0].numcol;nc++) dvdimpre[0].c[nc].offset-=(int)&svdimpre;

    vdselspool=abrecursor(SELSPOOL);
    definetodo(vdselspool,NULL);
    bindtodo(vdselspool,"ORDENADOR",svdimpre.ordenador,sizeof(svdimpre.ordenador),V10CADENA,
             "TIPOIMPRE",svdimpre.tipoimpre,sizeof(svdimpre.tipoimpre),V10CADENA,
             "CODIMPRE",svdimpre.codimpre,sizeof(svdimpre.codimpre),V10CADENA,
             "FICHERO",svdimpre.fichero,sizeof(svdimpre.fichero),V10CADENA,
             "DOCUMENTO",svdimpre.documento,sizeof(svdimpre.documento),V10CADENA,
             "PARAMS",svdimpre.params,sizeof(svdimpre.params),V10CADENA,
             "NUMCOPIAS",&svdimpre.numcopias,sizeof(svdimpre.numcopias),V10LONG,
             "FECPLANIF",&svdimpre.fecplanif,sizeof(svdimpre.fecplanif),V10LONG,
             "HORAPLANIF",svdimpre.horaplanif,sizeof(svdimpre.horaplanif),V10CADENA,
             "RET",&svdimpre.ret,sizeof(svdimpre.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_IMPRE);
        init = 1;
    }
}

static void init_selaudita(void)
{
    int nc;

    for(nc=0;nc<dvdimpre[0].numcol;nc++) dvdimpre[0].c[nc].offset-=(int)&svdimpre;

    vdselaudita=abrecursor(SELAUDITA);
    definetodo(vdselaudita,NULL);
    bindtodo(vdselaudita,"ORDENADOR",svdimpre.ordenador,sizeof(svdimpre.ordenador),V10CADENA,
             "TIPOIMPRE",svdimpre.tipoimpre,sizeof(svdimpre.tipoimpre),V10CADENA,
             "CODIMPRE",svdimpre.codimpre,sizeof(svdimpre.codimpre),V10CADENA,
             "FICHERO",svdimpre.fichero,sizeof(svdimpre.fichero),V10CADENA,
             "DOCUMENTO",svdimpre.documento,sizeof(svdimpre.documento),V10CADENA,
             "PARAMS",svdimpre.params,sizeof(svdimpre.params),V10CADENA,
             "NUMCOPIAS",&svdimpre.numcopias,sizeof(svdimpre.numcopias),V10LONG,
             "FECPLANIF",&svdimpre.fecplanif,sizeof(svdimpre.fecplanif),V10LONG,
             "HORAPLANIF",svdimpre.horaplanif,sizeof(svdimpre.horaplanif),V10CADENA,
             "RET",&svdimpre.ret,sizeof(svdimpre.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_IMPRE);
        init = 1;
    }
}

diccionario *IMPREdamediccionario(void)
{
    return(&dimpre);
}

int IMPREbuscaccuentaasiguser(char *ordenador,char *tipoimpre,char *documento,vdimpres *impre)
{
    int vdret;
    if (vdselccuentaasiguser==NULL) init_selccuentaasiguser();
    memset(&svdimpre,0,sizeof(svdimpre));
    strcpy(svdimpre.ordenador,ordenador);
    strcpy(svdimpre.tipoimpre,tipoimpre);
    strcpy(svdimpre.documento,documento);
    vdret=ejefetchcursor(vdselccuentaasiguser);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch IMPREbuscaccuentaasiguser vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *impre=svdimpre;
    return(vdret);
}

int IMPREnextccuentaasiguser(vdimpres *impre)
{
    int vdret;
    vdret=fetchcursor(vdselccuentaasiguser);
    if (!vdret) {
        *impre=svdimpre;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselccuentaasiguser);
    return(VD_EERRORACLE);
}

int IMPREbuscaccuentaasig(char *ordenador,char *tipoimpre,char *documento,vdimpres *impre)
{
    int vdret;
    if (vdselccuentaasig==NULL) init_selccuentaasig();
    memset(&svdimpre,0,sizeof(svdimpre));
    strcpy(svdimpre.ordenador,ordenador);
    strcpy(svdimpre.tipoimpre,tipoimpre);
    strcpy(svdimpre.documento,documento);
    vdret=ejefetchcursor(vdselccuentaasig);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch IMPREbuscaccuentaasig vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *impre=svdimpre;
    return(vdret);
}

int IMPREnextccuentaasig(vdimpres *impre)
{
    int vdret;
    vdret=fetchcursor(vdselccuentaasig);
    if (!vdret) {
        *impre=svdimpre;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselccuentaasig);
    return(VD_EERRORACLE);
}

int IMPREprocspool(char *ordenador,char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif,long ret,vdimpres *impre)
{
    int vdret;
    if (vdselspool==NULL) init_selspool();
    memset(&svdimpre,0,sizeof(svdimpre));
    strcpy(svdimpre.ordenador,ordenador);
    strcpy(svdimpre.tipoimpre,tipoimpre);
    strcpy(svdimpre.codimpre,codimpre);
    strcpy(svdimpre.fichero,fichero);
    strcpy(svdimpre.documento,documento);
    strcpy(svdimpre.params,params);
    svdimpre.numcopias=numcopias;
    svdimpre.fecplanif=fecplanif;
    strcpy(svdimpre.horaplanif,horaplanif);
    svdimpre.ret=ret;
    vdret=ejecutacursor(vdselspool);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta IMPREprocspool vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *impre=svdimpre;
    return(vdret);
}

int IMPREprocaudita(char *ordenador,char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif,long ret,vdimpres *impre)
{
    int vdret;
    if (vdselaudita==NULL) init_selaudita();
    memset(&svdimpre,0,sizeof(svdimpre));
    strcpy(svdimpre.ordenador,ordenador);
    strcpy(svdimpre.tipoimpre,tipoimpre);
    strcpy(svdimpre.codimpre,codimpre);
    strcpy(svdimpre.fichero,fichero);
    strcpy(svdimpre.documento,documento);
    strcpy(svdimpre.params,params);
    svdimpre.numcopias=numcopias;
    svdimpre.fecplanif=fecplanif;
    strcpy(svdimpre.horaplanif,horaplanif);
    svdimpre.ret=ret;
    vdret=ejecutacursor(vdselaudita);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta IMPREprocaudita vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *impre=svdimpre;
    return(vdret);
}

char * IMPREdebug(vdimpres *impre)
{
    debugestruct(&dimpre,impre,msgdebugimpre);
    return(msgdebugimpre);
}

