// Modulo generado automaticamente a partir de VDCOLCAMBIOVOL.DEF
//#***
//# VDCOLCAMBIOVOL.DEF - Generaci�n autom�tica del c�digo c para la tabla de 
//#                      colecci�n de cambio de volumetria                                                       
//# 
//# Prop�sito: Funciones de acceso a la tabla VDCOLCAMBIOVOL
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 24-04-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=CCV
//
//CLAVE=CODCOLCAMBIOVOL,CODCOLCAMBIOVOL;
//RECORRE=TIPOVOLORIG,CODCOLCAMBIOVOL,TIPOVOLORIG;
//
//INSERT 
//DELETE

#include "vd.h"
#define SELCCVCODCOLCAMBIOVOL "SELECT VDCOLCAMBIOVOL.ROWID,VDCOLCAMBIOVOL.CODCOLCAMBIOVOL,VDCOLCAMBIOVOL.TIPOVOLORIG, "\
                    " VDCOLCAMBIOVOL.TIPOVOLDEST,VDCOLCAMBIOVOL.CODOPEMODIF,VDCOLCAMBIOVOL.FECMODIF, "\
                    " VDCOLCAMBIOVOL.HORAMODIF,VDCOLCAMBIOVOL.CODCOMEN "\
        " FROM VDCOLCAMBIOVOL"\
        " WHERE "\
               " VDCOLCAMBIOVOL.CODCOLCAMBIOVOL=:CODCOLCAMBIOVOL "
static v10cursors *vdselccvcodcolcambiovol;

#define SELCCVTIPOVOLORIG "SELECT VDCOLCAMBIOVOL.ROWID,VDCOLCAMBIOVOL.CODCOLCAMBIOVOL,VDCOLCAMBIOVOL.TIPOVOLORIG, "\
                    " VDCOLCAMBIOVOL.TIPOVOLDEST,VDCOLCAMBIOVOL.CODOPEMODIF,VDCOLCAMBIOVOL.FECMODIF, "\
                    " VDCOLCAMBIOVOL.HORAMODIF,VDCOLCAMBIOVOL.CODCOMEN "\
        " FROM VDCOLCAMBIOVOL"\
        " WHERE "\
               " VDCOLCAMBIOVOL.CODCOLCAMBIOVOL=:CODCOLCAMBIOVOL "\
               " AND VDCOLCAMBIOVOL.TIPOVOLORIG=:TIPOVOLORIG "
static v10cursors *vdselccvtipovolorig;

#define SELCCVVDCOLCAMBIOVOL "SELECT VDCOLCAMBIOVOL.ROWID,VDCOLCAMBIOVOL.CODCOLCAMBIOVOL,VDCOLCAMBIOVOL.TIPOVOLORIG, "\
                    " VDCOLCAMBIOVOL.TIPOVOLDEST,VDCOLCAMBIOVOL.CODOPEMODIF,VDCOLCAMBIOVOL.FECMODIF, "\
                    " VDCOLCAMBIOVOL.HORAMODIF,VDCOLCAMBIOVOL.CODCOMEN "\
        " FROM VDCOLCAMBIOVOL"\
        " WHERE "\
               " VDCOLCAMBIOVOL.CODCOLCAMBIOVOL=:CODCOLCAMBIOVOL "\
               " AND VDCOLCAMBIOVOL.TIPOVOLORIG=:TIPOVOLORIG "\
               " AND VDCOLCAMBIOVOL.TIPOVOLDEST=:TIPOVOLDEST "
static v10cursors *vdselccvvdcolcambiovol;

#define INSCCV "INSERT INTO VDCOLCAMBIOVOL (CODCOLCAMBIOVOL,TIPOVOLORIG,TIPOVOLDEST,CODOPEMODIF,FECMODIF,HORAMODIF, "\
                    " CODCOMEN "\
       " ) VALUES ( "\
                    " :CODCOLCAMBIOVOL,:TIPOVOLORIG,:TIPOVOLDEST,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS, "\
                    " :CODCOMEN) "
static v10cursors *vdinsccv;

#define DELCCV "DELETE VDCOLCAMBIOVOL WHERE ROWID=:MIROWID "
static v10cursors *vddelccv;

static vdcolcambiovols svdcolcambiovol;

