// Modulo generado automaticamente a partir de VDCONTEAUX.DEF
//#***
//# VDCONTEAUX.DEF - Generación automática del código c SOLOQUERY sobre la tabla VDCONTE
//# 
//# Propósito: idem.
//#           
//# Autor	 : JMM
//# Revisado por: 
//# Fecha  : 21-05-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=CNTAUX;
//
//EXTRA=RET,V10LONG
//EXTRA=VERIFICAUBI,V10CADENA,1
//EXTRA=CONCEPTOENT,V10CADENA,10
//EXTRA=CONCEPTOSAL,V10CADENA,10
//EXTRA=FUENTE,V10CADENA,12
//EXTRA=SUMIDERO,V10CADENA,12
//EXTRA=PATRONBLOQUEOSORI,V10CADENA,20
//EXTRA=OBSERV,V10CADENA,4096
//EXTRA=VDCONTE.CODMAT
//
//PROCEDURE=DAMETEMPORAL, BEGIN
//                         :RET :=VDCNT.DAMETEMPORAL(:VDUBICA.CODUBI,:VDCONTE.CODMAT);
//                      END;@
//                      
//PROCEDURE=REENGANCHACONTE, BEGIN
//                         VDCNT.REENGANCHACONTE(:VDMOVIM.CODMOV,:VDCONTE.CODMAT, :VERIFICAUBI, :VDCOMEN.COMENTARIO, :RET);
//                      END;@                      
//
//PROCEDURE=BLOQUEOSSTKCONTE, BEGIN
//                              VDCNT.BLOQUEOSSTKCONTE(:VDCONTE.CODMAT,:VDSTOCK.CODART,:VDSTOCK.CODLOT,:CONCEPTOENT,:FUENTE,:CONCEPTOSAL,:SUMIDERO,:PATRONBLOQUEOSORI,:VDSTOCK.BLOQUEOS,:OBSERV,:VDSTOCK.CANTIDAD,:VDCOMEN.COMENTARIO,:RET);
//                            END;@
//                      
//PROCEDURE=USACONTE, BEGIN
//                         VDCNT.USACONTE(:VDCONTE.CODMAT,:VDCONTE.CODUBI, :VDCONTE.TIPOCONTE, :VDCOMEN.COMENTARIO, :RET);
//                      END;@                     
//                      
//CURSOR=DAMECNTNOMOVIBLE,SELECT CODMAT FROM VDCONTE CNT, VDTIPOCONTE TCNT
//                           WHERE CODUBI=:VDUBICA.CODUBI AND 
//                                 TCNT.TIPOCONTE=CNT.TIPOCONTE AND 
//                                 MOVIBLE='N';
// 
//                           

#include "vd.h"\

#define SELDAMETEMPORAL " BEGIN :RET :=VDCNT.DAMETEMPORAL(:CODUBI,:CODMAT); END;"
static v10cursors *vdseldametemporal;
#define SELREENGANCHACONTE " BEGIN VDCNT.REENGANCHACONTE(:CODMOV,:CODMAT, :VERIFICAUBI, :COMENTARIO, :RET); END;"
static v10cursors *vdselreenganchaconte;
#define SELBLOQUEOSSTKCONTE " BEGIN VDCNT.BLOQUEOSSTKCONTE(:CODMAT,:CODART,:CODLOT,:CONCEPTOENT,:FUENTE,:CONCEPTOSAL,:SUMIDERO,:PATRONBLOQUEOSORI,:BLOQUEOS,:OBSERV,:CANTIDAD,:COMENTARIO,:RET); END;"
static v10cursors *vdselbloqueosstkconte;
#define SELUSACONTE " BEGIN VDCNT.USACONTE(:CODMAT,:CODUBI, :TIPOCONTE, :COMENTARIO, :RET); END;"
static v10cursors *vdselusaconte;
#define SELDAMECNTNOMOVIBLE "SELECT CODMAT FROM VDCONTE CNT, VDTIPOCONTE TCNT WHERE CODUBI=:CODUBI AND  TCNT.TIPOCONTE=CNT.TIPOCONTE AND  MOVIBLE='N'"
static v10cursors *vdseldamecntnomovible;

static vdcntauxs svdcntaux;

