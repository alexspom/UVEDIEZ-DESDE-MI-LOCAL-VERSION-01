// Modulo generado automaticamente a partir de VDTIPOCOMEN.DEF
//#***
//# VDTIPOCOMEN.c - Generación automática del código c para la tabla VDTIPOCOMEN                                                       
//# 
//# Propósito: Funciones de acceso a la tabla VDTIPOCOMEN
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 13-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=TCO
//
//RECORRE=TIPOCOMEN,TIPOCOMEN
//
//INSERT

#include "vd.h"
#define SELTCOTIPOCOMEN "SELECT VDTIPOCOMEN.ROWID,VDTIPOCOMEN.TABLACOMEN,VDTIPOCOMEN.TIPOCOMEN, "\
                    " VDTIPOCOMEN.DESTIPOCOMEN,VDTIPOCOMEN.ORDEN,VDTIPOCOMEN.MAXLINEAS, "\
                    " VDTIPOCOMEN.NOTIFICABLE,VDTIPOCOMEN.PRIVILEGIOSVER,VDTIPOCOMEN.PRIVILEGIOSMOD, "\
                    " VDTIPOCOMEN.PRIVILEGIOSINS,VDTIPOCOMEN.CODOPEMODIF,VDTIPOCOMEN.FECMODIF, "\
                    " VDTIPOCOMEN.HORAMODIF "\
        " FROM VDTIPOCOMEN"\
        " WHERE "\
               " VDTIPOCOMEN.TIPOCOMEN=:TIPOCOMEN "
static v10cursors *vdseltcotipocomen;

#define SELTCOVDTIPOCOMEN "SELECT VDTIPOCOMEN.ROWID,VDTIPOCOMEN.TABLACOMEN,VDTIPOCOMEN.TIPOCOMEN, "\
                    " VDTIPOCOMEN.DESTIPOCOMEN,VDTIPOCOMEN.ORDEN,VDTIPOCOMEN.MAXLINEAS, "\
                    " VDTIPOCOMEN.NOTIFICABLE,VDTIPOCOMEN.PRIVILEGIOSVER,VDTIPOCOMEN.PRIVILEGIOSMOD, "\
                    " VDTIPOCOMEN.PRIVILEGIOSINS,VDTIPOCOMEN.CODOPEMODIF,VDTIPOCOMEN.FECMODIF, "\
                    " VDTIPOCOMEN.HORAMODIF "\
        " FROM VDTIPOCOMEN"\
        " WHERE "\
               " VDTIPOCOMEN.TABLACOMEN=:TABLACOMEN "\
               " AND VDTIPOCOMEN.TIPOCOMEN=:TIPOCOMEN "
static v10cursors *vdseltcovdtipocomen;

#define INSTCO "INSERT INTO VDTIPOCOMEN (TABLACOMEN,TIPOCOMEN,DESTIPOCOMEN,ORDEN,MAXLINEAS,NOTIFICABLE, "\
                    " PRIVILEGIOSVER,PRIVILEGIOSMOD,PRIVILEGIOSINS,CODOPEMODIF,FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :TABLACOMEN,:TIPOCOMEN,:DESTIPOCOMEN,:ORDEN,:MAXLINEAS,:NOTIFICABLE, "\
                    " :PRIVILEGIOSVER,:PRIVILEGIOSMOD,:PRIVILEGIOSINS,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS) "
static v10cursors *vdinstco;

static vdtipocomens svdtipocomen;

