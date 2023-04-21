// Modulo generado automaticamente a partir de VDGRUPOSERV.DEF
//# M�dulo : VDGRUPOSERV.DEF
//# Funci�n: Generaci�n automatica de rutinas C tabla VDGRUPOSERV
//#
//# Autor	 : EAA
//# Revisado por:
//# Fecha  : 12-06-2008
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=GRS
//
//PRIMARIA=CODGRUPOSERV
//
//CLAVE=CODGRUPOSERV,CODGRUPOSERV
//
//RECORRE=ORDENADOR,ORDENADOR

#include "vd.h"
#define SELGRSCODGRUPOSERV "SELECT VDGRUPOSERV.ROWID,VDGRUPOSERV.CODGRUPOSERV,VDGRUPOSERV.DESGRUPOSERV, "\
                    " VDGRUPOSERV.ORDENADOR,VDGRUPOSERV.ARRANQUE,VDGRUPOSERV.PATHGRUPO, "\
                    " VDGRUPOSERV.PATHV10GRUPO,VDGRUPOSERV.ENVGRUPO,VDGRUPOSERV.PARAMGRUPO, "\
                    " VDGRUPOSERV.CODOPEMODIF,VDGRUPOSERV.FECMODIF,VDGRUPOSERV.HORAMODIF, "\
                    " VDGRUPOSERV.CODCOMEN "\
        " FROM VDGRUPOSERV"\
        " WHERE "\
               " VDGRUPOSERV.CODGRUPOSERV=:CODGRUPOSERV "
static v10cursors *vdselgrscodgruposerv;

#define SELGRSORDENADOR "SELECT VDGRUPOSERV.ROWID,VDGRUPOSERV.CODGRUPOSERV,VDGRUPOSERV.DESGRUPOSERV, "\
                    " VDGRUPOSERV.ORDENADOR,VDGRUPOSERV.ARRANQUE,VDGRUPOSERV.PATHGRUPO, "\
                    " VDGRUPOSERV.PATHV10GRUPO,VDGRUPOSERV.ENVGRUPO,VDGRUPOSERV.PARAMGRUPO, "\
                    " VDGRUPOSERV.CODOPEMODIF,VDGRUPOSERV.FECMODIF,VDGRUPOSERV.HORAMODIF, "\
                    " VDGRUPOSERV.CODCOMEN "\
        " FROM VDGRUPOSERV"\
        " WHERE "\
               " VDGRUPOSERV.ORDENADOR=:ORDENADOR "\
        " ORDER BY VDGRUPOSERV.CODGRUPOSERV"
static v10cursors *vdselgrsordenador;

#define SELGRSVDGRUPOSERV "SELECT VDGRUPOSERV.ROWID,VDGRUPOSERV.CODGRUPOSERV,VDGRUPOSERV.DESGRUPOSERV, "\
                    " VDGRUPOSERV.ORDENADOR,VDGRUPOSERV.ARRANQUE,VDGRUPOSERV.PATHGRUPO, "\
                    " VDGRUPOSERV.PATHV10GRUPO,VDGRUPOSERV.ENVGRUPO,VDGRUPOSERV.PARAMGRUPO, "\
                    " VDGRUPOSERV.CODOPEMODIF,VDGRUPOSERV.FECMODIF,VDGRUPOSERV.HORAMODIF, "\
                    " VDGRUPOSERV.CODCOMEN "\
        " FROM VDGRUPOSERV"\
        " WHERE "\
               " VDGRUPOSERV.CODGRUPOSERV=:CODGRUPOSERV "
static v10cursors *vdselgrsvdgruposerv;

static vdgruposervs svdgruposerv;

