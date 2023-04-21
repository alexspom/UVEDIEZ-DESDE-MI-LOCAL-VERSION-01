// Modulo generado automaticamente a partir de VDCLASEARTIC.DEF
//# M�dulo : VDCLASEARTIC.DEF                                                        
//# Funci�n: Generaci�n automatica de rutinas C tabla VDCLASEARTIC
//#                        
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 06-03-2008                                              
//#********************************************************************************
//# Hist�rico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=CLA;
//CLAVE=CODARTCLASIF,CODART,CODCLASIF
//
//INTERFASE
//UPDATE
//INSERT
//DELETE

#include "vd.h"
#define SELCLACODARTCLASIF "SELECT VDCLASEARTIC.ROWID,VDCLASEARTIC.CODCLASIF,VDCLASEARTIC.CODCLASE, "\
                    " VDCLASEARTIC.CODART,VDCLASEARTIC.VDEXTRA,VDCLASEARTIC.CODOPEMODIF, "\
                    " VDCLASEARTIC.FECMODIF,VDCLASEARTIC.HORAMODIF,VDCLASEARTIC.CODCOMEN "\
        " FROM VDCLASEARTIC"\
        " WHERE "\
               " VDCLASEARTIC.CODART=:CODART "\
               " AND VDCLASEARTIC.CODCLASIF=:CODCLASIF "
static v10cursors *vdselclacodartclasif;

#define SELCLAVDCLASEARTIC "SELECT VDCLASEARTIC.ROWID,VDCLASEARTIC.CODCLASIF,VDCLASEARTIC.CODCLASE, "\
                    " VDCLASEARTIC.CODART,VDCLASEARTIC.VDEXTRA,VDCLASEARTIC.CODOPEMODIF, "\
                    " VDCLASEARTIC.FECMODIF,VDCLASEARTIC.HORAMODIF,VDCLASEARTIC.CODCOMEN "\
        " FROM VDCLASEARTIC"
static v10cursors *vdselclavdclaseartic;

#define UPDACLA "UPDATE VDCLASEARTIC SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODCLASIF=:CODCLASIF , "\
               " CODCLASE=:CODCLASE , "\
               " CODART=:CODART , "\
               " VDEXTRA=:VDEXTRA , "\
               " CODCOMEN=:CODCOMEN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaclavdclaseartic;

#define INSCLA "INSERT INTO VDCLASEARTIC (CODCLASIF,CODCLASE,CODART,VDEXTRA,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODCLASIF,:CODCLASE,:CODART,:VDEXTRA,VDUSER.GETUSER,VD.FECHASYS, "\
                    " VD.HORASYS,:CODCOMEN) "
static v10cursors *vdinscla;

#define DELCLA "DELETE VDCLASEARTIC WHERE ROWID=:MIROWID "
static v10cursors *vddelcla;

static vdclaseartics svdclaseartic;

