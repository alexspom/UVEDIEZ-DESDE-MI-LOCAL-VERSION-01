// Modulo generado automaticamente a partir de VDUBICAR.DEF
//#***
//# UBICAR.DEF - Generaci�n autom�tica del c�digo c SOLOQUERY para ubicador
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 11-12-2007                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=UBICAR;
//EXTRA=CUANTOS,V10LONG;
//EXTRA=VERIFICACOMP,V10CADENA,2;
//EXTRA=VEFIFICAFLP,V10CADENA,2;
//
//CURSOR=CONTEAUBICAR, SELECT CNT.CODMAT FROM VDCONTE CNT,VDUBICA UBI,  VDTIPOCONTE TCNT, VDAREA ARE   
//                         WHERE
//                            UBI.CODUBI = CNT.CODUBI AND
//                            UBI.TRANSITO='S' AND
//                            CNT.STATUS=0 AND
//                            CNT.TIPOCONTE = TCNT.TIPOCONTE AND
//                            TCNT.MOVIBLE='S' AND
//                            UBI.CODAREA = ARE.CODAREA AND
//                            ARE.CODALM=:VDALMA.CODALM AND
//                            VDSTK.CNTRESERVADO(CNT.CODMAT)=0;
//
//
//
//PROCEDURE=REUBICONTE,BEGIN 
//                       VDUBI.REUBICONTE(:VDCONTE.CODMAT, :VDFLUJOPARAM.TAREA, :VDMOVIM.CODMOV, :VDAREA.CODAREA, :VDUBICA.PASILLO, :VDUBICA.UNIAGRUPAE); 
//                     END;@
//
//PROCEDURE=REUBISTK,BEGIN 
//                         VDUBI.REUBISTK(:VDCONTE.CODMAT, :VDFLUJOPARAM.TAREA, :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB,:VDSTOCK.BLOQUEOS,:VDSTOCK.CANTIDAD, :VDMOVIM.CODMOV, :VDAREA.CODAREA, :VDUBICA.PASILLO, :VDUBICA.UNIAGRUPAE); 
//                       END;@
//
//
//PROCEDURE=CAMBIOUBICONTE,BEGIN 
//                           VDUBI.CAMBIOUBICONTE(:VDCONTE.CODMAT,:VDUBICA.CODUBI,:VDFLUJOPARAM.TAREA,:VDMOVIM.CODMOV,:VEFIFICAFLP,:VERIFICACOMP,:VDMOVIM.CODCONCE,
//                                                :VDMOVIM.PRIOMOV,:VDMOVIM.STATUS,:VDMOVIM.CODRECURSO);
//                         END;@
//                         
//PROCEDURE=CAMBIOUBISTK,BEGIN 
//                           VDUBI.CAMBIOUBISTK(:VDCONTE.CODMAT,:VDUBICA.CODUBI,:VDMOVIM.CODMATDEST,:VDFLUJOPARAM.TAREA,
//                                              :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB,:VDSTOCK.BLOQUEOS,:VDSTOCK.CANTIDAD,
//                                              :VDMOVIM.CODMOV,:VEFIFICAFLP,:VERIFICACOMP,:VDMOVIM.CODCONCE,
//                                              :VDMOVIM.PRIOMOV,:VDMOVIM.STATUS,:VDMOVIM.CODRECURSO);
//                       END;@
//
//PROCEDURE=CREAIDQUERY,BEGIN
//                       VDFLP.CREAIDQUERYDUMMY(:VDCONTE.CODMAT,:VDAREA.CODAREA,:VDAREATMP.IDQUERY);
//                      END;@     
//
//
//
//CURSOR=CONTEPARCIAL,SELECT CODMAT FROM VDCONTE CNT, VDTIPOCONTE TCO 
//                     WHERE CODUBI=:VDUBICA.CODUBI AND
//                           CNT.TIPOCONTE = TCO.TIPOCONTE AND   
//                           TCO.MOVIBLE='N'
//                     ORDER BY CNT.POSCONTE; 
//
//CURSOR=UBILIBRE,SELECT CODUBI FROM TABLE(VDUBI.DAMEUBILIBRE(:VDAREATMP.IDQUERY, :VDCONTE.CODMAT, :VDSTOCK.CODART, :VDSTOCK.CODLOT, :VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS,
//                                                         :VDSTOCK.CANTIDAD,:VDAREA.CODAREA, :VDUBICA.PASILLO, :VDUBICA.UNIAGRUPAE,9999));
//
//CURSOR=UBICOMPATIBLE,SELECT VDCOMP.ESCOMPATIBLE(:VDCONTE.CODMAT,:VDUBICA.CODUBI,:VDSTOCK.CODART, :VDSTOCK.CODLOT, :VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS, :VDSTOCK.CANTIDAD) COMPATIBLE FROM DUAL;
//
//
//%%h
//VDEXPORT int UBIdameubiarealibre(char *codmat,char *codarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,int pasillo,char *uniagrupa,vdubicars *ubicar);
//VDEXPORT int UBIdameubiareaconte(char *codmat,char *codarea,int pasillo, char uniagrupa, char *codubi);
//VDEXPORT int UBIdameubiareastk(char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,int pasillo, char uniagrupa,char *codubi);
//
//%%c      
//VDEXPORT int UBIdameubiarealibre(char *codmat,char *codarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,int pasillo,char *uniagrupa,vdubicars *ubicar)
//{   
//   int ret;
//   ret=UBICARproccreaidquery(codmat,codarea,0,ubicar); 
//   if (ret==0) ret=UBICARbuscaubilibre(ubicar->idquery,codmat,codart,codlot,uniemb,bloqueos,cantidad,codarea,pasillo,uniagrupa,ubicar); 
//   return(ret);
//}  
//
//// devuelve una ubicacion libre para una matr�cula,articulo,lote,cantidad en un �rea
//VDEXPORT int UBIdameubiareaconte(char *codmat,char *codarea,int pasillo, char uniagrupa, char *codubi) {
//  int ret;
//  vdubicars ubicar;
//
//  ret=UBIdameubiarealibre(codmat,codarea,NULL,NULL,0,NULL,0,pasillo,&uniagrupa,&ubicar);
//
//  if (ret) v10log(LOGNORMAL,"dameubiconte: No se encuentra ubicacion para contenedor %lf en area %s\n",codmat,codarea);
//  else v10log(LOGNORMAL,"dameubiconte: Encontrada ubicacion %s para contenedor %lf en area %s\n",ubicar.codubi,codmat,codarea);
//  if (ret==0) strcopia(codubi,ubicar.codubi,strlen(ubicar.codubi));
//  return(ret);
//}
//
//
//// devuelve una ubicacion libre para el stock de una matr�cula,articulo,lote,cantidad en un �rea
//VDEXPORT int UBIdameubiareastk(char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,int pasillo, char uniagrupa,char *codubi) {
//  int ret;
//  vdubicars ubicar;
//
//  ret=UBIdameubiarealibre(codmat,codarea,codart,codlot,uniemb,bloqueos,cantidad,pasillo,&uniagrupa,&ubicar);
// 
//  if (ret) v10log(LOGNORMAL,"dameubistk: No se encuentra ubicacion para contenedor %lf,articulo %s,lote %s y cantidad %ld en area %s\n",codmat,codart,codlot,cantidad,codarea);
//  else v10log(LOGNORMAL,"dameubistk: Encontrada ubicacion %s para contenedor %lf,articulo %s,lote %s y cantidad %ld en area %s\n",ubicar.codubi,codmat,codart,codlot,cantidad,codarea);
//  if (ret==0) strcopia(codubi,ubicar.codubi,strlen(ubicar.codubi));
//  return(ret);  
//}

