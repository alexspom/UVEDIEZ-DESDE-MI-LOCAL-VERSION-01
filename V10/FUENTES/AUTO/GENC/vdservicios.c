// Modulo generado automaticamente a partir de VDSERVICIOS.DEF
//# M¢dulo : VDSERVICIOS.DEF
//# Función: Generación automatica de rutinas C tabla VDSERVICIOS
//#
//# Autor	 : EAA
//# Revisado por:
//# Fecha  : 12-06-2008
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=SER
//
//PRIMARIA=CODGRUPOSERV,CODSERVICIO
//
//CLAVE=CODSERVICIO,CODGRUPOSERV,CODSERVICIO
//CLAVE=PID,PID
//RECORRE=CODGRUPOSERV,CODGRUPOSERV
//
//UPDATE=SID,SID
//UPDATE=DESCINMEDIATA,EJECUTAR
//UPDATE=ESTADO,STATUS,PID,SID,FECARRANQUE
//UPDATE=PLANIF,STATUS,PID,FECULTEJEC,HORAULTEJEC,FECEJEC,HORAEJEC,EJECUTAR

#include "vd.h"
#define SELSERCODSERVICIO "SELECT VDSERVICIOS.ROWID,VDSERVICIOS.CODGRUPOSERV,VDSERVICIOS.CODSERVICIO, "\
                    " VDSERVICIOS.DESSERVICIO,VDSERVICIOS.ACTIVO,VDSERVICIOS.VISUALIZADO, "\
                    " VDSERVICIOS.EJECUTABLE,VDSERVICIOS.PATHSERVICIO,VDSERVICIOS.PATHV10SERVICIO, "\
                    " VDSERVICIOS.ENVSERVICIO,VDSERVICIOS.PARAMSERVICIO,VDSERVICIOS.STATUS, "\
                    " VDSERVICIOS.PID,VDSERVICIOS.SID,VDSERVICIOS.SERIAL, "\
                    " VDSERVICIOS.ARRANQUE,VDSERVICIOS.CIERRE,VDSERVICIOS.EJECUTAR, "\
                    " VDSERVICIOS.PATRONPLANIF,VDSERVICIOS.HORAINICIO,VDSERVICIOS.HORALIMITE, "\
                    " VDSERVICIOS.INTERVALO,VDSERVICIOS.FECARRANQUE,VDSERVICIOS.FECULTEJEC, "\
                    " VDSERVICIOS.HORAULTEJEC,VDSERVICIOS.FECEJEC,VDSERVICIOS.HORAEJEC, "\
                    " VDSERVICIOS.CODOPEMODIF,VDSERVICIOS.FECMODIF,VDSERVICIOS.HORAMODIF, "\
                    " VDSERVICIOS.CODCOMEN "\
        " FROM VDSERVICIOS"\
        " WHERE "\
               " VDSERVICIOS.CODGRUPOSERV=:CODGRUPOSERV "\
               " AND VDSERVICIOS.CODSERVICIO=:CODSERVICIO "
static v10cursors *vdselsercodservicio;

#define SELSERPID "SELECT VDSERVICIOS.ROWID,VDSERVICIOS.CODGRUPOSERV,VDSERVICIOS.CODSERVICIO, "\
                    " VDSERVICIOS.DESSERVICIO,VDSERVICIOS.ACTIVO,VDSERVICIOS.VISUALIZADO, "\
                    " VDSERVICIOS.EJECUTABLE,VDSERVICIOS.PATHSERVICIO,VDSERVICIOS.PATHV10SERVICIO, "\
                    " VDSERVICIOS.ENVSERVICIO,VDSERVICIOS.PARAMSERVICIO,VDSERVICIOS.STATUS, "\
                    " VDSERVICIOS.PID,VDSERVICIOS.SID,VDSERVICIOS.SERIAL, "\
                    " VDSERVICIOS.ARRANQUE,VDSERVICIOS.CIERRE,VDSERVICIOS.EJECUTAR, "\
                    " VDSERVICIOS.PATRONPLANIF,VDSERVICIOS.HORAINICIO,VDSERVICIOS.HORALIMITE, "\
                    " VDSERVICIOS.INTERVALO,VDSERVICIOS.FECARRANQUE,VDSERVICIOS.FECULTEJEC, "\
                    " VDSERVICIOS.HORAULTEJEC,VDSERVICIOS.FECEJEC,VDSERVICIOS.HORAEJEC, "\
                    " VDSERVICIOS.CODOPEMODIF,VDSERVICIOS.FECMODIF,VDSERVICIOS.HORAMODIF, "\
                    " VDSERVICIOS.CODCOMEN "\
        " FROM VDSERVICIOS"\
        " WHERE "\
               " VDSERVICIOS.PID=:PID "
