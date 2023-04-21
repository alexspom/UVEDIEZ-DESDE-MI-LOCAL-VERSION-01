// Modulo generado automaticamente a partir de VDSTOCK.DEF
//#***
//# VDSTOCK.c - Generación automática del código c para la tabla  VDSTOCK                                                     
//# 
//# Propósito: Funciones de acceso a la tabla VDSTOCK
//#           
//# Autor	 : JMM
//# Revisado por: 
//# Fecha  : 29-050-2008                                              
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=STK
//
//CLAVE=CONTNS, CODMAT, GENCOUNT=NUMEROSERIE;WHERE=TRIM(NUMEROSERIE) IS NOT NULL;
//
//RECORRE=CODMAT,CODMAT
//
//UPDATE=MATRICULA,CODMAT
//#UPDATE=NUMEROSERIE,NUMEROSERIE;

#include "vd.h"
#define SELSTKCONTNS "SELECT COUNT(DISTINCT NUMEROSERIE) GENCOUNT "\
        " FROM VDSTOCK"\
        " WHERE "\
               " VDSTOCK.CODMAT=:CODMAT "\
              "  AND TRIM(NUMEROSERIE) IS NOT NULL "
static v10cursors *vdselstkcontns;

#define SELSTKCODMAT "SELECT VDSTOCK.ROWID,VDSTOCK.CODMAT,VDSTOCK.ORDENSTK, "\
                    " VDSTOCK.BULTO,VDSTOCK.MARCASTK,VDSTOCK.NUMEROSERIE, "\
                    " VDSTOCK.CODART,VDSTOCK.CODLOT,VDSTOCK.CANTIDAD, "\
                    " VDSTOCK.BLOQUEOS,VDSTOCK.TIPOEMBA,VDSTOCK.UNIEMB, "\
                    " VDSTOCK.EMBCONT,VDSTOCK.PRECIOUNI,VDSTOCK.PESOUNI, "\
                    " VDSTOCK.CODRECEP,VDSTOCK.VDEXTRA,VDSTOCK.CODCOMEN, "\
                    " VDSTOCK.CODOPEMODIF,VDSTOCK.FECMODIF,VDSTOCK.HORAMODIF "\
        " FROM VDSTOCK"\
        " WHERE "\
               " VDSTOCK.CODMAT=:CODMAT "
static v10cursors *vdselstkcodmat;

#define SELSTKVDSTOCK "SELECT VDSTOCK.ROWID,VDSTOCK.CODMAT,VDSTOCK.ORDENSTK, "\
                    " VDSTOCK.BULTO,VDSTOCK.MARCASTK,VDSTOCK.NUMEROSERIE, "\
                    " VDSTOCK.CODART,VDSTOCK.CODLOT,VDSTOCK.CANTIDAD, "\
                    " VDSTOCK.BLOQUEOS,VDSTOCK.TIPOEMBA,VDSTOCK.UNIEMB, "\
                    " VDSTOCK.EMBCONT,VDSTOCK.PRECIOUNI,VDSTOCK.PESOUNI, "\
                    " VDSTOCK.CODRECEP,VDSTOCK.VDEXTRA,VDSTOCK.CODCOMEN, "\
                    " VDSTOCK.CODOPEMODIF,VDSTOCK.FECMODIF,VDSTOCK.HORAMODIF "\
        " FROM VDSTOCK"\
        " WHERE "\
               " VDSTOCK.CODMAT=:CODMAT "\
               " AND VDSTOCK.ORDENSTK=:ORDENSTK "
static v10cursors *vdselstkvdstock;

#define UPDASTKMATRICULA "UPDATE VDSTOCK SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODMAT=:CODMAT  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdastkmatricula;

static vdstocks svdstock;

