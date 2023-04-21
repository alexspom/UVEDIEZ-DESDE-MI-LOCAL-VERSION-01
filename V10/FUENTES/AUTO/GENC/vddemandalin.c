// Modulo generado automaticamente a partir de VDDEMANDALIN.DEF
//#***
//# VDDEMANDACAB.c - Generación automática del código c para la tabla de Líneas de Demandas                                                      
//# 
//# Propósito: Funciones de acceso a la tabla VDDEMANDALIN
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 7-03-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=DEML
//EXTRA=COMENDEML,V10CADENA,1024
//EXTRA=RESERVADO,V10DOUBLE
//
//RECORRE=DEMANDASTATUS,TIPODEMANDA,CODDEMANDA,STATUS;
//RECORRE=STATUS,STATUS;
//
//RECORRE=LINEASPENDIENTES;WHERE= CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA AND STATUS< "CSTDELRESERVADA";
//
//UPDATE=STATUS,STATUS;
//UPDATE=FECHAINICIO,FECINI,HORAINI;
//UPDATE=FECHAFINAL,FECFIN,HORAFIN;
//
//LOCK

#include "vd.h"
#define SELDEMLDEMANDASTATUS "SELECT VDDEMANDALIN.ROWID,VDDEMANDALIN.TIPODEMANDA,VDDEMANDALIN.CODDEMANDA, "\
                    " VDDEMANDALIN.LINDEMANDA,VDDEMANDALIN.CLAVEEXT,VDDEMANDALIN.CODART, "\
                    " VDDEMANDALIN.CODLOT,VDDEMANDALIN.UNIEMB,VDDEMANDALIN.TIPOEMBA, "\
                    " VDDEMANDALIN.MARCASTK,VDDEMANDALIN.MARCASTKORIGEN,VDDEMANDALIN.BLOQUEOS, "\
                    " VDDEMANDALIN.NUMEROSERIE,VDDEMANDALIN.CODMAT,VDDEMANDALIN.BULTO, "\
                    " VDDEMANDALIN.CODRECEP,VDDEMANDALIN.PRECIOUNI,VDDEMANDALIN.BACKORDER, "\
                    " VDDEMANDALIN.UNIAGRUPA,VDDEMANDALIN.TIPOREDONDEO,VDDEMANDALIN.ORDENRESERVA, "\
                    " VDDEMANDALIN.ORDENRESERVAUBI,VDDEMANDALIN.CODUBIORI,VDDEMANDALIN.CODAREAORI, "\
                    " VDDEMANDALIN.CODUBIDEST,VDDEMANDALIN.CODAREADEST,VDDEMANDALIN.CANTIDAD, "\
                    " VDDEMANDALIN.STATUS,VDDEMANDALIN.CODOPEINSERT,VDDEMANDALIN.FECINSERT, "\
                    " VDDEMANDALIN.HORAINSERT,VDDEMANDALIN.FECINI,VDDEMANDALIN.HORAINI, "\
                    " VDDEMANDALIN.FECFIN,VDDEMANDALIN.HORAFIN,VDDEMANDALIN.VDEXTRA, "\
                    " VDDEMANDALIN.CODCOMEN,VDDEMANDALIN.CODOPEMODIF,VDDEMANDALIN.FECMODIF, "\
                    " VDDEMANDALIN.HORAMODIF,VDDEMANDALIN.PEDIDOHOST "\
        " FROM VDDEMANDALIN"\
        " WHERE "\
               " VDDEMANDALIN.TIPODEMANDA=:TIPODEMANDA "\
               " AND VDDEMANDALIN.CODDEMANDA=:CODDEMANDA "\
               " AND VDDEMANDALIN.STATUS=:STATUS "
static v10cursors *vdseldemldemandastatus;

#define SELDEMLSTATUS "SELECT VDDEMANDALIN.ROWID,VDDEMANDALIN.TIPODEMANDA,VDDEMANDALIN.CODDEMANDA, "\
                    " VDDEMANDALIN.LINDEMANDA,VDDEMANDALIN.CLAVEEXT,VDDEMANDALIN.CODART, "\
                    " VDDEMANDALIN.CODLOT,VDDEMANDALIN.UNIEMB,VDDEMANDALIN.TIPOEMBA, "\
                    " VDDEMANDALIN.MARCASTK,VDDEMANDALIN.MARCASTKORIGEN,VDDEMANDALIN.BLOQUEOS, "\
                    " VDDEMANDALIN.NUMEROSERIE,VDDEMANDALIN.CODMAT,VDDEMANDALIN.BULTO, "\
                    " VDDEMANDALIN.CODRECEP,VDDEMANDALIN.PRECIOUNI,VDDEMANDALIN.BACKORDER, "\
                    " VDDEMANDALIN.UNIAGRUPA,VDDEMANDALIN.TIPOREDONDEO,VDDEMANDALIN.ORDENRESERVA, "\
                    " VDDEMANDALIN.ORDENRESERVAUBI,VDDEMANDALIN.CODUBIORI,VDDEMANDALIN.CODAREAORI, "\
                    " VDDEMANDALIN.CODUBIDEST,VDDEMANDALIN.CODAREADEST,VDDEMANDALIN.CANTIDAD, "\
                    " VDDEMANDALIN.STATUS,VDDEMANDALIN.CODOPEINSERT,VDDEMANDALIN.FECINSERT, "\
                    " VDDEMANDALIN.HORAINSERT,VDDEMANDALIN.FECINI,VDDEMANDALIN.HORAINI, "\
                    " VDDEMANDALIN.FECFIN,VDDEMANDALIN.HORAFIN,VDDEMANDALIN.VDEXTRA, "\
                    " VDDEMANDALIN.CODCOMEN,VDDEMANDALIN.CODOPEMODIF,VDDEMANDALIN.FECMODIF, "\
                    " VDDEMANDALIN.HORAMODIF,VDDEMANDALIN.PEDIDOHOST "\
        " FROM VDDEMANDALIN"\
        " WHERE "\
               " VDDEMANDALIN.STATUS=:STATUS "
