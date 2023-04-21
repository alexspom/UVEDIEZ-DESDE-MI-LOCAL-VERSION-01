// Modulo generado automaticamente a partir de VDUBICA.DEF
//#***
//# VDUBICA.c - Generación automática del código c para la tabla                                                        
//# 
//# Propósito: Funciones de acceso a la tabla VDUBICA
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 8-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=UBI
//
//EXTRA=PASILLOAUX,V10LONG
//UPDATE=RECARGAR,RECARGAR
//
//INSERT 

#include "vd.h"
#define SELUBIVDUBICA "SELECT VDUBICA.ROWID,VDUBICA.CODUBI,VDUBICA.CODZONA, "\
                    " VDUBICA.CODAREA,VDUBICA.TRANSITO,VDUBICA.PLANTA, "\
                    " VDUBICA.PASILLO,VDUBICA.COLUMNA,VDUBICA.ALTURA, "\
                    " VDUBICA.PROFUNDIDAD,VDUBICA.ORDENENTRADA,VDUBICA.ORDENSALIDA, "\
                    " VDUBICA.ORDENMOVIM,VDUBICA.BLOQUEOSE,VDUBICA.BLOQUEOSS, "\
                    " VDUBICA.MULTIARTICULO,VDUBICA.MULTIFORMATO,VDUBICA.UNIAGRUPAE, "\
                    " VDUBICA.UNICAPAC,VDUBICA.SWTETIQ,VDUBICA.STKMAX, "\
                    " VDUBICA.STKMIN,VDUBICA.STKURG,VDUBICA.CODART, "\
                    " VDUBICA.STOCK,VDUBICA.RECARGAR,VDUBICA.AGRUPALIN, "\
                    " VDUBICA.CONFPICKING,VDUBICA.TIPOUBI,VDUBICA.VDEXTRA, "\
                    " VDUBICA.CODCOMEN,VDUBICA.CODOPEMODIF,VDUBICA.FECMODIF, "\
                    " VDUBICA.HORAMODIF,VDUBICA.FECULTINVEN,VDUBICA.FECULTMOV, "\
                    " VDUBICA.SWTUBIMARCADA "\
        " FROM VDUBICA"\
        " WHERE "\
               " VDUBICA.CODUBI=:CODUBI "
static v10cursors *vdselubivdubica;

#define UPDAUBIRECARGAR "UPDATE VDUBICA SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " RECARGAR=:RECARGAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaubirecargar;

#define INSUBI "INSERT INTO VDUBICA (CODUBI,CODZONA,CODAREA,TRANSITO,PLANTA,PASILLO, "\
                    " COLUMNA,ALTURA,PROFUNDIDAD,ORDENENTRADA,ORDENSALIDA,ORDENMOVIM,BLOQUEOSE, "\
                    " BLOQUEOSS,MULTIARTICULO,MULTIFORMATO,UNIAGRUPAE,UNICAPAC,SWTETIQ,STKMAX, "\
                    " STKMIN,STKURG,CODART,STOCK,RECARGAR,AGRUPALIN,CONFPICKING, "\
                    " TIPOUBI,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,FECULTINVEN, "\
                    " FECULTMOV,SWTUBIMARCADA "\
       " ) VALUES ( "\
                    " :CODUBI,:CODZONA,:CODAREA,:TRANSITO,:PLANTA,:PASILLO, "\
                    " :COLUMNA,:ALTURA,:PROFUNDIDAD,:ORDENENTRADA,:ORDENSALIDA,:ORDENMOVIM,:BLOQUEOSE, "\
                    " :BLOQUEOSS,:MULTIARTICULO,:MULTIFORMATO,:UNIAGRUPAE,:UNICAPAC,:SWTETIQ,:STKMAX, "\
                    " :STKMIN,:STKURG,:CODART,:STOCK,:RECARGAR,:AGRUPALIN,:CONFPICKING, "\
                    " :TIPOUBI,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:FECULTINVEN, "\
                    " :FECULTMOV,:SWTUBIMARCADA) "
static v10cursors *vdinsubi;

static vdubicas svdubica;

