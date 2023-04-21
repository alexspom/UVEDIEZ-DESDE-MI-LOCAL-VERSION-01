// Modulo generado automaticamente a partir de VDCAJAS.DEF
//#***
//# VDCAJAS.DEF - Generación automática del código c para la tabla de Cajas                                                       
//# 
//# Propósito: Funciones de acceso a la tabla VDCAJAS
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 24-04-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=CAJ
//EXTRA=VOLUMENCAJ,V10DOUBLE
//EXTRA=ALTURA,V10LONG
//
//RECORRE=DEMAYORAMENOR,TIPOVOL;ORDERBY=LARGOCAJA*ANCHOCAJA*ALTOCAJA DESC;
//
//INSERT 
//DELETE

#include "vd.h"
#define SELCAJDEMAYORAMENOR "SELECT VDCAJAS.ROWID,VDCAJAS.TIPOVOL,VDCAJAS.TIPOCAJA, "\
                    " VDCAJAS.TIPOEMBA,VDCAJAS.DESCAJA,VDCAJAS.LARGOCAJA, "\
                    " VDCAJAS.ANCHOCAJA,VDCAJAS.ALTOCAJA,VDCAJAS.PESOCAJA, "\
                    " VDCAJAS.PESORELLENO,VDCAJAS.MARGENPESO,VDCAJAS.MAXLLENADO, "\
                    " VDCAJAS.MINLLENADO,VDCAJAS.MAXPICOS,VDCAJAS.MAXPESO, "\
                    " VDCAJAS.VOLDINAMICA,VDCAJAS.CODCOMEN,VDCAJAS.CODOPEMODIF, "\
                    " VDCAJAS.FECMODIF,VDCAJAS.HORAMODIF "\
        " FROM VDCAJAS"\
        " WHERE "\
               " VDCAJAS.TIPOVOL=:TIPOVOL "\
        " ORDER BY LARGOCAJA*ANCHOCAJA*ALTOCAJA DESC "
static v10cursors *vdselcajdemayoramenor;

#define SELCAJVDCAJAS "SELECT VDCAJAS.ROWID,VDCAJAS.TIPOVOL,VDCAJAS.TIPOCAJA, "\
                    " VDCAJAS.TIPOEMBA,VDCAJAS.DESCAJA,VDCAJAS.LARGOCAJA, "\
                    " VDCAJAS.ANCHOCAJA,VDCAJAS.ALTOCAJA,VDCAJAS.PESOCAJA, "\
                    " VDCAJAS.PESORELLENO,VDCAJAS.MARGENPESO,VDCAJAS.MAXLLENADO, "\
                    " VDCAJAS.MINLLENADO,VDCAJAS.MAXPICOS,VDCAJAS.MAXPESO, "\
                    " VDCAJAS.VOLDINAMICA,VDCAJAS.CODCOMEN,VDCAJAS.CODOPEMODIF, "\
                    " VDCAJAS.FECMODIF,VDCAJAS.HORAMODIF "\
        " FROM VDCAJAS"\
        " WHERE "\
               " VDCAJAS.TIPOVOL=:TIPOVOL "\
               " AND VDCAJAS.TIPOCAJA=:TIPOCAJA "
static v10cursors *vdselcajvdcajas;

#define INSCAJ "INSERT INTO VDCAJAS (TIPOVOL,TIPOCAJA,TIPOEMBA,DESCAJA,LARGOCAJA,ANCHOCAJA, "\
                    " ALTOCAJA,PESOCAJA,PESORELLENO,MARGENPESO,MAXLLENADO,MINLLENADO,MAXPICOS, "\
                    " MAXPESO,VOLDINAMICA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :TIPOVOL,:TIPOCAJA,:TIPOEMBA,:DESCAJA,:LARGOCAJA,:ANCHOCAJA, "\
                    " :ALTOCAJA,:PESOCAJA,:PESORELLENO,:MARGENPESO,:MAXLLENADO,:MINLLENADO,:MAXPICOS, "\
                    " :MAXPESO,:VOLDINAMICA,:CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS) "
static v10cursors *vdinscaj;

#define DELCAJ "DELETE VDCAJAS WHERE ROWID=:MIROWID "
static v10cursors *vddelcaj;

static vdcajass svdcajas;

