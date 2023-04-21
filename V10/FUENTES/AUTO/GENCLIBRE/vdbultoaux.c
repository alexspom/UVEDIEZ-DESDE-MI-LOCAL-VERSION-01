// Modulo generado automaticamente a partir de VDBULTOAUX.DEF
//#***
//# VDBULTOAUX.DEF - Generaci�n autom�tica del c�digo c SOLOQUERY para Bultos
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : FPD
//# Revisado por: 
//# Fecha  : 28-03-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=BULTO;
//
//EXTRA=ESTADOPED,V10LONG;
//EXTRA=ACTPELIN,V10CADENA,2;
//EXTRA=RET,V10LONG;
//EXTRA=MIFLUJOC,V10CADENA,256
//EXTRA=MIFLUJOE,V10CADENA,256
//EXTRA=MIFLUJOU,V10CADENA,256
//EXTRA=TIPO,V10CADENA,2
//EXTRA=MIDIGITOEAN,V10CADENA,2;
//EXTRA=CALCULOPESO,V10CADENA,2;
//EXTRA=CALCULOVOLUMEN,V10CADENA,2;
//EXTRA=LINEABULTO,V10LONG;
//EXTRA=DIFERENCIA,V10LONG;
//EXTRA=INICIO,V10LONG;
//EXTRA=FIN,V10LONG;
//EXTRA=VERIF,V10CADENA,2;
//EXTRA=CANTAREGULARIZAR,V10LONG;
//EXTRA=MIFLUJOPREPICK,V10CADENA,256
//EXTRA=MIFLUJOPICKIV,V10CADENA,256
//#ROTURAS 
//EXTRA=CANTROTURA,V10DOUBLE;
//EXTRA=CANTASUSTITUIR,V10DOUBLE;
//EXTRA=TAREACONTE,V10CADENA,33;
//EXTRA=TAREAEMBA,V10CADENA,33;
//EXTRA=TAREAUNI,V10CADENA,33;
//EXTRA=STATUSCONTE,V10LONG;
//EXTRA=STATUSEMBA,V10LONG;
//EXTRA=STATUSUNI,V10LONG;
//EXTRA=STATUSNUEVOUNI,V10LONG;
//EXTRA=UNIAGRUPAEMBA,V10CADENA,2;
//EXTRA=UNIAGRUPAUNI,V10CADENA,2;
//EXTRA=MONOFORMATO,V10CADENA,2;
//EXTRA=REVISARCOMPLETO,V10CADENA,2;
//EXTRA=STNUEVOMOV,V10LONG;
//EXTRA=EJECMOV,V10LONG;
//EXTRA=CODMATPI,V10CADENA,18;
//EXTRA=CODMOVOUT,V10LONG;
//
//PROCEDURE=FINBULTO,BEGIN VDBULTO.FINBULTO(:VDBULTOCAB.CODBULTO,:VDBULTOCAB.STATUS,:ESTADOPED,:ACTPELIN,:RET); END;@
//PROCEDURE=TIPOBULTO, BEGIN
//                         VDBULTO.TIPOBULTO(:VDMOVIM.TAREA,:MIFLUJOC,:MIFLUJOE,:MIFLUJOPREPICK,:MIFLUJOPICKIV,:MIFLUJOU,:TIPO);
//                     END;@
//
//CURSOR=CODBULTO, SELECT VDBULTO.SELCODBULTO(:MIDIGITOEAN,:VDBULTOCAB.CODDIV) CODBULTO FROM DUAL;
//
//CURSOR=SECBULTOTMP, SELECT VDBULTO.SELCODBULTOTMP(:MIDIGITOEAN) SECBULTOTMP FROM DUAL;
//
//CURSOR=SECUENCIA, SELECT VDBULTO.DAMESECUENCIA(:VDBULTOCAB.CODBULTO) SECUENCIA FROM DUAL;
//  
//  
//PROCEDURE=CREABULTOS, BEGIN
//                       VDBULTO.CREABULTOS(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,
//                                          :MIFLUJOC,:MIFLUJOE,:MIFLUJOPREPICK,:MIFLUJOPICKIV,:MIFLUJOU,:MIDIGITOEAN,:RET);
//                      END;@
//
//PROCEDURE=BORRACABECERAYLINEAS, BEGIN VDBULTO.BORRACABECERAYLINEAS(:VDBULTOCAB.CODBULTO,:RET); END;@
//
//PROCEDURE=VOLUMETRIACAJASYCNT, BEGIN VDBULTO.VOLUMETRIACAJASYCONTENEDORES(:VDBULTOCAB.CODBULTO,:RET); END;@
//
//PROCEDURE=RENUMERABULTOS, BEGIN VDBULTO.RENUMERABULTOS(:VDPEDIDOCAB.CODDIV,:VDPEDIDOCAB.ANOPED,:VDPEDIDOCAB.CODPED,:VDPEDIDOCAB.SEQPED,
//                                                       :DIFERENCIA,:INICIO,:FIN,:RET); END;@
//
//CURSOR=LINEABULTO, SELECT NVL(MAX(SEQLINEA),0)+1 LINEABULTO
//                     FROM VDBULTOLIN
//                    WHERE CODBULTO=:VDBULTOCAB.CODBULTO;
//                    
//CURSOR=BULTOLINORDENMOVIM, SELECT BUL.SEQLINEA,BUL.CODART,BUL.CODMOV,BUL.CODLOT,BUL.CANTPEDIDA
//                             FROM VDBULTOLIN BUL,VDUBICA UBI,VDMOVIM MOV
//                            WHERE BUL.CODBULTO=:VDBULTOLIN.CODBULTO AND BUL.CODMOV=MOV.CODMOV AND 
//                                  MOV.CODUBIORI=UBI.CODUBI
//                           ORDER BY UBI.ORDENMOVIM,BUL.CODART;
//
//CURSOR=ULTIMOBULTO, SELECT MAX(NBULTO) ULTIMOBULTO
//                      FROM VDBULTOCAB
//                     WHERE CODDIV=:VDBULTOCAB.CODDIV AND ANOPED=:VDBULTOCAB.ANOPED AND
//                           CODPED=:VDBULTOCAB.CODPED AND SEQPED=:VDBULTOCAB.SEQPED AND 
//                           TIPOBULTO=:VDBULTOCAB.TIPOBULTO;
//
//SELECT=CHEQUEAVOLUMETRIA, SELECT CODART  
//                            FROM (SELECT CODART,SUM(CANTASERVIR) CANTASERVIR 
//                                    FROM VDPEDIDOLIN 
//                                   WHERE CODDIV=:VDBULTOCAB.CODDIV AND ANOPED=:VDBULTOCAB.ANOPED AND 
//                                         CODPED=:VDBULTOCAB.CODPED AND SEQPED=:VDBULTOCAB.SEQPED AND 
//                                         CANTASERVIR>0 AND STATUS=VDST.FPELASERVIR 
//                                  GROUP BY CODART) 
//                           WHERE (CODART,CANTASERVIR) NOT IN 
//                                 (SELECT BUL.CODART,SUM(CANTPEDIDA) CANTIDAD 
//                                    FROM VDBULTOLIN BUL,VDBULTOCAB BUC 
//                                   WHERE CODDIV=:VDBULTOCAB.CODDIV AND ANOPED=:VDBULTOCAB.ANOPED AND 
//                                         CODPED=:VDBULTOCAB.CODPED AND SEQPED=:VDBULTOCAB.SEQPED AND 
//                                         BUL.CODBULTO=BUC.CODBULTO 
//                                  GROUP BY BUL.CODART ) 
//                          UNION ALL 
//                          SELECT CODART  
//                            FROM (SELECT BUL.CODART,SUM(CANTPEDIDA) CANTIDAD 
//                                    FROM VDBULTOLIN BUL,VDBULTOCAB BUC 
//                                   WHERE CODDIV=:VDBULTOCAB.CODDIV AND ANOPED=:VDBULTOCAB.ANOPED AND 
//                                         CODPED=:VDBULTOCAB.CODPED AND SEQPED=:VDBULTOCAB.SEQPED AND 
//                                         BUL.CODBULTO=BUC.CODBULTO 
//                                  GROUP BY BUL.CODART) 
//                           WHERE (CODART,CANTIDAD) NOT IN 
//                                 (SELECT CODART,SUM(CANTASERVIR) CANTASERVIR 
//                                    FROM VDPEDIDOLIN 
//                                   WHERE CODDIV=:VDBULTOCAB.CODDIV AND ANOPED=:VDBULTOCAB.ANOPED AND 
//                                         CODPED=:VDBULTOCAB.CODPED AND SEQPED=:VDBULTOCAB.SEQPED AND 
//                                         CANTASERVIR>0 
//                                  GROUP BY CODART );
//                                  
//CURSOR=DAMEULTBULTO, SELECT VDBULTO.DAMEULTBULTO(:VDBULTOCAB.CODBULTO) VERIF FROM DUAL;
//
//PROCEDURE=ANULACANTPENDSERVIR,BEGIN VDBULTO.ANULACANTPENDSERVIR(:VDBULTOLIN.CODBULTO,:VDBULTOLIN.SEQLINEA,:CANTAREGULARIZAR,:RET); END;@
//
//PROCEDURE=ROTURABULTO,BEGIN VDROTURA.GENERAROTURA(:VDBULTOCAB.CODBULTO, :VDBULTOLIN.SEQLINEA, :CANTROTURA, :CANTASUSTITUIR, NULL, 0,
//                                                  :TAREACONTE, :TAREAEMBA, :TAREAUNI, :STATUSCONTE, :STATUSEMBA, :STATUSUNI, :STATUSNUEVOUNI,
//                                                  :UNIAGRUPAEMBA, :UNIAGRUPAUNI, :MONOFORMATO, :REVISARCOMPLETO, :VDSEMAFORO.CODSEMAFORO, :VDCONCEPTO.CODCONCE,
//                                                  :VDUBICA.CODUBI, :STNUEVOMOV, :RET); 
//                      END;@
//                      
//PROCEDURE=ROTURABULTOSTK,BEGIN VDROTURA.GENERAROTURA(:VDBULTOCAB.CODBULTO, :VDBULTOLIN.SEQLINEA, :CANTROTURA, 
//                               :CANTASUSTITUIR, :VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK, :TAREACONTE, :TAREAEMBA, :TAREAUNI, 0, 0, 0, 0,NULL, NULL, NULL, NULL, NULL, 
//                               :VDCONCEPTO.CODCONCE,:VDUBICA.CODUBI, 0, :RET); 
//                      END;@   
//                      
//PROCEDURE=CAMBIORESERVA,BEGIN VDROTURA.CAMBIORESERVA(:VDBULTOCAB.CODBULTO, :VDBULTOLIN.SEQLINEA, :CANTROTURA, 
//                               :VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK, :VDCONCEPTO.CODCONCE,:VDUBICA.CODUBI,:RET, :EJECMOV,:CODMOVOUT); 
//                        END;@        
//                        
//PROCEDURE=CAMBIORESERVAPI,BEGIN VDROTURA.CAMBIORESERVAPI(:VDBULTOCABPINV.CODBULTO, :CODMATPI, :CANTROTURA, 
//                               :VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK, :VDCONCEPTO.CODCONCE,:VDUBICA.CODUBI,:RET, :CODMOVOUT); 
//                        END;@                                                                  
//                      
//       

