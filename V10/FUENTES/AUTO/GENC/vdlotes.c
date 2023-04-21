// Modulo generado automaticamente a partir de VDLOTES.DEF
//# M¢dulo : VDLOTES.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDLOTES
//#                        
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 05-05-2008
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=LOT
//EXTRA=STATUS,V10LONG
//
//
//CLAVE=CODLOTARTORDR, CODLOT,CODART,WHERE= (CODART, CODLOT) NOT IN (SELECT CODART,CODLOT
//                                                                 FROM VDORDRECLIN
//                                                                WHERE STATUS = :STATUS);
//
//INTERFASE
//UPDATE
//DELETE
//INSERT

#include "vd.h"
#define SELLOTCODLOTARTORDR "SELECT VDLOTES.ROWID,VDLOTES.CODART,VDLOTES.CODLOT, "\
                    " VDLOTES.CODLOTPROV,VDLOTES.CADUCI,VDLOTES.RETEST, "\
                    " VDLOTES.BLOQLOTE,VDLOTES.POTENCIA,VDLOTES.SWTPRECIO, "\
                    " VDLOTES.MUESTREADO,VDLOTES.CODCOMEN,VDLOTES.VDEXTRA, "\
                    " VDLOTES.CODOPEMODIF,VDLOTES.FECMODIF,VDLOTES.HORAMODIF "\
        " FROM VDLOTES"\
        " WHERE "\
               " VDLOTES.CODLOT=:CODLOT "\
               " AND VDLOTES.CODART=:CODART "\
              "  AND  (CODART, CODLOT) NOT IN (SELECT CODART,CODLOT FROM VDORDRECLIN WHERE STATUS = :STATUS) "
static v10cursors *vdsellotcodlotartordr;

#define SELLOTVDLOTES "SELECT VDLOTES.ROWID,VDLOTES.CODART,VDLOTES.CODLOT, "\
                    " VDLOTES.CODLOTPROV,VDLOTES.CADUCI,VDLOTES.RETEST, "\
                    " VDLOTES.BLOQLOTE,VDLOTES.POTENCIA,VDLOTES.SWTPRECIO, "\
                    " VDLOTES.MUESTREADO,VDLOTES.CODCOMEN,VDLOTES.VDEXTRA, "\
                    " VDLOTES.CODOPEMODIF,VDLOTES.FECMODIF,VDLOTES.HORAMODIF "\
        " FROM VDLOTES"\
        " WHERE "\
               " VDLOTES.CODART=:CODART "\
               " AND VDLOTES.CODLOT=:CODLOT "
static v10cursors *vdsellotvdlotes;

#define UPDALOT "UPDATE VDLOTES SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODART=:CODART , "\
               " CODLOT=:CODLOT , "\
               " CODLOTPROV=:CODLOTPROV , "\
               " CADUCI=:CADUCI , "\
               " RETEST=:RETEST , "\
               " BLOQLOTE=:BLOQLOTE , "\
               " POTENCIA=:POTENCIA , "\
               " SWTPRECIO=:SWTPRECIO , "\
               " MUESTREADO=:MUESTREADO , "\
               " CODCOMEN=:CODCOMEN , "\
               " VDEXTRA=:VDEXTRA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdalotvdlotes;

#define INSLOT "INSERT INTO VDLOTES (CODART,CODLOT,CODLOTPROV,CADUCI,RETEST,BLOQLOTE, "\
                    " POTENCIA,SWTPRECIO,MUESTREADO,CODCOMEN,VDEXTRA,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF "\
       " ) VALUES ( "\
                    " :CODART,:CODLOT,:CODLOTPROV,:CADUCI,:RETEST,:BLOQLOTE, "\
                    " :POTENCIA,:SWTPRECIO,:MUESTREADO,:CODCOMEN,:VDEXTRA,VDUSER.GETUSER,VD.FECHASYS, "\
                    " VD.HORASYS) "
static v10cursors *vdinslot;

#define DELLOT "DELETE VDLOTES WHERE ROWID=:MIROWID "
static v10cursors *vddellot;

static vdlotess svdlotes;

