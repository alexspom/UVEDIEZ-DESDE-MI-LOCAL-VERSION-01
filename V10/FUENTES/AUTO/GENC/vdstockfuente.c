// Modulo generado automaticamente a partir de VDSTOCKFUENTE.DEF
//#***
//# VDSTOCKFUENTE.DEF - Generación automática del código c para la tabla de Fuente de Stock                                                       
//# 
//# Propósito: Funciones de acceso a la tabla VDSTOCKFUENTE
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 17-07-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=FTE
//EXTRA=COMEN,V10CADENA,1025
//
//RECORRE=STATUS,STATUS;
//UPDATE=STATUS,STATUS;
//
//INTERFASE
//UPDATE
//LOCK
//INSERT 
//DELETE

#include "vd.h"
#define SELFTESTATUS "SELECT VDSTOCKFUENTE.ROWID,VDSTOCKFUENTE.SEQFUENTE,VDSTOCKFUENTE.TIPOFUENTE, "\
                    " VDSTOCKFUENTE.CODUBI,VDSTOCKFUENTE.CODMAT,VDSTOCKFUENTE.TIPOCONTE, "\
                    " VDSTOCKFUENTE.CODART,VDSTOCKFUENTE.CODLOT,VDSTOCKFUENTE.CANTIDADHOST, "\
                    " VDSTOCKFUENTE.UNIDADESHOST,VDSTOCKFUENTE.UNIEMBHOST,VDSTOCKFUENTE.EMBCONT, "\
                    " VDSTOCKFUENTE.TIPOEMBA,VDSTOCKFUENTE.PRECIOUNI,VDSTOCKFUENTE.BLOQUEOS, "\
                    " VDSTOCKFUENTE.BULTO,VDSTOCKFUENTE.MARCASTK,VDSTOCKFUENTE.NUMEROSERIE, "\
                    " VDSTOCKFUENTE.CODRECEP,VDSTOCKFUENTE.PESOUNI,VDSTOCKFUENTE.CODLOTPROV, "\
                    " VDSTOCKFUENTE.CADUCI,VDSTOCKFUENTE.RETEST,VDSTOCKFUENTE.BLOQLOTE, "\
                    " VDSTOCKFUENTE.POTENCIA,VDSTOCKFUENTE.SWTPRECIO,VDSTOCKFUENTE.MUESTREADO, "\
                    " VDSTOCKFUENTE.STATUS,VDSTOCKFUENTE.VDEXTRA,VDSTOCKFUENTE.CODCOMEN, "\
                    " VDSTOCKFUENTE.CODOPEMODIF,VDSTOCKFUENTE.FECMODIF,VDSTOCKFUENTE.HORAMODIF, "\
                    " VDSTOCKFUENTE.FECENTRADA,VDSTOCKFUENTE.HORAENTRADA "\
        " FROM VDSTOCKFUENTE"\
        " WHERE "\
               " VDSTOCKFUENTE.STATUS=:STATUS "
static v10cursors *vdselftestatus;

