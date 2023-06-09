// Modulo generado automaticamente a partir de VDASIGNAGE.DEF
//#***
//# VDASIGNAGE.DEF - Generaci�n autom�tica del c�digo c para la tabla de Asignaci�n 
//#                  de Agencias
//#                        
//# Prop�sito: Funciones de acceso a la tabla VDASIGNAGE
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 12-03-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=ASA
//RECORRE=CODAGE,CODAGE
//

#include "vd.h"
#define SELASACODAGE "SELECT VDASIGNAGE.ROWID,VDASIGNAGE.SECASIGNAGE,VDASIGNAGE.PRIORIDADREGLA, "\
                    " VDASIGNAGE.CODAGE,VDASIGNAGE.RANGOCLIENTE,VDASIGNAGE.RANGODP, "\
                    " VDASIGNAGE.RANGOZONAGEO,VDASIGNAGE.RANGOPESO,VDASIGNAGE.RANGOVOLUMEN, "\
                    " VDASIGNAGE.RANGOBULTOS,VDASIGNAGE.RANGOTIPOPEDIDO,VDASIGNAGE.RANGOCODDIVPED, "\
                    " VDASIGNAGE.RANGOCODART,VDASIGNAGE.RANGOCODDIVART,VDASIGNAGE.RANGOCODCLASE, "\
                    " VDASIGNAGE.RANGOCODAGE,VDASIGNAGE.RANGOCODPAIS,VDASIGNAGE.URGENCIA, "\
                    " VDASIGNAGE.PRIORIDAD,VDASIGNAGE.VDEXTRA,VDASIGNAGE.CODOPEMODIF, "\
                    " VDASIGNAGE.FECMODIF,VDASIGNAGE.HORAMODIF,VDASIGNAGE.CODCOMEN, "\
                    " VDASIGNAGE.ENTORNO "\
        " FROM VDASIGNAGE"\
        " WHERE "\
               " VDASIGNAGE.CODAGE=:CODAGE "
static v10cursors *vdselasacodage;

#define SELASAVDASIGNAGE "SELECT VDASIGNAGE.ROWID,VDASIGNAGE.SECASIGNAGE,VDASIGNAGE.PRIORIDADREGLA, "\
                    " VDASIGNAGE.CODAGE,VDASIGNAGE.RANGOCLIENTE,VDASIGNAGE.RANGODP, "\
                    " VDASIGNAGE.RANGOZONAGEO,VDASIGNAGE.RANGOPESO,VDASIGNAGE.RANGOVOLUMEN, "\
                    " VDASIGNAGE.RANGOBULTOS,VDASIGNAGE.RANGOTIPOPEDIDO,VDASIGNAGE.RANGOCODDIVPED, "\
                    " VDASIGNAGE.RANGOCODART,VDASIGNAGE.RANGOCODDIVART,VDASIGNAGE.RANGOCODCLASE, "\
                    " VDASIGNAGE.RANGOCODAGE,VDASIGNAGE.RANGOCODPAIS,VDASIGNAGE.URGENCIA, "\
                    " VDASIGNAGE.PRIORIDAD,VDASIGNAGE.VDEXTRA,VDASIGNAGE.CODOPEMODIF, "\
                    " VDASIGNAGE.FECMODIF,VDASIGNAGE.HORAMODIF,VDASIGNAGE.CODCOMEN, "\
                    " VDASIGNAGE.ENTORNO "\
        " FROM VDASIGNAGE"\
        " WHERE "\
               " VDASIGNAGE.SECASIGNAGE=:SECASIGNAGE "
static v10cursors *vdselasavdasignage;

static vdasignages svdasignage;