static diccols colvdlotes[]={
	{"ROWID",V10CADENA,(size_t)&svdlotes.rowid,sizeof(svdlotes.rowid)},
	{"CODART",V10CADENA,(size_t)&svdlotes.codart,sizeof(svdlotes.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdlotes.codlot,sizeof(svdlotes.codlot)},
	{"CODLOTPROV",V10CADENA,(size_t)&svdlotes.codlotprov,sizeof(svdlotes.codlotprov)},
	{"CADUCI",V10CADENA,(size_t)&svdlotes.caduci,sizeof(svdlotes.caduci)},
	{"RETEST",V10CADENA,(size_t)&svdlotes.retest,sizeof(svdlotes.retest)},
	{"BLOQLOTE",V10CADENA,(size_t)&svdlotes.bloqlote,sizeof(svdlotes.bloqlote)},
	{"POTENCIA",V10DOUBLE,(size_t)&svdlotes.potencia,sizeof(svdlotes.potencia)},
	{"SWTPRECIO",V10CADENA,(size_t)&svdlotes.swtprecio,sizeof(svdlotes.swtprecio)},
	{"MUESTREADO",V10CADENA,(size_t)&svdlotes.muestreado,sizeof(svdlotes.muestreado)},
	{"CODCOMEN",V10LONG,(size_t)&svdlotes.codcomen,sizeof(svdlotes.codcomen)},
	{"VDEXTRA",V10CADENA,(size_t)&svdlotes.vdextra,sizeof(svdlotes.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdlotes.codopemodif,sizeof(svdlotes.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdlotes.fecmodif,sizeof(svdlotes.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdlotes.horamodif,sizeof(svdlotes.horamodif)},
	{"STATUS",V10LONG,(size_t)&svdlotes.status,sizeof(svdlotes.status)}
	};
static diccionarios dvdlotes[]={
    {colvdlotes,16}
};
diccionario dlot={dvdlotes,1};

static char msglogLOT[LCADENA];
static char msgdebugLOT[LCADENABIG];
static int init=0;


static void fin_vd_lot(void)
{
if (vdsellotcodlotartordr) {
    liberacursor(vdsellotcodlotartordr);
    vdsellotcodlotartordr = NULL;
}
if (vdsellotvdlotes) {
    liberacursor(vdsellotvdlotes);
    vdsellotvdlotes = NULL;
}
if (vdupdalotvdlotes) {
    liberacursor(vdupdalotvdlotes);
    vdupdalotvdlotes = NULL;
}
if (vdinslot != NULL) {
    liberacursor(vdinslot);
    vdinslot = NULL;
}
if (vddellot != NULL) {
    liberacursor(vddellot);
    vddellot = NULL;
}
}
static void init_sellotcodlotartordr(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotes[0].numcol;nc++) dvdlotes[0].c[nc].offset-=(size_t)&svdlotes;
    vdsellotcodlotartordr=abrecursordebug(SELLOTCODLOTARTORDR,1280);
    definetodo(vdsellotcodlotartordr,svdlotes.rowid,sizeof(svdlotes.rowid),V10CADENA,
                          svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          svdlotes.codlotprov,sizeof(svdlotes.codlotprov),V10CADENA,
                          svdlotes.caduci,sizeof(svdlotes.caduci),V10CADENA,
                          svdlotes.retest,sizeof(svdlotes.retest),V10CADENA,
                          svdlotes.bloqlote,sizeof(svdlotes.bloqlote),V10CADENA,
                          &svdlotes.potencia,sizeof(svdlotes.potencia),V10DOUBLE,
                          svdlotes.swtprecio,sizeof(svdlotes.swtprecio),V10CADENA,
                          svdlotes.muestreado,sizeof(svdlotes.muestreado),V10CADENA,
                          &svdlotes.codcomen,sizeof(svdlotes.codcomen),V10LONG,
                          svdlotes.vdextra,sizeof(svdlotes.vdextra),V10CADENA,
                          svdlotes.codopemodif,sizeof(svdlotes.codopemodif),V10CADENA,
                          &svdlotes.fecmodif,sizeof(svdlotes.fecmodif),V10LONG,
                          svdlotes.horamodif,sizeof(svdlotes.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellotcodlotartordr,"CODLOT",svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          "CODART",svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          "STATUS",&svdlotes.status,sizeof(svdlotes.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lot);
        init = 1;
    }
}

static void init_sellotvdlotes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotes[0].numcol;nc++) dvdlotes[0].c[nc].offset-=(size_t)&svdlotes;
    vdsellotvdlotes=abrecursordebug(SELLOTVDLOTES,1280);
    definetodo(vdsellotvdlotes,svdlotes.rowid,sizeof(svdlotes.rowid),V10CADENA,
                          svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          svdlotes.codlotprov,sizeof(svdlotes.codlotprov),V10CADENA,
                          svdlotes.caduci,sizeof(svdlotes.caduci),V10CADENA,
                          svdlotes.retest,sizeof(svdlotes.retest),V10CADENA,
                          svdlotes.bloqlote,sizeof(svdlotes.bloqlote),V10CADENA,
                          &svdlotes.potencia,sizeof(svdlotes.potencia),V10DOUBLE,
                          svdlotes.swtprecio,sizeof(svdlotes.swtprecio),V10CADENA,
                          svdlotes.muestreado,sizeof(svdlotes.muestreado),V10CADENA,
                          &svdlotes.codcomen,sizeof(svdlotes.codcomen),V10LONG,
                          svdlotes.vdextra,sizeof(svdlotes.vdextra),V10CADENA,
                          svdlotes.codopemodif,sizeof(svdlotes.codopemodif),V10CADENA,
                          &svdlotes.fecmodif,sizeof(svdlotes.fecmodif),V10LONG,
                          svdlotes.horamodif,sizeof(svdlotes.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellotvdlotes,"CODART",svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          "CODLOT",svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lot);
        init = 1;
    }
}

static void init_updalotvdlotes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotes[0].numcol;nc++) dvdlotes[0].c[nc].offset-=(size_t)&svdlotes;
    vdupdalotvdlotes=abrecursordebug(UPDALOT,1280);
    bindtodo(vdupdalotvdlotes,"CODART",svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          "CODLOT",svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          "CODLOTPROV",svdlotes.codlotprov,sizeof(svdlotes.codlotprov),V10CADENA,
                          "CADUCI",svdlotes.caduci,sizeof(svdlotes.caduci),V10CADENA,
                          "RETEST",svdlotes.retest,sizeof(svdlotes.retest),V10CADENA,
                          "BLOQLOTE",svdlotes.bloqlote,sizeof(svdlotes.bloqlote),V10CADENA,
                          "POTENCIA",&svdlotes.potencia,sizeof(svdlotes.potencia),V10DOUBLE,
                          "SWTPRECIO",svdlotes.swtprecio,sizeof(svdlotes.swtprecio),V10CADENA,
                          "MUESTREADO",svdlotes.muestreado,sizeof(svdlotes.muestreado),V10CADENA,
                          "CODCOMEN",&svdlotes.codcomen,sizeof(svdlotes.codcomen),V10LONG,
                          "VDEXTRA",svdlotes.vdextra,sizeof(svdlotes.vdextra),V10CADENA,
                          "MIROWID",svdlotes.rowid,sizeof(svdlotes.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lot);
        init = 1;
    }
}

