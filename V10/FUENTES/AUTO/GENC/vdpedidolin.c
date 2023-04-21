// Modulo generado automaticamente a partir de VDPEDIDOLIN.DEF
//#***
//# VDPEDIDOCAB.c - Generación automática del código c para la tabla de Líneas de Pedidos                                                       
//# 
//# Propósito: Funciones de acceso a la tabla VDPEDIDOLIN
//#           
//# Autor	 : RFD
//# Revisado por: 
//# Fecha  : 06-03-2008                                              
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=PEL
//EXTRA=COMEN,V10CADENA,1025
//EXTRA=CDEMANDA,V10CADENA,10
//EXTRA=TDEMANDA,V10CADENA,10
//EXTRA=LDEMANDA,V10LONG
//
//PRIMARIA=CODDIV,ANOPED,CODPED,SEQPED,SEQLINEA
//CLAVE=LINEA,CODDIV,ANOPED,CODPED,SEQPED,SEQLINEA
//
//RECORRE=PEDIDO,CODDIV,ANOPED,CODPED,SEQPED
//RECORRE=STATUS,STATUS;
//RECORRE=PEDLINPDTE,CODDIV,ANOPED,CODPED,SEQPED,STATUS
//RECORRE=PEDLINPORDEMANDA,TDEMANDA,CDEMANDA,LDEMANDA;TABLE=VDPEDIDOCAB PEC;WHERE=PEC.CODDIV=VDPEDIDOLIN.CODDIV 
//            AND PEC.ANOPED=VDPEDIDOLIN.ANOPED 
//            AND PEC.CODPED=VDPEDIDOLIN.CODPED 
//            AND PEC.SEQPED=VDPEDIDOLIN.SEQPED 
//            AND PEC.CODDEMANDA=:CDEMANDA  
//            AND PEC.TIPODEMANDA=:TDEMANDA 
//            AND VDPEDIDOLIN.SEQLINEA=:LDEMANDA;
//
//
//UPDATE=STATUS,STATUS;
//UPDATE=SEQPED,SEQPED;
//
//DELETE
//INSERT
//LOCK

#include "vd.h"
#define SELPELLINEA "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN"\
        " WHERE "\
               " VDPEDIDOLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDOLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDOLIN.CODPED=:CODPED "\
               " AND VDPEDIDOLIN.SEQPED=:SEQPED "\
               " AND VDPEDIDOLIN.SEQLINEA=:SEQLINEA "
static v10cursors *vdselpellinea;

#define SELPELPEDIDO "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN"\
        " WHERE "\
               " VDPEDIDOLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDOLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDOLIN.CODPED=:CODPED "\
               " AND VDPEDIDOLIN.SEQPED=:SEQPED "
static v10cursors *vdselpelpedido;

#define SELPELSTATUS "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN"\
        " WHERE "\
               " VDPEDIDOLIN.STATUS=:STATUS "
static v10cursors *vdselpelstatus;

#define SELPELPEDLINPDTE "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN"\
        " WHERE "\
               " VDPEDIDOLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDOLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDOLIN.CODPED=:CODPED "\
               " AND VDPEDIDOLIN.SEQPED=:SEQPED "\
               " AND VDPEDIDOLIN.STATUS=:STATUS "
static v10cursors *vdselpelpedlinpdte;

#define SELPELPEDLINPORDEMANDA "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN ,VDPEDIDOCAB PEC"\
        " WHERE "\
              " PEC.CODDIV=VDPEDIDOLIN.CODDIV  AND PEC.ANOPED=VDPEDIDOLIN.ANOPED  AND PEC.CODPED=VDPEDIDOLIN.CODPED  AND PEC.SEQPED=VDPEDIDOLIN.SEQPED  AND PEC.CODDEMANDA=:CDEMANDA   AND PEC.TIPODEMANDA=:TDEMANDA  AND VDPEDIDOLIN.SEQLINEA=:LDEMANDA "
static v10cursors *vdselpelpedlinpordemanda;

