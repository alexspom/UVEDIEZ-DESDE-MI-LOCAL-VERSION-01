// Modulo generado automaticamente a partir de VDBULTOCAB.DEF
//#***
//# VDBULCAB.DEF - Generaci�n autom�tica del c�digo c para la tabla de Cabecera de Bulto                                                       
//# 
//# Prop�sito: Funciones de acceso a la tabla VDBULCAB
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 12-03-2008
//#************************************************************************************
//# Modificaciones
//#***
//TABLE=BUC
//
//RECORRE=STATUS,STATUS;
//
//RECORRE=BULTOSDEUNPEDIDO,CODDIV,ANOPED,CODPED,SEQPED;
//RECORRE=BULTOSTIPOYVOLU,CODDIV,ANOPED,CODPED,SEQPED,TIPOBULTO,TIPOVOL;ORDERBY=CODPED,CODDIV,SEQPED,ANOPED,NBULTO;
//CLAVE=DISPLAYSTATUS,IDINFOPICK,NUMDISP,STATUS
//
//UPDATE=LLEVAALBARAN,SWTLLEVAALB;
//UPDATE=VERIFICAR,SWTVERIFFORZADA;
//UPDATE=CODBULTO,CODBULTO;
//UPDATE=STATUS,STATUS;
//UPDATE=VOLUMENYPESO,VOLUMEN,PESOTEORICO
//UPDATE=STATUSYPESO,STATUS,PESOTEORICO,PESOREAL
//UPDATE=PESOREAL,PESOREAL
//UPDATE=NUMRECIRCULAPREP,NUMRECIRCULAPREP
//UPDATE=NUMRECIRCULAVERIF,NUMRECIRCULAVERIF
//UPDATE=SCANNER,ULTSCAN,FECULTSCAN,HORAULTSCAN
//UPDATE=IMPRESION,CODOPEIMPRIME,FECIMPRIME,HORAIMPRIME
//
//LOCK
//INSERT 
//DELETE

#include "vdpedidos.h"
#define SELBUCSTATUS "SELECT VDBULTOCAB.ROWID,VDBULTOCAB.CODBULTO,VDBULTOCAB.CODDIV, "\
                    " VDBULTOCAB.ANOPED,VDBULTOCAB.CODPED,VDBULTOCAB.SEQPED, "\
                    " VDBULTOCAB.NBULTO,VDBULTOCAB.TIPOBULTO,VDBULTOCAB.TIPOVOL, "\
                    " VDBULTOCAB.TIPOCAJA,VDBULTOCAB.SWTANULAR,VDBULTOCAB.SWTLLEVAALB, "\
                    " VDBULTOCAB.SWTVERIFFORZADA,VDBULTOCAB.CNTSSCC,VDBULTOCAB.MATCAJA, "\
                    " VDBULTOCAB.SERIERECOGIDA,VDBULTOCAB.TRACKINGAGE,VDBULTOCAB.IDINFOPICK, "\
                    " VDBULTOCAB.NUMDISP,VDBULTOCAB.PESOTEORICO,VDBULTOCAB.PESOREAL, "\
                    " VDBULTOCAB.VOLUMEN,VDBULTOCAB.ULTSCAN,VDBULTOCAB.FECULTSCAN, "\
                    " VDBULTOCAB.HORAULTSCAN,VDBULTOCAB.NUMRECIRCULAPREP,VDBULTOCAB.NUMRECIRCULAVERIF, "\
                    " VDBULTOCAB.FECCREADO,VDBULTOCAB.HORACREADO,VDBULTOCAB.CODOPEIMPRIME, "\
                    " VDBULTOCAB.FECIMPRIME,VDBULTOCAB.HORAIMPRIME,VDBULTOCAB.CODOPEVERIFICA, "\
                    " VDBULTOCAB.FECVERIFICA,VDBULTOCAB.HORAVERIFICA,VDBULTOCAB.FECFINALIZA, "\
                    " VDBULTOCAB.HORAFINALIZA,VDBULTOCAB.STATUS,VDBULTOCAB.VDEXTRA, "\
                    " VDBULTOCAB.CODCOMEN,VDBULTOCAB.CODOPEMODIF,VDBULTOCAB.FECMODIF, "\
                    " VDBULTOCAB.HORAMODIF,VDBULTOCAB.PEDIDOHOST,VDBULTOCAB.CODRECURSO, "\
                    " VDBULTOCAB.FECETIQ,VDBULTOCAB.HORAETIQ,VDBULTOCAB.FECFINPICK, "\
                    " VDBULTOCAB.HORAFINPICK,VDBULTOCAB.ZONASSGT,VDBULTOCAB.TARA, "\
                    " VDBULTOCAB.CODMOVTERMOGRAFO,VDBULTOCAB.CODOPETERMOGRAFO,VDBULTOCAB.FECTERMOGRAFO, "\
                    " VDBULTOCAB.HORATERMOGRAFO,VDBULTOCAB.SERIETERMOGRAFO,VDBULTOCAB.TERMOGRAFO "\
        " FROM VDBULTOCAB"\
        " WHERE "\
               " VDBULTOCAB.STATUS=:STATUS "
static v10cursors *vdselbucstatus;