static diccols colvdcntaux[]={ 
    {"RET",V10LONG,(int)&svdcntaux.ret,sizeof(svdcntaux.ret)},
    {"VERIFICAUBI",V10CADENA,(int)&svdcntaux.verificaubi,sizeof(svdcntaux.verificaubi)},
    {"CONCEPTOENT",V10CADENA,(int)&svdcntaux.conceptoent,sizeof(svdcntaux.conceptoent)},
    {"CONCEPTOSAL",V10CADENA,(int)&svdcntaux.conceptosal,sizeof(svdcntaux.conceptosal)},
    {"FUENTE",V10CADENA,(int)&svdcntaux.fuente,sizeof(svdcntaux.fuente)},
    {"SUMIDERO",V10CADENA,(int)&svdcntaux.sumidero,sizeof(svdcntaux.sumidero)},
    {"PATRONBLOQUEOSORI",V10CADENA,(int)&svdcntaux.patronbloqueosori,sizeof(svdcntaux.patronbloqueosori)},
    {"OBSERV",V10CADENA,(int)&svdcntaux.observ,sizeof(svdcntaux.observ)},
    {"CODMAT",V10CADENA,(int)&svdcntaux.codmat,sizeof(svdcntaux.codmat)},
    {"CODUBI",V10CADENA,(int)&svdcntaux.codubi,sizeof(svdcntaux.codubi)},
    {"CODMOV",V10LONG,(int)&svdcntaux.codmov,sizeof(svdcntaux.codmov)},
    {"COMENTARIO",V10CADENA,(int)&svdcntaux.comentario,sizeof(svdcntaux.comentario)},
    {"CODART",V10CADENA,(int)&svdcntaux.codart,sizeof(svdcntaux.codart)},
    {"CODLOT",V10CADENA,(int)&svdcntaux.codlot,sizeof(svdcntaux.codlot)},
    {"BLOQUEOS",V10CADENA,(int)&svdcntaux.bloqueos,sizeof(svdcntaux.bloqueos)},
    {"CANTIDAD",V10DOUBLE,(int)&svdcntaux.cantidad,sizeof(svdcntaux.cantidad)},
    {"TIPOCONTE",V10CADENA,(int)&svdcntaux.tipoconte,sizeof(svdcntaux.tipoconte)}
    };

static diccionarios dvdcntaux[]={
    {colvdcntaux,17}
    };

diccionario dcntaux={dvdcntaux,1};

static char msgdebugcntaux[LCADENABIG];

static int init=0;


static void fin_vd_CNTAUX(void)
{
    if(vdseldametemporal){
        liberacursor(vdseldametemporal);
        vdseldametemporal=NULL;
    }
    if(vdselreenganchaconte){
        liberacursor(vdselreenganchaconte);
        vdselreenganchaconte=NULL;
    }
    if(vdselbloqueosstkconte){
        liberacursor(vdselbloqueosstkconte);
        vdselbloqueosstkconte=NULL;
    }
    if(vdselusaconte){
        liberacursor(vdselusaconte);
        vdselusaconte=NULL;
    }
    if(vdseldamecntnomovible){
        liberacursor(vdseldamecntnomovible);
        vdseldamecntnomovible=NULL;
    }
}


static void init_seldametemporal(void)
{
    int nc;

    for(nc=0;nc<dvdcntaux[0].numcol;nc++) dvdcntaux[0].c[nc].offset-=(int)&svdcntaux;

    vdseldametemporal=abrecursor(SELDAMETEMPORAL);
    definetodo(vdseldametemporal,NULL);
    bindtodo(vdseldametemporal,"RET",&svdcntaux.ret,sizeof(svdcntaux.ret),V10LONG,
             "CODUBI",svdcntaux.codubi,sizeof(svdcntaux.codubi),V10CADENA,
             "CODMAT",svdcntaux.codmat,sizeof(svdcntaux.codmat),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CNTAUX);
        init = 1;
    }
}

