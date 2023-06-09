// Modulo generado automaticamente a partir de VDINFOHARDDISP.DEF
//# Modulo : VDINFOHARDDISP.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFOHARDDISP
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 14-01-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IHD
//EXTRA=RANGOLINEAS,V10CADENA,255
//RECORRE=STATUS,IDINFOPICK,STATUS
//RECORRE=RANGO,IDINFOPICK,STATUS,WHERE VD.CONTIENENUM(:RANGOLINEAS,MOD(FLOOR(NUMDISP/1000),100))>0;
//RECORRE=DISPMIRROR,IDINFOPICKM,NUMDISPM
//RECORRE=TECLAS,IDINFOGEST,WHERE=TECLAS>CHR(1);
//UPDATE=STATUS,STATUS
//UPDATE=STYTEXTO,STATUS,TEXTO,LUCES
//UPDATE=TECLAS,TECLAS
//#INSERT
//LOCK

#include "vd.h"
#define SELIHDSTATUS "SELECT VDINFOHARDDISP.ROWID,VDINFOHARDDISP.IDINFOPICK,VDINFOHARDDISP.NUMDISP, "\
                    " VDINFOHARDDISP.IDINFOGEST,VDINFOHARDDISP.TEXTO,VDINFOHARDDISP.LUCES, "\
                    " VDINFOHARDDISP.TECLAS,VDINFOHARDDISP.STATUS,VDINFOHARDDISP.VDEXTRA, "\
                    " VDINFOHARDDISP.CODOPEMODIF,VDINFOHARDDISP.FECMODIF,VDINFOHARDDISP.HORAMODIF, "\
                    " VDINFOHARDDISP.IDINFOPICKM,VDINFOHARDDISP.NUMDISPM,VDINFOHARDDISP.CODCOMEN, "\
                    " VDINFOHARDDISP.ESTADOBOT "\
        " FROM VDINFOHARDDISP"\
        " WHERE "\
               " VDINFOHARDDISP.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFOHARDDISP.STATUS=:STATUS "
static v10cursors *vdselihdstatus;

#define SELIHDRANGO "SELECT VDINFOHARDDISP.ROWID,VDINFOHARDDISP.IDINFOPICK,VDINFOHARDDISP.NUMDISP, "\
                    " VDINFOHARDDISP.IDINFOGEST,VDINFOHARDDISP.TEXTO,VDINFOHARDDISP.LUCES, "\
                    " VDINFOHARDDISP.TECLAS,VDINFOHARDDISP.STATUS,VDINFOHARDDISP.VDEXTRA, "\
                    " VDINFOHARDDISP.CODOPEMODIF,VDINFOHARDDISP.FECMODIF,VDINFOHARDDISP.HORAMODIF, "\
                    " VDINFOHARDDISP.IDINFOPICKM,VDINFOHARDDISP.NUMDISPM,VDINFOHARDDISP.CODCOMEN, "\
                    " VDINFOHARDDISP.ESTADOBOT "\
        " FROM VDINFOHARDDISP"\
        " WHERE "\
               " VDINFOHARDDISP.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFOHARDDISP.STATUS=:STATUS "\
              "  AND VD.CONTIENENUM(:RANGOLINEAS,MOD(FLOOR(NUMDISP/1000),100))>0 "
static v10cursors *vdselihdrango;

#define SELIHDDISPMIRROR "SELECT VDINFOHARDDISP.ROWID,VDINFOHARDDISP.IDINFOPICK,VDINFOHARDDISP.NUMDISP, "\
                    " VDINFOHARDDISP.IDINFOGEST,VDINFOHARDDISP.TEXTO,VDINFOHARDDISP.LUCES, "\
                    " VDINFOHARDDISP.TECLAS,VDINFOHARDDISP.STATUS,VDINFOHARDDISP.VDEXTRA, "\
                    " VDINFOHARDDISP.CODOPEMODIF,VDINFOHARDDISP.FECMODIF,VDINFOHARDDISP.HORAMODIF, "\
                    " VDINFOHARDDISP.IDINFOPICKM,VDINFOHARDDISP.NUMDISPM,VDINFOHARDDISP.CODCOMEN, "\
                    " VDINFOHARDDISP.ESTADOBOT "\
        " FROM VDINFOHARDDISP"\
        " WHERE "\
               " VDINFOHARDDISP.IDINFOPICKM=:IDINFOPICKM "\
               " AND VDINFOHARDDISP.NUMDISPM=:NUMDISPM "
