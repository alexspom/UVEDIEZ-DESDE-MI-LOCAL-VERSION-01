// Modulo generado automaticamente a partir de VDUSUARIO.DEF
//# M¢dulo : VDUSUARIO.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDUSUARIO
//#                        
//# Autor	 : EAA
//# Revisado por: 
//# Fecha  : 10-10-2007                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=USU
//
//PRIMARIA=CODOPE
//
//CLAVE=CODOPE,CODOPE
//

#include "vd.h"
#define SELUSUCODOPE "SELECT VDUSUARIO.ROWID,VDUSUARIO.CODOPE,VDUSUARIO.NOMBRE, "\
                    " VDUSUARIO.APELLIDO1,VDUSUARIO.APELLIDO2,VDUSUARIO.INICIALES, "\
                    " RAWTOHEX(VDUSUARIO.HPASSWORD) HPASSWORD,VDUSUARIO.FECPASSWORD,VDUSUARIO.HORAPASSWORD, "\
                    " VDUSUARIO.FECCADUC,RAWTOHEX(VDUSUARIO.CPUB) CPUB,RAWTOHEX(VDUSUARIO.CPRIV) CPRIV, "\
                    " VDUSUARIO.TEMA,VDUSUARIO.NIVEL,VDUSUARIO.BLOQUEOPE, "\
                    " VDUSUARIO.CONTERRSUC,VDUSUARIO.CONTERRTOT,VDUSUARIO.CONTLOG, "\
                    " VDUSUARIO.MENUASOCIADO,VDUSUARIO.IDIOMA,VDUSUARIO.TPCVERIF, "\
                    " VDUSUARIO.VDEXTRA,VDUSUARIO.CODCOMEN,VDUSUARIO.CODOPEMODIF, "\
                    " VDUSUARIO.FECMODIF,VDUSUARIO.HORAMODIF "\
        " FROM VDUSUARIO"\
        " WHERE "\
               " VDUSUARIO.CODOPE=:CODOPE "
static v10cursors *vdselusucodope;

#define SELUSUVDUSUARIO "SELECT VDUSUARIO.ROWID,VDUSUARIO.CODOPE,VDUSUARIO.NOMBRE, "\
                    " VDUSUARIO.APELLIDO1,VDUSUARIO.APELLIDO2,VDUSUARIO.INICIALES, "\
                    " RAWTOHEX(VDUSUARIO.HPASSWORD) HPASSWORD,VDUSUARIO.FECPASSWORD,VDUSUARIO.HORAPASSWORD, "\
                    " VDUSUARIO.FECCADUC,RAWTOHEX(VDUSUARIO.CPUB) CPUB,RAWTOHEX(VDUSUARIO.CPRIV) CPRIV, "\
                    " VDUSUARIO.TEMA,VDUSUARIO.NIVEL,VDUSUARIO.BLOQUEOPE, "\
                    " VDUSUARIO.CONTERRSUC,VDUSUARIO.CONTERRTOT,VDUSUARIO.CONTLOG, "\
                    " VDUSUARIO.MENUASOCIADO,VDUSUARIO.IDIOMA,VDUSUARIO.TPCVERIF, "\
                    " VDUSUARIO.VDEXTRA,VDUSUARIO.CODCOMEN,VDUSUARIO.CODOPEMODIF, "\
                    " VDUSUARIO.FECMODIF,VDUSUARIO.HORAMODIF "\
        " FROM VDUSUARIO"\
        " WHERE "\
               " VDUSUARIO.CODOPE=:CODOPE "
static v10cursors *vdselusuvdusuario;

static vdusuarios svdusuario;