static diccols colvdtipocomen[]={
	{"ROWID",V10CADENA,(size_t)&svdtipocomen.rowid,sizeof(svdtipocomen.rowid)},
	{"TABLACOMEN",V10CADENA,(size_t)&svdtipocomen.tablacomen,sizeof(svdtipocomen.tablacomen)},
	{"TIPOCOMEN",V10CADENA,(size_t)&svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen)},
	{"DESTIPOCOMEN",V10CADENA,(size_t)&svdtipocomen.destipocomen,sizeof(svdtipocomen.destipocomen)},
	{"ORDEN",V10LONG,(size_t)&svdtipocomen.orden,sizeof(svdtipocomen.orden)},
	{"MAXLINEAS",V10LONG,(size_t)&svdtipocomen.maxlineas,sizeof(svdtipocomen.maxlineas)},
	{"NOTIFICABLE",V10CADENA,(size_t)&svdtipocomen.notificable,sizeof(svdtipocomen.notificable)},
	{"PRIVILEGIOSVER",V10CADENA,(size_t)&svdtipocomen.privilegiosver,sizeof(svdtipocomen.privilegiosver)},
	{"PRIVILEGIOSMOD",V10CADENA,(size_t)&svdtipocomen.privilegiosmod,sizeof(svdtipocomen.privilegiosmod)},
	{"PRIVILEGIOSINS",V10CADENA,(size_t)&svdtipocomen.privilegiosins,sizeof(svdtipocomen.privilegiosins)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdtipocomen.codopemodif,sizeof(svdtipocomen.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdtipocomen.fecmodif,sizeof(svdtipocomen.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdtipocomen.horamodif,sizeof(svdtipocomen.horamodif)}
	};
static diccionarios dvdtipocomen[]={
    {colvdtipocomen,13}
};
diccionario dtco={dvdtipocomen,1};

static char msglogTCO[LCADENA];
static char msgdebugTCO[LCADENABIG];
static int init=0;


static void fin_vd_tco(void)
{
if (vdseltcotipocomen) {
    liberacursor(vdseltcotipocomen);
    vdseltcotipocomen = NULL;
}
if (vdseltcovdtipocomen) {
    liberacursor(vdseltcovdtipocomen);
    vdseltcovdtipocomen = NULL;
}
if (vdinstco != NULL) {
    liberacursor(vdinstco);
    vdinstco = NULL;
}
}
static void init_seltcotipocomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtipocomen[0].numcol;nc++) dvdtipocomen[0].c[nc].offset-=(size_t)&svdtipocomen;
    vdseltcotipocomen=abrecursordebug(SELTCOTIPOCOMEN,1280);
    definetodo(vdseltcotipocomen,svdtipocomen.rowid,sizeof(svdtipocomen.rowid),V10CADENA,
                          svdtipocomen.tablacomen,sizeof(svdtipocomen.tablacomen),V10CADENA,
                          svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen),V10CADENA,
                          svdtipocomen.destipocomen,sizeof(svdtipocomen.destipocomen),V10CADENA,
                          &svdtipocomen.orden,sizeof(svdtipocomen.orden),V10LONG,
                          &svdtipocomen.maxlineas,sizeof(svdtipocomen.maxlineas),V10LONG,
                          svdtipocomen.notificable,sizeof(svdtipocomen.notificable),V10CADENA,
                          svdtipocomen.privilegiosver,sizeof(svdtipocomen.privilegiosver),V10CADENA,
                          svdtipocomen.privilegiosmod,sizeof(svdtipocomen.privilegiosmod),V10CADENA,
                          svdtipocomen.privilegiosins,sizeof(svdtipocomen.privilegiosins),V10CADENA,
                          svdtipocomen.codopemodif,sizeof(svdtipocomen.codopemodif),V10CADENA,
                          &svdtipocomen.fecmodif,sizeof(svdtipocomen.fecmodif),V10LONG,
                          svdtipocomen.horamodif,sizeof(svdtipocomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseltcotipocomen,"TIPOCOMEN",svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_tco);
        init = 1;
    }
}

static void init_seltcovdtipocomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtipocomen[0].numcol;nc++) dvdtipocomen[0].c[nc].offset-=(size_t)&svdtipocomen;
    vdseltcovdtipocomen=abrecursordebug(SELTCOVDTIPOCOMEN,1280);
    definetodo(vdseltcovdtipocomen,svdtipocomen.rowid,sizeof(svdtipocomen.rowid),V10CADENA,
                          svdtipocomen.tablacomen,sizeof(svdtipocomen.tablacomen),V10CADENA,
                          svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen),V10CADENA,
                          svdtipocomen.destipocomen,sizeof(svdtipocomen.destipocomen),V10CADENA,
                          &svdtipocomen.orden,sizeof(svdtipocomen.orden),V10LONG,
                          &svdtipocomen.maxlineas,sizeof(svdtipocomen.maxlineas),V10LONG,
                          svdtipocomen.notificable,sizeof(svdtipocomen.notificable),V10CADENA,
                          svdtipocomen.privilegiosver,sizeof(svdtipocomen.privilegiosver),V10CADENA,
                          svdtipocomen.privilegiosmod,sizeof(svdtipocomen.privilegiosmod),V10CADENA,
                          svdtipocomen.privilegiosins,sizeof(svdtipocomen.privilegiosins),V10CADENA,
                          svdtipocomen.codopemodif,sizeof(svdtipocomen.codopemodif),V10CADENA,
                          &svdtipocomen.fecmodif,sizeof(svdtipocomen.fecmodif),V10LONG,
                          svdtipocomen.horamodif,sizeof(svdtipocomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseltcovdtipocomen,"TABLACOMEN",svdtipocomen.tablacomen,sizeof(svdtipocomen.tablacomen),V10CADENA,
                          "TIPOCOMEN",svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_tco);
        init = 1;
    }
}

