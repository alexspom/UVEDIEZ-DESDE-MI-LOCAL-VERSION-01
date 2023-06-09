// Modulo generado automaticamente a partir de VDINTERFCARGACAB.DEF
//#***
//# VDINTERFCARGACAB.c - Generaci�n autom�tica del c�digo c para la tabla de los ficheros 
//#                     de las interfases                                                 
//# 
//# Prop�sito: Funciones de acceso a la tabla VDINTERFCARGACAB
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 25-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=ICC
//
//SECUENCIA=VDSECINTERF,CODINTERFASE
//
//CLAVE=CODINTERFASE,TIPOINTERFASE,FORMATO,FICHERO;
//
//CLAVE=FMTOFICH, FORMATO,FICHERO
//
//UPDATE=STATUS,STATUS
//
//INSERT 
//DELETE

#include "vd.h"
#define SELICCCODINTERFASE "SELECT VDINTERFCARGACAB.ROWID,VDINTERFCARGACAB.CODINTERFASE,VDINTERFCARGACAB.TIPOINTERFASE, "\
                    " VDINTERFCARGACAB.FORMATO,VDINTERFCARGACAB.FICHERO,VDINTERFCARGACAB.STATUS, "\
                    " VDINTERFCARGACAB.VDEXTRA,VDINTERFCARGACAB.CODOPEMODIF,VDINTERFCARGACAB.FECMODIF, "\
                    " VDINTERFCARGACAB.HORAMODIF,VDINTERFCARGACAB.CODCOMEN "\
        " FROM VDINTERFCARGACAB"\
        " WHERE "\
               " VDINTERFCARGACAB.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFCARGACAB.FORMATO=:FORMATO "\
               " AND VDINTERFCARGACAB.FICHERO=:FICHERO "
static v10cursors *vdselicccodinterfase;

#define SELICCFMTOFICH "SELECT VDINTERFCARGACAB.ROWID,VDINTERFCARGACAB.CODINTERFASE,VDINTERFCARGACAB.TIPOINTERFASE, "\
                    " VDINTERFCARGACAB.FORMATO,VDINTERFCARGACAB.FICHERO,VDINTERFCARGACAB.STATUS, "\
                    " VDINTERFCARGACAB.VDEXTRA,VDINTERFCARGACAB.CODOPEMODIF,VDINTERFCARGACAB.FECMODIF, "\
                    " VDINTERFCARGACAB.HORAMODIF,VDINTERFCARGACAB.CODCOMEN "\
        " FROM VDINTERFCARGACAB"\
        " WHERE "\
               " VDINTERFCARGACAB.FORMATO=:FORMATO "\
               " AND VDINTERFCARGACAB.FICHERO=:FICHERO "
static v10cursors *vdseliccfmtofich;

#define SELICCVDINTERFCARGACAB "SELECT VDINTERFCARGACAB.ROWID,VDINTERFCARGACAB.CODINTERFASE,VDINTERFCARGACAB.TIPOINTERFASE, "\
                    " VDINTERFCARGACAB.FORMATO,VDINTERFCARGACAB.FICHERO,VDINTERFCARGACAB.STATUS, "\
                    " VDINTERFCARGACAB.VDEXTRA,VDINTERFCARGACAB.CODOPEMODIF,VDINTERFCARGACAB.FECMODIF, "\
                    " VDINTERFCARGACAB.HORAMODIF,VDINTERFCARGACAB.CODCOMEN "\
        " FROM VDINTERFCARGACAB"\
        " WHERE "\
               " VDINTERFCARGACAB.CODINTERFASE=:CODINTERFASE "
static v10cursors *vdseliccvdinterfcargacab;

#define UPDAICCSTATUS "UPDATE VDINTERFCARGACAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaiccstatus;

#define SELVDSECINTERF "SELECT VDSECINTERF.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecinterf;

#define INSICC "INSERT INTO VDINTERFCARGACAB (CODINTERFASE,TIPOINTERFASE,FORMATO,FICHERO,STATUS,VDEXTRA, "\
                    " CODOPEMODIF,FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODINTERFASE,:TIPOINTERFASE,:FORMATO,:FICHERO,:STATUS,:VDEXTRA, "\
                    " VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:CODCOMEN) "
static v10cursors *vdinsicc;

#define DELICC "DELETE VDINTERFCARGACAB WHERE ROWID=:MIROWID "
static v10cursors *vddelicc;

static vdinterfcargacabs svdinterfcargacab;