static diccols colvdclaseartic[]={
	{"ROWID",V10CADENA,(size_t)&svdclaseartic.rowid,sizeof(svdclaseartic.rowid)},
	{"CODCLASIF",V10CADENA,(size_t)&svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif)},
	{"CODCLASE",V10CADENA,(size_t)&svdclaseartic.codclase,sizeof(svdclaseartic.codclase)},
	{"CODART",V10CADENA,(size_t)&svdclaseartic.codart,sizeof(svdclaseartic.codart)},
	{"VDEXTRA",V10CADENA,(size_t)&svdclaseartic.vdextra,sizeof(svdclaseartic.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdclaseartic.codopemodif,sizeof(svdclaseartic.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdclaseartic.fecmodif,sizeof(svdclaseartic.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdclaseartic.horamodif,sizeof(svdclaseartic.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdclaseartic.codcomen,sizeof(svdclaseartic.codcomen)}
	};
static diccionarios dvdclaseartic[]={
    {colvdclaseartic,9}
};
diccionario dcla={dvdclaseartic,1};

static char msglogCLA[LCADENA];
static char msgdebugCLA[LCADENABIG];
static int init=0;


static void fin_vd_cla(void)
{
if (vdselclacodartclasif) {
    liberacursor(vdselclacodartclasif);
    vdselclacodartclasif = NULL;
}
if (vdselclavdclaseartic) {
    liberacursor(vdselclavdclaseartic);
    vdselclavdclaseartic = NULL;
}
if (vdupdaclavdclaseartic) {
    liberacursor(vdupdaclavdclaseartic);
    vdupdaclavdclaseartic = NULL;
}
if (vdinscla != NULL) {
    liberacursor(vdinscla);
    vdinscla = NULL;
}
if (vddelcla != NULL) {
    liberacursor(vddelcla);
    vddelcla = NULL;
}
}
static void init_selclacodartclasif(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclaseartic[0].numcol;nc++) dvdclaseartic[0].c[nc].offset-=(size_t)&svdclaseartic;
    vdselclacodartclasif=abrecursordebug(SELCLACODARTCLASIF,1280);
    definetodo(vdselclacodartclasif,svdclaseartic.rowid,sizeof(svdclaseartic.rowid),V10CADENA,
                          svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif),V10CADENA,
                          svdclaseartic.codclase,sizeof(svdclaseartic.codclase),V10CADENA,
                          svdclaseartic.codart,sizeof(svdclaseartic.codart),V10CADENA,
                          svdclaseartic.vdextra,sizeof(svdclaseartic.vdextra),V10CADENA,
                          svdclaseartic.codopemodif,sizeof(svdclaseartic.codopemodif),V10CADENA,
                          &svdclaseartic.fecmodif,sizeof(svdclaseartic.fecmodif),V10LONG,
                          svdclaseartic.horamodif,sizeof(svdclaseartic.horamodif),V10CADENA,
                          &svdclaseartic.codcomen,sizeof(svdclaseartic.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselclacodartclasif,"CODART",svdclaseartic.codart,sizeof(svdclaseartic.codart),V10CADENA,
                          "CODCLASIF",svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cla);
        init = 1;
    }
}

static void init_selclavdclaseartic(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclaseartic[0].numcol;nc++) dvdclaseartic[0].c[nc].offset-=(size_t)&svdclaseartic;
    vdselclavdclaseartic=abrecursordebug(SELCLAVDCLASEARTIC,1280);
    definetodo(vdselclavdclaseartic,svdclaseartic.rowid,sizeof(svdclaseartic.rowid),V10CADENA,
                          svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif),V10CADENA,
                          svdclaseartic.codclase,sizeof(svdclaseartic.codclase),V10CADENA,
                          svdclaseartic.codart,sizeof(svdclaseartic.codart),V10CADENA,
                          svdclaseartic.vdextra,sizeof(svdclaseartic.vdextra),V10CADENA,
                          svdclaseartic.codopemodif,sizeof(svdclaseartic.codopemodif),V10CADENA,
                          &svdclaseartic.fecmodif,sizeof(svdclaseartic.fecmodif),V10LONG,
                          svdclaseartic.horamodif,sizeof(svdclaseartic.horamodif),V10CADENA,
                          &svdclaseartic.codcomen,sizeof(svdclaseartic.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselclavdclaseartic,NULL);
    if (init == 0) {
        atexit(fin_vd_cla);
        init = 1;
    }
}

static void init_updaclavdclaseartic(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclaseartic[0].numcol;nc++) dvdclaseartic[0].c[nc].offset-=(size_t)&svdclaseartic;
    vdupdaclavdclaseartic=abrecursordebug(UPDACLA,1280);
    bindtodo(vdupdaclavdclaseartic,"CODCLASIF",svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif),V10CADENA,
                          "CODCLASE",svdclaseartic.codclase,sizeof(svdclaseartic.codclase),V10CADENA,
                          "CODART",svdclaseartic.codart,sizeof(svdclaseartic.codart),V10CADENA,
                          "VDEXTRA",svdclaseartic.vdextra,sizeof(svdclaseartic.vdextra),V10CADENA,
                          "CODCOMEN",&svdclaseartic.codcomen,sizeof(svdclaseartic.codcomen),V10LONG,
                          "MIROWID",svdclaseartic.rowid,sizeof(svdclaseartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cla);
        init = 1;
    }
}

