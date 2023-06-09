// Modulo generado automaticamente a partir de VDINFOHARD.DEF
//# Modulo : VDINFOHARD.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDINFOHARD
//#                        
//# Autor	 : MGM
//# Revisado por: 
//# Fecha  : 11-02-2008                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=IHA

#include "vd.h"
#define SELIHAVDINFOHARD "SELECT VDINFOHARD.ROWID,VDINFOHARD.IDINFOPICK,VDINFOHARD.DELAYCAB, "\
                    " VDINFOHARD.DELAYCAR,VDINFOHARD.PREPEAT,VDINFOHARD.SREPEAT, "\
                    " VDINFOHARD.TPARPADE,VDINFOHARD.TPARPADA,VDINFOHARD.MAXERROR, "\
                    " VDINFOHARD.RATIOERR,VDINFOHARD.STATGAPS,VDINFOHARD.TCICLO, "\
                    " VDINFOHARD.LIMITELINEA,VDINFOHARD.TENVTRAMA,VDINFOHARD.TIMEOUTTRAMA, "\
                    " VDINFOHARD.TIMEOUTWHO,VDINFOHARD.DIRIP1,VDINFOHARD.DIRIP2, "\
                    " VDINFOHARD.DIRIP3,VDINFOHARD.DIRIP4,VDINFOHARD.DIRIP5, "\
                    " VDINFOHARD.DIRIP6,VDINFOHARD.DIRIP7,VDINFOHARD.DIRIP8, "\
                    " VDINFOHARD.DIRIP9,VDINFOHARD.DIRIP10,VDINFOHARD.DIRIP11, "\
                    " VDINFOHARD.DIRIP12,VDINFOHARD.DIRIP13,VDINFOHARD.DIRIP14, "\
                    " VDINFOHARD.DIRIP15,VDINFOHARD.LIBPROCESO,VDINFOHARD.VDEXTRA, "\
                    " VDINFOHARD.CODOPEMODIF,VDINFOHARD.FECMODIF,VDINFOHARD.HORAMODIF, "\
                    " VDINFOHARD.CODCOMEN,VDINFOHARD.RANGOLINEAS "\
        " FROM VDINFOHARD"\
        " WHERE "\
               " VDINFOHARD.IDINFOPICK=:IDINFOPICK "
static v10cursors *vdselihavdinfohard;

static vdinfohards svdinfohard;

