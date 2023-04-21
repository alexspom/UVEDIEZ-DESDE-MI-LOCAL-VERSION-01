// Modulo generado automaticamente a partir de VDORDRECCAB.DEF
//# M¢dulo : VDORDRECCAB.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDORDRECCAB
//#                        
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 06-05-2008
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=ORC
//
//INTERFASE
//UPDATE
//DELETE
//INSERT

#include "vd.h"
#define SELORCVDORDRECCAB "SELECT VDORDRECCAB.ROWID,VDORDRECCAB.CODORDREC,VDORDRECCAB.CODDIV, "\
                    " VDORDRECCAB.TIPORDREC,VDORDRECCAB.CLAVEEXT,VDORDRECCAB.CODPROVE, "\
                    " VDORDRECCAB.DESPROVE,VDORDRECCAB.FECORDREC,VDORDRECCAB.FECCREADO, "\
                    " VDORDRECCAB.HORACREADO,VDORDRECCAB.STATUS,VDORDRECCAB.VDEXTRA, "\
                    " VDORDRECCAB.CODCOMEN,VDORDRECCAB.CODOPEMODIF,VDORDRECCAB.FECMODIF, "\
                    " VDORDRECCAB.HORAMODIF,VDORDRECCAB.FECFIN,VDORDRECCAB.HORAFIN, "\
                    " VDORDRECCAB.FECINI,VDORDRECCAB.HORAINI "\
        " FROM VDORDRECCAB"\
        " WHERE "\
               " VDORDRECCAB.CODORDREC=:CODORDREC "\
               " AND VDORDRECCAB.CODDIV=:CODDIV "
static v10cursors *vdselorcvdordreccab;

#define UPDAORC "UPDATE VDORDRECCAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODORDREC=:CODORDREC , "\
               " CODDIV=:CODDIV , "\
               " TIPORDREC=:TIPORDREC , "\
               " CLAVEEXT=:CLAVEEXT , "\
               " CODPROVE=:CODPROVE , "\
               " DESPROVE=:DESPROVE , "\
               " FECORDREC=:FECORDREC , "\
               " FECCREADO=:FECCREADO , "\
               " HORACREADO=:HORACREADO , "\
               " STATUS=:STATUS , "\
               " VDEXTRA=:VDEXTRA , "\
               " CODCOMEN=:CODCOMEN , "\
               " FECFIN=:FECFIN , "\
               " HORAFIN=:HORAFIN , "\
               " FECINI=:FECINI , "\
               " HORAINI=:HORAINI  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaorcvdordreccab;

#define INSORC "INSERT INTO VDORDRECCAB (CODORDREC,CODDIV,TIPORDREC,CLAVEEXT,CODPROVE,DESPROVE, "\
                    " FECORDREC,FECCREADO,HORACREADO,STATUS,VDEXTRA,CODCOMEN,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF,FECFIN,HORAFIN,FECINI,HORAINI "\
       " ) VALUES ( "\
                    " :CODORDREC,:CODDIV,:TIPORDREC,:CLAVEEXT,:CODPROVE,:DESPROVE, "\
                    " :FECORDREC,:FECCREADO,:HORACREADO,:STATUS,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER, "\
                    " VD.FECHASYS,VD.HORASYS,:FECFIN,:HORAFIN,:FECINI,:HORAINI) "
static v10cursors *vdinsorc;

#define DELORC "DELETE VDORDRECCAB WHERE ROWID=:MIROWID "
static v10cursors *vddelorc;

static vdordreccabs svdordreccab;