#define SELPELVDPEDIDOLIN "SELECT VDPEDIDOLIN.ROWID,VDPEDIDOLIN.CODDIV,VDPEDIDOLIN.ANOPED, "\
                    " VDPEDIDOLIN.CODPED,VDPEDIDOLIN.SEQPED,VDPEDIDOLIN.SEQLINEA, "\
                    " VDPEDIDOLIN.SEQLINORIG,VDPEDIDOLIN.CODART,VDPEDIDOLIN.CODLOT, "\
                    " VDPEDIDOLIN.CADUCI,VDPEDIDOLIN.CANTPEDIDA,VDPEDIDOLIN.UNIDADESHOST, "\
                    " VDPEDIDOLIN.CANTASERVIR,VDPEDIDOLIN.CANTSERVIDA,VDPEDIDOLIN.BACKORDER, "\
                    " VDPEDIDOLIN.CODAGRUPA,VDPEDIDOLIN.OPCIONPRECIO,VDPEDIDOLIN.PRECIOUNI, "\
                    " VDPEDIDOLIN.UNIDADESPRECIO,VDPEDIDOLIN.DCTO,VDPEDIDOLIN.IVA, "\
                    " VDPEDIDOLIN.RECARGO,VDPEDIDOLIN.SWTCREAVERSION,VDPEDIDOLIN.MARCASTK, "\
                    " VDPEDIDOLIN.NUMEROSERIE,VDPEDIDOLIN.PEDIDOHOST,VDPEDIDOLIN.MARCARPT, "\
                    " VDPEDIDOLIN.TIPOREDONDEO,VDPEDIDOLIN.CODCOMEN,VDPEDIDOLIN.STATUS, "\
                    " VDPEDIDOLIN.VDEXTRA,VDPEDIDOLIN.CODOPEMODIF,VDPEDIDOLIN.FECMODIF, "\
                    " VDPEDIDOLIN.HORAMODIF,VDPEDIDOLIN.CODMAT,VDPEDIDOLIN.MANIPESPE, "\
                    " VDPEDIDOLIN.SECFACT,VDPEDIDOLIN.TIMBRE,VDPEDIDOLIN.FICHERO, "\
                    " VDPEDIDOLIN.FACTURA,VDPEDIDOLIN.FICHEROREMI,VDPEDIDOLIN.IMPFACT, "\
                    " VDPEDIDOLIN.SWTDCTO,VDPEDIDOLIN.SWTPEDBON,VDPEDIDOLIN.CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN"\
        " WHERE "\
               " VDPEDIDOLIN.CODDIV=:CODDIV "\
               " AND VDPEDIDOLIN.ANOPED=:ANOPED "\
               " AND VDPEDIDOLIN.CODPED=:CODPED "\
               " AND VDPEDIDOLIN.SEQPED=:SEQPED "\
               " AND VDPEDIDOLIN.SEQLINEA=:SEQLINEA "
static v10cursors *vdselpelvdpedidolin;

#define SELPELROWIDLOCK "SELECT ROWID,CODDIV,ANOPED,CODPED,SEQPED,SEQLINEA,SEQLINORIG, "\
                    " CODART,CODLOT,CADUCI,CANTPEDIDA,UNIDADESHOST,CANTASERVIR,CANTSERVIDA, "\
                    " BACKORDER,CODAGRUPA,OPCIONPRECIO,PRECIOUNI,UNIDADESPRECIO,DCTO,IVA, "\
                    " RECARGO,SWTCREAVERSION,MARCASTK,NUMEROSERIE,PEDIDOHOST,MARCARPT,TIPOREDONDEO, "\
                    " CODCOMEN,STATUS,VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF,CODMAT, "\
                    " MANIPESPE,SECFACT,TIMBRE,FICHERO,FACTURA,FICHEROREMI,IMPFACT, "\
                    " SWTDCTO,SWTPEDBON,CANTPEDIDACLI "\
        " FROM VDPEDIDOLIN "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselpelrowidlock;

#define UPDAPELSTATUS "UPDATE VDPEDIDOLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdapelstatus;

