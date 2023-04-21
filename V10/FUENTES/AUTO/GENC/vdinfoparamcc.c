// Modulo generado automaticamente a partir de VDINFOPARAMCC.DEF
//# Modulo : VDINFOPARAMCC.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFODISP
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 20-01-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IPC;
//
//
//UPDATE=TEXTOYPARAM,TEXTO,PARAM
//UPDATE=TEXTOPARAMYPRIORIDAD,TEXTO,PARAM,PRIORIDAD
//
//INSERT
//DELETE

#include "vd.h"
#define SELIPCVDINFOPARAMCC "SELECT VDINFOPARAMCC.ROWID,VDINFOPARAMCC.CODZONA,VDINFOPARAMCC.TEXTO, "\
                    " VDINFOPARAMCC.PARAM,VDINFOPARAMCC.PRIORIDAD,VDINFOPARAMCC.CODOPEMODIF, "\
                    " VDINFOPARAMCC.FECMODIF,VDINFOPARAMCC.HORAMODIF "\
        " FROM VDINFOPARAMCC"
static v10cursors *vdselipcvdinfoparamcc;

#define UPDAIPCTEXTOYPARAM "UPDATE VDINFOPARAMCC SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " TEXTO=:TEXTO , "\
               " PARAM=:PARAM  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaipctextoyparam;

#define UPDAIPCTEXTOPARAMYPRIORIDAD "UPDATE VDINFOPARAMCC SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " TEXTO=:TEXTO , "\
               " PARAM=:PARAM , "\
               " PRIORIDAD=:PRIORIDAD  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaipctextoparamyprioridad;

#define INSIPC "INSERT INTO VDINFOPARAMCC (CODZONA,TEXTO,PARAM,PRIORIDAD,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF "\
       " ) VALUES ( "\
                    " :CODZONA,:TEXTO,:PARAM,:PRIORIDAD,VDUSER.GETUSER(),VD.FECHASYS(), "\
                    " VD.HORASYS()) "
static v10cursors *vdinsipc;

#define DELIPC "DELETE VDINFOPARAMCC WHERE ROWID=:MIROWID "
static v10cursors *vddelipc;

static vdinfoparamccs svdinfoparamcc;

static diccols colvdinfoparamcc[]={
	{"ROWID",V10CADENA,(size_t)&svdinfoparamcc.rowid,sizeof(svdinfoparamcc.rowid)},
	{"CODZONA",V10LONG,(size_t)&svdinfoparamcc.codzona,sizeof(svdinfoparamcc.codzona)},
	{"TEXTO",V10CADENA,(size_t)&svdinfoparamcc.texto,sizeof(svdinfoparamcc.texto)},
	{"PARAM",V10CADENA,(size_t)&svdinfoparamcc.param,sizeof(svdinfoparamcc.param)},
	{"PRIORIDAD",V10LONG,(size_t)&svdinfoparamcc.prioridad,sizeof(svdinfoparamcc.prioridad)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfoparamcc.codopemodif,sizeof(svdinfoparamcc.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfoparamcc.fecmodif,sizeof(svdinfoparamcc.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfoparamcc.horamodif,sizeof(svdinfoparamcc.horamodif)}
	};
static diccionarios dvdinfoparamcc[]={
    {colvdinfoparamcc,8}
};
diccionario dipc={dvdinfoparamcc,1};

static char msglogIPC[LCADENA];
static char msgdebugIPC[LCADENABIG];
static int init=0;


static void fin_vd_ipc(void)
{
if (vdselipcvdinfoparamcc) {
    liberacursor(vdselipcvdinfoparamcc);
    vdselipcvdinfoparamcc = NULL;
}
if (vdupdaipctextoyparam) {
    liberacursor(vdupdaipctextoyparam);
    vdupdaipctextoyparam = NULL;
}
if (vdupdaipctextoparamyprioridad) {
    liberacursor(vdupdaipctextoparamyprioridad);
    vdupdaipctextoparamyprioridad = NULL;
}
if (vdinsipc != NULL) {
    liberacursor(vdinsipc);
    vdinsipc = NULL;
}
if (vddelipc != NULL) {
    liberacursor(vddelipc);
    vddelipc = NULL;
}
}
static void init_selipcvdinfoparamcc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoparamcc[0].numcol;nc++) dvdinfoparamcc[0].c[nc].offset-=(size_t)&svdinfoparamcc;
    vdselipcvdinfoparamcc=abrecursordebug(SELIPCVDINFOPARAMCC,1280);
    definetodo(vdselipcvdinfoparamcc,svdinfoparamcc.rowid,sizeof(svdinfoparamcc.rowid),V10CADENA,
                          &svdinfoparamcc.codzona,sizeof(svdinfoparamcc.codzona),V10LONG,
                          svdinfoparamcc.texto,sizeof(svdinfoparamcc.texto),V10CADENA,
                          svdinfoparamcc.param,sizeof(svdinfoparamcc.param),V10CADENA,
                          &svdinfoparamcc.prioridad,sizeof(svdinfoparamcc.prioridad),V10LONG,
                          svdinfoparamcc.codopemodif,sizeof(svdinfoparamcc.codopemodif),V10CADENA,
                          &svdinfoparamcc.fecmodif,sizeof(svdinfoparamcc.fecmodif),V10LONG,
                          svdinfoparamcc.horamodif,sizeof(svdinfoparamcc.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselipcvdinfoparamcc,NULL);
    if (init == 0) {
        atexit(fin_vd_ipc);
        init = 1;
    }
}

static void init_updaipctextoyparam(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoparamcc[0].numcol;nc++) dvdinfoparamcc[0].c[nc].offset-=(size_t)&svdinfoparamcc;
    vdupdaipctextoyparam=abrecursordebug(UPDAIPCTEXTOYPARAM,1280);
    bindtodo(vdupdaipctextoyparam,"TEXTO",svdinfoparamcc.texto,sizeof(svdinfoparamcc.texto),V10CADENA,
                          "PARAM",svdinfoparamcc.param,sizeof(svdinfoparamcc.param),V10CADENA,
                          "MIROWID",svdinfoparamcc.rowid,sizeof(svdinfoparamcc.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ipc);
        init = 1;
    }
}

