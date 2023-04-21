// Modulo generado automaticamente a partir de VDPERFILTAREA.DEF
//#***
//# VDPERFILTAREA.DEF - Generación automática del código c para la tabla de perfiles
//#
//# Propósito: Funciones de acceso a la tabla VDAGENCIA
//#
//# Autor	 : EAA
//# Revisado por:
//# Fecha  : 12-03-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=PER
//PRIMARIA=CODPERFIL
//CLAVE=CODPERFIL,CODPERFIL

#include "vd.h"
#define SELPERCODPERFIL "SELECT VDPERFILTAREA.ROWID,VDPERFILTAREA.CODPERFIL,VDPERFILTAREA.DESPERFIL, "\
                    " VDPERFILTAREA.NPANTALLA,VDPERFILTAREA.RANTAREA,VDPERFILTAREA.RANAREAORI, "\
                    " VDPERFILTAREA.RANAREADEST,VDPERFILTAREA.CODCLASIFUBI,VDPERFILTAREA.RANCLASEUBIORI, "\
                    " VDPERFILTAREA.RANCLASEUBIDEST,VDPERFILTAREA.CODCLASIFART,VDPERFILTAREA.RANCLASEART, "\
                    " VDPERFILTAREA.RANCODZONORI,VDPERFILTAREA.RANCODZONDEST,VDPERFILTAREA.CONTENEDORES, "\
                    " VDPERFILTAREA.EMBALAJES,VDPERFILTAREA.UNIDADESSUELTAS,VDPERFILTAREA.PRIVILEGIOSTAREA, "\
                    " VDPERFILTAREA.MINALT,VDPERFILTAREA.MAXALT,VDPERFILTAREA.AGRUPAORIG, "\
                    " VDPERFILTAREA.AGRUPADEST,VDPERFILTAREA.AGRUPASERIE,VDPERFILTAREA.MAXAGRUPA, "\
                    " VDPERFILTAREA.FORMPLANIF,VDPERFILTAREA.VDEXTRA,VDPERFILTAREA.CODCOMEN, "\
                    " VDPERFILTAREA.CODOPEMODIF,VDPERFILTAREA.FECMODIF,VDPERFILTAREA.HORAMODIF, "\
                    " VDPERFILTAREA.MAXPRIOMOV,VDPERFILTAREA.MINPRIOMOV,VDPERFILTAREA.ASIGNAMOV, "\
                    " VDPERFILTAREA.FUNPLANIF "\
        " FROM VDPERFILTAREA"\
        " WHERE "\
               " VDPERFILTAREA.CODPERFIL=:CODPERFIL "
static v10cursors *vdselpercodperfil;

#define SELPERVDPERFILTAREA "SELECT VDPERFILTAREA.ROWID,VDPERFILTAREA.CODPERFIL,VDPERFILTAREA.DESPERFIL, "\
                    " VDPERFILTAREA.NPANTALLA,VDPERFILTAREA.RANTAREA,VDPERFILTAREA.RANAREAORI, "\
                    " VDPERFILTAREA.RANAREADEST,VDPERFILTAREA.CODCLASIFUBI,VDPERFILTAREA.RANCLASEUBIORI, "\
                    " VDPERFILTAREA.RANCLASEUBIDEST,VDPERFILTAREA.CODCLASIFART,VDPERFILTAREA.RANCLASEART, "\
                    " VDPERFILTAREA.RANCODZONORI,VDPERFILTAREA.RANCODZONDEST,VDPERFILTAREA.CONTENEDORES, "\
                    " VDPERFILTAREA.EMBALAJES,VDPERFILTAREA.UNIDADESSUELTAS,VDPERFILTAREA.PRIVILEGIOSTAREA, "\
                    " VDPERFILTAREA.MINALT,VDPERFILTAREA.MAXALT,VDPERFILTAREA.AGRUPAORIG, "\
                    " VDPERFILTAREA.AGRUPADEST,VDPERFILTAREA.AGRUPASERIE,VDPERFILTAREA.MAXAGRUPA, "\
                    " VDPERFILTAREA.FORMPLANIF,VDPERFILTAREA.VDEXTRA,VDPERFILTAREA.CODCOMEN, "\
                    " VDPERFILTAREA.CODOPEMODIF,VDPERFILTAREA.FECMODIF,VDPERFILTAREA.HORAMODIF, "\
                    " VDPERFILTAREA.MAXPRIOMOV,VDPERFILTAREA.MINPRIOMOV,VDPERFILTAREA.ASIGNAMOV, "\
                    " VDPERFILTAREA.FUNPLANIF "\
        " FROM VDPERFILTAREA"\
        " WHERE "\
               " VDPERFILTAREA.CODPERFIL=:CODPERFIL "
