// Modulo generado automaticamente a partir de VDPROCESOS.DEF
//# Módulo : VDPROCESOS.def                                                         
//#
//# Propósito: Funciones de acceso a la tabla VDPROCESOS
//#
//# Autor	 : JCSR
//# Revisado por:
//# Fecha  : 24-01-2008
//#********************************************************************************
//# Modificaciones
//#***
//
//TABLE=PRO
//UPDATE=EJECUTAINMEDIATO,EJECUTAINMEDIATO
//
//CLAVE=EJECUTAINMEDIATO,PROCESO,WHERE=VDPROCESOS.EJECUTAINMEDIATO IS NOT NULL;

#include "vd.h"
#define SELPROEJECUTAINMEDIATO "SELECT VDPROCESOS.ROWID,VDPROCESOS.GRUPOPROC,VDPROCESOS.PROCESO, "\
                    " VDPROCESOS.PARAM,VDPROCESOS.FUNCIONPROC,VDPROCESOS.LIBPROCESO, "\
                    " VDPROCESOS.ORDENACION,VDPROCESOS.PERIODO,VDPROCESOS.CODSEMAFORO, "\
                    " VDPROCESOS.EJECUCIONES,VDPROCESOS.EJECUTAINMEDIATO,VDPROCESOS.INFOEXTRA, "\
                    " VDPROCESOS.CODCOMEN,VDPROCESOS.CODOPEMODIF,VDPROCESOS.FECMODIF, "\
                    " VDPROCESOS.HORAMODIF,VDPROCESOS.ACTIVO "\
        " FROM VDPROCESOS"\
        " WHERE "\
               " VDPROCESOS.PROCESO=:PROCESO "\
              "  AND VDPROCESOS.EJECUTAINMEDIATO IS NOT NULL "
static v10cursors *vdselproejecutainmediato;

#define SELPROVDPROCESOS "SELECT VDPROCESOS.ROWID,VDPROCESOS.GRUPOPROC,VDPROCESOS.PROCESO, "\
                    " VDPROCESOS.PARAM,VDPROCESOS.FUNCIONPROC,VDPROCESOS.LIBPROCESO, "\
                    " VDPROCESOS.ORDENACION,VDPROCESOS.PERIODO,VDPROCESOS.CODSEMAFORO, "\
                    " VDPROCESOS.EJECUCIONES,VDPROCESOS.EJECUTAINMEDIATO,VDPROCESOS.INFOEXTRA, "\
                    " VDPROCESOS.CODCOMEN,VDPROCESOS.CODOPEMODIF,VDPROCESOS.FECMODIF, "\
                    " VDPROCESOS.HORAMODIF,VDPROCESOS.ACTIVO "\
        " FROM VDPROCESOS"\
        " WHERE "\
               " VDPROCESOS.PROCESO=:PROCESO "
static v10cursors *vdselprovdprocesos;

#define UPDAPROEJECUTAINMEDIATO "UPDATE VDPROCESOS SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " EJECUTAINMEDIATO=:EJECUTAINMEDIATO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaproejecutainmediato;

static vdprocesoss svdprocesos;

