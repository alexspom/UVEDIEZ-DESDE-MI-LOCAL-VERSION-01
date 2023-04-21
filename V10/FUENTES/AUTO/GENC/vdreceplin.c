// Modulo generado automaticamente a partir de VDRECEPLIN.DEF
//# M¢dulo : VDRECEPLIN.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDRECEPLIN
//#                        
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 05-05-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=LRE
//
//
//CLAVE=CANTRECEP,CODORDREC,CODDIV,SECLINORD,GENSUM=CANTIDADR;
//

#include "vd.h"
#define SELLRECANTRECEP "SELECT SUM(CANTIDADR) GENSUM "\
        " FROM VDRECEPLIN"\
        " WHERE "\
               " VDRECEPLIN.CODORDREC=:CODORDREC "\
               " AND VDRECEPLIN.CODDIV=:CODDIV "\
               " AND VDRECEPLIN.SECLINORD=:SECLINORD "
static v10cursors *vdsellrecantrecep;

#define SELLREVDRECEPLIN "SELECT VDRECEPLIN.ROWID,VDRECEPLIN.CODRECEP,VDRECEPLIN.SECLINREC, "\
                    " VDRECEPLIN.CODORDREC,VDRECEPLIN.CODDIV,VDRECEPLIN.SECLINORD, "\
                    " VDRECEPLIN.CODART,VDRECEPLIN.CLAVEEXT,VDRECEPLIN.CANTIDADR, "\
                    " VDRECEPLIN.CANTIDADT,VDRECEPLIN.CODLOT,VDRECEPLIN.CADUCI, "\
                    " VDRECEPLIN.BLOQSTOCK,VDRECEPLIN.CODCOMEN,VDRECEPLIN.VDEXTRA, "\
                    " VDRECEPLIN.OBSERVACION1,VDRECEPLIN.OBSERVACION2,VDRECEPLIN.MUESTREADO, "\
                    " VDRECEPLIN.CODOPEMODIF,VDRECEPLIN.FECMODIF,VDRECEPLIN.HORAMODIF "\
        " FROM VDRECEPLIN"\
        " WHERE "\
               " VDRECEPLIN.CODRECEP=:CODRECEP "\
               " AND VDRECEPLIN.SECLINREC=:SECLINREC "
static v10cursors *vdsellrevdreceplin;

static vdreceplins svdreceplin;

static diccols colvdreceplin[]={
	{"ROWID",V10CADENA,(size_t)&svdreceplin.rowid,sizeof(svdreceplin.rowid)},
	{"CODRECEP",V10CADENA,(size_t)&svdreceplin.codrecep,sizeof(svdreceplin.codrecep)},
	{"SECLINREC",V10LONG,(size_t)&svdreceplin.seclinrec,sizeof(svdreceplin.seclinrec)},
	{"CODORDREC",V10CADENA,(size_t)&svdreceplin.codordrec,sizeof(svdreceplin.codordrec)},
	{"CODDIV",V10CADENA,(size_t)&svdreceplin.coddiv,sizeof(svdreceplin.coddiv)},
	{"SECLINORD",V10LONG,(size_t)&svdreceplin.seclinord,sizeof(svdreceplin.seclinord)},
	{"CODART",V10CADENA,(size_t)&svdreceplin.codart,sizeof(svdreceplin.codart)},
	{"CLAVEEXT",V10CADENA,(size_t)&svdreceplin.claveext,sizeof(svdreceplin.claveext)},
	{"CANTIDADR",V10DOUBLE,(size_t)&svdreceplin.cantidadr,sizeof(svdreceplin.cantidadr)},
	{"CANTIDADT",V10DOUBLE,(size_t)&svdreceplin.cantidadt,sizeof(svdreceplin.cantidadt)},
	{"CODLOT",V10CADENA,(size_t)&svdreceplin.codlot,sizeof(svdreceplin.codlot)},
	{"CADUCI",V10CADENA,(size_t)&svdreceplin.caduci,sizeof(svdreceplin.caduci)},
	{"BLOQSTOCK",V10CADENA,(size_t)&svdreceplin.bloqstock,sizeof(svdreceplin.bloqstock)},
	{"CODCOMEN",V10LONG,(size_t)&svdreceplin.codcomen,sizeof(svdreceplin.codcomen)},
	{"VDEXTRA",V10CADENA,(size_t)&svdreceplin.vdextra,sizeof(svdreceplin.vdextra)},
	{"OBSERVACION1",V10CADENA,(size_t)&svdreceplin.observacion1,sizeof(svdreceplin.observacion1)},
	{"OBSERVACION2",V10CADENA,(size_t)&svdreceplin.observacion2,sizeof(svdreceplin.observacion2)},
	{"MUESTREADO",V10CADENA,(size_t)&svdreceplin.muestreado,sizeof(svdreceplin.muestreado)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdreceplin.codopemodif,sizeof(svdreceplin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdreceplin.fecmodif,sizeof(svdreceplin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdreceplin.horamodif,sizeof(svdreceplin.horamodif)},
	{"GENSUM",V10DOUBLE,(size_t)&svdreceplin.gensum,sizeof(svdreceplin.gensum)}
	};
static diccionarios dvdreceplin[]={
    {colvdreceplin,22}
};
diccionario dlre={dvdreceplin,1};

static char msglogLRE[LCADENA];
static char msgdebugLRE[LCADENABIG];
static int init=0;


static void fin_vd_lre(void)
{
if (vdsellrecantrecep) {
    liberacursor(vdsellrecantrecep);
    vdsellrecantrecep = NULL;
}
if (vdsellrevdreceplin) {
    liberacursor(vdsellrevdreceplin);
    vdsellrevdreceplin = NULL;
}
}
static void init_sellrecantrecep(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdreceplin[0].numcol;nc++) dvdreceplin[0].c[nc].offset-=(size_t)&svdreceplin;
    vdsellrecantrecep=abrecursordebug(SELLRECANTRECEP,1280);
    definetodo(vdsellrecantrecep,&svdreceplin.gensum,sizeof(svdreceplin.gensum),V10DOUBLE,
                          NULL);
    bindtodo(vdsellrecantrecep,"CODORDREC",svdreceplin.codordrec,sizeof(svdreceplin.codordrec),V10CADENA,
                          "CODDIV",svdreceplin.coddiv,sizeof(svdreceplin.coddiv),V10CADENA,
                          "SECLINORD",&svdreceplin.seclinord,sizeof(svdreceplin.seclinord),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lre);
        init = 1;
    }
}

