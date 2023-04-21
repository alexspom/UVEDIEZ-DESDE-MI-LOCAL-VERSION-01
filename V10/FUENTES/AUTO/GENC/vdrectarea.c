// Modulo generado automaticamente a partir de VDRECTAREA.DEF
//# M¢dulo : VDRECURSO.DEF
//# Función: Generación automatica de rutinas C tabla VDRECURSO
//#
//# Autor	 : EAA
//# Revisado por:
//# Fecha  : 10-10-2007
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=RET
//
//PRIMARIA=CODRECURSO,CODPERFIL
//
//RECORRE=CODRECURSO,CODRECURSO,WHERE ACTIVA='S';ORDERBY=PRIOTAREA;

#include "vd.h"
#define SELRETCODRECURSO "SELECT VDRECTAREA.ROWID,VDRECTAREA.CODRECURSO,VDRECTAREA.CODPERFIL, "\
                    " VDRECTAREA.PRIOTAREA,VDRECTAREA.ACTIVA,VDRECTAREA.CODCOMEN, "\
                    " VDRECTAREA.CODOPEMODIF,VDRECTAREA.FECMODIF,VDRECTAREA.HORAMODIF "\
        " FROM VDRECTAREA"\
        " WHERE "\
               " VDRECTAREA.CODRECURSO=:CODRECURSO "\
              "  AND ACTIVA='S' "\
        " ORDER BY PRIOTAREA "
static v10cursors *vdselretcodrecurso;

#define SELRETVDRECTAREA "SELECT VDRECTAREA.ROWID,VDRECTAREA.CODRECURSO,VDRECTAREA.CODPERFIL, "\
                    " VDRECTAREA.PRIOTAREA,VDRECTAREA.ACTIVA,VDRECTAREA.CODCOMEN, "\
                    " VDRECTAREA.CODOPEMODIF,VDRECTAREA.FECMODIF,VDRECTAREA.HORAMODIF "\
        " FROM VDRECTAREA"\
        " WHERE "\
               " VDRECTAREA.CODRECURSO=:CODRECURSO "\
               " AND VDRECTAREA.CODPERFIL=:CODPERFIL "
static v10cursors *vdselretvdrectarea;

static vdrectareas svdrectarea;

