// Modulo generado automaticamente a partir de VDPICKINV.DEF
//#***
//# VDPICKINV.DEF - Generaci�n autom�tica del c�digo c SOLOQUERY para Picking inverso                                                       
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 02-09-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=PICKINV;
//
//EXTRA=RET,V10LONG;
//EXTRA=NUEVOESTATUS,V10LONG;
//EXTRA=STPDTEEQUILI,V10LONG;
//EXTRA=STPDTEBULINV,V10LONG;
//EXTRA=STPICKINV,V10LONG;
//EXTRA=FACTOR,V10LONG;
//EXTRA=HAYPICKINV,V10LONG;
//EXTRA=UBIRESTOS,V10CADENA,12;
//EXTRA=MITAREARESTOS,V10CADENA,32;
//EXTRA=MITAREAUNI,V10CADENA,32;
//EXTRA=MITAREAEMBA,V10CADENA,32;
//EXTRA=MICODCONCERESTOS,V10CADENA,10;
//EXTRA=STATUS1,V10LONG;
//EXTRA=STATUS2,V10LONG;
//EXTRA=LECTURA,V10CADENA,256;
//EXTRA=TEXTO, V10CADENA,20;
//EXTRA=ENCENDIDOS, V10LONG;
//EXTRA=DIFERIDO,V10CADENA,1;
//EXTRA=CODUBIDEST,V10CADENA,12;
//EXTRA=CODUBIRESERVA,V10CADENA,12;
//EXTRA=CODUBICODCONCE,V10CADENA,12;
//EXTRA=OBSERV,V10CADENA,1024;
//EXTRA=NUEVOCODMOV,V10DOUBLE;
//EXTRA=MAXBULTOS,V10LONG;
//EXTRA=FORZARREENGANCHE,V10CADENA,1;
//EXTRA=EJECMOVEMBA,V10CADENA,1;
//EXTRA=FORZARPICKINV,V10CADENA,1;
//EXTRA=MSJERROR,V10CADENA,1024;
//EXTRA=STATUSBUL,V10LONG
//EXTRA=STATUSBPL,V10LONG
//EXTRA=NUMEROSERIE,V10CADENA,60;
//
//
//CURSOR=CDISPENCENDIDOS, SELECT NVL(COUNT(*),0) ENCENDIDOS FROM VDINFODISP WHERE CODZONA=:VDINFODISP.CODZONA AND STATUS>:VDINFODISP.STATUS;
//
//PROCEDURE=DAMETEXTOZONA, BEGIN
// 															VDPICKINVLUCES.DAMETEXTODISPZONA(:VDINFODISP.IDINFOPICK,:VDZONAS.CODZONA, :LECTURA, :TEXTO);
// 												END;@
// 													
//PROCEDURE=FINVOLUMETRIA,BEGIN 
//                           VDPICKINV.FINVOLUMETRIA(:VDPEDIDOCAB.CODDIV,
//                                                   :VDPEDIDOCAB.ANOPED,
//                                                   :VDPEDIDOCAB.CODPED,
//                                                   :VDPEDIDOCAB.SEQPED,
//                                                   :FORZARPICKINV,
//                                                   :HAYPICKINV,
//                                                   :RET);
//                        END;@
//                        
//PROCEDURE=EQUILIBRASERIE,BEGIN
//                            VDPICKINV.EQUILIBRASERIE(:VDSERIEPREP.CODSERIEPREP,:STATUS1,:STATUS2,
//                                                     :STPDTEEQUILI,:STPDTEBULINV,:STPICKINV,
//                                                     :NUEVOESTATUS,:FORZARREENGANCHE,:RET);
//                          END;@
//                          
//PROCEDURE=REENGANCHAPINV, BEGIN
//                           VDPICKINV.REENGANCHAPINV(:VDSERIEPREP.CODSERIEPREP, :VDARTIC.CODART, :MITAREAUNI, :RET);
//                          END;@
//                          
//PROCEDURE=REENGANCHAEMBA, BEGIN
//                           VDPICKINV.REENGANCHAEMBA(:VDSERIEPREP.CODSERIEPREP, :VDARTIC.CODART, :MITAREAEMBA, :EJECMOVEMBA, :RET);
//                          END;@                          
//                          
//PROCEDURE=REENGANCHASPRPINV, BEGIN
//                              VDPICKINV.REENGANCHASPRPINV(:VDSERIEPREP.CODSERIEPREP, :STPDTEEQUILI,:STPDTEBULINV,:STPICKINV,
//                                                          :DIFERIDO, :MITAREAUNI, :MITAREAEMBA, :NUEVOESTATUS, :EJECMOVEMBA, :RET);
//                             END;@
//
//
//PROCEDURE=CREABULTOSPINVCONTE, BEGIN
//                                VDPICKINV.CREABULTOSPINVCONTE(:VDCONTE.CODMAT,:VDRECURSO.CODRECURSO,:VDMOVIM.TAREA,                             
//                                                              :STATUS1,:VDUBICA.CODUBI, :MITAREARESTOS, :MICODCONCERESTOS, :MAXBULTOS, :RET);
//                             END;@
//                
//CURSOR=COPEPICKINV SELECT CODOPE FROM VDUSUARIO WHERE CODOPE=:VDUSUARIO.CODOPE;                                   
//                     
//                                
//PROCEDURE=REGULARIZABPC, BEGIN
//                                VDPICKINV.REGULARIZABPC(:VDBULTOCABPINV.CODBULTO,
//                                                        :VDCONTE.CODMAT,
//                                                        :VDARTIC.CODART,
//                                                        :VDSTOCK.CODLOT,
//                                                        :VDSTOCK.UNIEMB,
//                                                        :CODUBIDEST,
//                                                        :CODUBIRESERVA,
//                                                        :VDSTOCK.CANTIDAD, 
//                                                        :VDMOVIM.CODCONCE,
//                                                        :CODUBICODCONCE,
//                                                        :OBSERV,
//                                                        :VDCOMEN.COMENTARIO,
//                                                        :RET);
//                           END;@         
//                           
//
//PROCEDURE=REGULARIZASTKPINV,BEGIN 
//                                VDPICKINV.REGULARIZASTKPINV(:VDCONTE.CODMAT, 
//                                                            :VDSTOCK.ORDENSTK,
//                                                            :VDCONCEPTO.CODCONCE,
//                                                            :CODUBICODCONCE,
//                                                            :VDSTOCK.CANTIDAD, 
//                                                            :OBSERV,
//                                                            :NUEVOCODMOV,
//                                                            :CODUBIDEST,
//                                                            :VDCOMEN.COMENTARIO,
//                                                            :RET);
//                            END;@
//                           
//                                                         
//PROCEDURE=PARTEMOVPINV, BEGIN
//                             VDPICKINV.PARTEMOVPINV(:VDMOVIM.CODMOV, 
//                                                    :CODUBIDEST,
//                                                    :VDCONTE.CODMAT,
//                                                    :NUEVOCODMOV,
//                                                    :VDCOMEN.COMENTARIO,
//                                                    :RET);
//                       END;@
//                       
//PROCEDURE=CREABPC, BEGIN
//                      VDPICKINV.CREABPC(:VDCONTE.CODMAT,:STATUS1,:MSJERROR);
//                   END;@                       
//
//## TRATAMIENTO DE N�MEROS DE SERIE ##
//
//# BUSCA LAS L�NEAS DE LOS BULTOS QUE TODAV�A NO SE HAN PREPARADO
//CURSOR=LINSINPREP, SELECT BUL.CODBULTO, BUL.SEQLINEA, BUL.CANTPEDIDA, BUL.CODMOV                         
//                     FROM VDBULTOCAB BUC, VDBULTOLIN BUL, VDBULTOLINPINV BPL, VDBULTOCABPINV BPC
//                    WHERE BUC.CODPED   = :VDBULTOCAB.CODPED
//                      AND BUC.CODDIV   = :VDBULTOCAB.CODDIV
//                      AND BUC.SEQPED   = :VDBULTOCAB.SEQPED
//                      AND BUC.CODBULTO = BUL.CODBULTO
//                      AND BUL.CODART   = :VDBULTOLIN.CODART
//                      AND BUL.STATUS   = :STATUSBUL
//                      AND BUL.CODMOV   = BPL.CODMOV
//                      AND BPL.STATUS   = :STATUSBPL
//                      AND BPL.CODBULTO = BPC.CODBULTO
//                      AND BPC.STATUS  <= :VDBULTOCABPINV.STATUS
//                    ORDER BY BUL.CANTPEDIDA DESC;
//
//CURSOR=YALEIDONS, SELECT 'ERR NS YA SERVID' MSJERROR
//                    FROM VDBULTOLIN BUL
//                   WHERE BUL.NUMEROSERIE = :NUMEROSERIE
//                UNION
//                  SELECT 'ERR NS YA LEIDO, MATRICULA '||CODMAT MSJERROR
//                    FROM VDSCANNUMSERIE 
//                   WHERE NUMEROSERIE=:NUMEROSERIE;

