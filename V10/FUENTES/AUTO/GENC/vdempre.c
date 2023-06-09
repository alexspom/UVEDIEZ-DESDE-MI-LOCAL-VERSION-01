// Modulo generado automaticamente a partir de VDEMPRE.DEF
//#***
//# VDEMPRE.c - Generaci�n autom�tica del c�digo c para la tabla de empresas                                                      
//# 
//# Prop�sito: Funciones de acceso a la tabla VDEMPRE
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 11-08-2008                                          
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=EMPRE
//
//
//

#include "vd.h"
#define SELEMPREVDEMPRE "SELECT VDEMPRE.ROWID,VDEMPRE.CODEMP,VDEMPRE.DESEMP, "\
                    " VDEMPRE.DABEMP,VDEMPRE.NIF,VDEMPRE.CONTACTO, "\
                    " VDEMPRE.DIRECCION1,VDEMPRE.DIRECCION2,VDEMPRE.DIRECCION3, "\
                    " VDEMPRE.DIRECCION4,VDEMPRE.POBLACION,VDEMPRE.CODPAIS, "\
                    " VDEMPRE.CODPROV,VDEMPRE.DP,VDEMPRE.TELEFONO1, "\
                    " VDEMPRE.TELEFONO2,VDEMPRE.FAX1,VDEMPRE.FAX2, "\
                    " VDEMPRE.EMAIL,VDEMPRE.EDI,VDEMPRE.SUFIJODOC, "\
                    " VDEMPRE.CODOPEMODIF,VDEMPRE.FECMODIF,VDEMPRE.HORAMODIF, "\
                    " VDEMPRE.CODCOMEN "\
        " FROM VDEMPRE"\
        " WHERE "\
               " VDEMPRE.CODEMP=:CODEMP "
static v10cursors *vdselemprevdempre;

static vdempres svdempre;