#define SELBUCBULTOSDEUNPEDIDO "SELECT VDBULTOCAB.ROWID,VDBULTOCAB.CODBULTO,VDBULTOCAB.CODDIV, "\
                    " VDBULTOCAB.ANOPED,VDBULTOCAB.CODPED,VDBULTOCAB.SEQPED, "\
                    " VDBULTOCAB.NBULTO,VDBULTOCAB.TIPOBULTO,VDBULTOCAB.TIPOVOL, "\
                    " VDBULTOCAB.TIPOCAJA,VDBULTOCAB.SWTANULAR,VDBULTOCAB.SWTLLEVAALB, "\
                    " VDBULTOCAB.SWTVERIFFORZADA,VDBULTOCAB.CNTSSCC,VDBULTOCAB.MATCAJA, "\
                    " VDBULTOCAB.SERIERECOGIDA,VDBULTOCAB.TRACKINGAGE,VDBULTOCAB.IDINFOPICK, "\
                    " VDBULTOCAB.NUMDISP,VDBULTOCAB.PESOTEORICO,VDBULTOCAB.PESOREAL, "\
                    " VDBULTOCAB.VOLUMEN,VDBULTOCAB.ULTSCAN,VDBULTOCAB.FECULTSCAN, "\
                    " VDBULTOCAB.HORAULTSCAN,VDBULTOCAB.NUMRECIRCULAPREP,VDBULTOCAB.NUMRECIRCULAVERIF, "\
                    " VDBULTOCAB.FECCREADO,VDBULTOCAB.HORACREADO,VDBULTOCAB.CODOPEIMPRIME, "\
                    " VDBULTOCAB.FECIMPRIME,VDBULTOCAB.HORAIMPRIME,VDBULTOCAB.CODOPEVERIFICA, "\
                    " VDBULTOCAB.FECVERIFICA,VDBULTOCAB.HORAVERIFICA,VDBULTOCAB.FECFINALIZA, "\
                    " VDBULTOCAB.HORAFINALIZA,VDBULTOCAB.STATUS,VDBULTOCAB.VDEXTRA, "\
                    " VDBULTOCAB.CODCOMEN,VDBULTOCAB.CODOPEMODIF,VDBULTOCAB.FECMODIF, "\
                    " VDBULTOCAB.HORAMODIF,VDBULTOCAB.PEDIDOHOST,VDBULTOCAB.CODRECURSO, "\
                    " VDBULTOCAB.FECETIQ,VDBULTOCAB.HORAETIQ,VDBULTOCAB.FECFINPICK, "\
                    " VDBULTOCAB.HORAFINPICK,VDBULTOCAB.ZONASSGT,VDBULTOCAB.TARA, "\
                    " VDBULTOCAB.CODMOVTERMOGRAFO,VDBULTOCAB.CODOPETERMOGRAFO,VDBULTOCAB.FECTERMOGRAFO, "\
                    " VDBULTOCAB.HORATERMOGRAFO,VDBULTOCAB.SERIETERMOGRAFO,VDBULTOCAB.TERMOGRAFO "\
        " FROM VDBULTOCAB"\
        " WHERE "\
               " VDBULTOCAB.CODDIV=:CODDIV "\
               " AND VDBULTOCAB.ANOPED=:ANOPED "\
               " AND VDBULTOCAB.CODPED=:CODPED "\
               " AND VDBULTOCAB.SEQPED=:SEQPED "
static v10cursors *vdselbucbultosdeunpedido;

#define SELBUCBULTOSTIPOYVOLU "SELECT VDBULTOCAB.ROWID,VDBULTOCAB.CODBULTO,VDBULTOCAB.CODDIV, "\
                    " VDBULTOCAB.ANOPED,VDBULTOCAB.CODPED,VDBULTOCAB.SEQPED, "\
                    " VDBULTOCAB.NBULTO,VDBULTOCAB.TIPOBULTO,VDBULTOCAB.TIPOVOL, "\
                    " VDBULTOCAB.TIPOCAJA,VDBULTOCAB.SWTANULAR,VDBULTOCAB.SWTLLEVAALB, "\
                    " VDBULTOCAB.SWTVERIFFORZADA,VDBULTOCAB.CNTSSCC,VDBULTOCAB.MATCAJA, "\
                    " VDBULTOCAB.SERIERECOGIDA,VDBULTOCAB.TRACKINGAGE,VDBULTOCAB.IDINFOPICK, "\
                    " VDBULTOCAB.NUMDISP,VDBULTOCAB.PESOTEORICO,VDBULTOCAB.PESOREAL, "\
                    " VDBULTOCAB.VOLUMEN,VDBULTOCAB.ULTSCAN,VDBULTOCAB.FECULTSCAN, "\
                    " VDBULTOCAB.HORAULTSCAN,VDBULTOCAB.NUMRECIRCULAPREP,VDBULTOCAB.NUMRECIRCULAVERIF, "\
                    " VDBULTOCAB.FECCREADO,VDBULTOCAB.HORACREADO,VDBULTOCAB.CODOPEIMPRIME, "\
                    " VDBULTOCAB.FECIMPRIME,VDBULTOCAB.HORAIMPRIME,VDBULTOCAB.CODOPEVERIFICA, "\
                    " VDBULTOCAB.FECVERIFICA,VDBULTOCAB.HORAVERIFICA,VDBULTOCAB.FECFINALIZA, "\
                    " VDBULTOCAB.HORAFINALIZA,VDBULTOCAB.STATUS,VDBULTOCAB.VDEXTRA, "\
                    " VDBULTOCAB.CODCOMEN,VDBULTOCAB.CODOPEMODIF,VDBULTOCAB.FECMODIF, "\
                    " VDBULTOCAB.HORAMODIF,VDBULTOCAB.PEDIDOHOST,VDBULTOCAB.CODRECURSO, "\
                    " VDBULTOCAB.FECETIQ,VDBULTOCAB.HORAETIQ,VDBULTOCAB.FECFINPICK, "\
                    " VDBULTOCAB.HORAFINPICK,VDBULTOCAB.ZONASSGT,VDBULTOCAB.TARA, "\
                    " VDBULTOCAB.CODMOVTERMOGRAFO,VDBULTOCAB.CODOPETERMOGRAFO,VDBULTOCAB.FECTERMOGRAFO, "\
                    " VDBULTOCAB.HORATERMOGRAFO,VDBULTOCAB.SERIETERMOGRAFO,VDBULTOCAB.TERMOGRAFO "\
        " FROM VDBULTOCAB"\
        " WHERE "\
               " VDBULTOCAB.CODDIV=:CODDIV "\
               " AND VDBULTOCAB.ANOPED=:ANOPED "\
               " AND VDBULTOCAB.CODPED=:CODPED "\
               " AND VDBULTOCAB.SEQPED=:SEQPED "\
               " AND VDBULTOCAB.TIPOBULTO=:TIPOBULTO "\
               " AND VDBULTOCAB.TIPOVOL=:TIPOVOL "\
        " ORDER BY CODPED,CODDIV,SEQPED,ANOPED,NBULTO "
static v10cursors *vdselbucbultostipoyvolu;