#define SELFTEVDSTOCKFUENTE "SELECT VDSTOCKFUENTE.ROWID,VDSTOCKFUENTE.SEQFUENTE,VDSTOCKFUENTE.TIPOFUENTE, "\
                    " VDSTOCKFUENTE.CODUBI,VDSTOCKFUENTE.CODMAT,VDSTOCKFUENTE.TIPOCONTE, "\
                    " VDSTOCKFUENTE.CODART,VDSTOCKFUENTE.CODLOT,VDSTOCKFUENTE.CANTIDADHOST, "\
                    " VDSTOCKFUENTE.UNIDADESHOST,VDSTOCKFUENTE.UNIEMBHOST,VDSTOCKFUENTE.EMBCONT, "\
                    " VDSTOCKFUENTE.TIPOEMBA,VDSTOCKFUENTE.PRECIOUNI,VDSTOCKFUENTE.BLOQUEOS, "\
                    " VDSTOCKFUENTE.BULTO,VDSTOCKFUENTE.MARCASTK,VDSTOCKFUENTE.NUMEROSERIE, "\
                    " VDSTOCKFUENTE.CODRECEP,VDSTOCKFUENTE.PESOUNI,VDSTOCKFUENTE.CODLOTPROV, "\
                    " VDSTOCKFUENTE.CADUCI,VDSTOCKFUENTE.RETEST,VDSTOCKFUENTE.BLOQLOTE, "\
                    " VDSTOCKFUENTE.POTENCIA,VDSTOCKFUENTE.SWTPRECIO,VDSTOCKFUENTE.MUESTREADO, "\
                    " VDSTOCKFUENTE.STATUS,VDSTOCKFUENTE.VDEXTRA,VDSTOCKFUENTE.CODCOMEN, "\
                    " VDSTOCKFUENTE.CODOPEMODIF,VDSTOCKFUENTE.FECMODIF,VDSTOCKFUENTE.HORAMODIF, "\
                    " VDSTOCKFUENTE.FECENTRADA,VDSTOCKFUENTE.HORAENTRADA "\
        " FROM VDSTOCKFUENTE"\
        " WHERE "\
               " VDSTOCKFUENTE.SEQFUENTE=:SEQFUENTE "
static v10cursors *vdselftevdstockfuente;

#define SELFTEROWIDLOCK "SELECT ROWID,SEQFUENTE,TIPOFUENTE,CODUBI,CODMAT,TIPOCONTE,CODART, "\
                    " CODLOT,CANTIDADHOST,UNIDADESHOST,UNIEMBHOST,EMBCONT,TIPOEMBA,PRECIOUNI, "\
                    " BLOQUEOS,BULTO,MARCASTK,NUMEROSERIE,CODRECEP,PESOUNI,CODLOTPROV, "\
                    " CADUCI,RETEST,BLOQLOTE,POTENCIA,SWTPRECIO,MUESTREADO,STATUS, "\
                    " VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,FECENTRADA,HORAENTRADA "\
        " FROM VDSTOCKFUENTE "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselfterowidlock;

#define UPDAFTESTATUS "UPDATE VDSTOCKFUENTE SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaftestatus;

#define UPDAFTE "UPDATE VDSTOCKFUENTE SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " SEQFUENTE=:SEQFUENTE , "\
               " TIPOFUENTE=:TIPOFUENTE , "\
               " CODUBI=:CODUBI , "\
               " CODMAT=:CODMAT , "\
               " TIPOCONTE=:TIPOCONTE , "\
               " CODART=:CODART , "\
               " CODLOT=:CODLOT , "\
               " CANTIDADHOST=:CANTIDADHOST , "\
               " UNIDADESHOST=:UNIDADESHOST , "\
               " UNIEMBHOST=:UNIEMBHOST , "\
               " EMBCONT=:EMBCONT , "\
               " TIPOEMBA=:TIPOEMBA , "\
               " PRECIOUNI=:PRECIOUNI , "\
               " BLOQUEOS=:BLOQUEOS , "\
               " BULTO=:BULTO , "\
               " MARCASTK=:MARCASTK , "\
               " NUMEROSERIE=:NUMEROSERIE , "\
               " CODRECEP=:CODRECEP , "\
               " PESOUNI=:PESOUNI , "\
               " CODLOTPROV=:CODLOTPROV , "\
               " CADUCI=:CADUCI , "\
               " RETEST=:RETEST , "\
               " BLOQLOTE=:BLOQLOTE , "\
               " POTENCIA=:POTENCIA , "\
               " SWTPRECIO=:SWTPRECIO , "\
               " MUESTREADO=:MUESTREADO , "\
               " STATUS=:STATUS , "\
               " VDEXTRA=:VDEXTRA , "\
               " CODCOMEN=:CODCOMEN , "\
               " FECENTRADA=:FECENTRADA , "\
               " HORAENTRADA=:HORAENTRADA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaftevdstockfuente;