static diccols colvdubica[]={
	{"ROWID",V10CADENA,(size_t)&svdubica.rowid,sizeof(svdubica.rowid)},
	{"CODUBI",V10CADENA,(size_t)&svdubica.codubi,sizeof(svdubica.codubi)},
	{"CODZONA",V10LONG,(size_t)&svdubica.codzona,sizeof(svdubica.codzona)},
	{"CODAREA",V10CADENA,(size_t)&svdubica.codarea,sizeof(svdubica.codarea)},
	{"TRANSITO",V10CADENA,(size_t)&svdubica.transito,sizeof(svdubica.transito)},
	{"PLANTA",V10LONG,(size_t)&svdubica.planta,sizeof(svdubica.planta)},
	{"PASILLO",V10LONG,(size_t)&svdubica.pasillo,sizeof(svdubica.pasillo)},
	{"COLUMNA",V10LONG,(size_t)&svdubica.columna,sizeof(svdubica.columna)},
	{"ALTURA",V10LONG,(size_t)&svdubica.altura,sizeof(svdubica.altura)},
	{"PROFUNDIDAD",V10LONG,(size_t)&svdubica.profundidad,sizeof(svdubica.profundidad)},
	{"ORDENENTRADA",V10LONG,(size_t)&svdubica.ordenentrada,sizeof(svdubica.ordenentrada)},
	{"ORDENSALIDA",V10LONG,(size_t)&svdubica.ordensalida,sizeof(svdubica.ordensalida)},
	{"ORDENMOVIM",V10LONG,(size_t)&svdubica.ordenmovim,sizeof(svdubica.ordenmovim)},
	{"BLOQUEOSE",V10CADENA,(size_t)&svdubica.bloqueose,sizeof(svdubica.bloqueose)},
	{"BLOQUEOSS",V10CADENA,(size_t)&svdubica.bloqueoss,sizeof(svdubica.bloqueoss)},
	{"MULTIARTICULO",V10CADENA,(size_t)&svdubica.multiarticulo,sizeof(svdubica.multiarticulo)},
	{"MULTIFORMATO",V10CADENA,(size_t)&svdubica.multiformato,sizeof(svdubica.multiformato)},
	{"UNIAGRUPAE",V10CADENA,(size_t)&svdubica.uniagrupae,sizeof(svdubica.uniagrupae)},
	{"UNICAPAC",V10CADENA,(size_t)&svdubica.unicapac,sizeof(svdubica.unicapac)},
	{"SWTETIQ",V10CADENA,(size_t)&svdubica.swtetiq,sizeof(svdubica.swtetiq)},
	{"STKMAX",V10LONG,(size_t)&svdubica.stkmax,sizeof(svdubica.stkmax)},
	{"STKMIN",V10LONG,(size_t)&svdubica.stkmin,sizeof(svdubica.stkmin)},
	{"STKURG",V10LONG,(size_t)&svdubica.stkurg,sizeof(svdubica.stkurg)},
	{"CODART",V10CADENA,(size_t)&svdubica.codart,sizeof(svdubica.codart)},
	{"STOCK",V10CADENA,(size_t)&svdubica.stock,sizeof(svdubica.stock)},
	{"RECARGAR",V10CADENA,(size_t)&svdubica.recargar,sizeof(svdubica.recargar)},
	{"AGRUPALIN",V10CADENA,(size_t)&svdubica.agrupalin,sizeof(svdubica.agrupalin)},
	{"CONFPICKING",V10CADENA,(size_t)&svdubica.confpicking,sizeof(svdubica.confpicking)},
	{"TIPOUBI",V10CADENA,(size_t)&svdubica.tipoubi,sizeof(svdubica.tipoubi)},
	{"VDEXTRA",V10CADENA,(size_t)&svdubica.vdextra,sizeof(svdubica.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdubica.codcomen,sizeof(svdubica.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdubica.codopemodif,sizeof(svdubica.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdubica.fecmodif,sizeof(svdubica.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdubica.horamodif,sizeof(svdubica.horamodif)},
	{"FECULTINVEN",V10LONG,(size_t)&svdubica.fecultinven,sizeof(svdubica.fecultinven)},
	{"FECULTMOV",V10LONG,(size_t)&svdubica.fecultmov,sizeof(svdubica.fecultmov)},
	{"SWTUBIMARCADA",V10CADENA,(size_t)&svdubica.swtubimarcada,sizeof(svdubica.swtubimarcada)},
	{"PASILLOAUX",V10LONG,(size_t)&svdubica.pasilloaux,sizeof(svdubica.pasilloaux)}
	};
static diccionarios dvdubica[]={
    {colvdubica,38}
};
diccionario dubi={dvdubica,1};

static char msglogUBI[LCADENA];
static char msgdebugUBI[LCADENABIG];
static int init=0;


static void fin_vd_ubi(void)
{
if (vdselubivdubica) {
    liberacursor(vdselubivdubica);
    vdselubivdubica = NULL;
}
if (vdupdaubirecargar) {
    liberacursor(vdupdaubirecargar);
    vdupdaubirecargar = NULL;
}
if (vdinsubi != NULL) {
    liberacursor(vdinsubi);
    vdinsubi = NULL;
}
}
static void init_selubivdubica(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdubica[0].numcol;nc++) dvdubica[0].c[nc].offset-=(size_t)&svdubica;
    vdselubivdubica=abrecursordebug(SELUBIVDUBICA,1280);
    definetodo(vdselubivdubica,svdubica.rowid,sizeof(svdubica.rowid),V10CADENA,
                          svdubica.codubi,sizeof(svdubica.codubi),V10CADENA,
                          &svdubica.codzona,sizeof(svdubica.codzona),V10LONG,
                          svdubica.codarea,sizeof(svdubica.codarea),V10CADENA,
                          svdubica.transito,sizeof(svdubica.transito),V10CADENA,
                          &svdubica.planta,sizeof(svdubica.planta),V10LONG,
                          &svdubica.pasillo,sizeof(svdubica.pasillo),V10LONG,
                          &svdubica.columna,sizeof(svdubica.columna),V10LONG,
                          &svdubica.altura,sizeof(svdubica.altura),V10LONG,
                          &svdubica.profundidad,sizeof(svdubica.profundidad),V10LONG,
                          &svdubica.ordenentrada,sizeof(svdubica.ordenentrada),V10LONG,
                          &svdubica.ordensalida,sizeof(svdubica.ordensalida),V10LONG,
                          &svdubica.ordenmovim,sizeof(svdubica.ordenmovim),V10LONG,
                          svdubica.bloqueose,sizeof(svdubica.bloqueose),V10CADENA,
                          svdubica.bloqueoss,sizeof(svdubica.bloqueoss),V10CADENA,
                          svdubica.multiarticulo,sizeof(svdubica.multiarticulo),V10CADENA,
                          svdubica.multiformato,sizeof(svdubica.multiformato),V10CADENA,
                          svdubica.uniagrupae,sizeof(svdubica.uniagrupae),V10CADENA,
                          svdubica.unicapac,sizeof(svdubica.unicapac),V10CADENA,
                          svdubica.swtetiq,sizeof(svdubica.swtetiq),V10CADENA,
                          &svdubica.stkmax,sizeof(svdubica.stkmax),V10LONG,
                          &svdubica.stkmin,sizeof(svdubica.stkmin),V10LONG,
                          &svdubica.stkurg,sizeof(svdubica.stkurg),V10LONG,
                          svdubica.codart,sizeof(svdubica.codart),V10CADENA,
                          svdubica.stock,sizeof(svdubica.stock),V10CADENA,
                          svdubica.recargar,sizeof(svdubica.recargar),V10CADENA,
                          svdubica.agrupalin,sizeof(svdubica.agrupalin),V10CADENA,
                          svdubica.confpicking,sizeof(svdubica.confpicking),V10CADENA,
                          svdubica.tipoubi,sizeof(svdubica.tipoubi),V10CADENA,
                          svdubica.vdextra,sizeof(svdubica.vdextra),V10CADENA,
                          &svdubica.codcomen,sizeof(svdubica.codcomen),V10LONG,
                          svdubica.codopemodif,sizeof(svdubica.codopemodif),V10CADENA,
                          &svdubica.fecmodif,sizeof(svdubica.fecmodif),V10LONG,
                          svdubica.horamodif,sizeof(svdubica.horamodif),V10CADENA,
                          &svdubica.fecultinven,sizeof(svdubica.fecultinven),V10LONG,
                          &svdubica.fecultmov,sizeof(svdubica.fecultmov),V10LONG,
                          svdubica.swtubimarcada,sizeof(svdubica.swtubimarcada),V10CADENA,
                          NULL);
    bindtodo(vdselubivdubica,"CODUBI",svdubica.codubi,sizeof(svdubica.codubi),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ubi);
        init = 1;
    }
}

static void init_updaubirecargar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdubica[0].numcol;nc++) dvdubica[0].c[nc].offset-=(size_t)&svdubica;
    vdupdaubirecargar=abrecursordebug(UPDAUBIRECARGAR,1280);
    bindtodo(vdupdaubirecargar,"RECARGAR",svdubica.recargar,sizeof(svdubica.recargar),V10CADENA,
                          "MIROWID",svdubica.rowid,sizeof(svdubica.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ubi);
        init = 1;
    }
}