#define SELBUCDISPLAYSTATUS "SELECT VDBULTOCAB.ROWID,VDBULTOCAB.CODBULTO,VDBULTOCAB.CODDIV, "\
                    " VDBULTOCAB.ANOPED,VDBULTOCAB.CODPED,VDBULTOCAB.SEQPED, "\
                    " VDBULTOCAB.NBULTO,VDBULTOCAB.TIPOBULTO,VDBULTOCAB.TIPOVOL, "\
                    " VDBULTOCAB.TIPOCAJA,VDBULTOCAB.SWTANULAR,VDBULTOCAB.SWTLLEVAALB, "\
                    " VDBULTOCAB.SWTVERIFFORZADA,VDBULTOCAB.CNTSSCC,VDBULTOCAB.MATCAJA, "\
                    " VDBULTOCAB.SERIERECOGIDA,VDBULTOCAB.TRACKINGAGE,VDBULTOCAB.IDINFOPICK, "\
                    " VDBULTOCAB.NUMDISP,VDBULTOCAB.PESOTEORICO,VDBULTOCAB.PESOREAL, "\
                    " VDBULTOCAB.VOLUMEN,VDBULTOCAB.ULTSCAN,VDBULTOCAB.FECULTSCAN, "\
                    " VDBULTOCAB.HORAULTSCAN,VDBULTOCAB.NUMRECIRCULAPREP,VDBULTOCAB.NUMRECIRCULAVERIF, "\
                    " VDBULTOCAB.FECCREADO,VDBULTOCAB.HORACREADO,VDBULTOCAB.CODOPEIMPRIME, "\
                    " VDBULTOCAB.FECIMPRIME,VDBULTOCAB.HORAIMPRIME,VDBULTOCAB.CODOPEVERIFICA, "\
                    " VDBULTOCAB.FECVERIFICA,VDBULTOCAB.HORAVERIFICA,VDBULTOCAB.FECFINALIZA, "\
                    " VDBULTOCAB.HORAFINALIZA,VDBULTOCAB.STATUS,VDBULTOCAB.VDEXTRA, "\
                    " VDBULTOCAB.CODCOMEN,VDBULTOCAB.CODOPEMODIF,VDBULTOCAB.FECMODIF, "\
                    " VDBULTOCAB.HORAMODIF,VDBULTOCAB.PEDIDOHOST,VDBULTOCAB.CODRECURSO, "\
                    " VDBULTOCAB.FECETIQ,VDBULTOCAB.HORAETIQ,VDBULTOCAB.FECFINPICK, "\
                    " VDBULTOCAB.HORAFINPICK,VDBULTOCAB.ZONASSGT,VDBULTOCAB.TARA, "\
                    " VDBULTOCAB.CODMOVTERMOGRAFO,VDBULTOCAB.CODOPETERMOGRAFO,VDBULTOCAB.FECTERMOGRAFO, "\
                    " VDBULTOCAB.HORATERMOGRAFO,VDBULTOCAB.SERIETERMOGRAFO,VDBULTOCAB.TERMOGRAFO "\
        " FROM VDBULTOCAB"\
        " WHERE "\
               " VDBULTOCAB.IDINFOPICK=:IDINFOPICK "\
               " AND VDBULTOCAB.NUMDISP=:NUMDISP "\
               " AND VDBULTOCAB.STATUS=:STATUS "
static v10cursors *vdselbucdisplaystatus;

#define SELBUCVDBULTOCAB "SELECT VDBULTOCAB.ROWID,VDBULTOCAB.CODBULTO,VDBULTOCAB.CODDIV, "\
                    " VDBULTOCAB.ANOPED,VDBULTOCAB.CODPED,VDBULTOCAB.SEQPED, "\
                    " VDBULTOCAB.NBULTO,VDBULTOCAB.TIPOBULTO,VDBULTOCAB.TIPOVOL, "\
                    " VDBULTOCAB.TIPOCAJA,VDBULTOCAB.SWTANULAR,VDBULTOCAB.SWTLLEVAALB, "\
                    " VDBULTOCAB.SWTVERIFFORZADA,VDBULTOCAB.CNTSSCC,VDBULTOCAB.MATCAJA, "\
                    " VDBULTOCAB.SERIERECOGIDA,VDBULTOCAB.TRACKINGAGE,VDBULTOCAB.IDINFOPICK, "\
                    " VDBULTOCAB.NUMDISP,VDBULTOCAB.PESOTEORICO,VDBULTOCAB.PESOREAL, "\
                    " VDBULTOCAB.VOLUMEN,VDBULTOCAB.ULTSCAN,VDBULTOCAB.FECULTSCAN, "\
                    " VDBULTOCAB.HORAULTSCAN,VDBULTOCAB.NUMRECIRCULAPREP,VDBULTOCAB.NUMRECIRCULAVERIF, "\
                    " VDBULTOCAB.FECCREADO,VDBULTOCAB.HORACREADO,VDBULTOCAB.CODOPEIMPRIME, "\
                    " VDBULTOCAB.FECIMPRIME,VDBULTOCAB.HORAIMPRIME,VDBULTOCAB.CODOPEVERIFICA, "\
                    " VDBULTOCAB.FECVERIFICA,VDBULTOCAB.HORAVERIFICA,VDBULTOCAB.FECFINALIZA, "\
                    " VDBULTOCAB.HORAFINALIZA,VDBULTOCAB.STATUS,VDBULTOCAB.VDEXTRA, "\
                    " VDBULTOCAB.CODCOMEN,VDBULTOCAB.CODOPEMODIF,VDBULTOCAB.FECMODIF, "\
                    " VDBULTOCAB.HORAMODIF,VDBULTOCAB.PEDIDOHOST,VDBULTOCAB.CODRECURSO, "\
                    " VDBULTOCAB.FECETIQ,VDBULTOCAB.HORAETIQ,VDBULTOCAB.FECFINPICK, "\
                    " VDBULTOCAB.HORAFINPICK,VDBULTOCAB.ZONASSGT,VDBULTOCAB.TARA, "\
                    " VDBULTOCAB.CODMOVTERMOGRAFO,VDBULTOCAB.CODOPETERMOGRAFO,VDBULTOCAB.FECTERMOGRAFO, "\
                    " VDBULTOCAB.HORATERMOGRAFO,VDBULTOCAB.SERIETERMOGRAFO,VDBULTOCAB.TERMOGRAFO "\
        " FROM VDBULTOCAB"\
        " WHERE "\
               " VDBULTOCAB.CODBULTO=:CODBULTO "
static v10cursors *vdselbucvdbultocab;

#define SELBUCROWIDLOCK "SELECT ROWID,CODBULTO,CODDIV,ANOPED,CODPED,SEQPED,NBULTO, "\
                    " TIPOBULTO,TIPOVOL,TIPOCAJA,SWTANULAR,SWTLLEVAALB,SWTVERIFFORZADA,CNTSSCC, "\
                    " MATCAJA,SERIERECOGIDA,TRACKINGAGE,IDINFOPICK,NUMDISP,PESOTEORICO,PESOREAL, "\
                    " VOLUMEN,ULTSCAN,FECULTSCAN,HORAULTSCAN,NUMRECIRCULAPREP,NUMRECIRCULAVERIF,FECCREADO, "\
                    " HORACREADO,CODOPEIMPRIME,FECIMPRIME,HORAIMPRIME,CODOPEVERIFICA,FECVERIFICA,HORAVERIFICA, "\
                    " FECFINALIZA,HORAFINALIZA,STATUS,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF,PEDIDOHOST,CODRECURSO,FECETIQ,HORAETIQ,FECFINPICK,HORAFINPICK, "\
                    " ZONASSGT,TARA,CODMOVTERMOGRAFO,CODOPETERMOGRAFO,FECTERMOGRAFO,HORATERMOGRAFO,SERIETERMOGRAFO, "\
                    " TERMOGRAFO "\
        " FROM VDBULTOCAB "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselbucrowidlock;