#include "vdpedidos.h"\

#define SELFINBULTO "BEGIN VDBULTO.FINBULTO(:CODBULTO,:STATUS,:ESTADOPED,:ACTPELIN,:RET); END;"
static v10cursors *vdselfinbulto;
#define SELTIPOBULTO " BEGIN VDBULTO.TIPOBULTO(:TAREA,:MIFLUJOC,:MIFLUJOE,:MIFLUJOPREPICK,:MIFLUJOPICKIV,:MIFLUJOU,:TIPO); END;"
static v10cursors *vdseltipobulto;
#define SELCODBULTO " BEGIN :CODBULTO:=VDBULTO.SELCODBULTO(:MIDIGITOEAN,:CODDIV); END;"
static v10cursors *vdselcodbulto;
#define SELSECBULTOTMP " SELECT VDBULTO.SELCODBULTOTMP(:MIDIGITOEAN) SECBULTOTMP FROM DUAL"
static v10cursors *vdselsecbultotmp;
#define SELSECUENCIA " SELECT VDBULTO.DAMESECUENCIA(:CODBULTO) SECUENCIA FROM DUAL"
static v10cursors *vdselsecuencia;
#define SELCREABULTOS " BEGIN VDBULTO.CREABULTOS(:CODDIV,:ANOPED,:CODPED,:SEQPED, :MIFLUJOC,:MIFLUJOE,:MIFLUJOPREPICK,:MIFLUJOPICKIV,:MIFLUJOU,:MIDIGITOEAN,:RET); END;"
static v10cursors *vdselcreabultos;
#define SELBORRACABECERAYLINEAS " BEGIN VDBULTO.BORRACABECERAYLINEAS(:CODBULTO,:RET); END;"
static v10cursors *vdselborracabeceraylineas;
#define SELVOLUMETRIACAJASYCNT " BEGIN VDBULTO.VOLUMETRIACAJASYCONTENEDORES(:CODBULTO,:RET); END;"
static v10cursors *vdselvolumetriacajasycnt;
#define SELRENUMERABULTOS " BEGIN VDBULTO.RENUMERABULTOS(:CODDIV,:ANOPED,:CODPED,:SEQPED, :DIFERENCIA,:INICIO,:FIN,:RET); END;"
static v10cursors *vdselrenumerabultos;
#define SELLINEABULTO " SELECT NVL(MAX(SEQLINEA),0)+1 LINEABULTO FROM VDBULTOLIN WHERE CODBULTO=:CODBULTO"
static v10cursors *vdsellineabulto;
#define SELBULTOLINORDENMOVIM " SELECT BUL.SEQLINEA,BUL.CODART,BUL.CODMOV,BUL.CODLOT,BUL.CANTPEDIDA FROM VDBULTOLIN BUL,VDUBICA UBI,VDMOVIM MOV WHERE BUL.CODBULTO=:CODBULTO AND BUL.CODMOV=MOV.CODMOV AND  MOV.CODUBIORI=UBI.CODUBI ORDER BY UBI.ORDENMOVIM,BUL.CODART"
static v10cursors *vdselbultolinordenmovim;
#define SELULTIMOBULTO " SELECT MAX(NBULTO) ULTIMOBULTO FROM VDBULTOCAB WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED AND  TIPOBULTO=:TIPOBULTO"
static v10cursors *vdselultimobulto;
#define SELCHEQUEAVOLUMETRIA " SELECT CODART   FROM (SELECT CODART,SUM(CANTASERVIR) CANTASERVIR  FROM VDPEDIDOLIN  WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND  CODPED=:CODPED AND SEQPED=:SEQPED AND  CANTASERVIR>0 AND STATUS=VDST.FPELASERVIR  GROUP BY CODART)  WHERE (CODART,CANTASERVIR) NOT IN  (SELECT BUL.CODART,SUM(CANTPEDIDA) CANTIDAD  FROM VDBULTOLIN BUL,VDBULTOCAB BUC  WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND  CODPED=:CODPED AND SEQPED=:SEQPED AND  BUL.CODBULTO=BUC.CODBULTO  GROUP BY BUL.CODART )  UNION ALL  SELECT CODART   FROM (SELECT BUL.CODART,SUM(CANTPEDIDA) CANTIDAD  FROM VDBULTOLIN BUL,VDBULTOCAB BUC  WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND  CODPED=:CODPED AND SEQPED=:SEQPED AND  BUL.CODBULTO=BUC.CODBULTO  GROUP BY BUL.CODART)  WHERE (CODART,CANTIDAD) NOT IN  (SELECT CODART,SUM(CANTASERVIR) CANTASERVIR  FROM VDPEDIDOLIN  WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND  CODPED=:CODPED AND SEQPED=:SEQPED AND  CANTASERVIR>0  GROUP BY CODART )"
static v10cursors *vdselchequeavolumetria;
#define SELDAMEULTBULTO " SELECT VDBULTO.DAMEULTBULTO(:CODBULTO) VERIF FROM DUAL"
static v10cursors *vdseldameultbulto;
#define SELANULACANTPENDSERVIR "BEGIN VDBULTO.ANULACANTPENDSERVIR(:CODBULTO,:SEQLINEA,:CANTAREGULARIZAR,:RET); END;"
static v10cursors *vdselanulacantpendservir;
#define SELROTURABULTO "BEGIN VDROTURA.GENERAROTURA(:CODBULTO, :SEQLINEA, :CANTROTURA, :CANTASUSTITUIR, NULL, 0, :TAREACONTE, :TAREAEMBA, :TAREAUNI, :STATUSCONTE, :STATUSEMBA, :STATUSUNI, :STATUSNUEVOUNI, :UNIAGRUPAEMBA, :UNIAGRUPAUNI, :MONOFORMATO, :REVISARCOMPLETO, :CODSEMAFORO, :CODCONCE, :CODUBI, :STNUEVOMOV, :RET);  END;"
static v10cursors *vdselroturabulto;
#define SELROTURABULTOSTK "BEGIN VDROTURA.GENERAROTURA(:CODBULTO, :SEQLINEA, :CANTROTURA,  :CANTASUSTITUIR, :CODMAT, :ORDENSTK, :TAREACONTE, :TAREAEMBA, :TAREAUNI, 0, 0, 0, 0,NULL, NULL, NULL, NULL, NULL,  :CODCONCE,:CODUBI, 0, :RET);  END;"
static v10cursors *vdselroturabultostk;
#define SELCAMBIORESERVA "BEGIN VDROTURA.CAMBIORESERVA(:CODBULTO, :SEQLINEA, :CANTROTURA,  :CODMAT, :ORDENSTK, :CODCONCE,:CODUBI,:RET, :EJECMOV,:CODMOVOUT);  END;"
static v10cursors *vdselcambioreserva;
#define SELCAMBIORESERVAPI "BEGIN VDROTURA.CAMBIORESERVAPI(:CODBULTO, :CODMATPI, :CANTROTURA,  :CODMAT, :ORDENSTK, :CODCONCE,:CODUBI,:RET, :CODMOVOUT);  END;"
static v10cursors *vdselcambioreservapi;

