// Modulo generado automaticamente a partir de VDINTERFCARGALIN.DEF
//#***
//# VDINTERFCARGALIN.c - Generaci�n autom�tica del c�digo c para la tabla de los registros 
//#                     de las interfases                                                 
//# 
//# Prop�sito: Funciones de acceso a la tabla VDINTERFCARGALIN
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 25-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=ICL
//
//EXTRA=STATUSCAB,V10LONG
//
//RECORRE=BUSCAREG, TIPOINTERFASE, FORMATO, STATUS,TABLE=VDINTERFCARGACAB;WHERE=VDINTERFCARGALIN.CODINTERFASE = VDINTERFCARGACAB.CODINTERFASE AND VDINTERFCARGACAB.STATUS = :STATUSCAB 
//                                                   AND VDINTERFCARGACAB.TIPOINTERFASE NOT IN (SELECT TIPOINTERFASE FROM VDINTERFCARGACAB
//                                                  WHERE STATUS = (-1)*:STATUSCAB);ORDERBY=VDINTERFCARGALIN.CODINTERFASE,VDINTERFCARGALIN.NUMREG;
//
//RECORRE=CODINTERFASE,CODINTERFASE;ORDERBY=NUMREG;
//
//CLAVE=NUMLINEAS,CODINTERFASE,GENCOUNT=NUMREG;
//
//UPDATE=STMSG,STATUS,MENSAJE
//
//INSERT 
//DELETE
//

#include "vd.h"
#define SELICLBUSCAREG "SELECT VDINTERFCARGALIN.ROWID,VDINTERFCARGALIN.CODINTERFASE,VDINTERFCARGALIN.TIPOINTERFASE, "\
                    " VDINTERFCARGALIN.FORMATO,VDINTERFCARGALIN.NUMREG,VDINTERFCARGALIN.REGISTRO, "\
                    " VDINTERFCARGALIN.MENSAJE,VDINTERFCARGALIN.STATUS,VDINTERFCARGALIN.VDEXTRA, "\
                    " VDINTERFCARGALIN.CODOPEMODIF,VDINTERFCARGALIN.FECMODIF,VDINTERFCARGALIN.HORAMODIF, "\
                    " VDINTERFCARGALIN.CODCOMEN "\
        " FROM VDINTERFCARGALIN ,VDINTERFCARGACAB"\
        " WHERE "\
               " VDINTERFCARGALIN.TIPOINTERFASE=:TIPOINTERFASE "\
               " AND VDINTERFCARGALIN.FORMATO=:FORMATO "\
               " AND VDINTERFCARGALIN.STATUS=:STATUS "\
              "  AND VDINTERFCARGALIN.CODINTERFASE = VDINTERFCARGACAB.CODINTERFASE AND VDINTERFCARGACAB.STATUS = :STATUSCAB  AND VDINTERFCARGACAB.TIPOINTERFASE NOT IN (SELECT TIPOINTERFASE FROM VDINTERFCARGACAB WHERE STATUS = (-1)*:STATUSCAB) "\
        " ORDER BY VDINTERFCARGALIN.CODINTERFASE,VDINTERFCARGALIN.NUMREG "
static v10cursors *vdseliclbuscareg;

#define SELICLCODINTERFASE "SELECT VDINTERFCARGALIN.ROWID,VDINTERFCARGALIN.CODINTERFASE,VDINTERFCARGALIN.TIPOINTERFASE, "\
                    " VDINTERFCARGALIN.FORMATO,VDINTERFCARGALIN.NUMREG,VDINTERFCARGALIN.REGISTRO, "\
                    " VDINTERFCARGALIN.MENSAJE,VDINTERFCARGALIN.STATUS,VDINTERFCARGALIN.VDEXTRA, "\
                    " VDINTERFCARGALIN.CODOPEMODIF,VDINTERFCARGALIN.FECMODIF,VDINTERFCARGALIN.HORAMODIF, "\
                    " VDINTERFCARGALIN.CODCOMEN "\
        " FROM VDINTERFCARGALIN"\
        " WHERE "\
               " VDINTERFCARGALIN.CODINTERFASE=:CODINTERFASE "\
        " ORDER BY NUMREG "
