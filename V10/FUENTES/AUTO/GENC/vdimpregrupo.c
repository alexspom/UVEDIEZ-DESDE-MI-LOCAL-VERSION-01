// Modulo generado automaticamente a partir de VDIMPREGRUPO.DEF
//#***
//# VDIMPREGRUPO.c - Generaci�n autom�tica del c�digo c para la tabla de Grupos de Impresoras                                                   
//# 
//# Prop�sito: Funciones de acceso a la tabla VDIMPREGRUPO
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=IMGR

#include "vd.h"
#define SELIMGRVDIMPREGRUPO "SELECT VDIMPREGRUPO.ROWID,VDIMPREGRUPO.GRUPOIMPRE,VDIMPREGRUPO.DESGRUPOIMPRE, "\
                    " VDIMPREGRUPO.ACTIVO,VDIMPREGRUPO.CODOPEMODIF,VDIMPREGRUPO.FECMODIF, "\
                    " VDIMPREGRUPO.HORAMODIF,VDIMPREGRUPO.CODCOMEN "\
        " FROM VDIMPREGRUPO"\
        " WHERE "\
               " VDIMPREGRUPO.GRUPOIMPRE=:GRUPOIMPRE "
static v10cursors *vdselimgrvdimpregrupo;

static vdimpregrupos svdimpregrupo;

static diccols colvdimpregrupo[]={
	{"ROWID",V10CADENA,(size_t)&svdimpregrupo.rowid,sizeof(svdimpregrupo.rowid)},
	{"GRUPOIMPRE",V10CADENA,(size_t)&svdimpregrupo.grupoimpre,sizeof(svdimpregrupo.grupoimpre)},
	{"DESGRUPOIMPRE",V10CADENA,(size_t)&svdimpregrupo.desgrupoimpre,sizeof(svdimpregrupo.desgrupoimpre)},
	{"ACTIVO",V10CADENA,(size_t)&svdimpregrupo.activo,sizeof(svdimpregrupo.activo)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdimpregrupo.codopemodif,sizeof(svdimpregrupo.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdimpregrupo.fecmodif,sizeof(svdimpregrupo.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdimpregrupo.horamodif,sizeof(svdimpregrupo.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdimpregrupo.codcomen,sizeof(svdimpregrupo.codcomen)}
	};
static diccionarios dvdimpregrupo[]={
    {colvdimpregrupo,8}
};
diccionario dimgr={dvdimpregrupo,1};

static char msglogIMGR[LCADENA];
static char msgdebugIMGR[LCADENABIG];
static int init=0;


static void fin_vd_imgr(void)
{
if (vdselimgrvdimpregrupo) {
    liberacursor(vdselimgrvdimpregrupo);
    vdselimgrvdimpregrupo = NULL;
}
}
static void init_selimgrvdimpregrupo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpregrupo[0].numcol;nc++) dvdimpregrupo[0].c[nc].offset-=(size_t)&svdimpregrupo;
    vdselimgrvdimpregrupo=abrecursordebug(SELIMGRVDIMPREGRUPO,1280);
    definetodo(vdselimgrvdimpregrupo,svdimpregrupo.rowid,sizeof(svdimpregrupo.rowid),V10CADENA,
                          svdimpregrupo.grupoimpre,sizeof(svdimpregrupo.grupoimpre),V10CADENA,
                          svdimpregrupo.desgrupoimpre,sizeof(svdimpregrupo.desgrupoimpre),V10CADENA,
                          svdimpregrupo.activo,sizeof(svdimpregrupo.activo),V10CADENA,
                          svdimpregrupo.codopemodif,sizeof(svdimpregrupo.codopemodif),V10CADENA,
                          &svdimpregrupo.fecmodif,sizeof(svdimpregrupo.fecmodif),V10LONG,
                          svdimpregrupo.horamodif,sizeof(svdimpregrupo.horamodif),V10CADENA,
                          &svdimpregrupo.codcomen,sizeof(svdimpregrupo.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimgrvdimpregrupo,"GRUPOIMPRE",svdimpregrupo.grupoimpre,sizeof(svdimpregrupo.grupoimpre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imgr);
        init = 1;
    }
}

diccionario *IMGRdamediccionario(void)
{
     return(&dimgr);
}

int IMGRselvdimpregrupo(char *grupoimpre,vdimpregrupos *imgr)
{
  int vdret;
  if (vdselimgrvdimpregrupo==NULL) init_selimgrvdimpregrupo();
  memset(&svdimpregrupo,0,sizeof(svdimpregrupo));
  strcpy(svdimpregrupo.grupoimpre,grupoimpre);
  vdret=ejefetchcursor(vdselimgrvdimpregrupo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimgrvdimpregrupo. vdret %d. \n",IMGRlog(&svdimpregrupo),vdret);
    return(VD_EERRORACLE);
   }
  *imgr=svdimpregrupo;
  return(vdret);
}

char * IMGRlog(vdimpregrupos *imgr)
{
    sprintf(msglogIMGR, "VDIMPREGRUPO: grupoimpre %s ",imgr->grupoimpre);
    return(msglogIMGR);
}

char * IMGRdebug(vdimpregrupos *imgr)
{
    debugestruct(&dimgr,imgr,msgdebugIMGR);
    return(msgdebugIMGR);
}