static diccols colvdgruposerv[]={
	{"ROWID",V10CADENA,(size_t)&svdgruposerv.rowid,sizeof(svdgruposerv.rowid)},
	{"CODGRUPOSERV",V10CADENA,(size_t)&svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv)},
	{"DESGRUPOSERV",V10CADENA,(size_t)&svdgruposerv.desgruposerv,sizeof(svdgruposerv.desgruposerv)},
	{"ORDENADOR",V10CADENA,(size_t)&svdgruposerv.ordenador,sizeof(svdgruposerv.ordenador)},
	{"ARRANQUE",V10CADENA,(size_t)&svdgruposerv.arranque,sizeof(svdgruposerv.arranque)},
	{"PATHGRUPO",V10CADENA,(size_t)&svdgruposerv.pathgrupo,sizeof(svdgruposerv.pathgrupo)},
	{"PATHV10GRUPO",V10CADENA,(size_t)&svdgruposerv.pathv10grupo,sizeof(svdgruposerv.pathv10grupo)},
	{"ENVGRUPO",V10CADENA,(size_t)&svdgruposerv.envgrupo,sizeof(svdgruposerv.envgrupo)},
	{"PARAMGRUPO",V10CADENA,(size_t)&svdgruposerv.paramgrupo,sizeof(svdgruposerv.paramgrupo)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdgruposerv.codopemodif,sizeof(svdgruposerv.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdgruposerv.fecmodif,sizeof(svdgruposerv.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdgruposerv.horamodif,sizeof(svdgruposerv.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdgruposerv.codcomen,sizeof(svdgruposerv.codcomen)}
	};
static diccionarios dvdgruposerv[]={
    {colvdgruposerv,13}
};
diccionario dgrs={dvdgruposerv,1};

static char msglogGRS[LCADENA];
static char msgdebugGRS[LCADENABIG];
static int init=0;


static void fin_vd_grs(void)
{
if (vdselgrscodgruposerv) {
    liberacursor(vdselgrscodgruposerv);
    vdselgrscodgruposerv = NULL;
}
if (vdselgrsordenador) {
    liberacursor(vdselgrsordenador);
    vdselgrsordenador = NULL;
}
if (vdselgrsvdgruposerv) {
    liberacursor(vdselgrsvdgruposerv);
    vdselgrsvdgruposerv = NULL;
}
}
static void init_selgrscodgruposerv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgruposerv[0].numcol;nc++) dvdgruposerv[0].c[nc].offset-=(size_t)&svdgruposerv;
    vdselgrscodgruposerv=abrecursordebug(SELGRSCODGRUPOSERV,1280);
    definetodo(vdselgrscodgruposerv,svdgruposerv.rowid,sizeof(svdgruposerv.rowid),V10CADENA,
                          svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv),V10CADENA,
                          svdgruposerv.desgruposerv,sizeof(svdgruposerv.desgruposerv),V10CADENA,
                          svdgruposerv.ordenador,sizeof(svdgruposerv.ordenador),V10CADENA,
                          svdgruposerv.arranque,sizeof(svdgruposerv.arranque),V10CADENA,
                          svdgruposerv.pathgrupo,sizeof(svdgruposerv.pathgrupo),V10CADENA,
                          svdgruposerv.pathv10grupo,sizeof(svdgruposerv.pathv10grupo),V10CADENA,
                          svdgruposerv.envgrupo,sizeof(svdgruposerv.envgrupo),V10CADENA,
                          svdgruposerv.paramgrupo,sizeof(svdgruposerv.paramgrupo),V10CADENA,
                          svdgruposerv.codopemodif,sizeof(svdgruposerv.codopemodif),V10CADENA,
                          &svdgruposerv.fecmodif,sizeof(svdgruposerv.fecmodif),V10LONG,
                          svdgruposerv.horamodif,sizeof(svdgruposerv.horamodif),V10CADENA,
                          &svdgruposerv.codcomen,sizeof(svdgruposerv.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselgrscodgruposerv,"CODGRUPOSERV",svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_grs);
        init = 1;
    }
}

static void init_selgrsordenador(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgruposerv[0].numcol;nc++) dvdgruposerv[0].c[nc].offset-=(size_t)&svdgruposerv;
    vdselgrsordenador=abrecursordebug(SELGRSORDENADOR,1280);
    definetodo(vdselgrsordenador,svdgruposerv.rowid,sizeof(svdgruposerv.rowid),V10CADENA,
                          svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv),V10CADENA,
                          svdgruposerv.desgruposerv,sizeof(svdgruposerv.desgruposerv),V10CADENA,
                          svdgruposerv.ordenador,sizeof(svdgruposerv.ordenador),V10CADENA,
                          svdgruposerv.arranque,sizeof(svdgruposerv.arranque),V10CADENA,
                          svdgruposerv.pathgrupo,sizeof(svdgruposerv.pathgrupo),V10CADENA,
                          svdgruposerv.pathv10grupo,sizeof(svdgruposerv.pathv10grupo),V10CADENA,
                          svdgruposerv.envgrupo,sizeof(svdgruposerv.envgrupo),V10CADENA,
                          svdgruposerv.paramgrupo,sizeof(svdgruposerv.paramgrupo),V10CADENA,
                          svdgruposerv.codopemodif,sizeof(svdgruposerv.codopemodif),V10CADENA,
                          &svdgruposerv.fecmodif,sizeof(svdgruposerv.fecmodif),V10LONG,
                          svdgruposerv.horamodif,sizeof(svdgruposerv.horamodif),V10CADENA,
                          &svdgruposerv.codcomen,sizeof(svdgruposerv.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselgrsordenador,"ORDENADOR",svdgruposerv.ordenador,sizeof(svdgruposerv.ordenador),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_grs);
        init = 1;
    }
}