#include "vd.h"\

#define SELCDISPENCENDIDOS " SELECT NVL(COUNT(*),0) ENCENDIDOS FROM VDINFODISP WHERE CODZONA=:CODZONA AND STATUS>:STATUS"
static v10cursors *vdselcdispencendidos;
#define SELDAMETEXTOZONA " BEGIN VDPICKINVLUCES.DAMETEXTODISPZONA(:IDINFOPICK,:CODZONA, :LECTURA, :TEXTO); END;"
static v10cursors *vdseldametextozona;
#define SELFINVOLUMETRIA "BEGIN  VDPICKINV.FINVOLUMETRIA(:CODDIV, :ANOPED, :CODPED, :SEQPED, :FORZARPICKINV, :HAYPICKINV, :RET); END;"
static v10cursors *vdselfinvolumetria;
#define SELEQUILIBRASERIE "BEGIN VDEQUILIBRA.EQUILIBRASERIE(:CODSERIEPREP,:STATUS1,:STATUS2, :STPDTEEQUILI,:STPDTEBULINV,:STPICKINV, :NUEVOESTATUS,:FORZARREENGANCHE,:RET); END;"
static v10cursors *vdselequilibraserie;
#define SELREENGANCHAPINV " BEGIN VDPICKINV.REENGANCHAPINV(:CODSERIEPREP, :CODART, :MITAREAUNI, :RET); END;"
static v10cursors *vdselreenganchapinv;
#define SELREENGANCHAEMBA " BEGIN VDPICKINV.REENGANCHAEMBA(:CODSERIEPREP, :CODART, :MITAREAEMBA, :EJECMOVEMBA, :RET); END;"
static v10cursors *vdselreenganchaemba;
#define SELREENGANCHASPRPINV " BEGIN VDPICKINV.REENGANCHASPRPINV(:CODSERIEPREP, :STPDTEEQUILI,:STPDTEBULINV,:STPICKINV, :DIFERIDO, :MITAREAUNI, :MITAREAEMBA, :NUEVOESTATUS, :EJECMOVEMBA, :RET); END;"
static v10cursors *vdselreenganchasprpinv;
#define SELCREABULTOSPINVCONTE " BEGIN VDPICKINV.CREABULTOSPINVCONTE(:CODMAT,:CODRECURSO,:TAREA,                              :STATUS1,:CODUBI, :MITAREARESTOS, :MICODCONCERESTOS, :MAXBULTOS, :RET); END;"
static v10cursors *vdselcreabultospinvconte;
#define SELCOPEPICKINV "SELECT CODOPE FROM VDUSUARIO WHERE CODOPE=:CODOPE"
static v10cursors *vdselcopepickinv;
#define SELREGULARIZABPC " BEGIN VDPICKINV.REGULARIZABPC(:CODBULTO, :CODMAT, :CODART, :CODLOT, :UNIEMB, :CODUBIDEST, :CODUBIRESERVA, :CANTIDAD,  :CODCONCE, :CODUBICODCONCE, :OBSERV, :COMENTARIO, :RET); END;"
static v10cursors *vdselregularizabpc;
#define SELREGULARIZASTKPINV "BEGIN  VDPICKINV.REGULARIZASTKPINV(:CODMAT,  :ORDENSTK, :CODCONCE, :CODUBICODCONCE, :CANTIDAD,  :OBSERV, :NUEVOCODMOV, :CODUBIDEST, :COMENTARIO, :RET); END;"
static v10cursors *vdselregularizastkpinv;
#define SELPARTEMOVPINV " BEGIN VDPICKINV.PARTEMOVPINV(:CODMOV,  :CODUBIDEST, :CODMAT, :NUEVOCODMOV, :COMENTARIO, :RET); END;"
static v10cursors *vdselpartemovpinv;
#define SELCREABPC " BEGIN VDPICKINV.CREABPC(:CODMAT,:STATUS1,:MSJERROR); END;"
static v10cursors *vdselcreabpc;
#define SELLINSINPREP " SELECT BUL.CODBULTO, BUL.SEQLINEA, BUL.CANTPEDIDA, BUL.CODMOV                          FROM VDBULTOCAB BUC, VDBULTOLIN BUL, VDBULTOLINPINV BPL, VDBULTOCABPINV BPC WHERE BUC.CODPED   = :CODPED AND BUC.CODDIV   = :CODDIV AND BUC.SEQPED   = :SEQPED AND BUC.CODBULTO = BUL.CODBULTO AND BUL.CODART   = :CODART AND BUL.STATUS   = :STATUSBUL AND BUL.CODMOV   = BPL.CODMOV AND BPL.STATUS   = :STATUSBPL AND BPL.CODBULTO = BPC.CODBULTO AND BPC.STATUS  <= :STATUS ORDER BY BUL.CANTPEDIDA DESC"
static v10cursors *vdsellinsinprep;
#define SELYALEIDONS " SELECT 'ERR NS YA SERVID' MSJERROR FROM VDBULTOLIN BUL WHERE BUL.NUMEROSERIE = :NUMEROSERIE UNION SELECT 'ERR NS YA LEIDO, MATRICULA '||CODMAT MSJERROR FROM VDSCANNUMSERIE  WHERE NUMEROSERIE=:NUMEROSERIE"
static v10cursors *vdselyaleidons;

