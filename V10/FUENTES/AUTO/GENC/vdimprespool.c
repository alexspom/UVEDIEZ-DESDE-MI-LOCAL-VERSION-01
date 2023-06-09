// Modulo generado automaticamente a partir de VDIMPRESPOOL.DEF
//#***
//# VDIMPRESPOOL.c - Generaci�n autom�tica del c�digo c para la tabla de spool/cola de impresiones                                                 
//# 
//# Prop�sito: Funciones de acceso a la tabla VDIMPRESPOOL
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 07-06-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=IMSP
//EXTRA=GRUPOIMPRE,V10CADENA,15
//EXTRA=COMENTARIO,V10CADENA,512
//
//SECUENCIA=VDSECIMPRESPOOL,SEQIMPRE
//RECORRE=PENDIENTE;WHERE=STATUS=:STATUS AND CODIMPRE IN (SELECT CODIMPRE FROM VDIMPRESORAS IMPR, VDIMPREGRUPO IMGR WHERE  
//                                                               IMGR.GRUPOIMPRE = IMPR.GRUPOIMPRE AND 
//                                                               IMGR.ACTIVO='S' AND 
//                                                               IMPR.ACTIVO='S' AND 
//                                                               IMGR.GRUPOIMPRE=:GRUPOIMPRE) 
//                                        AND (NVL(FECPLANIF,0)=0 OR (FECPLANIF>=VD.FECHASYS AND HORAPLANIF>=VD.HORASYS));ORDERBY=PRIORIDAD,SEQIMPRE;
//UPDATE=IMPRESO,STATUS,FECIMP,HORAIMP;
//UPDATE=DOCUMENTO,STATUS,DOCUMENTO;
//INSERT

#include "vd.h"
#define SELIMSPPENDIENTE "SELECT VDIMPRESPOOL.ROWID,VDIMPRESPOOL.SEQIMPRE,VDIMPRESPOOL.ORDENADOR, "\
                    " VDIMPRESPOOL.TIPOIMPRE,VDIMPRESPOOL.CODIMPRE,VDIMPRESPOOL.FICHERO, "\
                    " VDIMPRESPOOL.DOCUMENTO,VDIMPRESPOOL.PARAMS,VDIMPRESPOOL.NUMCOPIAS, "\
                    " VDIMPRESPOOL.PRIORIDAD,VDIMPRESPOOL.STATUS,VDIMPRESPOOL.CODOPEINS, "\
                    " VDIMPRESPOOL.FECINS,VDIMPRESPOOL.HORAINS,VDIMPRESPOOL.FECPLANIF, "\
                    " VDIMPRESPOOL.HORAPLANIF,VDIMPRESPOOL.FECIMP,VDIMPRESPOOL.HORAIMP, "\
                    " VDIMPRESPOOL.IMPPROGRAMA,VDIMPRESPOOL.IMPMODULO,VDIMPRESPOOL.IMPACCION, "\
                    " VDIMPRESPOOL.VDEXTRA,VDIMPRESPOOL.CODCOMEN,VDIMPRESPOOL.CODOPEMODIF, "\
                    " VDIMPRESPOOL.FECMODIF,VDIMPRESPOOL.HORAMODIF "\
        " FROM VDIMPRESPOOL"\
        " WHERE "\
              " STATUS=:STATUS AND CODIMPRE IN (SELECT CODIMPRE FROM VDIMPRESORAS IMPR, VDIMPREGRUPO IMGR WHERE   IMGR.GRUPOIMPRE = IMPR.GRUPOIMPRE AND  IMGR.ACTIVO='S' AND  IMPR.ACTIVO='S' AND  IMGR.GRUPOIMPRE=:GRUPOIMPRE)  AND (NVL(FECPLANIF,0)=0 OR (FECPLANIF>=VD.FECHASYS AND HORAPLANIF>=VD.HORASYS)) "\
        " ORDER BY PRIORIDAD,SEQIMPRE "
static v10cursors *vdselimsppendiente;

