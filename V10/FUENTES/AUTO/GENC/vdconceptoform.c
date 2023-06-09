// Modulo generado automaticamente a partir de VDCONCEPTOFORM.DEF
//# M�dulo : VDCONCEPTOFORM.DEF                                                        
//# Funci�n: Generaci�n automatica de rutinas C tabla VDCONCEPTOFORM
//#                        
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 13-6-2008                                              
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//
//TABLE=CSTK;
//

#include "vd.h"
#define SELCSTKVDCONCEPTOFORM "SELECT VDCONCEPTOFORM.ROWID,VDCONCEPTOFORM.TIPOPROP,VDCONCEPTOFORM.ORDEN, "\
                    " VDCONCEPTOFORM.DESTIPOPROP,VDCONCEPTOFORM.ACTIVO,VDCONCEPTOFORM.RANGODIV, "\
                    " VDCONCEPTOFORM.CODCLASIF,VDCONCEPTOFORM.CODCLASE,VDCONCEPTOFORM.CODCONCEENT, "\
                    " VDCONCEPTOFORM.CODCONCESAL,VDCONCEPTOFORM.FUENTE,VDCONCEPTOFORM.SUMIDERO, "\
                    " VDCONCEPTOFORM.PRIVILEGIOS,VDCONCEPTOFORM.CANTMAX,VDCONCEPTOFORM.PVLMAX, "\
                    " VDCONCEPTOFORM.CODOPEMODIF,VDCONCEPTOFORM.FECMODIF,VDCONCEPTOFORM.HORAMODIF, "\
                    " VDCONCEPTOFORM.CODCOMEN "\
        " FROM VDCONCEPTOFORM"\
        " WHERE "\
               " VDCONCEPTOFORM.TIPOPROP=:TIPOPROP "\
               " AND VDCONCEPTOFORM.ORDEN=:ORDEN "
static v10cursors *vdselcstkvdconceptoform;

static vdconceptoforms svdconceptoform;