#define INSFTE "INSERT INTO VDSTOCKFUENTE (SEQFUENTE,TIPOFUENTE,CODUBI,CODMAT,TIPOCONTE,CODART, "\
                    " CODLOT,CANTIDADHOST,UNIDADESHOST,UNIEMBHOST,EMBCONT,TIPOEMBA,PRECIOUNI, "\
                    " BLOQUEOS,BULTO,MARCASTK,NUMEROSERIE,CODRECEP,PESOUNI,CODLOTPROV, "\
                    " CADUCI,RETEST,BLOQLOTE,POTENCIA,SWTPRECIO,MUESTREADO,STATUS, "\
                    " VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,FECENTRADA,HORAENTRADA "\
       " ) VALUES ( "\
                    " :SEQFUENTE,:TIPOFUENTE,:CODUBI,:CODMAT,:TIPOCONTE,:CODART, "\
                    " :CODLOT,:CANTIDADHOST,:UNIDADESHOST,:UNIEMBHOST,:EMBCONT,:TIPOEMBA,:PRECIOUNI, "\
                    " :BLOQUEOS,:BULTO,:MARCASTK,:NUMEROSERIE,:CODRECEP,:PESOUNI,:CODLOTPROV, "\
                    " :CADUCI,:RETEST,:BLOQLOTE,:POTENCIA,:SWTPRECIO,:MUESTREADO,:STATUS, "\
                    " :VDEXTRA,:CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:FECENTRADA,:HORAENTRADA) "
static v10cursors *vdinsfte;

#define DELFTE "DELETE VDSTOCKFUENTE WHERE ROWID=:MIROWID "
static v10cursors *vddelfte;

static vdstockfuentes svdstockfuente;

static diccols colvdstockfuente[]={
	{"ROWID",V10CADENA,(size_t)&svdstockfuente.rowid,sizeof(svdstockfuente.rowid)},
	{"SEQFUENTE",V10LONG,(size_t)&svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente)},
	{"TIPOFUENTE",V10CADENA,(size_t)&svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente)},
	{"CODUBI",V10CADENA,(size_t)&svdstockfuente.codubi,sizeof(svdstockfuente.codubi)},
	{"CODMAT",V10CADENA,(size_t)&svdstockfuente.codmat,sizeof(svdstockfuente.codmat)},
	{"TIPOCONTE",V10CADENA,(size_t)&svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte)},
	{"CODART",V10CADENA,(size_t)&svdstockfuente.codart,sizeof(svdstockfuente.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdstockfuente.codlot,sizeof(svdstockfuente.codlot)},
	{"CANTIDADHOST",V10CADENA,(size_t)&svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost)},
	{"UNIDADESHOST",V10CADENA,(size_t)&svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost)},
	{"UNIEMBHOST",V10CADENA,(size_t)&svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost)},
	{"EMBCONT",V10LONG,(size_t)&svdstockfuente.embcont,sizeof(svdstockfuente.embcont)},
	{"TIPOEMBA",V10CADENA,(size_t)&svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni)},
	{"BLOQUEOS",V10CADENA,(size_t)&svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos)},
	{"BULTO",V10CADENA,(size_t)&svdstockfuente.bulto,sizeof(svdstockfuente.bulto)},
	{"MARCASTK",V10CADENA,(size_t)&svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie)},
	{"CODRECEP",V10CADENA,(size_t)&svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep)},
	{"PESOUNI",V10DOUBLE,(size_t)&svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni)},
	{"CODLOTPROV",V10CADENA,(size_t)&svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov)},
	{"CADUCI",V10CADENA,(size_t)&svdstockfuente.caduci,sizeof(svdstockfuente.caduci)},
	{"RETEST",V10CADENA,(size_t)&svdstockfuente.retest,sizeof(svdstockfuente.retest)},
	{"BLOQLOTE",V10CADENA,(size_t)&svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote)},
	{"POTENCIA",V10DOUBLE,(size_t)&svdstockfuente.potencia,sizeof(svdstockfuente.potencia)},
	{"SWTPRECIO",V10CADENA,(size_t)&svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio)},
	{"MUESTREADO",V10CADENA,(size_t)&svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado)},
	{"STATUS",V10LONG,(size_t)&svdstockfuente.status,sizeof(svdstockfuente.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdstockfuente.codopemodif,sizeof(svdstockfuente.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdstockfuente.fecmodif,sizeof(svdstockfuente.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdstockfuente.horamodif,sizeof(svdstockfuente.horamodif)},
	{"FECENTRADA",V10LONG,(size_t)&svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada)},
	{"HORAENTRADA",V10CADENA,(size_t)&svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada)},
	{"COMEN",V10CADENA,(size_t)&svdstockfuente.comen,sizeof(svdstockfuente.comen)}
	};
