// Modulo generado automaticamente a partir de VDCOMENTARIOS.DEF
//#***
//# VDCOMENTARIOS.DEF - Generación automática del código c SOLOQUERY para API de comentarios
//# 
//# Propósito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 15-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=PLSQLCOMEN;
//
//EXTRA=VDCOMEN.COMENTARIO;
//EXTRA=VALOR,V10LONG;
//EXTRA=RET,V10LONG;
//EXTRA=MSJERROR,V10CADENA,1024;
//EXTRA=MITABLA,V10CADENA,30
//EXTRA=MICAMPOCOMEN,V10CADENA,30
//EXTRA=MIWHERE,V10CADENA,1024
//EXTRA=RELOGIN,V10LONG
//EXTRA=LISTACODCOMEN, V10CADENA,1024
//
//ORADEBUG=1280
// 
//CURSOR=DAMECOMEN,SELECT VDCOM.DAMECOMEN(:VDCOMEN.CODCOMEN,:VDCOMEN.TIPOCOMEN,:VDCOMEN.LINCOMEN) COMENTARIO, VDCOM.DAMERETORNO RET, VDCOM.DAMEERROR MSJERROR FROM DUAL;
//
//CURSOR=DAMERET,SELECT VDCOM.DAMERETORNO RET, VDCOM.DAMEERROR MSJERROR FROM DUAL;
//
//PROCEDURE=CREACOMEN, BEGIN VDCOM.LLCREACOMEN(:VDTIPOCOMEN.TABLACOMEN,:VDCOMEN.CODCOMEN,:VDCOMEN.TIPOCOMEN,:VDCOMEN.LINCOMEN,:VDCOMEN.COMENTARIO,:RELOGIN); END;@
//
//PROCEDURE=BORRACOMENPORTIPO, BEGIN VDCOM.BORRACOMENPORTIPO(:VDCOMEN.CODCOMEN, :VDCOMEN.TIPOCOMEN); END;@
//
//CURSOR=COMENPROPCADENA,SELECT VDCOM.COMENPROPCADENA(:VDCOMEN.CODCOMEN, :VDCOMEN.TIPOCOMEN) COMENTARIO FROM DUAL;
//
//CURSOR=COMENPROPENTERO,SELECT VDCOM.COMENPROPENTERO(:VDCOMEN.CODCOMEN, :VDCOMEN.TIPOCOMEN) VALOR FROM DUAL;
//
//PROCEDURE=MUEVECOMENDEML2PEL, BEGIN
//                         VDCOM.MUEVECOMENDEML2PEL(:VDPEDIDOLIN.CODDIV,:VDPEDIDOLIN.ANOPED,:VDPEDIDOLIN.CODPED,:VDPEDIDOLIN.SEQPED,:LISTACODCOMEN, :VDCOMEN.TIPOCOMEN);
//                      END;@
//                      
//PROCEDURE=MUEVECOMENDEML2UBI, BEGIN
//                         VDCOM.MUEVECOMENDEML2UBI(:VDUBICA.CODUBI,:LISTACODCOMEN, :VDCOMEN.TIPOCOMEN, :VDCOMEN.COMENTARIO);
//                         END;@                                           
//                      
//                      
//                  

#include "vd.h"\

#define SELDAMECOMEN "SELECT VDCOM.DAMECOMEN(:CODCOMEN,:TIPOCOMEN,:LINCOMEN) COMENTARIO, VDCOM.DAMERETORNO RET, VDCOM.DAMEERROR MSJERROR FROM DUAL"
static v10cursors *vdseldamecomen;
#define SELDAMERET "SELECT VDCOM.DAMERETORNO RET, VDCOM.DAMEERROR MSJERROR FROM DUAL"
static v10cursors *vdseldameret;
#define SELCREACOMEN " BEGIN VDCOM.LLCREACOMEN(:TABLACOMEN,:CODCOMEN,:TIPOCOMEN,:LINCOMEN,:COMENTARIO,:RELOGIN); END;"
static v10cursors *vdselcreacomen;
#define SELBORRACOMENPORTIPO " BEGIN VDCOM.BORRACOMENPORTIPO(:CODCOMEN, :TIPOCOMEN); END;"
static v10cursors *vdselborracomenportipo;
#define SELCOMENPROPCADENA "SELECT VDCOM.COMENPROPCADENA(:CODCOMEN, :TIPOCOMEN) COMENTARIO FROM DUAL"
static v10cursors *vdselcomenpropcadena;
#define SELCOMENPROPENTERO "SELECT VDCOM.COMENPROPENTERO(:CODCOMEN, :TIPOCOMEN) VALOR FROM DUAL"
static v10cursors *vdselcomenpropentero;
#define SELMUEVECOMENDEML2PEL " BEGIN VDCOM.MUEVECOMENDEML2PEL(:CODDIV,:ANOPED,:CODPED,:SEQPED,:LISTACODCOMEN, :TIPOCOMEN); END;"
static v10cursors *vdselmuevecomendeml2pel;
#define SELMUEVECOMENDEML2UBI " BEGIN VDCOM.MUEVECOMENDEML2UBI(:CODUBI,:LISTACODCOMEN, :TIPOCOMEN, :COMENTARIO); END;"
static v10cursors *vdselmuevecomendeml2ubi;

