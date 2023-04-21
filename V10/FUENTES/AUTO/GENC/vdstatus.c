// Modulo generado automaticamente a partir de VDSTATUS.DEF
//#***
//# VDSTATUS.c - Generación automática del código c para la tabla                                                        
//# 
//# Propósito: Funciones de acceso a la tabla VDSTATUS
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 8-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=STA
//
//CLAVE=ABREVIADA, TIPOSTATUS, DABSTATUS
// 

#include "vd.h"
#define SELSTAABREVIADA "SELECT VDSTATUS.ROWID,VDSTATUS.TIPOSTATUS,VDSTATUS.STATUS, "\
                    " VDSTATUS.DESSTATUS,VDSTATUS.DABSTATUS,VDSTATUS.TIPOAPP, "\
                    " VDSTATUS.CODOPEMODIF,VDSTATUS.FECMODIF,VDSTATUS.HORAMODIF, "\
                    " VDSTATUS.CODCOMEN "\
        " FROM VDSTATUS"\
        " WHERE "\
               " VDSTATUS.TIPOSTATUS=:TIPOSTATUS "\
               " AND VDSTATUS.DABSTATUS=:DABSTATUS "
static v10cursors *vdselstaabreviada;

#define SELSTAVDSTATUS "SELECT VDSTATUS.ROWID,VDSTATUS.TIPOSTATUS,VDSTATUS.STATUS, "\
                    " VDSTATUS.DESSTATUS,VDSTATUS.DABSTATUS,VDSTATUS.TIPOAPP, "\
                    " VDSTATUS.CODOPEMODIF,VDSTATUS.FECMODIF,VDSTATUS.HORAMODIF, "\
                    " VDSTATUS.CODCOMEN "\
        " FROM VDSTATUS"\
        " WHERE "\
               " VDSTATUS.TIPOSTATUS=:TIPOSTATUS "\
               " AND VDSTATUS.STATUS=:STATUS "
static v10cursors *vdselstavdstatus;

static vdstatuss svdstatus;

