// Modulo generado automaticamente a partir de VDLOTEBLOQ.DEF
//# M¢dulo : VDLOTEBLOQ.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDLOTEBLOQ
//#                        
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 07-09-2009                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=LBLO
//
//CLAVE=SEQBLOQ,SEQBLOQ
//RECORRE=STATUS,STATUS
//
//UPDATE=TRATADO, STATUS;
//
//SECUENCIA=VDSECLOTEBLOQ,SEQBLOQ
//
//INSERT
//LOCK
//INTERFASE
//ROWID

#include "vd.h"
#define SELLBLOSEQBLOQ "SELECT VDLOTEBLOQ.ROWID,VDLOTEBLOQ.SEQBLOQ,VDLOTEBLOQ.CODART, "\
                    " VDLOTEBLOQ.CODLOT,VDLOTEBLOQ.CANTIDAD,VDLOTEBLOQ.CODMAT, "\
                    " VDLOTEBLOQ.CODRECEP,VDLOTEBLOQ.BULTO,VDLOTEBLOQ.BLOQINI, "\
                    " VDLOTEBLOQ.BLOQFIN,VDLOTEBLOQ.TIPOBLOQ,VDLOTEBLOQ.STATUS, "\
                    " VDLOTEBLOQ.CODOPEMODIF,VDLOTEBLOQ.FECMODIF,VDLOTEBLOQ.HORAMODIF "\
        " FROM VDLOTEBLOQ"\
        " WHERE "\
               " VDLOTEBLOQ.SEQBLOQ=:SEQBLOQ "
static v10cursors *vdsellbloseqbloq;

#define SELLBLOSTATUS "SELECT VDLOTEBLOQ.ROWID,VDLOTEBLOQ.SEQBLOQ,VDLOTEBLOQ.CODART, "\
                    " VDLOTEBLOQ.CODLOT,VDLOTEBLOQ.CANTIDAD,VDLOTEBLOQ.CODMAT, "\
                    " VDLOTEBLOQ.CODRECEP,VDLOTEBLOQ.BULTO,VDLOTEBLOQ.BLOQINI, "\
                    " VDLOTEBLOQ.BLOQFIN,VDLOTEBLOQ.TIPOBLOQ,VDLOTEBLOQ.STATUS, "\
                    " VDLOTEBLOQ.CODOPEMODIF,VDLOTEBLOQ.FECMODIF,VDLOTEBLOQ.HORAMODIF "\
        " FROM VDLOTEBLOQ"\
        " WHERE "\
               " VDLOTEBLOQ.STATUS=:STATUS "
static v10cursors *vdsellblostatus;

#define SELLBLOROWID "SELECT VDLOTEBLOQ.ROWID,VDLOTEBLOQ.SEQBLOQ,VDLOTEBLOQ.CODART, "\
                    " VDLOTEBLOQ.CODLOT,VDLOTEBLOQ.CANTIDAD,VDLOTEBLOQ.CODMAT, "\
                    " VDLOTEBLOQ.CODRECEP,VDLOTEBLOQ.BULTO,VDLOTEBLOQ.BLOQINI, "\
                    " VDLOTEBLOQ.BLOQFIN,VDLOTEBLOQ.TIPOBLOQ,VDLOTEBLOQ.STATUS, "\
                    " VDLOTEBLOQ.CODOPEMODIF,VDLOTEBLOQ.FECMODIF,VDLOTEBLOQ.HORAMODIF "\
        " FROM VDLOTEBLOQ"\
        " WHERE "\
              " ROWID=:MIROWID "
static v10cursors *vdsellblorowid;

#define SELLBLOVDLOTEBLOQ "SELECT VDLOTEBLOQ.ROWID,VDLOTEBLOQ.SEQBLOQ,VDLOTEBLOQ.CODART, "\
                    " VDLOTEBLOQ.CODLOT,VDLOTEBLOQ.CANTIDAD,VDLOTEBLOQ.CODMAT, "\
                    " VDLOTEBLOQ.CODRECEP,VDLOTEBLOQ.BULTO,VDLOTEBLOQ.BLOQINI, "\
                    " VDLOTEBLOQ.BLOQFIN,VDLOTEBLOQ.TIPOBLOQ,VDLOTEBLOQ.STATUS, "\
                    " VDLOTEBLOQ.CODOPEMODIF,VDLOTEBLOQ.FECMODIF,VDLOTEBLOQ.HORAMODIF "\
        " FROM VDLOTEBLOQ"
