// Modulo generado automaticamente a partir de VDTAREAS.DEF
//#***
//# VDTAREAS.c - Generación automática del código c para la tabla de Tareas                                                    
//# 
//# Propósito: Funciones de acceso a la tabla VDTAREAS
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 25-04-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=TAR
//
//

#include "vd.h"
#define SELTARVDTAREAS "SELECT VDTAREAS.ROWID,VDTAREAS.TAREA,VDTAREAS.DESTAREA, "\
                    " VDTAREAS.CODCLASIF,VDTAREAS.CODOPEMODIF,VDTAREAS.FECMODIF, "\
                    " VDTAREAS.HORAMODIF,VDTAREAS.CODCOMEN "\
        " FROM VDTAREAS"\
        " WHERE "\
               " VDTAREAS.TAREA=:TAREA "
static v10cursors *vdseltarvdtareas;

static vdtareass svdtareas;

static diccols colvdtareas[]={
	{"ROWID",V10CADENA,(size_t)&svdtareas.rowid,sizeof(svdtareas.rowid)},
	{"TAREA",V10CADENA,(size_t)&svdtareas.tarea,sizeof(svdtareas.tarea)},
	{"DESTAREA",V10CADENA,(size_t)&svdtareas.destarea,sizeof(svdtareas.destarea)},
	{"CODCLASIF",V10CADENA,(size_t)&svdtareas.codclasif,sizeof(svdtareas.codclasif)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdtareas.codopemodif,sizeof(svdtareas.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdtareas.fecmodif,sizeof(svdtareas.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdtareas.horamodif,sizeof(svdtareas.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdtareas.codcomen,sizeof(svdtareas.codcomen)}
	};
static diccionarios dvdtareas[]={
    {colvdtareas,8}
};
diccionario dtar={dvdtareas,1};

static char msglogTAR[LCADENA];
static char msgdebugTAR[LCADENABIG];
static int init=0;


static void fin_vd_tar(void)
{
if (vdseltarvdtareas) {
    liberacursor(vdseltarvdtareas);
    vdseltarvdtareas = NULL;
}
}
static void init_seltarvdtareas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtareas[0].numcol;nc++) dvdtareas[0].c[nc].offset-=(size_t)&svdtareas;
    vdseltarvdtareas=abrecursordebug(SELTARVDTAREAS,1280);
    definetodo(vdseltarvdtareas,svdtareas.rowid,sizeof(svdtareas.rowid),V10CADENA,
                          svdtareas.tarea,sizeof(svdtareas.tarea),V10CADENA,
                          svdtareas.destarea,sizeof(svdtareas.destarea),V10CADENA,
                          svdtareas.codclasif,sizeof(svdtareas.codclasif),V10CADENA,
                          svdtareas.codopemodif,sizeof(svdtareas.codopemodif),V10CADENA,
                          &svdtareas.fecmodif,sizeof(svdtareas.fecmodif),V10LONG,
                          svdtareas.horamodif,sizeof(svdtareas.horamodif),V10CADENA,
                          &svdtareas.codcomen,sizeof(svdtareas.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseltarvdtareas,"TAREA",svdtareas.tarea,sizeof(svdtareas.tarea),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_tar);
        init = 1;
    }
}

diccionario *TARdamediccionario(void)
{
     return(&dtar);
}

int TARselvdtareas(char *tarea,vdtareass *tar)
{
  int vdret;
  if (vdseltarvdtareas==NULL) init_seltarvdtareas();
  memset(&svdtareas,0,sizeof(svdtareas));
  strcpy(svdtareas.tarea,tarea);
  vdret=ejefetchcursor(vdseltarvdtareas);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseltarvdtareas. vdret %d. \n",TARlog(&svdtareas),vdret);
    return(VD_EERRORACLE);
   }
  *tar=svdtareas;
  return(vdret);
}

char * TARlog(vdtareass *tar)
{
    sprintf(msglogTAR, "VDTAREAS: tarea %s ",tar->tarea);
    return(msglogTAR);
}

char * TARdebug(vdtareass *tar)
{
    debugestruct(&dtar,tar,msgdebugTAR);
    return(msgdebugTAR);
}

