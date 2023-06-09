// Modulo generado automaticamente a partir de VDPEDIDORIGLIN.DEF
//#***
//# VDPEDIDORIGLIN.c - Generaci�n autom�tica del c�digo c para la tabla de L�neas de Pedidos                                                       
//# 
//# Prop�sito: Funciones de acceso a la tabla VDPEDIDOLIN
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 06-03-2008                                              
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=POL
//EXTRA=COMEN,V10CADENA,1025;
//
//CLAVE=LINEA,CODDIV,ANOPED,CODPED,SEQLINEA;
//
//RECORRE=PEDIDO,CODDIV,ANOPED,CODPED,SEQPED;
//RECORRE=STATUS,STATUS;
//RECORRE=LINPEPDTE,CODDIV,ANOPED,CODPED,SEQPED,STATUS
//UPDATE=STATUS,STATUS;
//
//INTERFASE
//UPDATE
//DELETE
//INSERT
//LOCK
//ROWID

#include "vdpedidos.h"
#define SELPOLLINEA "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
               " VDPEDIDORIGLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDORIGLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDORIGLIN.CODPED=:CODPED "\
               " AND VDPEDIDORIGLIN.SEQLINEA=:SEQLINEA "
static v10cursors *vdselpollinea;

#define SELPOLPEDIDO "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
               " VDPEDIDORIGLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDORIGLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDORIGLIN.CODPED=:CODPED "\
               " AND VDPEDIDORIGLIN.SEQPED=:SEQPED "
static v10cursors *vdselpolpedido;

#define SELPOLSTATUS "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
               " VDPEDIDORIGLIN.STATUS=:STATUS "
static v10cursors *vdselpolstatus;

#define SELPOLLINPEPDTE "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
               " VDPEDIDORIGLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDORIGLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDORIGLIN.CODPED=:CODPED "\
               " AND VDPEDIDORIGLIN.SEQPED=:SEQPED "\
               " AND VDPEDIDORIGLIN.STATUS=:STATUS "
static v10cursors *vdselpollinpepdte;

#define SELPOLROWID "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
              " ROWID=:MIROWID "
static v10cursors *vdselpolrowid;

#define SELPOLVDPEDIDORIGLIN "SELECT VDPEDIDORIGLIN.ROWID,VDPEDIDORIGLIN.CODDIV,VDPEDIDORIGLIN.ANOPED, "\
                    " VDPEDIDORIGLIN.CODPED,VDPEDIDORIGLIN.SEQLINEA,VDPEDIDORIGLIN.SEQLINORIG, "\
                    " VDPEDIDORIGLIN.CODART,VDPEDIDORIGLIN.CODLOT,VDPEDIDORIGLIN.CADUCI, "\
                    " VDPEDIDORIGLIN.CANTPEDIDA,VDPEDIDORIGLIN.UNIDADESHOST,VDPEDIDORIGLIN.BACKORDER, "\
                    " VDPEDIDORIGLIN.CODAGRUPA,VDPEDIDORIGLIN.OPCIONPRECIO,VDPEDIDORIGLIN.PRECIOUNI, "\
                    " VDPEDIDORIGLIN.UNIDADESPRECIO,VDPEDIDORIGLIN.DCTO,VDPEDIDORIGLIN.IVA, "\
                    " VDPEDIDORIGLIN.RECARGO,VDPEDIDORIGLIN.SWTCREAVERSION,VDPEDIDORIGLIN.MARCASTK, "\
                    " VDPEDIDORIGLIN.NUMEROSERIE,VDPEDIDORIGLIN.PEDIDOHOST,VDPEDIDORIGLIN.MARCARPT, "\
                    " VDPEDIDORIGLIN.TIPOREDONDEO,VDPEDIDORIGLIN.CODCOMEN,VDPEDIDORIGLIN.STATUS, "\
                    " VDPEDIDORIGLIN.VDEXTRA,VDPEDIDORIGLIN.CODOPEMODIF,VDPEDIDORIGLIN.FECMODIF, "\
                    " VDPEDIDORIGLIN.HORAMODIF,VDPEDIDORIGLIN.CODMAT,VDPEDIDORIGLIN.SEQPED, "\
                    " VDPEDIDORIGLIN.SWTDCTO,VDPEDIDORIGLIN.SWTPEDBON,VDPEDIDORIGLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN"\
        " WHERE "\
               " VDPEDIDORIGLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDORIGLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDORIGLIN.CODPED=:CODPED "\
               " AND VDPEDIDORIGLIN.SEQLINEA=:SEQLINEA "\
               " AND VDPEDIDORIGLIN.SEQPED=:SEQPED "