#define UPDABUCLLEVAALBARAN "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " SWTLLEVAALB=:SWTLLEVAALB  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucllevaalbaran;

#define UPDABUCVERIFICAR "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " SWTVERIFFORZADA=:SWTVERIFFORZADA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucverificar;

#define UPDABUCCODBULTO "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODBULTO=:CODBULTO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabuccodbulto;

#define UPDABUCSTATUS "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucstatus;

#define UPDABUCVOLUMENYPESO "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " VOLUMEN=:VOLUMEN , "\
               " PESOTEORICO=:PESOTEORICO  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucvolumenypeso;

#define UPDABUCSTATUSYPESO "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS , "\
               " PESOTEORICO=:PESOTEORICO , "\
               " PESOREAL=:PESOREAL  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucstatusypeso;

#define UPDABUCPESOREAL "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " PESOREAL=:PESOREAL  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucpesoreal;

#define UPDABUCNUMRECIRCULAPREP "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " NUMRECIRCULAPREP=:NUMRECIRCULAPREP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucnumrecirculaprep;

#define UPDABUCNUMRECIRCULAVERIF "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " NUMRECIRCULAVERIF=:NUMRECIRCULAVERIF  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucnumrecirculaverif;

#define UPDABUCSCANNER "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " ULTSCAN=:ULTSCAN , "\
               " FECULTSCAN=:FECULTSCAN , "\
               " HORAULTSCAN=:HORAULTSCAN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucscanner;

#define UPDABUCIMPRESION "UPDATE VDBULTOCAB SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODOPEIMPRIME=:CODOPEIMPRIME , "\
               " FECIMPRIME=:FECIMPRIME , "\
               " HORAIMPRIME=:HORAIMPRIME  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdabucimpresion;

#define INSBUC "INSERT INTO VDBULTOCAB (CODBULTO,CODDIV,ANOPED,CODPED,SEQPED,NBULTO, "\
                    " TIPOBULTO,TIPOVOL,TIPOCAJA,SWTANULAR,SWTLLEVAALB,SWTVERIFFORZADA,CNTSSCC, "\
                    " MATCAJA,SERIERECOGIDA,TRACKINGAGE,IDINFOPICK,NUMDISP,PESOTEORICO,PESOREAL, "\
                    " VOLUMEN,ULTSCAN,FECULTSCAN,HORAULTSCAN,NUMRECIRCULAPREP,NUMRECIRCULAVERIF,FECCREADO, "\
                    " HORACREADO,CODOPEIMPRIME,FECIMPRIME,HORAIMPRIME,CODOPEVERIFICA,FECVERIFICA,HORAVERIFICA, "\
                    " FECFINALIZA,HORAFINALIZA,STATUS,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF, "\
                    " HORAMODIF,PEDIDOHOST,CODRECURSO,FECETIQ,HORAETIQ,FECFINPICK,HORAFINPICK, "\
                    " ZONASSGT,TARA,CODMOVTERMOGRAFO,CODOPETERMOGRAFO,FECTERMOGRAFO,HORATERMOGRAFO,SERIETERMOGRAFO, "\
                    " TERMOGRAFO "\
       " ) VALUES ( "\
                    " :CODBULTO,:CODDIV,:ANOPED,:CODPED,:SEQPED,:NBULTO, "\
                    " :TIPOBULTO,:TIPOVOL,:TIPOCAJA,:SWTANULAR,:SWTLLEVAALB,:SWTVERIFFORZADA,:CNTSSCC, "\
                    " :MATCAJA,:SERIERECOGIDA,:TRACKINGAGE,:IDINFOPICK,:NUMDISP,:PESOTEORICO,:PESOREAL, "\
                    " :VOLUMEN,:ULTSCAN,:FECULTSCAN,:HORAULTSCAN,:NUMRECIRCULAPREP,:NUMRECIRCULAVERIF,:FECCREADO, "\
                    " :HORACREADO,:CODOPEIMPRIME,:FECIMPRIME,:HORAIMPRIME,:CODOPEVERIFICA,:FECVERIFICA,:HORAVERIFICA, "\
                    " :FECFINALIZA,:HORAFINALIZA,:STATUS,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER(),VD.FECHASYS(), "\
                    " VD.HORASYS(),:PEDIDOHOST,:CODRECURSO,:FECETIQ,:HORAETIQ,:FECFINPICK,:HORAFINPICK, "\
                    " :ZONASSGT,:TARA,:CODMOVTERMOGRAFO,:CODOPETERMOGRAFO,:FECTERMOGRAFO,:HORATERMOGRAFO,:SERIETERMOGRAFO, "\
                    " :TERMOGRAFO) "
static v10cursors *vdinsbuc;

#define DELBUC "DELETE VDBULTOCAB WHERE ROWID=:MIROWID "
static v10cursors *vddelbuc;

static vdbultocabs svdbultocab;

