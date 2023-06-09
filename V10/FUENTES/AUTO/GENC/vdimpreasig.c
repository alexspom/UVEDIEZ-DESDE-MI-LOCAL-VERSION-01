// Modulo generado automaticamente a partir de VDIMPREASIG.DEF
//#***
//# VDIMPREASIG.c - Generaci�n autom�tica del c�digo c para la tabla de Asignaci�n de Impresores a impresoras                                                  
//# 
//# Prop�sito: Funciones de acceso a la tabla VDIMPREASIG
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=IMAS
//
//RECORRE=IMPRESORAUSER;WHERE=CODOPEASIG=VDUSER.GETUSER AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S';ORDERBY=DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0);
//
//RECORRE=IMPRESORADEFECTO;WHERE=CODOPEASIG='DEFECTO' AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S';ORDERBY=DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0);
//
//RECORRE=IMPRESORA;WHERE=(CODOPEASIG=VDUSER.GETUSER OR CODOPEASIG='DEFECTO') AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S';ORDERBY=DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0);

#include "vd.h"
#define SELIMASIMPRESORAUSER "SELECT VDIMPREASIG.ROWID,VDIMPREASIG.CODOPEASIG,VDIMPREASIG.ORDENADOR, "\
                    " VDIMPREASIG.TIPOIMPRE,VDIMPREASIG.DOCUMENTO,VDIMPREASIG.CODIMPRE, "\
                    " VDIMPREASIG.ACTIVO,VDIMPREASIG.CODOPEMODIF,VDIMPREASIG.FECMODIF, "\
                    " VDIMPREASIG.HORAMODIF,VDIMPREASIG.CODCOMEN "\
        " FROM VDIMPREASIG"\
        " WHERE "\
              " CODOPEASIG=VDUSER.GETUSER AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S' "\
        " ORDER BY DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0) "
static v10cursors *vdselimasimpresorauser;

#define SELIMASIMPRESORADEFECTO "SELECT VDIMPREASIG.ROWID,VDIMPREASIG.CODOPEASIG,VDIMPREASIG.ORDENADOR, "\
                    " VDIMPREASIG.TIPOIMPRE,VDIMPREASIG.DOCUMENTO,VDIMPREASIG.CODIMPRE, "\
                    " VDIMPREASIG.ACTIVO,VDIMPREASIG.CODOPEMODIF,VDIMPREASIG.FECMODIF, "\
                    " VDIMPREASIG.HORAMODIF,VDIMPREASIG.CODCOMEN "\
        " FROM VDIMPREASIG"\
        " WHERE "\
              " CODOPEASIG='DEFECTO' AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S' "\
        " ORDER BY DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0) "
static v10cursors *vdselimasimpresoradefecto;

#define SELIMASIMPRESORA "SELECT VDIMPREASIG.ROWID,VDIMPREASIG.CODOPEASIG,VDIMPREASIG.ORDENADOR, "\
                    " VDIMPREASIG.TIPOIMPRE,VDIMPREASIG.DOCUMENTO,VDIMPREASIG.CODIMPRE, "\
                    " VDIMPREASIG.ACTIVO,VDIMPREASIG.CODOPEMODIF,VDIMPREASIG.FECMODIF, "\
                    " VDIMPREASIG.HORAMODIF,VDIMPREASIG.CODCOMEN "\
        " FROM VDIMPREASIG"\
        " WHERE "\
              " (CODOPEASIG=VDUSER.GETUSER OR CODOPEASIG='DEFECTO') AND (ORDENADOR=UPPER(:ORDENADOR) OR ORDENADOR='DEFECTO') AND TIPOIMPRE=:TIPOIMPRE AND (DOCUMENTO=UPPER(:DOCUMENTO) OR DOCUMENTO='DEFECTO') AND ACTIVO='S' "\
        " ORDER BY DECODE(CODOPEASIG,'DEFECTO',1,0),DECODE(ORDENADOR,'DEFECTO',1,0), DECODE(DOCUMENTO,'DEFECTO',1,0) "
