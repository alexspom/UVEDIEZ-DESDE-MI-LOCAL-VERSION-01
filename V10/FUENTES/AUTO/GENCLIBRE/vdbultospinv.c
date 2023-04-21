// Modulo generado automaticamente a partir de VDBULTOSPINV.DEF
//# M¢dulo : VDBUTLOSPINV.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDBULTOSPINV
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 21-01-2008                                           
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//NOMBRE=BUPINV;
//EXTRA=CANTIDAD,V10LONG;
//EXTRA=CODBULTOOUT,V10CADENA,18;
//EXTRA=CODCONCEAUX,V10CADENA,10;
//EXTRA=CODUBIREG,V10CADENA,12;
//EXTRA=RET,V10INT
//EXTRA=STBUCPREPARADO,V10LONG;
//EXTRA=STBPCFINALIZADO,V10LONG;
//EXTRA=ESFINPICKING,V10LONG;
//EXTRA=ESFINBULTO,V10LONG;
//EXTRA=ESFINBULTOPINVENZONA,V10LONG;
//EXTRA=ESFINBULTOPINV,V10LONG;
//EXTRA=ESBULTOPINVSINSTOCK,V10LONG;
//EXTRA=MIDIGEAN,V10CADENA,2;
//EXTRA=CODBULTOPINV,V10CADENA,18;
//EXTRA=CODBULTOPEXP,V10CADENA,18;
//EXTRA=PDTECAJA,V10LONG;
//EXTRA=MODOREGULARIZACION,V10LONG;
//EXTRA=CANTREGULARIZAR,V10LONG;
//EXTRA=OBSERV,V10CADENA,1024;
//EXTRA=UNIEMB,V10LONG;
//
//SELECT=PRIVILEGIO,SELECT VDUSER.TIENEPRIVILEGIO(:VDUSUARIO.CODOPE,NVL(:VDPRIVOPE.PRIVILEGIO,'PICKING')) TIENEPRIVILEGIO FROM DUAL;
//
//SELECT=DATOSOPE,SELECT COUNT(DISTINCT CODOPE) NUMOPE, COUNT(*) NUMBULTOSZONA, SUM(DECODE(CODOPE,:VDUSUARIO.CODOPE,1,0)) NUMBULTOSOPE
//                FROM VDBULTOZONA
//                WHERE CODZONA=:VDZONAS.CODZONA;
//
//SELECT=PDTESZONA,SELECT VDPICKINVLUCES.BULTOSPENDIENTEZONA(:VDINFODISP.IDINFOPICK, :VDBULTOCABPINV.CODMAT, :VDZONAS.CODZONA) NUMBULTOS FROM DUAL;
//
//SELECT=ZONASPDTES,SELECT VDPICKINVLUCES.DAMEZONASPDTESDEBULTO(:VDBULTOCAB.CODBULTO) ZONASPDTES FROM DUAL;
//
//SELECT=CANTDISPLAY,SELECT VDPICKINVLUCES.DAMECANTDISPLAY(:VDBULTOCAB.CODBULTO, :VDZONAS.CODZONA, :VDINFODISP.IDINFOPICK, :VDINFODISP.NUMDISP) CANTIDAD FROM DUAL;
//
//SELECT=CANTDISPLAYSERVIDA,SELECT VDPICKINVLUCES.DAMECANTDISPLAYSERVIDA(:VDBULTOCAB.CODBULTO, :VDZONAS.CODZONA, :VDINFODISP.IDINFOPICK, :VDINFODISP.NUMDISP) CANTIDAD FROM DUAL;
//
//SELECT=STOCKBULTO,SELECT VDPICKINVLUCES.DAMESTOCKBULTO(:VDBULTOCAB.CODBULTO) CANTIDAD FROM DUAL;
//
//SELECT=TIPOCAJA, BEGIN VDPICKINVLUCES.DAMETIPOCAJABULTO(:VDBULTOCAB.CODBULTO,:VDCAJAS.TIPOCAJA); END;@
//
//PROCEDURE=EJECUTAMOVPINV,BEGIN  
//                           VDPICKINVLUCES.EJECUTAMOVPINV(:VDMOVIM.TAREA, :VDMOVIM.STATUS,
//                                                           :VDBULTOCABPINV.CODBULTO,
//                                                           :VDZONAS.CODZONA, :VDINFODISP.IDINFOPICK, :VDINFODISP.NUMDISP, 
//                                                           :STBUCPREPARADO, :STBPCFINALIZADO,:MODOREGULARIZACION, :MIDIGEAN, :RET);
//                         END;@
//
//PROCEDURE=DAMEESTADOBULTOPINV,BEGIN 
//                             VDPICKINVLUCES.DAMEESTADOBULTOPINV(:CODBULTOPINV, :VDINFODISP.IDINFOPICK, :VDINFODISP.NUMDISP, :VDBULTOCAB.CODBULTO, :ESFINBULTO, :ESFINPICKING, :ESFINBULTOPINVENZONA, :ESFINBULTOPINV, :ESBULTOPINVSINSTOCK, :RET);
//                         END;@
//
//PROCEDURE=CAMBIACAJA,BEGIN VDPICKINVLUCES.CAMBIACAJA(:VDZONAS.CODZONA,:VDBULTOCABPINV.CODBULTO, :VDBULTOCABPINV.CODMAT, :VDMOVIM.TAREA, :VDMOVIM.CODCONCE, :RET);END;@
//
//PROCEDURE=ACTPLANIFMOV,BEGIN VDPICKINVLUCES.ACTPLANIFMOVIM(:VDBULTOCABPINV.CODBULTO, :VDZONAS.CODZONA, :VDINFODISP.IDINFOPICK, :VDINFODISP.NUMDISP, :RET);END;@ 
//
//CURSOR=DISPAENCENDERENZONA,SELECT IDI.CODZONA, IDI.IDINFOPICK, IDI.NUMDISP, BC.CODBULTO CODBULTOEXP,  BCP.CODBULTO CODBULTOPINV, DECODE(BC.STATUS,VDST.FBUCPDTEETIQ,1,0) PDTECAJA
//                FROM VDBULTOCABPINV BCP,
//                     VDBULTOLINPINV BLP,
//                     VDMOVIM MOV,
//                     VDBULTOLIN BL,
//                     VDBULTOCAB BC,
//                     VDINFODISP IDI
//                WHERE BCP.CODBULTO = :VDBULTOCAB.CODBULTO AND
//                      BCP.CODBULTO = BLP.CODBULTO AND
//                      BCP.STATUS = VDST.FBPCODS AND 
//                      BLP.STATUS = VDST.FBPLASERVIR AND 
//                      BLP.CODMOV = MOV.CODMOV AND
//                      MOV.STATUS = VDST.FMOVPDTERECOGE AND
//                      BLP.CODMOV = BL.CODMOV AND
//                      BL.CODBULTO = BC.CODBULTO AND
//                      BC.STATUS IN (VDST.FBUCPDTEETIQ, VDST.FBUCETIQUNI) AND
//                      BL.STATUS = VDST.FBULASERVIR AND
//                      IDI.CODZONA = :VDZONAS.CODZONA AND
//                      IDI.IDINFOPICK = BC.IDINFOPICK AND
//                      IDI.NUMDISP = BC.NUMDISP 
//               ORDER BY IDI.ORDENDISP;
//
//# DISPLAYS EN LOS QUE A SUS BULTOS ACTUALES SE HA SERVIDO ALGO EN ESA ZONA DE ESE BULTO DE PICKING INVERSO               
//CURSOR=DIPSSERVIDOSENZONA, SELECT IDI.CODZONA, IDI.IDINFOPICK, IDI.NUMDISP
//                      FROM VDMOVIM MOV,
//                           VDBULTOLIN BL,
//                           VDBULTOCAB BC,
//                           VDINFODISP IDI,
//                           VDBULTOLINPINV BLP,
//                           VDBULTOCABPINV BCP
//                      WHERE BCP.CODBULTO = :VDBULTOCABPINV.CODBULTO AND
//                            BCP.CODBULTO = BLP.CODBULTO AND
//                            BLP.CODMOV||'' = MOV.CODMOV AND
//                            BLP.CANTSERVIDA = BLP.CANTPEDIDA AND 
//                            BLP.STATUS = VDST.FBPLPROCESADA AND
//                            BLP.CODMOV = BL.CODMOV AND
//                            MOV.STATUS >= VDST.FMOVACTUALIZA AND                             
//                            BL.CODBULTO = BC.CODBULTO AND
//                            BL.STATUS = VDST.FBULSERVIDA AND
//                            IDI.CODZONA = :VDZONAS.CODZONA AND
//                            IDI.IDINFOPICK = BC.IDINFOPICK AND
//                            IDI.NUMDISP    = BC.NUMDISP  AND
//                            BC.STATUS < VDST.FBUCPREPARADO
//                      ORDER BY IDI.ORDENDISP; 
//
//CURSOR=REGULARIZARESTOSPINV,BEGIN
//                              VDPICKINVLUCES.REGULARIZARESTOSPINV (:VDZONAS.CODZONA,:VDBULTOCABPINV.CODMAT, :CANTREGULARIZAR,:VDMOVIM.CODCONCE,:VDUBICA.CODUBI,:OBSERV,:VDMOVIM.CODMOV,:RET); 
//                            END;@
//
//CURSOR=BULTOPINVPDTESERVIR,SELECT COUNT(*) RET FROM VDBULTOLINPINV BLP 
//                               WHERE BLP.CODBULTO = :VDBULTOCABPINV.CODBULTO AND
//                                     BLP.STATUS   = VDST.FBPLASERVIR;
//
//CURSOR=UNIEMBBULTOPINV, SELECT (STK.UNIEMB * DECODE(ART.CAJACUBETA,0,1,ART.CAJACUBETA)) UNIEMB FROM VDSTOCK STK, VDARTIC ART, VDBULTOCABPINV BPC WHERE BPC.CODBULTO=:VDBULTOCABPINV.CODBULTO AND BPC.CODMAT=STK.CODMAT AND ART.CODART = STK.CODART AND ROWNUM=1;