static diccols colvdbultocab[]={
	{"ROWID",V10CADENA,(size_t)&svdbultocab.rowid,sizeof(svdbultocab.rowid)},
	{"CODBULTO",V10CADENA,(size_t)&svdbultocab.codbulto,sizeof(svdbultocab.codbulto)},
	{"CODDIV",V10CADENA,(size_t)&svdbultocab.coddiv,sizeof(svdbultocab.coddiv)},
	{"ANOPED",V10LONG,(size_t)&svdbultocab.anoped,sizeof(svdbultocab.anoped)},
	{"CODPED",V10CADENA,(size_t)&svdbultocab.codped,sizeof(svdbultocab.codped)},
	{"SEQPED",V10LONG,(size_t)&svdbultocab.seqped,sizeof(svdbultocab.seqped)},
	{"NBULTO",V10LONG,(size_t)&svdbultocab.nbulto,sizeof(svdbultocab.nbulto)},
	{"TIPOBULTO",V10CADENA,(size_t)&svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto)},
	{"TIPOVOL",V10CADENA,(size_t)&svdbultocab.tipovol,sizeof(svdbultocab.tipovol)},
	{"TIPOCAJA",V10CADENA,(size_t)&svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja)},
	{"SWTANULAR",V10CADENA,(size_t)&svdbultocab.swtanular,sizeof(svdbultocab.swtanular)},
	{"SWTLLEVAALB",V10CADENA,(size_t)&svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb)},
	{"SWTVERIFFORZADA",V10CADENA,(size_t)&svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada)},
	{"CNTSSCC",V10CADENA,(size_t)&svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc)},
	{"MATCAJA",V10CADENA,(size_t)&svdbultocab.matcaja,sizeof(svdbultocab.matcaja)},
	{"SERIERECOGIDA",V10CADENA,(size_t)&svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida)},
	{"TRACKINGAGE",V10CADENA,(size_t)&svdbultocab.trackingage,sizeof(svdbultocab.trackingage)},
	{"IDINFOPICK",V10LONG,(size_t)&svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick)},
	{"NUMDISP",V10LONG,(size_t)&svdbultocab.numdisp,sizeof(svdbultocab.numdisp)},
	{"PESOTEORICO",V10DOUBLE,(size_t)&svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico)},
	{"PESOREAL",V10DOUBLE,(size_t)&svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal)},
	{"VOLUMEN",V10DOUBLE,(size_t)&svdbultocab.volumen,sizeof(svdbultocab.volumen)},
	{"ULTSCAN",V10LONG,(size_t)&svdbultocab.ultscan,sizeof(svdbultocab.ultscan)},
	{"FECULTSCAN",V10LONG,(size_t)&svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan)},
	{"HORAULTSCAN",V10CADENA,(size_t)&svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan)},
	{"NUMRECIRCULAPREP",V10LONG,(size_t)&svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep)},
	{"NUMRECIRCULAVERIF",V10LONG,(size_t)&svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif)},
	{"FECCREADO",V10LONG,(size_t)&svdbultocab.feccreado,sizeof(svdbultocab.feccreado)},
	{"HORACREADO",V10CADENA,(size_t)&svdbultocab.horacreado,sizeof(svdbultocab.horacreado)},
	{"CODOPEIMPRIME",V10CADENA,(size_t)&svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime)},
	{"FECIMPRIME",V10LONG,(size_t)&svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime)},
	{"HORAIMPRIME",V10CADENA,(size_t)&svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime)},
	{"CODOPEVERIFICA",V10CADENA,(size_t)&svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica)},
	{"FECVERIFICA",V10LONG,(size_t)&svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica)},
	{"HORAVERIFICA",V10CADENA,(size_t)&svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica)},
	{"FECFINALIZA",V10LONG,(size_t)&svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza)},
	{"HORAFINALIZA",V10CADENA,(size_t)&svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza)},
	{"STATUS",V10LONG,(size_t)&svdbultocab.status,sizeof(svdbultocab.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdbultocab.vdextra,sizeof(svdbultocab.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdbultocab.codcomen,sizeof(svdbultocab.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdbultocab.horamodif,sizeof(svdbultocab.horamodif)},
	{"PEDIDOHOST",V10CADENA,(size_t)&svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost)},
	{"CODRECURSO",V10CADENA,(size_t)&svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso)},
	{"FECETIQ",V10LONG,(size_t)&svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq)},
	{"HORAETIQ",V10CADENA,(size_t)&svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq)},
	{"FECFINPICK",V10LONG,(size_t)&svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick)},
	{"HORAFINPICK",V10CADENA,(size_t)&svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick)},
	{"ZONASSGT",V10CADENA,(size_t)&svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt)},
	{"TARA",V10DOUBLE,(size_t)&svdbultocab.tara,sizeof(svdbultocab.tara)},
	{"CODMOVTERMOGRAFO",V10LONG,(size_t)&svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo)},
	{"CODOPETERMOGRAFO",V10CADENA,(size_t)&svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo)},
	{"FECTERMOGRAFO",V10LONG,(size_t)&svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo)},
	{"HORATERMOGRAFO",V10CADENA,(size_t)&svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo)},
	{"SERIETERMOGRAFO",V10CADENA,(size_t)&svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo)},
	{"TERMOGRAFO",V10CADENA,(size_t)&svdbultocab.termografo,sizeof(svdbultocab.termografo)}
	};
static diccionarios dvdbultocab[]={
    {colvdbultocab,57}
};
diccionario dbuc={dvdbultocab,1};

static char msglogBUC[LCADENA];
static char msgdebugBUC[LCADENABIG];
static int init=0;


