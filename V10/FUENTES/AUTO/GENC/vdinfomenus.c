// Modulo generado automaticamente a partir de VDINFOMENUS.DEF
//# Modulo : VDINFOMENUS.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFOMENUS
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 21-01-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IME
//EXTRA=ORDENDESDE,V10LONG
//EXTRA=ORDENHASTA,V10LONG
//
//CLAVE=IDMENU,IDMENU;
//CLAVE=SIGPADRE,PADREMENU,ORDENDESDE,WHERE=ORDENMENU>:ORDENDESDE;ORDERBY=ORDENMENU;
//CLAVE=ANTPADRE,PADREMENU,ORDENHASTA,WHERE=ORDENMENU<:ORDENHASTA;,ORDERBY=ORDENMENU DESC;
//
//CLAVE=STATUSORIGZONA,STATUSORIGZONA;ORDERBY=ORDENMENU;
//
//INSERT

#include "vd.h"
#define SELIMEIDMENU "SELECT VDINFOMENUS.ROWID,VDINFOMENUS.IDMENU,VDINFOMENUS.PADREMENU, "\
                    " VDINFOMENUS.ORDENMENU,VDINFOMENUS.TEXTO,VDINFOMENUS.TIPOACCION, "\
                    " VDINFOMENUS.FUNCION,VDINFOMENUS.PARAM,VDINFOMENUS.TTICK, "\
                    " VDINFOMENUS.FPRESENTA,VDINFOMENUS.PARAMTICK,VDINFOMENUS.STATUSORIGZONA, "\
                    " VDINFOMENUS.STATUSORIGDISP,VDINFOMENUS.VDEXTRA,VDINFOMENUS.CODOPEMODIF, "\
                    " VDINFOMENUS.FECMODIF,VDINFOMENUS.HORAMODIF,VDINFOMENUS.CODCOMEN "\
        " FROM VDINFOMENUS"\
        " WHERE "\
               " VDINFOMENUS.IDMENU=:IDMENU "
static v10cursors *vdselimeidmenu;

#define SELIMESIGPADRE "SELECT VDINFOMENUS.ROWID,VDINFOMENUS.IDMENU,VDINFOMENUS.PADREMENU, "\
                    " VDINFOMENUS.ORDENMENU,VDINFOMENUS.TEXTO,VDINFOMENUS.TIPOACCION, "\
                    " VDINFOMENUS.FUNCION,VDINFOMENUS.PARAM,VDINFOMENUS.TTICK, "\
                    " VDINFOMENUS.FPRESENTA,VDINFOMENUS.PARAMTICK,VDINFOMENUS.STATUSORIGZONA, "\
                    " VDINFOMENUS.STATUSORIGDISP,VDINFOMENUS.VDEXTRA,VDINFOMENUS.CODOPEMODIF, "\
                    " VDINFOMENUS.FECMODIF,VDINFOMENUS.HORAMODIF,VDINFOMENUS.CODCOMEN "\
        " FROM VDINFOMENUS"\
        " WHERE "\
               " VDINFOMENUS.PADREMENU=:PADREMENU "\
              "  AND ORDENMENU>:ORDENDESDE "\
        " ORDER BY ORDENMENU "
static v10cursors *vdselimesigpadre;

#define SELIMEANTPADRE "SELECT VDINFOMENUS.ROWID,VDINFOMENUS.IDMENU,VDINFOMENUS.PADREMENU, "\
                    " VDINFOMENUS.ORDENMENU,VDINFOMENUS.TEXTO,VDINFOMENUS.TIPOACCION, "\
                    " VDINFOMENUS.FUNCION,VDINFOMENUS.PARAM,VDINFOMENUS.TTICK, "\
                    " VDINFOMENUS.FPRESENTA,VDINFOMENUS.PARAMTICK,VDINFOMENUS.STATUSORIGZONA, "\
                    " VDINFOMENUS.STATUSORIGDISP,VDINFOMENUS.VDEXTRA,VDINFOMENUS.CODOPEMODIF, "\
                    " VDINFOMENUS.FECMODIF,VDINFOMENUS.HORAMODIF,VDINFOMENUS.CODCOMEN "\
        " FROM VDINFOMENUS"\
        " WHERE "\
               " VDINFOMENUS.PADREMENU=:PADREMENU "\
              "  AND ORDENMENU<:ORDENHASTA "\
        " ORDER BY ORDENMENU DESC "
static v10cursors *vdselimeantpadre;