static vdpickinvs svdpickinv;

static diccols colvdpickinv[]={ 
    {"RET",V10LONG,(size_t)&svdpickinv.ret,sizeof(svdpickinv.ret)},
    {"NUEVOESTATUS",V10LONG,(size_t)&svdpickinv.nuevoestatus,sizeof(svdpickinv.nuevoestatus)},
    {"STPDTEEQUILI",V10LONG,(size_t)&svdpickinv.stpdteequili,sizeof(svdpickinv.stpdteequili)},
    {"STPDTEBULINV",V10LONG,(size_t)&svdpickinv.stpdtebulinv,sizeof(svdpickinv.stpdtebulinv)},
    {"STPICKINV",V10LONG,(size_t)&svdpickinv.stpickinv,sizeof(svdpickinv.stpickinv)},
    {"FACTOR",V10LONG,(size_t)&svdpickinv.factor,sizeof(svdpickinv.factor)},
    {"HAYPICKINV",V10LONG,(size_t)&svdpickinv.haypickinv,sizeof(svdpickinv.haypickinv)},
    {"UBIRESTOS",V10CADENA,(size_t)&svdpickinv.ubirestos,sizeof(svdpickinv.ubirestos)},
    {"MITAREARESTOS",V10CADENA,(size_t)&svdpickinv.mitarearestos,sizeof(svdpickinv.mitarearestos)},
    {"MITAREAUNI",V10CADENA,(size_t)&svdpickinv.mitareauni,sizeof(svdpickinv.mitareauni)},
    {"MITAREAEMBA",V10CADENA,(size_t)&svdpickinv.mitareaemba,sizeof(svdpickinv.mitareaemba)},
    {"MICODCONCERESTOS",V10CADENA,(size_t)&svdpickinv.micodconcerestos,sizeof(svdpickinv.micodconcerestos)},
    {"STATUS1",V10LONG,(size_t)&svdpickinv.status1,sizeof(svdpickinv.status1)},
    {"STATUS2",V10LONG,(size_t)&svdpickinv.status2,sizeof(svdpickinv.status2)},
    {"LECTURA",V10CADENA,(size_t)&svdpickinv.lectura,sizeof(svdpickinv.lectura)},
    {"TEXTO",V10CADENA,(size_t)&svdpickinv.texto,sizeof(svdpickinv.texto)},
    {"ENCENDIDOS",V10LONG,(size_t)&svdpickinv.encendidos,sizeof(svdpickinv.encendidos)},
    {"DIFERIDO",V10CADENA,(size_t)&svdpickinv.diferido,sizeof(svdpickinv.diferido)},
    {"CODUBIDEST",V10CADENA,(size_t)&svdpickinv.codubidest,sizeof(svdpickinv.codubidest)},
    {"CODUBIRESERVA",V10CADENA,(size_t)&svdpickinv.codubireserva,sizeof(svdpickinv.codubireserva)},
    {"CODUBICODCONCE",V10CADENA,(size_t)&svdpickinv.codubicodconce,sizeof(svdpickinv.codubicodconce)},
    {"OBSERV",V10CADENA,(size_t)&svdpickinv.observ,sizeof(svdpickinv.observ)},
    {"NUEVOCODMOV",V10DOUBLE,(size_t)&svdpickinv.nuevocodmov,sizeof(svdpickinv.nuevocodmov)},
    {"MAXBULTOS",V10LONG,(size_t)&svdpickinv.maxbultos,sizeof(svdpickinv.maxbultos)},
    {"FORZARREENGANCHE",V10CADENA,(size_t)&svdpickinv.forzarreenganche,sizeof(svdpickinv.forzarreenganche)},
    {"EJECMOVEMBA",V10CADENA,(size_t)&svdpickinv.ejecmovemba,sizeof(svdpickinv.ejecmovemba)},
    {"FORZARPICKINV",V10CADENA,(size_t)&svdpickinv.forzarpickinv,sizeof(svdpickinv.forzarpickinv)},
    {"MSJERROR",V10CADENA,(size_t)&svdpickinv.msjerror,sizeof(svdpickinv.msjerror)},
    {"STATUSBUL",V10LONG,(size_t)&svdpickinv.statusbul,sizeof(svdpickinv.statusbul)},
    {"STATUSBPL",V10LONG,(size_t)&svdpickinv.statusbpl,sizeof(svdpickinv.statusbpl)},
    {"NUMEROSERIE",V10CADENA,(size_t)&svdpickinv.numeroserie,sizeof(svdpickinv.numeroserie)},
    {"CODZONA",V10LONG,(size_t)&svdpickinv.codzona,sizeof(svdpickinv.codzona)},
    {"STATUS",V10LONG,(size_t)&svdpickinv.status,sizeof(svdpickinv.status)},
    {"IDINFOPICK",V10LONG,(size_t)&svdpickinv.idinfopick,sizeof(svdpickinv.idinfopick)},
    {"CODDIV",V10CADENA,(size_t)&svdpickinv.coddiv,sizeof(svdpickinv.coddiv)},
    {"ANOPED",V10LONG,(size_t)&svdpickinv.anoped,sizeof(svdpickinv.anoped)},
    {"CODPED",V10CADENA,(size_t)&svdpickinv.codped,sizeof(svdpickinv.codped)},
    {"SEQPED",V10LONG,(size_t)&svdpickinv.seqped,sizeof(svdpickinv.seqped)},
    {"CODSERIEPREP",V10LONG,(size_t)&svdpickinv.codserieprep,sizeof(svdpickinv.codserieprep)},
    {"CODART",V10CADENA,(size_t)&svdpickinv.codart,sizeof(svdpickinv.codart)},
    {"CODMAT",V10CADENA,(size_t)&svdpickinv.codmat,sizeof(svdpickinv.codmat)},
    {"CODRECURSO",V10CADENA,(size_t)&svdpickinv.codrecurso,sizeof(svdpickinv.codrecurso)},
    {"TAREA",V10CADENA,(size_t)&svdpickinv.tarea,sizeof(svdpickinv.tarea)},
    {"CODUBI",V10CADENA,(size_t)&svdpickinv.codubi,sizeof(svdpickinv.codubi)},
    {"CODOPE",V10CADENA,(size_t)&svdpickinv.codope,sizeof(svdpickinv.codope)},
    {"CODBULTO",V10CADENA,(size_t)&svdpickinv.codbulto,sizeof(svdpickinv.codbulto)},
    {"CODLOT",V10CADENA,(size_t)&svdpickinv.codlot,sizeof(svdpickinv.codlot)},
    {"UNIEMB",V10DOUBLE,(size_t)&svdpickinv.uniemb,sizeof(svdpickinv.uniemb)},
    {"CANTIDAD",V10DOUBLE,(size_t)&svdpickinv.cantidad,sizeof(svdpickinv.cantidad)},
    {"CODCONCE",V10CADENA,(size_t)&svdpickinv.codconce,sizeof(svdpickinv.codconce)},
    {"COMENTARIO",V10CADENA,(size_t)&svdpickinv.comentario,sizeof(svdpickinv.comentario)},
    {"ORDENSTK",V10LONG,(size_t)&svdpickinv.ordenstk,sizeof(svdpickinv.ordenstk)},
    {"CODMOV",V10LONG,(size_t)&svdpickinv.codmov,sizeof(svdpickinv.codmov)},
    {"SEQLINEA",V10LONG,(size_t)&svdpickinv.seqlinea,sizeof(svdpickinv.seqlinea)},
    {"CANTPEDIDA",V10DOUBLE,(size_t)&svdpickinv.cantpedida,sizeof(svdpickinv.cantpedida)}
    };

