// Modulo generado automaticamente a partir de VDRECURSO.DEF
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
//TABLE=REC
//
//PRIMARIA=CODRECURSO
//
//CLAVE=CODRECURSO,CODRECURSO
//
//RECORRE=DIRRECURSO,DIRRECURSO,ORDERBY=CODRECURSO;
//
//RECORRE=STATUS,STATUS
//
//UPDATE=STATUS,STATUS
//UPDATE=NPANTALLA,CODPERFIL,NPANTALLA
//UPDATE=CONECTADO,CONECTADO,TERMINAL,SID,SERIALNUM
//UPDATE=CODOPE,CODOPE

#include "vd.h"
#define SELRECCODRECURSO "SELECT VDRECURSO.ROWID,VDRECURSO.CODRECURSO,VDRECURSO.DESRECURSO, "\
                    " VDRECURSO.ACTIVO,VDRECURSO.DIRRECURSO,VDRECURSO.PRIVILEGIOSLOGIN, "\
                    " VDRECURSO.CODUBI,VDRECURSO.CODMAT,VDRECURSO.ULTCODUBI, "\
                    " VDRECURSO.CONECTADO,VDRECURSO.TERMINAL,VDRECURSO.SID, "\
                    " VDRECURSO.SERIALNUM,VDRECURSO.CONTENEDORES,VDRECURSO.EMBALAJES, "\
                    " VDRECURSO.UNIDADESSUELTAS,VDRECURSO.CODOPE,VDRECURSO.STATUS, "\
                    " VDRECURSO.CODPERFIL,VDRECURSO.NPANTALLA,VDRECURSO.CODIMPRE, "\
                    " VDRECURSO.MAXALT,VDRECURSO.MINALT,VDRECURSO.TECLEO, "\
                    " VDRECURSO.DRIVER,VDRECURSO.LIBPLANIFICADOR,VDRECURSO.PLANIFICADOR, "\
                    " VDRECURSO.PARAMPLANIF,VDRECURSO.VDEXTRA,VDRECURSO.CODCOMEN, "\
                    " VDRECURSO.CODOPEMODIF,VDRECURSO.FECMODIF,VDRECURSO.HORAMODIF, "\
                    " VDRECURSO.FECULTCOM,VDRECURSO.HORAULTCOM "\
        " FROM VDRECURSO"\
        " WHERE "\
               " VDRECURSO.CODRECURSO=:CODRECURSO "
static v10cursors *vdselreccodrecurso;

#define SELRECDIRRECURSO "SELECT VDRECURSO.ROWID,VDRECURSO.CODRECURSO,VDRECURSO.DESRECURSO, "\
                    " VDRECURSO.ACTIVO,VDRECURSO.DIRRECURSO,VDRECURSO.PRIVILEGIOSLOGIN, "\
                    " VDRECURSO.CODUBI,VDRECURSO.CODMAT,VDRECURSO.ULTCODUBI, "\
                    " VDRECURSO.CONECTADO,VDRECURSO.TERMINAL,VDRECURSO.SID, "\
                    " VDRECURSO.SERIALNUM,VDRECURSO.CONTENEDORES,VDRECURSO.EMBALAJES, "\
                    " VDRECURSO.UNIDADESSUELTAS,VDRECURSO.CODOPE,VDRECURSO.STATUS, "\
                    " VDRECURSO.CODPERFIL,VDRECURSO.NPANTALLA,VDRECURSO.CODIMPRE, "\
                    " VDRECURSO.MAXALT,VDRECURSO.MINALT,VDRECURSO.TECLEO, "\
                    " VDRECURSO.DRIVER,VDRECURSO.LIBPLANIFICADOR,VDRECURSO.PLANIFICADOR, "\
                    " VDRECURSO.PARAMPLANIF,VDRECURSO.VDEXTRA,VDRECURSO.CODCOMEN, "\
                    " VDRECURSO.CODOPEMODIF,VDRECURSO.FECMODIF,VDRECURSO.HORAMODIF, "\
                    " VDRECURSO.FECULTCOM,VDRECURSO.HORAULTCOM "\
        " FROM VDRECURSO"\
        " WHERE "\
               " :DIRRECURSO LIKE VDRECURSO.DIRRECURSO "\
        " ORDER BY CODRECURSO "
static v10cursors *vdselrecdirrecurso;

