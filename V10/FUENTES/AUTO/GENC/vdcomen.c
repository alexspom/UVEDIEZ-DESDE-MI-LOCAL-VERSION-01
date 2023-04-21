// Modulo generado automaticamente a partir de VDCOMEN.DEF
//#***
//# VDCOMEN.c - Generaci�n autom�tica del c�digo c para la tabla VDCOMEN                                                       
//# 
//# Prop�sito: Funciones de acceso a la tabla VDCOMEN
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 13-11-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=COM
//
//SECUENCIA=VDSECCOMEN,CODCOMEN
//RECORRE=TIPOCOMEN,TIPOCOMEN;ORDERBY=CODCOMEN,LINCOMEN;
//RECORRE=COMEN,CODCOMEN;ORDERBY=TIPOCOMEN,LINCOMEN;
//RECORRE=COMENYTIPO,CODCOMEN,TIPOCOMEN;ORDERBY=LINCOMEN;
//RECORRE=PORNOTIFICAR,NOTIFICAR;WHERE=NOTIFICAR IS NOT NULL;ORDERBY=FECMODIF,HORAMODIF;
//
//
//UPDATE=NOTIFICAR,NOTIFICAR
//UPDATE=COMENTARIO,COMENTARIO
//UPDATE=COMENTARIOYNOTIFICAR,COMENTARIO,NOTIFICAR
//
//INTERFASE
//UPDATE
//INSERT
//DELETE

#include "vd.h"
#define SELCOMTIPOCOMEN "SELECT VDCOMEN.ROWID,VDCOMEN.TIPOCOMEN,VDCOMEN.CODCOMEN, "\
                    " VDCOMEN.LINCOMEN,VDCOMEN.COMENTARIO,VDCOMEN.NOTIFICAR, "\
                    " VDCOMEN.CODOPEMODIF,VDCOMEN.FECMODIF,VDCOMEN.HORAMODIF "\
        " FROM VDCOMEN"\
        " WHERE "\
               " VDCOMEN.TIPOCOMEN=:TIPOCOMEN "\
        " ORDER BY CODCOMEN,LINCOMEN "
static v10cursors *vdselcomtipocomen;

#define SELCOMCOMEN "SELECT VDCOMEN.ROWID,VDCOMEN.TIPOCOMEN,VDCOMEN.CODCOMEN, "\
                    " VDCOMEN.LINCOMEN,VDCOMEN.COMENTARIO,VDCOMEN.NOTIFICAR, "\
                    " VDCOMEN.CODOPEMODIF,VDCOMEN.FECMODIF,VDCOMEN.HORAMODIF "\
        " FROM VDCOMEN"\
        " WHERE "\
               " VDCOMEN.CODCOMEN=:CODCOMEN "\
        " ORDER BY TIPOCOMEN,LINCOMEN "
static v10cursors *vdselcomcomen;

#define SELCOMCOMENYTIPO "SELECT VDCOMEN.ROWID,VDCOMEN.TIPOCOMEN,VDCOMEN.CODCOMEN, "\
                    " VDCOMEN.LINCOMEN,VDCOMEN.COMENTARIO,VDCOMEN.NOTIFICAR, "\
                    " VDCOMEN.CODOPEMODIF,VDCOMEN.FECMODIF,VDCOMEN.HORAMODIF "\
        " FROM VDCOMEN"\
        " WHERE "\
               " VDCOMEN.CODCOMEN=:CODCOMEN "\
               " AND VDCOMEN.TIPOCOMEN=:TIPOCOMEN "\
        " ORDER BY LINCOMEN "
static v10cursors *vdselcomcomenytipo;

#define SELCOMPORNOTIFICAR "SELECT VDCOMEN.ROWID,VDCOMEN.TIPOCOMEN,VDCOMEN.CODCOMEN, "\
                    " VDCOMEN.LINCOMEN,VDCOMEN.COMENTARIO,VDCOMEN.NOTIFICAR, "\
                    " VDCOMEN.CODOPEMODIF,VDCOMEN.FECMODIF,VDCOMEN.HORAMODIF "\
        " FROM VDCOMEN"\
        " WHERE "\
               " VDCOMEN.NOTIFICAR=:NOTIFICAR "\
              "  AND NOTIFICAR IS NOT NULL "\
        " ORDER BY FECMODIF,HORAMODIF "