static void init_inscla(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclaseartic[0].numcol;nc++) dvdclaseartic[0].c[nc].offset-=(size_t)&svdclaseartic;
    vdinscla=abrecursordebug(INSCLA,1280);
    bindtodo(vdinscla,"CODCLASIF",svdclaseartic.codclasif,sizeof(svdclaseartic.codclasif),V10CADENA,
                          "CODCLASE",svdclaseartic.codclase,sizeof(svdclaseartic.codclase),V10CADENA,
                          "CODART",svdclaseartic.codart,sizeof(svdclaseartic.codart),V10CADENA,
                          "VDEXTRA",svdclaseartic.vdextra,sizeof(svdclaseartic.vdextra),V10CADENA,
                          "CODCOMEN",&svdclaseartic.codcomen,sizeof(svdclaseartic.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cla);
        init = 1;
    }
}

static void init_delcla(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdclaseartic[0].numcol;nc++) dvdclaseartic[0].c[nc].offset-=(size_t)&svdclaseartic;
    vddelcla=abrecursordebug(DELCLA,1280);
    bindtodo(vddelcla,"MIROWID",svdclaseartic.rowid,sizeof(svdclaseartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cla);
        init = 1;
    }
}

diccionario *CLAdamediccionario(void)
{
     return(&dcla);
}

int CLAselcodartclasif(char *codart,char *codclasif,vdclaseartics *cla)
{
  int vdret;
  if (vdselclacodartclasif==NULL) init_selclacodartclasif();
  memset(&svdclaseartic,0,sizeof(svdclaseartic));
  strcpy(svdclaseartic.codart,codart);
  strcpy(svdclaseartic.codclasif,codclasif);
  vdret=ejefetchcursor(vdselclacodartclasif);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclacodartclasif. vdret %d. \n",CLAlog(&svdclaseartic),vdret);
    return(VD_EERRORACLE);
   }
  *cla=svdclaseartic;
  return(vdret);
}

int CLAselvdclaseartic(vdclaseartics *cla)
{
  int vdret;
  if (vdselclavdclaseartic==NULL) init_selclavdclaseartic();
  memset(&svdclaseartic,0,sizeof(svdclaseartic));
  vdret=ejefetchcursor(vdselclavdclaseartic);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclavdclaseartic. vdret %d. \n",CLAlog(&svdclaseartic),vdret);
    return(VD_EERRORACLE);
   }
  *cla=svdclaseartic;
  return(vdret);
}

int CLAactualizavdclaseartic(vdclaseartics *cla,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando CLAactualizavdclaseartic:  %s .  \n",CLAlog(&svdclaseartic));
  if (vdupdaclavdclaseartic==NULL) init_updaclavdclaseartic();
  svdclaseartic=*cla;
  vdret=ejecutacursor(vdupdaclavdclaseartic);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaclavdclaseartic);
     getcurerrornombre(vdupdaclavdclaseartic->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaclavdclaseartic)!=1) return(VD_EERRORACLE);
  return(0);
}

int CLAinsert(vdclaseartics *cla,int error)
{
  int vdret;
  if (!vdinscla) init_inscla();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",CLAlog(&svdclaseartic));
  svdclaseartic=*cla;
  vdret=ejecutacursor(vdinscla);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinscla);
     getcurerrornombre(vdinscla->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CLAdel(vdclaseartics *cla,int error)
{
  int vdret;
  svdclaseartic=*cla;
  if (vddelcla==NULL) init_delcla();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",CLAlog(&svdclaseartic));
  vdret=ejecutacursor(vddelcla);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelcla);
     getcurerrornombre(vddelcla->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CLAinter(vdclaseartics *cla)
{
  int vdret = 0;
  if (vdselclavdclaseartic==NULL) init_selclavdclaseartic();
  memset(&svdclaseartic,0,sizeof(svdclaseartic));
  vdret=ejefetchcursor(vdselclavdclaseartic);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselclavdclaseartic. vdret %d. \n",CLAlog(&svdclaseartic),vdret);
    return(VD_EERRORACLE);
  }

  *cla=svdclaseartic;
  return(vdret);
}

char * CLAlog(vdclaseartics *cla)
{
    sprintf(msglogCLA, "VDCLASEARTIC: ");
    return(msglogCLA);
}

char * CLAdebug(vdclaseartics *cla)
{
    debugestruct(&dcla,cla,msgdebugCLA);
    return(msgdebugCLA);
}

