// Modulo generado automaticamente a partir de VDFLUJOPARAM.DEF
//#***
//# VDFLUJOPARAM.c - Generaci�n autom�tica del c�digo c para la tabla                                                        
//# 
//# Prop�sito: Funciones de acceso a la tabla VDFLUJOPARAM
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 12-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=FLP
//
//
// 

#include "vd.h"
#define SELFLPVDFLUJOPARAM "SELECT VDFLUJOPARAM.ROWID,VDFLUJOPARAM.CODFLUJO,VDFLUJOPARAM.TAREA, "\
                    " VDFLUJOPARAM.CODAREAORI,VDFLUJOPARAM.CODAREADEST,VDFLUJOPARAM.CODCLASIF, "\
                    " VDFLUJOPARAM.CODCLASE,VDFLUJOPARAM.PATRONESTADO,VDFLUJOPARAM.CODCONCE, "\
                    " VDFLUJOPARAM.PRIOFLUJO,VDFLUJOPARAM.SUBPRIOFLUJO,VDFLUJOPARAM.PRIOMOV, "\
                    " VDFLUJOPARAM.TIPOSTATUS,VDFLUJOPARAM.DABSTATUS,VDFLUJOPARAM.CODCAMINO, "\
                    " VDFLUJOPARAM.CODOPEMODIF,VDFLUJOPARAM.FECMODIF,VDFLUJOPARAM.HORAMODIF, "\
                    " VDFLUJOPARAM.CODCOMEN "\
        " FROM VDFLUJOPARAM"\
        " WHERE "\
               " VDFLUJOPARAM.CODFLUJO=:CODFLUJO "
static v10cursors *vdselflpvdflujoparam;

static vdflujoparams svdflujoparam;

