// Modulo generado automaticamente a partir de VDTRADCODIGO.DEF
//# M¢dulo : VDTRADCODIGO.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDARTIC
//#                        
//# Autor	 : EAA
//# Revisado por: 
//# Fecha  : 10-10-2007                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=TRC
//
//
//CLAVE=CODARTALT,CODARTALT
//INTERFASE
//UPDATE
//DELETE
//INSERT

#include "vd.h"
#define SELTRCCODARTALT "SELECT VDTRADCODIGO.ROWID,VDTRADCODIGO.CODART,VDTRADCODIGO.CODARTALT, "\
                    " VDTRADCODIGO.SWTACTIVO,VDTRADCODIGO.TIPOBARRAS,VDTRADCODIGO.CODCOMEN, "\
                    " VDTRADCODIGO.CODOPEMODIF,VDTRADCODIGO.FECMODIF,VDTRADCODIGO.HORAMODIF "\
        " FROM VDTRADCODIGO"\
        " WHERE "\
               " VDTRADCODIGO.CODARTALT=:CODARTALT "
static v10cursors *vdseltrccodartalt;

#define SELTRCVDTRADCODIGO "SELECT VDTRADCODIGO.ROWID,VDTRADCODIGO.CODART,VDTRADCODIGO.CODARTALT, "\
                    " VDTRADCODIGO.SWTACTIVO,VDTRADCODIGO.TIPOBARRAS,VDTRADCODIGO.CODCOMEN, "\
                    " VDTRADCODIGO.CODOPEMODIF,VDTRADCODIGO.FECMODIF,VDTRADCODIGO.HORAMODIF "\
        " FROM VDTRADCODIGO"\
        " WHERE "\
               " VDTRADCODIGO.CODART=:CODART "\
               " AND VDTRADCODIGO.CODARTALT=:CODARTALT "
static v10cursors *vdseltrcvdtradcodigo;

#define UPDATRC "UPDATE VDTRADCODIGO SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODART=:CODART , "\
               " CODARTALT=:CODARTALT , "\
               " SWTACTIVO=:SWTACTIVO , "\
               " TIPOBARRAS=:TIPOBARRAS , "\
               " CODCOMEN=:CODCOMEN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdatrcvdtradcodigo;

#define INSTRC "INSERT INTO VDTRADCODIGO (CODART,CODARTALT,SWTACTIVO,TIPOBARRAS,CODCOMEN,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :CODART,:CODARTALT,:SWTACTIVO,:TIPOBARRAS,:CODCOMEN,VDUSER.GETUSER, "\
                    " VD.FECHASYS,VD.HORASYS) "
static v10cursors *vdinstrc;

#define DELTRC "DELETE VDTRADCODIGO WHERE ROWID=:MIROWID "
static v10cursors *vddeltrc;

static vdtradcodigos svdtradcodigo;