static v10cursors *vdseldemlstatus;

#define SELDEMLLINEASPENDIENTES "SELECT VDDEMANDALIN.ROWID,VDDEMANDALIN.TIPODEMANDA,VDDEMANDALIN.CODDEMANDA, "\
                    " VDDEMANDALIN.LINDEMANDA,VDDEMANDALIN.CLAVEEXT,VDDEMANDALIN.CODART, "\
                    " VDDEMANDALIN.CODLOT,VDDEMANDALIN.UNIEMB,VDDEMANDALIN.TIPOEMBA, "\
                    " VDDEMANDALIN.MARCASTK,VDDEMANDALIN.MARCASTKORIGEN,VDDEMANDALIN.BLOQUEOS, "\
                    " VDDEMANDALIN.NUMEROSERIE,VDDEMANDALIN.CODMAT,VDDEMANDALIN.BULTO, "\
                    " VDDEMANDALIN.CODRECEP,VDDEMANDALIN.PRECIOUNI,VDDEMANDALIN.BACKORDER, "\
                    " VDDEMANDALIN.UNIAGRUPA,VDDEMANDALIN.TIPOREDONDEO,VDDEMANDALIN.ORDENRESERVA, "\
                    " VDDEMANDALIN.ORDENRESERVAUBI,VDDEMANDALIN.CODUBIORI,VDDEMANDALIN.CODAREAORI, "\
                    " VDDEMANDALIN.CODUBIDEST,VDDEMANDALIN.CODAREADEST,VDDEMANDALIN.CANTIDAD, "\
                    " VDDEMANDALIN.STATUS,VDDEMANDALIN.CODOPEINSERT,VDDEMANDALIN.FECINSERT, "\
                    " VDDEMANDALIN.HORAINSERT,VDDEMANDALIN.FECINI,VDDEMANDALIN.HORAINI, "\
                    " VDDEMANDALIN.FECFIN,VDDEMANDALIN.HORAFIN,VDDEMANDALIN.VDEXTRA, "\
                    " VDDEMANDALIN.CODCOMEN,VDDEMANDALIN.CODOPEMODIF,VDDEMANDALIN.FECMODIF, "\
                    " VDDEMANDALIN.HORAMODIF,VDDEMANDALIN.PEDIDOHOST "\
        " FROM VDDEMANDALIN"\
        " WHERE "\
              "  CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA AND STATUS< "CSTDELRESERVADA" "
static v10cursors *vdseldemllineaspendientes;

#define SELDEMLVDDEMANDALIN "SELECT VDDEMANDALIN.ROWID,VDDEMANDALIN.TIPODEMANDA,VDDEMANDALIN.CODDEMANDA, "\
                    " VDDEMANDALIN.LINDEMANDA,VDDEMANDALIN.CLAVEEXT,VDDEMANDALIN.CODART, "\
                    " VDDEMANDALIN.CODLOT,VDDEMANDALIN.UNIEMB,VDDEMANDALIN.TIPOEMBA, "\
                    " VDDEMANDALIN.MARCASTK,VDDEMANDALIN.MARCASTKORIGEN,VDDEMANDALIN.BLOQUEOS, "\
                    " VDDEMANDALIN.NUMEROSERIE,VDDEMANDALIN.CODMAT,VDDEMANDALIN.BULTO, "\
                    " VDDEMANDALIN.CODRECEP,VDDEMANDALIN.PRECIOUNI,VDDEMANDALIN.BACKORDER, "\
                    " VDDEMANDALIN.UNIAGRUPA,VDDEMANDALIN.TIPOREDONDEO,VDDEMANDALIN.ORDENRESERVA, "\
                    " VDDEMANDALIN.ORDENRESERVAUBI,VDDEMANDALIN.CODUBIORI,VDDEMANDALIN.CODAREAORI, "\
                    " VDDEMANDALIN.CODUBIDEST,VDDEMANDALIN.CODAREADEST,VDDEMANDALIN.CANTIDAD, "\
                    " VDDEMANDALIN.STATUS,VDDEMANDALIN.CODOPEINSERT,VDDEMANDALIN.FECINSERT, "\
                    " VDDEMANDALIN.HORAINSERT,VDDEMANDALIN.FECINI,VDDEMANDALIN.HORAINI, "\
                    " VDDEMANDALIN.FECFIN,VDDEMANDALIN.HORAFIN,VDDEMANDALIN.VDEXTRA, "\
                    " VDDEMANDALIN.CODCOMEN,VDDEMANDALIN.CODOPEMODIF,VDDEMANDALIN.FECMODIF, "\
                    " VDDEMANDALIN.HORAMODIF,VDDEMANDALIN.PEDIDOHOST "\
        " FROM VDDEMANDALIN"\
        " WHERE "\
               " VDDEMANDALIN.TIPODEMANDA=:TIPODEMANDA "\
               " AND VDDEMANDALIN.CODDEMANDA=:CODDEMANDA "\
               " AND VDDEMANDALIN.LINDEMANDA=:LINDEMANDA "