static diccols colvdcolcambiovol[]={
	{"ROWID",V10CADENA,(size_t)&svdcolcambiovol.rowid,sizeof(svdcolcambiovol.rowid)},
	{"CODCOLCAMBIOVOL",V10CADENA,(size_t)&svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol)},
	{"TIPOVOLORIG",V10CADENA,(size_t)&svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig)},
	{"TIPOVOLDEST",V10CADENA,(size_t)&svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdcolcambiovol.codopemodif,sizeof(svdcolcambiovol.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdcolcambiovol.fecmodif,sizeof(svdcolcambiovol.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdcolcambiovol.horamodif,sizeof(svdcolcambiovol.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdcolcambiovol.codcomen,sizeof(svdcolcambiovol.codcomen)}
	};
static diccionarios dvdcolcambiovol[]={
    {colvdcolcambiovol,8}
};
diccionario dccv={dvdcolcambiovol,1};

static char msglogCCV[LCADENA];
static char msgdebugCCV[LCADENABIG];
static int init=0;


static void fin_vd_ccv(void)
{
if (vdselccvcodcolcambiovol) {
    liberacursor(vdselccvcodcolcambiovol);
    vdselccvcodcolcambiovol = NULL;
}
if (vdselccvtipovolorig) {
    liberacursor(vdselccvtipovolorig);
    vdselccvtipovolorig = NULL;
}
if (vdselccvvdcolcambiovol) {
    liberacursor(vdselccvvdcolcambiovol);
    vdselccvvdcolcambiovol = NULL;
}
if (vdinsccv != NULL) {
    liberacursor(vdinsccv);
    vdinsccv = NULL;
}
if (vddelccv != NULL) {
    liberacursor(vddelccv);
    vddelccv = NULL;
}
}
static void init_selccvcodcolcambiovol(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcolcambiovol[0].numcol;nc++) dvdcolcambiovol[0].c[nc].offset-=(size_t)&svdcolcambiovol;
    vdselccvcodcolcambiovol=abrecursordebug(SELCCVCODCOLCAMBIOVOL,1280);
    definetodo(vdselccvcodcolcambiovol,svdcolcambiovol.rowid,sizeof(svdcolcambiovol.rowid),V10CADENA,
                          svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest),V10CADENA,
                          svdcolcambiovol.codopemodif,sizeof(svdcolcambiovol.codopemodif),V10CADENA,
                          &svdcolcambiovol.fecmodif,sizeof(svdcolcambiovol.fecmodif),V10LONG,
                          svdcolcambiovol.horamodif,sizeof(svdcolcambiovol.horamodif),V10CADENA,
                          &svdcolcambiovol.codcomen,sizeof(svdcolcambiovol.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselccvcodcolcambiovol,"CODCOLCAMBIOVOL",svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ccv);
        init = 1;
    }
}

static void init_selccvtipovolorig(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcolcambiovol[0].numcol;nc++) dvdcolcambiovol[0].c[nc].offset-=(size_t)&svdcolcambiovol;
    vdselccvtipovolorig=abrecursordebug(SELCCVTIPOVOLORIG,1280);
    definetodo(vdselccvtipovolorig,svdcolcambiovol.rowid,sizeof(svdcolcambiovol.rowid),V10CADENA,
                          svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest),V10CADENA,
                          svdcolcambiovol.codopemodif,sizeof(svdcolcambiovol.codopemodif),V10CADENA,
                          &svdcolcambiovol.fecmodif,sizeof(svdcolcambiovol.fecmodif),V10LONG,
                          svdcolcambiovol.horamodif,sizeof(svdcolcambiovol.horamodif),V10CADENA,
                          &svdcolcambiovol.codcomen,sizeof(svdcolcambiovol.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselccvtipovolorig,"CODCOLCAMBIOVOL",svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          "TIPOVOLORIG",svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ccv);
        init = 1;
    }
}

static void init_selccvvdcolcambiovol(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcolcambiovol[0].numcol;nc++) dvdcolcambiovol[0].c[nc].offset-=(size_t)&svdcolcambiovol;
    vdselccvvdcolcambiovol=abrecursordebug(SELCCVVDCOLCAMBIOVOL,1280);
    definetodo(vdselccvvdcolcambiovol,svdcolcambiovol.rowid,sizeof(svdcolcambiovol.rowid),V10CADENA,
                          svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest),V10CADENA,
                          svdcolcambiovol.codopemodif,sizeof(svdcolcambiovol.codopemodif),V10CADENA,
                          &svdcolcambiovol.fecmodif,sizeof(svdcolcambiovol.fecmodif),V10LONG,
                          svdcolcambiovol.horamodif,sizeof(svdcolcambiovol.horamodif),V10CADENA,
                          &svdcolcambiovol.codcomen,sizeof(svdcolcambiovol.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselccvvdcolcambiovol,"CODCOLCAMBIOVOL",svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          "TIPOVOLORIG",svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          "TIPOVOLDEST",svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ccv);
        init = 1;
    }
}