static diccionarios dvdpickinv[]={
    {colvdpickinv,55}
    };

diccionario dpickinv={dvdpickinv,1};

static char msgdebugpickinv[LCADENABIG];

static int init=0;


static void fin_vd_PICKINV(void)
{
    if(vdselcdispencendidos){
        liberacursor(vdselcdispencendidos);
        vdselcdispencendidos=NULL;
    }
    if(vdseldametextozona){
        liberacursor(vdseldametextozona);
        vdseldametextozona=NULL;
    }
    if(vdselfinvolumetria){
        liberacursor(vdselfinvolumetria);
        vdselfinvolumetria=NULL;
    }
    if(vdselequilibraserie){
        liberacursor(vdselequilibraserie);
        vdselequilibraserie=NULL;
    }
    if(vdselreenganchapinv){
        liberacursor(vdselreenganchapinv);
        vdselreenganchapinv=NULL;
    }
    if(vdselreenganchaemba){
        liberacursor(vdselreenganchaemba);
        vdselreenganchaemba=NULL;
    }
    if(vdselreenganchasprpinv){
        liberacursor(vdselreenganchasprpinv);
        vdselreenganchasprpinv=NULL;
    }
    if(vdselcreabultospinvconte){
        liberacursor(vdselcreabultospinvconte);
        vdselcreabultospinvconte=NULL;
    }
    if(vdselcopepickinv){
        liberacursor(vdselcopepickinv);
        vdselcopepickinv=NULL;
    }
    if(vdselregularizabpc){
        liberacursor(vdselregularizabpc);
        vdselregularizabpc=NULL;
    }
    if(vdselregularizastkpinv){
        liberacursor(vdselregularizastkpinv);
        vdselregularizastkpinv=NULL;
    }
    if(vdselpartemovpinv){
        liberacursor(vdselpartemovpinv);
        vdselpartemovpinv=NULL;
    }
    if(vdselcreabpc){
        liberacursor(vdselcreabpc);
        vdselcreabpc=NULL;
    }
    if(vdsellinsinprep){
        liberacursor(vdsellinsinprep);
        vdsellinsinprep=NULL;
    }
    if(vdselyaleidons){
        liberacursor(vdselyaleidons);
        vdselyaleidons=NULL;
    }
}


