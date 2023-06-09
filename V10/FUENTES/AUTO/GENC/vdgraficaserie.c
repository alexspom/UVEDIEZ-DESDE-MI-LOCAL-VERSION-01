// Modulo generado automaticamente a partir de VDGRAFICASERIE.DEF
//# M�dulo : VDGRAFICASERIE.DEF                                                        
//# Funci�n: Definici�n de gr�ficas Web
//#                        
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 18-01-2010                                              
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=GRAS;
//RECORRE=NOMBREGRAF,NOMBREGRAF,ORDERBY=NUMSERIE;
//

#include "vd.h"
#define SELGRASNOMBREGRAF "SELECT VDGRAFICASERIE.ROWID,VDGRAFICASERIE.NOMBREGRAF,VDGRAFICASERIE.NUMSERIE, "\
                    " VDGRAFICASERIE.TIPOSERIE,VDGRAFICASERIE.CAMPOSERIE,VDGRAFICASERIE.TITULOSERIE, "\
                    " VDGRAFICASERIE.COLORVALORSERIE,VDGRAFICASERIE.ANCHOVALORSERIE,VDGRAFICASERIE.OPACIDADVALORSERIE, "\
                    " VDGRAFICASERIE.ANCHOBORDESERIE,VDGRAFICASERIE.OPACIDADBORDERSERIE,VDGRAFICASERIE.PADDINGX, "\
                    " VDGRAFICASERIE.PADDINGY,VDGRAFICASERIE.LEYENDASERIE,VDGRAFICASERIE.LEYENDAARBOL, "\
                    " VDGRAFICASERIE.AGRUPARBARRAS,VDGRAFICASERIE.ORIENTACION,VDGRAFICASERIE.TAMA�OPUNTO, "\
                    " VDGRAFICASERIE.COLORPUNTO,VDGRAFICASERIE.ANCHOBORDEPUNTO,VDGRAFICASERIE.COLORBORDEPUNTO, "\
                    " VDGRAFICASERIE.ANCHOPIE,VDGRAFICASERIE.ALTOPIE,VDGRAFICASERIE.POSICIONPIE, "\
                    " VDGRAFICASERIE.VERLABELPIE,VDGRAFICASERIE.CSSLABELPIE,VDGRAFICASERIE.VDEXTRA, "\
                    " VDGRAFICASERIE.CODCOMEN,VDGRAFICASERIE.CODOPEMODIF,VDGRAFICASERIE.FECMODIF, "\
                    " VDGRAFICASERIE.HORAMODIF "\
        " FROM VDGRAFICASERIE"\
        " WHERE "\
               " VDGRAFICASERIE.NOMBREGRAF=:NOMBREGRAF "\
        " ORDER BY NUMSERIE "
static v10cursors *vdselgrasnombregraf;

#define SELGRASVDGRAFICASERIE "SELECT VDGRAFICASERIE.ROWID,VDGRAFICASERIE.NOMBREGRAF,VDGRAFICASERIE.NUMSERIE, "\
                    " VDGRAFICASERIE.TIPOSERIE,VDGRAFICASERIE.CAMPOSERIE,VDGRAFICASERIE.TITULOSERIE, "\
                    " VDGRAFICASERIE.COLORVALORSERIE,VDGRAFICASERIE.ANCHOVALORSERIE,VDGRAFICASERIE.OPACIDADVALORSERIE, "\
                    " VDGRAFICASERIE.ANCHOBORDESERIE,VDGRAFICASERIE.OPACIDADBORDERSERIE,VDGRAFICASERIE.PADDINGX, "\
                    " VDGRAFICASERIE.PADDINGY,VDGRAFICASERIE.LEYENDASERIE,VDGRAFICASERIE.LEYENDAARBOL, "\
                    " VDGRAFICASERIE.AGRUPARBARRAS,VDGRAFICASERIE.ORIENTACION,VDGRAFICASERIE.TAMA�OPUNTO, "\
                    " VDGRAFICASERIE.COLORPUNTO,VDGRAFICASERIE.ANCHOBORDEPUNTO,VDGRAFICASERIE.COLORBORDEPUNTO, "\
                    " VDGRAFICASERIE.ANCHOPIE,VDGRAFICASERIE.ALTOPIE,VDGRAFICASERIE.POSICIONPIE, "\
                    " VDGRAFICASERIE.VERLABELPIE,VDGRAFICASERIE.CSSLABELPIE,VDGRAFICASERIE.VDEXTRA, "\
                    " VDGRAFICASERIE.CODCOMEN,VDGRAFICASERIE.CODOPEMODIF,VDGRAFICASERIE.FECMODIF, "\
                    " VDGRAFICASERIE.HORAMODIF "\
        " FROM VDGRAFICASERIE"