static vdbultos svdbulto;

static diccols colvdbulto[]={ 
    {"ESTADOPED",V10LONG,(int)&svdbulto.estadoped,sizeof(svdbulto.estadoped)},
    {"ACTPELIN",V10CADENA,(int)&svdbulto.actpelin,sizeof(svdbulto.actpelin)},
    {"RET",V10LONG,(int)&svdbulto.ret,sizeof(svdbulto.ret)},
    {"MIFLUJOC",V10CADENA,(int)&svdbulto.miflujoc,sizeof(svdbulto.miflujoc)},
    {"MIFLUJOE",V10CADENA,(int)&svdbulto.miflujoe,sizeof(svdbulto.miflujoe)},
    {"MIFLUJOU",V10CADENA,(int)&svdbulto.miflujou,sizeof(svdbulto.miflujou)},
    {"TIPO",V10CADENA,(int)&svdbulto.tipo,sizeof(svdbulto.tipo)},
    {"MIDIGITOEAN",V10CADENA,(int)&svdbulto.midigitoean,sizeof(svdbulto.midigitoean)},
    {"CALCULOPESO",V10CADENA,(int)&svdbulto.calculopeso,sizeof(svdbulto.calculopeso)},
    {"CALCULOVOLUMEN",V10CADENA,(int)&svdbulto.calculovolumen,sizeof(svdbulto.calculovolumen)},
    {"LINEABULTO",V10LONG,(int)&svdbulto.lineabulto,sizeof(svdbulto.lineabulto)},
    {"DIFERENCIA",V10LONG,(int)&svdbulto.diferencia,sizeof(svdbulto.diferencia)},
    {"INICIO",V10LONG,(int)&svdbulto.inicio,sizeof(svdbulto.inicio)},
    {"FIN",V10LONG,(int)&svdbulto.fin,sizeof(svdbulto.fin)},
    {"VERIF",V10CADENA,(int)&svdbulto.verif,sizeof(svdbulto.verif)},
    {"CANTAREGULARIZAR",V10LONG,(int)&svdbulto.cantaregularizar,sizeof(svdbulto.cantaregularizar)},
    {"MIFLUJOPREPICK",V10CADENA,(int)&svdbulto.miflujoprepick,sizeof(svdbulto.miflujoprepick)},
    {"MIFLUJOPICKIV",V10CADENA,(int)&svdbulto.miflujopickiv,sizeof(svdbulto.miflujopickiv)},
    {"CANTROTURA",V10DOUBLE,(int)&svdbulto.cantrotura,sizeof(svdbulto.cantrotura)},
    {"CANTASUSTITUIR",V10DOUBLE,(int)&svdbulto.cantasustituir,sizeof(svdbulto.cantasustituir)},
    {"TAREACONTE",V10CADENA,(int)&svdbulto.tareaconte,sizeof(svdbulto.tareaconte)},
    {"TAREAEMBA",V10CADENA,(int)&svdbulto.tareaemba,sizeof(svdbulto.tareaemba)},
    {"TAREAUNI",V10CADENA,(int)&svdbulto.tareauni,sizeof(svdbulto.tareauni)},
    {"STATUSCONTE",V10LONG,(int)&svdbulto.statusconte,sizeof(svdbulto.statusconte)},
    {"STATUSEMBA",V10LONG,(int)&svdbulto.statusemba,sizeof(svdbulto.statusemba)},
    {"STATUSUNI",V10LONG,(int)&svdbulto.statusuni,sizeof(svdbulto.statusuni)},
    {"STATUSNUEVOUNI",V10LONG,(int)&svdbulto.statusnuevouni,sizeof(svdbulto.statusnuevouni)},
    {"UNIAGRUPAEMBA",V10CADENA,(int)&svdbulto.uniagrupaemba,sizeof(svdbulto.uniagrupaemba)},
    {"UNIAGRUPAUNI",V10CADENA,(int)&svdbulto.uniagrupauni,sizeof(svdbulto.uniagrupauni)},
    {"MONOFORMATO",V10CADENA,(int)&svdbulto.monoformato,sizeof(svdbulto.monoformato)},
    {"REVISARCOMPLETO",V10CADENA,(int)&svdbulto.revisarcompleto,sizeof(svdbulto.revisarcompleto)},
    {"STNUEVOMOV",V10LONG,(int)&svdbulto.stnuevomov,sizeof(svdbulto.stnuevomov)},
    {"EJECMOV",V10LONG,(int)&svdbulto.ejecmov,sizeof(svdbulto.ejecmov)},
    {"CODMATPI",V10CADENA,(int)&svdbulto.codmatpi,sizeof(svdbulto.codmatpi)},
    {"CODMOVOUT",V10LONG,(int)&svdbulto.codmovout,sizeof(svdbulto.codmovout)},
    {"CODBULTO",V10CADENA,(int)&svdbulto.codbulto,sizeof(svdbulto.codbulto)},
    {"STATUS",V10LONG,(int)&svdbulto.status,sizeof(svdbulto.status)},
    {"TAREA",V10CADENA,(int)&svdbulto.tarea,sizeof(svdbulto.tarea)},
    {"CODDIV",V10CADENA,(int)&svdbulto.coddiv,sizeof(svdbulto.coddiv)},
    {"SECBULTOTMP",V10CADENA,(int)&svdbulto.secbultotmp,sizeof(svdbulto.secbultotmp)},
    {"SECUENCIA",V10LONG,(int)&svdbulto.secuencia,sizeof(svdbulto.secuencia)},
    {"ANOPED",V10LONG,(int)&svdbulto.anoped,sizeof(svdbulto.anoped)},
    {"CODPED",V10CADENA,(int)&svdbulto.codped,sizeof(svdbulto.codped)},
    {"SEQPED",V10LONG,(int)&svdbulto.seqped,sizeof(svdbulto.seqped)},
    {"SEQLINEA",V10LONG,(int)&svdbulto.seqlinea,sizeof(svdbulto.seqlinea)},
    {"CODART",V10CADENA,(int)&svdbulto.codart,sizeof(svdbulto.codart)},
    {"CODMOV",V10LONG,(int)&svdbulto.codmov,sizeof(svdbulto.codmov)},
    {"CODLOT",V10CADENA,(int)&svdbulto.codlot,sizeof(svdbulto.codlot)},
    {"CANTPEDIDA",V10DOUBLE,(int)&svdbulto.cantpedida,sizeof(svdbulto.cantpedida)},
    {"ULTIMOBULTO",V10LONG,(int)&svdbulto.ultimobulto,sizeof(svdbulto.ultimobulto)},
    {"TIPOBULTO",V10CADENA,(int)&svdbulto.tipobulto,sizeof(svdbulto.tipobulto)},
    {"CODSEMAFORO",V10CADENA,(int)&svdbulto.codsemaforo,sizeof(svdbulto.codsemaforo)},
    {"CODCONCE",V10CADENA,(int)&svdbulto.codconce,sizeof(svdbulto.codconce)},
    {"CODUBI",V10CADENA,(int)&svdbulto.codubi,sizeof(svdbulto.codubi)},
    {"CODMAT",V10CADENA,(int)&svdbulto.codmat,sizeof(svdbulto.codmat)},
    {"ORDENSTK",V10LONG,(int)&svdbulto.ordenstk,sizeof(svdbulto.ordenstk)}
    };

