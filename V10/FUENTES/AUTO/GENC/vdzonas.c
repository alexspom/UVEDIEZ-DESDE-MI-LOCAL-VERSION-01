// Modulo generado automaticamente a partir de VDZONAS.DEF
//#***
//# VDZONAS.DEF - Generación automática del código c para la tabla de ZONAS                                                       
//# 
//# Propósito: Funciones de acceso a la tabla VDZONAS
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 27-05-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=ZON
//CLAVE=SCANNER,REDSCAN,SCANNER
//CLAVE=NUMDISP,IDINFOPICK,NUMDISP
//RECORRE=TICK,IDINFOGEST, WHERE NEXTTICK IS NOT NULL AND NEXTTICK<=VD.FECHASEC;
//
//UPDATE=CODOPE,CODOPE
//UPDATE=IDMENU,IDMENU
//UPDATE=STATUS,STATUS
//UPDATE=PROCESOS,STATUS,PROCESOZONA,PROCESODISP
//
//INSERT 
//DELETE

#include "vd.h"
#define SELZONSCANNER "SELECT VDZONAS.ROWID,VDZONAS.CODZONA,VDZONAS.DESZONA, "\
                    " VDZONAS.TIPOZONA,VDZONAS.ACTIVA,VDZONAS.PRIOZONA, "\
                    " VDZONAS.IDINFOGEST,VDZONAS.IDINFOPICK,VDZONAS.NUMDISP, "\
                    " VDZONAS.MAXOPER,VDZONAS.MAXBULTOSOPER,VDZONAS.DISPILUMINADOS, "\
                    " VDZONAS.REDSCAN,VDZONAS.SCANNER,VDZONAS.MAXCAPACIDAD, "\
                    " VDZONAS.AUTOAPERTURA,VDZONAS.TIEMPOOK,VDZONAS.TIEMPOFIN, "\
                    " VDZONAS.NEXTTICK,VDZONAS.PRIVPICKING,VDZONAS.PROCESOZONA, "\
                    " VDZONAS.PROCESODISP,VDZONAS.IDMENU,VDZONAS.STATUS, "\
                    " VDZONAS.CODOPE,VDZONAS.VDEXTRA,VDZONAS.CODCOMEN, "\
                    " VDZONAS.CODOPEMODIF,VDZONAS.FECMODIF,VDZONAS.HORAMODIF, "\
                    " VDZONAS.RANGOTIPOVOL,VDZONAS.CODMOV,VDZONAS.NUMBASC, "\
                    " VDZONAS.ACTIVABASC,VDZONAS.CODIMPRE,VDZONAS.CANTQUEDABASC, "\
                    " VDZONAS.MENUPRIN,VDZONAS.DATOSMENU,VDZONAS.TEXTOMENU, "\
                    " VDZONAS.CAPACIDAD,VDZONAS.COLORZONA "\
        " FROM VDZONAS"\
        " WHERE "\
               " VDZONAS.REDSCAN=:REDSCAN "\
               " AND VDZONAS.SCANNER=:SCANNER "
static v10cursors *vdselzonscanner;

#define SELZONNUMDISP "SELECT VDZONAS.ROWID,VDZONAS.CODZONA,VDZONAS.DESZONA, "\
                    " VDZONAS.TIPOZONA,VDZONAS.ACTIVA,VDZONAS.PRIOZONA, "\
                    " VDZONAS.IDINFOGEST,VDZONAS.IDINFOPICK,VDZONAS.NUMDISP, "\
                    " VDZONAS.MAXOPER,VDZONAS.MAXBULTOSOPER,VDZONAS.DISPILUMINADOS, "\
                    " VDZONAS.REDSCAN,VDZONAS.SCANNER,VDZONAS.MAXCAPACIDAD, "\
                    " VDZONAS.AUTOAPERTURA,VDZONAS.TIEMPOOK,VDZONAS.TIEMPOFIN, "\
                    " VDZONAS.NEXTTICK,VDZONAS.PRIVPICKING,VDZONAS.PROCESOZONA, "\
                    " VDZONAS.PROCESODISP,VDZONAS.IDMENU,VDZONAS.STATUS, "\
                    " VDZONAS.CODOPE,VDZONAS.VDEXTRA,VDZONAS.CODCOMEN, "\
                    " VDZONAS.CODOPEMODIF,VDZONAS.FECMODIF,VDZONAS.HORAMODIF, "\
                    " VDZONAS.RANGOTIPOVOL,VDZONAS.CODMOV,VDZONAS.NUMBASC, "\
                    " VDZONAS.ACTIVABASC,VDZONAS.CODIMPRE,VDZONAS.CANTQUEDABASC, "\
                    " VDZONAS.MENUPRIN,VDZONAS.DATOSMENU,VDZONAS.TEXTOMENU, "\
                    " VDZONAS.CAPACIDAD,VDZONAS.COLORZONA "\
        " FROM VDZONAS"\
        " WHERE "\
               " VDZONAS.IDINFOPICK=:IDINFOPICK "\
               " AND VDZONAS.NUMDISP=:NUMDISP "
