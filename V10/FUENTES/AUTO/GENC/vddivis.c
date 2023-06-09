// Modulo generado automaticamente a partir de VDDIVIS.DEF
//#***
//# VDDIVIS.c - Generaci�n autom�tica del c�digo c para la tabla de divisiones                                                   
//# 
//# Prop�sito: Funciones de acceso a la tabla VDDIVIS
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 14-04-2008                                             
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=DIV
//
//RECORRE=TODO;ORDERBY=CODDIV,CODEMP;
//INSERT 
//DELETE

#include "vd.h"
#define SELDIVTODO "SELECT VDDIVIS.ROWID,VDDIVIS.CODDIV,VDDIVIS.CODEMP, "\
                    " VDDIVIS.CODDIVEMP,VDDIVIS.DESDIV,VDDIVIS.DABDIV, "\
                    " VDDIVIS.NIF,VDDIVIS.CONTACTO,VDDIVIS.DIRECCION1, "\
                    " VDDIVIS.DIRECCION2,VDDIVIS.DIRECCION3,VDDIVIS.DIRECCION4, "\
                    " VDDIVIS.POBLACION,VDDIVIS.CODPAIS,VDDIVIS.CODPROV, "\
                    " VDDIVIS.DP,VDDIVIS.TELEFONO1,VDDIVIS.TELEFONO2, "\
                    " VDDIVIS.FAX1,VDDIVIS.FAX2,VDDIVIS.EMAIL, "\
                    " VDDIVIS.EDI,VDDIVIS.BUZONIN,VDDIVIS.BUZONOUT, "\
                    " VDDIVIS.CODEANEMP,VDDIVIS.SUFIJODOC,VDDIVIS.CODOPEMODIF, "\
                    " VDDIVIS.FECMODIF,VDDIVIS.HORAMODIF,VDDIVIS.CODCOMEN "\
        " FROM VDDIVIS"\
        " ORDER BY CODDIV,CODEMP "
static v10cursors *vdseldivtodo;

#define SELDIVVDDIVIS "SELECT VDDIVIS.ROWID,VDDIVIS.CODDIV,VDDIVIS.CODEMP, "\
                    " VDDIVIS.CODDIVEMP,VDDIVIS.DESDIV,VDDIVIS.DABDIV, "\
                    " VDDIVIS.NIF,VDDIVIS.CONTACTO,VDDIVIS.DIRECCION1, "\
                    " VDDIVIS.DIRECCION2,VDDIVIS.DIRECCION3,VDDIVIS.DIRECCION4, "\
                    " VDDIVIS.POBLACION,VDDIVIS.CODPAIS,VDDIVIS.CODPROV, "\
                    " VDDIVIS.DP,VDDIVIS.TELEFONO1,VDDIVIS.TELEFONO2, "\
                    " VDDIVIS.FAX1,VDDIVIS.FAX2,VDDIVIS.EMAIL, "\
                    " VDDIVIS.EDI,VDDIVIS.BUZONIN,VDDIVIS.BUZONOUT, "\
                    " VDDIVIS.CODEANEMP,VDDIVIS.SUFIJODOC,VDDIVIS.CODOPEMODIF, "\
                    " VDDIVIS.FECMODIF,VDDIVIS.HORAMODIF,VDDIVIS.CODCOMEN "\
        " FROM VDDIVIS"\
        " WHERE "\
               " VDDIVIS.CODDIV=:CODDIV "
static v10cursors *vdseldivvddivis;

#define INSDIV "INSERT INTO VDDIVIS (CODDIV,CODEMP,CODDIVEMP,DESDIV,DABDIV,NIF, "\
                    " CONTACTO,DIRECCION1,DIRECCION2,DIRECCION3,DIRECCION4,POBLACION,CODPAIS, "\
                    " CODPROV,DP,TELEFONO1,TELEFONO2,FAX1,FAX2,EMAIL, "\
                    " EDI,BUZONIN,BUZONOUT,CODEANEMP,SUFIJODOC,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :CODDIV,:CODEMP,:CODDIVEMP,:DESDIV,:DABDIV,:NIF, "\
                    " :CONTACTO,:DIRECCION1,:DIRECCION2,:DIRECCION3,:DIRECCION4,:POBLACION,:CODPAIS, "\
                    " :CODPROV,:DP,:TELEFONO1,:TELEFONO2,:FAX1,:FAX2,:EMAIL, "\
                    " :EDI,:BUZONIN,:BUZONOUT,:CODEANEMP,:SUFIJODOC,VDUSER.GETUSER,VD.FECHASYS, "\
                    " VD.HORASYS,:CODCOMEN) "
