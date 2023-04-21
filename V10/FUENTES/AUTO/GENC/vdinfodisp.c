// Modulo generado automaticamente a partir de VDINFODISP.DEF
//TABLE=IDI;
//EXTRA=IDINFOGEST,V10LONG
//
//CLAVE=CODBULTO,CODBULTO;
//RECORRE=TICK,IDINFOGEST,TABLE=VDZONAS;WHERE=VDINFODISP.CODZONA=VDZONAS.CODZONA AND 
//                                                VDZONAS.IDINFOGEST=:IDINFOGEST AND 
//                                                VDINFODISP.NEXTTICK IS NOT NULL AND VDINFODISP.NEXTTICK<=VD.FECHASEC;
//
//#RECORRE=BULTOENZONA,CODBULTO,CODZONA,WHERE=CODUBI<>NVL(:CODUBI,'0');
//
//RECORRE=STATUSZONA,STATUS,CODZONA;
//RECORRE=DISPLAYSZONA,CODZONA;
//RECORRE=LUZPADRE,IDINFOPICKLUZ,NUMLUZ; 
//
//UPDATE=STATUS,STATUS
//UPDATE=CODBULTO,CODBULTO
//UPDATE=CANTIDADES,CANTPEDIDADISP,CANTVALIDADADISP
//UPDATE=CODBULTOYCANTIDADES,CODBULTO,CANTPEDIDADISP,CANTVALIDADADISP
//UPDATE=CONFIRMADO,CONFIRMADO

#include "vd.h"
#define SELIDICODBULTO "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP"\
        " WHERE "\
               " VDINFODISP.CODBULTO=:CODBULTO "
static v10cursors *vdselidicodbulto;

#define SELIDITICK "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP ,VDZONAS"\
        " WHERE "\
              " VDINFODISP.CODZONA=VDZONAS.CODZONA AND  VDZONAS.IDINFOGEST=:IDINFOGEST AND  VDINFODISP.NEXTTICK IS NOT NULL AND VDINFODISP.NEXTTICK<=VD.FECHASEC "
static v10cursors *vdseliditick;

#define SELIDISTATUSZONA "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP"\
        " WHERE "\
               " VDINFODISP.STATUS=:STATUS "\
               " AND VDINFODISP.CODZONA=:CODZONA "
static v10cursors *vdselidistatuszona;

#define SELIDIDISPLAYSZONA "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP"\
        " WHERE "\
               " VDINFODISP.CODZONA=:CODZONA "
static v10cursors *vdselididisplayszona;

#define SELIDILUZPADRE "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP"\
        " WHERE "\
               " VDINFODISP.IDINFOPICKLUZ=:IDINFOPICKLUZ "\
               " AND VDINFODISP.NUMLUZ=:NUMLUZ "
static v10cursors *vdselidiluzpadre;

#define SELIDIVDINFODISP "SELECT VDINFODISP.ROWID,VDINFODISP.IDINFOPICK,VDINFODISP.NUMDISP, "\
                    " VDINFODISP.CODZONA,VDINFODISP.IDINFOPICKPADRE,VDINFODISP.DPADRE, "\
                    " VDINFODISP.IDINFOPICKLUZ,VDINFODISP.NUMLUZ,VDINFODISP.ORDENDISP, "\
                    " VDINFODISP.MAXCANTDISP,VDINFODISP.CANTALEATORIA,VDINFODISP.TIEMPOOK, "\
                    " VDINFODISP.TIEMPOFIN,VDINFODISP.NEXTTICK,VDINFODISP.INVCONT, "\
                    " VDINFODISP.CODUBI,VDINFODISP.CODBULTO,VDINFODISP.CONFIRMADO, "\
                    " VDINFODISP.CANTPEDIDADISP,VDINFODISP.CANTVALIDADADISP,VDINFODISP.STATUS, "\
                    " VDINFODISP.VDEXTRA,VDINFODISP.CODOPEMODIF,VDINFODISP.FECMODIF, "\
                    " VDINFODISP.HORAMODIF,VDINFODISP.CODCOMEN,VDINFODISP.CODMOV, "\
                    " VDINFODISP.QUEDAN,VDINFODISP.IDINFOPICKALT,VDINFODISP.CODUBIALT, "\
                    " VDINFODISP.CODMAT "\
        " FROM VDINFODISP"\
        " WHERE "\
               " VDINFODISP.IDINFOPICK=:IDINFOPICK "\
               " AND VDINFODISP.NUMDISP=:NUMDISP "