static v10cursors *vdselimasimpresora;

#define SELIMASVDIMPREASIG "SELECT VDIMPREASIG.ROWID,VDIMPREASIG.CODOPEASIG,VDIMPREASIG.ORDENADOR, "\
                    " VDIMPREASIG.TIPOIMPRE,VDIMPREASIG.DOCUMENTO,VDIMPREASIG.CODIMPRE, "\
                    " VDIMPREASIG.ACTIVO,VDIMPREASIG.CODOPEMODIF,VDIMPREASIG.FECMODIF, "\
                    " VDIMPREASIG.HORAMODIF,VDIMPREASIG.CODCOMEN "\
        " FROM VDIMPREASIG"\
        " WHERE "\
               " VDIMPREASIG.CODOPEASIG=:CODOPEASIG "\
               " AND VDIMPREASIG.ORDENADOR=:ORDENADOR "\
               " AND VDIMPREASIG.TIPOIMPRE=:TIPOIMPRE "\
               " AND VDIMPREASIG.DOCUMENTO=:DOCUMENTO "\
               " AND VDIMPREASIG.CODIMPRE=:CODIMPRE "
static v10cursors *vdselimasvdimpreasig;

static vdimpreasigs svdimpreasig;

static diccols colvdimpreasig[]={
	{"ROWID",V10CADENA,(size_t)&svdimpreasig.rowid,sizeof(svdimpreasig.rowid)},
	{"CODOPEASIG",V10CADENA,(size_t)&svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig)},
	{"ORDENADOR",V10CADENA,(size_t)&svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador)},
	{"TIPOIMPRE",V10CADENA,(size_t)&svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre)},
	{"DOCUMENTO",V10CADENA,(size_t)&svdimpreasig.documento,sizeof(svdimpreasig.documento)},
	{"CODIMPRE",V10CADENA,(size_t)&svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre)},
	{"ACTIVO",V10CADENA,(size_t)&svdimpreasig.activo,sizeof(svdimpreasig.activo)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdimpreasig.codopemodif,sizeof(svdimpreasig.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdimpreasig.fecmodif,sizeof(svdimpreasig.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdimpreasig.horamodif,sizeof(svdimpreasig.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdimpreasig.codcomen,sizeof(svdimpreasig.codcomen)}
	};
static diccionarios dvdimpreasig[]={
    {colvdimpreasig,11}
};
diccionario dimas={dvdimpreasig,1};

static char msglogIMAS[LCADENA];
static char msgdebugIMAS[LCADENABIG];
static int init=0;


static void fin_vd_imas(void)
{
if (vdselimasimpresorauser) {
    liberacursor(vdselimasimpresorauser);
    vdselimasimpresorauser = NULL;
}
if (vdselimasimpresoradefecto) {
    liberacursor(vdselimasimpresoradefecto);
    vdselimasimpresoradefecto = NULL;
}
if (vdselimasimpresora) {
    liberacursor(vdselimasimpresora);
    vdselimasimpresora = NULL;
}
if (vdselimasvdimpreasig) {
    liberacursor(vdselimasvdimpreasig);
    vdselimasvdimpreasig = NULL;
}
}
static void init_selimasimpresorauser(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpreasig[0].numcol;nc++) dvdimpreasig[0].c[nc].offset-=(size_t)&svdimpreasig;
    vdselimasimpresorauser=abrecursordebug(SELIMASIMPRESORAUSER,1280);
    definetodo(vdselimasimpresorauser,svdimpreasig.rowid,sizeof(svdimpreasig.rowid),V10CADENA,
                          svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig),V10CADENA,
                          svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre),V10CADENA,
                          svdimpreasig.activo,sizeof(svdimpreasig.activo),V10CADENA,
                          svdimpreasig.codopemodif,sizeof(svdimpreasig.codopemodif),V10CADENA,
                          &svdimpreasig.fecmodif,sizeof(svdimpreasig.fecmodif),V10LONG,
                          svdimpreasig.horamodif,sizeof(svdimpreasig.horamodif),V10CADENA,
                          &svdimpreasig.codcomen,sizeof(svdimpreasig.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimasimpresorauser,"ORDENADOR",svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          "TIPOIMPRE",svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          "DOCUMENTO",svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imas);
        init = 1;
    }
}

