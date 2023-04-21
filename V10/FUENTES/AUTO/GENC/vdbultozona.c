// Modulo generado automaticamente a partir de VDBULTOZONA.DEF
//#***
//# VDBULTOZONA.DEF - Generación automática del código c para la tabla de INFOBULTOZONAS                                                       
//# 
//# Propósito: Funciones de acceso a la tabla INFOBULTOZONA
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 27-05-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=BZO
//
//CLAVE=BULTO,CODBULTO
//CLAVE=DAMEOPEBULTO,CODZONA,CODBULTO
//CLAVE=ZONAPEND,CODZONA,WHERE=STATUS=VDST.FBZOPDTECONF;
//CLAVE=NUMBUL,GENCOUNT=CODBULTO;WHERE=CODZONA=:CODZONA; 
//SECUENCIA=VDSECBULTOZONA,SEQBULTO
//RECORRE=CODBULTO,CODBULTO
//RECORRE=ZONAOPE,CODZONA,CODOPE; 
//
//RECORRE=FINBULTO,TABLE=VDBULTOCAB;WHERE=VDBULTOCAB.CODBULTO=VDBULTOZONA.CODBULTO AND VDBULTOZONA.CODZONA=:CODZONA AND VDBULTOCAB.STATUS=VDST.FBUCPREPARADO;
//
//RECORRE=CODZONA,CODZONA;ORDERBY=STATUS; 
//RECORRE=ZONSTAT,CODZONA,STATUS
//
//UPDATE=STATUS,STATUS
//UPDATE=CODOPE,CODOPE
//
//
//
//INSERT 
//DELETE

#include "vd.h"
#define SELBZOBULTO "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODBULTO=:CODBULTO "
static v10cursors *vdselbzobulto;

#define SELBZODAMEOPEBULTO "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODZONA=:CODZONA "\
               " AND VDBULTOZONA.CODBULTO=:CODBULTO "
static v10cursors *vdselbzodameopebulto;

#define SELBZOZONAPEND "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODZONA=:CODZONA "\
              "  AND STATUS=VDST.FBZOPDTECONF "
static v10cursors *vdselbzozonapend;

#define SELBZONUMBUL "SELECT COUNT(DISTINCT CODBULTO) GENCOUNT "\
        " FROM VDBULTOZONA"\
        " WHERE "\
              " CODZONA=:CODZONA "
static v10cursors *vdselbzonumbul;

#define SELBZOCODBULTO "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODBULTO=:CODBULTO "
static v10cursors *vdselbzocodbulto;

#define SELBZOZONAOPE "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODZONA=:CODZONA "\
               " AND VDBULTOZONA.CODOPE=:CODOPE "
static v10cursors *vdselbzozonaope;

#define SELBZOFINBULTO "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA ,VDBULTOCAB"\
        " WHERE "\
              " VDBULTOCAB.CODBULTO=VDBULTOZONA.CODBULTO AND VDBULTOZONA.CODZONA=:CODZONA AND VDBULTOCAB.STATUS=VDST.FBUCPREPARADO "
static v10cursors *vdselbzofinbulto;

#define SELBZOCODZONA "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODZONA=:CODZONA "\
        " ORDER BY STATUS "
static v10cursors *vdselbzocodzona;

#define SELBZOZONSTAT "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.CODZONA=:CODZONA "\
               " AND VDBULTOZONA.STATUS=:STATUS "
static v10cursors *vdselbzozonstat;

#define SELBZOVDBULTOZONA "SELECT VDBULTOZONA.ROWID,VDBULTOZONA.SEQBULTO,VDBULTOZONA.CODZONA, "\
                    " VDBULTOZONA.CODBULTO,VDBULTOZONA.CODOPE,VDBULTOZONA.COLOROPE, "\
                    " VDBULTOZONA.STATUS,VDBULTOZONA.VDEXTRA,VDBULTOZONA.CODOPEMODIF, "\
                    " VDBULTOZONA.FECMODIF,VDBULTOZONA.HORAMODIF,VDBULTOZONA.CODCOMEN "\
        " FROM VDBULTOZONA"\
        " WHERE "\
               " VDBULTOZONA.SEQBULTO=:SEQBULTO "