static diccols colvdprocesos[]={
	{"ROWID",V10CADENA,(size_t)&svdprocesos.rowid,sizeof(svdprocesos.rowid)},
	{"GRUPOPROC",V10CADENA,(size_t)&svdprocesos.grupoproc,sizeof(svdprocesos.grupoproc)},
	{"PROCESO",V10CADENA,(size_t)&svdprocesos.proceso,sizeof(svdprocesos.proceso)},
	{"PARAM",V10CADENA,(size_t)&svdprocesos.param,sizeof(svdprocesos.param)},
	{"FUNCIONPROC",V10CADENA,(size_t)&svdprocesos.funcionproc,sizeof(svdprocesos.funcionproc)},
	{"LIBPROCESO",V10CADENA,(size_t)&svdprocesos.libproceso,sizeof(svdprocesos.libproceso)},
	{"ORDENACION",V10LONG,(size_t)&svdprocesos.ordenacion,sizeof(svdprocesos.ordenacion)},
	{"PERIODO",V10LONG,(size_t)&svdprocesos.periodo,sizeof(svdprocesos.periodo)},
	{"CODSEMAFORO",V10CADENA,(size_t)&svdprocesos.codsemaforo,sizeof(svdprocesos.codsemaforo)},
	{"EJECUCIONES",V10LONG,(size_t)&svdprocesos.ejecuciones,sizeof(svdprocesos.ejecuciones)},
	{"EJECUTAINMEDIATO",V10CADENA,(size_t)&svdprocesos.ejecutainmediato,sizeof(svdprocesos.ejecutainmediato)},
	{"INFOEXTRA",V10CADENA,(size_t)&svdprocesos.infoextra,sizeof(svdprocesos.infoextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdprocesos.codcomen,sizeof(svdprocesos.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdprocesos.codopemodif,sizeof(svdprocesos.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdprocesos.fecmodif,sizeof(svdprocesos.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdprocesos.horamodif,sizeof(svdprocesos.horamodif)},
	{"ACTIVO",V10CADENA,(size_t)&svdprocesos.activo,sizeof(svdprocesos.activo)}
	};
static diccionarios dvdprocesos[]={
    {colvdprocesos,17}
};
diccionario dpro={dvdprocesos,1};

static char msglogPRO[LCADENA];
static char msgdebugPRO[LCADENABIG];
static int init=0;


static void fin_vd_pro(void)
{
if (vdselproejecutainmediato) {
    liberacursor(vdselproejecutainmediato);
    vdselproejecutainmediato = NULL;
}
if (vdselprovdprocesos) {
    liberacursor(vdselprovdprocesos);
    vdselprovdprocesos = NULL;
}
if (vdupdaproejecutainmediato) {
    liberacursor(vdupdaproejecutainmediato);
    vdupdaproejecutainmediato = NULL;
}
}
static void init_selproejecutainmediato(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdprocesos[0].numcol;nc++) dvdprocesos[0].c[nc].offset-=(size_t)&svdprocesos;
    vdselproejecutainmediato=abrecursordebug(SELPROEJECUTAINMEDIATO,1280);
    definetodo(vdselproejecutainmediato,svdprocesos.rowid,sizeof(svdprocesos.rowid),V10CADENA,
                          svdprocesos.grupoproc,sizeof(svdprocesos.grupoproc),V10CADENA,
                          svdprocesos.proceso,sizeof(svdprocesos.proceso),V10CADENA,
                          svdprocesos.param,sizeof(svdprocesos.param),V10CADENA,
                          svdprocesos.funcionproc,sizeof(svdprocesos.funcionproc),V10CADENA,
                          svdprocesos.libproceso,sizeof(svdprocesos.libproceso),V10CADENA,
                          &svdprocesos.ordenacion,sizeof(svdprocesos.ordenacion),V10LONG,
                          &svdprocesos.periodo,sizeof(svdprocesos.periodo),V10LONG,
                          svdprocesos.codsemaforo,sizeof(svdprocesos.codsemaforo),V10CADENA,
                          &svdprocesos.ejecuciones,sizeof(svdprocesos.ejecuciones),V10LONG,
                          svdprocesos.ejecutainmediato,sizeof(svdprocesos.ejecutainmediato),V10CADENA,
                          svdprocesos.infoextra,sizeof(svdprocesos.infoextra),V10CADENA,
                          &svdprocesos.codcomen,sizeof(svdprocesos.codcomen),V10LONG,
                          svdprocesos.codopemodif,sizeof(svdprocesos.codopemodif),V10CADENA,
                          &svdprocesos.fecmodif,sizeof(svdprocesos.fecmodif),V10LONG,
                          svdprocesos.horamodif,sizeof(svdprocesos.horamodif),V10CADENA,
                          svdprocesos.activo,sizeof(svdprocesos.activo),V10CADENA,
                          NULL);
    bindtodo(vdselproejecutainmediato,"PROCESO",svdprocesos.proceso,sizeof(svdprocesos.proceso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pro);
        init = 1;
    }
}

static void init_selprovdprocesos(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdprocesos[0].numcol;nc++) dvdprocesos[0].c[nc].offset-=(size_t)&svdprocesos;
    vdselprovdprocesos=abrecursordebug(SELPROVDPROCESOS,1280);
    definetodo(vdselprovdprocesos,svdprocesos.rowid,sizeof(svdprocesos.rowid),V10CADENA,
                          svdprocesos.grupoproc,sizeof(svdprocesos.grupoproc),V10CADENA,
                          svdprocesos.proceso,sizeof(svdprocesos.proceso),V10CADENA,
                          svdprocesos.param,sizeof(svdprocesos.param),V10CADENA,
                          svdprocesos.funcionproc,sizeof(svdprocesos.funcionproc),V10CADENA,
                          svdprocesos.libproceso,sizeof(svdprocesos.libproceso),V10CADENA,
                          &svdprocesos.ordenacion,sizeof(svdprocesos.ordenacion),V10LONG,
                          &svdprocesos.periodo,sizeof(svdprocesos.periodo),V10LONG,
                          svdprocesos.codsemaforo,sizeof(svdprocesos.codsemaforo),V10CADENA,
                          &svdprocesos.ejecuciones,sizeof(svdprocesos.ejecuciones),V10LONG,
                          svdprocesos.ejecutainmediato,sizeof(svdprocesos.ejecutainmediato),V10CADENA,
                          svdprocesos.infoextra,sizeof(svdprocesos.infoextra),V10CADENA,
                          &svdprocesos.codcomen,sizeof(svdprocesos.codcomen),V10LONG,
                          svdprocesos.codopemodif,sizeof(svdprocesos.codopemodif),V10CADENA,
                          &svdprocesos.fecmodif,sizeof(svdprocesos.fecmodif),V10LONG,
                          svdprocesos.horamodif,sizeof(svdprocesos.horamodif),V10CADENA,
                          svdprocesos.activo,sizeof(svdprocesos.activo),V10CADENA,
                          NULL);
    bindtodo(vdselprovdprocesos,"PROCESO",svdprocesos.proceso,sizeof(svdprocesos.proceso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pro);
        init = 1;
    }
}

static void init_updaproejecutainmediato(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdprocesos[0].numcol;nc++) dvdprocesos[0].c[nc].offset-=(size_t)&svdprocesos;
    vdupdaproejecutainmediato=abrecursordebug(UPDAPROEJECUTAINMEDIATO,1280);
    bindtodo(vdupdaproejecutainmediato,"EJECUTAINMEDIATO",svdprocesos.ejecutainmediato,sizeof(svdprocesos.ejecutainmediato),V10CADENA,
                          "MIROWID",svdprocesos.rowid,sizeof(svdprocesos.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pro);
        init = 1;
    }
}

diccionario *PROdamediccionario(void)
{
     return(&dpro);
}

int PROselejecutainmediato(char *proceso,vdprocesoss *pro)
{
  int vdret;
  if (vdselproejecutainmediato==NULL) init_selproejecutainmediato();
  memset(&svdprocesos,0,sizeof(svdprocesos));
  strcpy(svdprocesos.proceso,proceso);
  vdret=ejefetchcursor(vdselproejecutainmediato);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselproejecutainmediato. vdret %d. \n",PROlog(&svdprocesos),vdret);
    return(VD_EERRORACLE);
   }
  *pro=svdprocesos;
  return(vdret);
}