static diccols colvdstock[]={
	{"ROWID",V10CADENA,(size_t)&svdstock.rowid,sizeof(svdstock.rowid)},
	{"CODMAT",V10CADENA,(size_t)&svdstock.codmat,sizeof(svdstock.codmat)},
	{"ORDENSTK",V10LONG,(size_t)&svdstock.ordenstk,sizeof(svdstock.ordenstk)},
	{"BULTO",V10CADENA,(size_t)&svdstock.bulto,sizeof(svdstock.bulto)},
	{"MARCASTK",V10CADENA,(size_t)&svdstock.marcastk,sizeof(svdstock.marcastk)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdstock.numeroserie,sizeof(svdstock.numeroserie)},
	{"CODART",V10CADENA,(size_t)&svdstock.codart,sizeof(svdstock.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdstock.codlot,sizeof(svdstock.codlot)},
	{"CANTIDAD",V10DOUBLE,(size_t)&svdstock.cantidad,sizeof(svdstock.cantidad)},
	{"BLOQUEOS",V10CADENA,(size_t)&svdstock.bloqueos,sizeof(svdstock.bloqueos)},
	{"TIPOEMBA",V10CADENA,(size_t)&svdstock.tipoemba,sizeof(svdstock.tipoemba)},
	{"UNIEMB",V10DOUBLE,(size_t)&svdstock.uniemb,sizeof(svdstock.uniemb)},
	{"EMBCONT",V10LONG,(size_t)&svdstock.embcont,sizeof(svdstock.embcont)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svdstock.preciouni,sizeof(svdstock.preciouni)},
	{"PESOUNI",V10DOUBLE,(size_t)&svdstock.pesouni,sizeof(svdstock.pesouni)},
	{"CODRECEP",V10CADENA,(size_t)&svdstock.codrecep,sizeof(svdstock.codrecep)},
	{"VDEXTRA",V10CADENA,(size_t)&svdstock.vdextra,sizeof(svdstock.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdstock.codcomen,sizeof(svdstock.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdstock.codopemodif,sizeof(svdstock.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdstock.fecmodif,sizeof(svdstock.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdstock.horamodif,sizeof(svdstock.horamodif)},
	{"GENCOUNT",V10DOUBLE,(size_t)&svdstock.gencount,sizeof(svdstock.gencount)}
	};
static diccionarios dvdstock[]={
    {colvdstock,22}
};
diccionario dstk={dvdstock,1};

static char msglogSTK[LCADENA];
static char msgdebugSTK[LCADENABIG];
static int init=0;


static void fin_vd_stk(void)
{
if (vdselstkcontns) {
    liberacursor(vdselstkcontns);
    vdselstkcontns = NULL;
}
if (vdselstkcodmat) {
    liberacursor(vdselstkcodmat);
    vdselstkcodmat = NULL;
}
if (vdselstkvdstock) {
    liberacursor(vdselstkvdstock);
    vdselstkvdstock = NULL;
}
if (vdupdastkmatricula) {
    liberacursor(vdupdastkmatricula);
    vdupdastkmatricula = NULL;
}
}
static void init_selstkcontns(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstock[0].numcol;nc++) dvdstock[0].c[nc].offset-=(size_t)&svdstock;
    vdselstkcontns=abrecursordebug(SELSTKCONTNS,1280);
    definetodo(vdselstkcontns,&svdstock.gencount,sizeof(svdstock.gencount),V10DOUBLE,
                          NULL);
    bindtodo(vdselstkcontns,"CODMAT",svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_stk);
        init = 1;
    }
}

static void init_selstkcodmat(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstock[0].numcol;nc++) dvdstock[0].c[nc].offset-=(size_t)&svdstock;
    vdselstkcodmat=abrecursordebug(SELSTKCODMAT,1280);
    definetodo(vdselstkcodmat,svdstock.rowid,sizeof(svdstock.rowid),V10CADENA,
                          svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          &svdstock.ordenstk,sizeof(svdstock.ordenstk),V10LONG,
                          svdstock.bulto,sizeof(svdstock.bulto),V10CADENA,
                          svdstock.marcastk,sizeof(svdstock.marcastk),V10CADENA,
                          svdstock.numeroserie,sizeof(svdstock.numeroserie),V10CADENA,
                          svdstock.codart,sizeof(svdstock.codart),V10CADENA,
                          svdstock.codlot,sizeof(svdstock.codlot),V10CADENA,
                          &svdstock.cantidad,sizeof(svdstock.cantidad),V10DOUBLE,
                          svdstock.bloqueos,sizeof(svdstock.bloqueos),V10CADENA,
                          svdstock.tipoemba,sizeof(svdstock.tipoemba),V10CADENA,
                          &svdstock.uniemb,sizeof(svdstock.uniemb),V10DOUBLE,
                          &svdstock.embcont,sizeof(svdstock.embcont),V10LONG,
                          &svdstock.preciouni,sizeof(svdstock.preciouni),V10DOUBLE,
                          &svdstock.pesouni,sizeof(svdstock.pesouni),V10DOUBLE,
                          svdstock.codrecep,sizeof(svdstock.codrecep),V10CADENA,
                          svdstock.vdextra,sizeof(svdstock.vdextra),V10CADENA,
                          &svdstock.codcomen,sizeof(svdstock.codcomen),V10LONG,
                          svdstock.codopemodif,sizeof(svdstock.codopemodif),V10CADENA,
                          &svdstock.fecmodif,sizeof(svdstock.fecmodif),V10LONG,
                          svdstock.horamodif,sizeof(svdstock.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselstkcodmat,"CODMAT",svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_stk);
        init = 1;
    }
}

static void init_selstkvdstock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstock[0].numcol;nc++) dvdstock[0].c[nc].offset-=(size_t)&svdstock;
    vdselstkvdstock=abrecursordebug(SELSTKVDSTOCK,1280);
    definetodo(vdselstkvdstock,svdstock.rowid,sizeof(svdstock.rowid),V10CADENA,
                          svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          &svdstock.ordenstk,sizeof(svdstock.ordenstk),V10LONG,
                          svdstock.bulto,sizeof(svdstock.bulto),V10CADENA,
                          svdstock.marcastk,sizeof(svdstock.marcastk),V10CADENA,
                          svdstock.numeroserie,sizeof(svdstock.numeroserie),V10CADENA,
                          svdstock.codart,sizeof(svdstock.codart),V10CADENA,
                          svdstock.codlot,sizeof(svdstock.codlot),V10CADENA,
                          &svdstock.cantidad,sizeof(svdstock.cantidad),V10DOUBLE,
                          svdstock.bloqueos,sizeof(svdstock.bloqueos),V10CADENA,
                          svdstock.tipoemba,sizeof(svdstock.tipoemba),V10CADENA,
                          &svdstock.uniemb,sizeof(svdstock.uniemb),V10DOUBLE,
                          &svdstock.embcont,sizeof(svdstock.embcont),V10LONG,
                          &svdstock.preciouni,sizeof(svdstock.preciouni),V10DOUBLE,
                          &svdstock.pesouni,sizeof(svdstock.pesouni),V10DOUBLE,
                          svdstock.codrecep,sizeof(svdstock.codrecep),V10CADENA,
                          svdstock.vdextra,sizeof(svdstock.vdextra),V10CADENA,
                          &svdstock.codcomen,sizeof(svdstock.codcomen),V10LONG,
                          svdstock.codopemodif,sizeof(svdstock.codopemodif),V10CADENA,
                          &svdstock.fecmodif,sizeof(svdstock.fecmodif),V10LONG,
                          svdstock.horamodif,sizeof(svdstock.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselstkvdstock,"CODMAT",svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          "ORDENSTK",&svdstock.ordenstk,sizeof(svdstock.ordenstk),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_stk);
        init = 1;
    }
}

