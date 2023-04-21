// Modulo generado automaticamente a partir de VDARTIC.DEF
//# M¢dulo : VDARTIC.DEF                                                        
//# Función: Generación automatica de rutinas C tabla VDARTIC
//#                        
//# Autor	 : EAA
//# Revisado por: 
//# Fecha  : 10-10-2007                                              
//#********************************************************************************
//# Histórico de cambios
//# ====================
//# =================================================================================
//#
//TABLE=ART
//
//PRIMARIA=CODART
//
//CLAVE=CODART,CODART
//
//RECORRE=CODEAN,CODEAN
//
//UPDATE=PESOCAJC,PESOCAJC
//UPDATE=INTERFASE, CODEAN,DESARTALT
//
//INTERFASE
//UPDATE
//INSERT
//DELETE

#include "vd.h"
#define SELARTCODART "SELECT VDARTIC.ROWID,VDARTIC.CODART,VDARTIC.CODDIV, "\
                    " VDARTIC.CODARTDIV,VDARTIC.CODNAC,VDARTIC.CODEAN, "\
                    " VDARTIC.DESART,VDARTIC.DESARTALT,VDARTIC.UNIEMB, "\
                    " VDARTIC.EMBCONT,VDARTIC.EMBPISO,VDARTIC.TIPOEMBADEF, "\
                    " VDARTIC.TIPOCONTEDEF,VDARTIC.UNIDADES,VDARTIC.UNIDADESHOST, "\
                    " VDARTIC.ORDENSAL,VDARTIC.TRAZABULTO,VDARTIC.DECIMALES, "\
                    " VDARTIC.TIPOVOL,VDARTIC.LARGOUNI,VDARTIC.ANCHOUNI, "\
                    " VDARTIC.ALTOUNI,VDARTIC.COEFUNI,VDARTIC.PESOUNI, "\
                    " VDARTIC.UNIPAQ,VDARTIC.LARGOPAQ,VDARTIC.ANCHOPAQ, "\
                    " VDARTIC.ALTOPAQ,VDARTIC.COEFPAQ,VDARTIC.PESOPAQ, "\
                    " VDARTIC.INVCONT,VDARTIC.PETINICAJA,VDARTIC.CONFPICKING, "\
                    " VDARTIC.FECVIGNP,VDARTIC.PVPVIGENTE,VDARTIC.PVPNUEVO, "\
                    " VDARTIC.PVPANTIGUO,VDARTIC.PVDVIGENTE,VDARTIC.PVDNUEVO, "\
                    " VDARTIC.PVDANTIGUO,VDARTIC.PVPIVAVIGENTE,VDARTIC.PVPIVANUEVO, "\
                    " VDARTIC.PVPIVAANTIGUO,VDARTIC.SWTTUMBABLE,VDARTIC.SWTANULADO, "\
                    " VDARTIC.SWTETIQ,VDARTIC.AGRUPALIN,VDARTIC.TPCVERIF, "\
                    " VDARTIC.SWTANALISIS,VDARTIC.SWTGENERICO,VDARTIC.SWTSTOCK, "\
                    " VDARTIC.SWTLOTE,VDARTIC.TRETEST,VDARTIC.UNIRETEST, "\
                    " VDARTIC.TAVISA,VDARTIC.UNIAVISA,VDARTIC.FORMATOLOTE, "\
                    " VDARTIC.MUESTROTECA,VDARTIC.NUMMUESTRAS,VDARTIC.TCADUC, "\
                    " VDARTIC.UNICADUC,VDARTIC.PEDMULTIPLO,VDARTIC.TIPOAJUSTE, "\
                    " VDARTIC.MINPENDIENTE,VDARTIC.MAXUNI,VDARTIC.MINPAL, "\
                    " VDARTIC.TIPOCAJC,VDARTIC.PESOCAJC,VDARTIC.LARGOCAJC, "\
                    " VDARTIC.ANCHOCAJC,VDARTIC.ALTOCAJC,VDARTIC.SWTPESACAJA, "\
                    " VDARTIC.TPCMARGENPESO,VDARTIC.MARGENPESOSUP,VDARTIC.MARGENPESOINF, "\
                    " VDARTIC.PICKINV,VDARTIC.SWTNUMEROSERIE,VDARTIC.SWTACTIVO, "\
                    " VDARTIC.TIPOVERIFCIEGA,VDARTIC.CODCOMEN,VDARTIC.CODOPEMODIF, "\
                    " VDARTIC.FECMODIF,VDARTIC.HORAMODIF,VDARTIC.CAJACUBETA, "\
                    " VDARTIC.MAXLONGNS,VDARTIC.MINLONGNS,VDARTIC.SWTHOST, "\
                    " VDARTIC.CUBETACAJA,VDARTIC.TIPOABC "\
        " FROM VDARTIC"\
        " WHERE "\
               " VDARTIC.CODART=:CODART "
static v10cursors *vdselartcodart;

#define SELARTCODEAN "SELECT VDARTIC.ROWID,VDARTIC.CODART,VDARTIC.CODDIV, "\
                    " VDARTIC.CODARTDIV,VDARTIC.CODNAC,VDARTIC.CODEAN, "\
                    " VDARTIC.DESART,VDARTIC.DESARTALT,VDARTIC.UNIEMB, "\
                    " VDARTIC.EMBCONT,VDARTIC.EMBPISO,VDARTIC.TIPOEMBADEF, "\
                    " VDARTIC.TIPOCONTEDEF,VDARTIC.UNIDADES,VDARTIC.UNIDADESHOST, "\
                    " VDARTIC.ORDENSAL,VDARTIC.TRAZABULTO,VDARTIC.DECIMALES, "\
                    " VDARTIC.TIPOVOL,VDARTIC.LARGOUNI,VDARTIC.ANCHOUNI, "\
                    " VDARTIC.ALTOUNI,VDARTIC.COEFUNI,VDARTIC.PESOUNI, "\
                    " VDARTIC.UNIPAQ,VDARTIC.LARGOPAQ,VDARTIC.ANCHOPAQ, "\
                    " VDARTIC.ALTOPAQ,VDARTIC.COEFPAQ,VDARTIC.PESOPAQ, "\
                    " VDARTIC.INVCONT,VDARTIC.PETINICAJA,VDARTIC.CONFPICKING, "\
                    " VDARTIC.FECVIGNP,VDARTIC.PVPVIGENTE,VDARTIC.PVPNUEVO, "\
                    " VDARTIC.PVPANTIGUO,VDARTIC.PVDVIGENTE,VDARTIC.PVDNUEVO, "\
                    " VDARTIC.PVDANTIGUO,VDARTIC.PVPIVAVIGENTE,VDARTIC.PVPIVANUEVO, "\
                    " VDARTIC.PVPIVAANTIGUO,VDARTIC.SWTTUMBABLE,VDARTIC.SWTANULADO, "\
                    " VDARTIC.SWTETIQ,VDARTIC.AGRUPALIN,VDARTIC.TPCVERIF, "\
                    " VDARTIC.SWTANALISIS,VDARTIC.SWTGENERICO,VDARTIC.SWTSTOCK, "\
                    " VDARTIC.SWTLOTE,VDARTIC.TRETEST,VDARTIC.UNIRETEST, "\
                    " VDARTIC.TAVISA,VDARTIC.UNIAVISA,VDARTIC.FORMATOLOTE, "\
                    " VDARTIC.MUESTROTECA,VDARTIC.NUMMUESTRAS,VDARTIC.TCADUC, "\
                    " VDARTIC.UNICADUC,VDARTIC.PEDMULTIPLO,VDARTIC.TIPOAJUSTE, "\
                    " VDARTIC.MINPENDIENTE,VDARTIC.MAXUNI,VDARTIC.MINPAL, "\
                    " VDARTIC.TIPOCAJC,VDARTIC.PESOCAJC,VDARTIC.LARGOCAJC, "\
                    " VDARTIC.ANCHOCAJC,VDARTIC.ALTOCAJC,VDARTIC.SWTPESACAJA, "\
                    " VDARTIC.TPCMARGENPESO,VDARTIC.MARGENPESOSUP,VDARTIC.MARGENPESOINF, "\
                    " VDARTIC.PICKINV,VDARTIC.SWTNUMEROSERIE,VDARTIC.SWTACTIVO, "\
                    " VDARTIC.TIPOVERIFCIEGA,VDARTIC.CODCOMEN,VDARTIC.CODOPEMODIF, "\
                    " VDARTIC.FECMODIF,VDARTIC.HORAMODIF,VDARTIC.CAJACUBETA, "\
                    " VDARTIC.MAXLONGNS,VDARTIC.MINLONGNS,VDARTIC.SWTHOST, "\
                    " VDARTIC.CUBETACAJA,VDARTIC.TIPOABC "\
        " FROM VDARTIC"\
        " WHERE "\
               " VDARTIC.CODEAN=:CODEAN "
static v10cursors *vdselartcodean;