static diccionarios dvdstockfuente[]={
    {colvdstockfuente,36}
};
diccionario dfte={dvdstockfuente,1};

static char msglogFTE[LCADENA];
static char msgdebugFTE[LCADENABIG];
static int init=0;


static void fin_vd_fte(void)
{
if (vdselftestatus) {
    liberacursor(vdselftestatus);
    vdselftestatus = NULL;
}
if (vdselftevdstockfuente) {
    liberacursor(vdselftevdstockfuente);
    vdselftevdstockfuente = NULL;
}
if (vdselfterowidlock) {
    liberacursor(vdselfterowidlock);
    vdselfterowidlock = NULL;
}
if (vdupdaftestatus) {
    liberacursor(vdupdaftestatus);
    vdupdaftestatus = NULL;
}
if (vdupdaftevdstockfuente) {
    liberacursor(vdupdaftevdstockfuente);
    vdupdaftevdstockfuente = NULL;
}
if (vdinsfte != NULL) {
    liberacursor(vdinsfte);
    vdinsfte = NULL;
}
if (vddelfte != NULL) {
    liberacursor(vddelfte);
    vddelfte = NULL;
}
}
static void init_selftestatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdselftestatus=abrecursordebug(SELFTESTATUS,1280);
    definetodo(vdselftestatus,svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          &svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente),V10CADENA,
                          svdstockfuente.codubi,sizeof(svdstockfuente.codubi),V10CADENA,
                          svdstockfuente.codmat,sizeof(svdstockfuente.codmat),V10CADENA,
                          svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte),V10CADENA,
                          svdstockfuente.codart,sizeof(svdstockfuente.codart),V10CADENA,
                          svdstockfuente.codlot,sizeof(svdstockfuente.codlot),V10CADENA,
                          svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost),V10CADENA,
                          svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost),V10CADENA,
                          svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost),V10CADENA,
                          &svdstockfuente.embcont,sizeof(svdstockfuente.embcont),V10LONG,
                          svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba),V10CADENA,
                          &svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni),V10DOUBLE,
                          svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos),V10CADENA,
                          svdstockfuente.bulto,sizeof(svdstockfuente.bulto),V10CADENA,
                          svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk),V10CADENA,
                          svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie),V10CADENA,
                          svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep),V10CADENA,
                          &svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni),V10DOUBLE,
                          svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov),V10CADENA,
                          svdstockfuente.caduci,sizeof(svdstockfuente.caduci),V10CADENA,
                          svdstockfuente.retest,sizeof(svdstockfuente.retest),V10CADENA,
                          svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote),V10CADENA,
                          &svdstockfuente.potencia,sizeof(svdstockfuente.potencia),V10DOUBLE,
                          svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio),V10CADENA,
                          svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado),V10CADENA,
                          &svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra),V10CADENA,
                          &svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen),V10LONG,
                          svdstockfuente.codopemodif,sizeof(svdstockfuente.codopemodif),V10CADENA,
                          &svdstockfuente.fecmodif,sizeof(svdstockfuente.fecmodif),V10LONG,
                          svdstockfuente.horamodif,sizeof(svdstockfuente.horamodif),V10CADENA,
                          &svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada),V10LONG,
                          svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada),V10CADENA,
                          NULL);
    bindtodo(vdselftestatus,"STATUS",&svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_selftevdstockfuente(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdselftevdstockfuente=abrecursordebug(SELFTEVDSTOCKFUENTE,1280);
    definetodo(vdselftevdstockfuente,svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          &svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente),V10CADENA,
                          svdstockfuente.codubi,sizeof(svdstockfuente.codubi),V10CADENA,
                          svdstockfuente.codmat,sizeof(svdstockfuente.codmat),V10CADENA,
                          svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte),V10CADENA,
                          svdstockfuente.codart,sizeof(svdstockfuente.codart),V10CADENA,
                          svdstockfuente.codlot,sizeof(svdstockfuente.codlot),V10CADENA,
                          svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost),V10CADENA,
                          svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost),V10CADENA,
                          svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost),V10CADENA,
                          &svdstockfuente.embcont,sizeof(svdstockfuente.embcont),V10LONG,
                          svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba),V10CADENA,
                          &svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni),V10DOUBLE,
                          svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos),V10CADENA,
                          svdstockfuente.bulto,sizeof(svdstockfuente.bulto),V10CADENA,
                          svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk),V10CADENA,
                          svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie),V10CADENA,
                          svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep),V10CADENA,
                          &svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni),V10DOUBLE,
                          svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov),V10CADENA,
                          svdstockfuente.caduci,sizeof(svdstockfuente.caduci),V10CADENA,
                          svdstockfuente.retest,sizeof(svdstockfuente.retest),V10CADENA,
                          svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote),V10CADENA,
                          &svdstockfuente.potencia,sizeof(svdstockfuente.potencia),V10DOUBLE,
                          svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio),V10CADENA,
                          svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado),V10CADENA,
                          &svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra),V10CADENA,
                          &svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen),V10LONG,
                          svdstockfuente.codopemodif,sizeof(svdstockfuente.codopemodif),V10CADENA,
                          &svdstockfuente.fecmodif,sizeof(svdstockfuente.fecmodif),V10LONG,
                          svdstockfuente.horamodif,sizeof(svdstockfuente.horamodif),V10CADENA,
                          &svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada),V10LONG,
                          svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada),V10CADENA,
                          NULL);
    bindtodo(vdselftevdstockfuente,"SEQFUENTE",&svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_selfterowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdselfterowidlock=abrecursordebug(SELFTEROWIDLOCK,1280);
    definetodo(vdselfterowidlock,svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          &svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente),V10CADENA,
                          svdstockfuente.codubi,sizeof(svdstockfuente.codubi),V10CADENA,
                          svdstockfuente.codmat,sizeof(svdstockfuente.codmat),V10CADENA,
                          svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte),V10CADENA,
                          svdstockfuente.codart,sizeof(svdstockfuente.codart),V10CADENA,
                          svdstockfuente.codlot,sizeof(svdstockfuente.codlot),V10CADENA,
                          svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost),V10CADENA,
                          svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost),V10CADENA,
                          svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost),V10CADENA,
                          &svdstockfuente.embcont,sizeof(svdstockfuente.embcont),V10LONG,
                          svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba),V10CADENA,
                          &svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni),V10DOUBLE,
                          svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos),V10CADENA,
                          svdstockfuente.bulto,sizeof(svdstockfuente.bulto),V10CADENA,
                          svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk),V10CADENA,
                          svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie),V10CADENA,
                          svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep),V10CADENA,
                          &svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni),V10DOUBLE,
                          svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov),V10CADENA,
                          svdstockfuente.caduci,sizeof(svdstockfuente.caduci),V10CADENA,
                          svdstockfuente.retest,sizeof(svdstockfuente.retest),V10CADENA,
                          svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote),V10CADENA,
                          &svdstockfuente.potencia,sizeof(svdstockfuente.potencia),V10DOUBLE,
                          svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio),V10CADENA,
                          svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado),V10CADENA,
                          &svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra),V10CADENA,
                          &svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen),V10LONG,
                          svdstockfuente.codopemodif,sizeof(svdstockfuente.codopemodif),V10CADENA,
                          &svdstockfuente.fecmodif,sizeof(svdstockfuente.fecmodif),V10LONG,
                          svdstockfuente.horamodif,sizeof(svdstockfuente.horamodif),V10CADENA,
                          &svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada),V10LONG,
                          svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada),V10CADENA,
                          NULL);
    bindtodo(vdselfterowidlock,"MIROWID",svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_updaftestatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdupdaftestatus=abrecursordebug(UPDAFTESTATUS,1280);
    bindtodo(vdupdaftestatus,"STATUS",&svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          "MIROWID",svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_updaftevdstockfuente(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdupdaftevdstockfuente=abrecursordebug(UPDAFTE,1280);
    bindtodo(vdupdaftevdstockfuente,"SEQFUENTE",&svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          "TIPOFUENTE",svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente),V10CADENA,
                          "CODUBI",svdstockfuente.codubi,sizeof(svdstockfuente.codubi),V10CADENA,
                          "CODMAT",svdstockfuente.codmat,sizeof(svdstockfuente.codmat),V10CADENA,
                          "TIPOCONTE",svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte),V10CADENA,
                          "CODART",svdstockfuente.codart,sizeof(svdstockfuente.codart),V10CADENA,
                          "CODLOT",svdstockfuente.codlot,sizeof(svdstockfuente.codlot),V10CADENA,
                          "CANTIDADHOST",svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost),V10CADENA,
                          "UNIDADESHOST",svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost),V10CADENA,
                          "UNIEMBHOST",svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost),V10CADENA,
                          "EMBCONT",&svdstockfuente.embcont,sizeof(svdstockfuente.embcont),V10LONG,
                          "TIPOEMBA",svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba),V10CADENA,
                          "PRECIOUNI",&svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni),V10DOUBLE,
                          "BLOQUEOS",svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos),V10CADENA,
                          "BULTO",svdstockfuente.bulto,sizeof(svdstockfuente.bulto),V10CADENA,
                          "MARCASTK",svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk),V10CADENA,
                          "NUMEROSERIE",svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie),V10CADENA,
                          "CODRECEP",svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep),V10CADENA,
                          "PESOUNI",&svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni),V10DOUBLE,
                          "CODLOTPROV",svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov),V10CADENA,
                          "CADUCI",svdstockfuente.caduci,sizeof(svdstockfuente.caduci),V10CADENA,
                          "RETEST",svdstockfuente.retest,sizeof(svdstockfuente.retest),V10CADENA,
                          "BLOQLOTE",svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote),V10CADENA,
                          "POTENCIA",&svdstockfuente.potencia,sizeof(svdstockfuente.potencia),V10DOUBLE,
                          "SWTPRECIO",svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio),V10CADENA,
                          "MUESTREADO",svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado),V10CADENA,
                          "STATUS",&svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          "VDEXTRA",svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra),V10CADENA,
                          "CODCOMEN",&svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen),V10LONG,
                          "FECENTRADA",&svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada),V10LONG,
                          "HORAENTRADA",svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada),V10CADENA,
                          "MIROWID",svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_insfte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vdinsfte=abrecursordebug(INSFTE,1280);
    bindtodo(vdinsfte,"SEQFUENTE",&svdstockfuente.seqfuente,sizeof(svdstockfuente.seqfuente),V10LONG,
                          "TIPOFUENTE",svdstockfuente.tipofuente,sizeof(svdstockfuente.tipofuente),V10CADENA,
                          "CODUBI",svdstockfuente.codubi,sizeof(svdstockfuente.codubi),V10CADENA,
                          "CODMAT",svdstockfuente.codmat,sizeof(svdstockfuente.codmat),V10CADENA,
                          "TIPOCONTE",svdstockfuente.tipoconte,sizeof(svdstockfuente.tipoconte),V10CADENA,
                          "CODART",svdstockfuente.codart,sizeof(svdstockfuente.codart),V10CADENA,
                          "CODLOT",svdstockfuente.codlot,sizeof(svdstockfuente.codlot),V10CADENA,
                          "CANTIDADHOST",svdstockfuente.cantidadhost,sizeof(svdstockfuente.cantidadhost),V10CADENA,
                          "UNIDADESHOST",svdstockfuente.unidadeshost,sizeof(svdstockfuente.unidadeshost),V10CADENA,
                          "UNIEMBHOST",svdstockfuente.uniembhost,sizeof(svdstockfuente.uniembhost),V10CADENA,
                          "EMBCONT",&svdstockfuente.embcont,sizeof(svdstockfuente.embcont),V10LONG,
                          "TIPOEMBA",svdstockfuente.tipoemba,sizeof(svdstockfuente.tipoemba),V10CADENA,
                          "PRECIOUNI",&svdstockfuente.preciouni,sizeof(svdstockfuente.preciouni),V10DOUBLE,
                          "BLOQUEOS",svdstockfuente.bloqueos,sizeof(svdstockfuente.bloqueos),V10CADENA,
                          "BULTO",svdstockfuente.bulto,sizeof(svdstockfuente.bulto),V10CADENA,
                          "MARCASTK",svdstockfuente.marcastk,sizeof(svdstockfuente.marcastk),V10CADENA,
                          "NUMEROSERIE",svdstockfuente.numeroserie,sizeof(svdstockfuente.numeroserie),V10CADENA,
                          "CODRECEP",svdstockfuente.codrecep,sizeof(svdstockfuente.codrecep),V10CADENA,
                          "PESOUNI",&svdstockfuente.pesouni,sizeof(svdstockfuente.pesouni),V10DOUBLE,
                          "CODLOTPROV",svdstockfuente.codlotprov,sizeof(svdstockfuente.codlotprov),V10CADENA,
                          "CADUCI",svdstockfuente.caduci,sizeof(svdstockfuente.caduci),V10CADENA,
                          "RETEST",svdstockfuente.retest,sizeof(svdstockfuente.retest),V10CADENA,
                          "BLOQLOTE",svdstockfuente.bloqlote,sizeof(svdstockfuente.bloqlote),V10CADENA,
                          "POTENCIA",&svdstockfuente.potencia,sizeof(svdstockfuente.potencia),V10DOUBLE,
                          "SWTPRECIO",svdstockfuente.swtprecio,sizeof(svdstockfuente.swtprecio),V10CADENA,
                          "MUESTREADO",svdstockfuente.muestreado,sizeof(svdstockfuente.muestreado),V10CADENA,
                          "STATUS",&svdstockfuente.status,sizeof(svdstockfuente.status),V10LONG,
                          "VDEXTRA",svdstockfuente.vdextra,sizeof(svdstockfuente.vdextra),V10CADENA,
                          "CODCOMEN",&svdstockfuente.codcomen,sizeof(svdstockfuente.codcomen),V10LONG,
                          "FECENTRADA",&svdstockfuente.fecentrada,sizeof(svdstockfuente.fecentrada),V10LONG,
                          "HORAENTRADA",svdstockfuente.horaentrada,sizeof(svdstockfuente.horaentrada),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

static void init_delfte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdstockfuente[0].numcol;nc++) dvdstockfuente[0].c[nc].offset-=(size_t)&svdstockfuente;
    vddelfte=abrecursordebug(DELFTE,1280);
    bindtodo(vddelfte,"MIROWID",svdstockfuente.rowid,sizeof(svdstockfuente.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_fte);
        init = 1;
    }
}

