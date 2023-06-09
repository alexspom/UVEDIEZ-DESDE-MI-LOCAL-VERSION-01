// Modulo generado automaticamente a partir de VDCONTE.DEF
//#***
//# VDCONTE.c - Generaci�n autom�tica del c�digo c para la tabla                                                        
//# 
//# Prop�sito: Funciones de acceso a la tabla VDCONTE
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 8-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=CNT
//
//EXTRA=PTRMSG,V10CADENA,1025
//EXTRA=SECCNT,V10LONG
//
//UPDATE=STATUS,STATUS
//
//SECUENCIA=VDSECCNT,SECCNT
//
//INSERT 
//DELETE
//LOCK

#include "vd.h"
#define SELCNTVDCONTE "SELECT VDCONTE.ROWID,VDCONTE.CODMAT,VDCONTE.TIPOCONTE, "\
                    " VDCONTE.CNTSSCC,VDCONTE.CODUBI,VDCONTE.POSCONTE, "\
                    " VDCONTE.ALTURACONTE,VDCONTE.STATUS,VDCONTE.FECENTRADA, "\
                    " VDCONTE.HORAENTRADA,VDCONTE.FECCREADO,VDCONTE.HORACREADO, "\
                    " VDCONTE.VDEXTRA,VDCONTE.CLAVEEXT,VDCONTE.CODCOMEN, "\
                    " VDCONTE.CODOPEMODIF,VDCONTE.FECMODIF,VDCONTE.HORAMODIF, "\
                    " VDCONTE.PESOCONTE,VDCONTE.LARGOCONTE,VDCONTE.ANCHOCONTE "\
        " FROM VDCONTE"\
        " WHERE "\
               " VDCONTE.CODMAT=:CODMAT "
static v10cursors *vdselcntvdconte;

#define SELCNTROWIDLOCK "SELECT ROWID,CODMAT,TIPOCONTE,CNTSSCC,CODUBI,POSCONTE,ALTURACONTE, "\
                    " STATUS,FECENTRADA,HORAENTRADA,FECCREADO,HORACREADO,VDEXTRA,CLAVEEXT, "\
                    " CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,PESOCONTE,LARGOCONTE,ANCHOCONTE "\
        " FROM VDCONTE "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselcntrowidlock;

#define UPDACNTSTATUS "UPDATE VDCONTE SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdacntstatus;

#define SELVDSECCNT "SELECT VDSECCNT.NEXTVAL FROM DUAL"
static v10cursors *vdselvdseccnt;

#define INSCNT "INSERT INTO VDCONTE (CODMAT,TIPOCONTE,CNTSSCC,CODUBI,POSCONTE,ALTURACONTE, "\
                    " STATUS,FECENTRADA,HORAENTRADA,FECCREADO,HORACREADO,VDEXTRA,CLAVEEXT, "\
                    " CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,PESOCONTE,LARGOCONTE,ANCHOCONTE "\
       " ) VALUES ( "\
                    " :CODMAT,:TIPOCONTE,:CNTSSCC,:CODUBI,:POSCONTE,:ALTURACONTE, "\
                    " :STATUS,:FECENTRADA,:HORAENTRADA,:FECCREADO,:HORACREADO,:VDEXTRA,:CLAVEEXT, "\
                    " :CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:PESOCONTE,:LARGOCONTE,:ANCHOCONTE) "
static v10cursors *vdinscnt;

#define DELCNT "DELETE VDCONTE WHERE ROWID=:MIROWID "
static v10cursors *vddelcnt;

static vdcontes svdconte;