static void init_insccv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcolcambiovol[0].numcol;nc++) dvdcolcambiovol[0].c[nc].offset-=(size_t)&svdcolcambiovol;
    vdinsccv=abrecursordebug(INSCCV,1280);
    bindtodo(vdinsccv,"CODCOLCAMBIOVOL",svdcolcambiovol.codcolcambiovol,sizeof(svdcolcambiovol.codcolcambiovol),V10CADENA,
                          "TIPOVOLORIG",svdcolcambiovol.tipovolorig,sizeof(svdcolcambiovol.tipovolorig),V10CADENA,
                          "TIPOVOLDEST",svdcolcambiovol.tipovoldest,sizeof(svdcolcambiovol.tipovoldest),V10CADENA,
                          "CODCOMEN",&svdcolcambiovol.codcomen,sizeof(svdcolcambiovol.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ccv);
        init = 1;
    }
}

static void init_delccv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcolcambiovol[0].numcol;nc++) dvdcolcambiovol[0].c[nc].offset-=(size_t)&svdcolcambiovol;
    vddelccv=abrecursordebug(DELCCV,1280);
    bindtodo(vddelccv,"MIROWID",svdcolcambiovol.rowid,sizeof(svdcolcambiovol.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ccv);
        init = 1;
    }
}

diccionario *CCVdamediccionario(void)
{
     return(&dccv);
}

int CCVselcodcolcambiovol(char *codcolcambiovol,vdcolcambiovols *ccv)
{
  int vdret;
  if (vdselccvcodcolcambiovol==NULL) init_selccvcodcolcambiovol();
  memset(&svdcolcambiovol,0,sizeof(svdcolcambiovol));
  strcpy(svdcolcambiovol.codcolcambiovol,codcolcambiovol);
  vdret=ejefetchcursor(vdselccvcodcolcambiovol);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselccvcodcolcambiovol. vdret %d. \n",CCVlog(&svdcolcambiovol),vdret);
    return(VD_EERRORACLE);
   }
  *ccv=svdcolcambiovol;
  return(vdret);
}

int CCVbuscatipovolorig(char *codcolcambiovol,char *tipovolorig,vdcolcambiovols *ccv)
{
  int vdret;
  memset(&svdcolcambiovol,0,sizeof(svdcolcambiovol));
  strcpy(svdcolcambiovol.codcolcambiovol,codcolcambiovol);
  strcpy(svdcolcambiovol.tipovolorig,tipovolorig);
  if (vdselccvtipovolorig==NULL) init_selccvtipovolorig();
  vdret=ejefetchcursor(vdselccvtipovolorig);
  if (vdret==0) {
     *ccv=svdcolcambiovol;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselccvtipovolorig. vdret %d. \n",CCVlog(&svdcolcambiovol),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int CCVnexttipovolorig(vdcolcambiovols *ccv)
{
  int vdret;
  vdret=fetchcursor(vdselccvtipovolorig);
  if (vdret==0) {
     *ccv=svdcolcambiovol;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselccvtipovolorig. vdret %d. \n",CCVlog(&svdcolcambiovol),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselccvtipovolorig);
  return(VD_EERRORACLE);
}

int CCVselvdcolcambiovol(char *codcolcambiovol,char *tipovolorig,char *tipovoldest,vdcolcambiovols *ccv)
{
  int vdret;
  if (vdselccvvdcolcambiovol==NULL) init_selccvvdcolcambiovol();
  memset(&svdcolcambiovol,0,sizeof(svdcolcambiovol));
  strcpy(svdcolcambiovol.codcolcambiovol,codcolcambiovol);
  strcpy(svdcolcambiovol.tipovolorig,tipovolorig);
  strcpy(svdcolcambiovol.tipovoldest,tipovoldest);
  vdret=ejefetchcursor(vdselccvvdcolcambiovol);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselccvvdcolcambiovol. vdret %d. \n",CCVlog(&svdcolcambiovol),vdret);
    return(VD_EERRORACLE);
   }
  *ccv=svdcolcambiovol;
  return(vdret);
}

int CCVinsert(vdcolcambiovols *ccv,int error)
{
  int vdret;
  if (!vdinsccv) init_insccv();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",CCVlog(&svdcolcambiovol));
  svdcolcambiovol=*ccv;
  vdret=ejecutacursor(vdinsccv);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsccv);
     getcurerrornombre(vdinsccv->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CCVdel(vdcolcambiovols *ccv,int error)
{
  int vdret;
  svdcolcambiovol=*ccv;
  if (vddelccv==NULL) init_delccv();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",CCVlog(&svdcolcambiovol));
  vdret=ejecutacursor(vddelccv);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelccv);
     getcurerrornombre(vddelccv->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * CCVlog(vdcolcambiovols *ccv)
{
    sprintf(msglogCCV, "VDCOLCAMBIOVOL: codcolcambiovol %s tipovolorig %s tipovoldest %s ",ccv->codcolcambiovol,ccv->tipovolorig,ccv->tipovoldest);
    return(msglogCCV);
}

char * CCVdebug(vdcolcambiovols *ccv)
{
    debugestruct(&dccv,ccv,msgdebugCCV);
    return(msgdebugCCV);
}