static v10cursors *vdselserpid;

#define SELSERCODGRUPOSERV "SELECT VDSERVICIOS.ROWID,VDSERVICIOS.CODGRUPOSERV,VDSERVICIOS.CODSERVICIO, "\
                    " VDSERVICIOS.DESSERVICIO,VDSERVICIOS.ACTIVO,VDSERVICIOS.VISUALIZADO, "\
                    " VDSERVICIOS.EJECUTABLE,VDSERVICIOS.PATHSERVICIO,VDSERVICIOS.PATHV10SERVICIO, "\
                    " VDSERVICIOS.ENVSERVICIO,VDSERVICIOS.PARAMSERVICIO,VDSERVICIOS.STATUS, "\
                    " VDSERVICIOS.PID,VDSERVICIOS.SID,VDSERVICIOS.SERIAL, "\
                    " VDSERVICIOS.ARRANQUE,VDSERVICIOS.CIERRE,VDSERVICIOS.EJECUTAR, "\
                    " VDSERVICIOS.PATRONPLANIF,VDSERVICIOS.HORAINICIO,VDSERVICIOS.HORALIMITE, "\
                    " VDSERVICIOS.INTERVALO,VDSERVICIOS.FECARRANQUE,VDSERVICIOS.FECULTEJEC, "\
                    " VDSERVICIOS.HORAULTEJEC,VDSERVICIOS.FECEJEC,VDSERVICIOS.HORAEJEC, "\
                    " VDSERVICIOS.CODOPEMODIF,VDSERVICIOS.FECMODIF,VDSERVICIOS.HORAMODIF, "\
                    " VDSERVICIOS.CODCOMEN "\
        " FROM VDSERVICIOS"\
        " WHERE "\
               " VDSERVICIOS.CODGRUPOSERV=:CODGRUPOSERV "\
        " ORDER BY CODSERVICIO"
static v10cursors *vdselsercodgruposerv;

#define SELSERVDSERVICIOS "SELECT VDSERVICIOS.ROWID,VDSERVICIOS.CODGRUPOSERV,VDSERVICIOS.CODSERVICIO, "\
                    " VDSERVICIOS.DESSERVICIO,VDSERVICIOS.ACTIVO,VDSERVICIOS.VISUALIZADO, "\
                    " VDSERVICIOS.EJECUTABLE,VDSERVICIOS.PATHSERVICIO,VDSERVICIOS.PATHV10SERVICIO, "\
                    " VDSERVICIOS.ENVSERVICIO,VDSERVICIOS.PARAMSERVICIO,VDSERVICIOS.STATUS, "\
                    " VDSERVICIOS.PID,VDSERVICIOS.SID,VDSERVICIOS.SERIAL, "\
                    " VDSERVICIOS.ARRANQUE,VDSERVICIOS.CIERRE,VDSERVICIOS.EJECUTAR, "\
                    " VDSERVICIOS.PATRONPLANIF,VDSERVICIOS.HORAINICIO,VDSERVICIOS.HORALIMITE, "\
                    " VDSERVICIOS.INTERVALO,VDSERVICIOS.FECARRANQUE,VDSERVICIOS.FECULTEJEC, "\
                    " VDSERVICIOS.HORAULTEJEC,VDSERVICIOS.FECEJEC,VDSERVICIOS.HORAEJEC, "\
                    " VDSERVICIOS.CODOPEMODIF,VDSERVICIOS.FECMODIF,VDSERVICIOS.HORAMODIF, "\
                    " VDSERVICIOS.CODCOMEN "\
        " FROM VDSERVICIOS"\
        " WHERE "\
               " VDSERVICIOS.CODGRUPOSERV=:CODGRUPOSERV "\
               " AND VDSERVICIOS.CODSERVICIO=:CODSERVICIO "
