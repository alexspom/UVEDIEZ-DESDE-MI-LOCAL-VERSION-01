// Modulo generado automaticamente a partir de VDIMPRETIPO.DEF
//#***
//# VDIMPRETIPO.c - Generación automática del código c para la tabla de Tipos de Impresiones                                                    
//# 
//# Propósito: Funciones de acceso a la tabla VDIMPRETIPO
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=IMTP

#include "vd.h"
#define SELIMTPVDIMPRETIPO "SELECT VDIMPRETIPO.ROWID,VDIMPRETIPO.TIPOIMPRE,VDIMPRETIPO.DESTIPOIMPRE, "\
                    " VDIMPRETIPO.ACTIVO,VDIMPRETIPO.TIPODOC,VDIMPRETIPO.CODOPEMODIF, "\
                    " VDIMPRETIPO.FECMODIF,VDIMPRETIPO.HORAMODIF,VDIMPRETIPO.CODCOMEN "\
        " FROM VDIMPRETIPO"\
        " WHERE "\
               " VDIMPRETIPO.TIPOIMPRE=:TIPOIMPRE "
static v10cursors *vdselimtpvdimpretipo;

static vdimpretipos svdimpretipo;

static diccols colvdimpretipo[]={
	{"ROWID",V10CADENA,(size_t)&svdimpretipo.rowid,sizeof(svdimpretipo.rowid)},
	{"TIPOIMPRE",V10CADENA,(size_t)&svdimpretipo.tipoimpre,sizeof(svdimpretipo.tipoimpre)},
	{"DESTIPOIMPRE",V10CADENA,(size_t)&svdimpretipo.destipoimpre,sizeof(svdimpretipo.destipoimpre)},
	{"ACTIVO",V10CADENA,(size_t)&svdimpretipo.activo,sizeof(svdimpretipo.activo)},
	{"TIPODOC",V10CADENA,(size_t)&svdimpretipo.tipodoc,sizeof(svdimpretipo.tipodoc)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdimpretipo.codopemodif,sizeof(svdimpretipo.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdimpretipo.fecmodif,sizeof(svdimpretipo.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdimpretipo.horamodif,sizeof(svdimpretipo.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdimpretipo.codcomen,sizeof(svdimpretipo.codcomen)}
	};
static diccionarios dvdimpretipo[]={
    {colvdimpretipo,9}
};
diccionario dimtp={dvdimpretipo,1};

static char msglogIMTP[LCADENA];
static char msgdebugIMTP[LCADENABIG];
static int init=0;


static void fin_vd_imtp(void)
{
if (vdselimtpvdimpretipo) {
    liberacursor(vdselimtpvdimpretipo);
    vdselimtpvdimpretipo = NULL;
}
}
static void init_selimtpvdimpretipo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpretipo[0].numcol;nc++) dvdimpretipo[0].c[nc].offset-=(size_t)&svdimpretipo;
    vdselimtpvdimpretipo=abrecursordebug(SELIMTPVDIMPRETIPO,1280);
    definetodo(vdselimtpvdimpretipo,svdimpretipo.rowid,sizeof(svdimpretipo.rowid),V10CADENA,
                          svdimpretipo.tipoimpre,sizeof(svdimpretipo.tipoimpre),V10CADENA,
                          svdimpretipo.destipoimpre,sizeof(svdimpretipo.destipoimpre),V10CADENA,
                          svdimpretipo.activo,sizeof(svdimpretipo.activo),V10CADENA,
                          svdimpretipo.tipodoc,sizeof(svdimpretipo.tipodoc),V10CADENA,
                          svdimpretipo.codopemodif,sizeof(svdimpretipo.codopemodif),V10CADENA,
                          &svdimpretipo.fecmodif,sizeof(svdimpretipo.fecmodif),V10LONG,
                          svdimpretipo.horamodif,sizeof(svdimpretipo.horamodif),V10CADENA,
                          &svdimpretipo.codcomen,sizeof(svdimpretipo.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimtpvdimpretipo,"TIPOIMPRE",svdimpretipo.tipoimpre,sizeof(svdimpretipo.tipoimpre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imtp);
        init = 1;
    }
}

diccionario *IMTPdamediccionario(void)
{
     return(&dimtp);
}

int IMTPselvdimpretipo(char *tipoimpre,vdimpretipos *imtp)
{
  int vdret;
  if (vdselimtpvdimpretipo==NULL) init_selimtpvdimpretipo();
  memset(&svdimpretipo,0,sizeof(svdimpretipo));
  strcpy(svdimpretipo.tipoimpre,tipoimpre);
  vdret=ejefetchcursor(vdselimtpvdimpretipo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimtpvdimpretipo. vdret %d. \n",IMTPlog(&svdimpretipo),vdret);
    return(VD_EERRORACLE);
   }
  *imtp=svdimpretipo;
  return(vdret);
}

char * IMTPlog(vdimpretipos *imtp)
{
    sprintf(msglogIMTP, "VDIMPRETIPO: tipoimpre %s ",imtp->tipoimpre);
    return(msglogIMTP);
}

char * IMTPdebug(vdimpretipos *imtp)
{
    debugestruct(&dimtp,imtp,msgdebugIMTP);
    return(msgdebugIMTP);
}

