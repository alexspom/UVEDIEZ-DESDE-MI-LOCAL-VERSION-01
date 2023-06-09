// Modulo generado automaticamente a partir de VDMOVIM.DEF
//#***
//# VDMOVIM.c - Generaci�n autom�tica del c�digo c para la tabla                                                        
//# 
//# Prop�sito: Funciones de acceso a la tabla VDMOVIM
//#           
//# Autor	 : ICC
//# Revisado por: 
//# Fecha  : 25-10-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//TABLE=MOV
//EXTRA=STATUS1,V10LONG
//EXTRA=STATUS2,V10LONG
//EXTRA=COMEN,V10CADENA,1025
//EXTRA=MOVERPALET,V10CADENA,1
//
//SECUENCIA=VDSECPREP,CODPREPARACION
//SECUENCIA=VDSECMOVIM,CODMOV
//
//RECORRE=MISMOPALET,CODMATORI,WHERE=DECODE(CODMATORI,CODMATDEST,'S','N')=:MOVERPALET AND CODMOV != :CODMOV AND STATUS BETWEEN :STATUS1 AND :STATUS2;ORDERBY=STATUS DESC;
//RECORRE=CODMOVESP,WHERE CODMOVESP=:CODMOV;
//RECORRE=STATUS,STATUS;ORDERBY=CODMOV;
//RECORRE=STATUSARTMAT,STATUS;ORDERBY=CODART,CODMATORI,CODMOV;
//RECORRE=DEMANDA,TIPODEMANDA,CODDEMANDA;ORDERBY=TAREA;
//RECORRE=MOVTOSTAREA,CODMATORI,WHERE=CODMOV != :CODMOV AND STATUS < :STATUS1 AND TAREA=:TAREA;
//
//UPDATE=REENGANCHAMOV,CODUBIORI,CODMATORI,STATUS
//UPDATE=RUTA,STATUS,CODMOVPPASO,CODMOVESP
//UPDATE=STATUS,STATUS
//UPDATE=ORIGEN,CODMATORI,CODUBIORI
//UPDATE=DESTINO,CODMATDEST,CODUBIDEST
//UPDATE=CANTIDAD,CANTIDAD
//UPDATE=DEMANDA,TIPODEMANDA,CODDEMANDA,LINDEMANDA
//UPDATE=MATRICULAS,CODMATORI,CODMATDEST
//UPDATE=TAREA,TAREA
// 
// 
//INSERT 
//DELETE
//LOCK

#include "vd.h"
#define SELMOVMISMOPALET "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.CODMATORI=:CODMATORI "\
              "  AND DECODE(CODMATORI,CODMATDEST,'S','N')=:MOVERPALET AND CODMOV != :CODMOV AND STATUS BETWEEN :STATUS1 AND :STATUS2 "\
        " ORDER BY STATUS DESC "
static v10cursors *vdselmovmismopalet;

#define SELMOVCODMOVESP "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
              " CODMOVESP=:CODMOV "
static v10cursors *vdselmovcodmovesp;

#define SELMOVSTATUS "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.STATUS=:STATUS "\
        " ORDER BY CODMOV "
static v10cursors *vdselmovstatus;

#define SELMOVSTATUSARTMAT "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.STATUS=:STATUS "\
        " ORDER BY CODART,CODMATORI,CODMOV "
static v10cursors *vdselmovstatusartmat;

#define SELMOVDEMANDA "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.TIPODEMANDA=:TIPODEMANDA "\
               " AND VDMOVIM.CODDEMANDA=:CODDEMANDA "\
        " ORDER BY TAREA "
static v10cursors *vdselmovdemanda;

#define SELMOVMOVTOSTAREA "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.CODMATORI=:CODMATORI "\
              "  AND CODMOV != :CODMOV AND STATUS < :STATUS1 AND TAREA=:TAREA "
static v10cursors *vdselmovmovtostarea;

#define SELMOVVDMOVIM "SELECT VDMOVIM.ROWID,VDMOVIM.CODMOV,VDMOVIM.CODCONCE, "\
                    " VDMOVIM.DATOSHOST,VDMOVIM.CODUBIORI,VDMOVIM.CODUBITEMP, "\
                    " VDMOVIM.CODUBIDEST,VDMOVIM.CODMATORI,VDMOVIM.CODMATTEMP, "\
                    " VDMOVIM.CODMATDEST,VDMOVIM.TIPOCONTE,VDMOVIM.PRIOMOV, "\
                    " VDMOVIM.TAREA,VDMOVIM.CODRECURSO,VDMOVIM.SOLOMUEVE, "\
                    " VDMOVIM.CODMOVESP,VDMOVIM.CODMOVPPASO,VDMOVIM.CODDOCUMENTO, "\
                    " VDMOVIM.CODINTERFASE,VDMOVIM.CODPREPARACION,VDMOVIM.STATUS, "\
                    " VDMOVIM.BULTO,VDMOVIM.CODART,VDMOVIM.CODLOT, "\
                    " VDMOVIM.CANTIDAD,VDMOVIM.BLOQUEOSORI,VDMOVIM.BLOQUEOSDEST, "\
                    " VDMOVIM.TIPOEMBA,VDMOVIM.UNIEMB,VDMOVIM.EMBCONT, "\
                    " VDMOVIM.MARCASTK,VDMOVIM.NUMEROSERIE,VDMOVIM.PRECIOUNI, "\
                    " VDMOVIM.PESOUNI,VDMOVIM.CODRECEP,VDMOVIM.CODFLUJO, "\
                    " VDMOVIM.TIPODEMANDA,VDMOVIM.CODDEMANDA,VDMOVIM.LINDEMANDA, "\
                    " VDMOVIM.CODOPEINS,VDMOVIM.MODULOINS,VDMOVIM.ACCIONINS, "\
                    " VDMOVIM.FECINS,VDMOVIM.HORAINS,VDMOVIM.MODULOPLANMOV, "\
                    " VDMOVIM.ACCIONPLANMOV,VDMOVIM.FECPLANMOV,VDMOVIM.HORAPLANMOV, "\
                    " VDMOVIM.CODOPEEJEMOV,VDMOVIM.MODULOINIMOV,VDMOVIM.ACCIONINIMOV, "\
                    " VDMOVIM.FECINIMOV,VDMOVIM.HORAINIMOV,VDMOVIM.MODULOFINMOV, "\
                    " VDMOVIM.ACCIONFINMOV,VDMOVIM.FECFINMOV,VDMOVIM.HORAFINMOV, "\
                    " VDMOVIM.VDEXTRA,VDMOVIM.CODCOMEN,VDMOVIM.CODOPEMODIF, "\
                    " VDMOVIM.MODULOMODIF,VDMOVIM.ACCIONMODIF,VDMOVIM.FECMODIF, "\
                    " VDMOVIM.HORAMODIF,VDMOVIM.CODBULTOORI,VDMOVIM.CODBULTODEST "\
        " FROM VDMOVIM"\
        " WHERE "\
               " VDMOVIM.CODMOV=:CODMOV "
