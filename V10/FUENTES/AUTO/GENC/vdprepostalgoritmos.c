// Modulo generado automaticamente a partir de VDPREPOSTALGORITMOS.DEF
//# Modulo : VDINFOZONAS.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDSCANLECT
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 10-02-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=PREPOST
//
//RECORRE=ALGORITMO,WHERE=VDPREPOSTALGORITMOS.ACTIVO='S' AND VDPREPOSTALGORITMOS.TIPOALG=:TIPOALG AND PROCESO=:PROCESO AND NOMBREALG=:NOMBREALG;ORDERBY=PRIORIDAD;
//
//
//

#include "vd.h"
#define SELPREPOSTALGORITMO "SELECT VDPREPOSTALGORITMOS.ROWID,VDPREPOSTALGORITMOS.PROCESO,VDPREPOSTALGORITMOS.NOMBREALG, "\
                    " VDPREPOSTALGORITMOS.TIPOALG,VDPREPOSTALGORITMOS.FUNCIONALG,VDPREPOSTALGORITMOS.DESALG, "\
                    " VDPREPOSTALGORITMOS.PARAMALG,VDPREPOSTALGORITMOS.LIBALGORITMO,VDPREPOSTALGORITMOS.ACTIVO, "\
                    " VDPREPOSTALGORITMOS.PRIORIDAD,VDPREPOSTALGORITMOS.INFOEXTRA,VDPREPOSTALGORITMOS.CODCOMEN, "\
                    " VDPREPOSTALGORITMOS.CODOPEMODIF,VDPREPOSTALGORITMOS.FECMODIF,VDPREPOSTALGORITMOS.HORAMODIF "\
        " FROM VDPREPOSTALGORITMOS"\
        " WHERE "\
              " VDPREPOSTALGORITMOS.ACTIVO='S' AND VDPREPOSTALGORITMOS.TIPOALG=:TIPOALG AND PROCESO=:PROCESO AND NOMBREALG=:NOMBREALG "\
        " ORDER BY PRIORIDAD "
static v10cursors *vdselprepostalgoritmo;

#define SELPREPOSTVDPREPOSTALGORITMOS "SELECT VDPREPOSTALGORITMOS.ROWID,VDPREPOSTALGORITMOS.PROCESO,VDPREPOSTALGORITMOS.NOMBREALG, "\
                    " VDPREPOSTALGORITMOS.TIPOALG,VDPREPOSTALGORITMOS.FUNCIONALG,VDPREPOSTALGORITMOS.DESALG, "\
                    " VDPREPOSTALGORITMOS.PARAMALG,VDPREPOSTALGORITMOS.LIBALGORITMO,VDPREPOSTALGORITMOS.ACTIVO, "\
                    " VDPREPOSTALGORITMOS.PRIORIDAD,VDPREPOSTALGORITMOS.INFOEXTRA,VDPREPOSTALGORITMOS.CODCOMEN, "\
                    " VDPREPOSTALGORITMOS.CODOPEMODIF,VDPREPOSTALGORITMOS.FECMODIF,VDPREPOSTALGORITMOS.HORAMODIF "\
        " FROM VDPREPOSTALGORITMOS"\
        " WHERE "\
               " VDPREPOSTALGORITMOS.PROCESO=:PROCESO "\
               " AND VDPREPOSTALGORITMOS.NOMBREALG=:NOMBREALG "\
               " AND VDPREPOSTALGORITMOS.TIPOALG=:TIPOALG "\
               " AND VDPREPOSTALGORITMOS.PRIORIDAD=:PRIORIDAD "
static v10cursors *vdselprepostvdprepostalgoritmos;

static vdprepostalgoritmoss svdprepostalgoritmos;