#define SELIMSPVDIMPRESPOOL "SELECT VDIMPRESPOOL.ROWID,VDIMPRESPOOL.SEQIMPRE,VDIMPRESPOOL.ORDENADOR, "\
                    " VDIMPRESPOOL.TIPOIMPRE,VDIMPRESPOOL.CODIMPRE,VDIMPRESPOOL.FICHERO, "\
                    " VDIMPRESPOOL.DOCUMENTO,VDIMPRESPOOL.PARAMS,VDIMPRESPOOL.NUMCOPIAS, "\
                    " VDIMPRESPOOL.PRIORIDAD,VDIMPRESPOOL.STATUS,VDIMPRESPOOL.CODOPEINS, "\
                    " VDIMPRESPOOL.FECINS,VDIMPRESPOOL.HORAINS,VDIMPRESPOOL.FECPLANIF, "\
                    " VDIMPRESPOOL.HORAPLANIF,VDIMPRESPOOL.FECIMP,VDIMPRESPOOL.HORAIMP, "\
                    " VDIMPRESPOOL.IMPPROGRAMA,VDIMPRESPOOL.IMPMODULO,VDIMPRESPOOL.IMPACCION, "\
                    " VDIMPRESPOOL.VDEXTRA,VDIMPRESPOOL.CODCOMEN,VDIMPRESPOOL.CODOPEMODIF, "\
                    " VDIMPRESPOOL.FECMODIF,VDIMPRESPOOL.HORAMODIF "\
        " FROM VDIMPRESPOOL"\
        " WHERE "\
               " VDIMPRESPOOL.SEQIMPRE=:SEQIMPRE "
static v10cursors *vdselimspvdimprespool;

#define UPDAIMSPIMPRESO "UPDATE VDIMPRESPOOL SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS , "\
               " FECIMP=:FECIMP , "\
               " HORAIMP=:HORAIMP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaimspimpreso;

#define UPDAIMSPDOCUMENTO "UPDATE VDIMPRESPOOL SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS , "\
               " DOCUMENTO=:DOCUMENTO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaimspdocumento;

#define SELVDSECIMPRESPOOL "SELECT VDSECIMPRESPOOL.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecimprespool;

#define INSIMSP "INSERT INTO VDIMPRESPOOL (SEQIMPRE,ORDENADOR,TIPOIMPRE,CODIMPRE,FICHERO,DOCUMENTO, "\
                    " PARAMS,NUMCOPIAS,PRIORIDAD,STATUS,CODOPEINS,FECINS,HORAINS, "\
                    " FECPLANIF,HORAPLANIF,FECIMP,HORAIMP,IMPPROGRAMA,IMPMODULO,IMPACCION, "\
                    " VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :SEQIMPRE,:ORDENADOR,:TIPOIMPRE,:CODIMPRE,:FICHERO,:DOCUMENTO, "\
                    " :PARAMS,:NUMCOPIAS,:PRIORIDAD,:STATUS,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS, "\
                    " :FECPLANIF,:HORAPLANIF,:FECIMP,:HORAIMP,:IMPPROGRAMA,:IMPMODULO,:IMPACCION, "\
                    " :VDEXTRA,:CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS) "
static v10cursors *vdinsimsp;

static vdimprespools svdimprespool;

