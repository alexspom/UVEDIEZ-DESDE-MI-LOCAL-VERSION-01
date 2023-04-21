// Modulo generado automaticamente a partir de VDDEFBLOQUE.DEF
//# M¢dulo : VDDEFBLOQUE.DEF
//# Función: Generación automatica de rutinas C tabla VDDEFBLOQUE
//#
//# Autor	 : FGS
//# Revisado por:
//# Fecha  : 19-12-2008
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=DEB
//
//ORADEBUG=0
//INSERT
//UPDATE
//

#include "vd.h"
#define SELDEBVDDEFBLOQUE "SELECT VDDEFBLOQUE.ROWID,VDDEFBLOQUE.NBLOQUE,VDDEFBLOQUE.GRUPOBLOQUE, "\
                    " VDDEFBLOQUE.TIPOPANTALLA,VDDEFBLOQUE.NUMPOSX,VDDEFBLOQUE.NUMPOSY, "\
                    " VDDEFBLOQUE.NUMREGPAG,VDDEFBLOQUE.AYUDAONLINE,VDDEFBLOQUE.TITULOBLOQUE, "\
                    " VDDEFBLOQUE.MODOQUERY,VDDEFBLOQUE.FCONTEXTUAL,VDDEFBLOQUE.FTECLA, "\
                    " VDDEFBLOQUE.CAPITALIZA,VDDEFBLOQUE.TWHERE,VDDEFBLOQUE.TORDERBY, "\
                    " VDDEFBLOQUE.CNOINSERT,VDDEFBLOQUE.PRIVINSERT,VDDEFBLOQUE.CNODELETE, "\
                    " VDDEFBLOQUE.PRIVDELETE,VDDEFBLOQUE.CNOENTER,VDDEFBLOQUE.PRIVNOENTER, "\
                    " VDDEFBLOQUE.CNOUPDATE,VDDEFBLOQUE.PRIVUPDATE,VDDEFBLOQUE.CNOORAINS, "\
                    " VDDEFBLOQUE.PRIVORAINS,VDDEFBLOQUE.FAYUDA,VDDEFBLOQUE.FAUXILIAR, "\
                    " VDDEFBLOQUE.CODOPEMODIF,VDDEFBLOQUE.FECMODIF,VDDEFBLOQUE.HORAMODIF, "\
                    " VDDEFBLOQUE.CODCOMEN "\
        " FROM VDDEFBLOQUE"\
        " WHERE "\
               " VDDEFBLOQUE.NBLOQUE=UPPER(:NBLOQUE) "\
               " AND VDDEFBLOQUE.TIPOPANTALLA=UPPER(:TIPOPANTALLA) "
static v10cursors *vdseldebvddefbloque;

#define UPDADEB "UPDATE VDDEFBLOQUE SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " NBLOQUE=:NBLOQUE , "\
               " GRUPOBLOQUE=:GRUPOBLOQUE , "\
               " TIPOPANTALLA=:TIPOPANTALLA , "\
               " NUMPOSX=:NUMPOSX , "\
               " NUMPOSY=:NUMPOSY , "\
               " NUMREGPAG=:NUMREGPAG , "\
               " AYUDAONLINE=:AYUDAONLINE , "\
               " TITULOBLOQUE=:TITULOBLOQUE , "\
               " MODOQUERY=:MODOQUERY , "\
               " FCONTEXTUAL=:FCONTEXTUAL , "\
               " FTECLA=:FTECLA , "\
               " CAPITALIZA=:CAPITALIZA , "\
               " TWHERE=:TWHERE , "\
               " TORDERBY=:TORDERBY , "\
               " CNOINSERT=:CNOINSERT , "\
               " PRIVINSERT=:PRIVINSERT , "\
               " CNODELETE=:CNODELETE , "\
               " PRIVDELETE=:PRIVDELETE , "\
               " CNOENTER=:CNOENTER , "\
               " PRIVNOENTER=:PRIVNOENTER , "\
               " CNOUPDATE=:CNOUPDATE , "\
               " PRIVUPDATE=:PRIVUPDATE , "\
               " CNOORAINS=:CNOORAINS , "\
               " PRIVORAINS=:PRIVORAINS , "\
               " FAYUDA=:FAYUDA , "\
               " FAUXILIAR=:FAUXILIAR , "\
               " CODCOMEN=:CODCOMEN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdadebvddefbloque;