static v10cursors *vdselidivdinfodisp;

#define UPDAIDISTATUS "UPDATE VDINFODISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidistatus;

#define UPDAIDICODBULTO "UPDATE VDINFODISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODBULTO=:CODBULTO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidicodbulto;

#define UPDAIDICANTIDADES "UPDATE VDINFODISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CANTPEDIDADISP=:CANTPEDIDADISP , "\
               " CANTVALIDADADISP=:CANTVALIDADADISP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidicantidades;

#define UPDAIDICODBULTOYCANTIDADES "UPDATE VDINFODISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODBULTO=:CODBULTO , "\
               " CANTPEDIDADISP=:CANTPEDIDADISP , "\
               " CANTVALIDADADISP=:CANTVALIDADADISP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidicodbultoycantidades;

#define UPDAIDICONFIRMADO "UPDATE VDINFODISP SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CONFIRMADO=:CONFIRMADO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaidiconfirmado;

static vdinfodisps svdinfodisp;

static diccols colvdinfodisp[]={
	{"ROWID",V10CADENA,(size_t)&svdinfodisp.rowid,sizeof(svdinfodisp.rowid)},
	{"IDINFOPICK",V10LONG,(size_t)&svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick)},
	{"NUMDISP",V10LONG,(size_t)&svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp)},
	{"CODZONA",V10LONG,(size_t)&svdinfodisp.codzona,sizeof(svdinfodisp.codzona)},
	{"IDINFOPICKPADRE",V10LONG,(size_t)&svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre)},
	{"DPADRE",V10LONG,(size_t)&svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre)},
	{"IDINFOPICKLUZ",V10LONG,(size_t)&svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz)},
	{"NUMLUZ",V10LONG,(size_t)&svdinfodisp.numluz,sizeof(svdinfodisp.numluz)},
	{"ORDENDISP",V10LONG,(size_t)&svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp)},
	{"MAXCANTDISP",V10LONG,(size_t)&svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp)},
	{"CANTALEATORIA",V10CADENA,(size_t)&svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria)},
	{"TIEMPOOK",V10LONG,(size_t)&svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook)},
	{"TIEMPOFIN",V10LONG,(size_t)&svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin)},
	{"NEXTTICK",V10CADENA,(size_t)&svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick)},
	{"INVCONT",V10CADENA,(size_t)&svdinfodisp.invcont,sizeof(svdinfodisp.invcont)},
	{"CODUBI",V10CADENA,(size_t)&svdinfodisp.codubi,sizeof(svdinfodisp.codubi)},
	{"CODBULTO",V10CADENA,(size_t)&svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto)},
	{"CONFIRMADO",V10CADENA,(size_t)&svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado)},
	{"CANTPEDIDADISP",V10LONG,(size_t)&svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp)},
	{"CANTVALIDADADISP",V10LONG,(size_t)&svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp)},
	{"STATUS",V10LONG,(size_t)&svdinfodisp.status,sizeof(svdinfodisp.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen)},
	{"CODMOV",V10LONG,(size_t)&svdinfodisp.codmov,sizeof(svdinfodisp.codmov)},
	{"QUEDAN",V10LONG,(size_t)&svdinfodisp.quedan,sizeof(svdinfodisp.quedan)},
	{"IDINFOPICKALT",V10LONG,(size_t)&svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt)},
	{"CODUBIALT",V10CADENA,(size_t)&svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt)},
	{"CODMAT",V10CADENA,(size_t)&svdinfodisp.codmat,sizeof(svdinfodisp.codmat)},
	{"IDINFOGEST",V10LONG,(size_t)&svdinfodisp.idinfogest,sizeof(svdinfodisp.idinfogest)}
	};
static diccionarios dvdinfodisp[]={
    {colvdinfodisp,32}
};
diccionario didi={dvdinfodisp,1};

static char msglogIDI[LCADENA];
static char msgdebugIDI[LCADENABIG];
static int init=0;


