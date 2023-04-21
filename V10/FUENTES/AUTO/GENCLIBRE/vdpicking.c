// Modulo generado automaticamente a partir de VDPICKING.DEF
//NOMBRE=PICKING;
//
//EXTRA=ERROR,V10LONG;
//
//   
//CURSOR=OPEPICKING SELECT CODOPE FROM VDUSUARIO WHERE CODOPE=:VDUSUARIO.CODOPE;    
//
//SELECT=PRIVILEGIO,SELECT VDUSER.TIENEPRIVILEGIO(:VDUSUARIO.CODOPE,NVL(:VDPRIVOPE.PRIVILEGIO,'PICKING')) TIENEPRIVILEGIO FROM DUAL;                               
//                     
//SELECT=DATOSOPE,SELECT COUNT(DISTINCT OPA.CODOPE) NUMOPE, COUNT(DISTINCT BUZ.CODBULTO) NUMBULTOSZONA, COUNT (DISTINCT(DECODE(BUZ.CODOPE,:VDUSUARIO.CODOPE,BUZ.CODBULTO,0)))-1 NUMBULTOSOPE
//                FROM VDBULTOZONA BUZ, VDOPEACTIVIDAD OPA
//                WHERE OPA.CODZONA=:VDZONAS.CODZONA AND BUZ.CODZONA(+) = OPA.CODZONA AND
//                      NVL(OPA.FECFINACT,0)=0 AND OPA.HORAFINACT IS NULL;
//                
//SELECT=DAMEPARAMMENU,SELECT VD.PIECE(IME.PARAM,'#',2) PARAM 
//                     FROM VDZONAS ZON, VDINFOMENUS IME
//                     WHERE ZON.CODZONA = :VDZONAS.CODZONA AND 
//                           ZON.CODZONA = IME.CODZONA AND 
//                           ZON.IDMENU = IME.IDMENU; 
//                           
//CURSOR=DATOSCANAL, SELECT 'U' UNICAPAC, DECODE(UNICAPAC,'C',COUNT(DISTINCT CANTIDAD), SUM(CANTIDAD)) CANTTOTAL
//                   FROM (SELECT UBI.UNICAPAC, DECODE(UBI.UNICAPAC,'U',STK.CANTIDAD,'E',CEIL(STK.CANTIDAD/STK.UNIEMB),'C',STK.CODMAT) CANTIDAD
//                         FROM VDSTOCK STK, VDCONTE CNT, VDUBICA UBI 
//                         WHERE STK.CODMAT = CNT.CODMAT AND 
//                               CNT.CODUBI = :VDUBICA.CODUBI AND
//                               CNT.CODUBI = UBI.CODUBI 
//                         ORDER BY STK.ORDENSTK)
//                   GROUP BY UNICAPAC;                           
//                           
//CURSOR=DATOSBOCACANAL, SELECT STK.CODMAT, CNT.POSCONTE, STK.ORDENSTK, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.EMBCONT, 
//                              TRUNC(STK.CANTIDAD/STK.UNIEMB) BULTBOCACANAL, 
//                              DECODE(MOD(STK.CANTIDAD,STK.UNIEMB),0,STK.UNIEMB,MOD(STK.CANTIDAD,STK.UNIEMB)) CANTBOCACANAL,
//                              DECODE(UBI.UNICAPAC,'E','U','C','E','U') UNICAPAC 
//                       FROM VDSTOCK STK, VDCONTE CNT, VDUBICA UBI 
//                       WHERE STK.CODMAT = CNT.CODMAT AND 
//                             CNT.CODUBI = :VDUBICA.CODUBI AND 
//                             CNT.CODUBI = UBI.CODUBI      
//                       ORDER BY CNT.POSCONTE, STK.ORDENSTK;     
//                       
//CURSOR=DATOSULTMOV, SELECT MOV.CODART, MOV.CODLOT, MOV.UNIEMB, MOV.EMBCONT, 0 CANTBOCACANAL, DECODE(UBI.UNICAPAC,'E','U','C','E','U') UNICAPAC 
//                    FROM VDUBICA UBI, VDMOVIM MOV
//                         WHERE UBI.CODUBI= :VDUBICA.CODUBI AND
//                         VDCOM.DAMECOMEN(UBI.CODCOMEN,'CODMOVPICKUNI',1) = MOV.CODMOV;           
//                         
//CURSOR=DISPACTZONA SELECT IDI.IDINFOPICK, IDI.NUMDISP
//                   FROM VDINFODISP IDI, VDINFOHARDDISP IHD
//                   WHERE IDI.IDINFOPICK = IHD.IDINFOPICK AND
//                         IDI.NUMDISP = IHD.NUMDISP AND
//                         IDI.CODZONA = :VDZONAS.CODZONA AND
//                         IDI.STATUS <> VDST.FIDIAPAGADO AND
//                         IHD.TEXTO IS NOT NULL AND
//                         NVL(IHD.LUCES,'0,0,0,0,0,0') <> '0,0,0,0,0,0';
//
//CURSOR=HIJOSLUZ,SELECT IDINFOPICK, NUMDISP 
//                FROM VDINFODISP
//                WHERE IDINFOPICK = :VDINFODISP.IDINFOPICK AND NUMDISP = :VDINFODISP.NUMDISP AND
//                      ((IDINFOPICK <> IDINFOPICKLUZ OR NUMLUZ <> NUMDISP) OR 
//                       EXISTS (SELECT NUMDISP FROM VDINFODISP WHERE IDINFOPICKLUZ = :VDINFODISP.IDINFOPICK AND NUMLUZ = :VDINFODISP.NUMDISP AND
//                               (IDINFOPICK <> IDINFOPICKLUZ OR NUMLUZ <> NUMDISP)));
//                       
//
//    