static v10cursors *vdselcompornotificar;

#define SELCOMVDCOMEN "SELECT VDCOMEN.ROWID,VDCOMEN.TIPOCOMEN,VDCOMEN.CODCOMEN, "\
                    " VDCOMEN.LINCOMEN,VDCOMEN.COMENTARIO,VDCOMEN.NOTIFICAR, "\
                    " VDCOMEN.CODOPEMODIF,VDCOMEN.FECMODIF,VDCOMEN.HORAMODIF "\
        " FROM VDCOMEN"\
        " WHERE "\
               " VDCOMEN.TIPOCOMEN=:TIPOCOMEN "\
               " AND VDCOMEN.CODCOMEN=:CODCOMEN "\
               " AND VDCOMEN.LINCOMEN=:LINCOMEN "
static v10cursors *vdselcomvdcomen;

#define UPDACOMNOTIFICAR "UPDATE VDCOMEN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " NOTIFICAR=:NOTIFICAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdacomnotificar;

#define UPDACOMCOMENTARIO "UPDATE VDCOMEN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " COMENTARIO=:COMENTARIO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdacomcomentario;

#define UPDACOMCOMENTARIOYNOTIFICAR "UPDATE VDCOMEN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " COMENTARIO=:COMENTARIO , "\
               " NOTIFICAR=:NOTIFICAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdacomcomentarioynotificar;

#define UPDACOM "UPDATE VDCOMEN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " TIPOCOMEN=:TIPOCOMEN , "\
               " CODCOMEN=:CODCOMEN , "\
               " LINCOMEN=:LINCOMEN , "\
               " COMENTARIO=:COMENTARIO , "\
               " NOTIFICAR=:NOTIFICAR  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdacomvdcomen;

#define SELVDSECCOMEN "SELECT VDSECCOMEN.NEXTVAL FROM DUAL"
static v10cursors *vdselvdseccomen;

#define INSCOM "INSERT INTO VDCOMEN (TIPOCOMEN,CODCOMEN,LINCOMEN,COMENTARIO,NOTIFICAR,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF "\
       " ) VALUES ( "\
                    " :TIPOCOMEN,:CODCOMEN,:LINCOMEN,:COMENTARIO,:NOTIFICAR,VDUSER.GETUSER, "\
                    " VD.FECHASYS,VD.HORASYS) "
static v10cursors *vdinscom;

#define DELCOM "DELETE VDCOMEN WHERE ROWID=:MIROWID "
static v10cursors *vddelcom;

static vdcomens svdcomen;