static vdplsqlcomens svdplsqlcomen;

static diccols colvdplsqlcomen[]={ 
    {"COMENTARIO",V10CADENA,(int)&svdplsqlcomen.comentario,sizeof(svdplsqlcomen.comentario)},
    {"VALOR",V10LONG,(int)&svdplsqlcomen.valor,sizeof(svdplsqlcomen.valor)},
    {"RET",V10LONG,(int)&svdplsqlcomen.ret,sizeof(svdplsqlcomen.ret)},
    {"MSJERROR",V10CADENA,(int)&svdplsqlcomen.msjerror,sizeof(svdplsqlcomen.msjerror)},
    {"MITABLA",V10CADENA,(int)&svdplsqlcomen.mitabla,sizeof(svdplsqlcomen.mitabla)},
    {"MICAMPOCOMEN",V10CADENA,(int)&svdplsqlcomen.micampocomen,sizeof(svdplsqlcomen.micampocomen)},
    {"MIWHERE",V10CADENA,(int)&svdplsqlcomen.miwhere,sizeof(svdplsqlcomen.miwhere)},
    {"RELOGIN",V10LONG,(int)&svdplsqlcomen.relogin,sizeof(svdplsqlcomen.relogin)},
    {"LISTACODCOMEN",V10CADENA,(int)&svdplsqlcomen.listacodcomen,sizeof(svdplsqlcomen.listacodcomen)},
    {"CODCOMEN",V10LONG,(int)&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen)},
    {"TIPOCOMEN",V10CADENA,(int)&svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen)},
    {"LINCOMEN",V10LONG,(int)&svdplsqlcomen.lincomen,sizeof(svdplsqlcomen.lincomen)},
    {"TABLACOMEN",V10CADENA,(int)&svdplsqlcomen.tablacomen,sizeof(svdplsqlcomen.tablacomen)},
    {"CODDIV",V10CADENA,(int)&svdplsqlcomen.coddiv,sizeof(svdplsqlcomen.coddiv)},
    {"ANOPED",V10LONG,(int)&svdplsqlcomen.anoped,sizeof(svdplsqlcomen.anoped)},
    {"CODPED",V10CADENA,(int)&svdplsqlcomen.codped,sizeof(svdplsqlcomen.codped)},
    {"SEQPED",V10LONG,(int)&svdplsqlcomen.seqped,sizeof(svdplsqlcomen.seqped)},
    {"CODUBI",V10CADENA,(int)&svdplsqlcomen.codubi,sizeof(svdplsqlcomen.codubi)}
    };

static diccionarios dvdplsqlcomen[]={
    {colvdplsqlcomen,18}
    };

diccionario dplsqlcomen={dvdplsqlcomen,1};

static char msgdebugplsqlcomen[LCADENABIG];

static int init=0;


static void fin_vd_PLSQLCOMEN(void)
{
    if(vdseldamecomen){
        liberacursor(vdseldamecomen);
        vdseldamecomen=NULL;
    }
    if(vdseldameret){
        liberacursor(vdseldameret);
        vdseldameret=NULL;
    }
    if(vdselcreacomen){
        liberacursor(vdselcreacomen);
        vdselcreacomen=NULL;
    }
    if(vdselborracomenportipo){
        liberacursor(vdselborracomenportipo);
        vdselborracomenportipo=NULL;
    }
    if(vdselcomenpropcadena){
        liberacursor(vdselcomenpropcadena);
        vdselcomenpropcadena=NULL;
    }
    if(vdselcomenpropentero){
        liberacursor(vdselcomenpropentero);
        vdselcomenpropentero=NULL;
    }
    if(vdselmuevecomendeml2pel){
        liberacursor(vdselmuevecomendeml2pel);
        vdselmuevecomendeml2pel=NULL;
    }
    if(vdselmuevecomendeml2ubi){
        liberacursor(vdselmuevecomendeml2ubi);
        vdselmuevecomendeml2ubi=NULL;
    }
}