static v10cursors *vdselihddispmirror;

#define SELIHDTECLAS "SELECT VDINFOHARDDISP.ROWID,VDINFOHARDDISP.IDINFOPICK,VDINFOHARDDISP.NUMDISP, "\
                    " VDINFOHARDDISP.IDINFOGEST,VDINFOHARDDISP.TEXTO,VDINFOHARDDISP.LUCES, "\
                    " VDINFOHARDDISP.TECLAS,VDINFOHARDDISP.STATUS,VDINFOHARDDISP.VDEXTRA, "\
                    " VDINFOHARDDISP.CODOPEMODIF,VDINFOHARDDISP.FECMODIF,VDINFOHARDDISP.HORAMODIF, "\
                    " VDINFOHARDDISP.IDINFOPICKM,VDINFOHARDDISP.NUMDISPM,VDINFOHARDDISP.CODCOMEN, "\
                    " VDINFOHARDDISP.ESTADOBOT "\
        " FROM VDINFOHARDDISP"\
        " WHERE "\
               " VDINFOHARDDISP.IDINFOGEST=:IDINFOGEST "\
              "  AND TECLAS>CHR(1) "
static v10cursors *vdselihdteclas;

#define SELIHDVDINFOHARDDISP "SELECT VDINFOHARDDISP.ROWID,VDINFOHARDDISP.IDINFOPICK,VDINFOHARDDISP.NUMDISP, "\
                    " VDINFOHARDDISP.IDINFOGEST,VDINFOHARDDISP.TEXTO,VDINFOHARDDISP.LUCES, "\
                    " VDINFOHARDDISP.TECLAS,VDINFOHARDDISP.STATUS,VDINFOHARDDISP.VDEXTRA, "\
                    " VDINFOHARDDISP.CODOPEMODIF,VDINFOHARDDISP.FECMODIF,VDINFOHARDDISP.HORAMODIF, "\
                    " VDINFOHARDDISP.IDINFOPICKM,VDINFOHARDDISP.NUMDISPM,VDINFOHARDDISP.CODCOMEN, "\
                    " VDINFOHARDDISP.ESTADOBOT "\
        " FROM VDINFOHARDDISP"\
        " WHERE "\
               " VDINFOHARDDISP.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFOHARDDISP.NUMDISP=:NUMDISP "
static v10cursors *vdselihdvdinfoharddisp;

#define SELIHDROWIDLOCK "SELECT ROWID,IDINFOPICK,NUMDISP,IDINFOGEST,TEXTO,LUCES,TECLAS, "\
                    " STATUS,VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF,IDINFOPICKM,NUMDISPM, "\
                    " CODCOMEN,ESTADOBOT "\
        " FROM VDINFOHARDDISP "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselihdrowidlock;

#define UPDAIHDSTATUS "UPDATE VDINFOHARDDISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaihdstatus;

#define UPDAIHDSTYTEXTO "UPDATE VDINFOHARDDISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS , "\
               " TEXTO=:TEXTO , "\
               " LUCES=:LUCES  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaihdstytexto;

#define UPDAIHDTECLAS "UPDATE VDINFOHARDDISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " TECLAS=:TECLAS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaihdteclas;

static vdinfoharddisps svdinfoharddisp;

static diccols colvdinfoharddisp[]={
	{"ROWID",V10CADENA,(size_t)&svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid)},
	{"IDINFOPICK",V10LONG,(size_t)&svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick)},
	{"NUMDISP",V10LONG,(size_t)&svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp)},
	{"IDINFOGEST",V10LONG,(size_t)&svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest)},
	{"TEXTO",V10CADENA,(size_t)&svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto)},
	{"LUCES",V10CADENA,(size_t)&svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces)},
	{"TECLAS",V10CADENA,(size_t)&svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas)},
	{"STATUS",V10LONG,(size_t)&svdinfoharddisp.status,sizeof(svdinfoharddisp.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif)},
	{"IDINFOPICKM",V10LONG,(size_t)&svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm)},
	{"NUMDISPM",V10LONG,(size_t)&svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen)},
	{"ESTADOBOT",V10LONG,(size_t)&svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot)},
	{"RANGOLINEAS",V10CADENA,(size_t)&svdinfoharddisp.rangolineas,sizeof(svdinfoharddisp.rangolineas)}
	};