#define INSDEB "INSERT INTO VDDEFBLOQUE (NBLOQUE,GRUPOBLOQUE,TIPOPANTALLA,NUMPOSX,NUMPOSY,NUMREGPAG, "\
                    " AYUDAONLINE,TITULOBLOQUE,MODOQUERY,FCONTEXTUAL,FTECLA,CAPITALIZA,TWHERE, "\
                    " TORDERBY,CNOINSERT,PRIVINSERT,CNODELETE,PRIVDELETE,CNOENTER,PRIVNOENTER, "\
                    " CNOUPDATE,PRIVUPDATE,CNOORAINS,PRIVORAINS,FAYUDA,FAUXILIAR,CODOPEMODIF, "\
                    " FECMODIF,HORAMODIF,CODCOMEN "\
       " ) VALUES ( "\
                    " :NBLOQUE,:GRUPOBLOQUE,UPPER(:TIPOPANTALLA),:NUMPOSX,:NUMPOSY,:NUMREGPAG, "\
                    " :AYUDAONLINE,:TITULOBLOQUE,:MODOQUERY,:FCONTEXTUAL,:FTECLA,:CAPITALIZA,:TWHERE, "\
                    " :TORDERBY,:CNOINSERT,:PRIVINSERT,:CNODELETE,:PRIVDELETE,:CNOENTER,:PRIVNOENTER, "\
                    " :CNOUPDATE,:PRIVUPDATE,:CNOORAINS,:PRIVORAINS,:FAYUDA,:FAUXILIAR,VDUSER.GETUSER, "\
                    " VD.FECHASYS,VD.HORASYS,:CODCOMEN) "
static v10cursors *vdinsdeb;

static vddefbloques svddefbloque;

