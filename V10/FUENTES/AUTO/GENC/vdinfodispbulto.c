// Modulo generado automaticamente a partir de VDINFODISPBULTO.DEF
//# Modulo : VDINFODISPBULTO.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFODISPBULTO
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 05-11-2010                                            
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IDB
//EXTRA=CODZONA,V10INT;
//
//RECORRE=STATUS,STATUS; 
//RECORRE=DISPSTATUS,IDINFOPICK,NUMDISP,STATUS;ORDERBY=FECMODIF,HORAMODIF; 
//RECORRE=DISPLAY,IDINFOPICK,NUMDISP; 
//RECORRE=CODZONA,TABLE=VDINFODISP;WHERE=VDINFODISP.CODZONA=:CODZONA AND VDINFODISP.IDINFOPICK=VDINFODISPBULTO.IDINFOPICK AND VDINFODISP.NUMDISP=VDINFODISPBULTO.NUMDISP; 
//RECORRE=BULTOZONA,CODBULTO,TABLE=VDZONAS;WHERE=VDZONAS.CODZONA=:CODZONA AND VDZONAS.IDINFOPICK=VDINFODISPBULTO.IDINFOPICK AND VDZONAS.NUMDISP=VDINFODISPBULTO.NUMDISP; 
//
//UPDATE=CODBULTO,CODBULTO
//UPDATE=STATUS,STATUS
//
//INSERT
//DELETE 
//LOCK

#include "vd.h"
#define SELIDBSTATUS "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO"\
        " WHERE "\
               " VDINFODISPBULTO.STATUS=:STATUS "
static v10cursors *vdselidbstatus;

#define SELIDBDISPSTATUS "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO"\
        " WHERE "\
               " VDINFODISPBULTO.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFODISPBULTO.NUMDISP=:NUMDISP "\
               " AND VDINFODISPBULTO.STATUS=:STATUS "\
        " ORDER BY FECMODIF,HORAMODIF "
static v10cursors *vdselidbdispstatus;

#define SELIDBDISPLAY "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO"\
        " WHERE "\
               " VDINFODISPBULTO.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFODISPBULTO.NUMDISP=:NUMDISP "
static v10cursors *vdselidbdisplay;

#define SELIDBCODZONA "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO ,VDINFODISP"\
        " WHERE "\
              " VDINFODISP.CODZONA=:CODZONA AND VDINFODISP.IDINFOPICK=VDINFODISPBULTO.IDINFOPICK AND VDINFODISP.NUMDISP=VDINFODISPBULTO.NUMDISP "
static v10cursors *vdselidbcodzona;

#define SELIDBBULTOZONA "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO ,VDZONAS"\
        " WHERE "\
               " VDINFODISPBULTO.CODBULTO=:CODBULTO "\
              "  AND VDZONAS.CODZONA=:CODZONA AND VDZONAS.IDINFOPICK=VDINFODISPBULTO.IDINFOPICK AND VDZONAS.NUMDISP=VDINFODISPBULTO.NUMDISP "
static v10cursors *vdselidbbultozona;

#define SELIDBVDINFODISPBULTO "SELECT VDINFODISPBULTO.ROWID,VDINFODISPBULTO.IDINFOPICK,VDINFODISPBULTO.NUMDISP, "\
                    " VDINFODISPBULTO.IDINFOGEST,VDINFODISPBULTO.CODBULTO,VDINFODISPBULTO.STATUS, "\
                    " VDINFODISPBULTO.VDEXTRA,VDINFODISPBULTO.CODCOMEN,VDINFODISPBULTO.CODOPEMODIF, "\
                    " VDINFODISPBULTO.FECMODIF,VDINFODISPBULTO.HORAMODIF "\
        " FROM VDINFODISPBULTO"
static v10cursors *vdselidbvdinfodispbulto;

#define SELIDBROWIDLOCK "SELECT ROWID,IDINFOPICK,NUMDISP,IDINFOGEST,CODBULTO,STATUS,VDEXTRA, "\
                    " CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
        " FROM VDINFODISPBULTO "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselidbrowidlock;

#define UPDAIDBCODBULTO "UPDATE VDINFODISPBULTO SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODBULTO=:CODBULTO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidbcodbulto;

#define UPDAIDBSTATUS "UPDATE VDINFODISPBULTO SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidbstatus;

