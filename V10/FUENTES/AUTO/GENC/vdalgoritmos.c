// Modulo generado automaticamente a partir de VDALGORITMOS.DEF
//#***
//# VDALGORITMOS.c - Generación automática del código c para la tabla VDCOMEN
//#
//# Propósito: Funciones de acceso a la tabla VDALGORITMOS
//#
//# Autor	 : JCSR
//# Revisado por:
//# Fecha  : 24-01-2008
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=ALG
//PRIMARIA=PROCESO,NOMBREALG
//RECORRE=ALGORITMO,PROCESO,ACTIVO
//CLAVE=ALGPROC, PROCESO, NOMBREALG

#include "vd.h"
#define SELALGALGORITMO "SELECT VDALGORITMOS.ROWID,VDALGORITMOS.PROCESO,VDALGORITMOS.NOMBREALG, "\
                    " VDALGORITMOS.DESALG,VDALGORITMOS.DISCRIMINANTE,VDALGORITMOS.PARAMALG, "\
                    " VDALGORITMOS.FUNCIONALG,VDALGORITMOS.LIBALGORITMO,VDALGORITMOS.ACTIVO, "\
                    " VDALGORITMOS.INFOEXTRA,VDALGORITMOS.CODCOMEN,VDALGORITMOS.CODOPEMODIF, "\
                    " VDALGORITMOS.FECMODIF,VDALGORITMOS.HORAMODIF "\
        " FROM VDALGORITMOS"\
        " WHERE "\
               " VDALGORITMOS.PROCESO=:PROCESO "\
               " AND VDALGORITMOS.ACTIVO=:ACTIVO "
static v10cursors *vdselalgalgoritmo;

#define SELALGALGPROC "SELECT VDALGORITMOS.ROWID,VDALGORITMOS.PROCESO,VDALGORITMOS.NOMBREALG, "\
                    " VDALGORITMOS.DESALG,VDALGORITMOS.DISCRIMINANTE,VDALGORITMOS.PARAMALG, "\
                    " VDALGORITMOS.FUNCIONALG,VDALGORITMOS.LIBALGORITMO,VDALGORITMOS.ACTIVO, "\
                    " VDALGORITMOS.INFOEXTRA,VDALGORITMOS.CODCOMEN,VDALGORITMOS.CODOPEMODIF, "\
                    " VDALGORITMOS.FECMODIF,VDALGORITMOS.HORAMODIF "\
        " FROM VDALGORITMOS"\
        " WHERE "\
               " VDALGORITMOS.PROCESO=:PROCESO "\
               " AND VDALGORITMOS.NOMBREALG=:NOMBREALG "
static v10cursors *vdselalgalgproc;

#define SELALGVDALGORITMOS "SELECT VDALGORITMOS.ROWID,VDALGORITMOS.PROCESO,VDALGORITMOS.NOMBREALG, "\
                    " VDALGORITMOS.DESALG,VDALGORITMOS.DISCRIMINANTE,VDALGORITMOS.PARAMALG, "\
                    " VDALGORITMOS.FUNCIONALG,VDALGORITMOS.LIBALGORITMO,VDALGORITMOS.ACTIVO, "\
                    " VDALGORITMOS.INFOEXTRA,VDALGORITMOS.CODCOMEN,VDALGORITMOS.CODOPEMODIF, "\
                    " VDALGORITMOS.FECMODIF,VDALGORITMOS.HORAMODIF "\
        " FROM VDALGORITMOS"\
        " WHERE "\
               " VDALGORITMOS.PROCESO=:PROCESO "\
               " AND VDALGORITMOS.NOMBREALG=:NOMBREALG "
static v10cursors *vdselalgvdalgoritmos;

static vdalgoritmoss svdalgoritmos;

