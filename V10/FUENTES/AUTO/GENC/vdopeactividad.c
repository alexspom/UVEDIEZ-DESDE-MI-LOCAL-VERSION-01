// Modulo generado automaticamente a partir de VDOPEACTIVIDAD.DEF
//#***
//# VDOPEACTIVIDAD.DEF - Generaci�n autom�tica del c�digo c para la tabla de Actividad de operarios en zonas
//#                        
//# Prop�sito: Funciones de acceso a la tabla VDOPEACTIVIDAD
//#           
//# Autor	 : FGS	
//# Revisado por: 
//# Fecha  : 10-12-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=OACT
//UPDATE=CIERREZONA,FECFINACT,HORAFINACT
//RECORRE=ZONAABIERTA,CODZONA,CODOPE;WHERE=NVL(FECFINACT,0)=0 AND HORAFINACT IS NULL;
//RECORRE=OPEZONA,CODZONA,WHERE=NVL(FECFINACT,0)=0 AND HORAFINACT IS NULL;
//INSERT

#include "vd.h"
#define SELOACTZONAABIERTA "SELECT VDOPEACTIVIDAD.ROWID,VDOPEACTIVIDAD.CODOPE,VDOPEACTIVIDAD.CODZONA, "\
                    " VDOPEACTIVIDAD.FECINIACT,VDOPEACTIVIDAD.HORAINIACT,VDOPEACTIVIDAD.FECFINACT, "\
                    " VDOPEACTIVIDAD.HORAFINACT,VDOPEACTIVIDAD.CODOPEMODIF,VDOPEACTIVIDAD.FECMODIF, "\
                    " VDOPEACTIVIDAD.HORAMODIF,VDOPEACTIVIDAD.CODCOMEN "\
        " FROM VDOPEACTIVIDAD"\
        " WHERE "\
               " VDOPEACTIVIDAD.CODZONA=:CODZONA "\
               " AND VDOPEACTIVIDAD.CODOPE=:CODOPE "\
              "  AND NVL(FECFINACT,0)=0 AND HORAFINACT IS NULL "
static v10cursors *vdseloactzonaabierta;

#define SELOACTOPEZONA "SELECT VDOPEACTIVIDAD.ROWID,VDOPEACTIVIDAD.CODOPE,VDOPEACTIVIDAD.CODZONA, "\
                    " VDOPEACTIVIDAD.FECINIACT,VDOPEACTIVIDAD.HORAINIACT,VDOPEACTIVIDAD.FECFINACT, "\
                    " VDOPEACTIVIDAD.HORAFINACT,VDOPEACTIVIDAD.CODOPEMODIF,VDOPEACTIVIDAD.FECMODIF, "\
                    " VDOPEACTIVIDAD.HORAMODIF,VDOPEACTIVIDAD.CODCOMEN "\
        " FROM VDOPEACTIVIDAD"\
        " WHERE "\
               " VDOPEACTIVIDAD.CODZONA=:CODZONA "\
              "  AND NVL(FECFINACT,0)=0 AND HORAFINACT IS NULL "
static v10cursors *vdseloactopezona;

#define SELOACTVDOPEACTIVIDAD "SELECT VDOPEACTIVIDAD.ROWID,VDOPEACTIVIDAD.CODOPE,VDOPEACTIVIDAD.CODZONA, "\
                    " VDOPEACTIVIDAD.FECINIACT,VDOPEACTIVIDAD.HORAINIACT,VDOPEACTIVIDAD.FECFINACT, "\
                    " VDOPEACTIVIDAD.HORAFINACT,VDOPEACTIVIDAD.CODOPEMODIF,VDOPEACTIVIDAD.FECMODIF, "\
                    " VDOPEACTIVIDAD.HORAMODIF,VDOPEACTIVIDAD.CODCOMEN "\
        " FROM VDOPEACTIVIDAD"\
        " WHERE "\
               " VDOPEACTIVIDAD.CODOPE=:CODOPE "\
               " AND VDOPEACTIVIDAD.CODZONA=:CODZONA "\
               " AND VDOPEACTIVIDAD.FECINIACT=:FECINIACT "\
               " AND VDOPEACTIVIDAD.HORAINIACT=:HORAINIACT "