static void init_selcdispencendidos(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselcdispencendidos=abrecursor(SELCDISPENCENDIDOS);
    definetodo(vdselcdispencendidos,&svdpickinv.encendidos,sizeof(svdpickinv.encendidos),V10LONG,
               NULL);
    bindtodo(vdselcdispencendidos,"CODZONA",&svdpickinv.codzona,sizeof(svdpickinv.codzona),V10LONG,
             "STATUS",&svdpickinv.status,sizeof(svdpickinv.status),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_seldametextozona(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdseldametextozona=abrecursor(SELDAMETEXTOZONA);
    definetodo(vdseldametextozona,NULL);
    bindtodo(vdseldametextozona,"IDINFOPICK",&svdpickinv.idinfopick,sizeof(svdpickinv.idinfopick),V10LONG,
             "CODZONA",&svdpickinv.codzona,sizeof(svdpickinv.codzona),V10LONG,
             "LECTURA",svdpickinv.lectura,sizeof(svdpickinv.lectura),V10CADENA,
             "TEXTO",svdpickinv.texto,sizeof(svdpickinv.texto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selfinvolumetria(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselfinvolumetria=abrecursor(SELFINVOLUMETRIA);
    definetodo(vdselfinvolumetria,NULL);
    bindtodo(vdselfinvolumetria,"CODDIV",svdpickinv.coddiv,sizeof(svdpickinv.coddiv),V10CADENA,
             "ANOPED",&svdpickinv.anoped,sizeof(svdpickinv.anoped),V10LONG,
             "CODPED",svdpickinv.codped,sizeof(svdpickinv.codped),V10CADENA,
             "SEQPED",&svdpickinv.seqped,sizeof(svdpickinv.seqped),V10LONG,
             "FORZARPICKINV",svdpickinv.forzarpickinv,sizeof(svdpickinv.forzarpickinv),V10CADENA,
             "HAYPICKINV",&svdpickinv.haypickinv,sizeof(svdpickinv.haypickinv),V10LONG,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selequilibraserie(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselequilibraserie=abrecursor(SELEQUILIBRASERIE);
    definetodo(vdselequilibraserie,NULL);
    bindtodo(vdselequilibraserie,"CODSERIEPREP",&svdpickinv.codserieprep,sizeof(svdpickinv.codserieprep),V10LONG,
             "STATUS1",&svdpickinv.status1,sizeof(svdpickinv.status1),V10LONG,
             "STATUS2",&svdpickinv.status2,sizeof(svdpickinv.status2),V10LONG,
             "STPDTEEQUILI",&svdpickinv.stpdteequili,sizeof(svdpickinv.stpdteequili),V10LONG,
             "STPDTEBULINV",&svdpickinv.stpdtebulinv,sizeof(svdpickinv.stpdtebulinv),V10LONG,
             "STPICKINV",&svdpickinv.stpickinv,sizeof(svdpickinv.stpickinv),V10LONG,
             "NUEVOESTATUS",&svdpickinv.nuevoestatus,sizeof(svdpickinv.nuevoestatus),V10LONG,
             "FORZARREENGANCHE",svdpickinv.forzarreenganche,sizeof(svdpickinv.forzarreenganche),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selreenganchapinv(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselreenganchapinv=abrecursor(SELREENGANCHAPINV);
    definetodo(vdselreenganchapinv,NULL);
    bindtodo(vdselreenganchapinv,"CODSERIEPREP",&svdpickinv.codserieprep,sizeof(svdpickinv.codserieprep),V10LONG,
             "CODART",svdpickinv.codart,sizeof(svdpickinv.codart),V10CADENA,
             "MITAREAUNI",svdpickinv.mitareauni,sizeof(svdpickinv.mitareauni),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selreenganchaemba(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselreenganchaemba=abrecursor(SELREENGANCHAEMBA);
    definetodo(vdselreenganchaemba,NULL);
    bindtodo(vdselreenganchaemba,"CODSERIEPREP",&svdpickinv.codserieprep,sizeof(svdpickinv.codserieprep),V10LONG,
             "CODART",svdpickinv.codart,sizeof(svdpickinv.codart),V10CADENA,
             "MITAREAEMBA",svdpickinv.mitareaemba,sizeof(svdpickinv.mitareaemba),V10CADENA,
             "EJECMOVEMBA",svdpickinv.ejecmovemba,sizeof(svdpickinv.ejecmovemba),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selreenganchasprpinv(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselreenganchasprpinv=abrecursor(SELREENGANCHASPRPINV);
    definetodo(vdselreenganchasprpinv,NULL);
    bindtodo(vdselreenganchasprpinv,"CODSERIEPREP",&svdpickinv.codserieprep,sizeof(svdpickinv.codserieprep),V10LONG,
             "STPDTEEQUILI",&svdpickinv.stpdteequili,sizeof(svdpickinv.stpdteequili),V10LONG,
             "STPDTEBULINV",&svdpickinv.stpdtebulinv,sizeof(svdpickinv.stpdtebulinv),V10LONG,
             "STPICKINV",&svdpickinv.stpickinv,sizeof(svdpickinv.stpickinv),V10LONG,
             "DIFERIDO",svdpickinv.diferido,sizeof(svdpickinv.diferido),V10CADENA,
             "MITAREAUNI",svdpickinv.mitareauni,sizeof(svdpickinv.mitareauni),V10CADENA,
             "MITAREAEMBA",svdpickinv.mitareaemba,sizeof(svdpickinv.mitareaemba),V10CADENA,
             "NUEVOESTATUS",&svdpickinv.nuevoestatus,sizeof(svdpickinv.nuevoestatus),V10LONG,
             "EJECMOVEMBA",svdpickinv.ejecmovemba,sizeof(svdpickinv.ejecmovemba),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selcreabultospinvconte(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselcreabultospinvconte=abrecursor(SELCREABULTOSPINVCONTE);
    definetodo(vdselcreabultospinvconte,NULL);
    bindtodo(vdselcreabultospinvconte,"CODMAT",svdpickinv.codmat,sizeof(svdpickinv.codmat),V10CADENA,
             "CODRECURSO",svdpickinv.codrecurso,sizeof(svdpickinv.codrecurso),V10CADENA,
             "TAREA",svdpickinv.tarea,sizeof(svdpickinv.tarea),V10CADENA,
             "STATUS1",&svdpickinv.status1,sizeof(svdpickinv.status1),V10LONG,
             "CODUBI",svdpickinv.codubi,sizeof(svdpickinv.codubi),V10CADENA,
             "MITAREARESTOS",svdpickinv.mitarearestos,sizeof(svdpickinv.mitarearestos),V10CADENA,
             "MICODCONCERESTOS",svdpickinv.micodconcerestos,sizeof(svdpickinv.micodconcerestos),V10CADENA,
             "MAXBULTOS",&svdpickinv.maxbultos,sizeof(svdpickinv.maxbultos),V10LONG,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selcopepickinv(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselcopepickinv=abrecursor(SELCOPEPICKINV);
    definetodo(vdselcopepickinv,svdpickinv.codope,sizeof(svdpickinv.codope),V10CADENA,
               NULL);
    bindtodo(vdselcopepickinv,"CODOPE",svdpickinv.codope,sizeof(svdpickinv.codope),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selregularizabpc(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselregularizabpc=abrecursor(SELREGULARIZABPC);
    definetodo(vdselregularizabpc,NULL);
    bindtodo(vdselregularizabpc,"CODBULTO",svdpickinv.codbulto,sizeof(svdpickinv.codbulto),V10CADENA,
             "CODMAT",svdpickinv.codmat,sizeof(svdpickinv.codmat),V10CADENA,
             "CODART",svdpickinv.codart,sizeof(svdpickinv.codart),V10CADENA,
             "CODLOT",svdpickinv.codlot,sizeof(svdpickinv.codlot),V10CADENA,
             "UNIEMB",&svdpickinv.uniemb,sizeof(svdpickinv.uniemb),V10DOUBLE,
             "CODUBIDEST",svdpickinv.codubidest,sizeof(svdpickinv.codubidest),V10CADENA,
             "CODUBIRESERVA",svdpickinv.codubireserva,sizeof(svdpickinv.codubireserva),V10CADENA,
             "CANTIDAD",&svdpickinv.cantidad,sizeof(svdpickinv.cantidad),V10DOUBLE,
             "CODCONCE",svdpickinv.codconce,sizeof(svdpickinv.codconce),V10CADENA,
             "CODUBICODCONCE",svdpickinv.codubicodconce,sizeof(svdpickinv.codubicodconce),V10CADENA,
             "OBSERV",svdpickinv.observ,sizeof(svdpickinv.observ),V10CADENA,
             "COMENTARIO",svdpickinv.comentario,sizeof(svdpickinv.comentario),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selregularizastkpinv(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselregularizastkpinv=abrecursor(SELREGULARIZASTKPINV);
    definetodo(vdselregularizastkpinv,NULL);
    bindtodo(vdselregularizastkpinv,"CODMAT",svdpickinv.codmat,sizeof(svdpickinv.codmat),V10CADENA,
             "ORDENSTK",&svdpickinv.ordenstk,sizeof(svdpickinv.ordenstk),V10LONG,
             "CODCONCE",svdpickinv.codconce,sizeof(svdpickinv.codconce),V10CADENA,
             "CODUBICODCONCE",svdpickinv.codubicodconce,sizeof(svdpickinv.codubicodconce),V10CADENA,
             "CANTIDAD",&svdpickinv.cantidad,sizeof(svdpickinv.cantidad),V10DOUBLE,
             "OBSERV",svdpickinv.observ,sizeof(svdpickinv.observ),V10CADENA,
             "NUEVOCODMOV",&svdpickinv.nuevocodmov,sizeof(svdpickinv.nuevocodmov),V10DOUBLE,
             "CODUBIDEST",svdpickinv.codubidest,sizeof(svdpickinv.codubidest),V10CADENA,
             "COMENTARIO",svdpickinv.comentario,sizeof(svdpickinv.comentario),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selpartemovpinv(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselpartemovpinv=abrecursor(SELPARTEMOVPINV);
    definetodo(vdselpartemovpinv,NULL);
    bindtodo(vdselpartemovpinv,"CODMOV",&svdpickinv.codmov,sizeof(svdpickinv.codmov),V10LONG,
             "CODUBIDEST",svdpickinv.codubidest,sizeof(svdpickinv.codubidest),V10CADENA,
             "CODMAT",svdpickinv.codmat,sizeof(svdpickinv.codmat),V10CADENA,
             "NUEVOCODMOV",&svdpickinv.nuevocodmov,sizeof(svdpickinv.nuevocodmov),V10DOUBLE,
             "COMENTARIO",svdpickinv.comentario,sizeof(svdpickinv.comentario),V10CADENA,
             "RET",&svdpickinv.ret,sizeof(svdpickinv.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selcreabpc(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselcreabpc=abrecursor(SELCREABPC);
    definetodo(vdselcreabpc,NULL);
    bindtodo(vdselcreabpc,"CODMAT",svdpickinv.codmat,sizeof(svdpickinv.codmat),V10CADENA,
             "STATUS1",&svdpickinv.status1,sizeof(svdpickinv.status1),V10LONG,
             "MSJERROR",svdpickinv.msjerror,sizeof(svdpickinv.msjerror),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_sellinsinprep(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdsellinsinprep=abrecursor(SELLINSINPREP);
    definetodo(vdsellinsinprep,svdpickinv.codbulto,sizeof(svdpickinv.codbulto),V10CADENA,
               &svdpickinv.seqlinea,sizeof(svdpickinv.seqlinea),V10LONG,
               &svdpickinv.cantpedida,sizeof(svdpickinv.cantpedida),V10DOUBLE,
               &svdpickinv.codmov,sizeof(svdpickinv.codmov),V10LONG,
               NULL);
    bindtodo(vdsellinsinprep,"CODPED",svdpickinv.codped,sizeof(svdpickinv.codped),V10CADENA,
             "CODDIV",svdpickinv.coddiv,sizeof(svdpickinv.coddiv),V10CADENA,
             "SEQPED",&svdpickinv.seqped,sizeof(svdpickinv.seqped),V10LONG,
             "CODART",svdpickinv.codart,sizeof(svdpickinv.codart),V10CADENA,
             "STATUSBUL",&svdpickinv.statusbul,sizeof(svdpickinv.statusbul),V10LONG,
             "STATUSBPL",&svdpickinv.statusbpl,sizeof(svdpickinv.statusbpl),V10LONG,
             "STATUS",&svdpickinv.status,sizeof(svdpickinv.status),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

static void init_selyaleidons(void)
{
    int nc;

    for(nc=0;nc<dvdpickinv[0].numcol;nc++) dvdpickinv[0].c[nc].offset-=(size_t)&svdpickinv;

    vdselyaleidons=abrecursor(SELYALEIDONS);
    definetodo(vdselyaleidons,svdpickinv.msjerror,sizeof(svdpickinv.msjerror),V10CADENA,
               NULL);
    bindtodo(vdselyaleidons,"NUMEROSERIE",svdpickinv.numeroserie,sizeof(svdpickinv.numeroserie),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_PICKINV);
        init = 1;
    }
}

diccionario *PICKINVdamediccionario(void)
{
    return(&dpickinv);
}

int PICKINVbuscacdispencendidos(long codzona,long status,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselcdispencendidos==NULL) init_selcdispencendidos();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codzona=codzona;
    svdpickinv.status=status;
    vdret=ejefetchcursor(vdselcdispencendidos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINVbuscacdispencendidos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVnextcdispencendidos(vdpickinvs *pickinv)
{
    int vdret;
    vdret=fetchcursor(vdselcdispencendidos);
    if (!vdret) {
        *pickinv=svdpickinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcdispencendidos);
    return(VD_EERRORACLE);
}

int PICKINVprocdametextozona(long idinfopick,long codzona,char *lectura,char *texto,vdpickinvs *pickinv)
{
    int vdret;
    if (vdseldametextozona==NULL) init_seldametextozona();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.idinfopick=idinfopick;
    svdpickinv.codzona=codzona;
    strcpy(svdpickinv.lectura,lectura);
    strcpy(svdpickinv.texto,texto);
    vdret=ejecutacursor(vdseldametextozona);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocdametextozona vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocfinvolumetria(char *coddiv,long anoped,char *codped,long seqped,char *forzarpickinv,long haypickinv,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselfinvolumetria==NULL) init_selfinvolumetria();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.coddiv,coddiv);
    svdpickinv.anoped=anoped;
    strcpy(svdpickinv.codped,codped);
    svdpickinv.seqped=seqped;
    strcpy(svdpickinv.forzarpickinv,forzarpickinv);
    svdpickinv.haypickinv=haypickinv;
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselfinvolumetria);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocfinvolumetria vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocequilibraserie(long codserieprep,long status1,long status2,long stpdteequili,long stpdtebulinv,long stpickinv,long nuevoestatus,char *forzarreenganche,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselequilibraserie==NULL) init_selequilibraserie();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codserieprep=codserieprep;
    svdpickinv.status1=status1;
    svdpickinv.status2=status2;
    svdpickinv.stpdteequili=stpdteequili;
    svdpickinv.stpdtebulinv=stpdtebulinv;
    svdpickinv.stpickinv=stpickinv;
    svdpickinv.nuevoestatus=nuevoestatus;
    strcpy(svdpickinv.forzarreenganche,forzarreenganche);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselequilibraserie);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocequilibraserie vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocreenganchapinv(long codserieprep,char *codart,char *mitareauni,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselreenganchapinv==NULL) init_selreenganchapinv();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codserieprep=codserieprep;
    strcpy(svdpickinv.codart,codart);
    strcpy(svdpickinv.mitareauni,mitareauni);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselreenganchapinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocreenganchapinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocreenganchaemba(long codserieprep,char *codart,char *mitareaemba,char *ejecmovemba,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselreenganchaemba==NULL) init_selreenganchaemba();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codserieprep=codserieprep;
    strcpy(svdpickinv.codart,codart);
    strcpy(svdpickinv.mitareaemba,mitareaemba);
    strcpy(svdpickinv.ejecmovemba,ejecmovemba);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselreenganchaemba);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocreenganchaemba vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocreenganchasprpinv(long codserieprep,long stpdteequili,long stpdtebulinv,long stpickinv,char *diferido,char *mitareauni,char *mitareaemba,long nuevoestatus,char *ejecmovemba,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselreenganchasprpinv==NULL) init_selreenganchasprpinv();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codserieprep=codserieprep;
    svdpickinv.stpdteequili=stpdteequili;
    svdpickinv.stpdtebulinv=stpdtebulinv;
    svdpickinv.stpickinv=stpickinv;
    strcpy(svdpickinv.diferido,diferido);
    strcpy(svdpickinv.mitareauni,mitareauni);
    strcpy(svdpickinv.mitareaemba,mitareaemba);
    svdpickinv.nuevoestatus=nuevoestatus;
    strcpy(svdpickinv.ejecmovemba,ejecmovemba);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselreenganchasprpinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocreenganchasprpinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVproccreabultospinvconte(char *codmat,char *codrecurso,char *tarea,long status1,char *codubi,char *mitarearestos,char *micodconcerestos,long maxbultos,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselcreabultospinvconte==NULL) init_selcreabultospinvconte();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codmat,codmat);
    strcpy(svdpickinv.codrecurso,codrecurso);
    strcpy(svdpickinv.tarea,tarea);
    svdpickinv.status1=status1;
    strcpy(svdpickinv.codubi,codubi);
    strcpy(svdpickinv.mitarearestos,mitarearestos);
    strcpy(svdpickinv.micodconcerestos,micodconcerestos);
    svdpickinv.maxbultos=maxbultos;
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselcreabultospinvconte);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVproccreabultospinvconte vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVbuscacopepickinv(char *codope,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselcopepickinv==NULL) init_selcopepickinv();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codope,codope);
    vdret=ejefetchcursor(vdselcopepickinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINVbuscacopepickinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVnextcopepickinv(vdpickinvs *pickinv)
{
    int vdret;
    vdret=fetchcursor(vdselcopepickinv);
    if (!vdret) {
        *pickinv=svdpickinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcopepickinv);
    return(VD_EERRORACLE);
}

int PICKINVprocregularizabpc(char *codbulto,char *codmat,char *codart,char *codlot,double uniemb,char *codubidest,char *codubireserva,double cantidad,char *codconce,char *codubicodconce,char *observ,char *comentario,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselregularizabpc==NULL) init_selregularizabpc();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codbulto,codbulto);
    strcpy(svdpickinv.codmat,codmat);
    strcpy(svdpickinv.codart,codart);
    strcpy(svdpickinv.codlot,codlot);
    svdpickinv.uniemb=uniemb;
    strcpy(svdpickinv.codubidest,codubidest);
    strcpy(svdpickinv.codubireserva,codubireserva);
    svdpickinv.cantidad=cantidad;
    strcpy(svdpickinv.codconce,codconce);
    strcpy(svdpickinv.codubicodconce,codubicodconce);
    strcpy(svdpickinv.observ,observ);
    strcpy(svdpickinv.comentario,comentario);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselregularizabpc);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocregularizabpc vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocregularizastkpinv(char *codmat,long ordenstk,char *codconce,char *codubicodconce,double cantidad,char *observ,double nuevocodmov,char *codubidest,char *comentario,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselregularizastkpinv==NULL) init_selregularizastkpinv();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codmat,codmat);
    svdpickinv.ordenstk=ordenstk;
    strcpy(svdpickinv.codconce,codconce);
    strcpy(svdpickinv.codubicodconce,codubicodconce);
    svdpickinv.cantidad=cantidad;
    strcpy(svdpickinv.observ,observ);
    svdpickinv.nuevocodmov=nuevocodmov;
    strcpy(svdpickinv.codubidest,codubidest);
    strcpy(svdpickinv.comentario,comentario);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselregularizastkpinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocregularizastkpinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVprocpartemovpinv(long codmov,char *codubidest,char *codmat,double nuevocodmov,char *comentario,long ret,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselpartemovpinv==NULL) init_selpartemovpinv();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    svdpickinv.codmov=codmov;
    strcpy(svdpickinv.codubidest,codubidest);
    strcpy(svdpickinv.codmat,codmat);
    svdpickinv.nuevocodmov=nuevocodmov;
    strcpy(svdpickinv.comentario,comentario);
    svdpickinv.ret=ret;
    vdret=ejecutacursor(vdselpartemovpinv);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVprocpartemovpinv vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVproccreabpc(char *codmat,long status1,char *msjerror,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselcreabpc==NULL) init_selcreabpc();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codmat,codmat);
    svdpickinv.status1=status1;
    strcpy(svdpickinv.msjerror,msjerror);
    vdret=ejecutacursor(vdselcreabpc);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta PICKINVproccreabpc vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVbuscalinsinprep(char *codped,char *coddiv,long seqped,char *codart,long statusbul,long statusbpl,long status,vdpickinvs *pickinv)
{
    int vdret;
    if (vdsellinsinprep==NULL) init_sellinsinprep();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.codped,codped);
    strcpy(svdpickinv.coddiv,coddiv);
    svdpickinv.seqped=seqped;
    strcpy(svdpickinv.codart,codart);
    svdpickinv.statusbul=statusbul;
    svdpickinv.statusbpl=statusbpl;
    svdpickinv.status=status;
    vdret=ejefetchcursor(vdsellinsinprep);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINVbuscalinsinprep vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVnextlinsinprep(vdpickinvs *pickinv)
{
    int vdret;
    vdret=fetchcursor(vdsellinsinprep);
    if (!vdret) {
        *pickinv=svdpickinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdsellinsinprep);
    return(VD_EERRORACLE);
}

int PICKINVbuscayaleidons(char *numeroserie,vdpickinvs *pickinv)
{
    int vdret;
    if (vdselyaleidons==NULL) init_selyaleidons();
    memset(&svdpickinv,0,sizeof(svdpickinv));
    strcpy(svdpickinv.numeroserie,numeroserie);
    vdret=ejefetchcursor(vdselyaleidons);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch PICKINVbuscayaleidons vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *pickinv=svdpickinv;
    return(vdret);
}

int PICKINVnextyaleidons(vdpickinvs *pickinv)
{
    int vdret;
    vdret=fetchcursor(vdselyaleidons);
    if (!vdret) {
        *pickinv=svdpickinv;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselyaleidons);
    return(VD_EERRORACLE);
}

char * PICKINVdebug(vdpickinvs *pickinv)
{
    debugestruct(&dpickinv,pickinv,msgdebugpickinv);
    return(msgdebugpickinv);
}