#include "vd.h"\

#define SELCONTEAUBICAR " SELECT CNT.CODMAT FROM VDCONTE CNT,VDUBICA UBI,  VDTIPOCONTE TCNT, VDAREA ARE    WHERE UBI.CODUBI = CNT.CODUBI AND UBI.TRANSITO='S' AND CNT.STATUS=0 AND CNT.TIPOCONTE = TCNT.TIPOCONTE AND TCNT.MOVIBLE='S' AND UBI.CODAREA = ARE.CODAREA AND ARE.CODALM=:CODALM AND VDSTK.CNTRESERVADO(CNT.CODMAT)=0"
static v10cursors *vdselconteaubicar;
#define SELREUBICONTE "BEGIN  VDUBI.REUBICONTE(:CODMAT, :TAREA, :CODMOV, :CODAREA, :PASILLO, :UNIAGRUPAE);  END;"
static v10cursors *vdselreubiconte;
#define SELREUBISTK "BEGIN  VDUBI.REUBISTK(:CODMAT, :TAREA, :CODART, :CODLOT,:UNIEMB,:BLOQUEOS,:CANTIDAD, :CODMOV, :CODAREA, :PASILLO, :UNIAGRUPAE);  END;"
static v10cursors *vdselreubistk;
#define SELCAMBIOUBICONTE "BEGIN  VDUBI.CAMBIOUBICONTE(:CODMAT,:CODUBI,:TAREA,:CODMOV,:VEFIFICAFLP,:VERIFICACOMP,:CODCONCE, :PRIOMOV,:STATUS,:CODRECURSO); END;"
static v10cursors *vdselcambioubiconte;
#define SELCAMBIOUBISTK "BEGIN  VDUBI.CAMBIOUBISTK(:CODMAT,:CODUBI,:CODMATDEST,:TAREA, :CODART, :CODLOT,:UNIEMB,:BLOQUEOS,:CANTIDAD, :CODMOV,:VEFIFICAFLP,:VERIFICACOMP,:CODCONCE, :PRIOMOV,:STATUS,:CODRECURSO); END;"
static v10cursors *vdselcambioubistk;
#define SELCREAIDQUERY "BEGIN VDFLP.CREAIDQUERYDUMMY(:CODMAT,:CODAREA,:IDQUERY); END;"
static v10cursors *vdselcreaidquery;
#define SELCONTEPARCIAL "SELECT CODMAT FROM VDCONTE CNT, VDTIPOCONTE TCO  WHERE CODUBI=:CODUBI AND CNT.TIPOCONTE = TCO.TIPOCONTE AND    TCO.MOVIBLE='N' ORDER BY CNT.POSCONTE"
static v10cursors *vdselconteparcial;
#define SELUBILIBRE "SELECT CODUBI FROM TABLE(VDUBI.DAMEUBILIBRE(:IDQUERY, :CODMAT, :CODART, :CODLOT, :UNIEMB, :BLOQUEOS, :CANTIDAD,:CODAREA, :PASILLO, :UNIAGRUPAE,9999))"
static v10cursors *vdselubilibre;
#define SELUBICOMPATIBLE "SELECT VDCOMP.ESCOMPATIBLE(:CODMAT,:CODUBI,:CODART, :CODLOT, :UNIEMB, :BLOQUEOS, :CANTIDAD) COMPATIBLE FROM DUAL"
static v10cursors *vdselubicompatible;

