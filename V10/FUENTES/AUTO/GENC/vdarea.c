// Modulo generado automaticamente a partir de VDAREA.DEF
//#***
//# VDAREA.c - Generación automática del código c para la tabla de Áreas                                                    
//# 
//# Propósito: Funciones de acceso a la tabla VDAREA
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 06-03-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=ARE

#include "vd.h"
#define SELAREVDAREA "SELECT VDAREA.ROWID,VDAREA.CODAREA,VDAREA.CODALM, "\
                    " VDAREA.DESAREA,VDAREA.ORDENAREA,VDAREA.CODAREAREF, "\
                    " VDAREA.CODOPEMODIF,VDAREA.FECMODIF,VDAREA.HORAMODIF, "\
                    " VDAREA.CODCOMEN "\
        " FROM VDAREA"\
        " WHERE "\
               " VDAREA.CODAREA=:CODAREA "
static v10cursors *vdselarevdarea;

static vdareas svdarea;

static diccols colvdarea[]={
	{"ROWID",V10CADENA,(size_t)&svdarea.rowid,sizeof(svdarea.rowid)},
	{"CODAREA",V10CADENA,(size_t)&svdarea.codarea,sizeof(svdarea.codarea)},
	{"CODALM",V10CADENA,(size_t)&svdarea.codalm,sizeof(svdarea.codalm)},
	{"DESAREA",V10CADENA,(size_t)&svdarea.desarea,sizeof(svdarea.desarea)},
	{"ORDENAREA",V10LONG,(size_t)&svdarea.ordenarea,sizeof(svdarea.ordenarea)},
	{"CODAREAREF",V10CADENA,(size_t)&svdarea.codarearef,sizeof(svdarea.codarearef)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdarea.codopemodif,sizeof(svdarea.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdarea.fecmodif,sizeof(svdarea.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdarea.horamodif,sizeof(svdarea.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdarea.codcomen,sizeof(svdarea.codcomen)}
	};
static diccionarios dvdarea[]={
    {colvdarea,10}
};
diccionario dare={dvdarea,1};

static char msglogARE[LCADENA];
static char msgdebugARE[LCADENABIG];
static int init=0;


static void fin_vd_are(void)
{
if (vdselarevdarea) {
    liberacursor(vdselarevdarea);
    vdselarevdarea = NULL;
}
}
static void init_selarevdarea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdarea[0].numcol;nc++) dvdarea[0].c[nc].offset-=(size_t)&svdarea;
    vdselarevdarea=abrecursordebug(SELAREVDAREA,1280);
    definetodo(vdselarevdarea,svdarea.rowid,sizeof(svdarea.rowid),V10CADENA,
                          svdarea.codarea,sizeof(svdarea.codarea),V10CADENA,
                          svdarea.codalm,sizeof(svdarea.codalm),V10CADENA,
                          svdarea.desarea,sizeof(svdarea.desarea),V10CADENA,
                          &svdarea.ordenarea,sizeof(svdarea.ordenarea),V10LONG,
                          svdarea.codarearef,sizeof(svdarea.codarearef),V10CADENA,
                          svdarea.codopemodif,sizeof(svdarea.codopemodif),V10CADENA,
                          &svdarea.fecmodif,sizeof(svdarea.fecmodif),V10LONG,
                          svdarea.horamodif,sizeof(svdarea.horamodif),V10CADENA,
                          &svdarea.codcomen,sizeof(svdarea.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselarevdarea,"CODAREA",svdarea.codarea,sizeof(svdarea.codarea),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_are);
        init = 1;
    }
}

diccionario *AREdamediccionario(void)
{
     return(&dare);
}

int AREselvdarea(char *codarea,vdareas *are)
{
  int vdret;
  if (vdselarevdarea==NULL) init_selarevdarea();
  memset(&svdarea,0,sizeof(svdarea));
  strcpy(svdarea.codarea,codarea);
  vdret=ejefetchcursor(vdselarevdarea);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselarevdarea. vdret %d. \n",ARElog(&svdarea),vdret);
    return(VD_EERRORACLE);
   }
  *are=svdarea;
  return(vdret);
}

char * ARElog(vdareas *are)
{
    sprintf(msglogARE, "VDAREA: codarea %s ",are->codarea);
    return(msglogARE);
}

char * AREdebug(vdareas *are)
{
    debugestruct(&dare,are,msgdebugARE);
    return(msgdebugARE);
}