#define SELIMESTATUSORIGZONA "SELECT VDINFOMENUS.ROWID,VDINFOMENUS.IDMENU,VDINFOMENUS.PADREMENU, "\
                    " VDINFOMENUS.ORDENMENU,VDINFOMENUS.TEXTO,VDINFOMENUS.TIPOACCION, "\
                    " VDINFOMENUS.FUNCION,VDINFOMENUS.PARAM,VDINFOMENUS.TTICK, "\
                    " VDINFOMENUS.FPRESENTA,VDINFOMENUS.PARAMTICK,VDINFOMENUS.STATUSORIGZONA, "\
                    " VDINFOMENUS.STATUSORIGDISP,VDINFOMENUS.VDEXTRA,VDINFOMENUS.CODOPEMODIF, "\
                    " VDINFOMENUS.FECMODIF,VDINFOMENUS.HORAMODIF,VDINFOMENUS.CODCOMEN "\
        " FROM VDINFOMENUS"\
        " WHERE "\
               " VDINFOMENUS.STATUSORIGZONA=:STATUSORIGZONA "\
        " ORDER BY ORDENMENU "
static v10cursors *vdselimestatusorigzona;

#define SELIMEVDINFOMENUS "SELECT VDINFOMENUS.ROWID,VDINFOMENUS.IDMENU,VDINFOMENUS.PADREMENU, "\
                    " VDINFOMENUS.ORDENMENU,VDINFOMENUS.TEXTO,VDINFOMENUS.TIPOACCION, "\
                    " VDINFOMENUS.FUNCION,VDINFOMENUS.PARAM,VDINFOMENUS.TTICK, "\
                    " VDINFOMENUS.FPRESENTA,VDINFOMENUS.PARAMTICK,VDINFOMENUS.STATUSORIGZONA, "\
                    " VDINFOMENUS.STATUSORIGDISP,VDINFOMENUS.VDEXTRA,VDINFOMENUS.CODOPEMODIF, "\
                    " VDINFOMENUS.FECMODIF,VDINFOMENUS.HORAMODIF,VDINFOMENUS.CODCOMEN "\
        " FROM VDINFOMENUS"
static v10cursors *vdselimevdinfomenus;

#define INSIME "INSERT INTO VDINFOMENUS (IDMENU,PADREMENU,ORDENMENU,TEXTO,TIPOACCION,FUNCION, "\
                    " PARAM,TTICK,FPRESENTA,PARAMTICK,STATUSORIGZONA,STATUSORIGDISP,VDEXTRA, "\
                    " CODOPEMODIF,FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :IDMENU,:PADREMENU,:ORDENMENU,:TEXTO,:TIPOACCION,:FUNCION, "\
                    " :PARAM,:TTICK,:FPRESENTA,:PARAMTICK,:STATUSORIGZONA,:STATUSORIGDISP,:VDEXTRA, "\
                    " VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS(),:CODCOMEN) "
static v10cursors *vdinsime;

static vdinfomenuss svdinfomenus;

static diccols colvdinfomenus[]={
	{"ROWID",V10CADENA,(size_t)&svdinfomenus.rowid,sizeof(svdinfomenus.rowid)},
	{"IDMENU",V10CADENA,(size_t)&svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu)},
	{"PADREMENU",V10CADENA,(size_t)&svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu)},
	{"ORDENMENU",V10LONG,(size_t)&svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu)},
	{"TEXTO",V10CADENA,(size_t)&svdinfomenus.texto,sizeof(svdinfomenus.texto)},
	{"TIPOACCION",V10CADENA,(size_t)&svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion)},
	{"FUNCION",V10CADENA,(size_t)&svdinfomenus.funcion,sizeof(svdinfomenus.funcion)},
	{"PARAM",V10CADENA,(size_t)&svdinfomenus.param,sizeof(svdinfomenus.param)},
	{"TTICK",V10LONG,(size_t)&svdinfomenus.ttick,sizeof(svdinfomenus.ttick)},
	{"FPRESENTA",V10CADENA,(size_t)&svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta)},
	{"PARAMTICK",V10CADENA,(size_t)&svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick)},
	{"STATUSORIGZONA",V10LONG,(size_t)&svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona)},
	{"STATUSORIGDISP",V10LONG,(size_t)&svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen)},
	{"ORDENDESDE",V10LONG,(size_t)&svdinfomenus.ordendesde,sizeof(svdinfomenus.ordendesde)},
	{"ORDENHASTA",V10LONG,(size_t)&svdinfomenus.ordenhasta,sizeof(svdinfomenus.ordenhasta)}
	};
static diccionarios dvdinfomenus[]={
    {colvdinfomenus,20}
};
diccionario dime={dvdinfomenus,1};

static char msglogIME[LCADENA];
static char msgdebugIME[LCADENABIG];
static int init=0;


