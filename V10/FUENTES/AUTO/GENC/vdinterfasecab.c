// Modulo generado automaticamente a partir de VDINTERFASECAB.DEF
//#***
//# VDINTERFASECAB.c - Generaci�n autom�tica del c�digo c para la tabla de interfases                                                  
//# 
//# Prop�sito: Funciones de acceso a la tabla VDINTERFASECAB
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 14-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=INTC
//
//EXTRA=REG,V10CADENA,2048
//
//CLAVE=HIJO,TIPOINTERFASE,FORMATOPADRE
//
//CLAVE=SELFORMATO,TIPOINTERFASE, WHERE=(LONGFORMATO = 0
//                                   OR (LONGFORMATO > 0 AND SUBSTR(:REG,1,LONGFORMATO) = FORMATO));               
//
//RECORRE=TIPOFICHERO,TIPOFICHERO
//
//RECORRE=TIPOINTERFASE, TIPOINTERFASE;ORDERBY=ORDEN;
//
//RECORRE=RAIZ,ORDERBY=ORDEN;
//
//UPDATE=SECUENCIAL,SECUENCIAL
//

#include "vd.h"
#define SELINTCHIJO "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " WHERE "\
               " VDINTERFASECAB.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFASECAB.FORMATOPADRE=:FORMATOPADRE "
static v10cursors *vdselintchijo;

#define SELINTCSELFORMATO "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " WHERE "\
               " VDINTERFASECAB.TIPOINTERFASE=:TIPOINTERFASE "\
              "  AND (LONGFORMATO = 0 OR (LONGFORMATO > 0 AND SUBSTR(:REG,1,LONGFORMATO) = FORMATO)) "
static v10cursors *vdselintcselformato;

#define SELINTCTIPOFICHERO "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " WHERE "\
               " VDINTERFASECAB.TIPOFICHERO=:TIPOFICHERO "
static v10cursors *vdselintctipofichero;

#define SELINTCTIPOINTERFASE "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " WHERE "\
               " VDINTERFASECAB.TIPOINTERFASE=:TIPOINTERFASE "\
        " ORDER BY ORDEN "
static v10cursors *vdselintctipointerfase;

#define SELINTCRAIZ "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " ORDER BY ORDEN "
static v10cursors *vdselintcraiz;

#define SELINTCVDINTERFASECAB "SELECT VDINTERFASECAB.ROWID,VDINTERFASECAB.TIPOINTERFASE,VDINTERFASECAB.FORMATO, "\
                    " VDINTERFASECAB.FORMATOPADRE,VDINTERFASECAB.ORDEN,VDINTERFASECAB.NREGISTROS, "\
                    " VDINTERFASECAB.SWTACTUALIZA,VDINTERFASECAB.PREFFICHERO,VDINTERFASECAB.TIPOFICHERO, "\
                    " VDINTERFASECAB.SECUENCIAL,VDINTERFASECAB.SEPARADOR,VDINTERFASECAB.SWTLONGFIJA, "\
                    " VDINTERFASECAB.LONGFORMATO,VDINTERFASECAB.FUNCION,VDINTERFASECAB.LIBRERIA, "\
                    " VDINTERFASECAB.FORMATOFICH,VDINTERFASECAB.EXTFICHERO,VDINTERFASECAB.VDEXTRA, "\
                    " VDINTERFASECAB.CODOPEMODIF,VDINTERFASECAB.FECMODIF,VDINTERFASECAB.HORAMODIF, "\
                    " VDINTERFASECAB.CODCOMEN,VDINTERFASECAB.FORMATONUM "\
        " FROM VDINTERFASECAB"\
        " WHERE "\
               " VDINTERFASECAB.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFASECAB.FORMATO=:FORMATO "
static v10cursors *vdselintcvdinterfasecab;

#define UPDAINTCSECUENCIAL "UPDATE VDINTERFASECAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " SECUENCIAL=:SECUENCIAL  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaintcsecuencial;