int PROselvdprocesos(char *proceso,vdprocesoss *pro)
{
  int vdret;
  if (vdselprovdprocesos==NULL) init_selprovdprocesos();
  memset(&svdprocesos,0,sizeof(svdprocesos));
  strcpy(svdprocesos.proceso,proceso);
  vdret=ejefetchcursor(vdselprovdprocesos);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselprovdprocesos. vdret %d. \n",PROlog(&svdprocesos),vdret);
    return(VD_EERRORACLE);
   }
  *pro=svdprocesos;
  return(vdret);
}

int PROactualizaejecutainmediato(vdprocesoss *pro,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando PROactualizaejecutainmediato:  %s .  \n",PROlog(&svdprocesos));
  if (vdupdaproejecutainmediato==NULL) init_updaproejecutainmediato();
  svdprocesos=*pro;
  vdret=ejecutacursor(vdupdaproejecutainmediato);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaproejecutainmediato);
     getcurerrornombre(vdupdaproejecutainmediato->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaproejecutainmediato)!=1) return(VD_EERRORACLE);
  return(0);
}

char * PROlog(vdprocesoss *pro)
{
    sprintf(msglogPRO, "VDPROCESOS: proceso %s ",pro->proceso);
    return(msglogPRO);
}

char * PROdebug(vdprocesoss *pro)
{
    debugestruct(&dpro,pro,msgdebugPRO);
    return(msgdebugPRO);
}