static v10cursors *vdselpolvdpedidoriglin;

#define SELPOLROWIDLOCK "SELECT ROWID,CODDIV,ANOPED,CODPED,SEQLINEA,SEQLINORIG,CODART, "\
                    " CODLOT,CADUCI,CANTPEDIDA,UNIDADESHOST,BACKORDER,CODAGRUPA,OPCIONPRECIO, "\
                    " PRECIOUNI,UNIDADESPRECIO,DCTO,IVA,RECARGO,SWTCREAVERSION,MARCASTK, "\
                    " NUMEROSERIE,PEDIDOHOST,MARCARPT,TIPOREDONDEO,CODCOMEN,STATUS,VDEXTRA, "\
                    " CODOPEMODIF,FECMODIF,HORAMODIF,CODMAT,SEQPED,SWTDCTO,SWTPEDBON, "\
                    " CANTPEDIDACLI "\
        " FROM VDPEDIDORIGLIN "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselpolrowidlock;

#define UPDAPOLSTATUS "UPDATE VDPEDIDORIGLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdapolstatus;

#define UPDAPOL "UPDATE VDPEDIDORIGLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " CODDIV=:CODDIV , "\
               " ANOPED=:ANOPED , "\
               " CODPED=:CODPED , "\
               " SEQLINEA=:SEQLINEA , "\
               " SEQLINORIG=:SEQLINORIG , "\
               " CODART=:CODART , "\
               " CODLOT=:CODLOT , "\
               " CADUCI=:CADUCI , "\
               " CANTPEDIDA=:CANTPEDIDA , "\
               " UNIDADESHOST=:UNIDADESHOST , "\
               " BACKORDER=:BACKORDER , "\
               " CODAGRUPA=:CODAGRUPA , "\
               " OPCIONPRECIO=:OPCIONPRECIO , "\
               " PRECIOUNI=:PRECIOUNI , "\
               " UNIDADESPRECIO=:UNIDADESPRECIO , "\
               " DCTO=:DCTO , "\
               " IVA=:IVA , "\
               " RECARGO=:RECARGO , "\
               " SWTCREAVERSION=:SWTCREAVERSION , "\
               " MARCASTK=:MARCASTK , "\
               " NUMEROSERIE=:NUMEROSERIE , "\
               " PEDIDOHOST=:PEDIDOHOST , "\
               " MARCARPT=:MARCARPT , "\
               " TIPOREDONDEO=:TIPOREDONDEO , "\
               " CODCOMEN=:CODCOMEN , "\
               " STATUS=:STATUS , "\
               " VDEXTRA=:VDEXTRA , "\
               " CODMAT=:CODMAT , "\
               " SEQPED=:SEQPED , "\
               " SWTDCTO=:SWTDCTO , "\
               " SWTPEDBON=:SWTPEDBON , "\
               " CANTPEDIDACLI=:CANTPEDIDACLI  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdapolvdpedidoriglin;