static diccols colvdinfohard[]={
	{"ROWID",V10CADENA,(size_t)&svdinfohard.rowid,sizeof(svdinfohard.rowid)},
	{"IDINFOPICK",V10LONG,(size_t)&svdinfohard.idinfopick,sizeof(svdinfohard.idinfopick)},
	{"DELAYCAB",V10LONG,(size_t)&svdinfohard.delaycab,sizeof(svdinfohard.delaycab)},
	{"DELAYCAR",V10LONG,(size_t)&svdinfohard.delaycar,sizeof(svdinfohard.delaycar)},
	{"PREPEAT",V10LONG,(size_t)&svdinfohard.prepeat,sizeof(svdinfohard.prepeat)},
	{"SREPEAT",V10LONG,(size_t)&svdinfohard.srepeat,sizeof(svdinfohard.srepeat)},
	{"TPARPADE",V10LONG,(size_t)&svdinfohard.tparpade,sizeof(svdinfohard.tparpade)},
	{"TPARPADA",V10LONG,(size_t)&svdinfohard.tparpada,sizeof(svdinfohard.tparpada)},
	{"MAXERROR",V10LONG,(size_t)&svdinfohard.maxerror,sizeof(svdinfohard.maxerror)},
	{"RATIOERR",V10LONG,(size_t)&svdinfohard.ratioerr,sizeof(svdinfohard.ratioerr)},
	{"STATGAPS",V10LONG,(size_t)&svdinfohard.statgaps,sizeof(svdinfohard.statgaps)},
	{"TCICLO",V10LONG,(size_t)&svdinfohard.tciclo,sizeof(svdinfohard.tciclo)},
	{"LIMITELINEA",V10LONG,(size_t)&svdinfohard.limitelinea,sizeof(svdinfohard.limitelinea)},
	{"TENVTRAMA",V10LONG,(size_t)&svdinfohard.tenvtrama,sizeof(svdinfohard.tenvtrama)},
	{"TIMEOUTTRAMA",V10LONG,(size_t)&svdinfohard.timeouttrama,sizeof(svdinfohard.timeouttrama)},
	{"TIMEOUTWHO",V10LONG,(size_t)&svdinfohard.timeoutwho,sizeof(svdinfohard.timeoutwho)},
	{"DIRIP1",V10CADENA,(size_t)&svdinfohard.dirip1,sizeof(svdinfohard.dirip1)},
	{"DIRIP2",V10CADENA,(size_t)&svdinfohard.dirip2,sizeof(svdinfohard.dirip2)},
	{"DIRIP3",V10CADENA,(size_t)&svdinfohard.dirip3,sizeof(svdinfohard.dirip3)},
	{"DIRIP4",V10CADENA,(size_t)&svdinfohard.dirip4,sizeof(svdinfohard.dirip4)},
	{"DIRIP5",V10CADENA,(size_t)&svdinfohard.dirip5,sizeof(svdinfohard.dirip5)},
	{"DIRIP6",V10CADENA,(size_t)&svdinfohard.dirip6,sizeof(svdinfohard.dirip6)},
	{"DIRIP7",V10CADENA,(size_t)&svdinfohard.dirip7,sizeof(svdinfohard.dirip7)},
	{"DIRIP8",V10CADENA,(size_t)&svdinfohard.dirip8,sizeof(svdinfohard.dirip8)},
	{"DIRIP9",V10CADENA,(size_t)&svdinfohard.dirip9,sizeof(svdinfohard.dirip9)},
	{"DIRIP10",V10CADENA,(size_t)&svdinfohard.dirip10,sizeof(svdinfohard.dirip10)},
	{"DIRIP11",V10CADENA,(size_t)&svdinfohard.dirip11,sizeof(svdinfohard.dirip11)},
	{"DIRIP12",V10CADENA,(size_t)&svdinfohard.dirip12,sizeof(svdinfohard.dirip12)},
	{"DIRIP13",V10CADENA,(size_t)&svdinfohard.dirip13,sizeof(svdinfohard.dirip13)},
	{"DIRIP14",V10CADENA,(size_t)&svdinfohard.dirip14,sizeof(svdinfohard.dirip14)},
	{"DIRIP15",V10CADENA,(size_t)&svdinfohard.dirip15,sizeof(svdinfohard.dirip15)},
	{"LIBPROCESO",V10CADENA,(size_t)&svdinfohard.libproceso,sizeof(svdinfohard.libproceso)},
	{"VDEXTRA",V10CADENA,(size_t)&svdinfohard.vdextra,sizeof(svdinfohard.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdinfohard.codopemodif,sizeof(svdinfohard.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdinfohard.fecmodif,sizeof(svdinfohard.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdinfohard.horamodif,sizeof(svdinfohard.horamodif)},
	{"CODCOMEN",V10LONG,(size_t)&svdinfohard.codcomen,sizeof(svdinfohard.codcomen)},
	{"RANGOLINEAS",V10CADENA,(size_t)&svdinfohard.rangolineas,sizeof(svdinfohard.rangolineas)}
	};
static diccionarios dvdinfohard[]={
    {colvdinfohard,38}
};
diccionario diha={dvdinfohard,1};

static char msglogIHA[LCADENA];
static char msgdebugIHA[LCADENABIG];
static int init=0;


static void fin_vd_iha(void)
{
if (vdselihavdinfohard) {
    liberacursor(vdselihavdinfohard);
    vdselihavdinfohard = NULL;
}
}
static void init_selihavdinfohard(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdinfohard[0].numcol;nc++) dvdinfohard[0].c[nc].offset-=(size_t)&svdinfohard;
    vdselihavdinfohard=abrecursordebug(SELIHAVDINFOHARD,1280);
    definetodo(vdselihavdinfohard,svdinfohard.rowid,sizeof(svdinfohard.rowid),V10CADENA,
                          &svdinfohard.idinfopick,sizeof(svdinfohard.idinfopick),V10LONG,
                          &svdinfohard.delaycab,sizeof(svdinfohard.delaycab),V10LONG,
                          &svdinfohard.delaycar,sizeof(svdinfohard.delaycar),V10LONG,
                          &svdinfohard.prepeat,sizeof(svdinfohard.prepeat),V10LONG,
                          &svdinfohard.srepeat,sizeof(svdinfohard.srepeat),V10LONG,
                          &svdinfohard.tparpade,sizeof(svdinfohard.tparpade),V10LONG,
                          &svdinfohard.tparpada,sizeof(svdinfohard.tparpada),V10LONG,
                          &svdinfohard.maxerror,sizeof(svdinfohard.maxerror),V10LONG,
                          &svdinfohard.ratioerr,sizeof(svdinfohard.ratioerr),V10LONG,
                          &svdinfohard.statgaps,sizeof(svdinfohard.statgaps),V10LONG,
                          &svdinfohard.tciclo,sizeof(svdinfohard.tciclo),V10LONG,
                          &svdinfohard.limitelinea,sizeof(svdinfohard.limitelinea),V10LONG,
                          &svdinfohard.tenvtrama,sizeof(svdinfohard.tenvtrama),V10LONG,
                          &svdinfohard.timeouttrama,sizeof(svdinfohard.timeouttrama),V10LONG,
                          &svdinfohard.timeoutwho,sizeof(svdinfohard.timeoutwho),V10LONG,
                          svdinfohard.dirip1,sizeof(svdinfohard.dirip1),V10CADENA,
                          svdinfohard.dirip2,sizeof(svdinfohard.dirip2),V10CADENA,
                          svdinfohard.dirip3,sizeof(svdinfohard.dirip3),V10CADENA,
                          svdinfohard.dirip4,sizeof(svdinfohard.dirip4),V10CADENA,
                          svdinfohard.dirip5,sizeof(svdinfohard.dirip5),V10CADENA,
                          svdinfohard.dirip6,sizeof(svdinfohard.dirip6),V10CADENA,
                          svdinfohard.dirip7,sizeof(svdinfohard.dirip7),V10CADENA,
                          svdinfohard.dirip8,sizeof(svdinfohard.dirip8),V10CADENA,
                          svdinfohard.dirip9,sizeof(svdinfohard.dirip9),V10CADENA,
                          svdinfohard.dirip10,sizeof(svdinfohard.dirip10),V10CADENA,
                          svdinfohard.dirip11,sizeof(svdinfohard.dirip11),V10CADENA,
                          svdinfohard.dirip12,sizeof(svdinfohard.dirip12),V10CADENA,
                          svdinfohard.dirip13,sizeof(svdinfohard.dirip13),V10CADENA,
                          svdinfohard.dirip14,sizeof(svdinfohard.dirip14),V10CADENA,
                          svdinfohard.dirip15,sizeof(svdinfohard.dirip15),V10CADENA,
                          svdinfohard.libproceso,sizeof(svdinfohard.libproceso),V10CADENA,
                          svdinfohard.vdextra,sizeof(svdinfohard.vdextra),V10CADENA,
                          svdinfohard.codopemodif,sizeof(svdinfohard.codopemodif),V10CADENA,
                          &svdinfohard.fecmodif,sizeof(svdinfohard.fecmodif),V10LONG,
                          svdinfohard.horamodif,sizeof(svdinfohard.horamodif),V10CADENA,
                          &svdinfohard.codcomen,sizeof(svdinfohard.codcomen),V10LONG,
                          svdinfohard.rangolineas,sizeof(svdinfohard.rangolineas),V10CADENA,
                          NULL);
    bindtodo(vdselihavdinfohard,"IDINFOPICK",&svdinfohard.idinfopick,sizeof(svdinfohard.idinfopick),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_iha);
        init = 1;
    }
}

diccionario *IHAdamediccionario(void)
{
     return(&diha);
}

int IHAselvdinfohard(long idinfopick,vdinfohards *iha)
{
  int vdret;
  if (vdselihavdinfohard==NULL) init_selihavdinfohard();
  memset(&svdinfohard,0,sizeof(svdinfohard));
  svdinfohard.idinfopick=idinfopick;
  vdret=ejefetchcursor(vdselihavdinfohard);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselihavdinfohard. vdret %d. \n",IHAlog(&svdinfohard),vdret);
    return(VD_EERRORACLE);
   }
  *iha=svdinfohard;
  return(vdret);
}

char * IHAlog(vdinfohards *iha)
{
    sprintf(msglogIHA, "VDINFOHARD: idinfopick %ld ",iha->idinfopick);
    return(msglogIHA);
}

char * IHAdebug(vdinfohards *iha)
{
    debugestruct(&diha,iha,msgdebugIHA);
    return(msgdebugIHA);
}