static void init_selreenganchaconte(void)
{
    int nc;

    for(nc=0;nc<dvdcntaux[0].numcol;nc++) dvdcntaux[0].c[nc].offset-=(int)&svdcntaux;

    vdselreenganchaconte=abrecursor(SELREENGANCHACONTE);
    definetodo(vdselreenganchaconte,NULL);
    bindtodo(vdselreenganchaconte,"CODMOV",&svdcntaux.codmov,sizeof(svdcntaux.codmov),V10LONG,
             "CODMAT",svdcntaux.codmat,sizeof(svdcntaux.codmat),V10CADENA,
             "VERIFICAUBI",svdcntaux.verificaubi,sizeof(svdcntaux.verificaubi),V10CADENA,
             "COMENTARIO",svdcntaux.comentario,sizeof(svdcntaux.comentario),V10CADENA,
             "RET",&svdcntaux.ret,sizeof(svdcntaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CNTAUX);
        init = 1;
    }
}

static void init_selbloqueosstkconte(void)
{
    int nc;

    for(nc=0;nc<dvdcntaux[0].numcol;nc++) dvdcntaux[0].c[nc].offset-=(int)&svdcntaux;

    vdselbloqueosstkconte=abrecursor(SELBLOQUEOSSTKCONTE);
    definetodo(vdselbloqueosstkconte,NULL);
    bindtodo(vdselbloqueosstkconte,"CODMAT",svdcntaux.codmat,sizeof(svdcntaux.codmat),V10CADENA,
             "CODART",svdcntaux.codart,sizeof(svdcntaux.codart),V10CADENA,
             "CODLOT",svdcntaux.codlot,sizeof(svdcntaux.codlot),V10CADENA,
             "CONCEPTOENT",svdcntaux.conceptoent,sizeof(svdcntaux.conceptoent),V10CADENA,
             "FUENTE",svdcntaux.fuente,sizeof(svdcntaux.fuente),V10CADENA,
             "CONCEPTOSAL",svdcntaux.conceptosal,sizeof(svdcntaux.conceptosal),V10CADENA,
             "SUMIDERO",svdcntaux.sumidero,sizeof(svdcntaux.sumidero),V10CADENA,
             "PATRONBLOQUEOSORI",svdcntaux.patronbloqueosori,sizeof(svdcntaux.patronbloqueosori),V10CADENA,
             "BLOQUEOS",svdcntaux.bloqueos,sizeof(svdcntaux.bloqueos),V10CADENA,
             "OBSERV",svdcntaux.observ,sizeof(svdcntaux.observ),V10CADENA,
             "CANTIDAD",&svdcntaux.cantidad,sizeof(svdcntaux.cantidad),V10DOUBLE,
             "COMENTARIO",svdcntaux.comentario,sizeof(svdcntaux.comentario),V10CADENA,
             "RET",&svdcntaux.ret,sizeof(svdcntaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CNTAUX);
        init = 1;
    }
}

static void init_selusaconte(void)
{
    int nc;

    for(nc=0;nc<dvdcntaux[0].numcol;nc++) dvdcntaux[0].c[nc].offset-=(int)&svdcntaux;

    vdselusaconte=abrecursor(SELUSACONTE);
    definetodo(vdselusaconte,NULL);
    bindtodo(vdselusaconte,"CODMAT",svdcntaux.codmat,sizeof(svdcntaux.codmat),V10CADENA,
             "CODUBI",svdcntaux.codubi,sizeof(svdcntaux.codubi),V10CADENA,
             "TIPOCONTE",svdcntaux.tipoconte,sizeof(svdcntaux.tipoconte),V10CADENA,
             "COMENTARIO",svdcntaux.comentario,sizeof(svdcntaux.comentario),V10CADENA,
             "RET",&svdcntaux.ret,sizeof(svdcntaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CNTAUX);
        init = 1;
    }
}

static void init_seldamecntnomovible(void)
{
    int nc;

    for(nc=0;nc<dvdcntaux[0].numcol;nc++) dvdcntaux[0].c[nc].offset-=(int)&svdcntaux;

    vdseldamecntnomovible=abrecursor(SELDAMECNTNOMOVIBLE);
    definetodo(vdseldamecntnomovible,svdcntaux.codmat,sizeof(svdcntaux.codmat),V10CADENA,
               NULL);
    bindtodo(vdseldamecntnomovible,"CODUBI",svdcntaux.codubi,sizeof(svdcntaux.codubi),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_CNTAUX);
        init = 1;
    }
}

diccionario *CNTAUXdamediccionario(void)
{
    return(&dcntaux);
}