static v10cursors *vdselzonnumdisp;

#define SELZONTICK "SELECT VDZONAS.ROWID,VDZONAS.CODZONA,VDZONAS.DESZONA, "\
                    " VDZONAS.TIPOZONA,VDZONAS.ACTIVA,VDZONAS.PRIOZONA, "\
                    " VDZONAS.IDINFOGEST,VDZONAS.IDINFOPICK,VDZONAS.NUMDISP, "\
                    " VDZONAS.MAXOPER,VDZONAS.MAXBULTOSOPER,VDZONAS.DISPILUMINADOS, "\
                    " VDZONAS.REDSCAN,VDZONAS.SCANNER,VDZONAS.MAXCAPACIDAD, "\
                    " VDZONAS.AUTOAPERTURA,VDZONAS.TIEMPOOK,VDZONAS.TIEMPOFIN, "\
                    " VDZONAS.NEXTTICK,VDZONAS.PRIVPICKING,VDZONAS.PROCESOZONA, "\
                    " VDZONAS.PROCESODISP,VDZONAS.IDMENU,VDZONAS.STATUS, "\
                    " VDZONAS.CODOPE,VDZONAS.VDEXTRA,VDZONAS.CODCOMEN, "\
                    " VDZONAS.CODOPEMODIF,VDZONAS.FECMODIF,VDZONAS.HORAMODIF, "\
                    " VDZONAS.RANGOTIPOVOL,VDZONAS.CODMOV,VDZONAS.NUMBASC, "\
                    " VDZONAS.ACTIVABASC,VDZONAS.CODIMPRE,VDZONAS.CANTQUEDABASC, "\
                    " VDZONAS.MENUPRIN,VDZONAS.DATOSMENU,VDZONAS.TEXTOMENU, "\
                    " VDZONAS.CAPACIDAD,VDZONAS.COLORZONA "\
        " FROM VDZONAS"\
        " WHERE "\
               " VDZONAS.IDINFOGEST=:IDINFOGEST "\
              "  AND NEXTTICK IS NOT NULL AND NEXTTICK<=VD.FECHASEC "
static v10cursors *vdselzontick;

#define SELZONVDZONAS "SELECT VDZONAS.ROWID,VDZONAS.CODZONA,VDZONAS.DESZONA, "\
                    " VDZONAS.TIPOZONA,VDZONAS.ACTIVA,VDZONAS.PRIOZONA, "\
                    " VDZONAS.IDINFOGEST,VDZONAS.IDINFOPICK,VDZONAS.NUMDISP, "\
                    " VDZONAS.MAXOPER,VDZONAS.MAXBULTOSOPER,VDZONAS.DISPILUMINADOS, "\
                    " VDZONAS.REDSCAN,VDZONAS.SCANNER,VDZONAS.MAXCAPACIDAD, "\
                    " VDZONAS.AUTOAPERTURA,VDZONAS.TIEMPOOK,VDZONAS.TIEMPOFIN, "\
                    " VDZONAS.NEXTTICK,VDZONAS.PRIVPICKING,VDZONAS.PROCESOZONA, "\
                    " VDZONAS.PROCESODISP,VDZONAS.IDMENU,VDZONAS.STATUS, "\
                    " VDZONAS.CODOPE,VDZONAS.VDEXTRA,VDZONAS.CODCOMEN, "\
                    " VDZONAS.CODOPEMODIF,VDZONAS.FECMODIF,VDZONAS.HORAMODIF, "\
                    " VDZONAS.RANGOTIPOVOL,VDZONAS.CODMOV,VDZONAS.NUMBASC, "\
                    " VDZONAS.ACTIVABASC,VDZONAS.CODIMPRE,VDZONAS.CANTQUEDABASC, "\
                    " VDZONAS.MENUPRIN,VDZONAS.DATOSMENU,VDZONAS.TEXTOMENU, "\
                    " VDZONAS.CAPACIDAD,VDZONAS.COLORZONA "\
        " FROM VDZONAS"\
        " WHERE "\
               " VDZONAS.CODZONA=:CODZONA "
static v10cursors *vdselzonvdzonas;

#define UPDAZONCODOPE "UPDATE VDZONAS SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODOPE=:CODOPE  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdazoncodope;

#define UPDAZONIDMENU "UPDATE VDZONAS SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " IDMENU=:IDMENU  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdazonidmenu;

#define UPDAZONSTATUS "UPDATE VDZONAS SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdazonstatus;

#define UPDAZONPROCESOS "UPDATE VDZONAS SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS , "\
               " PROCESOZONA=:PROCESOZONA , "\
               " PROCESODISP=:PROCESODISP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdazonprocesos;