static v10cursors *vdselmovvdmovim;

#define SELMOVROWIDLOCK "SELECT ROWID,CODMOV,CODCONCE,DATOSHOST,CODUBIORI,CODUBITEMP,CODUBIDEST, "\
                    " CODMATORI,CODMATTEMP,CODMATDEST,TIPOCONTE,PRIOMOV,TAREA,CODRECURSO, "\
                    " SOLOMUEVE,CODMOVESP,CODMOVPPASO,CODDOCUMENTO,CODINTERFASE,CODPREPARACION,STATUS, "\
                    " BULTO,CODART,CODLOT,CANTIDAD,BLOQUEOSORI,BLOQUEOSDEST,TIPOEMBA, "\
                    " UNIEMB,EMBCONT,MARCASTK,NUMEROSERIE,PRECIOUNI,PESOUNI,CODRECEP, "\
                    " CODFLUJO,TIPODEMANDA,CODDEMANDA,LINDEMANDA,CODOPEINS,MODULOINS,ACCIONINS, "\
                    " FECINS,HORAINS,MODULOPLANMOV,ACCIONPLANMOV,FECPLANMOV,HORAPLANMOV,CODOPEEJEMOV, "\
                    " MODULOINIMOV,ACCIONINIMOV,FECINIMOV,HORAINIMOV,MODULOFINMOV,ACCIONFINMOV,FECFINMOV, "\
                    " HORAFINMOV,VDEXTRA,CODCOMEN,CODOPEMODIF,MODULOMODIF,ACCIONMODIF,FECMODIF, "\
                    " HORAMODIF,CODBULTOORI,CODBULTODEST "\
        " FROM VDMOVIM "\
        " WHERE ROWID=:MIROWID "\
     " FOR UPDATE NOWAIT "
static v10cursors *vdselmovrowidlock;

#define UPDAMOVREENGANCHAMOV "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " CODUBIORI=:CODUBIORI , "\
               " CODMATORI=:CODMATORI , "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovreenganchamov;

#define UPDAMOVRUTA "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " STATUS=:STATUS , "\
               " CODMOVPPASO=:CODMOVPPASO , "\
               " CODMOVESP=:CODMOVESP  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovruta;

#define UPDAMOVSTATUS "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " STATUS=:STATUS  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovstatus;

#define UPDAMOVORIGEN "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " CODMATORI=:CODMATORI , "\
               " CODUBIORI=:CODUBIORI  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovorigen;

#define UPDAMOVDESTINO "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " CODMATDEST=:CODMATDEST , "\
               " CODUBIDEST=:CODUBIDEST  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovdestino;

#define UPDAMOVCANTIDAD "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " CANTIDAD=:CANTIDAD  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovcantidad;

#define UPDAMOVDEMANDA "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " TIPODEMANDA=:TIPODEMANDA , "\
               " CODDEMANDA=:CODDEMANDA , "\
               " LINDEMANDA=:LINDEMANDA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovdemanda;

#define UPDAMOVMATRICULAS "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " CODMATORI=:CODMATORI , "\
               " CODMATDEST=:CODMATDEST  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovmatriculas;

#define UPDAMOVTAREA "UPDATE VDMOVIM SET  FECMODIF=VD.FECHASYS,  HORAMODIF=VD.HORASYS,  CODOPEMODIF=VDUSER.GETUSER,  MODULOMODIF=VDUSER.GETMODULO,  ACCIONMODIF=VDUSER.GETACCION,  "\
               " TAREA=:TAREA  "\
                     " WHERE ROWID=:MIROWID "
static v10cursors *vdupdamovtarea;

#define SELVDSECPREP "SELECT VDSECPREP.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecprep;

#define SELVDSECMOVIM "SELECT VDSECMOVIM.NEXTVAL FROM DUAL"
static v10cursors *vdselvdsecmovim;

