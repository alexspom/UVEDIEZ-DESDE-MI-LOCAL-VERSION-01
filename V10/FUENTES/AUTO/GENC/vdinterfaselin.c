// Modulo generado automaticamente a partir de VDINTERFASELIN.DEF
//#***
//# VDINTERFASELIN.c - Generaci�n autom�tica del c�digo c para la tabla de la descripci�n de interfases                                                  
//# 
//# Prop�sito: Funciones de acceso a la tabla VDINTERFASELIN
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 14-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=INTL
//
//PRIMARIA=TIPOINTERFASE,FORMATO,CAMPO,TABLA
//RECORRE=TIPOFORMATO,TIPOINTERFASE,FORMATO;ORDERBY=ORDEN;
//#RECORRE=SELPK, TIPOINTERFASE,FORMATO,PK;
//
//#RECORRE=CAMPOSPK, TIPOINTERFASE,FORMATO, SWTPK;ORDERBY=ORDEN;
//

#include "vd.h"
#define SELINTLTIPOFORMATO "SELECT VDINTERFASELIN.ROWID,VDINTERFASELIN.TIPOINTERFASE,VDINTERFASELIN.FORMATO, "\
                    " VDINTERFASELIN.ORDEN,VDINTERFASELIN.CAMPOHOST,VDINTERFASELIN.CAMPO, "\
                    " VDINTERFASELIN.DESCCAMPO,VDINTERFASELIN.TABLA,VDINTERFASELIN.SWTACTIVO, "\
                    " VDINTERFASELIN.SWTACTUALIZA,VDINTERFASELIN.ACCION,VDINTERFASELIN.LONGITUD, "\
                    " VDINTERFASELIN.TIPODATO,VDINTERFASELIN.DECIMALES,VDINTERFASELIN.FORMATEO, "\
                    " VDINTERFASELIN.DEFECTO,VDINTERFASELIN.FUNCION,VDINTERFASELIN.LIBRERIA, "\
                    " VDINTERFASELIN.VDEXTRA,VDINTERFASELIN.CODOPEMODIF,VDINTERFASELIN.FECMODIF, "\
                    " VDINTERFASELIN.HORAMODIF,VDINTERFASELIN.CODCOMEN,VDINTERFASELIN.PARAMETROS "\
        " FROM VDINTERFASELIN"\
        " WHERE "\
               " VDINTERFASELIN.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFASELIN.FORMATO=:FORMATO "\
        " ORDER BY ORDEN "
static v10cursors *vdselintltipoformato;

#define SELINTLVDINTERFASELIN "SELECT VDINTERFASELIN.ROWID,VDINTERFASELIN.TIPOINTERFASE,VDINTERFASELIN.FORMATO, "\
                    " VDINTERFASELIN.ORDEN,VDINTERFASELIN.CAMPOHOST,VDINTERFASELIN.CAMPO, "\
                    " VDINTERFASELIN.DESCCAMPO,VDINTERFASELIN.TABLA,VDINTERFASELIN.SWTACTIVO, "\
                    " VDINTERFASELIN.SWTACTUALIZA,VDINTERFASELIN.ACCION,VDINTERFASELIN.LONGITUD, "\
                    " VDINTERFASELIN.TIPODATO,VDINTERFASELIN.DECIMALES,VDINTERFASELIN.FORMATEO, "\
                    " VDINTERFASELIN.DEFECTO,VDINTERFASELIN.FUNCION,VDINTERFASELIN.LIBRERIA, "\
                    " VDINTERFASELIN.VDEXTRA,VDINTERFASELIN.CODOPEMODIF,VDINTERFASELIN.FECMODIF, "\
                    " VDINTERFASELIN.HORAMODIF,VDINTERFASELIN.CODCOMEN,VDINTERFASELIN.PARAMETROS "\
        " FROM VDINTERFASELIN"\
        " WHERE "\
               " VDINTERFASELIN.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFASELIN.FORMATO=:FORMATO "\
               " AND VDINTERFASELIN.CAMPO=:CAMPO "\
               " AND VDINTERFASELIN.TABLA=:TABLA "
static v10cursors *vdselintlvdinterfaselin;

static vdinterfaselins svdinterfaselin;