#include "vd.h"\

#define SELPRIVILEGIO "SELECT VDUSER.TIENEPRIVILEGIO(:CODOPE,NVL(:PRIVILEGIO,'PICKING')) TIENEPRIVILEGIO FROM DUAL"
static v10cursors *vdselprivilegio;
#define SELDATOSOPE "SELECT COUNT(DISTINCT CODOPE) NUMOPE, COUNT(*) NUMBULTOSZONA, SUM(DECODE(CODOPE,:CODOPE,1,0)) NUMBULTOSOPE FROM VDBULTOZONA WHERE CODZONA=:CODZONA"
static v10cursors *vdseldatosope;
#define SELPDTESZONA "SELECT VDPICKINVLUCES.BULTOSPENDIENTEZONA(:IDINFOPICK, :CODMAT, :CODZONA) NUMBULTOS FROM DUAL"
static v10cursors *vdselpdteszona;
#define SELZONASPDTES "SELECT VDPICKINVLUCES.DAMEZONASPDTESDEBULTO(:CODBULTO) ZONASPDTES FROM DUAL"
static v10cursors *vdselzonaspdtes;
#define SELCANTDISPLAY "SELECT VDPICKINVLUCES.DAMECANTDISPLAY(:CODBULTO, :CODZONA, :IDINFOPICK, :NUMDISP) CANTIDAD FROM DUAL"
static v10cursors *vdselcantdisplay;
#define SELCANTDISPLAYSERVIDA "SELECT VDPICKINVLUCES.DAMECANTDISPLAYSERVIDA(:CODBULTO, :CODZONA, :IDINFOPICK, :NUMDISP) CANTIDAD FROM DUAL"
static v10cursors *vdselcantdisplayservida;
#define SELSTOCKBULTO "SELECT VDPICKINVLUCES.DAMESTOCKBULTO(:CODBULTO) CANTIDAD FROM DUAL"
static v10cursors *vdselstockbulto;
#define SELTIPOCAJA " BEGIN VDPICKINVLUCES.DAMETIPOCAJABULTO(:CODBULTO,:TIPOCAJA); END;"
static v10cursors *vdseltipocaja;
#define SELEJECUTAMOVPINV "BEGIN   VDPICKINVLUCES.EJECUTAMOVPINV(:TAREA, :STATUS, :CODBULTO, :CODZONA, :IDINFOPICK, :NUMDISP,  :STBUCPREPARADO, :STBPCFINALIZADO,:MODOREGULARIZACION, :MIDIGEAN, :RET); END;"
static v10cursors *vdselejecutamovpinv;
#define SELDAMEESTADOBULTOPINV "BEGIN  VDPICKINVLUCES.DAMEESTADOBULTOPINV(:CODBULTOPINV, :IDINFOPICK, :NUMDISP, :CODBULTO, :ESFINBULTO, :ESFINPICKING, :ESFINBULTOPINVENZONA, :ESFINBULTOPINV, :ESBULTOPINVSINSTOCK, :RET); END;"
static v10cursors *vdseldameestadobultopinv;
#define SELCAMBIACAJA "BEGIN VDPICKINVLUCES.CAMBIACAJA(:CODZONA,:CODBULTO, :CODMAT, :TAREA, :CODCONCE, :RET);END;"
static v10cursors *vdselcambiacaja;
#define SELACTPLANIFMOV "BEGIN VDPICKINVLUCES.ACTPLANIFMOVIM(:CODBULTO, :CODZONA, :IDINFOPICK, :NUMDISP, :RET);END;"
static v10cursors *vdselactplanifmov;
#define SELDISPAENCENDERENZONA "SELECT IDI.CODZONA, IDI.IDINFOPICK, IDI.NUMDISP, BC.CODBULTO CODBULTOEXP,  BCP.CODBULTO CODBULTOPINV, DECODE(BC.STATUS,VDST.FBUCPDTEETIQ,1,0) PDTECAJA FROM VDBULTOCABPINV BCP, VDBULTOLINPINV BLP, VDMOVIM MOV, VDBULTOLIN BL, VDBULTOCAB BC, VDINFODISP IDI WHERE BCP.CODBULTO = :CODBULTO AND BCP.CODBULTO = BLP.CODBULTO AND BCP.STATUS = VDST.FBPCODS AND  BLP.STATUS = VDST.FBPLASERVIR AND  BLP.CODMOV = MOV.CODMOV AND MOV.STATUS = VDST.FMOVPDTERECOGE AND BLP.CODMOV = BL.CODMOV AND BL.CODBULTO = BC.CODBULTO AND BC.STATUS IN (VDST.FBUCPDTEETIQ, VDST.FBUCETIQUNI) AND BL.STATUS = VDST.FBULASERVIR AND IDI.CODZONA = :CODZONA AND IDI.IDINFOPICK = BC.IDINFOPICK AND IDI.NUMDISP = BC.NUMDISP  ORDER BY IDI.ORDENDISP"
static v10cursors *vdseldispaencenderenzona;
#define SELDIPSSERVIDOSENZONA " SELECT IDI.CODZONA, IDI.IDINFOPICK, IDI.NUMDISP FROM VDMOVIM MOV, VDBULTOLIN BL, VDBULTOCAB BC, VDINFODISP IDI, VDBULTOLINPINV BLP, VDBULTOCABPINV BCP WHERE BCP.CODBULTO = :CODBULTO AND BCP.CODBULTO = BLP.CODBULTO AND BLP.CODMOV||'' = MOV.CODMOV AND BLP.CANTSERVIDA = BLP.CANTPEDIDA AND  BLP.STATUS = VDST.FBPLPROCESADA AND BLP.CODMOV = BL.CODMOV AND MOV.STATUS >= VDST.FMOVACTUALIZA AND                              BL.CODBULTO = BC.CODBULTO AND BL.STATUS = VDST.FBULSERVIDA AND IDI.CODZONA = :CODZONA AND IDI.IDINFOPICK = BC.IDINFOPICK AND IDI.NUMDISP    = BC.NUMDISP  AND BC.STATUS < VDST.FBUCPREPARADO ORDER BY IDI.ORDENDISP"
static v10cursors *vdseldipsservidosenzona;
#define SELREGULARIZARESTOSPINV "BEGIN VDPICKINVLUCES.REGULARIZARESTOSPINV (:CODZONA,:CODMAT, :CANTREGULARIZAR,:CODCONCE,:CODUBI,:OBSERV,:CODMOV,:RET);  END;"
static v10cursors *vdselregularizarestospinv;
#define SELBULTOPINVPDTESERVIR "SELECT COUNT(*) RET FROM VDBULTOLINPINV BLP  WHERE BLP.CODBULTO = :CODBULTO AND BLP.STATUS   = VDST.FBPLASERVIR"
static v10cursors *vdselbultopinvpdteservir;
#define SELUNIEMBBULTOPINV " SELECT (STK.UNIEMB * DECODE(ART.CAJACUBETA,0,1,ART.CAJACUBETA)) UNIEMB FROM VDSTOCK STK, VDARTIC ART, VDBULTOCABPINV BPC WHERE BPC.CODBULTO=:CODBULTO AND BPC.CODMAT=STK.CODMAT AND ART.CODART = STK.CODART AND ROWNUM=1"
static v10cursors *vdseluniembbultopinv;

