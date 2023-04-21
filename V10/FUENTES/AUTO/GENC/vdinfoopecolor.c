// Modulo generado automaticamente a partir de VDINFOOPECOLOR.DEF
//# Modulo : VDINFOOPECOLOR.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFOOPECOLOR
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 20-01-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IOC;
//EXTRA=CODZONA,V10LONG;
//
//RECORRE=COLOR,CODOPE,WHERE=NOT EXISTS (SELECT CODZONA FROM VDBULTOZONA WHERE CODZONA=:CODZONA AND COLOROPE=VDINFOOPECOLOR.COLOROPE) ORDER BY PRIORIDAD;
//RECORRE=COLOROPE,CODOPE,ORDERBY=PRIORIDAD;

#include "vd.h"
#define SELIOCCOLOR "SELECT VDINFOOPECOLOR.ROWID,VDINFOOPECOLOR.CODOPE,VDINFOOPECOLOR.PRIORIDAD, "\
                    " VDINFOOPECOLOR.COLOROPE,VDINFOOPECOLOR.VDEXTRA,VDINFOOPECOLOR.CODOPEMODIF, "\
                    " VDINFOOPECOLOR.FECMODIF,VDINFOOPECOLOR.HORAMODIF,VDINFOOPECOLOR.CODCOMEN "\
        " FROM VDINFOOPECOLOR"\
        " WHERE "\
               " VDINFOOPECOLOR.CODOPE=:CODOPE "\
              "  AND NOT EXISTS (SELECT CODZONA FROM VDBULTOZONA WHERE CODZONA=:CODZONA AND COLOROPE=VDINFOOPECOLOR.COLOROPE) ORDER BY PRIORIDAD "
static v10cursors *vdselioccolor;

#define SELIOCCOLOROPE "SELECT VDINFOOPECOLOR.ROWID,VDINFOOPECOLOR.CODOPE,VDINFOOPECOLOR.PRIORIDAD, "\
                    " VDINFOOPECOLOR.COLOROPE,VDINFOOPECOLOR.VDEXTRA,VDINFOOPECOLOR.CODOPEMODIF, "\
                    " VDINFOOPECOLOR.FECMODIF,VDINFOOPECOLOR.HORAMODIF,VDINFOOPECOLOR.CODCOMEN "\
        " FROM VDINFOOPECOLOR"\
        " WHERE "\
               " VDINFOOPECOLOR.CODOPE=:CODOPE "\
        " ORDER BY PRIORIDAD "
static v10cursors *vdselioccolorope;

#define SELIOCVDINFOOPECOLOR "SELECT VDINFOOPECOLOR.ROWID,VDINFOOPECOLOR.CODOPE,VDINFOOPECOLOR.PRIORIDAD, "\
                    " VDINFOOPECOLOR.COLOROPE,VDINFOOPECOLOR.VDEXTRA,VDINFOOPECOLOR.CODOPEMODIF, "\
                    " VDINFOOPECOLOR.FECMODIF,VDINFOOPECOLOR.HORAMODIF,VDINFOOPECOLOR.CODCOMEN "\
        " FROM VDINFOOPECOLOR"\
        " WHERE "\
               " VDINFOOPECOLOR.CODOPE=:CODOPE "\
               " AND VDINFOOPECOLOR.COLOROPE=:COLOROPE "
static v10cursors *vdseliocvdinfoopecolor;

static vdinfoopecolors svdinfoopecolor;