static v10cursors *vdselgrasvdgraficaserie;

static vdgraficaseries svdgraficaserie;

static diccols colvdgraficaserie[]={
	{"ROWID",V10CADENA,(size_t)&svdgraficaserie.rowid,sizeof(svdgraficaserie.rowid)},
	{"NOMBREGRAF",V10CADENA,(size_t)&svdgraficaserie.nombregraf,sizeof(svdgraficaserie.nombregraf)},
	{"NUMSERIE",V10LONG,(size_t)&svdgraficaserie.numserie,sizeof(svdgraficaserie.numserie)},
	{"TIPOSERIE",V10CADENA,(size_t)&svdgraficaserie.tiposerie,sizeof(svdgraficaserie.tiposerie)},
	{"CAMPOSERIE",V10CADENA,(size_t)&svdgraficaserie.camposerie,sizeof(svdgraficaserie.camposerie)},
	{"TITULOSERIE",V10CADENA,(size_t)&svdgraficaserie.tituloserie,sizeof(svdgraficaserie.tituloserie)},
	{"COLORVALORSERIE",V10CADENA,(size_t)&svdgraficaserie.colorvalorserie,sizeof(svdgraficaserie.colorvalorserie)},
	{"ANCHOVALORSERIE",V10LONG,(size_t)&svdgraficaserie.anchovalorserie,sizeof(svdgraficaserie.anchovalorserie)},
	{"OPACIDADVALORSERIE",V10LONG,(size_t)&svdgraficaserie.opacidadvalorserie,sizeof(svdgraficaserie.opacidadvalorserie)},
	{"ANCHOBORDESERIE",V10LONG,(size_t)&svdgraficaserie.anchobordeserie,sizeof(svdgraficaserie.anchobordeserie)},
	{"OPACIDADBORDERSERIE",V10LONG,(size_t)&svdgraficaserie.opacidadborderserie,sizeof(svdgraficaserie.opacidadborderserie)},
	{"PADDINGX",V10LONG,(size_t)&svdgraficaserie.paddingx,sizeof(svdgraficaserie.paddingx)},
	{"PADDINGY",V10LONG,(size_t)&svdgraficaserie.paddingy,sizeof(svdgraficaserie.paddingy)},
	{"LEYENDASERIE",V10CADENA,(size_t)&svdgraficaserie.leyendaserie,sizeof(svdgraficaserie.leyendaserie)},
	{"LEYENDAARBOL",V10CADENA,(size_t)&svdgraficaserie.leyendaarbol,sizeof(svdgraficaserie.leyendaarbol)},
	{"AGRUPARBARRAS",V10CADENA,(size_t)&svdgraficaserie.agruparbarras,sizeof(svdgraficaserie.agruparbarras)},
	{"ORIENTACION",V10CADENA,(size_t)&svdgraficaserie.orientacion,sizeof(svdgraficaserie.orientacion)},
	{"TAMA�OPUNTO",V10LONG,(size_t)&svdgraficaserie.tama�opunto,sizeof(svdgraficaserie.tama�opunto)},
	{"COLORPUNTO",V10CADENA,(size_t)&svdgraficaserie.colorpunto,sizeof(svdgraficaserie.colorpunto)},
	{"ANCHOBORDEPUNTO",V10LONG,(size_t)&svdgraficaserie.anchobordepunto,sizeof(svdgraficaserie.anchobordepunto)},
	{"COLORBORDEPUNTO",V10CADENA,(size_t)&svdgraficaserie.colorbordepunto,sizeof(svdgraficaserie.colorbordepunto)},
	{"ANCHOPIE",V10LONG,(size_t)&svdgraficaserie.anchopie,sizeof(svdgraficaserie.anchopie)},
	{"ALTOPIE",V10LONG,(size_t)&svdgraficaserie.altopie,sizeof(svdgraficaserie.altopie)},
	{"POSICIONPIE",V10CADENA,(size_t)&svdgraficaserie.posicionpie,sizeof(svdgraficaserie.posicionpie)},
	{"VERLABELPIE",V10CADENA,(size_t)&svdgraficaserie.verlabelpie,sizeof(svdgraficaserie.verlabelpie)},
	{"CSSLABELPIE",V10CADENA,(size_t)&svdgraficaserie.csslabelpie,sizeof(svdgraficaserie.csslabelpie)},
	{"VDEXTRA",V10CADENA,(size_t)&svdgraficaserie.vdextra,sizeof(svdgraficaserie.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdgraficaserie.codcomen,sizeof(svdgraficaserie.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdgraficaserie.codopemodif,sizeof(svdgraficaserie.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdgraficaserie.fecmodif,sizeof(svdgraficaserie.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdgraficaserie.horamodif,sizeof(svdgraficaserie.horamodif)}
	};
static diccionarios dvdgraficaserie[]={
    {colvdgraficaserie,31}
};
diccionario dgras={dvdgraficaserie,1};

static char msglogGRAS[LCADENA];
static char msgdebugGRAS[LCADENABIG];
static int init=0;


static void fin_vd_gras(void)
{
if (vdselgrasnombregraf) {
    liberacursor(vdselgrasnombregraf);
    vdselgrasnombregraf = NULL;
}
if (vdselgrasvdgraficaserie) {
    liberacursor(vdselgrasvdgraficaserie);
    vdselgrasvdgraficaserie = NULL;
}
}
static void init_selgrasnombregraf(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgraficaserie[0].numcol;nc++) dvdgraficaserie[0].c[nc].offset-=(size_t)&svdgraficaserie;
    vdselgrasnombregraf=abrecursordebug(SELGRASNOMBREGRAF,1280);
    definetodo(vdselgrasnombregraf,svdgraficaserie.rowid,sizeof(svdgraficaserie.rowid),V10CADENA,
                          svdgraficaserie.nombregraf,sizeof(svdgraficaserie.nombregraf),V10CADENA,
                          &svdgraficaserie.numserie,sizeof(svdgraficaserie.numserie),V10LONG,
                          svdgraficaserie.tiposerie,sizeof(svdgraficaserie.tiposerie),V10CADENA,
                          svdgraficaserie.camposerie,sizeof(svdgraficaserie.camposerie),V10CADENA,
                          svdgraficaserie.tituloserie,sizeof(svdgraficaserie.tituloserie),V10CADENA,
                          svdgraficaserie.colorvalorserie,sizeof(svdgraficaserie.colorvalorserie),V10CADENA,
                          &svdgraficaserie.anchovalorserie,sizeof(svdgraficaserie.anchovalorserie),V10LONG,
                          &svdgraficaserie.opacidadvalorserie,sizeof(svdgraficaserie.opacidadvalorserie),V10LONG,
                          &svdgraficaserie.anchobordeserie,sizeof(svdgraficaserie.anchobordeserie),V10LONG,
                          &svdgraficaserie.opacidadborderserie,sizeof(svdgraficaserie.opacidadborderserie),V10LONG,
                          &svdgraficaserie.paddingx,sizeof(svdgraficaserie.paddingx),V10LONG,
                          &svdgraficaserie.paddingy,sizeof(svdgraficaserie.paddingy),V10LONG,
                          svdgraficaserie.leyendaserie,sizeof(svdgraficaserie.leyendaserie),V10CADENA,
                          svdgraficaserie.leyendaarbol,sizeof(svdgraficaserie.leyendaarbol),V10CADENA,
                          svdgraficaserie.agruparbarras,sizeof(svdgraficaserie.agruparbarras),V10CADENA,
                          svdgraficaserie.orientacion,sizeof(svdgraficaserie.orientacion),V10CADENA,
                          &svdgraficaserie.tama�opunto,sizeof(svdgraficaserie.tama�opunto),V10LONG,
                          svdgraficaserie.colorpunto,sizeof(svdgraficaserie.colorpunto),V10CADENA,
                          &svdgraficaserie.anchobordepunto,sizeof(svdgraficaserie.anchobordepunto),V10LONG,
                          svdgraficaserie.colorbordepunto,sizeof(svdgraficaserie.colorbordepunto),V10CADENA,
                          &svdgraficaserie.anchopie,sizeof(svdgraficaserie.anchopie),V10LONG,
                          &svdgraficaserie.altopie,sizeof(svdgraficaserie.altopie),V10LONG,
                          svdgraficaserie.posicionpie,sizeof(svdgraficaserie.posicionpie),V10CADENA,
                          svdgraficaserie.verlabelpie,sizeof(svdgraficaserie.verlabelpie),V10CADENA,
                          svdgraficaserie.csslabelpie,sizeof(svdgraficaserie.csslabelpie),V10CADENA,
                          svdgraficaserie.vdextra,sizeof(svdgraficaserie.vdextra),V10CADENA,
                          &svdgraficaserie.codcomen,sizeof(svdgraficaserie.codcomen),V10LONG,
                          svdgraficaserie.codopemodif,sizeof(svdgraficaserie.codopemodif),V10CADENA,
                          &svdgraficaserie.fecmodif,sizeof(svdgraficaserie.fecmodif),V10LONG,
                          svdgraficaserie.horamodif,sizeof(svdgraficaserie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselgrasnombregraf,"NOMBREGRAF",svdgraficaserie.nombregraf,sizeof(svdgraficaserie.nombregraf),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_gras);
        init = 1;
    }
}

static void init_selgrasvdgraficaserie(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdgraficaserie[0].numcol;nc++) dvdgraficaserie[0].c[nc].offset-=(size_t)&svdgraficaserie;
    vdselgrasvdgraficaserie=abrecursordebug(SELGRASVDGRAFICASERIE,1280);
    definetodo(vdselgrasvdgraficaserie,svdgraficaserie.rowid,sizeof(svdgraficaserie.rowid),V10CADENA,
                          svdgraficaserie.nombregraf,sizeof(svdgraficaserie.nombregraf),V10CADENA,
                          &svdgraficaserie.numserie,sizeof(svdgraficaserie.numserie),V10LONG,
                          svdgraficaserie.tiposerie,sizeof(svdgraficaserie.tiposerie),V10CADENA,
                          svdgraficaserie.camposerie,sizeof(svdgraficaserie.camposerie),V10CADENA,
                          svdgraficaserie.tituloserie,sizeof(svdgraficaserie.tituloserie),V10CADENA,
                          svdgraficaserie.colorvalorserie,sizeof(svdgraficaserie.colorvalorserie),V10CADENA,
                          &svdgraficaserie.anchovalorserie,sizeof(svdgraficaserie.anchovalorserie),V10LONG,
                          &svdgraficaserie.opacidadvalorserie,sizeof(svdgraficaserie.opacidadvalorserie),V10LONG,
                          &svdgraficaserie.anchobordeserie,sizeof(svdgraficaserie.anchobordeserie),V10LONG,
                          &svdgraficaserie.opacidadborderserie,sizeof(svdgraficaserie.opacidadborderserie),V10LONG,
                          &svdgraficaserie.paddingx,sizeof(svdgraficaserie.paddingx),V10LONG,
                          &svdgraficaserie.paddingy,sizeof(svdgraficaserie.paddingy),V10LONG,
                          svdgraficaserie.leyendaserie,sizeof(svdgraficaserie.leyendaserie),V10CADENA,
                          svdgraficaserie.leyendaarbol,sizeof(svdgraficaserie.leyendaarbol),V10CADENA,
                          svdgraficaserie.agruparbarras,sizeof(svdgraficaserie.agruparbarras),V10CADENA,
                          svdgraficaserie.orientacion,sizeof(svdgraficaserie.orientacion),V10CADENA,
                          &svdgraficaserie.tama�opunto,sizeof(svdgraficaserie.tama�opunto),V10LONG,
                          svdgraficaserie.colorpunto,sizeof(svdgraficaserie.colorpunto),V10CADENA,
                          &svdgraficaserie.anchobordepunto,sizeof(svdgraficaserie.anchobordepunto),V10LONG,
                          svdgraficaserie.colorbordepunto,sizeof(svdgraficaserie.colorbordepunto),V10CADENA,
                          &svdgraficaserie.anchopie,sizeof(svdgraficaserie.anchopie),V10LONG,
                          &svdgraficaserie.altopie,sizeof(svdgraficaserie.altopie),V10LONG,
                          svdgraficaserie.posicionpie,sizeof(svdgraficaserie.posicionpie),V10CADENA,
                          svdgraficaserie.verlabelpie,sizeof(svdgraficaserie.verlabelpie),V10CADENA,
                          svdgraficaserie.csslabelpie,sizeof(svdgraficaserie.csslabelpie),V10CADENA,
                          svdgraficaserie.vdextra,sizeof(svdgraficaserie.vdextra),V10CADENA,
                          &svdgraficaserie.codcomen,sizeof(svdgraficaserie.codcomen),V10LONG,
                          svdgraficaserie.codopemodif,sizeof(svdgraficaserie.codopemodif),V10CADENA,
                          &svdgraficaserie.fecmodif,sizeof(svdgraficaserie.fecmodif),V10LONG,
                          svdgraficaserie.horamodif,sizeof(svdgraficaserie.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselgrasvdgraficaserie,NULL);
    if (init == 0) {
        atexit(fin_vd_gras);
        init = 1;
    }
}

diccionario *GRASdamediccionario(void)
{
     return(&dgras);
}

int GRASbuscanombregraf(char *nombregraf,vdgraficaseries *gras)
{
  int vdret;
  memset(&svdgraficaserie,0,sizeof(svdgraficaserie));
  strcpy(svdgraficaserie.nombregraf,nombregraf);
  if (vdselgrasnombregraf==NULL) init_selgrasnombregraf();
  vdret=ejefetchcursor(vdselgrasnombregraf);
  if (vdret==0) {
     *gras=svdgraficaserie;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselgrasnombregraf. vdret %d. \n",GRASlog(&svdgraficaserie),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int GRASnextnombregraf(vdgraficaseries *gras)
{
  int vdret;
  vdret=fetchcursor(vdselgrasnombregraf);
  if (vdret==0) {
     *gras=svdgraficaserie;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselgrasnombregraf. vdret %d. \n",GRASlog(&svdgraficaserie),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselgrasnombregraf);
  return(VD_EERRORACLE);
}

int GRASselvdgraficaserie(vdgraficaseries *gras)
{
  int vdret;
  if (vdselgrasvdgraficaserie==NULL) init_selgrasvdgraficaserie();
  memset(&svdgraficaserie,0,sizeof(svdgraficaserie));
  vdret=ejefetchcursor(vdselgrasvdgraficaserie);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselgrasvdgraficaserie. vdret %d. \n",GRASlog(&svdgraficaserie),vdret);
    return(VD_EERRORACLE);
   }
  *gras=svdgraficaserie;
  return(vdret);
}

char * GRASlog(vdgraficaseries *gras)
{
    sprintf(msglogGRAS, "VDGRAFICASERIE: ");
    return(msglogGRAS);
}

char * GRASdebug(vdgraficaseries *gras)
{
    debugestruct(&dgras,gras,msgdebugGRAS);
    return(msgdebugGRAS);
}

