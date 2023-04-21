// Modulo generado automaticamente a partir de VDSERIEPREP.DEF
//#***
//# VDSERIEPREP.c - Generación automática del código c para la tabla VDSERIEPREP                                                        
//# 
//# Propósito: Funciones de acceso a la tabla VDSERIEPREP
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 16-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=SPR
//EXTRA=COMENSPR,V10CADENA,1025
//
//RECORRE=STATUS,STATUS;
//UPDATE=STATUS,STATUS;
//LOCK
//
//

#include "vd.h"
#define SELSPRSTATUS "SELECT VDSERIEPREP.ROWID,VDSERIEPREP.CODSERIEPREP,VDSERIEPREP.PRIORIDAD, "\
                    " VDSERIEPREP.SWTPICKINGINV,VDSERIEPREP.SWTPICKINGAGR,VDSERIEPREP.DESSERIE, "\
                    " VDSERIEPREP.RANGOZONASPICKINV,VDSERIEPREP.TIPOPUERTO,VDSERIEPREP.CODOPECREADA, "\
                    " VDSERIEPREP.FECCREADA,VDSERIEPREP.HORACREADA,VDSERIEPREP.CODOPELANZA, "\
                    " VDSERIEPREP.FECLANZA,VDSERIEPREP.HORALANZA,VDSERIEPREP.FECTERMIN, "\
                    " VDSERIEPREP.HORATERMIN,VDSERIEPREP.STATUS,VDSERIEPREP.CODCOMEN, "\
                    " VDSERIEPREP.VDEXTRA,VDSERIEPREP.CODOPEMODIF,VDSERIEPREP.FECMODIF, "\
                    " VDSERIEPREP.HORAMODIF,VDSERIEPREP.CODOPECIERRE,VDSERIEPREP.FECCIERRE, "\
                    " VDSERIEPREP.HORACIERRE,VDSERIEPREP.SWTBLOQETIQ "\
        " FROM VDSERIEPREP"\
        " WHERE "\
               " VDSERIEPREP.STATUS=:STATUS "
static v10cursors *vdselsprstatus;

#define SELSPRVDSERIEPREP "SELECT VDSERIEPREP.ROWID,VDSERIEPREP.CODSERIEPREP,VDSERIEPREP.PRIORIDAD, "\
                    " VDSERIEPREP.SWTPICKINGINV,VDSERIEPREP.SWTPICKINGAGR,VDSERIEPREP.DESSERIE, "\
                    " VDSERIEPREP.RANGOZONASPICKINV,VDSERIEPREP.TIPOPUERTO,VDSERIEPREP.CODOPECREADA, "\
                    " VDSERIEPREP.FECCREADA,VDSERIEPREP.HORACREADA,VDSERIEPREP.CODOPELANZA, "\
                    " VDSERIEPREP.FECLANZA,VDSERIEPREP.HORALANZA,VDSERIEPREP.FECTERMIN, "\
                    " VDSERIEPREP.HORATERMIN,VDSERIEPREP.STATUS,VDSERIEPREP.CODCOMEN, "\
                    " VDSERIEPREP.VDEXTRA,VDSERIEPREP.CODOPEMODIF,VDSERIEPREP.FECMODIF, "\
                    " VDSERIEPREP.HORAMODIF,VDSERIEPREP.CODOPECIERRE,VDSERIEPREP.FECCIERRE, "\
                    " VDSERIEPREP.HORACIERRE,VDSERIEPREP.SWTBLOQETIQ "\
        " FROM VDSERIEPREP"\
        " WHERE "\
               " VDSERIEPREP.CODSERIEPREP=:CODSERIEPREP "
static v10cursors *vdselsprvdserieprep;

#define SELSPRROWIDLOCK "SELECT ROWID,CODSERIEPREP,PRIORIDAD,SWTPICKINGINV,SWTPICKINGAGR,DESSERIE,RANGOZONASPICKINV, "\
                    " TIPOPUERTO,CODOPECREADA,FECCREADA,HORACREADA,CODOPELANZA,FECLANZA,HORALANZA, "\
                    " FECTERMIN,HORATERMIN,STATUS,CODCOMEN,VDEXTRA,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF,CODOPECIERRE,FECCIERRE,HORACIERRE,SWTBLOQETIQ "\
        " FROM VDSERIEPREP "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselsprrowidlock;