#define INSZON "INSERT INTO VDZONAS (CODZONA,DESZONA,TIPOZONA,ACTIVA,PRIOZONA,IDINFOGEST, "\
                    " IDINFOPICK,NUMDISP,MAXOPER,MAXBULTOSOPER,DISPILUMINADOS,REDSCAN,SCANNER, "\
                    " MAXCAPACIDAD,AUTOAPERTURA,TIEMPOOK,TIEMPOFIN,NEXTTICK,PRIVPICKING,PROCESOZONA, "\
                    " PROCESODISP,IDMENU,STATUS,CODOPE,VDEXTRA,CODCOMEN,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF,RANGOTIPOVOL,CODMOV,NUMBASC,ACTIVABASC,CODIMPRE, "\
                    " CANTQUEDABASC,MENUPRIN,DATOSMENU,TEXTOMENU,CAPACIDAD,COLORZONA "\
       " ) VALUES ( "\
                    " :CODZONA,:DESZONA,:TIPOZONA,:ACTIVA,:PRIOZONA,:IDINFOGEST, "\
                    " :IDINFOPICK,:NUMDISP,:MAXOPER,:MAXBULTOSOPER,:DISPILUMINADOS,:REDSCAN,:SCANNER, "\
                    " :MAXCAPACIDAD,:AUTOAPERTURA,:TIEMPOOK,:TIEMPOFIN,:NEXTTICK,:PRIVPICKING,:PROCESOZONA, "\
                    " :PROCESODISP,:IDMENU,:STATUS,:CODOPE,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER(), "\
                    " VD.FECHASYS(),VD.HORASYS(),:RANGOTIPOVOL,:CODMOV,:NUMBASC,:ACTIVABASC,:CODIMPRE, "\
                    " :CANTQUEDABASC,:MENUPRIN,:DATOSMENU,:TEXTOMENU,:CAPACIDAD,:COLORZONA) "
static v10cursors *vdinszon;

#define DELZON "DELETE VDZONAS WHERE ROWID=:MIROWID "
static v10cursors *vddelzon;

static vdzonass svdzonas;