static void init_inslot(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotes[0].numcol;nc++) dvdlotes[0].c[nc].offset-=(size_t)&svdlotes;
    vdinslot=abrecursordebug(INSLOT,1280);
    bindtodo(vdinslot,"CODART",svdlotes.codart,sizeof(svdlotes.codart),V10CADENA,
                          "CODLOT",svdlotes.codlot,sizeof(svdlotes.codlot),V10CADENA,
                          "CODLOTPROV",svdlotes.codlotprov,sizeof(svdlotes.codlotprov),V10CADENA,
                          "CADUCI",svdlotes.caduci,sizeof(svdlotes.caduci),V10CADENA,
                          "RETEST",svdlotes.retest,sizeof(svdlotes.retest),V10CADENA,
                          "BLOQLOTE",svdlotes.bloqlote,sizeof(svdlotes.bloqlote),V10CADENA,
                          "POTENCIA",&svdlotes.potencia,sizeof(svdlotes.potencia),V10DOUBLE,
                          "SWTPRECIO",svdlotes.swtprecio,sizeof(svdlotes.swtprecio),V10CADENA,
                          "MUESTREADO",svdlotes.muestreado,sizeof(svdlotes.muestreado),V10CADENA,
                          "CODCOMEN",&svdlotes.codcomen,sizeof(svdlotes.codcomen),V10LONG,
                          "VDEXTRA",svdlotes.vdextra,sizeof(svdlotes.vdextra),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lot);
        init = 1;
    }
}

