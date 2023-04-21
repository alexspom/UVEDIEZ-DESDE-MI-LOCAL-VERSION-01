// Modulo generado automaticamente a partir de VDSCANNUMSERIE.DEF
//#***
//# VDNUMSERIELEIDOS.c - Generaci�n autom�tica del c�digo c para la tabla VDNUMSERIELEIDOS                                              
//# 
//# Prop�sito: Funciones de acceso a la tabla VDNUMSERIELEIDOS
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 12-01-2010
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=NSL
//
//CLAVE=CONTNS, CODMAT, GENCOUNT=NUMEROSERIE;
//
//RECORRE=CODMAT,CODMAT;
//DELETE;
//

#include "vd.h"
#define SELNSLCONTNS "SELECT COUNT(DISTINCT NUMEROSERIE) GENCOUNT "\
        " FROM VDSCANNUMSERIE"\
        " WHERE "\
               " VDSCANNUMSERIE.CODMAT=:CODMAT "
static v10cursors *vdselnslcontns;

#define SELNSLCODMAT "SELECT VDSCANNUMSERIE.ROWID,VDSCANNUMSERIE.CODOPE,VDSCANNUMSERIE.CODRECURSO, "\
                    " VDSCANNUMSERIE.CODZONA,VDSCANNUMSERIE.NUMEROSERIE,VDSCANNUMSERIE.CODMAT, "\
                    " VDSCANNUMSERIE.RECEPCIONADO,VDSCANNUMSERIE.CODOPEMODIF,VDSCANNUMSERIE.FECMODIF, "\
                    " VDSCANNUMSERIE.HORAMODIF "\
        " FROM VDSCANNUMSERIE"\
        " WHERE "\
               " VDSCANNUMSERIE.CODMAT=:CODMAT "
static v10cursors *vdselnslcodmat;

#define SELNSLVDSCANNUMSERIE "SELECT VDSCANNUMSERIE.ROWID,VDSCANNUMSERIE.CODOPE,VDSCANNUMSERIE.CODRECURSO, "\
                    " VDSCANNUMSERIE.CODZONA,VDSCANNUMSERIE.NUMEROSERIE,VDSCANNUMSERIE.CODMAT, "\
                    " VDSCANNUMSERIE.RECEPCIONADO,VDSCANNUMSERIE.CODOPEMODIF,VDSCANNUMSERIE.FECMODIF, "\
                    " VDSCANNUMSERIE.HORAMODIF "\
        " FROM VDSCANNUMSERIE"
static v10cursors *vdselnslvdscannumserie;

#define DELNSL "DELETE VDSCANNUMSERIE WHERE ROWID=:MIROWID "
static v10cursors *vddelnsl;

static vdscannumseries svdscannumserie;

