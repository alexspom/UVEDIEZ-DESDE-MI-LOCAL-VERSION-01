// Modulo generado automaticamente a partir de VDSERIEEXP.DEF
//#***
//# VDSERIEEXP.DEF - Generación automática del código c para la tabla de Series de Expedición
//# 
//# Propósito: Funciones de acceso a la tabla VDSERIEEXP
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 24-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=SEX
//EXTRA=COMENSEX,V10CADENA,1025
//
//RECORRE=STATUS,STATUS;
//UPDATE=STATUS,STATUS;
//LOCK

#include "vd.h"
#define SELSEXSTATUS "SELECT VDSERIEEXP.ROWID,VDSERIEEXP.CODSERIEEXP,VDSERIEEXP.CODSERIEPREP, "\
                    " VDSERIEEXP.DESSERIE,VDSERIEEXP.ANOBOLETA,VDSERIEEXP.CODBOLETA, "\
                    " VDSERIEEXP.CODAGE,VDSERIEEXP.PUERTO,VDSERIEEXP.PRIORIDAD, "\
                    " VDSERIEEXP.CODOPELANZA,VDSERIEEXP.FECLANZA,VDSERIEEXP.HORALANZA, "\
                    " VDSERIEEXP.FECTERMIN,VDSERIEEXP.HORATERMIN,VDSERIEEXP.FECEXPIDE, "\
                    " VDSERIEEXP.HORAEXPIDE,VDSERIEEXP.STATUS,VDSERIEEXP.CODCOMEN, "\
                    " VDSERIEEXP.VDEXTRA,VDSERIEEXP.CODOPEMODIF,VDSERIEEXP.FECMODIF, "\
                    " VDSERIEEXP.HORAMODIF "\
        " FROM VDSERIEEXP"\
        " WHERE "\
               " VDSERIEEXP.STATUS=:STATUS "
static v10cursors *vdselsexstatus;

#define SELSEXVDSERIEEXP "SELECT VDSERIEEXP.ROWID,VDSERIEEXP.CODSERIEEXP,VDSERIEEXP.CODSERIEPREP, "\
                    " VDSERIEEXP.DESSERIE,VDSERIEEXP.ANOBOLETA,VDSERIEEXP.CODBOLETA, "\
                    " VDSERIEEXP.CODAGE,VDSERIEEXP.PUERTO,VDSERIEEXP.PRIORIDAD, "\
                    " VDSERIEEXP.CODOPELANZA,VDSERIEEXP.FECLANZA,VDSERIEEXP.HORALANZA, "\
                    " VDSERIEEXP.FECTERMIN,VDSERIEEXP.HORATERMIN,VDSERIEEXP.FECEXPIDE, "\
                    " VDSERIEEXP.HORAEXPIDE,VDSERIEEXP.STATUS,VDSERIEEXP.CODCOMEN, "\
                    " VDSERIEEXP.VDEXTRA,VDSERIEEXP.CODOPEMODIF,VDSERIEEXP.FECMODIF, "\
                    " VDSERIEEXP.HORAMODIF "\
        " FROM VDSERIEEXP"\
        " WHERE "\
               " VDSERIEEXP.CODSERIEEXP=:CODSERIEEXP "
static v10cursors *vdselsexvdserieexp;

#define SELSEXROWIDLOCK "SELECT ROWID,CODSERIEEXP,CODSERIEPREP,DESSERIE,ANOBOLETA,CODBOLETA,CODAGE, "\
                    " PUERTO,PRIORIDAD,CODOPELANZA,FECLANZA,HORALANZA,FECTERMIN,HORATERMIN, "\
                    " FECEXPIDE,HORAEXPIDE,STATUS,CODCOMEN,VDEXTRA,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF "\
        " FROM VDSERIEEXP "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselsexrowidlock;

#define UPDASEXSTATUS "UPDATE VDSERIEEXP SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdasexstatus;

static vdserieexps svdserieexp;