#include "vdpedidos.h"\

#define SELOPEPICKING "SELECT CODOPE FROM VDUSUARIO WHERE CODOPE=:CODOPE"
static v10cursors *vdselopepicking;
#define SELPRIVILEGIO "SELECT VDUSER.TIENEPRIVILEGIO(:CODOPE,NVL(:PRIVILEGIO,'PICKING')) TIENEPRIVILEGIO FROM DUAL"
static v10cursors *vdselprivilegio;
#define SELDATOSOPE "SELECT COUNT(DISTINCT OPA.CODOPE) NUMOPE, COUNT(DISTINCT BUZ.CODBULTO) NUMBULTOSZONA, COUNT (DISTINCT(DECODE(BUZ.CODOPE,:CODOPE,BUZ.CODBULTO,0)))-1 NUMBULTOSOPE FROM VDBULTOZONA BUZ, VDOPEACTIVIDAD OPA WHERE OPA.CODZONA=:CODZONA AND BUZ.CODZONA(+) = OPA.CODZONA AND NVL(OPA.FECFINACT,0)=0 AND OPA.HORAFINACT IS NULL"
static v10cursors *vdseldatosope;
#define SELDAMEPARAMMENU "SELECT VD.PIECE(IME.PARAM,'#',2) PARAM  FROM VDZONAS ZON, VDINFOMENUS IME WHERE ZON.CODZONA = :CODZONA AND  ZON.CODZONA = IME.CODZONA AND  ZON.IDMENU = IME.IDMENU"
static v10cursors *vdseldameparammenu;
#define SELDATOSCANAL " SELECT 'U' UNICAPAC, DECODE(UNICAPAC,'C',COUNT(DISTINCT CANTIDAD), SUM(CANTIDAD)) CANTTOTAL FROM (SELECT UBI.UNICAPAC, DECODE(UBI.UNICAPAC,'U',STK.CANTIDAD,'E',CEIL(STK.CANTIDAD/STK.UNIEMB),'C',STK.CODMAT) CANTIDAD FROM VDSTOCK STK, VDCONTE CNT, VDUBICA UBI  WHERE STK.CODMAT = CNT.CODMAT AND  CNT.CODUBI = :CODUBI AND CNT.CODUBI = UBI.CODUBI  ORDER BY STK.ORDENSTK) GROUP BY UNICAPAC"
static v10cursors *vdseldatoscanal;
#define SELDATOSBOCACANAL " SELECT STK.CODMAT, CNT.POSCONTE, STK.ORDENSTK, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.EMBCONT,  TRUNC(STK.CANTIDAD/STK.UNIEMB) BULTBOCACANAL,  DECODE(MOD(STK.CANTIDAD,STK.UNIEMB),0,STK.UNIEMB,MOD(STK.CANTIDAD,STK.UNIEMB)) CANTBOCACANAL, DECODE(UBI.UNICAPAC,'E','U','C','E','U') UNICAPAC  FROM VDSTOCK STK, VDCONTE CNT, VDUBICA UBI  WHERE STK.CODMAT = CNT.CODMAT AND  CNT.CODUBI = :CODUBI AND  CNT.CODUBI = UBI.CODUBI       ORDER BY CNT.POSCONTE, STK.ORDENSTK"
static v10cursors *vdseldatosbocacanal;
#define SELDATOSULTMOV " SELECT MOV.CODART, MOV.CODLOT, MOV.UNIEMB, MOV.EMBCONT, 0 CANTBOCACANAL, DECODE(UBI.UNICAPAC,'E','U','C','E','U') UNICAPAC  FROM VDUBICA UBI, VDMOVIM MOV WHERE UBI.CODUBI= :CODUBI AND VDCOM.DAMECOMEN(UBI.CODCOMEN,'CODMOVPICKUNI',1) = MOV.CODMOV"
static v10cursors *vdseldatosultmov;
#define SELDISPACTZONA "SELECT IDI.IDINFOPICK, IDI.NUMDISP FROM VDINFODISP IDI, VDINFOHARDDISP IHD WHERE IDI.IDINFOPICK = IHD.IDINFOPICK AND IDI.NUMDISP = IHD.NUMDISP AND IDI.CODZONA = :CODZONA AND IDI.STATUS <> VDST.FIDIAPAGADO AND IHD.TEXTO IS NOT NULL AND NVL(IHD.LUCES,'0,0,0,0,0,0') <> '0,0,0,0,0,0'"
static v10cursors *vdseldispactzona;
#define SELHIJOSLUZ "SELECT IDINFOPICK, NUMDISP  FROM VDINFODISP WHERE IDINFOPICK = :IDINFOPICK AND NUMDISP = :NUMDISP AND ((IDINFOPICK <> IDINFOPICKLUZ OR NUMLUZ <> NUMDISP) OR  EXISTS (SELECT NUMDISP FROM VDINFODISP WHERE IDINFOPICKLUZ = :IDINFOPICK AND NUMLUZ = :NUMDISP AND (IDINFOPICK <> IDINFOPICKLUZ OR NUMLUZ <> NUMDISP)))"
static v10cursors *vdselhijosluz;