static vdubicars svdubicar;

static diccols colvdubicar[]={ 
    {"CUANTOS",V10LONG,(size_t)&svdubicar.cuantos,sizeof(svdubicar.cuantos)},
    {"VERIFICACOMP",V10CADENA,(size_t)&svdubicar.verificacomp,sizeof(svdubicar.verificacomp)},
    {"VEFIFICAFLP",V10CADENA,(size_t)&svdubicar.vefificaflp,sizeof(svdubicar.vefificaflp)},
    {"CODMAT",V10CADENA,(size_t)&svdubicar.codmat,sizeof(svdubicar.codmat)},
    {"CODALM",V10CADENA,(size_t)&svdubicar.codalm,sizeof(svdubicar.codalm)},
    {"TAREA",V10CADENA,(size_t)&svdubicar.tarea,sizeof(svdubicar.tarea)},
    {"CODMOV",V10LONG,(size_t)&svdubicar.codmov,sizeof(svdubicar.codmov)},
    {"CODAREA",V10CADENA,(size_t)&svdubicar.codarea,sizeof(svdubicar.codarea)},
    {"PASILLO",V10LONG,(size_t)&svdubicar.pasillo,sizeof(svdubicar.pasillo)},
    {"UNIAGRUPAE",V10CADENA,(size_t)&svdubicar.uniagrupae,sizeof(svdubicar.uniagrupae)},
    {"CODART",V10CADENA,(size_t)&svdubicar.codart,sizeof(svdubicar.codart)},
    {"CODLOT",V10CADENA,(size_t)&svdubicar.codlot,sizeof(svdubicar.codlot)},
    {"UNIEMB",V10DOUBLE,(size_t)&svdubicar.uniemb,sizeof(svdubicar.uniemb)},
    {"BLOQUEOS",V10CADENA,(size_t)&svdubicar.bloqueos,sizeof(svdubicar.bloqueos)},
    {"CANTIDAD",V10DOUBLE,(size_t)&svdubicar.cantidad,sizeof(svdubicar.cantidad)},
    {"CODUBI",V10CADENA,(size_t)&svdubicar.codubi,sizeof(svdubicar.codubi)},
    {"CODCONCE",V10CADENA,(size_t)&svdubicar.codconce,sizeof(svdubicar.codconce)},
    {"PRIOMOV",V10LONG,(size_t)&svdubicar.priomov,sizeof(svdubicar.priomov)},
    {"STATUS",V10LONG,(size_t)&svdubicar.status,sizeof(svdubicar.status)},
    {"CODRECURSO",V10CADENA,(size_t)&svdubicar.codrecurso,sizeof(svdubicar.codrecurso)},
    {"CODMATDEST",V10CADENA,(size_t)&svdubicar.codmatdest,sizeof(svdubicar.codmatdest)},
    {"IDQUERY",V10LONG,(size_t)&svdubicar.idquery,sizeof(svdubicar.idquery)},
    {"COMPATIBLE",V10LONG,(size_t)&svdubicar.compatible,sizeof(svdubicar.compatible)}
    };