static void init_insubi(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdubica[0].numcol;nc++) dvdubica[0].c[nc].offset-=(size_t)&svdubica;
    vdinsubi=abrecursordebug(INSUBI,1280);
    bindtodo(vdinsubi,"CODUBI",svdubica.codubi,sizeof(svdubica.codubi),V10CADENA,
                          "CODZONA",&svdubica.codzona,sizeof(svdubica.codzona),V10LONG,
                          "CODAREA",svdubica.codarea,sizeof(svdubica.codarea),V10CADENA,
                          "TRANSITO",svdubica.transito,sizeof(svdubica.transito),V10CADENA,
                          "PLANTA",&svdubica.planta,sizeof(svdubica.planta),V10LONG,
                          "PASILLO",&svdubica.pasillo,sizeof(svdubica.pasillo),V10LONG,
                          "COLUMNA",&svdubica.columna,sizeof(svdubica.columna),V10LONG,
                          "ALTURA",&svdubica.altura,sizeof(svdubica.altura),V10LONG,
                          "PROFUNDIDAD",&svdubica.profundidad,sizeof(svdubica.profundidad),V10LONG,
                          "ORDENENTRADA",&svdubica.ordenentrada,sizeof(svdubica.ordenentrada),V10LONG,
                          "ORDENSALIDA",&svdubica.ordensalida,sizeof(svdubica.ordensalida),V10LONG,
                          "ORDENMOVIM",&svdubica.ordenmovim,sizeof(svdubica.ordenmovim),V10LONG,
                          "BLOQUEOSE",svdubica.bloqueose,sizeof(svdubica.bloqueose),V10CADENA,
                          "BLOQUEOSS",svdubica.bloqueoss,sizeof(svdubica.bloqueoss),V10CADENA,
                          "MULTIARTICULO",svdubica.multiarticulo,sizeof(svdubica.multiarticulo),V10CADENA,
                          "MULTIFORMATO",svdubica.multiformato,sizeof(svdubica.multiformato),V10CADENA,
                          "UNIAGRUPAE",svdubica.uniagrupae,sizeof(svdubica.uniagrupae),V10CADENA,
                          "UNICAPAC",svdubica.unicapac,sizeof(svdubica.unicapac),V10CADENA,
                          "SWTETIQ",svdubica.swtetiq,sizeof(svdubica.swtetiq),V10CADENA,
                          "STKMAX",&svdubica.stkmax,sizeof(svdubica.stkmax),V10LONG,
                          "STKMIN",&svdubica.stkmin,sizeof(svdubica.stkmin),V10LONG,
                          "STKURG",&svdubica.stkurg,sizeof(svdubica.stkurg),V10LONG,
                          "CODART",svdubica.codart,sizeof(svdubica.codart),V10CADENA,
                          "STOCK",svdubica.stock,sizeof(svdubica.stock),V10CADENA,
                          "RECARGAR",svdubica.recargar,sizeof(svdubica.recargar),V10CADENA,
                          "AGRUPALIN",svdubica.agrupalin,sizeof(svdubica.agrupalin),V10CADENA,
                          "CONFPICKING",svdubica.confpicking,sizeof(svdubica.confpicking),V10CADENA,
                          "TIPOUBI",svdubica.tipoubi,sizeof(svdubica.tipoubi),V10CADENA,
                          "VDEXTRA",svdubica.vdextra,sizeof(svdubica.vdextra),V10CADENA,
                          "CODCOMEN",&svdubica.codcomen,sizeof(svdubica.codcomen),V10LONG,
                          "FECULTINVEN",&svdubica.fecultinven,sizeof(svdubica.fecultinven),V10LONG,
                          "FECULTMOV",&svdubica.fecultmov,sizeof(svdubica.fecultmov),V10LONG,
                          "SWTUBIMARCADA",svdubica.swtubimarcada,sizeof(svdubica.swtubimarcada),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ubi);
        init = 1;
    }
}