static vdpickings svdpicking;

static diccols colvdpicking[]={ 
    {"ERROR",V10LONG,(size_t)&svdpicking.error,sizeof(svdpicking.error)},
    {"CODOPE",V10CADENA,(size_t)&svdpicking.codope,sizeof(svdpicking.codope)},
    {"TIENEPRIVILEGIO",V10LONG,(size_t)&svdpicking.tieneprivilegio,sizeof(svdpicking.tieneprivilegio)},
    {"PRIVILEGIO",V10CADENA,(size_t)&svdpicking.privilegio,sizeof(svdpicking.privilegio)},
    {"NUMOPE",V10LONG,(size_t)&svdpicking.numope,sizeof(svdpicking.numope)},
    {"NUMBULTOSZONA",V10LONG,(size_t)&svdpicking.numbultoszona,sizeof(svdpicking.numbultoszona)},
    {"NUMBULTOSOPE",V10LONG,(size_t)&svdpicking.numbultosope,sizeof(svdpicking.numbultosope)},
    {"CODZONA",V10LONG,(size_t)&svdpicking.codzona,sizeof(svdpicking.codzona)},
    {"PARAM",V10CADENA,(size_t)&svdpicking.param,sizeof(svdpicking.param)},
    {"UNICAPAC",V10CADENA,(size_t)&svdpicking.unicapac,sizeof(svdpicking.unicapac)},
    {"CANTTOTAL",V10LONG,(size_t)&svdpicking.canttotal,sizeof(svdpicking.canttotal)},
    {"CODUBI",V10CADENA,(size_t)&svdpicking.codubi,sizeof(svdpicking.codubi)},
    {"CODMAT",V10CADENA,(size_t)&svdpicking.codmat,sizeof(svdpicking.codmat)},
    {"POSCONTE",V10LONG,(size_t)&svdpicking.posconte,sizeof(svdpicking.posconte)},
    {"ORDENSTK",V10LONG,(size_t)&svdpicking.ordenstk,sizeof(svdpicking.ordenstk)},
    {"CODART",V10CADENA,(size_t)&svdpicking.codart,sizeof(svdpicking.codart)},
    {"CODLOT",V10CADENA,(size_t)&svdpicking.codlot,sizeof(svdpicking.codlot)},
    {"UNIEMB",V10DOUBLE,(size_t)&svdpicking.uniemb,sizeof(svdpicking.uniemb)},
    {"EMBCONT",V10LONG,(size_t)&svdpicking.embcont,sizeof(svdpicking.embcont)},
    {"BULTBOCACANAL",V10LONG,(size_t)&svdpicking.bultbocacanal,sizeof(svdpicking.bultbocacanal)},
    {"CANTBOCACANAL",V10LONG,(size_t)&svdpicking.cantbocacanal,sizeof(svdpicking.cantbocacanal)},
    {"IDINFOPICK",V10LONG,(size_t)&svdpicking.idinfopick,sizeof(svdpicking.idinfopick)},
    {"NUMDISP",V10LONG,(size_t)&svdpicking.numdisp,sizeof(svdpicking.numdisp)}
    };