static diccols colvdserieexp[]={
	{"ROWID",V10CADENA,(size_t)&svdserieexp.rowid,sizeof(svdserieexp.rowid)},
	{"CODSERIEEXP",V10LONG,(size_t)&svdserieexp.codserieexp,sizeof(svdserieexp.codserieexp)},
	{"CODSERIEPREP",V10LONG,(size_t)&svdserieexp.codserieprep,sizeof(svdserieexp.codserieprep)},
	{"DESSERIE",V10CADENA,(size_t)&svdserieexp.desserie,sizeof(svdserieexp.desserie)},
	{"ANOBOLETA",V10LONG,(size_t)&svdserieexp.anoboleta,sizeof(svdserieexp.anoboleta)},
	{"CODBOLETA",V10LONG,(size_t)&svdserieexp.codboleta,sizeof(svdserieexp.codboleta)},
	{"CODAGE",V10CADENA,(size_t)&svdserieexp.codage,sizeof(svdserieexp.codage)},
	{"PUERTO",V10LONG,(size_t)&svdserieexp.puerto,sizeof(svdserieexp.puerto)},
	{"PRIORIDAD",V10LONG,(size_t)&svdserieexp.prioridad,sizeof(svdserieexp.prioridad)},
	{"CODOPELANZA",V10CADENA,(size_t)&svdserieexp.codopelanza,sizeof(svdserieexp.codopelanza)},
	{"FECLANZA",V10LONG,(size_t)&svdserieexp.feclanza,sizeof(svdserieexp.feclanza)},
	{"HORALANZA",V10CADENA,(size_t)&svdserieexp.horalanza,sizeof(svdserieexp.horalanza)},
	{"FECTERMIN",V10LONG,(size_t)&svdserieexp.fectermin,sizeof(svdserieexp.fectermin)},
	{"HORATERMIN",V10CADENA,(size_t)&svdserieexp.horatermin,sizeof(svdserieexp.horatermin)},
	{"FECEXPIDE",V10LONG,(size_t)&svdserieexp.fecexpide,sizeof(svdserieexp.fecexpide)},
	{"HORAEXPIDE",V10CADENA,(size_t)&svdserieexp.horaexpide,sizeof(svdserieexp.horaexpide)},
	{"STATUS",V10LONG,(size_t)&svdserieexp.status,sizeof(svdserieexp.status)},
	{"CODCOMEN",V10LONG,(size_t)&svdserieexp.codcomen,sizeof(svdserieexp.codcomen)},
	{"VDEXTRA",V10CADENA,(size_t)&svdserieexp.vdextra,sizeof(svdserieexp.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdserieexp.codopemodif,sizeof(svdserieexp.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdserieexp.fecmodif,sizeof(svdserieexp.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdserieexp.horamodif,sizeof(svdserieexp.horamodif)},
	{"COMENSEX",V10CADENA,(size_t)&svdserieexp.comensex,sizeof(svdserieexp.comensex)}
	};
static diccionarios dvdserieexp[]={
    {colvdserieexp,23}
};
diccionario dsex={dvdserieexp,1};

static char msglogSEX[LCADENA];
static char msgdebugSEX[LCADENABIG];
static int init=0;


static void fin_vd_sex(void)
{
if (vdselsexstatus) {
    liberacursor(vdselsexstatus);
    vdselsexstatus = NULL;
}
if (vdselsexvdserieexp) {
    liberacursor(vdselsexvdserieexp);
    vdselsexvdserieexp = NULL;
}
if (vdselsexrowidlock) {
    liberacursor(vdselsexrowidlock);
    vdselsexrowidlock = NULL;
}
if (vdupdasexstatus) {
    liberacursor(vdupdasexstatus);
    vdupdasexstatus = NULL;
}
}
static void init_selsexstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieexp[0].numcol;nc++) dvdserieexp[0].c[nc].offset-=(size_t)&svdserieexp;
    vdselsexstatus=abrecursordebug(SELSEXSTATUS,1280);
    definetodo(vdselsexstatus,svdserieexp.rowid,sizeof(svdserieexp.rowid),V10CADENA,
                          &svdserieexp.codserieexp,sizeof(svdserieexp.codserieexp),V10LONG,
                          &svdserieexp.codserieprep,sizeof(svdserieexp.codserieprep),V10LONG,
                          svdserieexp.desserie,sizeof(svdserieexp.desserie),V10CADENA,
                          &svdserieexp.anoboleta,sizeof(svdserieexp.anoboleta),V10LONG,
                          &svdserieexp.codboleta,sizeof(svdserieexp.codboleta),V10LONG,
                          svdserieexp.codage,sizeof(svdserieexp.codage),V10CADENA,
                          &svdserieexp.puerto,sizeof(svdserieexp.puerto),V10LONG,
                          &svdserieexp.prioridad,sizeof(svdserieexp.prioridad),V10LONG,
                          svdserieexp.codopelanza,sizeof(svdserieexp.codopelanza),V10CADENA,
                          &svdserieexp.feclanza,sizeof(svdserieexp.feclanza),V10LONG,
                          svdserieexp.horalanza,sizeof(svdserieexp.horalanza),V10CADENA,
                          &svdserieexp.fectermin,sizeof(svdserieexp.fectermin),V10LONG,
                          svdserieexp.horatermin,sizeof(svdserieexp.horatermin),V10CADENA,
                          &svdserieexp.fecexpide,sizeof(svdserieexp.fecexpide),V10LONG,
                          svdserieexp.horaexpide,sizeof(svdserieexp.horaexpide),V10CADENA,
                          &svdserieexp.status,sizeof(svdserieexp.status),V10LONG,
                          &svdserieexp.codcomen,sizeof(svdserieexp.codcomen),V10LONG,
                          svdserieexp.vdextra,sizeof(svdserieexp.vdextra),V10CADENA,
                          svdserieexp.codopemodif,sizeof(svdserieexp.codopemodif),V10CADENA,
                          &svdserieexp.fecmodif,sizeof(svdserieexp.fecmodif),V10LONG,
                          svdserieexp.horamodif,sizeof(svdserieexp.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselsexstatus,"STATUS",&svdserieexp.status,sizeof(svdserieexp.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_sex);
        init = 1;
    }
}

static void init_selsexvdserieexp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieexp[0].numcol;nc++) dvdserieexp[0].c[nc].offset-=(size_t)&svdserieexp;
    vdselsexvdserieexp=abrecursordebug(SELSEXVDSERIEEXP,1280);
    definetodo(vdselsexvdserieexp,svdserieexp.rowid,sizeof(svdserieexp.rowid),V10CADENA,
                          &svdserieexp.codserieexp,sizeof(svdserieexp.codserieexp),V10LONG,
                          &svdserieexp.codserieprep,sizeof(svdserieexp.codserieprep),V10LONG,
                          svdserieexp.desserie,sizeof(svdserieexp.desserie),V10CADENA,
                          &svdserieexp.anoboleta,sizeof(svdserieexp.anoboleta),V10LONG,
                          &svdserieexp.codboleta,sizeof(svdserieexp.codboleta),V10LONG,
                          svdserieexp.codage,sizeof(svdserieexp.codage),V10CADENA,
                          &svdserieexp.puerto,sizeof(svdserieexp.puerto),V10LONG,
                          &svdserieexp.prioridad,sizeof(svdserieexp.prioridad),V10LONG,
                          svdserieexp.codopelanza,sizeof(svdserieexp.codopelanza),V10CADENA,
                          &svdserieexp.feclanza,sizeof(svdserieexp.feclanza),V10LONG,
                          svdserieexp.horalanza,sizeof(svdserieexp.horalanza),V10CADENA,
                          &svdserieexp.fectermin,sizeof(svdserieexp.fectermin),V10LONG,
                          svdserieexp.horatermin,sizeof(svdserieexp.horatermin),V10CADENA,
                          &svdserieexp.fecexpide,sizeof(svdserieexp.fecexpide),V10LONG,
                          svdserieexp.horaexpide,sizeof(svdserieexp.horaexpide),V10CADENA,
                          &svdserieexp.status,sizeof(svdserieexp.status),V10LONG,
                          &svdserieexp.codcomen,sizeof(svdserieexp.codcomen),V10LONG,
                          svdserieexp.vdextra,sizeof(svdserieexp.vdextra),V10CADENA,
                          svdserieexp.codopemodif,sizeof(svdserieexp.codopemodif),V10CADENA,
                          &svdserieexp.fecmodif,sizeof(svdserieexp.fecmodif),V10LONG,
                          svdserieexp.horamodif,sizeof(svdserieexp.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselsexvdserieexp,"CODSERIEEXP",&svdserieexp.codserieexp,sizeof(svdserieexp.codserieexp),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_sex);
        init = 1;
    }
}