diccionario *UBIdamediccionario(void)
{
     return(&dubi);
}

int UBIselvdubica(char *codubi,vdubicas *ubi)
{
  int vdret;
  if (vdselubivdubica==NULL) init_selubivdubica();
  memset(&svdubica,0,sizeof(svdubica));
  strcpy(svdubica.codubi,codubi);
  vdret=ejefetchcursor(vdselubivdubica);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselubivdubica. vdret %d. \n",UBIlog(&svdubica),vdret);
    return(VD_EERRORACLE);
   }
  *ubi=svdubica;
  return(vdret);
}

int UBIactualizarecargar(vdubicas *ubi,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando UBIactualizarecargar:  %s .  \n",UBIlog(&svdubica));
  if (vdupdaubirecargar==NULL) init_updaubirecargar();
  svdubica=*ubi;
  vdret=ejecutacursor(vdupdaubirecargar);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaubirecargar);
     getcurerrornombre(vdupdaubirecargar->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaubirecargar)!=1) return(VD_EERRORACLE);
  return(0);
}

int UBIinsert(vdubicas *ubi,int error)
{
  int vdret;
  if (!vdinsubi) init_insubi();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",UBIlog(&svdubica));
  svdubica=*ubi;
  vdret=ejecutacursor(vdinsubi);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsubi);
     getcurerrornombre(vdinsubi->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * UBIlog(vdubicas *ubi)
{
    sprintf(msglogUBI, "VDUBICA: codubi %s ",ubi->codubi);
    return(msglogUBI);
}

char * UBIdebug(vdubicas *ubi)
{
    debugestruct(&dubi,ubi,msgdebugUBI);
    return(msgdebugUBI);
}