#define UPDASPRSTATUS "UPDATE VDSERIEPREP SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdasprstatus;

static vdseriepreps svdserieprep;

static diccols colvdserieprep[]={
	{"ROWID",V10CADENA,(size_t)&svdserieprep.rowid,sizeof(svdserieprep.rowid)},
	{"CODSERIEPREP",V10LONG,(size_t)&svdserieprep.codserieprep,sizeof(svdserieprep.codserieprep)},
	{"PRIORIDAD",V10LONG,(size_t)&svdserieprep.prioridad,sizeof(svdserieprep.prioridad)},
	{"SWTPICKINGINV",V10CADENA,(size_t)&svdserieprep.swtpickinginv,sizeof(svdserieprep.swtpickinginv)},
	{"SWTPICKINGAGR",V10CADENA,(size_t)&svdserieprep.swtpickingagr,sizeof(svdserieprep.swtpickingagr)},
	{"DESSERIE",V10CADENA,(size_t)&svdserieprep.desserie,sizeof(svdserieprep.desserie)},
	{"RANGOZONASPICKINV",V10CADENA,(size_t)&svdserieprep.rangozonaspickinv,sizeof(svdserieprep.rangozonaspickinv)},
	{"TIPOPUERTO",V10CADENA,(size_t)&svdserieprep.tipopuerto,sizeof(svdserieprep.tipopuerto)},
	{"CODOPECREADA",V10CADENA,(size_t)&svdserieprep.codopecreada,sizeof(svdserieprep.codopecreada)},
	{"FECCREADA",V10LONG,(size_t)&svdserieprep.feccreada,sizeof(svdserieprep.feccreada)},
	{"HORACREADA",V10CADENA,(size_t)&svdserieprep.horacreada,sizeof(svdserieprep.horacreada)},
	{"CODOPELANZA",V10CADENA,(size_t)&svdserieprep.codopelanza,sizeof(svdserieprep.codopelanza)},
	{"FECLANZA",V10LONG,(size_t)&svdserieprep.feclanza,sizeof(svdserieprep.feclanza)},
	{"HORALANZA",V10CADENA,(size_t)&svdserieprep.horalanza,sizeof(svdserieprep.horalanza)},
	{"FECTERMIN",V10LONG,(size_t)&svdserieprep.fectermin,sizeof(svdserieprep.fectermin)},
	{"HORATERMIN",V10CADENA,(size_t)&svdserieprep.horatermin,sizeof(svdserieprep.horatermin)},
	{"STATUS",V10LONG,(size_t)&svdserieprep.status,sizeof(svdserieprep.status)},
	{"CODCOMEN",V10LONG,(size_t)&svdserieprep.codcomen,sizeof(svdserieprep.codcomen)},
	{"VDEXTRA",V10CADENA,(size_t)&svdserieprep.vdextra,sizeof(svdserieprep.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdserieprep.codopemodif,sizeof(svdserieprep.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdserieprep.fecmodif,sizeof(svdserieprep.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdserieprep.horamodif,sizeof(svdserieprep.horamodif)},
	{"CODOPECIERRE",V10CADENA,(size_t)&svdserieprep.codopecierre,sizeof(svdserieprep.codopecierre)},
	{"FECCIERRE",V10LONG,(size_t)&svdserieprep.feccierre,sizeof(svdserieprep.feccierre)},
	{"HORACIERRE",V10CADENA,(size_t)&svdserieprep.horacierre,sizeof(svdserieprep.horacierre)},
	{"SWTBLOQETIQ",V10CADENA,(size_t)&svdserieprep.swtbloqetiq,sizeof(svdserieprep.swtbloqetiq)},
	{"COMENSPR",V10CADENA,(size_t)&svdserieprep.comenspr,sizeof(svdserieprep.comenspr)}
	};
static diccionarios dvdserieprep[]={
    {colvdserieprep,27}
};
diccionario dspr={dvdserieprep,1};

static char msglogSPR[LCADENA];
static char msgdebugSPR[LCADENABIG];
static int init=0;


static void fin_vd_spr(void)
{
if (vdselsprstatus) {
    liberacursor(vdselsprstatus);
    vdselsprstatus = NULL;
}
if (vdselsprvdserieprep) {
    liberacursor(vdselsprvdserieprep);
    vdselsprvdserieprep = NULL;
}
if (vdselsprrowidlock) {
    liberacursor(vdselsprrowidlock);
    vdselsprrowidlock = NULL;
}
if (vdupdasprstatus) {
    liberacursor(vdupdasprstatus);
    vdupdasprstatus = NULL;
}
}
static void init_selsprstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieprep[0].numcol;nc++) dvdserieprep[0].c[nc].offset-=(size_t)&svdserieprep;
    vdselsprstatus=abrecursordebug(SELSPRSTATUS,1280);
    definetodo(vdselsprstatus,svdserieprep.rowid,sizeof(svdserieprep.rowid),V10CADENA,
                          &svdserieprep.codserieprep,sizeof(svdserieprep.codserieprep),V10LONG,
                          &svdserieprep.prioridad,sizeof(svdserieprep.prioridad),V10LONG,
                          svdserieprep.swtpickinginv,sizeof(svdserieprep.swtpickinginv),V10CADENA,
                          svdserieprep.swtpickingagr,sizeof(svdserieprep.swtpickingagr),V10CADENA,
                          svdserieprep.desserie,sizeof(svdserieprep.desserie),V10CADENA,
                          svdserieprep.rangozonaspickinv,sizeof(svdserieprep.rangozonaspickinv),V10CADENA,
                          svdserieprep.tipopuerto,sizeof(svdserieprep.tipopuerto),V10CADENA,
                          svdserieprep.codopecreada,sizeof(svdserieprep.codopecreada),V10CADENA,
                          &svdserieprep.feccreada,sizeof(svdserieprep.feccreada),V10LONG,
                          svdserieprep.horacreada,sizeof(svdserieprep.horacreada),V10CADENA,
                          svdserieprep.codopelanza,sizeof(svdserieprep.codopelanza),V10CADENA,
                          &svdserieprep.feclanza,sizeof(svdserieprep.feclanza),V10LONG,
                          svdserieprep.horalanza,sizeof(svdserieprep.horalanza),V10CADENA,
                          &svdserieprep.fectermin,sizeof(svdserieprep.fectermin),V10LONG,
                          svdserieprep.horatermin,sizeof(svdserieprep.horatermin),V10CADENA,
                          &svdserieprep.status,sizeof(svdserieprep.status),V10LONG,
                          &svdserieprep.codcomen,sizeof(svdserieprep.codcomen),V10LONG,
                          svdserieprep.vdextra,sizeof(svdserieprep.vdextra),V10CADENA,
                          svdserieprep.codopemodif,sizeof(svdserieprep.codopemodif),V10CADENA,
                          &svdserieprep.fecmodif,sizeof(svdserieprep.fecmodif),V10LONG,
                          svdserieprep.horamodif,sizeof(svdserieprep.horamodif),V10CADENA,
                          svdserieprep.codopecierre,sizeof(svdserieprep.codopecierre),V10CADENA,
                          &svdserieprep.feccierre,sizeof(svdserieprep.feccierre),V10LONG,
                          svdserieprep.horacierre,sizeof(svdserieprep.horacierre),V10CADENA,
                          svdserieprep.swtbloqetiq,sizeof(svdserieprep.swtbloqetiq),V10CADENA,
                          NULL);
    bindtodo(vdselsprstatus,"STATUS",&svdserieprep.status,sizeof(svdserieprep.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_spr);
        init = 1;
    }
}

static void init_selsprvdserieprep(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieprep[0].numcol;nc++) dvdserieprep[0].c[nc].offset-=(size_t)&svdserieprep;
    vdselsprvdserieprep=abrecursordebug(SELSPRVDSERIEPREP,1280);
    definetodo(vdselsprvdserieprep,svdserieprep.rowid,sizeof(svdserieprep.rowid),V10CADENA,
                          &svdserieprep.codserieprep,sizeof(svdserieprep.codserieprep),V10LONG,
                          &svdserieprep.prioridad,sizeof(svdserieprep.prioridad),V10LONG,
                          svdserieprep.swtpickinginv,sizeof(svdserieprep.swtpickinginv),V10CADENA,
                          svdserieprep.swtpickingagr,sizeof(svdserieprep.swtpickingagr),V10CADENA,
                          svdserieprep.desserie,sizeof(svdserieprep.desserie),V10CADENA,
                          svdserieprep.rangozonaspickinv,sizeof(svdserieprep.rangozonaspickinv),V10CADENA,
                          svdserieprep.tipopuerto,sizeof(svdserieprep.tipopuerto),V10CADENA,
                          svdserieprep.codopecreada,sizeof(svdserieprep.codopecreada),V10CADENA,
                          &svdserieprep.feccreada,sizeof(svdserieprep.feccreada),V10LONG,
                          svdserieprep.horacreada,sizeof(svdserieprep.horacreada),V10CADENA,
                          svdserieprep.codopelanza,sizeof(svdserieprep.codopelanza),V10CADENA,
                          &svdserieprep.feclanza,sizeof(svdserieprep.feclanza),V10LONG,
                          svdserieprep.horalanza,sizeof(svdserieprep.horalanza),V10CADENA,
                          &svdserieprep.fectermin,sizeof(svdserieprep.fectermin),V10LONG,
                          svdserieprep.horatermin,sizeof(svdserieprep.horatermin),V10CADENA,
                          &svdserieprep.status,sizeof(svdserieprep.status),V10LONG,
                          &svdserieprep.codcomen,sizeof(svdserieprep.codcomen),V10LONG,
                          svdserieprep.vdextra,sizeof(svdserieprep.vdextra),V10CADENA,
                          svdserieprep.codopemodif,sizeof(svdserieprep.codopemodif),V10CADENA,
                          &svdserieprep.fecmodif,sizeof(svdserieprep.fecmodif),V10LONG,
                          svdserieprep.horamodif,sizeof(svdserieprep.horamodif),V10CADENA,
                          svdserieprep.codopecierre,sizeof(svdserieprep.codopecierre),V10CADENA,
                          &svdserieprep.feccierre,sizeof(svdserieprep.feccierre),V10LONG,
                          svdserieprep.horacierre,sizeof(svdserieprep.horacierre),V10CADENA,
                          svdserieprep.swtbloqetiq,sizeof(svdserieprep.swtbloqetiq),V10CADENA,
                          NULL);
    bindtodo(vdselsprvdserieprep,"CODSERIEPREP",&svdserieprep.codserieprep,sizeof(svdserieprep.codserieprep),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_spr);
        init = 1;
    }
}

