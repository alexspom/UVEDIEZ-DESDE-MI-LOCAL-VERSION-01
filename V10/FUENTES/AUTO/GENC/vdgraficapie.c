// Modulo generado automaticamente a partir de VDGRAFICAPIE.DEF
//# M�dulo : VDGRAFICAPIE.DEF                                                        
//# Funci�n: Definici�n de colores de porciones de pastel de gr�ficas Web
//#                        
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 18-01-2010                                              
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=GRAP;
//RECORRE=NOMBREGRAF,NOMBREGRAF,ORDERBY=NUMCOLOR DESC;

#include "vd.h"
#define SELGRAPNOMBREGRAF "SELECT VDGRAFICAPIE.ROWID,VDGRAFICAPIE.NOMBREGRAF,VDGRAFICAPIE.NUMCOLOR, "\
                    " VDGRAFICAPIE.COLORPIE,VDGRAFICAPIE.VDEXTRA,VDGRAFICAPIE.CODCOMEN, "\
                    " VDGRAFICAPIE.CODOPEMODIF,VDGRAFICAPIE.FECMODIF,VDGRAFICAPIE.HORAMODIF "\
        " FROM VDGRAFICAPIE"\
        " WHERE "\
               " VDGRAFICAPIE.NOMBREGRAF=:NOMBREGRAF "\
        " ORDER BY NUMCOLOR DESC "
static v10cursors *vdselgrapnombregraf;

#define SELGRAPVDGRAFICAPIE "SELECT VDGRAFICAPIE.ROWID,VDGRAFICAPIE.NOMBREGRAF,VDGRAFICAPIE.NUMCOLOR, "\
                    " VDGRAFICAPIE.COLORPIE,VDGRAFICAPIE.VDEXTRA,VDGRAFICAPIE.CODCOMEN, "\
                    " VDGRAFICAPIE.CODOPEMODIF,VDGRAFICAPIE.FECMODIF,VDGRAFICAPIE.HORAMODIF "\
        " FROM VDGRAFICAPIE"
static v10cursors *vdselgrapvdgraficapie;

static vdgraficapies svdgraficapie;