static diccols colvdrectarea[]={
	{"ROWID",V10CADENA,(size_t)&svdrectarea.rowid,sizeof(svdrectarea.rowid)},
	{"CODRECURSO",V10CADENA,(size_t)&svdrectarea.codrecurso,sizeof(svdrectarea.codrecurso)},
	{"CODPERFIL",V10CADENA,(size_t)&svdrectarea.codperfil,sizeof(svdrectarea.codperfil)},
	{"PRIOTAREA",V10LONG,(size_t)&svdrectarea.priotarea,sizeof(svdrectarea.priotarea)},
	{"ACTIVA",V10CADENA,(size_t)&svdrectarea.activa,sizeof(svdrectarea.activa)},
	{"CODCOMEN",V10LONG,(size_t)&svdrectarea.codcomen,sizeof(svdrectarea.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdrectarea.codopemodif,sizeof(svdrectarea.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdrectarea.fecmodif,sizeof(svdrectarea.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdrectarea.horamodif,sizeof(svdrectarea.horamodif)}
	};
static diccionarios dvdrectarea[]={
    {colvdrectarea,9}
};
diccionario dret={dvdrectarea,1};

static char msglogRET[LCADENA];
static char msgdebugRET[LCADENABIG];
static int init=0;


static void fin_vd_ret(void)
{
if (vdselretcodrecurso) {
    liberacursor(vdselretcodrecurso);
    vdselretcodrecurso = NULL;
}
if (vdselretvdrectarea) {
    liberacursor(vdselretvdrectarea);
    vdselretvdrectarea = NULL;
}
}
static void init_selretcodrecurso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrectarea[0].numcol;nc++) dvdrectarea[0].c[nc].offset-=(size_t)&svdrectarea;
    vdselretcodrecurso=abrecursordebug(SELRETCODRECURSO,1280);
    definetodo(vdselretcodrecurso,svdrectarea.rowid,sizeof(svdrectarea.rowid),V10CADENA,
                          svdrectarea.codrecurso,sizeof(svdrectarea.codrecurso),V10CADENA,
                          svdrectarea.codperfil,sizeof(svdrectarea.codperfil),V10CADENA,
                          &svdrectarea.priotarea,sizeof(svdrectarea.priotarea),V10LONG,
                          svdrectarea.activa,sizeof(svdrectarea.activa),V10CADENA,
                          &svdrectarea.codcomen,sizeof(svdrectarea.codcomen),V10LONG,
                          svdrectarea.codopemodif,sizeof(svdrectarea.codopemodif),V10CADENA,
                          &svdrectarea.fecmodif,sizeof(svdrectarea.fecmodif),V10LONG,
                          svdrectarea.horamodif,sizeof(svdrectarea.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselretcodrecurso,"CODRECURSO",svdrectarea.codrecurso,sizeof(svdrectarea.codrecurso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ret);
        init = 1;
    }
}

static void init_selretvdrectarea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrectarea[0].numcol;nc++) dvdrectarea[0].c[nc].offset-=(size_t)&svdrectarea;
    vdselretvdrectarea=abrecursordebug(SELRETVDRECTAREA,1280);
    definetodo(vdselretvdrectarea,svdrectarea.rowid,sizeof(svdrectarea.rowid),V10CADENA,
                          svdrectarea.codrecurso,sizeof(svdrectarea.codrecurso),V10CADENA,
                          svdrectarea.codperfil,sizeof(svdrectarea.codperfil),V10CADENA,
                          &svdrectarea.priotarea,sizeof(svdrectarea.priotarea),V10LONG,
                          svdrectarea.activa,sizeof(svdrectarea.activa),V10CADENA,
                          &svdrectarea.codcomen,sizeof(svdrectarea.codcomen),V10LONG,
                          svdrectarea.codopemodif,sizeof(svdrectarea.codopemodif),V10CADENA,
                          &svdrectarea.fecmodif,sizeof(svdrectarea.fecmodif),V10LONG,
                          svdrectarea.horamodif,sizeof(svdrectarea.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselretvdrectarea,"CODRECURSO",svdrectarea.codrecurso,sizeof(svdrectarea.codrecurso),V10CADENA,
                          "CODPERFIL",svdrectarea.codperfil,sizeof(svdrectarea.codperfil),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ret);
        init = 1;
    }
}

diccionario *RETdamediccionario(void)
{
     return(&dret);
}

int RETbuscacodrecurso(char *codrecurso,vdrectareas *ret)
{
  int vdret;
  memset(&svdrectarea,0,sizeof(svdrectarea));
  strcpy(svdrectarea.codrecurso,codrecurso);
  if (vdselretcodrecurso==NULL) init_selretcodrecurso();
  vdret=ejefetchcursor(vdselretcodrecurso);
  if (vdret==0) {
     *ret=svdrectarea;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselretcodrecurso. vdret %d. \n",RETlog(&svdrectarea),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int RETnextcodrecurso(vdrectareas *ret)
{
  int vdret;
  vdret=fetchcursor(vdselretcodrecurso);
  if (vdret==0) {
     *ret=svdrectarea;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselretcodrecurso. vdret %d. \n",RETlog(&svdrectarea),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselretcodrecurso);
  return(VD_EERRORACLE);
}

int RETselvdrectarea(char *codrecurso,char *codperfil,vdrectareas *ret)
{
  int vdret;
  if (vdselretvdrectarea==NULL) init_selretvdrectarea();
  memset(&svdrectarea,0,sizeof(svdrectarea));
  strcpy(svdrectarea.codrecurso,codrecurso);
  strcpy(svdrectarea.codperfil,codperfil);
  vdret=ejefetchcursor(vdselretvdrectarea);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselretvdrectarea. vdret %d. \n",RETlog(&svdrectarea),vdret);
    return(VD_EERRORACLE);
   }
  *ret=svdrectarea;
  return(vdret);
}

char * RETlog(vdrectareas *ret)
{
    sprintf(msglogRET, "VDRECTAREA: codrecurso %s codperfil %s ",ret->codrecurso,ret->codperfil);
    return(msglogRET);
}

char * RETdebug(vdrectareas *ret)
{
    debugestruct(&dret,ret,msgdebugRET);
    return(msgdebugRET);
}