static v10cursors *vdseloactvdopeactividad;

#define UPDAOACTCIERREZONA "UPDATE VDOPEACTIVIDAD SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " FECFINACT=:FECFINACT , "\
               " HORAFINACT=:HORAFINACT  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaoactcierrezona;

#define INSOACT "INSERT INTO VDOPEACTIVIDAD (CODOPE,CODZONA,FECINIACT,HORAINIACT,FECFINACT,HORAFINACT, "\
                    " CODOPEMODIF,FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODOPE,:CODZONA,:FECINIACT,:HORAINIACT,:FECFINACT,:HORAFINACT, "\
                    " VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS(),:CODCOMEN) "
static v10cursors *vdinsoact;

static vdopeactividads svdopeactividad;

static diccols colvdopeactividad[]={
	{"ROWID",V10CADENA,(size_t)&svdopeactividad.rowid,sizeof(svdopeactividad.rowid)},
	{"CODOPE",V10CADENA,(size_t)&svdopeactividad.codope,sizeof(svdopeactividad.codope)},
	{"CODZONA",V10LONG,(size_t)&svdopeactividad.codzona,sizeof(svdopeactividad.codzona)},
	{"FECINIACT",V10LONG,(size_t)&svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact)},
	{"HORAINIACT",V10CADENA,(size_t)&svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact)},
	{"FECFINACT",V10LONG,(size_t)&svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact)},
	{"HORAFINACT",V10CADENA,(size_t)&svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdopeactividad.codopemodif,sizeof(svdopeactividad.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdopeactividad.fecmodif,sizeof(svdopeactividad.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdopeactividad.horamodif,sizeof(svdopeactividad.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdopeactividad.codcomen,sizeof(svdopeactividad.codcomen)}
	};
static diccionarios dvdopeactividad[]={
    {colvdopeactividad,11}
};
diccionario doact={dvdopeactividad,1};

static char msglogOACT[LCADENA];
static char msgdebugOACT[LCADENABIG];
static int init=0;


static void fin_vd_oact(void)
{
if (vdseloactzonaabierta) {
    liberacursor(vdseloactzonaabierta);
    vdseloactzonaabierta = NULL;
}
if (vdseloactopezona) {
    liberacursor(vdseloactopezona);
    vdseloactopezona = NULL;
}
if (vdseloactvdopeactividad) {
    liberacursor(vdseloactvdopeactividad);
    vdseloactvdopeactividad = NULL;
}
if (vdupdaoactcierrezona) {
    liberacursor(vdupdaoactcierrezona);
    vdupdaoactcierrezona = NULL;
}
if (vdinsoact != NULL) {
    liberacursor(vdinsoact);
    vdinsoact = NULL;
}
}
static void init_seloactzonaabierta(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdopeactividad[0].numcol;nc++) dvdopeactividad[0].c[nc].offset-=(size_t)&svdopeactividad;
    vdseloactzonaabierta=abrecursordebug(SELOACTZONAABIERTA,1280);
    definetodo(vdseloactzonaabierta,svdopeactividad.rowid,sizeof(svdopeactividad.rowid),V10CADENA,
                          svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          &svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          &svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact),V10LONG,
                          svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact),V10CADENA,
                          &svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact),V10LONG,
                          svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact),V10CADENA,
                          svdopeactividad.codopemodif,sizeof(svdopeactividad.codopemodif),V10CADENA,
                          &svdopeactividad.fecmodif,sizeof(svdopeactividad.fecmodif),V10LONG,
                          svdopeactividad.horamodif,sizeof(svdopeactividad.horamodif),V10CADENA,
                          &svdopeactividad.codcomen,sizeof(svdopeactividad.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseloactzonaabierta,"CODZONA",&svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          "CODOPE",svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_oact);
        init = 1;
    }
}