static diccols colvdordreccab[]={
	{"ROWID",V10CADENA,(size_t)&svdordreccab.rowid,sizeof(svdordreccab.rowid)},
	{"CODORDREC",V10CADENA,(size_t)&svdordreccab.codordrec,sizeof(svdordreccab.codordrec)},
	{"CODDIV",V10CADENA,(size_t)&svdordreccab.coddiv,sizeof(svdordreccab.coddiv)},
	{"TIPORDREC",V10CADENA,(size_t)&svdordreccab.tipordrec,sizeof(svdordreccab.tipordrec)},
	{"CLAVEEXT",V10CADENA,(size_t)&svdordreccab.claveext,sizeof(svdordreccab.claveext)},
	{"CODPROVE",V10CADENA,(size_t)&svdordreccab.codprove,sizeof(svdordreccab.codprove)},
	{"DESPROVE",V10CADENA,(size_t)&svdordreccab.desprove,sizeof(svdordreccab.desprove)},
	{"FECORDREC",V10LONG,(size_t)&svdordreccab.fecordrec,sizeof(svdordreccab.fecordrec)},
	{"FECCREADO",V10LONG,(size_t)&svdordreccab.feccreado,sizeof(svdordreccab.feccreado)},
	{"HORACREADO",V10CADENA,(size_t)&svdordreccab.horacreado,sizeof(svdordreccab.horacreado)},
	{"STATUS",V10LONG,(size_t)&svdordreccab.status,sizeof(svdordreccab.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdordreccab.vdextra,sizeof(svdordreccab.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdordreccab.codcomen,sizeof(svdordreccab.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdordreccab.codopemodif,sizeof(svdordreccab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdordreccab.fecmodif,sizeof(svdordreccab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdordreccab.horamodif,sizeof(svdordreccab.horamodif)},
	{"FECFIN",V10LONG,(size_t)&svdordreccab.fecfin,sizeof(svdordreccab.fecfin)},
	{"HORAFIN",V10CADENA,(size_t)&svdordreccab.horafin,sizeof(svdordreccab.horafin)},
	{"FECINI",V10LONG,(size_t)&svdordreccab.fecini,sizeof(svdordreccab.fecini)},
	{"HORAINI",V10CADENA,(size_t)&svdordreccab.horaini,sizeof(svdordreccab.horaini)}
	};
static diccionarios dvdordreccab[]={
    {colvdordreccab,20}
};
diccionario dorc={dvdordreccab,1};

static char msglogORC[LCADENA];
static char msgdebugORC[LCADENABIG];
static int init=0;


static void fin_vd_orc(void)
{
if (vdselorcvdordreccab) {
    liberacursor(vdselorcvdordreccab);
    vdselorcvdordreccab = NULL;
}
if (vdupdaorcvdordreccab) {
    liberacursor(vdupdaorcvdordreccab);
    vdupdaorcvdordreccab = NULL;
}
if (vdinsorc != NULL) {
    liberacursor(vdinsorc);
    vdinsorc = NULL;
}
if (vddelorc != NULL) {
    liberacursor(vddelorc);
    vddelorc = NULL;
}
}
static void init_selorcvdordreccab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdordreccab[0].numcol;nc++) dvdordreccab[0].c[nc].offset-=(size_t)&svdordreccab;
    vdselorcvdordreccab=abrecursordebug(SELORCVDORDRECCAB,1280);
    definetodo(vdselorcvdordreccab,svdordreccab.rowid,sizeof(svdordreccab.rowid),V10CADENA,
                          svdordreccab.codordrec,sizeof(svdordreccab.codordrec),V10CADENA,
                          svdordreccab.coddiv,sizeof(svdordreccab.coddiv),V10CADENA,
                          svdordreccab.tipordrec,sizeof(svdordreccab.tipordrec),V10CADENA,
                          svdordreccab.claveext,sizeof(svdordreccab.claveext),V10CADENA,
                          svdordreccab.codprove,sizeof(svdordreccab.codprove),V10CADENA,
                          svdordreccab.desprove,sizeof(svdordreccab.desprove),V10CADENA,
                          &svdordreccab.fecordrec,sizeof(svdordreccab.fecordrec),V10LONG,
                          &svdordreccab.feccreado,sizeof(svdordreccab.feccreado),V10LONG,
                          svdordreccab.horacreado,sizeof(svdordreccab.horacreado),V10CADENA,
                          &svdordreccab.status,sizeof(svdordreccab.status),V10LONG,
                          svdordreccab.vdextra,sizeof(svdordreccab.vdextra),V10CADENA,
                          &svdordreccab.codcomen,sizeof(svdordreccab.codcomen),V10LONG,
                          svdordreccab.codopemodif,sizeof(svdordreccab.codopemodif),V10CADENA,
                          &svdordreccab.fecmodif,sizeof(svdordreccab.fecmodif),V10LONG,
                          svdordreccab.horamodif,sizeof(svdordreccab.horamodif),V10CADENA,
                          &svdordreccab.fecfin,sizeof(svdordreccab.fecfin),V10LONG,
                          svdordreccab.horafin,sizeof(svdordreccab.horafin),V10CADENA,
                          &svdordreccab.fecini,sizeof(svdordreccab.fecini),V10LONG,
                          svdordreccab.horaini,sizeof(svdordreccab.horaini),V10CADENA,
                          NULL);
    bindtodo(vdselorcvdordreccab,"CODORDREC",svdordreccab.codordrec,sizeof(svdordreccab.codordrec),V10CADENA,
                          "CODDIV",svdordreccab.coddiv,sizeof(svdordreccab.coddiv),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_orc);
        init = 1;
    }
}

static void init_updaorcvdordreccab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdordreccab[0].numcol;nc++) dvdordreccab[0].c[nc].offset-=(size_t)&svdordreccab;
    vdupdaorcvdordreccab=abrecursordebug(UPDAORC,1280);
    bindtodo(vdupdaorcvdordreccab,"CODORDREC",svdordreccab.codordrec,sizeof(svdordreccab.codordrec),V10CADENA,
                          "CODDIV",svdordreccab.coddiv,sizeof(svdordreccab.coddiv),V10CADENA,
                          "TIPORDREC",svdordreccab.tipordrec,sizeof(svdordreccab.tipordrec),V10CADENA,
                          "CLAVEEXT",svdordreccab.claveext,sizeof(svdordreccab.claveext),V10CADENA,
                          "CODPROVE",svdordreccab.codprove,sizeof(svdordreccab.codprove),V10CADENA,
                          "DESPROVE",svdordreccab.desprove,sizeof(svdordreccab.desprove),V10CADENA,
                          "FECORDREC",&svdordreccab.fecordrec,sizeof(svdordreccab.fecordrec),V10LONG,
                          "FECCREADO",&svdordreccab.feccreado,sizeof(svdordreccab.feccreado),V10LONG,
                          "HORACREADO",svdordreccab.horacreado,sizeof(svdordreccab.horacreado),V10CADENA,
                          "STATUS",&svdordreccab.status,sizeof(svdordreccab.status),V10LONG,
                          "VDEXTRA",svdordreccab.vdextra,sizeof(svdordreccab.vdextra),V10CADENA,
                          "CODCOMEN",&svdordreccab.codcomen,sizeof(svdordreccab.codcomen),V10LONG,
                          "FECFIN",&svdordreccab.fecfin,sizeof(svdordreccab.fecfin),V10LONG,
                          "HORAFIN",svdordreccab.horafin,sizeof(svdordreccab.horafin),V10CADENA,
                          "FECINI",&svdordreccab.fecini,sizeof(svdordreccab.fecini),V10LONG,
                          "HORAINI",svdordreccab.horaini,sizeof(svdordreccab.horaini),V10CADENA,
                          "MIROWID",svdordreccab.rowid,sizeof(svdordreccab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_orc);
        init = 1;
    }
}