static void init_instco(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtipocomen[0].numcol;nc++) dvdtipocomen[0].c[nc].offset-=(size_t)&svdtipocomen;
    vdinstco=abrecursordebug(INSTCO,1280);
    bindtodo(vdinstco,"TABLACOMEN",svdtipocomen.tablacomen,sizeof(svdtipocomen.tablacomen),V10CADENA,
                          "TIPOCOMEN",svdtipocomen.tipocomen,sizeof(svdtipocomen.tipocomen),V10CADENA,
                          "DESTIPOCOMEN",svdtipocomen.destipocomen,sizeof(svdtipocomen.destipocomen),V10CADENA,
                          "ORDEN",&svdtipocomen.orden,sizeof(svdtipocomen.orden),V10LONG,
                          "MAXLINEAS",&svdtipocomen.maxlineas,sizeof(svdtipocomen.maxlineas),V10LONG,
                          "NOTIFICABLE",svdtipocomen.notificable,sizeof(svdtipocomen.notificable),V10CADENA,
                          "PRIVILEGIOSVER",svdtipocomen.privilegiosver,sizeof(svdtipocomen.privilegiosver),V10CADENA,
                          "PRIVILEGIOSMOD",svdtipocomen.privilegiosmod,sizeof(svdtipocomen.privilegiosmod),V10CADENA,
                          "PRIVILEGIOSINS",svdtipocomen.privilegiosins,sizeof(svdtipocomen.privilegiosins),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_tco);
        init = 1;
    }
}

diccionario *TCOdamediccionario(void)
{
     return(&dtco);
}

int TCObuscatipocomen(char *tipocomen,vdtipocomens *tco)
{
  int vdret;
  memset(&svdtipocomen,0,sizeof(svdtipocomen));
  strcpy(svdtipocomen.tipocomen,tipocomen);
  if (vdseltcotipocomen==NULL) init_seltcotipocomen();
  vdret=ejefetchcursor(vdseltcotipocomen);
  if (vdret==0) {
     *tco=svdtipocomen;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseltcotipocomen. vdret %d. \n",TCOlog(&svdtipocomen),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int TCOnexttipocomen(vdtipocomens *tco)
{
  int vdret;
  vdret=fetchcursor(vdseltcotipocomen);
  if (vdret==0) {
     *tco=svdtipocomen;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseltcotipocomen. vdret %d. \n",TCOlog(&svdtipocomen),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseltcotipocomen);
  return(VD_EERRORACLE);
}

int TCOselvdtipocomen(char *tablacomen,char *tipocomen,vdtipocomens *tco)
{
  int vdret;
  if (vdseltcovdtipocomen==NULL) init_seltcovdtipocomen();
  memset(&svdtipocomen,0,sizeof(svdtipocomen));
  strcpy(svdtipocomen.tablacomen,tablacomen);
  strcpy(svdtipocomen.tipocomen,tipocomen);
  vdret=ejefetchcursor(vdseltcovdtipocomen);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseltcovdtipocomen. vdret %d. \n",TCOlog(&svdtipocomen),vdret);
    return(VD_EERRORACLE);
   }
  *tco=svdtipocomen;
  return(vdret);
}

int TCOinsert(vdtipocomens *tco,int error)
{
  int vdret;
  if (!vdinstco) init_instco();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",TCOlog(&svdtipocomen));
  svdtipocomen=*tco;
  vdret=ejecutacursor(vdinstco);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinstco);
     getcurerrornombre(vdinstco->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * TCOlog(vdtipocomens *tco)
{
    sprintf(msglogTCO, "VDTIPOCOMEN: tablacomen %s tipocomen %s ",tco->tablacomen,tco->tipocomen);
    return(msglogTCO);
}

char * TCOdebug(vdtipocomens *tco)
{
    debugestruct(&dtco,tco,msgdebugTCO);
    return(msgdebugTCO);
}