static diccols colvddefbloque[]={
	{"ROWID",V10CADENA,(size_t)&svddefbloque.rowid,sizeof(svddefbloque.rowid)},
	{"NBLOQUE",V10CADENA,(size_t)&svddefbloque.nbloque,sizeof(svddefbloque.nbloque)},
	{"GRUPOBLOQUE",V10CADENA,(size_t)&svddefbloque.grupobloque,sizeof(svddefbloque.grupobloque)},
	{"TIPOPANTALLA",V10CADENA,(size_t)&svddefbloque.tipopantalla,sizeof(svddefbloque.tipopantalla)},
	{"NUMPOSX",V10LONG,(size_t)&svddefbloque.numposx,sizeof(svddefbloque.numposx)},
	{"NUMPOSY",V10LONG,(size_t)&svddefbloque.numposy,sizeof(svddefbloque.numposy)},
	{"NUMREGPAG",V10LONG,(size_t)&svddefbloque.numregpag,sizeof(svddefbloque.numregpag)},
	{"AYUDAONLINE",V10CADENA,(size_t)&svddefbloque.ayudaonline,sizeof(svddefbloque.ayudaonline)},
	{"TITULOBLOQUE",V10CADENA,(size_t)&svddefbloque.titulobloque,sizeof(svddefbloque.titulobloque)},
	{"MODOQUERY",V10CADENA,(size_t)&svddefbloque.modoquery,sizeof(svddefbloque.modoquery)},
	{"FCONTEXTUAL",V10CADENA,(size_t)&svddefbloque.fcontextual,sizeof(svddefbloque.fcontextual)},
	{"FTECLA",V10CADENA,(size_t)&svddefbloque.ftecla,sizeof(svddefbloque.ftecla)},
	{"CAPITALIZA",V10CADENA,(size_t)&svddefbloque.capitaliza,sizeof(svddefbloque.capitaliza)},
	{"TWHERE",V10CADENA,(size_t)&svddefbloque.twhere,sizeof(svddefbloque.twhere)},
	{"TORDERBY",V10CADENA,(size_t)&svddefbloque.torderby,sizeof(svddefbloque.torderby)},
	{"CNOINSERT",V10CADENA,(size_t)&svddefbloque.cnoinsert,sizeof(svddefbloque.cnoinsert)},
	{"PRIVINSERT",V10CADENA,(size_t)&svddefbloque.privinsert,sizeof(svddefbloque.privinsert)},
	{"CNODELETE",V10CADENA,(size_t)&svddefbloque.cnodelete,sizeof(svddefbloque.cnodelete)},
	{"PRIVDELETE",V10CADENA,(size_t)&svddefbloque.privdelete,sizeof(svddefbloque.privdelete)},
	{"CNOENTER",V10CADENA,(size_t)&svddefbloque.cnoenter,sizeof(svddefbloque.cnoenter)},
	{"PRIVNOENTER",V10CADENA,(size_t)&svddefbloque.privnoenter,sizeof(svddefbloque.privnoenter)},
	{"CNOUPDATE",V10CADENA,(size_t)&svddefbloque.cnoupdate,sizeof(svddefbloque.cnoupdate)},
	{"PRIVUPDATE",V10CADENA,(size_t)&svddefbloque.privupdate,sizeof(svddefbloque.privupdate)},
	{"CNOORAINS",V10CADENA,(size_t)&svddefbloque.cnoorains,sizeof(svddefbloque.cnoorains)},
	{"PRIVORAINS",V10CADENA,(size_t)&svddefbloque.privorains,sizeof(svddefbloque.privorains)},
	{"FAYUDA",V10CADENA,(size_t)&svddefbloque.fayuda,sizeof(svddefbloque.fayuda)},
	{"FAUXILIAR",V10CADENA,(size_t)&svddefbloque.fauxiliar,sizeof(svddefbloque.fauxiliar)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svddefbloque.codopemodif,sizeof(svddefbloque.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svddefbloque.fecmodif,sizeof(svddefbloque.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svddefbloque.horamodif,sizeof(svddefbloque.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svddefbloque.codcomen,sizeof(svddefbloque.codcomen)}
	};
static diccionarios dvddefbloque[]={
    {colvddefbloque,31}
};
diccionario ddeb={dvddefbloque,1};

static char msglogDEB[LCADENA];
static char msgdebugDEB[LCADENABIG];
static int init=0;


static void fin_vd_deb(void)
{
if (vdseldebvddefbloque) {
    liberacursor(vdseldebvddefbloque);
    vdseldebvddefbloque = NULL;
}
if (vdupdadebvddefbloque) {
    liberacursor(vdupdadebvddefbloque);
    vdupdadebvddefbloque = NULL;
}
if (vdinsdeb != NULL) {
    liberacursor(vdinsdeb);
    vdinsdeb = NULL;
}
}
static void init_seldebvddefbloque(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddefbloque[0].numcol;nc++) dvddefbloque[0].c[nc].offset-=(size_t)&svddefbloque;
    vdseldebvddefbloque=abrecursordebug(SELDEBVDDEFBLOQUE,0);
    definetodo(vdseldebvddefbloque,svddefbloque.rowid,sizeof(svddefbloque.rowid),V10CADENA,
                          svddefbloque.nbloque,sizeof(svddefbloque.nbloque),V10CADENA,
                          svddefbloque.grupobloque,sizeof(svddefbloque.grupobloque),V10CADENA,
                          svddefbloque.tipopantalla,sizeof(svddefbloque.tipopantalla),V10CADENA,
                          &svddefbloque.numposx,sizeof(svddefbloque.numposx),V10LONG,
                          &svddefbloque.numposy,sizeof(svddefbloque.numposy),V10LONG,
                          &svddefbloque.numregpag,sizeof(svddefbloque.numregpag),V10LONG,
                          svddefbloque.ayudaonline,sizeof(svddefbloque.ayudaonline),V10CADENA,
                          svddefbloque.titulobloque,sizeof(svddefbloque.titulobloque),V10CADENA,
                          svddefbloque.modoquery,sizeof(svddefbloque.modoquery),V10CADENA,
                          svddefbloque.fcontextual,sizeof(svddefbloque.fcontextual),V10CADENA,
                          svddefbloque.ftecla,sizeof(svddefbloque.ftecla),V10CADENA,
                          svddefbloque.capitaliza,sizeof(svddefbloque.capitaliza),V10CADENA,
                          svddefbloque.twhere,sizeof(svddefbloque.twhere),V10CADENA,
                          svddefbloque.torderby,sizeof(svddefbloque.torderby),V10CADENA,
                          svddefbloque.cnoinsert,sizeof(svddefbloque.cnoinsert),V10CADENA,
                          svddefbloque.privinsert,sizeof(svddefbloque.privinsert),V10CADENA,
                          svddefbloque.cnodelete,sizeof(svddefbloque.cnodelete),V10CADENA,
                          svddefbloque.privdelete,sizeof(svddefbloque.privdelete),V10CADENA,
                          svddefbloque.cnoenter,sizeof(svddefbloque.cnoenter),V10CADENA,
                          svddefbloque.privnoenter,sizeof(svddefbloque.privnoenter),V10CADENA,
                          svddefbloque.cnoupdate,sizeof(svddefbloque.cnoupdate),V10CADENA,
                          svddefbloque.privupdate,sizeof(svddefbloque.privupdate),V10CADENA,
                          svddefbloque.cnoorains,sizeof(svddefbloque.cnoorains),V10CADENA,
                          svddefbloque.privorains,sizeof(svddefbloque.privorains),V10CADENA,
                          svddefbloque.fayuda,sizeof(svddefbloque.fayuda),V10CADENA,
                          svddefbloque.fauxiliar,sizeof(svddefbloque.fauxiliar),V10CADENA,
                          svddefbloque.codopemodif,sizeof(svddefbloque.codopemodif),V10CADENA,
                          &svddefbloque.fecmodif,sizeof(svddefbloque.fecmodif),V10LONG,
                          svddefbloque.horamodif,sizeof(svddefbloque.horamodif),V10CADENA,
                          &svddefbloque.codcomen,sizeof(svddefbloque.codcomen),V10LONG,
                          NULL);
    bindtodo(vdseldebvddefbloque,"NBLOQUE",svddefbloque.nbloque,sizeof(svddefbloque.nbloque),V10CADENA,
                          "TIPOPANTALLA",svddefbloque.tipopantalla,sizeof(svddefbloque.tipopantalla),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deb);
        init = 1;
    }
}

static void init_updadebvddefbloque(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddefbloque[0].numcol;nc++) dvddefbloque[0].c[nc].offset-=(size_t)&svddefbloque;
    vdupdadebvddefbloque=abrecursordebug(UPDADEB,0);
    bindtodo(vdupdadebvddefbloque,"NBLOQUE",svddefbloque.nbloque,sizeof(svddefbloque.nbloque),V10CADENA,
                          "GRUPOBLOQUE",svddefbloque.grupobloque,sizeof(svddefbloque.grupobloque),V10CADENA,
                          "TIPOPANTALLA",svddefbloque.tipopantalla,sizeof(svddefbloque.tipopantalla),V10CADENA,
                          "NUMPOSX",&svddefbloque.numposx,sizeof(svddefbloque.numposx),V10LONG,
                          "NUMPOSY",&svddefbloque.numposy,sizeof(svddefbloque.numposy),V10LONG,
                          "NUMREGPAG",&svddefbloque.numregpag,sizeof(svddefbloque.numregpag),V10LONG,
                          "AYUDAONLINE",svddefbloque.ayudaonline,sizeof(svddefbloque.ayudaonline),V10CADENA,
                          "TITULOBLOQUE",svddefbloque.titulobloque,sizeof(svddefbloque.titulobloque),V10CADENA,
                          "MODOQUERY",svddefbloque.modoquery,sizeof(svddefbloque.modoquery),V10CADENA,
                          "FCONTEXTUAL",svddefbloque.fcontextual,sizeof(svddefbloque.fcontextual),V10CADENA,
                          "FTECLA",svddefbloque.ftecla,sizeof(svddefbloque.ftecla),V10CADENA,
                          "CAPITALIZA",svddefbloque.capitaliza,sizeof(svddefbloque.capitaliza),V10CADENA,
                          "TWHERE",svddefbloque.twhere,sizeof(svddefbloque.twhere),V10CADENA,
                          "TORDERBY",svddefbloque.torderby,sizeof(svddefbloque.torderby),V10CADENA,
                          "CNOINSERT",svddefbloque.cnoinsert,sizeof(svddefbloque.cnoinsert),V10CADENA,
                          "PRIVINSERT",svddefbloque.privinsert,sizeof(svddefbloque.privinsert),V10CADENA,
                          "CNODELETE",svddefbloque.cnodelete,sizeof(svddefbloque.cnodelete),V10CADENA,
                          "PRIVDELETE",svddefbloque.privdelete,sizeof(svddefbloque.privdelete),V10CADENA,
                          "CNOENTER",svddefbloque.cnoenter,sizeof(svddefbloque.cnoenter),V10CADENA,
                          "PRIVNOENTER",svddefbloque.privnoenter,sizeof(svddefbloque.privnoenter),V10CADENA,
                          "CNOUPDATE",svddefbloque.cnoupdate,sizeof(svddefbloque.cnoupdate),V10CADENA,
                          "PRIVUPDATE",svddefbloque.privupdate,sizeof(svddefbloque.privupdate),V10CADENA,
                          "CNOORAINS",svddefbloque.cnoorains,sizeof(svddefbloque.cnoorains),V10CADENA,
                          "PRIVORAINS",svddefbloque.privorains,sizeof(svddefbloque.privorains),V10CADENA,
                          "FAYUDA",svddefbloque.fayuda,sizeof(svddefbloque.fayuda),V10CADENA,
                          "FAUXILIAR",svddefbloque.fauxiliar,sizeof(svddefbloque.fauxiliar),V10CADENA,
                          "CODCOMEN",&svddefbloque.codcomen,sizeof(svddefbloque.codcomen),V10LONG,
                          "MIROWID",svddefbloque.rowid,sizeof(svddefbloque.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deb);
        init = 1;
    }
}

