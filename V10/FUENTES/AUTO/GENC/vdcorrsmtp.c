// Modulo generado automaticamente a partir de VDCORRSMTP.DEF
//#***
//# VDCORRSMTP.DEF - Generaci�n autom�tica del c�digo c para la tabla de env�o de correos
//#                        
//# Prop�sito: Funciones de acceso a la tabla VDCORRSMT
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 09-07-2008
//#************************************************************************************
//# Modificaciones
//#***
//
//EXTRA=COMEN,V10CADENA,1025
//
//TABLE=SMTP
//RECORRE=STATUS,STATUS;WHERE=(NVL(FECPLANIF,0)=0 OR (VD.FECHASYS>FECPLANIF AND VD.HORASYS>FECPLANIF));
//UPDATE=ENVIADO,STATUS,FECENVIO,HORAENVIO

#include "vd.h"
#define SELSMTPSTATUS "SELECT VDCORRSMTP.ROWID,VDCORRSMTP.IDMSG,VDCORRSMTP.ORDENADOR, "\
                    " VDCORRSMTP.TIPOCORREO,VDCORRSMTP.CUENTA,VDCORRSMTP.PARA, "\
                    " VDCORRSMTP.CC,VDCORRSMTP.CCO,VDCORRSMTP.ASUNTO, "\
                    " VDCORRSMTP.CUERPO,VDCORRSMTP.ADJUNTO,VDCORRSMTP.PRIORIDAD, "\
                    " VDCORRSMTP.MIME,VDCORRSMTP.DIRECTORIO,VDCORRSMTP.FICHERO, "\
                    " VDCORRSMTP.STATUS,VDCORRSMTP.CODOPEINS,VDCORRSMTP.FECINS, "\
                    " VDCORRSMTP.HORAINS,VDCORRSMTP.MODULOINS,VDCORRSMTP.ACCIONINS, "\
                    " VDCORRSMTP.FECPLANIF,VDCORRSMTP.HORAPLANIF,VDCORRSMTP.FECENVIO, "\
                    " VDCORRSMTP.HORAENVIO,VDCORRSMTP.VDEXTRA,VDCORRSMTP.CODCOMEN, "\
                    " VDCORRSMTP.CODOPEMODIF,VDCORRSMTP.FECMODIF,VDCORRSMTP.HORAMODIF "\
        " FROM VDCORRSMTP"\
        " WHERE "\
               " VDCORRSMTP.STATUS=:STATUS "\
              "  AND (NVL(FECPLANIF,0)=0 OR (VD.FECHASYS>FECPLANIF AND VD.HORASYS>FECPLANIF)) "
static v10cursors *vdselsmtpstatus;

#define SELSMTPVDCORRSMTP "SELECT VDCORRSMTP.ROWID,VDCORRSMTP.IDMSG,VDCORRSMTP.ORDENADOR, "\
                    " VDCORRSMTP.TIPOCORREO,VDCORRSMTP.CUENTA,VDCORRSMTP.PARA, "\
                    " VDCORRSMTP.CC,VDCORRSMTP.CCO,VDCORRSMTP.ASUNTO, "\
                    " VDCORRSMTP.CUERPO,VDCORRSMTP.ADJUNTO,VDCORRSMTP.PRIORIDAD, "\
                    " VDCORRSMTP.MIME,VDCORRSMTP.DIRECTORIO,VDCORRSMTP.FICHERO, "\
                    " VDCORRSMTP.STATUS,VDCORRSMTP.CODOPEINS,VDCORRSMTP.FECINS, "\
                    " VDCORRSMTP.HORAINS,VDCORRSMTP.MODULOINS,VDCORRSMTP.ACCIONINS, "\
                    " VDCORRSMTP.FECPLANIF,VDCORRSMTP.HORAPLANIF,VDCORRSMTP.FECENVIO, "\
                    " VDCORRSMTP.HORAENVIO,VDCORRSMTP.VDEXTRA,VDCORRSMTP.CODCOMEN, "\
                    " VDCORRSMTP.CODOPEMODIF,VDCORRSMTP.FECMODIF,VDCORRSMTP.HORAMODIF "\
        " FROM VDCORRSMTP"\
        " WHERE "\
               " VDCORRSMTP.IDMSG=:IDMSG "