static void init_insorc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdordreccab[0].numcol;nc++) dvdordreccab[0].c[nc].offset-=(size_t)&svdordreccab;
    vdinsorc=abrecursordebug(INSORC,1280);
    bindtodo(vdinsorc,"CODORDREC",svdordreccab.codordrec,sizeof(svdordreccab.codordrec),V10CADENA,
                          "CODDIV",svdordreccab.coddiv,sizeof(svdordreccab.coddiv),V10CADENA,
                          "TIPORDREC",svdordreccab.tipordrec,sizeof(svdordreccab.tipordrec),V10CADENA,
                          "CLAVEEXT",svdordreccab.claveext,sizeof(svdordreccab.claveext),V10CADENA,
                          "CODPROVE",svdordreccab.codprove,sizeof(svdordreccab.codprove),V10CADENA,
                          "DESPROVE",svdordreccab.desprove,sizeof(svdordreccab.desprove),V10CADENA,
                          "FECORDREC",&svdordreccab.fecordrec,sizeof(svdordreccab.fecordrec),V10LONG,
                          "FECCREADO",&svdordreccab.feccreado,sizeof(svdordreccab.feccreado),V10LONG,
                          "HORACREADO",svdordreccab.horacreado,sizeof(svdordreccab.horacreado),V10CADENA,
                          "STATUS",&svdordreccab.status,sizeof(svdordreccab.status),V10LONG,
                          "VDEXTRA",svdordreccab.vdextra,sizeof(svdordreccab.vdextra),V10CADENA,
                          "CODCOMEN",&svdordreccab.codcomen,sizeof(svdordreccab.codcomen),V10LONG,
                          "FECFIN",&svdordreccab.fecfin,sizeof(svdordreccab.fecfin),V10LONG,
                          "HORAFIN",svdordreccab.horafin,sizeof(svdordreccab.horafin),V10CADENA,
                          "FECINI",&svdordreccab.fecini,sizeof(svdordreccab.fecini),V10LONG,
                          "HORAINI",svdordreccab.horaini,sizeof(svdordreccab.horaini),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_orc);
        init = 1;
    }
}

