// Modulo generado automaticamente a partir de VDDEFCAMPO.DEF
//# M¢dulo : VDDEFCAMPO.DEF
//# Función: Generación automatica de rutinas C tabla VDDEFCAMPO
//#
//# Autor	 : EAA
//# Revisado por:
//# Fecha  : 10-10-2007
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=DEC
//
//PRIMARIA=NCAMPO
//
//CLAVE=NCAMPO,NCAMPO,TIPOPANTALLA
//
//ORADEBUG=0
//
//

#include "vd.h"
#define SELDECNCAMPO "SELECT VDDEFCAMPO.ROWID,VDDEFCAMPO.NCAMPO,VDDEFCAMPO.TIPOPANTALLA, "\
                    " VDDEFCAMPO.TTITULO,VDDEFCAMPO.TTOOLTIP,VDDEFCAMPO.FTOOLTIP, "\
                    " VDDEFCAMPO.FCONVIERTE,VDDEFCAMPO.CAPITALIZA,VDDEFCAMPO.FCONTEXTUAL, "\
                    " VDDEFCAMPO.ESTRADUCIBLE,VDDEFCAMPO.ESSCAN,VDDEFCAMPO.FPOSTCHANGE, "\
                    " VDDEFCAMPO.FTECLA,VDDEFCAMPO.PRIVMODIF,VDDEFCAMPO.PRIVVER, "\
                    " VDDEFCAMPO.FAUXILIAR,VDDEFCAMPO.CODOPEMODIF,VDDEFCAMPO.FECMODIF, "\
                    " VDDEFCAMPO.HORAMODIF,VDDEFCAMPO.CODCOMEN "\
        " FROM VDDEFCAMPO"\
        " WHERE "\
               " VDDEFCAMPO.NCAMPO=:NCAMPO "\
               " AND VDDEFCAMPO.TIPOPANTALLA=:TIPOPANTALLA "
static v10cursors *vdseldecncampo;

#define SELDECVDDEFCAMPO "SELECT VDDEFCAMPO.ROWID,VDDEFCAMPO.NCAMPO,VDDEFCAMPO.TIPOPANTALLA, "\
                    " VDDEFCAMPO.TTITULO,VDDEFCAMPO.TTOOLTIP,VDDEFCAMPO.FTOOLTIP, "\
                    " VDDEFCAMPO.FCONVIERTE,VDDEFCAMPO.CAPITALIZA,VDDEFCAMPO.FCONTEXTUAL, "\
                    " VDDEFCAMPO.ESTRADUCIBLE,VDDEFCAMPO.ESSCAN,VDDEFCAMPO.FPOSTCHANGE, "\
                    " VDDEFCAMPO.FTECLA,VDDEFCAMPO.PRIVMODIF,VDDEFCAMPO.PRIVVER, "\
                    " VDDEFCAMPO.FAUXILIAR,VDDEFCAMPO.CODOPEMODIF,VDDEFCAMPO.FECMODIF, "\
                    " VDDEFCAMPO.HORAMODIF,VDDEFCAMPO.CODCOMEN "\
        " FROM VDDEFCAMPO"\
        " WHERE "\
               " VDDEFCAMPO.NCAMPO=:NCAMPO "\
               " AND VDDEFCAMPO.TIPOPANTALLA=:TIPOPANTALLA "
static v10cursors *vdseldecvddefcampo;

static vddefcampos svddefcampo;

