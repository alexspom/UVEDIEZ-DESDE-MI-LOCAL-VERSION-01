// Modulo generado automaticamente a partir de VDTIPORDRECLIN.DEF
//# M¢dulo : VDTIPORDRECLIN.DEF                                                     
//# Función: Generación automatica de rutinas C tabla VDTIPORDRECLIN
//#                        
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 17-06-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=LTO
//EXTRA=CODART,V10CADENA,20
//
//CLAVE=ARTICULO, TIPORDREC,WHERE=(CODCLASIF,CODCLASE) IN (SELECT CODCLASIF,CODCLASE
//                                                           FROM VDCLASEARTIC
//                                                          WHERE CODART = :CODART);

#include "vd.h"
#define SELLTOARTICULO "SELECT VDTIPORDRECLIN.ROWID,VDTIPORDRECLIN.TIPORDREC,VDTIPORDRECLIN.CODCLASIF, "\
                    " VDTIPORDRECLIN.CODCLASE,VDTIPORDRECLIN.REQUIERE_ORDEN,VDTIPORDRECLIN.RECEPCION_UNICA, "\
                    " VDTIPORDRECLIN.MUESTREAR,VDTIPORDRECLIN.ALTAS_MANUALES,VDTIPORDRECLIN.CREA_LOTE, "\
                    " VDTIPORDRECLIN.ESTADOS_LOTE,VDTIPORDRECLIN.ESTADOS_STOCK,VDTIPORDRECLIN.DIASANTFECPREV, "\
                    " VDTIPORDRECLIN.DIASRETFECPREV,VDTIPORDRECLIN.INDLOTE,VDTIPORDRECLIN.LOTEDEF, "\
                    " VDTIPORDRECLIN.MULTIARTICULO,VDTIPORDRECLIN.CODOPEMODIF,VDTIPORDRECLIN.FECMODIF, "\
                    " VDTIPORDRECLIN.HORAMODIF,VDTIPORDRECLIN.CODCOMEN "\
        " FROM VDTIPORDRECLIN"\
        " WHERE "\
               " VDTIPORDRECLIN.TIPORDREC=:TIPORDREC "\
              "  AND (CODCLASIF,CODCLASE) IN (SELECT CODCLASIF,CODCLASE FROM VDCLASEARTIC WHERE CODART = :CODART) "
static v10cursors *vdselltoarticulo;

#define SELLTOVDTIPORDRECLIN "SELECT VDTIPORDRECLIN.ROWID,VDTIPORDRECLIN.TIPORDREC,VDTIPORDRECLIN.CODCLASIF, "\
                    " VDTIPORDRECLIN.CODCLASE,VDTIPORDRECLIN.REQUIERE_ORDEN,VDTIPORDRECLIN.RECEPCION_UNICA, "\
                    " VDTIPORDRECLIN.MUESTREAR,VDTIPORDRECLIN.ALTAS_MANUALES,VDTIPORDRECLIN.CREA_LOTE, "\
                    " VDTIPORDRECLIN.ESTADOS_LOTE,VDTIPORDRECLIN.ESTADOS_STOCK,VDTIPORDRECLIN.DIASANTFECPREV, "\
                    " VDTIPORDRECLIN.DIASRETFECPREV,VDTIPORDRECLIN.INDLOTE,VDTIPORDRECLIN.LOTEDEF, "\
                    " VDTIPORDRECLIN.MULTIARTICULO,VDTIPORDRECLIN.CODOPEMODIF,VDTIPORDRECLIN.FECMODIF, "\
                    " VDTIPORDRECLIN.HORAMODIF,VDTIPORDRECLIN.CODCOMEN "\
        " FROM VDTIPORDRECLIN"\
        " WHERE "\
               " VDTIPORDRECLIN.TIPORDREC=:TIPORDREC "\
               " AND VDTIPORDRECLIN.CODCLASIF=:CODCLASIF "\
               " AND VDTIPORDRECLIN.CODCLASE=:CODCLASE "
static v10cursors *vdselltovdtipordreclin;

static vdtipordreclins svdtipordreclin;