#define SELARTVDARTIC "SELECT VDARTIC.ROWID,VDARTIC.CODART,VDARTIC.CODDIV, "\
                    " VDARTIC.CODARTDIV,VDARTIC.CODNAC,VDARTIC.CODEAN, "\
                    " VDARTIC.DESART,VDARTIC.DESARTALT,VDARTIC.UNIEMB, "\
                    " VDARTIC.EMBCONT,VDARTIC.EMBPISO,VDARTIC.TIPOEMBADEF, "\
                    " VDARTIC.TIPOCONTEDEF,VDARTIC.UNIDADES,VDARTIC.UNIDADESHOST, "\
                    " VDARTIC.ORDENSAL,VDARTIC.TRAZABULTO,VDARTIC.DECIMALES, "\
                    " VDARTIC.TIPOVOL,VDARTIC.LARGOUNI,VDARTIC.ANCHOUNI, "\
                    " VDARTIC.ALTOUNI,VDARTIC.COEFUNI,VDARTIC.PESOUNI, "\
                    " VDARTIC.UNIPAQ,VDARTIC.LARGOPAQ,VDARTIC.ANCHOPAQ, "\
                    " VDARTIC.ALTOPAQ,VDARTIC.COEFPAQ,VDARTIC.PESOPAQ, "\
                    " VDARTIC.INVCONT,VDARTIC.PETINICAJA,VDARTIC.CONFPICKING, "\
                    " VDARTIC.FECVIGNP,VDARTIC.PVPVIGENTE,VDARTIC.PVPNUEVO, "\
                    " VDARTIC.PVPANTIGUO,VDARTIC.PVDVIGENTE,VDARTIC.PVDNUEVO, "\
                    " VDARTIC.PVDANTIGUO,VDARTIC.PVPIVAVIGENTE,VDARTIC.PVPIVANUEVO, "\
                    " VDARTIC.PVPIVAANTIGUO,VDARTIC.SWTTUMBABLE,VDARTIC.SWTANULADO, "\
                    " VDARTIC.SWTETIQ,VDARTIC.AGRUPALIN,VDARTIC.TPCVERIF, "\
                    " VDARTIC.SWTANALISIS,VDARTIC.SWTGENERICO,VDARTIC.SWTSTOCK, "\
                    " VDARTIC.SWTLOTE,VDARTIC.TRETEST,VDARTIC.UNIRETEST, "\
                    " VDARTIC.TAVISA,VDARTIC.UNIAVISA,VDARTIC.FORMATOLOTE, "\
                    " VDARTIC.MUESTROTECA,VDARTIC.NUMMUESTRAS,VDARTIC.TCADUC, "\
                    " VDARTIC.UNICADUC,VDARTIC.PEDMULTIPLO,VDARTIC.TIPOAJUSTE, "\
                    " VDARTIC.MINPENDIENTE,VDARTIC.MAXUNI,VDARTIC.MINPAL, "\
                    " VDARTIC.TIPOCAJC,VDARTIC.PESOCAJC,VDARTIC.LARGOCAJC, "\
                    " VDARTIC.ANCHOCAJC,VDARTIC.ALTOCAJC,VDARTIC.SWTPESACAJA, "\
                    " VDARTIC.TPCMARGENPESO,VDARTIC.MARGENPESOSUP,VDARTIC.MARGENPESOINF, "\
                    " VDARTIC.PICKINV,VDARTIC.SWTNUMEROSERIE,VDARTIC.SWTACTIVO, "\
                    " VDARTIC.TIPOVERIFCIEGA,VDARTIC.CODCOMEN,VDARTIC.CODOPEMODIF, "\
                    " VDARTIC.FECMODIF,VDARTIC.HORAMODIF,VDARTIC.CAJACUBETA, "\
                    " VDARTIC.MAXLONGNS,VDARTIC.MINLONGNS,VDARTIC.SWTHOST, "\
                    " VDARTIC.CUBETACAJA,VDARTIC.TIPOABC "\
        " FROM VDARTIC"\
        " WHERE "\
               " VDARTIC.CODART=:CODART "
static v10cursors *vdselartvdartic;

#define UPDAARTPESOCAJC "UPDATE VDARTIC SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " PESOCAJC=:PESOCAJC  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaartpesocajc;

#define UPDAARTINTERFASE "UPDATE VDARTIC SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODEAN=:CODEAN , "\
               " DESARTALT=:DESARTALT  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaartinterfase;

#define UPDAART "UPDATE VDARTIC SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " CODDIV=:CODDIV , "\
               " CODARTDIV=:CODARTDIV , "\
               " CODNAC=:CODNAC , "\
               " CODEAN=:CODEAN , "\
               " DESART=:DESART , "\
               " DESARTALT=:DESARTALT , "\
               " UNIEMB=:UNIEMB , "\
               " EMBCONT=:EMBCONT , "\
               " EMBPISO=:EMBPISO , "\
               " TIPOEMBADEF=:TIPOEMBADEF , "\
               " TIPOCONTEDEF=:TIPOCONTEDEF , "\
               " UNIDADES=:UNIDADES , "\
               " UNIDADESHOST=:UNIDADESHOST , "\
               " ORDENSAL=:ORDENSAL , "\
               " TRAZABULTO=:TRAZABULTO , "\
               " DECIMALES=:DECIMALES , "\
               " TIPOVOL=:TIPOVOL , "\
               " LARGOUNI=:LARGOUNI , "\
               " ANCHOUNI=:ANCHOUNI , "\
               " ALTOUNI=:ALTOUNI , "\
               " COEFUNI=:COEFUNI , "\
               " PESOUNI=:PESOUNI , "\
               " UNIPAQ=:UNIPAQ , "\
               " LARGOPAQ=:LARGOPAQ , "\
               " ANCHOPAQ=:ANCHOPAQ , "\
               " ALTOPAQ=:ALTOPAQ , "\
               " COEFPAQ=:COEFPAQ , "\
               " PESOPAQ=:PESOPAQ , "\
               " INVCONT=:INVCONT , "\
               " PETINICAJA=:PETINICAJA , "\
               " CONFPICKING=:CONFPICKING , "\
               " FECVIGNP=:FECVIGNP , "\
               " PVPVIGENTE=:PVPVIGENTE , "\
               " PVPNUEVO=:PVPNUEVO , "\
               " PVPANTIGUO=:PVPANTIGUO , "\
               " PVDVIGENTE=:PVDVIGENTE , "\
               " PVDNUEVO=:PVDNUEVO , "\
               " PVDANTIGUO=:PVDANTIGUO , "\
               " PVPIVAVIGENTE=:PVPIVAVIGENTE , "\
               " PVPIVANUEVO=:PVPIVANUEVO , "\
               " PVPIVAANTIGUO=:PVPIVAANTIGUO , "\
               " SWTTUMBABLE=:SWTTUMBABLE , "\
               " SWTANULADO=:SWTANULADO , "\
               " SWTETIQ=:SWTETIQ , "\
               " AGRUPALIN=:AGRUPALIN , "\
               " TPCVERIF=:TPCVERIF , "\
               " SWTANALISIS=:SWTANALISIS , "\
               " SWTGENERICO=:SWTGENERICO , "\
               " SWTSTOCK=:SWTSTOCK , "\
               " SWTLOTE=:SWTLOTE , "\
               " TRETEST=:TRETEST , "\
               " UNIRETEST=:UNIRETEST , "\
               " TAVISA=:TAVISA , "\
               " UNIAVISA=:UNIAVISA , "\
               " FORMATOLOTE=:FORMATOLOTE , "\
               " MUESTROTECA=:MUESTROTECA , "\
               " NUMMUESTRAS=:NUMMUESTRAS , "\
               " TCADUC=:TCADUC , "\
               " UNICADUC=:UNICADUC , "\
               " PEDMULTIPLO=:PEDMULTIPLO , "\
               " TIPOAJUSTE=:TIPOAJUSTE , "\
               " MINPENDIENTE=:MINPENDIENTE , "\
               " MAXUNI=:MAXUNI , "\
               " MINPAL=:MINPAL , "\
               " TIPOCAJC=:TIPOCAJC , "\
               " PESOCAJC=:PESOCAJC , "\
               " LARGOCAJC=:LARGOCAJC , "\
               " ANCHOCAJC=:ANCHOCAJC , "\
               " ALTOCAJC=:ALTOCAJC , "\
               " SWTPESACAJA=:SWTPESACAJA , "\
               " TPCMARGENPESO=:TPCMARGENPESO , "\
               " MARGENPESOSUP=:MARGENPESOSUP , "\
               " MARGENPESOINF=:MARGENPESOINF , "\
               " PICKINV=:PICKINV , "\
               " SWTNUMEROSERIE=:SWTNUMEROSERIE , "\
               " SWTACTIVO=:SWTACTIVO , "\
               " TIPOVERIFCIEGA=:TIPOVERIFCIEGA , "\
               " CODCOMEN=:CODCOMEN , "\
               " CAJACUBETA=:CAJACUBETA , "\
               " MAXLONGNS=:MAXLONGNS , "\
               " MINLONGNS=:MINLONGNS , "\
               " SWTHOST=:SWTHOST , "\
               " CUBETACAJA=:CUBETACAJA , "\
               " TIPOABC=:TIPOABC  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdaartvdartic;