static vdinterfasecabs svdinterfasecab;

static diccols colvdinterfasecab[]={
	{"ROWID",V10CADENA,(size_t)&svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid)},
	{"TIPOINTERFASE",V10CADENA,(size_t)&svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase)},
	{"FORMATO",V10CADENA,(size_t)&svdinterfasecab.formato,sizeof(svdinterfasecab.formato)},
	{"FORMATOPADRE",V10CADENA,(size_t)&svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre)},
	{"ORDEN",V10LONG,(size_t)&svdinterfasecab.orden,sizeof(svdinterfasecab.orden)},
	{"NREGISTROS",V10LONG,(size_t)&svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros)},
	{"SWTACTUALIZA",V10CADENA,(size_t)&svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza)},
	{"PREFFICHERO",V10CADENA,(size_t)&svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero)},
	{"TIPOFICHERO",V10CADENA,(size_t)&svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero)},
	{"SECUENCIAL",V10LONG,(size_t)&svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial)},
	{"SEPARADOR",V10CADENA,(size_t)&svdinterfasecab.separador,sizeof(svdinterfasecab.separador)},
	{"SWTLONGFIJA",V10CADENA,(size_t)&svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija)},
	{"LONGFORMATO",V10LONG,(size_t)&svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato)},
	{"FUNCION",V10CADENA,(size_t)&svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion)},
	{"LIBRERIA",V10CADENA,(size_t)&svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria)},
	{"FORMATOFICH",V10CADENA,(size_t)&svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich)},
	{"EXTFICHERO",V10CADENA,(size_t)&svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen)},
	{"FORMATONUM",V10CADENA,(size_t)&svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum)},
	{"REG",V10CADENA,(size_t)&svdinterfasecab.reg,sizeof(svdinterfasecab.reg)}
	};
static diccionarios dvdinterfasecab[]={
    {colvdinterfasecab,24}
};
diccionario dintc={dvdinterfasecab,1};

static char msglogINTC[LCADENA];
static char msgdebugINTC[LCADENABIG];
static int init=0;