#define UPDAPELSEQPED "UPDATE VDPEDIDOLIN SET  FECMODIF=VD.FECHASYS(),  CODOPEMODIF=VDUSER.GETUSER(),  "\
               " SEQPED=:SEQPED  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdapelseqped;

#define INSPEL "INSERT INTO VDPEDIDOLIN (CODDIV,ANOPED,CODPED,SEQPED,SEQLINEA,SEQLINORIG, "\
                    " CODART,CODLOT,CADUCI,CANTPEDIDA,UNIDADESHOST,CANTASERVIR,CANTSERVIDA, "\
                    " BACKORDER,CODAGRUPA,OPCIONPRECIO,PRECIOUNI,UNIDADESPRECIO,DCTO,IVA, "\
                    " RECARGO,SWTCREAVERSION,MARCASTK,NUMEROSERIE,PEDIDOHOST,MARCARPT,TIPOREDONDEO, "\
                    " CODCOMEN,STATUS,VDEXTRA,CODOPEMODIF,FECMODIF,HORAMODIF,CODMAT, "\
                    " MANIPESPE,SECFACT,TIMBRE,FICHERO,FACTURA,FICHEROREMI,IMPFACT, "\
                    " SWTDCTO,SWTPEDBON,CANTPEDIDACLI "\
       " ) VALUES ( "\
                    " :CODDIV,:ANOPED,:CODPED,:SEQPED,:SEQLINEA,:SEQLINORIG, "\
                    " :CODART,:CODLOT,:CADUCI,:CANTPEDIDA,:UNIDADESHOST,:CANTASERVIR,:CANTSERVIDA, "\
                    " :BACKORDER,:CODAGRUPA,:OPCIONPRECIO,:PRECIOUNI,:UNIDADESPRECIO,:DCTO,:IVA, "\
                    " :RECARGO,:SWTCREAVERSION,:MARCASTK,:NUMEROSERIE,:PEDIDOHOST,:MARCARPT,:TIPOREDONDEO, "\
                    " :CODCOMEN,:STATUS,:VDEXTRA,VDUSER.GETUSER(),VD.FECHASYS(),VD.HORASYS(),:CODMAT, "\
                    " :MANIPESPE,:SECFACT,:TIMBRE,:FICHERO,:FACTURA,:FICHEROREMI,:IMPFACT, "\
                    " :SWTDCTO,:SWTPEDBON,:CANTPEDIDACLI) "
static v10cursors *vdinspel;

#define DELPEL "DELETE VDPEDIDOLIN WHERE ROWID=:MIROWID "
static v10cursors *vddelpel;

static vdpedidolins svdpedidolin;