static vdbupinvs svdbupinv;

static diccols colvdbupinv[]={ 
    {"CANTIDAD",V10LONG,(int)&svdbupinv.cantidad,sizeof(svdbupinv.cantidad)},
    {"CODBULTOOUT",V10CADENA,(int)&svdbupinv.codbultoout,sizeof(svdbupinv.codbultoout)},
    {"CODCONCEAUX",V10CADENA,(int)&svdbupinv.codconceaux,sizeof(svdbupinv.codconceaux)},
    {"CODUBIREG",V10CADENA,(int)&svdbupinv.codubireg,sizeof(svdbupinv.codubireg)},
    {"RET",V10LONG,(int)&svdbupinv.ret,sizeof(svdbupinv.ret)},
    {"STBUCPREPARADO",V10LONG,(int)&svdbupinv.stbucpreparado,sizeof(svdbupinv.stbucpreparado)},
    {"STBPCFINALIZADO",V10LONG,(int)&svdbupinv.stbpcfinalizado,sizeof(svdbupinv.stbpcfinalizado)},
    {"ESFINPICKING",V10LONG,(int)&svdbupinv.esfinpicking,sizeof(svdbupinv.esfinpicking)},
    {"ESFINBULTO",V10LONG,(int)&svdbupinv.esfinbulto,sizeof(svdbupinv.esfinbulto)},
    {"ESFINBULTOPINVENZONA",V10LONG,(int)&svdbupinv.esfinbultopinvenzona,sizeof(svdbupinv.esfinbultopinvenzona)},
    {"ESFINBULTOPINV",V10LONG,(int)&svdbupinv.esfinbultopinv,sizeof(svdbupinv.esfinbultopinv)},
    {"ESBULTOPINVSINSTOCK",V10LONG,(int)&svdbupinv.esbultopinvsinstock,sizeof(svdbupinv.esbultopinvsinstock)},
    {"MIDIGEAN",V10CADENA,(int)&svdbupinv.midigean,sizeof(svdbupinv.midigean)},
    {"CODBULTOPINV",V10CADENA,(int)&svdbupinv.codbultopinv,sizeof(svdbupinv.codbultopinv)},
    {"CODBULTOPEXP",V10CADENA,(int)&svdbupinv.codbultopexp,sizeof(svdbupinv.codbultopexp)},
    {"PDTECAJA",V10LONG,(int)&svdbupinv.pdtecaja,sizeof(svdbupinv.pdtecaja)},
    {"MODOREGULARIZACION",V10LONG,(int)&svdbupinv.modoregularizacion,sizeof(svdbupinv.modoregularizacion)},
    {"CANTREGULARIZAR",V10LONG,(int)&svdbupinv.cantregularizar,sizeof(svdbupinv.cantregularizar)},
    {"OBSERV",V10CADENA,(int)&svdbupinv.observ,sizeof(svdbupinv.observ)},
    {"UNIEMB",V10LONG,(int)&svdbupinv.uniemb,sizeof(svdbupinv.uniemb)},
    {"TIENEPRIVILEGIO",V10LONG,(int)&svdbupinv.tieneprivilegio,sizeof(svdbupinv.tieneprivilegio)},
    {"CODOPE",V10CADENA,(int)&svdbupinv.codope,sizeof(svdbupinv.codope)},
    {"PRIVILEGIO",V10CADENA,(int)&svdbupinv.privilegio,sizeof(svdbupinv.privilegio)},
    {"NUMOPE",V10LONG,(int)&svdbupinv.numope,sizeof(svdbupinv.numope)},
    {"NUMBULTOSZONA",V10LONG,(int)&svdbupinv.numbultoszona,sizeof(svdbupinv.numbultoszona)},
    {"NUMBULTOSOPE",V10LONG,(int)&svdbupinv.numbultosope,sizeof(svdbupinv.numbultosope)},
    {"CODZONA",V10LONG,(int)&svdbupinv.codzona,sizeof(svdbupinv.codzona)},
    {"NUMBULTOS",V10LONG,(int)&svdbupinv.numbultos,sizeof(svdbupinv.numbultos)},
    {"IDINFOPICK",V10LONG,(int)&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick)},
    {"CODMAT",V10CADENA,(int)&svdbupinv.codmat,sizeof(svdbupinv.codmat)},
    {"ZONASPDTES",V10CADENA,(int)&svdbupinv.zonaspdtes,sizeof(svdbupinv.zonaspdtes)},
    {"CODBULTO",V10CADENA,(int)&svdbupinv.codbulto,sizeof(svdbupinv.codbulto)},
    {"NUMDISP",V10LONG,(int)&svdbupinv.numdisp,sizeof(svdbupinv.numdisp)},
    {"TIPOCAJA",V10CADENA,(int)&svdbupinv.tipocaja,sizeof(svdbupinv.tipocaja)},
    {"TAREA",V10CADENA,(int)&svdbupinv.tarea,sizeof(svdbupinv.tarea)},
    {"STATUS",V10LONG,(int)&svdbupinv.status,sizeof(svdbupinv.status)},
    {"CODCONCE",V10CADENA,(int)&svdbupinv.codconce,sizeof(svdbupinv.codconce)},
    {"CODBULTOEXP",V10CADENA,(int)&svdbupinv.codbultoexp,sizeof(svdbupinv.codbultoexp)},
    {"CODUBI",V10CADENA,(int)&svdbupinv.codubi,sizeof(svdbupinv.codubi)},
    {"CODMOV",V10LONG,(int)&svdbupinv.codmov,sizeof(svdbupinv.codmov)}
    };