static diccols colvdscannumserie[]={
	{"ROWID",V10CADENA,(size_t)&svdscannumserie.rowid,sizeof(svdscannumserie.rowid)},
	{"CODOPE",V10CADENA,(size_t)&svdscannumserie.codope,sizeof(svdscannumserie.codope)},
	{"CODRECURSO",V10CADENA,(size_t)&svdscannumserie.codrecurso,sizeof(svdscannumserie.codrecurso)},
	{"CODZONA",V10LONG,(size_t)&svdscannumserie.codzona,sizeof(svdscannumserie.codzona)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdscannumserie.numeroserie,sizeof(svdscannumserie.numeroserie)},
	{"CODMAT",V10CADENA,(size_t)&svdscannumserie.codmat,sizeof(svdscannumserie.codmat)},
	{"RECEPCIONADO",V10CADENA,(size_t)&svdscannumserie.recepcionado,sizeof(svdscannumserie.recepcionado)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdscannumserie.codopemodif,sizeof(svdscannumserie.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdscannumserie.fecmodif,sizeof(svdscannumserie.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdscannumserie.horamodif,sizeof(svdscannumserie.horamodif)},
	{"GENCOUNT",V10DOUBLE,(size_t)&svdscannumserie.gencount,sizeof(svdscannumserie.gencount)}
	};
static diccionarios dvdscannumserie[]={
    {colvdscannumserie,11}
};
diccionario dnsl={dvdscannumserie,1};

static char msglogNSL[LCADENA];
static char msgdebugNSL[LCADENABIG];
static int init=0;


static void fin_vd_nsl(void)
{
if (vdselnslcontns) {
    liberacursor(vdselnslcontns);
    vdselnslcontns = NULL;
}
if (vdselnslcodmat) {
    liberacursor(vdselnslcodmat);
    vdselnslcodmat = NULL;
}
if (vdselnslvdscannumserie) {
    liberacursor(vdselnslvdscannumserie);
    vdselnslvdscannumserie = NULL;
}
if (vddelnsl != NULL) {
    liberacursor(vddelnsl);
    vddelnsl = NULL;
}
}
static void init_selnslcontns(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscannumserie[0].numcol;nc++) dvdscannumserie[0].c[nc].offset-=(size_t)&svdscannumserie;
    vdselnslcontns=abrecursordebug(SELNSLCONTNS,1280);
    definetodo(vdselnslcontns,&svdscannumserie.gencount,sizeof(svdscannumserie.gencount),V10DOUBLE,
                          NULL);
    bindtodo(vdselnslcontns,"CODMAT",svdscannumserie.codmat,sizeof(svdscannumserie.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_nsl);
        init = 1;
    }
}

static void init_selnslcodmat(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscannumserie[0].numcol;nc++) dvdscannumserie[0].c[nc].offset-=(size_t)&svdscannumserie;
    vdselnslcodmat=abrecursordebug(SELNSLCODMAT,1280);
    definetodo(vdselnslcodmat,svdscannumserie.rowid,sizeof(svdscannumserie.rowid),V10CADENA,
                          svdscannumserie.codope,sizeof(svdscannumserie.codope),V10CADENA,
                          svdscannumserie.codrecurso,sizeof(svdscannumserie.codrecurso),V10CADENA,
                          &svdscannumserie.codzona,sizeof(svdscannumserie.codzona),V10LONG,
                          svdscannumserie.numeroserie,sizeof(svdscannumserie.numeroserie),V10CADENA,
                          svdscannumserie.codmat,sizeof(svdscannumserie.codmat),V10CADENA,
                          svdscannumserie.recepcionado,sizeof(svdscannumserie.recepcionado),V10CADENA,
                          svdscannumserie.codopemodif,sizeof(svdscannumserie.codopemodif),V10CADENA,
                          &svdscannumserie.fecmodif,sizeof(svdscannumserie.fecmodif),V10LONG,
                          svdscannumserie.horamodif,sizeof(svdscannumserie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselnslcodmat,"CODMAT",svdscannumserie.codmat,sizeof(svdscannumserie.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_nsl);
        init = 1;
    }
}

static void init_selnslvdscannumserie(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscannumserie[0].numcol;nc++) dvdscannumserie[0].c[nc].offset-=(size_t)&svdscannumserie;
    vdselnslvdscannumserie=abrecursordebug(SELNSLVDSCANNUMSERIE,1280);
    definetodo(vdselnslvdscannumserie,svdscannumserie.rowid,sizeof(svdscannumserie.rowid),V10CADENA,
                          svdscannumserie.codope,sizeof(svdscannumserie.codope),V10CADENA,
                          svdscannumserie.codrecurso,sizeof(svdscannumserie.codrecurso),V10CADENA,
                          &svdscannumserie.codzona,sizeof(svdscannumserie.codzona),V10LONG,
                          svdscannumserie.numeroserie,sizeof(svdscannumserie.numeroserie),V10CADENA,
                          svdscannumserie.codmat,sizeof(svdscannumserie.codmat),V10CADENA,
                          svdscannumserie.recepcionado,sizeof(svdscannumserie.recepcionado),V10CADENA,
                          svdscannumserie.codopemodif,sizeof(svdscannumserie.codopemodif),V10CADENA,
                          &svdscannumserie.fecmodif,sizeof(svdscannumserie.fecmodif),V10LONG,
                          svdscannumserie.horamodif,sizeof(svdscannumserie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselnslvdscannumserie,NULL);
    if (init == 0) {
        atexit(fin_vd_nsl);
        init = 1;
    }
}

static void init_delnsl(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscannumserie[0].numcol;nc++) dvdscannumserie[0].c[nc].offset-=(size_t)&svdscannumserie;
    vddelnsl=abrecursordebug(DELNSL,1280);
    bindtodo(vddelnsl,"MIROWID",svdscannumserie.rowid,sizeof(svdscannumserie.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_nsl);
        init = 1;
    }
}

diccionario *NSLdamediccionario(void)
{
     return(&dnsl);
}

int NSLselcontns(char *codmat,vdscannumseries *nsl)
{
  int vdret;
  if (vdselnslcontns==NULL) init_selnslcontns();
  memset(&svdscannumserie,0,sizeof(svdscannumserie));
  strcpy(svdscannumserie.codmat,codmat);
  vdret=ejefetchcursor(vdselnslcontns);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselnslcontns. vdret %d. \n",NSLlog(&svdscannumserie),vdret);
    return(VD_EERRORACLE);
   }
  *nsl=svdscannumserie;
  return(vdret);
}

int NSLbuscacodmat(char *codmat,vdscannumseries *nsl)
{
  int vdret;
  memset(&svdscannumserie,0,sizeof(svdscannumserie));
  strcpy(svdscannumserie.codmat,codmat);
  if (vdselnslcodmat==NULL) init_selnslcodmat();
  vdret=ejefetchcursor(vdselnslcodmat);
  if (vdret==0) {
     *nsl=svdscannumserie;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselnslcodmat. vdret %d. \n",NSLlog(&svdscannumserie),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int NSLnextcodmat(vdscannumseries *nsl)
{
  int vdret;
  vdret=fetchcursor(vdselnslcodmat);
  if (vdret==0) {
     *nsl=svdscannumserie;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselnslcodmat. vdret %d. \n",NSLlog(&svdscannumserie),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselnslcodmat);
  return(VD_EERRORACLE);
}

int NSLselvdscannumserie(vdscannumseries *nsl)
{
  int vdret;
  if (vdselnslvdscannumserie==NULL) init_selnslvdscannumserie();
  memset(&svdscannumserie,0,sizeof(svdscannumserie));
  vdret=ejefetchcursor(vdselnslvdscannumserie);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselnslvdscannumserie. vdret %d. \n",NSLlog(&svdscannumserie),vdret);
    return(VD_EERRORACLE);
   }
  *nsl=svdscannumserie;
  return(vdret);
}

int NSLdel(vdscannumseries *nsl,int error)
{
  int vdret;
  svdscannumserie=*nsl;
  if (vddelnsl==NULL) init_delnsl();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",NSLlog(&svdscannumserie));
  vdret=ejecutacursor(vddelnsl);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelnsl);
     getcurerrornombre(vddelnsl->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * NSLlog(vdscannumseries *nsl)
{
    sprintf(msglogNSL, "VDSCANNUMSERIE: ");
    return(msglogNSL);
}

char * NSLdebug(vdscannumseries *nsl)
{
    debugestruct(&dnsl,nsl,msgdebugNSL);
    return(msgdebugNSL);
}

