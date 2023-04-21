// Modulo generado automaticamente a partir de VDIMPRESORAS.DEF
//#***
//# VDIMPRESORAS.c - Generación automática del código c para la tabla de Impresoras del sistema                                                   
//# 
//# Propósito: Funciones de acceso a la tabla VDIMPRESORAS
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=IMPR

#include "vd.h"
#define SELIMPRVDIMPRESORAS "SELECT VDIMPRESORAS.ROWID,VDIMPRESORAS.CODIMPRE,VDIMPRESORAS.GRUPOIMPRE, "\
                    " VDIMPRESORAS.DESIMPRE,VDIMPRESORAS.SPOOL,VDIMPRESORAS.DRIVER, "\
                    " VDIMPRESORAS.FICHERO,VDIMPRESORAS.TIPOCONEX,VDIMPRESORAS.DIRIP, "\
                    " VDIMPRESORAS.PUERTOCONEX,VDIMPRESORAS.BAUDIOS,VDIMPRESORAS.BITS, "\
                    " VDIMPRESORAS.PARIDAD,VDIMPRESORAS.BITSTOP,VDIMPRESORAS.ACTIVO, "\
                    " VDIMPRESORAS.CODOPEMODIF,VDIMPRESORAS.FECMODIF,VDIMPRESORAS.HORAMODIF, "\
                    " VDIMPRESORAS.CODCOMEN "\
        " FROM VDIMPRESORAS"\
        " WHERE "\
               " VDIMPRESORAS.CODIMPRE=:CODIMPRE "
static v10cursors *vdselimprvdimpresoras;

static vdimpresorass svdimpresoras;