static v10cursors *vdseldemlvddemandalin;

#define SELDEMLROWIDLOCK "SELECT ROWID,TIPODEMANDA,CODDEMANDA,LINDEMANDA,CLAVEEXT,CODART,CODLOT, "\
                    " UNIEMB,TIPOEMBA,MARCASTK,MARCASTKORIGEN,BLOQUEOS,NUMEROSERIE,CODMAT, "\
                    " BULTO,CODRECEP,PRECIOUNI,BACKORDER,UNIAGRUPA,TIPOREDONDEO,ORDENRESERVA, "\
                    " ORDENRESERVAUBI,CODUBIORI,CODAREAORI,CODUBIDEST,CODAREADEST,CANTIDAD,STATUS, "\
                    " CODOPEINSERT,FECINSERT,HORAINSERT,FECINI,HORAINI,FECFIN,HORAFIN, "\
                    " VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF,PEDIDOHOST "\
        " FROM VDDEMANDALIN "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdseldemlrowidlock;

#define UPDADEMLSTATUS "UPDATE VDDEMANDALIN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademlstatus;

#define UPDADEMLFECHAINICIO "UPDATE VDDEMANDALIN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " FECINI=:FECINI , "\
               " HORAINI=:HORAINI  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademlfechainicio;

#define UPDADEMLFECHAFINAL "UPDATE VDDEMANDALIN SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " FECFIN=:FECFIN , "\
               " HORAFIN=:HORAFIN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademlfechafinal;

static vddemandalins svddemandalin;

static diccols colvddemandalin[]={
	{"ROWID",V10CADENA,(size_t)&svddemandalin.rowid,sizeof(svddemandalin.rowid)},
	{"TIPODEMANDA",V10CADENA,(size_t)&svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda)},
	{"CODDEMANDA",V10CADENA,(size_t)&svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda)},
	{"LINDEMANDA",V10LONG,(size_t)&svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda)},
	{"CLAVEEXT",V10CADENA,(size_t)&svddemandalin.claveext,sizeof(svddemandalin.claveext)},
	{"CODART",V10CADENA,(size_t)&svddemandalin.codart,sizeof(svddemandalin.codart)},
	{"CODLOT",V10CADENA,(size_t)&svddemandalin.codlot,sizeof(svddemandalin.codlot)},
	{"UNIEMB",V10DOUBLE,(size_t)&svddemandalin.uniemb,sizeof(svddemandalin.uniemb)},
	{"TIPOEMBA",V10CADENA,(size_t)&svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba)},
	{"MARCASTK",V10CADENA,(size_t)&svddemandalin.marcastk,sizeof(svddemandalin.marcastk)},
	{"MARCASTKORIGEN",V10CADENA,(size_t)&svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen)},
	{"BLOQUEOS",V10CADENA,(size_t)&svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie)},
	{"CODMAT",V10CADENA,(size_t)&svddemandalin.codmat,sizeof(svddemandalin.codmat)},
	{"BULTO",V10CADENA,(size_t)&svddemandalin.bulto,sizeof(svddemandalin.bulto)},
	{"CODRECEP",V10CADENA,(size_t)&svddemandalin.codrecep,sizeof(svddemandalin.codrecep)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svddemandalin.preciouni,sizeof(svddemandalin.preciouni)},
	{"BACKORDER",V10CADENA,(size_t)&svddemandalin.backorder,sizeof(svddemandalin.backorder)},
	{"UNIAGRUPA",V10CADENA,(size_t)&svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa)},
	{"TIPOREDONDEO",V10CADENA,(size_t)&svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo)},
	{"ORDENRESERVA",V10CADENA,(size_t)&svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva)},
	{"ORDENRESERVAUBI",V10CADENA,(size_t)&svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi)},
	{"CODUBIORI",V10CADENA,(size_t)&svddemandalin.codubiori,sizeof(svddemandalin.codubiori)},
	{"CODAREAORI",V10CADENA,(size_t)&svddemandalin.codareaori,sizeof(svddemandalin.codareaori)},
	{"CODUBIDEST",V10CADENA,(size_t)&svddemandalin.codubidest,sizeof(svddemandalin.codubidest)},
	{"CODAREADEST",V10CADENA,(size_t)&svddemandalin.codareadest,sizeof(svddemandalin.codareadest)},
	{"CANTIDAD",V10DOUBLE,(size_t)&svddemandalin.cantidad,sizeof(svddemandalin.cantidad)},
	{"STATUS",V10LONG,(size_t)&svddemandalin.status,sizeof(svddemandalin.status)},
	{"CODOPEINSERT",V10CADENA,(size_t)&svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert)},
	{"FECINSERT",V10LONG,(size_t)&svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert)},
	{"HORAINSERT",V10CADENA,(size_t)&svddemandalin.horainsert,sizeof(svddemandalin.horainsert)},
	{"FECINI",V10LONG,(size_t)&svddemandalin.fecini,sizeof(svddemandalin.fecini)},
	{"HORAINI",V10CADENA,(size_t)&svddemandalin.horaini,sizeof(svddemandalin.horaini)},
	{"FECFIN",V10LONG,(size_t)&svddemandalin.fecfin,sizeof(svddemandalin.fecfin)},
	{"HORAFIN",V10CADENA,(size_t)&svddemandalin.horafin,sizeof(svddemandalin.horafin)},
	{"VDEXTRA",V10CADENA,(size_t)&svddemandalin.vdextra,sizeof(svddemandalin.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svddemandalin.codcomen,sizeof(svddemandalin.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svddemandalin.horamodif,sizeof(svddemandalin.horamodif)},
	{"PEDIDOHOST",V10CADENA,(size_t)&svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost)},
	{"COMENDEML",V10CADENA,(size_t)&svddemandalin.comendeml,sizeof(svddemandalin.comendeml)},
	{"RESERVADO",V10DOUBLE,(size_t)&svddemandalin.reservado,sizeof(svddemandalin.reservado)}
	};