static void init_selsexrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieexp[0].numcol;nc++) dvdserieexp[0].c[nc].offset-=(size_t)&svdserieexp;
    vdselsexrowidlock=abrecursordebug(SELSEXROWIDLOCK,1280);
    definetodo(vdselsexrowidlock,svdserieexp.rowid,sizeof(svdserieexp.rowid),V10CADENA,
                          &svdserieexp.codserieexp,sizeof(svdserieexp.codserieexp),V10LONG,
                          &svdserieexp.codserieprep,sizeof(svdserieexp.codserieprep),V10LONG,
                          svdserieexp.desserie,sizeof(svdserieexp.desserie),V10CADENA,
                          &svdserieexp.anoboleta,sizeof(svdserieexp.anoboleta),V10LONG,
                          &svdserieexp.codboleta,sizeof(svdserieexp.codboleta),V10LONG,
                          svdserieexp.codage,sizeof(svdserieexp.codage),V10CADENA,
                          &svdserieexp.puerto,sizeof(svdserieexp.puerto),V10LONG,
                          &svdserieexp.prioridad,sizeof(svdserieexp.prioridad),V10LONG,
                          svdserieexp.codopelanza,sizeof(svdserieexp.codopelanza),V10CADENA,
                          &svdserieexp.feclanza,sizeof(svdserieexp.feclanza),V10LONG,
                          svdserieexp.horalanza,sizeof(svdserieexp.horalanza),V10CADENA,
                          &svdserieexp.fectermin,sizeof(svdserieexp.fectermin),V10LONG,
                          svdserieexp.horatermin,sizeof(svdserieexp.horatermin),V10CADENA,
                          &svdserieexp.fecexpide,sizeof(svdserieexp.fecexpide),V10LONG,
                          svdserieexp.horaexpide,sizeof(svdserieexp.horaexpide),V10CADENA,
                          &svdserieexp.status,sizeof(svdserieexp.status),V10LONG,
                          &svdserieexp.codcomen,sizeof(svdserieexp.codcomen),V10LONG,
                          svdserieexp.vdextra,sizeof(svdserieexp.vdextra),V10CADENA,
                          svdserieexp.codopemodif,sizeof(svdserieexp.codopemodif),V10CADENA,
                          &svdserieexp.fecmodif,sizeof(svdserieexp.fecmodif),V10LONG,
                          svdserieexp.horamodif,sizeof(svdserieexp.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselsexrowidlock,"MIROWID",svdserieexp.rowid,sizeof(svdserieexp.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_sex);
        init = 1;
    }
}