static void init_sellrevdreceplin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdreceplin[0].numcol;nc++) dvdreceplin[0].c[nc].offset-=(size_t)&svdreceplin;
    vdsellrevdreceplin=abrecursordebug(SELLREVDRECEPLIN,1280);
    definetodo(vdsellrevdreceplin,svdreceplin.rowid,sizeof(svdreceplin.rowid),V10CADENA,
                          svdreceplin.codrecep,sizeof(svdreceplin.codrecep),V10CADENA,
                          &svdreceplin.seclinrec,sizeof(svdreceplin.seclinrec),V10LONG,
                          svdreceplin.codordrec,sizeof(svdreceplin.codordrec),V10CADENA,
                          svdreceplin.coddiv,sizeof(svdreceplin.coddiv),V10CADENA,
                          &svdreceplin.seclinord,sizeof(svdreceplin.seclinord),V10LONG,
                          svdreceplin.codart,sizeof(svdreceplin.codart),V10CADENA,
                          svdreceplin.claveext,sizeof(svdreceplin.claveext),V10CADENA,
                          &svdreceplin.cantidadr,sizeof(svdreceplin.cantidadr),V10DOUBLE,
                          &svdreceplin.cantidadt,sizeof(svdreceplin.cantidadt),V10DOUBLE,
                          svdreceplin.codlot,sizeof(svdreceplin.codlot),V10CADENA,
                          svdreceplin.caduci,sizeof(svdreceplin.caduci),V10CADENA,
                          svdreceplin.bloqstock,sizeof(svdreceplin.bloqstock),V10CADENA,
                          &svdreceplin.codcomen,sizeof(svdreceplin.codcomen),V10LONG,
                          svdreceplin.vdextra,sizeof(svdreceplin.vdextra),V10CADENA,
                          svdreceplin.observacion1,sizeof(svdreceplin.observacion1),V10CADENA,
                          svdreceplin.observacion2,sizeof(svdreceplin.observacion2),V10CADENA,
                          svdreceplin.muestreado,sizeof(svdreceplin.muestreado),V10CADENA,
                          svdreceplin.codopemodif,sizeof(svdreceplin.codopemodif),V10CADENA,
                          &svdreceplin.fecmodif,sizeof(svdreceplin.fecmodif),V10LONG,
                          svdreceplin.horamodif,sizeof(svdreceplin.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdsellrevdreceplin,"CODRECEP",svdreceplin.codrecep,sizeof(svdreceplin.codrecep),V10CADENA,
                          "SECLINREC",&svdreceplin.seclinrec,sizeof(svdreceplin.seclinrec),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_lre);
        init = 1;
    }
}

diccionario *LREdamediccionario(void)
{
     return(&dlre);
}

int LREselcantrecep(char *codordrec,char *coddiv,long seclinord,vdreceplins *lre)
{
  int vdret;
  if (vdsellrecantrecep==NULL) init_sellrecantrecep();
  memset(&svdreceplin,0,sizeof(svdreceplin));
  strcpy(svdreceplin.codordrec,codordrec);
  strcpy(svdreceplin.coddiv,coddiv);
  svdreceplin.seclinord=seclinord;
  vdret=ejefetchcursor(vdsellrecantrecep);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellrecantrecep. vdret %d. \n",LRElog(&svdreceplin),vdret);
    return(VD_EERRORACLE);
   }
  *lre=svdreceplin;
  return(vdret);
}

int LREselvdreceplin(char *codrecep,long seclinrec,vdreceplins *lre)
{
  int vdret;
  if (vdsellrevdreceplin==NULL) init_sellrevdreceplin();
  memset(&svdreceplin,0,sizeof(svdreceplin));
  strcpy(svdreceplin.codrecep,codrecep);
  svdreceplin.seclinrec=seclinrec;
  vdret=ejefetchcursor(vdsellrevdreceplin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdsellrevdreceplin. vdret %d. \n",LRElog(&svdreceplin),vdret);
    return(VD_EERRORACLE);
   }
  *lre=svdreceplin;
  return(vdret);
}

char * LRElog(vdreceplins *lre)
{
    sprintf(msglogLRE, "VDRECEPLIN: codrecep %s seclinrec %ld ",lre->codrecep,lre->seclinrec);
    return(msglogLRE);
}

char * LREdebug(vdreceplins *lre)
{
    debugestruct(&dlre,lre,msgdebugLRE);
    return(msgdebugLRE);
}

