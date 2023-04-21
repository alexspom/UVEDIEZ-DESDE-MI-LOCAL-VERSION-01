// Modulo generado automaticamente a partir de VDCONVERSIONES.DEF
//# M¢dulo : VDCONVERSIONES.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDCONVERSIONES
//#                        
//# Autor	 : EAA
//# Revisado por: 
//# Fecha  : 10-10-2007                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=CON
//
//PRIMARIA=UNIDADORIGEN,UNIDADDESTINO
//
//CLAVE=UNIDADES,UNIDADORIGEN,UNIDADDESTINO
//

#include "vd.h"
#define SELCONUNIDADES "SELECT VDCONVERSIONES.ROWID,VDCONVERSIONES.UNIDADORIGEN,VDCONVERSIONES.UNIDADDESTINO, "\
                    " VDCONVERSIONES.FACTORCONVERSION,VDCONVERSIONES.CODOPEMODIF,VDCONVERSIONES.FECMODIF, "\
                    " VDCONVERSIONES.HORAMODIF,VDCONVERSIONES.CODCOMEN "\
        " FROM VDCONVERSIONES"\
        " WHERE "\
               " VDCONVERSIONES.UNIDADORIGEN=:UNIDADORIGEN "\
               " AND VDCONVERSIONES.UNIDADDESTINO=:UNIDADDESTINO "
static v10cursors *vdselconunidades;

#define SELCONVDCONVERSIONES "SELECT VDCONVERSIONES.ROWID,VDCONVERSIONES.UNIDADORIGEN,VDCONVERSIONES.UNIDADDESTINO, "\
                    " VDCONVERSIONES.FACTORCONVERSION,VDCONVERSIONES.CODOPEMODIF,VDCONVERSIONES.FECMODIF, "\
                    " VDCONVERSIONES.HORAMODIF,VDCONVERSIONES.CODCOMEN "\
        " FROM VDCONVERSIONES"\
        " WHERE "\
               " VDCONVERSIONES.UNIDADORIGEN=:UNIDADORIGEN "\
               " AND VDCONVERSIONES.UNIDADDESTINO=:UNIDADDESTINO "
static v10cursors *vdselconvdconversiones;

static vdconversioness svdconversiones;