static diccols colvdusuario[]={
	{"ROWID",V10CADENA,(size_t)&svdusuario.rowid,sizeof(svdusuario.rowid)},
	{"CODOPE",V10CADENA,(size_t)&svdusuario.codope,sizeof(svdusuario.codope)},
	{"NOMBRE",V10CADENA,(size_t)&svdusuario.nombre,sizeof(svdusuario.nombre)},
	{"APELLIDO1",V10CADENA,(size_t)&svdusuario.apellido1,sizeof(svdusuario.apellido1)},
	{"APELLIDO2",V10CADENA,(size_t)&svdusuario.apellido2,sizeof(svdusuario.apellido2)},
	{"INICIALES",V10CADENA,(size_t)&svdusuario.iniciales,sizeof(svdusuario.iniciales)},
	{"HPASSWORD",V10CADENA,(size_t)&svdusuario.hpassword,sizeof(svdusuario.hpassword)},
	{"FECPASSWORD",V10LONG,(size_t)&svdusuario.fecpassword,sizeof(svdusuario.fecpassword)},
	{"HORAPASSWORD",V10CADENA,(size_t)&svdusuario.horapassword,sizeof(svdusuario.horapassword)},
	{"FECCADUC",V10LONG,(size_t)&svdusuario.feccaduc,sizeof(svdusuario.feccaduc)},
	{"CPUB",V10CADENA,(size_t)&svdusuario.cpub,sizeof(svdusuario.cpub)},
	{"CPRIV",V10CADENA,(size_t)&svdusuario.cpriv,sizeof(svdusuario.cpriv)},
	{"TEMA",V10CADENA,(size_t)&svdusuario.tema,sizeof(svdusuario.tema)},
	{"NIVEL",V10LONG,(size_t)&svdusuario.nivel,sizeof(svdusuario.nivel)},
	{"BLOQUEOPE",V10CADENA,(size_t)&svdusuario.bloqueope,sizeof(svdusuario.bloqueope)},
	{"CONTERRSUC",V10LONG,(size_t)&svdusuario.conterrsuc,sizeof(svdusuario.conterrsuc)},
	{"CONTERRTOT",V10LONG,(size_t)&svdusuario.conterrtot,sizeof(svdusuario.conterrtot)},
	{"CONTLOG",V10LONG,(size_t)&svdusuario.contlog,sizeof(svdusuario.contlog)},
	{"MENUASOCIADO",V10CADENA,(size_t)&svdusuario.menuasociado,sizeof(svdusuario.menuasociado)},
	{"IDIOMA",V10CADENA,(size_t)&svdusuario.idioma,sizeof(svdusuario.idioma)},
	{"TPCVERIF",V10LONG,(size_t)&svdusuario.tpcverif,sizeof(svdusuario.tpcverif)},
	{"VDEXTRA",V10CADENA,(size_t)&svdusuario.vdextra,sizeof(svdusuario.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdusuario.codcomen,sizeof(svdusuario.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdusuario.codopemodif,sizeof(svdusuario.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdusuario.fecmodif,sizeof(svdusuario.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdusuario.horamodif,sizeof(svdusuario.horamodif)}
	};
static diccionarios dvdusuario[]={
    {colvdusuario,26}
};
diccionario dusu={dvdusuario,1};

static char msglogUSU[LCADENA];
static char msgdebugUSU[LCADENABIG];
static int init=0;


static void fin_vd_usu(void)
{
if (vdselusucodope) {
    liberacursor(vdselusucodope);
    vdselusucodope = NULL;
}
if (vdselusuvdusuario) {
    liberacursor(vdselusuvdusuario);
    vdselusuvdusuario = NULL;
}
}
static void init_selusucodope(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdusuario[0].numcol;nc++) dvdusuario[0].c[nc].offset-=(size_t)&svdusuario;
    vdselusucodope=abrecursordebug(SELUSUCODOPE,1280);
    definetodo(vdselusucodope,svdusuario.rowid,sizeof(svdusuario.rowid),V10CADENA,
                          svdusuario.codope,sizeof(svdusuario.codope),V10CADENA,
                          svdusuario.nombre,sizeof(svdusuario.nombre),V10CADENA,
                          svdusuario.apellido1,sizeof(svdusuario.apellido1),V10CADENA,
                          svdusuario.apellido2,sizeof(svdusuario.apellido2),V10CADENA,
                          svdusuario.iniciales,sizeof(svdusuario.iniciales),V10CADENA,
                          svdusuario.hpassword,sizeof(svdusuario.hpassword),V10CADENA,
                          &svdusuario.fecpassword,sizeof(svdusuario.fecpassword),V10LONG,
                          svdusuario.horapassword,sizeof(svdusuario.horapassword),V10CADENA,
                          &svdusuario.feccaduc,sizeof(svdusuario.feccaduc),V10LONG,
                          svdusuario.cpub,sizeof(svdusuario.cpub),V10CADENA,
                          svdusuario.cpriv,sizeof(svdusuario.cpriv),V10CADENA,
                          svdusuario.tema,sizeof(svdusuario.tema),V10CADENA,
                          &svdusuario.nivel,sizeof(svdusuario.nivel),V10LONG,
                          svdusuario.bloqueope,sizeof(svdusuario.bloqueope),V10CADENA,
                          &svdusuario.conterrsuc,sizeof(svdusuario.conterrsuc),V10LONG,
                          &svdusuario.conterrtot,sizeof(svdusuario.conterrtot),V10LONG,
                          &svdusuario.contlog,sizeof(svdusuario.contlog),V10LONG,
                          svdusuario.menuasociado,sizeof(svdusuario.menuasociado),V10CADENA,
                          svdusuario.idioma,sizeof(svdusuario.idioma),V10CADENA,
                          &svdusuario.tpcverif,sizeof(svdusuario.tpcverif),V10LONG,
                          svdusuario.vdextra,sizeof(svdusuario.vdextra),V10CADENA,
                          &svdusuario.codcomen,sizeof(svdusuario.codcomen),V10LONG,
                          svdusuario.codopemodif,sizeof(svdusuario.codopemodif),V10CADENA,
                          &svdusuario.fecmodif,sizeof(svdusuario.fecmodif),V10LONG,
                          svdusuario.horamodif,sizeof(svdusuario.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselusucodope,"CODOPE",svdusuario.codope,sizeof(svdusuario.codope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_usu);
        init = 1;
    }
}

static void init_selusuvdusuario(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdusuario[0].numcol;nc++) dvdusuario[0].c[nc].offset-=(size_t)&svdusuario;
    vdselusuvdusuario=abrecursordebug(SELUSUVDUSUARIO,1280);
    definetodo(vdselusuvdusuario,svdusuario.rowid,sizeof(svdusuario.rowid),V10CADENA,
                          svdusuario.codope,sizeof(svdusuario.codope),V10CADENA,
                          svdusuario.nombre,sizeof(svdusuario.nombre),V10CADENA,
                          svdusuario.apellido1,sizeof(svdusuario.apellido1),V10CADENA,
                          svdusuario.apellido2,sizeof(svdusuario.apellido2),V10CADENA,
                          svdusuario.iniciales,sizeof(svdusuario.iniciales),V10CADENA,
                          svdusuario.hpassword,sizeof(svdusuario.hpassword),V10CADENA,
                          &svdusuario.fecpassword,sizeof(svdusuario.fecpassword),V10LONG,
                          svdusuario.horapassword,sizeof(svdusuario.horapassword),V10CADENA,
                          &svdusuario.feccaduc,sizeof(svdusuario.feccaduc),V10LONG,
                          svdusuario.cpub,sizeof(svdusuario.cpub),V10CADENA,
                          svdusuario.cpriv,sizeof(svdusuario.cpriv),V10CADENA,
                          svdusuario.tema,sizeof(svdusuario.tema),V10CADENA,
                          &svdusuario.nivel,sizeof(svdusuario.nivel),V10LONG,
                          svdusuario.bloqueope,sizeof(svdusuario.bloqueope),V10CADENA,
                          &svdusuario.conterrsuc,sizeof(svdusuario.conterrsuc),V10LONG,
                          &svdusuario.conterrtot,sizeof(svdusuario.conterrtot),V10LONG,
                          &svdusuario.contlog,sizeof(svdusuario.contlog),V10LONG,
                          svdusuario.menuasociado,sizeof(svdusuario.menuasociado),V10CADENA,
                          svdusuario.idioma,sizeof(svdusuario.idioma),V10CADENA,
                          &svdusuario.tpcverif,sizeof(svdusuario.tpcverif),V10LONG,
                          svdusuario.vdextra,sizeof(svdusuario.vdextra),V10CADENA,
                          &svdusuario.codcomen,sizeof(svdusuario.codcomen),V10LONG,
                          svdusuario.codopemodif,sizeof(svdusuario.codopemodif),V10CADENA,
                          &svdusuario.fecmodif,sizeof(svdusuario.fecmodif),V10LONG,
                          svdusuario.horamodif,sizeof(svdusuario.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdselusuvdusuario,"CODOPE",svdusuario.codope,sizeof(svdusuario.codope),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_usu);
        init = 1;
    }
}

diccionario *USUdamediccionario(void)
{
     return(&dusu);
}

int USUselcodope(char *codope,vdusuarios *usu)
{
  int vdret;
  if (vdselusucodope==NULL) init_selusucodope();
  memset(&svdusuario,0,sizeof(svdusuario));
  strcpy(svdusuario.codope,codope);
  vdret=ejefetchcursor(vdselusucodope);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselusucodope. vdret %d. \n",USUlog(&svdusuario),vdret);
    return(VD_EERRORACLE);
   }
  *usu=svdusuario;
  return(vdret);
}

int USUselvdusuario(char *codope,vdusuarios *usu)
{
  int vdret;
  if (vdselusuvdusuario==NULL) init_selusuvdusuario();
  memset(&svdusuario,0,sizeof(svdusuario));
  strcpy(svdusuario.codope,codope);
  vdret=ejefetchcursor(vdselusuvdusuario);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselusuvdusuario. vdret %d. \n",USUlog(&svdusuario),vdret);
    return(VD_EERRORACLE);
   }
  *usu=svdusuario;
  return(vdret);
}

char * USUlog(vdusuarios *usu)
{
    sprintf(msglogUSU, "VDUSUARIO: codope %s ",usu->codope);
    return(msglogUSU);
}

char * USUdebug(vdusuarios *usu)
{
    debugestruct(&dusu,usu,msgdebugUSU);
    return(msgdebugUSU);
}