static diccols colvdalgoritmos[]={
	{"ROWID",V10CADENA,(size_t)&svdalgoritmos.rowid,sizeof(svdalgoritmos.rowid)},
	{"PROCESO",V10CADENA,(size_t)&svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso)},
	{"NOMBREALG",V10CADENA,(size_t)&svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg)},
	{"DESALG",V10CADENA,(size_t)&svdalgoritmos.desalg,sizeof(svdalgoritmos.desalg)},
	{"DISCRIMINANTE",V10CADENA,(size_t)&svdalgoritmos.discriminante,sizeof(svdalgoritmos.discriminante)},
	{"PARAMALG",V10CADENA,(size_t)&svdalgoritmos.paramalg,sizeof(svdalgoritmos.paramalg)},
	{"FUNCIONALG",V10CADENA,(size_t)&svdalgoritmos.funcionalg,sizeof(svdalgoritmos.funcionalg)},
	{"LIBALGORITMO",V10CADENA,(size_t)&svdalgoritmos.libalgoritmo,sizeof(svdalgoritmos.libalgoritmo)},
	{"ACTIVO",V10CADENA,(size_t)&svdalgoritmos.activo,sizeof(svdalgoritmos.activo)},
	{"INFOEXTRA",V10CADENA,(size_t)&svdalgoritmos.infoextra,sizeof(svdalgoritmos.infoextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdalgoritmos.codcomen,sizeof(svdalgoritmos.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdalgoritmos.codopemodif,sizeof(svdalgoritmos.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdalgoritmos.fecmodif,sizeof(svdalgoritmos.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdalgoritmos.horamodif,sizeof(svdalgoritmos.horamodif)}
	};
static diccionarios dvdalgoritmos[]={
    {colvdalgoritmos,14}
};
diccionario dalg={dvdalgoritmos,1};

static char msglogALG[LCADENA];
static char msgdebugALG[LCADENABIG];
static int init=0;


static void fin_vd_alg(void)
{
if (vdselalgalgoritmo) {
    liberacursor(vdselalgalgoritmo);
    vdselalgalgoritmo = NULL;
}
if (vdselalgalgproc) {
    liberacursor(vdselalgalgproc);
    vdselalgalgproc = NULL;
}
if (vdselalgvdalgoritmos) {
    liberacursor(vdselalgvdalgoritmos);
    vdselalgvdalgoritmos = NULL;
}
}
static void init_selalgalgoritmo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdalgoritmos[0].numcol;nc++) dvdalgoritmos[0].c[nc].offset-=(size_t)&svdalgoritmos;
    vdselalgalgoritmo=abrecursordebug(SELALGALGORITMO,1280);
    definetodo(vdselalgalgoritmo,svdalgoritmos.rowid,sizeof(svdalgoritmos.rowid),V10CADENA,
                          svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg),V10CADENA,
                          svdalgoritmos.desalg,sizeof(svdalgoritmos.desalg),V10CADENA,
                          svdalgoritmos.discriminante,sizeof(svdalgoritmos.discriminante),V10CADENA,
                          svdalgoritmos.paramalg,sizeof(svdalgoritmos.paramalg),V10CADENA,
                          svdalgoritmos.funcionalg,sizeof(svdalgoritmos.funcionalg),V10CADENA,
                          svdalgoritmos.libalgoritmo,sizeof(svdalgoritmos.libalgoritmo),V10CADENA,
                          svdalgoritmos.activo,sizeof(svdalgoritmos.activo),V10CADENA,
                          svdalgoritmos.infoextra,sizeof(svdalgoritmos.infoextra),V10CADENA,
                          &svdalgoritmos.codcomen,sizeof(svdalgoritmos.codcomen),V10LONG,
                          svdalgoritmos.codopemodif,sizeof(svdalgoritmos.codopemodif),V10CADENA,
                          &svdalgoritmos.fecmodif,sizeof(svdalgoritmos.fecmodif),V10LONG,
                          svdalgoritmos.horamodif,sizeof(svdalgoritmos.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselalgalgoritmo,"PROCESO",svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          "ACTIVO",svdalgoritmos.activo,sizeof(svdalgoritmos.activo),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_alg);
        init = 1;
    }
}

static void init_selalgalgproc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdalgoritmos[0].numcol;nc++) dvdalgoritmos[0].c[nc].offset-=(size_t)&svdalgoritmos;
    vdselalgalgproc=abrecursordebug(SELALGALGPROC,1280);
    definetodo(vdselalgalgproc,svdalgoritmos.rowid,sizeof(svdalgoritmos.rowid),V10CADENA,
                          svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg),V10CADENA,
                          svdalgoritmos.desalg,sizeof(svdalgoritmos.desalg),V10CADENA,
                          svdalgoritmos.discriminante,sizeof(svdalgoritmos.discriminante),V10CADENA,
                          svdalgoritmos.paramalg,sizeof(svdalgoritmos.paramalg),V10CADENA,
                          svdalgoritmos.funcionalg,sizeof(svdalgoritmos.funcionalg),V10CADENA,
                          svdalgoritmos.libalgoritmo,sizeof(svdalgoritmos.libalgoritmo),V10CADENA,
                          svdalgoritmos.activo,sizeof(svdalgoritmos.activo),V10CADENA,
                          svdalgoritmos.infoextra,sizeof(svdalgoritmos.infoextra),V10CADENA,
                          &svdalgoritmos.codcomen,sizeof(svdalgoritmos.codcomen),V10LONG,
                          svdalgoritmos.codopemodif,sizeof(svdalgoritmos.codopemodif),V10CADENA,
                          &svdalgoritmos.fecmodif,sizeof(svdalgoritmos.fecmodif),V10LONG,
                          svdalgoritmos.horamodif,sizeof(svdalgoritmos.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselalgalgproc,"PROCESO",svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          "NOMBREALG",svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_alg);
        init = 1;
    }
}