static diccols colvdcomen[]={
	{"ROWID",V10CADENA,(size_t)&svdcomen.rowid,sizeof(svdcomen.rowid)},
	{"TIPOCOMEN",V10CADENA,(size_t)&svdcomen.tipocomen,sizeof(svdcomen.tipocomen)},
	{"CODCOMEN",V10LONG,(size_t)&svdcomen.codcomen,sizeof(svdcomen.codcomen)},
	{"LINCOMEN",V10LONG,(size_t)&svdcomen.lincomen,sizeof(svdcomen.lincomen)},
	{"COMENTARIO",V10CADENA,(size_t)&svdcomen.comentario,sizeof(svdcomen.comentario)},
	{"NOTIFICAR",V10CADENA,(size_t)&svdcomen.notificar,sizeof(svdcomen.notificar)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdcomen.codopemodif,sizeof(svdcomen.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdcomen.fecmodif,sizeof(svdcomen.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdcomen.horamodif,sizeof(svdcomen.horamodif)}
	};
static diccionarios dvdcomen[]={
    {colvdcomen,9}
};
diccionario dcom={dvdcomen,1};

static char msglogCOM[LCADENA];
static char msgdebugCOM[LCADENABIG];
static int init=0;


static void fin_vd_com(void)
{
if (vdselcomtipocomen) {
    liberacursor(vdselcomtipocomen);
    vdselcomtipocomen = NULL;
}
if (vdselcomcomen) {
    liberacursor(vdselcomcomen);
    vdselcomcomen = NULL;
}
if (vdselcomcomenytipo) {
    liberacursor(vdselcomcomenytipo);
    vdselcomcomenytipo = NULL;
}
if (vdselcompornotificar) {
    liberacursor(vdselcompornotificar);
    vdselcompornotificar = NULL;
}
if (vdselcomvdcomen) {
    liberacursor(vdselcomvdcomen);
    vdselcomvdcomen = NULL;
}
if (vdupdacomnotificar) {
    liberacursor(vdupdacomnotificar);
    vdupdacomnotificar = NULL;
}
if (vdupdacomcomentario) {
    liberacursor(vdupdacomcomentario);
    vdupdacomcomentario = NULL;
}
if (vdupdacomcomentarioynotificar) {
    liberacursor(vdupdacomcomentarioynotificar);
    vdupdacomcomentarioynotificar = NULL;
}
if (vdupdacomvdcomen) {
    liberacursor(vdupdacomvdcomen);
    vdupdacomvdcomen = NULL;
}
if (vdselvdseccomen != NULL) {
    liberacursor(vdselvdseccomen);
    vdselvdseccomen = NULL;
}
if (vdinscom != NULL) {
    liberacursor(vdinscom);
    vdinscom = NULL;
}
if (vddelcom != NULL) {
    liberacursor(vddelcom);
    vddelcom = NULL;
}
}
static void init_selcomtipocomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselcomtipocomen=abrecursordebug(SELCOMTIPOCOMEN,1280);
    definetodo(vdselcomtipocomen,svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          &svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          &svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          svdcomen.codopemodif,sizeof(svdcomen.codopemodif),V10CADENA,
                          &svdcomen.fecmodif,sizeof(svdcomen.fecmodif),V10LONG,
                          svdcomen.horamodif,sizeof(svdcomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcomtipocomen,"TIPOCOMEN",svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_selcomcomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselcomcomen=abrecursordebug(SELCOMCOMEN,1280);
    definetodo(vdselcomcomen,svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          &svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          &svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          svdcomen.codopemodif,sizeof(svdcomen.codopemodif),V10CADENA,
                          &svdcomen.fecmodif,sizeof(svdcomen.fecmodif),V10LONG,
                          svdcomen.horamodif,sizeof(svdcomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcomcomen,"CODCOMEN",&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_selcomcomenytipo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselcomcomenytipo=abrecursordebug(SELCOMCOMENYTIPO,1280);
    definetodo(vdselcomcomenytipo,svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          &svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          &svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          svdcomen.codopemodif,sizeof(svdcomen.codopemodif),V10CADENA,
                          &svdcomen.fecmodif,sizeof(svdcomen.fecmodif),V10LONG,
                          svdcomen.horamodif,sizeof(svdcomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcomcomenytipo,"CODCOMEN",&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          "TIPOCOMEN",svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_selcompornotificar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselcompornotificar=abrecursordebug(SELCOMPORNOTIFICAR,1280);
    definetodo(vdselcompornotificar,svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          &svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          &svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          svdcomen.codopemodif,sizeof(svdcomen.codopemodif),V10CADENA,
                          &svdcomen.fecmodif,sizeof(svdcomen.fecmodif),V10LONG,
                          svdcomen.horamodif,sizeof(svdcomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcompornotificar,"NOTIFICAR",svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_selcomvdcomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselcomvdcomen=abrecursordebug(SELCOMVDCOMEN,1280);
    definetodo(vdselcomvdcomen,svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          &svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          &svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          svdcomen.codopemodif,sizeof(svdcomen.codopemodif),V10CADENA,
                          &svdcomen.fecmodif,sizeof(svdcomen.fecmodif),V10LONG,
                          svdcomen.horamodif,sizeof(svdcomen.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselcomvdcomen,"TIPOCOMEN",svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          "CODCOMEN",&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          "LINCOMEN",&svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_updacomnotificar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdupdacomnotificar=abrecursordebug(UPDACOMNOTIFICAR,1280);
    bindtodo(vdupdacomnotificar,"NOTIFICAR",svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          "MIROWID",svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_updacomcomentario(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdupdacomcomentario=abrecursordebug(UPDACOMCOMENTARIO,1280);
    bindtodo(vdupdacomcomentario,"COMENTARIO",svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          "MIROWID",svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_updacomcomentarioynotificar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdupdacomcomentarioynotificar=abrecursordebug(UPDACOMCOMENTARIOYNOTIFICAR,1280);
    bindtodo(vdupdacomcomentarioynotificar,"COMENTARIO",svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          "NOTIFICAR",svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          "MIROWID",svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_updacomvdcomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdupdacomvdcomen=abrecursordebug(UPDACOM,1280);
    bindtodo(vdupdacomvdcomen,"TIPOCOMEN",svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          "CODCOMEN",&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          "LINCOMEN",&svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          "COMENTARIO",svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          "NOTIFICAR",svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          "MIROWID",svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_selvdseccomen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdselvdseccomen=abrecursordebug(SELVDSECCOMEN,1280);
    definetodo(vdselvdseccomen,&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_inscom(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vdinscom=abrecursordebug(INSCOM,1280);
    bindtodo(vdinscom,"TIPOCOMEN",svdcomen.tipocomen,sizeof(svdcomen.tipocomen),V10CADENA,
                          "CODCOMEN",&svdcomen.codcomen,sizeof(svdcomen.codcomen),V10LONG,
                          "LINCOMEN",&svdcomen.lincomen,sizeof(svdcomen.lincomen),V10LONG,
                          "COMENTARIO",svdcomen.comentario,sizeof(svdcomen.comentario),V10CADENA,
                          "NOTIFICAR",svdcomen.notificar,sizeof(svdcomen.notificar),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

static void init_delcom(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdcomen[0].numcol;nc++) dvdcomen[0].c[nc].offset-=(size_t)&svdcomen;
    vddelcom=abrecursordebug(DELCOM,1280);
    bindtodo(vddelcom,"MIROWID",svdcomen.rowid,sizeof(svdcomen.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_com);
        init = 1;
    }
}

diccionario *COMdamediccionario(void)
{
     return(&dcom);
}

int COMbuscatipocomen(char *tipocomen,vdcomens *com)
{
  int vdret;
  memset(&svdcomen,0,sizeof(svdcomen));
  strcpy(svdcomen.tipocomen,tipocomen);
  if (vdselcomtipocomen==NULL) init_selcomtipocomen();
  vdret=ejefetchcursor(vdselcomtipocomen);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselcomtipocomen. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int COMnexttipocomen(vdcomens *com)
{
  int vdret;
  vdret=fetchcursor(vdselcomtipocomen);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselcomtipocomen. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselcomtipocomen);
  return(VD_EERRORACLE);
}

int COMbuscacomen(long codcomen,vdcomens *com)
{
  int vdret;
  memset(&svdcomen,0,sizeof(svdcomen));
  svdcomen.codcomen=codcomen;
  if (vdselcomcomen==NULL) init_selcomcomen();
  vdret=ejefetchcursor(vdselcomcomen);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselcomcomen. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int COMnextcomen(vdcomens *com)
{
  int vdret;
  vdret=fetchcursor(vdselcomcomen);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselcomcomen. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselcomcomen);
  return(VD_EERRORACLE);
}

int COMbuscacomenytipo(long codcomen,char *tipocomen,vdcomens *com)
{
  int vdret;
  memset(&svdcomen,0,sizeof(svdcomen));
  svdcomen.codcomen=codcomen;
  strcpy(svdcomen.tipocomen,tipocomen);
  if (vdselcomcomenytipo==NULL) init_selcomcomenytipo();
  vdret=ejefetchcursor(vdselcomcomenytipo);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselcomcomenytipo. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int COMnextcomenytipo(vdcomens *com)
{
  int vdret;
  vdret=fetchcursor(vdselcomcomenytipo);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselcomcomenytipo. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselcomcomenytipo);
  return(VD_EERRORACLE);
}

int COMbuscapornotificar(char *notificar,vdcomens *com)
{
  int vdret;
  memset(&svdcomen,0,sizeof(svdcomen));
  strcpy(svdcomen.notificar,notificar);
  if (vdselcompornotificar==NULL) init_selcompornotificar();
  vdret=ejefetchcursor(vdselcompornotificar);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselcompornotificar. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int COMnextpornotificar(vdcomens *com)
{
  int vdret;
  vdret=fetchcursor(vdselcompornotificar);
  if (vdret==0) {
     *com=svdcomen;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselcompornotificar. vdret %d. \n",COMlog(&svdcomen),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselcompornotificar);
  return(VD_EERRORACLE);
}

int COMselvdcomen(char *tipocomen,long codcomen,long lincomen,vdcomens *com)
{
  int vdret;
  if (vdselcomvdcomen==NULL) init_selcomvdcomen();
  memset(&svdcomen,0,sizeof(svdcomen));
  strcpy(svdcomen.tipocomen,tipocomen);
  svdcomen.codcomen=codcomen;
  svdcomen.lincomen=lincomen;
  vdret=ejefetchcursor(vdselcomvdcomen);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselcomvdcomen. vdret %d. \n",COMlog(&svdcomen),vdret);
    return(VD_EERRORACLE);
   }
  *com=svdcomen;
  return(vdret);
}

int COMactualizanotificar(vdcomens *com,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando COMactualizanotificar:  %s .  \n",COMlog(&svdcomen));
  if (vdupdacomnotificar==NULL) init_updacomnotificar();
  svdcomen=*com;
  vdret=ejecutacursor(vdupdacomnotificar);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdacomnotificar);
     getcurerrornombre(vdupdacomnotificar->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdacomnotificar)!=1) return(VD_EERRORACLE);
  return(0);
}

int COMactualizacomentario(vdcomens *com,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando COMactualizacomentario:  %s .  \n",COMlog(&svdcomen));
  if (vdupdacomcomentario==NULL) init_updacomcomentario();
  svdcomen=*com;
  vdret=ejecutacursor(vdupdacomcomentario);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdacomcomentario);
     getcurerrornombre(vdupdacomcomentario->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdacomcomentario)!=1) return(VD_EERRORACLE);
  return(0);
}

int COMactualizacomentarioynotificar(vdcomens *com,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando COMactualizacomentarioynotificar:  %s .  \n",COMlog(&svdcomen));
  if (vdupdacomcomentarioynotificar==NULL) init_updacomcomentarioynotificar();
  svdcomen=*com;
  vdret=ejecutacursor(vdupdacomcomentarioynotificar);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdacomcomentarioynotificar);
     getcurerrornombre(vdupdacomcomentarioynotificar->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdacomcomentarioynotificar)!=1) return(VD_EERRORACLE);
  return(0);
}

int COMactualizavdcomen(vdcomens *com,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando COMactualizavdcomen:  %s .  \n",COMlog(&svdcomen));
  if (vdupdacomvdcomen==NULL) init_updacomvdcomen();
  svdcomen=*com;
  vdret=ejecutacursor(vdupdacomvdcomen);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdacomvdcomen);
     getcurerrornombre(vdupdacomvdcomen->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdacomvdcomen)!=1) return(VD_EERRORACLE);
  return(0);
}

int COMselvdseccomen(long *donde)
{
  int vdret;
  if (!vdselvdseccomen) init_selvdseccomen();
  vdret=ejefetchcursor(vdselvdseccomen);
  if (!vdret) {
     *donde=svdcomen.codcomen;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int COMinsert(vdcomens *com,int error)
{
  int vdret;
  if (!vdinscom) init_inscom();
  if (!com->codcomen) {
     if ((vdret=COMselvdseccomen(&(com->codcomen)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",COMlog(&svdcomen));
  svdcomen=*com;
  vdret=ejecutacursor(vdinscom);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinscom);
     getcurerrornombre(vdinscom->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int COMdel(vdcomens *com,int error)
{
  int vdret;
  svdcomen=*com;
  if (vddelcom==NULL) init_delcom();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",COMlog(&svdcomen));
  vdret=ejecutacursor(vddelcom);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelcom);
     getcurerrornombre(vddelcom->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int COMinter(vdcomens *com)
{
  int vdret = 0;
  if (vdselcomvdcomen==NULL) init_selcomvdcomen();
  memset(&svdcomen,0,sizeof(svdcomen));
  strcpy(svdcomen.tipocomen,com->tipocomen);
  svdcomen.codcomen = com->codcomen;
  svdcomen.lincomen = com->lincomen;
  vdret=ejefetchcursor(vdselcomvdcomen);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselcomvdcomen. vdret %d. \n",COMlog(&svdcomen),vdret);
    return(VD_EERRORACLE);
  }

  *com=svdcomen;
  return(vdret);
}

char * COMlog(vdcomens *com)
{
    sprintf(msglogCOM, "VDCOMEN: tipocomen %s codcomen %ld lincomen %ld ",com->tipocomen,com->codcomen,com->lincomen);
    return(msglogCOM);
}

char * COMdebug(vdcomens *com)
{
    debugestruct(&dcom,com,msgdebugCOM);
    return(msgdebugCOM);
}

