// Modulo generado automaticamente a partir de VDPEDIDOAUX.DEF
//#***
//# VDPEDIDOAUX.DEF - Generación automática del código c SOLOQUERY para Pedidos                                                       
//# 
//# Propósito: idem.
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 27-03-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=PEDIDO;
//
//EXTRA=NUEVAVERSION,V10LONG
//EXTRA=ESTADOSPR,V10LONG;
//EXTRA=ESTADOSEX,V10LONG;
//EXTRA=ESTADOINI,V10LONG;
//EXTRA=ESTADOFIN,V10LONG;
//EXTRA=RET,V10LONG;
//EXTRA=VDPEDIDOCAB.CODDIV;
//EXTRA=VDPEDIDOCAB.ANOPED;
//EXTRA=VDPEDIDOCAB.CODPED;
//EXTRA=VDPEDIDOCAB.SEQPED;
//
//
//SELECT=NUEVAVERSION,SELECT NVL(MAX(SEQPED),0)+1 NUEVAVERSION
//                      FROM VDPEDIDOCAB
//				             WHERE CODDIV=:VDPEDIDOCAB.CODDIV AND ANOPED=:VDPEDIDOCAB.ANOPED AND CODPED=:VDPEDIDOCAB.CODPED;
//
//PROCEDURE=FINPEDIDO,BEGIN VDPED.FINPEDIDO(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,:VDPEDIDOCAB.STATUS,
//                                          :ESTADOSPR,:ESTADOSEX,:RET); END;@
//                                          
//PROCEDURE=CREAVERSION,BEGIN VDPED.CREAVERSION(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,:VDCOMEN.COMENTARIO,:RET); END;@                                          
//				             
//CURSOR=STATUSPRIO,SELECT CODDIV,ANOPED,CODPED,SEQPED FROM VDPEDIDOCAB PEC, VDSERIEEXP SEX 
//                    WHERE PEC.STATUS=:VDPEDIDOCAB.STATUS AND
//                          PEC.CODSERIEEXP = SEX.CODSERIEEXP
//              ORDER BY SEX.PRIORIDAD, SEX.CODSERIEEXP, PEC.PRIORIDAD, PEC.FECSERVICIO, PEC.CODDIV, PEC.ANOPED, PEC.CODPED, PEC.SEQPED;
//
//PROCEDURE=DISPONIBILIDAD, BEGIN
//                              VDDISP.CALCULADISP(:VDTAREAS.TAREA);
//                          END;@
//
//PROCEDURE=LIBERAMOVPEDIDO, BEGIN VDPED.LIBERAMOVPEDIDO(:VDPEDIDOCAB.CODDEMANDA,:ESTADOINI,:ESTADOFIN,:RET); END;@
//
//PROCEDURE=ACTLINEASPEDIDO,BEGIN 
//                              VDPED.ACTLINEASPEDIDO(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,:RET); 
//                          END;@

#include "vdpedidos.h"\

#define SELNUEVAVERSION "SELECT NVL(MAX(SEQPED),0)+1 NUEVAVERSION FROM VDPEDIDOCAB WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED"
static v10cursors *vdselnuevaversion;
#define SELFINPEDIDO "BEGIN VDPED.FINPEDIDO(:CODDIV,:ANOPED,:CODPED,:SEQPED,:STATUS, :ESTADOSPR,:ESTADOSEX,:RET); END;"
static v10cursors *vdselfinpedido;
#define SELCREAVERSION "BEGIN VDPED.CREAVERSION(:CODDIV,:ANOPED,:CODPED,:SEQPED,:COMENTARIO,:RET); END;"
static v10cursors *vdselcreaversion;
#define SELSTATUSPRIO "SELECT CODDIV,ANOPED,CODPED,SEQPED FROM VDPEDIDOCAB PEC, VDSERIEEXP SEX  WHERE PEC.STATUS=:STATUS AND PEC.CODSERIEEXP = SEX.CODSERIEEXP ORDER BY SEX.PRIORIDAD, SEX.CODSERIEEXP, PEC.PRIORIDAD, PEC.FECSERVICIO, PEC.CODDIV, PEC.ANOPED, PEC.CODPED, PEC.SEQPED"
static v10cursors *vdselstatusprio;
#define SELDISPONIBILIDAD " BEGIN VDDISP.CALCULADISP(:TAREA); END;"
static v10cursors *vdseldisponibilidad;
#define SELLIBERAMOVPEDIDO " BEGIN VDPED.LIBERAMOVPEDIDO(:CODDEMANDA,:ESTADOINI,:ESTADOFIN,:RET); END;"
static v10cursors *vdselliberamovpedido;
#define SELACTLINEASPEDIDO "BEGIN  VDPED.ACTLINEASPEDIDO(:CODDIV,:ANOPED,:CODPED,:SEQPED,:RET);  END;"
static v10cursors *vdselactlineaspedido;