static void init_selsprrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieprep[0].numcol;nc++) dvdserieprep[0].c[nc].offset-=(size_t)&svdserieprep;
    vdselsprrowidlock=abrecursordebug(SELSPRROWIDLOCK,1280);
    definetodo(vdselsprrowidlock,svdserieprep.rowid,sizeof(svdserieprep.rowid),V10CADENA,
                          &svdserieprep.codserieprep,sizeof(svdserieprep.codserieprep),V10LONG,
                          &svdserieprep.prioridad,sizeof(svdserieprep.prioridad),V10LONG,
                          svdserieprep.swtpickinginv,sizeof(svdserieprep.swtpickinginv),V10CADENA,
                          svdserieprep.swtpickingagr,sizeof(svdserieprep.swtpickingagr),V10CADENA,
                          svdserieprep.desserie,sizeof(svdserieprep.desserie),V10CADENA,
                          svdserieprep.rangozonaspickinv,sizeof(svdserieprep.rangozonaspickinv),V10CADENA,
                          svdserieprep.tipopuerto,sizeof(svdserieprep.tipopuerto),V10CADENA,
                          svdserieprep.codopecreada,sizeof(svdserieprep.codopecreada),V10CADENA,
                          &svdserieprep.feccreada,sizeof(svdserieprep.feccreada),V10LONG,
                          svdserieprep.horacreada,sizeof(svdserieprep.horacreada),V10CADENA,
                          svdserieprep.codopelanza,sizeof(svdserieprep.codopelanza),V10CADENA,
                          &svdserieprep.feclanza,sizeof(svdserieprep.feclanza),V10LONG,
                          svdserieprep.horalanza,sizeof(svdserieprep.horalanza),V10CADENA,
                          &svdserieprep.fectermin,sizeof(svdserieprep.fectermin),V10LONG,
                          svdserieprep.horatermin,sizeof(svdserieprep.horatermin),V10CADENA,
                          &svdserieprep.status,sizeof(svdserieprep.status),V10LONG,
                          &svdserieprep.codcomen,sizeof(svdserieprep.codcomen),V10LONG,
                          svdserieprep.vdextra,sizeof(svdserieprep.vdextra),V10CADENA,
                          svdserieprep.codopemodif,sizeof(svdserieprep.codopemodif),V10CADENA,
                          &svdserieprep.fecmodif,sizeof(svdserieprep.fecmodif),V10LONG,
                          svdserieprep.horamodif,sizeof(svdserieprep.horamodif),V10CADENA,
                          svdserieprep.codopecierre,sizeof(svdserieprep.codopecierre),V10CADENA,
                          &svdserieprep.feccierre,sizeof(svdserieprep.feccierre),V10LONG,
                          svdserieprep.horacierre,sizeof(svdserieprep.horacierre),V10CADENA,
                          svdserieprep.swtbloqetiq,sizeof(svdserieprep.swtbloqetiq),V10CADENA,
                          NULL);
    bindtodo(vdselsprrowidlock,"MIROWID",svdserieprep.rowid,sizeof(svdserieprep.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_spr);
        init = 1;
    }
}