#define INSART "INSERT INTO VDARTIC (CODART,CODDIV,CODARTDIV,CODNAC,CODEAN,DESART, "\
                    " DESARTALT,UNIEMB,EMBCONT,EMBPISO,TIPOEMBADEF,TIPOCONTEDEF,UNIDADES, "\
                    " UNIDADESHOST,ORDENSAL,TRAZABULTO,DECIMALES,TIPOVOL,LARGOUNI,ANCHOUNI, "\
                    " ALTOUNI,COEFUNI,PESOUNI,UNIPAQ,LARGOPAQ,ANCHOPAQ,ALTOPAQ, "\
                    " COEFPAQ,PESOPAQ,INVCONT,PETINICAJA,CONFPICKING,FECVIGNP,PVPVIGENTE, "\
                    " PVPNUEVO,PVPANTIGUO,PVDVIGENTE,PVDNUEVO,PVDANTIGUO,PVPIVAVIGENTE,PVPIVANUEVO, "\
                    " PVPIVAANTIGUO,SWTTUMBABLE,SWTANULADO,SWTETIQ,AGRUPALIN,TPCVERIF,SWTANALISIS, "\
                    " SWTGENERICO,SWTSTOCK,SWTLOTE,TRETEST,UNIRETEST,TAVISA,UNIAVISA, "\
                    " FORMATOLOTE,MUESTROTECA,NUMMUESTRAS,TCADUC,UNICADUC,PEDMULTIPLO,TIPOAJUSTE, "\
                    " MINPENDIENTE,MAXUNI,MINPAL,TIPOCAJC,PESOCAJC,LARGOCAJC,ANCHOCAJC, "\
                    " ALTOCAJC,SWTPESACAJA,TPCMARGENPESO,MARGENPESOSUP,MARGENPESOINF,PICKINV,SWTNUMEROSERIE, "\
                    " SWTACTIVO,TIPOVERIFCIEGA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,CAJACUBETA, "\
                    " MAXLONGNS,MINLONGNS,SWTHOST,CUBETACAJA,TIPOABC "\
       " ) VALUES ( "\
                    " :CODART,:CODDIV,:CODARTDIV,:CODNAC,:CODEAN,:DESART, "\
                    " :DESARTALT,:UNIEMB,:EMBCONT,:EMBPISO,:TIPOEMBADEF,:TIPOCONTEDEF,:UNIDADES, "\
                    " :UNIDADESHOST,:ORDENSAL,:TRAZABULTO,:DECIMALES,:TIPOVOL,:LARGOUNI,:ANCHOUNI, "\
                    " :ALTOUNI,:COEFUNI,:PESOUNI,:UNIPAQ,:LARGOPAQ,:ANCHOPAQ,:ALTOPAQ, "\
                    " :COEFPAQ,:PESOPAQ,:INVCONT,:PETINICAJA,:CONFPICKING,:FECVIGNP,:PVPVIGENTE, "\
                    " :PVPNUEVO,:PVPANTIGUO,:PVDVIGENTE,:PVDNUEVO,:PVDANTIGUO,:PVPIVAVIGENTE,:PVPIVANUEVO, "\
                    " :PVPIVAANTIGUO,:SWTTUMBABLE,:SWTANULADO,:SWTETIQ,:AGRUPALIN,:TPCVERIF,:SWTANALISIS, "\
                    " :SWTGENERICO,:SWTSTOCK,:SWTLOTE,:TRETEST,:UNIRETEST,:TAVISA,:UNIAVISA, "\
                    " :FORMATOLOTE,:MUESTROTECA,:NUMMUESTRAS,:TCADUC,:UNICADUC,:PEDMULTIPLO,:TIPOAJUSTE, "\
                    " :MINPENDIENTE,:MAXUNI,:MINPAL,:TIPOCAJC,:PESOCAJC,:LARGOCAJC,:ANCHOCAJC, "\
                    " :ALTOCAJC,:SWTPESACAJA,:TPCMARGENPESO,:MARGENPESOSUP,:MARGENPESOINF,:PICKINV,:SWTNUMEROSERIE, "\
                    " :SWTACTIVO,:TIPOVERIFCIEGA,:CODCOMEN,VDUSER.GETUSER,VD.FECHASYS,VD.HORASYS,:CAJACUBETA, "\
                    " :MAXLONGNS,:MINLONGNS,:SWTHOST,:CUBETACAJA,:TIPOABC) "
static v10cursors *vdinsart;

#define DELART "DELETE VDARTIC WHERE ROWID=:MIROWID "
static v10cursors *vddelart;

static vdartics svdartic;