static void init_insdeb(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddefbloque[0].numcol;nc++) dvddefbloque[0].c[nc].offset-=(size_t)&svddefbloque;
    vdinsdeb=abrecursordebug(INSDEB,0);
    bindtodo(vdinsdeb,"NBLOQUE",svddefbloque.nbloque,sizeof(svddefbloque.nbloque),V10CADENA,
                          "GRUPOBLOQUE",svddefbloque.grupobloque,sizeof(svddefbloque.grupobloque),V10CADENA,
                          "TIPOPANTALLA",svddefbloque.tipopantalla,sizeof(svddefbloque.tipopantalla),V10CADENA,
                          "NUMPOSX",&svddefbloque.numposx,sizeof(svddefbloque.numposx),V10LONG,
                          "NUMPOSY",&svddefbloque.numposy,sizeof(svddefbloque.numposy),V10LONG,
                          "NUMREGPAG",&svddefbloque.numregpag,sizeof(svddefbloque.numregpag),V10LONG,
                          "AYUDAONLINE",svddefbloque.ayudaonline,sizeof(svddefbloque.ayudaonline),V10CADENA,
                          "TITULOBLOQUE",svddefbloque.titulobloque,sizeof(svddefbloque.titulobloque),V10CADENA,
                          "MODOQUERY",svddefbloque.modoquery,sizeof(svddefbloque.modoquery),V10CADENA,
                          "FCONTEXTUAL",svddefbloque.fcontextual,sizeof(svddefbloque.fcontextual),V10CADENA,
                          "FTECLA",svddefbloque.ftecla,sizeof(svddefbloque.ftecla),V10CADENA,
                          "CAPITALIZA",svddefbloque.capitaliza,sizeof(svddefbloque.capitaliza),V10CADENA,
                          "TWHERE",svddefbloque.twhere,sizeof(svddefbloque.twhere),V10CADENA,
                          "TORDERBY",svddefbloque.torderby,sizeof(svddefbloque.torderby),V10CADENA,
                          "CNOINSERT",svddefbloque.cnoinsert,sizeof(svddefbloque.cnoinsert),V10CADENA,
                          "PRIVINSERT",svddefbloque.privinsert,sizeof(svddefbloque.privinsert),V10CADENA,
                          "CNODELETE",svddefbloque.cnodelete,sizeof(svddefbloque.cnodelete),V10CADENA,
                          "PRIVDELETE",svddefbloque.privdelete,sizeof(svddefbloque.privdelete),V10CADENA,
                          "CNOENTER",svddefbloque.cnoenter,sizeof(svddefbloque.cnoenter),V10CADENA,
                          "PRIVNOENTER",svddefbloque.privnoenter,sizeof(svddefbloque.privnoenter),V10CADENA,
                          "CNOUPDATE",svddefbloque.cnoupdate,sizeof(svddefbloque.cnoupdate),V10CADENA,
                          "PRIVUPDATE",svddefbloque.privupdate,sizeof(svddefbloque.privupdate),V10CADENA,
                          "CNOORAINS",svddefbloque.cnoorains,sizeof(svddefbloque.cnoorains),V10CADENA,
                          "PRIVORAINS",svddefbloque.privorains,sizeof(svddefbloque.privorains),V10CADENA,
                          "FAYUDA",svddefbloque.fayuda,sizeof(svddefbloque.fayuda),V10CADENA,
                          "FAUXILIAR",svddefbloque.fauxiliar,sizeof(svddefbloque.fauxiliar),V10CADENA,
                          "CODCOMEN",&svddefbloque.codcomen,sizeof(svddefbloque.codcomen),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deb);
        init = 1;
    }
}