static diccols colvdconte[]={
	{"ROWID",V10CADENA,(size_t)&svdconte.rowid,sizeof(svdconte.rowid)},
	{"CODMAT",V10CADENA,(size_t)&svdconte.codmat,sizeof(svdconte.codmat)},
	{"TIPOCONTE",V10CADENA,(size_t)&svdconte.tipoconte,sizeof(svdconte.tipoconte)},
	{"CNTSSCC",V10CADENA,(size_t)&svdconte.cntsscc,sizeof(svdconte.cntsscc)},
	{"CODUBI",V10CADENA,(size_t)&svdconte.codubi,sizeof(svdconte.codubi)},
	{"POSCONTE",V10LONG,(size_t)&svdconte.posconte,sizeof(svdconte.posconte)},
	{"ALTURACONTE",V10LONG,(size_t)&svdconte.alturaconte,sizeof(svdconte.alturaconte)},
	{"STATUS",V10LONG,(size_t)&svdconte.status,sizeof(svdconte.status)},
	{"FECENTRADA",V10LONG,(size_t)&svdconte.fecentrada,sizeof(svdconte.fecentrada)},
	{"HORAENTRADA",V10CADENA,(size_t)&svdconte.horaentrada,sizeof(svdconte.horaentrada)},
	{"FECCREADO",V10LONG,(size_t)&svdconte.feccreado,sizeof(svdconte.feccreado)},
	{"HORACREADO",V10CADENA,(size_t)&svdconte.horacreado,sizeof(svdconte.horacreado)},
	{"VDEXTRA",V10CADENA,(size_t)&svdconte.vdextra,sizeof(svdconte.vdextra)},
	{"CLAVEEXT",V10CADENA,(size_t)&svdconte.claveext,sizeof(svdconte.claveext)},
	{"CODCOMEN",V10LONG,(size_t)&svdconte.codcomen,sizeof(svdconte.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdconte.codopemodif,sizeof(svdconte.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdconte.fecmodif,sizeof(svdconte.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdconte.horamodif,sizeof(svdconte.horamodif)},
	{"PESOCONTE",V10LONG,(size_t)&svdconte.pesoconte,sizeof(svdconte.pesoconte)},
	{"LARGOCONTE",V10LONG,(size_t)&svdconte.largoconte,sizeof(svdconte.largoconte)},
	{"ANCHOCONTE",V10LONG,(size_t)&svdconte.anchoconte,sizeof(svdconte.anchoconte)},
	{"PTRMSG",V10CADENA,(size_t)&svdconte.ptrmsg,sizeof(svdconte.ptrmsg)},
	{"SECCNT",V10LONG,(size_t)&svdconte.seccnt,sizeof(svdconte.seccnt)}
	};
static diccionarios dvdconte[]={
    {colvdconte,23}
};
diccionario dcnt={dvdconte,1};

static char msglogCNT[LCADENA];
static char msgdebugCNT[LCADENABIG];
static int init=0;


static void fin_vd_cnt(void)
{
if (vdselcntvdconte) {
    liberacursor(vdselcntvdconte);
    vdselcntvdconte = NULL;
}
if (vdselcntrowidlock) {
    liberacursor(vdselcntrowidlock);
    vdselcntrowidlock = NULL;
}
if (vdupdacntstatus) {
    liberacursor(vdupdacntstatus);
    vdupdacntstatus = NULL;
}
if (vdselvdseccnt != NULL) {
    liberacursor(vdselvdseccnt);
    vdselvdseccnt = NULL;
}
if (vdinscnt != NULL) {
    liberacursor(vdinscnt);
    vdinscnt = NULL;
}
if (vddelcnt != NULL) {
    liberacursor(vddelcnt);
    vddelcnt = NULL;
}
}
static void init_selcntvdconte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vdselcntvdconte=abrecursordebug(SELCNTVDCONTE,1280);
    definetodo(vdselcntvdconte,svdconte.rowid,sizeof(svdconte.rowid),V10CADENA,
                          svdconte.codmat,sizeof(svdconte.codmat),V10CADENA,
                          svdconte.tipoconte,sizeof(svdconte.tipoconte),V10CADENA,
                          svdconte.cntsscc,sizeof(svdconte.cntsscc),V10CADENA,
                          svdconte.codubi,sizeof(svdconte.codubi),V10CADENA,
                          &svdconte.posconte,sizeof(svdconte.posconte),V10LONG,
                          &svdconte.alturaconte,sizeof(svdconte.alturaconte),V10LONG,
                          &svdconte.status,sizeof(svdconte.status),V10LONG,
                          &svdconte.fecentrada,sizeof(svdconte.fecentrada),V10LONG,
                          svdconte.horaentrada,sizeof(svdconte.horaentrada),V10CADENA,
                          &svdconte.feccreado,sizeof(svdconte.feccreado),V10LONG,
                          svdconte.horacreado,sizeof(svdconte.horacreado),V10CADENA,
                          svdconte.vdextra,sizeof(svdconte.vdextra),V10CADENA,
                          svdconte.claveext,sizeof(svdconte.claveext),V10CADENA,
                          &svdconte.codcomen,sizeof(svdconte.codcomen),V10LONG,
                          svdconte.codopemodif,sizeof(svdconte.codopemodif),V10CADENA,
                          &svdconte.fecmodif,sizeof(svdconte.fecmodif),V10LONG,
                          svdconte.horamodif,sizeof(svdconte.horamodif),V10CADENA,
                          &svdconte.pesoconte,sizeof(svdconte.pesoconte),V10LONG,
                          &svdconte.largoconte,sizeof(svdconte.largoconte),V10LONG,
                          &svdconte.anchoconte,sizeof(svdconte.anchoconte),V10LONG,
                          NULL);
    bindtodo(vdselcntvdconte,"CODMAT",svdconte.codmat,sizeof(svdconte.codmat),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

static void init_selcntrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vdselcntrowidlock=abrecursordebug(SELCNTROWIDLOCK,1280);
    definetodo(vdselcntrowidlock,svdconte.rowid,sizeof(svdconte.rowid),V10CADENA,
                          svdconte.codmat,sizeof(svdconte.codmat),V10CADENA,
                          svdconte.tipoconte,sizeof(svdconte.tipoconte),V10CADENA,
                          svdconte.cntsscc,sizeof(svdconte.cntsscc),V10CADENA,
                          svdconte.codubi,sizeof(svdconte.codubi),V10CADENA,
                          &svdconte.posconte,sizeof(svdconte.posconte),V10LONG,
                          &svdconte.alturaconte,sizeof(svdconte.alturaconte),V10LONG,
                          &svdconte.status,sizeof(svdconte.status),V10LONG,
                          &svdconte.fecentrada,sizeof(svdconte.fecentrada),V10LONG,
                          svdconte.horaentrada,sizeof(svdconte.horaentrada),V10CADENA,
                          &svdconte.feccreado,sizeof(svdconte.feccreado),V10LONG,
                          svdconte.horacreado,sizeof(svdconte.horacreado),V10CADENA,
                          svdconte.vdextra,sizeof(svdconte.vdextra),V10CADENA,
                          svdconte.claveext,sizeof(svdconte.claveext),V10CADENA,
                          &svdconte.codcomen,sizeof(svdconte.codcomen),V10LONG,
                          svdconte.codopemodif,sizeof(svdconte.codopemodif),V10CADENA,
                          &svdconte.fecmodif,sizeof(svdconte.fecmodif),V10LONG,
                          svdconte.horamodif,sizeof(svdconte.horamodif),V10CADENA,
                          &svdconte.pesoconte,sizeof(svdconte.pesoconte),V10LONG,
                          &svdconte.largoconte,sizeof(svdconte.largoconte),V10LONG,
                          &svdconte.anchoconte,sizeof(svdconte.anchoconte),V10LONG,
                          NULL);
    bindtodo(vdselcntrowidlock,"MIROWID",svdconte.rowid,sizeof(svdconte.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

static void init_updacntstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vdupdacntstatus=abrecursordebug(UPDACNTSTATUS,1280);
    bindtodo(vdupdacntstatus,"STATUS",&svdconte.status,sizeof(svdconte.status),V10LONG,
                          "MIROWID",svdconte.rowid,sizeof(svdconte.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

static void init_selvdseccnt(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vdselvdseccnt=abrecursordebug(SELVDSECCNT,1280);
    definetodo(vdselvdseccnt,&svdconte.seccnt,sizeof(svdconte.seccnt),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

static void init_inscnt(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vdinscnt=abrecursordebug(INSCNT,1280);
    bindtodo(vdinscnt,"CODMAT",svdconte.codmat,sizeof(svdconte.codmat),V10CADENA,
                          "TIPOCONTE",svdconte.tipoconte,sizeof(svdconte.tipoconte),V10CADENA,
                          "CNTSSCC",svdconte.cntsscc,sizeof(svdconte.cntsscc),V10CADENA,
                          "CODUBI",svdconte.codubi,sizeof(svdconte.codubi),V10CADENA,
                          "POSCONTE",&svdconte.posconte,sizeof(svdconte.posconte),V10LONG,
                          "ALTURACONTE",&svdconte.alturaconte,sizeof(svdconte.alturaconte),V10LONG,
                          "STATUS",&svdconte.status,sizeof(svdconte.status),V10LONG,
                          "FECENTRADA",&svdconte.fecentrada,sizeof(svdconte.fecentrada),V10LONG,
                          "HORAENTRADA",svdconte.horaentrada,sizeof(svdconte.horaentrada),V10CADENA,
                          "FECCREADO",&svdconte.feccreado,sizeof(svdconte.feccreado),V10LONG,
                          "HORACREADO",svdconte.horacreado,sizeof(svdconte.horacreado),V10CADENA,
                          "VDEXTRA",svdconte.vdextra,sizeof(svdconte.vdextra),V10CADENA,
                          "CLAVEEXT",svdconte.claveext,sizeof(svdconte.claveext),V10CADENA,
                          "CODCOMEN",&svdconte.codcomen,sizeof(svdconte.codcomen),V10LONG,
                          "PESOCONTE",&svdconte.pesoconte,sizeof(svdconte.pesoconte),V10LONG,
                          "LARGOCONTE",&svdconte.largoconte,sizeof(svdconte.largoconte),V10LONG,
                          "ANCHOCONTE",&svdconte.anchoconte,sizeof(svdconte.anchoconte),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

static void init_delcnt(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdconte[0].numcol;nc++) dvdconte[0].c[nc].offset-=(size_t)&svdconte;
    vddelcnt=abrecursordebug(DELCNT,1280);
    bindtodo(vddelcnt,"MIROWID",svdconte.rowid,sizeof(svdconte.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_cnt);
        init = 1;
    }
}

diccionario *CNTdamediccionario(void)
{
     return(&dcnt);
}

int CNTselvdconte(char *codmat,vdcontes *cnt)
{
  int vdret;
  if (vdselcntvdconte==NULL) init_selcntvdconte();
  memset(&svdconte,0,sizeof(svdconte));
  strcpy(svdconte.codmat,codmat);
  vdret=ejefetchcursor(vdselcntvdconte);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselcntvdconte. vdret %d. \n",CNTlog(&svdconte),vdret);
    return(VD_EERRORACLE);
   }
  *cnt=svdconte;
  return(vdret);
}

int CNTlock(vdcontes *cnt,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdconte=*cnt;
    if (vdselcntrowidlock==NULL) init_selcntrowidlock();
    savepoint("lockvdconte");
    while (1) {
        vdret=ejefetchcursor(vdselcntrowidlock);
        if (vdret==0) break;
        if (vdret==BLOQUEADO && wait) {
           Sleep(1000);
           if (hay_tecla()) if (tecla()==esc) return(VD_EERRBLOQUEO);
           continue;
         } else {
           if (wait==0) return(VD_EERRBLOQUEO);
         }
    }
    if (vdret) return(VD_EERRORACLE);
    if (verificar==0) return(vdret);
    va_start(arg,verificar);
    vdret=vverificacampos(cnt,&svdconte,&dvdconte[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdconte");
    return(vdret);
}

int CNTactualizastatus(vdcontes *cnt,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando CNTactualizastatus:  %s .  \n",CNTlog(&svdconte));
  if (vdupdacntstatus==NULL) init_updacntstatus();
  svdconte=*cnt;
  vdret=ejecutacursor(vdupdacntstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdacntstatus);
     getcurerrornombre(vdupdacntstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdacntstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int CNTselvdseccnt(long *donde)
{
  int vdret;
  if (!vdselvdseccnt) init_selvdseccnt();
  vdret=ejefetchcursor(vdselvdseccnt);
  if (!vdret) {
     *donde=svdconte.seccnt;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int CNTinsert(vdcontes *cnt,int error)
{
  int vdret;
  if (!vdinscnt) init_inscnt();
  if (!cnt->seccnt) {
     if ((vdret=CNTselvdseccnt(&(cnt->seccnt)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",CNTlog(&svdconte));
  svdconte=*cnt;
  vdret=ejecutacursor(vdinscnt);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinscnt);
     getcurerrornombre(vdinscnt->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int CNTdel(vdcontes *cnt,int error)
{
  int vdret;
  svdconte=*cnt;
  if (vddelcnt==NULL) init_delcnt();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",CNTlog(&svdconte));
  vdret=ejecutacursor(vddelcnt);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelcnt);
     getcurerrornombre(vddelcnt->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * CNTlog(vdcontes *cnt)
{
    sprintf(msglogCNT, "VDCONTE: codmat %s ",cnt->codmat);
    return(msglogCNT);
}

char * CNTdebug(vdcontes *cnt)
{
    debugestruct(&dcnt,cnt,msgdebugCNT);
    return(msgdebugCNT);
}

