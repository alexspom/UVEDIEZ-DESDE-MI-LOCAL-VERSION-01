// Modulo generado automaticamente a partir de VDBULTOCABPINV.DEF
//#***
//# VDBULTOCABPINV.DEF - Generaci�n autom�tica del c�digo c para la tabla de Cabecera de Bulto de picking inverso.                                                      
//# 
//# Prop�sito: Funciones de acceso a la tabla VDBULTOCABPINV
//#           
//# Autor	 : JCSR
//# Revisado por: 
//# Fecha  : 30-05-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=BPC
//
//CLAVE=CODMAT,CODMAT
//RECORRE=STATUS,STATUS
//RECORRE=CODMATACTIVA,CODMAT,STATUS
//UPDATE=STATUS,STATUS
//
//LOCK

#include "vd.h"
#define SELBPCCODMAT "SELECT VDBULTOCABPINV.ROWID,VDBULTOCABPINV.CODBULTO,VDBULTOCABPINV.CODMAT, "\
                    " VDBULTOCABPINV.CAJACOMPLETA,VDBULTOCABPINV.FECCREADO,VDBULTOCABPINV.HORACREADO, "\
                    " VDBULTOCABPINV.FECFINALIZA,VDBULTOCABPINV.HORAFINALIZA,VDBULTOCABPINV.STATUS, "\
                    " VDBULTOCABPINV.VDEXTRA,VDBULTOCABPINV.CODCOMEN,VDBULTOCABPINV.CODOPEMODIF, "\
                    " VDBULTOCABPINV.FECMODIF,VDBULTOCABPINV.HORAMODIF,VDBULTOCABPINV.TARABULTO, "\
                    " VDBULTOCABPINV.PESOBULTO,VDBULTOCABPINV.MONOREF,VDBULTOCABPINV.OBSERV, "\
                    " VDBULTOCABPINV.VERIFFORZADA,VDBULTOCABPINV.LARGOBULTO,VDBULTOCABPINV.ALTOBULTO, "\
                    " VDBULTOCABPINV.ANCHOBULTO,VDBULTOCABPINV.DESTINOPLC,VDBULTOCABPINV.PUNTOPLC "\
        " FROM VDBULTOCABPINV"\
        " WHERE "\
               " VDBULTOCABPINV.CODMAT=:CODMAT "
static v10cursors *vdselbpccodmat;

#define SELBPCSTATUS "SELECT VDBULTOCABPINV.ROWID,VDBULTOCABPINV.CODBULTO,VDBULTOCABPINV.CODMAT, "\
                    " VDBULTOCABPINV.CAJACOMPLETA,VDBULTOCABPINV.FECCREADO,VDBULTOCABPINV.HORACREADO, "\
                    " VDBULTOCABPINV.FECFINALIZA,VDBULTOCABPINV.HORAFINALIZA,VDBULTOCABPINV.STATUS, "\
                    " VDBULTOCABPINV.VDEXTRA,VDBULTOCABPINV.CODCOMEN,VDBULTOCABPINV.CODOPEMODIF, "\
                    " VDBULTOCABPINV.FECMODIF,VDBULTOCABPINV.HORAMODIF,VDBULTOCABPINV.TARABULTO, "\
                    " VDBULTOCABPINV.PESOBULTO,VDBULTOCABPINV.MONOREF,VDBULTOCABPINV.OBSERV, "\
                    " VDBULTOCABPINV.VERIFFORZADA,VDBULTOCABPINV.LARGOBULTO,VDBULTOCABPINV.ALTOBULTO, "\
                    " VDBULTOCABPINV.ANCHOBULTO,VDBULTOCABPINV.DESTINOPLC,VDBULTOCABPINV.PUNTOPLC "\
        " FROM VDBULTOCABPINV"\
        " WHERE "\
               " VDBULTOCABPINV.STATUS=:STATUS "
static v10cursors *vdselbpcstatus;