static diccols colvdcajas[]={
	{"ROWID",V10CADENA,(size_t)&svdcajas.rowid,sizeof(svdcajas.rowid)},
	{"TIPOVOL",V10CADENA,(size_t)&svdcajas.tipovol,sizeof(svdcajas.tipovol)},
	{"TIPOCAJA",V10CADENA,(size_t)&svdcajas.tipocaja,sizeof(svdcajas.tipocaja)},
	{"TIPOEMBA",V10CADENA,(size_t)&svdcajas.tipoemba,sizeof(svdcajas.tipoemba)},
	{"DESCAJA",V10CADENA,(size_t)&svdcajas.descaja,sizeof(svdcajas.descaja)},
	{"LARGOCAJA",V10LONG,(size_t)&svdcajas.largocaja,sizeof(svdcajas.largocaja)},
	{"ANCHOCAJA",V10LONG,(size_t)&svdcajas.anchocaja,sizeof(svdcajas.anchocaja)},
	{"ALTOCAJA",V10LONG,(size_t)&svdcajas.altocaja,sizeof(svdcajas.altocaja)},
	{"PESOCAJA",V10LONG,(size_t)&svdcajas.pesocaja,sizeof(svdcajas.pesocaja)},
	{"PESORELLENO",V10LONG,(size_t)&svdcajas.pesorelleno,sizeof(svdcajas.pesorelleno)},
	{"MARGENPESO",V10DOUBLE,(size_t)&svdcajas.margenpeso,sizeof(svdcajas.margenpeso)},
	{"MAXLLENADO",V10LONG,(size_t)&svdcajas.maxllenado,sizeof(svdcajas.maxllenado)},
	{"MINLLENADO",V10LONG,(size_t)&svdcajas.minllenado,sizeof(svdcajas.minllenado)},
	{"MAXPICOS",V10LONG,(size_t)&svdcajas.maxpicos,sizeof(svdcajas.maxpicos)},
	{"MAXPESO",V10LONG,(size_t)&svdcajas.maxpeso,sizeof(svdcajas.maxpeso)},
	{"VOLDINAMICA",V10CADENA,(size_t)&svdcajas.voldinamica,sizeof(svdcajas.voldinamica)},
	{"CODCOMEN",V10LONG,(size_t)&svdcajas.codcomen,sizeof(svdcajas.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdcajas.codopemodif,sizeof(svdcajas.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdcajas.fecmodif,sizeof(svdcajas.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdcajas.horamodif,sizeof(svdcajas.horamodif)},
	{"VOLUMENCAJ",V10DOUBLE,(size_t)&svdcajas.volumencaj,sizeof(svdcajas.volumencaj)},
	{"ALTURA",V10LONG,(size_t)&svdcajas.altura,sizeof(svdcajas.altura)}
	};
static diccionarios dvdcajas[]={
    {colvdcajas,22}
};
diccionario dcaj={dvdcajas,1};

static char msglogCAJ[LCADENA];
static char msgdebugCAJ[LCADENABIG];
static int init=0;


static void fin_vd_caj(void)
{
if (vdselcajdemayoramenor) {
    liberacursor(vdselcajdemayoramenor);
    vdselcajdemayoramenor = NULL;
}
if (vdselcajvdcajas) {
    liberacursor(vdselcajvdcajas);
    vdselcajvdcajas = NULL;
}
if (vdinscaj != NULL) {
    liberacursor(vdinscaj);
    vdinscaj = NULL;
}
if (vddelcaj != NULL) {
    liberacursor(vddelcaj);
    vddelcaj = NULL;
}
}
static void init_selcajdemayoramenor(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcajas[0].numcol;nc++) dvdcajas[0].c[nc].offset-=(size_t)&svdcajas;
    vdselcajdemayoramenor=abrecursordebug(SELCAJDEMAYORAMENOR,1280);
    definetodo(vdselcajdemayoramenor,svdcajas.rowid,sizeof(svdcajas.rowid),V10CADENA,
                          svdcajas.tipovol,sizeof(svdcajas.tipovol),V10CADENA,
                          svdcajas.tipocaja,sizeof(svdcajas.tipocaja),V10CADENA,
                          svdcajas.tipoemba,sizeof(svdcajas.tipoemba),V10CADENA,
                          svdcajas.descaja,sizeof(svdcajas.descaja),V10CADENA,
                          &svdcajas.largocaja,sizeof(svdcajas.largocaja),V10LONG,
                          &svdcajas.anchocaja,sizeof(svdcajas.anchocaja),V10LONG,
                          &svdcajas.altocaja,sizeof(svdcajas.altocaja),V10LONG,
                          &svdcajas.pesocaja,sizeof(svdcajas.pesocaja),V10LONG,
                          &svdcajas.pesorelleno,sizeof(svdcajas.pesorelleno),V10LONG,
                          &svdcajas.margenpeso,sizeof(svdcajas.margenpeso),V10DOUBLE,
                          &svdcajas.maxllenado,sizeof(svdcajas.maxllenado),V10LONG,
                          &svdcajas.minllenado,sizeof(svdcajas.minllenado),V10LONG,
                          &svdcajas.maxpicos,sizeof(svdcajas.maxpicos),V10LONG,
                          &svdcajas.maxpeso,sizeof(svdcajas.maxpeso),V10LONG,
                          svdcajas.voldinamica,sizeof(svdcajas.voldinamica),V10CADENA,
                          &svdcajas.codcomen,sizeof(svdcajas.codcomen),V10LONG,
                          svdcajas.codopemodif,sizeof(svdcajas.codopemodif),V10CADENA,
                          &svdcajas.fecmodif,sizeof(svdcajas.fecmodif),V10LONG,
                          svdcajas.horamodif,sizeof(svdcajas.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcajdemayoramenor,"TIPOVOL",svdcajas.tipovol,sizeof(svdcajas.tipovol),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_caj);
        init = 1;
    }
}

static void init_selcajvdcajas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcajas[0].numcol;nc++) dvdcajas[0].c[nc].offset-=(size_t)&svdcajas;
    vdselcajvdcajas=abrecursordebug(SELCAJVDCAJAS,1280);
    definetodo(vdselcajvdcajas,svdcajas.rowid,sizeof(svdcajas.rowid),V10CADENA,
                          svdcajas.tipovol,sizeof(svdcajas.tipovol),V10CADENA,
                          svdcajas.tipocaja,sizeof(svdcajas.tipocaja),V10CADENA,
                          svdcajas.tipoemba,sizeof(svdcajas.tipoemba),V10CADENA,
                          svdcajas.descaja,sizeof(svdcajas.descaja),V10CADENA,
                          &svdcajas.largocaja,sizeof(svdcajas.largocaja),V10LONG,
                          &svdcajas.anchocaja,sizeof(svdcajas.anchocaja),V10LONG,
                          &svdcajas.altocaja,sizeof(svdcajas.altocaja),V10LONG,
                          &svdcajas.pesocaja,sizeof(svdcajas.pesocaja),V10LONG,
                          &svdcajas.pesorelleno,sizeof(svdcajas.pesorelleno),V10LONG,
                          &svdcajas.margenpeso,sizeof(svdcajas.margenpeso),V10DOUBLE,
                          &svdcajas.maxllenado,sizeof(svdcajas.maxllenado),V10LONG,
                          &svdcajas.minllenado,sizeof(svdcajas.minllenado),V10LONG,
                          &svdcajas.maxpicos,sizeof(svdcajas.maxpicos),V10LONG,
                          &svdcajas.maxpeso,sizeof(svdcajas.maxpeso),V10LONG,
                          svdcajas.voldinamica,sizeof(svdcajas.voldinamica),V10CADENA,
                          &svdcajas.codcomen,sizeof(svdcajas.codcomen),V10LONG,
                          svdcajas.codopemodif,sizeof(svdcajas.codopemodif),V10CADENA,
                          &svdcajas.fecmodif,sizeof(svdcajas.fecmodif),V10LONG,
                          svdcajas.horamodif,sizeof(svdcajas.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcajvdcajas,"TIPOVOL",svdcajas.tipovol,sizeof(svdcajas.tipovol),V10CADENA,
                          "TIPOCAJA",svdcajas.tipocaja,sizeof(svdcajas.tipocaja),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_caj);
        init = 1;
    }
}