static v10cursors *vdinsdiv;

#define DELDIV "DELETE VDDIVIS WHERE ROWID=:MIROWID "
static v10cursors *vddeldiv;

static vddiviss svddivis;

static diccols colvddivis[]={
	{"ROWID",V10CADENA,(size_t)&svddivis.rowid,sizeof(svddivis.rowid)},
	{"CODDIV",V10CADENA,(size_t)&svddivis.coddiv,sizeof(svddivis.coddiv)},
	{"CODEMP",V10CADENA,(size_t)&svddivis.codemp,sizeof(svddivis.codemp)},
	{"CODDIVEMP",V10CADENA,(size_t)&svddivis.coddivemp,sizeof(svddivis.coddivemp)},
	{"DESDIV",V10CADENA,(size_t)&svddivis.desdiv,sizeof(svddivis.desdiv)},
	{"DABDIV",V10CADENA,(size_t)&svddivis.dabdiv,sizeof(svddivis.dabdiv)},
	{"NIF",V10CADENA,(size_t)&svddivis.nif,sizeof(svddivis.nif)},
	{"CONTACTO",V10CADENA,(size_t)&svddivis.contacto,sizeof(svddivis.contacto)},
	{"DIRECCION1",V10CADENA,(size_t)&svddivis.direccion1,sizeof(svddivis.direccion1)},
	{"DIRECCION2",V10CADENA,(size_t)&svddivis.direccion2,sizeof(svddivis.direccion2)},
	{"DIRECCION3",V10CADENA,(size_t)&svddivis.direccion3,sizeof(svddivis.direccion3)},
	{"DIRECCION4",V10CADENA,(size_t)&svddivis.direccion4,sizeof(svddivis.direccion4)},
	{"POBLACION",V10CADENA,(size_t)&svddivis.poblacion,sizeof(svddivis.poblacion)},
	{"CODPAIS",V10CADENA,(size_t)&svddivis.codpais,sizeof(svddivis.codpais)},
	{"CODPROV",V10CADENA,(size_t)&svddivis.codprov,sizeof(svddivis.codprov)},
	{"DP",V10CADENA,(size_t)&svddivis.dp,sizeof(svddivis.dp)},
	{"TELEFONO1",V10CADENA,(size_t)&svddivis.telefono1,sizeof(svddivis.telefono1)},
	{"TELEFONO2",V10CADENA,(size_t)&svddivis.telefono2,sizeof(svddivis.telefono2)},
	{"FAX1",V10CADENA,(size_t)&svddivis.fax1,sizeof(svddivis.fax1)},
	{"FAX2",V10CADENA,(size_t)&svddivis.fax2,sizeof(svddivis.fax2)},
	{"EMAIL",V10CADENA,(size_t)&svddivis.email,sizeof(svddivis.email)},
	{"EDI",V10CADENA,(size_t)&svddivis.edi,sizeof(svddivis.edi)},
	{"BUZONIN",V10CADENA,(size_t)&svddivis.buzonin,sizeof(svddivis.buzonin)},
	{"BUZONOUT",V10CADENA,(size_t)&svddivis.buzonout,sizeof(svddivis.buzonout)},
	{"CODEANEMP",V10CADENA,(size_t)&svddivis.codeanemp,sizeof(svddivis.codeanemp)},
	{"SUFIJODOC",V10CADENA,(size_t)&svddivis.sufijodoc,sizeof(svddivis.sufijodoc)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svddivis.codopemodif,sizeof(svddivis.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svddivis.fecmodif,sizeof(svddivis.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svddivis.horamodif,sizeof(svddivis.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svddivis.codcomen,sizeof(svddivis.codcomen)}
	};
static diccionarios dvddivis[]={
    {colvddivis,30}
};
diccionario ddiv={dvddivis,1};

static char msglogDIV[LCADENA];
static char msgdebugDIV[LCADENABIG];
static int init=0;


static void fin_vd_div(void)
{
if (vdseldivtodo) {
    liberacursor(vdseldivtodo);
    vdseldivtodo = NULL;
}
if (vdseldivvddivis) {
    liberacursor(vdseldivvddivis);
    vdseldivvddivis = NULL;
}
if (vdinsdiv != NULL) {
    liberacursor(vdinsdiv);
    vdinsdiv = NULL;
}
if (vddeldiv != NULL) {
    liberacursor(vddeldiv);
    vddeldiv = NULL;
}
}
static void init_seldivtodo(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddivis[0].numcol;nc++) dvddivis[0].c[nc].offset-=(size_t)&svddivis;
    vdseldivtodo=abrecursordebug(SELDIVTODO,1280);
    definetodo(vdseldivtodo,svddivis.rowid,sizeof(svddivis.rowid),V10CADENA,
                          svddivis.coddiv,sizeof(svddivis.coddiv),V10CADENA,
                          svddivis.codemp,sizeof(svddivis.codemp),V10CADENA,
                          svddivis.coddivemp,sizeof(svddivis.coddivemp),V10CADENA,
                          svddivis.desdiv,sizeof(svddivis.desdiv),V10CADENA,
                          svddivis.dabdiv,sizeof(svddivis.dabdiv),V10CADENA,
                          svddivis.nif,sizeof(svddivis.nif),V10CADENA,
                          svddivis.contacto,sizeof(svddivis.contacto),V10CADENA,
                          svddivis.direccion1,sizeof(svddivis.direccion1),V10CADENA,
                          svddivis.direccion2,sizeof(svddivis.direccion2),V10CADENA,
                          svddivis.direccion3,sizeof(svddivis.direccion3),V10CADENA,
                          svddivis.direccion4,sizeof(svddivis.direccion4),V10CADENA,
                          svddivis.poblacion,sizeof(svddivis.poblacion),V10CADENA,
                          svddivis.codpais,sizeof(svddivis.codpais),V10CADENA,
                          svddivis.codprov,sizeof(svddivis.codprov),V10CADENA,
                          svddivis.dp,sizeof(svddivis.dp),V10CADENA,
                          svddivis.telefono1,sizeof(svddivis.telefono1),V10CADENA,
                          svddivis.telefono2,sizeof(svddivis.telefono2),V10CADENA,
                          svddivis.fax1,sizeof(svddivis.fax1),V10CADENA,
                          svddivis.fax2,sizeof(svddivis.fax2),V10CADENA,
                          svddivis.email,sizeof(svddivis.email),V10CADENA,
                          svddivis.edi,sizeof(svddivis.edi),V10CADENA,
                          svddivis.buzonin,sizeof(svddivis.buzonin),V10CADENA,
                          svddivis.buzonout,sizeof(svddivis.buzonout),V10CADENA,
                          svddivis.codeanemp,sizeof(svddivis.codeanemp),V10CADENA,
                          svddivis.sufijodoc,sizeof(svddivis.sufijodoc),V10CADENA,
                          svddivis.codopemodif,sizeof(svddivis.codopemodif),V10CADENA,
                          &svddivis.fecmodif,sizeof(svddivis.fecmodif),V10LONG,
                          svddivis.horamodif,sizeof(svddivis.horamodif),V10CADENA,
                          &svddivis.codcomen,sizeof(svddivis.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseldivtodo,NULL);
    if (init == 0) {
        atexit(fin_vd_div);
        init = 1;
    }
}

static void init_seldivvddivis(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddivis[0].numcol;nc++) dvddivis[0].c[nc].offset-=(size_t)&svddivis;
    vdseldivvddivis=abrecursordebug(SELDIVVDDIVIS,1280);
    definetodo(vdseldivvddivis,svddivis.rowid,sizeof(svddivis.rowid),V10CADENA,
                          svddivis.coddiv,sizeof(svddivis.coddiv),V10CADENA,
                          svddivis.codemp,sizeof(svddivis.codemp),V10CADENA,
                          svddivis.coddivemp,sizeof(svddivis.coddivemp),V10CADENA,
                          svddivis.desdiv,sizeof(svddivis.desdiv),V10CADENA,
                          svddivis.dabdiv,sizeof(svddivis.dabdiv),V10CADENA,
                          svddivis.nif,sizeof(svddivis.nif),V10CADENA,
                          svddivis.contacto,sizeof(svddivis.contacto),V10CADENA,
                          svddivis.direccion1,sizeof(svddivis.direccion1),V10CADENA,
                          svddivis.direccion2,sizeof(svddivis.direccion2),V10CADENA,
                          svddivis.direccion3,sizeof(svddivis.direccion3),V10CADENA,
                          svddivis.direccion4,sizeof(svddivis.direccion4),V10CADENA,
                          svddivis.poblacion,sizeof(svddivis.poblacion),V10CADENA,
                          svddivis.codpais,sizeof(svddivis.codpais),V10CADENA,
                          svddivis.codprov,sizeof(svddivis.codprov),V10CADENA,
                          svddivis.dp,sizeof(svddivis.dp),V10CADENA,
                          svddivis.telefono1,sizeof(svddivis.telefono1),V10CADENA,
                          svddivis.telefono2,sizeof(svddivis.telefono2),V10CADENA,
                          svddivis.fax1,sizeof(svddivis.fax1),V10CADENA,
                          svddivis.fax2,sizeof(svddivis.fax2),V10CADENA,
                          svddivis.email,sizeof(svddivis.email),V10CADENA,
                          svddivis.edi,sizeof(svddivis.edi),V10CADENA,
                          svddivis.buzonin,sizeof(svddivis.buzonin),V10CADENA,
                          svddivis.buzonout,sizeof(svddivis.buzonout),V10CADENA,
                          svddivis.codeanemp,sizeof(svddivis.codeanemp),V10CADENA,
                          svddivis.sufijodoc,sizeof(svddivis.sufijodoc),V10CADENA,
                          svddivis.codopemodif,sizeof(svddivis.codopemodif),V10CADENA,
                          &svddivis.fecmodif,sizeof(svddivis.fecmodif),V10LONG,
                          svddivis.horamodif,sizeof(svddivis.horamodif),V10CADENA,
                          &svddivis.codcomen,sizeof(svddivis.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseldivvddivis,"CODDIV",svddivis.coddiv,sizeof(svddivis.coddiv),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_div);
        init = 1;
    }
}

static void init_insdiv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddivis[0].numcol;nc++) dvddivis[0].c[nc].offset-=(size_t)&svddivis;
    vdinsdiv=abrecursordebug(INSDIV,1280);
    bindtodo(vdinsdiv,"CODDIV",svddivis.coddiv,sizeof(svddivis.coddiv),V10CADENA,
                          "CODEMP",svddivis.codemp,sizeof(svddivis.codemp),V10CADENA,
                          "CODDIVEMP",svddivis.coddivemp,sizeof(svddivis.coddivemp),V10CADENA,
                          "DESDIV",svddivis.desdiv,sizeof(svddivis.desdiv),V10CADENA,
                          "DABDIV",svddivis.dabdiv,sizeof(svddivis.dabdiv),V10CADENA,
                          "NIF",svddivis.nif,sizeof(svddivis.nif),V10CADENA,
                          "CONTACTO",svddivis.contacto,sizeof(svddivis.contacto),V10CADENA,
                          "DIRECCION1",svddivis.direccion1,sizeof(svddivis.direccion1),V10CADENA,
                          "DIRECCION2",svddivis.direccion2,sizeof(svddivis.direccion2),V10CADENA,
                          "DIRECCION3",svddivis.direccion3,sizeof(svddivis.direccion3),V10CADENA,
                          "DIRECCION4",svddivis.direccion4,sizeof(svddivis.direccion4),V10CADENA,
                          "POBLACION",svddivis.poblacion,sizeof(svddivis.poblacion),V10CADENA,
                          "CODPAIS",svddivis.codpais,sizeof(svddivis.codpais),V10CADENA,
                          "CODPROV",svddivis.codprov,sizeof(svddivis.codprov),V10CADENA,
                          "DP",svddivis.dp,sizeof(svddivis.dp),V10CADENA,
                          "TELEFONO1",svddivis.telefono1,sizeof(svddivis.telefono1),V10CADENA,
                          "TELEFONO2",svddivis.telefono2,sizeof(svddivis.telefono2),V10CADENA,
                          "FAX1",svddivis.fax1,sizeof(svddivis.fax1),V10CADENA,
                          "FAX2",svddivis.fax2,sizeof(svddivis.fax2),V10CADENA,
                          "EMAIL",svddivis.email,sizeof(svddivis.email),V10CADENA,
                          "EDI",svddivis.edi,sizeof(svddivis.edi),V10CADENA,
                          "BUZONIN",svddivis.buzonin,sizeof(svddivis.buzonin),V10CADENA,
                          "BUZONOUT",svddivis.buzonout,sizeof(svddivis.buzonout),V10CADENA,
                          "CODEANEMP",svddivis.codeanemp,sizeof(svddivis.codeanemp),V10CADENA,
                          "SUFIJODOC",svddivis.sufijodoc,sizeof(svddivis.sufijodoc),V10CADENA,
                          "CODCOMEN",&svddivis.codcomen,sizeof(svddivis.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_div);
        init = 1;
    }
}