static void init_updastkmatricula(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstock[0].numcol;nc++) dvdstock[0].c[nc].offset-=(size_t)&svdstock;
    vdupdastkmatricula=abrecursordebug(UPDASTKMATRICULA,1280);
    bindtodo(vdupdastkmatricula,"CODMAT",svdstock.codmat,sizeof(svdstock.codmat),V10CADENA,
                          "MIROWID",svdstock.rowid,sizeof(svdstock.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_stk);
        init = 1;
    }
}

diccionario *STKdamediccionario(void)
{
     return(&dstk);
}

int STKselcontns(char *codmat,vdstocks *stk)
{
  int vdret;
  if (vdselstkcontns==NULL) init_selstkcontns();
  memset(&svdstock,0,sizeof(svdstock));
  strcpy(svdstock.codmat,codmat);
  vdret=ejefetchcursor(vdselstkcontns);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselstkcontns. vdret %d. \n",STKlog(&svdstock),vdret);
    return(VD_EERRORACLE);
   }
  *stk=svdstock;
  return(vdret);
}

int STKbuscacodmat(char *codmat,vdstocks *stk)
{
  int vdret;
  memset(&svdstock,0,sizeof(svdstock));
  strcpy(svdstock.codmat,codmat);
  if (vdselstkcodmat==NULL) init_selstkcodmat();
  vdret=ejefetchcursor(vdselstkcodmat);
  if (vdret==0) {
     *stk=svdstock;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselstkcodmat. vdret %d. \n",STKlog(&svdstock),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int STKnextcodmat(vdstocks *stk)
{
  int vdret;
  vdret=fetchcursor(vdselstkcodmat);
  if (vdret==0) {
     *stk=svdstock;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselstkcodmat. vdret %d. \n",STKlog(&svdstock),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselstkcodmat);
  return(VD_EERRORACLE);
}

int STKselvdstock(char *codmat,long ordenstk,vdstocks *stk)
{
  int vdret;
  if (vdselstkvdstock==NULL) init_selstkvdstock();
  memset(&svdstock,0,sizeof(svdstock));
  strcpy(svdstock.codmat,codmat);
  svdstock.ordenstk=ordenstk;
  vdret=ejefetchcursor(vdselstkvdstock);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselstkvdstock. vdret %d. \n",STKlog(&svdstock),vdret);
    return(VD_EERRORACLE);
   }
  *stk=svdstock;
  return(vdret);
}

int STKactualizamatricula(vdstocks *stk,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando STKactualizamatricula:  %s .  \n",STKlog(&svdstock));
  if (vdupdastkmatricula==NULL) init_updastkmatricula();
  svdstock=*stk;
  vdret=ejecutacursor(vdupdastkmatricula);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdastkmatricula);
     getcurerrornombre(vdupdastkmatricula->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdastkmatricula)!=1) return(VD_EERRORACLE);
  return(0);
}

char * STKlog(vdstocks *stk)
{
    sprintf(msglogSTK, "VDSTOCK: codmat %s ordenstk %ld ",stk->codmat,stk->ordenstk);
    return(msglogSTK);
}

char * STKdebug(vdstocks *stk)
{
    debugestruct(&dstk,stk,msgdebugSTK);
    return(msgdebugSTK);
}