static void init_inscaj(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcajas[0].numcol;nc++) dvdcajas[0].c[nc].offset-=(size_t)&svdcajas;
    vdinscaj=abrecursordebug(INSCAJ,1280);
    bindtodo(vdinscaj,"TIPOVOL",svdcajas.tipovol,sizeof(svdcajas.tipovol),V10CADENA,
                          "TIPOCAJA",svdcajas.tipocaja,sizeof(svdcajas.tipocaja),V10CADENA,
                          "TIPOEMBA",svdcajas.tipoemba,sizeof(svdcajas.tipoemba),V10CADENA,
                          "DESCAJA",svdcajas.descaja,sizeof(svdcajas.descaja),V10CADENA,
                          "LARGOCAJA",&svdcajas.largocaja,sizeof(svdcajas.largocaja),V10LONG,
                          "ANCHOCAJA",&svdcajas.anchocaja,sizeof(svdcajas.anchocaja),V10LONG,
                          "ALTOCAJA",&svdcajas.altocaja,sizeof(svdcajas.altocaja),V10LONG,
                          "PESOCAJA",&svdcajas.pesocaja,sizeof(svdcajas.pesocaja),V10LONG,
                          "PESORELLENO",&svdcajas.pesorelleno,sizeof(svdcajas.pesorelleno),V10LONG,
                          "MARGENPESO",&svdcajas.margenpeso,sizeof(svdcajas.margenpeso),V10DOUBLE,
                          "MAXLLENADO",&svdcajas.maxllenado,sizeof(svdcajas.maxllenado),V10LONG,
                          "MINLLENADO",&svdcajas.minllenado,sizeof(svdcajas.minllenado),V10LONG,
                          "MAXPICOS",&svdcajas.maxpicos,sizeof(svdcajas.maxpicos),V10LONG,
                          "MAXPESO",&svdcajas.maxpeso,sizeof(svdcajas.maxpeso),V10LONG,
                          "VOLDINAMICA",svdcajas.voldinamica,sizeof(svdcajas.voldinamica),V10CADENA,
                          "CODCOMEN",&svdcajas.codcomen,sizeof(svdcajas.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_caj);
        init = 1;
    }
}