static diccionarios dvdubicar[]={
    {colvdubicar,23}
    };

diccionario dubicar={dvdubicar,1};

static char msgdebugubicar[LCADENABIG];

static int init=0;


static void fin_vd_UBICAR(void)
{
    if(vdselconteaubicar){
        liberacursor(vdselconteaubicar);
        vdselconteaubicar=NULL;
    }
    if(vdselreubiconte){
        liberacursor(vdselreubiconte);
        vdselreubiconte=NULL;
    }
    if(vdselreubistk){
        liberacursor(vdselreubistk);
        vdselreubistk=NULL;
    }
    if(vdselcambioubiconte){
        liberacursor(vdselcambioubiconte);
        vdselcambioubiconte=NULL;
    }
    if(vdselcambioubistk){
        liberacursor(vdselcambioubistk);
        vdselcambioubistk=NULL;
    }
    if(vdselcreaidquery){
        liberacursor(vdselcreaidquery);
        vdselcreaidquery=NULL;
    }
    if(vdselconteparcial){
        liberacursor(vdselconteparcial);
        vdselconteparcial=NULL;
    }
    if(vdselubilibre){
        liberacursor(vdselubilibre);
        vdselubilibre=NULL;
    }
    if(vdselubicompatible){
        liberacursor(vdselubicompatible);
        vdselubicompatible=NULL;
    }
}


