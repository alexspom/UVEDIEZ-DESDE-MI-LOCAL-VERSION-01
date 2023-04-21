// Modulo generado automaticamente a partir de VDDEMANDACAB.DEF
//#***
//# VDDEMANDACAB.c - Generación automática del código c para la tabla de Cabecera de Demandas                                                      
//# 
//# Propósito: Funciones de acceso a la tabla VDDEMANDACAB
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 5-03-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=DEMC
//EXTRA=COMENDEMC,V10CADENA,1024
//
//RECORRE=SINLINEASPDTES,WHERE= CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA 
//                              AND NOT EXISTS (SELECT 1 FROM VDDEMANDALIN DEML WHERE 
//                                                  VDDEMANDACAB.TIPODEMANDA=DEML.TIPODEMANDA AND 
//                                                  VDDEMANDACAB.CODDEMANDA=DEML.CODDEMANDA AND                                                  
//                                                  STATUS< "CSTDELRESERVADA");
//                                                  
//RECORRE=SINLINEASPORFINALIZAR,WHERE= CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA 
//                              AND NOT EXISTS (SELECT 1 FROM VDDEMANDALIN DEML WHERE 
//                                                  VDDEMANDACAB.TIPODEMANDA=DEML.TIPODEMANDA AND 
//                                                  VDDEMANDACAB.CODDEMANDA=DEML.CODDEMANDA AND                                                 
//                                                  STATUS< "CSTDELMVFINAL");                                                  
//RECORRE=TIPOYSTATUS,TIPODEMANDA,STATUS;
//UPDATE=STATUS,STATUS;
//UPDATE=FECHAINICIO,FECINI,HORAINI;
//UPDATE=FECHAFINAL,FECFIN,HORAFIN;
//LOCK

#include "vd.h"
#define SELDEMCSINLINEASPDTES "SELECT VDDEMANDACAB.ROWID,VDDEMANDACAB.TIPODEMANDA,VDDEMANDACAB.CODDEMANDA, "\
                    " VDDEMANDACAB.CLAVEEXT,VDDEMANDACAB.BACKORDER,VDDEMANDACAB.PRIORI, "\
                    " VDDEMANDACAB.STATUS,VDDEMANDACAB.CODOPEINSERT,VDDEMANDACAB.FECINSERT, "\
                    " VDDEMANDACAB.HORAINSERT,VDDEMANDACAB.FECINI,VDDEMANDACAB.HORAINI, "\
                    " VDDEMANDACAB.FECFIN,VDDEMANDACAB.HORAFIN,VDDEMANDACAB.FECNEC, "\
                    " VDDEMANDACAB.VDEXTRA,VDDEMANDACAB.CODCOMEN,VDDEMANDACAB.CODOPEMODIF, "\
                    " VDDEMANDACAB.FECMODIF,VDDEMANDACAB.HORAMODIF "\
        " FROM VDDEMANDACAB"\
        " WHERE "\
              "  CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA  AND NOT EXISTS (SELECT 1 FROM VDDEMANDALIN DEML WHERE  VDDEMANDACAB.TIPODEMANDA=DEML.TIPODEMANDA AND  VDDEMANDACAB.CODDEMANDA=DEML.CODDEMANDA AND                                                   STATUS< "CSTDELRESERVADA") "
static v10cursors *vdseldemcsinlineaspdtes;

#define SELDEMCSINLINEASPORFINALIZAR "SELECT VDDEMANDACAB.ROWID,VDDEMANDACAB.TIPODEMANDA,VDDEMANDACAB.CODDEMANDA, "\
                    " VDDEMANDACAB.CLAVEEXT,VDDEMANDACAB.BACKORDER,VDDEMANDACAB.PRIORI, "\
                    " VDDEMANDACAB.STATUS,VDDEMANDACAB.CODOPEINSERT,VDDEMANDACAB.FECINSERT, "\
                    " VDDEMANDACAB.HORAINSERT,VDDEMANDACAB.FECINI,VDDEMANDACAB.HORAINI, "\
                    " VDDEMANDACAB.FECFIN,VDDEMANDACAB.HORAFIN,VDDEMANDACAB.FECNEC, "\
                    " VDDEMANDACAB.VDEXTRA,VDDEMANDACAB.CODCOMEN,VDDEMANDACAB.CODOPEMODIF, "\
                    " VDDEMANDACAB.FECMODIF,VDDEMANDACAB.HORAMODIF "\
        " FROM VDDEMANDACAB"\
        " WHERE "\
              "  CODDEMANDA=:CODDEMANDA AND TIPODEMANDA=:TIPODEMANDA  AND NOT EXISTS (SELECT 1 FROM VDDEMANDALIN DEML WHERE  VDDEMANDACAB.TIPODEMANDA=DEML.TIPODEMANDA AND  VDDEMANDACAB.CODDEMANDA=DEML.CODDEMANDA AND                                                  STATUS< "CSTDELMVFINAL") "