static diccols colvdtipordreclin[]={
	{"ROWID",V10CADENA,(size_t)&svdtipordreclin.rowid,sizeof(svdtipordreclin.rowid)},
	{"TIPORDREC",V10CADENA,(size_t)&svdtipordreclin.tipordrec,sizeof(svdtipordreclin.tipordrec)},
	{"CODCLASIF",V10CADENA,(size_t)&svdtipordreclin.codclasif,sizeof(svdtipordreclin.codclasif)},
	{"CODCLASE",V10CADENA,(size_t)&svdtipordreclin.codclase,sizeof(svdtipordreclin.codclase)},
	{"REQUIERE_ORDEN",V10CADENA,(size_t)&svdtipordreclin.requiere_orden,sizeof(svdtipordreclin.requiere_orden)},
	{"RECEPCION_UNICA",V10CADENA,(size_t)&svdtipordreclin.recepcion_unica,sizeof(svdtipordreclin.recepcion_unica)},
	{"MUESTREAR",V10CADENA,(size_t)&svdtipordreclin.muestrear,sizeof(svdtipordreclin.muestrear)},
	{"ALTAS_MANUALES",V10CADENA,(size_t)&svdtipordreclin.altas_manuales,sizeof(svdtipordreclin.altas_manuales)},
	{"CREA_LOTE",V10CADENA,(size_t)&svdtipordreclin.crea_lote,sizeof(svdtipordreclin.crea_lote)},
	{"ESTADOS_LOTE",V10CADENA,(size_t)&svdtipordreclin.estados_lote,sizeof(svdtipordreclin.estados_lote)},
	{"ESTADOS_STOCK",V10CADENA,(size_t)&svdtipordreclin.estados_stock,sizeof(svdtipordreclin.estados_stock)},
	{"DIASANTFECPREV",V10LONG,(size_t)&svdtipordreclin.diasantfecprev,sizeof(svdtipordreclin.diasantfecprev)},
	{"DIASRETFECPREV",V10LONG,(size_t)&svdtipordreclin.diasretfecprev,sizeof(svdtipordreclin.diasretfecprev)},
	{"INDLOTE",V10CADENA,(size_t)&svdtipordreclin.indlote,sizeof(svdtipordreclin.indlote)},
	{"LOTEDEF",V10CADENA,(size_t)&svdtipordreclin.lotedef,sizeof(svdtipordreclin.lotedef)},
	{"MULTIARTICULO",V10CADENA,(size_t)&svdtipordreclin.multiarticulo,sizeof(svdtipordreclin.multiarticulo)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdtipordreclin.codopemodif,sizeof(svdtipordreclin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdtipordreclin.fecmodif,sizeof(svdtipordreclin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdtipordreclin.horamodif,sizeof(svdtipordreclin.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdtipordreclin.codcomen,sizeof(svdtipordreclin.codcomen)},
	{"CODART",V10CADENA,(size_t)&svdtipordreclin.codart,sizeof(svdtipordreclin.codart)}
	};
static diccionarios dvdtipordreclin[]={
    {colvdtipordreclin,21}
};
diccionario dlto={dvdtipordreclin,1};

static char msglogLTO[LCADENA];
static char msgdebugLTO[LCADENABIG];
static int init=0;


static void fin_vd_lto(void)
{
if (vdselltoarticulo) {
    liberacursor(vdselltoarticulo);
    vdselltoarticulo = NULL;
}
if (vdselltovdtipordreclin) {
    liberacursor(vdselltovdtipordreclin);
    vdselltovdtipordreclin = NULL;
}
}
static void init_selltoarticulo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtipordreclin[0].numcol;nc++) dvdtipordreclin[0].c[nc].offset-=(size_t)&svdtipordreclin;
    vdselltoarticulo=abrecursordebug(SELLTOARTICULO,1280);
    definetodo(vdselltoarticulo,svdtipordreclin.rowid,sizeof(svdtipordreclin.rowid),V10CADENA,
                          svdtipordreclin.tipordrec,sizeof(svdtipordreclin.tipordrec),V10CADENA,
                          svdtipordreclin.codclasif,sizeof(svdtipordreclin.codclasif),V10CADENA,
                          svdtipordreclin.codclase,sizeof(svdtipordreclin.codclase),V10CADENA,
                          svdtipordreclin.requiere_orden,sizeof(svdtipordreclin.requiere_orden),V10CADENA,
                          svdtipordreclin.recepcion_unica,sizeof(svdtipordreclin.recepcion_unica),V10CADENA,
                          svdtipordreclin.muestrear,sizeof(svdtipordreclin.muestrear),V10CADENA,
                          svdtipordreclin.altas_manuales,sizeof(svdtipordreclin.altas_manuales),V10CADENA,
                          svdtipordreclin.crea_lote,sizeof(svdtipordreclin.crea_lote),V10CADENA,
                          svdtipordreclin.estados_lote,sizeof(svdtipordreclin.estados_lote),V10CADENA,
                          svdtipordreclin.estados_stock,sizeof(svdtipordreclin.estados_stock),V10CADENA,
                          &svdtipordreclin.diasantfecprev,sizeof(svdtipordreclin.diasantfecprev),V10LONG,
                          &svdtipordreclin.diasretfecprev,sizeof(svdtipordreclin.diasretfecprev),V10LONG,
                          svdtipordreclin.indlote,sizeof(svdtipordreclin.indlote),V10CADENA,
                          svdtipordreclin.lotedef,sizeof(svdtipordreclin.lotedef),V10CADENA,
                          svdtipordreclin.multiarticulo,sizeof(svdtipordreclin.multiarticulo),V10CADENA,
                          svdtipordreclin.codopemodif,sizeof(svdtipordreclin.codopemodif),V10CADENA,
                          &svdtipordreclin.fecmodif,sizeof(svdtipordreclin.fecmodif),V10LONG,
                          svdtipordreclin.horamodif,sizeof(svdtipordreclin.horamodif),V10CADENA,
                          &svdtipordreclin.codcomen,sizeof(svdtipordreclin.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselltoarticulo,"TIPORDREC",svdtipordreclin.tipordrec,sizeof(svdtipordreclin.tipordrec),V10CADENA,
                          "CODART",svdtipordreclin.codart,sizeof(svdtipordreclin.codart),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lto);
        init = 1;
    }
}

static void init_selltovdtipordreclin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtipordreclin[0].numcol;nc++) dvdtipordreclin[0].c[nc].offset-=(size_t)&svdtipordreclin;
    vdselltovdtipordreclin=abrecursordebug(SELLTOVDTIPORDRECLIN,1280);
    definetodo(vdselltovdtipordreclin,svdtipordreclin.rowid,sizeof(svdtipordreclin.rowid),V10CADENA,
                          svdtipordreclin.tipordrec,sizeof(svdtipordreclin.tipordrec),V10CADENA,
                          svdtipordreclin.codclasif,sizeof(svdtipordreclin.codclasif),V10CADENA,
                          svdtipordreclin.codclase,sizeof(svdtipordreclin.codclase),V10CADENA,
                          svdtipordreclin.requiere_orden,sizeof(svdtipordreclin.requiere_orden),V10CADENA,
                          svdtipordreclin.recepcion_unica,sizeof(svdtipordreclin.recepcion_unica),V10CADENA,
                          svdtipordreclin.muestrear,sizeof(svdtipordreclin.muestrear),V10CADENA,
                          svdtipordreclin.altas_manuales,sizeof(svdtipordreclin.altas_manuales),V10CADENA,
                          svdtipordreclin.crea_lote,sizeof(svdtipordreclin.crea_lote),V10CADENA,
                          svdtipordreclin.estados_lote,sizeof(svdtipordreclin.estados_lote),V10CADENA,
                          svdtipordreclin.estados_stock,sizeof(svdtipordreclin.estados_stock),V10CADENA,
                          &svdtipordreclin.diasantfecprev,sizeof(svdtipordreclin.diasantfecprev),V10LONG,
                          &svdtipordreclin.diasretfecprev,sizeof(svdtipordreclin.diasretfecprev),V10LONG,
                          svdtipordreclin.indlote,sizeof(svdtipordreclin.indlote),V10CADENA,
                          svdtipordreclin.lotedef,sizeof(svdtipordreclin.lotedef),V10CADENA,
                          svdtipordreclin.multiarticulo,sizeof(svdtipordreclin.multiarticulo),V10CADENA,
                          svdtipordreclin.codopemodif,sizeof(svdtipordreclin.codopemodif),V10CADENA,
                          &svdtipordreclin.fecmodif,sizeof(svdtipordreclin.fecmodif),V10LONG,
                          svdtipordreclin.horamodif,sizeof(svdtipordreclin.horamodif),V10CADENA,
                          &svdtipordreclin.codcomen,sizeof(svdtipordreclin.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselltovdtipordreclin,"TIPORDREC",svdtipordreclin.tipordrec,sizeof(svdtipordreclin.tipordrec),V10CADENA,
                          "CODCLASIF",svdtipordreclin.codclasif,sizeof(svdtipordreclin.codclasif),V10CADENA,
                          "CODCLASE",svdtipordreclin.codclase,sizeof(svdtipordreclin.codclase),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lto);
        init = 1;
    }
}