#define INSPOL "INSERT INTO VDPEDIDORIGLIN (CODDIV,ANOPED,CODPED,SEQLINEA,SEQLINORIG,CODART, "\
                    " CODLOT,CADUCI,CANTPEDIDA,UNIDADESHOST,BACKORDER,CODAGRUPA,OPCIONPRECIO, "\
                    " PRECIOUNI,UNIDADESPRECIO,DCTO,IVA,RECARGO,SWTCREAVERSION,MARCASTK, "\
                    " NUMEROSERIE,PEDIDOHOST,MARCARPT,TIPOREDONDEO,CODCOMEN,STATUS,VDEXTRA, "\
                    " CODOPEMODIF,FECMODIF,HORAMODIF,CODMAT,SEQPED,SWTDCTO,SWTPEDBON, "\
                    " CANTPEDIDACLI "\
       " ) VALUES ( "\
                    " :CODDIV,:ANOPED,:CODPED,:SEQLINEA,:SEQLINORIG,:CODART, "\
                    " :CODLOT,:CADUCI,:CANTPEDIDA,:UNIDADESHOST,:BACKORDER,:CODAGRUPA,:OPCIONPRECIO, "\
                    " :PRECIOUNI,:UNIDADESPRECIO,:DCTO,:IVA,:RECARGO,:SWTCREAVERSION,:MARCASTK, "\
                    " :NUMEROSERIE,:PEDIDOHOST,:MARCARPT,:TIPOREDONDEO,:CODCOMEN,:STATUS,:VDEXTRA, "\
                    " VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS(),:CODMAT,:SEQPED,:SWTDCTO,:SWTPEDBON, "\
                    " :CANTPEDIDACLI) "
static v10cursors *vdinspol;

#define DELPOL "DELETE VDPEDIDORIGLIN WHERE ROWID=:MIROWID "
static v10cursors *vddelpol;

static vdpedidoriglins svdpedidoriglin;

static diccols colvdpedidoriglin[]={
	{"ROWID",V10CADENA,(size_t)&svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid)},
	{"CODDIV",V10CADENA,(size_t)&svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv)},
	{"ANOPED",V10LONG,(size_t)&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped)},
	{"CODPED",V10CADENA,(size_t)&svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped)},
	{"SEQLINEA",V10LONG,(size_t)&svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea)},
	{"SEQLINORIG",V10LONG,(size_t)&svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig)},
	{"CODART",V10CADENA,(size_t)&svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot)},
	{"CADUCI",V10CADENA,(size_t)&svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci)},
	{"CANTPEDIDA",V10DOUBLE,(size_t)&svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida)},
	{"UNIDADESHOST",V10CADENA,(size_t)&svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost)},
	{"BACKORDER",V10CADENA,(size_t)&svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder)},
	{"CODAGRUPA",V10CADENA,(size_t)&svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa)},
	{"OPCIONPRECIO",V10CADENA,(size_t)&svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni)},
	{"UNIDADESPRECIO",V10CADENA,(size_t)&svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio)},
	{"DCTO",V10DOUBLE,(size_t)&svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto)},
	{"IVA",V10DOUBLE,(size_t)&svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva)},
	{"RECARGO",V10DOUBLE,(size_t)&svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo)},
	{"SWTCREAVERSION",V10CADENA,(size_t)&svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion)},
	{"MARCASTK",V10CADENA,(size_t)&svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie)},
	{"PEDIDOHOST",V10CADENA,(size_t)&svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost)},
	{"MARCARPT",V10CADENA,(size_t)&svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt)},
	{"TIPOREDONDEO",V10CADENA,(size_t)&svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo)},
	{"CODCOMEN",V10LONG,(size_t)&svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen)},
	{"STATUS",V10LONG,(size_t)&svdpedidoriglin.status,sizeof(svdpedidoriglin.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif)},
	{"CODMAT",V10CADENA,(size_t)&svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat)},
	{"SEQPED",V10LONG,(size_t)&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped)},
	{"SWTDCTO",V10CADENA,(size_t)&svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto)},
	{"SWTPEDBON",V10CADENA,(size_t)&svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon)},
	{"CANTPEDIDACLI",V10DOUBLE,(size_t)&svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli)},
	{"COMEN",V10CADENA,(size_t)&svdpedidoriglin.comen,sizeof(svdpedidoriglin.comen)},
	};
static diccionarios dvdpedidoriglin[]={
    {colvdpedidoriglin,37}
};
diccionario dpol={dvdpedidoriglin,1};

static char msglogPOL[LCADENA];
static char msgdebugPOL[LCADENABIG];
static int init=0;