static v10cursors *vdseldemcsinlineasporfinalizar;

#define SELDEMCTIPOYSTATUS "SELECT VDDEMANDACAB.ROWID,VDDEMANDACAB.TIPODEMANDA,VDDEMANDACAB.CODDEMANDA, "\
                    " VDDEMANDACAB.CLAVEEXT,VDDEMANDACAB.BACKORDER,VDDEMANDACAB.PRIORI, "\
                    " VDDEMANDACAB.STATUS,VDDEMANDACAB.CODOPEINSERT,VDDEMANDACAB.FECINSERT, "\
                    " VDDEMANDACAB.HORAINSERT,VDDEMANDACAB.FECINI,VDDEMANDACAB.HORAINI, "\
                    " VDDEMANDACAB.FECFIN,VDDEMANDACAB.HORAFIN,VDDEMANDACAB.FECNEC, "\
                    " VDDEMANDACAB.VDEXTRA,VDDEMANDACAB.CODCOMEN,VDDEMANDACAB.CODOPEMODIF, "\
                    " VDDEMANDACAB.FECMODIF,VDDEMANDACAB.HORAMODIF "\
        " FROM VDDEMANDACAB"\
        " WHERE "\
               " VDDEMANDACAB.TIPODEMANDA=:TIPODEMANDA "\
               " AND VDDEMANDACAB.STATUS=:STATUS "
static v10cursors *vdseldemctipoystatus;

#define SELDEMCVDDEMANDACAB "SELECT VDDEMANDACAB.ROWID,VDDEMANDACAB.TIPODEMANDA,VDDEMANDACAB.CODDEMANDA, "\
                    " VDDEMANDACAB.CLAVEEXT,VDDEMANDACAB.BACKORDER,VDDEMANDACAB.PRIORI, "\
                    " VDDEMANDACAB.STATUS,VDDEMANDACAB.CODOPEINSERT,VDDEMANDACAB.FECINSERT, "\
                    " VDDEMANDACAB.HORAINSERT,VDDEMANDACAB.FECINI,VDDEMANDACAB.HORAINI, "\
                    " VDDEMANDACAB.FECFIN,VDDEMANDACAB.HORAFIN,VDDEMANDACAB.FECNEC, "\
                    " VDDEMANDACAB.VDEXTRA,VDDEMANDACAB.CODCOMEN,VDDEMANDACAB.CODOPEMODIF, "\
                    " VDDEMANDACAB.FECMODIF,VDDEMANDACAB.HORAMODIF "\
        " FROM VDDEMANDACAB"\
        " WHERE "\
               " VDDEMANDACAB.TIPODEMANDA=:TIPODEMANDA "\
               " AND VDDEMANDACAB.CODDEMANDA=:CODDEMANDA "
static v10cursors *vdseldemcvddemandacab;

#define SELDEMCROWIDLOCK "SELECT ROWID,TIPODEMANDA,CODDEMANDA,CLAVEEXT,BACKORDER,PRIORI,STATUS, "\
                    " CODOPEINSERT,FECINSERT,HORAINSERT,FECINI,HORAINI,FECFIN,HORAFIN, "\
                    " FECNEC,VDEXTRA,CODCOMEN,CODOPEMODIF,FECMODIF,HORAMODIF "\
        " FROM VDDEMANDACAB "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdseldemcrowidlock;

#define UPDADEMCSTATUS "UPDATE VDDEMANDACAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademcstatus;

#define UPDADEMCFECHAINICIO "UPDATE VDDEMANDACAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " FECINI=:FECINI , "\
               " HORAINI=:HORAINI  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademcfechainicio;

#define UPDADEMCFECHAFINAL "UPDATE VDDEMANDACAB SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  "\
               " FECFIN=:FECFIN , "\
               " HORAFIN=:HORAFIN  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdademcfechafinal;