static v10cursors *vdselservdservicios;

#define UPDASERSID "UPDATE VDSERVICIOS SET  FECMODIF=VD.FECHASYS(),  HORAMODIF=VD.HORASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
                                          " SID=:SID ,SERIAL=:SERIAL "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdasersid;

#define UPDASERDESCINMEDIATA "UPDATE VDSERVICIOS SET  FECMODIF=VD.FECHASYS(),  HORAMODIF=VD.HORASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " EJECUTAR=:EJECUTAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaserdescinmediata;

#define UPDASERESTADO "UPDATE VDSERVICIOS SET  FECMODIF=VD.FECHASYS(),  HORAMODIF=VD.HORASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS , "\
               " PID=:PID , "\
               " SID=:SID , "\
               " FECARRANQUE=:FECARRANQUE  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaserestado;

#define UPDASERPLANIF "UPDATE VDSERVICIOS SET  FECMODIF=VD.FECHASYS(),  HORAMODIF=VD.HORASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS , "\
               " PID=:PID , "\
               " FECULTEJEC=:FECULTEJEC , "\
               " HORAULTEJEC=:HORAULTEJEC , "\
               " FECEJEC=:FECEJEC , "\
               " HORAEJEC=:HORAEJEC , "\
               " EJECUTAR=:EJECUTAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaserplanif;

static vdservicioss svdservicios;