static diccols colvdprepostalgoritmos[]={
	{"ROWID",V10CADENA,(size_t)&svdprepostalgoritmos.rowid,sizeof(svdprepostalgoritmos.rowid)},
	{"PROCESO",V10CADENA,(size_t)&svdprepostalgoritmos.proceso,sizeof(svdprepostalgoritmos.proceso)},
	{"NOMBREALG",V10CADENA,(size_t)&svdprepostalgoritmos.nombrealg,sizeof(svdprepostalgoritmos.nombrealg)},
	{"TIPOALG",V10CADENA,(size_t)&svdprepostalgoritmos.tipoalg,sizeof(svdprepostalgoritmos.tipoalg)},
	{"FUNCIONALG",V10CADENA,(size_t)&svdprepostalgoritmos.funcionalg,sizeof(svdprepostalgoritmos.funcionalg)},
	{"DESALG",V10CADENA,(size_t)&svdprepostalgoritmos.desalg,sizeof(svdprepostalgoritmos.desalg)},
	{"PARAMALG",V10CADENA,(size_t)&svdprepostalgoritmos.paramalg,sizeof(svdprepostalgoritmos.paramalg)},
	{"LIBALGORITMO",V10CADENA,(size_t)&svdprepostalgoritmos.libalgoritmo,sizeof(svdprepostalgoritmos.libalgoritmo)},
	{"ACTIVO",V10CADENA,(size_t)&svdprepostalgoritmos.activo,sizeof(svdprepostalgoritmos.activo)},
	{"PRIORIDAD",V10LONG,(size_t)&svdprepostalgoritmos.prioridad,sizeof(svdprepostalgoritmos.prioridad)},
	{"INFOEXTRA",V10CADENA,(size_t)&svdprepostalgoritmos.infoextra,sizeof(svdprepostalgoritmos.infoextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdprepostalgoritmos.codcomen,sizeof(svdprepostalgoritmos.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdprepostalgoritmos.codopemodif,sizeof(svdprepostalgoritmos.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdprepostalgoritmos.fecmodif,sizeof(svdprepostalgoritmos.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdprepostalgoritmos.horamodif,sizeof(svdprepostalgoritmos.horamodif)}
	};
static diccionarios dvdprepostalgoritmos[]={
    {colvdprepostalgoritmos,15}
};
diccionario dprepost={dvdprepostalgoritmos,1};

static char msglogPREPOST[LCADENA];
static char msgdebugPREPOST[LCADENABIG];
static int init=0;


static void fin_vd_prepost(void)
{
if (vdselprepostalgoritmo) {
    liberacursor(vdselprepostalgoritmo);
    vdselprepostalgoritmo = NULL;
}
if (vdselprepostvdprepostalgoritmos) {
    liberacursor(vdselprepostvdprepostalgoritmos);
    vdselprepostvdprepostalgoritmos = NULL;
}
}
static void init_selprepostalgoritmo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdprepostalgoritmos[0].numcol;nc++) dvdprepostalgoritmos[0].c[nc].offset-=(size_t)&svdprepostalgoritmos;
    vdselprepostalgoritmo=abrecursordebug(SELPREPOSTALGORITMO,1280);
    definetodo(vdselprepostalgoritmo,svdprepostalgoritmos.rowid,sizeof(svdprepostalgoritmos.rowid),V10CADENA,
                          svdprepostalgoritmos.proceso,sizeof(svdprepostalgoritmos.proceso),V10CADENA,
                          svdprepostalgoritmos.nombrealg,sizeof(svdprepostalgoritmos.nombrealg),V10CADENA,
                          svdprepostalgoritmos.tipoalg,sizeof(svdprepostalgoritmos.tipoalg),V10CADENA,
                          svdprepostalgoritmos.funcionalg,sizeof(svdprepostalgoritmos.funcionalg),V10CADENA,
                          svdprepostalgoritmos.desalg,sizeof(svdprepostalgoritmos.desalg),V10CADENA,
                          svdprepostalgoritmos.paramalg,sizeof(svdprepostalgoritmos.paramalg),V10CADENA,
                          svdprepostalgoritmos.libalgoritmo,sizeof(svdprepostalgoritmos.libalgoritmo),V10CADENA,
                          svdprepostalgoritmos.activo,sizeof(svdprepostalgoritmos.activo),V10CADENA,
                          &svdprepostalgoritmos.prioridad,sizeof(svdprepostalgoritmos.prioridad),V10LONG,
                          svdprepostalgoritmos.infoextra,sizeof(svdprepostalgoritmos.infoextra),V10CADENA,
                          &svdprepostalgoritmos.codcomen,sizeof(svdprepostalgoritmos.codcomen),V10LONG,
                          svdprepostalgoritmos.codopemodif,sizeof(svdprepostalgoritmos.codopemodif),V10CADENA,
                          &svdprepostalgoritmos.fecmodif,sizeof(svdprepostalgoritmos.fecmodif),V10LONG,
                          svdprepostalgoritmos.horamodif,sizeof(svdprepostalgoritmos.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselprepostalgoritmo,"TIPOALG",svdprepostalgoritmos.tipoalg,sizeof(svdprepostalgoritmos.tipoalg),V10CADENA,
                          "PROCESO",svdprepostalgoritmos.proceso,sizeof(svdprepostalgoritmos.proceso),V10CADENA,
                          "NOMBREALG",svdprepostalgoritmos.nombrealg,sizeof(svdprepostalgoritmos.nombrealg),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_prepost);
        init = 1;
    }
}

static void init_selprepostvdprepostalgoritmos(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdprepostalgoritmos[0].numcol;nc++) dvdprepostalgoritmos[0].c[nc].offset-=(size_t)&svdprepostalgoritmos;
    vdselprepostvdprepostalgoritmos=abrecursordebug(SELPREPOSTVDPREPOSTALGORITMOS,1280);
    definetodo(vdselprepostvdprepostalgoritmos,svdprepostalgoritmos.rowid,sizeof(svdprepostalgoritmos.rowid),V10CADENA,
                          svdprepostalgoritmos.proceso,sizeof(svdprepostalgoritmos.proceso),V10CADENA,
                          svdprepostalgoritmos.nombrealg,sizeof(svdprepostalgoritmos.nombrealg),V10CADENA,
                          svdprepostalgoritmos.tipoalg,sizeof(svdprepostalgoritmos.tipoalg),V10CADENA,
                          svdprepostalgoritmos.funcionalg,sizeof(svdprepostalgoritmos.funcionalg),V10CADENA,
                          svdprepostalgoritmos.desalg,sizeof(svdprepostalgoritmos.desalg),V10CADENA,
                          svdprepostalgoritmos.paramalg,sizeof(svdprepostalgoritmos.paramalg),V10CADENA,
                          svdprepostalgoritmos.libalgoritmo,sizeof(svdprepostalgoritmos.libalgoritmo),V10CADENA,
                          svdprepostalgoritmos.activo,sizeof(svdprepostalgoritmos.activo),V10CADENA,
                          &svdprepostalgoritmos.prioridad,sizeof(svdprepostalgoritmos.prioridad),V10LONG,
                          svdprepostalgoritmos.infoextra,sizeof(svdprepostalgoritmos.infoextra),V10CADENA,
                          &svdprepostalgoritmos.codcomen,sizeof(svdprepostalgoritmos.codcomen),V10LONG,
                          svdprepostalgoritmos.codopemodif,sizeof(svdprepostalgoritmos.codopemodif),V10CADENA,
                          &svdprepostalgoritmos.fecmodif,sizeof(svdprepostalgoritmos.fecmodif),V10LONG,
                          svdprepostalgoritmos.horamodif,sizeof(svdprepostalgoritmos.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselprepostvdprepostalgoritmos,"PROCESO",svdprepostalgoritmos.proceso,sizeof(svdprepostalgoritmos.proceso),V10CADENA,
                          "NOMBREALG",svdprepostalgoritmos.nombrealg,sizeof(svdprepostalgoritmos.nombrealg),V10CADENA,
                          "TIPOALG",svdprepostalgoritmos.tipoalg,sizeof(svdprepostalgoritmos.tipoalg),V10CADENA,
                          "PRIORIDAD",&svdprepostalgoritmos.prioridad,sizeof(svdprepostalgoritmos.prioridad),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_prepost);
        init = 1;
    }
}

diccionario *PREPOSTdamediccionario(void)
{
     return(&dprepost);
}

int PREPOSTbuscaalgoritmo(char *tipoalg,char *proceso,char *nombrealg,vdprepostalgoritmoss *prepost)
{
  int vdret;
  memset(&svdprepostalgoritmos,0,sizeof(svdprepostalgoritmos));
  strcpy(svdprepostalgoritmos.tipoalg,tipoalg);
  strcpy(svdprepostalgoritmos.proceso,proceso);
  strcpy(svdprepostalgoritmos.nombrealg,nombrealg);
  if (vdselprepostalgoritmo==NULL) init_selprepostalgoritmo();
  vdret=ejefetchcursor(vdselprepostalgoritmo);
  if (vdret==0) {
     *prepost=svdprepostalgoritmos;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselprepostalgoritmo. vdret %d. \n",PREPOSTlog(&svdprepostalgoritmos),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PREPOSTnextalgoritmo(vdprepostalgoritmoss *prepost)
{
  int vdret;
  vdret=fetchcursor(vdselprepostalgoritmo);
  if (vdret==0) {
     *prepost=svdprepostalgoritmos;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselprepostalgoritmo. vdret %d. \n",PREPOSTlog(&svdprepostalgoritmos),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselprepostalgoritmo);
  return(VD_EERRORACLE);
}

int PREPOSTselvdprepostalgoritmos(char *proceso,char *nombrealg,char *tipoalg,long prioridad,vdprepostalgoritmoss *prepost)
{
  int vdret;
  if (vdselprepostvdprepostalgoritmos==NULL) init_selprepostvdprepostalgoritmos();
  memset(&svdprepostalgoritmos,0,sizeof(svdprepostalgoritmos));
  strcpy(svdprepostalgoritmos.proceso,proceso);
  strcpy(svdprepostalgoritmos.nombrealg,nombrealg);
  strcpy(svdprepostalgoritmos.tipoalg,tipoalg);
  svdprepostalgoritmos.prioridad=prioridad;
  vdret=ejefetchcursor(vdselprepostvdprepostalgoritmos);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselprepostvdprepostalgoritmos. vdret %d. \n",PREPOSTlog(&svdprepostalgoritmos),vdret);
    return(VD_EERRORACLE);
   }
  *prepost=svdprepostalgoritmos;
  return(vdret);
}

char * PREPOSTlog(vdprepostalgoritmoss *prepost)
{
    sprintf(msglogPREPOST, "VDPREPOSTALGORITMOS: proceso %s nombrealg %s tipoalg %s prioridad %ld ",prepost->proceso,prepost->nombrealg,prepost->tipoalg,prepost->prioridad);
    return(msglogPREPOST);
}

char * PREPOSTdebug(vdprepostalgoritmoss *prepost)
{
    debugestruct(&dprepost,prepost,msgdebugPREPOST);
    return(msgdebugPREPOST);
}