static v10cursors *vdseliclcodinterfase;

#define SELICLNUMLINEAS "SELECT COUNT(DISTINCT NUMREG) GENCOUNT "\
        " FROM VDINTERFCARGALIN"\
        " WHERE "\
               " VDINTERFCARGALIN.CODINTERFASE=:CODINTERFASE "
static v10cursors *vdseliclnumlineas;

#define SELICLVDINTERFCARGALIN "SELECT VDINTERFCARGALIN.ROWID,VDINTERFCARGALIN.CODINTERFASE,VDINTERFCARGALIN.TIPOINTERFASE, "\
                    " VDINTERFCARGALIN.FORMATO,VDINTERFCARGALIN.NUMREG,VDINTERFCARGALIN.REGISTRO, "\
                    " VDINTERFCARGALIN.MENSAJE,VDINTERFCARGALIN.STATUS,VDINTERFCARGALIN.VDEXTRA, "\
                    " VDINTERFCARGALIN.CODOPEMODIF,VDINTERFCARGALIN.FECMODIF,VDINTERFCARGALIN.HORAMODIF, "\
                    " VDINTERFCARGALIN.CODCOMEN "\
        " FROM VDINTERFCARGALIN"\
        " WHERE "\
               " VDINTERFCARGALIN.CODINTERFASE=:CODINTERFASE "\
               " AND VDINTERFCARGALIN.NUMREG=:NUMREG "
static v10cursors *vdseliclvdinterfcargalin;

#define UPDAICLSTMSG "UPDATE VDINTERFCARGALIN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS , "\
               " MENSAJE=:MENSAJE  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaiclstmsg;

#define INSICL "INSERT INTO VDINTERFCARGALIN (CODINTERFASE,TIPOINTERFASE,FORMATO,NUMREG,REGISTRO,MENSAJE, "\
                    " STATUS,VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODINTERFASE,:TIPOINTERFASE,:FORMATO,:NUMREG,:REGISTRO,:MENSAJE, "\
                    " :STATUS,:VDEXTRA,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:CODCOMEN) "
static v10cursors *vdinsicl;

#define DELICL "DELETE VDINTERFCARGALIN WHERE ROWID=:MIROWID "
static v10cursors *vddelicl;

static vdinterfcargalins svdinterfcargalin;