#define SELRECSTATUS "SELECT VDRECURSO.ROWID,VDRECURSO.CODRECURSO,VDRECURSO.DESRECURSO, "\
                    " VDRECURSO.ACTIVO,VDRECURSO.DIRRECURSO,VDRECURSO.PRIVILEGIOSLOGIN, "\
                    " VDRECURSO.CODUBI,VDRECURSO.CODMAT,VDRECURSO.ULTCODUBI, "\
                    " VDRECURSO.CONECTADO,VDRECURSO.TERMINAL,VDRECURSO.SID, "\
                    " VDRECURSO.SERIALNUM,VDRECURSO.CONTENEDORES,VDRECURSO.EMBALAJES, "\
                    " VDRECURSO.UNIDADESSUELTAS,VDRECURSO.CODOPE,VDRECURSO.STATUS, "\
                    " VDRECURSO.CODPERFIL,VDRECURSO.NPANTALLA,VDRECURSO.CODIMPRE, "\
                    " VDRECURSO.MAXALT,VDRECURSO.MINALT,VDRECURSO.TECLEO, "\
                    " VDRECURSO.DRIVER,VDRECURSO.LIBPLANIFICADOR,VDRECURSO.PLANIFICADOR, "\
                    " VDRECURSO.PARAMPLANIF,VDRECURSO.VDEXTRA,VDRECURSO.CODCOMEN, "\
                    " VDRECURSO.CODOPEMODIF,VDRECURSO.FECMODIF,VDRECURSO.HORAMODIF, "\
                    " VDRECURSO.FECULTCOM,VDRECURSO.HORAULTCOM "\
        " FROM VDRECURSO"\
        " WHERE "\
               " VDRECURSO.STATUS=:STATUS "
static v10cursors *vdselrecstatus;

#define SELRECVDRECURSO "SELECT VDRECURSO.ROWID,VDRECURSO.CODRECURSO,VDRECURSO.DESRECURSO, "\
                    " VDRECURSO.ACTIVO,VDRECURSO.DIRRECURSO,VDRECURSO.PRIVILEGIOSLOGIN, "\
                    " VDRECURSO.CODUBI,VDRECURSO.CODMAT,VDRECURSO.ULTCODUBI, "\
                    " VDRECURSO.CONECTADO,VDRECURSO.TERMINAL,VDRECURSO.SID, "\
                    " VDRECURSO.SERIALNUM,VDRECURSO.CONTENEDORES,VDRECURSO.EMBALAJES, "\
                    " VDRECURSO.UNIDADESSUELTAS,VDRECURSO.CODOPE,VDRECURSO.STATUS, "\
                    " VDRECURSO.CODPERFIL,VDRECURSO.NPANTALLA,VDRECURSO.CODIMPRE, "\
                    " VDRECURSO.MAXALT,VDRECURSO.MINALT,VDRECURSO.TECLEO, "\
                    " VDRECURSO.DRIVER,VDRECURSO.LIBPLANIFICADOR,VDRECURSO.PLANIFICADOR, "\
                    " VDRECURSO.PARAMPLANIF,VDRECURSO.VDEXTRA,VDRECURSO.CODCOMEN, "\
                    " VDRECURSO.CODOPEMODIF,VDRECURSO.FECMODIF,VDRECURSO.HORAMODIF, "\
                    " VDRECURSO.FECULTCOM,VDRECURSO.HORAULTCOM "\
        " FROM VDRECURSO"\
        " WHERE "\
               " VDRECURSO.CODRECURSO=:CODRECURSO "
static v10cursors *vdselrecvdrecurso;

#define UPDARECSTATUS "UPDATE VDRECURSO SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdarecstatus;

#define UPDARECNPANTALLA "UPDATE VDRECURSO SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODPERFIL=:CODPERFIL , "\
               " NPANTALLA=:NPANTALLA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdarecnpantalla;

#define UPDARECCONECTADO "UPDATE VDRECURSO SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CONECTADO=:CONECTADO , "\
               " TERMINAL=:TERMINAL , "\
               " SID=:SID , "\
               " SERIALNUM=:SERIALNUM  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdarecconectado;

#define UPDARECCODOPE "UPDATE VDRECURSO SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODOPE=:CODOPE  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdareccodope;

static vdrecursos svdrecurso;