#define INSMOV "INSERT INTO VDMOVIM (CODMOV,CODCONCE,DATOSHOST,CODUBIORI,CODUBITEMP,CODUBIDEST, "\
                    " CODMATORI,CODMATTEMP,CODMATDEST,TIPOCONTE,PRIOMOV,TAREA,CODRECURSO, "\
                    " SOLOMUEVE,CODMOVESP,CODMOVPPASO,CODDOCUMENTO,CODINTERFASE,CODPREPARACION,STATUS, "\
                    " BULTO,CODART,CODLOT,CANTIDAD,BLOQUEOSORI,BLOQUEOSDEST,TIPOEMBA, "\
                    " UNIEMB,EMBCONT,MARCASTK,NUMEROSERIE,PRECIOUNI,PESOUNI,CODRECEP, "\
                    " CODFLUJO,TIPODEMANDA,CODDEMANDA,LINDEMANDA,CODOPEINS,MODULOINS,ACCIONINS, "\
                    " FECINS,HORAINS,MODULOPLANMOV,ACCIONPLANMOV,FECPLANMOV,HORAPLANMOV,CODOPEEJEMOV, "\
                    " MODULOINIMOV,ACCIONINIMOV,FECINIMOV,HORAINIMOV,MODULOFINMOV,ACCIONFINMOV,FECFINMOV, "\
                    " HORAFINMOV,VDEXTRA,CODCOMEN,CODOPEMODIF,MODULOMODIF,ACCIONMODIF,FECMODIF, "\
                    " HORAMODIF,CODBULTOORI,CODBULTODEST "\
       " ) VALUES ( "\
                    " :CODMOV,:CODCONCE,:DATOSHOST,:CODUBIORI,:CODUBITEMP,:CODUBIDEST, "\
                    " :CODMATORI,:CODMATTEMP,:CODMATDEST,:TIPOCONTE,:PRIOMOV,:TAREA,:CODRECURSO, "\
                    " :SOLOMUEVE,:CODMOVESP,:CODMOVPPASO,:CODDOCUMENTO,:CODINTERFASE,:CODPREPARACION,:STATUS, "\
                    " :BULTO,:CODART,:CODLOT,:CANTIDAD,:BLOQUEOSORI,:BLOQUEOSDEST,:TIPOEMBA, "\
                    " :UNIEMB,:EMBCONT,:MARCASTK,:NUMEROSERIE,:PRECIOUNI,:PESOUNI,:CODRECEP, "\
                    " :CODFLUJO,:TIPODEMANDA,:CODDEMANDA,:LINDEMANDA,VDUSER.GETUSER,VDUSER.GETMODULO,VDUSER.GETACCION, "\
                    " VD.FECHASYS,VD.HORASYS,:MODULOPLANMOV,:ACCIONPLANMOV,:FECPLANMOV,:HORAPLANMOV,:CODOPEEJEMOV, "\
                    " :MODULOINIMOV,:ACCIONINIMOV,:FECINIMOV,:HORAINIMOV,:MODULOFINMOV,:ACCIONFINMOV,:FECFINMOV, "\
                    " :HORAFINMOV,:VDEXTRA,:CODCOMEN,VDUSER.GETUSER,VDUSER.GETMODULO,VDUSER.GETACCION,VD.FECHASYS, "\
                    " VD.HORASYS,:CODBULTOORI,:CODBULTODEST) "
static v10cursors *vdinsmov;

#define DELMOV "DELETE VDMOVIM WHERE ROWID=:MIROWID "
static v10cursors *vddelmov;

static vdmovims svdmovim;