#define SELBPCCODMATACTIVA "SELECT VDBULTOCABPINV.ROWID,VDBULTOCABPINV.CODBULTO,VDBULTOCABPINV.CODMAT, "\
                    " VDBULTOCABPINV.CAJACOMPLETA,VDBULTOCABPINV.FECCREADO,VDBULTOCABPINV.HORACREADO, "\
                    " VDBULTOCABPINV.FECFINALIZA,VDBULTOCABPINV.HORAFINALIZA,VDBULTOCABPINV.STATUS, "\
                    " VDBULTOCABPINV.VDEXTRA,VDBULTOCABPINV.CODCOMEN,VDBULTOCABPINV.CODOPEMODIF, "\
                    " VDBULTOCABPINV.FECMODIF,VDBULTOCABPINV.HORAMODIF,VDBULTOCABPINV.TARABULTO, "\
                    " VDBULTOCABPINV.PESOBULTO,VDBULTOCABPINV.MONOREF,VDBULTOCABPINV.OBSERV, "\
                    " VDBULTOCABPINV.VERIFFORZADA,VDBULTOCABPINV.LARGOBULTO,VDBULTOCABPINV.ALTOBULTO, "\
                    " VDBULTOCABPINV.ANCHOBULTO,VDBULTOCABPINV.DESTINOPLC,VDBULTOCABPINV.PUNTOPLC "\
        " FROM VDBULTOCABPINV"\
        " WHERE "\
               " VDBULTOCABPINV.CODMAT=:CODMAT "\
               " AND VDBULTOCABPINV.STATUS=:STATUS "
static v10cursors *vdselbpccodmatactiva;

#define SELBPCVDBULTOCABPINV "SELECT VDBULTOCABPINV.ROWID,VDBULTOCABPINV.CODBULTO,VDBULTOCABPINV.CODMAT, "\
                    " VDBULTOCABPINV.CAJACOMPLETA,VDBULTOCABPINV.FECCREADO,VDBULTOCABPINV.HORACREADO, "\
                    " VDBULTOCABPINV.FECFINALIZA,VDBULTOCABPINV.HORAFINALIZA,VDBULTOCABPINV.STATUS, "\
                    " VDBULTOCABPINV.VDEXTRA,VDBULTOCABPINV.CODCOMEN,VDBULTOCABPINV.CODOPEMODIF, "\
                    " VDBULTOCABPINV.FECMODIF,VDBULTOCABPINV.HORAMODIF,VDBULTOCABPINV.TARABULTO, "\
                    " VDBULTOCABPINV.PESOBULTO,VDBULTOCABPINV.MONOREF,VDBULTOCABPINV.OBSERV, "\
                    " VDBULTOCABPINV.VERIFFORZADA,VDBULTOCABPINV.LARGOBULTO,VDBULTOCABPINV.ALTOBULTO, "\
                    " VDBULTOCABPINV.ANCHOBULTO,VDBULTOCABPINV.DESTINOPLC,VDBULTOCABPINV.PUNTOPLC "\
        " FROM VDBULTOCABPINV"\
        " WHERE "\
               " VDBULTOCABPINV.CODBULTO=:CODBULTO "
static v10cursors *vdselbpcvdbultocabpinv;

#define SELBPCROWIDLOCK "SELECT ROWID,CODBULTO,CODMAT,CAJACOMPLETA,FECCREADO,HORACREADO,FECFINALIZA, "\
                    " HORAFINALIZA,STATUS,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF, "\
                    " TARABULTO,PESOBULTO,MONOREF,OBSERV,VERIFFORZADA,LARGOBULTO,ALTOBULTO, "\
                    " ANCHOBULTO,DESTINOPLC,PUNTOPLC "\
        " FROM VDBULTOCABPINV "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselbpcrowidlock;

#define UPDABPCSTATUS "UPDATE VDBULTOCABPINV SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabpcstatus;

static vdbultocabpinvs svdbultocabpinv;

static diccols colvdbultocabpinv[]={
	{"ROWID",V10CADENA,(size_t)&svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid)},
	{"CODBULTO",V10CADENA,(size_t)&svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto)},
	{"CODMAT",V10CADENA,(size_t)&svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat)},
	{"CAJACOMPLETA",V10CADENA,(size_t)&svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta)},
	{"FECCREADO",V10LONG,(size_t)&svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado)},
	{"HORACREADO",V10CADENA,(size_t)&svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado)},
	{"FECFINALIZA",V10LONG,(size_t)&svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza)},
	{"HORAFINALIZA",V10CADENA,(size_t)&svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza)},
	{"STATUS",V10LONG,(size_t)&svdbultocabpinv.status,sizeof(svdbultocabpinv.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif)},
	{"TARABULTO",V10LONG,(size_t)&svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto)},
	{"PESOBULTO",V10LONG,(size_t)&svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto)},
	{"MONOREF",V10CADENA,(size_t)&svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref)},
	{"OBSERV",V10CADENA,(size_t)&svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ)},
	{"VERIFFORZADA",V10CADENA,(size_t)&svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada)},
	{"LARGOBULTO",V10LONG,(size_t)&svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto)},
	{"ALTOBULTO",V10LONG,(size_t)&svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto)},
	{"ANCHOBULTO",V10LONG,(size_t)&svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto)},
	{"DESTINOPLC",V10CADENA,(size_t)&svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc)},
	{"PUNTOPLC",V10CADENA,(size_t)&svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc)}
	};