static v10cursors *vdselsmtpvdcorrsmtp;

#define UPDASMTPENVIADO "UPDATE VDCORRSMTP SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS , "\
               " FECENVIO=:FECENVIO , "\
               " HORAENVIO=:HORAENVIO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdasmtpenviado;

static vdcorrsmtps svdcorrsmtp;

static diccols colvdcorrsmtp[]={
	{"ROWID",V10CADENA,(size_t)&svdcorrsmtp.rowid,sizeof(svdcorrsmtp.rowid)},
	{"IDMSG",V10LONG,(size_t)&svdcorrsmtp.idmsg,sizeof(svdcorrsmtp.idmsg)},
	{"ORDENADOR",V10CADENA,(size_t)&svdcorrsmtp.ordenador,sizeof(svdcorrsmtp.ordenador)},
	{"TIPOCORREO",V10CADENA,(size_t)&svdcorrsmtp.tipocorreo,sizeof(svdcorrsmtp.tipocorreo)},
	{"CUENTA",V10CADENA,(size_t)&svdcorrsmtp.cuenta,sizeof(svdcorrsmtp.cuenta)},
	{"PARA",V10CADENA,(size_t)&svdcorrsmtp.para,sizeof(svdcorrsmtp.para)},
	{"CC",V10CADENA,(size_t)&svdcorrsmtp.cc,sizeof(svdcorrsmtp.cc)},
	{"CCO",V10CADENA,(size_t)&svdcorrsmtp.cco,sizeof(svdcorrsmtp.cco)},
	{"ASUNTO",V10CADENA,(size_t)&svdcorrsmtp.asunto,sizeof(svdcorrsmtp.asunto)},
	{"CUERPO",V10CADENA,(size_t)&svdcorrsmtp.cuerpo,sizeof(svdcorrsmtp.cuerpo)},
	{"ADJUNTO",V10CADENA,(size_t)&svdcorrsmtp.adjunto,sizeof(svdcorrsmtp.adjunto)},
	{"PRIORIDAD",V10LONG,(size_t)&svdcorrsmtp.prioridad,sizeof(svdcorrsmtp.prioridad)},
	{"MIME",V10CADENA,(size_t)&svdcorrsmtp.mime,sizeof(svdcorrsmtp.mime)},
	{"DIRECTORIO",V10CADENA,(size_t)&svdcorrsmtp.directorio,sizeof(svdcorrsmtp.directorio)},
	{"FICHERO",V10CADENA,(size_t)&svdcorrsmtp.fichero,sizeof(svdcorrsmtp.fichero)},
	{"STATUS",V10LONG,(size_t)&svdcorrsmtp.status,sizeof(svdcorrsmtp.status)},
	{"CODOPEINS",V10CADENA,(size_t)&svdcorrsmtp.codopeins,sizeof(svdcorrsmtp.codopeins)},
	{"FECINS",V10LONG,(size_t)&svdcorrsmtp.fecins,sizeof(svdcorrsmtp.fecins)},
	{"HORAINS",V10CADENA,(size_t)&svdcorrsmtp.horains,sizeof(svdcorrsmtp.horains)},
	{"MODULOINS",V10CADENA,(size_t)&svdcorrsmtp.moduloins,sizeof(svdcorrsmtp.moduloins)},
	{"ACCIONINS",V10CADENA,(size_t)&svdcorrsmtp.accionins,sizeof(svdcorrsmtp.accionins)},
	{"FECPLANIF",V10LONG,(size_t)&svdcorrsmtp.fecplanif,sizeof(svdcorrsmtp.fecplanif)},
	{"HORAPLANIF",V10CADENA,(size_t)&svdcorrsmtp.horaplanif,sizeof(svdcorrsmtp.horaplanif)},
	{"FECENVIO",V10LONG,(size_t)&svdcorrsmtp.fecenvio,sizeof(svdcorrsmtp.fecenvio)},
	{"HORAENVIO",V10CADENA,(size_t)&svdcorrsmtp.horaenvio,sizeof(svdcorrsmtp.horaenvio)},
	{"VDEXTRA",V10CADENA,(size_t)&svdcorrsmtp.vdextra,sizeof(svdcorrsmtp.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdcorrsmtp.codcomen,sizeof(svdcorrsmtp.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdcorrsmtp.codopemodif,sizeof(svdcorrsmtp.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdcorrsmtp.fecmodif,sizeof(svdcorrsmtp.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdcorrsmtp.horamodif,sizeof(svdcorrsmtp.horamodif)},
	{"COMEN",V10CADENA,(size_t)&svdcorrsmtp.comen,sizeof(svdcorrsmtp.comen)}
	};
static diccionarios dvdcorrsmtp[]={
    {colvdcorrsmtp,31}
};
diccionario dsmtp={dvdcorrsmtp,1};

static char msglogSMTP[LCADENA];
static char msgdebugSMTP[LCADENABIG];
static int init=0;


static void fin_vd_smtp(void)
{
if (vdselsmtpstatus) {
    liberacursor(vdselsmtpstatus);
    vdselsmtpstatus = NULL;
}
if (vdselsmtpvdcorrsmtp) {
    liberacursor(vdselsmtpvdcorrsmtp);
    vdselsmtpvdcorrsmtp = NULL;
}
if (vdupdasmtpenviado) {
    liberacursor(vdupdasmtpenviado);
    vdupdasmtpenviado = NULL;
}
}
static void init_selsmtpstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcorrsmtp[0].numcol;nc++) dvdcorrsmtp[0].c[nc].offset-=(size_t)&svdcorrsmtp;
    vdselsmtpstatus=abrecursordebug(SELSMTPSTATUS,1280);
    definetodo(vdselsmtpstatus,svdcorrsmtp.rowid,sizeof(svdcorrsmtp.rowid),V10CADENA,
                          &svdcorrsmtp.idmsg,sizeof(svdcorrsmtp.idmsg),V10LONG,
                          svdcorrsmtp.ordenador,sizeof(svdcorrsmtp.ordenador),V10CADENA,
                          svdcorrsmtp.tipocorreo,sizeof(svdcorrsmtp.tipocorreo),V10CADENA,
                          svdcorrsmtp.cuenta,sizeof(svdcorrsmtp.cuenta),V10CADENA,
                          svdcorrsmtp.para,sizeof(svdcorrsmtp.para),V10CADENA,
                          svdcorrsmtp.cc,sizeof(svdcorrsmtp.cc),V10CADENA,
                          svdcorrsmtp.cco,sizeof(svdcorrsmtp.cco),V10CADENA,
                          svdcorrsmtp.asunto,sizeof(svdcorrsmtp.asunto),V10CADENA,
                          svdcorrsmtp.cuerpo,sizeof(svdcorrsmtp.cuerpo),V10CADENA,
                          svdcorrsmtp.adjunto,sizeof(svdcorrsmtp.adjunto),V10CADENA,
                          &svdcorrsmtp.prioridad,sizeof(svdcorrsmtp.prioridad),V10LONG,
                          svdcorrsmtp.mime,sizeof(svdcorrsmtp.mime),V10CADENA,
                          svdcorrsmtp.directorio,sizeof(svdcorrsmtp.directorio),V10CADENA,
                          svdcorrsmtp.fichero,sizeof(svdcorrsmtp.fichero),V10CADENA,
                          &svdcorrsmtp.status,sizeof(svdcorrsmtp.status),V10LONG,
                          svdcorrsmtp.codopeins,sizeof(svdcorrsmtp.codopeins),V10CADENA,
                          &svdcorrsmtp.fecins,sizeof(svdcorrsmtp.fecins),V10LONG,
                          svdcorrsmtp.horains,sizeof(svdcorrsmtp.horains),V10CADENA,
                          svdcorrsmtp.moduloins,sizeof(svdcorrsmtp.moduloins),V10CADENA,
                          svdcorrsmtp.accionins,sizeof(svdcorrsmtp.accionins),V10CADENA,
                          &svdcorrsmtp.fecplanif,sizeof(svdcorrsmtp.fecplanif),V10LONG,
                          svdcorrsmtp.horaplanif,sizeof(svdcorrsmtp.horaplanif),V10CADENA,
                          &svdcorrsmtp.fecenvio,sizeof(svdcorrsmtp.fecenvio),V10LONG,
                          svdcorrsmtp.horaenvio,sizeof(svdcorrsmtp.horaenvio),V10CADENA,
                          svdcorrsmtp.vdextra,sizeof(svdcorrsmtp.vdextra),V10CADENA,
                          &svdcorrsmtp.codcomen,sizeof(svdcorrsmtp.codcomen),V10LONG,
                          svdcorrsmtp.codopemodif,sizeof(svdcorrsmtp.codopemodif),V10CADENA,
                          &svdcorrsmtp.fecmodif,sizeof(svdcorrsmtp.fecmodif),V10LONG,
                          svdcorrsmtp.horamodif,sizeof(svdcorrsmtp.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselsmtpstatus,"STATUS",&svdcorrsmtp.status,sizeof(svdcorrsmtp.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_smtp);
        init = 1;
    }
}

static void init_selsmtpvdcorrsmtp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcorrsmtp[0].numcol;nc++) dvdcorrsmtp[0].c[nc].offset-=(size_t)&svdcorrsmtp;
    vdselsmtpvdcorrsmtp=abrecursordebug(SELSMTPVDCORRSMTP,1280);
    definetodo(vdselsmtpvdcorrsmtp,svdcorrsmtp.rowid,sizeof(svdcorrsmtp.rowid),V10CADENA,
                          &svdcorrsmtp.idmsg,sizeof(svdcorrsmtp.idmsg),V10LONG,
                          svdcorrsmtp.ordenador,sizeof(svdcorrsmtp.ordenador),V10CADENA,
                          svdcorrsmtp.tipocorreo,sizeof(svdcorrsmtp.tipocorreo),V10CADENA,
                          svdcorrsmtp.cuenta,sizeof(svdcorrsmtp.cuenta),V10CADENA,
                          svdcorrsmtp.para,sizeof(svdcorrsmtp.para),V10CADENA,
                          svdcorrsmtp.cc,sizeof(svdcorrsmtp.cc),V10CADENA,
                          svdcorrsmtp.cco,sizeof(svdcorrsmtp.cco),V10CADENA,
                          svdcorrsmtp.asunto,sizeof(svdcorrsmtp.asunto),V10CADENA,
                          svdcorrsmtp.cuerpo,sizeof(svdcorrsmtp.cuerpo),V10CADENA,
                          svdcorrsmtp.adjunto,sizeof(svdcorrsmtp.adjunto),V10CADENA,
                          &svdcorrsmtp.prioridad,sizeof(svdcorrsmtp.prioridad),V10LONG,
                          svdcorrsmtp.mime,sizeof(svdcorrsmtp.mime),V10CADENA,
                          svdcorrsmtp.directorio,sizeof(svdcorrsmtp.directorio),V10CADENA,
                          svdcorrsmtp.fichero,sizeof(svdcorrsmtp.fichero),V10CADENA,
                          &svdcorrsmtp.status,sizeof(svdcorrsmtp.status),V10LONG,
                          svdcorrsmtp.codopeins,sizeof(svdcorrsmtp.codopeins),V10CADENA,
                          &svdcorrsmtp.fecins,sizeof(svdcorrsmtp.fecins),V10LONG,
                          svdcorrsmtp.horains,sizeof(svdcorrsmtp.horains),V10CADENA,
                          svdcorrsmtp.moduloins,sizeof(svdcorrsmtp.moduloins),V10CADENA,
                          svdcorrsmtp.accionins,sizeof(svdcorrsmtp.accionins),V10CADENA,
                          &svdcorrsmtp.fecplanif,sizeof(svdcorrsmtp.fecplanif),V10LONG,
                          svdcorrsmtp.horaplanif,sizeof(svdcorrsmtp.horaplanif),V10CADENA,
                          &svdcorrsmtp.fecenvio,sizeof(svdcorrsmtp.fecenvio),V10LONG,
                          svdcorrsmtp.horaenvio,sizeof(svdcorrsmtp.horaenvio),V10CADENA,
                          svdcorrsmtp.vdextra,sizeof(svdcorrsmtp.vdextra),V10CADENA,
                          &svdcorrsmtp.codcomen,sizeof(svdcorrsmtp.codcomen),V10LONG,
                          svdcorrsmtp.codopemodif,sizeof(svdcorrsmtp.codopemodif),V10CADENA,
                          &svdcorrsmtp.fecmodif,sizeof(svdcorrsmtp.fecmodif),V10LONG,
                          svdcorrsmtp.horamodif,sizeof(svdcorrsmtp.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselsmtpvdcorrsmtp,"IDMSG",&svdcorrsmtp.idmsg,sizeof(svdcorrsmtp.idmsg),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_smtp);
        init = 1;
    }
}

static void init_updasmtpenviado(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcorrsmtp[0].numcol;nc++) dvdcorrsmtp[0].c[nc].offset-=(size_t)&svdcorrsmtp;
    vdupdasmtpenviado=abrecursordebug(UPDASMTPENVIADO,1280);
    bindtodo(vdupdasmtpenviado,"STATUS",&svdcorrsmtp.status,sizeof(svdcorrsmtp.status),V10LONG,
                          "FECENVIO",&svdcorrsmtp.fecenvio,sizeof(svdcorrsmtp.fecenvio),V10LONG,
                          "HORAENVIO",svdcorrsmtp.horaenvio,sizeof(svdcorrsmtp.horaenvio),V10CADENA,
                          "MIROWID",svdcorrsmtp.rowid,sizeof(svdcorrsmtp.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_smtp);
        init = 1;
    }
}