static diccols colvdmovim[]={
	{"ROWID",V10CADENA,(size_t)&svdmovim.rowid,sizeof(svdmovim.rowid)},
	{"CODMOV",V10LONG,(size_t)&svdmovim.codmov,sizeof(svdmovim.codmov)},
	{"CODCONCE",V10CADENA,(size_t)&svdmovim.codconce,sizeof(svdmovim.codconce)},
	{"DATOSHOST",V10CADENA,(size_t)&svdmovim.datoshost,sizeof(svdmovim.datoshost)},
	{"CODUBIORI",V10CADENA,(size_t)&svdmovim.codubiori,sizeof(svdmovim.codubiori)},
	{"CODUBITEMP",V10CADENA,(size_t)&svdmovim.codubitemp,sizeof(svdmovim.codubitemp)},
	{"CODUBIDEST",V10CADENA,(size_t)&svdmovim.codubidest,sizeof(svdmovim.codubidest)},
	{"CODMATORI",V10CADENA,(size_t)&svdmovim.codmatori,sizeof(svdmovim.codmatori)},
	{"CODMATTEMP",V10CADENA,(size_t)&svdmovim.codmattemp,sizeof(svdmovim.codmattemp)},
	{"CODMATDEST",V10CADENA,(size_t)&svdmovim.codmatdest,sizeof(svdmovim.codmatdest)},
	{"TIPOCONTE",V10CADENA,(size_t)&svdmovim.tipoconte,sizeof(svdmovim.tipoconte)},
	{"PRIOMOV",V10LONG,(size_t)&svdmovim.priomov,sizeof(svdmovim.priomov)},
	{"TAREA",V10CADENA,(size_t)&svdmovim.tarea,sizeof(svdmovim.tarea)},
	{"CODRECURSO",V10CADENA,(size_t)&svdmovim.codrecurso,sizeof(svdmovim.codrecurso)},
	{"SOLOMUEVE",V10CADENA,(size_t)&svdmovim.solomueve,sizeof(svdmovim.solomueve)},
	{"CODMOVESP",V10LONG,(size_t)&svdmovim.codmovesp,sizeof(svdmovim.codmovesp)},
	{"CODMOVPPASO",V10LONG,(size_t)&svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso)},
	{ "CODDOCUMENTO", V10CADENA, (size_t)&svdmovim.coddocumento, sizeof(svdmovim.coddocumento) },
	{"CODINTERFASE",V10LONG,(size_t)&svdmovim.codinterfase,sizeof(svdmovim.codinterfase)},
	{"CODPREPARACION",V10LONG,(size_t)&svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion)},
	{"STATUS",V10LONG,(size_t)&svdmovim.status,sizeof(svdmovim.status)},
	{"BULTO",V10CADENA,(size_t)&svdmovim.bulto,sizeof(svdmovim.bulto)},
	{"CODART",V10CADENA,(size_t)&svdmovim.codart,sizeof(svdmovim.codart)},
	{"CODLOT",V10CADENA,(size_t)&svdmovim.codlot,sizeof(svdmovim.codlot)},
	{"CANTIDAD",V10DOUBLE,(size_t)&svdmovim.cantidad,sizeof(svdmovim.cantidad)},
	{"BLOQUEOSORI",V10CADENA,(size_t)&svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori)},
	{"BLOQUEOSDEST",V10CADENA,(size_t)&svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest)},
	{"TIPOEMBA",V10CADENA,(size_t)&svdmovim.tipoemba,sizeof(svdmovim.tipoemba)},
	{"UNIEMB",V10DOUBLE,(size_t)&svdmovim.uniemb,sizeof(svdmovim.uniemb)},
	{"EMBCONT",V10LONG,(size_t)&svdmovim.embcont,sizeof(svdmovim.embcont)},
	{"MARCASTK",V10CADENA,(size_t)&svdmovim.marcastk,sizeof(svdmovim.marcastk)},
	{"NUMEROSERIE",V10CADENA,(size_t)&svdmovim.numeroserie,sizeof(svdmovim.numeroserie)},
	{"PRECIOUNI",V10DOUBLE,(size_t)&svdmovim.preciouni,sizeof(svdmovim.preciouni)},
	{"PESOUNI",V10DOUBLE,(size_t)&svdmovim.pesouni,sizeof(svdmovim.pesouni)},
	{"CODRECEP",V10CADENA,(size_t)&svdmovim.codrecep,sizeof(svdmovim.codrecep)},
	{"CODFLUJO",V10LONG,(size_t)&svdmovim.codflujo,sizeof(svdmovim.codflujo)},
	{"TIPODEMANDA",V10CADENA,(size_t)&svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda)},
	{"CODDEMANDA",V10CADENA,(size_t)&svdmovim.coddemanda,sizeof(svdmovim.coddemanda)},
	{"LINDEMANDA",V10LONG,(size_t)&svdmovim.lindemanda,sizeof(svdmovim.lindemanda)},
	{"CODOPEINS",V10CADENA,(size_t)&svdmovim.codopeins,sizeof(svdmovim.codopeins)},
	{"MODULOINS",V10CADENA,(size_t)&svdmovim.moduloins,sizeof(svdmovim.moduloins)},
	{"ACCIONINS",V10CADENA,(size_t)&svdmovim.accionins,sizeof(svdmovim.accionins)},
	{"FECINS",V10LONG,(size_t)&svdmovim.fecins,sizeof(svdmovim.fecins)},
	{"HORAINS",V10CADENA,(size_t)&svdmovim.horains,sizeof(svdmovim.horains)},
	{"MODULOPLANMOV",V10CADENA,(size_t)&svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov)},
	{"ACCIONPLANMOV",V10CADENA,(size_t)&svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov)},
	{"FECPLANMOV",V10LONG,(size_t)&svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov)},
	{"HORAPLANMOV",V10CADENA,(size_t)&svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov)},
	{"CODOPEEJEMOV",V10CADENA,(size_t)&svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov)},
	{"MODULOINIMOV",V10CADENA,(size_t)&svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov)},
	{"ACCIONINIMOV",V10CADENA,(size_t)&svdmovim.accioninimov,sizeof(svdmovim.accioninimov)},
	{"FECINIMOV",V10LONG,(size_t)&svdmovim.fecinimov,sizeof(svdmovim.fecinimov)},
	{"HORAINIMOV",V10CADENA,(size_t)&svdmovim.horainimov,sizeof(svdmovim.horainimov)},
	{"MODULOFINMOV",V10CADENA,(size_t)&svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov)},
	{"ACCIONFINMOV",V10CADENA,(size_t)&svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov)},
	{"FECFINMOV",V10LONG,(size_t)&svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov)},
	{"HORAFINMOV",V10CADENA,(size_t)&svdmovim.horafinmov,sizeof(svdmovim.horafinmov)},
	{"VDEXTRA",V10CADENA,(size_t)&svdmovim.vdextra,sizeof(svdmovim.vdextra)},
	{"CODCOMEN",V10LONG,(size_t)&svdmovim.codcomen,sizeof(svdmovim.codcomen)},
	{"CODOPEMODIF",V10CADENA,(size_t)&svdmovim.codopemodif,sizeof(svdmovim.codopemodif)},
	{"MODULOMODIF",V10CADENA,(size_t)&svdmovim.modulomodif,sizeof(svdmovim.modulomodif)},
	{"ACCIONMODIF",V10CADENA,(size_t)&svdmovim.accionmodif,sizeof(svdmovim.accionmodif)},
	{"FECMODIF",V10LONG,(size_t)&svdmovim.fecmodif,sizeof(svdmovim.fecmodif)},
	{"HORAMODIF",V10CADENA,(size_t)&svdmovim.horamodif,sizeof(svdmovim.horamodif)},
	{"CODBULTOORI",V10CADENA,(size_t)&svdmovim.codbultoori,sizeof(svdmovim.codbultoori)},
	{"CODBULTODEST",V10CADENA,(size_t)&svdmovim.codbultodest,sizeof(svdmovim.codbultodest)},
	{"STATUS1",V10LONG,(size_t)&svdmovim.status1,sizeof(svdmovim.status1)},
	{"STATUS2",V10LONG,(size_t)&svdmovim.status2,sizeof(svdmovim.status2)},
	{"COMEN",V10CADENA,(size_t)&svdmovim.comen,sizeof(svdmovim.comen)},
	{"MOVERPALET",V10CADENA,(size_t)&svdmovim.moverpalet,sizeof(svdmovim.moverpalet)}
	};
static diccionarios dvdmovim[]={
    {colvdmovim,70}
};
diccionario dmov={dvdmovim,1};

static char msglogMOV[LCADENA];
static char msgdebugMOV[LCADENABIG];
static int init=0;