static diccols colvdpedidolin[]={
	{"ROWID",V10CADENA,(size_t)&svdpedidolin.rowid,sizeof(svdpedidolin.rowid)},
	{"CODDIV",V10CADENA,(size_t)&svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv)},
	{"ANOPED",V10LONG,(size_t)&svdpedidolin.anoped,sizeof(svdpedidolin.anoped)},
	{"CODPED",V10CADENA,(size_t)&svdpedidolin.codped,sizeof(svdpedidolin.codped)},
	{"SEQPED",V10LONG,(size_t)&svdpedidolin.seqped,sizeof(svdpedidolin.seqped)},
	{"SEQLINEA",V10LONG,(size_t)&svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea)},
	{"SEQLINORIG",V10LONG,(size_t)&svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig)},
	{"CODART",V10CADENA,(size_t)&svdpedidolin.codart,sizeof(svdpedidolin.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdpedidolin.codlot,sizeof(svdpedidolin.codlot)},
	{"CADUCI",V10CADENA,(size_t)&svdpedidolin.caduci,sizeof(svdpedidolin.caduci)},
	{"CANTPEDIDA",V10DOUBLE,(size_t)&svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida)},
	{"UNIDADESHOST",V10CADENA,(size_t)&svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost)},
	{"CANTASERVIR",V10DOUBLE,(size_t)&svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir)},
	{"CANTSERVIDA",V10DOUBLE,(size_t)&svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida)},
	{"BACKORDER",V10CADENA,(size_t)&svdpedidolin.backorder,sizeof(svdpedidolin.backorder)},
	{"CODAGRUPA",V10CADENA,(size_t)&svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa)},
	{"OPCIONPRECIO",V10CADENA,(size_t)&svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni)},
	{"UNIDADESPRECIO",V10CADENA,(size_t)&svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio)},
	{"DCTO",V10DOUBLE,(size_t)&svdpedidolin.dcto,sizeof(svdpedidolin.dcto)},
	{"IVA",V10DOUBLE,(size_t)&svdpedidolin.iva,sizeof(svdpedidolin.iva)},
	{"RECARGO",V10DOUBLE,(size_t)&svdpedidolin.recargo,sizeof(svdpedidolin.recargo)},
	{"SWTCREAVERSION",V10CADENA,(size_t)&svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion)},
	{"MARCASTK",V10CADENA,(size_t)&svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie)},
	{"PEDIDOHOST",V10CADENA,(size_t)&svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost)},
	{"MARCARPT",V10CADENA,(size_t)&svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt)},
	{"TIPOREDONDEO",V10CADENA,(size_t)&svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo)},
	{"CODCOMEN",V10LONG,(size_t)&svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen)},
	{"STATUS",V10LONG,(size_t)&svdpedidolin.status,sizeof(svdpedidolin.status)},
	{"VDEXTRA",V10CADENA,(size_t)&svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif)},
	{"CODMAT",V10CADENA,(size_t)&svdpedidolin.codmat,sizeof(svdpedidolin.codmat)},
	{"MANIPESPE",V10CADENA,(size_t)&svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe)},
	{"SECFACT",V10LONG,(size_t)&svdpedidolin.secfact,sizeof(svdpedidolin.secfact)},
	{"TIMBRE",V10CADENA,(size_t)&svdpedidolin.timbre,sizeof(svdpedidolin.timbre)},
	{"FICHERO",V10CADENA,(size_t)&svdpedidolin.fichero,sizeof(svdpedidolin.fichero)},
	{"FACTURA",V10CADENA,(size_t)&svdpedidolin.factura,sizeof(svdpedidolin.factura)},
	{"FICHEROREMI",V10CADENA,(size_t)&svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi)},
	{"IMPFACT",V10DOUBLE,(size_t)&svdpedidolin.impfact,sizeof(svdpedidolin.impfact)},
	{"SWTDCTO",V10CADENA,(size_t)&svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto)},
	{"SWTPEDBON",V10CADENA,(size_t)&svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon)},
	{"CANTPEDIDACLI",V10DOUBLE,(size_t)&svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli)},
	{"COMEN",V10CADENA,(size_t)&svdpedidolin.comen,sizeof(svdpedidolin.comen)},
	{"CDEMANDA",V10CADENA,(size_t)&svdpedidolin.cdemanda,sizeof(svdpedidolin.cdemanda)},
	{"TDEMANDA",V10CADENA,(size_t)&svdpedidolin.tdemanda,sizeof(svdpedidolin.tdemanda)},
	{"LDEMANDA",V10LONG,(size_t)&svdpedidolin.ldemanda,sizeof(svdpedidolin.ldemanda)}
	};
static diccionarios dvdpedidolin[]={
    {colvdpedidolin,49}
};
diccionario dpel={dvdpedidolin,1};

static char msglogPEL[LCADENA];
static char msgdebugPEL[LCADENABIG];
static int init=0;