static void init_deldiv(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddivis[0].numcol;nc++) dvddivis[0].c[nc].offset-=(size_t)&svddivis;
    vddeldiv=abrecursordebug(DELDIV,1280);
    bindtodo(vddeldiv,"MIROWID",svddivis.rowid,sizeof(svddivis.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_div);
        init = 1;
    }
}

diccionario *DIVdamediccionario(void)
{
     return(&ddiv);
}

int DIVbuscatodo(vddiviss *div)
{
  int vdret;
  memset(&svddivis,0,sizeof(svddivis));
  if (vdseldivtodo==NULL) init_seldivtodo();
  vdret=ejefetchcursor(vdseldivtodo);
  if (vdret==0) {
     *div=svddivis;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldivtodo. vdret %d. \n",DIVlog(&svddivis),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DIVnexttodo(vddiviss *div)
{
  int vdret;
  vdret=fetchcursor(vdseldivtodo);
  if (vdret==0) {
     *div=svddivis;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldivtodo. vdret %d. \n",DIVlog(&svddivis),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldivtodo);
  return(VD_EERRORACLE);
}

int DIVselvddivis(char *coddiv,vddiviss *div)
{
  int vdret;
  if (vdseldivvddivis==NULL) init_seldivvddivis();
  memset(&svddivis,0,sizeof(svddivis));
  strcpy(svddivis.coddiv,coddiv);
  vdret=ejefetchcursor(vdseldivvddivis);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldivvddivis. vdret %d. \n",DIVlog(&svddivis),vdret);
    return(VD_EERRORACLE);
   }
  *div=svddivis;
  return(vdret);
}

int DIVinsert(vddiviss *div,int error)
{
  int vdret;
  if (!vdinsdiv) init_insdiv();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",DIVlog(&svddivis));
  svddivis=*div;
  vdret=ejecutacursor(vdinsdiv);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsdiv);
     getcurerrornombre(vdinsdiv->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int DIVdel(vddiviss *div,int error)
{
  int vdret;
  svddivis=*div;
  if (vddeldiv==NULL) init_deldiv();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",DIVlog(&svddivis));
  vdret=ejecutacursor(vddeldiv);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddeldiv);
     getcurerrornombre(vddeldiv->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * DIVlog(vddiviss *div)
{
    sprintf(msglogDIV, "VDDIVIS: coddiv %s ",div->coddiv);
    return(msglogDIV);
}

char * DIVdebug(vddiviss *div)
{
    debugestruct(&ddiv,div,msgdebugDIV);
    return(msgdebugDIV);
}