static diccols colvdgraficapie[]={
	{"ROWID",V10CADENA,(size_t)&svdgraficapie.rowid,sizeof(svdgraficapie.rowid)},
	{"NOMBREGRAF",V10CADENA,(size_t)&svdgraficapie.nombregraf,sizeof(svdgraficapie.nombregraf)},
	{"NUMCOLOR",V10LONG,(size_t)&svdgraficapie.numcolor,sizeof(svdgraficapie.numcolor)},
	{"COLORPIE",V10CADENA,(size_t)&svdgraficapie.colorpie,sizeof(svdgraficapie.colorpie)},
	{"VDEXTRA",V10CADENA,(size_t)&svdgraficapie.vdextra,sizeof(svdgraficapie.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdgraficapie.codcomen,sizeof(svdgraficapie.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdgraficapie.codopemodif,sizeof(svdgraficapie.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdgraficapie.fecmodif,sizeof(svdgraficapie.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdgraficapie.horamodif,sizeof(svdgraficapie.horamodif)}
	};
static diccionarios dvdgraficapie[]={
    {colvdgraficapie,9}
};
diccionario dgrap={dvdgraficapie,1};

static char msglogGRAP[LCADENA];
static char msgdebugGRAP[LCADENABIG];
static int init=0;


static void fin_vd_grap(void)
{
if (vdselgrapnombregraf) {
    liberacursor(vdselgrapnombregraf);
    vdselgrapnombregraf = NULL;
}
if (vdselgrapvdgraficapie) {
    liberacursor(vdselgrapvdgraficapie);
    vdselgrapvdgraficapie = NULL;
}
}
static void init_selgrapnombregraf(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgraficapie[0].numcol;nc++) dvdgraficapie[0].c[nc].offset-=(size_t)&svdgraficapie;
    vdselgrapnombregraf=abrecursordebug(SELGRAPNOMBREGRAF,1280);
    definetodo(vdselgrapnombregraf,svdgraficapie.rowid,sizeof(svdgraficapie.rowid),V10CADENA,
                          svdgraficapie.nombregraf,sizeof(svdgraficapie.nombregraf),V10CADENA,
                          &svdgraficapie.numcolor,sizeof(svdgraficapie.numcolor),V10LONG,
                          svdgraficapie.colorpie,sizeof(svdgraficapie.colorpie),V10CADENA,
                          svdgraficapie.vdextra,sizeof(svdgraficapie.vdextra),V10CADENA,
                          &svdgraficapie.codcomen,sizeof(svdgraficapie.codcomen),V10LONG,
                          svdgraficapie.codopemodif,sizeof(svdgraficapie.codopemodif),V10CADENA,
                          &svdgraficapie.fecmodif,sizeof(svdgraficapie.fecmodif),V10LONG,
                          svdgraficapie.horamodif,sizeof(svdgraficapie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselgrapnombregraf,"NOMBREGRAF",svdgraficapie.nombregraf,sizeof(svdgraficapie.nombregraf),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_grap);
        init = 1;
    }
}

static void init_selgrapvdgraficapie(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgraficapie[0].numcol;nc++) dvdgraficapie[0].c[nc].offset-=(size_t)&svdgraficapie;
    vdselgrapvdgraficapie=abrecursordebug(SELGRAPVDGRAFICAPIE,1280);
    definetodo(vdselgrapvdgraficapie,svdgraficapie.rowid,sizeof(svdgraficapie.rowid),V10CADENA,
                          svdgraficapie.nombregraf,sizeof(svdgraficapie.nombregraf),V10CADENA,
                          &svdgraficapie.numcolor,sizeof(svdgraficapie.numcolor),V10LONG,
                          svdgraficapie.colorpie,sizeof(svdgraficapie.colorpie),V10CADENA,
                          svdgraficapie.vdextra,sizeof(svdgraficapie.vdextra),V10CADENA,
                          &svdgraficapie.codcomen,sizeof(svdgraficapie.codcomen),V10LONG,
                          svdgraficapie.codopemodif,sizeof(svdgraficapie.codopemodif),V10CADENA,
                          &svdgraficapie.fecmodif,sizeof(svdgraficapie.fecmodif),V10LONG,
                          svdgraficapie.horamodif,sizeof(svdgraficapie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselgrapvdgraficapie,NULL);
    if (init == 0) {
        atexit(fin_vd_grap);
        init = 1;
    }
}

diccionario *GRAPdamediccionario(void)
{
     return(&dgrap);
}

int GRAPbuscanombregraf(char *nombregraf,vdgraficapies *grap)
{
  int vdret;
  memset(&svdgraficapie,0,sizeof(svdgraficapie));
  strcpy(svdgraficapie.nombregraf,nombregraf);
  if (vdselgrapnombregraf==NULL) init_selgrapnombregraf();
  vdret=ejefetchcursor(vdselgrapnombregraf);
  if (vdret==0) {
     *grap=svdgraficapie;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselgrapnombregraf. vdret %d. \n",GRAPlog(&svdgraficapie),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int GRAPnextnombregraf(vdgraficapies *grap)
{
  int vdret;
  vdret=fetchcursor(vdselgrapnombregraf);
  if (vdret==0) {
     *grap=svdgraficapie;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselgrapnombregraf. vdret %d. \n",GRAPlog(&svdgraficapie),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselgrapnombregraf);
  return(VD_EERRORACLE);
}

int GRAPselvdgraficapie(vdgraficapies *grap)
{
  int vdret;
  if (vdselgrapvdgraficapie==NULL) init_selgrapvdgraficapie();
  memset(&svdgraficapie,0,sizeof(svdgraficapie));
  vdret=ejefetchcursor(vdselgrapvdgraficapie);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselgrapvdgraficapie. vdret %d. \n",GRAPlog(&svdgraficapie),vdret);
    return(VD_EERRORACLE);
   }
  *grap=svdgraficapie;
  return(vdret);
}

char * GRAPlog(vdgraficapies *grap)
{
    sprintf(msglogGRAP, "VDGRAFICAPIE: ");
    return(msglogGRAP);
}

char * GRAPdebug(vdgraficapies *grap)
{
    debugestruct(&dgrap,grap,msgdebugGRAP);
    return(msgdebugGRAP);
}