static void init_seloactopezona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdopeactividad[0].numcol;nc++) dvdopeactividad[0].c[nc].offset-=(size_t)&svdopeactividad;
    vdseloactopezona=abrecursordebug(SELOACTOPEZONA,1280);
    definetodo(vdseloactopezona,svdopeactividad.rowid,sizeof(svdopeactividad.rowid),V10CADENA,
                          svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          &svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          &svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact),V10LONG,
                          svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact),V10CADENA,
                          &svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact),V10LONG,
                          svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact),V10CADENA,
                          svdopeactividad.codopemodif,sizeof(svdopeactividad.codopemodif),V10CADENA,
                          &svdopeactividad.fecmodif,sizeof(svdopeactividad.fecmodif),V10LONG,
                          svdopeactividad.horamodif,sizeof(svdopeactividad.horamodif),V10CADENA,
                          &svdopeactividad.codcomen,sizeof(svdopeactividad.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseloactopezona,"CODZONA",&svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_oact);
        init = 1;
    }
}

static void init_seloactvdopeactividad(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdopeactividad[0].numcol;nc++) dvdopeactividad[0].c[nc].offset-=(size_t)&svdopeactividad;
    vdseloactvdopeactividad=abrecursordebug(SELOACTVDOPEACTIVIDAD,1280);
    definetodo(vdseloactvdopeactividad,svdopeactividad.rowid,sizeof(svdopeactividad.rowid),V10CADENA,
                          svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          &svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          &svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact),V10LONG,
                          svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact),V10CADENA,
                          &svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact),V10LONG,
                          svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact),V10CADENA,
                          svdopeactividad.codopemodif,sizeof(svdopeactividad.codopemodif),V10CADENA,
                          &svdopeactividad.fecmodif,sizeof(svdopeactividad.fecmodif),V10LONG,
                          svdopeactividad.horamodif,sizeof(svdopeactividad.horamodif),V10CADENA,
                          &svdopeactividad.codcomen,sizeof(svdopeactividad.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseloactvdopeactividad,"CODOPE",svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          "CODZONA",&svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          "FECINIACT",&svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact),V10LONG,
                          "HORAINIACT",svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_oact);
        init = 1;
    }
}

static void init_updaoactcierrezona(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdopeactividad[0].numcol;nc++) dvdopeactividad[0].c[nc].offset-=(size_t)&svdopeactividad;
    vdupdaoactcierrezona=abrecursordebug(UPDAOACTCIERREZONA,1280);
    bindtodo(vdupdaoactcierrezona,"FECFINACT",&svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact),V10LONG,
                          "HORAFINACT",svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact),V10CADENA,
                          "MIROWID",svdopeactividad.rowid,sizeof(svdopeactividad.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_oact);
        init = 1;
    }
}

static void init_insoact(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdopeactividad[0].numcol;nc++) dvdopeactividad[0].c[nc].offset-=(size_t)&svdopeactividad;
    vdinsoact=abrecursordebug(INSOACT,1280);
    bindtodo(vdinsoact,"CODOPE",svdopeactividad.codope,sizeof(svdopeactividad.codope),V10CADENA,
                          "CODZONA",&svdopeactividad.codzona,sizeof(svdopeactividad.codzona),V10LONG,
                          "FECINIACT",&svdopeactividad.feciniact,sizeof(svdopeactividad.feciniact),V10LONG,
                          "HORAINIACT",svdopeactividad.horainiact,sizeof(svdopeactividad.horainiact),V10CADENA,
                          "FECFINACT",&svdopeactividad.fecfinact,sizeof(svdopeactividad.fecfinact),V10LONG,
                          "HORAFINACT",svdopeactividad.horafinact,sizeof(svdopeactividad.horafinact),V10CADENA,
                          "CODCOMEN",&svdopeactividad.codcomen,sizeof(svdopeactividad.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_oact);
        init = 1;
    }
}