static vdpedidos svdpedido;

static diccols colvdpedido[]={ 
    {"NUEVAVERSION",V10LONG,(int)&svdpedido.nuevaversion,sizeof(svdpedido.nuevaversion)},
    {"ESTADOSPR",V10LONG,(int)&svdpedido.estadospr,sizeof(svdpedido.estadospr)},
    {"ESTADOSEX",V10LONG,(int)&svdpedido.estadosex,sizeof(svdpedido.estadosex)},
    {"ESTADOINI",V10LONG,(int)&svdpedido.estadoini,sizeof(svdpedido.estadoini)},
    {"ESTADOFIN",V10LONG,(int)&svdpedido.estadofin,sizeof(svdpedido.estadofin)},
    {"RET",V10LONG,(int)&svdpedido.ret,sizeof(svdpedido.ret)},
    {"CODDIV",V10CADENA,(int)&svdpedido.coddiv,sizeof(svdpedido.coddiv)},
    {"ANOPED",V10LONG,(int)&svdpedido.anoped,sizeof(svdpedido.anoped)},
    {"CODPED",V10CADENA,(int)&svdpedido.codped,sizeof(svdpedido.codped)},
    {"SEQPED",V10LONG,(int)&svdpedido.seqped,sizeof(svdpedido.seqped)},
    {"STATUS",V10LONG,(int)&svdpedido.status,sizeof(svdpedido.status)},
    {"COMENTARIO",V10CADENA,(int)&svdpedido.comentario,sizeof(svdpedido.comentario)},
    {"TAREA",V10CADENA,(int)&svdpedido.tarea,sizeof(svdpedido.tarea)},
    {"CODDEMANDA",V10CADENA,(int)&svdpedido.coddemanda,sizeof(svdpedido.coddemanda)}
    };

static diccionarios dvdpedido[]={
    {colvdpedido,14}
    };

diccionario dpedido={dvdpedido,1};

static char msgdebugpedido[LCADENABIG];

static int init=0;


static void fin_vd_PEDIDO(void)
{
    if(vdselnuevaversion){
        liberacursor(vdselnuevaversion);
        vdselnuevaversion=NULL;
    }
    if(vdselfinpedido){
        liberacursor(vdselfinpedido);
        vdselfinpedido=NULL;
    }
    if(vdselcreaversion){
        liberacursor(vdselcreaversion);
        vdselcreaversion=NULL;
    }
    if(vdselstatusprio){
        liberacursor(vdselstatusprio);
        vdselstatusprio=NULL;
    }
    if(vdseldisponibilidad){
        liberacursor(vdseldisponibilidad);
        vdseldisponibilidad=NULL;
    }
    if(vdselliberamovpedido){
        liberacursor(vdselliberamovpedido);
        vdselliberamovpedido=NULL;
    }
    if(vdselactlineaspedido){
        liberacursor(vdselactlineaspedido);
        vdselactlineaspedido=NULL;
    }
}