static v10cursors *vdselbzovdbultozona;

#define UPDABZOSTATUS "UPDATE VDBULTOZONA SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabzostatus;

#define UPDABZOCODOPE "UPDATE VDBULTOZONA SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODOPE=:CODOPE  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabzocodope;

#define SELVDSECBULTOZONA "SELECT VDSECBULTOZONA.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecbultozona;

#define INSBZO "INSERT INTO VDBULTOZONA (SEQBULTO,CODZONA,CODBULTO,CODOPE,COLOROPE,STATUS, "\
                    " VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :SEQBULTO,:CODZONA,:CODBULTO,:CODOPE,:COLOROPE,:STATUS, "\
                    " :VDEXTRA,VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS(),:CODCOMEN) "
static v10cursors *vdinsbzo;

#define DELBZO "DELETE VDBULTOZONA WHERE ROWID=:MIROWID "
static v10cursors *vddelbzo;

static vdbultozonas svdbultozona;

static diccols colvdbultozona[]={
	{"ROWID",V10CADENA,(size_t)&svdbultozona.rowid,sizeof(svdbultozona.rowid)},
	{"SEQBULTO",V10LONG,(size_t)&svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto)},
	{"CODZONA",V10LONG,(size_t)&svdbultozona.codzona,sizeof(svdbultozona.codzona)},
	{"CODBULTO",V10CADENA,(size_t)&svdbultozona.codbulto,sizeof(svdbultozona.codbulto)},
	{"CODOPE",V10CADENA,(size_t)&svdbultozona.codope,sizeof(svdbultozona.codope)},
	{"COLOROPE",V10CADENA,(size_t)&svdbultozona.colorope,sizeof(svdbultozona.colorope)},
	{"STATUS",V10LONG,(size_t)&svdbultozona.status,sizeof(svdbultozona.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdbultozona.vdextra,sizeof(svdbultozona.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdbultozona.horamodif,sizeof(svdbultozona.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdbultozona.codcomen,sizeof(svdbultozona.codcomen)},
	{"GENCOUNT",V10DOUBLE,(size_t)&svdbultozona.gencount,sizeof(svdbultozona.gencount)}
	};
static diccionarios dvdbultozona[]={
    {colvdbultozona,13}
};
diccionario dbzo={dvdbultozona,1};

static char msglogBZO[LCADENA];
static char msgdebugBZO[LCADENABIG];
static int init=0;


static void fin_vd_bzo(void)
{
if (vdselbzobulto) {
    liberacursor(vdselbzobulto);
    vdselbzobulto = NULL;
}
if (vdselbzodameopebulto) {
    liberacursor(vdselbzodameopebulto);
    vdselbzodameopebulto = NULL;
}
if (vdselbzozonapend) {
    liberacursor(vdselbzozonapend);
    vdselbzozonapend = NULL;
}
if (vdselbzonumbul) {
    liberacursor(vdselbzonumbul);
    vdselbzonumbul = NULL;
}
if (vdselbzocodbulto) {
    liberacursor(vdselbzocodbulto);
    vdselbzocodbulto = NULL;
}
if (vdselbzozonaope) {
    liberacursor(vdselbzozonaope);
    vdselbzozonaope = NULL;
}
if (vdselbzofinbulto) {
    liberacursor(vdselbzofinbulto);
    vdselbzofinbulto = NULL;
}
if (vdselbzocodzona) {
    liberacursor(vdselbzocodzona);
    vdselbzocodzona = NULL;
}
if (vdselbzozonstat) {
    liberacursor(vdselbzozonstat);
    vdselbzozonstat = NULL;
}
if (vdselbzovdbultozona) {
    liberacursor(vdselbzovdbultozona);
    vdselbzovdbultozona = NULL;
}
if (vdupdabzostatus) {
    liberacursor(vdupdabzostatus);
    vdupdabzostatus = NULL;
}
if (vdupdabzocodope) {
    liberacursor(vdupdabzocodope);
    vdupdabzocodope = NULL;
}
if (vdselvdsecbultozona != NULL) {
    liberacursor(vdselvdsecbultozona);
    vdselvdsecbultozona = NULL;
}
if (vdinsbzo != NULL) {
    liberacursor(vdinsbzo);
    vdinsbzo = NULL;
}
if (vddelbzo != NULL) {
    liberacursor(vddelbzo);
    vddelbzo = NULL;
}
}
static void init_selbzobulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzobulto=abrecursordebug(SELBZOBULTO,1280);
    definetodo(vdselbzobulto,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzobulto,"CODBULTO",svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzodameopebulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzodameopebulto=abrecursordebug(SELBZODAMEOPEBULTO,1280);
    definetodo(vdselbzodameopebulto,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzodameopebulto,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          "CODBULTO",svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzozonapend(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzozonapend=abrecursordebug(SELBZOZONAPEND,1280);
    definetodo(vdselbzozonapend,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzozonapend,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzonumbul(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzonumbul=abrecursordebug(SELBZONUMBUL,1280);
    definetodo(vdselbzonumbul,&svdbultozona.gencount,sizeof(svdbultozona.gencount),V10DOUBLE,
                          NULL);
    bindtodo(vdselbzonumbul,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzocodbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzocodbulto=abrecursordebug(SELBZOCODBULTO,1280);
    definetodo(vdselbzocodbulto,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzocodbulto,"CODBULTO",svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzozonaope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzozonaope=abrecursordebug(SELBZOZONAOPE,1280);
    definetodo(vdselbzozonaope,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzozonaope,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          "CODOPE",svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzofinbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzofinbulto=abrecursordebug(SELBZOFINBULTO,1280);
    definetodo(vdselbzofinbulto,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzofinbulto,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzocodzona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzocodzona=abrecursordebug(SELBZOCODZONA,1280);
    definetodo(vdselbzocodzona,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzocodzona,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzozonstat(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzozonstat=abrecursordebug(SELBZOZONSTAT,1280);
    definetodo(vdselbzozonstat,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzozonstat,"CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          "STATUS",&svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selbzovdbultozona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselbzovdbultozona=abrecursordebug(SELBZOVDBULTOZONA,1280);
    definetodo(vdselbzovdbultozona,svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          &svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          &svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          &svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          svdbultozona.codopemodif,sizeof(svdbultozona.codopemodif),V10CADENA,
                          &svdbultozona.fecmodif,sizeof(svdbultozona.fecmodif),V10LONG,
                          svdbultozona.horamodif,sizeof(svdbultozona.horamodif),V10CADENA,
                          &svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselbzovdbultozona,"SEQBULTO",&svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_updabzostatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdupdabzostatus=abrecursordebug(UPDABZOSTATUS,1280);
    bindtodo(vdupdabzostatus,"STATUS",&svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          "MIROWID",svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_updabzocodope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdupdabzocodope=abrecursordebug(UPDABZOCODOPE,1280);
    bindtodo(vdupdabzocodope,"CODOPE",svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          "MIROWID",svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_selvdsecbultozona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdselvdsecbultozona=abrecursordebug(SELVDSECBULTOZONA,1280);
    definetodo(vdselvdsecbultozona,&svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_insbzo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vdinsbzo=abrecursordebug(INSBZO,1280);
    bindtodo(vdinsbzo,"SEQBULTO",&svdbultozona.seqbulto,sizeof(svdbultozona.seqbulto),V10LONG,
                          "CODZONA",&svdbultozona.codzona,sizeof(svdbultozona.codzona),V10LONG,
                          "CODBULTO",svdbultozona.codbulto,sizeof(svdbultozona.codbulto),V10CADENA,
                          "CODOPE",svdbultozona.codope,sizeof(svdbultozona.codope),V10CADENA,
                          "COLOROPE",svdbultozona.colorope,sizeof(svdbultozona.colorope),V10CADENA,
                          "STATUS",&svdbultozona.status,sizeof(svdbultozona.status),V10LONG,
                          "VDEXTRA",svdbultozona.vdextra,sizeof(svdbultozona.vdextra),V10CADENA,
                          "CODCOMEN",&svdbultozona.codcomen,sizeof(svdbultozona.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

static void init_delbzo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultozona[0].numcol;nc++) dvdbultozona[0].c[nc].offset-=(size_t)&svdbultozona;
    vddelbzo=abrecursordebug(DELBZO,1280);
    bindtodo(vddelbzo,"MIROWID",svdbultozona.rowid,sizeof(svdbultozona.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bzo);
        init = 1;
    }
}

diccionario *BZOdamediccionario(void)
{
     return(&dbzo);
}

int BZOselbulto(char *codbulto,vdbultozonas *bzo)
{
  int vdret;
  if (vdselbzobulto==NULL) init_selbzobulto();
  memset(&svdbultozona,0,sizeof(svdbultozona));
  strcpy(svdbultozona.codbulto,codbulto);
  vdret=ejefetchcursor(vdselbzobulto);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbzobulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
    return(VD_EERRORACLE);
   }
  *bzo=svdbultozona;
  return(vdret);
}

int BZOseldameopebulto(long codzona,char *codbulto,vdbultozonas *bzo)
{
  int vdret;
  if (vdselbzodameopebulto==NULL) init_selbzodameopebulto();
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  strcpy(svdbultozona.codbulto,codbulto);
  vdret=ejefetchcursor(vdselbzodameopebulto);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbzodameopebulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
    return(VD_EERRORACLE);
   }
  *bzo=svdbultozona;
  return(vdret);
}

int BZOselzonapend(long codzona,vdbultozonas *bzo)
{
  int vdret;
  if (vdselbzozonapend==NULL) init_selbzozonapend();
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  vdret=ejefetchcursor(vdselbzozonapend);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbzozonapend. vdret %d. \n",BZOlog(&svdbultozona),vdret);
    return(VD_EERRORACLE);
   }
  *bzo=svdbultozona;
  return(vdret);
}

int BZOselnumbul(long codzona,vdbultozonas *bzo)
{
  int vdret;
  if (vdselbzonumbul==NULL) init_selbzonumbul();
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  vdret=ejefetchcursor(vdselbzonumbul);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbzonumbul. vdret %d. \n",BZOlog(&svdbultozona),vdret);
    return(VD_EERRORACLE);
   }
  *bzo=svdbultozona;
  return(vdret);
}

int BZObuscacodbulto(char *codbulto,vdbultozonas *bzo)
{
  int vdret;
  memset(&svdbultozona,0,sizeof(svdbultozona));
  strcpy(svdbultozona.codbulto,codbulto);
  if (vdselbzocodbulto==NULL) init_selbzocodbulto();
  vdret=ejefetchcursor(vdselbzocodbulto);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbzocodbulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BZOnextcodbulto(vdbultozonas *bzo)
{
  int vdret;
  vdret=fetchcursor(vdselbzocodbulto);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbzocodbulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbzocodbulto);
  return(VD_EERRORACLE);
}

int BZObuscazonaope(long codzona,char *codope,vdbultozonas *bzo)
{
  int vdret;
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  strcpy(svdbultozona.codope,codope);
  if (vdselbzozonaope==NULL) init_selbzozonaope();
  vdret=ejefetchcursor(vdselbzozonaope);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbzozonaope. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BZOnextzonaope(vdbultozonas *bzo)
{
  int vdret;
  vdret=fetchcursor(vdselbzozonaope);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbzozonaope. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbzozonaope);
  return(VD_EERRORACLE);
}

int BZObuscafinbulto(long codzona,vdbultozonas *bzo)
{
  int vdret;
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  if (vdselbzofinbulto==NULL) init_selbzofinbulto();
  vdret=ejefetchcursor(vdselbzofinbulto);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbzofinbulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BZOnextfinbulto(vdbultozonas *bzo)
{
  int vdret;
  vdret=fetchcursor(vdselbzofinbulto);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbzofinbulto. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbzofinbulto);
  return(VD_EERRORACLE);
}

int BZObuscacodzona(long codzona,vdbultozonas *bzo)
{
  int vdret;
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  if (vdselbzocodzona==NULL) init_selbzocodzona();
  vdret=ejefetchcursor(vdselbzocodzona);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbzocodzona. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BZOnextcodzona(vdbultozonas *bzo)
{
  int vdret;
  vdret=fetchcursor(vdselbzocodzona);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbzocodzona. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbzocodzona);
  return(VD_EERRORACLE);
}

int BZObuscazonstat(long codzona,long status,vdbultozonas *bzo)
{
  int vdret;
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.codzona=codzona;
  svdbultozona.status=status;
  if (vdselbzozonstat==NULL) init_selbzozonstat();
  vdret=ejefetchcursor(vdselbzozonstat);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbzozonstat. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BZOnextzonstat(vdbultozonas *bzo)
{
  int vdret;
  vdret=fetchcursor(vdselbzozonstat);
  if (vdret==0) {
     *bzo=svdbultozona;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbzozonstat. vdret %d. \n",BZOlog(&svdbultozona),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbzozonstat);
  return(VD_EERRORACLE);
}

int BZOselvdbultozona(long seqbulto,vdbultozonas *bzo)
{
  int vdret;
  if (vdselbzovdbultozona==NULL) init_selbzovdbultozona();
  memset(&svdbultozona,0,sizeof(svdbultozona));
  svdbultozona.seqbulto=seqbulto;
  vdret=ejefetchcursor(vdselbzovdbultozona);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbzovdbultozona. vdret %d. \n",BZOlog(&svdbultozona),vdret);
    return(VD_EERRORACLE);
   }
  *bzo=svdbultozona;
  return(vdret);
}

int BZOactualizastatus(vdbultozonas *bzo,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BZOactualizastatus:  %s .  \n",BZOlog(&svdbultozona));
  if (vdupdabzostatus==NULL) init_updabzostatus();
  svdbultozona=*bzo;
  vdret=ejecutacursor(vdupdabzostatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabzostatus);
     getcurerrornombre(vdupdabzostatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabzostatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int BZOactualizacodope(vdbultozonas *bzo,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BZOactualizacodope:  %s .  \n",BZOlog(&svdbultozona));
  if (vdupdabzocodope==NULL) init_updabzocodope();
  svdbultozona=*bzo;
  vdret=ejecutacursor(vdupdabzocodope);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabzocodope);
     getcurerrornombre(vdupdabzocodope->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabzocodope)!=1) return(VD_EERRORACLE);
  return(0);
}

int BZOselvdsecbultozona(long *donde)
{
  int vdret;
  if (!vdselvdsecbultozona) init_selvdsecbultozona();
  vdret=ejefetchcursor(vdselvdsecbultozona);
  if (!vdret) {
     *donde=svdbultozona.seqbulto;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int BZOinsert(vdbultozonas *bzo,int error)
{
  int vdret;
  if (!vdinsbzo) init_insbzo();
  if (!bzo->seqbulto) {
     if ((vdret=BZOselvdsecbultozona(&(bzo->seqbulto)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",BZOlog(&svdbultozona));
  svdbultozona=*bzo;
  vdret=ejecutacursor(vdinsbzo);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsbzo);
     getcurerrornombre(vdinsbzo->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int BZOdel(vdbultozonas *bzo,int error)
{
  int vdret;
  svdbultozona=*bzo;
  if (vddelbzo==NULL) init_delbzo();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",BZOlog(&svdbultozona));
  vdret=ejecutacursor(vddelbzo);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelbzo);
     getcurerrornombre(vddelbzo->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * BZOlog(vdbultozonas *bzo)
{
    sprintf(msglogBZO, "VDBULTOZONA: seqbulto %ld ",bzo->seqbulto);
    return(msglogBZO);
}

char * BZOdebug(vdbultozonas *bzo)
{
    debugestruct(&dbzo,bzo,msgdebugBZO);
    return(msgdebugBZO);
}

