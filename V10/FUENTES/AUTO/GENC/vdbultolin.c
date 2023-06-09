// Modulo generado automaticamente a partir de VDBULTOLIN.DEF
//#***
//# VDBULLIN.DEF - Generaci�n autom�tica del c�digo c para la tabla de L�nea de Bulto                                                       
//# 
//# Prop�sito: Funciones de acceso a la tabla VDBULLIN
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 3-03-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=BUL
//
//RECORRE=CODMOV,CODMOV;
//RECORRE=BULCODART,CODBULTO,CODART;
//RECORRE=BULCODARTCODLOT,CODBULTO,CODART,CODLOT;
//RECORRE=LINBULTO,CODBULTO;
//RECORRE=LINBULPDTE,CODBULTO;WHERE=STATUS=VDST.FBULASERVIR;
//
//UPDATE=CODMOV,CODMOV;
//UPDATE=CANTPEDIDA,CANTPEDIDA;
//
//INSERT 
//DELETE

#include "vd.h"
#define SELBULCODMOV "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODMOV=:CODMOV "
static v10cursors *vdselbulcodmov;

#define SELBULBULCODART "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODBULTO=:CODBULTO "\
               " AND VDBULTOLIN.CODART=:CODART "
static v10cursors *vdselbulbulcodart;

#define SELBULBULCODARTCODLOT "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODBULTO=:CODBULTO "\
               " AND VDBULTOLIN.CODART=:CODART "\
               " AND VDBULTOLIN.CODLOT=:CODLOT "
static v10cursors *vdselbulbulcodartcodlot;

#define SELBULLINBULTO "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODBULTO=:CODBULTO "
static v10cursors *vdselbullinbulto;

#define SELBULLINBULPDTE "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODBULTO=:CODBULTO "\
              "  AND STATUS=VDST.FBULASERVIR "
static v10cursors *vdselbullinbulpdte;

#define SELBULVDBULTOLIN "SELECT VDBULTOLIN.ROWID,VDBULTOLIN.CODBULTO,VDBULTOLIN.SEQLINEA, "\
                    " VDBULTOLIN.CODART,VDBULTOLIN.CODMOV,VDBULTOLIN.CODMOVEXP, "\
                    " VDBULTOLIN.CODLOT,VDBULTOLIN.CANTPEDIDA,VDBULTOLIN.CANTSERVIDA, "\
                    " VDBULTOLIN.NUMEROSERIE,VDBULTOLIN.BULTO,VDBULTOLIN.STATUS, "\
                    " VDBULTOLIN.CODOPEPREPARA,VDBULTOLIN.FECPREPARA,VDBULTOLIN.HORAPREPARA, "\
                    " VDBULTOLIN.VDEXTRA,VDBULTOLIN.CODCOMEN,VDBULTOLIN.CODOPEMODIF, "\
                    " VDBULTOLIN.FECMODIF,VDBULTOLIN.HORAMODIF "\
        " FROM VDBULTOLIN"\
        " WHERE "\
               " VDBULTOLIN.CODBULTO=:CODBULTO "\
               " AND VDBULTOLIN.SEQLINEA=:SEQLINEA "
static v10cursors *vdselbulvdbultolin;

#define UPDABULCODMOV "UPDATE VDBULTOLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODMOV=:CODMOV  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabulcodmov;

#define UPDABULCANTPEDIDA "UPDATE VDBULTOLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CANTPEDIDA=:CANTPEDIDA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabulcantpedida;

#define INSBUL "INSERT INTO VDBULTOLIN (CODBULTO,SEQLINEA,CODART,CODMOV,CODMOVEXP,CODLOT, "\
                    " CANTPEDIDA,CANTSERVIDA,NUMEROSERIE,BULTO,STATUS,CODOPEPREPARA,FECPREPARA, "\
                    " HORAPREPARA,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :CODBULTO,:SEQLINEA,:CODART,:CODMOV,:CODMOVEXP,:CODLOT, "\
                    " :CANTPEDIDA,:CANTSERVIDA,:NUMEROSERIE,:BULTO,:STATUS,:CODOPEPREPARA,:FECPREPARA, "\
                    " :HORAPREPARA,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS()) "
static v10cursors *vdinsbul;

#define DELBUL "DELETE VDBULTOLIN WHERE ROWID=:MIROWID "
static v10cursors *vddelbul;

static vdbultolins svdbultolin;