static void init_selimasimpresoradefecto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpreasig[0].numcol;nc++) dvdimpreasig[0].c[nc].offset-=(size_t)&svdimpreasig;
    vdselimasimpresoradefecto=abrecursordebug(SELIMASIMPRESORADEFECTO,1280);
    definetodo(vdselimasimpresoradefecto,svdimpreasig.rowid,sizeof(svdimpreasig.rowid),V10CADENA,
                          svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig),V10CADENA,
                          svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre),V10CADENA,
                          svdimpreasig.activo,sizeof(svdimpreasig.activo),V10CADENA,
                          svdimpreasig.codopemodif,sizeof(svdimpreasig.codopemodif),V10CADENA,
                          &svdimpreasig.fecmodif,sizeof(svdimpreasig.fecmodif),V10LONG,
                          svdimpreasig.horamodif,sizeof(svdimpreasig.horamodif),V10CADENA,
                          &svdimpreasig.codcomen,sizeof(svdimpreasig.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimasimpresoradefecto,"ORDENADOR",svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          "TIPOIMPRE",svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          "DOCUMENTO",svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imas);
        init = 1;
    }
}

static void init_selimasimpresora(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpreasig[0].numcol;nc++) dvdimpreasig[0].c[nc].offset-=(size_t)&svdimpreasig;
    vdselimasimpresora=abrecursordebug(SELIMASIMPRESORA,1280);
    definetodo(vdselimasimpresora,svdimpreasig.rowid,sizeof(svdimpreasig.rowid),V10CADENA,
                          svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig),V10CADENA,
                          svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre),V10CADENA,
                          svdimpreasig.activo,sizeof(svdimpreasig.activo),V10CADENA,
                          svdimpreasig.codopemodif,sizeof(svdimpreasig.codopemodif),V10CADENA,
                          &svdimpreasig.fecmodif,sizeof(svdimpreasig.fecmodif),V10LONG,
                          svdimpreasig.horamodif,sizeof(svdimpreasig.horamodif),V10CADENA,
                          &svdimpreasig.codcomen,sizeof(svdimpreasig.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimasimpresora,"ORDENADOR",svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          "TIPOIMPRE",svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          "DOCUMENTO",svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imas);
        init = 1;
    }
}

static void init_selimasvdimpreasig(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpreasig[0].numcol;nc++) dvdimpreasig[0].c[nc].offset-=(size_t)&svdimpreasig;
    vdselimasvdimpreasig=abrecursordebug(SELIMASVDIMPREASIG,1280);
    definetodo(vdselimasvdimpreasig,svdimpreasig.rowid,sizeof(svdimpreasig.rowid),V10CADENA,
                          svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig),V10CADENA,
                          svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre),V10CADENA,
                          svdimpreasig.activo,sizeof(svdimpreasig.activo),V10CADENA,
                          svdimpreasig.codopemodif,sizeof(svdimpreasig.codopemodif),V10CADENA,
                          &svdimpreasig.fecmodif,sizeof(svdimpreasig.fecmodif),V10LONG,
                          svdimpreasig.horamodif,sizeof(svdimpreasig.horamodif),V10CADENA,
                          &svdimpreasig.codcomen,sizeof(svdimpreasig.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimasvdimpreasig,"CODOPEASIG",svdimpreasig.codopeasig,sizeof(svdimpreasig.codopeasig),V10CADENA,
                          "ORDENADOR",svdimpreasig.ordenador,sizeof(svdimpreasig.ordenador),V10CADENA,
                          "TIPOIMPRE",svdimpreasig.tipoimpre,sizeof(svdimpreasig.tipoimpre),V10CADENA,
                          "DOCUMENTO",svdimpreasig.documento,sizeof(svdimpreasig.documento),V10CADENA,
                          "CODIMPRE",svdimpreasig.codimpre,sizeof(svdimpreasig.codimpre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imas);
        init = 1;
    }
}