static diccols colvdartic[]={
	{"ROWID",V10CADENA,(size_t)&svdartic.rowid,sizeof(svdartic.rowid)},
	{"CODART",V10CADENA,(size_t)&svdartic.codart,sizeof(svdartic.codart)},
	{"CODDIV",V10CADENA,(size_t)&svdartic.coddiv,sizeof(svdartic.coddiv)},
	{"CODARTDIV",V10CADENA,(size_t)&svdartic.codartdiv,sizeof(svdartic.codartdiv)},
	{"CODNAC",V10CADENA,(size_t)&svdartic.codnac,sizeof(svdartic.codnac)},
	{"CODEAN",V10CADENA,(size_t)&svdartic.codean,sizeof(svdartic.codean)},
	{"DESART",V10CADENA,(size_t)&svdartic.desart,sizeof(svdartic.desart)},
	{"DESARTALT",V10CADENA,(size_t)&svdartic.desartalt,sizeof(svdartic.desartalt)},
	{"UNIEMB",V10DOUBLE,(size_t)&svdartic.uniemb,sizeof(svdartic.uniemb)},
	{"EMBCONT",V10LONG,(size_t)&svdartic.embcont,sizeof(svdartic.embcont)},
	{"EMBPISO",V10LONG,(size_t)&svdartic.embpiso,sizeof(svdartic.embpiso)},
	{"TIPOEMBADEF",V10CADENA,(size_t)&svdartic.tipoembadef,sizeof(svdartic.tipoembadef)},
	{"TIPOCONTEDEF",V10CADENA,(size_t)&svdartic.tipocontedef,sizeof(svdartic.tipocontedef)},
	{"UNIDADES",V10CADENA,(size_t)&svdartic.unidades,sizeof(svdartic.unidades)},
	{"UNIDADESHOST",V10CADENA,(size_t)&svdartic.unidadeshost,sizeof(svdartic.unidadeshost)},
	{"ORDENSAL",V10CADENA,(size_t)&svdartic.ordensal,sizeof(svdartic.ordensal)},
	{"TRAZABULTO",V10CADENA,(size_t)&svdartic.trazabulto,sizeof(svdartic.trazabulto)},
	{"DECIMALES",V10LONG,(size_t)&svdartic.decimales,sizeof(svdartic.decimales)},
	{"TIPOVOL",V10CADENA,(size_t)&svdartic.tipovol,sizeof(svdartic.tipovol)},
	{"LARGOUNI",V10DOUBLE,(size_t)&svdartic.largouni,sizeof(svdartic.largouni)},
	{"ANCHOUNI",V10DOUBLE,(size_t)&svdartic.anchouni,sizeof(svdartic.anchouni)},
	{"ALTOUNI",V10DOUBLE,(size_t)&svdartic.altouni,sizeof(svdartic.altouni)},
	{"COEFUNI",V10LONG,(size_t)&svdartic.coefuni,sizeof(svdartic.coefuni)},
	{"PESOUNI",V10DOUBLE,(size_t)&svdartic.pesouni,sizeof(svdartic.pesouni)},
	{"UNIPAQ",V10LONG,(size_t)&svdartic.unipaq,sizeof(svdartic.unipaq)},
	{"LARGOPAQ",V10LONG,(size_t)&svdartic.largopaq,sizeof(svdartic.largopaq)},
	{"ANCHOPAQ",V10LONG,(size_t)&svdartic.anchopaq,sizeof(svdartic.anchopaq)},
	{"ALTOPAQ",V10LONG,(size_t)&svdartic.altopaq,sizeof(svdartic.altopaq)},
	{"COEFPAQ",V10LONG,(size_t)&svdartic.coefpaq,sizeof(svdartic.coefpaq)},
	{"PESOPAQ",V10DOUBLE,(size_t)&svdartic.pesopaq,sizeof(svdartic.pesopaq)},
	{"INVCONT",V10CADENA,(size_t)&svdartic.invcont,sizeof(svdartic.invcont)},
	{"PETINICAJA",V10CADENA,(size_t)&svdartic.petinicaja,sizeof(svdartic.petinicaja)},
	{"CONFPICKING",V10CADENA,(size_t)&svdartic.confpicking,sizeof(svdartic.confpicking)},
	{"FECVIGNP",V10LONG,(size_t)&svdartic.fecvignp,sizeof(svdartic.fecvignp)},
	{"PVPVIGENTE",V10DOUBLE,(size_t)&svdartic.pvpvigente,sizeof(svdartic.pvpvigente)},
	{"PVPNUEVO",V10DOUBLE,(size_t)&svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo)},
	{"PVPANTIGUO",V10DOUBLE,(size_t)&svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo)},
	{"PVDVIGENTE",V10DOUBLE,(size_t)&svdartic.pvdvigente,sizeof(svdartic.pvdvigente)},
	{"PVDNUEVO",V10DOUBLE,(size_t)&svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo)},
	{"PVDANTIGUO",V10DOUBLE,(size_t)&svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo)},
	{"PVPIVAVIGENTE",V10DOUBLE,(size_t)&svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente)},
	{"PVPIVANUEVO",V10DOUBLE,(size_t)&svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo)},
	{"PVPIVAANTIGUO",V10DOUBLE,(size_t)&svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo)},
	{"SWTTUMBABLE",V10CADENA,(size_t)&svdartic.swttumbable,sizeof(svdartic.swttumbable)},
	{"SWTANULADO",V10CADENA,(size_t)&svdartic.swtanulado,sizeof(svdartic.swtanulado)},
	{"SWTETIQ",V10CADENA,(size_t)&svdartic.swtetiq,sizeof(svdartic.swtetiq)},
	{"AGRUPALIN",V10CADENA,(size_t)&svdartic.agrupalin,sizeof(svdartic.agrupalin)},
	{"TPCVERIF",V10LONG,(size_t)&svdartic.tpcverif,sizeof(svdartic.tpcverif)},
	{"SWTANALISIS",V10CADENA,(size_t)&svdartic.swtanalisis,sizeof(svdartic.swtanalisis)},
	{"SWTGENERICO",V10CADENA,(size_t)&svdartic.swtgenerico,sizeof(svdartic.swtgenerico)},
	{"SWTSTOCK",V10CADENA,(size_t)&svdartic.swtstock,sizeof(svdartic.swtstock)},
	{"SWTLOTE",V10CADENA,(size_t)&svdartic.swtlote,sizeof(svdartic.swtlote)},
	{"TRETEST",V10LONG,(size_t)&svdartic.tretest,sizeof(svdartic.tretest)},
	{"UNIRETEST",V10CADENA,(size_t)&svdartic.uniretest,sizeof(svdartic.uniretest)},
	{"TAVISA",V10LONG,(size_t)&svdartic.tavisa,sizeof(svdartic.tavisa)},
	{"UNIAVISA",V10CADENA,(size_t)&svdartic.uniavisa,sizeof(svdartic.uniavisa)},
	{"FORMATOLOTE",V10CADENA,(size_t)&svdartic.formatolote,sizeof(svdartic.formatolote)},
	{"MUESTROTECA",V10CADENA,(size_t)&svdartic.muestroteca,sizeof(svdartic.muestroteca)},
	{"NUMMUESTRAS",V10LONG,(size_t)&svdartic.nummuestras,sizeof(svdartic.nummuestras)},
	{"TCADUC",V10LONG,(size_t)&svdartic.tcaduc,sizeof(svdartic.tcaduc)},
	{"UNICADUC",V10CADENA,(size_t)&svdartic.unicaduc,sizeof(svdartic.unicaduc)},
	{"PEDMULTIPLO",V10LONG,(size_t)&svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo)},
	{"TIPOAJUSTE",V10CADENA,(size_t)&svdartic.tipoajuste,sizeof(svdartic.tipoajuste)},
	{"MINPENDIENTE",V10LONG,(size_t)&svdartic.minpendiente,sizeof(svdartic.minpendiente)},
	{"MAXUNI",V10LONG,(size_t)&svdartic.maxuni,sizeof(svdartic.maxuni)},
	{"MINPAL",V10LONG,(size_t)&svdartic.minpal,sizeof(svdartic.minpal)},
	{"TIPOCAJC",V10CADENA,(size_t)&svdartic.tipocajc,sizeof(svdartic.tipocajc)},
	{"PESOCAJC",V10LONG,(size_t)&svdartic.pesocajc,sizeof(svdartic.pesocajc)},
	{"LARGOCAJC",V10LONG,(size_t)&svdartic.largocajc,sizeof(svdartic.largocajc)},
	{"ANCHOCAJC",V10LONG,(size_t)&svdartic.anchocajc,sizeof(svdartic.anchocajc)},
	{"ALTOCAJC",V10LONG,(size_t)&svdartic.altocajc,sizeof(svdartic.altocajc)},
	{"SWTPESACAJA",V10CADENA,(size_t)&svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja)},
	{"TPCMARGENPESO",V10DOUBLE,(size_t)&svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso)},
	{"MARGENPESOSUP",V10LONG,(size_t)&svdartic.margenpesosup,sizeof(svdartic.margenpesosup)},
	{"MARGENPESOINF",V10LONG,(size_t)&svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf)},
	{"PICKINV",V10CADENA,(size_t)&svdartic.pickinv,sizeof(svdartic.pickinv)},
	{"SWTNUMEROSERIE",V10CADENA,(size_t)&svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie)},
	{"SWTACTIVO",V10CADENA,(size_t)&svdartic.swtactivo,sizeof(svdartic.swtactivo)},
	{"TIPOVERIFCIEGA",V10CADENA,(size_t)&svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega)},
	{"CODCOMEN",V10LONG,(size_t)&svdartic.codcomen,sizeof(svdartic.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdartic.codopemodif,sizeof(svdartic.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdartic.fecmodif,sizeof(svdartic.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdartic.horamodif,sizeof(svdartic.horamodif)},
	{"CAJACUBETA",V10LONG,(size_t)&svdartic.cajacubeta,sizeof(svdartic.cajacubeta)},
	{"MAXLONGNS",V10LONG,(size_t)&svdartic.maxlongns,sizeof(svdartic.maxlongns)},
	{"MINLONGNS",V10LONG,(size_t)&svdartic.minlongns,sizeof(svdartic.minlongns)},
	{"SWTHOST",V10CADENA,(size_t)&svdartic.swthost,sizeof(svdartic.swthost)},
	{"CUBETACAJA",V10LONG,(size_t)&svdartic.cubetacaja,sizeof(svdartic.cubetacaja)},
	{"TIPOABC",V10CADENA,(size_t)&svdartic.tipoabc,sizeof(svdartic.tipoabc)}
	};
static diccionarios dvdartic[]={
    {colvdartic,89}
};
diccionario dart={dvdartic,1};

static char msglogART[LCADENA];
static char msgdebugART[LCADENABIG];
static int init=0;


static void fin_vd_art(void)
{
if (vdselartcodart) {
    liberacursor(vdselartcodart);
    vdselartcodart = NULL;
}
if (vdselartcodean) {
    liberacursor(vdselartcodean);
    vdselartcodean = NULL;
}
if (vdselartvdartic) {
    liberacursor(vdselartvdartic);
    vdselartvdartic = NULL;
}
if (vdupdaartpesocajc) {
    liberacursor(vdupdaartpesocajc);
    vdupdaartpesocajc = NULL;
}
if (vdupdaartinterfase) {
    liberacursor(vdupdaartinterfase);
    vdupdaartinterfase = NULL;
}
if (vdupdaartvdartic) {
    liberacursor(vdupdaartvdartic);
    vdupdaartvdartic = NULL;
}
if (vdinsart != NULL) {
    liberacursor(vdinsart);
    vdinsart = NULL;
}
if (vddelart != NULL) {
    liberacursor(vddelart);
    vddelart = NULL;
}
}
static void init_selartcodart(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdselartcodart=abrecursordebug(SELARTCODART,1280);
    definetodo(vdselartcodart,svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          svdartic.coddiv,sizeof(svdartic.coddiv),V10CADENA,
                          svdartic.codartdiv,sizeof(svdartic.codartdiv),V10CADENA,
                          svdartic.codnac,sizeof(svdartic.codnac),V10CADENA,
                          svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          svdartic.desart,sizeof(svdartic.desart),V10CADENA,
                          svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          &svdartic.uniemb,sizeof(svdartic.uniemb),V10DOUBLE,
                          &svdartic.embcont,sizeof(svdartic.embcont),V10LONG,
                          &svdartic.embpiso,sizeof(svdartic.embpiso),V10LONG,
                          svdartic.tipoembadef,sizeof(svdartic.tipoembadef),V10CADENA,
                          svdartic.tipocontedef,sizeof(svdartic.tipocontedef),V10CADENA,
                          svdartic.unidades,sizeof(svdartic.unidades),V10CADENA,
                          svdartic.unidadeshost,sizeof(svdartic.unidadeshost),V10CADENA,
                          svdartic.ordensal,sizeof(svdartic.ordensal),V10CADENA,
                          svdartic.trazabulto,sizeof(svdartic.trazabulto),V10CADENA,
                          &svdartic.decimales,sizeof(svdartic.decimales),V10LONG,
                          svdartic.tipovol,sizeof(svdartic.tipovol),V10CADENA,
                          &svdartic.largouni,sizeof(svdartic.largouni),V10DOUBLE,
                          &svdartic.anchouni,sizeof(svdartic.anchouni),V10DOUBLE,
                          &svdartic.altouni,sizeof(svdartic.altouni),V10DOUBLE,
                          &svdartic.coefuni,sizeof(svdartic.coefuni),V10LONG,
                          &svdartic.pesouni,sizeof(svdartic.pesouni),V10DOUBLE,
                          &svdartic.unipaq,sizeof(svdartic.unipaq),V10LONG,
                          &svdartic.largopaq,sizeof(svdartic.largopaq),V10LONG,
                          &svdartic.anchopaq,sizeof(svdartic.anchopaq),V10LONG,
                          &svdartic.altopaq,sizeof(svdartic.altopaq),V10LONG,
                          &svdartic.coefpaq,sizeof(svdartic.coefpaq),V10LONG,
                          &svdartic.pesopaq,sizeof(svdartic.pesopaq),V10DOUBLE,
                          svdartic.invcont,sizeof(svdartic.invcont),V10CADENA,
                          svdartic.petinicaja,sizeof(svdartic.petinicaja),V10CADENA,
                          svdartic.confpicking,sizeof(svdartic.confpicking),V10CADENA,
                          &svdartic.fecvignp,sizeof(svdartic.fecvignp),V10LONG,
                          &svdartic.pvpvigente,sizeof(svdartic.pvpvigente),V10DOUBLE,
                          &svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo),V10DOUBLE,
                          &svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo),V10DOUBLE,
                          &svdartic.pvdvigente,sizeof(svdartic.pvdvigente),V10DOUBLE,
                          &svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo),V10DOUBLE,
                          &svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo),V10DOUBLE,
                          &svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente),V10DOUBLE,
                          &svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo),V10DOUBLE,
                          &svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo),V10DOUBLE,
                          svdartic.swttumbable,sizeof(svdartic.swttumbable),V10CADENA,
                          svdartic.swtanulado,sizeof(svdartic.swtanulado),V10CADENA,
                          svdartic.swtetiq,sizeof(svdartic.swtetiq),V10CADENA,
                          svdartic.agrupalin,sizeof(svdartic.agrupalin),V10CADENA,
                          &svdartic.tpcverif,sizeof(svdartic.tpcverif),V10LONG,
                          svdartic.swtanalisis,sizeof(svdartic.swtanalisis),V10CADENA,
                          svdartic.swtgenerico,sizeof(svdartic.swtgenerico),V10CADENA,
                          svdartic.swtstock,sizeof(svdartic.swtstock),V10CADENA,
                          svdartic.swtlote,sizeof(svdartic.swtlote),V10CADENA,
                          &svdartic.tretest,sizeof(svdartic.tretest),V10LONG,
                          svdartic.uniretest,sizeof(svdartic.uniretest),V10CADENA,
                          &svdartic.tavisa,sizeof(svdartic.tavisa),V10LONG,
                          svdartic.uniavisa,sizeof(svdartic.uniavisa),V10CADENA,
                          svdartic.formatolote,sizeof(svdartic.formatolote),V10CADENA,
                          svdartic.muestroteca,sizeof(svdartic.muestroteca),V10CADENA,
                          &svdartic.nummuestras,sizeof(svdartic.nummuestras),V10LONG,
                          &svdartic.tcaduc,sizeof(svdartic.tcaduc),V10LONG,
                          svdartic.unicaduc,sizeof(svdartic.unicaduc),V10CADENA,
                          &svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo),V10LONG,
                          svdartic.tipoajuste,sizeof(svdartic.tipoajuste),V10CADENA,
                          &svdartic.minpendiente,sizeof(svdartic.minpendiente),V10LONG,
                          &svdartic.maxuni,sizeof(svdartic.maxuni),V10LONG,
                          &svdartic.minpal,sizeof(svdartic.minpal),V10LONG,
                          svdartic.tipocajc,sizeof(svdartic.tipocajc),V10CADENA,
                          &svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          &svdartic.largocajc,sizeof(svdartic.largocajc),V10LONG,
                          &svdartic.anchocajc,sizeof(svdartic.anchocajc),V10LONG,
                          &svdartic.altocajc,sizeof(svdartic.altocajc),V10LONG,
                          svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja),V10CADENA,
                          &svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso),V10DOUBLE,
                          &svdartic.margenpesosup,sizeof(svdartic.margenpesosup),V10LONG,
                          &svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf),V10LONG,
                          svdartic.pickinv,sizeof(svdartic.pickinv),V10CADENA,
                          svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie),V10CADENA,
                          svdartic.swtactivo,sizeof(svdartic.swtactivo),V10CADENA,
                          svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega),V10CADENA,
                          &svdartic.codcomen,sizeof(svdartic.codcomen),V10LONG,
                          svdartic.codopemodif,sizeof(svdartic.codopemodif),V10CADENA,
                          &svdartic.fecmodif,sizeof(svdartic.fecmodif),V10LONG,
                          svdartic.horamodif,sizeof(svdartic.horamodif),V10CADENA,
                          &svdartic.cajacubeta,sizeof(svdartic.cajacubeta),V10LONG,
                          &svdartic.maxlongns,sizeof(svdartic.maxlongns),V10LONG,
                          &svdartic.minlongns,sizeof(svdartic.minlongns),V10LONG,
                          svdartic.swthost,sizeof(svdartic.swthost),V10CADENA,
                          &svdartic.cubetacaja,sizeof(svdartic.cubetacaja),V10LONG,
                          svdartic.tipoabc,sizeof(svdartic.tipoabc),V10CADENA,
                          NULL);
    bindtodo(vdselartcodart,"CODART",svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_selartcodean(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdselartcodean=abrecursordebug(SELARTCODEAN,1280);
    definetodo(vdselartcodean,svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          svdartic.coddiv,sizeof(svdartic.coddiv),V10CADENA,
                          svdartic.codartdiv,sizeof(svdartic.codartdiv),V10CADENA,
                          svdartic.codnac,sizeof(svdartic.codnac),V10CADENA,
                          svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          svdartic.desart,sizeof(svdartic.desart),V10CADENA,
                          svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          &svdartic.uniemb,sizeof(svdartic.uniemb),V10DOUBLE,
                          &svdartic.embcont,sizeof(svdartic.embcont),V10LONG,
                          &svdartic.embpiso,sizeof(svdartic.embpiso),V10LONG,
                          svdartic.tipoembadef,sizeof(svdartic.tipoembadef),V10CADENA,
                          svdartic.tipocontedef,sizeof(svdartic.tipocontedef),V10CADENA,
                          svdartic.unidades,sizeof(svdartic.unidades),V10CADENA,
                          svdartic.unidadeshost,sizeof(svdartic.unidadeshost),V10CADENA,
                          svdartic.ordensal,sizeof(svdartic.ordensal),V10CADENA,
                          svdartic.trazabulto,sizeof(svdartic.trazabulto),V10CADENA,
                          &svdartic.decimales,sizeof(svdartic.decimales),V10LONG,
                          svdartic.tipovol,sizeof(svdartic.tipovol),V10CADENA,
                          &svdartic.largouni,sizeof(svdartic.largouni),V10DOUBLE,
                          &svdartic.anchouni,sizeof(svdartic.anchouni),V10DOUBLE,
                          &svdartic.altouni,sizeof(svdartic.altouni),V10DOUBLE,
                          &svdartic.coefuni,sizeof(svdartic.coefuni),V10LONG,
                          &svdartic.pesouni,sizeof(svdartic.pesouni),V10DOUBLE,
                          &svdartic.unipaq,sizeof(svdartic.unipaq),V10LONG,
                          &svdartic.largopaq,sizeof(svdartic.largopaq),V10LONG,
                          &svdartic.anchopaq,sizeof(svdartic.anchopaq),V10LONG,
                          &svdartic.altopaq,sizeof(svdartic.altopaq),V10LONG,
                          &svdartic.coefpaq,sizeof(svdartic.coefpaq),V10LONG,
                          &svdartic.pesopaq,sizeof(svdartic.pesopaq),V10DOUBLE,
                          svdartic.invcont,sizeof(svdartic.invcont),V10CADENA,
                          svdartic.petinicaja,sizeof(svdartic.petinicaja),V10CADENA,
                          svdartic.confpicking,sizeof(svdartic.confpicking),V10CADENA,
                          &svdartic.fecvignp,sizeof(svdartic.fecvignp),V10LONG,
                          &svdartic.pvpvigente,sizeof(svdartic.pvpvigente),V10DOUBLE,
                          &svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo),V10DOUBLE,
                          &svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo),V10DOUBLE,
                          &svdartic.pvdvigente,sizeof(svdartic.pvdvigente),V10DOUBLE,
                          &svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo),V10DOUBLE,
                          &svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo),V10DOUBLE,
                          &svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente),V10DOUBLE,
                          &svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo),V10DOUBLE,
                          &svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo),V10DOUBLE,
                          svdartic.swttumbable,sizeof(svdartic.swttumbable),V10CADENA,
                          svdartic.swtanulado,sizeof(svdartic.swtanulado),V10CADENA,
                          svdartic.swtetiq,sizeof(svdartic.swtetiq),V10CADENA,
                          svdartic.agrupalin,sizeof(svdartic.agrupalin),V10CADENA,
                          &svdartic.tpcverif,sizeof(svdartic.tpcverif),V10LONG,
                          svdartic.swtanalisis,sizeof(svdartic.swtanalisis),V10CADENA,
                          svdartic.swtgenerico,sizeof(svdartic.swtgenerico),V10CADENA,
                          svdartic.swtstock,sizeof(svdartic.swtstock),V10CADENA,
                          svdartic.swtlote,sizeof(svdartic.swtlote),V10CADENA,
                          &svdartic.tretest,sizeof(svdartic.tretest),V10LONG,
                          svdartic.uniretest,sizeof(svdartic.uniretest),V10CADENA,
                          &svdartic.tavisa,sizeof(svdartic.tavisa),V10LONG,
                          svdartic.uniavisa,sizeof(svdartic.uniavisa),V10CADENA,
                          svdartic.formatolote,sizeof(svdartic.formatolote),V10CADENA,
                          svdartic.muestroteca,sizeof(svdartic.muestroteca),V10CADENA,
                          &svdartic.nummuestras,sizeof(svdartic.nummuestras),V10LONG,
                          &svdartic.tcaduc,sizeof(svdartic.tcaduc),V10LONG,
                          svdartic.unicaduc,sizeof(svdartic.unicaduc),V10CADENA,
                          &svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo),V10LONG,
                          svdartic.tipoajuste,sizeof(svdartic.tipoajuste),V10CADENA,
                          &svdartic.minpendiente,sizeof(svdartic.minpendiente),V10LONG,
                          &svdartic.maxuni,sizeof(svdartic.maxuni),V10LONG,
                          &svdartic.minpal,sizeof(svdartic.minpal),V10LONG,
                          svdartic.tipocajc,sizeof(svdartic.tipocajc),V10CADENA,
                          &svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          &svdartic.largocajc,sizeof(svdartic.largocajc),V10LONG,
                          &svdartic.anchocajc,sizeof(svdartic.anchocajc),V10LONG,
                          &svdartic.altocajc,sizeof(svdartic.altocajc),V10LONG,
                          svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja),V10CADENA,
                          &svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso),V10DOUBLE,
                          &svdartic.margenpesosup,sizeof(svdartic.margenpesosup),V10LONG,
                          &svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf),V10LONG,
                          svdartic.pickinv,sizeof(svdartic.pickinv),V10CADENA,
                          svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie),V10CADENA,
                          svdartic.swtactivo,sizeof(svdartic.swtactivo),V10CADENA,
                          svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega),V10CADENA,
                          &svdartic.codcomen,sizeof(svdartic.codcomen),V10LONG,
                          svdartic.codopemodif,sizeof(svdartic.codopemodif),V10CADENA,
                          &svdartic.fecmodif,sizeof(svdartic.fecmodif),V10LONG,
                          svdartic.horamodif,sizeof(svdartic.horamodif),V10CADENA,
                          &svdartic.cajacubeta,sizeof(svdartic.cajacubeta),V10LONG,
                          &svdartic.maxlongns,sizeof(svdartic.maxlongns),V10LONG,
                          &svdartic.minlongns,sizeof(svdartic.minlongns),V10LONG,
                          svdartic.swthost,sizeof(svdartic.swthost),V10CADENA,
                          &svdartic.cubetacaja,sizeof(svdartic.cubetacaja),V10LONG,
                          svdartic.tipoabc,sizeof(svdartic.tipoabc),V10CADENA,
                          NULL);
    bindtodo(vdselartcodean,"CODEAN",svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_selartvdartic(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdselartvdartic=abrecursordebug(SELARTVDARTIC,1280);
    definetodo(vdselartvdartic,svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          svdartic.coddiv,sizeof(svdartic.coddiv),V10CADENA,
                          svdartic.codartdiv,sizeof(svdartic.codartdiv),V10CADENA,
                          svdartic.codnac,sizeof(svdartic.codnac),V10CADENA,
                          svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          svdartic.desart,sizeof(svdartic.desart),V10CADENA,
                          svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          &svdartic.uniemb,sizeof(svdartic.uniemb),V10DOUBLE,
                          &svdartic.embcont,sizeof(svdartic.embcont),V10LONG,
                          &svdartic.embpiso,sizeof(svdartic.embpiso),V10LONG,
                          svdartic.tipoembadef,sizeof(svdartic.tipoembadef),V10CADENA,
                          svdartic.tipocontedef,sizeof(svdartic.tipocontedef),V10CADENA,
                          svdartic.unidades,sizeof(svdartic.unidades),V10CADENA,
                          svdartic.unidadeshost,sizeof(svdartic.unidadeshost),V10CADENA,
                          svdartic.ordensal,sizeof(svdartic.ordensal),V10CADENA,
                          svdartic.trazabulto,sizeof(svdartic.trazabulto),V10CADENA,
                          &svdartic.decimales,sizeof(svdartic.decimales),V10LONG,
                          svdartic.tipovol,sizeof(svdartic.tipovol),V10CADENA,
                          &svdartic.largouni,sizeof(svdartic.largouni),V10DOUBLE,
                          &svdartic.anchouni,sizeof(svdartic.anchouni),V10DOUBLE,
                          &svdartic.altouni,sizeof(svdartic.altouni),V10DOUBLE,
                          &svdartic.coefuni,sizeof(svdartic.coefuni),V10LONG,
                          &svdartic.pesouni,sizeof(svdartic.pesouni),V10DOUBLE,
                          &svdartic.unipaq,sizeof(svdartic.unipaq),V10LONG,
                          &svdartic.largopaq,sizeof(svdartic.largopaq),V10LONG,
                          &svdartic.anchopaq,sizeof(svdartic.anchopaq),V10LONG,
                          &svdartic.altopaq,sizeof(svdartic.altopaq),V10LONG,
                          &svdartic.coefpaq,sizeof(svdartic.coefpaq),V10LONG,
                          &svdartic.pesopaq,sizeof(svdartic.pesopaq),V10DOUBLE,
                          svdartic.invcont,sizeof(svdartic.invcont),V10CADENA,
                          svdartic.petinicaja,sizeof(svdartic.petinicaja),V10CADENA,
                          svdartic.confpicking,sizeof(svdartic.confpicking),V10CADENA,
                          &svdartic.fecvignp,sizeof(svdartic.fecvignp),V10LONG,
                          &svdartic.pvpvigente,sizeof(svdartic.pvpvigente),V10DOUBLE,
                          &svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo),V10DOUBLE,
                          &svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo),V10DOUBLE,
                          &svdartic.pvdvigente,sizeof(svdartic.pvdvigente),V10DOUBLE,
                          &svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo),V10DOUBLE,
                          &svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo),V10DOUBLE,
                          &svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente),V10DOUBLE,
                          &svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo),V10DOUBLE,
                          &svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo),V10DOUBLE,
                          svdartic.swttumbable,sizeof(svdartic.swttumbable),V10CADENA,
                          svdartic.swtanulado,sizeof(svdartic.swtanulado),V10CADENA,
                          svdartic.swtetiq,sizeof(svdartic.swtetiq),V10CADENA,
                          svdartic.agrupalin,sizeof(svdartic.agrupalin),V10CADENA,
                          &svdartic.tpcverif,sizeof(svdartic.tpcverif),V10LONG,
                          svdartic.swtanalisis,sizeof(svdartic.swtanalisis),V10CADENA,
                          svdartic.swtgenerico,sizeof(svdartic.swtgenerico),V10CADENA,
                          svdartic.swtstock,sizeof(svdartic.swtstock),V10CADENA,
                          svdartic.swtlote,sizeof(svdartic.swtlote),V10CADENA,
                          &svdartic.tretest,sizeof(svdartic.tretest),V10LONG,
                          svdartic.uniretest,sizeof(svdartic.uniretest),V10CADENA,
                          &svdartic.tavisa,sizeof(svdartic.tavisa),V10LONG,
                          svdartic.uniavisa,sizeof(svdartic.uniavisa),V10CADENA,
                          svdartic.formatolote,sizeof(svdartic.formatolote),V10CADENA,
                          svdartic.muestroteca,sizeof(svdartic.muestroteca),V10CADENA,
                          &svdartic.nummuestras,sizeof(svdartic.nummuestras),V10LONG,
                          &svdartic.tcaduc,sizeof(svdartic.tcaduc),V10LONG,
                          svdartic.unicaduc,sizeof(svdartic.unicaduc),V10CADENA,
                          &svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo),V10LONG,
                          svdartic.tipoajuste,sizeof(svdartic.tipoajuste),V10CADENA,
                          &svdartic.minpendiente,sizeof(svdartic.minpendiente),V10LONG,
                          &svdartic.maxuni,sizeof(svdartic.maxuni),V10LONG,
                          &svdartic.minpal,sizeof(svdartic.minpal),V10LONG,
                          svdartic.tipocajc,sizeof(svdartic.tipocajc),V10CADENA,
                          &svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          &svdartic.largocajc,sizeof(svdartic.largocajc),V10LONG,
                          &svdartic.anchocajc,sizeof(svdartic.anchocajc),V10LONG,
                          &svdartic.altocajc,sizeof(svdartic.altocajc),V10LONG,
                          svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja),V10CADENA,
                          &svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso),V10DOUBLE,
                          &svdartic.margenpesosup,sizeof(svdartic.margenpesosup),V10LONG,
                          &svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf),V10LONG,
                          svdartic.pickinv,sizeof(svdartic.pickinv),V10CADENA,
                          svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie),V10CADENA,
                          svdartic.swtactivo,sizeof(svdartic.swtactivo),V10CADENA,
                          svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega),V10CADENA,
                          &svdartic.codcomen,sizeof(svdartic.codcomen),V10LONG,
                          svdartic.codopemodif,sizeof(svdartic.codopemodif),V10CADENA,
                          &svdartic.fecmodif,sizeof(svdartic.fecmodif),V10LONG,
                          svdartic.horamodif,sizeof(svdartic.horamodif),V10CADENA,
                          &svdartic.cajacubeta,sizeof(svdartic.cajacubeta),V10LONG,
                          &svdartic.maxlongns,sizeof(svdartic.maxlongns),V10LONG,
                          &svdartic.minlongns,sizeof(svdartic.minlongns),V10LONG,
                          svdartic.swthost,sizeof(svdartic.swthost),V10CADENA,
                          &svdartic.cubetacaja,sizeof(svdartic.cubetacaja),V10LONG,
                          svdartic.tipoabc,sizeof(svdartic.tipoabc),V10CADENA,
                          NULL);
    bindtodo(vdselartvdartic,"CODART",svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_updaartpesocajc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdupdaartpesocajc=abrecursordebug(UPDAARTPESOCAJC,1280);
    bindtodo(vdupdaartpesocajc,"PESOCAJC",&svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          "MIROWID",svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_updaartinterfase(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdupdaartinterfase=abrecursordebug(UPDAARTINTERFASE,1280);
    bindtodo(vdupdaartinterfase,"CODEAN",svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          "DESARTALT",svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          "MIROWID",svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_updaartvdartic(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdupdaartvdartic=abrecursordebug(UPDAART,1280);
    bindtodo(vdupdaartvdartic,"CODDIV",svdartic.coddiv,sizeof(svdartic.coddiv),V10CADENA,
                          "CODARTDIV",svdartic.codartdiv,sizeof(svdartic.codartdiv),V10CADENA,
                          "CODNAC",svdartic.codnac,sizeof(svdartic.codnac),V10CADENA,
                          "CODEAN",svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          "DESART",svdartic.desart,sizeof(svdartic.desart),V10CADENA,
                          "DESARTALT",svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          "UNIEMB",&svdartic.uniemb,sizeof(svdartic.uniemb),V10DOUBLE,
                          "EMBCONT",&svdartic.embcont,sizeof(svdartic.embcont),V10LONG,
                          "EMBPISO",&svdartic.embpiso,sizeof(svdartic.embpiso),V10LONG,
                          "TIPOEMBADEF",svdartic.tipoembadef,sizeof(svdartic.tipoembadef),V10CADENA,
                          "TIPOCONTEDEF",svdartic.tipocontedef,sizeof(svdartic.tipocontedef),V10CADENA,
                          "UNIDADES",svdartic.unidades,sizeof(svdartic.unidades),V10CADENA,
                          "UNIDADESHOST",svdartic.unidadeshost,sizeof(svdartic.unidadeshost),V10CADENA,
                          "ORDENSAL",svdartic.ordensal,sizeof(svdartic.ordensal),V10CADENA,
                          "TRAZABULTO",svdartic.trazabulto,sizeof(svdartic.trazabulto),V10CADENA,
                          "DECIMALES",&svdartic.decimales,sizeof(svdartic.decimales),V10LONG,
                          "TIPOVOL",svdartic.tipovol,sizeof(svdartic.tipovol),V10CADENA,
                          "LARGOUNI",&svdartic.largouni,sizeof(svdartic.largouni),V10DOUBLE,
                          "ANCHOUNI",&svdartic.anchouni,sizeof(svdartic.anchouni),V10DOUBLE,
                          "ALTOUNI",&svdartic.altouni,sizeof(svdartic.altouni),V10DOUBLE,
                          "COEFUNI",&svdartic.coefuni,sizeof(svdartic.coefuni),V10LONG,
                          "PESOUNI",&svdartic.pesouni,sizeof(svdartic.pesouni),V10DOUBLE,
                          "UNIPAQ",&svdartic.unipaq,sizeof(svdartic.unipaq),V10LONG,
                          "LARGOPAQ",&svdartic.largopaq,sizeof(svdartic.largopaq),V10LONG,
                          "ANCHOPAQ",&svdartic.anchopaq,sizeof(svdartic.anchopaq),V10LONG,
                          "ALTOPAQ",&svdartic.altopaq,sizeof(svdartic.altopaq),V10LONG,
                          "COEFPAQ",&svdartic.coefpaq,sizeof(svdartic.coefpaq),V10LONG,
                          "PESOPAQ",&svdartic.pesopaq,sizeof(svdartic.pesopaq),V10DOUBLE,
                          "INVCONT",svdartic.invcont,sizeof(svdartic.invcont),V10CADENA,
                          "PETINICAJA",svdartic.petinicaja,sizeof(svdartic.petinicaja),V10CADENA,
                          "CONFPICKING",svdartic.confpicking,sizeof(svdartic.confpicking),V10CADENA,
                          "FECVIGNP",&svdartic.fecvignp,sizeof(svdartic.fecvignp),V10LONG,
                          "PVPVIGENTE",&svdartic.pvpvigente,sizeof(svdartic.pvpvigente),V10DOUBLE,
                          "PVPNUEVO",&svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo),V10DOUBLE,
                          "PVPANTIGUO",&svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo),V10DOUBLE,
                          "PVDVIGENTE",&svdartic.pvdvigente,sizeof(svdartic.pvdvigente),V10DOUBLE,
                          "PVDNUEVO",&svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo),V10DOUBLE,
                          "PVDANTIGUO",&svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo),V10DOUBLE,
                          "PVPIVAVIGENTE",&svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente),V10DOUBLE,
                          "PVPIVANUEVO",&svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo),V10DOUBLE,
                          "PVPIVAANTIGUO",&svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo),V10DOUBLE,
                          "SWTTUMBABLE",svdartic.swttumbable,sizeof(svdartic.swttumbable),V10CADENA,
                          "SWTANULADO",svdartic.swtanulado,sizeof(svdartic.swtanulado),V10CADENA,
                          "SWTETIQ",svdartic.swtetiq,sizeof(svdartic.swtetiq),V10CADENA,
                          "AGRUPALIN",svdartic.agrupalin,sizeof(svdartic.agrupalin),V10CADENA,
                          "TPCVERIF",&svdartic.tpcverif,sizeof(svdartic.tpcverif),V10LONG,
                          "SWTANALISIS",svdartic.swtanalisis,sizeof(svdartic.swtanalisis),V10CADENA,
                          "SWTGENERICO",svdartic.swtgenerico,sizeof(svdartic.swtgenerico),V10CADENA,
                          "SWTSTOCK",svdartic.swtstock,sizeof(svdartic.swtstock),V10CADENA,
                          "SWTLOTE",svdartic.swtlote,sizeof(svdartic.swtlote),V10CADENA,
                          "TRETEST",&svdartic.tretest,sizeof(svdartic.tretest),V10LONG,
                          "UNIRETEST",svdartic.uniretest,sizeof(svdartic.uniretest),V10CADENA,
                          "TAVISA",&svdartic.tavisa,sizeof(svdartic.tavisa),V10LONG,
                          "UNIAVISA",svdartic.uniavisa,sizeof(svdartic.uniavisa),V10CADENA,
                          "FORMATOLOTE",svdartic.formatolote,sizeof(svdartic.formatolote),V10CADENA,
                          "MUESTROTECA",svdartic.muestroteca,sizeof(svdartic.muestroteca),V10CADENA,
                          "NUMMUESTRAS",&svdartic.nummuestras,sizeof(svdartic.nummuestras),V10LONG,
                          "TCADUC",&svdartic.tcaduc,sizeof(svdartic.tcaduc),V10LONG,
                          "UNICADUC",svdartic.unicaduc,sizeof(svdartic.unicaduc),V10CADENA,
                          "PEDMULTIPLO",&svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo),V10LONG,
                          "TIPOAJUSTE",svdartic.tipoajuste,sizeof(svdartic.tipoajuste),V10CADENA,
                          "MINPENDIENTE",&svdartic.minpendiente,sizeof(svdartic.minpendiente),V10LONG,
                          "MAXUNI",&svdartic.maxuni,sizeof(svdartic.maxuni),V10LONG,
                          "MINPAL",&svdartic.minpal,sizeof(svdartic.minpal),V10LONG,
                          "TIPOCAJC",svdartic.tipocajc,sizeof(svdartic.tipocajc),V10CADENA,
                          "PESOCAJC",&svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          "LARGOCAJC",&svdartic.largocajc,sizeof(svdartic.largocajc),V10LONG,
                          "ANCHOCAJC",&svdartic.anchocajc,sizeof(svdartic.anchocajc),V10LONG,
                          "ALTOCAJC",&svdartic.altocajc,sizeof(svdartic.altocajc),V10LONG,
                          "SWTPESACAJA",svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja),V10CADENA,
                          "TPCMARGENPESO",&svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso),V10DOUBLE,
                          "MARGENPESOSUP",&svdartic.margenpesosup,sizeof(svdartic.margenpesosup),V10LONG,
                          "MARGENPESOINF",&svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf),V10LONG,
                          "PICKINV",svdartic.pickinv,sizeof(svdartic.pickinv),V10CADENA,
                          "SWTNUMEROSERIE",svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie),V10CADENA,
                          "SWTACTIVO",svdartic.swtactivo,sizeof(svdartic.swtactivo),V10CADENA,
                          "TIPOVERIFCIEGA",svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega),V10CADENA,
                          "CODCOMEN",&svdartic.codcomen,sizeof(svdartic.codcomen),V10LONG,
                          "CAJACUBETA",&svdartic.cajacubeta,sizeof(svdartic.cajacubeta),V10LONG,
                          "MAXLONGNS",&svdartic.maxlongns,sizeof(svdartic.maxlongns),V10LONG,
                          "MINLONGNS",&svdartic.minlongns,sizeof(svdartic.minlongns),V10LONG,
                          "SWTHOST",svdartic.swthost,sizeof(svdartic.swthost),V10CADENA,
                          "CUBETACAJA",&svdartic.cubetacaja,sizeof(svdartic.cubetacaja),V10LONG,
                          "TIPOABC",svdartic.tipoabc,sizeof(svdartic.tipoabc),V10CADENA,
                          "MIROWID",svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_insart(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vdinsart=abrecursordebug(INSART,1280);
    bindtodo(vdinsart,"CODART",svdartic.codart,sizeof(svdartic.codart),V10CADENA,
                          "CODDIV",svdartic.coddiv,sizeof(svdartic.coddiv),V10CADENA,
                          "CODARTDIV",svdartic.codartdiv,sizeof(svdartic.codartdiv),V10CADENA,
                          "CODNAC",svdartic.codnac,sizeof(svdartic.codnac),V10CADENA,
                          "CODEAN",svdartic.codean,sizeof(svdartic.codean),V10CADENA,
                          "DESART",svdartic.desart,sizeof(svdartic.desart),V10CADENA,
                          "DESARTALT",svdartic.desartalt,sizeof(svdartic.desartalt),V10CADENA,
                          "UNIEMB",&svdartic.uniemb,sizeof(svdartic.uniemb),V10DOUBLE,
                          "EMBCONT",&svdartic.embcont,sizeof(svdartic.embcont),V10LONG,
                          "EMBPISO",&svdartic.embpiso,sizeof(svdartic.embpiso),V10LONG,
                          "TIPOEMBADEF",svdartic.tipoembadef,sizeof(svdartic.tipoembadef),V10CADENA,
                          "TIPOCONTEDEF",svdartic.tipocontedef,sizeof(svdartic.tipocontedef),V10CADENA,
                          "UNIDADES",svdartic.unidades,sizeof(svdartic.unidades),V10CADENA,
                          "UNIDADESHOST",svdartic.unidadeshost,sizeof(svdartic.unidadeshost),V10CADENA,
                          "ORDENSAL",svdartic.ordensal,sizeof(svdartic.ordensal),V10CADENA,
                          "TRAZABULTO",svdartic.trazabulto,sizeof(svdartic.trazabulto),V10CADENA,
                          "DECIMALES",&svdartic.decimales,sizeof(svdartic.decimales),V10LONG,
                          "TIPOVOL",svdartic.tipovol,sizeof(svdartic.tipovol),V10CADENA,
                          "LARGOUNI",&svdartic.largouni,sizeof(svdartic.largouni),V10DOUBLE,
                          "ANCHOUNI",&svdartic.anchouni,sizeof(svdartic.anchouni),V10DOUBLE,
                          "ALTOUNI",&svdartic.altouni,sizeof(svdartic.altouni),V10DOUBLE,
                          "COEFUNI",&svdartic.coefuni,sizeof(svdartic.coefuni),V10LONG,
                          "PESOUNI",&svdartic.pesouni,sizeof(svdartic.pesouni),V10DOUBLE,
                          "UNIPAQ",&svdartic.unipaq,sizeof(svdartic.unipaq),V10LONG,
                          "LARGOPAQ",&svdartic.largopaq,sizeof(svdartic.largopaq),V10LONG,
                          "ANCHOPAQ",&svdartic.anchopaq,sizeof(svdartic.anchopaq),V10LONG,
                          "ALTOPAQ",&svdartic.altopaq,sizeof(svdartic.altopaq),V10LONG,
                          "COEFPAQ",&svdartic.coefpaq,sizeof(svdartic.coefpaq),V10LONG,
                          "PESOPAQ",&svdartic.pesopaq,sizeof(svdartic.pesopaq),V10DOUBLE,
                          "INVCONT",svdartic.invcont,sizeof(svdartic.invcont),V10CADENA,
                          "PETINICAJA",svdartic.petinicaja,sizeof(svdartic.petinicaja),V10CADENA,
                          "CONFPICKING",svdartic.confpicking,sizeof(svdartic.confpicking),V10CADENA,
                          "FECVIGNP",&svdartic.fecvignp,sizeof(svdartic.fecvignp),V10LONG,
                          "PVPVIGENTE",&svdartic.pvpvigente,sizeof(svdartic.pvpvigente),V10DOUBLE,
                          "PVPNUEVO",&svdartic.pvpnuevo,sizeof(svdartic.pvpnuevo),V10DOUBLE,
                          "PVPANTIGUO",&svdartic.pvpantiguo,sizeof(svdartic.pvpantiguo),V10DOUBLE,
                          "PVDVIGENTE",&svdartic.pvdvigente,sizeof(svdartic.pvdvigente),V10DOUBLE,
                          "PVDNUEVO",&svdartic.pvdnuevo,sizeof(svdartic.pvdnuevo),V10DOUBLE,
                          "PVDANTIGUO",&svdartic.pvdantiguo,sizeof(svdartic.pvdantiguo),V10DOUBLE,
                          "PVPIVAVIGENTE",&svdartic.pvpivavigente,sizeof(svdartic.pvpivavigente),V10DOUBLE,
                          "PVPIVANUEVO",&svdartic.pvpivanuevo,sizeof(svdartic.pvpivanuevo),V10DOUBLE,
                          "PVPIVAANTIGUO",&svdartic.pvpivaantiguo,sizeof(svdartic.pvpivaantiguo),V10DOUBLE,
                          "SWTTUMBABLE",svdartic.swttumbable,sizeof(svdartic.swttumbable),V10CADENA,
                          "SWTANULADO",svdartic.swtanulado,sizeof(svdartic.swtanulado),V10CADENA,
                          "SWTETIQ",svdartic.swtetiq,sizeof(svdartic.swtetiq),V10CADENA,
                          "AGRUPALIN",svdartic.agrupalin,sizeof(svdartic.agrupalin),V10CADENA,
                          "TPCVERIF",&svdartic.tpcverif,sizeof(svdartic.tpcverif),V10LONG,
                          "SWTANALISIS",svdartic.swtanalisis,sizeof(svdartic.swtanalisis),V10CADENA,
                          "SWTGENERICO",svdartic.swtgenerico,sizeof(svdartic.swtgenerico),V10CADENA,
                          "SWTSTOCK",svdartic.swtstock,sizeof(svdartic.swtstock),V10CADENA,
                          "SWTLOTE",svdartic.swtlote,sizeof(svdartic.swtlote),V10CADENA,
                          "TRETEST",&svdartic.tretest,sizeof(svdartic.tretest),V10LONG,
                          "UNIRETEST",svdartic.uniretest,sizeof(svdartic.uniretest),V10CADENA,
                          "TAVISA",&svdartic.tavisa,sizeof(svdartic.tavisa),V10LONG,
                          "UNIAVISA",svdartic.uniavisa,sizeof(svdartic.uniavisa),V10CADENA,
                          "FORMATOLOTE",svdartic.formatolote,sizeof(svdartic.formatolote),V10CADENA,
                          "MUESTROTECA",svdartic.muestroteca,sizeof(svdartic.muestroteca),V10CADENA,
                          "NUMMUESTRAS",&svdartic.nummuestras,sizeof(svdartic.nummuestras),V10LONG,
                          "TCADUC",&svdartic.tcaduc,sizeof(svdartic.tcaduc),V10LONG,
                          "UNICADUC",svdartic.unicaduc,sizeof(svdartic.unicaduc),V10CADENA,
                          "PEDMULTIPLO",&svdartic.pedmultiplo,sizeof(svdartic.pedmultiplo),V10LONG,
                          "TIPOAJUSTE",svdartic.tipoajuste,sizeof(svdartic.tipoajuste),V10CADENA,
                          "MINPENDIENTE",&svdartic.minpendiente,sizeof(svdartic.minpendiente),V10LONG,
                          "MAXUNI",&svdartic.maxuni,sizeof(svdartic.maxuni),V10LONG,
                          "MINPAL",&svdartic.minpal,sizeof(svdartic.minpal),V10LONG,
                          "TIPOCAJC",svdartic.tipocajc,sizeof(svdartic.tipocajc),V10CADENA,
                          "PESOCAJC",&svdartic.pesocajc,sizeof(svdartic.pesocajc),V10LONG,
                          "LARGOCAJC",&svdartic.largocajc,sizeof(svdartic.largocajc),V10LONG,
                          "ANCHOCAJC",&svdartic.anchocajc,sizeof(svdartic.anchocajc),V10LONG,
                          "ALTOCAJC",&svdartic.altocajc,sizeof(svdartic.altocajc),V10LONG,
                          "SWTPESACAJA",svdartic.swtpesacaja,sizeof(svdartic.swtpesacaja),V10CADENA,
                          "TPCMARGENPESO",&svdartic.tpcmargenpeso,sizeof(svdartic.tpcmargenpeso),V10DOUBLE,
                          "MARGENPESOSUP",&svdartic.margenpesosup,sizeof(svdartic.margenpesosup),V10LONG,
                          "MARGENPESOINF",&svdartic.margenpesoinf,sizeof(svdartic.margenpesoinf),V10LONG,
                          "PICKINV",svdartic.pickinv,sizeof(svdartic.pickinv),V10CADENA,
                          "SWTNUMEROSERIE",svdartic.swtnumeroserie,sizeof(svdartic.swtnumeroserie),V10CADENA,
                          "SWTACTIVO",svdartic.swtactivo,sizeof(svdartic.swtactivo),V10CADENA,
                          "TIPOVERIFCIEGA",svdartic.tipoverifciega,sizeof(svdartic.tipoverifciega),V10CADENA,
                          "CODCOMEN",&svdartic.codcomen,sizeof(svdartic.codcomen),V10LONG,
                          "CAJACUBETA",&svdartic.cajacubeta,sizeof(svdartic.cajacubeta),V10LONG,
                          "MAXLONGNS",&svdartic.maxlongns,sizeof(svdartic.maxlongns),V10LONG,
                          "MINLONGNS",&svdartic.minlongns,sizeof(svdartic.minlongns),V10LONG,
                          "SWTHOST",svdartic.swthost,sizeof(svdartic.swthost),V10CADENA,
                          "CUBETACAJA",&svdartic.cubetacaja,sizeof(svdartic.cubetacaja),V10LONG,
                          "TIPOABC",svdartic.tipoabc,sizeof(svdartic.tipoabc),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

static void init_delart(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdartic[0].numcol;nc++) dvdartic[0].c[nc].offset-=(size_t)&svdartic;
    vddelart=abrecursordebug(DELART,1280);
    bindtodo(vddelart,"MIROWID",svdartic.rowid,sizeof(svdartic.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_art);
        init = 1;
    }
}

diccionario *ARTdamediccionario(void)
{
     return(&dart);
}

int ARTselcodart(char *codart,vdartics *art)
{
  int vdret;
  if (vdselartcodart==NULL) init_selartcodart();
  memset(&svdartic,0,sizeof(svdartic));
  strcpy(svdartic.codart,codart);
  vdret=ejefetchcursor(vdselartcodart);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselartcodart. vdret %d. \n",ARTlog(&svdartic),vdret);
    return(VD_EERRORACLE);
   }
  *art=svdartic;
  return(vdret);
}