diccionario *SMTPdamediccionario(void)
{
     return(&dsmtp);
}

int SMTPbuscastatus(long status,vdcorrsmtps *smtp)
{
  int vdret;
  memset(&svdcorrsmtp,0,sizeof(svdcorrsmtp));
  svdcorrsmtp.status=status;
  if (vdselsmtpstatus==NULL) init_selsmtpstatus();
  vdret=ejefetchcursor(vdselsmtpstatus);
  if (vdret==0) {
     *smtp=svdcorrsmtp;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselsmtpstatus. vdret %d. \n",SMTPlog(&svdcorrsmtp),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int SMTPnextstatus(vdcorrsmtps *smtp)
{
  int vdret;
  vdret=fetchcursor(vdselsmtpstatus);
  if (vdret==0) {
     *smtp=svdcorrsmtp;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselsmtpstatus. vdret %d. \n",SMTPlog(&svdcorrsmtp),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselsmtpstatus);
  return(VD_EERRORACLE);
}

int SMTPselvdcorrsmtp(long idmsg,vdcorrsmtps *smtp)
{
  int vdret;
  if (vdselsmtpvdcorrsmtp==NULL) init_selsmtpvdcorrsmtp();
  memset(&svdcorrsmtp,0,sizeof(svdcorrsmtp));
  svdcorrsmtp.idmsg=idmsg;
  vdret=ejefetchcursor(vdselsmtpvdcorrsmtp);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselsmtpvdcorrsmtp. vdret %d. \n",SMTPlog(&svdcorrsmtp),vdret);
    return(VD_EERRORACLE);
   }
  *smtp=svdcorrsmtp;
  return(vdret);
}

int SMTPactualizaenviado(vdcorrsmtps *smtp,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando SMTPactualizaenviado:  %s .  \n",SMTPlog(&svdcorrsmtp));
  if (vdupdasmtpenviado==NULL) init_updasmtpenviado();
  svdcorrsmtp=*smtp;
  vdret=ejecutacursor(vdupdasmtpenviado);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdasmtpenviado);
     getcurerrornombre(vdupdasmtpenviado->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdasmtpenviado)!=1) return(VD_EERRORACLE);
  return(0);
}

char * SMTPlog(vdcorrsmtps *smtp)
{
    sprintf(msglogSMTP, "VDCORRSMTP: idmsg %ld ",smtp->idmsg);
    return(msglogSMTP);
}

char * SMTPdebug(vdcorrsmtps *smtp)
{
    debugestruct(&dsmtp,smtp,msgdebugSMTP);
    return(msgdebugSMTP);
}