static void init_delorc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdordreccab[0].numcol;nc++) dvdordreccab[0].c[nc].offset-=(size_t)&svdordreccab;
    vddelorc=abrecursordebug(DELORC,1280);
    bindtodo(vddelorc,"MIROWID",svdordreccab.rowid,sizeof(svdordreccab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_orc);
        init = 1;
    }
}

diccionario *ORCdamediccionario(void)
{
     return(&dorc);
}

int ORCselvdordreccab(char *codordrec,char *coddiv,vdordreccabs *orc)
{
  int vdret;
  if (vdselorcvdordreccab==NULL) init_selorcvdordreccab();
  memset(&svdordreccab,0,sizeof(svdordreccab));
  strcpy(svdordreccab.codordrec,codordrec);
  strcpy(svdordreccab.coddiv,coddiv);
  vdret=ejefetchcursor(vdselorcvdordreccab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselorcvdordreccab. vdret %d. \n",ORClog(&svdordreccab),vdret);
    return(VD_EERRORACLE);
   }
  *orc=svdordreccab;
  return(vdret);
}

int ORCactualizavdordreccab(vdordreccabs *orc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ORCactualizavdordreccab:  %s .  \n",ORClog(&svdordreccab));
  if (vdupdaorcvdordreccab==NULL) init_updaorcvdordreccab();
  svdordreccab=*orc;
  vdret=ejecutacursor(vdupdaorcvdordreccab);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaorcvdordreccab);
     getcurerrornombre(vdupdaorcvdordreccab->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaorcvdordreccab)!=1) return(VD_EERRORACLE);
  return(0);
}

int ORCinsert(vdordreccabs *orc,int error)
{
  int vdret;
  if (!vdinsorc) init_insorc();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",ORClog(&svdordreccab));
  svdordreccab=*orc;
  vdret=ejecutacursor(vdinsorc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsorc);
     getcurerrornombre(vdinsorc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ORCdel(vdordreccabs *orc,int error)
{
  int vdret;
  svdordreccab=*orc;
  if (vddelorc==NULL) init_delorc();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",ORClog(&svdordreccab));
  vdret=ejecutacursor(vddelorc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelorc);
     getcurerrornombre(vddelorc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ORCinter(vdordreccabs *orc)
{
  int vdret = 0;
  if (vdselorcvdordreccab==NULL) init_selorcvdordreccab();
  memset(&svdordreccab,0,sizeof(svdordreccab));
  strcpy(svdordreccab.codordrec,orc->codordrec);
  strcpy(svdordreccab.coddiv,orc->coddiv);
  vdret=ejefetchcursor(vdselorcvdordreccab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselorcvdordreccab. vdret %d. \n",ORClog(&svdordreccab),vdret);
    return(VD_EERRORACLE);
  }

  *orc=svdordreccab;
  return(vdret);
}

char * ORClog(vdordreccabs *orc)
{
    sprintf(msglogORC, "VDORDRECCAB: codordrec %s coddiv %s ",orc->codordrec,orc->coddiv);
    return(msglogORC);
}

char * ORCdebug(vdordreccabs *orc)
{
    debugestruct(&dorc,orc,msgdebugORC);
    return(msgdebugORC);
}