static void init_delcaj(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcajas[0].numcol;nc++) dvdcajas[0].c[nc].offset-=(size_t)&svdcajas;
    vddelcaj=abrecursordebug(DELCAJ,1280);
    bindtodo(vddelcaj,"MIROWID",svdcajas.rowid,sizeof(svdcajas.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_caj);
        init = 1;
    }
}

diccionario *CAJdamediccionario(void)
{
     return(&dcaj);
}

int CAJbuscademayoramenor(char *tipovol,vdcajass *caj)
{
  int vdret;
  memset(&svdcajas,0,sizeof(svdcajas));
  strcpy(svdcajas.tipovol,tipovol);
  if (vdselcajdemayoramenor==NULL) init_selcajdemayoramenor();
  vdret=ejefetchcursor(vdselcajdemayoramenor);
  if (vdret==0) {
     *caj=svdcajas;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselcajdemayoramenor. vdret %d. \n",CAJlog(&svdcajas),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int CAJnextdemayoramenor(vdcajass *caj)
{
  int vdret;
  vdret=fetchcursor(vdselcajdemayoramenor);
  if (vdret==0) {
     *caj=svdcajas;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselcajdemayoramenor. vdret %d. \n",CAJlog(&svdcajas),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselcajdemayoramenor);
  return(VD_EERRORACLE);
}

int CAJselvdcajas(char *tipovol,char *tipocaja,vdcajass *caj)
{
  int vdret;
  if (vdselcajvdcajas==NULL) init_selcajvdcajas();
  memset(&svdcajas,0,sizeof(svdcajas));
  strcpy(svdcajas.tipovol,tipovol);
  strcpy(svdcajas.tipocaja,tipocaja);
  vdret=ejefetchcursor(vdselcajvdcajas);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselcajvdcajas. vdret %d. \n",CAJlog(&svdcajas),vdret);
    return(VD_EERRORACLE);
   }
  *caj=svdcajas;
  return(vdret);
}

int CAJinsert(vdcajass *caj,int error)
{
  int vdret;
  if (!vdinscaj) init_inscaj();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",CAJlog(&svdcajas));
  svdcajas=*caj;
  vdret=ejecutacursor(vdinscaj);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinscaj);
     getcurerrornombre(vdinscaj->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CAJdel(vdcajass *caj,int error)
{
  int vdret;
  svdcajas=*caj;
  if (vddelcaj==NULL) init_delcaj();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",CAJlog(&svdcajas));
  vdret=ejecutacursor(vddelcaj);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelcaj);
     getcurerrornombre(vddelcaj->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * CAJlog(vdcajass *caj)
{
    sprintf(msglogCAJ, "VDCAJAS: tipovol %s tipocaja %s ",caj->tipovol,caj->tipocaja);
    return(msglogCAJ);
}

char * CAJdebug(vdcajass *caj)
{
    debugestruct(&dcaj,caj,msgdebugCAJ);
    return(msgdebugCAJ);
}