static void fin_vd_buc(void)
{
if (vdselbucstatus) {
    liberacursor(vdselbucstatus);
    vdselbucstatus = NULL;
}
if (vdselbucbultosdeunpedido) {
    liberacursor(vdselbucbultosdeunpedido);
    vdselbucbultosdeunpedido = NULL;
}
if (vdselbucbultostipoyvolu) {
    liberacursor(vdselbucbultostipoyvolu);
    vdselbucbultostipoyvolu = NULL;
}
if (vdselbucdisplaystatus) {
    liberacursor(vdselbucdisplaystatus);
    vdselbucdisplaystatus = NULL;
}
if (vdselbucvdbultocab) {
    liberacursor(vdselbucvdbultocab);
    vdselbucvdbultocab = NULL;
}
if (vdselbucrowidlock) {
    liberacursor(vdselbucrowidlock);
    vdselbucrowidlock = NULL;
}
if (vdupdabucllevaalbaran) {
    liberacursor(vdupdabucllevaalbaran);
    vdupdabucllevaalbaran = NULL;
}
if (vdupdabucverificar) {
    liberacursor(vdupdabucverificar);
    vdupdabucverificar = NULL;
}
if (vdupdabuccodbulto) {
    liberacursor(vdupdabuccodbulto);
    vdupdabuccodbulto = NULL;
}
if (vdupdabucstatus) {
    liberacursor(vdupdabucstatus);
    vdupdabucstatus = NULL;
}
if (vdupdabucvolumenypeso) {
    liberacursor(vdupdabucvolumenypeso);
    vdupdabucvolumenypeso = NULL;
}
if (vdupdabucstatusypeso) {
    liberacursor(vdupdabucstatusypeso);
    vdupdabucstatusypeso = NULL;
}
if (vdupdabucpesoreal) {
    liberacursor(vdupdabucpesoreal);
    vdupdabucpesoreal = NULL;
}
if (vdupdabucnumrecirculaprep) {
    liberacursor(vdupdabucnumrecirculaprep);
    vdupdabucnumrecirculaprep = NULL;
}
if (vdupdabucnumrecirculaverif) {
    liberacursor(vdupdabucnumrecirculaverif);
    vdupdabucnumrecirculaverif = NULL;
}
if (vdupdabucscanner) {
    liberacursor(vdupdabucscanner);
    vdupdabucscanner = NULL;
}
if (vdupdabucimpresion) {
    liberacursor(vdupdabucimpresion);
    vdupdabucimpresion = NULL;
}
if (vdinsbuc != NULL) {
    liberacursor(vdinsbuc);
    vdinsbuc = NULL;
}
if (vddelbuc != NULL) {
    liberacursor(vddelbuc);
    vddelbuc = NULL;
}
}
static void init_selbucstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucstatus=abrecursordebug(SELBUCSTATUS,1280);
    definetodo(vdselbucstatus,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucstatus,"STATUS",&svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_selbucbultosdeunpedido(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucbultosdeunpedido=abrecursordebug(SELBUCBULTOSDEUNPEDIDO,1280);
    definetodo(vdselbucbultosdeunpedido,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucbultosdeunpedido,"CODDIV",svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          "ANOPED",&svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          "CODPED",svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          "SEQPED",&svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_selbucbultostipoyvolu(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucbultostipoyvolu=abrecursordebug(SELBUCBULTOSTIPOYVOLU,1280);
    definetodo(vdselbucbultostipoyvolu,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucbultostipoyvolu,"CODDIV",svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          "ANOPED",&svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          "CODPED",svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          "SEQPED",&svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          "TIPOBULTO",svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          "TIPOVOL",svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_selbucdisplaystatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucdisplaystatus=abrecursordebug(SELBUCDISPLAYSTATUS,1280);
    definetodo(vdselbucdisplaystatus,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucdisplaystatus,"IDINFOPICK",&svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          "NUMDISP",&svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          "STATUS",&svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_selbucvdbultocab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucvdbultocab=abrecursordebug(SELBUCVDBULTOCAB,1280);
    definetodo(vdselbucvdbultocab,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucvdbultocab,"CODBULTO",svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_selbucrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdselbucrowidlock=abrecursordebug(SELBUCROWIDLOCK,1280);
    definetodo(vdselbucrowidlock,svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          &svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          &svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          &svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          &svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          &svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          &svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          &svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          &svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          &svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          &svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          &svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          &svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          &svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          &svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          &svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          &svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          &svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          &svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          svdbultocab.codopemodif,sizeof(svdbultocab.codopemodif),V10CADENA,
                          &svdbultocab.fecmodif,sizeof(svdbultocab.fecmodif),V10LONG,
                          svdbultocab.horamodif,sizeof(svdbultocab.horamodif),V10CADENA,
                          svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          &svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          &svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          &svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          &svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          &svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    bindtodo(vdselbucrowidlock,"MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucllevaalbaran(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucllevaalbaran=abrecursordebug(UPDABUCLLEVAALBARAN,1280);
    bindtodo(vdupdabucllevaalbaran,"SWTLLEVAALB",svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucverificar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucverificar=abrecursordebug(UPDABUCVERIFICAR,1280);
    bindtodo(vdupdabucverificar,"SWTVERIFFORZADA",svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabuccodbulto(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabuccodbulto=abrecursordebug(UPDABUCCODBULTO,1280);
    bindtodo(vdupdabuccodbulto,"CODBULTO",svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucstatus=abrecursordebug(UPDABUCSTATUS,1280);
    bindtodo(vdupdabucstatus,"STATUS",&svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucvolumenypeso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucvolumenypeso=abrecursordebug(UPDABUCVOLUMENYPESO,1280);
    bindtodo(vdupdabucvolumenypeso,"VOLUMEN",&svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          "PESOTEORICO",&svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucstatusypeso(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucstatusypeso=abrecursordebug(UPDABUCSTATUSYPESO,1280);
    bindtodo(vdupdabucstatusypeso,"STATUS",&svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          "PESOTEORICO",&svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          "PESOREAL",&svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucpesoreal(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucpesoreal=abrecursordebug(UPDABUCPESOREAL,1280);
    bindtodo(vdupdabucpesoreal,"PESOREAL",&svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucnumrecirculaprep(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucnumrecirculaprep=abrecursordebug(UPDABUCNUMRECIRCULAPREP,1280);
    bindtodo(vdupdabucnumrecirculaprep,"NUMRECIRCULAPREP",&svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucnumrecirculaverif(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucnumrecirculaverif=abrecursordebug(UPDABUCNUMRECIRCULAVERIF,1280);
    bindtodo(vdupdabucnumrecirculaverif,"NUMRECIRCULAVERIF",&svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucscanner(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucscanner=abrecursordebug(UPDABUCSCANNER,1280);
    bindtodo(vdupdabucscanner,"ULTSCAN",&svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          "FECULTSCAN",&svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          "HORAULTSCAN",svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_updabucimpresion(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdupdabucimpresion=abrecursordebug(UPDABUCIMPRESION,1280);
    bindtodo(vdupdabucimpresion,"CODOPEIMPRIME",svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          "FECIMPRIME",&svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          "HORAIMPRIME",svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          "MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_insbuc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vdinsbuc=abrecursordebug(INSBUC,1280);
    bindtodo(vdinsbuc,"CODBULTO",svdbultocab.codbulto,sizeof(svdbultocab.codbulto),V10CADENA,
                          "CODDIV",svdbultocab.coddiv,sizeof(svdbultocab.coddiv),V10CADENA,
                          "ANOPED",&svdbultocab.anoped,sizeof(svdbultocab.anoped),V10LONG,
                          "CODPED",svdbultocab.codped,sizeof(svdbultocab.codped),V10CADENA,
                          "SEQPED",&svdbultocab.seqped,sizeof(svdbultocab.seqped),V10LONG,
                          "NBULTO",&svdbultocab.nbulto,sizeof(svdbultocab.nbulto),V10LONG,
                          "TIPOBULTO",svdbultocab.tipobulto,sizeof(svdbultocab.tipobulto),V10CADENA,
                          "TIPOVOL",svdbultocab.tipovol,sizeof(svdbultocab.tipovol),V10CADENA,
                          "TIPOCAJA",svdbultocab.tipocaja,sizeof(svdbultocab.tipocaja),V10CADENA,
                          "SWTANULAR",svdbultocab.swtanular,sizeof(svdbultocab.swtanular),V10CADENA,
                          "SWTLLEVAALB",svdbultocab.swtllevaalb,sizeof(svdbultocab.swtllevaalb),V10CADENA,
                          "SWTVERIFFORZADA",svdbultocab.swtverifforzada,sizeof(svdbultocab.swtverifforzada),V10CADENA,
                          "CNTSSCC",svdbultocab.cntsscc,sizeof(svdbultocab.cntsscc),V10CADENA,
                          "MATCAJA",svdbultocab.matcaja,sizeof(svdbultocab.matcaja),V10CADENA,
                          "SERIERECOGIDA",svdbultocab.serierecogida,sizeof(svdbultocab.serierecogida),V10CADENA,
                          "TRACKINGAGE",svdbultocab.trackingage,sizeof(svdbultocab.trackingage),V10CADENA,
                          "IDINFOPICK",&svdbultocab.idinfopick,sizeof(svdbultocab.idinfopick),V10LONG,
                          "NUMDISP",&svdbultocab.numdisp,sizeof(svdbultocab.numdisp),V10LONG,
                          "PESOTEORICO",&svdbultocab.pesoteorico,sizeof(svdbultocab.pesoteorico),V10DOUBLE,
                          "PESOREAL",&svdbultocab.pesoreal,sizeof(svdbultocab.pesoreal),V10DOUBLE,
                          "VOLUMEN",&svdbultocab.volumen,sizeof(svdbultocab.volumen),V10DOUBLE,
                          "ULTSCAN",&svdbultocab.ultscan,sizeof(svdbultocab.ultscan),V10LONG,
                          "FECULTSCAN",&svdbultocab.fecultscan,sizeof(svdbultocab.fecultscan),V10LONG,
                          "HORAULTSCAN",svdbultocab.horaultscan,sizeof(svdbultocab.horaultscan),V10CADENA,
                          "NUMRECIRCULAPREP",&svdbultocab.numrecirculaprep,sizeof(svdbultocab.numrecirculaprep),V10LONG,
                          "NUMRECIRCULAVERIF",&svdbultocab.numrecirculaverif,sizeof(svdbultocab.numrecirculaverif),V10LONG,
                          "FECCREADO",&svdbultocab.feccreado,sizeof(svdbultocab.feccreado),V10LONG,
                          "HORACREADO",svdbultocab.horacreado,sizeof(svdbultocab.horacreado),V10CADENA,
                          "CODOPEIMPRIME",svdbultocab.codopeimprime,sizeof(svdbultocab.codopeimprime),V10CADENA,
                          "FECIMPRIME",&svdbultocab.fecimprime,sizeof(svdbultocab.fecimprime),V10LONG,
                          "HORAIMPRIME",svdbultocab.horaimprime,sizeof(svdbultocab.horaimprime),V10CADENA,
                          "CODOPEVERIFICA",svdbultocab.codopeverifica,sizeof(svdbultocab.codopeverifica),V10CADENA,
                          "FECVERIFICA",&svdbultocab.fecverifica,sizeof(svdbultocab.fecverifica),V10LONG,
                          "HORAVERIFICA",svdbultocab.horaverifica,sizeof(svdbultocab.horaverifica),V10CADENA,
                          "FECFINALIZA",&svdbultocab.fecfinaliza,sizeof(svdbultocab.fecfinaliza),V10LONG,
                          "HORAFINALIZA",svdbultocab.horafinaliza,sizeof(svdbultocab.horafinaliza),V10CADENA,
                          "STATUS",&svdbultocab.status,sizeof(svdbultocab.status),V10LONG,
                          "VDEXTRA",svdbultocab.vdextra,sizeof(svdbultocab.vdextra),V10CADENA,
                          "CODCOMEN",&svdbultocab.codcomen,sizeof(svdbultocab.codcomen),V10LONG,
                          "PEDIDOHOST",svdbultocab.pedidohost,sizeof(svdbultocab.pedidohost),V10CADENA,
                          "CODRECURSO",svdbultocab.codrecurso,sizeof(svdbultocab.codrecurso),V10CADENA,
                          "FECETIQ",&svdbultocab.fecetiq,sizeof(svdbultocab.fecetiq),V10LONG,
                          "HORAETIQ",svdbultocab.horaetiq,sizeof(svdbultocab.horaetiq),V10CADENA,
                          "FECFINPICK",&svdbultocab.fecfinpick,sizeof(svdbultocab.fecfinpick),V10LONG,
                          "HORAFINPICK",svdbultocab.horafinpick,sizeof(svdbultocab.horafinpick),V10CADENA,
                          "ZONASSGT",svdbultocab.zonassgt,sizeof(svdbultocab.zonassgt),V10CADENA,
                          "TARA",&svdbultocab.tara,sizeof(svdbultocab.tara),V10DOUBLE,
                          "CODMOVTERMOGRAFO",&svdbultocab.codmovtermografo,sizeof(svdbultocab.codmovtermografo),V10LONG,
                          "CODOPETERMOGRAFO",svdbultocab.codopetermografo,sizeof(svdbultocab.codopetermografo),V10CADENA,
                          "FECTERMOGRAFO",&svdbultocab.fectermografo,sizeof(svdbultocab.fectermografo),V10LONG,
                          "HORATERMOGRAFO",svdbultocab.horatermografo,sizeof(svdbultocab.horatermografo),V10CADENA,
                          "SERIETERMOGRAFO",svdbultocab.serietermografo,sizeof(svdbultocab.serietermografo),V10CADENA,
                          "TERMOGRAFO",svdbultocab.termografo,sizeof(svdbultocab.termografo),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

static void init_delbuc(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdbultocab[0].numcol;nc++) dvdbultocab[0].c[nc].offset-=(size_t)&svdbultocab;
    vddelbuc=abrecursordebug(DELBUC,1280);
    bindtodo(vddelbuc,"MIROWID",svdbultocab.rowid,sizeof(svdbultocab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_buc);
        init = 1;
    }
}

diccionario *BUCdamediccionario(void)
{
     return(&dbuc);
}

int BUCbuscastatus(long status,vdbultocabs *buc)
{
  int vdret;
  memset(&svdbultocab,0,sizeof(svdbultocab));
  svdbultocab.status=status;
  if (vdselbucstatus==NULL) init_selbucstatus();
  vdret=ejefetchcursor(vdselbucstatus);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbucstatus. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BUCnextstatus(vdbultocabs *buc)
{
  int vdret;
  vdret=fetchcursor(vdselbucstatus);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbucstatus. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbucstatus);
  return(VD_EERRORACLE);
}

int BUCbuscabultosdeunpedido(char *coddiv,long anoped,char *codped,long seqped,vdbultocabs *buc)
{
  int vdret;
  memset(&svdbultocab,0,sizeof(svdbultocab));
  strcpy(svdbultocab.coddiv,coddiv);
  svdbultocab.anoped=anoped;
  strcpy(svdbultocab.codped,codped);
  svdbultocab.seqped=seqped;
  if (vdselbucbultosdeunpedido==NULL) init_selbucbultosdeunpedido();
  vdret=ejefetchcursor(vdselbucbultosdeunpedido);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbucbultosdeunpedido. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BUCnextbultosdeunpedido(vdbultocabs *buc)
{
  int vdret;
  vdret=fetchcursor(vdselbucbultosdeunpedido);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbucbultosdeunpedido. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbucbultosdeunpedido);
  return(VD_EERRORACLE);
}

int BUCbuscabultostipoyvolu(char *coddiv,long anoped,char *codped,long seqped,char *tipobulto,char *tipovol,vdbultocabs *buc)
{
  int vdret;
  memset(&svdbultocab,0,sizeof(svdbultocab));
  strcpy(svdbultocab.coddiv,coddiv);
  svdbultocab.anoped=anoped;
  strcpy(svdbultocab.codped,codped);
  svdbultocab.seqped=seqped;
  strcpy(svdbultocab.tipobulto,tipobulto);
  strcpy(svdbultocab.tipovol,tipovol);
  if (vdselbucbultostipoyvolu==NULL) init_selbucbultostipoyvolu();
  vdret=ejefetchcursor(vdselbucbultostipoyvolu);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselbucbultostipoyvolu. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int BUCnextbultostipoyvolu(vdbultocabs *buc)
{
  int vdret;
  vdret=fetchcursor(vdselbucbultostipoyvolu);
  if (vdret==0) {
     *buc=svdbultocab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselbucbultostipoyvolu. vdret %d. \n",BUClog(&svdbultocab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselbucbultostipoyvolu);
  return(VD_EERRORACLE);
}

int BUCseldisplaystatus(long idinfopick,long numdisp,long status,vdbultocabs *buc)
{
  int vdret;
  if (vdselbucdisplaystatus==NULL) init_selbucdisplaystatus();
  memset(&svdbultocab,0,sizeof(svdbultocab));
  svdbultocab.idinfopick=idinfopick;
  svdbultocab.numdisp=numdisp;
  svdbultocab.status=status;
  vdret=ejefetchcursor(vdselbucdisplaystatus);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbucdisplaystatus. vdret %d. \n",BUClog(&svdbultocab),vdret);
    return(VD_EERRORACLE);
   }
  *buc=svdbultocab;
  return(vdret);
}

int BUCselvdbultocab(char *codbulto,vdbultocabs *buc)
{
  int vdret;
  if (vdselbucvdbultocab==NULL) init_selbucvdbultocab();
  memset(&svdbultocab,0,sizeof(svdbultocab));
  strcpy(svdbultocab.codbulto,codbulto);
  vdret=ejefetchcursor(vdselbucvdbultocab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselbucvdbultocab. vdret %d. \n",BUClog(&svdbultocab),vdret);
    return(VD_EERRORACLE);
   }
  *buc=svdbultocab;
  return(vdret);
}

int BUClock(vdbultocabs *buc,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdbultocab=*buc;
    if (vdselbucrowidlock==NULL) init_selbucrowidlock();
    savepoint("lockvdbultocab");
    while (1) {
        vdret=ejefetchcursor(vdselbucrowidlock);
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
    vdret=vverificacampos(buc,&svdbultocab,&dvdbultocab[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdbultocab");
    return(vdret);
}

int BUCactualizallevaalbaran(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizallevaalbaran:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucllevaalbaran==NULL) init_updabucllevaalbaran();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucllevaalbaran);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucllevaalbaran);
     getcurerrornombre(vdupdabucllevaalbaran->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucllevaalbaran)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizaverificar(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizaverificar:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucverificar==NULL) init_updabucverificar();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucverificar);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucverificar);
     getcurerrornombre(vdupdabucverificar->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucverificar)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizacodbulto(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizacodbulto:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabuccodbulto==NULL) init_updabuccodbulto();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabuccodbulto);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabuccodbulto);
     getcurerrornombre(vdupdabuccodbulto->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabuccodbulto)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizastatus(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizastatus:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucstatus==NULL) init_updabucstatus();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucstatus);
     getcurerrornombre(vdupdabucstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizavolumenypeso(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizavolumenypeso:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucvolumenypeso==NULL) init_updabucvolumenypeso();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucvolumenypeso);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucvolumenypeso);
     getcurerrornombre(vdupdabucvolumenypeso->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucvolumenypeso)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizastatusypeso(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizastatusypeso:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucstatusypeso==NULL) init_updabucstatusypeso();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucstatusypeso);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucstatusypeso);
     getcurerrornombre(vdupdabucstatusypeso->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucstatusypeso)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizapesoreal(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizapesoreal:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucpesoreal==NULL) init_updabucpesoreal();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucpesoreal);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucpesoreal);
     getcurerrornombre(vdupdabucpesoreal->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucpesoreal)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizanumrecirculaprep(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizanumrecirculaprep:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucnumrecirculaprep==NULL) init_updabucnumrecirculaprep();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucnumrecirculaprep);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucnumrecirculaprep);
     getcurerrornombre(vdupdabucnumrecirculaprep->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucnumrecirculaprep)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizanumrecirculaverif(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizanumrecirculaverif:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucnumrecirculaverif==NULL) init_updabucnumrecirculaverif();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucnumrecirculaverif);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucnumrecirculaverif);
     getcurerrornombre(vdupdabucnumrecirculaverif->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucnumrecirculaverif)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizascanner(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizascanner:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucscanner==NULL) init_updabucscanner();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucscanner);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucscanner);
     getcurerrornombre(vdupdabucscanner->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucscanner)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCactualizaimpresion(vdbultocabs *buc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando BUCactualizaimpresion:  %s .  \n",BUClog(&svdbultocab));
  if (vdupdabucimpresion==NULL) init_updabucimpresion();
  svdbultocab=*buc;
  vdret=ejecutacursor(vdupdabucimpresion);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdabucimpresion);
     getcurerrornombre(vdupdabucimpresion->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdabucimpresion)!=1) return(VD_EERRORACLE);
  return(0);
}

int BUCinsert(vdbultocabs *buc,int error)
{
  int vdret;
  if (!vdinsbuc) init_insbuc();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",BUClog(&svdbultocab));
  svdbultocab=*buc;
  vdret=ejecutacursor(vdinsbuc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsbuc);
     getcurerrornombre(vdinsbuc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int BUCdel(vdbultocabs *buc,int error)
{
  int vdret;
  svdbultocab=*buc;
  if (vddelbuc==NULL) init_delbuc();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",BUClog(&svdbultocab));
  vdret=ejecutacursor(vddelbuc);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelbuc);
     getcurerrornombre(vddelbuc->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * BUClog(vdbultocabs *buc)
{
    sprintf(msglogBUC, "VDBULTOCAB: codbulto %s ",buc->codbulto);
    return(msglogBUC);
}

char * BUCdebug(vdbultocabs *buc)
{
    debugestruct(&dbuc,buc,msgdebugBUC);
    return(msgdebugBUC);
}