static void fin_vd_pol(void)
{
if (vdselpollinea) {
    liberacursor(vdselpollinea);
    vdselpollinea = NULL;
}
if (vdselpolpedido) {
    liberacursor(vdselpolpedido);
    vdselpolpedido = NULL;
}
if (vdselpolstatus) {
    liberacursor(vdselpolstatus);
    vdselpolstatus = NULL;
}
if (vdselpollinpepdte) {
    liberacursor(vdselpollinpepdte);
    vdselpollinpepdte = NULL;
}
if (vdselpolrowid) {
    liberacursor(vdselpolrowid);
    vdselpolrowid = NULL;
}
if (vdselpolvdpedidoriglin) {
    liberacursor(vdselpolvdpedidoriglin);
    vdselpolvdpedidoriglin = NULL;
}
if (vdselpolrowidlock) {
    liberacursor(vdselpolrowidlock);
    vdselpolrowidlock = NULL;
}
if (vdupdapolstatus) {
    liberacursor(vdupdapolstatus);
    vdupdapolstatus = NULL;
}
if (vdupdapolvdpedidoriglin) {
    liberacursor(vdupdapolvdpedidoriglin);
    vdupdapolvdpedidoriglin = NULL;
}
if (vdinspol != NULL) {
    liberacursor(vdinspol);
    vdinspol = NULL;
}
if (vddelpol != NULL) {
    liberacursor(vddelpol);
    vddelpol = NULL;
}
}
static void init_selpollinea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpollinea=abrecursordebug(SELPOLLINEA,1280);
    definetodo(vdselpollinea,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpollinea,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQLINEA",&svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpolpedido(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpolpedido=abrecursordebug(SELPOLPEDIDO,1280);
    definetodo(vdselpolpedido,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpolpedido,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQPED",&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpolstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpolstatus=abrecursordebug(SELPOLSTATUS,1280);
    definetodo(vdselpolstatus,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpolstatus,"STATUS",&svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpollinpepdte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpollinpepdte=abrecursordebug(SELPOLLINPEPDTE,1280);
    definetodo(vdselpollinpepdte,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpollinpepdte,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQPED",&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          "STATUS",&svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpolrowid(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpolrowid=abrecursordebug(SELPOLROWID,1280);
    definetodo(vdselpolrowid,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpolrowid,"MIROWID",svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpolvdpedidoriglin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpolvdpedidoriglin=abrecursordebug(SELPOLVDPEDIDORIGLIN,1280);
    definetodo(vdselpolvdpedidoriglin,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpolvdpedidoriglin,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQLINEA",&svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          "SEQPED",&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_selpolrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdselpolrowidlock=abrecursordebug(SELPOLROWIDLOCK,1280);
    definetodo(vdselpolrowidlock,svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          &svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          &svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          &svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          &svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          &svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          &svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          &svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          &svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          &svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          &svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          svdpedidoriglin.codopemodif,sizeof(svdpedidoriglin.codopemodif),V10CADENA,
                          &svdpedidoriglin.fecmodif,sizeof(svdpedidoriglin.fecmodif),V10LONG,
                          svdpedidoriglin.horamodif,sizeof(svdpedidoriglin.horamodif),V10CADENA,
                          svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          &svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          &svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpolrowidlock,"MIROWID",svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_updapolstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdupdapolstatus=abrecursordebug(UPDAPOLSTATUS,1280);
    bindtodo(vdupdapolstatus,"STATUS",&svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          "MIROWID",svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_updapolvdpedidoriglin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdupdapolvdpedidoriglin=abrecursordebug(UPDAPOL,1280);
    bindtodo(vdupdapolvdpedidoriglin,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQLINEA",&svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          "SEQLINORIG",&svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          "CODART",svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          "CODLOT",svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          "CADUCI",svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          "CANTPEDIDA",&svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          "UNIDADESHOST",svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          "BACKORDER",svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          "CODAGRUPA",svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          "OPCIONPRECIO",svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          "PRECIOUNI",&svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          "UNIDADESPRECIO",svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          "DCTO",&svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          "IVA",&svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          "RECARGO",&svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          "SWTCREAVERSION",svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          "MARCASTK",svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          "NUMEROSERIE",svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          "PEDIDOHOST",svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          "MARCARPT",svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          "TIPOREDONDEO",svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          "CODCOMEN",&svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          "STATUS",&svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          "VDEXTRA",svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          "CODMAT",svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          "SEQPED",&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          "SWTDCTO",svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          "SWTPEDBON",svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          "CANTPEDIDACLI",&svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          "MIROWID",svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_inspol(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vdinspol=abrecursordebug(INSPOL,1280);
    bindtodo(vdinspol,"CODDIV",svdpedidoriglin.coddiv,sizeof(svdpedidoriglin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidoriglin.anoped,sizeof(svdpedidoriglin.anoped),V10LONG,
                          "CODPED",svdpedidoriglin.codped,sizeof(svdpedidoriglin.codped),V10CADENA,
                          "SEQLINEA",&svdpedidoriglin.seqlinea,sizeof(svdpedidoriglin.seqlinea),V10LONG,
                          "SEQLINORIG",&svdpedidoriglin.seqlinorig,sizeof(svdpedidoriglin.seqlinorig),V10LONG,
                          "CODART",svdpedidoriglin.codart,sizeof(svdpedidoriglin.codart),V10CADENA,
                          "CODLOT",svdpedidoriglin.codlot,sizeof(svdpedidoriglin.codlot),V10CADENA,
                          "CADUCI",svdpedidoriglin.caduci,sizeof(svdpedidoriglin.caduci),V10CADENA,
                          "CANTPEDIDA",&svdpedidoriglin.cantpedida,sizeof(svdpedidoriglin.cantpedida),V10DOUBLE,
                          "UNIDADESHOST",svdpedidoriglin.unidadeshost,sizeof(svdpedidoriglin.unidadeshost),V10CADENA,
                          "BACKORDER",svdpedidoriglin.backorder,sizeof(svdpedidoriglin.backorder),V10CADENA,
                          "CODAGRUPA",svdpedidoriglin.codagrupa,sizeof(svdpedidoriglin.codagrupa),V10CADENA,
                          "OPCIONPRECIO",svdpedidoriglin.opcionprecio,sizeof(svdpedidoriglin.opcionprecio),V10CADENA,
                          "PRECIOUNI",&svdpedidoriglin.preciouni,sizeof(svdpedidoriglin.preciouni),V10DOUBLE,
                          "UNIDADESPRECIO",svdpedidoriglin.unidadesprecio,sizeof(svdpedidoriglin.unidadesprecio),V10CADENA,
                          "DCTO",&svdpedidoriglin.dcto,sizeof(svdpedidoriglin.dcto),V10DOUBLE,
                          "IVA",&svdpedidoriglin.iva,sizeof(svdpedidoriglin.iva),V10DOUBLE,
                          "RECARGO",&svdpedidoriglin.recargo,sizeof(svdpedidoriglin.recargo),V10DOUBLE,
                          "SWTCREAVERSION",svdpedidoriglin.swtcreaversion,sizeof(svdpedidoriglin.swtcreaversion),V10CADENA,
                          "MARCASTK",svdpedidoriglin.marcastk,sizeof(svdpedidoriglin.marcastk),V10CADENA,
                          "NUMEROSERIE",svdpedidoriglin.numeroserie,sizeof(svdpedidoriglin.numeroserie),V10CADENA,
                          "PEDIDOHOST",svdpedidoriglin.pedidohost,sizeof(svdpedidoriglin.pedidohost),V10CADENA,
                          "MARCARPT",svdpedidoriglin.marcarpt,sizeof(svdpedidoriglin.marcarpt),V10CADENA,
                          "TIPOREDONDEO",svdpedidoriglin.tiporedondeo,sizeof(svdpedidoriglin.tiporedondeo),V10CADENA,
                          "CODCOMEN",&svdpedidoriglin.codcomen,sizeof(svdpedidoriglin.codcomen),V10LONG,
                          "STATUS",&svdpedidoriglin.status,sizeof(svdpedidoriglin.status),V10LONG,
                          "VDEXTRA",svdpedidoriglin.vdextra,sizeof(svdpedidoriglin.vdextra),V10CADENA,
                          "CODMAT",svdpedidoriglin.codmat,sizeof(svdpedidoriglin.codmat),V10CADENA,
                          "SEQPED",&svdpedidoriglin.seqped,sizeof(svdpedidoriglin.seqped),V10LONG,
                          "SWTDCTO",svdpedidoriglin.swtdcto,sizeof(svdpedidoriglin.swtdcto),V10CADENA,
                          "SWTPEDBON",svdpedidoriglin.swtpedbon,sizeof(svdpedidoriglin.swtpedbon),V10CADENA,
                          "CANTPEDIDACLI",&svdpedidoriglin.cantpedidacli,sizeof(svdpedidoriglin.cantpedidacli),V10DOUBLE,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

static void init_delpol(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidoriglin[0].numcol;nc++) dvdpedidoriglin[0].c[nc].offset-=(size_t)&svdpedidoriglin;
    vddelpol=abrecursordebug(DELPOL,1280);
    bindtodo(vddelpol,"MIROWID",svdpedidoriglin.rowid,sizeof(svdpedidoriglin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pol);
        init = 1;
    }
}

diccionario *POLdamediccionario(void)
{
     return(&dpol);
}

int POLsellinea(char *coddiv,long anoped,char *codped,long seqlinea,vdpedidoriglins *pol)
{
  int vdret;
  if (vdselpollinea==NULL) init_selpollinea();
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.coddiv,coddiv);
  svdpedidoriglin.anoped=anoped;
  strcpy(svdpedidoriglin.codped,codped);
  svdpedidoriglin.seqlinea=seqlinea;
  vdret=ejefetchcursor(vdselpollinea);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpollinea. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
    return(VD_EERRORACLE);
   }
  *pol=svdpedidoriglin;
  return(vdret);
}

int POLbuscapedido(char *coddiv,long anoped,char *codped,long seqped,vdpedidoriglins *pol)
{
  int vdret;
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.coddiv,coddiv);
  svdpedidoriglin.anoped=anoped;
  strcpy(svdpedidoriglin.codped,codped);
  svdpedidoriglin.seqped=seqped;
  if (vdselpolpedido==NULL) init_selpolpedido();
  vdret=ejefetchcursor(vdselpolpedido);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpolpedido. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int POLnextpedido(vdpedidoriglins *pol)
{
  int vdret;
  vdret=fetchcursor(vdselpolpedido);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpolpedido. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpolpedido);
  return(VD_EERRORACLE);
}

int POLbuscastatus(long status,vdpedidoriglins *pol)
{
  int vdret;
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  svdpedidoriglin.status=status;
  if (vdselpolstatus==NULL) init_selpolstatus();
  vdret=ejefetchcursor(vdselpolstatus);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpolstatus. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int POLnextstatus(vdpedidoriglins *pol)
{
  int vdret;
  vdret=fetchcursor(vdselpolstatus);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpolstatus. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpolstatus);
  return(VD_EERRORACLE);
}

int POLbuscalinpepdte(char *coddiv,long anoped,char *codped,long seqped,long status,vdpedidoriglins *pol)
{
  int vdret;
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.coddiv,coddiv);
  svdpedidoriglin.anoped=anoped;
  strcpy(svdpedidoriglin.codped,codped);
  svdpedidoriglin.seqped=seqped;
  svdpedidoriglin.status=status;
  if (vdselpollinpepdte==NULL) init_selpollinpepdte();
  vdret=ejefetchcursor(vdselpollinpepdte);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpollinpepdte. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int POLnextlinpepdte(vdpedidoriglins *pol)
{
  int vdret;
  vdret=fetchcursor(vdselpollinpepdte);
  if (vdret==0) {
     *pol=svdpedidoriglin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpollinpepdte. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpollinpepdte);
  return(VD_EERRORACLE);
}

int POLselrowid(char *mirowid,vdpedidoriglins *pol)
{
  int vdret;
  if (vdselpolrowid==NULL) init_selpolrowid();
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.rowid,mirowid);
  vdret=ejefetchcursor(vdselpolrowid);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpolrowid. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
    return(VD_EERRORACLE);
   }
  *pol=svdpedidoriglin;
  return(vdret);
}

int POLselvdpedidoriglin(char *coddiv,long anoped,char *codped,long seqlinea,long seqped,vdpedidoriglins *pol)
{
  int vdret;
  if (vdselpolvdpedidoriglin==NULL) init_selpolvdpedidoriglin();
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.coddiv,coddiv);
  svdpedidoriglin.anoped=anoped;
  strcpy(svdpedidoriglin.codped,codped);
  svdpedidoriglin.seqlinea=seqlinea;
  svdpedidoriglin.seqped=seqped;
  vdret=ejefetchcursor(vdselpolvdpedidoriglin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpolvdpedidoriglin. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
    return(VD_EERRORACLE);
   }
  *pol=svdpedidoriglin;
  return(vdret);
}

int POLlock(vdpedidoriglins *pol,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdpedidoriglin=*pol;
    if (vdselpolrowidlock==NULL) init_selpolrowidlock();
    savepoint("lockvdpedidoriglin");
    while (1) {
        vdret=ejefetchcursor(vdselpolrowidlock);
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
    vdret=vverificacampos(pol,&svdpedidoriglin,&dvdpedidoriglin[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdpedidoriglin");
    return(vdret);
}

int POLactualizastatus(vdpedidoriglins *pol,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando POLactualizastatus:  %s .  \n",POLlog(&svdpedidoriglin));
  if (vdupdapolstatus==NULL) init_updapolstatus();
  svdpedidoriglin=*pol;
  vdret=ejecutacursor(vdupdapolstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdapolstatus);
     getcurerrornombre(vdupdapolstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdapolstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int POLactualizavdpedidoriglin(vdpedidoriglins *pol,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando POLactualizavdpedidoriglin:  %s .  \n",POLlog(&svdpedidoriglin));
  if (vdupdapolvdpedidoriglin==NULL) init_updapolvdpedidoriglin();
  svdpedidoriglin=*pol;
  vdret=ejecutacursor(vdupdapolvdpedidoriglin);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdapolvdpedidoriglin);
     getcurerrornombre(vdupdapolvdpedidoriglin->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdapolvdpedidoriglin)!=1) return(VD_EERRORACLE);
  return(0);
}

int POLinsert(vdpedidoriglins *pol,int error)
{
  int vdret;
  if (!vdinspol) init_inspol();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",POLlog(&svdpedidoriglin));
  svdpedidoriglin=*pol;
  vdret=ejecutacursor(vdinspol);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinspol);
     getcurerrornombre(vdinspol->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int POLdel(vdpedidoriglins *pol,int error)
{
  int vdret;
  svdpedidoriglin=*pol;
  if (vddelpol==NULL) init_delpol();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",POLlog(&svdpedidoriglin));
  vdret=ejecutacursor(vddelpol);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelpol);
     getcurerrornombre(vddelpol->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int POLinter(vdpedidoriglins *pol)
{
  int vdret = 0;
  if (vdselpolvdpedidoriglin==NULL) init_selpolvdpedidoriglin();
  memset(&svdpedidoriglin,0,sizeof(svdpedidoriglin));
  strcpy(svdpedidoriglin.coddiv,pol->coddiv);
  svdpedidoriglin.anoped = pol->anoped;
  strcpy(svdpedidoriglin.codped,pol->codped);
  svdpedidoriglin.seqlinea = pol->seqlinea;
  svdpedidoriglin.seqped = pol->seqped;
  vdret=ejefetchcursor(vdselpolvdpedidoriglin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpolvdpedidoriglin. vdret %d. \n",POLlog(&svdpedidoriglin),vdret);
    return(VD_EERRORACLE);
  }

  *pol=svdpedidoriglin;
  return(vdret);
}

char * POLlog(vdpedidoriglins *pol)
{
    sprintf(msglogPOL, "VDPEDIDORIGLIN: coddiv %s anoped %ld codped %s seqlinea %ld seqped %ld ",pol->coddiv,pol->anoped,pol->codped,pol->seqlinea,pol->seqped);
    return(msglogPOL);
}

char * POLdebug(vdpedidoriglins *pol)
{
    debugestruct(&dpol,pol,msgdebugPOL);
    return(msgdebugPOL);
}