static v10cursors *vdsellblovdlotebloq;

#define SELLBLOROWIDLOCK "SELECT ROWID,SEQBLOQ,CODART,CODLOT,CANTIDAD,CODMAT,CODRECEP, "\
                    " BULTO,BLOQINI,BLOQFIN,TIPOBLOQ,STATUS,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF "\
        " FROM VDLOTEBLOQ "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdsellblorowidlock;

#define UPDALBLOTRATADO "UPDATE VDLOTEBLOQ SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdalblotratado;

#define SELVDSECLOTEBLOQ "SELECT VDSECLOTEBLOQ.NEXTVAL FROM DUAL"
static v10cursors *vdselvdseclotebloq;

#define INSLBLO "INSERT INTO VDLOTEBLOQ (SEQBLOQ,CODART,CODLOT,CANTIDAD,CODMAT,CODRECEP, "\
                    " BULTO,BLOQINI,BLOQFIN,TIPOBLOQ,STATUS,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF "\
       " ) VALUES ( "\
                    " :SEQBLOQ,:CODART,:CODLOT,:CANTIDAD,:CODMAT,:CODRECEP, "\
                    " :BULTO,:BLOQINI,:BLOQFIN,:TIPOBLOQ,:STATUS,VDUSER.GETUSER,VD.FECHASYS, "\
                    " VD.HORASYS) "
static v10cursors *vdinslblo;

static vdlotebloqs svdlotebloq;

static diccols colvdlotebloq[]={
	{"ROWID",V10CADENA,(size_t)&svdlotebloq.rowid,sizeof(svdlotebloq.rowid)},
	{"SEQBLOQ",V10LONG,(size_t)&svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq)},
	{"CODART",V10CADENA,(size_t)&svdlotebloq.codart,sizeof(svdlotebloq.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdlotebloq.codlot,sizeof(svdlotebloq.codlot)},
	{"CANTIDAD",V10DOUBLE,(size_t)&svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad)},
	{"CODMAT",V10CADENA,(size_t)&svdlotebloq.codmat,sizeof(svdlotebloq.codmat)},
	{"CODRECEP",V10CADENA,(size_t)&svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep)},
	{"BULTO",V10CADENA,(size_t)&svdlotebloq.bulto,sizeof(svdlotebloq.bulto)},
	{"BLOQINI",V10CADENA,(size_t)&svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini)},
	{"BLOQFIN",V10CADENA,(size_t)&svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin)},
	{"TIPOBLOQ",V10CADENA,(size_t)&svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq)},
	{"STATUS",V10LONG,(size_t)&svdlotebloq.status,sizeof(svdlotebloq.status)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif)},
	};
static diccionarios dvdlotebloq[]={
    {colvdlotebloq,15}
};
diccionario dlblo={dvdlotebloq,1};

static char msglogLBLO[LCADENA];
static char msgdebugLBLO[LCADENABIG];
static int init=0;