static void init_selconteaubicar(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselconteaubicar=abrecursor(SELCONTEAUBICAR);
    definetodo(vdselconteaubicar,svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
               NULL);
    bindtodo(vdselconteaubicar,"CODALM",svdubicar.codalm,sizeof(svdubicar.codalm),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selreubiconte(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselreubiconte=abrecursor(SELREUBICONTE);
    definetodo(vdselreubiconte,NULL);
    bindtodo(vdselreubiconte,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "TAREA",svdubicar.tarea,sizeof(svdubicar.tarea),V10CADENA,
             "CODMOV",&svdubicar.codmov,sizeof(svdubicar.codmov),V10LONG,
             "CODAREA",svdubicar.codarea,sizeof(svdubicar.codarea),V10CADENA,
             "PASILLO",&svdubicar.pasillo,sizeof(svdubicar.pasillo),V10LONG,
             "UNIAGRUPAE",svdubicar.uniagrupae,sizeof(svdubicar.uniagrupae),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selreubistk(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselreubistk=abrecursor(SELREUBISTK);
    definetodo(vdselreubistk,NULL);
    bindtodo(vdselreubistk,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "TAREA",svdubicar.tarea,sizeof(svdubicar.tarea),V10CADENA,
             "CODART",svdubicar.codart,sizeof(svdubicar.codart),V10CADENA,
             "CODLOT",svdubicar.codlot,sizeof(svdubicar.codlot),V10CADENA,
             "UNIEMB",&svdubicar.uniemb,sizeof(svdubicar.uniemb),V10DOUBLE,
             "BLOQUEOS",svdubicar.bloqueos,sizeof(svdubicar.bloqueos),V10CADENA,
             "CANTIDAD",&svdubicar.cantidad,sizeof(svdubicar.cantidad),V10DOUBLE,
             "CODMOV",&svdubicar.codmov,sizeof(svdubicar.codmov),V10LONG,
             "CODAREA",svdubicar.codarea,sizeof(svdubicar.codarea),V10CADENA,
             "PASILLO",&svdubicar.pasillo,sizeof(svdubicar.pasillo),V10LONG,
             "UNIAGRUPAE",svdubicar.uniagrupae,sizeof(svdubicar.uniagrupae),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selcambioubiconte(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselcambioubiconte=abrecursor(SELCAMBIOUBICONTE);
    definetodo(vdselcambioubiconte,NULL);
    bindtodo(vdselcambioubiconte,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "CODUBI",svdubicar.codubi,sizeof(svdubicar.codubi),V10CADENA,
             "TAREA",svdubicar.tarea,sizeof(svdubicar.tarea),V10CADENA,
             "CODMOV",&svdubicar.codmov,sizeof(svdubicar.codmov),V10LONG,
             "VEFIFICAFLP",svdubicar.vefificaflp,sizeof(svdubicar.vefificaflp),V10CADENA,
             "VERIFICACOMP",svdubicar.verificacomp,sizeof(svdubicar.verificacomp),V10CADENA,
             "CODCONCE",svdubicar.codconce,sizeof(svdubicar.codconce),V10CADENA,
             "PRIOMOV",&svdubicar.priomov,sizeof(svdubicar.priomov),V10LONG,
             "STATUS",&svdubicar.status,sizeof(svdubicar.status),V10LONG,
             "CODRECURSO",svdubicar.codrecurso,sizeof(svdubicar.codrecurso),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selcambioubistk(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselcambioubistk=abrecursor(SELCAMBIOUBISTK);
    definetodo(vdselcambioubistk,NULL);
    bindtodo(vdselcambioubistk,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "CODUBI",svdubicar.codubi,sizeof(svdubicar.codubi),V10CADENA,
             "CODMATDEST",svdubicar.codmatdest,sizeof(svdubicar.codmatdest),V10CADENA,
             "TAREA",svdubicar.tarea,sizeof(svdubicar.tarea),V10CADENA,
             "CODART",svdubicar.codart,sizeof(svdubicar.codart),V10CADENA,
             "CODLOT",svdubicar.codlot,sizeof(svdubicar.codlot),V10CADENA,
             "UNIEMB",&svdubicar.uniemb,sizeof(svdubicar.uniemb),V10DOUBLE,
             "BLOQUEOS",svdubicar.bloqueos,sizeof(svdubicar.bloqueos),V10CADENA,
             "CANTIDAD",&svdubicar.cantidad,sizeof(svdubicar.cantidad),V10DOUBLE,
             "CODMOV",&svdubicar.codmov,sizeof(svdubicar.codmov),V10LONG,
             "VEFIFICAFLP",svdubicar.vefificaflp,sizeof(svdubicar.vefificaflp),V10CADENA,
             "VERIFICACOMP",svdubicar.verificacomp,sizeof(svdubicar.verificacomp),V10CADENA,
             "CODCONCE",svdubicar.codconce,sizeof(svdubicar.codconce),V10CADENA,
             "PRIOMOV",&svdubicar.priomov,sizeof(svdubicar.priomov),V10LONG,
             "STATUS",&svdubicar.status,sizeof(svdubicar.status),V10LONG,
             "CODRECURSO",svdubicar.codrecurso,sizeof(svdubicar.codrecurso),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selcreaidquery(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselcreaidquery=abrecursor(SELCREAIDQUERY);
    definetodo(vdselcreaidquery,NULL);
    bindtodo(vdselcreaidquery,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "CODAREA",svdubicar.codarea,sizeof(svdubicar.codarea),V10CADENA,
             "IDQUERY",&svdubicar.idquery,sizeof(svdubicar.idquery),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selconteparcial(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselconteparcial=abrecursor(SELCONTEPARCIAL);
    definetodo(vdselconteparcial,svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
               NULL);
    bindtodo(vdselconteparcial,"CODUBI",svdubicar.codubi,sizeof(svdubicar.codubi),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selubilibre(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselubilibre=abrecursor(SELUBILIBRE);
    definetodo(vdselubilibre,svdubicar.codubi,sizeof(svdubicar.codubi),V10CADENA,
               NULL);
    bindtodo(vdselubilibre,"IDQUERY",&svdubicar.idquery,sizeof(svdubicar.idquery),V10LONG,
             "CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "CODART",svdubicar.codart,sizeof(svdubicar.codart),V10CADENA,
             "CODLOT",svdubicar.codlot,sizeof(svdubicar.codlot),V10CADENA,
             "UNIEMB",&svdubicar.uniemb,sizeof(svdubicar.uniemb),V10DOUBLE,
             "BLOQUEOS",svdubicar.bloqueos,sizeof(svdubicar.bloqueos),V10CADENA,
             "CANTIDAD",&svdubicar.cantidad,sizeof(svdubicar.cantidad),V10DOUBLE,
             "CODAREA",svdubicar.codarea,sizeof(svdubicar.codarea),V10CADENA,
             "PASILLO",&svdubicar.pasillo,sizeof(svdubicar.pasillo),V10LONG,
             "UNIAGRUPAE",svdubicar.uniagrupae,sizeof(svdubicar.uniagrupae),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

static void init_selubicompatible(void)
{
    int nc;

    for(nc=0;nc<dvdubicar[0].numcol;nc++) dvdubicar[0].c[nc].offset-=(size_t)&svdubicar;

    vdselubicompatible=abrecursor(SELUBICOMPATIBLE);
    definetodo(vdselubicompatible,&svdubicar.compatible,sizeof(svdubicar.compatible),V10LONG,
               NULL);
    bindtodo(vdselubicompatible,"CODMAT",svdubicar.codmat,sizeof(svdubicar.codmat),V10CADENA,
             "CODUBI",svdubicar.codubi,sizeof(svdubicar.codubi),V10CADENA,
             "CODART",svdubicar.codart,sizeof(svdubicar.codart),V10CADENA,
             "CODLOT",svdubicar.codlot,sizeof(svdubicar.codlot),V10CADENA,
             "UNIEMB",&svdubicar.uniemb,sizeof(svdubicar.uniemb),V10DOUBLE,
             "BLOQUEOS",svdubicar.bloqueos,sizeof(svdubicar.bloqueos),V10CADENA,
             "CANTIDAD",&svdubicar.cantidad,sizeof(svdubicar.cantidad),V10DOUBLE,
             NULL);

    if (init == 0) {
        atexit(fin_vd_UBICAR);
        init = 1;
    }
}

diccionario *UBICARdamediccionario(void)
{
    return(&dubicar);
}

int UBICARbuscaconteaubicar(char *codalm,vdubicars *ubicar)
{
    int vdret;
    if (vdselconteaubicar==NULL) init_selconteaubicar();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codalm,codalm);
    vdret=ejefetchcursor(vdselconteaubicar);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch UBICARbuscaconteaubicar vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARnextconteaubicar(vdubicars *ubicar)
{
    int vdret;
    vdret=fetchcursor(vdselconteaubicar);
    if (!vdret) {
        *ubicar=svdubicar;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselconteaubicar);
    return(VD_EERRORACLE);
}

int UBICARprocreubiconte(char *codmat,char *tarea,long codmov,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar)
{
    int vdret;
    if (vdselreubiconte==NULL) init_selreubiconte();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.tarea,tarea);
    svdubicar.codmov=codmov;
    strcpy(svdubicar.codarea,codarea);
    svdubicar.pasillo=pasillo;
    strcpy(svdubicar.uniagrupae,uniagrupae);
    vdret=ejecutacursor(vdselreubiconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta UBICARprocreubiconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARprocreubistk(char *codmat,char *tarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,long codmov,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar)
{
    int vdret;
    if (vdselreubistk==NULL) init_selreubistk();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.tarea,tarea);
    strcpy(svdubicar.codart,codart);
    strcpy(svdubicar.codlot,codlot);
    svdubicar.uniemb=uniemb;
    strcpy(svdubicar.bloqueos,bloqueos);
    svdubicar.cantidad=cantidad;
    svdubicar.codmov=codmov;
    strcpy(svdubicar.codarea,codarea);
    svdubicar.pasillo=pasillo;
    strcpy(svdubicar.uniagrupae,uniagrupae);
    vdret=ejecutacursor(vdselreubistk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta UBICARprocreubistk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARproccambioubiconte(char *codmat,char *codubi,char *tarea,long codmov,char *vefificaflp,char *verificacomp,char *codconce,long priomov,long status,char *codrecurso,vdubicars *ubicar)
{
    int vdret;
    if (vdselcambioubiconte==NULL) init_selcambioubiconte();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.codubi,codubi);
    strcpy(svdubicar.tarea,tarea);
    svdubicar.codmov=codmov;
    strcpy(svdubicar.vefificaflp,vefificaflp);
    strcpy(svdubicar.verificacomp,verificacomp);
    strcpy(svdubicar.codconce,codconce);
    svdubicar.priomov=priomov;
    svdubicar.status=status;
    strcpy(svdubicar.codrecurso,codrecurso);
    vdret=ejecutacursor(vdselcambioubiconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta UBICARproccambioubiconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARproccambioubistk(char *codmat,char *codubi,char *codmatdest,char *tarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,long codmov,char *vefificaflp,char *verificacomp,char *codconce,long priomov,long status,char *codrecurso,vdubicars *ubicar)
{
    int vdret;
    if (vdselcambioubistk==NULL) init_selcambioubistk();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.codubi,codubi);
    strcpy(svdubicar.codmatdest,codmatdest);
    strcpy(svdubicar.tarea,tarea);
    strcpy(svdubicar.codart,codart);
    strcpy(svdubicar.codlot,codlot);
    svdubicar.uniemb=uniemb;
    strcpy(svdubicar.bloqueos,bloqueos);
    svdubicar.cantidad=cantidad;
    svdubicar.codmov=codmov;
    strcpy(svdubicar.vefificaflp,vefificaflp);
    strcpy(svdubicar.verificacomp,verificacomp);
    strcpy(svdubicar.codconce,codconce);
    svdubicar.priomov=priomov;
    svdubicar.status=status;
    strcpy(svdubicar.codrecurso,codrecurso);
    vdret=ejecutacursor(vdselcambioubistk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta UBICARproccambioubistk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARproccreaidquery(char *codmat,char *codarea,long idquery,vdubicars *ubicar)
{
    int vdret;
    if (vdselcreaidquery==NULL) init_selcreaidquery();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.codarea,codarea);
    svdubicar.idquery=idquery;
    vdret=ejecutacursor(vdselcreaidquery);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta UBICARproccreaidquery vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARbuscaconteparcial(char *codubi,vdubicars *ubicar)
{
    int vdret;
    if (vdselconteparcial==NULL) init_selconteparcial();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codubi,codubi);
    vdret=ejefetchcursor(vdselconteparcial);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch UBICARbuscaconteparcial vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARnextconteparcial(vdubicars *ubicar)
{
    int vdret;
    vdret=fetchcursor(vdselconteparcial);
    if (!vdret) {
        *ubicar=svdubicar;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselconteparcial);
    return(VD_EERRORACLE);
}

int UBICARbuscaubilibre(long idquery,char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar)
{
    int vdret;
    if (vdselubilibre==NULL) init_selubilibre();
    memset(&svdubicar,0,sizeof(svdubicar));
    svdubicar.idquery=idquery;
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.codart,codart);
    strcpy(svdubicar.codlot,codlot);
    svdubicar.uniemb=uniemb;
    strcpy(svdubicar.bloqueos,bloqueos);
    svdubicar.cantidad=cantidad;
    strcpy(svdubicar.codarea,codarea);
    svdubicar.pasillo=pasillo;
    strcpy(svdubicar.uniagrupae,uniagrupae);
    vdret=ejefetchcursor(vdselubilibre);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch UBICARbuscaubilibre vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARnextubilibre(vdubicars *ubicar)
{
    int vdret;
    vdret=fetchcursor(vdselubilibre);
    if (!vdret) {
        *ubicar=svdubicar;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselubilibre);
    return(VD_EERRORACLE);
}

int UBICARbuscaubicompatible(char *codmat,char *codubi,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,vdubicars *ubicar)
{
    int vdret;
    if (vdselubicompatible==NULL) init_selubicompatible();
    memset(&svdubicar,0,sizeof(svdubicar));
    strcpy(svdubicar.codmat,codmat);
    strcpy(svdubicar.codubi,codubi);
    strcpy(svdubicar.codart,codart);
    strcpy(svdubicar.codlot,codlot);
    svdubicar.uniemb=uniemb;
    strcpy(svdubicar.bloqueos,bloqueos);
    svdubicar.cantidad=cantidad;
    vdret=ejefetchcursor(vdselubicompatible);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch UBICARbuscaubicompatible vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *ubicar=svdubicar;
    return(vdret);
}

int UBICARnextubicompatible(vdubicars *ubicar)
{
    int vdret;
    vdret=fetchcursor(vdselubicompatible);
    if (!vdret) {
        *ubicar=svdubicar;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselubicompatible);
    return(VD_EERRORACLE);
}

char * UBICARdebug(vdubicars *ubicar)
{
    debugestruct(&dubicar,ubicar,msgdebugubicar);
    return(msgdebugubicar);
}


//Codigo incluido explicitamente en el DEF
VDEXPORT int UBIdameubiarealibre(char *codmat,char *codarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,int pasillo,char *uniagrupa,vdubicars *ubicar)
{   
   int ret;
   ret=UBICARproccreaidquery(codmat,codarea,0,ubicar); 
   if (ret==0) ret=UBICARbuscaubilibre(ubicar->idquery,codmat,codart,codlot,uniemb,bloqueos,cantidad,codarea,pasillo,uniagrupa,ubicar); 
   return(ret);
}  

// devuelve una ubicacion libre para una matr�cula,articulo,lote,cantidad en un �rea
VDEXPORT int UBIdameubiareaconte(char *codmat,char *codarea,int pasillo, char uniagrupa, char *codubi) {
  int ret;
  vdubicars ubicar;

  ret=UBIdameubiarealibre(codmat,codarea,NULL,NULL,0,NULL,0,pasillo,&uniagrupa,&ubicar);

  if (ret) v10log(LOGNORMAL,"dameubiconte: No se encuentra ubicacion para contenedor %lf en area %s\n",codmat,codarea);
  else v10log(LOGNORMAL,"dameubiconte: Encontrada ubicacion %s para contenedor %lf en area %s\n",ubicar.codubi,codmat,codarea);
  if (ret==0) strcopia(codubi,ubicar.codubi,strlen(ubicar.codubi));
  return(ret);
}


// devuelve una ubicacion libre para el stock de una matr�cula,articulo,lote,cantidad en un �rea
VDEXPORT int UBIdameubiareastk(char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,int pasillo, char uniagrupa,char *codubi) {
  int ret;
  vdubicars ubicar;

  ret=UBIdameubiarealibre(codmat,codarea,codart,codlot,uniemb,bloqueos,cantidad,pasillo,&uniagrupa,&ubicar);
 
  if (ret) v10log(LOGNORMAL,"dameubistk: No se encuentra ubicacion para contenedor %lf,articulo %s,lote %s y cantidad %ld en area %s\n",codmat,codart,codlot,cantidad,codarea);
  else v10log(LOGNORMAL,"dameubistk: Encontrada ubicacion %s para contenedor %lf,articulo %s,lote %s y cantidad %ld en area %s\n",ubicar.codubi,codmat,codart,codlot,cantidad,codarea);
  if (ret==0) strcopia(codubi,ubicar.codubi,strlen(ubicar.codubi));
  return(ret);  
}