diccionario *LTOdamediccionario(void)
{
     return(&dlto);
}

int LTOselarticulo(char *tipordrec,char *codart,vdtipordreclins *lto)
{
  int vdret;
  if (vdselltoarticulo==NULL) init_selltoarticulo();
  memset(&svdtipordreclin,0,sizeof(svdtipordreclin));
  strcpy(svdtipordreclin.tipordrec,tipordrec);
  strcpy(svdtipordreclin.codart,codart);
  vdret=ejefetchcursor(vdselltoarticulo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselltoarticulo. vdret %d. \n",LTOlog(&svdtipordreclin),vdret);
    return(VD_EERRORACLE);
   }
  *lto=svdtipordreclin;
  return(vdret);
}

int LTOselvdtipordreclin(char *tipordrec,char *codclasif,char *codclase,vdtipordreclins *lto)
{
  int vdret;
  if (vdselltovdtipordreclin==NULL) init_selltovdtipordreclin();
  memset(&svdtipordreclin,0,sizeof(svdtipordreclin));
  strcpy(svdtipordreclin.tipordrec,tipordrec);
  strcpy(svdtipordreclin.codclasif,codclasif);
  strcpy(svdtipordreclin.codclase,codclase);
  vdret=ejefetchcursor(vdselltovdtipordreclin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselltovdtipordreclin. vdret %d. \n",LTOlog(&svdtipordreclin),vdret);
    return(VD_EERRORACLE);
   }
  *lto=svdtipordreclin;
  return(vdret);
}

char * LTOlog(vdtipordreclins *lto)
{
    sprintf(msglogLTO, "VDTIPORDRECLIN: tipordrec %s codclasif %s codclase %s ",lto->tipordrec,lto->codclasif,lto->codclase);
    return(msglogLTO);
}

char * LTOdebug(vdtipordreclins *lto)
{
    debugestruct(&dlto,lto,msgdebugLTO);
    return(msgdebugLTO);
}