static diccols colvdconceptoform[]={
	{"ROWID",V10CADENA,(size_t)&svdconceptoform.rowid,sizeof(svdconceptoform.rowid)},
	{"TIPOPROP",V10CADENA,(size_t)&svdconceptoform.tipoprop,sizeof(svdconceptoform.tipoprop)},
	{"ORDEN",V10LONG,(size_t)&svdconceptoform.orden,sizeof(svdconceptoform.orden)},
	{"DESTIPOPROP",V10CADENA,(size_t)&svdconceptoform.destipoprop,sizeof(svdconceptoform.destipoprop)},
	{"ACTIVO",V10CADENA,(size_t)&svdconceptoform.activo,sizeof(svdconceptoform.activo)},
	{"RANGODIV",V10CADENA,(size_t)&svdconceptoform.rangodiv,sizeof(svdconceptoform.rangodiv)},
	{"CODCLASIF",V10CADENA,(size_t)&svdconceptoform.codclasif,sizeof(svdconceptoform.codclasif)},
	{"CODCLASE",V10CADENA,(size_t)&svdconceptoform.codclase,sizeof(svdconceptoform.codclase)},
	{"CODCONCEENT",V10CADENA,(size_t)&svdconceptoform.codconceent,sizeof(svdconceptoform.codconceent)},
	{"CODCONCESAL",V10CADENA,(size_t)&svdconceptoform.codconcesal,sizeof(svdconceptoform.codconcesal)},
	{"FUENTE",V10CADENA,(size_t)&svdconceptoform.fuente,sizeof(svdconceptoform.fuente)},
	{"SUMIDERO",V10CADENA,(size_t)&svdconceptoform.sumidero,sizeof(svdconceptoform.sumidero)},
	{"PRIVILEGIOS",V10CADENA,(size_t)&svdconceptoform.privilegios,sizeof(svdconceptoform.privilegios)},
	{"CANTMAX",V10LONG,(size_t)&svdconceptoform.cantmax,sizeof(svdconceptoform.cantmax)},
	{"PVLMAX",V10LONG,(size_t)&svdconceptoform.pvlmax,sizeof(svdconceptoform.pvlmax)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdconceptoform.codopemodif,sizeof(svdconceptoform.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdconceptoform.fecmodif,sizeof(svdconceptoform.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdconceptoform.horamodif,sizeof(svdconceptoform.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdconceptoform.codcomen,sizeof(svdconceptoform.codcomen)}
	};
static diccionarios dvdconceptoform[]={
    {colvdconceptoform,19}
};
diccionario dcstk={dvdconceptoform,1};

static char msglogCSTK[LCADENA];
static char msgdebugCSTK[LCADENABIG];
static int init=0;


static void fin_vd_cstk(void)
{
if (vdselcstkvdconceptoform) {
    liberacursor(vdselcstkvdconceptoform);
    vdselcstkvdconceptoform = NULL;
}
}
static void init_selcstkvdconceptoform(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconceptoform[0].numcol;nc++) dvdconceptoform[0].c[nc].offset-=(size_t)&svdconceptoform;
    vdselcstkvdconceptoform=abrecursordebug(SELCSTKVDCONCEPTOFORM,1280);
    definetodo(vdselcstkvdconceptoform,svdconceptoform.rowid,sizeof(svdconceptoform.rowid),V10CADENA,
                          svdconceptoform.tipoprop,sizeof(svdconceptoform.tipoprop),V10CADENA,
                          &svdconceptoform.orden,sizeof(svdconceptoform.orden),V10LONG,
                          svdconceptoform.destipoprop,sizeof(svdconceptoform.destipoprop),V10CADENA,
                          svdconceptoform.activo,sizeof(svdconceptoform.activo),V10CADENA,
                          svdconceptoform.rangodiv,sizeof(svdconceptoform.rangodiv),V10CADENA,
                          svdconceptoform.codclasif,sizeof(svdconceptoform.codclasif),V10CADENA,
                          svdconceptoform.codclase,sizeof(svdconceptoform.codclase),V10CADENA,
                          svdconceptoform.codconceent,sizeof(svdconceptoform.codconceent),V10CADENA,
                          svdconceptoform.codconcesal,sizeof(svdconceptoform.codconcesal),V10CADENA,
                          svdconceptoform.fuente,sizeof(svdconceptoform.fuente),V10CADENA,
                          svdconceptoform.sumidero,sizeof(svdconceptoform.sumidero),V10CADENA,
                          svdconceptoform.privilegios,sizeof(svdconceptoform.privilegios),V10CADENA,
                          &svdconceptoform.cantmax,sizeof(svdconceptoform.cantmax),V10LONG,
                          &svdconceptoform.pvlmax,sizeof(svdconceptoform.pvlmax),V10LONG,
                          svdconceptoform.codopemodif,sizeof(svdconceptoform.codopemodif),V10CADENA,
                          &svdconceptoform.fecmodif,sizeof(svdconceptoform.fecmodif),V10LONG,
                          svdconceptoform.horamodif,sizeof(svdconceptoform.horamodif),V10CADENA,
                          &svdconceptoform.codcomen,sizeof(svdconceptoform.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselcstkvdconceptoform,"TIPOPROP",svdconceptoform.tipoprop,sizeof(svdconceptoform.tipoprop),V10CADENA,
                          "ORDEN",&svdconceptoform.orden,sizeof(svdconceptoform.orden),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cstk);
        init = 1;
    }
}

diccionario *CSTKdamediccionario(void)
{
     return(&dcstk);
}

int CSTKselvdconceptoform(char *tipoprop,long orden,vdconceptoforms *cstk)
{
  int vdret;
  if (vdselcstkvdconceptoform==NULL) init_selcstkvdconceptoform();
  memset(&svdconceptoform,0,sizeof(svdconceptoform));
  strcpy(svdconceptoform.tipoprop,tipoprop);
  svdconceptoform.orden=orden;
  vdret=ejefetchcursor(vdselcstkvdconceptoform);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselcstkvdconceptoform. vdret %d. \n",CSTKlog(&svdconceptoform),vdret);
    return(VD_EERRORACLE);
   }
  *cstk=svdconceptoform;
  return(vdret);
}

char * CSTKlog(vdconceptoforms *cstk)
{
    sprintf(msglogCSTK, "VDCONCEPTOFORM: tipoprop %s orden %ld ",cstk->tipoprop,cstk->orden);
    return(msglogCSTK);
}

char * CSTKdebug(vdconceptoforms *cstk)
{
    debugestruct(&dcstk,cstk,msgdebugCSTK);
    return(msgdebugCSTK);
}