static void fin_vd_ime(void)
{
if (vdselimeidmenu) {
    liberacursor(vdselimeidmenu);
    vdselimeidmenu = NULL;
}
if (vdselimesigpadre) {
    liberacursor(vdselimesigpadre);
    vdselimesigpadre = NULL;
}
if (vdselimeantpadre) {
    liberacursor(vdselimeantpadre);
    vdselimeantpadre = NULL;
}
if (vdselimestatusorigzona) {
    liberacursor(vdselimestatusorigzona);
    vdselimestatusorigzona = NULL;
}
if (vdselimevdinfomenus) {
    liberacursor(vdselimevdinfomenus);
    vdselimevdinfomenus = NULL;
}
if (vdinsime != NULL) {
    liberacursor(vdinsime);
    vdinsime = NULL;
}
}
static void init_selimeidmenu(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdselimeidmenu=abrecursordebug(SELIMEIDMENU,1280);
    definetodo(vdselimeidmenu,svdinfomenus.rowid,sizeof(svdinfomenus.rowid),V10CADENA,
                          svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          &svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          &svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          &svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          &svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif),V10CADENA,
                          &svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif),V10LONG,
                          svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif),V10CADENA,
                          &svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimeidmenu,"IDMENU",svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

static void init_selimesigpadre(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdselimesigpadre=abrecursordebug(SELIMESIGPADRE,1280);
    definetodo(vdselimesigpadre,svdinfomenus.rowid,sizeof(svdinfomenus.rowid),V10CADENA,
                          svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          &svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          &svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          &svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          &svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif),V10CADENA,
                          &svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif),V10LONG,
                          svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif),V10CADENA,
                          &svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimesigpadre,"PADREMENU",svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          "ORDENDESDE",&svdinfomenus.ordendesde,sizeof(svdinfomenus.ordendesde),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

static void init_selimeantpadre(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdselimeantpadre=abrecursordebug(SELIMEANTPADRE,1280);
    definetodo(vdselimeantpadre,svdinfomenus.rowid,sizeof(svdinfomenus.rowid),V10CADENA,
                          svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          &svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          &svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          &svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          &svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif),V10CADENA,
                          &svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif),V10LONG,
                          svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif),V10CADENA,
                          &svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimeantpadre,"PADREMENU",svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          "ORDENHASTA",&svdinfomenus.ordenhasta,sizeof(svdinfomenus.ordenhasta),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

static void init_selimestatusorigzona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdselimestatusorigzona=abrecursordebug(SELIMESTATUSORIGZONA,1280);
    definetodo(vdselimestatusorigzona,svdinfomenus.rowid,sizeof(svdinfomenus.rowid),V10CADENA,
                          svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          &svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          &svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          &svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          &svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif),V10CADENA,
                          &svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif),V10LONG,
                          svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif),V10CADENA,
                          &svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimestatusorigzona,"STATUSORIGZONA",&svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

static void init_selimevdinfomenus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdselimevdinfomenus=abrecursordebug(SELIMEVDINFOMENUS,1280);
    definetodo(vdselimevdinfomenus,svdinfomenus.rowid,sizeof(svdinfomenus.rowid),V10CADENA,
                          svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          &svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          &svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          &svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          &svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          svdinfomenus.codopemodif,sizeof(svdinfomenus.codopemodif),V10CADENA,
                          &svdinfomenus.fecmodif,sizeof(svdinfomenus.fecmodif),V10LONG,
                          svdinfomenus.horamodif,sizeof(svdinfomenus.horamodif),V10CADENA,
                          &svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimevdinfomenus,NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

static void init_insime(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfomenus[0].numcol;nc++) dvdinfomenus[0].c[nc].offset-=(size_t)&svdinfomenus;
    vdinsime=abrecursordebug(INSIME,1280);
    bindtodo(vdinsime,"IDMENU",svdinfomenus.idmenu,sizeof(svdinfomenus.idmenu),V10CADENA,
                          "PADREMENU",svdinfomenus.padremenu,sizeof(svdinfomenus.padremenu),V10CADENA,
                          "ORDENMENU",&svdinfomenus.ordenmenu,sizeof(svdinfomenus.ordenmenu),V10LONG,
                          "TEXTO",svdinfomenus.texto,sizeof(svdinfomenus.texto),V10CADENA,
                          "TIPOACCION",svdinfomenus.tipoaccion,sizeof(svdinfomenus.tipoaccion),V10CADENA,
                          "FUNCION",svdinfomenus.funcion,sizeof(svdinfomenus.funcion),V10CADENA,
                          "PARAM",svdinfomenus.param,sizeof(svdinfomenus.param),V10CADENA,
                          "TTICK",&svdinfomenus.ttick,sizeof(svdinfomenus.ttick),V10LONG,
                          "FPRESENTA",svdinfomenus.fpresenta,sizeof(svdinfomenus.fpresenta),V10CADENA,
                          "PARAMTICK",svdinfomenus.paramtick,sizeof(svdinfomenus.paramtick),V10CADENA,
                          "STATUSORIGZONA",&svdinfomenus.statusorigzona,sizeof(svdinfomenus.statusorigzona),V10LONG,
                          "STATUSORIGDISP",&svdinfomenus.statusorigdisp,sizeof(svdinfomenus.statusorigdisp),V10LONG,
                          "VDEXTRA",svdinfomenus.vdextra,sizeof(svdinfomenus.vdextra),V10CADENA,
                          "CODCOMEN",&svdinfomenus.codcomen,sizeof(svdinfomenus.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ime);
        init = 1;
    }
}