static diccols colvdtradcodigo[]={
	{"ROWID",V10CADENA,(size_t)&svdtradcodigo.rowid,sizeof(svdtradcodigo.rowid)},
	{"CODART",V10CADENA,(size_t)&svdtradcodigo.codart,sizeof(svdtradcodigo.codart)},
	{"CODARTALT",V10CADENA,(size_t)&svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt)},
	{"SWTACTIVO",V10CADENA,(size_t)&svdtradcodigo.swtactivo,sizeof(svdtradcodigo.swtactivo)},
	{"TIPOBARRAS",V10CADENA,(size_t)&svdtradcodigo.tipobarras,sizeof(svdtradcodigo.tipobarras)},
	{"CODCOMEN",V10LONG,(size_t)&svdtradcodigo.codcomen,sizeof(svdtradcodigo.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdtradcodigo.codopemodif,sizeof(svdtradcodigo.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdtradcodigo.fecmodif,sizeof(svdtradcodigo.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdtradcodigo.horamodif,sizeof(svdtradcodigo.horamodif)}
	};
static diccionarios dvdtradcodigo[]={
    {colvdtradcodigo,9}
};
diccionario dtrc={dvdtradcodigo,1};

static char msglogTRC[LCADENA];
static char msgdebugTRC[LCADENABIG];
static int init=0;


static void fin_vd_trc(void)
{
if (vdseltrccodartalt) {
    liberacursor(vdseltrccodartalt);
    vdseltrccodartalt = NULL;
}
if (vdseltrcvdtradcodigo) {
    liberacursor(vdseltrcvdtradcodigo);
    vdseltrcvdtradcodigo = NULL;
}
if (vdupdatrcvdtradcodigo) {
    liberacursor(vdupdatrcvdtradcodigo);
    vdupdatrcvdtradcodigo = NULL;
}
if (vdinstrc != NULL) {
    liberacursor(vdinstrc);
    vdinstrc = NULL;
}
if (vddeltrc != NULL) {
    liberacursor(vddeltrc);
    vddeltrc = NULL;
}
}
static void init_seltrccodartalt(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtradcodigo[0].numcol;nc++) dvdtradcodigo[0].c[nc].offset-=(size_t)&svdtradcodigo;
    vdseltrccodartalt=abrecursordebug(SELTRCCODARTALT,1280);
    definetodo(vdseltrccodartalt,svdtradcodigo.rowid,sizeof(svdtradcodigo.rowid),V10CADENA,
                          svdtradcodigo.codart,sizeof(svdtradcodigo.codart),V10CADENA,
                          svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          svdtradcodigo.swtactivo,sizeof(svdtradcodigo.swtactivo),V10CADENA,
                          svdtradcodigo.tipobarras,sizeof(svdtradcodigo.tipobarras),V10CADENA,
                          &svdtradcodigo.codcomen,sizeof(svdtradcodigo.codcomen),V10LONG,
                          svdtradcodigo.codopemodif,sizeof(svdtradcodigo.codopemodif),V10CADENA,
                          &svdtradcodigo.fecmodif,sizeof(svdtradcodigo.fecmodif),V10LONG,
                          svdtradcodigo.horamodif,sizeof(svdtradcodigo.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseltrccodartalt,"CODARTALT",svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_trc);
        init = 1;
    }
}

static void init_seltrcvdtradcodigo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtradcodigo[0].numcol;nc++) dvdtradcodigo[0].c[nc].offset-=(size_t)&svdtradcodigo;
    vdseltrcvdtradcodigo=abrecursordebug(SELTRCVDTRADCODIGO,1280);
    definetodo(vdseltrcvdtradcodigo,svdtradcodigo.rowid,sizeof(svdtradcodigo.rowid),V10CADENA,
                          svdtradcodigo.codart,sizeof(svdtradcodigo.codart),V10CADENA,
                          svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          svdtradcodigo.swtactivo,sizeof(svdtradcodigo.swtactivo),V10CADENA,
                          svdtradcodigo.tipobarras,sizeof(svdtradcodigo.tipobarras),V10CADENA,
                          &svdtradcodigo.codcomen,sizeof(svdtradcodigo.codcomen),V10LONG,
                          svdtradcodigo.codopemodif,sizeof(svdtradcodigo.codopemodif),V10CADENA,
                          &svdtradcodigo.fecmodif,sizeof(svdtradcodigo.fecmodif),V10LONG,
                          svdtradcodigo.horamodif,sizeof(svdtradcodigo.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseltrcvdtradcodigo,"CODART",svdtradcodigo.codart,sizeof(svdtradcodigo.codart),V10CADENA,
                          "CODARTALT",svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_trc);
        init = 1;
    }
}

static void init_updatrcvdtradcodigo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtradcodigo[0].numcol;nc++) dvdtradcodigo[0].c[nc].offset-=(size_t)&svdtradcodigo;
    vdupdatrcvdtradcodigo=abrecursordebug(UPDATRC,1280);
    bindtodo(vdupdatrcvdtradcodigo,"CODART",svdtradcodigo.codart,sizeof(svdtradcodigo.codart),V10CADENA,
                          "CODARTALT",svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          "SWTACTIVO",svdtradcodigo.swtactivo,sizeof(svdtradcodigo.swtactivo),V10CADENA,
                          "TIPOBARRAS",svdtradcodigo.tipobarras,sizeof(svdtradcodigo.tipobarras),V10CADENA,
                          "CODCOMEN",&svdtradcodigo.codcomen,sizeof(svdtradcodigo.codcomen),V10LONG,
                          "MIROWID",svdtradcodigo.rowid,sizeof(svdtradcodigo.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_trc);
        init = 1;
    }
}

static void init_instrc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtradcodigo[0].numcol;nc++) dvdtradcodigo[0].c[nc].offset-=(size_t)&svdtradcodigo;
    vdinstrc=abrecursordebug(INSTRC,1280);
    bindtodo(vdinstrc,"CODART",svdtradcodigo.codart,sizeof(svdtradcodigo.codart),V10CADENA,
                          "CODARTALT",svdtradcodigo.codartalt,sizeof(svdtradcodigo.codartalt),V10CADENA,
                          "SWTACTIVO",svdtradcodigo.swtactivo,sizeof(svdtradcodigo.swtactivo),V10CADENA,
                          "TIPOBARRAS",svdtradcodigo.tipobarras,sizeof(svdtradcodigo.tipobarras),V10CADENA,
                          "CODCOMEN",&svdtradcodigo.codcomen,sizeof(svdtradcodigo.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_trc);
        init = 1;
    }
}