static diccols colvdservicios[]={
	{"ROWID",V10CADENA,(size_t)&svdservicios.rowid,sizeof(svdservicios.rowid)},
	{"CODGRUPOSERV",V10CADENA,(size_t)&svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv)},
	{"CODSERVICIO",V10CADENA,(size_t)&svdservicios.codservicio,sizeof(svdservicios.codservicio)},
	{"DESSERVICIO",V10CADENA,(size_t)&svdservicios.desservicio,sizeof(svdservicios.desservicio)},
	{"ACTIVO",V10CADENA,(size_t)&svdservicios.activo,sizeof(svdservicios.activo)},
	{"VISUALIZADO",V10CADENA,(size_t)&svdservicios.visualizado,sizeof(svdservicios.visualizado)},
	{"EJECUTABLE",V10CADENA,(size_t)&svdservicios.ejecutable,sizeof(svdservicios.ejecutable)},
	{"PATHSERVICIO",V10CADENA,(size_t)&svdservicios.pathservicio,sizeof(svdservicios.pathservicio)},
	{"PATHV10SERVICIO",V10CADENA,(size_t)&svdservicios.pathv10servicio,sizeof(svdservicios.pathv10servicio)},
	{"ENVSERVICIO",V10CADENA,(size_t)&svdservicios.envservicio,sizeof(svdservicios.envservicio)},
	{"PARAMSERVICIO",V10CADENA,(size_t)&svdservicios.paramservicio,sizeof(svdservicios.paramservicio)},
	{"STATUS",V10LONG,(size_t)&svdservicios.status,sizeof(svdservicios.status)},
	{"PID",V10LONG,(size_t)&svdservicios.pid,sizeof(svdservicios.pid)},
	{"SID",V10LONG,(size_t)&svdservicios.sid,sizeof(svdservicios.sid)},
	{"SERIAL",V10LONG,(size_t)&svdservicios.serial,sizeof(svdservicios.serial)},
	{"ARRANQUE",V10CADENA,(size_t)&svdservicios.arranque,sizeof(svdservicios.arranque)},
	{"CIERRE",V10CADENA,(size_t)&svdservicios.cierre,sizeof(svdservicios.cierre)},
	{"EJECUTAR",V10CADENA,(size_t)&svdservicios.ejecutar,sizeof(svdservicios.ejecutar)},
	{"PATRONPLANIF",V10CADENA,(size_t)&svdservicios.patronplanif,sizeof(svdservicios.patronplanif)},
	{"HORAINICIO",V10CADENA,(size_t)&svdservicios.horainicio,sizeof(svdservicios.horainicio)},
	{"HORALIMITE",V10CADENA,(size_t)&svdservicios.horalimite,sizeof(svdservicios.horalimite)},
	{"INTERVALO",V10LONG,(size_t)&svdservicios.intervalo,sizeof(svdservicios.intervalo)},
	{"FECARRANQUE",V10LONG,(size_t)&svdservicios.fecarranque,sizeof(svdservicios.fecarranque)},
	{"FECULTEJEC",V10LONG,(size_t)&svdservicios.fecultejec,sizeof(svdservicios.fecultejec)},
	{"HORAULTEJEC",V10CADENA,(size_t)&svdservicios.horaultejec,sizeof(svdservicios.horaultejec)},
	{"FECEJEC",V10LONG,(size_t)&svdservicios.fecejec,sizeof(svdservicios.fecejec)},
	{"HORAEJEC",V10CADENA,(size_t)&svdservicios.horaejec,sizeof(svdservicios.horaejec)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdservicios.codopemodif,sizeof(svdservicios.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdservicios.fecmodif,sizeof(svdservicios.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdservicios.horamodif,sizeof(svdservicios.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdservicios.codcomen,sizeof(svdservicios.codcomen)}
	};
static diccionarios dvdservicios[]={
    {colvdservicios,31}
};
diccionario dser={dvdservicios,1};

static char msglogSER[LCADENA];
static char msgdebugSER[LCADENABIG];
static int init=0;


static void fin_vd_ser(void)
{
if (vdselsercodservicio) {
    liberacursor(vdselsercodservicio);
    vdselsercodservicio = NULL;
}
if (vdselserpid) {
    liberacursor(vdselserpid);
    vdselserpid = NULL;
}
if (vdselsercodgruposerv) {
    liberacursor(vdselsercodgruposerv);
    vdselsercodgruposerv = NULL;
}
if (vdselservdservicios) {
    liberacursor(vdselservdservicios);
    vdselservdservicios = NULL;
}
if (vdupdasersid) {
    liberacursor(vdupdasersid);
    vdupdasersid = NULL;
}
if (vdupdaserdescinmediata) {
    liberacursor(vdupdaserdescinmediata);
    vdupdaserdescinmediata = NULL;
}
if (vdupdaserestado) {
    liberacursor(vdupdaserestado);
    vdupdaserestado = NULL;
}
if (vdupdaserplanif) {
    liberacursor(vdupdaserplanif);
    vdupdaserplanif = NULL;
}
}
static void init_selsercodservicio(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdselsercodservicio=abrecursordebug(SELSERCODSERVICIO,1280);
    definetodo(vdselsercodservicio,svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          svdservicios.desservicio,sizeof(svdservicios.desservicio),V10CADENA,
                          svdservicios.activo,sizeof(svdservicios.activo),V10CADENA,
                          svdservicios.visualizado,sizeof(svdservicios.visualizado),V10CADENA,
                          svdservicios.ejecutable,sizeof(svdservicios.ejecutable),V10CADENA,
                          svdservicios.pathservicio,sizeof(svdservicios.pathservicio),V10CADENA,
                          svdservicios.pathv10servicio,sizeof(svdservicios.pathv10servicio),V10CADENA,
                          svdservicios.envservicio,sizeof(svdservicios.envservicio),V10CADENA,
                          svdservicios.paramservicio,sizeof(svdservicios.paramservicio),V10CADENA,
                          &svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          &svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          &svdservicios.sid,sizeof(svdservicios.sid),V10LONG,
                          &svdservicios.serial,sizeof(svdservicios.serial),V10LONG,
                          svdservicios.arranque,sizeof(svdservicios.arranque),V10CADENA,
                          svdservicios.cierre,sizeof(svdservicios.cierre),V10CADENA,
                          svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          svdservicios.patronplanif,sizeof(svdservicios.patronplanif),V10CADENA,
                          svdservicios.horainicio,sizeof(svdservicios.horainicio),V10CADENA,
                          svdservicios.horalimite,sizeof(svdservicios.horalimite),V10CADENA,
                          &svdservicios.intervalo,sizeof(svdservicios.intervalo),V10LONG,
                          &svdservicios.fecarranque,sizeof(svdservicios.fecarranque),V10LONG,
                          &svdservicios.fecultejec,sizeof(svdservicios.fecultejec),V10LONG,
                          svdservicios.horaultejec,sizeof(svdservicios.horaultejec),V10CADENA,
                          &svdservicios.fecejec,sizeof(svdservicios.fecejec),V10LONG,
                          svdservicios.horaejec,sizeof(svdservicios.horaejec),V10CADENA,
                          svdservicios.codopemodif,sizeof(svdservicios.codopemodif),V10CADENA,
                          &svdservicios.fecmodif,sizeof(svdservicios.fecmodif),V10LONG,
                          svdservicios.horamodif,sizeof(svdservicios.horamodif),V10CADENA,
                          &svdservicios.codcomen,sizeof(svdservicios.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselsercodservicio,"CODGRUPOSERV",svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          "CODSERVICIO",svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_selserpid(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdselserpid=abrecursordebug(SELSERPID,1280);
    definetodo(vdselserpid,svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          svdservicios.desservicio,sizeof(svdservicios.desservicio),V10CADENA,
                          svdservicios.activo,sizeof(svdservicios.activo),V10CADENA,
                          svdservicios.visualizado,sizeof(svdservicios.visualizado),V10CADENA,
                          svdservicios.ejecutable,sizeof(svdservicios.ejecutable),V10CADENA,
                          svdservicios.pathservicio,sizeof(svdservicios.pathservicio),V10CADENA,
                          svdservicios.pathv10servicio,sizeof(svdservicios.pathv10servicio),V10CADENA,
                          svdservicios.envservicio,sizeof(svdservicios.envservicio),V10CADENA,
                          svdservicios.paramservicio,sizeof(svdservicios.paramservicio),V10CADENA,
                          &svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          &svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          &svdservicios.sid,sizeof(svdservicios.sid),V10LONG,
                          &svdservicios.serial,sizeof(svdservicios.serial),V10LONG,
                          svdservicios.arranque,sizeof(svdservicios.arranque),V10CADENA,
                          svdservicios.cierre,sizeof(svdservicios.cierre),V10CADENA,
                          svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          svdservicios.patronplanif,sizeof(svdservicios.patronplanif),V10CADENA,
                          svdservicios.horainicio,sizeof(svdservicios.horainicio),V10CADENA,
                          svdservicios.horalimite,sizeof(svdservicios.horalimite),V10CADENA,
                          &svdservicios.intervalo,sizeof(svdservicios.intervalo),V10LONG,
                          &svdservicios.fecarranque,sizeof(svdservicios.fecarranque),V10LONG,
                          &svdservicios.fecultejec,sizeof(svdservicios.fecultejec),V10LONG,
                          svdservicios.horaultejec,sizeof(svdservicios.horaultejec),V10CADENA,
                          &svdservicios.fecejec,sizeof(svdservicios.fecejec),V10LONG,
                          svdservicios.horaejec,sizeof(svdservicios.horaejec),V10CADENA,
                          svdservicios.codopemodif,sizeof(svdservicios.codopemodif),V10CADENA,
                          &svdservicios.fecmodif,sizeof(svdservicios.fecmodif),V10LONG,
                          svdservicios.horamodif,sizeof(svdservicios.horamodif),V10CADENA,
                          &svdservicios.codcomen,sizeof(svdservicios.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselserpid,"PID",&svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_selsercodgruposerv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdselsercodgruposerv=abrecursordebug(SELSERCODGRUPOSERV,1280);
    definetodo(vdselsercodgruposerv,svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          svdservicios.desservicio,sizeof(svdservicios.desservicio),V10CADENA,
                          svdservicios.activo,sizeof(svdservicios.activo),V10CADENA,
                          svdservicios.visualizado,sizeof(svdservicios.visualizado),V10CADENA,
                          svdservicios.ejecutable,sizeof(svdservicios.ejecutable),V10CADENA,
                          svdservicios.pathservicio,sizeof(svdservicios.pathservicio),V10CADENA,
                          svdservicios.pathv10servicio,sizeof(svdservicios.pathv10servicio),V10CADENA,
                          svdservicios.envservicio,sizeof(svdservicios.envservicio),V10CADENA,
                          svdservicios.paramservicio,sizeof(svdservicios.paramservicio),V10CADENA,
                          &svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          &svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          &svdservicios.sid,sizeof(svdservicios.sid),V10LONG,
                          &svdservicios.serial,sizeof(svdservicios.serial),V10LONG,
                          svdservicios.arranque,sizeof(svdservicios.arranque),V10CADENA,
                          svdservicios.cierre,sizeof(svdservicios.cierre),V10CADENA,
                          svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          svdservicios.patronplanif,sizeof(svdservicios.patronplanif),V10CADENA,
                          svdservicios.horainicio,sizeof(svdservicios.horainicio),V10CADENA,
                          svdservicios.horalimite,sizeof(svdservicios.horalimite),V10CADENA,
                          &svdservicios.intervalo,sizeof(svdservicios.intervalo),V10LONG,
                          &svdservicios.fecarranque,sizeof(svdservicios.fecarranque),V10LONG,
                          &svdservicios.fecultejec,sizeof(svdservicios.fecultejec),V10LONG,
                          svdservicios.horaultejec,sizeof(svdservicios.horaultejec),V10CADENA,
                          &svdservicios.fecejec,sizeof(svdservicios.fecejec),V10LONG,
                          svdservicios.horaejec,sizeof(svdservicios.horaejec),V10CADENA,
                          svdservicios.codopemodif,sizeof(svdservicios.codopemodif),V10CADENA,
                          &svdservicios.fecmodif,sizeof(svdservicios.fecmodif),V10LONG,
                          svdservicios.horamodif,sizeof(svdservicios.horamodif),V10CADENA,
                          &svdservicios.codcomen,sizeof(svdservicios.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselsercodgruposerv,"CODGRUPOSERV",svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_selservdservicios(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdselservdservicios=abrecursordebug(SELSERVDSERVICIOS,1280);
    definetodo(vdselservdservicios,svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          svdservicios.desservicio,sizeof(svdservicios.desservicio),V10CADENA,
                          svdservicios.activo,sizeof(svdservicios.activo),V10CADENA,
                          svdservicios.visualizado,sizeof(svdservicios.visualizado),V10CADENA,
                          svdservicios.ejecutable,sizeof(svdservicios.ejecutable),V10CADENA,
                          svdservicios.pathservicio,sizeof(svdservicios.pathservicio),V10CADENA,
                          svdservicios.pathv10servicio,sizeof(svdservicios.pathv10servicio),V10CADENA,
                          svdservicios.envservicio,sizeof(svdservicios.envservicio),V10CADENA,
                          svdservicios.paramservicio,sizeof(svdservicios.paramservicio),V10CADENA,
                          &svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          &svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          &svdservicios.sid,sizeof(svdservicios.sid),V10LONG,
                          &svdservicios.serial,sizeof(svdservicios.serial),V10LONG,
                          svdservicios.arranque,sizeof(svdservicios.arranque),V10CADENA,
                          svdservicios.cierre,sizeof(svdservicios.cierre),V10CADENA,
                          svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          svdservicios.patronplanif,sizeof(svdservicios.patronplanif),V10CADENA,
                          svdservicios.horainicio,sizeof(svdservicios.horainicio),V10CADENA,
                          svdservicios.horalimite,sizeof(svdservicios.horalimite),V10CADENA,
                          &svdservicios.intervalo,sizeof(svdservicios.intervalo),V10LONG,
                          &svdservicios.fecarranque,sizeof(svdservicios.fecarranque),V10LONG,
                          &svdservicios.fecultejec,sizeof(svdservicios.fecultejec),V10LONG,
                          svdservicios.horaultejec,sizeof(svdservicios.horaultejec),V10CADENA,
                          &svdservicios.fecejec,sizeof(svdservicios.fecejec),V10LONG,
                          svdservicios.horaejec,sizeof(svdservicios.horaejec),V10CADENA,
                          svdservicios.codopemodif,sizeof(svdservicios.codopemodif),V10CADENA,
                          &svdservicios.fecmodif,sizeof(svdservicios.fecmodif),V10LONG,
                          svdservicios.horamodif,sizeof(svdservicios.horamodif),V10CADENA,
                          &svdservicios.codcomen,sizeof(svdservicios.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselservdservicios,"CODGRUPOSERV",svdservicios.codgruposerv,sizeof(svdservicios.codgruposerv),V10CADENA,
                          "CODSERVICIO",svdservicios.codservicio,sizeof(svdservicios.codservicio),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_updasersid(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdupdasersid=abrecursordebug(UPDASERSID,1280);
    bindtodo(vdupdasersid, "SID", &svdservicios.sid, sizeof(svdservicios.sid), V10LONG,
                            "SERIAL", &svdservicios.serial, sizeof(svdservicios.serial), V10LONG,
                            "MIROWID", svdservicios.rowid, sizeof(svdservicios.rowid), V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_updaserdescinmediata(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdupdaserdescinmediata=abrecursordebug(UPDASERDESCINMEDIATA,1280);
    bindtodo(vdupdaserdescinmediata,"EJECUTAR",svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          "MIROWID",svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_updaserestado(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdupdaserestado=abrecursordebug(UPDASERESTADO,1280);
    bindtodo(vdupdaserestado,"STATUS",&svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          "PID",&svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          "SID",&svdservicios.sid,sizeof(svdservicios.sid),V10LONG,
                          "FECARRANQUE",&svdservicios.fecarranque,sizeof(svdservicios.fecarranque),V10LONG,
                          "MIROWID",svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

static void init_updaserplanif(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdservicios[0].numcol;nc++) dvdservicios[0].c[nc].offset-=(size_t)&svdservicios;
    vdupdaserplanif=abrecursordebug(UPDASERPLANIF,1280);
    bindtodo(vdupdaserplanif,"STATUS",&svdservicios.status,sizeof(svdservicios.status),V10LONG,
                          "PID",&svdservicios.pid,sizeof(svdservicios.pid),V10LONG,
                          "FECULTEJEC",&svdservicios.fecultejec,sizeof(svdservicios.fecultejec),V10LONG,
                          "HORAULTEJEC",svdservicios.horaultejec,sizeof(svdservicios.horaultejec),V10CADENA,
                          "FECEJEC",&svdservicios.fecejec,sizeof(svdservicios.fecejec),V10LONG,
                          "HORAEJEC",svdservicios.horaejec,sizeof(svdservicios.horaejec),V10CADENA,
                          "EJECUTAR",svdservicios.ejecutar,sizeof(svdservicios.ejecutar),V10CADENA,
                          "MIROWID",svdservicios.rowid,sizeof(svdservicios.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ser);
        init = 1;
    }
}

diccionario *SERdamediccionario(void)
{
     return(&dser);
}

int SERselcodservicio(char *codgruposerv,char *codservicio,vdservicioss *ser)
{
  int vdret;
  if (vdselsercodservicio==NULL) init_selsercodservicio();
  memset(&svdservicios,0,sizeof(svdservicios));
  strcpy(svdservicios.codgruposerv,codgruposerv);
  strcpy(svdservicios.codservicio,codservicio);
  vdret=ejefetchcursor(vdselsercodservicio);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselsercodservicio. vdret %d. \n",SERlog(&svdservicios),vdret);
    return(VD_EERRORACLE);
   }
  *ser=svdservicios;
  return(vdret);
}

int SERselpid(long pid,vdservicioss *ser)
{
  int vdret;
  if (vdselserpid==NULL) init_selserpid();
  memset(&svdservicios,0,sizeof(svdservicios));
  svdservicios.pid=pid;
  vdret=ejefetchcursor(vdselserpid);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselserpid. vdret %d. \n",SERlog(&svdservicios),vdret);
    return(VD_EERRORACLE);
   }
  *ser=svdservicios;
  return(vdret);
}

int SERbuscacodgruposerv(char *codgruposerv,vdservicioss *ser)
{
  int vdret;
  memset(&svdservicios,0,sizeof(svdservicios));
  strcpy(svdservicios.codgruposerv,codgruposerv);
  if (vdselsercodgruposerv==NULL) init_selsercodgruposerv();
  vdret=ejefetchcursor(vdselsercodgruposerv);
  if (vdret==0) {
     *ser=svdservicios;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsercodgruposerv. vdret %d. \n",SERlog(&svdservicios),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SERnextcodgruposerv(vdservicioss *ser)
{
  int vdret;
  vdret=fetchcursor(vdselsercodgruposerv);
  if (vdret==0) {
     *ser=svdservicios;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsercodgruposerv. vdret %d. \n",SERlog(&svdservicios),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsercodgruposerv);
  return(VD_EERRORACLE);
}

int SERselvdservicios(char *codgruposerv,char *codservicio,vdservicioss *ser)
{
  int vdret;
  if (vdselservdservicios==NULL) init_selservdservicios();
  memset(&svdservicios,0,sizeof(svdservicios));
  strcpy(svdservicios.codgruposerv,codgruposerv);
  strcpy(svdservicios.codservicio,codservicio);
  vdret=ejefetchcursor(vdselservdservicios);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselservdservicios. vdret %d. \n",SERlog(&svdservicios),vdret);
    return(VD_EERRORACLE);
   }
  *ser=svdservicios;
  return(vdret);
}

int SERactualizasid(vdservicioss *ser,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SERactualizasid:  %s .  \n",SERlog(&svdservicios));
  if (vdupdasersid==NULL) init_updasersid();
  svdservicios=*ser;
  vdret=ejecutacursor(vdupdasersid);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdasersid);
     getcurerrornombre(vdupdasersid->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdasersid)!=1) return(VD_EERRORACLE);
  return(0);
}

int SERactualizadescinmediata(vdservicioss *ser,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SERactualizadescinmediata:  %s .  \n",SERlog(&svdservicios));
  if (vdupdaserdescinmediata==NULL) init_updaserdescinmediata();
  svdservicios=*ser;
  vdret=ejecutacursor(vdupdaserdescinmediata);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaserdescinmediata);
     getcurerrornombre(vdupdaserdescinmediata->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaserdescinmediata)!=1) return(VD_EERRORACLE);
  return(0);
}

int SERactualizaestado(vdservicioss *ser,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SERactualizaestado:  %s .  \n",SERlog(&svdservicios));
  if (vdupdaserestado==NULL) init_updaserestado();
  svdservicios=*ser;
  vdret=ejecutacursor(vdupdaserestado);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaserestado);
     getcurerrornombre(vdupdaserestado->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaserestado)!=1) return(VD_EERRORACLE);
  return(0);
}

int SERactualizaplanif(vdservicioss *ser,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SERactualizaplanif:  %s .  \n",SERlog(&svdservicios));
  if (vdupdaserplanif==NULL) init_updaserplanif();
  svdservicios=*ser;
  vdret=ejecutacursor(vdupdaserplanif);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaserplanif);
     getcurerrornombre(vdupdaserplanif->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaserplanif)!=1) return(VD_EERRORACLE);
  return(0);
}

char * SERlog(vdservicioss *ser)
{
    sprintf(msglogSER, "VDSERVICIOS: codgruposerv %s codservicio %s ",ser->codgruposerv,ser->codservicio);
    return(msglogSER);
}

char * SERdebug(vdservicioss *ser)
{
    debugestruct(&dser,ser,msgdebugSER);
    return(msgdebugSER);
}