static diccols colvddefcampo[]={
	{"ROWID",V10CADENA,(size_t)&svddefcampo.rowid,sizeof(svddefcampo.rowid)},
	{"NCAMPO",V10CADENA,(size_t)&svddefcampo.ncampo,sizeof(svddefcampo.ncampo)},
	{"TIPOPANTALLA",V10CADENA,(size_t)&svddefcampo.tipopantalla,sizeof(svddefcampo.tipopantalla)},
	{"TTITULO",V10CADENA,(size_t)&svddefcampo.ttitulo,sizeof(svddefcampo.ttitulo)},
	{"TTOOLTIP",V10CADENA,(size_t)&svddefcampo.ttooltip,sizeof(svddefcampo.ttooltip)},
	{"FTOOLTIP",V10CADENA,(size_t)&svddefcampo.ftooltip,sizeof(svddefcampo.ftooltip)},
	{"FCONVIERTE",V10CADENA,(size_t)&svddefcampo.fconvierte,sizeof(svddefcampo.fconvierte)},
	{"CAPITALIZA",V10CADENA,(size_t)&svddefcampo.capitaliza,sizeof(svddefcampo.capitaliza)},
	{"FCONTEXTUAL",V10CADENA,(size_t)&svddefcampo.fcontextual,sizeof(svddefcampo.fcontextual)},
	{"ESTRADUCIBLE",V10CADENA,(size_t)&svddefcampo.estraducible,sizeof(svddefcampo.estraducible)},
	{"ESSCAN",V10CADENA,(size_t)&svddefcampo.esscan,sizeof(svddefcampo.esscan)},
	{"FPOSTCHANGE",V10CADENA,(size_t)&svddefcampo.fpostchange,sizeof(svddefcampo.fpostchange)},
	{"FTECLA",V10CADENA,(size_t)&svddefcampo.ftecla,sizeof(svddefcampo.ftecla)},
	{"PRIVMODIF",V10CADENA,(size_t)&svddefcampo.privmodif,sizeof(svddefcampo.privmodif)},
	{"PRIVVER",V10CADENA,(size_t)&svddefcampo.privver,sizeof(svddefcampo.privver)},
	{"FAUXILIAR",V10CADENA,(size_t)&svddefcampo.fauxiliar,sizeof(svddefcampo.fauxiliar)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svddefcampo.codopemodif,sizeof(svddefcampo.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svddefcampo.fecmodif,sizeof(svddefcampo.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svddefcampo.horamodif,sizeof(svddefcampo.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svddefcampo.codcomen,sizeof(svddefcampo.codcomen)}
	};
static diccionarios dvddefcampo[]={
    {colvddefcampo,20}
};
diccionario ddec={dvddefcampo,1};

static char msglogDEC[LCADENA];
static char msgdebugDEC[LCADENABIG];
static int init=0;


static void fin_vd_dec(void)
{
if (vdseldecncampo) {
    liberacursor(vdseldecncampo);
    vdseldecncampo = NULL;
}
if (vdseldecvddefcampo) {
    liberacursor(vdseldecvddefcampo);
    vdseldecvddefcampo = NULL;
}
}
static void init_seldecncampo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddefcampo[0].numcol;nc++) dvddefcampo[0].c[nc].offset-=(size_t)&svddefcampo;
    vdseldecncampo=abrecursordebug(SELDECNCAMPO,0);
    definetodo(vdseldecncampo,svddefcampo.rowid,sizeof(svddefcampo.rowid),V10CADENA,
                          svddefcampo.ncampo,sizeof(svddefcampo.ncampo),V10CADENA,
                          svddefcampo.tipopantalla,sizeof(svddefcampo.tipopantalla),V10CADENA,
                          svddefcampo.ttitulo,sizeof(svddefcampo.ttitulo),V10CADENA,
                          svddefcampo.ttooltip,sizeof(svddefcampo.ttooltip),V10CADENA,
                          svddefcampo.ftooltip,sizeof(svddefcampo.ftooltip),V10CADENA,
                          svddefcampo.fconvierte,sizeof(svddefcampo.fconvierte),V10CADENA,
                          svddefcampo.capitaliza,sizeof(svddefcampo.capitaliza),V10CADENA,
                          svddefcampo.fcontextual,sizeof(svddefcampo.fcontextual),V10CADENA,
                          svddefcampo.estraducible,sizeof(svddefcampo.estraducible),V10CADENA,
                          svddefcampo.esscan,sizeof(svddefcampo.esscan),V10CADENA,
                          svddefcampo.fpostchange,sizeof(svddefcampo.fpostchange),V10CADENA,
                          svddefcampo.ftecla,sizeof(svddefcampo.ftecla),V10CADENA,
                          svddefcampo.privmodif,sizeof(svddefcampo.privmodif),V10CADENA,
                          svddefcampo.privver,sizeof(svddefcampo.privver),V10CADENA,
                          svddefcampo.fauxiliar,sizeof(svddefcampo.fauxiliar),V10CADENA,
                          svddefcampo.codopemodif,sizeof(svddefcampo.codopemodif),V10CADENA,
                          &svddefcampo.fecmodif,sizeof(svddefcampo.fecmodif),V10LONG,
                          svddefcampo.horamodif,sizeof(svddefcampo.horamodif),V10CADENA,
                          &svddefcampo.codcomen,sizeof(svddefcampo.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseldecncampo,"NCAMPO",svddefcampo.ncampo,sizeof(svddefcampo.ncampo),V10CADENA,
                          "TIPOPANTALLA",svddefcampo.tipopantalla,sizeof(svddefcampo.tipopantalla),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_dec);
        init = 1;
    }
}

static void init_seldecvddefcampo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddefcampo[0].numcol;nc++) dvddefcampo[0].c[nc].offset-=(size_t)&svddefcampo;
    vdseldecvddefcampo=abrecursordebug(SELDECVDDEFCAMPO,0);
    definetodo(vdseldecvddefcampo,svddefcampo.rowid,sizeof(svddefcampo.rowid),V10CADENA,
                          svddefcampo.ncampo,sizeof(svddefcampo.ncampo),V10CADENA,
                          svddefcampo.tipopantalla,sizeof(svddefcampo.tipopantalla),V10CADENA,
                          svddefcampo.ttitulo,sizeof(svddefcampo.ttitulo),V10CADENA,
                          svddefcampo.ttooltip,sizeof(svddefcampo.ttooltip),V10CADENA,
                          svddefcampo.ftooltip,sizeof(svddefcampo.ftooltip),V10CADENA,
                          svddefcampo.fconvierte,sizeof(svddefcampo.fconvierte),V10CADENA,
                          svddefcampo.capitaliza,sizeof(svddefcampo.capitaliza),V10CADENA,
                          svddefcampo.fcontextual,sizeof(svddefcampo.fcontextual),V10CADENA,
                          svddefcampo.estraducible,sizeof(svddefcampo.estraducible),V10CADENA,
                          svddefcampo.esscan,sizeof(svddefcampo.esscan),V10CADENA,
                          svddefcampo.fpostchange,sizeof(svddefcampo.fpostchange),V10CADENA,
                          svddefcampo.ftecla,sizeof(svddefcampo.ftecla),V10CADENA,
                          svddefcampo.privmodif,sizeof(svddefcampo.privmodif),V10CADENA,
                          svddefcampo.privver,sizeof(svddefcampo.privver),V10CADENA,
                          svddefcampo.fauxiliar,sizeof(svddefcampo.fauxiliar),V10CADENA,
                          svddefcampo.codopemodif,sizeof(svddefcampo.codopemodif),V10CADENA,
                          &svddefcampo.fecmodif,sizeof(svddefcampo.fecmodif),V10LONG,
                          svddefcampo.horamodif,sizeof(svddefcampo.horamodif),V10CADENA,
                          &svddefcampo.codcomen,sizeof(svddefcampo.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseldecvddefcampo,"NCAMPO",svddefcampo.ncampo,sizeof(svddefcampo.ncampo),V10CADENA,
                          "TIPOPANTALLA",svddefcampo.tipopantalla,sizeof(svddefcampo.tipopantalla),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_dec);
        init = 1;
    }
}