static diccols colvdempre[]={
	{"ROWID",V10CADENA,(size_t)&svdempre.rowid,sizeof(svdempre.rowid)},
	{"CODEMP",V10CADENA,(size_t)&svdempre.codemp,sizeof(svdempre.codemp)},
	{"DESEMP",V10CADENA,(size_t)&svdempre.desemp,sizeof(svdempre.desemp)},
	{"DABEMP",V10CADENA,(size_t)&svdempre.dabemp,sizeof(svdempre.dabemp)},
	{"NIF",V10CADENA,(size_t)&svdempre.nif,sizeof(svdempre.nif)},
	{"CONTACTO",V10CADENA,(size_t)&svdempre.contacto,sizeof(svdempre.contacto)},
	{"DIRECCION1",V10CADENA,(size_t)&svdempre.direccion1,sizeof(svdempre.direccion1)},
	{"DIRECCION2",V10CADENA,(size_t)&svdempre.direccion2,sizeof(svdempre.direccion2)},
	{"DIRECCION3",V10CADENA,(size_t)&svdempre.direccion3,sizeof(svdempre.direccion3)},
	{"DIRECCION4",V10CADENA,(size_t)&svdempre.direccion4,sizeof(svdempre.direccion4)},
	{"POBLACION",V10CADENA,(size_t)&svdempre.poblacion,sizeof(svdempre.poblacion)},
	{"CODPAIS",V10CADENA,(size_t)&svdempre.codpais,sizeof(svdempre.codpais)},
	{"CODPROV",V10CADENA,(size_t)&svdempre.codprov,sizeof(svdempre.codprov)},
	{"DP",V10CADENA,(size_t)&svdempre.dp,sizeof(svdempre.dp)},
	{"TELEFONO1",V10CADENA,(size_t)&svdempre.telefono1,sizeof(svdempre.telefono1)},
	{"TELEFONO2",V10CADENA,(size_t)&svdempre.telefono2,sizeof(svdempre.telefono2)},
	{"FAX1",V10CADENA,(size_t)&svdempre.fax1,sizeof(svdempre.fax1)},
	{"FAX2",V10CADENA,(size_t)&svdempre.fax2,sizeof(svdempre.fax2)},
	{"EMAIL",V10CADENA,(size_t)&svdempre.email,sizeof(svdempre.email)},
	{"EDI",V10CADENA,(size_t)&svdempre.edi,sizeof(svdempre.edi)},
	{"SUFIJODOC",V10CADENA,(size_t)&svdempre.sufijodoc,sizeof(svdempre.sufijodoc)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdempre.codopemodif,sizeof(svdempre.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdempre.fecmodif,sizeof(svdempre.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdempre.horamodif,sizeof(svdempre.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdempre.codcomen,sizeof(svdempre.codcomen)}
	};
static diccionarios dvdempre[]={
    {colvdempre,25}
};
diccionario dempre={dvdempre,1};

static char msglogEMPRE[LCADENA];
static char msgdebugEMPRE[LCADENABIG];
static int init=0;


static void fin_vd_empre(void)
{
if (vdselemprevdempre) {
    liberacursor(vdselemprevdempre);
    vdselemprevdempre = NULL;
}
}
static void init_selemprevdempre(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdempre[0].numcol;nc++) dvdempre[0].c[nc].offset-=(size_t)&svdempre;
    vdselemprevdempre=abrecursordebug(SELEMPREVDEMPRE,1280);
    definetodo(vdselemprevdempre,svdempre.rowid,sizeof(svdempre.rowid),V10CADENA,
                          svdempre.codemp,sizeof(svdempre.codemp),V10CADENA,
                          svdempre.desemp,sizeof(svdempre.desemp),V10CADENA,
                          svdempre.dabemp,sizeof(svdempre.dabemp),V10CADENA,
                          svdempre.nif,sizeof(svdempre.nif),V10CADENA,
                          svdempre.contacto,sizeof(svdempre.contacto),V10CADENA,
                          svdempre.direccion1,sizeof(svdempre.direccion1),V10CADENA,
                          svdempre.direccion2,sizeof(svdempre.direccion2),V10CADENA,
                          svdempre.direccion3,sizeof(svdempre.direccion3),V10CADENA,
                          svdempre.direccion4,sizeof(svdempre.direccion4),V10CADENA,
                          svdempre.poblacion,sizeof(svdempre.poblacion),V10CADENA,
                          svdempre.codpais,sizeof(svdempre.codpais),V10CADENA,
                          svdempre.codprov,sizeof(svdempre.codprov),V10CADENA,
                          svdempre.dp,sizeof(svdempre.dp),V10CADENA,
                          svdempre.telefono1,sizeof(svdempre.telefono1),V10CADENA,
                          svdempre.telefono2,sizeof(svdempre.telefono2),V10CADENA,
                          svdempre.fax1,sizeof(svdempre.fax1),V10CADENA,
                          svdempre.fax2,sizeof(svdempre.fax2),V10CADENA,
                          svdempre.email,sizeof(svdempre.email),V10CADENA,
                          svdempre.edi,sizeof(svdempre.edi),V10CADENA,
                          svdempre.sufijodoc,sizeof(svdempre.sufijodoc),V10CADENA,
                          svdempre.codopemodif,sizeof(svdempre.codopemodif),V10CADENA,
                          &svdempre.fecmodif,sizeof(svdempre.fecmodif),V10LONG,
                          svdempre.horamodif,sizeof(svdempre.horamodif),V10CADENA,
                          &svdempre.codcomen,sizeof(svdempre.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselemprevdempre,"CODEMP",svdempre.codemp,sizeof(svdempre.codemp),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_empre);
        init = 1;
    }
}

diccionario *EMPREdamediccionario(void)
{
     return(&dempre);
}

int EMPREselvdempre(char *codemp,vdempres *empre)
{
  int vdret;
  if (vdselemprevdempre==NULL) init_selemprevdempre();
  memset(&svdempre,0,sizeof(svdempre));
  strcpy(svdempre.codemp,codemp);
  vdret=ejefetchcursor(vdselemprevdempre);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselemprevdempre. vdret %d. \n",EMPRElog(&svdempre),vdret);
    return(VD_EERRORACLE);
   }
  *empre=svdempre;
  return(vdret);
}

char * EMPRElog(vdempres *empre)
{
    sprintf(msglogEMPRE, "VDEMPRE: codemp %s ",empre->codemp);
    return(msglogEMPRE);
}

char * EMPREdebug(vdempres *empre)
{
    debugestruct(&dempre,empre,msgdebugEMPRE);
    return(msgdebugEMPRE);
}

