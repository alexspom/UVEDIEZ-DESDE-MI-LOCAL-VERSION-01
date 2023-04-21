// Modulo generado automaticamente a partir de VDBASCULAS.DEF
//
//
//TABLE=BAS
//
//RECORRE=STATUS,STATUS
//
//RECORRE=TODO
//
//UPDATE=STATUSYPESO,DATOS,STATUS

#include "vd.h"
#include "vdbasculas.h"

#define SELBASSTATUS "SELECT VDBASCULAS.ROWID,VDBASCULAS.NUMBASC,VDBASCULAS.ACTIVA, "\
                    " VDBASCULAS.DIRIP,VDBASCULAS.PUERTOTCP,VDBASCULAS.PUERTO232, "\
                    " VDBASCULAS.VELOCIDAD,VDBASCULAS.STATUS,VDBASCULAS.DATOS, "\
                    " VDBASCULAS.CODOPESOL,VDBASCULAS.FECSOL,VDBASCULAS.HORASOL, "\
                    " VDBASCULAS.CODOPELEE,VDBASCULAS.FECLEE,VDBASCULAS.HORALEE "\
        " FROM VDBASCULAS"\
        " WHERE "\
               " VDBASCULAS.STATUS=:STATUS "
static v10cursors *vdselbasstatus;

#define SELBASTODO "SELECT VDBASCULAS.ROWID,VDBASCULAS.NUMBASC,VDBASCULAS.ACTIVA, "\
                    " VDBASCULAS.DIRIP,VDBASCULAS.PUERTOTCP,VDBASCULAS.PUERTO232, "\
                    " VDBASCULAS.VELOCIDAD,VDBASCULAS.STATUS,VDBASCULAS.DATOS, "\
                    " VDBASCULAS.CODOPESOL,VDBASCULAS.FECSOL,VDBASCULAS.HORASOL, "\
                    " VDBASCULAS.CODOPELEE,VDBASCULAS.FECLEE,VDBASCULAS.HORALEE "\
        " FROM VDBASCULAS"
static v10cursors *vdselbastodo;

#define SELBASVDBASCULAS "SELECT VDBASCULAS.ROWID,VDBASCULAS.NUMBASC,VDBASCULAS.ACTIVA, "\
                    " VDBASCULAS.DIRIP,VDBASCULAS.PUERTOTCP,VDBASCULAS.PUERTO232, "\
                    " VDBASCULAS.VELOCIDAD,VDBASCULAS.STATUS,VDBASCULAS.DATOS, "\
                    " VDBASCULAS.CODOPESOL,VDBASCULAS.FECSOL,VDBASCULAS.HORASOL, "\
                    " VDBASCULAS.CODOPELEE,VDBASCULAS.FECLEE,VDBASCULAS.HORALEE "\
        " FROM VDBASCULAS"\
        " WHERE "\
               " VDBASCULAS.NUMBASC=:NUMBASC "
static v10cursors *vdselbasvdbasculas;

#define UPDABASSTATUSYPESO "UPDATE VDBASCULAS SET  "\
               " DATOS=:DATOS , "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabasstatusypeso;

static vdbasculass svdbasculas;

static diccols colvdbasculas[]={
	{"ROWID",V10CADENA,(size_t)&svdbasculas.rowid,sizeof(svdbasculas.rowid)},
	{"NUMBASC",V10LONG,(size_t)&svdbasculas.numbasc,sizeof(svdbasculas.numbasc)},
	{"ACTIVA",V10CADENA,(size_t)&svdbasculas.activa,sizeof(svdbasculas.activa)},
	{"DIRIP",V10CADENA,(size_t)&svdbasculas.dirip,sizeof(svdbasculas.dirip)},
	{"PUERTOTCP",V10CADENA,(size_t)&svdbasculas.puertotcp,sizeof(svdbasculas.puertotcp)},
	{"PUERTO232",V10LONG,(size_t)&svdbasculas.puerto232,sizeof(svdbasculas.puerto232)},
	{"VELOCIDAD",V10LONG,(size_t)&svdbasculas.velocidad,sizeof(svdbasculas.velocidad)},
	{"STATUS",V10LONG,(size_t)&svdbasculas.status,sizeof(svdbasculas.status)},
	{"DATOS",V10CADENA,(size_t)&svdbasculas.datos,sizeof(svdbasculas.datos)},
	{"CODOPESOL",V10CADENA,(size_t)&svdbasculas.codopesol,sizeof(svdbasculas.codopesol)},
	{"FECSOL",V10LONG,(size_t)&svdbasculas.fecsol,sizeof(svdbasculas.fecsol)},
	{"HORASOL",V10CADENA,(size_t)&svdbasculas.horasol,sizeof(svdbasculas.horasol)},
	{"CODOPELEE",V10CADENA,(size_t)&svdbasculas.codopelee,sizeof(svdbasculas.codopelee)},
	{"FECLEE",V10LONG,(size_t)&svdbasculas.feclee,sizeof(svdbasculas.feclee)},
	{"HORALEE",V10CADENA,(size_t)&svdbasculas.horalee,sizeof(svdbasculas.horalee)}
	};