#define INSIDB "INSERT INTO VDINFODISPBULTO (IDINFOPICK,NUMDISP,IDINFOGEST,CODBULTO,STATUS,VDEXTRA, "\
                    " CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :IDINFOPICK,:NUMDISP,:IDINFOGEST,:CODBULTO,:STATUS,:VDEXTRA, "\
                    " :CODCOMEN,VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS()) "
static v10cursors *vdinsidb;

#define DELIDB "DELETE VDINFODISPBULTO WHERE ROWID=:MIROWID "
static v10cursors *vddelidb;

static vdinfodispbultos svdinfodispbulto;

static diccols colvdinfodispbulto[]={
	{"ROWID",V10CADENA,(size_t)&svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid)},
	{"IDINFOPICK",V10LONG,(size_t)&svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick)},
	{"NUMDISP",V10LONG,(size_t)&svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp)},
	{"IDINFOGEST",V10LONG,(size_t)&svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest)},
	{"CODBULTO",V10CADENA,(size_t)&svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto)},
	{"STATUS",V10LONG,(size_t)&svdinfodispbulto.status,sizeof(svdinfodispbulto.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif)},
	{"CODZONA",V10LONG,(size_t)&svdinfodispbulto.codzona,sizeof(svdinfodispbulto.codzona)}
	};
static diccionarios dvdinfodispbulto[]={
    {colvdinfodispbulto,12}
};
diccionario didb={dvdinfodispbulto,1};

static char msglogIDB[LCADENA];
static char msgdebugIDB[LCADENABIG];
static int init=0;