static diccionarios dvdpicking[]={
    {colvdpicking,23}
    };

diccionario dpicking={dvdpicking,1};

static char msgdebugpicking[LCADENABIG];

static int init=0;


static void fin_vd_PICKING(void)
{
    if(vdselopepicking){
        liberacursor(vdselopepicking);
        vdselopepicking=NULL;
    }
    if(vdselprivilegio){
        liberacursor(vdselprivilegio);
        vdselprivilegio=NULL;
    }
    if(vdseldatosope){
        liberacursor(vdseldatosope);
        vdseldatosope=NULL;
    }
    if(vdseldameparammenu){
        liberacursor(vdseldameparammenu);
        vdseldameparammenu=NULL;
    }
    if(vdseldatoscanal){
        liberacursor(vdseldatoscanal);
        vdseldatoscanal=NULL;
    }
    if(vdseldatosbocacanal){
        liberacursor(vdseldatosbocacanal);
        vdseldatosbocacanal=NULL;
    }
    if(vdseldatosultmov){
        liberacursor(vdseldatosultmov);
        vdseldatosultmov=NULL;
    }
    if(vdseldispactzona){
        liberacursor(vdseldispactzona);
        vdseldispactzona=NULL;
    }
    if(vdselhijosluz){
        liberacursor(vdselhijosluz);
        vdselhijosluz=NULL;
    }
}