static diccols colvdbultolin[]={
	{"ROWID",V10CADENA,(size_t)&svdbultolin.rowid,sizeof(svdbultolin.rowid)},
	{"CODBULTO",V10CADENA,(size_t)&svdbultolin.codbulto,sizeof(svdbultolin.codbulto)},
	{"SEQLINEA",V10LONG,(size_t)&svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea)},
	{"CODART",V10CADENA,(size_t)&svdbultolin.codart,sizeof(svdbultolin.codart)},
	{"CODMOV",V10LONG,(size_t)&svdbultolin.codmov,sizeof(svdbultolin.codmov)},
	{"CODMOVEXP",V10LONG,(size_t)&svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp)},
	{"CODLOT",V10CADENA,(size_t)&svdbultolin.codlot,sizeof(svdbultolin.codlot)},
	{"CANTPEDIDA",V10DOUBLE,(size_t)&svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida)},
	{"CANTSERVIDA",V10DOUBLE,(size_t)&svdbultolin.cantservida,sizeof(svdbultolin.cantservida)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie)},
	{"BULTO",V10CADENA,(size_t)&svdbultolin.bulto,sizeof(svdbultolin.bulto)},
	{"STATUS",V10LONG,(size_t)&svdbultolin.status,sizeof(svdbultolin.status)},
	{"CODOPEPREPARA",V10CADENA,(size_t)&svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara)},
	{"FECPREPARA",V10LONG,(size_t)&svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara)},
	{"HORAPREPARA",V10CADENA,(size_t)&svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara)},
	{"VDEXTRA",V10CADENA,(size_t)&svdbultolin.vdextra,sizeof(svdbultolin.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdbultolin.codcomen,sizeof(svdbultolin.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdbultolin.horamodif,sizeof(svdbultolin.horamodif)}
	};
static diccionarios dvdbultolin[]={
    {colvdbultolin,20}
};
diccionario dbul={dvdbultolin,1};

static char msglogBUL[LCADENA];
static char msgdebugBUL[LCADENABIG];
static int init=0;


static void fin_vd_bul(void)
{
if (vdselbulcodmov) {
    liberacursor(vdselbulcodmov);
    vdselbulcodmov = NULL;
}
if (vdselbulbulcodart) {
    liberacursor(vdselbulbulcodart);
    vdselbulbulcodart = NULL;
}
if (vdselbulbulcodartcodlot) {
    liberacursor(vdselbulbulcodartcodlot);
    vdselbulbulcodartcodlot = NULL;
}
if (vdselbullinbulto) {
    liberacursor(vdselbullinbulto);
    vdselbullinbulto = NULL;
}
if (vdselbullinbulpdte) {
    liberacursor(vdselbullinbulpdte);
    vdselbullinbulpdte = NULL;
}
if (vdselbulvdbultolin) {
    liberacursor(vdselbulvdbultolin);
    vdselbulvdbultolin = NULL;
}
if (vdupdabulcodmov) {
    liberacursor(vdupdabulcodmov);
    vdupdabulcodmov = NULL;
}
if (vdupdabulcantpedida) {
    liberacursor(vdupdabulcantpedida);
    vdupdabulcantpedida = NULL;
}
if (vdinsbul != NULL) {
    liberacursor(vdinsbul);
    vdinsbul = NULL;
}
if (vddelbul != NULL) {
    liberacursor(vddelbul);
    vddelbul = NULL;
}
}
static void init_selbulcodmov(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbulcodmov=abrecursordebug(SELBULCODMOV,1280);
    definetodo(vdselbulcodmov,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbulcodmov,"CODMOV",&svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_selbulbulcodart(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbulbulcodart=abrecursordebug(SELBULBULCODART,1280);
    definetodo(vdselbulbulcodart,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbulbulcodart,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          "CODART",svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_selbulbulcodartcodlot(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbulbulcodartcodlot=abrecursordebug(SELBULBULCODARTCODLOT,1280);
    definetodo(vdselbulbulcodartcodlot,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbulbulcodartcodlot,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          "CODART",svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          "CODLOT",svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_selbullinbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbullinbulto=abrecursordebug(SELBULLINBULTO,1280);
    definetodo(vdselbullinbulto,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbullinbulto,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_selbullinbulpdte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbullinbulpdte=abrecursordebug(SELBULLINBULPDTE,1280);
    definetodo(vdselbullinbulpdte,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbullinbulpdte,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_selbulvdbultolin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdselbulvdbultolin=abrecursordebug(SELBULVDBULTOLIN,1280);
    definetodo(vdselbulvdbultolin,svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          &svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          &svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          &svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          &svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          &svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          &svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          &svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          &svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          svdbultolin.codopemodif,sizeof(svdbultolin.codopemodif),V10CADENA,
                          &svdbultolin.fecmodif,sizeof(svdbultolin.fecmodif),V10LONG,
                          svdbultolin.horamodif,sizeof(svdbultolin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselbulvdbultolin,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          "SEQLINEA",&svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_updabulcodmov(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdupdabulcodmov=abrecursordebug(UPDABULCODMOV,1280);
    bindtodo(vdupdabulcodmov,"CODMOV",&svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          "MIROWID",svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_updabulcantpedida(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdupdabulcantpedida=abrecursordebug(UPDABULCANTPEDIDA,1280);
    bindtodo(vdupdabulcantpedida,"CANTPEDIDA",&svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          "MIROWID",svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_insbul(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vdinsbul=abrecursordebug(INSBUL,1280);
    bindtodo(vdinsbul,"CODBULTO",svdbultolin.codbulto,sizeof(svdbultolin.codbulto),V10CADENA,
                          "SEQLINEA",&svdbultolin.seqlinea,sizeof(svdbultolin.seqlinea),V10LONG,
                          "CODART",svdbultolin.codart,sizeof(svdbultolin.codart),V10CADENA,
                          "CODMOV",&svdbultolin.codmov,sizeof(svdbultolin.codmov),V10LONG,
                          "CODMOVEXP",&svdbultolin.codmovexp,sizeof(svdbultolin.codmovexp),V10LONG,
                          "CODLOT",svdbultolin.codlot,sizeof(svdbultolin.codlot),V10CADENA,
                          "CANTPEDIDA",&svdbultolin.cantpedida,sizeof(svdbultolin.cantpedida),V10DOUBLE,
                          "CANTSERVIDA",&svdbultolin.cantservida,sizeof(svdbultolin.cantservida),V10DOUBLE,
                          "NUMEROSERIE",svdbultolin.numeroserie,sizeof(svdbultolin.numeroserie),V10CADENA,
                          "BULTO",svdbultolin.bulto,sizeof(svdbultolin.bulto),V10CADENA,
                          "STATUS",&svdbultolin.status,sizeof(svdbultolin.status),V10LONG,
                          "CODOPEPREPARA",svdbultolin.codopeprepara,sizeof(svdbultolin.codopeprepara),V10CADENA,
                          "FECPREPARA",&svdbultolin.fecprepara,sizeof(svdbultolin.fecprepara),V10LONG,
                          "HORAPREPARA",svdbultolin.horaprepara,sizeof(svdbultolin.horaprepara),V10CADENA,
                          "VDEXTRA",svdbultolin.vdextra,sizeof(svdbultolin.vdextra),V10CADENA,
                          "CODCOMEN",&svdbultolin.codcomen,sizeof(svdbultolin.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

static void init_delbul(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultolin[0].numcol;nc++) dvdbultolin[0].c[nc].offset-=(size_t)&svdbultolin;
    vddelbul=abrecursordebug(DELBUL,1280);
    bindtodo(vddelbul,"MIROWID",svdbultolin.rowid,sizeof(svdbultolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bul);
        init = 1;
    }
}

diccionario *BULdamediccionario(void)
{
     return(&dbul);
}

int BULbuscacodmov(long codmov,vdbultolins *bul)
{
  int vdret;
  memset(&svdbultolin,0,sizeof(svdbultolin));
  svdbultolin.codmov=codmov;
  if (vdselbulcodmov==NULL) init_selbulcodmov();
  vdret=ejefetchcursor(vdselbulcodmov);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbulcodmov. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BULnextcodmov(vdbultolins *bul)
{
  int vdret;
  vdret=fetchcursor(vdselbulcodmov);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbulcodmov. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbulcodmov);
  return(VD_EERRORACLE);
}

int BULbuscabulcodart(char *codbulto,char *codart,vdbultolins *bul)
{
  int vdret;
  memset(&svdbultolin,0,sizeof(svdbultolin));
  strcpy(svdbultolin.codbulto,codbulto);
  strcpy(svdbultolin.codart,codart);
  if (vdselbulbulcodart==NULL) init_selbulbulcodart();
  vdret=ejefetchcursor(vdselbulbulcodart);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbulbulcodart. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BULnextbulcodart(vdbultolins *bul)
{
  int vdret;
  vdret=fetchcursor(vdselbulbulcodart);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbulbulcodart. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbulbulcodart);
  return(VD_EERRORACLE);
}

int BULbuscabulcodartcodlot(char *codbulto,char *codart,char *codlot,vdbultolins *bul)
{
  int vdret;
  memset(&svdbultolin,0,sizeof(svdbultolin));
  strcpy(svdbultolin.codbulto,codbulto);
  strcpy(svdbultolin.codart,codart);
  strcpy(svdbultolin.codlot,codlot);
  if (vdselbulbulcodartcodlot==NULL) init_selbulbulcodartcodlot();
  vdret=ejefetchcursor(vdselbulbulcodartcodlot);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbulbulcodartcodlot. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BULnextbulcodartcodlot(vdbultolins *bul)
{
  int vdret;
  vdret=fetchcursor(vdselbulbulcodartcodlot);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbulbulcodartcodlot. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbulbulcodartcodlot);
  return(VD_EERRORACLE);
}

int BULbuscalinbulto(char *codbulto,vdbultolins *bul)
{
  int vdret;
  memset(&svdbultolin,0,sizeof(svdbultolin));
  strcpy(svdbultolin.codbulto,codbulto);
  if (vdselbullinbulto==NULL) init_selbullinbulto();
  vdret=ejefetchcursor(vdselbullinbulto);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbullinbulto. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BULnextlinbulto(vdbultolins *bul)
{
  int vdret;
  vdret=fetchcursor(vdselbullinbulto);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbullinbulto. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbullinbulto);
  return(VD_EERRORACLE);
}

int BULbuscalinbulpdte(char *codbulto,vdbultolins *bul)
{
  int vdret;
  memset(&svdbultolin,0,sizeof(svdbultolin));
  strcpy(svdbultolin.codbulto,codbulto);
  if (vdselbullinbulpdte==NULL) init_selbullinbulpdte();
  vdret=ejefetchcursor(vdselbullinbulpdte);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbullinbulpdte. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BULnextlinbulpdte(vdbultolins *bul)
{
  int vdret;
  vdret=fetchcursor(vdselbullinbulpdte);
  if (vdret==0) {
     *bul=svdbultolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbullinbulpdte. vdret %d. \n",BULlog(&svdbultolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbullinbulpdte);
  return(VD_EERRORACLE);
}

int BULselvdbultolin(char *codbulto,long seqlinea,vdbultolins *bul)
{
  int vdret;
  if (vdselbulvdbultolin==NULL) init_selbulvdbultolin();
  memset(&svdbultolin,0,sizeof(svdbultolin));
  strcpy(svdbultolin.codbulto,codbulto);
  svdbultolin.seqlinea=seqlinea;
  vdret=ejefetchcursor(vdselbulvdbultolin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbulvdbultolin. vdret %d. \n",BULlog(&svdbultolin),vdret);
    return(VD_EERRORACLE);
   }
  *bul=svdbultolin;
  return(vdret);
}

int BULactualizacodmov(vdbultolins *bul,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BULactualizacodmov:  %s .  \n",BULlog(&svdbultolin));
  if (vdupdabulcodmov==NULL) init_updabulcodmov();
  svdbultolin=*bul;
  vdret=ejecutacursor(vdupdabulcodmov);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabulcodmov);
     getcurerrornombre(vdupdabulcodmov->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabulcodmov)!=1) return(VD_EERRORACLE);
  return(0);
}

int BULactualizacantpedida(vdbultolins *bul,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BULactualizacantpedida:  %s .  \n",BULlog(&svdbultolin));
  if (vdupdabulcantpedida==NULL) init_updabulcantpedida();
  svdbultolin=*bul;
  vdret=ejecutacursor(vdupdabulcantpedida);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabulcantpedida);
     getcurerrornombre(vdupdabulcantpedida->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabulcantpedida)!=1) return(VD_EERRORACLE);
  return(0);
}

int BULinsert(vdbultolins *bul,int error)
{
  int vdret;
  if (!vdinsbul) init_insbul();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",BULlog(&svdbultolin));
  svdbultolin=*bul;
  vdret=ejecutacursor(vdinsbul);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsbul);
     getcurerrornombre(vdinsbul->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int BULdel(vdbultolins *bul,int error)
{
  int vdret;
  svdbultolin=*bul;
  if (vddelbul==NULL) init_delbul();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",BULlog(&svdbultolin));
  vdret=ejecutacursor(vddelbul);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelbul);
     getcurerrornombre(vddelbul->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * BULlog(vdbultolins *bul)
{
    sprintf(msglogBUL, "VDBULTOLIN: codbulto %s seqlinea %ld ",bul->codbulto,bul->seqlinea);
    return(msglogBUL);
}

char * BULdebug(vdbultolins *bul)
{
    debugestruct(&dbul,bul,msgdebugBUL);
    return(msgdebugBUL);
}

