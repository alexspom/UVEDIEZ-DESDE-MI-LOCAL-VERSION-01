// Modulo generado automaticamente a partir de VDSCANMIRROR.DEF
//#***
//# VDSCANMIRROR.DEF - Generaci�n autom�tica del c�digo c para la tabla de Escaners Espejo
//#                        
//# Prop�sito: Funciones de acceso a la tabla VDSCANMIRROR
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 22-02-2010
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=SCM
//RECORRE=SCMAESTROS,REDSCANM,SCANNERM;WHERE=ACTIVO='S';ORDERBY=ORDEN;

#include "vd.h"
#define SELSCMSCMAESTROS "SELECT VDSCANMIRROR.ROWID,VDSCANMIRROR.ORDEN,VDSCANMIRROR.REDSCAN, "\
                    " VDSCANMIRROR.SCANNER,VDSCANMIRROR.REDSCANM,VDSCANMIRROR.SCANNERM, "\
                    " VDSCANMIRROR.ACTIVO,VDSCANMIRROR.CODCOMEN,VDSCANMIRROR.CODOPEMODIF, "\
                    " VDSCANMIRROR.FECMODIF,VDSCANMIRROR.HORAMODIF "\
        " FROM VDSCANMIRROR"\
        " WHERE "\
               " VDSCANMIRROR.REDSCANM=:REDSCANM "\
               " AND VDSCANMIRROR.SCANNERM=:SCANNERM "\
              "  AND ACTIVO='S' "\
        " ORDER BY ORDEN "
static v10cursors *vdselscmscmaestros;

#define SELSCMVDSCANMIRROR "SELECT VDSCANMIRROR.ROWID,VDSCANMIRROR.ORDEN,VDSCANMIRROR.REDSCAN, "\
                    " VDSCANMIRROR.SCANNER,VDSCANMIRROR.REDSCANM,VDSCANMIRROR.SCANNERM, "\
                    " VDSCANMIRROR.ACTIVO,VDSCANMIRROR.CODCOMEN,VDSCANMIRROR.CODOPEMODIF, "\
                    " VDSCANMIRROR.FECMODIF,VDSCANMIRROR.HORAMODIF "\
        " FROM VDSCANMIRROR"
static v10cursors *vdselscmvdscanmirror;

static vdscanmirrors svdscanmirror;