static diccionarios dvdbulto[]={
    {colvdbulto,56}
    };

diccionario dbulto={dvdbulto,1};

static char msgdebugbulto[LCADENABIG];

static int init=0;


static void fin_vd_BULTO(void)
{
    if(vdselfinbulto){
        liberacursor(vdselfinbulto);
        vdselfinbulto=NULL;
    }
    if(vdseltipobulto){
        liberacursor(vdseltipobulto);
        vdseltipobulto=NULL;
    }
    if(vdselcodbulto){
        liberacursor(vdselcodbulto);
        vdselcodbulto=NULL;
    }
    if(vdselsecbultotmp){
        liberacursor(vdselsecbultotmp);
        vdselsecbultotmp=NULL;
    }
    if(vdselsecuencia){
        liberacursor(vdselsecuencia);
        vdselsecuencia=NULL;
    }
    if(vdselcreabultos){
        liberacursor(vdselcreabultos);
        vdselcreabultos=NULL;
    }
    if(vdselborracabeceraylineas){
        liberacursor(vdselborracabeceraylineas);
        vdselborracabeceraylineas=NULL;
    }
    if(vdselvolumetriacajasycnt){
        liberacursor(vdselvolumetriacajasycnt);
        vdselvolumetriacajasycnt=NULL;
    }
    if(vdselrenumerabultos){
        liberacursor(vdselrenumerabultos);
        vdselrenumerabultos=NULL;
    }
    if(vdsellineabulto){
        liberacursor(vdsellineabulto);
        vdsellineabulto=NULL;
    }
    if(vdselbultolinordenmovim){
        liberacursor(vdselbultolinordenmovim);
        vdselbultolinordenmovim=NULL;
    }
    if(vdselultimobulto){
        liberacursor(vdselultimobulto);
        vdselultimobulto=NULL;
    }
    if(vdselchequeavolumetria){
        liberacursor(vdselchequeavolumetria);
        vdselchequeavolumetria=NULL;
    }
    if(vdseldameultbulto){
        liberacursor(vdseldameultbulto);
        vdseldameultbulto=NULL;
    }
    if(vdselanulacantpendservir){
        liberacursor(vdselanulacantpendservir);
        vdselanulacantpendservir=NULL;
    }
    if(vdselroturabulto){
        liberacursor(vdselroturabulto);
        vdselroturabulto=NULL;
    }
    if(vdselroturabultostk){
        liberacursor(vdselroturabultostk);
        vdselroturabultostk=NULL;
    }
    if(vdselcambioreserva){
        liberacursor(vdselcambioreserva);
        vdselcambioreserva=NULL;
    }
    if(vdselcambioreservapi){
        liberacursor(vdselcambioreservapi);
        vdselcambioreservapi=NULL;
    }
}