static void fin_vd_mov(void)
{
if (vdselmovmismopalet) {
    liberacursor(vdselmovmismopalet);
    vdselmovmismopalet = NULL;
}
if (vdselmovcodmovesp) {
    liberacursor(vdselmovcodmovesp);
    vdselmovcodmovesp = NULL;
}
if (vdselmovstatus) {
    liberacursor(vdselmovstatus);
    vdselmovstatus = NULL;
}
if (vdselmovstatusartmat) {
    liberacursor(vdselmovstatusartmat);
    vdselmovstatusartmat = NULL;
}
if (vdselmovdemanda) {
    liberacursor(vdselmovdemanda);
    vdselmovdemanda = NULL;
}
if (vdselmovmovtostarea) {
    liberacursor(vdselmovmovtostarea);
    vdselmovmovtostarea = NULL;
}
if (vdselmovvdmovim) {
    liberacursor(vdselmovvdmovim);
    vdselmovvdmovim = NULL;
}
if (vdselmovrowidlock) {
    liberacursor(vdselmovrowidlock);
    vdselmovrowidlock = NULL;
}
if (vdupdamovreenganchamov) {
    liberacursor(vdupdamovreenganchamov);
    vdupdamovreenganchamov = NULL;
}
if (vdupdamovruta) {
    liberacursor(vdupdamovruta);
    vdupdamovruta = NULL;
}
if (vdupdamovstatus) {
    liberacursor(vdupdamovstatus);
    vdupdamovstatus = NULL;
}
if (vdupdamovorigen) {
    liberacursor(vdupdamovorigen);
    vdupdamovorigen = NULL;
}
if (vdupdamovdestino) {
    liberacursor(vdupdamovdestino);
    vdupdamovdestino = NULL;
}
if (vdupdamovcantidad) {
    liberacursor(vdupdamovcantidad);
    vdupdamovcantidad = NULL;
}
if (vdupdamovdemanda) {
    liberacursor(vdupdamovdemanda);
    vdupdamovdemanda = NULL;
}
if (vdupdamovmatriculas) {
    liberacursor(vdupdamovmatriculas);
    vdupdamovmatriculas = NULL;
}
if (vdupdamovtarea) {
    liberacursor(vdupdamovtarea);
    vdupdamovtarea = NULL;
}
if (vdselvdsecprep != NULL) {
    liberacursor(vdselvdsecprep);
    vdselvdsecprep = NULL;
}
if (vdselvdsecmovim != NULL) {
    liberacursor(vdselvdsecmovim);
    vdselvdsecmovim = NULL;
}
if (vdinsmov != NULL) {
    liberacursor(vdinsmov);
    vdinsmov = NULL;
}
if (vddelmov != NULL) {
    liberacursor(vddelmov);
    vddelmov = NULL;
}
}
static void init_selmovmismopalet(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovmismopalet=abrecursordebug(SELMOVMISMOPALET,1280);
    definetodo(vdselmovmismopalet,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovmismopalet,"CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "MOVERPALET",svdmovim.moverpalet,sizeof(svdmovim.moverpalet),V10CADENA,
                          "CODMOV",&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          "STATUS1",&svdmovim.status1,sizeof(svdmovim.status1),V10LONG,
                          "STATUS2",&svdmovim.status2,sizeof(svdmovim.status2),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovcodmovesp(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovcodmovesp=abrecursordebug(SELMOVCODMOVESP,1280);
    definetodo(vdselmovcodmovesp,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovcodmovesp,"CODMOV",&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovstatus=abrecursordebug(SELMOVSTATUS,1280);
    definetodo(vdselmovstatus,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovstatus,"STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovstatusartmat(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovstatusartmat=abrecursordebug(SELMOVSTATUSARTMAT,1280);
    definetodo(vdselmovstatusartmat,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovstatusartmat,"STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovdemanda(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovdemanda=abrecursordebug(SELMOVDEMANDA,1280);
    definetodo(vdselmovdemanda,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovdemanda,"TIPODEMANDA",svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          "CODDEMANDA",svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovmovtostarea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovmovtostarea=abrecursordebug(SELMOVMOVTOSTAREA,1280);
    definetodo(vdselmovmovtostarea,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovmovtostarea,"CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "CODMOV",&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          "STATUS1",&svdmovim.status1,sizeof(svdmovim.status1),V10LONG,
                          "TAREA",svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovvdmovim(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovvdmovim=abrecursordebug(SELMOVVDMOVIM,1280);
    definetodo(vdselmovvdmovim,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovvdmovim,"CODMOV",&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selmovrowidlock(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselmovrowidlock=abrecursordebug(SELMOVROWIDLOCK,1280);
    definetodo(vdselmovrowidlock,svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          &svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          &svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          &svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          &svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          &svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          &svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          &svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          &svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          &svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          &svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          &svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          &svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          &svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          &svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          svdmovim.codopeins,sizeof(svdmovim.codopeins),V10CADENA,
                          svdmovim.moduloins,sizeof(svdmovim.moduloins),V10CADENA,
                          svdmovim.accionins,sizeof(svdmovim.accionins),V10CADENA,
                          &svdmovim.fecins,sizeof(svdmovim.fecins),V10LONG,
                          svdmovim.horains,sizeof(svdmovim.horains),V10CADENA,
                          svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          &svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          &svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          &svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          &svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          svdmovim.codopemodif,sizeof(svdmovim.codopemodif),V10CADENA,
                          svdmovim.modulomodif,sizeof(svdmovim.modulomodif),V10CADENA,
                          svdmovim.accionmodif,sizeof(svdmovim.accionmodif),V10CADENA,
                          &svdmovim.fecmodif,sizeof(svdmovim.fecmodif),V10LONG,
                          svdmovim.horamodif,sizeof(svdmovim.horamodif),V10CADENA,
                          svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    bindtodo(vdselmovrowidlock,"MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovreenganchamov(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovreenganchamov=abrecursordebug(UPDAMOVREENGANCHAMOV,1280);
    bindtodo(vdupdamovreenganchamov,"CODUBIORI",svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          "CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovruta(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovruta=abrecursordebug(UPDAMOVRUTA,1280);
    bindtodo(vdupdamovruta,"STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          "CODMOVPPASO",&svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
                          "CODMOVESP",&svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovstatus(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovstatus=abrecursordebug(UPDAMOVSTATUS,1280);
    bindtodo(vdupdamovstatus,"STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovorigen(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovorigen=abrecursordebug(UPDAMOVORIGEN,1280);
    bindtodo(vdupdamovorigen,"CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "CODUBIORI",svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovdestino(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovdestino=abrecursordebug(UPDAMOVDESTINO,1280);
    bindtodo(vdupdamovdestino,"CODMATDEST",svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          "CODUBIDEST",svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovcantidad(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovcantidad=abrecursordebug(UPDAMOVCANTIDAD,1280);
    bindtodo(vdupdamovcantidad,"CANTIDAD",&svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovdemanda(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovdemanda=abrecursordebug(UPDAMOVDEMANDA,1280);
    bindtodo(vdupdamovdemanda,"TIPODEMANDA",svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          "CODDEMANDA",svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          "LINDEMANDA",&svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovmatriculas(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovmatriculas=abrecursordebug(UPDAMOVMATRICULAS,1280);
    bindtodo(vdupdamovmatriculas,"CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "CODMATDEST",svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_updamovtarea(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdupdamovtarea=abrecursordebug(UPDAMOVTAREA,1280);
    bindtodo(vdupdamovtarea,"TAREA",svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          "MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selvdsecprep(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselvdsecprep=abrecursordebug(SELVDSECPREP,1280);
    definetodo(vdselvdsecprep,&svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_selvdsecmovim(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdselvdsecmovim=abrecursordebug(SELVDSECMOVIM,1280);
    definetodo(vdselvdsecmovim,&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_insmov(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vdinsmov=abrecursordebug(INSMOV,1280);
    bindtodo(vdinsmov,"CODMOV",&svdmovim.codmov,sizeof(svdmovim.codmov),V10LONG,
                          "CODCONCE",svdmovim.codconce,sizeof(svdmovim.codconce),V10CADENA,
                          "DATOSHOST",svdmovim.datoshost,sizeof(svdmovim.datoshost),V10CADENA,
                          "CODUBIORI",svdmovim.codubiori,sizeof(svdmovim.codubiori),V10CADENA,
                          "CODUBITEMP",svdmovim.codubitemp,sizeof(svdmovim.codubitemp),V10CADENA,
                          "CODUBIDEST",svdmovim.codubidest,sizeof(svdmovim.codubidest),V10CADENA,
                          "CODMATORI",svdmovim.codmatori,sizeof(svdmovim.codmatori),V10CADENA,
                          "CODMATTEMP",svdmovim.codmattemp,sizeof(svdmovim.codmattemp),V10CADENA,
                          "CODMATDEST",svdmovim.codmatdest,sizeof(svdmovim.codmatdest),V10CADENA,
                          "TIPOCONTE",svdmovim.tipoconte,sizeof(svdmovim.tipoconte),V10CADENA,
                          "PRIOMOV",&svdmovim.priomov,sizeof(svdmovim.priomov),V10LONG,
                          "TAREA",svdmovim.tarea,sizeof(svdmovim.tarea),V10CADENA,
                          "CODRECURSO",svdmovim.codrecurso,sizeof(svdmovim.codrecurso),V10CADENA,
                          "SOLOMUEVE",svdmovim.solomueve,sizeof(svdmovim.solomueve),V10CADENA,
                          "CODMOVESP",&svdmovim.codmovesp,sizeof(svdmovim.codmovesp),V10LONG,
                          "CODMOVPPASO",&svdmovim.codmovppaso,sizeof(svdmovim.codmovppaso),V10LONG,
						  "CODDOCUMENTO", svdmovim.coddocumento, sizeof(svdmovim.coddocumento), V10CADENA,
                          "CODINTERFASE",&svdmovim.codinterfase,sizeof(svdmovim.codinterfase),V10LONG,
                          "CODPREPARACION",&svdmovim.codpreparacion,sizeof(svdmovim.codpreparacion),V10LONG,
                          "STATUS",&svdmovim.status,sizeof(svdmovim.status),V10LONG,
                          "BULTO",svdmovim.bulto,sizeof(svdmovim.bulto),V10CADENA,
                          "CODART",svdmovim.codart,sizeof(svdmovim.codart),V10CADENA,
                          "CODLOT",svdmovim.codlot,sizeof(svdmovim.codlot),V10CADENA,
                          "CANTIDAD",&svdmovim.cantidad,sizeof(svdmovim.cantidad),V10DOUBLE,
                          "BLOQUEOSORI",svdmovim.bloqueosori,sizeof(svdmovim.bloqueosori),V10CADENA,
                          "BLOQUEOSDEST",svdmovim.bloqueosdest,sizeof(svdmovim.bloqueosdest),V10CADENA,
                          "TIPOEMBA",svdmovim.tipoemba,sizeof(svdmovim.tipoemba),V10CADENA,
                          "UNIEMB",&svdmovim.uniemb,sizeof(svdmovim.uniemb),V10DOUBLE,
                          "EMBCONT",&svdmovim.embcont,sizeof(svdmovim.embcont),V10LONG,
                          "MARCASTK",svdmovim.marcastk,sizeof(svdmovim.marcastk),V10CADENA,
                          "NUMEROSERIE",svdmovim.numeroserie,sizeof(svdmovim.numeroserie),V10CADENA,
                          "PRECIOUNI",&svdmovim.preciouni,sizeof(svdmovim.preciouni),V10DOUBLE,
                          "PESOUNI",&svdmovim.pesouni,sizeof(svdmovim.pesouni),V10DOUBLE,
                          "CODRECEP",svdmovim.codrecep,sizeof(svdmovim.codrecep),V10CADENA,
                          "CODFLUJO",&svdmovim.codflujo,sizeof(svdmovim.codflujo),V10LONG,
                          "TIPODEMANDA",svdmovim.tipodemanda,sizeof(svdmovim.tipodemanda),V10CADENA,
                          "CODDEMANDA",svdmovim.coddemanda,sizeof(svdmovim.coddemanda),V10CADENA,
                          "LINDEMANDA",&svdmovim.lindemanda,sizeof(svdmovim.lindemanda),V10LONG,
                          "MODULOPLANMOV",svdmovim.moduloplanmov,sizeof(svdmovim.moduloplanmov),V10CADENA,
                          "ACCIONPLANMOV",svdmovim.accionplanmov,sizeof(svdmovim.accionplanmov),V10CADENA,
                          "FECPLANMOV",&svdmovim.fecplanmov,sizeof(svdmovim.fecplanmov),V10LONG,
                          "HORAPLANMOV",svdmovim.horaplanmov,sizeof(svdmovim.horaplanmov),V10CADENA,
                          "CODOPEEJEMOV",svdmovim.codopeejemov,sizeof(svdmovim.codopeejemov),V10CADENA,
                          "MODULOINIMOV",svdmovim.moduloinimov,sizeof(svdmovim.moduloinimov),V10CADENA,
                          "ACCIONINIMOV",svdmovim.accioninimov,sizeof(svdmovim.accioninimov),V10CADENA,
                          "FECINIMOV",&svdmovim.fecinimov,sizeof(svdmovim.fecinimov),V10LONG,
                          "HORAINIMOV",svdmovim.horainimov,sizeof(svdmovim.horainimov),V10CADENA,
                          "MODULOFINMOV",svdmovim.modulofinmov,sizeof(svdmovim.modulofinmov),V10CADENA,
                          "ACCIONFINMOV",svdmovim.accionfinmov,sizeof(svdmovim.accionfinmov),V10CADENA,
                          "FECFINMOV",&svdmovim.fecfinmov,sizeof(svdmovim.fecfinmov),V10LONG,
                          "HORAFINMOV",svdmovim.horafinmov,sizeof(svdmovim.horafinmov),V10CADENA,
                          "VDEXTRA",svdmovim.vdextra,sizeof(svdmovim.vdextra),V10CADENA,
                          "CODCOMEN",&svdmovim.codcomen,sizeof(svdmovim.codcomen),V10LONG,
                          "CODBULTOORI",svdmovim.codbultoori,sizeof(svdmovim.codbultoori),V10CADENA,
                          "CODBULTODEST",svdmovim.codbultodest,sizeof(svdmovim.codbultodest),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

static void init_delmov(void)
{
    int nc;

    if (init == 0) for (nc=0;nc<dvdmovim[0].numcol;nc++) dvdmovim[0].c[nc].offset-=(size_t)&svdmovim;
    vddelmov=abrecursordebug(DELMOV,1280);
    bindtodo(vddelmov,"MIROWID",svdmovim.rowid,sizeof(svdmovim.rowid),V10CADENA,
                          NULL);
    if (init == 0) {
        atexit(fin_vd_mov);
        init = 1;
    }
}

diccionario *MOVdamediccionario(void)
{
     return(&dmov);
}

int MOVbuscamismopalet(char *codmatori,char *moverpalet,long codmov,long status1,long status2,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  strcpy(svdmovim.codmatori,codmatori);
  strcpy(svdmovim.moverpalet,moverpalet);
  svdmovim.codmov=codmov;
  svdmovim.status1=status1;
  svdmovim.status2=status2;
  if (vdselmovmismopalet==NULL) init_selmovmismopalet();
  vdret=ejefetchcursor(vdselmovmismopalet);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovmismopalet. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextmismopalet(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovmismopalet);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovmismopalet. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovmismopalet);
  return(VD_EERRORACLE);
}

int MOVbuscacodmovesp(long codmov,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  svdmovim.codmov=codmov;
  if (vdselmovcodmovesp==NULL) init_selmovcodmovesp();
  vdret=ejefetchcursor(vdselmovcodmovesp);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovcodmovesp. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextcodmovesp(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovcodmovesp);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovcodmovesp. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovcodmovesp);
  return(VD_EERRORACLE);
}

int MOVbuscastatus(long status,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  svdmovim.status=status;
  if (vdselmovstatus==NULL) init_selmovstatus();
  vdret=ejefetchcursor(vdselmovstatus);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovstatus. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextstatus(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovstatus);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovstatus. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovstatus);
  return(VD_EERRORACLE);
}

int MOVbuscastatusartmat(long status,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  svdmovim.status=status;
  if (vdselmovstatusartmat==NULL) init_selmovstatusartmat();
  vdret=ejefetchcursor(vdselmovstatusartmat);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovstatusartmat. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextstatusartmat(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovstatusartmat);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovstatusartmat. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovstatusartmat);
  return(VD_EERRORACLE);
}

int MOVbuscademanda(char *tipodemanda,char *coddemanda,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  strcpy(svdmovim.tipodemanda,tipodemanda);
  strcpy(svdmovim.coddemanda,coddemanda);
  if (vdselmovdemanda==NULL) init_selmovdemanda();
  vdret=ejefetchcursor(vdselmovdemanda);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovdemanda. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextdemanda(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovdemanda);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovdemanda. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovdemanda);
  return(VD_EERRORACLE);
}

int MOVbuscamovtostarea(char *codmatori,long codmov,long status1,char *tarea,vdmovims *mov)
{
  int vdret;
  memset(&svdmovim,0,sizeof(svdmovim));
  strcpy(svdmovim.codmatori,codmatori);
  svdmovim.codmov=codmov;
  svdmovim.status1=status1;
  strcpy(svdmovim.tarea,tarea);
  if (vdselmovmovtostarea==NULL) init_selmovmovtostarea();
  vdret=ejefetchcursor(vdselmovmovtostarea);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Encontrado primero %s vdselmovmovtostarea. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  return(VD_EERRORACLE);
}

int MOVnextmovtostarea(vdmovims *mov)
{
  int vdret;
  vdret=fetchcursor(vdselmovmovtostarea);
  if (vdret==0) {
     *mov=svdmovim;
    v10log(LOGDEBUGAPI,"Siguiente %s vdselmovmovtostarea. vdret %d. \n",MOVlog(&svdmovim),vdret);
     return(0);
   }
  if (vdret!=NOFOUND) cursordebug(vdselmovmovtostarea);
  return(VD_EERRORACLE);
}

int MOVselvdmovim(long codmov,vdmovims *mov)
{
  int vdret;
  if (vdselmovvdmovim==NULL) init_selmovvdmovim();
  memset(&svdmovim,0,sizeof(svdmovim));
  svdmovim.codmov=codmov;
  vdret=ejefetchcursor(vdselmovvdmovim);
  if (vdret) {
    v10log(LOGDEBUGAPI,"Ejefetch %s vdselmovvdmovim. vdret %d. \n",MOVlog(&svdmovim),vdret);
    return(VD_EERRORACLE);
   }
  *mov=svdmovim;
  return(vdret);
}

int MOVlock(vdmovims *mov,int wait,int verificar,...)
{
    int vdret;
    va_list arg;
    svdmovim=*mov;
    if (vdselmovrowidlock==NULL) init_selmovrowidlock();
    savepoint("lockvdmovim");
    while (1) {
        vdret=ejefetchcursor(vdselmovrowidlock);
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
    vdret=vverificacampos(mov,&svdmovim,&dvdmovim[0],arg);
    va_end(arg);
    if (vdret!=0) rollbacksavepoint("lockvdmovim");
    return(vdret);
}

int MOVactualizareenganchamov(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizareenganchamov:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovreenganchamov==NULL) init_updamovreenganchamov();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovreenganchamov);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovreenganchamov);
     getcurerrornombre(vdupdamovreenganchamov->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovreenganchamov)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizaruta(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizaruta:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovruta==NULL) init_updamovruta();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovruta);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovruta);
     getcurerrornombre(vdupdamovruta->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovruta)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizastatus(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizastatus:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovstatus==NULL) init_updamovstatus();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovstatus);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovstatus);
     getcurerrornombre(vdupdamovstatus->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovstatus)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizaorigen(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizaorigen:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovorigen==NULL) init_updamovorigen();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovorigen);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovorigen);
     getcurerrornombre(vdupdamovorigen->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovorigen)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizadestino(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizadestino:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovdestino==NULL) init_updamovdestino();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovdestino);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovdestino);
     getcurerrornombre(vdupdamovdestino->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovdestino)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizacantidad(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizacantidad:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovcantidad==NULL) init_updamovcantidad();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovcantidad);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovcantidad);
     getcurerrornombre(vdupdamovcantidad->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovcantidad)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizademanda(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizademanda:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovdemanda==NULL) init_updamovdemanda();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovdemanda);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovdemanda);
     getcurerrornombre(vdupdamovdemanda->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovdemanda)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizamatriculas(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizamatriculas:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovmatriculas==NULL) init_updamovmatriculas();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovmatriculas);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovmatriculas);
     getcurerrornombre(vdupdamovmatriculas->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovmatriculas)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVactualizatarea(vdmovims *mov,int error)
{
  int vdret = 0;
    v10log(LOGDEBUGAPI,"Actualizando MOVactualizatarea:  %s .  \n",MOVlog(&svdmovim));
  if (vdupdamovtarea==NULL) init_updamovtarea();
  svdmovim=*mov;
  vdret=ejecutacursor(vdupdamovtarea);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdupdamovtarea);
     getcurerrornombre(vdupdamovtarea->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  if (procesadascursor(vdupdamovtarea)!=1) return(VD_EERRORACLE);
  return(0);
}

int MOVselvdsecprep(long *donde)
{
  int vdret;
  if (!vdselvdsecprep) init_selvdsecprep();
  vdret=ejefetchcursor(vdselvdsecprep);
  if (!vdret) {
     *donde=svdmovim.codpreparacion;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int MOVselvdsecmovim(long *donde)
{
  int vdret;
  if (!vdselvdsecmovim) init_selvdsecmovim();
  vdret=ejefetchcursor(vdselvdsecmovim);
  if (!vdret) {
     *donde=svdmovim.codmov;
     return(vdret);
   }
  *donde=0;
  return(VD_EERRORACLE);
}

int MOVinsert(vdmovims *mov,int error)
{
  int vdret;
  if (!vdinsmov) init_insmov();
  if (!mov->codpreparacion) {
     if ((vdret=MOVselvdsecprep(&(mov->codpreparacion)))!=0) return(vdret);
   }
  if (!mov->codmov) {
     if ((vdret=MOVselvdsecmovim(&(mov->codmov)))!=0) return(vdret);
   }
    v10log(LOGDEBUGAPI,"Insertando %s .  \n",MOVlog(&svdmovim));
  svdmovim=*mov;
  vdret=ejecutacursor(vdinsmov);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vdinsmov);
     getcurerrornombre(vdinsmov->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

int MOVdel(vdmovims *mov,int error)
{
  int vdret;
  svdmovim=*mov;
  if (vddelmov==NULL) init_delmov();
    v10log(LOGDEBUGAPI,"Borrando %s .  \n",MOVlog(&svdmovim));
  vdret=ejecutacursor(vddelmov);
  if (vdret) {
     char mensajeerror[MAXCADENA]="";
     if (error==1) cursordebug(vddelmov);
     getcurerrornombre(vddelmov->nombre,mensajeerror);
     v10log(LOGERROR,"%s\n",mensajeerror);
     return(VD_EERRORACLE);
  }
  return(0);
}

char * MOVlog(vdmovims *mov)
{
    sprintf(msglogMOV, "VDMOVIM: codmov %ld ",mov->codmov);
    return(msglogMOV);
}

char * MOVdebug(vdmovims *mov)
{
    debugestruct(&dmov,mov,msgdebugMOV);
    return(msgdebugMOV);
}