static diccionarios dvdbupinv[]={
    {colvdbupinv,40}
    };

diccionario dbupinv={dvdbupinv,1};

static char msgdebugbupinv[LCADENABIG];

static int init=0;


static void fin_vd_BUPINV(void)
{
    if(vdselprivilegio){
        liberacursor(vdselprivilegio);
        vdselprivilegio=NULL;
    }
    if(vdseldatosope){
        liberacursor(vdseldatosope);
        vdseldatosope=NULL;
    }
    if(vdselpdteszona){
        liberacursor(vdselpdteszona);
        vdselpdteszona=NULL;
    }
    if(vdselzonaspdtes){
        liberacursor(vdselzonaspdtes);
        vdselzonaspdtes=NULL;
    }
    if(vdselcantdisplay){
        liberacursor(vdselcantdisplay);
        vdselcantdisplay=NULL;
    }
    if(vdselcantdisplayservida){
        liberacursor(vdselcantdisplayservida);
        vdselcantdisplayservida=NULL;
    }
    if(vdselstockbulto){
        liberacursor(vdselstockbulto);
        vdselstockbulto=NULL;
    }
    if(vdseltipocaja){
        liberacursor(vdseltipocaja);
        vdseltipocaja=NULL;
    }
    if(vdselejecutamovpinv){
        liberacursor(vdselejecutamovpinv);
        vdselejecutamovpinv=NULL;
    }
    if(vdseldameestadobultopinv){
        liberacursor(vdseldameestadobultopinv);
        vdseldameestadobultopinv=NULL;
    }
    if(vdselcambiacaja){
        liberacursor(vdselcambiacaja);
        vdselcambiacaja=NULL;
    }
    if(vdselactplanifmov){
        liberacursor(vdselactplanifmov);
        vdselactplanifmov=NULL;
    }
    if(vdseldispaencenderenzona){
        liberacursor(vdseldispaencenderenzona);
        vdseldispaencenderenzona=NULL;
    }
    if(vdseldipsservidosenzona){
        liberacursor(vdseldipsservidosenzona);
        vdseldipsservidosenzona=NULL;
    }
    if(vdselregularizarestospinv){
        liberacursor(vdselregularizarestospinv);
        vdselregularizarestospinv=NULL;
    }
    if(vdselbultopinvpdteservir){
        liberacursor(vdselbultopinvpdteservir);
        vdselbultopinvpdteservir=NULL;
    }
    if(vdseluniembbultopinv){
        liberacursor(vdseluniembbultopinv);
        vdseluniembbultopinv=NULL;
    }
}