static diccols colvdinfoopecolor[]={
	{"ROWID",V10CADENA,(size_t)&svdinfoopecolor.rowid,sizeof(svdinfoopecolor.rowid)},
	{"CODOPE",V10CADENA,(size_t)&svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope)},
	{"PRIORIDAD",V10LONG,(size_t)&svdinfoopecolor.prioridad,sizeof(svdinfoopecolor.prioridad)},
	{"COLOROPE",V10CADENA,(size_t)&svdinfoopecolor.colorope,sizeof(svdinfoopecolor.colorope)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfoopecolor.vdextra,sizeof(svdinfoopecolor.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfoopecolor.codopemodif,sizeof(svdinfoopecolor.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfoopecolor.fecmodif,sizeof(svdinfoopecolor.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfoopecolor.horamodif,sizeof(svdinfoopecolor.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfoopecolor.codcomen,sizeof(svdinfoopecolor.codcomen)},
	{"CODZONA",V10LONG,(size_t)&svdinfoopecolor.codzona,sizeof(svdinfoopecolor.codzona)}
	};
static diccionarios dvdinfoopecolor[]={
    {colvdinfoopecolor,10}
};
diccionario dioc={dvdinfoopecolor,1};

static char msglogIOC[LCADENA];
static char msgdebugIOC[LCADENABIG];
static int init=0;


static void fin_vd_ioc(void)
{
if (vdselioccolor) {
    liberacursor(vdselioccolor);
    vdselioccolor = NULL;
}
if (vdselioccolorope) {
    liberacursor(vdselioccolorope);
    vdselioccolorope = NULL;
}
if (vdseliocvdinfoopecolor) {
    liberacursor(vdseliocvdinfoopecolor);
    vdseliocvdinfoopecolor = NULL;
}
}
static void init_selioccolor(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoopecolor[0].numcol;nc++) dvdinfoopecolor[0].c[nc].offset-=(size_t)&svdinfoopecolor;
    vdselioccolor=abrecursordebug(SELIOCCOLOR,1280);
    definetodo(vdselioccolor,svdinfoopecolor.rowid,sizeof(svdinfoopecolor.rowid),V10CADENA,
                          svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          &svdinfoopecolor.prioridad,sizeof(svdinfoopecolor.prioridad),V10LONG,
                          svdinfoopecolor.colorope,sizeof(svdinfoopecolor.colorope),V10CADENA,
                          svdinfoopecolor.vdextra,sizeof(svdinfoopecolor.vdextra),V10CADENA,
                          svdinfoopecolor.codopemodif,sizeof(svdinfoopecolor.codopemodif),V10CADENA,
                          &svdinfoopecolor.fecmodif,sizeof(svdinfoopecolor.fecmodif),V10LONG,
                          svdinfoopecolor.horamodif,sizeof(svdinfoopecolor.horamodif),V10CADENA,
                          &svdinfoopecolor.codcomen,sizeof(svdinfoopecolor.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselioccolor,"CODOPE",svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          "CODZONA",&svdinfoopecolor.codzona,sizeof(svdinfoopecolor.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ioc);
        init = 1;
    }
}

static void init_selioccolorope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoopecolor[0].numcol;nc++) dvdinfoopecolor[0].c[nc].offset-=(size_t)&svdinfoopecolor;
    vdselioccolorope=abrecursordebug(SELIOCCOLOROPE,1280);
    definetodo(vdselioccolorope,svdinfoopecolor.rowid,sizeof(svdinfoopecolor.rowid),V10CADENA,
                          svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          &svdinfoopecolor.prioridad,sizeof(svdinfoopecolor.prioridad),V10LONG,
                          svdinfoopecolor.colorope,sizeof(svdinfoopecolor.colorope),V10CADENA,
                          svdinfoopecolor.vdextra,sizeof(svdinfoopecolor.vdextra),V10CADENA,
                          svdinfoopecolor.codopemodif,sizeof(svdinfoopecolor.codopemodif),V10CADENA,
                          &svdinfoopecolor.fecmodif,sizeof(svdinfoopecolor.fecmodif),V10LONG,
                          svdinfoopecolor.horamodif,sizeof(svdinfoopecolor.horamodif),V10CADENA,
                          &svdinfoopecolor.codcomen,sizeof(svdinfoopecolor.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselioccolorope,"CODOPE",svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ioc);
        init = 1;
    }
}

static void init_seliocvdinfoopecolor(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoopecolor[0].numcol;nc++) dvdinfoopecolor[0].c[nc].offset-=(size_t)&svdinfoopecolor;
    vdseliocvdinfoopecolor=abrecursordebug(SELIOCVDINFOOPECOLOR,1280);
    definetodo(vdseliocvdinfoopecolor,svdinfoopecolor.rowid,sizeof(svdinfoopecolor.rowid),V10CADENA,
                          svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          &svdinfoopecolor.prioridad,sizeof(svdinfoopecolor.prioridad),V10LONG,
                          svdinfoopecolor.colorope,sizeof(svdinfoopecolor.colorope),V10CADENA,
                          svdinfoopecolor.vdextra,sizeof(svdinfoopecolor.vdextra),V10CADENA,
                          svdinfoopecolor.codopemodif,sizeof(svdinfoopecolor.codopemodif),V10CADENA,
                          &svdinfoopecolor.fecmodif,sizeof(svdinfoopecolor.fecmodif),V10LONG,
                          svdinfoopecolor.horamodif,sizeof(svdinfoopecolor.horamodif),V10CADENA,
                          &svdinfoopecolor.codcomen,sizeof(svdinfoopecolor.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliocvdinfoopecolor,"CODOPE",svdinfoopecolor.codope,sizeof(svdinfoopecolor.codope),V10CADENA,
                          "COLOROPE",svdinfoopecolor.colorope,sizeof(svdinfoopecolor.colorope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ioc);
        init = 1;
    }
}

diccionario *IOCdamediccionario(void)
{
     return(&dioc);
}

int IOCbuscacolor(char *codope,long codzona,vdinfoopecolors *ioc)
{
  int vdret;
  memset(&svdinfoopecolor,0,sizeof(svdinfoopecolor));
  strcpy(svdinfoopecolor.codope,codope);
  svdinfoopecolor.codzona=codzona;
  if (vdselioccolor==NULL) init_selioccolor();
  vdret=ejefetchcursor(vdselioccolor);
  if (vdret==0) {
     *ioc=svdinfoopecolor;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselioccolor. vdret %d. \n",IOClog(&svdinfoopecolor),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IOCnextcolor(vdinfoopecolors *ioc)
{
  int vdret;
  vdret=fetchcursor(vdselioccolor);
  if (vdret==0) {
     *ioc=svdinfoopecolor;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselioccolor. vdret %d. \n",IOClog(&svdinfoopecolor),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselioccolor);
  return(VD_EERRORACLE);
}

int IOCbuscacolorope(char *codope,vdinfoopecolors *ioc)
{
  int vdret;
  memset(&svdinfoopecolor,0,sizeof(svdinfoopecolor));
  strcpy(svdinfoopecolor.codope,codope);
  if (vdselioccolorope==NULL) init_selioccolorope();
  vdret=ejefetchcursor(vdselioccolorope);
  if (vdret==0) {
     *ioc=svdinfoopecolor;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselioccolorope. vdret %d. \n",IOClog(&svdinfoopecolor),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IOCnextcolorope(vdinfoopecolors *ioc)
{
  int vdret;
  vdret=fetchcursor(vdselioccolorope);
  if (vdret==0) {
     *ioc=svdinfoopecolor;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselioccolorope. vdret %d. \n",IOClog(&svdinfoopecolor),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselioccolorope);
  return(VD_EERRORACLE);
}

int IOCselvdinfoopecolor(char *codope,char *colorope,vdinfoopecolors *ioc)
{
  int vdret;
  if (vdseliocvdinfoopecolor==NULL) init_seliocvdinfoopecolor();
  memset(&svdinfoopecolor,0,sizeof(svdinfoopecolor));
  strcpy(svdinfoopecolor.codope,codope);
  strcpy(svdinfoopecolor.colorope,colorope);
  vdret=ejefetchcursor(vdseliocvdinfoopecolor);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseliocvdinfoopecolor. vdret %d. \n",IOClog(&svdinfoopecolor),vdret);
    return(VD_EERRORACLE);
   }
  *ioc=svdinfoopecolor;
  return(vdret);
}

char * IOClog(vdinfoopecolors *ioc)
{
    sprintf(msglogIOC, "VDINFOOPECOLOR: codope %s colorope %s ",ioc->codope,ioc->colorope);
    return(msglogIOC);
}

char * IOCdebug(vdinfoopecolors *ioc)
{
    debugestruct(&dioc,ioc,msgdebugIOC);
    return(msgdebugIOC);
}