static diccols colvdzonas[]={
	{"ROWID",V10CADENA,(size_t)&svdzonas.rowid,sizeof(svdzonas.rowid)},
	{"CODZONA",V10LONG,(size_t)&svdzonas.codzona,sizeof(svdzonas.codzona)},
	{"DESZONA",V10CADENA,(size_t)&svdzonas.deszona,sizeof(svdzonas.deszona)},
	{"TIPOZONA",V10CADENA,(size_t)&svdzonas.tipozona,sizeof(svdzonas.tipozona)},
	{"ACTIVA",V10CADENA,(size_t)&svdzonas.activa,sizeof(svdzonas.activa)},
	{"PRIOZONA",V10LONG,(size_t)&svdzonas.priozona,sizeof(svdzonas.priozona)},
	{"IDINFOGEST",V10LONG,(size_t)&svdzonas.idinfogest,sizeof(svdzonas.idinfogest)},
	{"IDINFOPICK",V10LONG,(size_t)&svdzonas.idinfopick,sizeof(svdzonas.idinfopick)},
	{"NUMDISP",V10LONG,(size_t)&svdzonas.numdisp,sizeof(svdzonas.numdisp)},
	{"MAXOPER",V10LONG,(size_t)&svdzonas.maxoper,sizeof(svdzonas.maxoper)},
	{"MAXBULTOSOPER",V10LONG,(size_t)&svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper)},
	{"DISPILUMINADOS",V10LONG,(size_t)&svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados)},
	{"REDSCAN",V10LONG,(size_t)&svdzonas.redscan,sizeof(svdzonas.redscan)},
	{"SCANNER",V10LONG,(size_t)&svdzonas.scanner,sizeof(svdzonas.scanner)},
	{"MAXCAPACIDAD",V10LONG,(size_t)&svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad)},
	{"AUTOAPERTURA",V10CADENA,(size_t)&svdzonas.autoapertura,sizeof(svdzonas.autoapertura)},
	{"TIEMPOOK",V10LONG,(size_t)&svdzonas.tiempook,sizeof(svdzonas.tiempook)},
	{"TIEMPOFIN",V10LONG,(size_t)&svdzonas.tiempofin,sizeof(svdzonas.tiempofin)},
	{"NEXTTICK",V10CADENA,(size_t)&svdzonas.nexttick,sizeof(svdzonas.nexttick)},
	{"PRIVPICKING",V10CADENA,(size_t)&svdzonas.privpicking,sizeof(svdzonas.privpicking)},
	{"PROCESOZONA",V10CADENA,(size_t)&svdzonas.procesozona,sizeof(svdzonas.procesozona)},
	{"PROCESODISP",V10CADENA,(size_t)&svdzonas.procesodisp,sizeof(svdzonas.procesodisp)},
	{"IDMENU",V10CADENA,(size_t)&svdzonas.idmenu,sizeof(svdzonas.idmenu)},
	{"STATUS",V10LONG,(size_t)&svdzonas.status,sizeof(svdzonas.status)},
	{"CODOPE",V10CADENA,(size_t)&svdzonas.codope,sizeof(svdzonas.codope)},
	{"VDEXTRA",V10CADENA,(size_t)&svdzonas.vdextra,sizeof(svdzonas.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdzonas.codcomen,sizeof(svdzonas.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdzonas.codopemodif,sizeof(svdzonas.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdzonas.fecmodif,sizeof(svdzonas.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdzonas.horamodif,sizeof(svdzonas.horamodif)},
	{"RANGOTIPOVOL",V10CADENA,(size_t)&svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol)},
	{"CODMOV",V10LONG,(size_t)&svdzonas.codmov,sizeof(svdzonas.codmov)},
	{"NUMBASC",V10LONG,(size_t)&svdzonas.numbasc,sizeof(svdzonas.numbasc)},
	{"ACTIVABASC",V10CADENA,(size_t)&svdzonas.activabasc,sizeof(svdzonas.activabasc)},
	{"CODIMPRE",V10CADENA,(size_t)&svdzonas.codimpre,sizeof(svdzonas.codimpre)},
	{"CANTQUEDABASC",V10DOUBLE,(size_t)&svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc)},
	{"MENUPRIN",V10LONG,(size_t)&svdzonas.menuprin,sizeof(svdzonas.menuprin)},
	{"DATOSMENU",V10CADENA,(size_t)&svdzonas.datosmenu,sizeof(svdzonas.datosmenu)},
	{"TEXTOMENU",V10CADENA,(size_t)&svdzonas.textomenu,sizeof(svdzonas.textomenu)},
	{"CAPACIDAD",V10LONG,(size_t)&svdzonas.capacidad,sizeof(svdzonas.capacidad)},
	{"COLORZONA",V10CADENA,(size_t)&svdzonas.colorzona,sizeof(svdzonas.colorzona)}
	};
static diccionarios dvdzonas[]={
    {colvdzonas,41}
};
diccionario dzon={dvdzonas,1};

static char msglogZON[LCADENA];
static char msgdebugZON[LCADENABIG];
static int init=0;


static void fin_vd_zon(void)
{
if (vdselzonscanner) {
    liberacursor(vdselzonscanner);
    vdselzonscanner = NULL;
}
if (vdselzonnumdisp) {
    liberacursor(vdselzonnumdisp);
    vdselzonnumdisp = NULL;
}
if (vdselzontick) {
    liberacursor(vdselzontick);
    vdselzontick = NULL;
}
if (vdselzonvdzonas) {
    liberacursor(vdselzonvdzonas);
    vdselzonvdzonas = NULL;
}
if (vdupdazoncodope) {
    liberacursor(vdupdazoncodope);
    vdupdazoncodope = NULL;
}
if (vdupdazonidmenu) {
    liberacursor(vdupdazonidmenu);
    vdupdazonidmenu = NULL;
}
if (vdupdazonstatus) {
    liberacursor(vdupdazonstatus);
    vdupdazonstatus = NULL;
}
if (vdupdazonprocesos) {
    liberacursor(vdupdazonprocesos);
    vdupdazonprocesos = NULL;
}
if (vdinszon != NULL) {
    liberacursor(vdinszon);
    vdinszon = NULL;
}
if (vddelzon != NULL) {
    liberacursor(vddelzon);
    vddelzon = NULL;
}
}
static void init_selzonscanner(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdselzonscanner=abrecursordebug(SELZONSCANNER,1280);
    definetodo(vdselzonscanner,svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          &svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          svdzonas.deszona,sizeof(svdzonas.deszona),V10CADENA,
                          svdzonas.tipozona,sizeof(svdzonas.tipozona),V10CADENA,
                          svdzonas.activa,sizeof(svdzonas.activa),V10CADENA,
                          &svdzonas.priozona,sizeof(svdzonas.priozona),V10LONG,
                          &svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          &svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          &svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          &svdzonas.maxoper,sizeof(svdzonas.maxoper),V10LONG,
                          &svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper),V10LONG,
                          &svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados),V10LONG,
                          &svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          &svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          &svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad),V10LONG,
                          svdzonas.autoapertura,sizeof(svdzonas.autoapertura),V10CADENA,
                          &svdzonas.tiempook,sizeof(svdzonas.tiempook),V10LONG,
                          &svdzonas.tiempofin,sizeof(svdzonas.tiempofin),V10LONG,
                          svdzonas.nexttick,sizeof(svdzonas.nexttick),V10CADENA,
                          svdzonas.privpicking,sizeof(svdzonas.privpicking),V10CADENA,
                          svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          &svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          svdzonas.vdextra,sizeof(svdzonas.vdextra),V10CADENA,
                          &svdzonas.codcomen,sizeof(svdzonas.codcomen),V10LONG,
                          svdzonas.codopemodif,sizeof(svdzonas.codopemodif),V10CADENA,
                          &svdzonas.fecmodif,sizeof(svdzonas.fecmodif),V10LONG,
                          svdzonas.horamodif,sizeof(svdzonas.horamodif),V10CADENA,
                          svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol),V10CADENA,
                          &svdzonas.codmov,sizeof(svdzonas.codmov),V10LONG,
                          &svdzonas.numbasc,sizeof(svdzonas.numbasc),V10LONG,
                          svdzonas.activabasc,sizeof(svdzonas.activabasc),V10CADENA,
                          svdzonas.codimpre,sizeof(svdzonas.codimpre),V10CADENA,
                          &svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc),V10DOUBLE,
                          &svdzonas.menuprin,sizeof(svdzonas.menuprin),V10LONG,
                          svdzonas.datosmenu,sizeof(svdzonas.datosmenu),V10CADENA,
                          svdzonas.textomenu,sizeof(svdzonas.textomenu),V10CADENA,
                          &svdzonas.capacidad,sizeof(svdzonas.capacidad),V10LONG,
                          svdzonas.colorzona,sizeof(svdzonas.colorzona),V10CADENA,
                          NULL);
    bindtodo(vdselzonscanner,"REDSCAN",&svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          "SCANNER",&svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_selzonnumdisp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdselzonnumdisp=abrecursordebug(SELZONNUMDISP,1280);
    definetodo(vdselzonnumdisp,svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          &svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          svdzonas.deszona,sizeof(svdzonas.deszona),V10CADENA,
                          svdzonas.tipozona,sizeof(svdzonas.tipozona),V10CADENA,
                          svdzonas.activa,sizeof(svdzonas.activa),V10CADENA,
                          &svdzonas.priozona,sizeof(svdzonas.priozona),V10LONG,
                          &svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          &svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          &svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          &svdzonas.maxoper,sizeof(svdzonas.maxoper),V10LONG,
                          &svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper),V10LONG,
                          &svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados),V10LONG,
                          &svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          &svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          &svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad),V10LONG,
                          svdzonas.autoapertura,sizeof(svdzonas.autoapertura),V10CADENA,
                          &svdzonas.tiempook,sizeof(svdzonas.tiempook),V10LONG,
                          &svdzonas.tiempofin,sizeof(svdzonas.tiempofin),V10LONG,
                          svdzonas.nexttick,sizeof(svdzonas.nexttick),V10CADENA,
                          svdzonas.privpicking,sizeof(svdzonas.privpicking),V10CADENA,
                          svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          &svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          svdzonas.vdextra,sizeof(svdzonas.vdextra),V10CADENA,
                          &svdzonas.codcomen,sizeof(svdzonas.codcomen),V10LONG,
                          svdzonas.codopemodif,sizeof(svdzonas.codopemodif),V10CADENA,
                          &svdzonas.fecmodif,sizeof(svdzonas.fecmodif),V10LONG,
                          svdzonas.horamodif,sizeof(svdzonas.horamodif),V10CADENA,
                          svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol),V10CADENA,
                          &svdzonas.codmov,sizeof(svdzonas.codmov),V10LONG,
                          &svdzonas.numbasc,sizeof(svdzonas.numbasc),V10LONG,
                          svdzonas.activabasc,sizeof(svdzonas.activabasc),V10CADENA,
                          svdzonas.codimpre,sizeof(svdzonas.codimpre),V10CADENA,
                          &svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc),V10DOUBLE,
                          &svdzonas.menuprin,sizeof(svdzonas.menuprin),V10LONG,
                          svdzonas.datosmenu,sizeof(svdzonas.datosmenu),V10CADENA,
                          svdzonas.textomenu,sizeof(svdzonas.textomenu),V10CADENA,
                          &svdzonas.capacidad,sizeof(svdzonas.capacidad),V10LONG,
                          svdzonas.colorzona,sizeof(svdzonas.colorzona),V10CADENA,
                          NULL);
    bindtodo(vdselzonnumdisp,"IDINFOPICK",&svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          "NUMDISP",&svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_selzontick(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdselzontick=abrecursordebug(SELZONTICK,1280);
    definetodo(vdselzontick,svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          &svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          svdzonas.deszona,sizeof(svdzonas.deszona),V10CADENA,
                          svdzonas.tipozona,sizeof(svdzonas.tipozona),V10CADENA,
                          svdzonas.activa,sizeof(svdzonas.activa),V10CADENA,
                          &svdzonas.priozona,sizeof(svdzonas.priozona),V10LONG,
                          &svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          &svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          &svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          &svdzonas.maxoper,sizeof(svdzonas.maxoper),V10LONG,
                          &svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper),V10LONG,
                          &svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados),V10LONG,
                          &svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          &svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          &svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad),V10LONG,
                          svdzonas.autoapertura,sizeof(svdzonas.autoapertura),V10CADENA,
                          &svdzonas.tiempook,sizeof(svdzonas.tiempook),V10LONG,
                          &svdzonas.tiempofin,sizeof(svdzonas.tiempofin),V10LONG,
                          svdzonas.nexttick,sizeof(svdzonas.nexttick),V10CADENA,
                          svdzonas.privpicking,sizeof(svdzonas.privpicking),V10CADENA,
                          svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          &svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          svdzonas.vdextra,sizeof(svdzonas.vdextra),V10CADENA,
                          &svdzonas.codcomen,sizeof(svdzonas.codcomen),V10LONG,
                          svdzonas.codopemodif,sizeof(svdzonas.codopemodif),V10CADENA,
                          &svdzonas.fecmodif,sizeof(svdzonas.fecmodif),V10LONG,
                          svdzonas.horamodif,sizeof(svdzonas.horamodif),V10CADENA,
                          svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol),V10CADENA,
                          &svdzonas.codmov,sizeof(svdzonas.codmov),V10LONG,
                          &svdzonas.numbasc,sizeof(svdzonas.numbasc),V10LONG,
                          svdzonas.activabasc,sizeof(svdzonas.activabasc),V10CADENA,
                          svdzonas.codimpre,sizeof(svdzonas.codimpre),V10CADENA,
                          &svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc),V10DOUBLE,
                          &svdzonas.menuprin,sizeof(svdzonas.menuprin),V10LONG,
                          svdzonas.datosmenu,sizeof(svdzonas.datosmenu),V10CADENA,
                          svdzonas.textomenu,sizeof(svdzonas.textomenu),V10CADENA,
                          &svdzonas.capacidad,sizeof(svdzonas.capacidad),V10LONG,
                          svdzonas.colorzona,sizeof(svdzonas.colorzona),V10CADENA,
                          NULL);
    bindtodo(vdselzontick,"IDINFOGEST",&svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_selzonvdzonas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdselzonvdzonas=abrecursordebug(SELZONVDZONAS,1280);
    definetodo(vdselzonvdzonas,svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          &svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          svdzonas.deszona,sizeof(svdzonas.deszona),V10CADENA,
                          svdzonas.tipozona,sizeof(svdzonas.tipozona),V10CADENA,
                          svdzonas.activa,sizeof(svdzonas.activa),V10CADENA,
                          &svdzonas.priozona,sizeof(svdzonas.priozona),V10LONG,
                          &svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          &svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          &svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          &svdzonas.maxoper,sizeof(svdzonas.maxoper),V10LONG,
                          &svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper),V10LONG,
                          &svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados),V10LONG,
                          &svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          &svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          &svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad),V10LONG,
                          svdzonas.autoapertura,sizeof(svdzonas.autoapertura),V10CADENA,
                          &svdzonas.tiempook,sizeof(svdzonas.tiempook),V10LONG,
                          &svdzonas.tiempofin,sizeof(svdzonas.tiempofin),V10LONG,
                          svdzonas.nexttick,sizeof(svdzonas.nexttick),V10CADENA,
                          svdzonas.privpicking,sizeof(svdzonas.privpicking),V10CADENA,
                          svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          &svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          svdzonas.vdextra,sizeof(svdzonas.vdextra),V10CADENA,
                          &svdzonas.codcomen,sizeof(svdzonas.codcomen),V10LONG,
                          svdzonas.codopemodif,sizeof(svdzonas.codopemodif),V10CADENA,
                          &svdzonas.fecmodif,sizeof(svdzonas.fecmodif),V10LONG,
                          svdzonas.horamodif,sizeof(svdzonas.horamodif),V10CADENA,
                          svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol),V10CADENA,
                          &svdzonas.codmov,sizeof(svdzonas.codmov),V10LONG,
                          &svdzonas.numbasc,sizeof(svdzonas.numbasc),V10LONG,
                          svdzonas.activabasc,sizeof(svdzonas.activabasc),V10CADENA,
                          svdzonas.codimpre,sizeof(svdzonas.codimpre),V10CADENA,
                          &svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc),V10DOUBLE,
                          &svdzonas.menuprin,sizeof(svdzonas.menuprin),V10LONG,
                          svdzonas.datosmenu,sizeof(svdzonas.datosmenu),V10CADENA,
                          svdzonas.textomenu,sizeof(svdzonas.textomenu),V10CADENA,
                          &svdzonas.capacidad,sizeof(svdzonas.capacidad),V10LONG,
                          svdzonas.colorzona,sizeof(svdzonas.colorzona),V10CADENA,
                          NULL);
    bindtodo(vdselzonvdzonas,"CODZONA",&svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_updazoncodope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdupdazoncodope=abrecursordebug(UPDAZONCODOPE,1280);
    bindtodo(vdupdazoncodope,"CODOPE",svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          "MIROWID",svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_updazonidmenu(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdupdazonidmenu=abrecursordebug(UPDAZONIDMENU,1280);
    bindtodo(vdupdazonidmenu,"IDMENU",svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          "MIROWID",svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_updazonstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdupdazonstatus=abrecursordebug(UPDAZONSTATUS,1280);
    bindtodo(vdupdazonstatus,"STATUS",&svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          "MIROWID",svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_updazonprocesos(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdupdazonprocesos=abrecursordebug(UPDAZONPROCESOS,1280);
    bindtodo(vdupdazonprocesos,"STATUS",&svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          "PROCESOZONA",svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          "PROCESODISP",svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          "MIROWID",svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_inszon(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vdinszon=abrecursordebug(INSZON,1280);
    bindtodo(vdinszon,"CODZONA",&svdzonas.codzona,sizeof(svdzonas.codzona),V10LONG,
                          "DESZONA",svdzonas.deszona,sizeof(svdzonas.deszona),V10CADENA,
                          "TIPOZONA",svdzonas.tipozona,sizeof(svdzonas.tipozona),V10CADENA,
                          "ACTIVA",svdzonas.activa,sizeof(svdzonas.activa),V10CADENA,
                          "PRIOZONA",&svdzonas.priozona,sizeof(svdzonas.priozona),V10LONG,
                          "IDINFOGEST",&svdzonas.idinfogest,sizeof(svdzonas.idinfogest),V10LONG,
                          "IDINFOPICK",&svdzonas.idinfopick,sizeof(svdzonas.idinfopick),V10LONG,
                          "NUMDISP",&svdzonas.numdisp,sizeof(svdzonas.numdisp),V10LONG,
                          "MAXOPER",&svdzonas.maxoper,sizeof(svdzonas.maxoper),V10LONG,
                          "MAXBULTOSOPER",&svdzonas.maxbultosoper,sizeof(svdzonas.maxbultosoper),V10LONG,
                          "DISPILUMINADOS",&svdzonas.dispiluminados,sizeof(svdzonas.dispiluminados),V10LONG,
                          "REDSCAN",&svdzonas.redscan,sizeof(svdzonas.redscan),V10LONG,
                          "SCANNER",&svdzonas.scanner,sizeof(svdzonas.scanner),V10LONG,
                          "MAXCAPACIDAD",&svdzonas.maxcapacidad,sizeof(svdzonas.maxcapacidad),V10LONG,
                          "AUTOAPERTURA",svdzonas.autoapertura,sizeof(svdzonas.autoapertura),V10CADENA,
                          "TIEMPOOK",&svdzonas.tiempook,sizeof(svdzonas.tiempook),V10LONG,
                          "TIEMPOFIN",&svdzonas.tiempofin,sizeof(svdzonas.tiempofin),V10LONG,
                          "NEXTTICK",svdzonas.nexttick,sizeof(svdzonas.nexttick),V10CADENA,
                          "PRIVPICKING",svdzonas.privpicking,sizeof(svdzonas.privpicking),V10CADENA,
                          "PROCESOZONA",svdzonas.procesozona,sizeof(svdzonas.procesozona),V10CADENA,
                          "PROCESODISP",svdzonas.procesodisp,sizeof(svdzonas.procesodisp),V10CADENA,
                          "IDMENU",svdzonas.idmenu,sizeof(svdzonas.idmenu),V10CADENA,
                          "STATUS",&svdzonas.status,sizeof(svdzonas.status),V10LONG,
                          "CODOPE",svdzonas.codope,sizeof(svdzonas.codope),V10CADENA,
                          "VDEXTRA",svdzonas.vdextra,sizeof(svdzonas.vdextra),V10CADENA,
                          "CODCOMEN",&svdzonas.codcomen,sizeof(svdzonas.codcomen),V10LONG,
                          "RANGOTIPOVOL",svdzonas.rangotipovol,sizeof(svdzonas.rangotipovol),V10CADENA,
                          "CODMOV",&svdzonas.codmov,sizeof(svdzonas.codmov),V10LONG,
                          "NUMBASC",&svdzonas.numbasc,sizeof(svdzonas.numbasc),V10LONG,
                          "ACTIVABASC",svdzonas.activabasc,sizeof(svdzonas.activabasc),V10CADENA,
                          "CODIMPRE",svdzonas.codimpre,sizeof(svdzonas.codimpre),V10CADENA,
                          "CANTQUEDABASC",&svdzonas.cantquedabasc,sizeof(svdzonas.cantquedabasc),V10DOUBLE,
                          "MENUPRIN",&svdzonas.menuprin,sizeof(svdzonas.menuprin),V10LONG,
                          "DATOSMENU",svdzonas.datosmenu,sizeof(svdzonas.datosmenu),V10CADENA,
                          "TEXTOMENU",svdzonas.textomenu,sizeof(svdzonas.textomenu),V10CADENA,
                          "CAPACIDAD",&svdzonas.capacidad,sizeof(svdzonas.capacidad),V10LONG,
                          "COLORZONA",svdzonas.colorzona,sizeof(svdzonas.colorzona),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

static void init_delzon(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdzonas[0].numcol;nc++) dvdzonas[0].c[nc].offset-=(size_t)&svdzonas;
    vddelzon=abrecursordebug(DELZON,1280);
    bindtodo(vddelzon,"MIROWID",svdzonas.rowid,sizeof(svdzonas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_zon);
        init = 1;
    }
}

diccionario *ZONdamediccionario(void)
{
     return(&dzon);
}

int ZONselscanner(long redscan,long scanner,vdzonass *zon)
{
  int vdret;
  if (vdselzonscanner==NULL) init_selzonscanner();
  memset(&svdzonas,0,sizeof(svdzonas));
  svdzonas.redscan=redscan;
  svdzonas.scanner=scanner;
  vdret=ejefetchcursor(vdselzonscanner);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselzonscanner. vdret %d. \n",ZONlog(&svdzonas),vdret);
    return(VD_EERRORACLE);
   }
  *zon=svdzonas;
  return(vdret);
}

int ZONselnumdisp(long idinfopick,long numdisp,vdzonass *zon)
{
  int vdret;
  if (vdselzonnumdisp==NULL) init_selzonnumdisp();
  memset(&svdzonas,0,sizeof(svdzonas));
  svdzonas.idinfopick=idinfopick;
  svdzonas.numdisp=numdisp;
  vdret=ejefetchcursor(vdselzonnumdisp);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselzonnumdisp. vdret %d. \n",ZONlog(&svdzonas),vdret);
    return(VD_EERRORACLE);
   }
  *zon=svdzonas;
  return(vdret);
}

int ZONbuscatick(long idinfogest,vdzonass *zon)
{
  int vdret;
  memset(&svdzonas,0,sizeof(svdzonas));
  svdzonas.idinfogest=idinfogest;
  if (vdselzontick==NULL) init_selzontick();
  vdret=ejefetchcursor(vdselzontick);
  if (vdret==0) {
     *zon=svdzonas;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselzontick. vdret %d. \n",ZONlog(&svdzonas),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ZONnexttick(vdzonass *zon)
{
  int vdret;
  vdret=fetchcursor(vdselzontick);
  if (vdret==0) {
     *zon=svdzonas;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselzontick. vdret %d. \n",ZONlog(&svdzonas),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselzontick);
  return(VD_EERRORACLE);
}

int ZONselvdzonas(long codzona,vdzonass *zon)
{
  int vdret;
  if (vdselzonvdzonas==NULL) init_selzonvdzonas();
  memset(&svdzonas,0,sizeof(svdzonas));
  svdzonas.codzona=codzona;
  vdret=ejefetchcursor(vdselzonvdzonas);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselzonvdzonas. vdret %d. \n",ZONlog(&svdzonas),vdret);
    return(VD_EERRORACLE);
   }
  *zon=svdzonas;
  return(vdret);
}

int ZONactualizacodope(vdzonass *zon,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ZONactualizacodope:  %s .  \n",ZONlog(&svdzonas));
  if (vdupdazoncodope==NULL) init_updazoncodope();
  svdzonas=*zon;
  vdret=ejecutacursor(vdupdazoncodope);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdazoncodope);
     getcurerrornombre(vdupdazoncodope->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdazoncodope)!=1) return(VD_EERRORACLE);
  return(0);
}

int ZONactualizaidmenu(vdzonass *zon,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ZONactualizaidmenu:  %s .  \n",ZONlog(&svdzonas));
  if (vdupdazonidmenu==NULL) init_updazonidmenu();
  svdzonas=*zon;
  vdret=ejecutacursor(vdupdazonidmenu);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdazonidmenu);
     getcurerrornombre(vdupdazonidmenu->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdazonidmenu)!=1) return(VD_EERRORACLE);
  return(0);
}

int ZONactualizastatus(vdzonass *zon,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ZONactualizastatus:  %s .  \n",ZONlog(&svdzonas));
  if (vdupdazonstatus==NULL) init_updazonstatus();
  svdzonas=*zon;
  vdret=ejecutacursor(vdupdazonstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdazonstatus);
     getcurerrornombre(vdupdazonstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdazonstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int ZONactualizaprocesos(vdzonass *zon,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ZONactualizaprocesos:  %s .  \n",ZONlog(&svdzonas));
  if (vdupdazonprocesos==NULL) init_updazonprocesos();
  svdzonas=*zon;
  vdret=ejecutacursor(vdupdazonprocesos);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdazonprocesos);
     getcurerrornombre(vdupdazonprocesos->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdazonprocesos)!=1) return(VD_EERRORACLE);
  return(0);
}

int ZONinsert(vdzonass *zon,int error)
{
  int vdret;
  if (!vdinszon) init_inszon();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",ZONlog(&svdzonas));
  svdzonas=*zon;
  vdret=ejecutacursor(vdinszon);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinszon);
     getcurerrornombre(vdinszon->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ZONdel(vdzonass *zon,int error)
{
  int vdret;
  svdzonas=*zon;
  if (vddelzon==NULL) init_delzon();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",ZONlog(&svdzonas));
  vdret=ejecutacursor(vddelzon);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelzon);
     getcurerrornombre(vddelzon->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * ZONlog(vdzonass *zon)
{
    sprintf(msglogZON, "VDZONAS: codzona %ld ",zon->codzona);
    return(msglogZON);
}

char * ZONdebug(vdzonass *zon)
{
    debugestruct(&dzon,zon,msgdebugZON);
    return(msgdebugZON);
}