static void init_selnuevaversion(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselnuevaversion=abrecursor(SELNUEVAVERSION);
    definetodo(vdselnuevaversion,&svdpedido.nuevaversion,sizeof(svdpedido.nuevaversion),V10LONG,
               NULL);
    bindtodo(vdselnuevaversion,"CODDIV",svdpedido.coddiv,sizeof(svdpedido.coddiv),V10CADENA,
             "ANOPED",&svdpedido.anoped,sizeof(svdpedido.anoped),V10LONG,
             "CODPED",svdpedido.codped,sizeof(svdpedido.codped),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_selfinpedido(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselfinpedido=abrecursor(SELFINPEDIDO);
    definetodo(vdselfinpedido,NULL);
    bindtodo(vdselfinpedido,"CODDIV",svdpedido.coddiv,sizeof(svdpedido.coddiv),V10CADENA,
             "ANOPED",&svdpedido.anoped,sizeof(svdpedido.anoped),V10LONG,
             "CODPED",svdpedido.codped,sizeof(svdpedido.codped),V10CADENA,
             "SEQPED",&svdpedido.seqped,sizeof(svdpedido.seqped),V10LONG,
             "STATUS",&svdpedido.status,sizeof(svdpedido.status),V10LONG,
             "ESTADOSPR",&svdpedido.estadospr,sizeof(svdpedido.estadospr),V10LONG,
             "ESTADOSEX",&svdpedido.estadosex,sizeof(svdpedido.estadosex),V10LONG,
             "RET",&svdpedido.ret,sizeof(svdpedido.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_selcreaversion(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselcreaversion=abrecursor(SELCREAVERSION);
    definetodo(vdselcreaversion,NULL);
    bindtodo(vdselcreaversion,"CODDIV",svdpedido.coddiv,sizeof(svdpedido.coddiv),V10CADENA,
             "ANOPED",&svdpedido.anoped,sizeof(svdpedido.anoped),V10LONG,
             "CODPED",svdpedido.codped,sizeof(svdpedido.codped),V10CADENA,
             "SEQPED",&svdpedido.seqped,sizeof(svdpedido.seqped),V10LONG,
             "COMENTARIO",svdpedido.comentario,sizeof(svdpedido.comentario),V10CADENA,
             "RET",&svdpedido.ret,sizeof(svdpedido.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_selstatusprio(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselstatusprio=abrecursor(SELSTATUSPRIO);
    definetodo(vdselstatusprio,svdpedido.coddiv,sizeof(svdpedido.coddiv),V10CADENA,
               &svdpedido.anoped,sizeof(svdpedido.anoped),V10LONG,
               svdpedido.codped,sizeof(svdpedido.codped),V10CADENA,
               &svdpedido.seqped,sizeof(svdpedido.seqped),V10LONG,
               NULL);
    bindtodo(vdselstatusprio,"STATUS",&svdpedido.status,sizeof(svdpedido.status),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_seldisponibilidad(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdseldisponibilidad=abrecursor(SELDISPONIBILIDAD);
    definetodo(vdseldisponibilidad,NULL);
    bindtodo(vdseldisponibilidad,"TAREA",svdpedido.tarea,sizeof(svdpedido.tarea),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_selliberamovpedido(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselliberamovpedido=abrecursor(SELLIBERAMOVPEDIDO);
    definetodo(vdselliberamovpedido,NULL);
    bindtodo(vdselliberamovpedido,"CODDEMANDA",svdpedido.coddemanda,sizeof(svdpedido.coddemanda),V10CADENA,
             "ESTADOINI",&svdpedido.estadoini,sizeof(svdpedido.estadoini),V10LONG,
             "ESTADOFIN",&svdpedido.estadofin,sizeof(svdpedido.estadofin),V10LONG,
             "RET",&svdpedido.ret,sizeof(svdpedido.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

static void init_selactlineaspedido(void)
{
    int nc;

    for(nc=0;nc<dvdpedido[0].numcol;nc++) dvdpedido[0].c[nc].offset-=(int)&svdpedido;

    vdselactlineaspedido=abrecursor(SELACTLINEASPEDIDO);
    definetodo(vdselactlineaspedido,NULL);
    bindtodo(vdselactlineaspedido,"CODDIV",svdpedido.coddiv,sizeof(svdpedido.coddiv),V10CADENA,
             "ANOPED",&svdpedido.anoped,sizeof(svdpedido.anoped),V10LONG,
             "CODPED",svdpedido.codped,sizeof(svdpedido.codped),V10CADENA,
             "SEQPED",&svdpedido.seqped,sizeof(svdpedido.seqped),V10LONG,
             "RET",&svdpedido.ret,sizeof(svdpedido.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PEDIDO);
        init = 1;
    }
}

diccionario *PEDIDOdamediccionario(void)
{
    return(&dpedido);
}

int PEDIDOselnuevaversion(char *coddiv,long anoped,char *codped,vdpedidos *pedido)
{
    int vdret;
    if (vdselnuevaversion==NULL) init_selnuevaversion();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.coddiv,coddiv);
    svdpedido.anoped=anoped;
    strcpy(svdpedido.codped,codped);
    vdret=ejefetchcursor(vdselnuevaversion);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PEDIDObuscanuevaversion vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDOprocfinpedido(char *coddiv,long anoped,char *codped,long seqped,long status,long estadospr,long estadosex,long ret,vdpedidos *pedido)
{
    int vdret;
    if (vdselfinpedido==NULL) init_selfinpedido();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.coddiv,coddiv);
    svdpedido.anoped=anoped;
    strcpy(svdpedido.codped,codped);
    svdpedido.seqped=seqped;
    svdpedido.status=status;
    svdpedido.estadospr=estadospr;
    svdpedido.estadosex=estadosex;
    svdpedido.ret=ret;
    vdret=ejecutacursor(vdselfinpedido);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PEDIDOprocfinpedido vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDOproccreaversion(char *coddiv,long anoped,char *codped,long seqped,char *comentario,long ret,vdpedidos *pedido)
{
    int vdret;
    if (vdselcreaversion==NULL) init_selcreaversion();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.coddiv,coddiv);
    svdpedido.anoped=anoped;
    strcpy(svdpedido.codped,codped);
    svdpedido.seqped=seqped;
    strcpy(svdpedido.comentario,comentario);
    svdpedido.ret=ret;
    vdret=ejecutacursor(vdselcreaversion);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PEDIDOproccreaversion vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDObuscastatusprio(long status,vdpedidos *pedido)
{
    int vdret;
    if (vdselstatusprio==NULL) init_selstatusprio();
    memset(&svdpedido,0,sizeof(svdpedido));
    svdpedido.status=status;
    vdret=ejefetchcursor(vdselstatusprio);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PEDIDObuscastatusprio vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDOnextstatusprio(vdpedidos *pedido)
{
    int vdret;
    vdret=fetchcursor(vdselstatusprio);
    if (!vdret) {
        *pedido=svdpedido;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstatusprio);
    return(VD_EERRORACLE);
}

int PEDIDOprocdisponibilidad(char *tarea,vdpedidos *pedido)
{
    int vdret;
    if (vdseldisponibilidad==NULL) init_seldisponibilidad();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.tarea,tarea);
    vdret=ejecutacursor(vdseldisponibilidad);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PEDIDOprocdisponibilidad vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDOprocliberamovpedido(char *coddemanda,long estadoini,long estadofin,long ret,vdpedidos *pedido)
{
    int vdret;
    if (vdselliberamovpedido==NULL) init_selliberamovpedido();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.coddemanda,coddemanda);
    svdpedido.estadoini=estadoini;
    svdpedido.estadofin=estadofin;
    svdpedido.ret=ret;
    vdret=ejecutacursor(vdselliberamovpedido);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PEDIDOprocliberamovpedido vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

int PEDIDOprocactlineaspedido(char *coddiv,long anoped,char *codped,long seqped,long ret,vdpedidos *pedido)
{
    int vdret;
    if (vdselactlineaspedido==NULL) init_selactlineaspedido();
    memset(&svdpedido,0,sizeof(svdpedido));
    strcpy(svdpedido.coddiv,coddiv);
    svdpedido.anoped=anoped;
    strcpy(svdpedido.codped,codped);
    svdpedido.seqped=seqped;
    svdpedido.ret=ret;
    vdret=ejecutacursor(vdselactlineaspedido);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PEDIDOprocactlineaspedido vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pedido=svdpedido;
    return(vdret);
}

char * PEDIDOdebug(vdpedidos *pedido)
{
    debugestruct(&dpedido,pedido,msgdebugpedido);
    return(msgdebugpedido);
}