diccionario *FTEdamediccionario(void)
{
     return(&dfte);
}

int FTEbuscastatus(long status,vdstockfuentes *fte)
{
  int vdret;
  memset(&svdstockfuente,0,sizeof(svdstockfuente));
  svdstockfuente.status=status;
  if (vdselftestatus==NULL) init_selftestatus();
  vdret=ejefetchcursor(vdselftestatus);
  if (vdret==0) {
     *fte=svdstockfuente;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselftestatus. vdret %d. \n",FTElog(&svdstockfuente),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int FTEnextstatus(vdstockfuentes *fte)
{
  int vdret;
  vdret=fetchcursor(vdselftestatus);
  if (vdret==0) {
     *fte=svdstockfuente;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselftestatus. vdret %d. \n",FTElog(&svdstockfuente),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselftestatus);
  return(VD_EERRORACLE);
}

int FTEselvdstockfuente(long seqfuente,vdstockfuentes *fte)
{
  int vdret;
  if (vdselftevdstockfuente==NULL) init_selftevdstockfuente();
  memset(&svdstockfuente,0,sizeof(svdstockfuente));
  svdstockfuente.seqfuente=seqfuente;
  vdret=ejefetchcursor(vdselftevdstockfuente);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselftevdstockfuente. vdret %d. \n",FTElog(&svdstockfuente),vdret);
    return(VD_EERRORACLE);
   }
  *fte=svdstockfuente;
  return(vdret);
}

int FTElock(vdstockfuentes *fte,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdstockfuente=*fte;
    if (vdselfterowidlock==NULL) init_selfterowidlock();
    savepoint("lockvdstockfuente");
    while (1) {
        vdret=ejefetchcursor(vdselfterowidlock);
        if (vdret==0) break;
        if (vdret==BLOQUEADO && wait) {
           Sleep(1000);
           if (hay_tecla()) if (tecla()==esc) return(VD_EERRBLOQUEO);
           continue;
         } else {
           if (wait==0) return(VD_EERRBLOQUEO);
         }
    }
    if (vdret) return(VD_EERRORACLE);
    if (verificar==0) return(vdret);
    va_start(arg,verificar);
    vdret=vverificacampos(fte,&svdstockfuente,&dvdstockfuente[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdstockfuente");
    return(vdret);
}

int FTEactualizastatus(vdstockfuentes *fte,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando FTEactualizastatus:  %s .  \n",FTElog(&svdstockfuente));
  if (vdupdaftestatus==NULL) init_updaftestatus();
  svdstockfuente=*fte;
  vdret=ejecutacursor(vdupdaftestatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaftestatus);
     getcurerrornombre(vdupdaftestatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaftestatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int FTEactualizavdstockfuente(vdstockfuentes *fte,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando FTEactualizavdstockfuente:  %s .  \n",FTElog(&svdstockfuente));
  if (vdupdaftevdstockfuente==NULL) init_updaftevdstockfuente();
  svdstockfuente=*fte;
  vdret=ejecutacursor(vdupdaftevdstockfuente);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaftevdstockfuente);
     getcurerrornombre(vdupdaftevdstockfuente->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaftevdstockfuente)!=1) return(VD_EERRORACLE);
  return(0);
}

int FTEinsert(vdstockfuentes *fte,int error)
{
  int vdret;
  if (!vdinsfte) init_insfte();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",FTElog(&svdstockfuente));
  svdstockfuente=*fte;
  vdret=ejecutacursor(vdinsfte);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsfte);
     getcurerrornombre(vdinsfte->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int FTEdel(vdstockfuentes *fte,int error)
{
  int vdret;
  svdstockfuente=*fte;
  if (vddelfte==NULL) init_delfte();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",FTElog(&svdstockfuente));
  vdret=ejecutacursor(vddelfte);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelfte);
     getcurerrornombre(vddelfte->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int FTEinter(vdstockfuentes *fte)
{
  int vdret = 0;
  if (vdselftevdstockfuente==NULL) init_selftevdstockfuente();
  memset(&svdstockfuente,0,sizeof(svdstockfuente));
  svdstockfuente.seqfuente = fte->seqfuente;
  vdret=ejefetchcursor(vdselftevdstockfuente);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselftevdstockfuente. vdret %d. \n",FTElog(&svdstockfuente),vdret);
    return(VD_EERRORACLE);
  }

  *fte=svdstockfuente;
  return(vdret);
}

char * FTElog(vdstockfuentes *fte)
{
    sprintf(msglogFTE, "VDSTOCKFUENTE: seqfuente %ld ",fte->seqfuente);
    return(msglogFTE);
}

char * FTEdebug(vdstockfuentes *fte)
{
    debugestruct(&dfte,fte,msgdebugFTE);
    return(msgdebugFTE);
}