static diccols colvdrecurso[]={
	{"ROWID",V10CADENA,(size_t)&svdrecurso.rowid,sizeof(svdrecurso.rowid)},
	{"CODRECURSO",V10CADENA,(size_t)&svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso)},
	{"DESRECURSO",V10CADENA,(size_t)&svdrecurso.desrecurso,sizeof(svdrecurso.desrecurso)},
	{"ACTIVO",V10CADENA,(size_t)&svdrecurso.activo,sizeof(svdrecurso.activo)},
	{"DIRRECURSO",V10CADENA,(size_t)&svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso)},
	{"PRIVILEGIOSLOGIN",V10CADENA,(size_t)&svdrecurso.privilegioslogin,sizeof(svdrecurso.privilegioslogin)},
	{"CODUBI",V10CADENA,(size_t)&svdrecurso.codubi,sizeof(svdrecurso.codubi)},
	{"CODMAT",V10CADENA,(size_t)&svdrecurso.codmat,sizeof(svdrecurso.codmat)},
	{"ULTCODUBI",V10CADENA,(size_t)&svdrecurso.ultcodubi,sizeof(svdrecurso.ultcodubi)},
	{"CONECTADO",V10CADENA,(size_t)&svdrecurso.conectado,sizeof(svdrecurso.conectado)},
	{"TERMINAL",V10CADENA,(size_t)&svdrecurso.terminal,sizeof(svdrecurso.terminal)},
	{"SID",V10LONG,(size_t)&svdrecurso.sid,sizeof(svdrecurso.sid)},
	{"SERIALNUM",V10LONG,(size_t)&svdrecurso.serialnum,sizeof(svdrecurso.serialnum)},
	{"CONTENEDORES",V10CADENA,(size_t)&svdrecurso.contenedores,sizeof(svdrecurso.contenedores)},
	{"EMBALAJES",V10CADENA,(size_t)&svdrecurso.embalajes,sizeof(svdrecurso.embalajes)},
	{"UNIDADESSUELTAS",V10CADENA,(size_t)&svdrecurso.unidadessueltas,sizeof(svdrecurso.unidadessueltas)},
	{"CODOPE",V10CADENA,(size_t)&svdrecurso.codope,sizeof(svdrecurso.codope)},
	{"STATUS",V10LONG,(size_t)&svdrecurso.status,sizeof(svdrecurso.status)},
	{"CODPERFIL",V10CADENA,(size_t)&svdrecurso.codperfil,sizeof(svdrecurso.codperfil)},
	{"NPANTALLA",V10CADENA,(size_t)&svdrecurso.npantalla,sizeof(svdrecurso.npantalla)},
	{"CODIMPRE",V10CADENA,(size_t)&svdrecurso.codimpre,sizeof(svdrecurso.codimpre)},
	{"MAXALT",V10LONG,(size_t)&svdrecurso.maxalt,sizeof(svdrecurso.maxalt)},
	{"MINALT",V10LONG,(size_t)&svdrecurso.minalt,sizeof(svdrecurso.minalt)},
	{"TECLEO",V10CADENA,(size_t)&svdrecurso.tecleo,sizeof(svdrecurso.tecleo)},
	{"DRIVER",V10CADENA,(size_t)&svdrecurso.driver,sizeof(svdrecurso.driver)},
	{"LIBPLANIFICADOR",V10CADENA,(size_t)&svdrecurso.libplanificador,sizeof(svdrecurso.libplanificador)},
	{"PLANIFICADOR",V10CADENA,(size_t)&svdrecurso.planificador,sizeof(svdrecurso.planificador)},
	{"PARAMPLANIF",V10CADENA,(size_t)&svdrecurso.paramplanif,sizeof(svdrecurso.paramplanif)},
	{"VDEXTRA",V10CADENA,(size_t)&svdrecurso.vdextra,sizeof(svdrecurso.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdrecurso.codcomen,sizeof(svdrecurso.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdrecurso.codopemodif,sizeof(svdrecurso.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdrecurso.fecmodif,sizeof(svdrecurso.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdrecurso.horamodif,sizeof(svdrecurso.horamodif)},
	{"FECULTCOM",V10LONG,(size_t)&svdrecurso.fecultcom,sizeof(svdrecurso.fecultcom)},
	{"HORAULTCOM",V10CADENA,(size_t)&svdrecurso.horaultcom,sizeof(svdrecurso.horaultcom)}
	};
static diccionarios dvdrecurso[]={
    {colvdrecurso,35}
};
diccionario drec={dvdrecurso,1};

static char msglogREC[LCADENA];
static char msgdebugREC[LCADENABIG];
static int init=0;


static void fin_vd_rec(void)
{
if (vdselreccodrecurso) {
    liberacursor(vdselreccodrecurso);
    vdselreccodrecurso = NULL;
}
if (vdselrecdirrecurso) {
    liberacursor(vdselrecdirrecurso);
    vdselrecdirrecurso = NULL;
}
if (vdselrecstatus) {
    liberacursor(vdselrecstatus);
    vdselrecstatus = NULL;
}
if (vdselrecvdrecurso) {
    liberacursor(vdselrecvdrecurso);
    vdselrecvdrecurso = NULL;
}
if (vdupdarecstatus) {
    liberacursor(vdupdarecstatus);
    vdupdarecstatus = NULL;
}
if (vdupdarecnpantalla) {
    liberacursor(vdupdarecnpantalla);
    vdupdarecnpantalla = NULL;
}
if (vdupdarecconectado) {
    liberacursor(vdupdarecconectado);
    vdupdarecconectado = NULL;
}
if (vdupdareccodope) {
    liberacursor(vdupdareccodope);
    vdupdareccodope = NULL;
}
}
static void init_selreccodrecurso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdselreccodrecurso=abrecursordebug(SELRECCODRECURSO,1280);
    definetodo(vdselreccodrecurso,svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          svdrecurso.desrecurso,sizeof(svdrecurso.desrecurso),V10CADENA,
                          svdrecurso.activo,sizeof(svdrecurso.activo),V10CADENA,
                          svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso),V10CADENA,
                          svdrecurso.privilegioslogin,sizeof(svdrecurso.privilegioslogin),V10CADENA,
                          svdrecurso.codubi,sizeof(svdrecurso.codubi),V10CADENA,
                          svdrecurso.codmat,sizeof(svdrecurso.codmat),V10CADENA,
                          svdrecurso.ultcodubi,sizeof(svdrecurso.ultcodubi),V10CADENA,
                          svdrecurso.conectado,sizeof(svdrecurso.conectado),V10CADENA,
                          svdrecurso.terminal,sizeof(svdrecurso.terminal),V10CADENA,
                          &svdrecurso.sid,sizeof(svdrecurso.sid),V10LONG,
                          &svdrecurso.serialnum,sizeof(svdrecurso.serialnum),V10LONG,
                          svdrecurso.contenedores,sizeof(svdrecurso.contenedores),V10CADENA,
                          svdrecurso.embalajes,sizeof(svdrecurso.embalajes),V10CADENA,
                          svdrecurso.unidadessueltas,sizeof(svdrecurso.unidadessueltas),V10CADENA,
                          svdrecurso.codope,sizeof(svdrecurso.codope),V10CADENA,
                          &svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          svdrecurso.codperfil,sizeof(svdrecurso.codperfil),V10CADENA,
                          svdrecurso.npantalla,sizeof(svdrecurso.npantalla),V10CADENA,
                          svdrecurso.codimpre,sizeof(svdrecurso.codimpre),V10CADENA,
                          &svdrecurso.maxalt,sizeof(svdrecurso.maxalt),V10LONG,
                          &svdrecurso.minalt,sizeof(svdrecurso.minalt),V10LONG,
                          svdrecurso.tecleo,sizeof(svdrecurso.tecleo),V10CADENA,
                          svdrecurso.driver,sizeof(svdrecurso.driver),V10CADENA,
                          svdrecurso.libplanificador,sizeof(svdrecurso.libplanificador),V10CADENA,
                          svdrecurso.planificador,sizeof(svdrecurso.planificador),V10CADENA,
                          svdrecurso.paramplanif,sizeof(svdrecurso.paramplanif),V10CADENA,
                          svdrecurso.vdextra,sizeof(svdrecurso.vdextra),V10CADENA,
                          &svdrecurso.codcomen,sizeof(svdrecurso.codcomen),V10LONG,
                          svdrecurso.codopemodif,sizeof(svdrecurso.codopemodif),V10CADENA,
                          &svdrecurso.fecmodif,sizeof(svdrecurso.fecmodif),V10LONG,
                          svdrecurso.horamodif,sizeof(svdrecurso.horamodif),V10CADENA,
                          &svdrecurso.fecultcom,sizeof(svdrecurso.fecultcom),V10LONG,
                          svdrecurso.horaultcom,sizeof(svdrecurso.horaultcom),V10CADENA,
                          NULL);
    bindtodo(vdselreccodrecurso,"CODRECURSO",svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_selrecdirrecurso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdselrecdirrecurso=abrecursordebug(SELRECDIRRECURSO,1280);
    definetodo(vdselrecdirrecurso,svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          svdrecurso.desrecurso,sizeof(svdrecurso.desrecurso),V10CADENA,
                          svdrecurso.activo,sizeof(svdrecurso.activo),V10CADENA,
                          svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso),V10CADENA,
                          svdrecurso.privilegioslogin,sizeof(svdrecurso.privilegioslogin),V10CADENA,
                          svdrecurso.codubi,sizeof(svdrecurso.codubi),V10CADENA,
                          svdrecurso.codmat,sizeof(svdrecurso.codmat),V10CADENA,
                          svdrecurso.ultcodubi,sizeof(svdrecurso.ultcodubi),V10CADENA,
                          svdrecurso.conectado,sizeof(svdrecurso.conectado),V10CADENA,
                          svdrecurso.terminal,sizeof(svdrecurso.terminal),V10CADENA,
                          &svdrecurso.sid,sizeof(svdrecurso.sid),V10LONG,
                          &svdrecurso.serialnum,sizeof(svdrecurso.serialnum),V10LONG,
                          svdrecurso.contenedores,sizeof(svdrecurso.contenedores),V10CADENA,
                          svdrecurso.embalajes,sizeof(svdrecurso.embalajes),V10CADENA,
                          svdrecurso.unidadessueltas,sizeof(svdrecurso.unidadessueltas),V10CADENA,
                          svdrecurso.codope,sizeof(svdrecurso.codope),V10CADENA,
                          &svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          svdrecurso.codperfil,sizeof(svdrecurso.codperfil),V10CADENA,
                          svdrecurso.npantalla,sizeof(svdrecurso.npantalla),V10CADENA,
                          svdrecurso.codimpre,sizeof(svdrecurso.codimpre),V10CADENA,
                          &svdrecurso.maxalt,sizeof(svdrecurso.maxalt),V10LONG,
                          &svdrecurso.minalt,sizeof(svdrecurso.minalt),V10LONG,
                          svdrecurso.tecleo,sizeof(svdrecurso.tecleo),V10CADENA,
                          svdrecurso.driver,sizeof(svdrecurso.driver),V10CADENA,
                          svdrecurso.libplanificador,sizeof(svdrecurso.libplanificador),V10CADENA,
                          svdrecurso.planificador,sizeof(svdrecurso.planificador),V10CADENA,
                          svdrecurso.paramplanif,sizeof(svdrecurso.paramplanif),V10CADENA,
                          svdrecurso.vdextra,sizeof(svdrecurso.vdextra),V10CADENA,
                          &svdrecurso.codcomen,sizeof(svdrecurso.codcomen),V10LONG,
                          svdrecurso.codopemodif,sizeof(svdrecurso.codopemodif),V10CADENA,
                          &svdrecurso.fecmodif,sizeof(svdrecurso.fecmodif),V10LONG,
                          svdrecurso.horamodif,sizeof(svdrecurso.horamodif),V10CADENA,
                          &svdrecurso.fecultcom,sizeof(svdrecurso.fecultcom),V10LONG,
                          svdrecurso.horaultcom,sizeof(svdrecurso.horaultcom),V10CADENA,
                          NULL);
    bindtodo(vdselrecdirrecurso,"DIRRECURSO",svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_selrecstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdselrecstatus=abrecursordebug(SELRECSTATUS,1280);
    definetodo(vdselrecstatus,svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          svdrecurso.desrecurso,sizeof(svdrecurso.desrecurso),V10CADENA,
                          svdrecurso.activo,sizeof(svdrecurso.activo),V10CADENA,
                          svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso),V10CADENA,
                          svdrecurso.privilegioslogin,sizeof(svdrecurso.privilegioslogin),V10CADENA,
                          svdrecurso.codubi,sizeof(svdrecurso.codubi),V10CADENA,
                          svdrecurso.codmat,sizeof(svdrecurso.codmat),V10CADENA,
                          svdrecurso.ultcodubi,sizeof(svdrecurso.ultcodubi),V10CADENA,
                          svdrecurso.conectado,sizeof(svdrecurso.conectado),V10CADENA,
                          svdrecurso.terminal,sizeof(svdrecurso.terminal),V10CADENA,
                          &svdrecurso.sid,sizeof(svdrecurso.sid),V10LONG,
                          &svdrecurso.serialnum,sizeof(svdrecurso.serialnum),V10LONG,
                          svdrecurso.contenedores,sizeof(svdrecurso.contenedores),V10CADENA,
                          svdrecurso.embalajes,sizeof(svdrecurso.embalajes),V10CADENA,
                          svdrecurso.unidadessueltas,sizeof(svdrecurso.unidadessueltas),V10CADENA,
                          svdrecurso.codope,sizeof(svdrecurso.codope),V10CADENA,
                          &svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          svdrecurso.codperfil,sizeof(svdrecurso.codperfil),V10CADENA,
                          svdrecurso.npantalla,sizeof(svdrecurso.npantalla),V10CADENA,
                          svdrecurso.codimpre,sizeof(svdrecurso.codimpre),V10CADENA,
                          &svdrecurso.maxalt,sizeof(svdrecurso.maxalt),V10LONG,
                          &svdrecurso.minalt,sizeof(svdrecurso.minalt),V10LONG,
                          svdrecurso.tecleo,sizeof(svdrecurso.tecleo),V10CADENA,
                          svdrecurso.driver,sizeof(svdrecurso.driver),V10CADENA,
                          svdrecurso.libplanificador,sizeof(svdrecurso.libplanificador),V10CADENA,
                          svdrecurso.planificador,sizeof(svdrecurso.planificador),V10CADENA,
                          svdrecurso.paramplanif,sizeof(svdrecurso.paramplanif),V10CADENA,
                          svdrecurso.vdextra,sizeof(svdrecurso.vdextra),V10CADENA,
                          &svdrecurso.codcomen,sizeof(svdrecurso.codcomen),V10LONG,
                          svdrecurso.codopemodif,sizeof(svdrecurso.codopemodif),V10CADENA,
                          &svdrecurso.fecmodif,sizeof(svdrecurso.fecmodif),V10LONG,
                          svdrecurso.horamodif,sizeof(svdrecurso.horamodif),V10CADENA,
                          &svdrecurso.fecultcom,sizeof(svdrecurso.fecultcom),V10LONG,
                          svdrecurso.horaultcom,sizeof(svdrecurso.horaultcom),V10CADENA,
                          NULL);
    bindtodo(vdselrecstatus,"STATUS",&svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_selrecvdrecurso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdselrecvdrecurso=abrecursordebug(SELRECVDRECURSO,1280);
    definetodo(vdselrecvdrecurso,svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          svdrecurso.desrecurso,sizeof(svdrecurso.desrecurso),V10CADENA,
                          svdrecurso.activo,sizeof(svdrecurso.activo),V10CADENA,
                          svdrecurso.dirrecurso,sizeof(svdrecurso.dirrecurso),V10CADENA,
                          svdrecurso.privilegioslogin,sizeof(svdrecurso.privilegioslogin),V10CADENA,
                          svdrecurso.codubi,sizeof(svdrecurso.codubi),V10CADENA,
                          svdrecurso.codmat,sizeof(svdrecurso.codmat),V10CADENA,
                          svdrecurso.ultcodubi,sizeof(svdrecurso.ultcodubi),V10CADENA,
                          svdrecurso.conectado,sizeof(svdrecurso.conectado),V10CADENA,
                          svdrecurso.terminal,sizeof(svdrecurso.terminal),V10CADENA,
                          &svdrecurso.sid,sizeof(svdrecurso.sid),V10LONG,
                          &svdrecurso.serialnum,sizeof(svdrecurso.serialnum),V10LONG,
                          svdrecurso.contenedores,sizeof(svdrecurso.contenedores),V10CADENA,
                          svdrecurso.embalajes,sizeof(svdrecurso.embalajes),V10CADENA,
                          svdrecurso.unidadessueltas,sizeof(svdrecurso.unidadessueltas),V10CADENA,
                          svdrecurso.codope,sizeof(svdrecurso.codope),V10CADENA,
                          &svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          svdrecurso.codperfil,sizeof(svdrecurso.codperfil),V10CADENA,
                          svdrecurso.npantalla,sizeof(svdrecurso.npantalla),V10CADENA,
                          svdrecurso.codimpre,sizeof(svdrecurso.codimpre),V10CADENA,
                          &svdrecurso.maxalt,sizeof(svdrecurso.maxalt),V10LONG,
                          &svdrecurso.minalt,sizeof(svdrecurso.minalt),V10LONG,
                          svdrecurso.tecleo,sizeof(svdrecurso.tecleo),V10CADENA,
                          svdrecurso.driver,sizeof(svdrecurso.driver),V10CADENA,
                          svdrecurso.libplanificador,sizeof(svdrecurso.libplanificador),V10CADENA,
                          svdrecurso.planificador,sizeof(svdrecurso.planificador),V10CADENA,
                          svdrecurso.paramplanif,sizeof(svdrecurso.paramplanif),V10CADENA,
                          svdrecurso.vdextra,sizeof(svdrecurso.vdextra),V10CADENA,
                          &svdrecurso.codcomen,sizeof(svdrecurso.codcomen),V10LONG,
                          svdrecurso.codopemodif,sizeof(svdrecurso.codopemodif),V10CADENA,
                          &svdrecurso.fecmodif,sizeof(svdrecurso.fecmodif),V10LONG,
                          svdrecurso.horamodif,sizeof(svdrecurso.horamodif),V10CADENA,
                          &svdrecurso.fecultcom,sizeof(svdrecurso.fecultcom),V10LONG,
                          svdrecurso.horaultcom,sizeof(svdrecurso.horaultcom),V10CADENA,
                          NULL);
    bindtodo(vdselrecvdrecurso,"CODRECURSO",svdrecurso.codrecurso,sizeof(svdrecurso.codrecurso),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_updarecstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdupdarecstatus=abrecursordebug(UPDARECSTATUS,1280);
    bindtodo(vdupdarecstatus,"STATUS",&svdrecurso.status,sizeof(svdrecurso.status),V10LONG,
                          "MIROWID",svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_updarecnpantalla(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdupdarecnpantalla=abrecursordebug(UPDARECNPANTALLA,1280);
    bindtodo(vdupdarecnpantalla,"CODPERFIL",svdrecurso.codperfil,sizeof(svdrecurso.codperfil),V10CADENA,
                          "NPANTALLA",svdrecurso.npantalla,sizeof(svdrecurso.npantalla),V10CADENA,
                          "MIROWID",svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_updarecconectado(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdupdarecconectado=abrecursordebug(UPDARECCONECTADO,1280);
    bindtodo(vdupdarecconectado,"CONECTADO",svdrecurso.conectado,sizeof(svdrecurso.conectado),V10CADENA,
                          "TERMINAL",svdrecurso.terminal,sizeof(svdrecurso.terminal),V10CADENA,
                          "SID",&svdrecurso.sid,sizeof(svdrecurso.sid),V10LONG,
                          "SERIALNUM",&svdrecurso.serialnum,sizeof(svdrecurso.serialnum),V10LONG,
                          "MIROWID",svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

static void init_updareccodope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdrecurso[0].numcol;nc++) dvdrecurso[0].c[nc].offset-=(size_t)&svdrecurso;
    vdupdareccodope=abrecursordebug(UPDARECCODOPE,1280);
    bindtodo(vdupdareccodope,"CODOPE",svdrecurso.codope,sizeof(svdrecurso.codope),V10CADENA,
                          "MIROWID",svdrecurso.rowid,sizeof(svdrecurso.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_rec);
        init = 1;
    }
}

diccionario *RECdamediccionario(void)
{
     return(&drec);
}

int RECselcodrecurso(char *codrecurso,vdrecursos *rec)
{
  int vdret;
  if (vdselreccodrecurso==NULL) init_selreccodrecurso();
  memset(&svdrecurso,0,sizeof(svdrecurso));
  strcpy(svdrecurso.codrecurso,codrecurso);
  vdret=ejefetchcursor(vdselreccodrecurso);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselreccodrecurso. vdret %d. \n",REClog(&svdrecurso),vdret);
    return(VD_EERRORACLE);
   }
  *rec=svdrecurso;
  return(vdret);
}

int RECbuscadirrecurso(char *dirrecurso,vdrecursos *rec)
{
  int vdret;
  memset(&svdrecurso,0,sizeof(svdrecurso));
  strcpy(svdrecurso.dirrecurso,dirrecurso);
  if (vdselrecdirrecurso==NULL) init_selrecdirrecurso();
  vdret=ejefetchcursor(vdselrecdirrecurso);
  if (vdret==0) {
     *rec=svdrecurso;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselrecdirrecurso. vdret %d. \n",REClog(&svdrecurso),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int RECnextdirrecurso(vdrecursos *rec)
{
  int vdret;
  vdret=fetchcursor(vdselrecdirrecurso);
  if (vdret==0) {
     *rec=svdrecurso;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselrecdirrecurso. vdret %d. \n",REClog(&svdrecurso),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselrecdirrecurso);
  return(VD_EERRORACLE);
}

int RECbuscastatus(long status,vdrecursos *rec)
{
  int vdret;
  memset(&svdrecurso,0,sizeof(svdrecurso));
  svdrecurso.status=status;
  if (vdselrecstatus==NULL) init_selrecstatus();
  vdret=ejefetchcursor(vdselrecstatus);
  if (vdret==0) {
     *rec=svdrecurso;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselrecstatus. vdret %d. \n",REClog(&svdrecurso),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int RECnextstatus(vdrecursos *rec)
{
  int vdret;
  vdret=fetchcursor(vdselrecstatus);
  if (vdret==0) {
     *rec=svdrecurso;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselrecstatus. vdret %d. \n",REClog(&svdrecurso),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselrecstatus);
  return(VD_EERRORACLE);
}

int RECselvdrecurso(char *codrecurso,vdrecursos *rec)
{
  int vdret;
  if (vdselrecvdrecurso==NULL) init_selrecvdrecurso();
  memset(&svdrecurso,0,sizeof(svdrecurso));
  strcpy(svdrecurso.codrecurso,codrecurso);
  vdret=ejefetchcursor(vdselrecvdrecurso);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselrecvdrecurso. vdret %d. \n",REClog(&svdrecurso),vdret);
    return(VD_EERRORACLE);
   }
  *rec=svdrecurso;
  return(vdret);
}

int RECactualizastatus(vdrecursos *rec,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando RECactualizastatus:  %s .  \n",REClog(&svdrecurso));
  if (vdupdarecstatus==NULL) init_updarecstatus();
  svdrecurso=*rec;
  vdret=ejecutacursor(vdupdarecstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdarecstatus);
     getcurerrornombre(vdupdarecstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdarecstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int RECactualizanpantalla(vdrecursos *rec,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando RECactualizanpantalla:  %s .  \n",REClog(&svdrecurso));
  if (vdupdarecnpantalla==NULL) init_updarecnpantalla();
  svdrecurso=*rec;
  vdret=ejecutacursor(vdupdarecnpantalla);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdarecnpantalla);
     getcurerrornombre(vdupdarecnpantalla->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdarecnpantalla)!=1) return(VD_EERRORACLE);
  return(0);
}

int RECactualizaconectado(vdrecursos *rec,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando RECactualizaconectado:  %s .  \n",REClog(&svdrecurso));
  if (vdupdarecconectado==NULL) init_updarecconectado();
  svdrecurso=*rec;
  vdret=ejecutacursor(vdupdarecconectado);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdarecconectado);
     getcurerrornombre(vdupdarecconectado->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdarecconectado)!=1) return(VD_EERRORACLE);
  return(0);
}

int RECactualizacodope(vdrecursos *rec,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando RECactualizacodope:  %s .  \n",REClog(&svdrecurso));
  if (vdupdareccodope==NULL) init_updareccodope();
  svdrecurso=*rec;
  vdret=ejecutacursor(vdupdareccodope);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdareccodope);
     getcurerrornombre(vdupdareccodope->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdareccodope)!=1) return(VD_EERRORACLE);
  return(0);
}

char * REClog(vdrecursos *rec)
{
    sprintf(msglogREC, "VDRECURSO: codrecurso %s ",rec->codrecurso);
    return(msglogREC);
}

char * RECdebug(vdrecursos *rec)
{
    debugestruct(&drec,rec,msgdebugREC);
    return(msgdebugREC);
}