static diccols colvdinterfcargalin[]={
	{"ROWID",V10CADENA,(size_t)&svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid)},
	{"CODINTERFASE",V10LONG,(size_t)&svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase)},
	{"TIPOINTERFASE",V10CADENA,(size_t)&svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase)},
	{"FORMATO",V10CADENA,(size_t)&svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato)},
	{"NUMREG",V10LONG,(size_t)&svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg)},
	{"REGISTRO",V10CADENA,(size_t)&svdinterfcargalin.registro,sizeof(svdinterfcargalin.registro)},
	{"MENSAJE",V10CADENA,(size_t)&svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje)},
	{"STATUS",V10LONG,(size_t)&svdinterfcargalin.status,sizeof(svdinterfcargalin.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinterfcargalin.vdextra,sizeof(svdinterfcargalin.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinterfcargalin.codopemodif,sizeof(svdinterfcargalin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinterfcargalin.fecmodif,sizeof(svdinterfcargalin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinterfcargalin.horamodif,sizeof(svdinterfcargalin.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinterfcargalin.codcomen,sizeof(svdinterfcargalin.codcomen)},
	{"STATUSCAB",V10LONG,(size_t)&svdinterfcargalin.statuscab,sizeof(svdinterfcargalin.statuscab)},
	{"GENCOUNT",V10DOUBLE,(size_t)&svdinterfcargalin.gencount,sizeof(svdinterfcargalin.gencount)}
	};
static diccionarios dvdinterfcargalin[]={
    {colvdinterfcargalin,15}
};
diccionario dicl={dvdinterfcargalin,1};

static char msglogICL[LCADENA];
static char msgdebugICL[LCADENABIG];
static int init=0;


static void fin_vd_icl(void)
{
if (vdseliclbuscareg) {
    liberacursor(vdseliclbuscareg);
    vdseliclbuscareg = NULL;
}
if (vdseliclcodinterfase) {
    liberacursor(vdseliclcodinterfase);
    vdseliclcodinterfase = NULL;
}
if (vdseliclnumlineas) {
    liberacursor(vdseliclnumlineas);
    vdseliclnumlineas = NULL;
}
if (vdseliclvdinterfcargalin) {
    liberacursor(vdseliclvdinterfcargalin);
    vdseliclvdinterfcargalin = NULL;
}
if (vdupdaiclstmsg) {
    liberacursor(vdupdaiclstmsg);
    vdupdaiclstmsg = NULL;
}
if (vdinsicl != NULL) {
    liberacursor(vdinsicl);
    vdinsicl = NULL;
}
if (vddelicl != NULL) {
    liberacursor(vddelicl);
    vddelicl = NULL;
}
}
static void init_seliclbuscareg(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdseliclbuscareg=abrecursordebug(SELICLBUSCAREG,1280);
    definetodo(vdseliclbuscareg,svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid),V10CADENA,
                          &svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase),V10CADENA,
                          svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato),V10CADENA,
                          &svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg),V10LONG,
                          svdinterfcargalin.registro,sizeof(svdinterfcargalin.registro),V10CADENA,
                          svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje),V10CADENA,
                          &svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          svdinterfcargalin.vdextra,sizeof(svdinterfcargalin.vdextra),V10CADENA,
                          svdinterfcargalin.codopemodif,sizeof(svdinterfcargalin.codopemodif),V10CADENA,
                          &svdinterfcargalin.fecmodif,sizeof(svdinterfcargalin.fecmodif),V10LONG,
                          svdinterfcargalin.horamodif,sizeof(svdinterfcargalin.horamodif),V10CADENA,
                          &svdinterfcargalin.codcomen,sizeof(svdinterfcargalin.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliclbuscareg,"TIPOINTERFASE",svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato),V10CADENA,
                          "STATUS",&svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          "STATUSCAB",&svdinterfcargalin.statuscab,sizeof(svdinterfcargalin.statuscab),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_seliclcodinterfase(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdseliclcodinterfase=abrecursordebug(SELICLCODINTERFASE,1280);
    definetodo(vdseliclcodinterfase,svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid),V10CADENA,
                          &svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase),V10CADENA,
                          svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato),V10CADENA,
                          &svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg),V10LONG,
                          svdinterfcargalin.registro,sizeof(svdinterfcargalin.registro),V10CADENA,
                          svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje),V10CADENA,
                          &svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          svdinterfcargalin.vdextra,sizeof(svdinterfcargalin.vdextra),V10CADENA,
                          svdinterfcargalin.codopemodif,sizeof(svdinterfcargalin.codopemodif),V10CADENA,
                          &svdinterfcargalin.fecmodif,sizeof(svdinterfcargalin.fecmodif),V10LONG,
                          svdinterfcargalin.horamodif,sizeof(svdinterfcargalin.horamodif),V10CADENA,
                          &svdinterfcargalin.codcomen,sizeof(svdinterfcargalin.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliclcodinterfase,"CODINTERFASE",&svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_seliclnumlineas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdseliclnumlineas=abrecursordebug(SELICLNUMLINEAS,1280);
    definetodo(vdseliclnumlineas,&svdinterfcargalin.gencount,sizeof(svdinterfcargalin.gencount),V10DOUBLE,
                          NULL);
    bindtodo(vdseliclnumlineas,"CODINTERFASE",&svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_seliclvdinterfcargalin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdseliclvdinterfcargalin=abrecursordebug(SELICLVDINTERFCARGALIN,1280);
    definetodo(vdseliclvdinterfcargalin,svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid),V10CADENA,
                          &svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase),V10CADENA,
                          svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato),V10CADENA,
                          &svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg),V10LONG,
                          svdinterfcargalin.registro,sizeof(svdinterfcargalin.registro),V10CADENA,
                          svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje),V10CADENA,
                          &svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          svdinterfcargalin.vdextra,sizeof(svdinterfcargalin.vdextra),V10CADENA,
                          svdinterfcargalin.codopemodif,sizeof(svdinterfcargalin.codopemodif),V10CADENA,
                          &svdinterfcargalin.fecmodif,sizeof(svdinterfcargalin.fecmodif),V10LONG,
                          svdinterfcargalin.horamodif,sizeof(svdinterfcargalin.horamodif),V10CADENA,
                          &svdinterfcargalin.codcomen,sizeof(svdinterfcargalin.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseliclvdinterfcargalin,"CODINTERFASE",&svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          "NUMREG",&svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_updaiclstmsg(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdupdaiclstmsg=abrecursordebug(UPDAICLSTMSG,1280);
    bindtodo(vdupdaiclstmsg,"STATUS",&svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          "MENSAJE",svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje),V10CADENA,
                          "MIROWID",svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_insicl(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vdinsicl=abrecursordebug(INSICL,1280);
    bindtodo(vdinsicl,"CODINTERFASE",&svdinterfcargalin.codinterfase,sizeof(svdinterfcargalin.codinterfase),V10LONG,
                          "TIPOINTERFASE",svdinterfcargalin.tipointerfase,sizeof(svdinterfcargalin.tipointerfase),V10CADENA,
                          "FORMATO",svdinterfcargalin.formato,sizeof(svdinterfcargalin.formato),V10CADENA,
                          "NUMREG",&svdinterfcargalin.numreg,sizeof(svdinterfcargalin.numreg),V10LONG,
                          "REGISTRO",svdinterfcargalin.registro,sizeof(svdinterfcargalin.registro),V10CADENA,
                          "MENSAJE",svdinterfcargalin.mensaje,sizeof(svdinterfcargalin.mensaje),V10CADENA,
                          "STATUS",&svdinterfcargalin.status,sizeof(svdinterfcargalin.status),V10LONG,
                          "VDEXTRA",svdinterfcargalin.vdextra,sizeof(svdinterfcargalin.vdextra),V10CADENA,
                          "CODCOMEN",&svdinterfcargalin.codcomen,sizeof(svdinterfcargalin.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

static void init_delicl(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinterfcargalin[0].numcol;nc++) dvdinterfcargalin[0].c[nc].offset-=(size_t)&svdinterfcargalin;
    vddelicl=abrecursordebug(DELICL,1280);
    bindtodo(vddelicl,"MIROWID",svdinterfcargalin.rowid,sizeof(svdinterfcargalin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_icl);
        init = 1;
    }
}

diccionario *ICLdamediccionario(void)
{
     return(&dicl);
}

int ICLbuscabuscareg(char *tipointerfase,char *formato,long status,long statuscab,vdinterfcargalins *icl)
{
  int vdret;
  memset(&svdinterfcargalin,0,sizeof(svdinterfcargalin));
  strcpy(svdinterfcargalin.tipointerfase,tipointerfase);
  strcpy(svdinterfcargalin.formato,formato);
  svdinterfcargalin.status=status;
  svdinterfcargalin.statuscab=statuscab;
  if (vdseliclbuscareg==NULL) init_seliclbuscareg();
  vdret=ejefetchcursor(vdseliclbuscareg);
  if (vdret==0) {
     *icl=svdinterfcargalin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseliclbuscareg. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ICLnextbuscareg(vdinterfcargalins *icl)
{
  int vdret;
  vdret=fetchcursor(vdseliclbuscareg);
  if (vdret==0) {
     *icl=svdinterfcargalin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseliclbuscareg. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseliclbuscareg);
  return(VD_EERRORACLE);
}

int ICLbuscacodinterfase(long codinterfase,vdinterfcargalins *icl)
{
  int vdret;
  memset(&svdinterfcargalin,0,sizeof(svdinterfcargalin));
  svdinterfcargalin.codinterfase=codinterfase;
  if (vdseliclcodinterfase==NULL) init_seliclcodinterfase();
  vdret=ejefetchcursor(vdseliclcodinterfase);
  if (vdret==0) {
     *icl=svdinterfcargalin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseliclcodinterfase. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ICLnextcodinterfase(vdinterfcargalins *icl)
{
  int vdret;
  vdret=fetchcursor(vdseliclcodinterfase);
  if (vdret==0) {
     *icl=svdinterfcargalin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseliclcodinterfase. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseliclcodinterfase);
  return(VD_EERRORACLE);
}

int ICLselnumlineas(long codinterfase,vdinterfcargalins *icl)
{
  int vdret;
  if (vdseliclnumlineas==NULL) init_seliclnumlineas();
  memset(&svdinterfcargalin,0,sizeof(svdinterfcargalin));
  svdinterfcargalin.codinterfase=codinterfase;
  vdret=ejefetchcursor(vdseliclnumlineas);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseliclnumlineas. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
    return(VD_EERRORACLE);
   }
  *icl=svdinterfcargalin;
  return(vdret);
}

int ICLselvdinterfcargalin(long codinterfase,long numreg,vdinterfcargalins *icl)
{
  int vdret;
  if (vdseliclvdinterfcargalin==NULL) init_seliclvdinterfcargalin();
  memset(&svdinterfcargalin,0,sizeof(svdinterfcargalin));
  svdinterfcargalin.codinterfase=codinterfase;
  svdinterfcargalin.numreg=numreg;
  vdret=ejefetchcursor(vdseliclvdinterfcargalin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseliclvdinterfcargalin. vdret %d. \n",ICLlog(&svdinterfcargalin),vdret);
    return(VD_EERRORACLE);
   }
  *icl=svdinterfcargalin;
  return(vdret);
}

int ICLactualizastmsg(vdinterfcargalins *icl,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ICLactualizastmsg:  %s .  \n",ICLlog(&svdinterfcargalin));
  if (vdupdaiclstmsg==NULL) init_updaiclstmsg();
  svdinterfcargalin=*icl;
  vdret=ejecutacursor(vdupdaiclstmsg);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaiclstmsg);
     getcurerrornombre(vdupdaiclstmsg->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaiclstmsg)!=1) return(VD_EERRORACLE);
  return(0);
}

int ICLinsert(vdinterfcargalins *icl,int error)
{
  int vdret;
  if (!vdinsicl) init_insicl();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",ICLlog(&svdinterfcargalin));
  svdinterfcargalin=*icl;
  vdret=ejecutacursor(vdinsicl);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsicl);
     getcurerrornombre(vdinsicl->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ICLdel(vdinterfcargalins *icl,int error)
{
  int vdret;
  svdinterfcargalin=*icl;
  if (vddelicl==NULL) init_delicl();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",ICLlog(&svdinterfcargalin));
  vdret=ejecutacursor(vddelicl);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelicl);
     getcurerrornombre(vddelicl->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * ICLlog(vdinterfcargalins *icl)
{
    sprintf(msglogICL, "VDINTERFCARGALIN: codinterfase %ld numreg %ld ",icl->codinterfase,icl->numreg);
    return(msglogICL);
}

char * ICLdebug(vdinterfcargalins *icl)
{
    debugestruct(&dicl,icl,msgdebugICL);
    return(msgdebugICL);
}