static void init_selopepicking(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdselopepicking=abrecursor(SELOPEPICKING);
    definetodo(vdselopepicking,svdpicking.codope,sizeof(svdpicking.codope),V10CADENA,
               NULL);
    bindtodo(vdselopepicking,"CODOPE",svdpicking.codope,sizeof(svdpicking.codope),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_selprivilegio(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdselprivilegio=abrecursor(SELPRIVILEGIO);
    definetodo(vdselprivilegio,&svdpicking.tieneprivilegio,sizeof(svdpicking.tieneprivilegio),V10LONG,
               NULL);
    bindtodo(vdselprivilegio,"CODOPE",svdpicking.codope,sizeof(svdpicking.codope),V10CADENA,
             "PRIVILEGIO",svdpicking.privilegio,sizeof(svdpicking.privilegio),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldatosope(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldatosope=abrecursor(SELDATOSOPE);
    definetodo(vdseldatosope,&svdpicking.numope,sizeof(svdpicking.numope),V10LONG,
               &svdpicking.numbultoszona,sizeof(svdpicking.numbultoszona),V10LONG,
               &svdpicking.numbultosope,sizeof(svdpicking.numbultosope),V10LONG,
               NULL);
    bindtodo(vdseldatosope,"CODOPE",svdpicking.codope,sizeof(svdpicking.codope),V10CADENA,
             "CODZONA",&svdpicking.codzona,sizeof(svdpicking.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldameparammenu(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldameparammenu=abrecursor(SELDAMEPARAMMENU);
    definetodo(vdseldameparammenu,svdpicking.param,sizeof(svdpicking.param),V10CADENA,
               NULL);
    bindtodo(vdseldameparammenu,"CODZONA",&svdpicking.codzona,sizeof(svdpicking.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldatoscanal(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldatoscanal=abrecursor(SELDATOSCANAL);
    definetodo(vdseldatoscanal,svdpicking.unicapac,sizeof(svdpicking.unicapac),V10CADENA,
               &svdpicking.canttotal,sizeof(svdpicking.canttotal),V10LONG,
               NULL);
    bindtodo(vdseldatoscanal,"CODUBI",svdpicking.codubi,sizeof(svdpicking.codubi),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldatosbocacanal(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldatosbocacanal=abrecursor(SELDATOSBOCACANAL);
    definetodo(vdseldatosbocacanal,svdpicking.codmat,sizeof(svdpicking.codmat),V10CADENA,
               &svdpicking.posconte,sizeof(svdpicking.posconte),V10LONG,
               &svdpicking.ordenstk,sizeof(svdpicking.ordenstk),V10LONG,
               svdpicking.codart,sizeof(svdpicking.codart),V10CADENA,
               svdpicking.codlot,sizeof(svdpicking.codlot),V10CADENA,
               &svdpicking.uniemb,sizeof(svdpicking.uniemb),V10DOUBLE,
               &svdpicking.embcont,sizeof(svdpicking.embcont),V10LONG,
               &svdpicking.bultbocacanal,sizeof(svdpicking.bultbocacanal),V10LONG,
               &svdpicking.cantbocacanal,sizeof(svdpicking.cantbocacanal),V10LONG,
               svdpicking.unicapac,sizeof(svdpicking.unicapac),V10CADENA,
               NULL);
    bindtodo(vdseldatosbocacanal,"CODUBI",svdpicking.codubi,sizeof(svdpicking.codubi),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldatosultmov(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldatosultmov=abrecursor(SELDATOSULTMOV);
    definetodo(vdseldatosultmov,svdpicking.codart,sizeof(svdpicking.codart),V10CADENA,
               svdpicking.codlot,sizeof(svdpicking.codlot),V10CADENA,
               &svdpicking.uniemb,sizeof(svdpicking.uniemb),V10DOUBLE,
               &svdpicking.embcont,sizeof(svdpicking.embcont),V10LONG,
               &svdpicking.cantbocacanal,sizeof(svdpicking.cantbocacanal),V10LONG,
               svdpicking.unicapac,sizeof(svdpicking.unicapac),V10CADENA,
               NULL);
    bindtodo(vdseldatosultmov,"CODUBI",svdpicking.codubi,sizeof(svdpicking.codubi),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_seldispactzona(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdseldispactzona=abrecursor(SELDISPACTZONA);
    definetodo(vdseldispactzona,&svdpicking.idinfopick,sizeof(svdpicking.idinfopick),V10LONG,
               &svdpicking.numdisp,sizeof(svdpicking.numdisp),V10LONG,
               NULL);
    bindtodo(vdseldispactzona,"CODZONA",&svdpicking.codzona,sizeof(svdpicking.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

static void init_selhijosluz(void)
{
    int nc;

    for(nc=0;nc<dvdpicking[0].numcol;nc++) dvdpicking[0].c[nc].offset-=(size_t)&svdpicking;

    vdselhijosluz=abrecursor(SELHIJOSLUZ);
    definetodo(vdselhijosluz,&svdpicking.idinfopick,sizeof(svdpicking.idinfopick),V10LONG,
               &svdpicking.numdisp,sizeof(svdpicking.numdisp),V10LONG,
               NULL);
    bindtodo(vdselhijosluz,"IDINFOPICK",&svdpicking.idinfopick,sizeof(svdpicking.idinfopick),V10LONG,
             "NUMDISP",&svdpicking.numdisp,sizeof(svdpicking.numdisp),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKING);
        init = 1;
    }
}

diccionario *PICKINGdamediccionario(void)
{
    return(&dpicking);
}

int PICKINGbuscaopepicking(char *codope,vdpickings *picking)
{
    int vdret;
    if (vdselopepicking==NULL) init_selopepicking();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codope,codope);
    vdret=ejefetchcursor(vdselopepicking);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscaopepicking vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnextopepicking(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdselopepicking);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselopepicking);
    return(VD_EERRORACLE);
}

int PICKINGselprivilegio(char *codope,char *privilegio,vdpickings *picking)
{
    int vdret;
    if (vdselprivilegio==NULL) init_selprivilegio();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codope,codope);
    strcpy(svdpicking.privilegio,privilegio);
    vdret=ejefetchcursor(vdselprivilegio);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscaprivilegio vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGseldatosope(char *codope,long codzona,vdpickings *picking)
{
    int vdret;
    if (vdseldatosope==NULL) init_seldatosope();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codope,codope);
    svdpicking.codzona=codzona;
    vdret=ejefetchcursor(vdseldatosope);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadatosope vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGseldameparammenu(long codzona,vdpickings *picking)
{
    int vdret;
    if (vdseldameparammenu==NULL) init_seldameparammenu();
    memset(&svdpicking,0,sizeof(svdpicking));
    svdpicking.codzona=codzona;
    vdret=ejefetchcursor(vdseldameparammenu);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadameparammenu vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGbuscadatoscanal(char *codubi,vdpickings *picking)
{
    int vdret;
    if (vdseldatoscanal==NULL) init_seldatoscanal();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codubi,codubi);
    vdret=ejefetchcursor(vdseldatoscanal);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadatoscanal vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnextdatoscanal(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdseldatoscanal);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldatoscanal);
    return(VD_EERRORACLE);
}

int PICKINGbuscadatosbocacanal(char *codubi,vdpickings *picking)
{
    int vdret;
    if (vdseldatosbocacanal==NULL) init_seldatosbocacanal();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codubi,codubi);
    vdret=ejefetchcursor(vdseldatosbocacanal);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadatosbocacanal vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnextdatosbocacanal(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdseldatosbocacanal);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldatosbocacanal);
    return(VD_EERRORACLE);
}

int PICKINGbuscadatosultmov(char *codubi,vdpickings *picking)
{
    int vdret;
    if (vdseldatosultmov==NULL) init_seldatosultmov();
    memset(&svdpicking,0,sizeof(svdpicking));
    strcpy(svdpicking.codubi,codubi);
    vdret=ejefetchcursor(vdseldatosultmov);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadatosultmov vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnextdatosultmov(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdseldatosultmov);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldatosultmov);
    return(VD_EERRORACLE);
}

int PICKINGbuscadispactzona(long codzona,vdpickings *picking)
{
    int vdret;
    if (vdseldispactzona==NULL) init_seldispactzona();
    memset(&svdpicking,0,sizeof(svdpicking));
    svdpicking.codzona=codzona;
    vdret=ejefetchcursor(vdseldispactzona);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscadispactzona vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnextdispactzona(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdseldispactzona);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldispactzona);
    return(VD_EERRORACLE);
}

int PICKINGbuscahijosluz(long idinfopick,long numdisp,vdpickings *picking)
{
    int vdret;
    if (vdselhijosluz==NULL) init_selhijosluz();
    memset(&svdpicking,0,sizeof(svdpicking));
    svdpicking.idinfopick=idinfopick;
    svdpicking.numdisp=numdisp;
    vdret=ejefetchcursor(vdselhijosluz);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINGbuscahijosluz vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *picking=svdpicking;
    return(vdret);
}

int PICKINGnexthijosluz(vdpickings *picking)
{
    int vdret;
    vdret=fetchcursor(vdselhijosluz);
    if (!vdret) {
        *picking=svdpicking;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselhijosluz);
    return(VD_EERRORACLE);
}

char * PICKINGdebug(vdpickings *picking)
{
    debugestruct(&dpicking,picking,msgdebugpicking);
    return(msgdebugpicking);
}