static void init_selprivilegio(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselprivilegio=abrecursor(SELPRIVILEGIO);
    definetodo(vdselprivilegio,&svdbupinv.tieneprivilegio,sizeof(svdbupinv.tieneprivilegio),V10LONG,
               NULL);
    bindtodo(vdselprivilegio,"CODOPE",svdbupinv.codope,sizeof(svdbupinv.codope),V10CADENA,
             "PRIVILEGIO",svdbupinv.privilegio,sizeof(svdbupinv.privilegio),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seldatosope(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseldatosope=abrecursor(SELDATOSOPE);
    definetodo(vdseldatosope,&svdbupinv.numope,sizeof(svdbupinv.numope),V10LONG,
               &svdbupinv.numbultoszona,sizeof(svdbupinv.numbultoszona),V10LONG,
               &svdbupinv.numbultosope,sizeof(svdbupinv.numbultosope),V10LONG,
               NULL);
    bindtodo(vdseldatosope,"CODOPE",svdbupinv.codope,sizeof(svdbupinv.codope),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selpdteszona(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselpdteszona=abrecursor(SELPDTESZONA);
    definetodo(vdselpdteszona,&svdbupinv.numbultos,sizeof(svdbupinv.numbultos),V10LONG,
               NULL);
    bindtodo(vdselpdteszona,"IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "CODMAT",svdbupinv.codmat,sizeof(svdbupinv.codmat),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selzonaspdtes(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselzonaspdtes=abrecursor(SELZONASPDTES);
    definetodo(vdselzonaspdtes,svdbupinv.zonaspdtes,sizeof(svdbupinv.zonaspdtes),V10CADENA,
               NULL);
    bindtodo(vdselzonaspdtes,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selcantdisplay(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselcantdisplay=abrecursor(SELCANTDISPLAY);
    definetodo(vdselcantdisplay,&svdbupinv.cantidad,sizeof(svdbupinv.cantidad),V10LONG,
               NULL);
    bindtodo(vdselcantdisplay,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "NUMDISP",&svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selcantdisplayservida(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselcantdisplayservida=abrecursor(SELCANTDISPLAYSERVIDA);
    definetodo(vdselcantdisplayservida,&svdbupinv.cantidad,sizeof(svdbupinv.cantidad),V10LONG,
               NULL);
    bindtodo(vdselcantdisplayservida,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "NUMDISP",&svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selstockbulto(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselstockbulto=abrecursor(SELSTOCKBULTO);
    definetodo(vdselstockbulto,&svdbupinv.cantidad,sizeof(svdbupinv.cantidad),V10LONG,
               NULL);
    bindtodo(vdselstockbulto,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seltipocaja(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseltipocaja=abrecursor(SELTIPOCAJA);
    definetodo(vdseltipocaja,NULL);
    bindtodo(vdseltipocaja,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "TIPOCAJA",svdbupinv.tipocaja,sizeof(svdbupinv.tipocaja),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selejecutamovpinv(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselejecutamovpinv=abrecursor(SELEJECUTAMOVPINV);
    definetodo(vdselejecutamovpinv,NULL);
    bindtodo(vdselejecutamovpinv,"TAREA",svdbupinv.tarea,sizeof(svdbupinv.tarea),V10CADENA,
             "STATUS",&svdbupinv.status,sizeof(svdbupinv.status),V10LONG,
             "CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "NUMDISP",&svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
             "STBUCPREPARADO",&svdbupinv.stbucpreparado,sizeof(svdbupinv.stbucpreparado),V10LONG,
             "STBPCFINALIZADO",&svdbupinv.stbpcfinalizado,sizeof(svdbupinv.stbpcfinalizado),V10LONG,
             "MODOREGULARIZACION",&svdbupinv.modoregularizacion,sizeof(svdbupinv.modoregularizacion),V10LONG,
             "MIDIGEAN",svdbupinv.midigean,sizeof(svdbupinv.midigean),V10CADENA,
             "RET",&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seldameestadobultopinv(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseldameestadobultopinv=abrecursor(SELDAMEESTADOBULTOPINV);
    definetodo(vdseldameestadobultopinv,NULL);
    bindtodo(vdseldameestadobultopinv,"CODBULTOPINV",svdbupinv.codbultopinv,sizeof(svdbupinv.codbultopinv),V10CADENA,
             "IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "NUMDISP",&svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
             "CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "ESFINBULTO",&svdbupinv.esfinbulto,sizeof(svdbupinv.esfinbulto),V10LONG,
             "ESFINPICKING",&svdbupinv.esfinpicking,sizeof(svdbupinv.esfinpicking),V10LONG,
             "ESFINBULTOPINVENZONA",&svdbupinv.esfinbultopinvenzona,sizeof(svdbupinv.esfinbultopinvenzona),V10LONG,
             "ESFINBULTOPINV",&svdbupinv.esfinbultopinv,sizeof(svdbupinv.esfinbultopinv),V10LONG,
             "ESBULTOPINVSINSTOCK",&svdbupinv.esbultopinvsinstock,sizeof(svdbupinv.esbultopinvsinstock),V10LONG,
             "RET",&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selcambiacaja(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselcambiacaja=abrecursor(SELCAMBIACAJA);
    definetodo(vdselcambiacaja,NULL);
    bindtodo(vdselcambiacaja,"CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODMAT",svdbupinv.codmat,sizeof(svdbupinv.codmat),V10CADENA,
             "TAREA",svdbupinv.tarea,sizeof(svdbupinv.tarea),V10CADENA,
             "CODCONCE",svdbupinv.codconce,sizeof(svdbupinv.codconce),V10CADENA,
             "RET",&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selactplanifmov(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselactplanifmov=abrecursor(SELACTPLANIFMOV);
    definetodo(vdselactplanifmov,NULL);
    bindtodo(vdselactplanifmov,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "IDINFOPICK",&svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
             "NUMDISP",&svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
             "RET",&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seldispaencenderenzona(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseldispaencenderenzona=abrecursor(SELDISPAENCENDERENZONA);
    definetodo(vdseldispaencenderenzona,&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
               &svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
               &svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
               svdbupinv.codbultoexp,sizeof(svdbupinv.codbultoexp),V10CADENA,
               svdbupinv.codbultopinv,sizeof(svdbupinv.codbultopinv),V10CADENA,
               &svdbupinv.pdtecaja,sizeof(svdbupinv.pdtecaja),V10LONG,
               NULL);
    bindtodo(vdseldispaencenderenzona,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seldipsservidosenzona(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseldipsservidosenzona=abrecursor(SELDIPSSERVIDOSENZONA);
    definetodo(vdseldipsservidosenzona,&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
               &svdbupinv.idinfopick,sizeof(svdbupinv.idinfopick),V10LONG,
               &svdbupinv.numdisp,sizeof(svdbupinv.numdisp),V10LONG,
               NULL);
    bindtodo(vdseldipsservidosenzona,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             "CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selregularizarestospinv(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselregularizarestospinv=abrecursor(SELREGULARIZARESTOSPINV);
    definetodo(vdselregularizarestospinv,NULL);
    bindtodo(vdselregularizarestospinv,"CODZONA",&svdbupinv.codzona,sizeof(svdbupinv.codzona),V10LONG,
             "CODMAT",svdbupinv.codmat,sizeof(svdbupinv.codmat),V10CADENA,
             "CANTREGULARIZAR",&svdbupinv.cantregularizar,sizeof(svdbupinv.cantregularizar),V10LONG,
             "CODCONCE",svdbupinv.codconce,sizeof(svdbupinv.codconce),V10CADENA,
             "CODUBI",svdbupinv.codubi,sizeof(svdbupinv.codubi),V10CADENA,
             "OBSERV",svdbupinv.observ,sizeof(svdbupinv.observ),V10CADENA,
             "CODMOV",&svdbupinv.codmov,sizeof(svdbupinv.codmov),V10LONG,
             "RET",&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_selbultopinvpdteservir(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdselbultopinvpdteservir=abrecursor(SELBULTOPINVPDTESERVIR);
    definetodo(vdselbultopinvpdteservir,&svdbupinv.ret,sizeof(svdbupinv.ret),V10LONG,
               NULL);
    bindtodo(vdselbultopinvpdteservir,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

static void init_seluniembbultopinv(void)
{
    int nc;

    for(nc=0;nc<dvdbupinv[0].numcol;nc++) dvdbupinv[0].c[nc].offset-=(int)&svdbupinv;

    vdseluniembbultopinv=abrecursor(SELUNIEMBBULTOPINV);
    definetodo(vdseluniembbultopinv,&svdbupinv.uniemb,sizeof(svdbupinv.uniemb),V10LONG,
               NULL);
    bindtodo(vdseluniembbultopinv,"CODBULTO",svdbupinv.codbulto,sizeof(svdbupinv.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BUPINV);
        init = 1;
    }
}

diccionario *BUPINVdamediccionario(void)
{
    return(&dbupinv);
}

int BUPINVselprivilegio(char *codope,char *privilegio,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselprivilegio==NULL) init_selprivilegio();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codope,codope);
    strcpy(svdbupinv.privilegio,privilegio);
    vdret=ejefetchcursor(vdselprivilegio);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscaprivilegio vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVseldatosope(char *codope,long codzona,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseldatosope==NULL) init_seldatosope();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codope,codope);
    svdbupinv.codzona=codzona;
    vdret=ejefetchcursor(vdseldatosope);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscadatosope vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVselpdteszona(long idinfopick,char *codmat,long codzona,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselpdteszona==NULL) init_selpdteszona();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    svdbupinv.idinfopick=idinfopick;
    strcpy(svdbupinv.codmat,codmat);
    svdbupinv.codzona=codzona;
    vdret=ejefetchcursor(vdselpdteszona);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscapdteszona vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVselzonaspdtes(char *codbulto,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselzonaspdtes==NULL) init_selzonaspdtes();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    vdret=ejefetchcursor(vdselzonaspdtes);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscazonaspdtes vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVselcantdisplay(char *codbulto,long codzona,long idinfopick,long numdisp,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselcantdisplay==NULL) init_selcantdisplay();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    svdbupinv.idinfopick=idinfopick;
    svdbupinv.numdisp=numdisp;
    vdret=ejefetchcursor(vdselcantdisplay);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscacantdisplay vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVselcantdisplayservida(char *codbulto,long codzona,long idinfopick,long numdisp,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselcantdisplayservida==NULL) init_selcantdisplayservida();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    svdbupinv.idinfopick=idinfopick;
    svdbupinv.numdisp=numdisp;
    vdret=ejefetchcursor(vdselcantdisplayservida);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscacantdisplayservida vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVselstockbulto(char *codbulto,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselstockbulto==NULL) init_selstockbulto();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    vdret=ejefetchcursor(vdselstockbulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscastockbulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVseltipocaja(char *codbulto,char *tipocaja,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseltipocaja==NULL) init_seltipocaja();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    strcpy(svdbupinv.tipocaja,tipocaja);
    vdret=ejefetchcursor(vdseltipocaja);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscatipocaja vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVprocejecutamovpinv(char *tarea,long status,char *codbulto,long codzona,long idinfopick,long numdisp,long stbucpreparado,long stbpcfinalizado,long modoregularizacion,char *midigean,long ret,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselejecutamovpinv==NULL) init_selejecutamovpinv();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.tarea,tarea);
    svdbupinv.status=status;
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    svdbupinv.idinfopick=idinfopick;
    svdbupinv.numdisp=numdisp;
    svdbupinv.stbucpreparado=stbucpreparado;
    svdbupinv.stbpcfinalizado=stbpcfinalizado;
    svdbupinv.modoregularizacion=modoregularizacion;
    strcpy(svdbupinv.midigean,midigean);
    svdbupinv.ret=ret;
    vdret=ejecutacursor(vdselejecutamovpinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BUPINVprocejecutamovpinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVprocdameestadobultopinv(char *codbultopinv,long idinfopick,long numdisp,char *codbulto,long esfinbulto,long esfinpicking,long esfinbultopinvenzona,long esfinbultopinv,long esbultopinvsinstock,long ret,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseldameestadobultopinv==NULL) init_seldameestadobultopinv();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbultopinv,codbultopinv);
    svdbupinv.idinfopick=idinfopick;
    svdbupinv.numdisp=numdisp;
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.esfinbulto=esfinbulto;
    svdbupinv.esfinpicking=esfinpicking;
    svdbupinv.esfinbultopinvenzona=esfinbultopinvenzona;
    svdbupinv.esfinbultopinv=esfinbultopinv;
    svdbupinv.esbultopinvsinstock=esbultopinvsinstock;
    svdbupinv.ret=ret;
    vdret=ejecutacursor(vdseldameestadobultopinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BUPINVprocdameestadobultopinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVproccambiacaja(long codzona,char *codbulto,char *codmat,char *tarea,char *codconce,long ret,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselcambiacaja==NULL) init_selcambiacaja();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    svdbupinv.codzona=codzona;
    strcpy(svdbupinv.codbulto,codbulto);
    strcpy(svdbupinv.codmat,codmat);
    strcpy(svdbupinv.tarea,tarea);
    strcpy(svdbupinv.codconce,codconce);
    svdbupinv.ret=ret;
    vdret=ejecutacursor(vdselcambiacaja);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BUPINVproccambiacaja vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVprocactplanifmov(char *codbulto,long codzona,long idinfopick,long numdisp,long ret,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselactplanifmov==NULL) init_selactplanifmov();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    svdbupinv.idinfopick=idinfopick;
    svdbupinv.numdisp=numdisp;
    svdbupinv.ret=ret;
    vdret=ejecutacursor(vdselactplanifmov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BUPINVprocactplanifmov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVbuscadispaencenderenzona(char *codbulto,long codzona,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseldispaencenderenzona==NULL) init_seldispaencenderenzona();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    vdret=ejefetchcursor(vdseldispaencenderenzona);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscadispaencenderenzona vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVnextdispaencenderenzona(vdbupinvs *bupinv)
{
    int vdret;
    vdret=fetchcursor(vdseldispaencenderenzona);
    if (!vdret) {
        *bupinv=svdbupinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldispaencenderenzona);
    return(VD_EERRORACLE);
}

int BUPINVbuscadipsservidosenzona(char *codbulto,long codzona,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseldipsservidosenzona==NULL) init_seldipsservidosenzona();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    svdbupinv.codzona=codzona;
    vdret=ejefetchcursor(vdseldipsservidosenzona);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscadipsservidosenzona vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVnextdipsservidosenzona(vdbupinvs *bupinv)
{
    int vdret;
    vdret=fetchcursor(vdseldipsservidosenzona);
    if (!vdret) {
        *bupinv=svdbupinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldipsservidosenzona);
    return(VD_EERRORACLE);
}

int BUPINVbuscaregularizarestospinv(long codzona,char *codmat,long cantregularizar,char *codconce,char *codubi,char *observ,long codmov,long ret,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselregularizarestospinv==NULL) init_selregularizarestospinv();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    svdbupinv.codzona=codzona;
    strcpy(svdbupinv.codmat,codmat);
    svdbupinv.cantregularizar=cantregularizar;
    strcpy(svdbupinv.codconce,codconce);
    strcpy(svdbupinv.codubi,codubi);
    strcpy(svdbupinv.observ,observ);
    svdbupinv.codmov=codmov;
    svdbupinv.ret=ret;
    vdret=ejefetchcursor(vdselregularizarestospinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscaregularizarestospinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVnextregularizarestospinv(vdbupinvs *bupinv)
{
    int vdret;
    vdret=fetchcursor(vdselregularizarestospinv);
    if (!vdret) {
        *bupinv=svdbupinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselregularizarestospinv);
    return(VD_EERRORACLE);
}

int BUPINVbuscabultopinvpdteservir(char *codbulto,vdbupinvs *bupinv)
{
    int vdret;
    if (vdselbultopinvpdteservir==NULL) init_selbultopinvpdteservir();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    vdret=ejefetchcursor(vdselbultopinvpdteservir);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscabultopinvpdteservir vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVnextbultopinvpdteservir(vdbupinvs *bupinv)
{
    int vdret;
    vdret=fetchcursor(vdselbultopinvpdteservir);
    if (!vdret) {
        *bupinv=svdbupinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselbultopinvpdteservir);
    return(VD_EERRORACLE);
}

int BUPINVbuscauniembbultopinv(char *codbulto,vdbupinvs *bupinv)
{
    int vdret;
    if (vdseluniembbultopinv==NULL) init_seluniembbultopinv();
    memset(&svdbupinv,0,sizeof(svdbupinv));
    strcpy(svdbupinv.codbulto,codbulto);
    vdret=ejefetchcursor(vdseluniembbultopinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BUPINVbuscauniembbultopinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bupinv=svdbupinv;
    return(vdret);
}

int BUPINVnextuniembbultopinv(vdbupinvs *bupinv)
{
    int vdret;
    vdret=fetchcursor(vdseluniembbultopinv);
    if (!vdret) {
        *bupinv=svdbupinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseluniembbultopinv);
    return(VD_EERRORACLE);
}

char * BUPINVdebug(vdbupinvs *bupinv)
{
    debugestruct(&dbupinv,bupinv,msgdebugbupinv);
    return(msgdebugbupinv);
}

