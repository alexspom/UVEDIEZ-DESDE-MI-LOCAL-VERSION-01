// Modulo generado automaticamente a partir de VDAGENCIA.DEF
//#***
//# VDAGENCIA.DEF - Generación automática del código c para la tabla de Agencias
//#                        
//# Propósito: Funciones de acceso a la tabla VDAGENCIA
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 12-03-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=AG
//CLAVE=CODAGE,CODAGE

#include "vd.h"
#define SELAGCODAGE "SELECT VDAGENCIA.ROWID,VDAGENCIA.CODAGE,VDAGENCIA.DESAGE, "\
                    " VDAGENCIA.GRUPOAGE,VDAGENCIA.SERVICIO,VDAGENCIA.PRODUCTO, "\
                    " VDAGENCIA.SUFIJODOC,VDAGENCIA.NUMBOL,VDAGENCIA.NUMALBA, "\
                    " VDAGENCIA.NUMFAC,VDAGENCIA.PUERTO,VDAGENCIA.BUZONOUT, "\
                    " VDAGENCIA.VDEXTRA,VDAGENCIA.CODOPEMODIF,VDAGENCIA.FECMODIF, "\
                    " VDAGENCIA.HORAMODIF,VDAGENCIA.CODCOMEN,VDAGENCIA.CODAGERECEP, "\
                    " VDAGENCIA.NUMBOLIND,VDAGENCIA.AGRUPASERIE,VDAGENCIA.CODAGEEXP, "\
                    " VDAGENCIA.NOMBRESECUEN,VDAGENCIA.NOMBRELOGO,VDAGENCIA.CLAVEINCI "\
        " FROM VDAGENCIA"\
        " WHERE "\
               " VDAGENCIA.CODAGE=:CODAGE "
static v10cursors *vdselagcodage;

#define SELAGVDAGENCIA "SELECT VDAGENCIA.ROWID,VDAGENCIA.CODAGE,VDAGENCIA.DESAGE, "\
                    " VDAGENCIA.GRUPOAGE,VDAGENCIA.SERVICIO,VDAGENCIA.PRODUCTO, "\
                    " VDAGENCIA.SUFIJODOC,VDAGENCIA.NUMBOL,VDAGENCIA.NUMALBA, "\
                    " VDAGENCIA.NUMFAC,VDAGENCIA.PUERTO,VDAGENCIA.BUZONOUT, "\
                    " VDAGENCIA.VDEXTRA,VDAGENCIA.CODOPEMODIF,VDAGENCIA.FECMODIF, "\
                    " VDAGENCIA.HORAMODIF,VDAGENCIA.CODCOMEN,VDAGENCIA.CODAGERECEP, "\
                    " VDAGENCIA.NUMBOLIND,VDAGENCIA.AGRUPASERIE,VDAGENCIA.CODAGEEXP, "\
                    " VDAGENCIA.NOMBRESECUEN,VDAGENCIA.NOMBRELOGO,VDAGENCIA.CLAVEINCI "\
        " FROM VDAGENCIA"\
        " WHERE "\
               " VDAGENCIA.CODAGE=:CODAGE "
static v10cursors *vdselagvdagencia;

static vdagencias svdagencia;

