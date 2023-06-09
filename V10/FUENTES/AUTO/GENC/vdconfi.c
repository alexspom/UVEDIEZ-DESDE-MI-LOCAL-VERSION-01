// Modulo generado automaticamente a partir de VDCONFI.DEF
//# M�dulo : VDCONFI.DEF                                                        
//# Funci�n: Generaci�n automatica de rutinas C tabla VDCONFI
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 18-12-2007                                              
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=CONF;
//CLAVE=PROPIEDAD,PROPIEDAD;WHERE=ACTIVO='S';
//
//ORADEBUG=0

#include "vd.h"
#define SELCONFPROPIEDAD "SELECT VDCONFI.ROWID,VDCONFI.PROPIEDAD,VDCONFI.GRUPOPROP, "\
                    " VDCONFI.COMENTARIO,VDCONFI.TIPODATO,VDCONFI.VALOR, "\
                    " VDCONFI.ACTIVO,VDCONFI.PRIVILEGIOSVER,VDCONFI.PRIVILEGIOSMOD, "\
                    " VDCONFI.PERMITIDOS,VDCONFI.CODOPEMODIF,VDCONFI.FECMODIF, "\
                    " VDCONFI.HORAMODIF,VDCONFI.CODCOMEN "\
        " FROM VDCONFI"\
        " WHERE "\
               " VDCONFI.PROPIEDAD=:PROPIEDAD  AND INSTANCIA='GLOBAL'"\
              "  AND ACTIVO='S' "
static v10cursors *vdselconfpropiedad;

#define SELCONFVDCONFI "SELECT VDCONFI.ROWID,VDCONFI.PROPIEDAD,VDCONFI.GRUPOPROP, "\
                    " VDCONFI.COMENTARIO,VDCONFI.TIPODATO,VDCONFI.VALOR, "\
                    " VDCONFI.ACTIVO,VDCONFI.PRIVILEGIOSVER,VDCONFI.PRIVILEGIOSMOD, "\
                    " VDCONFI.PERMITIDOS,VDCONFI.CODOPEMODIF,VDCONFI.FECMODIF, "\
                    " VDCONFI.HORAMODIF,VDCONFI.CODCOMEN "\
        " FROM VDCONFI"\
        " WHERE "\
               " VDCONFI.PROPIEDAD=:PROPIEDAD  AND INSTANCIA='GLOBAL'"
static v10cursors *vdselconfvdconfi;

static vdconfis svdconfi;