static diccols colvdasignage[]={
	{"ROWID",V10CADENA,(size_t)&svdasignage.rowid,sizeof(svdasignage.rowid)},
	{"SECASIGNAGE",V10LONG,(size_t)&svdasignage.secasignage,sizeof(svdasignage.secasignage)},
	{"PRIORIDADREGLA",V10LONG,(size_t)&svdasignage.prioridadregla,sizeof(svdasignage.prioridadregla)},
	{"CODAGE",V10CADENA,(size_t)&svdasignage.codage,sizeof(svdasignage.codage)},
	{"RANGOCLIENTE",V10CADENA,(size_t)&svdasignage.rangocliente,sizeof(svdasignage.rangocliente)},
	{"RANGODP",V10CADENA,(size_t)&svdasignage.rangodp,sizeof(svdasignage.rangodp)},
	{"RANGOZONAGEO",V10CADENA,(size_t)&svdasignage.rangozonageo,sizeof(svdasignage.rangozonageo)},
	{"RANGOPESO",V10CADENA,(size_t)&svdasignage.rangopeso,sizeof(svdasignage.rangopeso)},
	{"RANGOVOLUMEN",V10CADENA,(size_t)&svdasignage.rangovolumen,sizeof(svdasignage.rangovolumen)},
	{"RANGOBULTOS",V10CADENA,(size_t)&svdasignage.rangobultos,sizeof(svdasignage.rangobultos)},
	{"RANGOTIPOPEDIDO",V10CADENA,(size_t)&svdasignage.rangotipopedido,sizeof(svdasignage.rangotipopedido)},
	{"RANGOCODDIVPED",V10CADENA,(size_t)&svdasignage.rangocoddivped,sizeof(svdasignage.rangocoddivped)},
	{"RANGOCODART",V10CADENA,(size_t)&svdasignage.rangocodart,sizeof(svdasignage.rangocodart)},
	{"RANGOCODDIVART",V10CADENA,(size_t)&svdasignage.rangocoddivart,sizeof(svdasignage.rangocoddivart)},
	{"RANGOCODCLASE",V10CADENA,(size_t)&svdasignage.rangocodclase,sizeof(svdasignage.rangocodclase)},
	{"RANGOCODAGE",V10CADENA,(size_t)&svdasignage.rangocodage,sizeof(svdasignage.rangocodage)},
	{"RANGOCODPAIS",V10CADENA,(size_t)&svdasignage.rangocodpais,sizeof(svdasignage.rangocodpais)},
	{"URGENCIA",V10LONG,(size_t)&svdasignage.urgencia,sizeof(svdasignage.urgencia)},
	{"PRIORIDAD",V10LONG,(size_t)&svdasignage.prioridad,sizeof(svdasignage.prioridad)},
	{"VDEXTRA",V10CADENA,(size_t)&svdasignage.vdextra,sizeof(svdasignage.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdasignage.codopemodif,sizeof(svdasignage.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdasignage.fecmodif,sizeof(svdasignage.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdasignage.horamodif,sizeof(svdasignage.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdasignage.codcomen,sizeof(svdasignage.codcomen)},
	{"ENTORNO",V10CADENA,(size_t)&svdasignage.entorno,sizeof(svdasignage.entorno)}
	};
static diccionarios dvdasignage[]={
    {colvdasignage,25}
};
diccionario dasa={dvdasignage,1};

static char msglogASA[LCADENA];
static char msgdebugASA[LCADENABIG];
static int init=0;


static void fin_vd_asa(void)
{
if (vdselasacodage) {
    liberacursor(vdselasacodage);
    vdselasacodage = NULL;
}
if (vdselasavdasignage) {
    liberacursor(vdselasavdasignage);
    vdselasavdasignage = NULL;
}
}
static void init_selasacodage(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdasignage[0].numcol;nc++) dvdasignage[0].c[nc].offset-=(size_t)&svdasignage;
    vdselasacodage=abrecursordebug(SELASACODAGE,1280);
    definetodo(vdselasacodage,svdasignage.rowid,sizeof(svdasignage.rowid),V10CADENA,
                          &svdasignage.secasignage,sizeof(svdasignage.secasignage),V10LONG,
                          &svdasignage.prioridadregla,sizeof(svdasignage.prioridadregla),V10LONG,
                          svdasignage.codage,sizeof(svdasignage.codage),V10CADENA,
                          svdasignage.rangocliente,sizeof(svdasignage.rangocliente),V10CADENA,
                          svdasignage.rangodp,sizeof(svdasignage.rangodp),V10CADENA,
                          svdasignage.rangozonageo,sizeof(svdasignage.rangozonageo),V10CADENA,
                          svdasignage.rangopeso,sizeof(svdasignage.rangopeso),V10CADENA,
                          svdasignage.rangovolumen,sizeof(svdasignage.rangovolumen),V10CADENA,
                          svdasignage.rangobultos,sizeof(svdasignage.rangobultos),V10CADENA,
                          svdasignage.rangotipopedido,sizeof(svdasignage.rangotipopedido),V10CADENA,
                          svdasignage.rangocoddivped,sizeof(svdasignage.rangocoddivped),V10CADENA,
                          svdasignage.rangocodart,sizeof(svdasignage.rangocodart),V10CADENA,
                          svdasignage.rangocoddivart,sizeof(svdasignage.rangocoddivart),V10CADENA,
                          svdasignage.rangocodclase,sizeof(svdasignage.rangocodclase),V10CADENA,
                          svdasignage.rangocodage,sizeof(svdasignage.rangocodage),V10CADENA,
                          svdasignage.rangocodpais,sizeof(svdasignage.rangocodpais),V10CADENA,
                          &svdasignage.urgencia,sizeof(svdasignage.urgencia),V10LONG,
                          &svdasignage.prioridad,sizeof(svdasignage.prioridad),V10LONG,
                          svdasignage.vdextra,sizeof(svdasignage.vdextra),V10CADENA,
                          svdasignage.codopemodif,sizeof(svdasignage.codopemodif),V10CADENA,
                          &svdasignage.fecmodif,sizeof(svdasignage.fecmodif),V10LONG,
                          svdasignage.horamodif,sizeof(svdasignage.horamodif),V10CADENA,
                          &svdasignage.codcomen,sizeof(svdasignage.codcomen),V10LONG,
                          svdasignage.entorno,sizeof(svdasignage.entorno),V10CADENA,
                          NULL);
    bindtodo(vdselasacodage,"CODAGE",svdasignage.codage,sizeof(svdasignage.codage),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_asa);
        init = 1;
    }
}

static void init_selasavdasignage(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdasignage[0].numcol;nc++) dvdasignage[0].c[nc].offset-=(size_t)&svdasignage;
    vdselasavdasignage=abrecursordebug(SELASAVDASIGNAGE,1280);
    definetodo(vdselasavdasignage,svdasignage.rowid,sizeof(svdasignage.rowid),V10CADENA,
                          &svdasignage.secasignage,sizeof(svdasignage.secasignage),V10LONG,
                          &svdasignage.prioridadregla,sizeof(svdasignage.prioridadregla),V10LONG,
                          svdasignage.codage,sizeof(svdasignage.codage),V10CADENA,
                          svdasignage.rangocliente,sizeof(svdasignage.rangocliente),V10CADENA,
                          svdasignage.rangodp,sizeof(svdasignage.rangodp),V10CADENA,
                          svdasignage.rangozonageo,sizeof(svdasignage.rangozonageo),V10CADENA,
                          svdasignage.rangopeso,sizeof(svdasignage.rangopeso),V10CADENA,
                          svdasignage.rangovolumen,sizeof(svdasignage.rangovolumen),V10CADENA,
                          svdasignage.rangobultos,sizeof(svdasignage.rangobultos),V10CADENA,
                          svdasignage.rangotipopedido,sizeof(svdasignage.rangotipopedido),V10CADENA,
                          svdasignage.rangocoddivped,sizeof(svdasignage.rangocoddivped),V10CADENA,
                          svdasignage.rangocodart,sizeof(svdasignage.rangocodart),V10CADENA,
                          svdasignage.rangocoddivart,sizeof(svdasignage.rangocoddivart),V10CADENA,
                          svdasignage.rangocodclase,sizeof(svdasignage.rangocodclase),V10CADENA,
                          svdasignage.rangocodage,sizeof(svdasignage.rangocodage),V10CADENA,
                          svdasignage.rangocodpais,sizeof(svdasignage.rangocodpais),V10CADENA,
                          &svdasignage.urgencia,sizeof(svdasignage.urgencia),V10LONG,
                          &svdasignage.prioridad,sizeof(svdasignage.prioridad),V10LONG,
                          svdasignage.vdextra,sizeof(svdasignage.vdextra),V10CADENA,
                          svdasignage.codopemodif,sizeof(svdasignage.codopemodif),V10CADENA,
                          &svdasignage.fecmodif,sizeof(svdasignage.fecmodif),V10LONG,
                          svdasignage.horamodif,sizeof(svdasignage.horamodif),V10CADENA,
                          &svdasignage.codcomen,sizeof(svdasignage.codcomen),V10LONG,
                          svdasignage.entorno,sizeof(svdasignage.entorno),V10CADENA,
                          NULL);
    bindtodo(vdselasavdasignage,"SECASIGNAGE",&svdasignage.secasignage,sizeof(svdasignage.secasignage),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_asa);
        init = 1;
    }
}