static diccols colvdagencia[]={
	{"ROWID",V10CADENA,(size_t)&svdagencia.rowid,sizeof(svdagencia.rowid)},
	{"CODAGE",V10CADENA,(size_t)&svdagencia.codage,sizeof(svdagencia.codage)},
	{"DESAGE",V10CADENA,(size_t)&svdagencia.desage,sizeof(svdagencia.desage)},
	{"GRUPOAGE",V10CADENA,(size_t)&svdagencia.grupoage,sizeof(svdagencia.grupoage)},
	{"SERVICIO",V10CADENA,(size_t)&svdagencia.servicio,sizeof(svdagencia.servicio)},
	{"PRODUCTO",V10CADENA,(size_t)&svdagencia.producto,sizeof(svdagencia.producto)},
	{"SUFIJODOC",V10CADENA,(size_t)&svdagencia.sufijodoc,sizeof(svdagencia.sufijodoc)},
	{"NUMBOL",V10LONG,(size_t)&svdagencia.numbol,sizeof(svdagencia.numbol)},
	{"NUMALBA",V10LONG,(size_t)&svdagencia.numalba,sizeof(svdagencia.numalba)},
	{"NUMFAC",V10LONG,(size_t)&svdagencia.numfac,sizeof(svdagencia.numfac)},
	{"PUERTO",V10LONG,(size_t)&svdagencia.puerto,sizeof(svdagencia.puerto)},
	{"BUZONOUT",V10CADENA,(size_t)&svdagencia.buzonout,sizeof(svdagencia.buzonout)},
	{"VDEXTRA",V10CADENA,(size_t)&svdagencia.vdextra,sizeof(svdagencia.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdagencia.codopemodif,sizeof(svdagencia.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdagencia.fecmodif,sizeof(svdagencia.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdagencia.horamodif,sizeof(svdagencia.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdagencia.codcomen,sizeof(svdagencia.codcomen)},
	{"CODAGERECEP",V10CADENA,(size_t)&svdagencia.codagerecep,sizeof(svdagencia.codagerecep)},
	{"NUMBOLIND",V10LONG,(size_t)&svdagencia.numbolind,sizeof(svdagencia.numbolind)},
	{"AGRUPASERIE",V10CADENA,(size_t)&svdagencia.agrupaserie,sizeof(svdagencia.agrupaserie)},
	{"CODAGEEXP",V10CADENA,(size_t)&svdagencia.codageexp,sizeof(svdagencia.codageexp)},
	{"NOMBRESECUEN",V10CADENA,(size_t)&svdagencia.nombresecuen,sizeof(svdagencia.nombresecuen)},
	{"NOMBRELOGO",V10CADENA,(size_t)&svdagencia.nombrelogo,sizeof(svdagencia.nombrelogo)},
	{"CLAVEINCI",V10LONG,(size_t)&svdagencia.claveinci,sizeof(svdagencia.claveinci)}
	};
static diccionarios dvdagencia[]={
    {colvdagencia,24}
};
diccionario dag={dvdagencia,1};

static char msglogAG[LCADENA];
static char msgdebugAG[LCADENABIG];
static int init=0;


static void fin_vd_ag(void)
{
if (vdselagcodage) {
    liberacursor(vdselagcodage);
    vdselagcodage = NULL;
}
if (vdselagvdagencia) {
    liberacursor(vdselagvdagencia);
    vdselagvdagencia = NULL;
}
}
static void init_selagcodage(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdagencia[0].numcol;nc++) dvdagencia[0].c[nc].offset-=(size_t)&svdagencia;
    vdselagcodage=abrecursordebug(SELAGCODAGE,1280);
    definetodo(vdselagcodage,svdagencia.rowid,sizeof(svdagencia.rowid),V10CADENA,
                          svdagencia.codage,sizeof(svdagencia.codage),V10CADENA,
                          svdagencia.desage,sizeof(svdagencia.desage),V10CADENA,
                          svdagencia.grupoage,sizeof(svdagencia.grupoage),V10CADENA,
                          svdagencia.servicio,sizeof(svdagencia.servicio),V10CADENA,
                          svdagencia.producto,sizeof(svdagencia.producto),V10CADENA,
                          svdagencia.sufijodoc,sizeof(svdagencia.sufijodoc),V10CADENA,
                          &svdagencia.numbol,sizeof(svdagencia.numbol),V10LONG,
                          &svdagencia.numalba,sizeof(svdagencia.numalba),V10LONG,
                          &svdagencia.numfac,sizeof(svdagencia.numfac),V10LONG,
                          &svdagencia.puerto,sizeof(svdagencia.puerto),V10LONG,
                          svdagencia.buzonout,sizeof(svdagencia.buzonout),V10CADENA,
                          svdagencia.vdextra,sizeof(svdagencia.vdextra),V10CADENA,
                          svdagencia.codopemodif,sizeof(svdagencia.codopemodif),V10CADENA,
                          &svdagencia.fecmodif,sizeof(svdagencia.fecmodif),V10LONG,
                          svdagencia.horamodif,sizeof(svdagencia.horamodif),V10CADENA,
                          &svdagencia.codcomen,sizeof(svdagencia.codcomen),V10LONG,
                          svdagencia.codagerecep,sizeof(svdagencia.codagerecep),V10CADENA,
                          &svdagencia.numbolind,sizeof(svdagencia.numbolind),V10LONG,
                          svdagencia.agrupaserie,sizeof(svdagencia.agrupaserie),V10CADENA,
                          svdagencia.codageexp,sizeof(svdagencia.codageexp),V10CADENA,
                          svdagencia.nombresecuen,sizeof(svdagencia.nombresecuen),V10CADENA,
                          svdagencia.nombrelogo,sizeof(svdagencia.nombrelogo),V10CADENA,
                          &svdagencia.claveinci,sizeof(svdagencia.claveinci),V10LONG,
                          NULL);
    bindtodo(vdselagcodage,"CODAGE",svdagencia.codage,sizeof(svdagencia.codage),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ag);
        init = 1;
    }
}

static void init_selagvdagencia(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdagencia[0].numcol;nc++) dvdagencia[0].c[nc].offset-=(size_t)&svdagencia;
    vdselagvdagencia=abrecursordebug(SELAGVDAGENCIA,1280);
    definetodo(vdselagvdagencia,svdagencia.rowid,sizeof(svdagencia.rowid),V10CADENA,
                          svdagencia.codage,sizeof(svdagencia.codage),V10CADENA,
                          svdagencia.desage,sizeof(svdagencia.desage),V10CADENA,
                          svdagencia.grupoage,sizeof(svdagencia.grupoage),V10CADENA,
                          svdagencia.servicio,sizeof(svdagencia.servicio),V10CADENA,
                          svdagencia.producto,sizeof(svdagencia.producto),V10CADENA,
                          svdagencia.sufijodoc,sizeof(svdagencia.sufijodoc),V10CADENA,
                          &svdagencia.numbol,sizeof(svdagencia.numbol),V10LONG,
                          &svdagencia.numalba,sizeof(svdagencia.numalba),V10LONG,
                          &svdagencia.numfac,sizeof(svdagencia.numfac),V10LONG,
                          &svdagencia.puerto,sizeof(svdagencia.puerto),V10LONG,
                          svdagencia.buzonout,sizeof(svdagencia.buzonout),V10CADENA,
                          svdagencia.vdextra,sizeof(svdagencia.vdextra),V10CADENA,
                          svdagencia.codopemodif,sizeof(svdagencia.codopemodif),V10CADENA,
                          &svdagencia.fecmodif,sizeof(svdagencia.fecmodif),V10LONG,
                          svdagencia.horamodif,sizeof(svdagencia.horamodif),V10CADENA,
                          &svdagencia.codcomen,sizeof(svdagencia.codcomen),V10LONG,
                          svdagencia.codagerecep,sizeof(svdagencia.codagerecep),V10CADENA,
                          &svdagencia.numbolind,sizeof(svdagencia.numbolind),V10LONG,
                          svdagencia.agrupaserie,sizeof(svdagencia.agrupaserie),V10CADENA,
                          svdagencia.codageexp,sizeof(svdagencia.codageexp),V10CADENA,
                          svdagencia.nombresecuen,sizeof(svdagencia.nombresecuen),V10CADENA,
                          svdagencia.nombrelogo,sizeof(svdagencia.nombrelogo),V10CADENA,
                          &svdagencia.claveinci,sizeof(svdagencia.claveinci),V10LONG,
                          NULL);
    bindtodo(vdselagvdagencia,"CODAGE",svdagencia.codage,sizeof(svdagencia.codage),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_ag);
        init = 1;
    }
}