static diccols colvdconfi[]={
	{"ROWID",V10CADENA,(size_t)&svdconfi.rowid,sizeof(svdconfi.rowid)},
	{"PROPIEDAD",V10CADENA,(size_t)&svdconfi.propiedad,sizeof(svdconfi.propiedad)},
	{"GRUPOPROP",V10CADENA,(size_t)&svdconfi.grupoprop,sizeof(svdconfi.grupoprop)},
	{"COMENTARIO",V10CADENA,(size_t)&svdconfi.comentario,sizeof(svdconfi.comentario)},
	{"TIPODATO",V10CADENA,(size_t)&svdconfi.tipodato,sizeof(svdconfi.tipodato)},
	{"VALOR",V10CADENA,(size_t)&svdconfi.valor,sizeof(svdconfi.valor)},
	{"ACTIVO",V10CADENA,(size_t)&svdconfi.activo,sizeof(svdconfi.activo)},
	{"PRIVILEGIOSVER",V10CADENA,(size_t)&svdconfi.privilegiosver,sizeof(svdconfi.privilegiosver)},
	{"PRIVILEGIOSMOD",V10CADENA,(size_t)&svdconfi.privilegiosmod,sizeof(svdconfi.privilegiosmod)},
	{"PERMITIDOS",V10CADENA,(size_t)&svdconfi.permitidos,sizeof(svdconfi.permitidos)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdconfi.codopemodif,sizeof(svdconfi.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdconfi.fecmodif,sizeof(svdconfi.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdconfi.horamodif,sizeof(svdconfi.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdconfi.codcomen,sizeof(svdconfi.codcomen)}
	};
static diccionarios dvdconfi[]={
    {colvdconfi,14}
};
diccionario dconf={dvdconfi,1};

static char msglogCONF[LCADENA];
static char msgdebugCONF[LCADENABIG];
static int init=0;


static void fin_vd_conf(void)
{
if (vdselconfpropiedad) {
    liberacursor(vdselconfpropiedad);
    vdselconfpropiedad = NULL;
}
if (vdselconfvdconfi) {
    liberacursor(vdselconfvdconfi);
    vdselconfvdconfi = NULL;
}
}
static void init_selconfpropiedad(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconfi[0].numcol;nc++) dvdconfi[0].c[nc].offset-=(size_t)&svdconfi;
    vdselconfpropiedad=abrecursordebug(SELCONFPROPIEDAD,0);
    definetodo(vdselconfpropiedad,svdconfi.rowid,sizeof(svdconfi.rowid),V10CADENA,
                          svdconfi.propiedad,sizeof(svdconfi.propiedad),V10CADENA,
                          svdconfi.grupoprop,sizeof(svdconfi.grupoprop),V10CADENA,
                          svdconfi.comentario,sizeof(svdconfi.comentario),V10CADENA,
                          svdconfi.tipodato,sizeof(svdconfi.tipodato),V10CADENA,
                          svdconfi.valor,sizeof(svdconfi.valor),V10CADENA,
                          svdconfi.activo,sizeof(svdconfi.activo),V10CADENA,
                          svdconfi.privilegiosver,sizeof(svdconfi.privilegiosver),V10CADENA,
                          svdconfi.privilegiosmod,sizeof(svdconfi.privilegiosmod),V10CADENA,
                          svdconfi.permitidos,sizeof(svdconfi.permitidos),V10CADENA,
                          svdconfi.codopemodif,sizeof(svdconfi.codopemodif),V10CADENA,
                          &svdconfi.fecmodif,sizeof(svdconfi.fecmodif),V10LONG,
                          svdconfi.horamodif,sizeof(svdconfi.horamodif),V10CADENA,
                          &svdconfi.codcomen,sizeof(svdconfi.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselconfpropiedad,"PROPIEDAD",svdconfi.propiedad,sizeof(svdconfi.propiedad),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_conf);
        init = 1;
    }
}

static void init_selconfvdconfi(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconfi[0].numcol;nc++) dvdconfi[0].c[nc].offset-=(size_t)&svdconfi;
    vdselconfvdconfi=abrecursordebug(SELCONFVDCONFI,0);
    definetodo(vdselconfvdconfi,svdconfi.rowid,sizeof(svdconfi.rowid),V10CADENA,
                          svdconfi.propiedad,sizeof(svdconfi.propiedad),V10CADENA,
                          svdconfi.grupoprop,sizeof(svdconfi.grupoprop),V10CADENA,
                          svdconfi.comentario,sizeof(svdconfi.comentario),V10CADENA,
                          svdconfi.tipodato,sizeof(svdconfi.tipodato),V10CADENA,
                          svdconfi.valor,sizeof(svdconfi.valor),V10CADENA,
                          svdconfi.activo,sizeof(svdconfi.activo),V10CADENA,
                          svdconfi.privilegiosver,sizeof(svdconfi.privilegiosver),V10CADENA,
                          svdconfi.privilegiosmod,sizeof(svdconfi.privilegiosmod),V10CADENA,
                          svdconfi.permitidos,sizeof(svdconfi.permitidos),V10CADENA,
                          svdconfi.codopemodif,sizeof(svdconfi.codopemodif),V10CADENA,
                          &svdconfi.fecmodif,sizeof(svdconfi.fecmodif),V10LONG,
                          svdconfi.horamodif,sizeof(svdconfi.horamodif),V10CADENA,
                          &svdconfi.codcomen,sizeof(svdconfi.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselconfvdconfi,"PROPIEDAD",svdconfi.propiedad,sizeof(svdconfi.propiedad),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_conf);
        init = 1;
    }
}

diccionario *CONFdamediccionario(void)
{
     return(&dconf);
}

int CONFselpropiedad(char *propiedad,vdconfis *conf)
{
  int vdret;
  if (vdselconfpropiedad==NULL) init_selconfpropiedad();
  memset(&svdconfi,0,sizeof(svdconfi));
  strcpy(svdconfi.propiedad,propiedad);
  vdret=ejefetchcursor(vdselconfpropiedad);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselconfpropiedad. vdret %d. \n",CONFlog(&svdconfi),vdret);
    return(VD_EERRORACLE);
   }
  *conf=svdconfi;
  return(vdret);
}

int CONFselvdconfi(char *propiedad,vdconfis *conf)
{
  int vdret;
  if (vdselconfvdconfi==NULL) init_selconfvdconfi();
  memset(&svdconfi,0,sizeof(svdconfi));
  strcpy(svdconfi.propiedad,propiedad);
  vdret=ejefetchcursor(vdselconfvdconfi);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselconfvdconfi. vdret %d. \n",CONFlog(&svdconfi),vdret);
    return(VD_EERRORACLE);
   }
  *conf=svdconfi;
  return(vdret);
}

char * CONFlog(vdconfis *conf)
{
    sprintf(msglogCONF, "VDCONFI: propiedad %s ",conf->propiedad);
    return(msglogCONF);
}

char * CONFdebug(vdconfis *conf)
{
    debugestruct(&dconf,conf,msgdebugCONF);
    return(msgdebugCONF);
}