static diccols colvdscanmirror[]={
	{"ROWID",V10CADENA,(size_t)&svdscanmirror.rowid,sizeof(svdscanmirror.rowid)},
	{"ORDEN",V10LONG,(size_t)&svdscanmirror.orden,sizeof(svdscanmirror.orden)},
	{"REDSCAN",V10LONG,(size_t)&svdscanmirror.redscan,sizeof(svdscanmirror.redscan)},
	{"SCANNER",V10LONG,(size_t)&svdscanmirror.scanner,sizeof(svdscanmirror.scanner)},
	{"REDSCANM",V10LONG,(size_t)&svdscanmirror.redscanm,sizeof(svdscanmirror.redscanm)},
	{"SCANNERM",V10LONG,(size_t)&svdscanmirror.scannerm,sizeof(svdscanmirror.scannerm)},
	{"ACTIVO",V10CADENA,(size_t)&svdscanmirror.activo,sizeof(svdscanmirror.activo)},
	{"CODCOMEN",V10LONG,(size_t)&svdscanmirror.codcomen,sizeof(svdscanmirror.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdscanmirror.codopemodif,sizeof(svdscanmirror.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdscanmirror.fecmodif,sizeof(svdscanmirror.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdscanmirror.horamodif,sizeof(svdscanmirror.horamodif)}
	};
static diccionarios dvdscanmirror[]={
    {colvdscanmirror,11}
};
diccionario dscm={dvdscanmirror,1};

static char msglogSCM[LCADENA];
static char msgdebugSCM[LCADENABIG];
static int init=0;


static void fin_vd_scm(void)
{
if (vdselscmscmaestros) {
    liberacursor(vdselscmscmaestros);
    vdselscmscmaestros = NULL;
}
if (vdselscmvdscanmirror) {
    liberacursor(vdselscmvdscanmirror);
    vdselscmvdscanmirror = NULL;
}
}
static void init_selscmscmaestros(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanmirror[0].numcol;nc++) dvdscanmirror[0].c[nc].offset-=(size_t)&svdscanmirror;
    vdselscmscmaestros=abrecursordebug(SELSCMSCMAESTROS,1280);
    definetodo(vdselscmscmaestros,svdscanmirror.rowid,sizeof(svdscanmirror.rowid),V10CADENA,
                          &svdscanmirror.orden,sizeof(svdscanmirror.orden),V10LONG,
                          &svdscanmirror.redscan,sizeof(svdscanmirror.redscan),V10LONG,
                          &svdscanmirror.scanner,sizeof(svdscanmirror.scanner),V10LONG,
                          &svdscanmirror.redscanm,sizeof(svdscanmirror.redscanm),V10LONG,
                          &svdscanmirror.scannerm,sizeof(svdscanmirror.scannerm),V10LONG,
                          svdscanmirror.activo,sizeof(svdscanmirror.activo),V10CADENA,
                          &svdscanmirror.codcomen,sizeof(svdscanmirror.codcomen),V10LONG,
                          svdscanmirror.codopemodif,sizeof(svdscanmirror.codopemodif),V10CADENA,
                          &svdscanmirror.fecmodif,sizeof(svdscanmirror.fecmodif),V10LONG,
                          svdscanmirror.horamodif,sizeof(svdscanmirror.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselscmscmaestros,"REDSCANM",&svdscanmirror.redscanm,sizeof(svdscanmirror.redscanm),V10LONG,
                          "SCANNERM",&svdscanmirror.scannerm,sizeof(svdscanmirror.scannerm),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scm);
        init = 1;
    }
}

static void init_selscmvdscanmirror(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanmirror[0].numcol;nc++) dvdscanmirror[0].c[nc].offset-=(size_t)&svdscanmirror;
    vdselscmvdscanmirror=abrecursordebug(SELSCMVDSCANMIRROR,1280);
    definetodo(vdselscmvdscanmirror,svdscanmirror.rowid,sizeof(svdscanmirror.rowid),V10CADENA,
                          &svdscanmirror.orden,sizeof(svdscanmirror.orden),V10LONG,
                          &svdscanmirror.redscan,sizeof(svdscanmirror.redscan),V10LONG,
                          &svdscanmirror.scanner,sizeof(svdscanmirror.scanner),V10LONG,
                          &svdscanmirror.redscanm,sizeof(svdscanmirror.redscanm),V10LONG,
                          &svdscanmirror.scannerm,sizeof(svdscanmirror.scannerm),V10LONG,
                          svdscanmirror.activo,sizeof(svdscanmirror.activo),V10CADENA,
                          &svdscanmirror.codcomen,sizeof(svdscanmirror.codcomen),V10LONG,
                          svdscanmirror.codopemodif,sizeof(svdscanmirror.codopemodif),V10CADENA,
                          &svdscanmirror.fecmodif,sizeof(svdscanmirror.fecmodif),V10LONG,
                          svdscanmirror.horamodif,sizeof(svdscanmirror.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselscmvdscanmirror,NULL);
    if (init == 0) {
        atexit(fin_vd_scm);
        init = 1;
    }
}

diccionario *SCMdamediccionario(void)
{
     return(&dscm);
}

int SCMbuscascmaestros(long redscanm,long scannerm,vdscanmirrors *scm)
{
  int vdret;
  memset(&svdscanmirror,0,sizeof(svdscanmirror));
  svdscanmirror.redscanm=redscanm;
  svdscanmirror.scannerm=scannerm;
  if (vdselscmscmaestros==NULL) init_selscmscmaestros();
  vdret=ejefetchcursor(vdselscmscmaestros);
  if (vdret==0) {
     *scm=svdscanmirror;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselscmscmaestros. vdret %d. \n",SCMlog(&svdscanmirror),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SCMnextscmaestros(vdscanmirrors *scm)
{
  int vdret;
  vdret=fetchcursor(vdselscmscmaestros);
  if (vdret==0) {
     *scm=svdscanmirror;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselscmscmaestros. vdret %d. \n",SCMlog(&svdscanmirror),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselscmscmaestros);
  return(VD_EERRORACLE);
}

int SCMselvdscanmirror(vdscanmirrors *scm)
{
  int vdret;
  if (vdselscmvdscanmirror==NULL) init_selscmvdscanmirror();
  memset(&svdscanmirror,0,sizeof(svdscanmirror));
  vdret=ejefetchcursor(vdselscmvdscanmirror);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselscmvdscanmirror. vdret %d. \n",SCMlog(&svdscanmirror),vdret);
    return(VD_EERRORACLE);
   }
  *scm=svdscanmirror;
  return(vdret);
}

char * SCMlog(vdscanmirrors *scm)
{
    sprintf(msglogSCM, "VDSCANMIRROR: ");
    return(msglogSCM);
}

char * SCMdebug(vdscanmirrors *scm)
{
    debugestruct(&dscm,scm,msgdebugSCM);
    return(msgdebugSCM);
}