static void init_updasprstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieprep[0].numcol;nc++) dvdserieprep[0].c[nc].offset-=(size_t)&svdserieprep;
    vdupdasprstatus=abrecursordebug(UPDASPRSTATUS,1280);
    bindtodo(vdupdasprstatus,"STATUS",&svdserieprep.status,sizeof(svdserieprep.status),V10LONG,
                          "MIROWID",svdserieprep.rowid,sizeof(svdserieprep.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_spr);
        init = 1;
    }
}

diccionario *SPRdamediccionario(void)
{
     return(&dspr);
}

int SPRbuscastatus(long status,vdseriepreps *spr)
{
  int vdret;
  memset(&svdserieprep,0,sizeof(svdserieprep));
  svdserieprep.status=status;
  if (vdselsprstatus==NULL) init_selsprstatus();
  vdret=ejefetchcursor(vdselsprstatus);
  if (vdret==0) {
     *spr=svdserieprep;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsprstatus. vdret %d. \n",SPRlog(&svdserieprep),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SPRnextstatus(vdseriepreps *spr)
{
  int vdret;
  vdret=fetchcursor(vdselsprstatus);
  if (vdret==0) {
     *spr=svdserieprep;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsprstatus. vdret %d. \n",SPRlog(&svdserieprep),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsprstatus);
  return(VD_EERRORACLE);
}

int SPRselvdserieprep(long codserieprep,vdseriepreps *spr)
{
  int vdret;
  if (vdselsprvdserieprep==NULL) init_selsprvdserieprep();
  memset(&svdserieprep,0,sizeof(svdserieprep));
  svdserieprep.codserieprep=codserieprep;
  vdret=ejefetchcursor(vdselsprvdserieprep);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselsprvdserieprep. vdret %d. \n",SPRlog(&svdserieprep),vdret);
    return(VD_EERRORACLE);
   }
  *spr=svdserieprep;
  return(vdret);
}

int SPRlock(vdseriepreps *spr,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdserieprep=*spr;
    if (vdselsprrowidlock==NULL) init_selsprrowidlock();
    savepoint("lockvdserieprep");
    while (1) {
        vdret=ejefetchcursor(vdselsprrowidlock);
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
    vdret=vverificacampos(spr,&svdserieprep,&dvdserieprep[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdserieprep");
    return(vdret);
}

int SPRactualizastatus(vdseriepreps *spr,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SPRactualizastatus:  %s .  \n",SPRlog(&svdserieprep));
  if (vdupdasprstatus==NULL) init_updasprstatus();
  svdserieprep=*spr;
  vdret=ejecutacursor(vdupdasprstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdasprstatus);
     getcurerrornombre(vdupdasprstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdasprstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

char * SPRlog(vdseriepreps *spr)
{
    sprintf(msglogSPR, "VDSERIEPREP: codserieprep %ld ",spr->codserieprep);
    return(msglogSPR);
}

char * SPRdebug(vdseriepreps *spr)
{
    debugestruct(&dspr,spr,msgdebugSPR);
    return(msgdebugSPR);
}