static void init_updasexstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdserieexp[0].numcol;nc++) dvdserieexp[0].c[nc].offset-=(size_t)&svdserieexp;
    vdupdasexstatus=abrecursordebug(UPDASEXSTATUS,1280);
    bindtodo(vdupdasexstatus,"STATUS",&svdserieexp.status,sizeof(svdserieexp.status),V10LONG,
                          "MIROWID",svdserieexp.rowid,sizeof(svdserieexp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_sex);
        init = 1;
    }
}

diccionario *SEXdamediccionario(void)
{
     return(&dsex);
}

int SEXbuscastatus(long status,vdserieexps *sex)
{
  int vdret;
  memset(&svdserieexp,0,sizeof(svdserieexp));
  svdserieexp.status=status;
  if (vdselsexstatus==NULL) init_selsexstatus();
  vdret=ejefetchcursor(vdselsexstatus);
  if (vdret==0) {
     *sex=svdserieexp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsexstatus. vdret %d. \n",SEXlog(&svdserieexp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SEXnextstatus(vdserieexps *sex)
{
  int vdret;
  vdret=fetchcursor(vdselsexstatus);
  if (vdret==0) {
     *sex=svdserieexp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsexstatus. vdret %d. \n",SEXlog(&svdserieexp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsexstatus);
  return(VD_EERRORACLE);
}

int SEXselvdserieexp(long codserieexp,vdserieexps *sex)
{
  int vdret;
  if (vdselsexvdserieexp==NULL) init_selsexvdserieexp();
  memset(&svdserieexp,0,sizeof(svdserieexp));
  svdserieexp.codserieexp=codserieexp;
  vdret=ejefetchcursor(vdselsexvdserieexp);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselsexvdserieexp. vdret %d. \n",SEXlog(&svdserieexp),vdret);
    return(VD_EERRORACLE);
   }
  *sex=svdserieexp;
  return(vdret);
}

int SEXlock(vdserieexps *sex,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdserieexp=*sex;
    if (vdselsexrowidlock==NULL) init_selsexrowidlock();
    savepoint("lockvdserieexp");
    while (1) {
        vdret=ejefetchcursor(vdselsexrowidlock);
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
    vdret=vverificacampos(sex,&svdserieexp,&dvdserieexp[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdserieexp");
    return(vdret);
}

int SEXactualizastatus(vdserieexps *sex,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SEXactualizastatus:  %s .  \n",SEXlog(&svdserieexp));
  if (vdupdasexstatus==NULL) init_updasexstatus();
  svdserieexp=*sex;
  vdret=ejecutacursor(vdupdasexstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdasexstatus);
     getcurerrornombre(vdupdasexstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdasexstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

char * SEXlog(vdserieexps *sex)
{
    sprintf(msglogSEX, "VDSERIEEXP: codserieexp %ld ",sex->codserieexp);
    return(msglogSEX);
}

char * SEXdebug(vdserieexps *sex)
{
    debugestruct(&dsex,sex,msgdebugSEX);
    return(msgdebugSEX);
}