static void init_updaipctextoparamyprioridad(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoparamcc[0].numcol;nc++) dvdinfoparamcc[0].c[nc].offset-=(size_t)&svdinfoparamcc;
    vdupdaipctextoparamyprioridad=abrecursordebug(UPDAIPCTEXTOPARAMYPRIORIDAD,1280);
    bindtodo(vdupdaipctextoparamyprioridad,"TEXTO",svdinfoparamcc.texto,sizeof(svdinfoparamcc.texto),V10CADENA,
                          "PARAM",svdinfoparamcc.param,sizeof(svdinfoparamcc.param),V10CADENA,
                          "PRIORIDAD",&svdinfoparamcc.prioridad,sizeof(svdinfoparamcc.prioridad),V10LONG,
                          "MIROWID",svdinfoparamcc.rowid,sizeof(svdinfoparamcc.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ipc);
        init = 1;
    }
}

static void init_insipc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoparamcc[0].numcol;nc++) dvdinfoparamcc[0].c[nc].offset-=(size_t)&svdinfoparamcc;
    vdinsipc=abrecursordebug(INSIPC,1280);
    bindtodo(vdinsipc,"CODZONA",&svdinfoparamcc.codzona,sizeof(svdinfoparamcc.codzona),V10LONG,
                          "TEXTO",svdinfoparamcc.texto,sizeof(svdinfoparamcc.texto),V10CADENA,
                          "PARAM",svdinfoparamcc.param,sizeof(svdinfoparamcc.param),V10CADENA,
                          "PRIORIDAD",&svdinfoparamcc.prioridad,sizeof(svdinfoparamcc.prioridad),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ipc);
        init = 1;
    }
}

static void init_delipc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfoparamcc[0].numcol;nc++) dvdinfoparamcc[0].c[nc].offset-=(size_t)&svdinfoparamcc;
    vddelipc=abrecursordebug(DELIPC,1280);
    bindtodo(vddelipc,"MIROWID",svdinfoparamcc.rowid,sizeof(svdinfoparamcc.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ipc);
        init = 1;
    }
}

diccionario *IPCdamediccionario(void)
{
     return(&dipc);
}

int IPCselvdinfoparamcc(vdinfoparamccs *ipc)
{
  int vdret;
  if (vdselipcvdinfoparamcc==NULL) init_selipcvdinfoparamcc();
  memset(&svdinfoparamcc,0,sizeof(svdinfoparamcc));
  vdret=ejefetchcursor(vdselipcvdinfoparamcc);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselipcvdinfoparamcc. vdret %d. \n",IPClog(&svdinfoparamcc),vdret);
    return(VD_EERRORACLE);
   }
  *ipc=svdinfoparamcc;
  return(vdret);
}

int IPCactualizatextoyparam(vdinfoparamccs *ipc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IPCactualizatextoyparam:  %s .  \n",IPClog(&svdinfoparamcc));
  if (vdupdaipctextoyparam==NULL) init_updaipctextoyparam();
  svdinfoparamcc=*ipc;
  vdret=ejecutacursor(vdupdaipctextoyparam);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaipctextoyparam);
     getcurerrornombre(vdupdaipctextoyparam->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaipctextoyparam)!=1) return(VD_EERRORACLE);
  return(0);
}

int IPCactualizatextoparamyprioridad(vdinfoparamccs *ipc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IPCactualizatextoparamyprioridad:  %s .  \n",IPClog(&svdinfoparamcc));
  if (vdupdaipctextoparamyprioridad==NULL) init_updaipctextoparamyprioridad();
  svdinfoparamcc=*ipc;
  vdret=ejecutacursor(vdupdaipctextoparamyprioridad);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaipctextoparamyprioridad);
     getcurerrornombre(vdupdaipctextoparamyprioridad->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaipctextoparamyprioridad)!=1) return(VD_EERRORACLE);
  return(0);
}

int IPCinsert(vdinfoparamccs *ipc,int error)
{
  int vdret;
  if (!vdinsipc) init_insipc();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",IPClog(&svdinfoparamcc));
  svdinfoparamcc=*ipc;
  vdret=ejecutacursor(vdinsipc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsipc);
     getcurerrornombre(vdinsipc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int IPCdel(vdinfoparamccs *ipc,int error)
{
  int vdret;
  svdinfoparamcc=*ipc;
  if (vddelipc==NULL) init_delipc();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",IPClog(&svdinfoparamcc));
  vdret=ejecutacursor(vddelipc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelipc);
     getcurerrornombre(vddelipc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * IPClog(vdinfoparamccs *ipc)
{
    sprintf(msglogIPC, "VDINFOPARAMCC: ");
    return(msglogIPC);
}

char * IPCdebug(vdinfoparamccs *ipc)
{
    debugestruct(&dipc,ipc,msgdebugIPC);
    return(msgdebugIPC);
}