static diccols colvdinterfcargacab[]={
	{"ROWID",V10CADENA,(size_t)&svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid)},
	{"CODINTERFASE",V10LONG,(size_t)&svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase)},
	{"TIPOINTERFASE",V10CADENA,(size_t)&svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase)},
	{"FORMATO",V10CADENA,(size_t)&svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato)},
	{"FICHERO",V10CADENA,(size_t)&svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero)},
	{"STATUS",V10LONG,(size_t)&svdinterfcargacab.status,sizeof(svdinterfcargacab.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinterfcargacab.vdextra,sizeof(svdinterfcargacab.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinterfcargacab.codopemodif,sizeof(svdinterfcargacab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinterfcargacab.fecmodif,sizeof(svdinterfcargacab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinterfcargacab.horamodif,sizeof(svdinterfcargacab.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinterfcargacab.codcomen,sizeof(svdinterfcargacab.codcomen)}
	};
static diccionarios dvdinterfcargacab[]={
    {colvdinterfcargacab,11}
};
diccionario dicc={dvdinterfcargacab,1};

static char msglogICC[LCADENA];
static char msgdebugICC[LCADENABIG];
static int init=0;


static void fin_vd_icc(void)
{
if (vdselicccodinterfase) {
    liberacursor(vdselicccodinterfase);
    vdselicccodinterfase = NULL;
}
if (vdseliccfmtofich) {
    liberacursor(vdseliccfmtofich);
    vdseliccfmtofich = NULL;
}
if (vdseliccvdinterfcargacab) {
    liberacursor(vdseliccvdinterfcargacab);
    vdseliccvdinterfcargacab = NULL;
}
if (vdupdaiccstatus) {
    liberacursor(vdupdaiccstatus);
    vdupdaiccstatus = NULL;
}
if (vdselvdsecinterf != NULL) {
    liberacursor(vdselvdsecinterf);
    vdselvdsecinterf = NULL;
}
if (vdinsicc != NULL) {
    liberacursor(vdinsicc);
    vdinsicc = NULL;
}
if (vddelicc != NULL) {
    liberacursor(vddelicc);
    vddelicc = NULL;
}
}
static void init_selicccodinterfase(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdselicccodinterfase=abrecursordebug(SELICCCODINTERFASE,1280);
    definetodo(vdselicccodinterfase,svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid),V10CADENA,
                          &svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,
                          svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase),V10CADENA,
                          svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          &svdinterfcargacab.status,sizeof(svdinterfcargacab.status),V10LONG,
                          svdinterfcargacab.vdextra,sizeof(svdinterfcargacab.vdextra),V10CADENA,
                          svdinterfcargacab.codopemodif,sizeof(svdinterfcargacab.codopemodif),V10CADENA,
                          &svdinterfcargacab.fecmodif,sizeof(svdinterfcargacab.fecmodif),V10LONG,
                          svdinterfcargacab.horamodif,sizeof(svdinterfcargacab.horamodif),V10CADENA,
                          &svdinterfcargacab.codcomen,sizeof(svdinterfcargacab.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselicccodinterfase,"TIPOINTERFASE",svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          "FICHERO",svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_seliccfmtofich(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdseliccfmtofich=abrecursordebug(SELICCFMTOFICH,1280);
    definetodo(vdseliccfmtofich,svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid),V10CADENA,
                          &svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,
                          svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase),V10CADENA,
                          svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          &svdinterfcargacab.status,sizeof(svdinterfcargacab.status),V10LONG,
                          svdinterfcargacab.vdextra,sizeof(svdinterfcargacab.vdextra),V10CADENA,
                          svdinterfcargacab.codopemodif,sizeof(svdinterfcargacab.codopemodif),V10CADENA,
                          &svdinterfcargacab.fecmodif,sizeof(svdinterfcargacab.fecmodif),V10LONG,
                          svdinterfcargacab.horamodif,sizeof(svdinterfcargacab.horamodif),V10CADENA,
                          &svdinterfcargacab.codcomen,sizeof(svdinterfcargacab.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliccfmtofich,"FORMATO",svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          "FICHERO",svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_seliccvdinterfcargacab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdseliccvdinterfcargacab=abrecursordebug(SELICCVDINTERFCARGACAB,1280);
    definetodo(vdseliccvdinterfcargacab,svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid),V10CADENA,
                          &svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,
                          svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase),V10CADENA,
                          svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          &svdinterfcargacab.status,sizeof(svdinterfcargacab.status),V10LONG,
                          svdinterfcargacab.vdextra,sizeof(svdinterfcargacab.vdextra),V10CADENA,
                          svdinterfcargacab.codopemodif,sizeof(svdinterfcargacab.codopemodif),V10CADENA,
                          &svdinterfcargacab.fecmodif,sizeof(svdinterfcargacab.fecmodif),V10LONG,
                          svdinterfcargacab.horamodif,sizeof(svdinterfcargacab.horamodif),V10CADENA,
                          &svdinterfcargacab.codcomen,sizeof(svdinterfcargacab.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliccvdinterfcargacab,"CODINTERFASE",&svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_updaiccstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdupdaiccstatus=abrecursordebug(UPDAICCSTATUS,1280);
    bindtodo(vdupdaiccstatus,"STATUS",&svdinterfcargacab.status,sizeof(svdinterfcargacab.status),V10LONG,
                          "MIROWID",svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_selvdsecinterf(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdselvdsecinterf=abrecursordebug(SELVDSECINTERF,1280);
    definetodo(vdselvdsecinterf,&svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_insicc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vdinsicc=abrecursordebug(INSICC,1280);
    bindtodo(vdinsicc,"CODINTERFASE",&svdinterfcargacab.codinterfase,sizeof(svdinterfcargacab.codinterfase),V10LONG,
                          "TIPOINTERFASE",svdinterfcargacab.tipointerfase,sizeof(svdinterfcargacab.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfcargacab.formato,sizeof(svdinterfcargacab.formato),V10CADENA,
                          "FICHERO",svdinterfcargacab.fichero,sizeof(svdinterfcargacab.fichero),V10CADENA,
                          "STATUS",&svdinterfcargacab.status,sizeof(svdinterfcargacab.status),V10LONG,
                          "VDEXTRA",svdinterfcargacab.vdextra,sizeof(svdinterfcargacab.vdextra),V10CADENA,
                          "CODCOMEN",&svdinterfcargacab.codcomen,sizeof(svdinterfcargacab.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

static void init_delicc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargacab[0].numcol;nc++) dvdinterfcargacab[0].c[nc].offset-=(size_t)&svdinterfcargacab;
    vddelicc=abrecursordebug(DELICC,1280);
    bindtodo(vddelicc,"MIROWID",svdinterfcargacab.rowid,sizeof(svdinterfcargacab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icc);
        init = 1;
    }
}

diccionario *ICCdamediccionario(void)
{
     return(&dicc);
}

int ICCselcodinterfase(char *tipointerfase,char *formato,char *fichero,vdinterfcargacabs *icc)
{
  int vdret;
  if (vdselicccodinterfase==NULL) init_selicccodinterfase();
  memset(&svdinterfcargacab,0,sizeof(svdinterfcargacab));
  strcpy(svdinterfcargacab.tipointerfase,tipointerfase);
  strcpy(svdinterfcargacab.formato,formato);
  strcpy(svdinterfcargacab.fichero,fichero);
  vdret=ejefetchcursor(vdselicccodinterfase);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselicccodinterfase. vdret %d. \n",ICClog(&svdinterfcargacab),vdret);
    return(VD_EERRORACLE);
   }
  *icc=svdinterfcargacab;
  return(vdret);
}

int ICCselfmtofich(char *formato,char *fichero,vdinterfcargacabs *icc)
{
  int vdret;
  if (vdseliccfmtofich==NULL) init_seliccfmtofich();
  memset(&svdinterfcargacab,0,sizeof(svdinterfcargacab));
  strcpy(svdinterfcargacab.formato,formato);
  strcpy(svdinterfcargacab.fichero,fichero);
  vdret=ejefetchcursor(vdseliccfmtofich);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseliccfmtofich. vdret %d. \n",ICClog(&svdinterfcargacab),vdret);
    return(VD_EERRORACLE);
   }
  *icc=svdinterfcargacab;
  return(vdret);
}

int ICCselvdinterfcargacab(long codinterfase,vdinterfcargacabs *icc)
{
  int vdret;
  if (vdseliccvdinterfcargacab==NULL) init_seliccvdinterfcargacab();
  memset(&svdinterfcargacab,0,sizeof(svdinterfcargacab));
  svdinterfcargacab.codinterfase=codinterfase;
  vdret=ejefetchcursor(vdseliccvdinterfcargacab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseliccvdinterfcargacab. vdret %d. \n",ICClog(&svdinterfcargacab),vdret);
    return(VD_EERRORACLE);
   }
  *icc=svdinterfcargacab;
  return(vdret);
}

int ICCactualizastatus(vdinterfcargacabs *icc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ICCactualizastatus:  %s .  \n",ICClog(&svdinterfcargacab));
  if (vdupdaiccstatus==NULL) init_updaiccstatus();
  svdinterfcargacab=*icc;
  vdret=ejecutacursor(vdupdaiccstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaiccstatus);
     getcurerrornombre(vdupdaiccstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaiccstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int ICCselvdsecinterf(long *donde)
{
  int vdret;
  if (!vdselvdsecinterf) init_selvdsecinterf();
  vdret=ejefetchcursor(vdselvdsecinterf);
  if (!vdret) {
     *donde=svdinterfcargacab.codinterfase;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int ICCinsert(vdinterfcargacabs *icc,int error)
{
  int vdret;
  if (!vdinsicc) init_insicc();
  if (!icc->codinterfase) {
     if ((vdret=ICCselvdsecinterf(&(icc->codinterfase)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",ICClog(&svdinterfcargacab));
  svdinterfcargacab=*icc;
  vdret=ejecutacursor(vdinsicc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsicc);
     getcurerrornombre(vdinsicc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ICCdel(vdinterfcargacabs *icc,int error)
{
  int vdret;
  svdinterfcargacab=*icc;
  if (vddelicc==NULL) init_delicc();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",ICClog(&svdinterfcargacab));
  vdret=ejecutacursor(vddelicc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelicc);
     getcurerrornombre(vddelicc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * ICClog(vdinterfcargacabs *icc)
{
    sprintf(msglogICC, "VDINTERFCARGACAB: codinterfase %ld ",icc->codinterfase);
    return(msglogICC);
}

char * ICCdebug(vdinterfcargacabs *icc)
{
    debugestruct(&dicc,icc,msgdebugICC);
    return(msgdebugICC);
}