static v10cursors *vdselpervdperfiltarea;

static vdperfiltareas svdperfiltarea;

static diccols colvdperfiltarea[]={
	{"ROWID",V10CADENA,(size_t)&svdperfiltarea.rowid,sizeof(svdperfiltarea.rowid)},
	{"CODPERFIL",V10CADENA,(size_t)&svdperfiltarea.codperfil,sizeof(svdperfiltarea.codperfil)},
	{"DESPERFIL",V10CADENA,(size_t)&svdperfiltarea.desperfil,sizeof(svdperfiltarea.desperfil)},
	{"NPANTALLA",V10CADENA,(size_t)&svdperfiltarea.npantalla,sizeof(svdperfiltarea.npantalla)},
	{"RANTAREA",V10CADENA,(size_t)&svdperfiltarea.rantarea,sizeof(svdperfiltarea.rantarea)},
	{"RANAREAORI",V10CADENA,(size_t)&svdperfiltarea.ranareaori,sizeof(svdperfiltarea.ranareaori)},
	{"RANAREADEST",V10CADENA,(size_t)&svdperfiltarea.ranareadest,sizeof(svdperfiltarea.ranareadest)},
	{"CODCLASIFUBI",V10CADENA,(size_t)&svdperfiltarea.codclasifubi,sizeof(svdperfiltarea.codclasifubi)},
	{"RANCLASEUBIORI",V10CADENA,(size_t)&svdperfiltarea.ranclaseubiori,sizeof(svdperfiltarea.ranclaseubiori)},
	{"RANCLASEUBIDEST",V10CADENA,(size_t)&svdperfiltarea.ranclaseubidest,sizeof(svdperfiltarea.ranclaseubidest)},
	{"CODCLASIFART",V10CADENA,(size_t)&svdperfiltarea.codclasifart,sizeof(svdperfiltarea.codclasifart)},
	{"RANCLASEART",V10CADENA,(size_t)&svdperfiltarea.ranclaseart,sizeof(svdperfiltarea.ranclaseart)},
	{"RANCODZONORI",V10CADENA,(size_t)&svdperfiltarea.rancodzonori,sizeof(svdperfiltarea.rancodzonori)},
	{"RANCODZONDEST",V10CADENA,(size_t)&svdperfiltarea.rancodzondest,sizeof(svdperfiltarea.rancodzondest)},
	{"CONTENEDORES",V10CADENA,(size_t)&svdperfiltarea.contenedores,sizeof(svdperfiltarea.contenedores)},
	{"EMBALAJES",V10CADENA,(size_t)&svdperfiltarea.embalajes,sizeof(svdperfiltarea.embalajes)},
	{"UNIDADESSUELTAS",V10CADENA,(size_t)&svdperfiltarea.unidadessueltas,sizeof(svdperfiltarea.unidadessueltas)},
	{"PRIVILEGIOSTAREA",V10CADENA,(size_t)&svdperfiltarea.privilegiostarea,sizeof(svdperfiltarea.privilegiostarea)},
	{"MINALT",V10LONG,(size_t)&svdperfiltarea.minalt,sizeof(svdperfiltarea.minalt)},
	{"MAXALT",V10LONG,(size_t)&svdperfiltarea.maxalt,sizeof(svdperfiltarea.maxalt)},
	{"AGRUPAORIG",V10CADENA,(size_t)&svdperfiltarea.agrupaorig,sizeof(svdperfiltarea.agrupaorig)},
	{"AGRUPADEST",V10CADENA,(size_t)&svdperfiltarea.agrupadest,sizeof(svdperfiltarea.agrupadest)},
	{"AGRUPASERIE",V10CADENA,(size_t)&svdperfiltarea.agrupaserie,sizeof(svdperfiltarea.agrupaserie)},
	{"MAXAGRUPA",V10LONG,(size_t)&svdperfiltarea.maxagrupa,sizeof(svdperfiltarea.maxagrupa)},
	{"FORMPLANIF",V10CADENA,(size_t)&svdperfiltarea.formplanif,sizeof(svdperfiltarea.formplanif)},
	{"VDEXTRA",V10CADENA,(size_t)&svdperfiltarea.vdextra,sizeof(svdperfiltarea.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdperfiltarea.codcomen,sizeof(svdperfiltarea.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdperfiltarea.codopemodif,sizeof(svdperfiltarea.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdperfiltarea.fecmodif,sizeof(svdperfiltarea.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdperfiltarea.horamodif,sizeof(svdperfiltarea.horamodif)},
	{"MAXPRIOMOV",V10LONG,(size_t)&svdperfiltarea.maxpriomov,sizeof(svdperfiltarea.maxpriomov)},
	{"MINPRIOMOV",V10LONG,(size_t)&svdperfiltarea.minpriomov,sizeof(svdperfiltarea.minpriomov)},
	{"ASIGNAMOV",V10CADENA,(size_t)&svdperfiltarea.asignamov,sizeof(svdperfiltarea.asignamov)},
	{"FUNPLANIF",V10CADENA,(size_t)&svdperfiltarea.funplanif,sizeof(svdperfiltarea.funplanif)}
	};
static diccionarios dvdperfiltarea[]={
    {colvdperfiltarea,34}
};
diccionario dper={dvdperfiltarea,1};

static char msglogPER[LCADENA];
static char msgdebugPER[LCADENABIG];
static int init=0;


static void fin_vd_per(void)
{
if (vdselpercodperfil) {
    liberacursor(vdselpercodperfil);
    vdselpercodperfil = NULL;
}
if (vdselpervdperfiltarea) {
    liberacursor(vdselpervdperfiltarea);
    vdselpervdperfiltarea = NULL;
}
}
static void init_selpercodperfil(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdperfiltarea[0].numcol;nc++) dvdperfiltarea[0].c[nc].offset-=(size_t)&svdperfiltarea;
    vdselpercodperfil=abrecursordebug(SELPERCODPERFIL,1280);
    definetodo(vdselpercodperfil,svdperfiltarea.rowid,sizeof(svdperfiltarea.rowid),V10CADENA,
                          svdperfiltarea.codperfil,sizeof(svdperfiltarea.codperfil),V10CADENA,
                          svdperfiltarea.desperfil,sizeof(svdperfiltarea.desperfil),V10CADENA,
                          svdperfiltarea.npantalla,sizeof(svdperfiltarea.npantalla),V10CADENA,
                          svdperfiltarea.rantarea,sizeof(svdperfiltarea.rantarea),V10CADENA,
                          svdperfiltarea.ranareaori,sizeof(svdperfiltarea.ranareaori),V10CADENA,
                          svdperfiltarea.ranareadest,sizeof(svdperfiltarea.ranareadest),V10CADENA,
                          svdperfiltarea.codclasifubi,sizeof(svdperfiltarea.codclasifubi),V10CADENA,
                          svdperfiltarea.ranclaseubiori,sizeof(svdperfiltarea.ranclaseubiori),V10CADENA,
                          svdperfiltarea.ranclaseubidest,sizeof(svdperfiltarea.ranclaseubidest),V10CADENA,
                          svdperfiltarea.codclasifart,sizeof(svdperfiltarea.codclasifart),V10CADENA,
                          svdperfiltarea.ranclaseart,sizeof(svdperfiltarea.ranclaseart),V10CADENA,
                          svdperfiltarea.rancodzonori,sizeof(svdperfiltarea.rancodzonori),V10CADENA,
                          svdperfiltarea.rancodzondest,sizeof(svdperfiltarea.rancodzondest),V10CADENA,
                          svdperfiltarea.contenedores,sizeof(svdperfiltarea.contenedores),V10CADENA,
                          svdperfiltarea.embalajes,sizeof(svdperfiltarea.embalajes),V10CADENA,
                          svdperfiltarea.unidadessueltas,sizeof(svdperfiltarea.unidadessueltas),V10CADENA,
                          svdperfiltarea.privilegiostarea,sizeof(svdperfiltarea.privilegiostarea),V10CADENA,
                          &svdperfiltarea.minalt,sizeof(svdperfiltarea.minalt),V10LONG,
                          &svdperfiltarea.maxalt,sizeof(svdperfiltarea.maxalt),V10LONG,
                          svdperfiltarea.agrupaorig,sizeof(svdperfiltarea.agrupaorig),V10CADENA,
                          svdperfiltarea.agrupadest,sizeof(svdperfiltarea.agrupadest),V10CADENA,
                          svdperfiltarea.agrupaserie,sizeof(svdperfiltarea.agrupaserie),V10CADENA,
                          &svdperfiltarea.maxagrupa,sizeof(svdperfiltarea.maxagrupa),V10LONG,
                          svdperfiltarea.formplanif,sizeof(svdperfiltarea.formplanif),V10CADENA,
                          svdperfiltarea.vdextra,sizeof(svdperfiltarea.vdextra),V10CADENA,
                          &svdperfiltarea.codcomen,sizeof(svdperfiltarea.codcomen),V10LONG,
                          svdperfiltarea.codopemodif,sizeof(svdperfiltarea.codopemodif),V10CADENA,
                          &svdperfiltarea.fecmodif,sizeof(svdperfiltarea.fecmodif),V10LONG,
                          svdperfiltarea.horamodif,sizeof(svdperfiltarea.horamodif),V10CADENA,
                          &svdperfiltarea.maxpriomov,sizeof(svdperfiltarea.maxpriomov),V10LONG,
                          &svdperfiltarea.minpriomov,sizeof(svdperfiltarea.minpriomov),V10LONG,
                          svdperfiltarea.asignamov,sizeof(svdperfiltarea.asignamov),V10CADENA,
                          svdperfiltarea.funplanif,sizeof(svdperfiltarea.funplanif),V10CADENA,
                          NULL);
    bindtodo(vdselpercodperfil,"CODPERFIL",svdperfiltarea.codperfil,sizeof(svdperfiltarea.codperfil),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_per);
        init = 1;
    }
}

static void init_selpervdperfiltarea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdperfiltarea[0].numcol;nc++) dvdperfiltarea[0].c[nc].offset-=(size_t)&svdperfiltarea;
    vdselpervdperfiltarea=abrecursordebug(SELPERVDPERFILTAREA,1280);
    definetodo(vdselpervdperfiltarea,svdperfiltarea.rowid,sizeof(svdperfiltarea.rowid),V10CADENA,
                          svdperfiltarea.codperfil,sizeof(svdperfiltarea.codperfil),V10CADENA,
                          svdperfiltarea.desperfil,sizeof(svdperfiltarea.desperfil),V10CADENA,
                          svdperfiltarea.npantalla,sizeof(svdperfiltarea.npantalla),V10CADENA,
                          svdperfiltarea.rantarea,sizeof(svdperfiltarea.rantarea),V10CADENA,
                          svdperfiltarea.ranareaori,sizeof(svdperfiltarea.ranareaori),V10CADENA,
                          svdperfiltarea.ranareadest,sizeof(svdperfiltarea.ranareadest),V10CADENA,
                          svdperfiltarea.codclasifubi,sizeof(svdperfiltarea.codclasifubi),V10CADENA,
                          svdperfiltarea.ranclaseubiori,sizeof(svdperfiltarea.ranclaseubiori),V10CADENA,
                          svdperfiltarea.ranclaseubidest,sizeof(svdperfiltarea.ranclaseubidest),V10CADENA,
                          svdperfiltarea.codclasifart,sizeof(svdperfiltarea.codclasifart),V10CADENA,
                          svdperfiltarea.ranclaseart,sizeof(svdperfiltarea.ranclaseart),V10CADENA,
                          svdperfiltarea.rancodzonori,sizeof(svdperfiltarea.rancodzonori),V10CADENA,
                          svdperfiltarea.rancodzondest,sizeof(svdperfiltarea.rancodzondest),V10CADENA,
                          svdperfiltarea.contenedores,sizeof(svdperfiltarea.contenedores),V10CADENA,
                          svdperfiltarea.embalajes,sizeof(svdperfiltarea.embalajes),V10CADENA,
                          svdperfiltarea.unidadessueltas,sizeof(svdperfiltarea.unidadessueltas),V10CADENA,
                          svdperfiltarea.privilegiostarea,sizeof(svdperfiltarea.privilegiostarea),V10CADENA,
                          &svdperfiltarea.minalt,sizeof(svdperfiltarea.minalt),V10LONG,
                          &svdperfiltarea.maxalt,sizeof(svdperfiltarea.maxalt),V10LONG,
                          svdperfiltarea.agrupaorig,sizeof(svdperfiltarea.agrupaorig),V10CADENA,
                          svdperfiltarea.agrupadest,sizeof(svdperfiltarea.agrupadest),V10CADENA,
                          svdperfiltarea.agrupaserie,sizeof(svdperfiltarea.agrupaserie),V10CADENA,
                          &svdperfiltarea.maxagrupa,sizeof(svdperfiltarea.maxagrupa),V10LONG,
                          svdperfiltarea.formplanif,sizeof(svdperfiltarea.formplanif),V10CADENA,
                          svdperfiltarea.vdextra,sizeof(svdperfiltarea.vdextra),V10CADENA,
                          &svdperfiltarea.codcomen,sizeof(svdperfiltarea.codcomen),V10LONG,
                          svdperfiltarea.codopemodif,sizeof(svdperfiltarea.codopemodif),V10CADENA,
                          &svdperfiltarea.fecmodif,sizeof(svdperfiltarea.fecmodif),V10LONG,
                          svdperfiltarea.horamodif,sizeof(svdperfiltarea.horamodif),V10CADENA,
                          &svdperfiltarea.maxpriomov,sizeof(svdperfiltarea.maxpriomov),V10LONG,
                          &svdperfiltarea.minpriomov,sizeof(svdperfiltarea.minpriomov),V10LONG,
                          svdperfiltarea.asignamov,sizeof(svdperfiltarea.asignamov),V10CADENA,
                          svdperfiltarea.funplanif,sizeof(svdperfiltarea.funplanif),V10CADENA,
                          NULL);
    bindtodo(vdselpervdperfiltarea,"CODPERFIL",svdperfiltarea.codperfil,sizeof(svdperfiltarea.codperfil),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_per);
        init = 1;
    }
}

