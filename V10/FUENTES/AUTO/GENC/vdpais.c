// Modulo generado automaticamente a partir de VDPAIS.DEF
//#***
//# VDPAIS.c - Generación automática del código c para la tabla de paises                                                      
//# 
//# Propósito: Funciones de acceso a la tabla VDPAIS
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 11-12-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=PAIS
//
//RECORRE=DESPAIS,DESPAIS
//

#include "vd.h"
#define SELPAISDESPAIS "SELECT VDPAIS.ROWID,VDPAIS.CODPAIS,VDPAIS.DESPAIS, "\
                    " VDPAIS.CODOPEMODIF,VDPAIS.FECMODIF,VDPAIS.HORAMODIF, "\
                    " VDPAIS.CODCOMEN "\
        " FROM VDPAIS"\
        " WHERE "\
               " VDPAIS.DESPAIS=:DESPAIS "
static v10cursors *vdselpaisdespais;

#define SELPAISVDPAIS "SELECT VDPAIS.ROWID,VDPAIS.CODPAIS,VDPAIS.DESPAIS, "\
                    " VDPAIS.CODOPEMODIF,VDPAIS.FECMODIF,VDPAIS.HORAMODIF, "\
                    " VDPAIS.CODCOMEN "\
        " FROM VDPAIS"\
        " WHERE "\
               " VDPAIS.CODPAIS=:CODPAIS "
static v10cursors *vdselpaisvdpais;

static vdpaiss svdpais;

static diccols colvdpais[]={
	{"ROWID",V10CADENA,(size_t)&svdpais.rowid,sizeof(svdpais.rowid)},
	{"CODPAIS",V10CADENA,(size_t)&svdpais.codpais,sizeof(svdpais.codpais)},
	{"DESPAIS",V10CADENA,(size_t)&svdpais.despais,sizeof(svdpais.despais)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdpais.codopemodif,sizeof(svdpais.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdpais.fecmodif,sizeof(svdpais.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdpais.horamodif,sizeof(svdpais.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdpais.codcomen,sizeof(svdpais.codcomen)}
	};
static diccionarios dvdpais[]={
    {colvdpais,7}
};
diccionario dpais={dvdpais,1};

static char msglogPAIS[LCADENA];
static char msgdebugPAIS[LCADENABIG];
static int init=0;


static void fin_vd_pais(void)
{
if (vdselpaisdespais) {
    liberacursor(vdselpaisdespais);
    vdselpaisdespais = NULL;
}
if (vdselpaisvdpais) {
    liberacursor(vdselpaisvdpais);
    vdselpaisvdpais = NULL;
}
}
static void init_selpaisdespais(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpais[0].numcol;nc++) dvdpais[0].c[nc].offset-=(size_t)&svdpais;
    vdselpaisdespais=abrecursordebug(SELPAISDESPAIS,1280);
    definetodo(vdselpaisdespais,svdpais.rowid,sizeof(svdpais.rowid),V10CADENA,
                          svdpais.codpais,sizeof(svdpais.codpais),V10CADENA,
                          svdpais.despais,sizeof(svdpais.despais),V10CADENA,
                          svdpais.codopemodif,sizeof(svdpais.codopemodif),V10CADENA,
                          &svdpais.fecmodif,sizeof(svdpais.fecmodif),V10LONG,
                          svdpais.horamodif,sizeof(svdpais.horamodif),V10CADENA,
                          &svdpais.codcomen,sizeof(svdpais.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselpaisdespais,"DESPAIS",svdpais.despais,sizeof(svdpais.despais),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pais);
        init = 1;
    }
}

static void init_selpaisvdpais(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpais[0].numcol;nc++) dvdpais[0].c[nc].offset-=(size_t)&svdpais;
    vdselpaisvdpais=abrecursordebug(SELPAISVDPAIS,1280);
    definetodo(vdselpaisvdpais,svdpais.rowid,sizeof(svdpais.rowid),V10CADENA,
                          svdpais.codpais,sizeof(svdpais.codpais),V10CADENA,
                          svdpais.despais,sizeof(svdpais.despais),V10CADENA,
                          svdpais.codopemodif,sizeof(svdpais.codopemodif),V10CADENA,
                          &svdpais.fecmodif,sizeof(svdpais.fecmodif),V10LONG,
                          svdpais.horamodif,sizeof(svdpais.horamodif),V10CADENA,
                          &svdpais.codcomen,sizeof(svdpais.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselpaisvdpais,"CODPAIS",svdpais.codpais,sizeof(svdpais.codpais),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pais);
        init = 1;
    }
}

diccionario *PAISdamediccionario(void)
{
     return(&dpais);
}

int PAISbuscadespais(char *despais,vdpaiss *pais)
{
  int vdret;
  memset(&svdpais,0,sizeof(svdpais));
  strcpy(svdpais.despais,despais);
  if (vdselpaisdespais==NULL) init_selpaisdespais();
  vdret=ejefetchcursor(vdselpaisdespais);
  if (vdret==0) {
     *pais=svdpais;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpaisdespais. vdret %d. \n",PAISlog(&svdpais),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PAISnextdespais(vdpaiss *pais)
{
  int vdret;
  vdret=fetchcursor(vdselpaisdespais);
  if (vdret==0) {
     *pais=svdpais;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpaisdespais. vdret %d. \n",PAISlog(&svdpais),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpaisdespais);
  return(VD_EERRORACLE);
}

int PAISselvdpais(char *codpais,vdpaiss *pais)
{
  int vdret;
  if (vdselpaisvdpais==NULL) init_selpaisvdpais();
  memset(&svdpais,0,sizeof(svdpais));
  strcpy(svdpais.codpais,codpais);
  vdret=ejefetchcursor(vdselpaisvdpais);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpaisvdpais. vdret %d. \n",PAISlog(&svdpais),vdret);
    return(VD_EERRORACLE);
   }
  *pais=svdpais;
  return(vdret);
}

char * PAISlog(vdpaiss *pais)
{
    sprintf(msglogPAIS, "VDPAIS: codpais %s ",pais->codpais);
    return(msglogPAIS);
}

char * PAISdebug(vdpaiss *pais)
{
    debugestruct(&dpais,pais,msgdebugPAIS);
    return(msgdebugPAIS);
}