static void fin_vd_lblo(void)
{
if (vdsellbloseqbloq) {
    liberacursor(vdsellbloseqbloq);
    vdsellbloseqbloq = NULL;
}
if (vdsellblostatus) {
    liberacursor(vdsellblostatus);
    vdsellblostatus = NULL;
}
if (vdsellblorowid) {
    liberacursor(vdsellblorowid);
    vdsellblorowid = NULL;
}
if (vdsellblovdlotebloq) {
    liberacursor(vdsellblovdlotebloq);
    vdsellblovdlotebloq = NULL;
}
if (vdsellblorowidlock) {
    liberacursor(vdsellblorowidlock);
    vdsellblorowidlock = NULL;
}
if (vdupdalblotratado) {
    liberacursor(vdupdalblotratado);
    vdupdalblotratado = NULL;
}
if (vdselvdseclotebloq != NULL) {
    liberacursor(vdselvdseclotebloq);
    vdselvdseclotebloq = NULL;
}
if (vdinslblo != NULL) {
    liberacursor(vdinslblo);
    vdinslblo = NULL;
}
}
static void init_sellbloseqbloq(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdsellbloseqbloq=abrecursordebug(SELLBLOSEQBLOQ,1280);
    definetodo(vdsellbloseqbloq,svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          &svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          &svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          &svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif),V10CADENA,
                          &svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif),V10LONG,
                          svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellbloseqbloq,"SEQBLOQ",&svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_sellblostatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdsellblostatus=abrecursordebug(SELLBLOSTATUS,1280);
    definetodo(vdsellblostatus,svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          &svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          &svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          &svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif),V10CADENA,
                          &svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif),V10LONG,
                          svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellblostatus,"STATUS",&svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_sellblorowid(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdsellblorowid=abrecursordebug(SELLBLOROWID,1280);
    definetodo(vdsellblorowid,svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          &svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          &svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          &svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif),V10CADENA,
                          &svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif),V10LONG,
                          svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellblorowid,"MIROWID",svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_sellblovdlotebloq(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdsellblovdlotebloq=abrecursordebug(SELLBLOVDLOTEBLOQ,1280);
    definetodo(vdsellblovdlotebloq,svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          &svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          &svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          &svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif),V10CADENA,
                          &svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif),V10LONG,
                          svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellblovdlotebloq,NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_sellblorowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdsellblorowidlock=abrecursordebug(SELLBLOROWIDLOCK,1280);
    definetodo(vdsellblorowidlock,svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          &svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          &svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          &svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          svdlotebloq.codopemodif,sizeof(svdlotebloq.codopemodif),V10CADENA,
                          &svdlotebloq.fecmodif,sizeof(svdlotebloq.fecmodif),V10LONG,
                          svdlotebloq.horamodif,sizeof(svdlotebloq.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellblorowidlock,"MIROWID",svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_updalblotratado(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdupdalblotratado=abrecursordebug(UPDALBLOTRATADO,1280);
    bindtodo(vdupdalblotratado,"STATUS",&svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          "MIROWID",svdlotebloq.rowid,sizeof(svdlotebloq.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_selvdseclotebloq(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdselvdseclotebloq=abrecursordebug(SELVDSECLOTEBLOQ,1280);
    definetodo(vdselvdseclotebloq,&svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

static void init_inslblo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotebloq[0].numcol;nc++) dvdlotebloq[0].c[nc].offset-=(size_t)&svdlotebloq;
    vdinslblo=abrecursordebug(INSLBLO,1280);
    bindtodo(vdinslblo,"SEQBLOQ",&svdlotebloq.seqbloq,sizeof(svdlotebloq.seqbloq),V10LONG,
                          "CODART",svdlotebloq.codart,sizeof(svdlotebloq.codart),V10CADENA,
                          "CODLOT",svdlotebloq.codlot,sizeof(svdlotebloq.codlot),V10CADENA,
                          "CANTIDAD",&svdlotebloq.cantidad,sizeof(svdlotebloq.cantidad),V10DOUBLE,
                          "CODMAT",svdlotebloq.codmat,sizeof(svdlotebloq.codmat),V10CADENA,
                          "CODRECEP",svdlotebloq.codrecep,sizeof(svdlotebloq.codrecep),V10CADENA,
                          "BULTO",svdlotebloq.bulto,sizeof(svdlotebloq.bulto),V10CADENA,
                          "BLOQINI",svdlotebloq.bloqini,sizeof(svdlotebloq.bloqini),V10CADENA,
                          "BLOQFIN",svdlotebloq.bloqfin,sizeof(svdlotebloq.bloqfin),V10CADENA,
                          "TIPOBLOQ",svdlotebloq.tipobloq,sizeof(svdlotebloq.tipobloq),V10CADENA,
                          "STATUS",&svdlotebloq.status,sizeof(svdlotebloq.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lblo);
        init = 1;
    }
}

diccionario *LBLOdamediccionario(void)
{
     return(&dlblo);
}

int LBLOselseqbloq(long seqbloq,vdlotebloqs *lblo)
{
  int vdret;
  if (vdsellbloseqbloq==NULL) init_sellbloseqbloq();
  memset(&svdlotebloq,0,sizeof(svdlotebloq));
  svdlotebloq.seqbloq=seqbloq;
  vdret=ejefetchcursor(vdsellbloseqbloq);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellbloseqbloq. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
    return(VD_EERRORACLE);
   }
  *lblo=svdlotebloq;
  return(vdret);
}

int LBLObuscastatus(long status,vdlotebloqs *lblo)
{
  int vdret;
  memset(&svdlotebloq,0,sizeof(svdlotebloq));
  svdlotebloq.status=status;
  if (vdsellblostatus==NULL) init_sellblostatus();
  vdret=ejefetchcursor(vdsellblostatus);
  if (vdret==0) {
     *lblo=svdlotebloq;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdsellblostatus. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int LBLOnextstatus(vdlotebloqs *lblo)
{
  int vdret;
  vdret=fetchcursor(vdsellblostatus);
  if (vdret==0) {
     *lblo=svdlotebloq;
    v10log(LOGDEBUGAPI,"Siguiente %s vdsellblostatus. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdsellblostatus);
  return(VD_EERRORACLE);
}

int LBLOselrowid(char *mirowid,vdlotebloqs *lblo)
{
  int vdret;
  if (vdsellblorowid==NULL) init_sellblorowid();
  memset(&svdlotebloq,0,sizeof(svdlotebloq));
  strcpy(svdlotebloq.rowid,mirowid);
  vdret=ejefetchcursor(vdsellblorowid);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellblorowid. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
    return(VD_EERRORACLE);
   }
  *lblo=svdlotebloq;
  return(vdret);
}

int LBLOselvdlotebloq(vdlotebloqs *lblo)
{
  int vdret;
  if (vdsellblovdlotebloq==NULL) init_sellblovdlotebloq();
  memset(&svdlotebloq,0,sizeof(svdlotebloq));
  vdret=ejefetchcursor(vdsellblovdlotebloq);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellblovdlotebloq. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
    return(VD_EERRORACLE);
   }
  *lblo=svdlotebloq;
  return(vdret);
}

int LBLOlock(vdlotebloqs *lblo,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdlotebloq=*lblo;
    if (vdsellblorowidlock==NULL) init_sellblorowidlock();
    savepoint("lockvdlotebloq");
    while (1) {
        vdret=ejefetchcursor(vdsellblorowidlock);
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
    vdret=vverificacampos(lblo,&svdlotebloq,&dvdlotebloq[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdlotebloq");
    return(vdret);
}

int LBLOactualizatratado(vdlotebloqs *lblo,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando LBLOactualizatratado:  %s .  \n",LBLOlog(&svdlotebloq));
  if (vdupdalblotratado==NULL) init_updalblotratado();
  svdlotebloq=*lblo;
  vdret=ejecutacursor(vdupdalblotratado);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdalblotratado);
     getcurerrornombre(vdupdalblotratado->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdalblotratado)!=1) return(VD_EERRORACLE);
  return(0);
}

int LBLOselvdseclotebloq(long *donde)
{
  int vdret;
  if (!vdselvdseclotebloq) init_selvdseclotebloq();
  vdret=ejefetchcursor(vdselvdseclotebloq);
  if (!vdret) {
     *donde=svdlotebloq.seqbloq;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int LBLOinsert(vdlotebloqs *lblo,int error)
{
  int vdret;
  if (!vdinslblo) init_inslblo();
  if (!lblo->seqbloq) {
     if ((vdret=LBLOselvdseclotebloq(&(lblo->seqbloq)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",LBLOlog(&svdlotebloq));
  svdlotebloq=*lblo;
  vdret=ejecutacursor(vdinslblo);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinslblo);
     getcurerrornombre(vdinslblo->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int LBLOinter(vdlotebloqs *lblo)
{
  int vdret = 0;
  if (vdsellblovdlotebloq==NULL) init_sellblovdlotebloq();
  memset(&svdlotebloq,0,sizeof(svdlotebloq));
  vdret=ejefetchcursor(vdsellblovdlotebloq);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellblovdlotebloq. vdret %d. \n",LBLOlog(&svdlotebloq),vdret);
    return(VD_EERRORACLE);
  }

  *lblo=svdlotebloq;
  return(vdret);
}

char * LBLOlog(vdlotebloqs *lblo)
{
    sprintf(msglogLBLO, "VDLOTEBLOQ: ");
    return(msglogLBLO);
}

char * LBLOdebug(vdlotebloqs *lblo)
{
    debugestruct(&dlblo,lblo,msgdebugLBLO);
    return(msgdebugLBLO);
}