static void fin_vd_intc(void)
{
if (vdselintchijo) {
    liberacursor(vdselintchijo);
    vdselintchijo = NULL;
}
if (vdselintcselformato) {
    liberacursor(vdselintcselformato);
    vdselintcselformato = NULL;
}
if (vdselintctipofichero) {
    liberacursor(vdselintctipofichero);
    vdselintctipofichero = NULL;
}
if (vdselintctipointerfase) {
    liberacursor(vdselintctipointerfase);
    vdselintctipointerfase = NULL;
}
if (vdselintcraiz) {
    liberacursor(vdselintcraiz);
    vdselintcraiz = NULL;
}
if (vdselintcvdinterfasecab) {
    liberacursor(vdselintcvdinterfasecab);
    vdselintcvdinterfasecab = NULL;
}
if (vdupdaintcsecuencial) {
    liberacursor(vdupdaintcsecuencial);
    vdupdaintcsecuencial = NULL;
}
}
static void init_selintchijo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintchijo=abrecursordebug(SELINTCHIJO,1280);
    definetodo(vdselintchijo,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintchijo,"TIPOINTERFASE",svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          "FORMATOPADRE",svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_selintcselformato(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintcselformato=abrecursordebug(SELINTCSELFORMATO,1280);
    definetodo(vdselintcselformato,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintcselformato,"TIPOINTERFASE",svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          "REG",svdinterfasecab.reg,sizeof(svdinterfasecab.reg),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_selintctipofichero(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintctipofichero=abrecursordebug(SELINTCTIPOFICHERO,1280);
    definetodo(vdselintctipofichero,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintctipofichero,"TIPOFICHERO",svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_selintctipointerfase(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintctipointerfase=abrecursordebug(SELINTCTIPOINTERFASE,1280);
    definetodo(vdselintctipointerfase,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintctipointerfase,"TIPOINTERFASE",svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_selintcraiz(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintcraiz=abrecursordebug(SELINTCRAIZ,1280);
    definetodo(vdselintcraiz,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintcraiz,NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_selintcvdinterfasecab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdselintcvdinterfasecab=abrecursordebug(SELINTCVDINTERFASECAB,1280);
    definetodo(vdselintcvdinterfasecab,svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          svdinterfasecab.formatopadre,sizeof(svdinterfasecab.formatopadre),V10CADENA,
                          &svdinterfasecab.orden,sizeof(svdinterfasecab.orden),V10LONG,
                          &svdinterfasecab.nregistros,sizeof(svdinterfasecab.nregistros),V10LONG,
                          svdinterfasecab.swtactualiza,sizeof(svdinterfasecab.swtactualiza),V10CADENA,
                          svdinterfasecab.preffichero,sizeof(svdinterfasecab.preffichero),V10CADENA,
                          svdinterfasecab.tipofichero,sizeof(svdinterfasecab.tipofichero),V10CADENA,
                          &svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          svdinterfasecab.separador,sizeof(svdinterfasecab.separador),V10CADENA,
                          svdinterfasecab.swtlongfija,sizeof(svdinterfasecab.swtlongfija),V10CADENA,
                          &svdinterfasecab.longformato,sizeof(svdinterfasecab.longformato),V10LONG,
                          svdinterfasecab.funcion,sizeof(svdinterfasecab.funcion),V10CADENA,
                          svdinterfasecab.libreria,sizeof(svdinterfasecab.libreria),V10CADENA,
                          svdinterfasecab.formatofich,sizeof(svdinterfasecab.formatofich),V10CADENA,
                          svdinterfasecab.extfichero,sizeof(svdinterfasecab.extfichero),V10CADENA,
                          svdinterfasecab.vdextra,sizeof(svdinterfasecab.vdextra),V10CADENA,
                          svdinterfasecab.codopemodif,sizeof(svdinterfasecab.codopemodif),V10CADENA,
                          &svdinterfasecab.fecmodif,sizeof(svdinterfasecab.fecmodif),V10LONG,
                          svdinterfasecab.horamodif,sizeof(svdinterfasecab.horamodif),V10CADENA,
                          &svdinterfasecab.codcomen,sizeof(svdinterfasecab.codcomen),V10LONG,
                          svdinterfasecab.formatonum,sizeof(svdinterfasecab.formatonum),V10CADENA,
                          NULL);
    bindtodo(vdselintcvdinterfasecab,"TIPOINTERFASE",svdinterfasecab.tipointerfase,sizeof(svdinterfasecab.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfasecab.formato,sizeof(svdinterfasecab.formato),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

static void init_updaintcsecuencial(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasecab[0].numcol;nc++) dvdinterfasecab[0].c[nc].offset-=(size_t)&svdinterfasecab;
    vdupdaintcsecuencial=abrecursordebug(UPDAINTCSECUENCIAL,1280);
    bindtodo(vdupdaintcsecuencial,"SECUENCIAL",&svdinterfasecab.secuencial,sizeof(svdinterfasecab.secuencial),V10LONG,
                          "MIROWID",svdinterfasecab.rowid,sizeof(svdinterfasecab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intc);
        init = 1;
    }
}

diccionario *INTCdamediccionario(void)
{
     return(&dintc);
}

int INTCselhijo(char *tipointerfase,char *formatopadre,vdinterfasecabs *intc)
{
  int vdret;
  if (vdselintchijo==NULL) init_selintchijo();
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  strcpy(svdinterfasecab.tipointerfase,tipointerfase);
  strcpy(svdinterfasecab.formatopadre,formatopadre);
  vdret=ejefetchcursor(vdselintchijo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselintchijo. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
    return(VD_EERRORACLE);
   }
  *intc=svdinterfasecab;
  return(vdret);
}

int INTCselselformato(char *tipointerfase,char *reg,vdinterfasecabs *intc)
{
  int vdret;
  if (vdselintcselformato==NULL) init_selintcselformato();
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  strcpy(svdinterfasecab.tipointerfase,tipointerfase);
  strcpy(svdinterfasecab.reg,reg);
  vdret=ejefetchcursor(vdselintcselformato);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselintcselformato. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
    return(VD_EERRORACLE);
   }
  *intc=svdinterfasecab;
  return(vdret);
}

int INTCbuscatipofichero(char *tipofichero,vdinterfasecabs *intc)
{
  int vdret;
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  strcpy(svdinterfasecab.tipofichero,tipofichero);
  if (vdselintctipofichero==NULL) init_selintctipofichero();
  vdret=ejefetchcursor(vdselintctipofichero);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselintctipofichero. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int INTCnexttipofichero(vdinterfasecabs *intc)
{
  int vdret;
  vdret=fetchcursor(vdselintctipofichero);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselintctipofichero. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselintctipofichero);
  return(VD_EERRORACLE);
}

int INTCbuscatipointerfase(char *tipointerfase,vdinterfasecabs *intc)
{
  int vdret;
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  strcpy(svdinterfasecab.tipointerfase,tipointerfase);
  if (vdselintctipointerfase==NULL) init_selintctipointerfase();
  vdret=ejefetchcursor(vdselintctipointerfase);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselintctipointerfase. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int INTCnexttipointerfase(vdinterfasecabs *intc)
{
  int vdret;
  vdret=fetchcursor(vdselintctipointerfase);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselintctipointerfase. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselintctipointerfase);
  return(VD_EERRORACLE);
}

int INTCbuscaraiz(vdinterfasecabs *intc)
{
  int vdret;
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  if (vdselintcraiz==NULL) init_selintcraiz();
  vdret=ejefetchcursor(vdselintcraiz);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselintcraiz. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int INTCnextraiz(vdinterfasecabs *intc)
{
  int vdret;
  vdret=fetchcursor(vdselintcraiz);
  if (vdret==0) {
     *intc=svdinterfasecab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselintcraiz. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselintcraiz);
  return(VD_EERRORACLE);
}

int INTCselvdinterfasecab(char *tipointerfase,char *formato,vdinterfasecabs *intc)
{
  int vdret;
  if (vdselintcvdinterfasecab==NULL) init_selintcvdinterfasecab();
  memset(&svdinterfasecab,0,sizeof(svdinterfasecab));
  strcpy(svdinterfasecab.tipointerfase,tipointerfase);
  strcpy(svdinterfasecab.formato,formato);
  vdret=ejefetchcursor(vdselintcvdinterfasecab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselintcvdinterfasecab. vdret %d. \n",INTClog(&svdinterfasecab),vdret);
    return(VD_EERRORACLE);
   }
  *intc=svdinterfasecab;
  return(vdret);
}

int INTCactualizasecuencial(vdinterfasecabs *intc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando INTCactualizasecuencial:  %s .  \n",INTClog(&svdinterfasecab));
  if (vdupdaintcsecuencial==NULL) init_updaintcsecuencial();
  svdinterfasecab=*intc;
  vdret=ejecutacursor(vdupdaintcsecuencial);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaintcsecuencial);
     getcurerrornombre(vdupdaintcsecuencial->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaintcsecuencial)!=1) return(VD_EERRORACLE);
  return(0);
}

char * INTClog(vdinterfasecabs *intc)
{
    sprintf(msglogINTC, "VDINTERFASECAB: tipointerfase %s formato %s ",intc->tipointerfase,intc->formato);
    return(msglogINTC);
}

char * INTCdebug(vdinterfasecabs *intc)
{
    debugestruct(&dintc,intc,msgdebugINTC);
    return(msgdebugINTC);
}