static void fin_vd_pel(void)
{
if (vdselpellinea) {
    liberacursor(vdselpellinea);
    vdselpellinea = NULL;
}
if (vdselpelpedido) {
    liberacursor(vdselpelpedido);
    vdselpelpedido = NULL;
}
if (vdselpelstatus) {
    liberacursor(vdselpelstatus);
    vdselpelstatus = NULL;
}
if (vdselpelpedlinpdte) {
    liberacursor(vdselpelpedlinpdte);
    vdselpelpedlinpdte = NULL;
}
if (vdselpelpedlinpordemanda) {
    liberacursor(vdselpelpedlinpordemanda);
    vdselpelpedlinpordemanda = NULL;
}
if (vdselpelvdpedidolin) {
    liberacursor(vdselpelvdpedidolin);
    vdselpelvdpedidolin = NULL;
}
if (vdselpelrowidlock) {
    liberacursor(vdselpelrowidlock);
    vdselpelrowidlock = NULL;
}
if (vdupdapelstatus) {
    liberacursor(vdupdapelstatus);
    vdupdapelstatus = NULL;
}
if (vdupdapelseqped) {
    liberacursor(vdupdapelseqped);
    vdupdapelseqped = NULL;
}
if (vdinspel != NULL) {
    liberacursor(vdinspel);
    vdinspel = NULL;
}
if (vddelpel != NULL) {
    liberacursor(vddelpel);
    vddelpel = NULL;
}
}
static void init_selpellinea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpellinea=abrecursordebug(SELPELLINEA,1280);
    definetodo(vdselpellinea,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpellinea,"CODDIV",svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          "CODPED",svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          "SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          "SEQLINEA",&svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelpedido(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelpedido=abrecursordebug(SELPELPEDIDO,1280);
    definetodo(vdselpelpedido,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelpedido,"CODDIV",svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          "CODPED",svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          "SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelstatus=abrecursordebug(SELPELSTATUS,1280);
    definetodo(vdselpelstatus,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelstatus,"STATUS",&svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelpedlinpdte(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelpedlinpdte=abrecursordebug(SELPELPEDLINPDTE,1280);
    definetodo(vdselpelpedlinpdte,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelpedlinpdte,"CODDIV",svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          "CODPED",svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          "SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          "STATUS",&svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelpedlinpordemanda(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelpedlinpordemanda=abrecursordebug(SELPELPEDLINPORDEMANDA,1280);
    definetodo(vdselpelpedlinpordemanda,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelpedlinpordemanda,"TDEMANDA",svdpedidolin.tdemanda,sizeof(svdpedidolin.tdemanda),V10CADENA,
                          "CDEMANDA",svdpedidolin.cdemanda,sizeof(svdpedidolin.cdemanda),V10CADENA,
                          "LDEMANDA",&svdpedidolin.ldemanda,sizeof(svdpedidolin.ldemanda),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelvdpedidolin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelvdpedidolin=abrecursordebug(SELPELVDPEDIDOLIN,1280);
    definetodo(vdselpelvdpedidolin,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelvdpedidolin,"CODDIV",svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          "CODPED",svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          "SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          "SEQLINEA",&svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_selpelrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdselpelrowidlock=abrecursordebug(SELPELROWIDLOCK,1280);
    definetodo(vdselpelrowidlock,svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          &svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          &svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          &svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          &svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          &svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          &svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          &svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          &svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          &svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          &svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          &svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          &svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          &svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          svdpedidolin.codopemodif,sizeof(svdpedidolin.codopemodif),V10CADENA,
                          &svdpedidolin.fecmodif,sizeof(svdpedidolin.fecmodif),V10LONG,
                          svdpedidolin.horamodif,sizeof(svdpedidolin.horamodif),V10CADENA,
                          svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          &svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          &svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          &svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    bindtodo(vdselpelrowidlock,"MIROWID",svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_updapelstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdupdapelstatus=abrecursordebug(UPDAPELSTATUS,1280);
    bindtodo(vdupdapelstatus,"STATUS",&svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          "MIROWID",svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_updapelseqped(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdupdapelseqped=abrecursordebug(UPDAPELSEQPED,1280);
    bindtodo(vdupdapelseqped,"SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          "MIROWID",svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_inspel(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vdinspel=abrecursordebug(INSPEL,1280);
    bindtodo(vdinspel,"CODDIV",svdpedidolin.coddiv,sizeof(svdpedidolin.coddiv),V10CADENA,
                          "ANOPED",&svdpedidolin.anoped,sizeof(svdpedidolin.anoped),V10LONG,
                          "CODPED",svdpedidolin.codped,sizeof(svdpedidolin.codped),V10CADENA,
                          "SEQPED",&svdpedidolin.seqped,sizeof(svdpedidolin.seqped),V10LONG,
                          "SEQLINEA",&svdpedidolin.seqlinea,sizeof(svdpedidolin.seqlinea),V10LONG,
                          "SEQLINORIG",&svdpedidolin.seqlinorig,sizeof(svdpedidolin.seqlinorig),V10LONG,
                          "CODART",svdpedidolin.codart,sizeof(svdpedidolin.codart),V10CADENA,
                          "CODLOT",svdpedidolin.codlot,sizeof(svdpedidolin.codlot),V10CADENA,
                          "CADUCI",svdpedidolin.caduci,sizeof(svdpedidolin.caduci),V10CADENA,
                          "CANTPEDIDA",&svdpedidolin.cantpedida,sizeof(svdpedidolin.cantpedida),V10DOUBLE,
                          "UNIDADESHOST",svdpedidolin.unidadeshost,sizeof(svdpedidolin.unidadeshost),V10CADENA,
                          "CANTASERVIR",&svdpedidolin.cantaservir,sizeof(svdpedidolin.cantaservir),V10DOUBLE,
                          "CANTSERVIDA",&svdpedidolin.cantservida,sizeof(svdpedidolin.cantservida),V10DOUBLE,
                          "BACKORDER",svdpedidolin.backorder,sizeof(svdpedidolin.backorder),V10CADENA,
                          "CODAGRUPA",svdpedidolin.codagrupa,sizeof(svdpedidolin.codagrupa),V10CADENA,
                          "OPCIONPRECIO",svdpedidolin.opcionprecio,sizeof(svdpedidolin.opcionprecio),V10CADENA,
                          "PRECIOUNI",&svdpedidolin.preciouni,sizeof(svdpedidolin.preciouni),V10DOUBLE,
                          "UNIDADESPRECIO",svdpedidolin.unidadesprecio,sizeof(svdpedidolin.unidadesprecio),V10CADENA,
                          "DCTO",&svdpedidolin.dcto,sizeof(svdpedidolin.dcto),V10DOUBLE,
                          "IVA",&svdpedidolin.iva,sizeof(svdpedidolin.iva),V10DOUBLE,
                          "RECARGO",&svdpedidolin.recargo,sizeof(svdpedidolin.recargo),V10DOUBLE,
                          "SWTCREAVERSION",svdpedidolin.swtcreaversion,sizeof(svdpedidolin.swtcreaversion),V10CADENA,
                          "MARCASTK",svdpedidolin.marcastk,sizeof(svdpedidolin.marcastk),V10CADENA,
                          "NUMEROSERIE",svdpedidolin.numeroserie,sizeof(svdpedidolin.numeroserie),V10CADENA,
                          "PEDIDOHOST",svdpedidolin.pedidohost,sizeof(svdpedidolin.pedidohost),V10CADENA,
                          "MARCARPT",svdpedidolin.marcarpt,sizeof(svdpedidolin.marcarpt),V10CADENA,
                          "TIPOREDONDEO",svdpedidolin.tiporedondeo,sizeof(svdpedidolin.tiporedondeo),V10CADENA,
                          "CODCOMEN",&svdpedidolin.codcomen,sizeof(svdpedidolin.codcomen),V10LONG,
                          "STATUS",&svdpedidolin.status,sizeof(svdpedidolin.status),V10LONG,
                          "VDEXTRA",svdpedidolin.vdextra,sizeof(svdpedidolin.vdextra),V10CADENA,
                          "CODMAT",svdpedidolin.codmat,sizeof(svdpedidolin.codmat),V10CADENA,
                          "MANIPESPE",svdpedidolin.manipespe,sizeof(svdpedidolin.manipespe),V10CADENA,
                          "SECFACT",&svdpedidolin.secfact,sizeof(svdpedidolin.secfact),V10LONG,
                          "TIMBRE",svdpedidolin.timbre,sizeof(svdpedidolin.timbre),V10CADENA,
                          "FICHERO",svdpedidolin.fichero,sizeof(svdpedidolin.fichero),V10CADENA,
                          "FACTURA",svdpedidolin.factura,sizeof(svdpedidolin.factura),V10CADENA,
                          "FICHEROREMI",svdpedidolin.ficheroremi,sizeof(svdpedidolin.ficheroremi),V10CADENA,
                          "IMPFACT",&svdpedidolin.impfact,sizeof(svdpedidolin.impfact),V10DOUBLE,
                          "SWTDCTO",svdpedidolin.swtdcto,sizeof(svdpedidolin.swtdcto),V10CADENA,
                          "SWTPEDBON",svdpedidolin.swtpedbon,sizeof(svdpedidolin.swtpedbon),V10CADENA,
                          "CANTPEDIDACLI",&svdpedidolin.cantpedidacli,sizeof(svdpedidolin.cantpedidacli),V10DOUBLE,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

static void init_delpel(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdpedidolin[0].numcol;nc++) dvdpedidolin[0].c[nc].offset-=(size_t)&svdpedidolin;
    vddelpel=abrecursordebug(DELPEL,1280);
    bindtodo(vddelpel,"MIROWID",svdpedidolin.rowid,sizeof(svdpedidolin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_pel);
        init = 1;
    }
}

diccionario *PELdamediccionario(void)
{
     return(&dpel);
}

int PELsellinea(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,vdpedidolins *pel)
{
  int vdret;
  if (vdselpellinea==NULL) init_selpellinea();
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  strcpy(svdpedidolin.coddiv,coddiv);
  svdpedidolin.anoped=anoped;
  strcpy(svdpedidolin.codped,codped);
  svdpedidolin.seqped=seqped;
  svdpedidolin.seqlinea=seqlinea;
  vdret=ejefetchcursor(vdselpellinea);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpellinea. vdret %d. \n",PELlog(&svdpedidolin),vdret);
    return(VD_EERRORACLE);
   }
  *pel=svdpedidolin;
  return(vdret);
}

int PELbuscapedido(char *coddiv,long anoped,char *codped,long seqped,vdpedidolins *pel)
{
  int vdret;
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  strcpy(svdpedidolin.coddiv,coddiv);
  svdpedidolin.anoped=anoped;
  strcpy(svdpedidolin.codped,codped);
  svdpedidolin.seqped=seqped;
  if (vdselpelpedido==NULL) init_selpelpedido();
  vdret=ejefetchcursor(vdselpelpedido);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpelpedido. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PELnextpedido(vdpedidolins *pel)
{
  int vdret;
  vdret=fetchcursor(vdselpelpedido);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpelpedido. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpelpedido);
  return(VD_EERRORACLE);
}

int PELbuscastatus(long status,vdpedidolins *pel)
{
  int vdret;
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  svdpedidolin.status=status;
  if (vdselpelstatus==NULL) init_selpelstatus();
  vdret=ejefetchcursor(vdselpelstatus);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpelstatus. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PELnextstatus(vdpedidolins *pel)
{
  int vdret;
  vdret=fetchcursor(vdselpelstatus);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpelstatus. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpelstatus);
  return(VD_EERRORACLE);
}

int PELbuscapedlinpdte(char *coddiv,long anoped,char *codped,long seqped,long status,vdpedidolins *pel)
{
  int vdret;
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  strcpy(svdpedidolin.coddiv,coddiv);
  svdpedidolin.anoped=anoped;
  strcpy(svdpedidolin.codped,codped);
  svdpedidolin.seqped=seqped;
  svdpedidolin.status=status;
  if (vdselpelpedlinpdte==NULL) init_selpelpedlinpdte();
  vdret=ejefetchcursor(vdselpelpedlinpdte);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpelpedlinpdte. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PELnextpedlinpdte(vdpedidolins *pel)
{
  int vdret;
  vdret=fetchcursor(vdselpelpedlinpdte);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpelpedlinpdte. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpelpedlinpdte);
  return(VD_EERRORACLE);
}

int PELbuscapedlinpordemanda(char *tdemanda,char *cdemanda,long ldemanda,vdpedidolins *pel)
{
  int vdret;
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  strcpy(svdpedidolin.tdemanda,tdemanda);
  strcpy(svdpedidolin.cdemanda,cdemanda);
  svdpedidolin.ldemanda=ldemanda;
  if (vdselpelpedlinpordemanda==NULL) init_selpelpedlinpordemanda();
  vdret=ejefetchcursor(vdselpelpedlinpordemanda);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselpelpedlinpordemanda. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int PELnextpedlinpordemanda(vdpedidolins *pel)
{
  int vdret;
  vdret=fetchcursor(vdselpelpedlinpordemanda);
  if (vdret==0) {
     *pel=svdpedidolin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselpelpedlinpordemanda. vdret %d. \n",PELlog(&svdpedidolin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselpelpedlinpordemanda);
  return(VD_EERRORACLE);
}

int PELselvdpedidolin(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,vdpedidolins *pel)
{
  int vdret;
  if (vdselpelvdpedidolin==NULL) init_selpelvdpedidolin();
  memset(&svdpedidolin,0,sizeof(svdpedidolin));
  strcpy(svdpedidolin.coddiv,coddiv);
  svdpedidolin.anoped=anoped;
  strcpy(svdpedidolin.codped,codped);
  svdpedidolin.seqped=seqped;
  svdpedidolin.seqlinea=seqlinea;
  vdret=ejefetchcursor(vdselpelvdpedidolin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselpelvdpedidolin. vdret %d. \n",PELlog(&svdpedidolin),vdret);
    return(VD_EERRORACLE);
   }
  *pel=svdpedidolin;
  return(vdret);
}

int PELlock(vdpedidolins *pel,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdpedidolin=*pel;
    if (vdselpelrowidlock==NULL) init_selpelrowidlock();
    savepoint("lockvdpedidolin");
    while (1) {
        vdret=ejefetchcursor(vdselpelrowidlock);
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
    vdret=vverificacampos(pel,&svdpedidolin,&dvdpedidolin[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdpedidolin");
    return(vdret);
}

int PELactualizastatus(vdpedidolins *pel,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando PELactualizastatus:  %s .  \n",PELlog(&svdpedidolin));
  if (vdupdapelstatus==NULL) init_updapelstatus();
  svdpedidolin=*pel;
  vdret=ejecutacursor(vdupdapelstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdapelstatus);
     getcurerrornombre(vdupdapelstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdapelstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int PELactualizaseqped(vdpedidolins *pel,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando PELactualizaseqped:  %s .  \n",PELlog(&svdpedidolin));
  if (vdupdapelseqped==NULL) init_updapelseqped();
  svdpedidolin=*pel;
  vdret=ejecutacursor(vdupdapelseqped);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdapelseqped);
     getcurerrornombre(vdupdapelseqped->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdapelseqped)!=1) return(VD_EERRORACLE);
  return(0);
}

int PELinsert(vdpedidolins *pel,int error)
{
  int vdret;
  if (!vdinspel) init_inspel();
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",PELlog(&svdpedidolin));
  svdpedidolin=*pel;
  vdret=ejecutacursor(vdinspel);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinspel);
     getcurerrornombre(vdinspel->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int PELdel(vdpedidolins *pel,int error)
{
  int vdret;
  svdpedidolin=*pel;
  if (vddelpel==NULL) init_delpel();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",PELlog(&svdpedidolin));
  vdret=ejecutacursor(vddelpel);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelpel);
     getcurerrornombre(vddelpel->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * PELlog(vdpedidolins *pel)
{
    sprintf(msglogPEL, "VDPEDIDOLIN: coddiv %s anoped %ld codped %s seqped %ld seqlinea %ld ",pel->coddiv,pel->anoped,pel->codped,pel->seqped,pel->seqlinea);
    return(msglogPEL);
}

char * PELdebug(vdpedidolins *pel)
{
    debugestruct(&dpel,pel,msgdebugPEL);
    return(msgdebugPEL);
}