static void init_dellot(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdlotes[0].numcol;nc++) dvdlotes[0].c[nc].offset-=(size_t)&svdlotes;
    vddellot=abrecursordebug(DELLOT,1280);
    bindtodo(vddellot,"MIROWID",svdlotes.rowid,sizeof(svdlotes.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lot);
        init = 1;
    }
}

diccionario *LOTdamediccionario(void)
{
     return(&dlot);
}

int LOTselcodlotartordr(char *codlot,char *codart,long status,vdlotess *lot)
{
  int vdret;
  if (vdsellotcodlotartordr==NULL) init_sellotcodlotartordr();
  memset(&svdlotes,0,sizeof(svdlotes));
  strcpy(svdlotes.codlot,codlot);
  strcpy(svdlotes.codart,codart);
  svdlotes.status=status;
  vdret=ejefetchcursor(vdsellotcodlotartordr);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellotcodlotartordr. vdret %d. \n",LOTlog(&svdlotes),vdret);
    return(VD_EERRORACLE);
   }
  *lot=svdlotes;
  return(vdret);
}

int LOTselvdlotes(char *codart,char *codlot,vdlotess *lot)
{
  int vdret;
  if (vdsellotvdlotes==NULL) init_sellotvdlotes();
  memset(&svdlotes,0,sizeof(svdlotes));
  strcpy(svdlotes.codart,codart);
  strcpy(svdlotes.codlot,codlot);
  vdret=ejefetchcursor(vdsellotvdlotes);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellotvdlotes. vdret %d. \n",LOTlog(&svdlotes),vdret);
    return(VD_EERRORACLE);
   }
  *lot=svdlotes;
  return(vdret);
}

int LOTactualizavdlotes(vdlotess *lot,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando LOTactualizavdlotes:  %s .  \n",LOTlog(&svdlotes));
  if (vdupdalotvdlotes==NULL) init_updalotvdlotes();
  svdlotes=*lot;
  vdret=ejecutacursor(vdupdalotvdlotes);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdalotvdlotes);
     getcurerrornombre(vdupdalotvdlotes->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdalotvdlotes)!=1) return(VD_EERRORACLE);
  return(0);
}

int LOTinsert(vdlotess *lot,int error)
{
  int vdret;
  if (!vdinslot) init_inslot();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",LOTlog(&svdlotes));
  svdlotes=*lot;
  vdret=ejecutacursor(vdinslot);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinslot);
     getcurerrornombre(vdinslot->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int LOTdel(vdlotess *lot,int error)
{
  int vdret;
  svdlotes=*lot;
  if (vddellot==NULL) init_dellot();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",LOTlog(&svdlotes));
  vdret=ejecutacursor(vddellot);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddellot);
     getcurerrornombre(vddellot->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int LOTinter(vdlotess *lot)
{
  int vdret = 0;
  if (vdsellotvdlotes==NULL) init_sellotvdlotes();
  memset(&svdlotes,0,sizeof(svdlotes));
  strcpy(svdlotes.codart,lot->codart);
  strcpy(svdlotes.codlot,lot->codlot);
  vdret=ejefetchcursor(vdsellotvdlotes);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellotvdlotes. vdret %d. \n",LOTlog(&svdlotes),vdret);
    return(VD_EERRORACLE);
  }

  *lot=svdlotes;
  return(vdret);
}

char * LOTlog(vdlotess *lot)
{
    sprintf(msglogLOT, "VDLOTES: codart %s codlot %s ",lot->codart,lot->codlot);
    return(msglogLOT);
}

char * LOTdebug(vdlotess *lot)
{
    debugestruct(&dlot,lot,msgdebugLOT);
    return(msgdebugLOT);
}