static diccols colvdstatus[]={
	{"ROWID",V10CADENA,(size_t)&svdstatus.rowid,sizeof(svdstatus.rowid)},
	{"TIPOSTATUS",V10CADENA,(size_t)&svdstatus.tipostatus,sizeof(svdstatus.tipostatus)},
	{"STATUS",V10LONG,(size_t)&svdstatus.status,sizeof(svdstatus.status)},
	{"DESSTATUS",V10CADENA,(size_t)&svdstatus.desstatus,sizeof(svdstatus.desstatus)},
	{"DABSTATUS",V10CADENA,(size_t)&svdstatus.dabstatus,sizeof(svdstatus.dabstatus)},
	{"TIPOAPP",V10CADENA,(size_t)&svdstatus.tipoapp,sizeof(svdstatus.tipoapp)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdstatus.codopemodif,sizeof(svdstatus.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdstatus.fecmodif,sizeof(svdstatus.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdstatus.horamodif,sizeof(svdstatus.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdstatus.codcomen,sizeof(svdstatus.codcomen)}
	};
static diccionarios dvdstatus[]={
    {colvdstatus,10}
};
diccionario dsta={dvdstatus,1};

static char msglogSTA[LCADENA];
static char msgdebugSTA[LCADENABIG];
static int init=0;


static void fin_vd_sta(void)
{
if (vdselstaabreviada) {
    liberacursor(vdselstaabreviada);
    vdselstaabreviada = NULL;
}
if (vdselstavdstatus) {
    liberacursor(vdselstavdstatus);
    vdselstavdstatus = NULL;
}
}
static void init_selstaabreviada(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstatus[0].numcol;nc++) dvdstatus[0].c[nc].offset-=(size_t)&svdstatus;
    vdselstaabreviada=abrecursordebug(SELSTAABREVIADA,1280);
    definetodo(vdselstaabreviada,svdstatus.rowid,sizeof(svdstatus.rowid),V10CADENA,
                          svdstatus.tipostatus,sizeof(svdstatus.tipostatus),V10CADENA,
                          &svdstatus.status,sizeof(svdstatus.status),V10LONG,
                          svdstatus.desstatus,sizeof(svdstatus.desstatus),V10CADENA,
                          svdstatus.dabstatus,sizeof(svdstatus.dabstatus),V10CADENA,
                          svdstatus.tipoapp,sizeof(svdstatus.tipoapp),V10CADENA,
                          svdstatus.codopemodif,sizeof(svdstatus.codopemodif),V10CADENA,
                          &svdstatus.fecmodif,sizeof(svdstatus.fecmodif),V10LONG,
                          svdstatus.horamodif,sizeof(svdstatus.horamodif),V10CADENA,
                          &svdstatus.codcomen,sizeof(svdstatus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselstaabreviada,"TIPOSTATUS",svdstatus.tipostatus,sizeof(svdstatus.tipostatus),V10CADENA,
                          "DABSTATUS",svdstatus.dabstatus,sizeof(svdstatus.dabstatus),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_sta);
        init = 1;
    }
}

static void init_selstavdstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstatus[0].numcol;nc++) dvdstatus[0].c[nc].offset-=(size_t)&svdstatus;
    vdselstavdstatus=abrecursordebug(SELSTAVDSTATUS,1280);
    definetodo(vdselstavdstatus,svdstatus.rowid,sizeof(svdstatus.rowid),V10CADENA,
                          svdstatus.tipostatus,sizeof(svdstatus.tipostatus),V10CADENA,
                          &svdstatus.status,sizeof(svdstatus.status),V10LONG,
                          svdstatus.desstatus,sizeof(svdstatus.desstatus),V10CADENA,
                          svdstatus.dabstatus,sizeof(svdstatus.dabstatus),V10CADENA,
                          svdstatus.tipoapp,sizeof(svdstatus.tipoapp),V10CADENA,
                          svdstatus.codopemodif,sizeof(svdstatus.codopemodif),V10CADENA,
                          &svdstatus.fecmodif,sizeof(svdstatus.fecmodif),V10LONG,
                          svdstatus.horamodif,sizeof(svdstatus.horamodif),V10CADENA,
                          &svdstatus.codcomen,sizeof(svdstatus.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselstavdstatus,"TIPOSTATUS",svdstatus.tipostatus,sizeof(svdstatus.tipostatus),V10CADENA,
                          "STATUS",&svdstatus.status,sizeof(svdstatus.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_sta);
        init = 1;
    }
}

diccionario *STAdamediccionario(void)
{
     return(&dsta);
}

int STAselabreviada(char *tipostatus,char *dabstatus,vdstatuss *sta)
{
  int vdret;
  if (vdselstaabreviada==NULL) init_selstaabreviada();
  memset(&svdstatus,0,sizeof(svdstatus));
  strcpy(svdstatus.tipostatus,tipostatus);
  strcpy(svdstatus.dabstatus,dabstatus);
  vdret=ejefetchcursor(vdselstaabreviada);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselstaabreviada. vdret %d. \n",STAlog(&svdstatus),vdret);
    return(VD_EERRORACLE);
   }
  *sta=svdstatus;
  return(vdret);
}

int STAselvdstatus(char *tipostatus,long status,vdstatuss *sta)
{
  int vdret;
  if (vdselstavdstatus==NULL) init_selstavdstatus();
  memset(&svdstatus,0,sizeof(svdstatus));
  strcpy(svdstatus.tipostatus,tipostatus);
  svdstatus.status=status;
  vdret=ejefetchcursor(vdselstavdstatus);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselstavdstatus. vdret %d. \n",STAlog(&svdstatus),vdret);
    return(VD_EERRORACLE);
   }
  *sta=svdstatus;
  return(vdret);
}

char * STAlog(vdstatuss *sta)
{
    sprintf(msglogSTA, "VDSTATUS: tipostatus %s status %ld ",sta->tipostatus,sta->status);
    return(msglogSTA);
}

char * STAdebug(vdstatuss *sta)
{
    debugestruct(&dsta,sta,msgdebugSTA);
    return(msgdebugSTA);
}