diccionario *OACTdamediccionario(void)
{
     return(&doact);
}

int OACTbuscazonaabierta(long codzona,char *codope,vdopeactividads *oact)
{
  int vdret;
  memset(&svdopeactividad,0,sizeof(svdopeactividad));
  svdopeactividad.codzona=codzona;
  strcpy(svdopeactividad.codope,codope);
  if (vdseloactzonaabierta==NULL) init_seloactzonaabierta();
  vdret=ejefetchcursor(vdseloactzonaabierta);
  if (vdret==0) {
     *oact=svdopeactividad;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseloactzonaabierta. vdret %d. \n",OACTlog(&svdopeactividad),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int OACTnextzonaabierta(vdopeactividads *oact)
{
  int vdret;
  vdret=fetchcursor(vdseloactzonaabierta);
  if (vdret==0) {
     *oact=svdopeactividad;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseloactzonaabierta. vdret %d. \n",OACTlog(&svdopeactividad),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseloactzonaabierta);
  return(VD_EERRORACLE);
}

int OACTbuscaopezona(long codzona,vdopeactividads *oact)
{
  int vdret;
  memset(&svdopeactividad,0,sizeof(svdopeactividad));
  svdopeactividad.codzona=codzona;
  if (vdseloactopezona==NULL) init_seloactopezona();
  vdret=ejefetchcursor(vdseloactopezona);
  if (vdret==0) {
     *oact=svdopeactividad;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseloactopezona. vdret %d. \n",OACTlog(&svdopeactividad),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int OACTnextopezona(vdopeactividads *oact)
{
  int vdret;
  vdret=fetchcursor(vdseloactopezona);
  if (vdret==0) {
     *oact=svdopeactividad;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseloactopezona. vdret %d. \n",OACTlog(&svdopeactividad),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseloactopezona);
  return(VD_EERRORACLE);
}

int OACTselvdopeactividad(char *codope,long codzona,long feciniact,char *horainiact,vdopeactividads *oact)
{
  int vdret;
  if (vdseloactvdopeactividad==NULL) init_seloactvdopeactividad();
  memset(&svdopeactividad,0,sizeof(svdopeactividad));
  strcpy(svdopeactividad.codope,codope);
  svdopeactividad.codzona=codzona;
  svdopeactividad.feciniact=feciniact;
  strcpy(svdopeactividad.horainiact,horainiact);
  vdret=ejefetchcursor(vdseloactvdopeactividad);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseloactvdopeactividad. vdret %d. \n",OACTlog(&svdopeactividad),vdret);
    return(VD_EERRORACLE);
   }
  *oact=svdopeactividad;
  return(vdret);
}

int OACTactualizacierrezona(vdopeactividads *oact,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando OACTactualizacierrezona:  %s .  \n",OACTlog(&svdopeactividad));
  if (vdupdaoactcierrezona==NULL) init_updaoactcierrezona();
  svdopeactividad=*oact;
  vdret=ejecutacursor(vdupdaoactcierrezona);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaoactcierrezona);
     getcurerrornombre(vdupdaoactcierrezona->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaoactcierrezona)!=1) return(VD_EERRORACLE);
  return(0);
}

int OACTinsert(vdopeactividads *oact,int error)
{
  int vdret;
  if (!vdinsoact) init_insoact();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",OACTlog(&svdopeactividad));
  svdopeactividad=*oact;
  vdret=ejecutacursor(vdinsoact);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsoact);
     getcurerrornombre(vdinsoact->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * OACTlog(vdopeactividads *oact)
{
    sprintf(msglogOACT, "VDOPEACTIVIDAD: codope %s codzona %ld feciniact %ld horainiact %s ",oact->codope,oact->codzona,oact->feciniact,oact->horainiact);
    return(msglogOACT);
}

char * OACTdebug(vdopeactividads *oact)
{
    debugestruct(&doact,oact,msgdebugOACT);
    return(msgdebugOACT);
}

