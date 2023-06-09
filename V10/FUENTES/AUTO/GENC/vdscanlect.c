// Modulo generado automaticamente a partir de VDSCANLECT.DEF
//# Modulo : VDSCANLECT.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDSCANLECT
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 10-02-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=SCL
//EXTRA=IDINFOGEST,V10LONG
//
//RECORRE=IDINFOGEST,IDINFOGEST,WHERE=(REDSCAN,SCANNER) IN (SELECT REDSCAN,SCANNER FROM VDZONAS WHERE IDINFOGEST=:IDINFOGEST);
//SECUENCIA=VDSECSCANLECT,SEQACCION;
//RECORRE=ESCANERYSTATUS,STATUS,WHERE= (REDSCAN,SCANNER) IN (SELECT ORD.IDINFOLECTURA,ORD.SCANNER FROM VDORDENADORES ORD, SYS.V_$SESSION S WHERE AUDSID=USERENV('SESSIONID') AND ORD.ORDENADOR = S.TERMINAL);ORDERBY=SEQACCION DESC;
//UPDATE=STATUS,STATUS
//DELETE
//INSERT
//

#include "vd.h"
#define SELSCLIDINFOGEST "SELECT VDSCANLECT.ROWID,VDSCANLECT.SEQACCION,VDSCANLECT.REDSCAN, "\
                    " VDSCANLECT.SCANNER,VDSCANLECT.TEXTO,VDSCANLECT.STATUS, "\
                    " VDSCANLECT.CODOPEMODIF,VDSCANLECT.FECMODIF,VDSCANLECT.HORAMODIF, "\
                    " VDSCANLECT.CODCOMEN "\
        " FROM VDSCANLECT"\
        " WHERE "\
              " (REDSCAN,SCANNER) IN (SELECT REDSCAN,SCANNER FROM VDZONAS WHERE IDINFOGEST=:IDINFOGEST) "
static v10cursors *vdselsclidinfogest;

#define SELSCLESCANERYSTATUS "SELECT VDSCANLECT.ROWID,VDSCANLECT.SEQACCION,VDSCANLECT.REDSCAN, "\
                    " VDSCANLECT.SCANNER,VDSCANLECT.TEXTO,VDSCANLECT.STATUS, "\
                    " VDSCANLECT.CODOPEMODIF,VDSCANLECT.FECMODIF,VDSCANLECT.HORAMODIF, "\
                    " VDSCANLECT.CODCOMEN "\
        " FROM VDSCANLECT"\
        " WHERE "\
               " VDSCANLECT.STATUS=:STATUS "\
              "  AND  (REDSCAN,SCANNER) IN (SELECT ORD.IDINFOLECTURA,ORD.SCANNER FROM VDORDENADORES ORD, SYS.V_$SESSION S WHERE AUDSID=USERENV('SESSIONID') AND ORD.ORDENADOR = S.TERMINAL) "\
        " ORDER BY SEQACCION DESC "
static v10cursors *vdselsclescanerystatus;

#define SELSCLVDSCANLECT "SELECT VDSCANLECT.ROWID,VDSCANLECT.SEQACCION,VDSCANLECT.REDSCAN, "\
                    " VDSCANLECT.SCANNER,VDSCANLECT.TEXTO,VDSCANLECT.STATUS, "\
                    " VDSCANLECT.CODOPEMODIF,VDSCANLECT.FECMODIF,VDSCANLECT.HORAMODIF, "\
                    " VDSCANLECT.CODCOMEN "\
        " FROM VDSCANLECT"\
        " WHERE "\
               " VDSCANLECT.SEQACCION=:SEQACCION "
static v10cursors *vdselsclvdscanlect;

#define UPDASCLSTATUS "UPDATE VDSCANLECT SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdasclstatus;

#define SELVDSECSCANLECT "SELECT VDSECSCANLECT.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecscanlect;

#define INSSCL "INSERT INTO VDSCANLECT (SEQACCION,REDSCAN,SCANNER,TEXTO,STATUS,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :SEQACCION,:REDSCAN,:SCANNER,:TEXTO,:STATUS,VDUSER.GETUSER(), "\
                    " VD.FECHASYS(),VD.HORASYS(),:CODCOMEN) "
static v10cursors *vdinsscl;

#define DELSCL "DELETE VDSCANLECT WHERE ROWID=:MIROWID "
static v10cursors *vddelscl;

static vdscanlects svdscanlect;