static diccols colvdflujoparam[]={
	{"ROWID",V10CADENA,(size_t)&svdflujoparam.rowid,sizeof(svdflujoparam.rowid)},
	{"CODFLUJO",V10LONG,(size_t)&svdflujoparam.codflujo,sizeof(svdflujoparam.codflujo)},
	{"TAREA",V10CADENA,(size_t)&svdflujoparam.tarea,sizeof(svdflujoparam.tarea)},
	{"CODAREAORI",V10CADENA,(size_t)&svdflujoparam.codareaori,sizeof(svdflujoparam.codareaori)},
	{"CODAREADEST",V10CADENA,(size_t)&svdflujoparam.codareadest,sizeof(svdflujoparam.codareadest)},
	{"CODCLASIF",V10CADENA,(size_t)&svdflujoparam.codclasif,sizeof(svdflujoparam.codclasif)},
	{"CODCLASE",V10CADENA,(size_t)&svdflujoparam.codclase,sizeof(svdflujoparam.codclase)},
	{"PATRONESTADO",V10CADENA,(size_t)&svdflujoparam.patronestado,sizeof(svdflujoparam.patronestado)},
	{"CODCONCE",V10CADENA,(size_t)&svdflujoparam.codconce,sizeof(svdflujoparam.codconce)},
	{"PRIOFLUJO",V10LONG,(size_t)&svdflujoparam.prioflujo,sizeof(svdflujoparam.prioflujo)},
	{"SUBPRIOFLUJO",V10LONG,(size_t)&svdflujoparam.subprioflujo,sizeof(svdflujoparam.subprioflujo)},
	{"PRIOMOV",V10LONG,(size_t)&svdflujoparam.priomov,sizeof(svdflujoparam.priomov)},
	{"TIPOSTATUS",V10CADENA,(size_t)&svdflujoparam.tipostatus,sizeof(svdflujoparam.tipostatus)},
	{"DABSTATUS",V10CADENA,(size_t)&svdflujoparam.dabstatus,sizeof(svdflujoparam.dabstatus)},
	{"CODCAMINO",V10LONG,(size_t)&svdflujoparam.codcamino,sizeof(svdflujoparam.codcamino)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdflujoparam.codopemodif,sizeof(svdflujoparam.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdflujoparam.fecmodif,sizeof(svdflujoparam.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdflujoparam.horamodif,sizeof(svdflujoparam.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdflujoparam.codcomen,sizeof(svdflujoparam.codcomen)}
	};
static diccionarios dvdflujoparam[]={
    {colvdflujoparam,19}
};
diccionario dflp={dvdflujoparam,1};

static char msglogFLP[LCADENA];
static char msgdebugFLP[LCADENABIG];
static int init=0;


static void fin_vd_flp(void)
{
if (vdselflpvdflujoparam) {
    liberacursor(vdselflpvdflujoparam);
    vdselflpvdflujoparam = NULL;
}
}
static void init_selflpvdflujoparam(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdflujoparam[0].numcol;nc++) dvdflujoparam[0].c[nc].offset-=(size_t)&svdflujoparam;
    vdselflpvdflujoparam=abrecursordebug(SELFLPVDFLUJOPARAM,1280);
    definetodo(vdselflpvdflujoparam,svdflujoparam.rowid,sizeof(svdflujoparam.rowid),V10CADENA,
                          &svdflujoparam.codflujo,sizeof(svdflujoparam.codflujo),V10LONG,
                          svdflujoparam.tarea,sizeof(svdflujoparam.tarea),V10CADENA,
                          svdflujoparam.codareaori,sizeof(svdflujoparam.codareaori),V10CADENA,
                          svdflujoparam.codareadest,sizeof(svdflujoparam.codareadest),V10CADENA,
                          svdflujoparam.codclasif,sizeof(svdflujoparam.codclasif),V10CADENA,
                          svdflujoparam.codclase,sizeof(svdflujoparam.codclase),V10CADENA,
                          svdflujoparam.patronestado,sizeof(svdflujoparam.patronestado),V10CADENA,
                          svdflujoparam.codconce,sizeof(svdflujoparam.codconce),V10CADENA,
                          &svdflujoparam.prioflujo,sizeof(svdflujoparam.prioflujo),V10LONG,
                          &svdflujoparam.subprioflujo,sizeof(svdflujoparam.subprioflujo),V10LONG,
                          &svdflujoparam.priomov,sizeof(svdflujoparam.priomov),V10LONG,
                          svdflujoparam.tipostatus,sizeof(svdflujoparam.tipostatus),V10CADENA,
                          svdflujoparam.dabstatus,sizeof(svdflujoparam.dabstatus),V10CADENA,
                          &svdflujoparam.codcamino,sizeof(svdflujoparam.codcamino),V10LONG,
                          svdflujoparam.codopemodif,sizeof(svdflujoparam.codopemodif),V10CADENA,
                          &svdflujoparam.fecmodif,sizeof(svdflujoparam.fecmodif),V10LONG,
                          svdflujoparam.horamodif,sizeof(svdflujoparam.horamodif),V10CADENA,
                          &svdflujoparam.codcomen,sizeof(svdflujoparam.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselflpvdflujoparam,"CODFLUJO",&svdflujoparam.codflujo,sizeof(svdflujoparam.codflujo),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_flp);
        init = 1;
    }
}

diccionario *FLPdamediccionario(void)
{
     return(&dflp);
}

int FLPselvdflujoparam(long codflujo,vdflujoparams *flp)
{
  int vdret;
  if (vdselflpvdflujoparam==NULL) init_selflpvdflujoparam();
  memset(&svdflujoparam,0,sizeof(svdflujoparam));
  svdflujoparam.codflujo=codflujo;
  vdret=ejefetchcursor(vdselflpvdflujoparam);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselflpvdflujoparam. vdret %d. \n",FLPlog(&svdflujoparam),vdret);
    return(VD_EERRORACLE);
   }
  *flp=svdflujoparam;
  return(vdret);
}

char * FLPlog(vdflujoparams *flp)
{
    sprintf(msglogFLP, "VDFLUJOPARAM: codflujo %ld ",flp->codflujo);
    return(msglogFLP);
}

char * FLPdebug(vdflujoparams *flp)
{
    debugestruct(&dflp,flp,msgdebugFLP);
    return(msgdebugFLP);
}