diccionario *DECdamediccionario(void)
{
     return(&ddec);
}

int DECselncampo(char *ncampo,char *tipopantalla,vddefcampos *dec)
{
  int vdret;
  if (vdseldecncampo==NULL) init_seldecncampo();
  memset(&svddefcampo,0,sizeof(svddefcampo));
  strcpy(svddefcampo.ncampo,ncampo);
  strcpy(svddefcampo.tipopantalla,tipopantalla);
  vdret=ejefetchcursor(vdseldecncampo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldecncampo. vdret %d. \n",DEClog(&svddefcampo),vdret);
    return(VD_EERRORACLE);
   }
  *dec=svddefcampo;
  return(vdret);
}

int DECselvddefcampo(char *ncampo,char *tipopantalla,vddefcampos *dec)
{
  int vdret;
  if (vdseldecvddefcampo==NULL) init_seldecvddefcampo();
  memset(&svddefcampo,0,sizeof(svddefcampo));
  strcpy(svddefcampo.ncampo,ncampo);
  strcpy(svddefcampo.tipopantalla,tipopantalla);
  vdret=ejefetchcursor(vdseldecvddefcampo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldecvddefcampo. vdret %d. \n",DEClog(&svddefcampo),vdret);
    return(VD_EERRORACLE);
   }
  *dec=svddefcampo;
  return(vdret);
}

char * DEClog(vddefcampos *dec)
{
    sprintf(msglogDEC, "VDDEFCAMPO: ncampo %s tipopantalla %s ",dec->ncampo,dec->tipopantalla);
    return(msglogDEC);
}

char * DECdebug(vddefcampos *dec)
{
    debugestruct(&ddec,dec,msgdebugDEC);
    return(msgdebugDEC);
}