static void init_deltrc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdtradcodigo[0].numcol;nc++) dvdtradcodigo[0].c[nc].offset-=(size_t)&svdtradcodigo;
    vddeltrc=abrecursordebug(DELTRC,1280);
    bindtodo(vddeltrc,"MIROWID",svdtradcodigo.rowid,sizeof(svdtradcodigo.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_trc);
        init = 1;
    }
}

diccionario *TRCdamediccionario(void)
{
     return(&dtrc);
}

int TRCselcodartalt(char *codartalt,vdtradcodigos *trc)
{
  int vdret;
  if (vdseltrccodartalt==NULL) init_seltrccodartalt();
  memset(&svdtradcodigo,0,sizeof(svdtradcodigo));
  strcpy(svdtradcodigo.codartalt,codartalt);
  vdret=ejefetchcursor(vdseltrccodartalt);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseltrccodartalt. vdret %d. \n",TRClog(&svdtradcodigo),vdret);
    return(VD_EERRORACLE);
   }
  *trc=svdtradcodigo;
  return(vdret);
}

int TRCselvdtradcodigo(char *codart,char *codartalt,vdtradcodigos *trc)
{
  int vdret;
  if (vdseltrcvdtradcodigo==NULL) init_seltrcvdtradcodigo();
  memset(&svdtradcodigo,0,sizeof(svdtradcodigo));
  strcpy(svdtradcodigo.codart,codart);
  strcpy(svdtradcodigo.codartalt,codartalt);
  vdret=ejefetchcursor(vdseltrcvdtradcodigo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseltrcvdtradcodigo. vdret %d. \n",TRClog(&svdtradcodigo),vdret);
    return(VD_EERRORACLE);
   }
  *trc=svdtradcodigo;
  return(vdret);
}

int TRCactualizavdtradcodigo(vdtradcodigos *trc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando TRCactualizavdtradcodigo:  %s .  \n",TRClog(&svdtradcodigo));
  if (vdupdatrcvdtradcodigo==NULL) init_updatrcvdtradcodigo();
  svdtradcodigo=*trc;
  vdret=ejecutacursor(vdupdatrcvdtradcodigo);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdatrcvdtradcodigo);
     getcurerrornombre(vdupdatrcvdtradcodigo->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdatrcvdtradcodigo)!=1) return(VD_EERRORACLE);
  return(0);
}

int TRCinsert(vdtradcodigos *trc,int error)
{
  int vdret;
  if (!vdinstrc) init_instrc();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",TRClog(&svdtradcodigo));
  svdtradcodigo=*trc;
  vdret=ejecutacursor(vdinstrc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinstrc);
     getcurerrornombre(vdinstrc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int TRCdel(vdtradcodigos *trc,int error)
{
  int vdret;
  svdtradcodigo=*trc;
  if (vddeltrc==NULL) init_deltrc();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",TRClog(&svdtradcodigo));
  vdret=ejecutacursor(vddeltrc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddeltrc);
     getcurerrornombre(vddeltrc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int TRCinter(vdtradcodigos *trc)
{
  int vdret = 0;
  if (vdseltrcvdtradcodigo==NULL) init_seltrcvdtradcodigo();
  memset(&svdtradcodigo,0,sizeof(svdtradcodigo));
  strcpy(svdtradcodigo.codart,trc->codart);
  strcpy(svdtradcodigo.codartalt,trc->codartalt);
  vdret=ejefetchcursor(vdseltrcvdtradcodigo);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseltrcvdtradcodigo. vdret %d. \n",TRClog(&svdtradcodigo),vdret);
    return(VD_EERRORACLE);
  }

  *trc=svdtradcodigo;
  return(vdret);
}

char * TRClog(vdtradcodigos *trc)
{
    sprintf(msglogTRC, "VDTRADCODIGO: codart %s codartalt %s ",trc->codart,trc->codartalt);
    return(msglogTRC);
}

char * TRCdebug(vdtradcodigos *trc)
{
    debugestruct(&dtrc,trc,msgdebugTRC);
    return(msgdebugTRC);
}

