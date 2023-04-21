// Modulo generado automaticamente a partir de VDINTERFASETAB.DEF
//#***
//# VDINTERFASETAB.c - Generación automática del código c para las tablas a mantener en las interfases                                                 
//# 
//# Propósito: Funciones de acceso a la tabla VDINTERFASETAB
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 04-08-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=INTT
//
//RECORRE=TODO;ORDERBY=ORDENINSUPD;
//
//

#include "vd.h"
#define SELINTTTODO "SELECT VDINTERFASETAB.ROWID,VDINTERFASETAB.TABLA,VDINTERFASETAB.TABLAALIAS, "\
                    " VDINTERFASETAB.ABREVIATURA,VDINTERFASETAB.ORDENINSUPD,VDINTERFASETAB.VDEXTRA, "\
                    " VDINTERFASETAB.CODOPEMODIF,VDINTERFASETAB.FECMODIF,VDINTERFASETAB.HORAMODIF, "\
                    " VDINTERFASETAB.LIBRERIA,VDINTERFASETAB.CODCOMEN "\
        " FROM VDINTERFASETAB"\
        " ORDER BY ORDENINSUPD "
static v10cursors *vdselintttodo;

#define SELINTTVDINTERFASETAB "SELECT VDINTERFASETAB.ROWID,VDINTERFASETAB.TABLA,VDINTERFASETAB.TABLAALIAS, "\
                    " VDINTERFASETAB.ABREVIATURA,VDINTERFASETAB.ORDENINSUPD,VDINTERFASETAB.VDEXTRA, "\
                    " VDINTERFASETAB.CODOPEMODIF,VDINTERFASETAB.FECMODIF,VDINTERFASETAB.HORAMODIF, "\
                    " VDINTERFASETAB.LIBRERIA,VDINTERFASETAB.CODCOMEN "\
        " FROM VDINTERFASETAB"\
        " WHERE "\
               " VDINTERFASETAB.TABLA=:TABLA "\
               " AND VDINTERFASETAB.TABLAALIAS=:TABLAALIAS "
static v10cursors *vdselinttvdinterfasetab;

static vdinterfasetabs svdinterfasetab;