static diccionarios dvddemandalin[]={
    {colvddemandalin,43}
};
diccionario ddeml={dvddemandalin,1};

static char msglogDEML[LCADENA];
static char msgdebugDEML[LCADENABIG];
static int init=0;


static void fin_vd_deml(void)
{
if (vdseldemldemandastatus) {
    liberacursor(vdseldemldemandastatus);
    vdseldemldemandastatus = NULL;
}
if (vdseldemlstatus) {
    liberacursor(vdseldemlstatus);
    vdseldemlstatus = NULL;
}
if (vdseldemllineaspendientes) {
    liberacursor(vdseldemllineaspendientes);
    vdseldemllineaspendientes = NULL;
}
if (vdseldemlvddemandalin) {
    liberacursor(vdseldemlvddemandalin);
    vdseldemlvddemandalin = NULL;
}
if (vdseldemlrowidlock) {
    liberacursor(vdseldemlrowidlock);
    vdseldemlrowidlock = NULL;
}
if (vdupdademlstatus) {
    liberacursor(vdupdademlstatus);
    vdupdademlstatus = NULL;
}
if (vdupdademlfechainicio) {
    liberacursor(vdupdademlfechainicio);
    vdupdademlfechainicio = NULL;
}
if (vdupdademlfechafinal) {
    liberacursor(vdupdademlfechafinal);
    vdupdademlfechafinal = NULL;
}
}
static void init_seldemldemandastatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdseldemldemandastatus=abrecursordebug(SELDEMLDEMANDASTATUS,1280);
    definetodo(vdseldemldemandastatus,svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          &svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          svddemandalin.claveext,sizeof(svddemandalin.claveext),V10CADENA,
                          svddemandalin.codart,sizeof(svddemandalin.codart),V10CADENA,
                          svddemandalin.codlot,sizeof(svddemandalin.codlot),V10CADENA,
                          &svddemandalin.uniemb,sizeof(svddemandalin.uniemb),V10DOUBLE,
                          svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba),V10CADENA,
                          svddemandalin.marcastk,sizeof(svddemandalin.marcastk),V10CADENA,
                          svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen),V10CADENA,
                          svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos),V10CADENA,
                          svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie),V10CADENA,
                          svddemandalin.codmat,sizeof(svddemandalin.codmat),V10CADENA,
                          svddemandalin.bulto,sizeof(svddemandalin.bulto),V10CADENA,
                          svddemandalin.codrecep,sizeof(svddemandalin.codrecep),V10CADENA,
                          &svddemandalin.preciouni,sizeof(svddemandalin.preciouni),V10DOUBLE,
                          svddemandalin.backorder,sizeof(svddemandalin.backorder),V10CADENA,
                          svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa),V10CADENA,
                          svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo),V10CADENA,
                          svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva),V10CADENA,
                          svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi),V10CADENA,
                          svddemandalin.codubiori,sizeof(svddemandalin.codubiori),V10CADENA,
                          svddemandalin.codareaori,sizeof(svddemandalin.codareaori),V10CADENA,
                          svddemandalin.codubidest,sizeof(svddemandalin.codubidest),V10CADENA,
                          svddemandalin.codareadest,sizeof(svddemandalin.codareadest),V10CADENA,
                          &svddemandalin.cantidad,sizeof(svddemandalin.cantidad),V10DOUBLE,
                          &svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert),V10CADENA,
                          &svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert),V10LONG,
                          svddemandalin.horainsert,sizeof(svddemandalin.horainsert),V10CADENA,
                          &svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          &svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          svddemandalin.vdextra,sizeof(svddemandalin.vdextra),V10CADENA,
                          &svddemandalin.codcomen,sizeof(svddemandalin.codcomen),V10LONG,
                          svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif),V10CADENA,
                          &svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif),V10LONG,
                          svddemandalin.horamodif,sizeof(svddemandalin.horamodif),V10CADENA,
                          svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost),V10CADENA,
                          NULL);
    bindtodo(vdseldemldemandastatus,"TIPODEMANDA",svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          "CODDEMANDA",svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          "STATUS",&svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_seldemlstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdseldemlstatus=abrecursordebug(SELDEMLSTATUS,1280);
    definetodo(vdseldemlstatus,svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          &svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          svddemandalin.claveext,sizeof(svddemandalin.claveext),V10CADENA,
                          svddemandalin.codart,sizeof(svddemandalin.codart),V10CADENA,
                          svddemandalin.codlot,sizeof(svddemandalin.codlot),V10CADENA,
                          &svddemandalin.uniemb,sizeof(svddemandalin.uniemb),V10DOUBLE,
                          svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba),V10CADENA,
                          svddemandalin.marcastk,sizeof(svddemandalin.marcastk),V10CADENA,
                          svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen),V10CADENA,
                          svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos),V10CADENA,
                          svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie),V10CADENA,
                          svddemandalin.codmat,sizeof(svddemandalin.codmat),V10CADENA,
                          svddemandalin.bulto,sizeof(svddemandalin.bulto),V10CADENA,
                          svddemandalin.codrecep,sizeof(svddemandalin.codrecep),V10CADENA,
                          &svddemandalin.preciouni,sizeof(svddemandalin.preciouni),V10DOUBLE,
                          svddemandalin.backorder,sizeof(svddemandalin.backorder),V10CADENA,
                          svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa),V10CADENA,
                          svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo),V10CADENA,
                          svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva),V10CADENA,
                          svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi),V10CADENA,
                          svddemandalin.codubiori,sizeof(svddemandalin.codubiori),V10CADENA,
                          svddemandalin.codareaori,sizeof(svddemandalin.codareaori),V10CADENA,
                          svddemandalin.codubidest,sizeof(svddemandalin.codubidest),V10CADENA,
                          svddemandalin.codareadest,sizeof(svddemandalin.codareadest),V10CADENA,
                          &svddemandalin.cantidad,sizeof(svddemandalin.cantidad),V10DOUBLE,
                          &svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert),V10CADENA,
                          &svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert),V10LONG,
                          svddemandalin.horainsert,sizeof(svddemandalin.horainsert),V10CADENA,
                          &svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          &svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          svddemandalin.vdextra,sizeof(svddemandalin.vdextra),V10CADENA,
                          &svddemandalin.codcomen,sizeof(svddemandalin.codcomen),V10LONG,
                          svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif),V10CADENA,
                          &svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif),V10LONG,
                          svddemandalin.horamodif,sizeof(svddemandalin.horamodif),V10CADENA,
                          svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost),V10CADENA,
                          NULL);
    bindtodo(vdseldemlstatus,"STATUS",&svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_seldemllineaspendientes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdseldemllineaspendientes=abrecursordebug(SELDEMLLINEASPENDIENTES,1280);
    definetodo(vdseldemllineaspendientes,svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          &svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          svddemandalin.claveext,sizeof(svddemandalin.claveext),V10CADENA,
                          svddemandalin.codart,sizeof(svddemandalin.codart),V10CADENA,
                          svddemandalin.codlot,sizeof(svddemandalin.codlot),V10CADENA,
                          &svddemandalin.uniemb,sizeof(svddemandalin.uniemb),V10DOUBLE,
                          svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba),V10CADENA,
                          svddemandalin.marcastk,sizeof(svddemandalin.marcastk),V10CADENA,
                          svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen),V10CADENA,
                          svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos),V10CADENA,
                          svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie),V10CADENA,
                          svddemandalin.codmat,sizeof(svddemandalin.codmat),V10CADENA,
                          svddemandalin.bulto,sizeof(svddemandalin.bulto),V10CADENA,
                          svddemandalin.codrecep,sizeof(svddemandalin.codrecep),V10CADENA,
                          &svddemandalin.preciouni,sizeof(svddemandalin.preciouni),V10DOUBLE,
                          svddemandalin.backorder,sizeof(svddemandalin.backorder),V10CADENA,
                          svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa),V10CADENA,
                          svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo),V10CADENA,
                          svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva),V10CADENA,
                          svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi),V10CADENA,
                          svddemandalin.codubiori,sizeof(svddemandalin.codubiori),V10CADENA,
                          svddemandalin.codareaori,sizeof(svddemandalin.codareaori),V10CADENA,
                          svddemandalin.codubidest,sizeof(svddemandalin.codubidest),V10CADENA,
                          svddemandalin.codareadest,sizeof(svddemandalin.codareadest),V10CADENA,
                          &svddemandalin.cantidad,sizeof(svddemandalin.cantidad),V10DOUBLE,
                          &svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert),V10CADENA,
                          &svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert),V10LONG,
                          svddemandalin.horainsert,sizeof(svddemandalin.horainsert),V10CADENA,
                          &svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          &svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          svddemandalin.vdextra,sizeof(svddemandalin.vdextra),V10CADENA,
                          &svddemandalin.codcomen,sizeof(svddemandalin.codcomen),V10LONG,
                          svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif),V10CADENA,
                          &svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif),V10LONG,
                          svddemandalin.horamodif,sizeof(svddemandalin.horamodif),V10CADENA,
                          svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost),V10CADENA,
                          NULL);
    bindtodo(vdseldemllineaspendientes,"CODDEMANDA",svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          "TIPODEMANDA",svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_seldemlvddemandalin(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdseldemlvddemandalin=abrecursordebug(SELDEMLVDDEMANDALIN,1280);
    definetodo(vdseldemlvddemandalin,svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          &svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          svddemandalin.claveext,sizeof(svddemandalin.claveext),V10CADENA,
                          svddemandalin.codart,sizeof(svddemandalin.codart),V10CADENA,
                          svddemandalin.codlot,sizeof(svddemandalin.codlot),V10CADENA,
                          &svddemandalin.uniemb,sizeof(svddemandalin.uniemb),V10DOUBLE,
                          svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba),V10CADENA,
                          svddemandalin.marcastk,sizeof(svddemandalin.marcastk),V10CADENA,
                          svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen),V10CADENA,
                          svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos),V10CADENA,
                          svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie),V10CADENA,
                          svddemandalin.codmat,sizeof(svddemandalin.codmat),V10CADENA,
                          svddemandalin.bulto,sizeof(svddemandalin.bulto),V10CADENA,
                          svddemandalin.codrecep,sizeof(svddemandalin.codrecep),V10CADENA,
                          &svddemandalin.preciouni,sizeof(svddemandalin.preciouni),V10DOUBLE,
                          svddemandalin.backorder,sizeof(svddemandalin.backorder),V10CADENA,
                          svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa),V10CADENA,
                          svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo),V10CADENA,
                          svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva),V10CADENA,
                          svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi),V10CADENA,
                          svddemandalin.codubiori,sizeof(svddemandalin.codubiori),V10CADENA,
                          svddemandalin.codareaori,sizeof(svddemandalin.codareaori),V10CADENA,
                          svddemandalin.codubidest,sizeof(svddemandalin.codubidest),V10CADENA,
                          svddemandalin.codareadest,sizeof(svddemandalin.codareadest),V10CADENA,
                          &svddemandalin.cantidad,sizeof(svddemandalin.cantidad),V10DOUBLE,
                          &svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert),V10CADENA,
                          &svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert),V10LONG,
                          svddemandalin.horainsert,sizeof(svddemandalin.horainsert),V10CADENA,
                          &svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          &svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          svddemandalin.vdextra,sizeof(svddemandalin.vdextra),V10CADENA,
                          &svddemandalin.codcomen,sizeof(svddemandalin.codcomen),V10LONG,
                          svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif),V10CADENA,
                          &svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif),V10LONG,
                          svddemandalin.horamodif,sizeof(svddemandalin.horamodif),V10CADENA,
                          svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost),V10CADENA,
                          NULL);
    bindtodo(vdseldemlvddemandalin,"TIPODEMANDA",svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          "CODDEMANDA",svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          "LINDEMANDA",&svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_seldemlrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdseldemlrowidlock=abrecursordebug(SELDEMLROWIDLOCK,1280);
    definetodo(vdseldemlrowidlock,svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          svddemandalin.tipodemanda,sizeof(svddemandalin.tipodemanda),V10CADENA,
                          svddemandalin.coddemanda,sizeof(svddemandalin.coddemanda),V10CADENA,
                          &svddemandalin.lindemanda,sizeof(svddemandalin.lindemanda),V10LONG,
                          svddemandalin.claveext,sizeof(svddemandalin.claveext),V10CADENA,
                          svddemandalin.codart,sizeof(svddemandalin.codart),V10CADENA,
                          svddemandalin.codlot,sizeof(svddemandalin.codlot),V10CADENA,
                          &svddemandalin.uniemb,sizeof(svddemandalin.uniemb),V10DOUBLE,
                          svddemandalin.tipoemba,sizeof(svddemandalin.tipoemba),V10CADENA,
                          svddemandalin.marcastk,sizeof(svddemandalin.marcastk),V10CADENA,
                          svddemandalin.marcastkorigen,sizeof(svddemandalin.marcastkorigen),V10CADENA,
                          svddemandalin.bloqueos,sizeof(svddemandalin.bloqueos),V10CADENA,
                          svddemandalin.numeroserie,sizeof(svddemandalin.numeroserie),V10CADENA,
                          svddemandalin.codmat,sizeof(svddemandalin.codmat),V10CADENA,
                          svddemandalin.bulto,sizeof(svddemandalin.bulto),V10CADENA,
                          svddemandalin.codrecep,sizeof(svddemandalin.codrecep),V10CADENA,
                          &svddemandalin.preciouni,sizeof(svddemandalin.preciouni),V10DOUBLE,
                          svddemandalin.backorder,sizeof(svddemandalin.backorder),V10CADENA,
                          svddemandalin.uniagrupa,sizeof(svddemandalin.uniagrupa),V10CADENA,
                          svddemandalin.tiporedondeo,sizeof(svddemandalin.tiporedondeo),V10CADENA,
                          svddemandalin.ordenreserva,sizeof(svddemandalin.ordenreserva),V10CADENA,
                          svddemandalin.ordenreservaubi,sizeof(svddemandalin.ordenreservaubi),V10CADENA,
                          svddemandalin.codubiori,sizeof(svddemandalin.codubiori),V10CADENA,
                          svddemandalin.codareaori,sizeof(svddemandalin.codareaori),V10CADENA,
                          svddemandalin.codubidest,sizeof(svddemandalin.codubidest),V10CADENA,
                          svddemandalin.codareadest,sizeof(svddemandalin.codareadest),V10CADENA,
                          &svddemandalin.cantidad,sizeof(svddemandalin.cantidad),V10DOUBLE,
                          &svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          svddemandalin.codopeinsert,sizeof(svddemandalin.codopeinsert),V10CADENA,
                          &svddemandalin.fecinsert,sizeof(svddemandalin.fecinsert),V10LONG,
                          svddemandalin.horainsert,sizeof(svddemandalin.horainsert),V10CADENA,
                          &svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          &svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          svddemandalin.vdextra,sizeof(svddemandalin.vdextra),V10CADENA,
                          &svddemandalin.codcomen,sizeof(svddemandalin.codcomen),V10LONG,
                          svddemandalin.codopemodif,sizeof(svddemandalin.codopemodif),V10CADENA,
                          &svddemandalin.fecmodif,sizeof(svddemandalin.fecmodif),V10LONG,
                          svddemandalin.horamodif,sizeof(svddemandalin.horamodif),V10CADENA,
                          svddemandalin.pedidohost,sizeof(svddemandalin.pedidohost),V10CADENA,
                          NULL);
    bindtodo(vdseldemlrowidlock,"MIROWID",svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_updademlstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdupdademlstatus=abrecursordebug(UPDADEMLSTATUS,1280);
    bindtodo(vdupdademlstatus,"STATUS",&svddemandalin.status,sizeof(svddemandalin.status),V10LONG,
                          "MIROWID",svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_updademlfechainicio(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdupdademlfechainicio=abrecursordebug(UPDADEMLFECHAINICIO,1280);
    bindtodo(vdupdademlfechainicio,"FECINI",&svddemandalin.fecini,sizeof(svddemandalin.fecini),V10LONG,
                          "HORAINI",svddemandalin.horaini,sizeof(svddemandalin.horaini),V10CADENA,
                          "MIROWID",svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

static void init_updademlfechafinal(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandalin[0].numcol;nc++) dvddemandalin[0].c[nc].offset-=(size_t)&svddemandalin;
    vdupdademlfechafinal=abrecursordebug(UPDADEMLFECHAFINAL,1280);
    bindtodo(vdupdademlfechafinal,"FECFIN",&svddemandalin.fecfin,sizeof(svddemandalin.fecfin),V10LONG,
                          "HORAFIN",svddemandalin.horafin,sizeof(svddemandalin.horafin),V10CADENA,
                          "MIROWID",svddemandalin.rowid,sizeof(svddemandalin.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_deml);
        init = 1;
    }
}

diccionario *DEMLdamediccionario(void)
{
     return(&ddeml);
}

int DEMLbuscademandastatus(char *tipodemanda,char *coddemanda,long status,vddemandalins *deml)
{
  int vdret;
  memset(&svddemandalin,0,sizeof(svddemandalin));
  strcpy(svddemandalin.tipodemanda,tipodemanda);
  strcpy(svddemandalin.coddemanda,coddemanda);
  svddemandalin.status=status;
  if (vdseldemldemandastatus==NULL) init_seldemldemandastatus();
  vdret=ejefetchcursor(vdseldemldemandastatus);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemldemandastatus. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMLnextdemandastatus(vddemandalins *deml)
{
  int vdret;
  vdret=fetchcursor(vdseldemldemandastatus);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemldemandastatus. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemldemandastatus);
  return(VD_EERRORACLE);
}

int DEMLbuscastatus(long status,vddemandalins *deml)
{
  int vdret;
  memset(&svddemandalin,0,sizeof(svddemandalin));
  svddemandalin.status=status;
  if (vdseldemlstatus==NULL) init_seldemlstatus();
  vdret=ejefetchcursor(vdseldemlstatus);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemlstatus. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMLnextstatus(vddemandalins *deml)
{
  int vdret;
  vdret=fetchcursor(vdseldemlstatus);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemlstatus. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemlstatus);
  return(VD_EERRORACLE);
}

int DEMLbuscalineaspendientes(char *coddemanda,char *tipodemanda,vddemandalins *deml)
{
  int vdret;
  memset(&svddemandalin,0,sizeof(svddemandalin));
  strcpy(svddemandalin.coddemanda,coddemanda);
  strcpy(svddemandalin.tipodemanda,tipodemanda);
  if (vdseldemllineaspendientes==NULL) init_seldemllineaspendientes();
  vdret=ejefetchcursor(vdseldemllineaspendientes);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemllineaspendientes. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMLnextlineaspendientes(vddemandalins *deml)
{
  int vdret;
  vdret=fetchcursor(vdseldemllineaspendientes);
  if (vdret==0) {
     *deml=svddemandalin;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemllineaspendientes. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemllineaspendientes);
  return(VD_EERRORACLE);
}

int DEMLselvddemandalin(char *tipodemanda,char *coddemanda,long lindemanda,vddemandalins *deml)
{
  int vdret;
  if (vdseldemlvddemandalin==NULL) init_seldemlvddemandalin();
  memset(&svddemandalin,0,sizeof(svddemandalin));
  strcpy(svddemandalin.tipodemanda,tipodemanda);
  strcpy(svddemandalin.coddemanda,coddemanda);
  svddemandalin.lindemanda=lindemanda;
  vdret=ejefetchcursor(vdseldemlvddemandalin);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldemlvddemandalin. vdret %d. \n",DEMLlog(&svddemandalin),vdret);
    return(VD_EERRORACLE);
   }
  *deml=svddemandalin;
  return(vdret);
}

int DEMLlock(vddemandalins *deml,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svddemandalin=*deml;
    if (vdseldemlrowidlock==NULL) init_seldemlrowidlock();
    savepoint("lockvddemandalin");
    while (1) {
        vdret=ejefetchcursor(vdseldemlrowidlock);
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
    vdret=vverificacampos(deml,&svddemandalin,&dvddemandalin[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvddemandalin");
    return(vdret);
}

int DEMLactualizastatus(vddemandalins *deml,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMLactualizastatus:  %s .  \n",DEMLlog(&svddemandalin));
  if (vdupdademlstatus==NULL) init_updademlstatus();
  svddemandalin=*deml;
  vdret=ejecutacursor(vdupdademlstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademlstatus);
     getcurerrornombre(vdupdademlstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademlstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int DEMLactualizafechainicio(vddemandalins *deml,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMLactualizafechainicio:  %s .  \n",DEMLlog(&svddemandalin));
  if (vdupdademlfechainicio==NULL) init_updademlfechainicio();
  svddemandalin=*deml;
  vdret=ejecutacursor(vdupdademlfechainicio);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademlfechainicio);
     getcurerrornombre(vdupdademlfechainicio->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademlfechainicio)!=1) return(VD_EERRORACLE);
  return(0);
}

int DEMLactualizafechafinal(vddemandalins *deml,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMLactualizafechafinal:  %s .  \n",DEMLlog(&svddemandalin));
  if (vdupdademlfechafinal==NULL) init_updademlfechafinal();
  svddemandalin=*deml;
  vdret=ejecutacursor(vdupdademlfechafinal);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademlfechafinal);
     getcurerrornombre(vdupdademlfechafinal->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademlfechafinal)!=1) return(VD_EERRORACLE);
  return(0);
}

char * DEMLlog(vddemandalins *deml)
{
    sprintf(msglogDEML, "VDDEMANDALIN: tipodemanda %s coddemanda %s lindemanda %ld ",deml->tipodemanda,deml->coddemanda,deml->lindemanda);
    return(msglogDEML);
}

char * DEMLdebug(vddemandalins *deml)
{
    debugestruct(&ddeml,deml,msgdebugDEML);
    return(msgdebugDEML);
}