diccionario *PERdamediccionario(void)
{
     return(&dper);
}

int PERselcodperfil(char *codperfil,vdperfiltareas *per)
{
  int vdret;
  if (vdselpercodperfil==NULL) init_selpercodperfil();
  memset(&svdperfiltarea,0,sizeof(svdperfiltarea));
  strcpy(svdperfiltarea.codperfil,codperfil);
  vdret=ejefetchcursor(vdselpercodperfil);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpercodperfil. vdret %d. \n",PERlog(&svdperfiltarea),vdret);
    return(VD_EERRORACLE);
   }
  *per=svdperfiltarea;
  return(vdret);
}

int PERselvdperfiltarea(char *codperfil,vdperfiltareas *per)
{
  int vdret;
  if (vdselpervdperfiltarea==NULL) init_selpervdperfiltarea();
  memset(&svdperfiltarea,0,sizeof(svdperfiltarea));
  strcpy(svdperfiltarea.codperfil,codperfil);
  vdret=ejefetchcursor(vdselpervdperfiltarea);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpervdperfiltarea. vdret %d. \n",PERlog(&svdperfiltarea),vdret);
    return(VD_EERRORACLE);
   }
  *per=svdperfiltarea;
  return(vdret);
}

char * PERlog(vdperfiltareas *per)
{
    sprintf(msglogPER, "VDPERFILTAREA: codperfil %s ",per->codperfil);
    return(msglogPER);
}

char * PERdebug(vdperfiltareas *per)
{
    debugestruct(&dper,per,msgdebugPER);
    return(msgdebugPER);
}