static void init_selalgvdalgoritmos(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdalgoritmos[0].numcol;nc++) dvdalgoritmos[0].c[nc].offset-=(size_t)&svdalgoritmos;
    vdselalgvdalgoritmos=abrecursordebug(SELALGVDALGORITMOS,1280);
    definetodo(vdselalgvdalgoritmos,svdalgoritmos.rowid,sizeof(svdalgoritmos.rowid),V10CADENA,
                          svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg),V10CADENA,
                          svdalgoritmos.desalg,sizeof(svdalgoritmos.desalg),V10CADENA,
                          svdalgoritmos.discriminante,sizeof(svdalgoritmos.discriminante),V10CADENA,
                          svdalgoritmos.paramalg,sizeof(svdalgoritmos.paramalg),V10CADENA,
                          svdalgoritmos.funcionalg,sizeof(svdalgoritmos.funcionalg),V10CADENA,
                          svdalgoritmos.libalgoritmo,sizeof(svdalgoritmos.libalgoritmo),V10CADENA,
                          svdalgoritmos.activo,sizeof(svdalgoritmos.activo),V10CADENA,
                          svdalgoritmos.infoextra,sizeof(svdalgoritmos.infoextra),V10CADENA,
                          &svdalgoritmos.codcomen,sizeof(svdalgoritmos.codcomen),V10LONG,
                          svdalgoritmos.codopemodif,sizeof(svdalgoritmos.codopemodif),V10CADENA,
                          &svdalgoritmos.fecmodif,sizeof(svdalgoritmos.fecmodif),V10LONG,
                          svdalgoritmos.horamodif,sizeof(svdalgoritmos.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselalgvdalgoritmos,"PROCESO",svdalgoritmos.proceso,sizeof(svdalgoritmos.proceso),V10CADENA,
                          "NOMBREALG",svdalgoritmos.nombrealg,sizeof(svdalgoritmos.nombrealg),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_alg);
        init = 1;
    }
}

diccionario *ALGdamediccionario(void)
{
     return(&dalg);
}

int ALGbuscaalgoritmo(char *proceso,char *activo,vdalgoritmoss *alg)
{
  int vdret;
  memset(&svdalgoritmos,0,sizeof(svdalgoritmos));
  strcpy(svdalgoritmos.proceso,proceso);
  strcpy(svdalgoritmos.activo,activo);
  if (vdselalgalgoritmo==NULL) init_selalgalgoritmo();
  vdret=ejefetchcursor(vdselalgalgoritmo);
  if (vdret==0) {
     *alg=svdalgoritmos;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselalgalgoritmo. vdret %d. \n",ALGlog(&svdalgoritmos),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ALGnextalgoritmo(vdalgoritmoss *alg)
{
  int vdret;
  vdret=fetchcursor(vdselalgalgoritmo);
  if (vdret==0) {
     *alg=svdalgoritmos;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselalgalgoritmo. vdret %d. \n",ALGlog(&svdalgoritmos),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselalgalgoritmo);
  return(VD_EERRORACLE);
}

int ALGselalgproc(char *proceso,char *nombrealg,vdalgoritmoss *alg)
{
  int vdret;
  if (vdselalgalgproc==NULL) init_selalgalgproc();
  memset(&svdalgoritmos,0,sizeof(svdalgoritmos));
  strcpy(svdalgoritmos.proceso,proceso);
  strcpy(svdalgoritmos.nombrealg,nombrealg);
  vdret=ejefetchcursor(vdselalgalgproc);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselalgalgproc. vdret %d. \n",ALGlog(&svdalgoritmos),vdret);
    return(VD_EERRORACLE);
   }
  *alg=svdalgoritmos;
  return(vdret);
}

int ALGselvdalgoritmos(char *proceso,char *nombrealg,vdalgoritmoss *alg)
{
  int vdret;
  if (vdselalgvdalgoritmos==NULL) init_selalgvdalgoritmos();
  memset(&svdalgoritmos,0,sizeof(svdalgoritmos));
  strcpy(svdalgoritmos.proceso,proceso);
  strcpy(svdalgoritmos.nombrealg,nombrealg);
  vdret=ejefetchcursor(vdselalgvdalgoritmos);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselalgvdalgoritmos. vdret %d. \n",ALGlog(&svdalgoritmos),vdret);
    return(VD_EERRORACLE);
   }
  *alg=svdalgoritmos;
  return(vdret);
}

char * ALGlog(vdalgoritmoss *alg)
{
    sprintf(msglogALG, "VDALGORITMOS: proceso %s nombrealg %s ",alg->proceso,alg->nombrealg);
    return(msglogALG);
}

char * ALGdebug(vdalgoritmoss *alg)
{
    debugestruct(&dalg,alg,msgdebugALG);
    return(msgdebugALG);
}