diccionario *IMEdamediccionario(void)
{
     return(&dime);
}

int IMEselidmenu(char *idmenu,vdinfomenuss *ime)
{
  int vdret;
  if (vdselimeidmenu==NULL) init_selimeidmenu();
  memset(&svdinfomenus,0,sizeof(svdinfomenus));
  strcpy(svdinfomenus.idmenu,idmenu);
  vdret=ejefetchcursor(vdselimeidmenu);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimeidmenu. vdret %d. \n",IMElog(&svdinfomenus),vdret);
    return(VD_EERRORACLE);
   }
  *ime=svdinfomenus;
  return(vdret);
}

int IMEselsigpadre(char *padremenu,long ordendesde,vdinfomenuss *ime)
{
  int vdret;
  if (vdselimesigpadre==NULL) init_selimesigpadre();
  memset(&svdinfomenus,0,sizeof(svdinfomenus));
  strcpy(svdinfomenus.padremenu,padremenu);
  svdinfomenus.ordendesde=ordendesde;
  vdret=ejefetchcursor(vdselimesigpadre);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimesigpadre. vdret %d. \n",IMElog(&svdinfomenus),vdret);
    return(VD_EERRORACLE);
   }
  *ime=svdinfomenus;
  return(vdret);
}

int IMEselantpadre(char *padremenu,long ordenhasta,vdinfomenuss *ime)
{
  int vdret;
  if (vdselimeantpadre==NULL) init_selimeantpadre();
  memset(&svdinfomenus,0,sizeof(svdinfomenus));
  strcpy(svdinfomenus.padremenu,padremenu);
  svdinfomenus.ordenhasta=ordenhasta;
  vdret=ejefetchcursor(vdselimeantpadre);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimeantpadre. vdret %d. \n",IMElog(&svdinfomenus),vdret);
    return(VD_EERRORACLE);
   }
  *ime=svdinfomenus;
  return(vdret);
}

int IMEselstatusorigzona(long statusorigzona,vdinfomenuss *ime)
{
  int vdret;
  if (vdselimestatusorigzona==NULL) init_selimestatusorigzona();
  memset(&svdinfomenus,0,sizeof(svdinfomenus));
  svdinfomenus.statusorigzona=statusorigzona;
  vdret=ejefetchcursor(vdselimestatusorigzona);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimestatusorigzona. vdret %d. \n",IMElog(&svdinfomenus),vdret);
    return(VD_EERRORACLE);
   }
  *ime=svdinfomenus;
  return(vdret);
}

int IMEselvdinfomenus(vdinfomenuss *ime)
{
  int vdret;
  if (vdselimevdinfomenus==NULL) init_selimevdinfomenus();
  memset(&svdinfomenus,0,sizeof(svdinfomenus));
  vdret=ejefetchcursor(vdselimevdinfomenus);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimevdinfomenus. vdret %d. \n",IMElog(&svdinfomenus),vdret);
    return(VD_EERRORACLE);
   }
  *ime=svdinfomenus;
  return(vdret);
}

int IMEinsert(vdinfomenuss *ime,int error)
{
  int vdret;
  if (!vdinsime) init_insime();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",IMElog(&svdinfomenus));
  svdinfomenus=*ime;
  vdret=ejecutacursor(vdinsime);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsime);
     getcurerrornombre(vdinsime->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * IMElog(vdinfomenuss *ime)
{
    sprintf(msglogIME, "VDINFOMENUS: ");
    return(msglogIME);
}

char * IMEdebug(vdinfomenuss *ime)
{
    debugestruct(&dime,ime,msgdebugIME);
    return(msgdebugIME);
}