static vddemandacabs svddemandacab;

static diccols colvddemandacab[]={
	{"ROWID",V10CADENA,(size_t)&svddemandacab.rowid,sizeof(svddemandacab.rowid)},
	{"TIPODEMANDA",V10CADENA,(size_t)&svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda)},
	{"CODDEMANDA",V10CADENA,(size_t)&svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda)},
	{"CLAVEEXT",V10CADENA,(size_t)&svddemandacab.claveext,sizeof(svddemandacab.claveext)},
	{"BACKORDER",V10CADENA,(size_t)&svddemandacab.backorder,sizeof(svddemandacab.backorder)},
	{"PRIORI",V10LONG,(size_t)&svddemandacab.priori,sizeof(svddemandacab.priori)},
	{"STATUS",V10LONG,(size_t)&svddemandacab.status,sizeof(svddemandacab.status)},
	{"CODOPEINSERT",V10CADENA,(size_t)&svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert)},
	{"FECINSERT",V10LONG,(size_t)&svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert)},
	{"HORAINSERT",V10CADENA,(size_t)&svddemandacab.horainsert,sizeof(svddemandacab.horainsert)},
	{"FECINI",V10LONG,(size_t)&svddemandacab.fecini,sizeof(svddemandacab.fecini)},
	{"HORAINI",V10CADENA,(size_t)&svddemandacab.horaini,sizeof(svddemandacab.horaini)},
	{"FECFIN",V10LONG,(size_t)&svddemandacab.fecfin,sizeof(svddemandacab.fecfin)},
	{"HORAFIN",V10CADENA,(size_t)&svddemandacab.horafin,sizeof(svddemandacab.horafin)},
	{"FECNEC",V10LONG,(size_t)&svddemandacab.fecnec,sizeof(svddemandacab.fecnec)},
	{"VDEXTRA",V10CADENA,(size_t)&svddemandacab.vdextra,sizeof(svddemandacab.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svddemandacab.codcomen,sizeof(svddemandacab.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif)},
	{"FECMODIF",V10LONG,(size_t)&svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svddemandacab.horamodif,sizeof(svddemandacab.horamodif)},
	{"COMENDEMC",V10CADENA,(size_t)&svddemandacab.comendemc,sizeof(svddemandacab.comendemc)}
	};
static diccionarios dvddemandacab[]={
    {colvddemandacab,21}
};
diccionario ddemc={dvddemandacab,1};

static char msglogDEMC[LCADENA];
static char msgdebugDEMC[LCADENABIG];
static int init=0;