static void init_selfinbulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselfinbulto=abrecursor(SELFINBULTO);
    definetodo(vdselfinbulto,NULL);
    bindtodo(vdselfinbulto,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "STATUS",&svdbulto.status,sizeof(svdbulto.status),V10LONG,
             "ESTADOPED",&svdbulto.estadoped,sizeof(svdbulto.estadoped),V10LONG,
             "ACTPELIN",svdbulto.actpelin,sizeof(svdbulto.actpelin),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_seltipobulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdseltipobulto=abrecursor(SELTIPOBULTO);
    definetodo(vdseltipobulto,NULL);
    bindtodo(vdseltipobulto,"TAREA",svdbulto.tarea,sizeof(svdbulto.tarea),V10CADENA,
             "MIFLUJOC",svdbulto.miflujoc,sizeof(svdbulto.miflujoc),V10CADENA,
             "MIFLUJOE",svdbulto.miflujoe,sizeof(svdbulto.miflujoe),V10CADENA,
             "MIFLUJOPREPICK",svdbulto.miflujoprepick,sizeof(svdbulto.miflujoprepick),V10CADENA,
             "MIFLUJOPICKIV",svdbulto.miflujopickiv,sizeof(svdbulto.miflujopickiv),V10CADENA,
             "MIFLUJOU",svdbulto.miflujou,sizeof(svdbulto.miflujou),V10CADENA,
             "TIPO",svdbulto.tipo,sizeof(svdbulto.tipo),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selcodbulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselcodbulto=abrecursor(SELCODBULTO);
    bindtodo(vdselcodbulto,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
		                   "MIDIGITOEAN",svdbulto.midigitoean,sizeof(svdbulto.midigitoean),V10CADENA,
                           "CODDIV",svdbulto.coddiv,sizeof(svdbulto.coddiv),V10CADENA,
                           NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selsecbultotmp(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselsecbultotmp=abrecursor(SELSECBULTOTMP);
    definetodo(vdselsecbultotmp,svdbulto.secbultotmp,sizeof(svdbulto.secbultotmp),V10CADENA,
               NULL);
    bindtodo(vdselsecbultotmp,"MIDIGITOEAN",svdbulto.midigitoean,sizeof(svdbulto.midigitoean),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selsecuencia(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselsecuencia=abrecursor(SELSECUENCIA);
    definetodo(vdselsecuencia,&svdbulto.secuencia,sizeof(svdbulto.secuencia),V10LONG,
               NULL);
    bindtodo(vdselsecuencia,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selcreabultos(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselcreabultos=abrecursor(SELCREABULTOS);
    definetodo(vdselcreabultos,NULL);
    bindtodo(vdselcreabultos,"CODDIV",svdbulto.coddiv,sizeof(svdbulto.coddiv),V10CADENA,
             "ANOPED",&svdbulto.anoped,sizeof(svdbulto.anoped),V10LONG,
             "CODPED",svdbulto.codped,sizeof(svdbulto.codped),V10CADENA,
             "SEQPED",&svdbulto.seqped,sizeof(svdbulto.seqped),V10LONG,
             "MIFLUJOC",svdbulto.miflujoc,sizeof(svdbulto.miflujoc),V10CADENA,
             "MIFLUJOE",svdbulto.miflujoe,sizeof(svdbulto.miflujoe),V10CADENA,
             "MIFLUJOPREPICK",svdbulto.miflujoprepick,sizeof(svdbulto.miflujoprepick),V10CADENA,
             "MIFLUJOPICKIV",svdbulto.miflujopickiv,sizeof(svdbulto.miflujopickiv),V10CADENA,
             "MIFLUJOU",svdbulto.miflujou,sizeof(svdbulto.miflujou),V10CADENA,
             "MIDIGITOEAN",svdbulto.midigitoean,sizeof(svdbulto.midigitoean),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selborracabeceraylineas(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselborracabeceraylineas=abrecursor(SELBORRACABECERAYLINEAS);
    definetodo(vdselborracabeceraylineas,NULL);
    bindtodo(vdselborracabeceraylineas,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selvolumetriacajasycnt(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselvolumetriacajasycnt=abrecursor(SELVOLUMETRIACAJASYCNT);
    definetodo(vdselvolumetriacajasycnt,NULL);
    bindtodo(vdselvolumetriacajasycnt,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selrenumerabultos(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselrenumerabultos=abrecursor(SELRENUMERABULTOS);
    definetodo(vdselrenumerabultos,NULL);
    bindtodo(vdselrenumerabultos,"CODDIV",svdbulto.coddiv,sizeof(svdbulto.coddiv),V10CADENA,
             "ANOPED",&svdbulto.anoped,sizeof(svdbulto.anoped),V10LONG,
             "CODPED",svdbulto.codped,sizeof(svdbulto.codped),V10CADENA,
             "SEQPED",&svdbulto.seqped,sizeof(svdbulto.seqped),V10LONG,
             "DIFERENCIA",&svdbulto.diferencia,sizeof(svdbulto.diferencia),V10LONG,
             "INICIO",&svdbulto.inicio,sizeof(svdbulto.inicio),V10LONG,
             "FIN",&svdbulto.fin,sizeof(svdbulto.fin),V10LONG,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_sellineabulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdsellineabulto=abrecursor(SELLINEABULTO);
    definetodo(vdsellineabulto,&svdbulto.lineabulto,sizeof(svdbulto.lineabulto),V10LONG,
               NULL);
    bindtodo(vdsellineabulto,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selbultolinordenmovim(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselbultolinordenmovim=abrecursor(SELBULTOLINORDENMOVIM);
    definetodo(vdselbultolinordenmovim,&svdbulto.seqlinea,sizeof(svdbulto.seqlinea),V10LONG,
               svdbulto.codart,sizeof(svdbulto.codart),V10CADENA,
               &svdbulto.codmov,sizeof(svdbulto.codmov),V10LONG,
               svdbulto.codlot,sizeof(svdbulto.codlot),V10CADENA,
               &svdbulto.cantpedida,sizeof(svdbulto.cantpedida),V10DOUBLE,
               NULL);
    bindtodo(vdselbultolinordenmovim,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selultimobulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselultimobulto=abrecursor(SELULTIMOBULTO);
    definetodo(vdselultimobulto,&svdbulto.ultimobulto,sizeof(svdbulto.ultimobulto),V10LONG,
               NULL);
    bindtodo(vdselultimobulto,"CODDIV",svdbulto.coddiv,sizeof(svdbulto.coddiv),V10CADENA,
             "ANOPED",&svdbulto.anoped,sizeof(svdbulto.anoped),V10LONG,
             "CODPED",svdbulto.codped,sizeof(svdbulto.codped),V10CADENA,
             "SEQPED",&svdbulto.seqped,sizeof(svdbulto.seqped),V10LONG,
             "TIPOBULTO",svdbulto.tipobulto,sizeof(svdbulto.tipobulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selchequeavolumetria(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselchequeavolumetria=abrecursor(SELCHEQUEAVOLUMETRIA);
    definetodo(vdselchequeavolumetria,svdbulto.codart,sizeof(svdbulto.codart),V10CADENA,
               NULL);
    bindtodo(vdselchequeavolumetria,"CODDIV",svdbulto.coddiv,sizeof(svdbulto.coddiv),V10CADENA,
             "ANOPED",&svdbulto.anoped,sizeof(svdbulto.anoped),V10LONG,
             "CODPED",svdbulto.codped,sizeof(svdbulto.codped),V10CADENA,
             "SEQPED",&svdbulto.seqped,sizeof(svdbulto.seqped),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_seldameultbulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdseldameultbulto=abrecursor(SELDAMEULTBULTO);
    definetodo(vdseldameultbulto,svdbulto.verif,sizeof(svdbulto.verif),V10CADENA,
               NULL);
    bindtodo(vdseldameultbulto,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selanulacantpendservir(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselanulacantpendservir=abrecursor(SELANULACANTPENDSERVIR);
    definetodo(vdselanulacantpendservir,NULL);
    bindtodo(vdselanulacantpendservir,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "SEQLINEA",&svdbulto.seqlinea,sizeof(svdbulto.seqlinea),V10LONG,
             "CANTAREGULARIZAR",&svdbulto.cantaregularizar,sizeof(svdbulto.cantaregularizar),V10LONG,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selroturabulto(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselroturabulto=abrecursor(SELROTURABULTO);
    definetodo(vdselroturabulto,NULL);
    bindtodo(vdselroturabulto,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "SEQLINEA",&svdbulto.seqlinea,sizeof(svdbulto.seqlinea),V10LONG,
             "CANTROTURA",&svdbulto.cantrotura,sizeof(svdbulto.cantrotura),V10DOUBLE,
             "CANTASUSTITUIR",&svdbulto.cantasustituir,sizeof(svdbulto.cantasustituir),V10DOUBLE,
             "TAREACONTE",svdbulto.tareaconte,sizeof(svdbulto.tareaconte),V10CADENA,
             "TAREAEMBA",svdbulto.tareaemba,sizeof(svdbulto.tareaemba),V10CADENA,
             "TAREAUNI",svdbulto.tareauni,sizeof(svdbulto.tareauni),V10CADENA,
             "STATUSCONTE",&svdbulto.statusconte,sizeof(svdbulto.statusconte),V10LONG,
             "STATUSEMBA",&svdbulto.statusemba,sizeof(svdbulto.statusemba),V10LONG,
             "STATUSUNI",&svdbulto.statusuni,sizeof(svdbulto.statusuni),V10LONG,
             "STATUSNUEVOUNI",&svdbulto.statusnuevouni,sizeof(svdbulto.statusnuevouni),V10LONG,
             "UNIAGRUPAEMBA",svdbulto.uniagrupaemba,sizeof(svdbulto.uniagrupaemba),V10CADENA,
             "UNIAGRUPAUNI",svdbulto.uniagrupauni,sizeof(svdbulto.uniagrupauni),V10CADENA,
             "MONOFORMATO",svdbulto.monoformato,sizeof(svdbulto.monoformato),V10CADENA,
             "REVISARCOMPLETO",svdbulto.revisarcompleto,sizeof(svdbulto.revisarcompleto),V10CADENA,
             "CODSEMAFORO",svdbulto.codsemaforo,sizeof(svdbulto.codsemaforo),V10CADENA,
             "CODCONCE",svdbulto.codconce,sizeof(svdbulto.codconce),V10CADENA,
             "CODUBI",svdbulto.codubi,sizeof(svdbulto.codubi),V10CADENA,
             "STNUEVOMOV",&svdbulto.stnuevomov,sizeof(svdbulto.stnuevomov),V10LONG,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selroturabultostk(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselroturabultostk=abrecursor(SELROTURABULTOSTK);
    definetodo(vdselroturabultostk,NULL);
    bindtodo(vdselroturabultostk,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "SEQLINEA",&svdbulto.seqlinea,sizeof(svdbulto.seqlinea),V10LONG,
             "CANTROTURA",&svdbulto.cantrotura,sizeof(svdbulto.cantrotura),V10DOUBLE,
             "CANTASUSTITUIR",&svdbulto.cantasustituir,sizeof(svdbulto.cantasustituir),V10DOUBLE,
             "CODMAT",svdbulto.codmat,sizeof(svdbulto.codmat),V10CADENA,
             "ORDENSTK",&svdbulto.ordenstk,sizeof(svdbulto.ordenstk),V10LONG,
             "TAREACONTE",svdbulto.tareaconte,sizeof(svdbulto.tareaconte),V10CADENA,
             "TAREAEMBA",svdbulto.tareaemba,sizeof(svdbulto.tareaemba),V10CADENA,
             "TAREAUNI",svdbulto.tareauni,sizeof(svdbulto.tareauni),V10CADENA,
             "CODCONCE",svdbulto.codconce,sizeof(svdbulto.codconce),V10CADENA,
             "CODUBI",svdbulto.codubi,sizeof(svdbulto.codubi),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selcambioreserva(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselcambioreserva=abrecursor(SELCAMBIORESERVA);
    definetodo(vdselcambioreserva,NULL);
    bindtodo(vdselcambioreserva,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "SEQLINEA",&svdbulto.seqlinea,sizeof(svdbulto.seqlinea),V10LONG,
             "CANTROTURA",&svdbulto.cantrotura,sizeof(svdbulto.cantrotura),V10DOUBLE,
             "CODMAT",svdbulto.codmat,sizeof(svdbulto.codmat),V10CADENA,
             "ORDENSTK",&svdbulto.ordenstk,sizeof(svdbulto.ordenstk),V10LONG,
             "CODCONCE",svdbulto.codconce,sizeof(svdbulto.codconce),V10CADENA,
             "CODUBI",svdbulto.codubi,sizeof(svdbulto.codubi),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             "EJECMOV",&svdbulto.ejecmov,sizeof(svdbulto.ejecmov),V10LONG,
             "CODMOVOUT",&svdbulto.codmovout,sizeof(svdbulto.codmovout),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

static void init_selcambioreservapi(void)
{
    int nc;

    for(nc=0;nc<dvdbulto[0].numcol;nc++) dvdbulto[0].c[nc].offset-=(int)&svdbulto;

    vdselcambioreservapi=abrecursor(SELCAMBIORESERVAPI);
    definetodo(vdselcambioreservapi,NULL);
    bindtodo(vdselcambioreservapi,"CODBULTO",svdbulto.codbulto,sizeof(svdbulto.codbulto),V10CADENA,
             "CODMATPI",svdbulto.codmatpi,sizeof(svdbulto.codmatpi),V10CADENA,
             "CANTROTURA",&svdbulto.cantrotura,sizeof(svdbulto.cantrotura),V10DOUBLE,
             "CODMAT",svdbulto.codmat,sizeof(svdbulto.codmat),V10CADENA,
             "ORDENSTK",&svdbulto.ordenstk,sizeof(svdbulto.ordenstk),V10LONG,
             "CODCONCE",svdbulto.codconce,sizeof(svdbulto.codconce),V10CADENA,
             "CODUBI",svdbulto.codubi,sizeof(svdbulto.codubi),V10CADENA,
             "RET",&svdbulto.ret,sizeof(svdbulto.ret),V10LONG,
             "CODMOVOUT",&svdbulto.codmovout,sizeof(svdbulto.codmovout),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_BULTO);
        init = 1;
    }
}

diccionario *BULTOdamediccionario(void)
{
    return(&dbulto);
}

int BULTOprocfinbulto(char *codbulto,long status,long estadoped,char *actpelin,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselfinbulto==NULL) init_selfinbulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.status=status;
    svdbulto.estadoped=estadoped;
    strcpy(svdbulto.actpelin,actpelin);
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselfinbulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocfinbulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOproctipobulto(char *tarea,char *miflujoc,char *miflujoe,char *miflujoprepick,char *miflujopickiv,char *miflujou,char *tipo,vdbultos *bulto)
{
    int vdret;
    if (vdseltipobulto==NULL) init_seltipobulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.tarea,tarea);
    strcpy(svdbulto.miflujoc,miflujoc);
    strcpy(svdbulto.miflujoe,miflujoe);
    strcpy(svdbulto.miflujoprepick,miflujoprepick);
    strcpy(svdbulto.miflujopickiv,miflujopickiv);
    strcpy(svdbulto.miflujou,miflujou);
    strcpy(svdbulto.tipo,tipo);
    vdret=ejecutacursor(vdseltipobulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOproctipobulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTObuscacodbulto(char *midigitoean,char *coddiv,vdbultos *bulto)
{
    int vdret;
    if (vdselcodbulto==NULL) init_selcodbulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.midigitoean,midigitoean);
    strcpy(svdbulto.coddiv,coddiv);
    vdret=ejefetchcursor(vdselcodbulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscacodbulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextcodbulto(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdselcodbulto);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselcodbulto);
    return(VD_EERRORACLE);
}

int BULTObuscasecbultotmp(char *midigitoean,vdbultos *bulto)
{
    int vdret;
    if (vdselsecbultotmp==NULL) init_selsecbultotmp();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.midigitoean,midigitoean);
    vdret=ejefetchcursor(vdselsecbultotmp);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscasecbultotmp vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextsecbultotmp(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdselsecbultotmp);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselsecbultotmp);
    return(VD_EERRORACLE);
}

int BULTObuscasecuencia(char *codbulto,vdbultos *bulto)
{
    int vdret;
    if (vdselsecuencia==NULL) init_selsecuencia();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    vdret=ejefetchcursor(vdselsecuencia);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscasecuencia vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextsecuencia(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdselsecuencia);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselsecuencia);
    return(VD_EERRORACLE);
}

int BULTOproccreabultos(char *coddiv,long anoped,char *codped,long seqped,char *miflujoc,char *miflujoe,char *miflujoprepick,char *miflujopickiv,char *miflujou,char *midigitoean,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselcreabultos==NULL) init_selcreabultos();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.coddiv,coddiv);
    svdbulto.anoped=anoped;
    strcpy(svdbulto.codped,codped);
    svdbulto.seqped=seqped;
    strcpy(svdbulto.miflujoc,miflujoc);
    strcpy(svdbulto.miflujoe,miflujoe);
    strcpy(svdbulto.miflujoprepick,miflujoprepick);
    strcpy(svdbulto.miflujopickiv,miflujopickiv);
    strcpy(svdbulto.miflujou,miflujou);
    strcpy(svdbulto.midigitoean,midigitoean);
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselcreabultos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOproccreabultos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOprocborracabeceraylineas(char *codbulto,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselborracabeceraylineas==NULL) init_selborracabeceraylineas();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselborracabeceraylineas);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocborracabeceraylineas vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOprocvolumetriacajasycnt(char *codbulto,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselvolumetriacajasycnt==NULL) init_selvolumetriacajasycnt();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselvolumetriacajasycnt);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocvolumetriacajasycnt vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOprocrenumerabultos(char *coddiv,long anoped,char *codped,long seqped,long diferencia,long inicio,long fin,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselrenumerabultos==NULL) init_selrenumerabultos();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.coddiv,coddiv);
    svdbulto.anoped=anoped;
    strcpy(svdbulto.codped,codped);
    svdbulto.seqped=seqped;
    svdbulto.diferencia=diferencia;
    svdbulto.inicio=inicio;
    svdbulto.fin=fin;
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselrenumerabultos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocrenumerabultos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTObuscalineabulto(char *codbulto,vdbultos *bulto)
{
    int vdret;
    if (vdsellineabulto==NULL) init_sellineabulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    vdret=ejefetchcursor(vdsellineabulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscalineabulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextlineabulto(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdsellineabulto);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdsellineabulto);
    return(VD_EERRORACLE);
}

int BULTObuscabultolinordenmovim(char *codbulto,vdbultos *bulto)
{
    int vdret;
    if (vdselbultolinordenmovim==NULL) init_selbultolinordenmovim();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    vdret=ejefetchcursor(vdselbultolinordenmovim);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscabultolinordenmovim vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextbultolinordenmovim(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdselbultolinordenmovim);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselbultolinordenmovim);
    return(VD_EERRORACLE);
}

int BULTObuscaultimobulto(char *coddiv,long anoped,char *codped,long seqped,char *tipobulto,vdbultos *bulto)
{
    int vdret;
    if (vdselultimobulto==NULL) init_selultimobulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.coddiv,coddiv);
    svdbulto.anoped=anoped;
    strcpy(svdbulto.codped,codped);
    svdbulto.seqped=seqped;
    strcpy(svdbulto.tipobulto,tipobulto);
    vdret=ejefetchcursor(vdselultimobulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscaultimobulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextultimobulto(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdselultimobulto);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselultimobulto);
    return(VD_EERRORACLE);
}

int BULTOselchequeavolumetria(char *coddiv,long anoped,char *codped,long seqped,vdbultos *bulto)
{
    int vdret;
    if (vdselchequeavolumetria==NULL) init_selchequeavolumetria();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.coddiv,coddiv);
    svdbulto.anoped=anoped;
    strcpy(svdbulto.codped,codped);
    svdbulto.seqped=seqped;
    vdret=ejefetchcursor(vdselchequeavolumetria);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscachequeavolumetria vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTObuscadameultbulto(char *codbulto,vdbultos *bulto)
{
    int vdret;
    if (vdseldameultbulto==NULL) init_seldameultbulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    vdret=ejefetchcursor(vdseldameultbulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch BULTObuscadameultbulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOnextdameultbulto(vdbultos *bulto)
{
    int vdret;
    vdret=fetchcursor(vdseldameultbulto);
    if (!vdret) {
        *bulto=svdbulto;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldameultbulto);
    return(VD_EERRORACLE);
}

int BULTOprocanulacantpendservir(char *codbulto,long seqlinea,long cantaregularizar,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselanulacantpendservir==NULL) init_selanulacantpendservir();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.seqlinea=seqlinea;
    svdbulto.cantaregularizar=cantaregularizar;
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselanulacantpendservir);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocanulacantpendservir vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOprocroturabulto(char *codbulto,long seqlinea,double cantrotura,double cantasustituir,char *tareaconte,char *tareaemba,char *tareauni,long statusconte,long statusemba,long statusuni,long statusnuevouni,char *uniagrupaemba,char *uniagrupauni,char *monoformato,char *revisarcompleto,char *codsemaforo,char *codconce,char *codubi,long stnuevomov,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselroturabulto==NULL) init_selroturabulto();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.seqlinea=seqlinea;
    svdbulto.cantrotura=cantrotura;
    svdbulto.cantasustituir=cantasustituir;
    strcpy(svdbulto.tareaconte,tareaconte);
    strcpy(svdbulto.tareaemba,tareaemba);
    strcpy(svdbulto.tareauni,tareauni);
    svdbulto.statusconte=statusconte;
    svdbulto.statusemba=statusemba;
    svdbulto.statusuni=statusuni;
    svdbulto.statusnuevouni=statusnuevouni;
    strcpy(svdbulto.uniagrupaemba,uniagrupaemba);
    strcpy(svdbulto.uniagrupauni,uniagrupauni);
    strcpy(svdbulto.monoformato,monoformato);
    strcpy(svdbulto.revisarcompleto,revisarcompleto);
    strcpy(svdbulto.codsemaforo,codsemaforo);
    strcpy(svdbulto.codconce,codconce);
    strcpy(svdbulto.codubi,codubi);
    svdbulto.stnuevomov=stnuevomov;
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselroturabulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocroturabulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOprocroturabultostk(char *codbulto,long seqlinea,double cantrotura,double cantasustituir,char *codmat,long ordenstk,char *tareaconte,char *tareaemba,char *tareauni,char *codconce,char *codubi,long ret,vdbultos *bulto)
{
    int vdret;
    if (vdselroturabultostk==NULL) init_selroturabultostk();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.seqlinea=seqlinea;
    svdbulto.cantrotura=cantrotura;
    svdbulto.cantasustituir=cantasustituir;
    strcpy(svdbulto.codmat,codmat);
    svdbulto.ordenstk=ordenstk;
    strcpy(svdbulto.tareaconte,tareaconte);
    strcpy(svdbulto.tareaemba,tareaemba);
    strcpy(svdbulto.tareauni,tareauni);
    strcpy(svdbulto.codconce,codconce);
    strcpy(svdbulto.codubi,codubi);
    svdbulto.ret=ret;
    vdret=ejecutacursor(vdselroturabultostk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOprocroturabultostk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOproccambioreserva(char *codbulto,long seqlinea,double cantrotura,char *codmat,long ordenstk,char *codconce,char *codubi,long ret,long ejecmov,long codmovout,vdbultos *bulto)
{
    int vdret;
    if (vdselcambioreserva==NULL) init_selcambioreserva();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    svdbulto.seqlinea=seqlinea;
    svdbulto.cantrotura=cantrotura;
    strcpy(svdbulto.codmat,codmat);
    svdbulto.ordenstk=ordenstk;
    strcpy(svdbulto.codconce,codconce);
    strcpy(svdbulto.codubi,codubi);
    svdbulto.ret=ret;
    svdbulto.ejecmov=ejecmov;
    svdbulto.codmovout=codmovout;
    vdret=ejecutacursor(vdselcambioreserva);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOproccambioreserva vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

int BULTOproccambioreservapi(char *codbulto,char *codmatpi,double cantrotura,char *codmat,long ordenstk,char *codconce,char *codubi,long ret,long codmovout,vdbultos *bulto)
{
    int vdret;
    if (vdselcambioreservapi==NULL) init_selcambioreservapi();
    memset(&svdbulto,0,sizeof(svdbulto));
    strcpy(svdbulto.codbulto,codbulto);
    strcpy(svdbulto.codmatpi,codmatpi);
    svdbulto.cantrotura=cantrotura;
    strcpy(svdbulto.codmat,codmat);
    svdbulto.ordenstk=ordenstk;
    strcpy(svdbulto.codconce,codconce);
    strcpy(svdbulto.codubi,codubi);
    svdbulto.ret=ret;
    svdbulto.codmovout=codmovout;
    vdret=ejecutacursor(vdselcambioreservapi);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta BULTOproccambioreservapi vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *bulto=svdbulto;
    return(vdret);
}

char * BULTOdebug(vdbultos *bulto)
{
    debugestruct(&dbulto,bulto,msgdebugbulto);
    return(msgdebugbulto);
}