static diccionarios dvdinfoharddisp[]={
    {colvdinfoharddisp,17}
};
diccionario dihd={dvdinfoharddisp,1};

static char msglogIHD[LCADENA];
static char msgdebugIHD[LCADENABIG];
static int init=0;


static void fin_vd_ihd(void)
{
if (vdselihdstatus) {
    liberacursor(vdselihdstatus);
    vdselihdstatus = NULL;
}
if (vdselihdrango) {
    liberacursor(vdselihdrango);
    vdselihdrango = NULL;
}
if (vdselihddispmirror) {
    liberacursor(vdselihddispmirror);
    vdselihddispmirror = NULL;
}
if (vdselihdteclas) {
    liberacursor(vdselihdteclas);
    vdselihdteclas = NULL;
}
if (vdselihdvdinfoharddisp) {
    liberacursor(vdselihdvdinfoharddisp);
    vdselihdvdinfoharddisp = NULL;
}
if (vdselihdrowidlock) {
    liberacursor(vdselihdrowidlock);
    vdselihdrowidlock = NULL;
}
if (vdupdaihdstatus) {
    liberacursor(vdupdaihdstatus);
    vdupdaihdstatus = NULL;
}
if (vdupdaihdstytexto) {
    liberacursor(vdupdaihdstytexto);
    vdupdaihdstytexto = NULL;
}
if (vdupdaihdteclas) {
    liberacursor(vdupdaihdteclas);
    vdupdaihdteclas = NULL;
}
}
static void init_selihdstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihdstatus=abrecursordebug(SELIHDSTATUS,1280);
    definetodo(vdselihdstatus,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihdstatus,"IDINFOPICK",&svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          "STATUS",&svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_selihdrango(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihdrango=abrecursordebug(SELIHDRANGO,1280);
    definetodo(vdselihdrango,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihdrango,"IDINFOPICK",&svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          "STATUS",&svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          "RANGOLINEAS",svdinfoharddisp.rangolineas,sizeof(svdinfoharddisp.rangolineas),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_selihddispmirror(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihddispmirror=abrecursordebug(SELIHDDISPMIRROR,1280);
    definetodo(vdselihddispmirror,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihddispmirror,"IDINFOPICKM",&svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          "NUMDISPM",&svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_selihdteclas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihdteclas=abrecursordebug(SELIHDTECLAS,1280);
    definetodo(vdselihdteclas,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihdteclas,"IDINFOGEST",&svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_selihdvdinfoharddisp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihdvdinfoharddisp=abrecursordebug(SELIHDVDINFOHARDDISP,1280);
    definetodo(vdselihdvdinfoharddisp,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihdvdinfoharddisp,"IDINFOPICK",&svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          "NUMDISP",&svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_selihdrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdselihdrowidlock=abrecursordebug(SELIHDROWIDLOCK,1280);
    definetodo(vdselihdrowidlock,svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          &svdinfoharddisp.idinfopick,sizeof(svdinfoharddisp.idinfopick),V10LONG,
                          &svdinfoharddisp.numdisp,sizeof(svdinfoharddisp.numdisp),V10LONG,
                          &svdinfoharddisp.idinfogest,sizeof(svdinfoharddisp.idinfogest),V10LONG,
                          svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          &svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          svdinfoharddisp.vdextra,sizeof(svdinfoharddisp.vdextra),V10CADENA,
                          svdinfoharddisp.codopemodif,sizeof(svdinfoharddisp.codopemodif),V10CADENA,
                          &svdinfoharddisp.fecmodif,sizeof(svdinfoharddisp.fecmodif),V10LONG,
                          svdinfoharddisp.horamodif,sizeof(svdinfoharddisp.horamodif),V10CADENA,
                          &svdinfoharddisp.idinfopickm,sizeof(svdinfoharddisp.idinfopickm),V10LONG,
                          &svdinfoharddisp.numdispm,sizeof(svdinfoharddisp.numdispm),V10LONG,
                          &svdinfoharddisp.codcomen,sizeof(svdinfoharddisp.codcomen),V10LONG,
                          &svdinfoharddisp.estadobot,sizeof(svdinfoharddisp.estadobot),V10LONG,
                          NULL);
    bindtodo(vdselihdrowidlock,"MIROWID",svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_updaihdstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdupdaihdstatus=abrecursordebug(UPDAIHDSTATUS,1280);
    bindtodo(vdupdaihdstatus,"STATUS",&svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          "MIROWID",svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_updaihdstytexto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdupdaihdstytexto=abrecursordebug(UPDAIHDSTYTEXTO,1280);
    bindtodo(vdupdaihdstytexto,"STATUS",&svdinfoharddisp.status,sizeof(svdinfoharddisp.status),V10LONG,
                          "TEXTO",svdinfoharddisp.texto,sizeof(svdinfoharddisp.texto),V10CADENA,
                          "LUCES",svdinfoharddisp.luces,sizeof(svdinfoharddisp.luces),V10CADENA,
                          "MIROWID",svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

static void init_updaihdteclas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoharddisp[0].numcol;nc++) dvdinfoharddisp[0].c[nc].offset-=(size_t)&svdinfoharddisp;
    vdupdaihdteclas=abrecursordebug(UPDAIHDTECLAS,1280);
    bindtodo(vdupdaihdteclas,"TECLAS",svdinfoharddisp.teclas,sizeof(svdinfoharddisp.teclas),V10CADENA,
                          "MIROWID",svdinfoharddisp.rowid,sizeof(svdinfoharddisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ihd);
        init = 1;
    }
}

diccionario *IHDdamediccionario(void)
{
     return(&dihd);
}

int IHDbuscastatus(long idinfopick,long status,vdinfoharddisps *ihd)
{
  int vdret;
  memset(&svdinfoharddisp,0,sizeof(svdinfoharddisp));
  svdinfoharddisp.idinfopick=idinfopick;
  svdinfoharddisp.status=status;
  if (vdselihdstatus==NULL) init_selihdstatus();
  vdret=ejefetchcursor(vdselihdstatus);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselihdstatus. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IHDnextstatus(vdinfoharddisps *ihd)
{
  int vdret;
  vdret=fetchcursor(vdselihdstatus);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselihdstatus. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselihdstatus);
  return(VD_EERRORACLE);
}

int IHDbuscarango(long idinfopick,long status,char *rangolineas,vdinfoharddisps *ihd)
{
  int vdret;
  memset(&svdinfoharddisp,0,sizeof(svdinfoharddisp));
  svdinfoharddisp.idinfopick=idinfopick;
  svdinfoharddisp.status=status;
  strcpy(svdinfoharddisp.rangolineas,rangolineas);
  if (vdselihdrango==NULL) init_selihdrango();
  vdret=ejefetchcursor(vdselihdrango);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselihdrango. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IHDnextrango(vdinfoharddisps *ihd)
{
  int vdret;
  vdret=fetchcursor(vdselihdrango);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselihdrango. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselihdrango);
  return(VD_EERRORACLE);
}

int IHDbuscadispmirror(long idinfopickm,long numdispm,vdinfoharddisps *ihd)
{
  int vdret;
  memset(&svdinfoharddisp,0,sizeof(svdinfoharddisp));
  svdinfoharddisp.idinfopickm=idinfopickm;
  svdinfoharddisp.numdispm=numdispm;
  if (vdselihddispmirror==NULL) init_selihddispmirror();
  vdret=ejefetchcursor(vdselihddispmirror);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselihddispmirror. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IHDnextdispmirror(vdinfoharddisps *ihd)
{
  int vdret;
  vdret=fetchcursor(vdselihddispmirror);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselihddispmirror. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselihddispmirror);
  return(VD_EERRORACLE);
}

int IHDbuscateclas(long idinfogest,vdinfoharddisps *ihd)
{
  int vdret;
  memset(&svdinfoharddisp,0,sizeof(svdinfoharddisp));
  svdinfoharddisp.idinfogest=idinfogest;
  if (vdselihdteclas==NULL) init_selihdteclas();
  vdret=ejefetchcursor(vdselihdteclas);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselihdteclas. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IHDnextteclas(vdinfoharddisps *ihd)
{
  int vdret;
  vdret=fetchcursor(vdselihdteclas);
  if (vdret==0) {
     *ihd=svdinfoharddisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselihdteclas. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselihdteclas);
  return(VD_EERRORACLE);
}

int IHDselvdinfoharddisp(long idinfopick,long numdisp,vdinfoharddisps *ihd)
{
  int vdret;
  if (vdselihdvdinfoharddisp==NULL) init_selihdvdinfoharddisp();
  memset(&svdinfoharddisp,0,sizeof(svdinfoharddisp));
  svdinfoharddisp.idinfopick=idinfopick;
  svdinfoharddisp.numdisp=numdisp;
  vdret=ejefetchcursor(vdselihdvdinfoharddisp);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselihdvdinfoharddisp. vdret %d. \n",IHDlog(&svdinfoharddisp),vdret);
    return(VD_EERRORACLE);
   }
  *ihd=svdinfoharddisp;
  return(vdret);
}

int IHDlock(vdinfoharddisps *ihd,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdinfoharddisp=*ihd;
    if (vdselihdrowidlock==NULL) init_selihdrowidlock();
 //   savepoint("lockvdinfoharddisp");
    while (1) {
        vdret=ejefetchcursor(vdselihdrowidlock);
        if (vdret==0) break;
        if (vdret==BLOQUEADO && wait) {
           Sleep(1000);
           if (hay_tecla()) if (tecla()==esc) return(VD_EERRBLOQUEO);
           continue;
         } else {
           if (wait==0) return(VD_EERRBLOQUEO);
         }
    }
    if (vdret) return(VD_EERRORACLE);
    if (verificar==0) return(vdret);
    va_start(arg,verificar);
    vdret=vverificacampos(ihd,&svdinfoharddisp,&dvdinfoharddisp[0],arg);
    va_end(arg);
   // if (vdret!=0) rollbacksavepoint("lockvdinfoharddisp");
    return(vdret);
}

int IHDactualizastatus(vdinfoharddisps *ihd,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IHDactualizastatus:  %s .  \n",IHDlog(&svdinfoharddisp));
  if (vdupdaihdstatus==NULL) init_updaihdstatus();
  svdinfoharddisp=*ihd;
  vdret=ejecutacursor(vdupdaihdstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaihdstatus);
     getcurerrornombre(vdupdaihdstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaihdstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int IHDactualizastytexto(vdinfoharddisps *ihd,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IHDactualizastytexto:  %s .  \n",IHDlog(&svdinfoharddisp));
  if (vdupdaihdstytexto==NULL) init_updaihdstytexto();
  svdinfoharddisp=*ihd;
  vdret=ejecutacursor(vdupdaihdstytexto);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaihdstytexto);
     getcurerrornombre(vdupdaihdstytexto->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaihdstytexto)!=1) return(VD_EERRORACLE);
  return(0);
}

int IHDactualizateclas(vdinfoharddisps *ihd,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IHDactualizateclas:  %s .  \n",IHDlog(&svdinfoharddisp));
  if (vdupdaihdteclas==NULL) init_updaihdteclas();
  svdinfoharddisp=*ihd;
  vdret=ejecutacursor(vdupdaihdteclas);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaihdteclas);
     getcurerrornombre(vdupdaihdteclas->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaihdteclas)!=1) return(VD_EERRORACLE);
  return(0);
}

char * IHDlog(vdinfoharddisps *ihd)
{
    sprintf(msglogIHD, "VDINFOHARDDISP: idinfopick %ld numdisp %ld ",ihd->idinfopick,ihd->numdisp);
    return(msglogIHD);
}

char * IHDdebug(vdinfoharddisps *ihd)
{
    debugestruct(&dihd,ihd,msgdebugIHD);
    return(msgdebugIHD);
}

