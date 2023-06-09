// Modulo generado automaticamente a partir de VDALMA.DEF
//#***
//# VDALMA.c - Generaci�n autom�tica del c�digo c para la tabla de almacenes                                                      
//# 
//# Prop�sito: Funciones de acceso a la tabla VDALMA
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 11-12-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=ALM

#include "vd.h"
#define SELALMVDALMA "SELECT VDALMA.ROWID,VDALMA.CODALM,VDALMA.DESALM, "\
                    " VDALMA.CONTACTO,VDALMA.DIRECCION1,VDALMA.DIRECCION2, "\
                    " VDALMA.DIRECCION3,VDALMA.DIRECCION4,VDALMA.POBLACION, "\
                    " VDALMA.CODPAIS,VDALMA.CODPROV,VDALMA.DP, "\
                    " VDALMA.TELEFONO1,VDALMA.TELEFONO2,VDALMA.FAX1, "\
                    " VDALMA.FAX2,VDALMA.EMAIL,VDALMA.EDI, "\
                    " VDALMA.CODOPEMODIF,VDALMA.FECMODIF,VDALMA.HORAMODIF, "\
                    " VDALMA.CODCOMEN "\
        " FROM VDALMA"\
        " WHERE "\
               " VDALMA.CODALM=:CODALM "
static v10cursors *vdselalmvdalma;

static vdalmas svdalma;

static diccols colvdalma[]={
	{"ROWID",V10CADENA,(size_t)&svdalma.rowid,sizeof(svdalma.rowid)},
	{"CODALM",V10CADENA,(size_t)&svdalma.codalm,sizeof(svdalma.codalm)},
	{"DESALM",V10CADENA,(size_t)&svdalma.desalm,sizeof(svdalma.desalm)},
	{"CONTACTO",V10CADENA,(size_t)&svdalma.contacto,sizeof(svdalma.contacto)},
	{"DIRECCION1",V10CADENA,(size_t)&svdalma.direccion1,sizeof(svdalma.direccion1)},
	{"DIRECCION2",V10CADENA,(size_t)&svdalma.direccion2,sizeof(svdalma.direccion2)},
	{"DIRECCION3",V10CADENA,(size_t)&svdalma.direccion3,sizeof(svdalma.direccion3)},
	{"DIRECCION4",V10CADENA,(size_t)&svdalma.direccion4,sizeof(svdalma.direccion4)},
	{"POBLACION",V10CADENA,(size_t)&svdalma.poblacion,sizeof(svdalma.poblacion)},
	{"CODPAIS",V10CADENA,(size_t)&svdalma.codpais,sizeof(svdalma.codpais)},
	{"CODPROV",V10CADENA,(size_t)&svdalma.codprov,sizeof(svdalma.codprov)},
	{"DP",V10CADENA,(size_t)&svdalma.dp,sizeof(svdalma.dp)},
	{"TELEFONO1",V10CADENA,(size_t)&svdalma.telefono1,sizeof(svdalma.telefono1)},
	{"TELEFONO2",V10CADENA,(size_t)&svdalma.telefono2,sizeof(svdalma.telefono2)},
	{"FAX1",V10CADENA,(size_t)&svdalma.fax1,sizeof(svdalma.fax1)},
	{"FAX2",V10CADENA,(size_t)&svdalma.fax2,sizeof(svdalma.fax2)},
	{"EMAIL",V10CADENA,(size_t)&svdalma.email,sizeof(svdalma.email)},
	{"EDI",V10CADENA,(size_t)&svdalma.edi,sizeof(svdalma.edi)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdalma.codopemodif,sizeof(svdalma.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdalma.fecmodif,sizeof(svdalma.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdalma.horamodif,sizeof(svdalma.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdalma.codcomen,sizeof(svdalma.codcomen)}
	};
static diccionarios dvdalma[]={
    {colvdalma,22}
};
diccionario dalm={dvdalma,1};

static char msglogALM[LCADENA];
static char msgdebugALM[LCADENABIG];
static int init=0;


static void fin_vd_alm(void)
{
if (vdselalmvdalma) {
    liberacursor(vdselalmvdalma);
    vdselalmvdalma = NULL;
}
}
static void init_selalmvdalma(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdalma[0].numcol;nc++) dvdalma[0].c[nc].offset-=(size_t)&svdalma;
    vdselalmvdalma=abrecursordebug(SELALMVDALMA,1280);
    definetodo(vdselalmvdalma,svdalma.rowid,sizeof(svdalma.rowid),V10CADENA,
                          svdalma.codalm,sizeof(svdalma.codalm),V10CADENA,
                          svdalma.desalm,sizeof(svdalma.desalm),V10CADENA,
                          svdalma.contacto,sizeof(svdalma.contacto),V10CADENA,
                          svdalma.direccion1,sizeof(svdalma.direccion1),V10CADENA,
                          svdalma.direccion2,sizeof(svdalma.direccion2),V10CADENA,
                          svdalma.direccion3,sizeof(svdalma.direccion3),V10CADENA,
                          svdalma.direccion4,sizeof(svdalma.direccion4),V10CADENA,
                          svdalma.poblacion,sizeof(svdalma.poblacion),V10CADENA,
                          svdalma.codpais,sizeof(svdalma.codpais),V10CADENA,
                          svdalma.codprov,sizeof(svdalma.codprov),V10CADENA,
                          svdalma.dp,sizeof(svdalma.dp),V10CADENA,
                          svdalma.telefono1,sizeof(svdalma.telefono1),V10CADENA,
                          svdalma.telefono2,sizeof(svdalma.telefono2),V10CADENA,
                          svdalma.fax1,sizeof(svdalma.fax1),V10CADENA,
                          svdalma.fax2,sizeof(svdalma.fax2),V10CADENA,
                          svdalma.email,sizeof(svdalma.email),V10CADENA,
                          svdalma.edi,sizeof(svdalma.edi),V10CADENA,
                          svdalma.codopemodif,sizeof(svdalma.codopemodif),V10CADENA,
                          &svdalma.fecmodif,sizeof(svdalma.fecmodif),V10LONG,
                          svdalma.horamodif,sizeof(svdalma.horamodif),V10CADENA,
                          &svdalma.codcomen,sizeof(svdalma.codcomen),V10LONG,
                          NULL);
    bindtodo(vdselalmvdalma,"CODALM",svdalma.codalm,sizeof(svdalma.codalm),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_alm);
        init = 1;
    }
}

diccionario *ALMdamediccionario(void)
{
     return(&dalm);
}

int ALMselvdalma(char *codalm,vdalmas *alm)
{
  int vdret;
  if (vdselalmvdalma==NULL) init_selalmvdalma();
  memset(&svdalma,0,sizeof(svdalma));
  strcpy(svdalma.codalm,codalm);
  vdret=ejefetchcursor(vdselalmvdalma);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselalmvdalma. vdret %d. \n",ALMlog(&svdalma),vdret);
    return(VD_EERRORACLE);
   }
  *alm=svdalma;
  return(vdret);
}

char * ALMlog(vdalmas *alm)
{
    sprintf(msglogALM, "VDALMA: codalm %s ",alm->codalm);
    return(msglogALM);
}

char * ALMdebug(vdalmas *alm)
{
    debugestruct(&dalm,alm,msgdebugALM);
    return(msgdebugALM);
}