static void init_seldamecomen(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdseldamecomen=abrecursordebug(SELDAMECOMEN,1280);
    definetodo(vdseldamecomen,svdplsqlcomen.comentario,sizeof(svdplsqlcomen.comentario),V10CADENA,
               &svdplsqlcomen.ret,sizeof(svdplsqlcomen.ret),V10LONG,
               svdplsqlcomen.msjerror,sizeof(svdplsqlcomen.msjerror),V10CADENA,
               NULL);
    bindtodo(vdseldamecomen,"CODCOMEN",&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen),V10LONG,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             "LINCOMEN",&svdplsqlcomen.lincomen,sizeof(svdplsqlcomen.lincomen),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_seldameret(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdseldameret=abrecursordebug(SELDAMERET,1280);
    definetodo(vdseldameret,&svdplsqlcomen.ret,sizeof(svdplsqlcomen.ret),V10LONG,
               svdplsqlcomen.msjerror,sizeof(svdplsqlcomen.msjerror),V10CADENA,
               NULL);
    bindtodo(vdseldameret,NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selcreacomen(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselcreacomen=abrecursordebug(SELCREACOMEN,1280);
    definetodo(vdselcreacomen,NULL);
    bindtodo(vdselcreacomen,"TABLACOMEN",svdplsqlcomen.tablacomen,sizeof(svdplsqlcomen.tablacomen),V10CADENA,
             "CODCOMEN",&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen),V10LONG,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             "LINCOMEN",&svdplsqlcomen.lincomen,sizeof(svdplsqlcomen.lincomen),V10LONG,
             "COMENTARIO",svdplsqlcomen.comentario,sizeof(svdplsqlcomen.comentario),V10CADENA,
             "RELOGIN",&svdplsqlcomen.relogin,sizeof(svdplsqlcomen.relogin),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selborracomenportipo(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselborracomenportipo=abrecursordebug(SELBORRACOMENPORTIPO,1280);
    definetodo(vdselborracomenportipo,NULL);
    bindtodo(vdselborracomenportipo,"CODCOMEN",&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen),V10LONG,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selcomenpropcadena(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselcomenpropcadena=abrecursordebug(SELCOMENPROPCADENA,1280);
    definetodo(vdselcomenpropcadena,svdplsqlcomen.comentario,sizeof(svdplsqlcomen.comentario),V10CADENA,
               NULL);
    bindtodo(vdselcomenpropcadena,"CODCOMEN",&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen),V10LONG,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selcomenpropentero(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselcomenpropentero=abrecursordebug(SELCOMENPROPENTERO,1280);
    definetodo(vdselcomenpropentero,&svdplsqlcomen.valor,sizeof(svdplsqlcomen.valor),V10LONG,
               NULL);
    bindtodo(vdselcomenpropentero,"CODCOMEN",&svdplsqlcomen.codcomen,sizeof(svdplsqlcomen.codcomen),V10LONG,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selmuevecomendeml2pel(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselmuevecomendeml2pel=abrecursordebug(SELMUEVECOMENDEML2PEL,1280);
    definetodo(vdselmuevecomendeml2pel,NULL);
    bindtodo(vdselmuevecomendeml2pel,"CODDIV",svdplsqlcomen.coddiv,sizeof(svdplsqlcomen.coddiv),V10CADENA,
             "ANOPED",&svdplsqlcomen.anoped,sizeof(svdplsqlcomen.anoped),V10LONG,
             "CODPED",svdplsqlcomen.codped,sizeof(svdplsqlcomen.codped),V10CADENA,
             "SEQPED",&svdplsqlcomen.seqped,sizeof(svdplsqlcomen.seqped),V10LONG,
             "LISTACODCOMEN",svdplsqlcomen.listacodcomen,sizeof(svdplsqlcomen.listacodcomen),V10CADENA,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

static void init_selmuevecomendeml2ubi(void)
{
    int nc;

    for(nc=0;nc<dvdplsqlcomen[0].numcol;nc++) dvdplsqlcomen[0].c[nc].offset-=(int)&svdplsqlcomen;

    vdselmuevecomendeml2ubi=abrecursordebug(SELMUEVECOMENDEML2UBI,1280);
    definetodo(vdselmuevecomendeml2ubi,NULL);
    bindtodo(vdselmuevecomendeml2ubi,"CODUBI",svdplsqlcomen.codubi,sizeof(svdplsqlcomen.codubi),V10CADENA,
             "LISTACODCOMEN",svdplsqlcomen.listacodcomen,sizeof(svdplsqlcomen.listacodcomen),V10CADENA,
             "TIPOCOMEN",svdplsqlcomen.tipocomen,sizeof(svdplsqlcomen.tipocomen),V10CADENA,
             "COMENTARIO",svdplsqlcomen.comentario,sizeof(svdplsqlcomen.comentario),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PLSQLCOMEN);
        init = 1;
    }
}

diccionario *PLSQLCOMENdamediccionario(void)
{
    return(&dplsqlcomen);
}

int PLSQLCOMENbuscadamecomen(long codcomen,char *tipocomen,long lincomen,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdseldamecomen==NULL) init_seldamecomen();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    svdplsqlcomen.codcomen=codcomen;
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    svdplsqlcomen.lincomen=lincomen;
    vdret=ejefetchcursor(vdseldamecomen);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PLSQLCOMENbuscadamecomen vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENnextdamecomen(vdplsqlcomens *plsqlcomen)
{
    int vdret;
    vdret=fetchcursor(vdseldamecomen);
    if (!vdret) {
        *plsqlcomen=svdplsqlcomen;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldamecomen);
    return(VD_EERRORACLE);
}

int PLSQLCOMENbuscadameret(vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdseldameret==NULL) init_seldameret();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    vdret=ejefetchcursor(vdseldameret);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PLSQLCOMENbuscadameret vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENnextdameret(vdplsqlcomens *plsqlcomen)
{
    int vdret;
    vdret=fetchcursor(vdseldameret);
    if (!vdret) {
        *plsqlcomen=svdplsqlcomen;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldameret);
    return(VD_EERRORACLE);
}

int PLSQLCOMENproccreacomen(char *tablacomen,long codcomen,char *tipocomen,long lincomen,char *comentario,long relogin,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselcreacomen==NULL) init_selcreacomen();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    strcpy(svdplsqlcomen.tablacomen,tablacomen);
    svdplsqlcomen.codcomen=codcomen;
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    svdplsqlcomen.lincomen=lincomen;
    strcpy(svdplsqlcomen.comentario,comentario);
    svdplsqlcomen.relogin=relogin;
    vdret=ejecutacursor(vdselcreacomen);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PLSQLCOMENproccreacomen vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENprocborracomenportipo(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselborracomenportipo==NULL) init_selborracomenportipo();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    svdplsqlcomen.codcomen=codcomen;
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    vdret=ejecutacursor(vdselborracomenportipo);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PLSQLCOMENprocborracomenportipo vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENbuscacomenpropcadena(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselcomenpropcadena==NULL) init_selcomenpropcadena();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    svdplsqlcomen.codcomen=codcomen;
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    vdret=ejefetchcursor(vdselcomenpropcadena);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PLSQLCOMENbuscacomenpropcadena vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENnextcomenpropcadena(vdplsqlcomens *plsqlcomen)
{
    int vdret;
    vdret=fetchcursor(vdselcomenpropcadena);
    if (!vdret) {
        *plsqlcomen=svdplsqlcomen;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcomenpropcadena);
    return(VD_EERRORACLE);
}

int PLSQLCOMENbuscacomenpropentero(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselcomenpropentero==NULL) init_selcomenpropentero();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    svdplsqlcomen.codcomen=codcomen;
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    vdret=ejefetchcursor(vdselcomenpropentero);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PLSQLCOMENbuscacomenpropentero vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENnextcomenpropentero(vdplsqlcomens *plsqlcomen)
{
    int vdret;
    vdret=fetchcursor(vdselcomenpropentero);
    if (!vdret) {
        *plsqlcomen=svdplsqlcomen;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcomenpropentero);
    return(VD_EERRORACLE);
}

int PLSQLCOMENprocmuevecomendeml2pel(char *coddiv,long anoped,char *codped,long seqped,char *listacodcomen,char *tipocomen,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselmuevecomendeml2pel==NULL) init_selmuevecomendeml2pel();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    strcpy(svdplsqlcomen.coddiv,coddiv);
    svdplsqlcomen.anoped=anoped;
    strcpy(svdplsqlcomen.codped,codped);
    svdplsqlcomen.seqped=seqped;
    strcpy(svdplsqlcomen.listacodcomen,listacodcomen);
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    vdret=ejecutacursor(vdselmuevecomendeml2pel);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PLSQLCOMENprocmuevecomendeml2pel vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

int PLSQLCOMENprocmuevecomendeml2ubi(char *codubi,char *listacodcomen,char *tipocomen,char *comentario,vdplsqlcomens *plsqlcomen)
{
    int vdret;
    if (vdselmuevecomendeml2ubi==NULL) init_selmuevecomendeml2ubi();
    memset(&svdplsqlcomen,0,sizeof(svdplsqlcomen));
    strcpy(svdplsqlcomen.codubi,codubi);
    strcpy(svdplsqlcomen.listacodcomen,listacodcomen);
    strcpy(svdplsqlcomen.tipocomen,tipocomen);
    strcpy(svdplsqlcomen.comentario,comentario);
    vdret=ejecutacursor(vdselmuevecomendeml2ubi);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PLSQLCOMENprocmuevecomendeml2ubi vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *plsqlcomen=svdplsqlcomen;
    return(vdret);
}

char * PLSQLCOMENdebug(vdplsqlcomens *plsqlcomen)
{
    debugestruct(&dplsqlcomen,plsqlcomen,msgdebugplsqlcomen);
    return(msgdebugplsqlcomen);
}