int ARTbuscacodean(char *codean,vdartics *art)
{
  int vdret;
  memset(&svdartic,0,sizeof(svdartic));
  strcpy(svdartic.codean,codean);
  if (vdselartcodean==NULL) init_selartcodean();
  vdret=ejefetchcursor(vdselartcodean);
  if (vdret==0) {
     *art=svdartic;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselartcodean. vdret %d. \n",ARTlog(&svdartic),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int ARTnextcodean(vdartics *art)
{
  int vdret;
  vdret=fetchcursor(vdselartcodean);
  if (vdret==0) {
     *art=svdartic;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselartcodean. vdret %d. \n",ARTlog(&svdartic),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselartcodean);
  return(VD_EERRORACLE);
}

int ARTselvdartic(char *codart,vdartics *art)
{
  int vdret;
  if (vdselartvdartic==NULL) init_selartvdartic();
  memset(&svdartic,0,sizeof(svdartic));
  strcpy(svdartic.codart,codart);
  vdret=ejefetchcursor(vdselartvdartic);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselartvdartic. vdret %d. \n",ARTlog(&svdartic),vdret);
    return(VD_EERRORACLE);
   }
  *art=svdartic;
  return(vdret);
}

int ARTactualizapesocajc(vdartics *art,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ARTactualizapesocajc:  %s .  \n",ARTlog(&svdartic));
  if (vdupdaartpesocajc==NULL) init_updaartpesocajc();
  svdartic=*art;
  vdret=ejecutacursor(vdupdaartpesocajc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaartpesocajc);
     getcurerrornombre(vdupdaartpesocajc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaartpesocajc)!=1) return(VD_EERRORACLE);
  return(0);
}

int ARTactualizainterfase(vdartics *art,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ARTactualizainterfase:  %s .  \n",ARTlog(&svdartic));
  if (vdupdaartinterfase==NULL) init_updaartinterfase();
  svdartic=*art;
  vdret=ejecutacursor(vdupdaartinterfase);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaartinterfase);
     getcurerrornombre(vdupdaartinterfase->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaartinterfase)!=1) return(VD_EERRORACLE);
  return(0);
}