static diccionarios dvdbultocabpinv[]={
    {colvdbultocabpinv,24}
};
diccionario dbpc={dvdbultocabpinv,1};

static char msglogBPC[LCADENA];
static char msgdebugBPC[LCADENABIG];
static int init=0;


static void fin_vd_bpc(void)
{
if (vdselbpccodmat) {
    liberacursor(vdselbpccodmat);
    vdselbpccodmat = NULL;
}
if (vdselbpcstatus) {
    liberacursor(vdselbpcstatus);
    vdselbpcstatus = NULL;
}
if (vdselbpccodmatactiva) {
    liberacursor(vdselbpccodmatactiva);
    vdselbpccodmatactiva = NULL;
}
if (vdselbpcvdbultocabpinv) {
    liberacursor(vdselbpcvdbultocabpinv);
    vdselbpcvdbultocabpinv = NULL;
}
if (vdselbpcrowidlock) {
    liberacursor(vdselbpcrowidlock);
    vdselbpcrowidlock = NULL;
}
if (vdupdabpcstatus) {
    liberacursor(vdupdabpcstatus);
    vdupdabpcstatus = NULL;
}
}
static void init_selbpccodmat(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdselbpccodmat=abrecursordebug(SELBPCCODMAT,1280);
    definetodo(vdselbpccodmat,svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta),V10CADENA,
                          &svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado),V10LONG,
                          svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado),V10CADENA,
                          &svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza),V10LONG,
                          svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza),V10CADENA,
                          &svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra),V10CADENA,
                          &svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen),V10LONG,
                          svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif),V10CADENA,
                          &svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif),V10LONG,
                          svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif),V10CADENA,
                          &svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto),V10LONG,
                          &svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto),V10LONG,
                          svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref),V10CADENA,
                          svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ),V10CADENA,
                          svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada),V10CADENA,
                          &svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto),V10LONG,
                          &svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto),V10LONG,
                          &svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto),V10LONG,
                          svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc),V10CADENA,
                          svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc),V10CADENA,
                          NULL);
    bindtodo(vdselbpccodmat,"CODMAT",svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

static void init_selbpcstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdselbpcstatus=abrecursordebug(SELBPCSTATUS,1280);
    definetodo(vdselbpcstatus,svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta),V10CADENA,
                          &svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado),V10LONG,
                          svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado),V10CADENA,
                          &svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza),V10LONG,
                          svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza),V10CADENA,
                          &svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra),V10CADENA,
                          &svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen),V10LONG,
                          svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif),V10CADENA,
                          &svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif),V10LONG,
                          svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif),V10CADENA,
                          &svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto),V10LONG,
                          &svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto),V10LONG,
                          svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref),V10CADENA,
                          svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ),V10CADENA,
                          svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada),V10CADENA,
                          &svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto),V10LONG,
                          &svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto),V10LONG,
                          &svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto),V10LONG,
                          svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc),V10CADENA,
                          svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc),V10CADENA,
                          NULL);
    bindtodo(vdselbpcstatus,"STATUS",&svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

static void init_selbpccodmatactiva(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdselbpccodmatactiva=abrecursordebug(SELBPCCODMATACTIVA,1280);
    definetodo(vdselbpccodmatactiva,svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta),V10CADENA,
                          &svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado),V10LONG,
                          svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado),V10CADENA,
                          &svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza),V10LONG,
                          svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza),V10CADENA,
                          &svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra),V10CADENA,
                          &svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen),V10LONG,
                          svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif),V10CADENA,
                          &svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif),V10LONG,
                          svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif),V10CADENA,
                          &svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto),V10LONG,
                          &svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto),V10LONG,
                          svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref),V10CADENA,
                          svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ),V10CADENA,
                          svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada),V10CADENA,
                          &svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto),V10LONG,
                          &svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto),V10LONG,
                          &svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto),V10LONG,
                          svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc),V10CADENA,
                          svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc),V10CADENA,
                          NULL);
    bindtodo(vdselbpccodmatactiva,"CODMAT",svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          "STATUS",&svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

static void init_selbpcvdbultocabpinv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdselbpcvdbultocabpinv=abrecursordebug(SELBPCVDBULTOCABPINV,1280);
    definetodo(vdselbpcvdbultocabpinv,svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta),V10CADENA,
                          &svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado),V10LONG,
                          svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado),V10CADENA,
                          &svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza),V10LONG,
                          svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza),V10CADENA,
                          &svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra),V10CADENA,
                          &svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen),V10LONG,
                          svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif),V10CADENA,
                          &svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif),V10LONG,
                          svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif),V10CADENA,
                          &svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto),V10LONG,
                          &svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto),V10LONG,
                          svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref),V10CADENA,
                          svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ),V10CADENA,
                          svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada),V10CADENA,
                          &svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto),V10LONG,
                          &svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto),V10LONG,
                          &svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto),V10LONG,
                          svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc),V10CADENA,
                          svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc),V10CADENA,
                          NULL);
    bindtodo(vdselbpcvdbultocabpinv,"CODBULTO",svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

static void init_selbpcrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdselbpcrowidlock=abrecursordebug(SELBPCROWIDLOCK,1280);
    definetodo(vdselbpcrowidlock,svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          svdbultocabpinv.codbulto,sizeof(svdbultocabpinv.codbulto),V10CADENA,
                          svdbultocabpinv.codmat,sizeof(svdbultocabpinv.codmat),V10CADENA,
                          svdbultocabpinv.cajacompleta,sizeof(svdbultocabpinv.cajacompleta),V10CADENA,
                          &svdbultocabpinv.feccreado,sizeof(svdbultocabpinv.feccreado),V10LONG,
                          svdbultocabpinv.horacreado,sizeof(svdbultocabpinv.horacreado),V10CADENA,
                          &svdbultocabpinv.fecfinaliza,sizeof(svdbultocabpinv.fecfinaliza),V10LONG,
                          svdbultocabpinv.horafinaliza,sizeof(svdbultocabpinv.horafinaliza),V10CADENA,
                          &svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          svdbultocabpinv.vdextra,sizeof(svdbultocabpinv.vdextra),V10CADENA,
                          &svdbultocabpinv.codcomen,sizeof(svdbultocabpinv.codcomen),V10LONG,
                          svdbultocabpinv.codopemodif,sizeof(svdbultocabpinv.codopemodif),V10CADENA,
                          &svdbultocabpinv.fecmodif,sizeof(svdbultocabpinv.fecmodif),V10LONG,
                          svdbultocabpinv.horamodif,sizeof(svdbultocabpinv.horamodif),V10CADENA,
                          &svdbultocabpinv.tarabulto,sizeof(svdbultocabpinv.tarabulto),V10LONG,
                          &svdbultocabpinv.pesobulto,sizeof(svdbultocabpinv.pesobulto),V10LONG,
                          svdbultocabpinv.monoref,sizeof(svdbultocabpinv.monoref),V10CADENA,
                          svdbultocabpinv.observ,sizeof(svdbultocabpinv.observ),V10CADENA,
                          svdbultocabpinv.verifforzada,sizeof(svdbultocabpinv.verifforzada),V10CADENA,
                          &svdbultocabpinv.largobulto,sizeof(svdbultocabpinv.largobulto),V10LONG,
                          &svdbultocabpinv.altobulto,sizeof(svdbultocabpinv.altobulto),V10LONG,
                          &svdbultocabpinv.anchobulto,sizeof(svdbultocabpinv.anchobulto),V10LONG,
                          svdbultocabpinv.destinoplc,sizeof(svdbultocabpinv.destinoplc),V10CADENA,
                          svdbultocabpinv.puntoplc,sizeof(svdbultocabpinv.puntoplc),V10CADENA,
                          NULL);
    bindtodo(vdselbpcrowidlock,"MIROWID",svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

static void init_updabpcstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocabpinv[0].numcol;nc++) dvdbultocabpinv[0].c[nc].offset-=(size_t)&svdbultocabpinv;
    vdupdabpcstatus=abrecursordebug(UPDABPCSTATUS,1280);
    bindtodo(vdupdabpcstatus,"STATUS",&svdbultocabpinv.status,sizeof(svdbultocabpinv.status),V10LONG,
                          "MIROWID",svdbultocabpinv.rowid,sizeof(svdbultocabpinv.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bpc);
        init = 1;
    }
}