int CNTAUXprocdametemporal(long ret,char *codubi,char *codmat,vdcntauxs *cntaux)
{
    int vdret;
    if (vdseldametemporal==NULL) init_seldametemporal();
    memset(&svdcntaux,0,sizeof(svdcntaux));
    svdcntaux.ret=ret;
    strcpy(svdcntaux.codubi,codubi);
    strcpy(svdcntaux.codmat,codmat);
    vdret=ejecutacursor(vdseldametemporal);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CNTAUXprocdametemporal vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cntaux=svdcntaux;
    return(vdret);
}

int CNTAUXprocreenganchaconte(long codmov,char *codmat,char *verificaubi,char *comentario,long ret,vdcntauxs *cntaux)
{
    int vdret;
    if (vdselreenganchaconte==NULL) init_selreenganchaconte();
    memset(&svdcntaux,0,sizeof(svdcntaux));
    svdcntaux.codmov=codmov;
    strcpy(svdcntaux.codmat,codmat);
    strcpy(svdcntaux.verificaubi,verificaubi);
    strcpy(svdcntaux.comentario,comentario);
    svdcntaux.ret=ret;
    vdret=ejecutacursor(vdselreenganchaconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CNTAUXprocreenganchaconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cntaux=svdcntaux;
    return(vdret);
}

int CNTAUXprocbloqueosstkconte(char *codmat,char *codart,char *codlot,char *conceptoent,char *fuente,char *conceptosal,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdcntauxs *cntaux)
{
    int vdret;
    if (vdselbloqueosstkconte==NULL) init_selbloqueosstkconte();
    memset(&svdcntaux,0,sizeof(svdcntaux));
    strcpy(svdcntaux.codmat,codmat);
    strcpy(svdcntaux.codart,codart);
    strcpy(svdcntaux.codlot,codlot);
    strcpy(svdcntaux.conceptoent,conceptoent);
    strcpy(svdcntaux.fuente,fuente);
    strcpy(svdcntaux.conceptosal,conceptosal);
    strcpy(svdcntaux.sumidero,sumidero);
    strcpy(svdcntaux.patronbloqueosori,patronbloqueosori);
    strcpy(svdcntaux.bloqueos,bloqueos);
    strcpy(svdcntaux.observ,observ);
    svdcntaux.cantidad=cantidad;
    strcpy(svdcntaux.comentario,comentario);
    svdcntaux.ret=ret;
    vdret=ejecutacursor(vdselbloqueosstkconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CNTAUXprocbloqueosstkconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cntaux=svdcntaux;
    return(vdret);
}

int CNTAUXprocusaconte(char *codmat,char *codubi,char *tipoconte,char *comentario,long ret,vdcntauxs *cntaux)
{
    int vdret;
    if (vdselusaconte==NULL) init_selusaconte();
    memset(&svdcntaux,0,sizeof(svdcntaux));
    strcpy(svdcntaux.codmat,codmat);
    strcpy(svdcntaux.codubi,codubi);
    strcpy(svdcntaux.tipoconte,tipoconte);
    strcpy(svdcntaux.comentario,comentario);
    svdcntaux.ret=ret;
    vdret=ejecutacursor(vdselusaconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta CNTAUXprocusaconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cntaux=svdcntaux;
    return(vdret);
}

int CNTAUXbuscadamecntnomovible(char *codubi,vdcntauxs *cntaux)
{
    int vdret;
    if (vdseldamecntnomovible==NULL) init_seldamecntnomovible();
    memset(&svdcntaux,0,sizeof(svdcntaux));
    strcpy(svdcntaux.codubi,codubi);
    vdret=ejefetchcursor(vdseldamecntnomovible);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch CNTAUXbuscadamecntnomovible vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *cntaux=svdcntaux;
    return(vdret);
}

int CNTAUXnextdamecntnomovible(vdcntauxs *cntaux)
{
    int vdret;
    vdret=fetchcursor(vdseldamecntnomovible);
    if (!vdret) {
        *cntaux=svdcntaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldamecntnomovible);
    return(VD_EERRORACLE);
}

char * CNTAUXdebug(vdcntauxs *cntaux)
{
    debugestruct(&dcntaux,cntaux,msgdebugcntaux);
    return(msgdebugcntaux);
}