static void fin_vd_idi(void)
{
if (vdselidicodbulto) {
    liberacursor(vdselidicodbulto);
    vdselidicodbulto = NULL;
}
if (vdseliditick) {
    liberacursor(vdseliditick);
    vdseliditick = NULL;
}
if (vdselidistatuszona) {
    liberacursor(vdselidistatuszona);
    vdselidistatuszona = NULL;
}
if (vdselididisplayszona) {
    liberacursor(vdselididisplayszona);
    vdselididisplayszona = NULL;
}
if (vdselidiluzpadre) {
    liberacursor(vdselidiluzpadre);
    vdselidiluzpadre = NULL;
}
if (vdselidivdinfodisp) {
    liberacursor(vdselidivdinfodisp);
    vdselidivdinfodisp = NULL;
}
if (vdupdaidistatus) {
    liberacursor(vdupdaidistatus);
    vdupdaidistatus = NULL;
}
if (vdupdaidicodbulto) {
    liberacursor(vdupdaidicodbulto);
    vdupdaidicodbulto = NULL;
}
if (vdupdaidicantidades) {
    liberacursor(vdupdaidicantidades);
    vdupdaidicantidades = NULL;
}
if (vdupdaidicodbultoycantidades) {
    liberacursor(vdupdaidicodbultoycantidades);
    vdupdaidicodbultoycantidades = NULL;
}
if (vdupdaidiconfirmado) {
    liberacursor(vdupdaidiconfirmado);
    vdupdaidiconfirmado = NULL;
}
}
static void init_selidicodbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdselidicodbulto=abrecursordebug(SELIDICODBULTO,1280);
    definetodo(vdselidicodbulto,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdselidicodbulto,"CODBULTO",svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_seliditick(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdseliditick=abrecursordebug(SELIDITICK,1280);
    definetodo(vdseliditick,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdseliditick,"IDINFOGEST",&svdinfodisp.idinfogest,sizeof(svdinfodisp.idinfogest),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_selidistatuszona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdselidistatuszona=abrecursordebug(SELIDISTATUSZONA,1280);
    definetodo(vdselidistatuszona,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdselidistatuszona,"STATUS",&svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          "CODZONA",&svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_selididisplayszona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdselididisplayszona=abrecursordebug(SELIDIDISPLAYSZONA,1280);
    definetodo(vdselididisplayszona,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdselididisplayszona,"CODZONA",&svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_selidiluzpadre(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdselidiluzpadre=abrecursordebug(SELIDILUZPADRE,1280);
    definetodo(vdselidiluzpadre,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdselidiluzpadre,"IDINFOPICKLUZ",&svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          "NUMLUZ",&svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_selidivdinfodisp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdselidivdinfodisp=abrecursordebug(SELIDIVDINFODISP,1280);
    definetodo(vdselidivdinfodisp,svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          &svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          &svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          &svdinfodisp.codzona,sizeof(svdinfodisp.codzona),V10LONG,
                          &svdinfodisp.idinfopickpadre,sizeof(svdinfodisp.idinfopickpadre),V10LONG,
                          &svdinfodisp.dpadre,sizeof(svdinfodisp.dpadre),V10LONG,
                          &svdinfodisp.idinfopickluz,sizeof(svdinfodisp.idinfopickluz),V10LONG,
                          &svdinfodisp.numluz,sizeof(svdinfodisp.numluz),V10LONG,
                          &svdinfodisp.ordendisp,sizeof(svdinfodisp.ordendisp),V10LONG,
                          &svdinfodisp.maxcantdisp,sizeof(svdinfodisp.maxcantdisp),V10LONG,
                          svdinfodisp.cantaleatoria,sizeof(svdinfodisp.cantaleatoria),V10CADENA,
                          &svdinfodisp.tiempook,sizeof(svdinfodisp.tiempook),V10LONG,
                          &svdinfodisp.tiempofin,sizeof(svdinfodisp.tiempofin),V10LONG,
                          svdinfodisp.nexttick,sizeof(svdinfodisp.nexttick),V10CADENA,
                          svdinfodisp.invcont,sizeof(svdinfodisp.invcont),V10CADENA,
                          svdinfodisp.codubi,sizeof(svdinfodisp.codubi),V10CADENA,
                          svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          &svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          &svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          &svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          svdinfodisp.vdextra,sizeof(svdinfodisp.vdextra),V10CADENA,
                          svdinfodisp.codopemodif,sizeof(svdinfodisp.codopemodif),V10CADENA,
                          &svdinfodisp.fecmodif,sizeof(svdinfodisp.fecmodif),V10LONG,
                          svdinfodisp.horamodif,sizeof(svdinfodisp.horamodif),V10CADENA,
                          &svdinfodisp.codcomen,sizeof(svdinfodisp.codcomen),V10LONG,
                          &svdinfodisp.codmov,sizeof(svdinfodisp.codmov),V10LONG,
                          &svdinfodisp.quedan,sizeof(svdinfodisp.quedan),V10LONG,
                          &svdinfodisp.idinfopickalt,sizeof(svdinfodisp.idinfopickalt),V10LONG,
                          svdinfodisp.codubialt,sizeof(svdinfodisp.codubialt),V10CADENA,
                          svdinfodisp.codmat,sizeof(svdinfodisp.codmat),V10CADENA,
                          NULL);
    bindtodo(vdselidivdinfodisp,"IDINFOPICK",&svdinfodisp.idinfopick,sizeof(svdinfodisp.idinfopick),V10LONG,
                          "NUMDISP",&svdinfodisp.numdisp,sizeof(svdinfodisp.numdisp),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_updaidistatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdupdaidistatus=abrecursordebug(UPDAIDISTATUS,1280);
    bindtodo(vdupdaidistatus,"STATUS",&svdinfodisp.status,sizeof(svdinfodisp.status),V10LONG,
                          "MIROWID",svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_updaidicodbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdupdaidicodbulto=abrecursordebug(UPDAIDICODBULTO,1280);
    bindtodo(vdupdaidicodbulto,"CODBULTO",svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          "MIROWID",svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_updaidicantidades(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdupdaidicantidades=abrecursordebug(UPDAIDICANTIDADES,1280);
    bindtodo(vdupdaidicantidades,"CANTPEDIDADISP",&svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          "CANTVALIDADADISP",&svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          "MIROWID",svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_updaidicodbultoycantidades(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdupdaidicodbultoycantidades=abrecursordebug(UPDAIDICODBULTOYCANTIDADES,1280);
    bindtodo(vdupdaidicodbultoycantidades,"CODBULTO",svdinfodisp.codbulto,sizeof(svdinfodisp.codbulto),V10CADENA,
                          "CANTPEDIDADISP",&svdinfodisp.cantpedidadisp,sizeof(svdinfodisp.cantpedidadisp),V10LONG,
                          "CANTVALIDADADISP",&svdinfodisp.cantvalidadadisp,sizeof(svdinfodisp.cantvalidadadisp),V10LONG,
                          "MIROWID",svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

static void init_updaidiconfirmado(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfodisp[0].numcol;nc++) dvdinfodisp[0].c[nc].offset-=(size_t)&svdinfodisp;
    vdupdaidiconfirmado=abrecursordebug(UPDAIDICONFIRMADO,1280);
    bindtodo(vdupdaidiconfirmado,"CONFIRMADO",svdinfodisp.confirmado,sizeof(svdinfodisp.confirmado),V10CADENA,
                          "MIROWID",svdinfodisp.rowid,sizeof(svdinfodisp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_idi);
        init = 1;
    }
}

diccionario *IDIdamediccionario(void)
{
     return(&didi);
}

int IDIselcodbulto(char *codbulto,vdinfodisps *idi)
{
  int vdret;
  if (vdselidicodbulto==NULL) init_selidicodbulto();
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  strcpy(svdinfodisp.codbulto,codbulto);
  vdret=ejefetchcursor(vdselidicodbulto);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselidicodbulto. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
    return(VD_EERRORACLE);
   }
  *idi=svdinfodisp;
  return(vdret);
}

int IDIbuscatick(long idinfogest,vdinfodisps *idi)
{
  int vdret;
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  svdinfodisp.idinfogest=idinfogest;
  if (vdseliditick==NULL) init_seliditick();
  vdret=ejefetchcursor(vdseliditick);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseliditick. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDInexttick(vdinfodisps *idi)
{
  int vdret;
  vdret=fetchcursor(vdseliditick);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseliditick. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseliditick);
  return(VD_EERRORACLE);
}

int IDIbuscastatuszona(long status,long codzona,vdinfodisps *idi)
{
  int vdret;
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  svdinfodisp.status=status;
  svdinfodisp.codzona=codzona;
  if (vdselidistatuszona==NULL) init_selidistatuszona();
  vdret=ejefetchcursor(vdselidistatuszona);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidistatuszona. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDInextstatuszona(vdinfodisps *idi)
{
  int vdret;
  vdret=fetchcursor(vdselidistatuszona);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidistatuszona. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidistatuszona);
  return(VD_EERRORACLE);
}

int IDIbuscadisplayszona(long codzona,vdinfodisps *idi)
{
  int vdret;
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  svdinfodisp.codzona=codzona;
  if (vdselididisplayszona==NULL) init_selididisplayszona();
  vdret=ejefetchcursor(vdselididisplayszona);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselididisplayszona. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDInextdisplayszona(vdinfodisps *idi)
{
  int vdret;
  vdret=fetchcursor(vdselididisplayszona);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselididisplayszona. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselididisplayszona);
  return(VD_EERRORACLE);
}

int IDIbuscaluzpadre(long idinfopickluz,long numluz,vdinfodisps *idi)
{
  int vdret;
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  svdinfodisp.idinfopickluz=idinfopickluz;
  svdinfodisp.numluz=numluz;
  if (vdselidiluzpadre==NULL) init_selidiluzpadre();
  vdret=ejefetchcursor(vdselidiluzpadre);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselidiluzpadre. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IDInextluzpadre(vdinfodisps *idi)
{
  int vdret;
  vdret=fetchcursor(vdselidiluzpadre);
  if (vdret==0) {
     *idi=svdinfodisp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselidiluzpadre. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselidiluzpadre);
  return(VD_EERRORACLE);
}

int IDIselvdinfodisp(long idinfopick,long numdisp,vdinfodisps *idi)
{
  int vdret;
  if (vdselidivdinfodisp==NULL) init_selidivdinfodisp();
  memset(&svdinfodisp,0,sizeof(svdinfodisp));
  svdinfodisp.idinfopick=idinfopick;
  svdinfodisp.numdisp=numdisp;
  vdret=ejefetchcursor(vdselidivdinfodisp);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselidivdinfodisp. vdret %d. \n",IDIlog(&svdinfodisp),vdret);
    return(VD_EERRORACLE);
   }
  *idi=svdinfodisp;
  return(vdret);
}

int IDIactualizastatus(vdinfodisps *idi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDIactualizastatus:  %s .  \n",IDIlog(&svdinfodisp));
  if (vdupdaidistatus==NULL) init_updaidistatus();
  svdinfodisp=*idi;
  vdret=ejecutacursor(vdupdaidistatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidistatus);
     getcurerrornombre(vdupdaidistatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidistatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDIactualizacodbulto(vdinfodisps *idi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDIactualizacodbulto:  %s .  \n",IDIlog(&svdinfodisp));
  if (vdupdaidicodbulto==NULL) init_updaidicodbulto();
  svdinfodisp=*idi;
  vdret=ejecutacursor(vdupdaidicodbulto);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidicodbulto);
     getcurerrornombre(vdupdaidicodbulto->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidicodbulto)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDIactualizacantidades(vdinfodisps *idi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDIactualizacantidades:  %s .  \n",IDIlog(&svdinfodisp));
  if (vdupdaidicantidades==NULL) init_updaidicantidades();
  svdinfodisp=*idi;
  vdret=ejecutacursor(vdupdaidicantidades);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidicantidades);
     getcurerrornombre(vdupdaidicantidades->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidicantidades)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDIactualizacodbultoycantidades(vdinfodisps *idi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDIactualizacodbultoycantidades:  %s .  \n",IDIlog(&svdinfodisp));
  if (vdupdaidicodbultoycantidades==NULL) init_updaidicodbultoycantidades();
  svdinfodisp=*idi;
  vdret=ejecutacursor(vdupdaidicodbultoycantidades);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidicodbultoycantidades);
     getcurerrornombre(vdupdaidicodbultoycantidades->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidicodbultoycantidades)!=1) return(VD_EERRORACLE);
  return(0);
}

int IDIactualizaconfirmado(vdinfodisps *idi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IDIactualizaconfirmado:  %s .  \n",IDIlog(&svdinfodisp));
  if (vdupdaidiconfirmado==NULL) init_updaidiconfirmado();
  svdinfodisp=*idi;
  vdret=ejecutacursor(vdupdaidiconfirmado);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaidiconfirmado);
     getcurerrornombre(vdupdaidiconfirmado->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaidiconfirmado)!=1) return(VD_EERRORACLE);
  return(0);
}

char * IDIlog(vdinfodisps *idi)
{
    sprintf(msglogIDI, "VDINFODISP: idinfopick %ld numdisp %ld ",idi->idinfopick,idi->numdisp);
    return(msglogIDI);
}

char * IDIdebug(vdinfodisps *idi)
{
    debugestruct(&didi,idi,msgdebugIDI);
    return(msgdebugIDI);
}