diccionario *IMASdamediccionario(void)
{
     return(&dimas);
}

int IMASbuscaimpresorauser(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas)
{
  int vdret;
  memset(&svdimpreasig,0,sizeof(svdimpreasig));
  strcpy(svdimpreasig.ordenador,ordenador);
  strcpy(svdimpreasig.tipoimpre,tipoimpre);
  strcpy(svdimpreasig.documento,documento);
  if (vdselimasimpresorauser==NULL) init_selimasimpresorauser();
  vdret=ejefetchcursor(vdselimasimpresorauser);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselimasimpresorauser. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IMASnextimpresorauser(vdimpreasigs *imas)
{
  int vdret;
  vdret=fetchcursor(vdselimasimpresorauser);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselimasimpresorauser. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselimasimpresorauser);
  return(VD_EERRORACLE);
}

int IMASbuscaimpresoradefecto(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas)
{
  int vdret;
  memset(&svdimpreasig,0,sizeof(svdimpreasig));
  strcpy(svdimpreasig.ordenador,ordenador);
  strcpy(svdimpreasig.tipoimpre,tipoimpre);
  strcpy(svdimpreasig.documento,documento);
  if (vdselimasimpresoradefecto==NULL) init_selimasimpresoradefecto();
  vdret=ejefetchcursor(vdselimasimpresoradefecto);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselimasimpresoradefecto. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IMASnextimpresoradefecto(vdimpreasigs *imas)
{
  int vdret;
  vdret=fetchcursor(vdselimasimpresoradefecto);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselimasimpresoradefecto. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselimasimpresoradefecto);
  return(VD_EERRORACLE);
}

int IMASbuscaimpresora(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas)
{
  int vdret;
  memset(&svdimpreasig,0,sizeof(svdimpreasig));
  strcpy(svdimpreasig.ordenador,ordenador);
  strcpy(svdimpreasig.tipoimpre,tipoimpre);
  strcpy(svdimpreasig.documento,documento);
  if (vdselimasimpresora==NULL) init_selimasimpresora();
  vdret=ejefetchcursor(vdselimasimpresora);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselimasimpresora. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IMASnextimpresora(vdimpreasigs *imas)
{
  int vdret;
  vdret=fetchcursor(vdselimasimpresora);
  if (vdret==0) {
     *imas=svdimpreasig;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselimasimpresora. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselimasimpresora);
  return(VD_EERRORACLE);
}

int IMASselvdimpreasig(char *codopeasig,char *ordenador,char *tipoimpre,char *documento,char *codimpre,vdimpreasigs *imas)
{
  int vdret;
  if (vdselimasvdimpreasig==NULL) init_selimasvdimpreasig();
  memset(&svdimpreasig,0,sizeof(svdimpreasig));
  strcpy(svdimpreasig.codopeasig,codopeasig);
  strcpy(svdimpreasig.ordenador,ordenador);
  strcpy(svdimpreasig.tipoimpre,tipoimpre);
  strcpy(svdimpreasig.documento,documento);
  strcpy(svdimpreasig.codimpre,codimpre);
  vdret=ejefetchcursor(vdselimasvdimpreasig);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimasvdimpreasig. vdret %d. \n",IMASlog(&svdimpreasig),vdret);
    return(VD_EERRORACLE);
   }
  *imas=svdimpreasig;
  return(vdret);
}

char * IMASlog(vdimpreasigs *imas)
{
    sprintf(msglogIMAS, "VDIMPREASIG: codopeasig %s ordenador %s tipoimpre %s documento %s codimpre %s ",imas->codopeasig,imas->ordenador,imas->tipoimpre,imas->documento,imas->codimpre);
    return(msglogIMAS);
}

char * IMASdebug(vdimpreasigs *imas)
{
    debugestruct(&dimas,imas,msgdebugIMAS);
    return(msgdebugIMAS);
}