int ARTactualizavdartic(vdartics *art,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando ARTactualizavdartic:  %s .  \n",ARTlog(&svdartic));
  if (vdupdaartvdartic==NULL) init_updaartvdartic();
  svdartic=*art;
  vdret=ejecutacursor(vdupdaartvdartic);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdaartvdartic);
     getcurerrornombre(vdupdaartvdartic->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdaartvdartic)!=1) return(VD_EERRORACLE);
  return(0);
}

int ARTinsert(vdartics *art,int error)
{
  int vdret;
  if (!vdinsart) init_insart();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",ARTlog(&svdartic));
  svdartic=*art;
  vdret=ejecutacursor(vdinsart);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsart);
     getcurerrornombre(vdinsart->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ARTdel(vdartics *art,int error)
{
  int vdret;
  svdartic=*art;
  if (vddelart==NULL) init_delart();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",ARTlog(&svdartic));
  vdret=ejecutacursor(vddelart);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelart);
     getcurerrornombre(vddelart->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int ARTinter(vdartics *art)
{
  int vdret = 0;
  if (vdselartvdartic==NULL) init_selartvdartic();
  memset(&svdartic,0,sizeof(svdartic));
  strcpy(svdartic.codart,art->codart);
  vdret=ejefetchcursor(vdselartvdartic);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselartvdartic. vdret %d. \n",ARTlog(&svdartic),vdret);
    return(VD_EERRORACLE);
  }

  *art=svdartic;
  return(vdret);
}

char * ARTlog(vdartics *art)
{
    sprintf(msglogART, "VDARTIC: codart %s ",art->codart);
    return(msglogART);
}

char * ARTdebug(vdartics *art)
{
    debugestruct(&dart,art,msgdebugART);
    return(msgdebugART);
}