diccionario *ASAdamediccionario(void)
{
     return(&dasa);
}

int ASAbuscacodage(char *codage,vdasignages *asa)
{
  int vdret;
  memset(&svdasignage,0,sizeof(svdasignage));
  strcpy(svdasignage.codage,codage);
  if (vdselasacodage==NULL) init_selasacodage();
  vdret=ejefetchcursor(vdselasacodage);
  if (vdret==0) {
     *asa=svdasignage;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselasacodage. vdret %d. \n",ASAlog(&svdasignage),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ASAnextcodage(vdasignages *asa)
{
  int vdret;
  vdret=fetchcursor(vdselasacodage);
  if (vdret==0) {
     *asa=svdasignage;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselasacodage. vdret %d. \n",ASAlog(&svdasignage),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselasacodage);
  return(VD_EERRORACLE);
}

int ASAselvdasignage(long secasignage,vdasignages *asa)
{
  int vdret;
  if (vdselasavdasignage==NULL) init_selasavdasignage();
  memset(&svdasignage,0,sizeof(svdasignage));
  svdasignage.secasignage=secasignage;
  vdret=ejefetchcursor(vdselasavdasignage);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselasavdasignage. vdret %d. \n",ASAlog(&svdasignage),vdret);
    return(VD_EERRORACLE);
   }
  *asa=svdasignage;
  return(vdret);
}

char * ASAlog(vdasignages *asa)
{
    sprintf(msglogASA, "VDASIGNAGE: secasignage %ld ",asa->secasignage);
    return(msglogASA);
}

char * ASAdebug(vdasignages *asa)
{
    debugestruct(&dasa,asa,msgdebugASA);
    return(msgdebugASA);
}