diccionario *AGdamediccionario(void)
{
     return(&dag);
}

int AGselcodage(char *codage,vdagencias *ag)
{
  int vdret;
  if (vdselagcodage==NULL) init_selagcodage();
  memset(&svdagencia,0,sizeof(svdagencia));
  strcpy(svdagencia.codage,codage);
  vdret=ejefetchcursor(vdselagcodage);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselagcodage. vdret %d. \n",AGlog(&svdagencia),vdret);
    return(VD_EERRORACLE);
   }
  *ag=svdagencia;
  return(vdret);
}

int AGselvdagencia(char *codage,vdagencias *ag)
{
  int vdret;
  if (vdselagvdagencia==NULL) init_selagvdagencia();
  memset(&svdagencia,0,sizeof(svdagencia));
  strcpy(svdagencia.codage,codage);
  vdret=ejefetchcursor(vdselagvdagencia);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselagvdagencia. vdret %d. \n",AGlog(&svdagencia),vdret);
    return(VD_EERRORACLE);
   }
  *ag=svdagencia;
  return(vdret);
}

char * AGlog(vdagencias *ag)
{
    sprintf(msglogAG, "VDAGENCIA: codage %s ",ag->codage);
    return(msglogAG);
}

char * AGdebug(vdagencias *ag)
{
    debugestruct(&dag,ag,msgdebugAG);
    return(msgdebugAG);
}