diccionario *BPCdamediccionario(void)
{
     return(&dbpc);
}

int BPCselcodmat(char *codmat,vdbultocabpinvs *bpc)
{
  int vdret;
  if (vdselbpccodmat==NULL) init_selbpccodmat();
  memset(&svdbultocabpinv,0,sizeof(svdbultocabpinv));
  strcpy(svdbultocabpinv.codmat,codmat);
  vdret=ejefetchcursor(vdselbpccodmat);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbpccodmat. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
    return(VD_EERRORACLE);
   }
  *bpc=svdbultocabpinv;
  return(vdret);
}

int BPCbuscastatus(long status,vdbultocabpinvs *bpc)
{
  int vdret;
  memset(&svdbultocabpinv,0,sizeof(svdbultocabpinv));
  svdbultocabpinv.status=status;
  if (vdselbpcstatus==NULL) init_selbpcstatus();
  vdret=ejefetchcursor(vdselbpcstatus);
  if (vdret==0) {
     *bpc=svdbultocabpinv;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbpcstatus. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BPCnextstatus(vdbultocabpinvs *bpc)
{
  int vdret;
  vdret=fetchcursor(vdselbpcstatus);
  if (vdret==0) {
     *bpc=svdbultocabpinv;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbpcstatus. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbpcstatus);
  return(VD_EERRORACLE);
}

int BPCbuscacodmatactiva(char *codmat,long status,vdbultocabpinvs *bpc)
{
  int vdret;
  memset(&svdbultocabpinv,0,sizeof(svdbultocabpinv));
  strcpy(svdbultocabpinv.codmat,codmat);
  svdbultocabpinv.status=status;
  if (vdselbpccodmatactiva==NULL) init_selbpccodmatactiva();
  vdret=ejefetchcursor(vdselbpccodmatactiva);
  if (vdret==0) {
     *bpc=svdbultocabpinv;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbpccodmatactiva. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BPCnextcodmatactiva(vdbultocabpinvs *bpc)
{
  int vdret;
  vdret=fetchcursor(vdselbpccodmatactiva);
  if (vdret==0) {
     *bpc=svdbultocabpinv;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbpccodmatactiva. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbpccodmatactiva);
  return(VD_EERRORACLE);
}

int BPCselvdbultocabpinv(char *codbulto,vdbultocabpinvs *bpc)
{
  int vdret;
  if (vdselbpcvdbultocabpinv==NULL) init_selbpcvdbultocabpinv();
  memset(&svdbultocabpinv,0,sizeof(svdbultocabpinv));
  strcpy(svdbultocabpinv.codbulto,codbulto);
  vdret=ejefetchcursor(vdselbpcvdbultocabpinv);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbpcvdbultocabpinv. vdret %d. \n",BPClog(&svdbultocabpinv),vdret);
    return(VD_EERRORACLE);
   }
  *bpc=svdbultocabpinv;
  return(vdret);
}

int BPClock(vdbultocabpinvs *bpc,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdbultocabpinv=*bpc;
    if (vdselbpcrowidlock==NULL) init_selbpcrowidlock();
    savepoint("lockvdbultocabpinv");
    while (1) {
        vdret=ejefetchcursor(vdselbpcrowidlock);
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
    vdret=vverificacampos(bpc,&svdbultocabpinv,&dvdbultocabpinv[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdbultocabpinv");
    return(vdret);
}

int BPCactualizastatus(vdbultocabpinvs *bpc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BPCactualizastatus:  %s .  \n",BPClog(&svdbultocabpinv));
  if (vdupdabpcstatus==NULL) init_updabpcstatus();
  svdbultocabpinv=*bpc;
  vdret=ejecutacursor(vdupdabpcstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabpcstatus);
     getcurerrornombre(vdupdabpcstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabpcstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

char * BPClog(vdbultocabpinvs *bpc)
{
    sprintf(msglogBPC, "VDBULTOCABPINV: codbulto %s ",bpc->codbulto);
    return(msglogBPC);
}

char * BPCdebug(vdbultocabpinvs *bpc)
{
    debugestruct(&dbpc,bpc,msgdebugBPC);
    return(msgdebugBPC);
}