static diccols colvdscanlect[]={
	{"ROWID",V10CADENA,(size_t)&svdscanlect.rowid,sizeof(svdscanlect.rowid)},
	{"SEQACCION",V10LONG,(size_t)&svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion)},
	{"REDSCAN",V10LONG,(size_t)&svdscanlect.redscan,sizeof(svdscanlect.redscan)},
	{"SCANNER",V10LONG,(size_t)&svdscanlect.scanner,sizeof(svdscanlect.scanner)},
	{"TEXTO",V10CADENA,(size_t)&svdscanlect.texto,sizeof(svdscanlect.texto)},
	{"STATUS",V10LONG,(size_t)&svdscanlect.status,sizeof(svdscanlect.status)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdscanlect.codopemodif,sizeof(svdscanlect.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdscanlect.fecmodif,sizeof(svdscanlect.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdscanlect.horamodif,sizeof(svdscanlect.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdscanlect.codcomen,sizeof(svdscanlect.codcomen)},
	{"IDINFOGEST",V10LONG,(size_t)&svdscanlect.idinfogest,sizeof(svdscanlect.idinfogest)}
	};
static diccionarios dvdscanlect[]={
    {colvdscanlect,11}
};
diccionario dscl={dvdscanlect,1};

static char msglogSCL[LCADENA];
static char msgdebugSCL[LCADENABIG];
static int init=0;


static void fin_vd_scl(void)
{
if (vdselsclidinfogest) {
    liberacursor(vdselsclidinfogest);
    vdselsclidinfogest = NULL;
}
if (vdselsclescanerystatus) {
    liberacursor(vdselsclescanerystatus);
    vdselsclescanerystatus = NULL;
}
if (vdselsclvdscanlect) {
    liberacursor(vdselsclvdscanlect);
    vdselsclvdscanlect = NULL;
}
if (vdupdasclstatus) {
    liberacursor(vdupdasclstatus);
    vdupdasclstatus = NULL;
}
if (vdselvdsecscanlect != NULL) {
    liberacursor(vdselvdsecscanlect);
    vdselvdsecscanlect = NULL;
}
if (vdinsscl != NULL) {
    liberacursor(vdinsscl);
    vdinsscl = NULL;
}
if (vddelscl != NULL) {
    liberacursor(vddelscl);
    vddelscl = NULL;
}
}
static void init_selsclidinfogest(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdselsclidinfogest=abrecursordebug(SELSCLIDINFOGEST,1280);
    definetodo(vdselsclidinfogest,svdscanlect.rowid,sizeof(svdscanlect.rowid),V10CADENA,
                          &svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,
                          &svdscanlect.redscan,sizeof(svdscanlect.redscan),V10LONG,
                          &svdscanlect.scanner,sizeof(svdscanlect.scanner),V10LONG,
                          svdscanlect.texto,sizeof(svdscanlect.texto),V10CADENA,
                          &svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          svdscanlect.codopemodif,sizeof(svdscanlect.codopemodif),V10CADENA,
                          &svdscanlect.fecmodif,sizeof(svdscanlect.fecmodif),V10LONG,
                          svdscanlect.horamodif,sizeof(svdscanlect.horamodif),V10CADENA,
                          &svdscanlect.codcomen,sizeof(svdscanlect.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselsclidinfogest,"IDINFOGEST",&svdscanlect.idinfogest,sizeof(svdscanlect.idinfogest),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_selsclescanerystatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdselsclescanerystatus=abrecursordebug(SELSCLESCANERYSTATUS,1280);
    definetodo(vdselsclescanerystatus,svdscanlect.rowid,sizeof(svdscanlect.rowid),V10CADENA,
                          &svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,
                          &svdscanlect.redscan,sizeof(svdscanlect.redscan),V10LONG,
                          &svdscanlect.scanner,sizeof(svdscanlect.scanner),V10LONG,
                          svdscanlect.texto,sizeof(svdscanlect.texto),V10CADENA,
                          &svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          svdscanlect.codopemodif,sizeof(svdscanlect.codopemodif),V10CADENA,
                          &svdscanlect.fecmodif,sizeof(svdscanlect.fecmodif),V10LONG,
                          svdscanlect.horamodif,sizeof(svdscanlect.horamodif),V10CADENA,
                          &svdscanlect.codcomen,sizeof(svdscanlect.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselsclescanerystatus,"STATUS",&svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_selsclvdscanlect(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdselsclvdscanlect=abrecursordebug(SELSCLVDSCANLECT,1280);
    definetodo(vdselsclvdscanlect,svdscanlect.rowid,sizeof(svdscanlect.rowid),V10CADENA,
                          &svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,
                          &svdscanlect.redscan,sizeof(svdscanlect.redscan),V10LONG,
                          &svdscanlect.scanner,sizeof(svdscanlect.scanner),V10LONG,
                          svdscanlect.texto,sizeof(svdscanlect.texto),V10CADENA,
                          &svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          svdscanlect.codopemodif,sizeof(svdscanlect.codopemodif),V10CADENA,
                          &svdscanlect.fecmodif,sizeof(svdscanlect.fecmodif),V10LONG,
                          svdscanlect.horamodif,sizeof(svdscanlect.horamodif),V10CADENA,
                          &svdscanlect.codcomen,sizeof(svdscanlect.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselsclvdscanlect,"SEQACCION",&svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_updasclstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdupdasclstatus=abrecursordebug(UPDASCLSTATUS,1280);
    bindtodo(vdupdasclstatus,"STATUS",&svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          "MIROWID",svdscanlect.rowid,sizeof(svdscanlect.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_selvdsecscanlect(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdselvdsecscanlect=abrecursordebug(SELVDSECSCANLECT,1280);
    definetodo(vdselvdsecscanlect,&svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_insscl(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vdinsscl=abrecursordebug(INSSCL,1280);
    bindtodo(vdinsscl,"SEQACCION",&svdscanlect.seqaccion,sizeof(svdscanlect.seqaccion),V10LONG,
                          "REDSCAN",&svdscanlect.redscan,sizeof(svdscanlect.redscan),V10LONG,
                          "SCANNER",&svdscanlect.scanner,sizeof(svdscanlect.scanner),V10LONG,
                          "TEXTO",svdscanlect.texto,sizeof(svdscanlect.texto),V10CADENA,
                          "STATUS",&svdscanlect.status,sizeof(svdscanlect.status),V10LONG,
                          "CODCOMEN",&svdscanlect.codcomen,sizeof(svdscanlect.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

static void init_delscl(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdscanlect[0].numcol;nc++) dvdscanlect[0].c[nc].offset-=(size_t)&svdscanlect;
    vddelscl=abrecursordebug(DELSCL,1280);
    bindtodo(vddelscl,"MIROWID",svdscanlect.rowid,sizeof(svdscanlect.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_scl);
        init = 1;
    }
}

diccionario *SCLdamediccionario(void)
{
     return(&dscl);
}

int SCLbuscaidinfogest(long idinfogest,vdscanlects *scl)
{
  int vdret;
  memset(&svdscanlect,0,sizeof(svdscanlect));
  svdscanlect.idinfogest=idinfogest;
  if (vdselsclidinfogest==NULL) init_selsclidinfogest();
  vdret=ejefetchcursor(vdselsclidinfogest);
  if (vdret==0) {
     *scl=svdscanlect;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsclidinfogest. vdret %d. \n",SCLlog(&svdscanlect),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SCLnextidinfogest(vdscanlects *scl)
{
  int vdret;
  vdret=fetchcursor(vdselsclidinfogest);
  if (vdret==0) {
     *scl=svdscanlect;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsclidinfogest. vdret %d. \n",SCLlog(&svdscanlect),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsclidinfogest);
  return(VD_EERRORACLE);
}

int SCLbuscaescanerystatus(long status,vdscanlects *scl)
{
  int vdret;
  memset(&svdscanlect,0,sizeof(svdscanlect));
  svdscanlect.status=status;
  if (vdselsclescanerystatus==NULL) init_selsclescanerystatus();
  vdret=ejefetchcursor(vdselsclescanerystatus);
  if (vdret==0) {
     *scl=svdscanlect;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsclescanerystatus. vdret %d. \n",SCLlog(&svdscanlect),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SCLnextescanerystatus(vdscanlects *scl)
{
  int vdret;
  vdret=fetchcursor(vdselsclescanerystatus);
  if (vdret==0) {
     *scl=svdscanlect;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsclescanerystatus. vdret %d. \n",SCLlog(&svdscanlect),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsclescanerystatus);
  return(VD_EERRORACLE);
}

int SCLselvdscanlect(long seqaccion,vdscanlects *scl)
{
  int vdret;
  if (vdselsclvdscanlect==NULL) init_selsclvdscanlect();
  memset(&svdscanlect,0,sizeof(svdscanlect));
  svdscanlect.seqaccion=seqaccion;
  vdret=ejefetchcursor(vdselsclvdscanlect);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselsclvdscanlect. vdret %d. \n",SCLlog(&svdscanlect),vdret);
    return(VD_EERRORACLE);
   }
  *scl=svdscanlect;
  return(vdret);
}

int SCLactualizastatus(vdscanlects *scl,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SCLactualizastatus:  %s .  \n",SCLlog(&svdscanlect));
  if (vdupdasclstatus==NULL) init_updasclstatus();
  svdscanlect=*scl;
  vdret=ejecutacursor(vdupdasclstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdasclstatus);
     getcurerrornombre(vdupdasclstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdasclstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int SCLselvdsecscanlect(long *donde)
{
  int vdret;
  if (!vdselvdsecscanlect) init_selvdsecscanlect();
  vdret=ejefetchcursor(vdselvdsecscanlect);
  if (!vdret) {
     *donde=svdscanlect.seqaccion;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int SCLinsert(vdscanlects *scl,int error)
{
  int vdret;
  if (!vdinsscl) init_insscl();
  if (!scl->seqaccion) {
     if ((vdret=SCLselvdsecscanlect(&(scl->seqaccion)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",SCLlog(&svdscanlect));
  svdscanlect=*scl;
  vdret=ejecutacursor(vdinsscl);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsscl);
     getcurerrornombre(vdinsscl->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int SCLdel(vdscanlects *scl,int error)
{
  int vdret;
  svdscanlect=*scl;
  if (vddelscl==NULL) init_delscl();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",SCLlog(&svdscanlect));
  vdret=ejecutacursor(vddelscl);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelscl);
     getcurerrornombre(vddelscl->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * SCLlog(vdscanlects *scl)
{
    sprintf(msglogSCL, "VDSCANLECT: seqaccion %ld ",scl->seqaccion);
    return(msglogSCL);
}

char * SCLdebug(vdscanlects *scl)
{
    debugestruct(&dscl,scl,msgdebugSCL);
    return(msgdebugSCL);
}