static diccols colvdimpresoras[]={
	{"ROWID",V10CADENA,(size_t)&svdimpresoras.rowid,sizeof(svdimpresoras.rowid)},
	{"CODIMPRE",V10CADENA,(size_t)&svdimpresoras.codimpre,sizeof(svdimpresoras.codimpre)},
	{"GRUPOIMPRE",V10CADENA,(size_t)&svdimpresoras.grupoimpre,sizeof(svdimpresoras.grupoimpre)},
	{"DESIMPRE",V10CADENA,(size_t)&svdimpresoras.desimpre,sizeof(svdimpresoras.desimpre)},
	{"SPOOL",V10CADENA,(size_t)&svdimpresoras.spool,sizeof(svdimpresoras.spool)},
	{"DRIVER",V10CADENA,(size_t)&svdimpresoras.driver,sizeof(svdimpresoras.driver)},
	{"FICHERO",V10CADENA,(size_t)&svdimpresoras.fichero,sizeof(svdimpresoras.fichero)},
	{"TIPOCONEX",V10LONG,(size_t)&svdimpresoras.tipoconex,sizeof(svdimpresoras.tipoconex)},
	{"DIRIP",V10CADENA,(size_t)&svdimpresoras.dirip,sizeof(svdimpresoras.dirip)},
	{"PUERTOCONEX",V10LONG,(size_t)&svdimpresoras.puertoconex,sizeof(svdimpresoras.puertoconex)},
	{"BAUDIOS",V10LONG,(size_t)&svdimpresoras.baudios,sizeof(svdimpresoras.baudios)},
	{"BITS",V10LONG,(size_t)&svdimpresoras.bits,sizeof(svdimpresoras.bits)},
	{"PARIDAD",V10LONG,(size_t)&svdimpresoras.paridad,sizeof(svdimpresoras.paridad)},
	{"BITSTOP",V10LONG,(size_t)&svdimpresoras.bitstop,sizeof(svdimpresoras.bitstop)},
	{"ACTIVO",V10CADENA,(size_t)&svdimpresoras.activo,sizeof(svdimpresoras.activo)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdimpresoras.codopemodif,sizeof(svdimpresoras.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdimpresoras.fecmodif,sizeof(svdimpresoras.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdimpresoras.horamodif,sizeof(svdimpresoras.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdimpresoras.codcomen,sizeof(svdimpresoras.codcomen)}
	};
static diccionarios dvdimpresoras[]={
    {colvdimpresoras,19}
};
diccionario dimpr={dvdimpresoras,1};

static char msglogIMPR[LCADENA];
static char msgdebugIMPR[LCADENABIG];
static int init=0;


static void fin_vd_impr(void)
{
if (vdselimprvdimpresoras) {
    liberacursor(vdselimprvdimpresoras);
    vdselimprvdimpresoras = NULL;
}
}
static void init_selimprvdimpresoras(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimpresoras[0].numcol;nc++) dvdimpresoras[0].c[nc].offset-=(size_t)&svdimpresoras;
    vdselimprvdimpresoras=abrecursordebug(SELIMPRVDIMPRESORAS,1280);
    definetodo(vdselimprvdimpresoras,svdimpresoras.rowid,sizeof(svdimpresoras.rowid),V10CADENA,
                          svdimpresoras.codimpre,sizeof(svdimpresoras.codimpre),V10CADENA,
                          svdimpresoras.grupoimpre,sizeof(svdimpresoras.grupoimpre),V10CADENA,
                          svdimpresoras.desimpre,sizeof(svdimpresoras.desimpre),V10CADENA,
                          svdimpresoras.spool,sizeof(svdimpresoras.spool),V10CADENA,
                          svdimpresoras.driver,sizeof(svdimpresoras.driver),V10CADENA,
                          svdimpresoras.fichero,sizeof(svdimpresoras.fichero),V10CADENA,
                          &svdimpresoras.tipoconex,sizeof(svdimpresoras.tipoconex),V10LONG,
                          svdimpresoras.dirip,sizeof(svdimpresoras.dirip),V10CADENA,
                          &svdimpresoras.puertoconex,sizeof(svdimpresoras.puertoconex),V10LONG,
                          &svdimpresoras.baudios,sizeof(svdimpresoras.baudios),V10LONG,
                          &svdimpresoras.bits,sizeof(svdimpresoras.bits),V10LONG,
                          &svdimpresoras.paridad,sizeof(svdimpresoras.paridad),V10LONG,
                          &svdimpresoras.bitstop,sizeof(svdimpresoras.bitstop),V10LONG,
                          svdimpresoras.activo,sizeof(svdimpresoras.activo),V10CADENA,
                          svdimpresoras.codopemodif,sizeof(svdimpresoras.codopemodif),V10CADENA,
                          &svdimpresoras.fecmodif,sizeof(svdimpresoras.fecmodif),V10LONG,
                          svdimpresoras.horamodif,sizeof(svdimpresoras.horamodif),V10CADENA,
                          &svdimpresoras.codcomen,sizeof(svdimpresoras.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselimprvdimpresoras,"CODIMPRE",svdimpresoras.codimpre,sizeof(svdimpresoras.codimpre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_impr);
        init = 1;
    }
}

diccionario *IMPRdamediccionario(void)
{
     return(&dimpr);
}

int IMPRselvdimpresoras(char *codimpre,vdimpresorass *impr)
{
  int vdret;
  if (vdselimprvdimpresoras==NULL) init_selimprvdimpresoras();
  memset(&svdimpresoras,0,sizeof(svdimpresoras));
  strcpy(svdimpresoras.codimpre,codimpre);
  vdret=ejefetchcursor(vdselimprvdimpresoras);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimprvdimpresoras. vdret %d. \n",IMPRlog(&svdimpresoras),vdret);
    return(VD_EERRORACLE);
   }
  *impr=svdimpresoras;
  return(vdret);
}

char * IMPRlog(vdimpresorass *impr)
{
    sprintf(msglogIMPR, "VDIMPRESORAS: codimpre %s ",impr->codimpre);
    return(msglogIMPR);
}

char * IMPRdebug(vdimpresorass *impr)
{
    debugestruct(&dimpr,impr,msgdebugIMPR);
    return(msgdebugIMPR);
}