static void fin_vd_demc(void)
{
if (vdseldemcsinlineaspdtes) {
    liberacursor(vdseldemcsinlineaspdtes);
    vdseldemcsinlineaspdtes = NULL;
}
if (vdseldemcsinlineasporfinalizar) {
    liberacursor(vdseldemcsinlineasporfinalizar);
    vdseldemcsinlineasporfinalizar = NULL;
}
if (vdseldemctipoystatus) {
    liberacursor(vdseldemctipoystatus);
    vdseldemctipoystatus = NULL;
}
if (vdseldemcvddemandacab) {
    liberacursor(vdseldemcvddemandacab);
    vdseldemcvddemandacab = NULL;
}
if (vdseldemcrowidlock) {
    liberacursor(vdseldemcrowidlock);
    vdseldemcrowidlock = NULL;
}
if (vdupdademcstatus) {
    liberacursor(vdupdademcstatus);
    vdupdademcstatus = NULL;
}
if (vdupdademcfechainicio) {
    liberacursor(vdupdademcfechainicio);
    vdupdademcfechainicio = NULL;
}
if (vdupdademcfechafinal) {
    liberacursor(vdupdademcfechafinal);
    vdupdademcfechafinal = NULL;
}
}
static void init_seldemcsinlineaspdtes(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdseldemcsinlineaspdtes=abrecursordebug(SELDEMCSINLINEASPDTES,1280);
    definetodo(vdseldemcsinlineaspdtes,svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          svddemandacab.claveext,sizeof(svddemandacab.claveext),V10CADENA,
                          svddemandacab.backorder,sizeof(svddemandacab.backorder),V10CADENA,
                          &svddemandacab.priori,sizeof(svddemandacab.priori),V10LONG,
                          &svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert),V10CADENA,
                          &svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert),V10LONG,
                          svddemandacab.horainsert,sizeof(svddemandacab.horainsert),V10CADENA,
                          &svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          &svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          &svddemandacab.fecnec,sizeof(svddemandacab.fecnec),V10LONG,
                          svddemandacab.vdextra,sizeof(svddemandacab.vdextra),V10CADENA,
                          &svddemandacab.codcomen,sizeof(svddemandacab.codcomen),V10LONG,
                          svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif),V10CADENA,
                          &svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif),V10LONG,
                          svddemandacab.horamodif,sizeof(svddemandacab.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseldemcsinlineaspdtes,"CODDEMANDA",svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          "TIPODEMANDA",svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_seldemcsinlineasporfinalizar(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdseldemcsinlineasporfinalizar=abrecursordebug(SELDEMCSINLINEASPORFINALIZAR,1280);
    definetodo(vdseldemcsinlineasporfinalizar,svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          svddemandacab.claveext,sizeof(svddemandacab.claveext),V10CADENA,
                          svddemandacab.backorder,sizeof(svddemandacab.backorder),V10CADENA,
                          &svddemandacab.priori,sizeof(svddemandacab.priori),V10LONG,
                          &svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert),V10CADENA,
                          &svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert),V10LONG,
                          svddemandacab.horainsert,sizeof(svddemandacab.horainsert),V10CADENA,
                          &svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          &svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          &svddemandacab.fecnec,sizeof(svddemandacab.fecnec),V10LONG,
                          svddemandacab.vdextra,sizeof(svddemandacab.vdextra),V10CADENA,
                          &svddemandacab.codcomen,sizeof(svddemandacab.codcomen),V10LONG,
                          svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif),V10CADENA,
                          &svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif),V10LONG,
                          svddemandacab.horamodif,sizeof(svddemandacab.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseldemcsinlineasporfinalizar,"CODDEMANDA",svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          "TIPODEMANDA",svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_seldemctipoystatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdseldemctipoystatus=abrecursordebug(SELDEMCTIPOYSTATUS,1280);
    definetodo(vdseldemctipoystatus,svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          svddemandacab.claveext,sizeof(svddemandacab.claveext),V10CADENA,
                          svddemandacab.backorder,sizeof(svddemandacab.backorder),V10CADENA,
                          &svddemandacab.priori,sizeof(svddemandacab.priori),V10LONG,
                          &svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert),V10CADENA,
                          &svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert),V10LONG,
                          svddemandacab.horainsert,sizeof(svddemandacab.horainsert),V10CADENA,
                          &svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          &svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          &svddemandacab.fecnec,sizeof(svddemandacab.fecnec),V10LONG,
                          svddemandacab.vdextra,sizeof(svddemandacab.vdextra),V10CADENA,
                          &svddemandacab.codcomen,sizeof(svddemandacab.codcomen),V10LONG,
                          svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif),V10CADENA,
                          &svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif),V10LONG,
                          svddemandacab.horamodif,sizeof(svddemandacab.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseldemctipoystatus,"TIPODEMANDA",svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          "STATUS",&svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_seldemcvddemandacab(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdseldemcvddemandacab=abrecursordebug(SELDEMCVDDEMANDACAB,1280);
    definetodo(vdseldemcvddemandacab,svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          svddemandacab.claveext,sizeof(svddemandacab.claveext),V10CADENA,
                          svddemandacab.backorder,sizeof(svddemandacab.backorder),V10CADENA,
                          &svddemandacab.priori,sizeof(svddemandacab.priori),V10LONG,
                          &svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert),V10CADENA,
                          &svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert),V10LONG,
                          svddemandacab.horainsert,sizeof(svddemandacab.horainsert),V10CADENA,
                          &svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          &svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          &svddemandacab.fecnec,sizeof(svddemandacab.fecnec),V10LONG,
                          svddemandacab.vdextra,sizeof(svddemandacab.vdextra),V10CADENA,
                          &svddemandacab.codcomen,sizeof(svddemandacab.codcomen),V10LONG,
                          svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif),V10CADENA,
                          &svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif),V10LONG,
                          svddemandacab.horamodif,sizeof(svddemandacab.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseldemcvddemandacab,"TIPODEMANDA",svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          "CODDEMANDA",svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_seldemcrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdseldemcrowidlock=abrecursordebug(SELDEMCROWIDLOCK,1280);
    definetodo(vdseldemcrowidlock,svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          svddemandacab.tipodemanda,sizeof(svddemandacab.tipodemanda),V10CADENA,
                          svddemandacab.coddemanda,sizeof(svddemandacab.coddemanda),V10CADENA,
                          svddemandacab.claveext,sizeof(svddemandacab.claveext),V10CADENA,
                          svddemandacab.backorder,sizeof(svddemandacab.backorder),V10CADENA,
                          &svddemandacab.priori,sizeof(svddemandacab.priori),V10LONG,
                          &svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          svddemandacab.codopeinsert,sizeof(svddemandacab.codopeinsert),V10CADENA,
                          &svddemandacab.fecinsert,sizeof(svddemandacab.fecinsert),V10LONG,
                          svddemandacab.horainsert,sizeof(svddemandacab.horainsert),V10CADENA,
                          &svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          &svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          &svddemandacab.fecnec,sizeof(svddemandacab.fecnec),V10LONG,
                          svddemandacab.vdextra,sizeof(svddemandacab.vdextra),V10CADENA,
                          &svddemandacab.codcomen,sizeof(svddemandacab.codcomen),V10LONG,
                          svddemandacab.codopemodif,sizeof(svddemandacab.codopemodif),V10CADENA,
                          &svddemandacab.fecmodif,sizeof(svddemandacab.fecmodif),V10LONG,
                          svddemandacab.horamodif,sizeof(svddemandacab.horamodif),V10CADENA,
                          NULL);
    bindtodo(vdseldemcrowidlock,"MIROWID",svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_updademcstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdupdademcstatus=abrecursordebug(UPDADEMCSTATUS,1280);
    bindtodo(vdupdademcstatus,"STATUS",&svddemandacab.status,sizeof(svddemandacab.status),V10LONG,
                          "MIROWID",svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_updademcfechainicio(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdupdademcfechainicio=abrecursordebug(UPDADEMCFECHAINICIO,1280);
    bindtodo(vdupdademcfechainicio,"FECINI",&svddemandacab.fecini,sizeof(svddemandacab.fecini),V10LONG,
                          "HORAINI",svddemandacab.horaini,sizeof(svddemandacab.horaini),V10CADENA,
                          "MIROWID",svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

static void init_updademcfechafinal(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvddemandacab[0].numcol;nc++) dvddemandacab[0].c[nc].offset-=(size_t)&svddemandacab;
    vdupdademcfechafinal=abrecursordebug(UPDADEMCFECHAFINAL,1280);
    bindtodo(vdupdademcfechafinal,"FECFIN",&svddemandacab.fecfin,sizeof(svddemandacab.fecfin),V10LONG,
                          "HORAFIN",svddemandacab.horafin,sizeof(svddemandacab.horafin),V10CADENA,
                          "MIROWID",svddemandacab.rowid,sizeof(svddemandacab.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_demc);
        init = 1;
    }
}

diccionario *DEMCdamediccionario(void)
{
     return(&ddemc);
}

int DEMCbuscasinlineaspdtes(char *coddemanda,char *tipodemanda,vddemandacabs *demc)
{
  int vdret;
  memset(&svddemandacab,0,sizeof(svddemandacab));
  strcpy(svddemandacab.coddemanda,coddemanda);
  strcpy(svddemandacab.tipodemanda,tipodemanda);
  if (vdseldemcsinlineaspdtes==NULL) init_seldemcsinlineaspdtes();
  vdret=ejefetchcursor(vdseldemcsinlineaspdtes);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemcsinlineaspdtes. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMCnextsinlineaspdtes(vddemandacabs *demc)
{
  int vdret;
  vdret=fetchcursor(vdseldemcsinlineaspdtes);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemcsinlineaspdtes. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemcsinlineaspdtes);
  return(VD_EERRORACLE);
}

int DEMCbuscasinlineasporfinalizar(char *coddemanda,char *tipodemanda,vddemandacabs *demc)
{
  int vdret;
  memset(&svddemandacab,0,sizeof(svddemandacab));
  strcpy(svddemandacab.coddemanda,coddemanda);
  strcpy(svddemandacab.tipodemanda,tipodemanda);
  if (vdseldemcsinlineasporfinalizar==NULL) init_seldemcsinlineasporfinalizar();
  vdret=ejefetchcursor(vdseldemcsinlineasporfinalizar);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemcsinlineasporfinalizar. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMCnextsinlineasporfinalizar(vddemandacabs *demc)
{
  int vdret;
  vdret=fetchcursor(vdseldemcsinlineasporfinalizar);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemcsinlineasporfinalizar. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemcsinlineasporfinalizar);
  return(VD_EERRORACLE);
}

int DEMCbuscatipoystatus(char *tipodemanda,long status,vddemandacabs *demc)
{
  int vdret;
  memset(&svddemandacab,0,sizeof(svddemandacab));
  strcpy(svddemandacab.tipodemanda,tipodemanda);
  svddemandacab.status=status;
  if (vdseldemctipoystatus==NULL) init_seldemctipoystatus();
  vdret=ejefetchcursor(vdseldemctipoystatus);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdseldemctipoystatus. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int DEMCnexttipoystatus(vddemandacabs *demc)
{
  int vdret;
  vdret=fetchcursor(vdseldemctipoystatus);
  if (vdret==0) {
     *demc=svddemandacab;
    v10log(LOGDEBUGAPI,"Siguiente %s vdseldemctipoystatus. vdret %d. \n",DEMClog(&svddemandacab),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdseldemctipoystatus);
  return(VD_EERRORACLE);
}

int DEMCselvddemandacab(char *tipodemanda,char *coddemanda,vddemandacabs *demc)
{
  int vdret;
  if (vdseldemcvddemandacab==NULL) init_seldemcvddemandacab();
  memset(&svddemandacab,0,sizeof(svddemandacab));
  strcpy(svddemandacab.tipodemanda,tipodemanda);
  strcpy(svddemandacab.coddemanda,coddemanda);
  vdret=ejefetchcursor(vdseldemcvddemandacab);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdseldemcvddemandacab. vdret %d. \n",DEMClog(&svddemandacab),vdret);
    return(VD_EERRORACLE);
   }
  *demc=svddemandacab;
  return(vdret);
}

int DEMClock(vddemandacabs *demc,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svddemandacab=*demc;
    if (vdseldemcrowidlock==NULL) init_seldemcrowidlock();
    savepoint("lockvddemandacab");
    while (1) {
        vdret=ejefetchcursor(vdseldemcrowidlock);
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
    vdret=vverificacampos(demc,&svddemandacab,&dvddemandacab[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvddemandacab");
    return(vdret);
}

int DEMCactualizastatus(vddemandacabs *demc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMCactualizastatus:  %s .  \n",DEMClog(&svddemandacab));
  if (vdupdademcstatus==NULL) init_updademcstatus();
  svddemandacab=*demc;
  vdret=ejecutacursor(vdupdademcstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademcstatus);
     getcurerrornombre(vdupdademcstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademcstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int DEMCactualizafechainicio(vddemandacabs *demc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMCactualizafechainicio:  %s .  \n",DEMClog(&svddemandacab));
  if (vdupdademcfechainicio==NULL) init_updademcfechainicio();
  svddemandacab=*demc;
  vdret=ejecutacursor(vdupdademcfechainicio);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademcfechainicio);
     getcurerrornombre(vdupdademcfechainicio->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademcfechainicio)!=1) return(VD_EERRORACLE);
  return(0);
}

int DEMCactualizafechafinal(vddemandacabs *demc,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando DEMCactualizafechafinal:  %s .  \n",DEMClog(&svddemandacab));
  if (vdupdademcfechafinal==NULL) init_updademcfechafinal();
  svddemandacab=*demc;
  vdret=ejecutacursor(vdupdademcfechafinal);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdademcfechafinal);
     getcurerrornombre(vdupdademcfechafinal->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdademcfechafinal)!=1) return(VD_EERRORACLE);
  return(0);
}

char * DEMClog(vddemandacabs *demc)
{
    sprintf(msglogDEMC, "VDDEMANDACAB: tipodemanda %s coddemanda %s ",demc->tipodemanda,demc->coddemanda);
    return(msglogDEMC);
}

char * DEMCdebug(vddemandacabs *demc)
{
    debugestruct(&ddemc,demc,msgdebugDEMC);
    return(msgdebugDEMC);
}