static diccols colvdinterfaselin[]={
	{"ROWID",V10CADENA,(size_t)&svdinterfaselin.rowid,sizeof(svdinterfaselin.rowid)},
	{"TIPOINTERFASE",V10CADENA,(size_t)&svdinterfaselin.tipointerfase,sizeof(svdinterfaselin.tipointerfase)},
	{"FORMATO",V10CADENA,(size_t)&svdinterfaselin.formato,sizeof(svdinterfaselin.formato)},
	{"ORDEN",V10LONG,(size_t)&svdinterfaselin.orden,sizeof(svdinterfaselin.orden)},
	{"CAMPOHOST",V10CADENA,(size_t)&svdinterfaselin.campohost,sizeof(svdinterfaselin.campohost)},
	{"CAMPO",V10CADENA,(size_t)&svdinterfaselin.campo,sizeof(svdinterfaselin.campo)},
	{"DESCCAMPO",V10CADENA,(size_t)&svdinterfaselin.desccampo,sizeof(svdinterfaselin.desccampo)},
	{"TABLA",V10CADENA,(size_t)&svdinterfaselin.tabla,sizeof(svdinterfaselin.tabla)},
	{"SWTACTIVO",V10CADENA,(size_t)&svdinterfaselin.swtactivo,sizeof(svdinterfaselin.swtactivo)},
	{"SWTACTUALIZA",V10CADENA,(size_t)&svdinterfaselin.swtactualiza,sizeof(svdinterfaselin.swtactualiza)},
	{"ACCION",V10CADENA,(size_t)&svdinterfaselin.accion,sizeof(svdinterfaselin.accion)},
	{"LONGITUD",V10LONG,(size_t)&svdinterfaselin.longitud,sizeof(svdinterfaselin.longitud)},
	{"TIPODATO",V10CADENA,(size_t)&svdinterfaselin.tipodato,sizeof(svdinterfaselin.tipodato)},
	{"DECIMALES",V10LONG,(size_t)&svdinterfaselin.decimales,sizeof(svdinterfaselin.decimales)},
	{"FORMATEO",V10CADENA,(size_t)&svdinterfaselin.formateo,sizeof(svdinterfaselin.formateo)},
	{"DEFECTO",V10CADENA,(size_t)&svdinterfaselin.defecto,sizeof(svdinterfaselin.defecto)},
	{"FUNCION",V10CADENA,(size_t)&svdinterfaselin.funcion,sizeof(svdinterfaselin.funcion)},
	{"LIBRERIA",V10CADENA,(size_t)&svdinterfaselin.libreria,sizeof(svdinterfaselin.libreria)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinterfaselin.vdextra,sizeof(svdinterfaselin.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinterfaselin.codopemodif,sizeof(svdinterfaselin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinterfaselin.fecmodif,sizeof(svdinterfaselin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinterfaselin.horamodif,sizeof(svdinterfaselin.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinterfaselin.codcomen,sizeof(svdinterfaselin.codcomen)},
	{"PARAMETROS",V10CADENA,(size_t)&svdinterfaselin.parametros,sizeof(svdinterfaselin.parametros)}
	};
static diccionarios dvdinterfaselin[]={
    {colvdinterfaselin,24}
};
diccionario dintl={dvdinterfaselin,1};

static char msglogINTL[LCADENA];
static char msgdebugINTL[LCADENABIG];
static int init=0;


static void fin_vd_intl(void)
{
if (vdselintltipoformato) {
    liberacursor(vdselintltipoformato);
    vdselintltipoformato = NULL;
}
if (vdselintlvdinterfaselin) {
    liberacursor(vdselintlvdinterfaselin);
    vdselintlvdinterfaselin = NULL;
}
}
static void init_selintltipoformato(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfaselin[0].numcol;nc++) dvdinterfaselin[0].c[nc].offset-=(size_t)&svdinterfaselin;
    vdselintltipoformato=abrecursordebug(SELINTLTIPOFORMATO,1280);
    definetodo(vdselintltipoformato,svdinterfaselin.rowid,sizeof(svdinterfaselin.rowid),V10CADENA,
                          svdinterfaselin.tipointerfase,sizeof(svdinterfaselin.tipointerfase),V10CADENA,
                          svdinterfaselin.formato,sizeof(svdinterfaselin.formato),V10CADENA,
                          &svdinterfaselin.orden,sizeof(svdinterfaselin.orden),V10LONG,
                          svdinterfaselin.campohost,sizeof(svdinterfaselin.campohost),V10CADENA,
                          svdinterfaselin.campo,sizeof(svdinterfaselin.campo),V10CADENA,
                          svdinterfaselin.desccampo,sizeof(svdinterfaselin.desccampo),V10CADENA,
                          svdinterfaselin.tabla,sizeof(svdinterfaselin.tabla),V10CADENA,
                          svdinterfaselin.swtactivo,sizeof(svdinterfaselin.swtactivo),V10CADENA,
                          svdinterfaselin.swtactualiza,sizeof(svdinterfaselin.swtactualiza),V10CADENA,
                          svdinterfaselin.accion,sizeof(svdinterfaselin.accion),V10CADENA,
                          &svdinterfaselin.longitud,sizeof(svdinterfaselin.longitud),V10LONG,
                          svdinterfaselin.tipodato,sizeof(svdinterfaselin.tipodato),V10CADENA,
                          &svdinterfaselin.decimales,sizeof(svdinterfaselin.decimales),V10LONG,
                          svdinterfaselin.formateo,sizeof(svdinterfaselin.formateo),V10CADENA,
                          svdinterfaselin.defecto,sizeof(svdinterfaselin.defecto),V10CADENA,
                          svdinterfaselin.funcion,sizeof(svdinterfaselin.funcion),V10CADENA,
                          svdinterfaselin.libreria,sizeof(svdinterfaselin.libreria),V10CADENA,
                          svdinterfaselin.vdextra,sizeof(svdinterfaselin.vdextra),V10CADENA,
                          svdinterfaselin.codopemodif,sizeof(svdinterfaselin.codopemodif),V10CADENA,
                          &svdinterfaselin.fecmodif,sizeof(svdinterfaselin.fecmodif),V10LONG,
                          svdinterfaselin.horamodif,sizeof(svdinterfaselin.horamodif),V10CADENA,
                          &svdinterfaselin.codcomen,sizeof(svdinterfaselin.codcomen),V10LONG,
                          svdinterfaselin.parametros,sizeof(svdinterfaselin.parametros),V10CADENA,
                          NULL);
    bindtodo(vdselintltipoformato,"TIPOINTERFASE",svdinterfaselin.tipointerfase,sizeof(svdinterfaselin.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfaselin.formato,sizeof(svdinterfaselin.formato),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intl);
        init = 1;
    }
}

static void init_selintlvdinterfaselin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfaselin[0].numcol;nc++) dvdinterfaselin[0].c[nc].offset-=(size_t)&svdinterfaselin;
    vdselintlvdinterfaselin=abrecursordebug(SELINTLVDINTERFASELIN,1280);
    definetodo(vdselintlvdinterfaselin,svdinterfaselin.rowid,sizeof(svdinterfaselin.rowid),V10CADENA,
                          svdinterfaselin.tipointerfase,sizeof(svdinterfaselin.tipointerfase),V10CADENA,
                          svdinterfaselin.formato,sizeof(svdinterfaselin.formato),V10CADENA,
                          &svdinterfaselin.orden,sizeof(svdinterfaselin.orden),V10LONG,
                          svdinterfaselin.campohost,sizeof(svdinterfaselin.campohost),V10CADENA,
                          svdinterfaselin.campo,sizeof(svdinterfaselin.campo),V10CADENA,
                          svdinterfaselin.desccampo,sizeof(svdinterfaselin.desccampo),V10CADENA,
                          svdinterfaselin.tabla,sizeof(svdinterfaselin.tabla),V10CADENA,
                          svdinterfaselin.swtactivo,sizeof(svdinterfaselin.swtactivo),V10CADENA,
                          svdinterfaselin.swtactualiza,sizeof(svdinterfaselin.swtactualiza),V10CADENA,
                          svdinterfaselin.accion,sizeof(svdinterfaselin.accion),V10CADENA,
                          &svdinterfaselin.longitud,sizeof(svdinterfaselin.longitud),V10LONG,
                          svdinterfaselin.tipodato,sizeof(svdinterfaselin.tipodato),V10CADENA,
                          &svdinterfaselin.decimales,sizeof(svdinterfaselin.decimales),V10LONG,
                          svdinterfaselin.formateo,sizeof(svdinterfaselin.formateo),V10CADENA,
                          svdinterfaselin.defecto,sizeof(svdinterfaselin.defecto),V10CADENA,
                          svdinterfaselin.funcion,sizeof(svdinterfaselin.funcion),V10CADENA,
                          svdinterfaselin.libreria,sizeof(svdinterfaselin.libreria),V10CADENA,
                          svdinterfaselin.vdextra,sizeof(svdinterfaselin.vdextra),V10CADENA,
                          svdinterfaselin.codopemodif,sizeof(svdinterfaselin.codopemodif),V10CADENA,
                          &svdinterfaselin.fecmodif,sizeof(svdinterfaselin.fecmodif),V10LONG,
                          svdinterfaselin.horamodif,sizeof(svdinterfaselin.horamodif),V10CADENA,
                          &svdinterfaselin.codcomen,sizeof(svdinterfaselin.codcomen),V10LONG,
                          svdinterfaselin.parametros,sizeof(svdinterfaselin.parametros),V10CADENA,
                          NULL);
    bindtodo(vdselintlvdinterfaselin,"TIPOINTERFASE",svdinterfaselin.tipointerfase,sizeof(svdinterfaselin.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfaselin.formato,sizeof(svdinterfaselin.formato),V10CADENA,
                          "CAMPO",svdinterfaselin.campo,sizeof(svdinterfaselin.campo),V10CADENA,
                          "TABLA",svdinterfaselin.tabla,sizeof(svdinterfaselin.tabla),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intl);
        init = 1;
    }
}

diccionario *INTLdamediccionario(void)
{
     return(&dintl);
}

int INTLbuscatipoformato(char *tipointerfase,char *formato,vdinterfaselins *intl)
{
  int vdret;
  memset(&svdinterfaselin,0,sizeof(svdinterfaselin));
  strcpy(svdinterfaselin.tipointerfase,tipointerfase);
  strcpy(svdinterfaselin.formato,formato);
  if (vdselintltipoformato==NULL) init_selintltipoformato();
  vdret=ejefetchcursor(vdselintltipoformato);
  if (vdret==0) {
     *intl=svdinterfaselin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselintltipoformato. vdret %d. \n",INTLlog(&svdinterfaselin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int INTLnexttipoformato(vdinterfaselins *intl)
{
  int vdret;
  vdret=fetchcursor(vdselintltipoformato);
  if (vdret==0) {
     *intl=svdinterfaselin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselintltipoformato. vdret %d. \n",INTLlog(&svdinterfaselin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselintltipoformato);
  return(VD_EERRORACLE);
}

int INTLselvdinterfaselin(char *tipointerfase,char *formato,char *campo,char *tabla,vdinterfaselins *intl)
{
  int vdret;
  if (vdselintlvdinterfaselin==NULL) init_selintlvdinterfaselin();
  memset(&svdinterfaselin,0,sizeof(svdinterfaselin));
  strcpy(svdinterfaselin.tipointerfase,tipointerfase);
  strcpy(svdinterfaselin.formato,formato);
  strcpy(svdinterfaselin.campo,campo);
  strcpy(svdinterfaselin.tabla,tabla);
  vdret=ejefetchcursor(vdselintlvdinterfaselin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselintlvdinterfaselin. vdret %d. \n",INTLlog(&svdinterfaselin),vdret);
    return(VD_EERRORACLE);
   }
  *intl=svdinterfaselin;
  return(vdret);
}

char * INTLlog(vdinterfaselins *intl)
{
    sprintf(msglogINTL, "VDINTERFASELIN: tipointerfase %s formato %s campo %s tabla %s ",intl->tipointerfase,intl->formato,intl->campo,intl->tabla);
    return(msglogINTL);
}

char * INTLdebug(vdinterfaselins *intl)
{
    debugestruct(&dintl,intl,msgdebugINTL);
    return(msgdebugINTL);
}