static diccols colvdconversiones[]={
	{"ROWID",V10CADENA,(size_t)&svdconversiones.rowid,sizeof(svdconversiones.rowid)},
	{"UNIDADORIGEN",V10CADENA,(size_t)&svdconversiones.unidadorigen,sizeof(svdconversiones.unidadorigen)},
	{"UNIDADDESTINO",V10CADENA,(size_t)&svdconversiones.unidaddestino,sizeof(svdconversiones.unidaddestino)},
	{"FACTORCONVERSION",V10DOUBLE,(size_t)&svdconversiones.factorconversion,sizeof(svdconversiones.factorconversion)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdconversiones.codopemodif,sizeof(svdconversiones.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdconversiones.fecmodif,sizeof(svdconversiones.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdconversiones.horamodif,sizeof(svdconversiones.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdconversiones.codcomen,sizeof(svdconversiones.codcomen)}
	};
static diccionarios dvdconversiones[]={
    {colvdconversiones,8}
};
diccionario dcon={dvdconversiones,1};

static char msglogCON[LCADENA];
static char msgdebugCON[LCADENABIG];
static int init=0;


static void fin_vd_con(void)
{
if (vdselconunidades) {
    liberacursor(vdselconunidades);
    vdselconunidades = NULL;
}
if (vdselconvdconversiones) {
    liberacursor(vdselconvdconversiones);
    vdselconvdconversiones = NULL;
}
}
static void init_selconunidades(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconversiones[0].numcol;nc++) dvdconversiones[0].c[nc].offset-=(size_t)&svdconversiones;
    vdselconunidades=abrecursordebug(SELCONUNIDADES,1280);
    definetodo(vdselconunidades,svdconversiones.rowid,sizeof(svdconversiones.rowid),V10CADENA,
                          svdconversiones.unidadorigen,sizeof(svdconversiones.unidadorigen),V10CADENA,
                          svdconversiones.unidaddestino,sizeof(svdconversiones.unidaddestino),V10CADENA,
                          &svdconversiones.factorconversion,sizeof(svdconversiones.factorconversion),V10DOUBLE,
                          svdconversiones.codopemodif,sizeof(svdconversiones.codopemodif),V10CADENA,
                          &svdconversiones.fecmodif,sizeof(svdconversiones.fecmodif),V10LONG,
                          svdconversiones.horamodif,sizeof(svdconversiones.horamodif),V10CADENA,
                          &svdconversiones.codcomen,sizeof(svdconversiones.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselconunidades,"UNIDADORIGEN",svdconversiones.unidadorigen,sizeof(svdconversiones.unidadorigen),V10CADENA,
                          "UNIDADDESTINO",svdconversiones.unidaddestino,sizeof(svdconversiones.unidaddestino),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_con);
        init = 1;
    }
}

static void init_selconvdconversiones(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconversiones[0].numcol;nc++) dvdconversiones[0].c[nc].offset-=(size_t)&svdconversiones;
    vdselconvdconversiones=abrecursordebug(SELCONVDCONVERSIONES,1280);
    definetodo(vdselconvdconversiones,svdconversiones.rowid,sizeof(svdconversiones.rowid),V10CADENA,
                          svdconversiones.unidadorigen,sizeof(svdconversiones.unidadorigen),V10CADENA,
                          svdconversiones.unidaddestino,sizeof(svdconversiones.unidaddestino),V10CADENA,
                          &svdconversiones.factorconversion,sizeof(svdconversiones.factorconversion),V10DOUBLE,
                          svdconversiones.codopemodif,sizeof(svdconversiones.codopemodif),V10CADENA,
                          &svdconversiones.fecmodif,sizeof(svdconversiones.fecmodif),V10LONG,
                          svdconversiones.horamodif,sizeof(svdconversiones.horamodif),V10CADENA,
                          &svdconversiones.codcomen,sizeof(svdconversiones.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselconvdconversiones,"UNIDADORIGEN",svdconversiones.unidadorigen,sizeof(svdconversiones.unidadorigen),V10CADENA,
                          "UNIDADDESTINO",svdconversiones.unidaddestino,sizeof(svdconversiones.unidaddestino),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_con);
        init = 1;
    }
}

diccionario *CONdamediccionario(void)
{
     return(&dcon);
}

int CONselunidades(char *unidadorigen,char *unidaddestino,vdconversioness *con)
{
  int vdret;
  if (vdselconunidades==NULL) init_selconunidades();
  memset(&svdconversiones,0,sizeof(svdconversiones));
  strcpy(svdconversiones.unidadorigen,unidadorigen);
  strcpy(svdconversiones.unidaddestino,unidaddestino);
  vdret=ejefetchcursor(vdselconunidades);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselconunidades. vdret %d. \n",CONlog(&svdconversiones),vdret);
    return(VD_EERRORACLE);
   }
  *con=svdconversiones;
  return(vdret);
}

int CONselvdconversiones(char *unidadorigen,char *unidaddestino,vdconversioness *con)
{
  int vdret;
  if (vdselconvdconversiones==NULL) init_selconvdconversiones();
  memset(&svdconversiones,0,sizeof(svdconversiones));
  strcpy(svdconversiones.unidadorigen,unidadorigen);
  strcpy(svdconversiones.unidaddestino,unidaddestino);
  vdret=ejefetchcursor(vdselconvdconversiones);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselconvdconversiones. vdret %d. \n",CONlog(&svdconversiones),vdret);
    return(VD_EERRORACLE);
   }
  *con=svdconversiones;
  return(vdret);
}

char * CONlog(vdconversioness *con)
{
    sprintf(msglogCON, "VDCONVERSIONES: unidadorigen %s unidaddestino %s ",con->unidadorigen,con->unidaddestino);
    return(msglogCON);
}

char * CONdebug(vdconversioness *con)
{
    debugestruct(&dcon,con,msgdebugCON);
    return(msgdebugCON);
}