static diccionarios dvdbasculas[]={
    {colvdbasculas,15}
};
diccionario dbas={dvdbasculas,1};

static char msglogBAS[LCADENA];
static char msgdebugBAS[LCADENABIG];
static int init=0;


static void fin_vd_bas(void)
{
if (vdselbasstatus) {
    liberacursor(vdselbasstatus);
    vdselbasstatus = NULL;
}
if (vdselbastodo) {
    liberacursor(vdselbastodo);
    vdselbastodo = NULL;
}
if (vdselbasvdbasculas) {
    liberacursor(vdselbasvdbasculas);
    vdselbasvdbasculas = NULL;
}
if (vdupdabasstatusypeso) {
    liberacursor(vdupdabasstatusypeso);
    vdupdabasstatusypeso = NULL;
}
}
static void init_selbasstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbasculas[0].numcol;nc++) dvdbasculas[0].c[nc].offset-=(size_t)&svdbasculas;
    vdselbasstatus=abrecursordebug(SELBASSTATUS,1280);
    definetodo(vdselbasstatus,svdbasculas.rowid,sizeof(svdbasculas.rowid),V10CADENA,
                          &svdbasculas.numbasc,sizeof(svdbasculas.numbasc),V10LONG,
                          svdbasculas.activa,sizeof(svdbasculas.activa),V10CADENA,
                          svdbasculas.dirip,sizeof(svdbasculas.dirip),V10CADENA,
                          svdbasculas.puertotcp,sizeof(svdbasculas.puertotcp),V10CADENA,
                          &svdbasculas.puerto232,sizeof(svdbasculas.puerto232),V10LONG,
                          &svdbasculas.velocidad,sizeof(svdbasculas.velocidad),V10LONG,
                          &svdbasculas.status,sizeof(svdbasculas.status),V10LONG,
                          svdbasculas.datos,sizeof(svdbasculas.datos),V10CADENA,
                          svdbasculas.codopesol,sizeof(svdbasculas.codopesol),V10CADENA,
                          &svdbasculas.fecsol,sizeof(svdbasculas.fecsol),V10LONG,
                          svdbasculas.horasol,sizeof(svdbasculas.horasol),V10CADENA,
                          svdbasculas.codopelee,sizeof(svdbasculas.codopelee),V10CADENA,
                          &svdbasculas.feclee,sizeof(svdbasculas.feclee),V10LONG,
                          svdbasculas.horalee,sizeof(svdbasculas.horalee),V10CADENA,
                          NULL);
    bindtodo(vdselbasstatus,"STATUS",&svdbasculas.status,sizeof(svdbasculas.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bas);
        init = 1;
    }
}

static void init_selbastodo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbasculas[0].numcol;nc++) dvdbasculas[0].c[nc].offset-=(size_t)&svdbasculas;
    vdselbastodo=abrecursordebug(SELBASTODO,1280);
    definetodo(vdselbastodo,svdbasculas.rowid,sizeof(svdbasculas.rowid),V10CADENA,
                          &svdbasculas.numbasc,sizeof(svdbasculas.numbasc),V10LONG,
                          svdbasculas.activa,sizeof(svdbasculas.activa),V10CADENA,
                          svdbasculas.dirip,sizeof(svdbasculas.dirip),V10CADENA,
                          svdbasculas.puertotcp,sizeof(svdbasculas.puertotcp),V10CADENA,
                          &svdbasculas.puerto232,sizeof(svdbasculas.puerto232),V10LONG,
                          &svdbasculas.velocidad,sizeof(svdbasculas.velocidad),V10LONG,
                          &svdbasculas.status,sizeof(svdbasculas.status),V10LONG,
                          svdbasculas.datos,sizeof(svdbasculas.datos),V10CADENA,
                          svdbasculas.codopesol,sizeof(svdbasculas.codopesol),V10CADENA,
                          &svdbasculas.fecsol,sizeof(svdbasculas.fecsol),V10LONG,
                          svdbasculas.horasol,sizeof(svdbasculas.horasol),V10CADENA,
                          svdbasculas.codopelee,sizeof(svdbasculas.codopelee),V10CADENA,
                          &svdbasculas.feclee,sizeof(svdbasculas.feclee),V10LONG,
                          svdbasculas.horalee,sizeof(svdbasculas.horalee),V10CADENA,
                          NULL);
    bindtodo(vdselbastodo,NULL);
    if (init == 0) {
        atexit(fin_vd_bas);
        init = 1;
    }
}