diccionario *DEBdamediccionario(void)
{
     return(&ddeb);
}

int DEBselvddefbloque(char *nbloque,char *tipopantalla,vddefbloques *deb)
{
  int vdret;
  if (vdseldebvddefbloque==NULL) init_seldebvddefbloque();
  memset(&svddefbloque,0,sizeof(svddefbloque));
  strcpy(svddefbloque.nbloque,nbloque);
  strcpy(svddefbloque.tipopantalla,tipopantalla);
  vdret=ejefetchcursor(vdseldebvddefbloque);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldebvddefbloque. vdret %d. \n",DEBlog(&svddefbloque),vdret);
    return(VD_EERRORACLE);
   }
  *deb=svddefbloque;
  return(vdret);
}

int DEBactualizavddefbloque(vddefbloques *deb,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEBactualizavddefbloque:  %s .  \n",DEBlog(&svddefbloque));
  if (vdupdadebvddefbloque==NULL) init_updadebvddefbloque();
  svddefbloque=*deb;
  vdret=ejecutacursor(vdupdadebvddefbloque);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdadebvddefbloque);
     getcurerrornombre(vdupdadebvddefbloque->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdadebvddefbloque)!=1) return(VD_EERRORACLE);
  return(0);
}

int DEBinsert(vddefbloques *deb,int error)
{
  int vdret;
  if (!vdinsdeb) init_insdeb();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",DEBlog(&svddefbloque));
  svddefbloque=*deb;
  vdret=ejecutacursor(vdinsdeb);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsdeb);
     getcurerrornombre(vdinsdeb->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * DEBlog(vddefbloques *deb)
{
    sprintf(msglogDEB, "VDDEFBLOQUE: nbloque %s tipopantalla %s ",deb->nbloque,deb->tipopantalla);
    return(msglogDEB);
}

char * DEBdebug(vddefbloques *deb)
{
    debugestruct(&ddeb,deb,msgdebugDEB);
    return(msgdebugDEB);
}