static diccols colvdimprespool[]={
	{"ROWID",V10CADENA,(size_t)&svdimprespool.rowid,sizeof(svdimprespool.rowid)},
	{"SEQIMPRE",V10LONG,(size_t)&svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre)},
	{"ORDENADOR",V10CADENA,(size_t)&svdimprespool.ordenador,sizeof(svdimprespool.ordenador)},
	{"TIPOIMPRE",V10CADENA,(size_t)&svdimprespool.tipoimpre,sizeof(svdimprespool.tipoimpre)},
	{"CODIMPRE",V10CADENA,(size_t)&svdimprespool.codimpre,sizeof(svdimprespool.codimpre)},
	{"FICHERO",V10CADENA,(size_t)&svdimprespool.fichero,sizeof(svdimprespool.fichero)},
	{"DOCUMENTO",V10CADENA,(size_t)&svdimprespool.documento,sizeof(svdimprespool.documento)},
	{"PARAMS",V10CADENA,(size_t)&svdimprespool.params,sizeof(svdimprespool.params)},
	{"NUMCOPIAS",V10LONG,(size_t)&svdimprespool.numcopias,sizeof(svdimprespool.numcopias)},
	{"PRIORIDAD",V10LONG,(size_t)&svdimprespool.prioridad,sizeof(svdimprespool.prioridad)},
	{"STATUS",V10LONG,(size_t)&svdimprespool.status,sizeof(svdimprespool.status)},
	{"CODOPEINS",V10CADENA,(size_t)&svdimprespool.codopeins,sizeof(svdimprespool.codopeins)},
	{"FECINS",V10LONG,(size_t)&svdimprespool.fecins,sizeof(svdimprespool.fecins)},
	{"HORAINS",V10CADENA,(size_t)&svdimprespool.horains,sizeof(svdimprespool.horains)},
	{"FECPLANIF",V10LONG,(size_t)&svdimprespool.fecplanif,sizeof(svdimprespool.fecplanif)},
	{"HORAPLANIF",V10CADENA,(size_t)&svdimprespool.horaplanif,sizeof(svdimprespool.horaplanif)},
	{"FECIMP",V10LONG,(size_t)&svdimprespool.fecimp,sizeof(svdimprespool.fecimp)},
	{"HORAIMP",V10CADENA,(size_t)&svdimprespool.horaimp,sizeof(svdimprespool.horaimp)},
	{"IMPPROGRAMA",V10CADENA,(size_t)&svdimprespool.impprograma,sizeof(svdimprespool.impprograma)},
	{"IMPMODULO",V10CADENA,(size_t)&svdimprespool.impmodulo,sizeof(svdimprespool.impmodulo)},
	{"IMPACCION",V10CADENA,(size_t)&svdimprespool.impaccion,sizeof(svdimprespool.impaccion)},
	{"VDEXTRA",V10CADENA,(size_t)&svdimprespool.vdextra,sizeof(svdimprespool.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdimprespool.codcomen,sizeof(svdimprespool.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdimprespool.codopemodif,sizeof(svdimprespool.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdimprespool.fecmodif,sizeof(svdimprespool.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdimprespool.horamodif,sizeof(svdimprespool.horamodif)},
	{"GRUPOIMPRE",V10CADENA,(size_t)&svdimprespool.grupoimpre,sizeof(svdimprespool.grupoimpre)},
	{"COMENTARIO",V10CADENA,(size_t)&svdimprespool.comentario,sizeof(svdimprespool.comentario)}
	};
static diccionarios dvdimprespool[]={
    {colvdimprespool,28}
};
diccionario dimsp={dvdimprespool,1};

static char msglogIMSP[LCADENA];
static char msgdebugIMSP[LCADENABIG];
static int init=0;


static void fin_vd_imsp(void)
{
if (vdselimsppendiente) {
    liberacursor(vdselimsppendiente);
    vdselimsppendiente = NULL;
}
if (vdselimspvdimprespool) {
    liberacursor(vdselimspvdimprespool);
    vdselimspvdimprespool = NULL;
}
if (vdupdaimspimpreso) {
    liberacursor(vdupdaimspimpreso);
    vdupdaimspimpreso = NULL;
}
if (vdupdaimspdocumento) {
    liberacursor(vdupdaimspdocumento);
    vdupdaimspdocumento = NULL;
}
if (vdselvdsecimprespool != NULL) {
    liberacursor(vdselvdsecimprespool);
    vdselvdsecimprespool = NULL;
}
if (vdinsimsp != NULL) {
    liberacursor(vdinsimsp);
    vdinsimsp = NULL;
}
}
static void init_selimsppendiente(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdselimsppendiente=abrecursordebug(SELIMSPPENDIENTE,0);
    definetodo(vdselimsppendiente,svdimprespool.rowid,sizeof(svdimprespool.rowid),V10CADENA,
                          &svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre),V10LONG,
                          svdimprespool.ordenador,sizeof(svdimprespool.ordenador),V10CADENA,
                          svdimprespool.tipoimpre,sizeof(svdimprespool.tipoimpre),V10CADENA,
                          svdimprespool.codimpre,sizeof(svdimprespool.codimpre),V10CADENA,
                          svdimprespool.fichero,sizeof(svdimprespool.fichero),V10CADENA,
                          svdimprespool.documento,sizeof(svdimprespool.documento),V10CADENA,
                          svdimprespool.params,sizeof(svdimprespool.params),V10CADENA,
                          &svdimprespool.numcopias,sizeof(svdimprespool.numcopias),V10LONG,
                          &svdimprespool.prioridad,sizeof(svdimprespool.prioridad),V10LONG,
                          &svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          svdimprespool.codopeins,sizeof(svdimprespool.codopeins),V10CADENA,
                          &svdimprespool.fecins,sizeof(svdimprespool.fecins),V10LONG,
                          svdimprespool.horains,sizeof(svdimprespool.horains),V10CADENA,
                          &svdimprespool.fecplanif,sizeof(svdimprespool.fecplanif),V10LONG,
                          svdimprespool.horaplanif,sizeof(svdimprespool.horaplanif),V10CADENA,
                          &svdimprespool.fecimp,sizeof(svdimprespool.fecimp),V10LONG,
                          svdimprespool.horaimp,sizeof(svdimprespool.horaimp),V10CADENA,
                          svdimprespool.impprograma,sizeof(svdimprespool.impprograma),V10CADENA,
                          svdimprespool.impmodulo,sizeof(svdimprespool.impmodulo),V10CADENA,
                          svdimprespool.impaccion,sizeof(svdimprespool.impaccion),V10CADENA,
                          svdimprespool.vdextra,sizeof(svdimprespool.vdextra),V10CADENA,
                          &svdimprespool.codcomen,sizeof(svdimprespool.codcomen),V10LONG,
                          svdimprespool.codopemodif,sizeof(svdimprespool.codopemodif),V10CADENA,
                          &svdimprespool.fecmodif,sizeof(svdimprespool.fecmodif),V10LONG,
                          svdimprespool.horamodif,sizeof(svdimprespool.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselimsppendiente,"STATUS",&svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          "GRUPOIMPRE",svdimprespool.grupoimpre,sizeof(svdimprespool.grupoimpre),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

static void init_selimspvdimprespool(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdselimspvdimprespool=abrecursordebug(SELIMSPVDIMPRESPOOL,1280);
    definetodo(vdselimspvdimprespool,svdimprespool.rowid,sizeof(svdimprespool.rowid),V10CADENA,
                          &svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre),V10LONG,
                          svdimprespool.ordenador,sizeof(svdimprespool.ordenador),V10CADENA,
                          svdimprespool.tipoimpre,sizeof(svdimprespool.tipoimpre),V10CADENA,
                          svdimprespool.codimpre,sizeof(svdimprespool.codimpre),V10CADENA,
                          svdimprespool.fichero,sizeof(svdimprespool.fichero),V10CADENA,
                          svdimprespool.documento,sizeof(svdimprespool.documento),V10CADENA,
                          svdimprespool.params,sizeof(svdimprespool.params),V10CADENA,
                          &svdimprespool.numcopias,sizeof(svdimprespool.numcopias),V10LONG,
                          &svdimprespool.prioridad,sizeof(svdimprespool.prioridad),V10LONG,
                          &svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          svdimprespool.codopeins,sizeof(svdimprespool.codopeins),V10CADENA,
                          &svdimprespool.fecins,sizeof(svdimprespool.fecins),V10LONG,
                          svdimprespool.horains,sizeof(svdimprespool.horains),V10CADENA,
                          &svdimprespool.fecplanif,sizeof(svdimprespool.fecplanif),V10LONG,
                          svdimprespool.horaplanif,sizeof(svdimprespool.horaplanif),V10CADENA,
                          &svdimprespool.fecimp,sizeof(svdimprespool.fecimp),V10LONG,
                          svdimprespool.horaimp,sizeof(svdimprespool.horaimp),V10CADENA,
                          svdimprespool.impprograma,sizeof(svdimprespool.impprograma),V10CADENA,
                          svdimprespool.impmodulo,sizeof(svdimprespool.impmodulo),V10CADENA,
                          svdimprespool.impaccion,sizeof(svdimprespool.impaccion),V10CADENA,
                          svdimprespool.vdextra,sizeof(svdimprespool.vdextra),V10CADENA,
                          &svdimprespool.codcomen,sizeof(svdimprespool.codcomen),V10LONG,
                          svdimprespool.codopemodif,sizeof(svdimprespool.codopemodif),V10CADENA,
                          &svdimprespool.fecmodif,sizeof(svdimprespool.fecmodif),V10LONG,
                          svdimprespool.horamodif,sizeof(svdimprespool.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselimspvdimprespool,"SEQIMPRE",&svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

static void init_updaimspimpreso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdupdaimspimpreso=abrecursordebug(UPDAIMSPIMPRESO,1280);
    bindtodo(vdupdaimspimpreso,"STATUS",&svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          "FECIMP",&svdimprespool.fecimp,sizeof(svdimprespool.fecimp),V10LONG,
                          "HORAIMP",svdimprespool.horaimp,sizeof(svdimprespool.horaimp),V10CADENA,
                          "MIROWID",svdimprespool.rowid,sizeof(svdimprespool.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

static void init_updaimspdocumento(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdupdaimspdocumento=abrecursordebug(UPDAIMSPDOCUMENTO,1280);
    bindtodo(vdupdaimspdocumento,"STATUS",&svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          "DOCUMENTO",svdimprespool.documento,sizeof(svdimprespool.documento),V10CADENA,
                          "MIROWID",svdimprespool.rowid,sizeof(svdimprespool.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

static void init_selvdsecimprespool(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdselvdsecimprespool=abrecursordebug(SELVDSECIMPRESPOOL,1280);
    definetodo(vdselvdsecimprespool,&svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

static void init_insimsp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdimprespool[0].numcol;nc++) dvdimprespool[0].c[nc].offset-=(size_t)&svdimprespool;
    vdinsimsp=abrecursordebug(INSIMSP,1280);
    bindtodo(vdinsimsp,"SEQIMPRE",&svdimprespool.seqimpre,sizeof(svdimprespool.seqimpre),V10LONG,
                          "ORDENADOR",svdimprespool.ordenador,sizeof(svdimprespool.ordenador),V10CADENA,
                          "TIPOIMPRE",svdimprespool.tipoimpre,sizeof(svdimprespool.tipoimpre),V10CADENA,
                          "CODIMPRE",svdimprespool.codimpre,sizeof(svdimprespool.codimpre),V10CADENA,
                          "FICHERO",svdimprespool.fichero,sizeof(svdimprespool.fichero),V10CADENA,
                          "DOCUMENTO",svdimprespool.documento,sizeof(svdimprespool.documento),V10CADENA,
                          "PARAMS",svdimprespool.params,sizeof(svdimprespool.params),V10CADENA,
                          "NUMCOPIAS",&svdimprespool.numcopias,sizeof(svdimprespool.numcopias),V10LONG,
                          "PRIORIDAD",&svdimprespool.prioridad,sizeof(svdimprespool.prioridad),V10LONG,
                          "STATUS",&svdimprespool.status,sizeof(svdimprespool.status),V10LONG,
                          "FECPLANIF",&svdimprespool.fecplanif,sizeof(svdimprespool.fecplanif),V10LONG,
                          "HORAPLANIF",svdimprespool.horaplanif,sizeof(svdimprespool.horaplanif),V10CADENA,
                          "FECIMP",&svdimprespool.fecimp,sizeof(svdimprespool.fecimp),V10LONG,
                          "HORAIMP",svdimprespool.horaimp,sizeof(svdimprespool.horaimp),V10CADENA,
                          "IMPPROGRAMA",svdimprespool.impprograma,sizeof(svdimprespool.impprograma),V10CADENA,
                          "IMPMODULO",svdimprespool.impmodulo,sizeof(svdimprespool.impmodulo),V10CADENA,
                          "IMPACCION",svdimprespool.impaccion,sizeof(svdimprespool.impaccion),V10CADENA,
                          "VDEXTRA",svdimprespool.vdextra,sizeof(svdimprespool.vdextra),V10CADENA,
                          "CODCOMEN",&svdimprespool.codcomen,sizeof(svdimprespool.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_imsp);
        init = 1;
    }
}

diccionario *IMSPdamediccionario(void)
{
     return(&dimsp);
}

int IMSPbuscapendiente(long status,char *grupoimpre,vdimprespools *imsp)
{
  int vdret;
  memset(&svdimprespool,0,sizeof(svdimprespool));
  svdimprespool.status=status;
  strcpy(svdimprespool.grupoimpre,grupoimpre);
  if (vdselimsppendiente==NULL) init_selimsppendiente();
  vdret=ejefetchcursor(vdselimsppendiente);
  if (vdret==0) {
     *imsp=svdimprespool;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselimsppendiente. vdret %d. \n",IMSPlog(&svdimprespool),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int IMSPnextpendiente(vdimprespools *imsp)
{
  int vdret;
  vdret=fetchcursor(vdselimsppendiente);
  if (vdret==0) {
     *imsp=svdimprespool;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselimsppendiente. vdret %d. \n",IMSPlog(&svdimprespool),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselimsppendiente);
  return(VD_EERRORACLE);
}

int IMSPselvdimprespool(long seqimpre,vdimprespools *imsp)
{
  int vdret;
  if (vdselimspvdimprespool==NULL) init_selimspvdimprespool();
  memset(&svdimprespool,0,sizeof(svdimprespool));
  svdimprespool.seqimpre=seqimpre;
  vdret=ejefetchcursor(vdselimspvdimprespool);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselimspvdimprespool. vdret %d. \n",IMSPlog(&svdimprespool),vdret);
    return(VD_EERRORACLE);
   }
  *imsp=svdimprespool;
  return(vdret);
}

int IMSPactualizaimpreso(vdimprespools *imsp,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IMSPactualizaimpreso:  %s .  \n",IMSPlog(&svdimprespool));
  if (vdupdaimspimpreso==NULL) init_updaimspimpreso();
  svdimprespool=*imsp;
  vdret=ejecutacursor(vdupdaimspimpreso);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaimspimpreso);
     getcurerrornombre(vdupdaimspimpreso->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaimspimpreso)!=1) return(VD_EERRORACLE);
  return(0);
}

int IMSPactualizadocumento(vdimprespools *imsp,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando IMSPactualizadocumento:  %s .  \n",IMSPlog(&svdimprespool));
  if (vdupdaimspdocumento==NULL) init_updaimspdocumento();
  svdimprespool=*imsp;
  vdret=ejecutacursor(vdupdaimspdocumento);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaimspdocumento);
     getcurerrornombre(vdupdaimspdocumento->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaimspdocumento)!=1) return(VD_EERRORACLE);
  return(0);
}

int IMSPselvdsecimprespool(long *donde)
{
  int vdret;
  if (!vdselvdsecimprespool) init_selvdsecimprespool();
  vdret=ejefetchcursor(vdselvdsecimprespool);
  if (!vdret) {
     *donde=svdimprespool.seqimpre;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int IMSPinsert(vdimprespools *imsp,int error)
{
  int vdret;
  if (!vdinsimsp) init_insimsp();
  if (!imsp->seqimpre) {
     if ((vdret=IMSPselvdsecimprespool(&(imsp->seqimpre)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",IMSPlog(&svdimprespool));
  svdimprespool=*imsp;
  vdret=ejecutacursor(vdinsimsp);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsimsp);
     getcurerrornombre(vdinsimsp->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * IMSPlog(vdimprespools *imsp)
{
    sprintf(msglogIMSP, "VDIMPRESPOOL: seqimpre %ld ",imsp->seqimpre);
    return(msglogIMSP);
}

char * IMSPdebug(vdimprespools *imsp)
{
    debugestruct(&dimsp,imsp,msgdebugIMSP);
    return(msgdebugIMSP);
}