static void init_selbasvdbasculas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbasculas[0].numcol;nc++) dvdbasculas[0].c[nc].offset-=(size_t)&svdbasculas;
    vdselbasvdbasculas=abrecursordebug(SELBASVDBASCULAS,1280);
    definetodo(vdselbasvdbasculas,svdbasculas.rowid,sizeof(svdbasculas.rowid),V10CADENA,
                          &svdbasculas.numbasc,sizeof(svdbasculas.numbasc),V10LONG,
                          svdbasculas.activa,sizeof(svdbasculas.activa),V10CADENA,
                          svdbasculas.dirip,sizeof(svdbasculas.dirip),V10CADENA,
                          svdbasculas.puertotcp,sizeof(svdbasculas.puertotcp),V10CADENA,
                          &svdbasculas.puerto232,sizeof(svdbasculas.puerto232),V10LONG,
                          &svdbasculas.velocidad,sizeof(svdbasculas.velocidad),V10LONG,
                          &svdbasculas.status,sizeof(svdbasculas.status),V10LONG,
                          svdbasculas.datos,sizeof(svdbasculas.datos),V10CADENA,
                          svdbasculas.codopesol,sizeof(svdbasculas.codopesol),V10CADENA,
                          &svdbasculas.fecsol,sizeof(svdbasculas.fecsol),V10LONG,
                          svdbasculas.horasol,sizeof(svdbasculas.horasol),V10CADENA,
                          svdbasculas.codopelee,sizeof(svdbasculas.codopelee),V10CADENA,
                          &svdbasculas.feclee,sizeof(svdbasculas.feclee),V10LONG,
                          svdbasculas.horalee,sizeof(svdbasculas.horalee),V10CADENA,
                          NULL);
    bindtodo(vdselbasvdbasculas,"NUMBASC",&svdbasculas.numbasc,sizeof(svdbasculas.numbasc),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bas);
        init = 1;
    }
}

static void init_updabasstatusypeso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbasculas[0].numcol;nc++) dvdbasculas[0].c[nc].offset-=(size_t)&svdbasculas;
    vdupdabasstatusypeso=abrecursordebug(UPDABASSTATUSYPESO,1280);
    bindtodo(vdupdabasstatusypeso,"DATOS",svdbasculas.datos,sizeof(svdbasculas.datos),V10CADENA,
                          "STATUS",&svdbasculas.status,sizeof(svdbasculas.status),V10LONG,
                          "MIROWID",svdbasculas.rowid,sizeof(svdbasculas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_bas);
        init = 1;
    }
}

diccionario *BASdamediccionario(void)
{
     return(&dbas);
}

int BASbuscastatus(long status,vdbasculass *bas)
{
  int vdret;
  memset(&svdbasculas,0,sizeof(svdbasculas));
  svdbasculas.status=status;
  if (vdselbasstatus==NULL) init_selbasstatus();
  vdret=ejefetchcursor(vdselbasstatus);
  if (vdret==0) {
     *bas=svdbasculas;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbasstatus. vdret %d. \n",BASlog(&svdbasculas),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BASnextstatus(vdbasculass *bas)
{
  int vdret;
  vdret=fetchcursor(vdselbasstatus);
  if (vdret==0) {
     *bas=svdbasculas;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbasstatus. vdret %d. \n",BASlog(&svdbasculas),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbasstatus);
  return(VD_EERRORACLE);
}

int BASbuscatodo(vdbasculass *bas)
{
  int vdret;
  memset(&svdbasculas,0,sizeof(svdbasculas));
  if (vdselbastodo==NULL) init_selbastodo();
  vdret=ejefetchcursor(vdselbastodo);
  if (vdret==0) {
     *bas=svdbasculas;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbastodo. vdret %d. \n",BASlog(&svdbasculas),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BASnexttodo(vdbasculass *bas)
{
  int vdret;
  vdret=fetchcursor(vdselbastodo);
  if (vdret==0) {
     *bas=svdbasculas;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbastodo. vdret %d. \n",BASlog(&svdbasculas),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbastodo);
  return(VD_EERRORACLE);
}

int BASselvdbasculas(long numbasc,vdbasculass *bas)
{
  int vdret;
  if (vdselbasvdbasculas==NULL) init_selbasvdbasculas();
  memset(&svdbasculas,0,sizeof(svdbasculas));
  svdbasculas.numbasc=numbasc;
  vdret=ejefetchcursor(vdselbasvdbasculas);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbasvdbasculas. vdret %d. \n",BASlog(&svdbasculas),vdret);
    return(VD_EERRORACLE);
   }
  *bas=svdbasculas;
  return(vdret);
}

int BASactualizastatusypeso(vdbasculass *bas,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BASactualizastatusypeso:  %s .  \n",BASlog(&svdbasculas));
  if (vdupdabasstatusypeso==NULL) init_updabasstatusypeso();
  svdbasculas=*bas;
  vdret=ejecutacursor(vdupdabasstatusypeso);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabasstatusypeso);
     getcurerrornombre(vdupdabasstatusypeso->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabasstatusypeso)!=1) return(VD_EERRORACLE);
  return(0);
}

char * BASlog(vdbasculass *bas)
{
    sprintf(msglogBAS, "VDBASCULAS: numbasc %ld ",bas->numbasc);
    return(msglogBAS);
}

char * BASdebug(vdbasculass *bas)
{
    debugestruct(&dbas,bas,msgdebugBAS);
    return(msgdebugBAS);
}