static void fin_vd_idb(void)
{
if (vdselidbstatus) {
    liberacursor(vdselidbstatus);
    vdselidbstatus = NULL;
}
if (vdselidbdispstatus) {
    liberacursor(vdselidbdispstatus);
    vdselidbdispstatus = NULL;
}
if (vdselidbdisplay) {
    liberacursor(vdselidbdisplay);
    vdselidbdisplay = NULL;
}
if (vdselidbcodzona) {
    liberacursor(vdselidbcodzona);
    vdselidbcodzona = NULL;
}
if (vdselidbbultozona) {
    liberacursor(vdselidbbultozona);
    vdselidbbultozona = NULL;
}
if (vdselidbvdinfodispbulto) {
    liberacursor(vdselidbvdinfodispbulto);
    vdselidbvdinfodispbulto = NULL;
}
if (vdselidbrowidlock) {
    liberacursor(vdselidbrowidlock);
    vdselidbrowidlock = NULL;
}
if (vdupdaidbcodbulto) {
    liberacursor(vdupdaidbcodbulto);
    vdupdaidbcodbulto = NULL;
}
if (vdupdaidbstatus) {
    liberacursor(vdupdaidbstatus);
    vdupdaidbstatus = NULL;
}
if (vdinsidb != NULL) {
    liberacursor(vdinsidb);
    vdinsidb = NULL;
}
if (vddelidb != NULL) {
    liberacursor(vddelidb);
    vddelidb = NULL;
}
}
static void init_selidbstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbstatus=abrecursordebug(SELIDBSTATUS,1280);
    definetodo(vdselidbstatus,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbstatus,"STATUS",&svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbdispstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbdispstatus=abrecursordebug(SELIDBDISPSTATUS,1280);
    definetodo(vdselidbdispstatus,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbdispstatus,"IDINFOPICK",&svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          "NUMDISP",&svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          "STATUS",&svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbdisplay(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbdisplay=abrecursordebug(SELIDBDISPLAY,1280);
    definetodo(vdselidbdisplay,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbdisplay,"IDINFOPICK",&svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          "NUMDISP",&svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbcodzona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbcodzona=abrecursordebug(SELIDBCODZONA,1280);
    definetodo(vdselidbcodzona,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbcodzona,"CODZONA",&svdinfodispbulto.codzona,sizeof(svdinfodispbulto.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbbultozona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbbultozona=abrecursordebug(SELIDBBULTOZONA,1280);
    definetodo(vdselidbbultozona,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbbultozona,"CODBULTO",svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          "CODZONA",&svdinfodispbulto.codzona,sizeof(svdinfodispbulto.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbvdinfodispbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbvdinfodispbulto=abrecursordebug(SELIDBVDINFODISPBULTO,1280);
    definetodo(vdselidbvdinfodispbulto,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbvdinfodispbulto,NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_selidbrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdselidbrowidlock=abrecursordebug(SELIDBROWIDLOCK,1280);
    definetodo(vdselidbrowidlock,svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          &svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          &svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          &svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          &svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          &svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          svdinfodispbulto.codopemodif,sizeof(svdinfodispbulto.codopemodif),V10CADENA,
                          &svdinfodispbulto.fecmodif,sizeof(svdinfodispbulto.fecmodif),V10LONG,
                          svdinfodispbulto.horamodif,sizeof(svdinfodispbulto.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselidbrowidlock,"MIROWID",svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_updaidbcodbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdupdaidbcodbulto=abrecursordebug(UPDAIDBCODBULTO,1280);
    bindtodo(vdupdaidbcodbulto,"CODBULTO",svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          "MIROWID",svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_updaidbstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdupdaidbstatus=abrecursordebug(UPDAIDBSTATUS,1280);
    bindtodo(vdupdaidbstatus,"STATUS",&svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          "MIROWID",svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_insidb(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vdinsidb=abrecursordebug(INSIDB,1280);
    bindtodo(vdinsidb,"IDINFOPICK",&svdinfodispbulto.idinfopick,sizeof(svdinfodispbulto.idinfopick),V10LONG,
                          "NUMDISP",&svdinfodispbulto.numdisp,sizeof(svdinfodispbulto.numdisp),V10LONG,
                          "IDINFOGEST",&svdinfodispbulto.idinfogest,sizeof(svdinfodispbulto.idinfogest),V10LONG,
                          "CODBULTO",svdinfodispbulto.codbulto,sizeof(svdinfodispbulto.codbulto),V10CADENA,
                          "STATUS",&svdinfodispbulto.status,sizeof(svdinfodispbulto.status),V10LONG,
                          "VDEXTRA",svdinfodispbulto.vdextra,sizeof(svdinfodispbulto.vdextra),V10CADENA,
                          "CODCOMEN",&svdinfodispbulto.codcomen,sizeof(svdinfodispbulto.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

static void init_delidb(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodispbulto[0].numcol;nc++) dvdinfodispbulto[0].c[nc].offset-=(size_t)&svdinfodispbulto;
    vddelidb=abrecursordebug(DELIDB,1280);
    bindtodo(vddelidb,"MIROWID",svdinfodispbulto.rowid,sizeof(svdinfodispbulto.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idb);
        init = 1;
    }
}

diccionario *IDBdamediccionario(void)
{
     return(&didb);
}

int IDBbuscastatus(long status,vdinfodispbultos *idb)
{
  int vdret;
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  svdinfodispbulto.status=status;
  if (vdselidbstatus==NULL) init_selidbstatus();
  vdret=ejefetchcursor(vdselidbstatus);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidbstatus. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDBnextstatus(vdinfodispbultos *idb)
{
  int vdret;
  vdret=fetchcursor(vdselidbstatus);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidbstatus. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidbstatus);
  return(VD_EERRORACLE);
}

int IDBbuscadispstatus(long idinfopick,long numdisp,long status,vdinfodispbultos *idb)
{
  int vdret;
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  svdinfodispbulto.idinfopick=idinfopick;
  svdinfodispbulto.numdisp=numdisp;
  svdinfodispbulto.status=status;
  if (vdselidbdispstatus==NULL) init_selidbdispstatus();
  vdret=ejefetchcursor(vdselidbdispstatus);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidbdispstatus. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDBnextdispstatus(vdinfodispbultos *idb)
{
  int vdret;
  vdret=fetchcursor(vdselidbdispstatus);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidbdispstatus. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidbdispstatus);
  return(VD_EERRORACLE);
}

int IDBbuscadisplay(long idinfopick,long numdisp,vdinfodispbultos *idb)
{
  int vdret;
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  svdinfodispbulto.idinfopick=idinfopick;
  svdinfodispbulto.numdisp=numdisp;
  if (vdselidbdisplay==NULL) init_selidbdisplay();
  vdret=ejefetchcursor(vdselidbdisplay);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidbdisplay. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDBnextdisplay(vdinfodispbultos *idb)
{
  int vdret;
  vdret=fetchcursor(vdselidbdisplay);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidbdisplay. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidbdisplay);
  return(VD_EERRORACLE);
}

int IDBbuscacodzona(long codzona,vdinfodispbultos *idb)
{
  int vdret;
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  svdinfodispbulto.codzona=codzona;
  if (vdselidbcodzona==NULL) init_selidbcodzona();
  vdret=ejefetchcursor(vdselidbcodzona);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidbcodzona. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDBnextcodzona(vdinfodispbultos *idb)
{
  int vdret;
  vdret=fetchcursor(vdselidbcodzona);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidbcodzona. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidbcodzona);
  return(VD_EERRORACLE);
}

int IDBbuscabultozona(char *codbulto,long codzona,vdinfodispbultos *idb)
{
  int vdret;
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  strcpy(svdinfodispbulto.codbulto,codbulto);
  svdinfodispbulto.codzona=codzona;
  if (vdselidbbultozona==NULL) init_selidbbultozona();
  vdret=ejefetchcursor(vdselidbbultozona);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidbbultozona. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDBnextbultozona(vdinfodispbultos *idb)
{
  int vdret;
  vdret=fetchcursor(vdselidbbultozona);
  if (vdret==0) {
     *idb=svdinfodispbulto;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidbbultozona. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidbbultozona);
  return(VD_EERRORACLE);
}

int IDBselvdinfodispbulto(vdinfodispbultos *idb)
{
  int vdret;
  if (vdselidbvdinfodispbulto==NULL) init_selidbvdinfodispbulto();
  memset(&svdinfodispbulto,0,sizeof(svdinfodispbulto));
  vdret=ejefetchcursor(vdselidbvdinfodispbulto);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselidbvdinfodispbulto. vdret %d. \n",IDBlog(&svdinfodispbulto),vdret);
    return(VD_EERRORACLE);
   }
  *idb=svdinfodispbulto;
  return(vdret);
}

int IDBlock(vdinfodispbultos *idb,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdinfodispbulto=*idb;
    if (vdselidbrowidlock==NULL) init_selidbrowidlock();
    savepoint("lockvdinfodispbulto");
    while (1) {
        vdret=ejefetchcursor(vdselidbrowidlock);
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
    vdret=vverificacampos(idb,&svdinfodispbulto,&dvdinfodispbulto[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdinfodispbulto");
    return(vdret);
}

int IDBactualizacodbulto(vdinfodispbultos *idb,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDBactualizacodbulto:  %s .  \n",IDBlog(&svdinfodispbulto));
  if (vdupdaidbcodbulto==NULL) init_updaidbcodbulto();
  svdinfodispbulto=*idb;
  vdret=ejecutacursor(vdupdaidbcodbulto);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidbcodbulto);
     getcurerrornombre(vdupdaidbcodbulto->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidbcodbulto)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDBactualizastatus(vdinfodispbultos *idb,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDBactualizastatus:  %s .  \n",IDBlog(&svdinfodispbulto));
  if (vdupdaidbstatus==NULL) init_updaidbstatus();
  svdinfodispbulto=*idb;
  vdret=ejecutacursor(vdupdaidbstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidbstatus);
     getcurerrornombre(vdupdaidbstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidbstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDBinsert(vdinfodispbultos *idb,int error)
{
  int vdret;
  if (!vdinsidb) init_insidb();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",IDBlog(&svdinfodispbulto));
  svdinfodispbulto=*idb;
  vdret=ejecutacursor(vdinsidb);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsidb);
     getcurerrornombre(vdinsidb->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int IDBdel(vdinfodispbultos *idb,int error)
{
  int vdret;
  svdinfodispbulto=*idb;
  if (vddelidb==NULL) init_delidb();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",IDBlog(&svdinfodispbulto));
  vdret=ejecutacursor(vddelidb);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelidb);
     getcurerrornombre(vddelidb->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * IDBlog(vdinfodispbultos *idb)
{
    sprintf(msglogIDB, "VDINFODISPBULTO: ");
    return(msglogIDB);
}

char * IDBdebug(vdinfodispbultos *idb)
{
    debugestruct(&didb,idb,msgdebugIDB);
    return(msgdebugIDB);
}