static diccols colvdinterfasetab[]={
	{"ROWID",V10CADENA,(size_t)&svdinterfasetab.rowid,sizeof(svdinterfasetab.rowid)},
	{"TABLA",V10CADENA,(size_t)&svdinterfasetab.tabla,sizeof(svdinterfasetab.tabla)},
	{"TABLAALIAS",V10CADENA,(size_t)&svdinterfasetab.tablaalias,sizeof(svdinterfasetab.tablaalias)},
	{"ABREVIATURA",V10CADENA,(size_t)&svdinterfasetab.abreviatura,sizeof(svdinterfasetab.abreviatura)},
	{"ORDENINSUPD",V10LONG,(size_t)&svdinterfasetab.ordeninsupd,sizeof(svdinterfasetab.ordeninsupd)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinterfasetab.vdextra,sizeof(svdinterfasetab.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinterfasetab.codopemodif,sizeof(svdinterfasetab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinterfasetab.fecmodif,sizeof(svdinterfasetab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinterfasetab.horamodif,sizeof(svdinterfasetab.horamodif)},
	{"LIBRERIA",V10CADENA,(size_t)&svdinterfasetab.libreria,sizeof(svdinterfasetab.libreria)},
	{"CODCOMEN",V10LONG,(size_t)&svdinterfasetab.codcomen,sizeof(svdinterfasetab.codcomen)}
	};
static diccionarios dvdinterfasetab[]={
    {colvdinterfasetab,11}
};
diccionario dintt={dvdinterfasetab,1};

static char msglogINTT[LCADENA];
static char msgdebugINTT[LCADENABIG];
static int init=0;


static void fin_vd_intt(void)
{
if (vdselintttodo) {
    liberacursor(vdselintttodo);
    vdselintttodo = NULL;
}
if (vdselinttvdinterfasetab) {
    liberacursor(vdselinttvdinterfasetab);
    vdselinttvdinterfasetab = NULL;
}
}
static void init_selintttodo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasetab[0].numcol;nc++) dvdinterfasetab[0].c[nc].offset-=(size_t)&svdinterfasetab;
    vdselintttodo=abrecursordebug(SELINTTTODO,1280);
    definetodo(vdselintttodo,svdinterfasetab.rowid,sizeof(svdinterfasetab.rowid),V10CADENA,
                          svdinterfasetab.tabla,sizeof(svdinterfasetab.tabla),V10CADENA,
                          svdinterfasetab.tablaalias,sizeof(svdinterfasetab.tablaalias),V10CADENA,
                          svdinterfasetab.abreviatura,sizeof(svdinterfasetab.abreviatura),V10CADENA,
                          &svdinterfasetab.ordeninsupd,sizeof(svdinterfasetab.ordeninsupd),V10LONG,
                          svdinterfasetab.vdextra,sizeof(svdinterfasetab.vdextra),V10CADENA,
                          svdinterfasetab.codopemodif,sizeof(svdinterfasetab.codopemodif),V10CADENA,
                          &svdinterfasetab.fecmodif,sizeof(svdinterfasetab.fecmodif),V10LONG,
                          svdinterfasetab.horamodif,sizeof(svdinterfasetab.horamodif),V10CADENA,
                          svdinterfasetab.libreria,sizeof(svdinterfasetab.libreria),V10CADENA,
                          &svdinterfasetab.codcomen,sizeof(svdinterfasetab.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselintttodo,NULL);
    if (init == 0) {
        atexit(fin_vd_intt);
        init = 1;
    }
}

static void init_selinttvdinterfasetab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfasetab[0].numcol;nc++) dvdinterfasetab[0].c[nc].offset-=(size_t)&svdinterfasetab;
    vdselinttvdinterfasetab=abrecursordebug(SELINTTVDINTERFASETAB,1280);
    definetodo(vdselinttvdinterfasetab,svdinterfasetab.rowid,sizeof(svdinterfasetab.rowid),V10CADENA,
                          svdinterfasetab.tabla,sizeof(svdinterfasetab.tabla),V10CADENA,
                          svdinterfasetab.tablaalias,sizeof(svdinterfasetab.tablaalias),V10CADENA,
                          svdinterfasetab.abreviatura,sizeof(svdinterfasetab.abreviatura),V10CADENA,
                          &svdinterfasetab.ordeninsupd,sizeof(svdinterfasetab.ordeninsupd),V10LONG,
                          svdinterfasetab.vdextra,sizeof(svdinterfasetab.vdextra),V10CADENA,
                          svdinterfasetab.codopemodif,sizeof(svdinterfasetab.codopemodif),V10CADENA,
                          &svdinterfasetab.fecmodif,sizeof(svdinterfasetab.fecmodif),V10LONG,
                          svdinterfasetab.horamodif,sizeof(svdinterfasetab.horamodif),V10CADENA,
                          svdinterfasetab.libreria,sizeof(svdinterfasetab.libreria),V10CADENA,
                          &svdinterfasetab.codcomen,sizeof(svdinterfasetab.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselinttvdinterfasetab,"TABLA",svdinterfasetab.tabla,sizeof(svdinterfasetab.tabla),V10CADENA,
                          "TABLAALIAS",svdinterfasetab.tablaalias,sizeof(svdinterfasetab.tablaalias),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_intt);
        init = 1;
    }
}

diccionario *INTTdamediccionario(void)
{
     return(&dintt);
}

int INTTbuscatodo(vdinterfasetabs *intt)
{
  int vdret;
  memset(&svdinterfasetab,0,sizeof(svdinterfasetab));
  if (vdselintttodo==NULL) init_selintttodo();
  vdret=ejefetchcursor(vdselintttodo);
  if (vdret==0) {
     *intt=svdinterfasetab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselintttodo. vdret %d. \n",INTTlog(&svdinterfasetab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int INTTnexttodo(vdinterfasetabs *intt)
{
  int vdret;
  vdret=fetchcursor(vdselintttodo);
  if (vdret==0) {
     *intt=svdinterfasetab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselintttodo. vdret %d. \n",INTTlog(&svdinterfasetab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselintttodo);
  return(VD_EERRORACLE);
}

int INTTselvdinterfasetab(char *tabla,char *tablaalias,vdinterfasetabs *intt)
{
  int vdret;
  if (vdselinttvdinterfasetab==NULL) init_selinttvdinterfasetab();
  memset(&svdinterfasetab,0,sizeof(svdinterfasetab));
  strcpy(svdinterfasetab.tabla,tabla);
  strcpy(svdinterfasetab.tablaalias,tablaalias);
  vdret=ejefetchcursor(vdselinttvdinterfasetab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselinttvdinterfasetab. vdret %d. \n",INTTlog(&svdinterfasetab),vdret);
    return(VD_EERRORACLE);
   }
  *intt=svdinterfasetab;
  return(vdret);
}

char * INTTlog(vdinterfasetabs *intt)
{
    sprintf(msglogINTT, "VDINTERFASETAB: tabla %s tablaalias %s ",intt->tabla,intt->tablaalias);
    return(msglogINTT);
}

char * INTTdebug(vdinterfasetabs *intt)
{
    debugestruct(&dintt,intt,msgdebugINTT);
    return(msgdebugINTT);
}