static void init_selgrsvdgruposerv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgruposerv[0].numcol;nc++) dvdgruposerv[0].c[nc].offset-=(size_t)&svdgruposerv;
    vdselgrsvdgruposerv=abrecursordebug(SELGRSVDGRUPOSERV,1280);
    definetodo(vdselgrsvdgruposerv,svdgruposerv.rowid,sizeof(svdgruposerv.rowid),V10CADENA,
                          svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv),V10CADENA,
                          svdgruposerv.desgruposerv,sizeof(svdgruposerv.desgruposerv),V10CADENA,
                          svdgruposerv.ordenador,sizeof(svdgruposerv.ordenador),V10CADENA,
                          svdgruposerv.arranque,sizeof(svdgruposerv.arranque),V10CADENA,
                          svdgruposerv.pathgrupo,sizeof(svdgruposerv.pathgrupo),V10CADENA,
                          svdgruposerv.pathv10grupo,sizeof(svdgruposerv.pathv10grupo),V10CADENA,
                          svdgruposerv.envgrupo,sizeof(svdgruposerv.envgrupo),V10CADENA,
                          svdgruposerv.paramgrupo,sizeof(svdgruposerv.paramgrupo),V10CADENA,
                          svdgruposerv.codopemodif,sizeof(svdgruposerv.codopemodif),V10CADENA,
                          &svdgruposerv.fecmodif,sizeof(svdgruposerv.fecmodif),V10LONG,
                          svdgruposerv.horamodif,sizeof(svdgruposerv.horamodif),V10CADENA,
                          &svdgruposerv.codcomen,sizeof(svdgruposerv.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselgrsvdgruposerv,"CODGRUPOSERV",svdgruposerv.codgruposerv,sizeof(svdgruposerv.codgruposerv),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_grs);
        init = 1;
    }
}

diccionario *GRSdamediccionario(void)
{
     return(&dgrs);
}

int GRSselcodgruposerv(char *codgruposerv,vdgruposervs *grs)
{
  int vdret;
  if (vdselgrscodgruposerv==NULL) init_selgrscodgruposerv();
  memset(&svdgruposerv,0,sizeof(svdgruposerv));
  strcpy(svdgruposerv.codgruposerv,codgruposerv);
  vdret=ejefetchcursor(vdselgrscodgruposerv);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselgrscodgruposerv. vdret %d. \n",GRSlog(&svdgruposerv),vdret);
    return(VD_EERRORACLE);
   }
  *grs=svdgruposerv;
  return(vdret);
}

int GRSbuscaordenador(char *ordenador,vdgruposervs *grs)
{
  int vdret;
  memset(&svdgruposerv,0,sizeof(svdgruposerv));
  strcpy(svdgruposerv.ordenador,ordenador);
  if (vdselgrsordenador==NULL) init_selgrsordenador();
  vdret=ejefetchcursor(vdselgrsordenador);
  if (vdret==0) {
     *grs=svdgruposerv;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselgrsordenador. vdret %d. \n",GRSlog(&svdgruposerv),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int GRSnextordenador(vdgruposervs *grs)
{
  int vdret;
  vdret=fetchcursor(vdselgrsordenador);
  if (vdret==0) {
     *grs=svdgruposerv;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselgrsordenador. vdret %d. \n",GRSlog(&svdgruposerv),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselgrsordenador);
  return(VD_EERRORACLE);
}

int GRSselvdgruposerv(char *codgruposerv,vdgruposervs *grs)
{
  int vdret;
  if (vdselgrsvdgruposerv==NULL) init_selgrsvdgruposerv();
  memset(&svdgruposerv,0,sizeof(svdgruposerv));
  strcpy(svdgruposerv.codgruposerv,codgruposerv);
  vdret=ejefetchcursor(vdselgrsvdgruposerv);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselgrsvdgruposerv. vdret %d. \n",GRSlog(&svdgruposerv),vdret);
    return(VD_EERRORACLE);
   }
  *grs=svdgruposerv;
  return(vdret);
}

char * GRSlog(vdgruposervs *grs)
{
    sprintf(msglogGRS, "VDGRUPOSERV: codgruposerv %s ",grs->codgruposerv);
    return(msglogGRS);
}

char * GRSdebug(vdgruposervs *grs)
{
    debugestruct(&dgrs,grs,msgdebugGRS);
    return(msgdebugGRS);
}

