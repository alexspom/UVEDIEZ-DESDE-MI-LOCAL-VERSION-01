// Modulo generado automaticamente a partir de VDSTOCKAUX.DEF
//#***
//# VDSTOCKAUX.DEF - Generaci�n autom�tica del c�digo c SOLOQUERY sobre la tabla VDSOTCK                                                    
//# 
//# Prop�sito: idem.
//#           
//# Autor	 : FGS
//# Revisado por: 
//# Fecha  : 19-02-2008                                               
//#********************************************************************************
//# Modificaciones
//#***
//NOMBRE=STKAUX;
//EXTRA=STATUSAUX,V10LONG
//EXTRA=RET,V10LONG
//EXTRA=CODMATESPERADO,V10CADENA,19
//EXTRA=CODMATLEIDO,V10CADENA,19
//EXTRA=CODCONCEENTRADA,V10CADENA,10
//EXTRA=CODCONCESALIDA,V10CADENA,10
//EXTRA=FUENTE,V10CADENA,12
//EXTRA=SUMIDERO,V10CADENA,12
//EXTRA=OBSERV,V10CADENA,4096
//EXTRA=MSJERROR,V10CADENA,1024
//EXTRA=CODMOVENTRADA,V10DOUBLE
//EXTRA=CODMOVSALIDA,V10DOUBLE
//EXTRA=CODMOVINTERNO,V10DOUBLE
//EXTRA=NUEVOORDENSTK,V10LONG
//EXTRA=DIFF,V10DOUBLE
//EXTRA=FUERZASTOCK,V10LONG
//EXTRA=VDSTOCK.CANTIDAD
//EXTRA=LIMPIAR,V10CADENA,1
//EXTRA=CODRECURSO,V10CADENA,32
//EXTRA=CODZONA,V10LONG
//EXTRA=TOTALNSL,V10LONG
//EXTRA=PATRONBLOQUEOSORI,V10CADENA,20
//EXTRA=OBSERV,V10CADENA,4096
//
//CURSOR=RESERVADOENCODMAT,SELECT  VDSTK.CNTRESERVADO (:VDCONTE.CODMAT, :VDUBICA.UNICAPAC, :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS) CANTIDAD FROM DUAL;
//
//CURSOR=DISPONIBLEENCODMAT,SELECT VDSTK.CNTDISPONIBLE(:VDCONTE.CODMAT, :VDUBICA.UNICAPAC, :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS) CANTIDAD FROM DUAL;
//   
//CURSOR=STOCKENCODMAT,SELECT VDSTK.CNTSTOCK(:VDCONTE.CODMAT, :VDUBICA.UNICAPAC, :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS) CANTIDAD FROM DUAL;
//   
//CURSOR=STOCKENCODUBI,SELECT VDSTK.UBISTOCK(:VDUBICA.CODUBI, :VDUBICA.UNICAPAC, :VDSTOCK.CODART, :VDSTOCK.CODLOT,:VDSTOCK.UNIEMB, :VDSTOCK.BLOQUEOS) CANTIDAD FROM DUAL;
// 
//CURSOR=STOCKLOTE, SELECT VDLOT.DAMECANTIDAD(:VDSTOCK.CODART, :VDSTOCK.CODLOT, :PATRONBLOQUEOSORI) CANTIDAD FROM DUAL;
//
//PROCEDURE=ACTSTOCKORI, BEGIN
//                         :RET :=VDACTSTOCK.actstkori(:VDMOVIM.CODMOV,:STATUSAUX);
//                      END;@
//
//PROCEDURE=ACTSTOCKDEST, BEGIN
//                         :RET :=VDACTSTOCK.actstkdest(:VDMOVIM.CODMOV,:STATUSAUX);
//                       END;@
//
//PROCEDURE=RECOGESTK,BEGIN
//                         VDMOV.RECOGESTK(:VDMOVIM.CODMOV,:STATUSAUX,:RET,:VDRECURSO.CODRECURSO);
//                    END;@
//                    
//PROCEDURE=DEPOSITASTK,BEGIN
//                         VDMOV.DEPOSITASTK(:VDMOVIM.CODMOV,:STATUSAUX,:RET);
//                    END;@            
//
//PROCEDURE=CONGELA,BEGIN
//                      :RET :=VDMOV.CONGELA(:VDMOVIM.CODMOV, :LIMPIAR);
//                  END;@    
//                  
//PROCEDURE=DESCONGELA,BEGIN
//                      VDMOV.LIMPIAMOV(:VDMOVIM.CODMOV);
//                     END;@    
//                                                            
//                         
//PROCEDURE=TRANSFORMASTK,BEGIN
//                           VDSTK.TRANSFORMASTK(:VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK,
//                                               :CODCONCEENTRADA, :FUENTE, 
//                                               :CODCONCESALIDA, :SUMIDERO, :OBSERV, 
//                                               :VDSTOCK.CODART, :VDSTOCK.CODLOT, :VDSTOCK.NUMEROSERIE,
//                                               :VDSTOCK.BULTO,  :VDSTOCK.MARCASTK, :VDSTOCK.CODRECEP,
//                                               :VDSTOCK.UNIEMB, :VDSTOCK.EMBCONT, :VDSTOCK.TIPOEMBA,
//                                               :VDSTOCK.PRECIOUNI, :VDSTOCK.PESOUNI, :VDSTOCK.BLOQUEOS,
//                                               :MSJERROR, :CODMOVENTRADA, :CODMOVSALIDA, :CODMOVINTERNO, :RET);
//                       END;@
//                       
//PROCEDURE=REGULARIZASTK,BEGIN
//                           VDSTK.REGULARIZASTK(:VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK,
//                                               :VDMOVIM.CODCONCE, :VDCONTE.CODUBI, 
//                                               :DIFF,  :OBSERV, :MSJERROR, :VDMOVIM.CODMOV, :RET);
//                        END;@ 
//                        
//PROCEDURE=DIVIDETK,BEGIN
//                           VDSTK.DIVIDESTK(:VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK,
//                                               :CODCONCEENTRADA, :FUENTE, 
//                                               :CODCONCESALIDA, :SUMIDERO,
//                                               :DIFF, :OBSERV, :MSJERROR, :CODMOVENTRADA, :CODMOVSALIDA, :NUEVOORDENSTK, :RET);
//                        END;@                                               
//                         
//                         
//PROCEDURE=CREASTK,BEGIN
//                           VDSTK.CREASTK(:VDSTOCK.CODMAT, :VDSTOCK.ORDENSTK,
//                                               :VDSTOCK.CODART, :VDSTOCK.CODLOT, :VDSTOCK.NUMEROSERIE,
//                                               :VDSTOCK.BULTO,  :VDSTOCK.MARCASTK, :VDSTOCK.CODRECEP,
//                                               :VDSTOCK.UNIEMB, :VDSTOCK.EMBCONT, :VDSTOCK.TIPOEMBA,
//                                               :VDSTOCK.PRECIOUNI, :VDSTOCK.PESOUNI, :VDSTOCK.BLOQUEOS,
//                                               :CANTIDAD,:CODCONCEENTRADA, :FUENTE, :OBSERV,:MSJERROR,:CODMOVENTRADA,:FUERZASTOCK,:RET);
//                       END;@    
//                       
//
//PROCEDURE=BLOQUEOSSTKBULTO, BEGIN
//                              VDLIBERA.BLOQUEOSSTKBULTO(:VDSTOCK.BULTO,:VDSTOCK.CODART,:VDSTOCK.CODLOT,:CODCONCEENTRADA, :FUENTE,:CODCONCESALIDA, :SUMIDERO,:PATRONBLOQUEOSORI,:VDSTOCK.BLOQUEOS,:OBSERV,:VDSTOCK.CANTIDAD,:VDCOMEN.COMENTARIO,:RET);
//                            END;@
//                            
//PROCEDURE=BLOQUEOSSTKRECEP, BEGIN
//                              VDLIBERA.BLOQUEOSSTKRECEP(:VDSTOCK.CODRECEP,:VDSTOCK.CODART,:VDSTOCK.CODLOT,:CODCONCEENTRADA, :FUENTE,:CODCONCESALIDA, :SUMIDERO, :PATRONBLOQUEOSORI,:VDSTOCK.BLOQUEOS,:OBSERV,:VDSTOCK.CANTIDAD,:VDCOMEN.COMENTARIO,:RET);
//                            END;@                                                   
//
//PROCEDURE=ACTSTKNS,BEGIN 
//                        VDSTK.ACTSTOCKNS(:VDSTOCK.CODMAT, :VDSTOCK.NUMEROSERIE, :VDSTOCK.CODOPEMODIF, :CODRECURSO, :CODZONA);
//                    END;@
//
//
//PROCEDURE=DELNUMLEIDOS, BEGIN VDSTK.DELNUMLEIDOS(:VDCONTE.CODMAT); END;@                    
//
//PROCEDURE=LIMPIANSSTOCK,BEGIN 
//                        VDSTK.LIMPIANSSTOCK(:VDSTOCK.CODMAT);
//                    END;@          
//
//
//
//
//PROCEDURE=ORDENASTOCKCONNS, BEGIN  
//                              VDSTK.ORDENASTOCKCONNS(:VDSTOCK.CODMAT, :TOTALNSL); 
//                            END;@
//
//
//
//
//%%h
// VDEXPORT int STKAUXactstockori(void *ptr,int statusfinal);
// VDEXPORT int STKAUXactstockdest(void *ptr,int statusfinal);
// 
//%%c      
// //Actualiza el stock origen y deja el movimiento preparado para que pase el actualizador de stock destino.
// VDEXPORT int STKAUXactstockori(void *ptr,int statusfinal) {
//   int ret=0;
//   vdmovims *mov=ptr;   
//   vdstkauxs stock;
//    
//   ret=STKAUXprocactstockori(ret,mov->codmov, statusfinal, &stock);
//   if (ret) {
//     *mov->comen=0;   
//   	strcpy(mov->comen,"STKactstockori: error ejecutando algoritmo PLSQL VDACTSTOCK.algactstkori\n");
//     v10log(LOGERROR,mov->comen);
//   	return(-1);
//   }
//   return(stock.ret);
// }  
// 
// //Actualiza el stock en la ubicaci�n destino.
// VDEXPORT int STKAUXactstockdest(void *ptr,int statusfinal) {
//    int ret=0;
//    vdmovims *mov=ptr;   
//    vdstkauxs stock;
//    
//    ret=STKAUXprocactstockdest(ret,mov->codmov, statusfinal, &stock);   
//    if (ret) {
//     *mov->comen=0;
//     strcpy(mov->comen,"STKactstockori: error ejecutando algoritmo PLSQL VDACTSTOCK.algactstkdest\n");
//   	v10log(LOGERROR,mov->comen);
//   	return(-1);
//    }
//    return(stock.ret);
// }  

#include "vd.h"\

#define SELRESERVADOENCODMAT "SELECT  VDSTK.CNTRESERVADO (:CODMAT, :UNICAPAC, :CODART, :CODLOT,:UNIEMB, :BLOQUEOS) CANTIDAD FROM DUAL"
static v10cursors *vdselreservadoencodmat;
#define SELDISPONIBLEENCODMAT "SELECT VDSTK.CNTDISPONIBLE(:CODMAT, :UNICAPAC, :CODART, :CODLOT,:UNIEMB, :BLOQUEOS) CANTIDAD FROM DUAL"
static v10cursors *vdseldisponibleencodmat;
#define SELSTOCKENCODMAT "SELECT VDSTK.CNTSTOCK(:CODMAT, :UNICAPAC, :CODART, :CODLOT,:UNIEMB, :BLOQUEOS) CANTIDAD FROM DUAL"
static v10cursors *vdselstockencodmat;
#define SELSTOCKENCODUBI "SELECT VDSTK.UBISTOCK(:CODUBI, :UNICAPAC, :CODART, :CODLOT,:UNIEMB, :BLOQUEOS) CANTIDAD FROM DUAL"
static v10cursors *vdselstockencodubi;
#define SELSTOCKLOTE " SELECT VDLOT.DAMECANTIDAD(:CODART, :CODLOT, :PATRONBLOQUEOSORI) CANTIDAD FROM DUAL"
static v10cursors *vdselstocklote;
#define SELACTSTOCKORI " BEGIN :RET :=VDACTSTOCK.actstkori(:CODMOV,:STATUSAUX); END;"
static v10cursors *vdselactstockori;
#define SELACTSTOCKDEST " BEGIN :RET :=VDACTSTOCK.actstkdest(:CODMOV,:STATUSAUX); END;"
static v10cursors *vdselactstockdest;
#define SELRECOGESTK "BEGIN VDMOV.RECOGESTK(:CODMOV,:STATUSAUX,:RET,:CODRECURSO); END;"
static v10cursors *vdselrecogestk;
#define SELDEPOSITASTK "BEGIN VDMOV.DEPOSITASTK(:CODMOV,:STATUSAUX,:RET); END;"
static v10cursors *vdseldepositastk;
#define SELCONGELA "BEGIN :RET :=VDMOV.CONGELA(:CODMOV, :LIMPIAR); END;"
static v10cursors *vdselcongela;
#define SELDESCONGELA "BEGIN VDMOV.LIMPIAMOV(:CODMOV); END;"
static v10cursors *vdseldescongela;
#define SELTRANSFORMASTK "BEGIN VDSTK.TRANSFORMASTK(:CODMAT, :ORDENSTK, :CODCONCEENTRADA, :FUENTE,  :CODCONCESALIDA, :SUMIDERO, :OBSERV,  :CODART, :CODLOT, :NUMEROSERIE, :BULTO,  :MARCASTK, :CODRECEP, :UNIEMB, :EMBCONT, :TIPOEMBA, :PRECIOUNI, :PESOUNI, :BLOQUEOS, :MSJERROR, :CODMOVENTRADA, :CODMOVSALIDA, :CODMOVINTERNO, :RET); END;"
static v10cursors *vdseltransformastk;
#define SELREGULARIZASTK "BEGIN VDSTK.REGULARIZASTK(:CODMAT, :ORDENSTK, :CODCONCE, :CODUBI,  :DIFF,  :OBSERV, :MSJERROR, :CODMOV, :RET); END;"
static v10cursors *vdselregularizastk;
#define SELDIVIDETK "BEGIN VDSTK.DIVIDESTK(:CODMAT, :ORDENSTK, :CODCONCEENTRADA, :FUENTE,  :CODCONCESALIDA, :SUMIDERO, :DIFF, :OBSERV, :MSJERROR, :CODMOVENTRADA, :CODMOVSALIDA, :NUEVOORDENSTK, :RET); END;"
static v10cursors *vdseldividetk;
#define SELCREASTK "BEGIN VDSTK.CREASTK(:CODMAT, :ORDENSTK, :CODART, :CODLOT, :NUMEROSERIE, :BULTO,  :MARCASTK, :CODRECEP, :UNIEMB, :EMBCONT, :TIPOEMBA, :PRECIOUNI, :PESOUNI, :BLOQUEOS, :CANTIDAD,:CODCONCEENTRADA, :FUENTE, :OBSERV,:MSJERROR,:CODMOVENTRADA,:FUERZASTOCK,:RET); END;"
static v10cursors *vdselcreastk;
#define SELBLOQUEOSSTKBULTO " BEGIN VDLIBERA.BLOQUEOSSTKBULTO(:BULTO,:CODART,:CODLOT,:CODCONCEENTRADA, :FUENTE,:CODCONCESALIDA, :SUMIDERO,:PATRONBLOQUEOSORI,:BLOQUEOS,:OBSERV,:CANTIDAD,:COMENTARIO,:RET); END;"
static v10cursors *vdselbloqueosstkbulto;
#define SELBLOQUEOSSTKRECEP " BEGIN VDLIBERA.BLOQUEOSSTKRECEP(:CODRECEP,:CODART,:CODLOT,:CODCONCEENTRADA, :FUENTE,:CODCONCESALIDA, :SUMIDERO, :PATRONBLOQUEOSORI,:BLOQUEOS,:OBSERV,:CANTIDAD,:COMENTARIO,:RET); END;"
static v10cursors *vdselbloqueosstkrecep;
#define SELACTSTKNS "BEGIN  VDSTK.ACTSTOCKNS(:CODMAT, :NUMEROSERIE, :CODOPEMODIF, :CODRECURSO, :CODZONA); END;"
static v10cursors *vdselactstkns;
#define SELDELNUMLEIDOS " BEGIN VDSTK.DELNUMLEIDOS(:CODMAT); END;"
static v10cursors *vdseldelnumleidos;
#define SELLIMPIANSSTOCK "BEGIN  VDSTK.LIMPIANSSTOCK(:CODMAT); END;"
static v10cursors *vdsellimpiansstock;
#define SELORDENASTOCKCONNS " BEGIN   VDSTK.ORDENASTOCKCONNS(:CODMAT, :TOTALNSL);  END;"
static v10cursors *vdselordenastockconns;

static vdstkauxs svdstkaux;

static diccols colvdstkaux[]={ 
    {"STATUSAUX",V10LONG,(size_t)&svdstkaux.statusaux,sizeof(svdstkaux.statusaux)},
    {"RET",V10LONG,(size_t)&svdstkaux.ret,sizeof(svdstkaux.ret)},
    {"CODMATESPERADO",V10CADENA,(size_t)&svdstkaux.codmatesperado,sizeof(svdstkaux.codmatesperado)},
    {"CODMATLEIDO",V10CADENA,(size_t)&svdstkaux.codmatleido,sizeof(svdstkaux.codmatleido)},
    {"CODCONCEENTRADA",V10CADENA,(size_t)&svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada)},
    {"CODCONCESALIDA",V10CADENA,(size_t)&svdstkaux.codconcesalida,sizeof(svdstkaux.codconcesalida)},
    {"FUENTE",V10CADENA,(size_t)&svdstkaux.fuente,sizeof(svdstkaux.fuente)},
    {"SUMIDERO",V10CADENA,(size_t)&svdstkaux.sumidero,sizeof(svdstkaux.sumidero)},
    {"OBSERV",V10CADENA,(size_t)&svdstkaux.observ,sizeof(svdstkaux.observ)},
    {"MSJERROR",V10CADENA,(size_t)&svdstkaux.msjerror,sizeof(svdstkaux.msjerror)},
    {"CODMOVENTRADA",V10DOUBLE,(size_t)&svdstkaux.codmoventrada,sizeof(svdstkaux.codmoventrada)},
    {"CODMOVSALIDA",V10DOUBLE,(size_t)&svdstkaux.codmovsalida,sizeof(svdstkaux.codmovsalida)},
    {"CODMOVINTERNO",V10DOUBLE,(size_t)&svdstkaux.codmovinterno,sizeof(svdstkaux.codmovinterno)},
    {"NUEVOORDENSTK",V10LONG,(size_t)&svdstkaux.nuevoordenstk,sizeof(svdstkaux.nuevoordenstk)},
    {"DIFF",V10DOUBLE,(size_t)&svdstkaux.diff,sizeof(svdstkaux.diff)},
    {"FUERZASTOCK",V10LONG,(size_t)&svdstkaux.fuerzastock,sizeof(svdstkaux.fuerzastock)},
    {"CANTIDAD",V10DOUBLE,(size_t)&svdstkaux.cantidad,sizeof(svdstkaux.cantidad)},
    {"LIMPIAR",V10CADENA,(size_t)&svdstkaux.limpiar,sizeof(svdstkaux.limpiar)},
    {"CODRECURSO",V10CADENA,(size_t)&svdstkaux.codrecurso,sizeof(svdstkaux.codrecurso)},
    {"CODZONA",V10LONG,(size_t)&svdstkaux.codzona,sizeof(svdstkaux.codzona)},
    {"TOTALNSL",V10LONG,(size_t)&svdstkaux.totalnsl,sizeof(svdstkaux.totalnsl)},
    {"PATRONBLOQUEOSORI",V10CADENA,(size_t)&svdstkaux.patronbloqueosori,sizeof(svdstkaux.patronbloqueosori)},
    {"CODMAT",V10CADENA,(size_t)&svdstkaux.codmat,sizeof(svdstkaux.codmat)},
    {"UNICAPAC",V10CADENA,(size_t)&svdstkaux.unicapac,sizeof(svdstkaux.unicapac)},
    {"CODART",V10CADENA,(size_t)&svdstkaux.codart,sizeof(svdstkaux.codart)},
    {"CODLOT",V10CADENA,(size_t)&svdstkaux.codlot,sizeof(svdstkaux.codlot)},
    {"UNIEMB",V10DOUBLE,(size_t)&svdstkaux.uniemb,sizeof(svdstkaux.uniemb)},
    {"BLOQUEOS",V10CADENA,(size_t)&svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos)},
    {"CODUBI",V10CADENA,(size_t)&svdstkaux.codubi,sizeof(svdstkaux.codubi)},
    {"CODMOV",V10LONG,(size_t)&svdstkaux.codmov,sizeof(svdstkaux.codmov)},
    {"ORDENSTK",V10LONG,(size_t)&svdstkaux.ordenstk,sizeof(svdstkaux.ordenstk)},
    {"NUMEROSERIE",V10CADENA,(size_t)&svdstkaux.numeroserie,sizeof(svdstkaux.numeroserie)},
    {"BULTO",V10CADENA,(size_t)&svdstkaux.bulto,sizeof(svdstkaux.bulto)},
    {"MARCASTK",V10CADENA,(size_t)&svdstkaux.marcastk,sizeof(svdstkaux.marcastk)},
    {"CODRECEP",V10CADENA,(size_t)&svdstkaux.codrecep,sizeof(svdstkaux.codrecep)},
    {"EMBCONT",V10LONG,(size_t)&svdstkaux.embcont,sizeof(svdstkaux.embcont)},
    {"TIPOEMBA",V10CADENA,(size_t)&svdstkaux.tipoemba,sizeof(svdstkaux.tipoemba)},
    {"PRECIOUNI",V10DOUBLE,(size_t)&svdstkaux.preciouni,sizeof(svdstkaux.preciouni)},
    {"PESOUNI",V10DOUBLE,(size_t)&svdstkaux.pesouni,sizeof(svdstkaux.pesouni)},
    {"CODCONCE",V10CADENA,(size_t)&svdstkaux.codconce,sizeof(svdstkaux.codconce)},
    {"COMENTARIO",V10CADENA,(size_t)&svdstkaux.comentario,sizeof(svdstkaux.comentario)},
    {"CODOPEMODIF",V10CADENA,(size_t)&svdstkaux.codopemodif,sizeof(svdstkaux.codopemodif)}
    };

static diccionarios dvdstkaux[]={
    {colvdstkaux,42}
    };

diccionario dstkaux={dvdstkaux,1};

static char msgdebugstkaux[LCADENABIG];

static int init=0;


static void fin_vd_STKAUX(void)
{
    if(vdselreservadoencodmat){
        liberacursor(vdselreservadoencodmat);
        vdselreservadoencodmat=NULL;
    }
    if(vdseldisponibleencodmat){
        liberacursor(vdseldisponibleencodmat);
        vdseldisponibleencodmat=NULL;
    }
    if(vdselstockencodmat){
        liberacursor(vdselstockencodmat);
        vdselstockencodmat=NULL;
    }
    if(vdselstockencodubi){
        liberacursor(vdselstockencodubi);
        vdselstockencodubi=NULL;
    }
    if(vdselstocklote){
        liberacursor(vdselstocklote);
        vdselstocklote=NULL;
    }
    if(vdselactstockori){
        liberacursor(vdselactstockori);
        vdselactstockori=NULL;
    }
    if(vdselactstockdest){
        liberacursor(vdselactstockdest);
        vdselactstockdest=NULL;
    }
    if(vdselrecogestk){
        liberacursor(vdselrecogestk);
        vdselrecogestk=NULL;
    }
    if(vdseldepositastk){
        liberacursor(vdseldepositastk);
        vdseldepositastk=NULL;
    }
    if(vdselcongela){
        liberacursor(vdselcongela);
        vdselcongela=NULL;
    }
    if(vdseldescongela){
        liberacursor(vdseldescongela);
        vdseldescongela=NULL;
    }
    if(vdseltransformastk){
        liberacursor(vdseltransformastk);
        vdseltransformastk=NULL;
    }
    if(vdselregularizastk){
        liberacursor(vdselregularizastk);
        vdselregularizastk=NULL;
    }
    if(vdseldividetk){
        liberacursor(vdseldividetk);
        vdseldividetk=NULL;
    }
    if(vdselcreastk){
        liberacursor(vdselcreastk);
        vdselcreastk=NULL;
    }
    if(vdselbloqueosstkbulto){
        liberacursor(vdselbloqueosstkbulto);
        vdselbloqueosstkbulto=NULL;
    }
    if(vdselbloqueosstkrecep){
        liberacursor(vdselbloqueosstkrecep);
        vdselbloqueosstkrecep=NULL;
    }
    if(vdselactstkns){
        liberacursor(vdselactstkns);
        vdselactstkns=NULL;
    }
    if(vdseldelnumleidos){
        liberacursor(vdseldelnumleidos);
        vdseldelnumleidos=NULL;
    }
    if(vdsellimpiansstock){
        liberacursor(vdsellimpiansstock);
        vdsellimpiansstock=NULL;
    }
    if(vdselordenastockconns){
        liberacursor(vdselordenastockconns);
        vdselordenastockconns=NULL;
    }
}


static void init_selreservadoencodmat(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselreservadoencodmat=abrecursor(SELRESERVADOENCODMAT);
    definetodo(vdselreservadoencodmat,&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdselreservadoencodmat,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "UNICAPAC",svdstkaux.unicapac,sizeof(svdstkaux.unicapac),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seldisponibleencodmat(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseldisponibleencodmat=abrecursor(SELDISPONIBLEENCODMAT);
    definetodo(vdseldisponibleencodmat,&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdseldisponibleencodmat,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "UNICAPAC",svdstkaux.unicapac,sizeof(svdstkaux.unicapac),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selstockencodmat(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselstockencodmat=abrecursor(SELSTOCKENCODMAT);
    definetodo(vdselstockencodmat,&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdselstockencodmat,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "UNICAPAC",svdstkaux.unicapac,sizeof(svdstkaux.unicapac),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selstockencodubi(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselstockencodubi=abrecursor(SELSTOCKENCODUBI);
    definetodo(vdselstockencodubi,&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdselstockencodubi,"CODUBI",svdstkaux.codubi,sizeof(svdstkaux.codubi),V10CADENA,
             "UNICAPAC",svdstkaux.unicapac,sizeof(svdstkaux.unicapac),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selstocklote(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselstocklote=abrecursor(SELSTOCKLOTE);
    definetodo(vdselstocklote,&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
               NULL);
    bindtodo(vdselstocklote,"CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "PATRONBLOQUEOSORI",svdstkaux.patronbloqueosori,sizeof(svdstkaux.patronbloqueosori),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selactstockori(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselactstockori=abrecursor(SELACTSTOCKORI);
    definetodo(vdselactstockori,NULL);
    bindtodo(vdselactstockori,"RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             "CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "STATUSAUX",&svdstkaux.statusaux,sizeof(svdstkaux.statusaux),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selactstockdest(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselactstockdest=abrecursor(SELACTSTOCKDEST);
    definetodo(vdselactstockdest,NULL);
    bindtodo(vdselactstockdest,"RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             "CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "STATUSAUX",&svdstkaux.statusaux,sizeof(svdstkaux.statusaux),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selrecogestk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselrecogestk=abrecursor(SELRECOGESTK);
    definetodo(vdselrecogestk,NULL);
    bindtodo(vdselrecogestk,"CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "STATUSAUX",&svdstkaux.statusaux,sizeof(svdstkaux.statusaux),V10LONG,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             "CODRECURSO",svdstkaux.codrecurso,sizeof(svdstkaux.codrecurso),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seldepositastk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseldepositastk=abrecursor(SELDEPOSITASTK);
    definetodo(vdseldepositastk,NULL);
    bindtodo(vdseldepositastk,"CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "STATUSAUX",&svdstkaux.statusaux,sizeof(svdstkaux.statusaux),V10LONG,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selcongela(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselcongela=abrecursor(SELCONGELA);
    definetodo(vdselcongela,NULL);
    bindtodo(vdselcongela,"RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             "CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "LIMPIAR",svdstkaux.limpiar,sizeof(svdstkaux.limpiar),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seldescongela(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseldescongela=abrecursor(SELDESCONGELA);
    definetodo(vdseldescongela,NULL);
    bindtodo(vdseldescongela,"CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seltransformastk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseltransformastk=abrecursor(SELTRANSFORMASTK);
    definetodo(vdseltransformastk,NULL);
    bindtodo(vdseltransformastk,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "ORDENSTK",&svdstkaux.ordenstk,sizeof(svdstkaux.ordenstk),V10LONG,
             "CODCONCEENTRADA",svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada),V10CADENA,
             "FUENTE",svdstkaux.fuente,sizeof(svdstkaux.fuente),V10CADENA,
             "CODCONCESALIDA",svdstkaux.codconcesalida,sizeof(svdstkaux.codconcesalida),V10CADENA,
             "SUMIDERO",svdstkaux.sumidero,sizeof(svdstkaux.sumidero),V10CADENA,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "NUMEROSERIE",svdstkaux.numeroserie,sizeof(svdstkaux.numeroserie),V10CADENA,
             "BULTO",svdstkaux.bulto,sizeof(svdstkaux.bulto),V10CADENA,
             "MARCASTK",svdstkaux.marcastk,sizeof(svdstkaux.marcastk),V10CADENA,
             "CODRECEP",svdstkaux.codrecep,sizeof(svdstkaux.codrecep),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "EMBCONT",&svdstkaux.embcont,sizeof(svdstkaux.embcont),V10LONG,
             "TIPOEMBA",svdstkaux.tipoemba,sizeof(svdstkaux.tipoemba),V10CADENA,
             "PRECIOUNI",&svdstkaux.preciouni,sizeof(svdstkaux.preciouni),V10DOUBLE,
             "PESOUNI",&svdstkaux.pesouni,sizeof(svdstkaux.pesouni),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             "MSJERROR",svdstkaux.msjerror,sizeof(svdstkaux.msjerror),V10CADENA,
             "CODMOVENTRADA",&svdstkaux.codmoventrada,sizeof(svdstkaux.codmoventrada),V10DOUBLE,
             "CODMOVSALIDA",&svdstkaux.codmovsalida,sizeof(svdstkaux.codmovsalida),V10DOUBLE,
             "CODMOVINTERNO",&svdstkaux.codmovinterno,sizeof(svdstkaux.codmovinterno),V10DOUBLE,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selregularizastk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselregularizastk=abrecursor(SELREGULARIZASTK);
    definetodo(vdselregularizastk,NULL);
    bindtodo(vdselregularizastk,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "ORDENSTK",&svdstkaux.ordenstk,sizeof(svdstkaux.ordenstk),V10LONG,
             "CODCONCE",svdstkaux.codconce,sizeof(svdstkaux.codconce),V10CADENA,
             "CODUBI",svdstkaux.codubi,sizeof(svdstkaux.codubi),V10CADENA,
             "DIFF",&svdstkaux.diff,sizeof(svdstkaux.diff),V10DOUBLE,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "MSJERROR",svdstkaux.msjerror,sizeof(svdstkaux.msjerror),V10CADENA,
             "CODMOV",&svdstkaux.codmov,sizeof(svdstkaux.codmov),V10LONG,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seldividetk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseldividetk=abrecursor(SELDIVIDETK);
    definetodo(vdseldividetk,NULL);
    bindtodo(vdseldividetk,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "ORDENSTK",&svdstkaux.ordenstk,sizeof(svdstkaux.ordenstk),V10LONG,
             "CODCONCEENTRADA",svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada),V10CADENA,
             "FUENTE",svdstkaux.fuente,sizeof(svdstkaux.fuente),V10CADENA,
             "CODCONCESALIDA",svdstkaux.codconcesalida,sizeof(svdstkaux.codconcesalida),V10CADENA,
             "SUMIDERO",svdstkaux.sumidero,sizeof(svdstkaux.sumidero),V10CADENA,
             "DIFF",&svdstkaux.diff,sizeof(svdstkaux.diff),V10DOUBLE,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "MSJERROR",svdstkaux.msjerror,sizeof(svdstkaux.msjerror),V10CADENA,
             "CODMOVENTRADA",&svdstkaux.codmoventrada,sizeof(svdstkaux.codmoventrada),V10DOUBLE,
             "CODMOVSALIDA",&svdstkaux.codmovsalida,sizeof(svdstkaux.codmovsalida),V10DOUBLE,
             "NUEVOORDENSTK",&svdstkaux.nuevoordenstk,sizeof(svdstkaux.nuevoordenstk),V10LONG,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selcreastk(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselcreastk=abrecursor(SELCREASTK);
    definetodo(vdselcreastk,NULL);
    bindtodo(vdselcreastk,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "ORDENSTK",&svdstkaux.ordenstk,sizeof(svdstkaux.ordenstk),V10LONG,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "NUMEROSERIE",svdstkaux.numeroserie,sizeof(svdstkaux.numeroserie),V10CADENA,
             "BULTO",svdstkaux.bulto,sizeof(svdstkaux.bulto),V10CADENA,
             "MARCASTK",svdstkaux.marcastk,sizeof(svdstkaux.marcastk),V10CADENA,
             "CODRECEP",svdstkaux.codrecep,sizeof(svdstkaux.codrecep),V10CADENA,
             "UNIEMB",&svdstkaux.uniemb,sizeof(svdstkaux.uniemb),V10DOUBLE,
             "EMBCONT",&svdstkaux.embcont,sizeof(svdstkaux.embcont),V10LONG,
             "TIPOEMBA",svdstkaux.tipoemba,sizeof(svdstkaux.tipoemba),V10CADENA,
             "PRECIOUNI",&svdstkaux.preciouni,sizeof(svdstkaux.preciouni),V10DOUBLE,
             "PESOUNI",&svdstkaux.pesouni,sizeof(svdstkaux.pesouni),V10DOUBLE,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             "CANTIDAD",&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
             "CODCONCEENTRADA",svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada),V10CADENA,
             "FUENTE",svdstkaux.fuente,sizeof(svdstkaux.fuente),V10CADENA,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "MSJERROR",svdstkaux.msjerror,sizeof(svdstkaux.msjerror),V10CADENA,
             "CODMOVENTRADA",&svdstkaux.codmoventrada,sizeof(svdstkaux.codmoventrada),V10DOUBLE,
             "FUERZASTOCK",&svdstkaux.fuerzastock,sizeof(svdstkaux.fuerzastock),V10LONG,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selbloqueosstkbulto(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselbloqueosstkbulto=abrecursor(SELBLOQUEOSSTKBULTO);
    definetodo(vdselbloqueosstkbulto,NULL);
    bindtodo(vdselbloqueosstkbulto,"BULTO",svdstkaux.bulto,sizeof(svdstkaux.bulto),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "CODCONCEENTRADA",svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada),V10CADENA,
             "FUENTE",svdstkaux.fuente,sizeof(svdstkaux.fuente),V10CADENA,
             "CODCONCESALIDA",svdstkaux.codconcesalida,sizeof(svdstkaux.codconcesalida),V10CADENA,
             "SUMIDERO",svdstkaux.sumidero,sizeof(svdstkaux.sumidero),V10CADENA,
             "PATRONBLOQUEOSORI",svdstkaux.patronbloqueosori,sizeof(svdstkaux.patronbloqueosori),V10CADENA,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "CANTIDAD",&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
             "COMENTARIO",svdstkaux.comentario,sizeof(svdstkaux.comentario),V10CADENA,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selbloqueosstkrecep(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselbloqueosstkrecep=abrecursor(SELBLOQUEOSSTKRECEP);
    definetodo(vdselbloqueosstkrecep,NULL);
    bindtodo(vdselbloqueosstkrecep,"CODRECEP",svdstkaux.codrecep,sizeof(svdstkaux.codrecep),V10CADENA,
             "CODART",svdstkaux.codart,sizeof(svdstkaux.codart),V10CADENA,
             "CODLOT",svdstkaux.codlot,sizeof(svdstkaux.codlot),V10CADENA,
             "CODCONCEENTRADA",svdstkaux.codconceentrada,sizeof(svdstkaux.codconceentrada),V10CADENA,
             "FUENTE",svdstkaux.fuente,sizeof(svdstkaux.fuente),V10CADENA,
             "CODCONCESALIDA",svdstkaux.codconcesalida,sizeof(svdstkaux.codconcesalida),V10CADENA,
             "SUMIDERO",svdstkaux.sumidero,sizeof(svdstkaux.sumidero),V10CADENA,
             "PATRONBLOQUEOSORI",svdstkaux.patronbloqueosori,sizeof(svdstkaux.patronbloqueosori),V10CADENA,
             "BLOQUEOS",svdstkaux.bloqueos,sizeof(svdstkaux.bloqueos),V10CADENA,
             "OBSERV",svdstkaux.observ,sizeof(svdstkaux.observ),V10CADENA,
             "CANTIDAD",&svdstkaux.cantidad,sizeof(svdstkaux.cantidad),V10DOUBLE,
             "COMENTARIO",svdstkaux.comentario,sizeof(svdstkaux.comentario),V10CADENA,
             "RET",&svdstkaux.ret,sizeof(svdstkaux.ret),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selactstkns(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselactstkns=abrecursor(SELACTSTKNS);
    definetodo(vdselactstkns,NULL);
    bindtodo(vdselactstkns,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "NUMEROSERIE",svdstkaux.numeroserie,sizeof(svdstkaux.numeroserie),V10CADENA,
             "CODOPEMODIF",svdstkaux.codopemodif,sizeof(svdstkaux.codopemodif),V10CADENA,
             "CODRECURSO",svdstkaux.codrecurso,sizeof(svdstkaux.codrecurso),V10CADENA,
             "CODZONA",&svdstkaux.codzona,sizeof(svdstkaux.codzona),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_seldelnumleidos(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdseldelnumleidos=abrecursor(SELDELNUMLEIDOS);
    definetodo(vdseldelnumleidos,NULL);
    bindtodo(vdseldelnumleidos,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_sellimpiansstock(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdsellimpiansstock=abrecursor(SELLIMPIANSSTOCK);
    definetodo(vdsellimpiansstock,NULL);
    bindtodo(vdsellimpiansstock,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

static void init_selordenastockconns(void)
{
    int nc;

    for(nc=0;nc<dvdstkaux[0].numcol;nc++) dvdstkaux[0].c[nc].offset-=(size_t)&svdstkaux;

    vdselordenastockconns=abrecursor(SELORDENASTOCKCONNS);
    definetodo(vdselordenastockconns,NULL);
    bindtodo(vdselordenastockconns,"CODMAT",svdstkaux.codmat,sizeof(svdstkaux.codmat),V10CADENA,
             "TOTALNSL",&svdstkaux.totalnsl,sizeof(svdstkaux.totalnsl),V10LONG,
             NULL);

    if (init == 0) {
        atexit(fin_vd_STKAUX);
        init = 1;
    }
}

diccionario *STKAUXdamediccionario(void)
{
    return(&dstkaux);
}

int STKAUXbuscareservadoencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselreservadoencodmat==NULL) init_selreservadoencodmat();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    strcpy(svdstkaux.unicapac,unicapac);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    svdstkaux.uniemb=uniemb;
    strcpy(svdstkaux.bloqueos,bloqueos);
    vdret=ejefetchcursor(vdselreservadoencodmat);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch STKAUXbuscareservadoencodmat vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXnextreservadoencodmat(vdstkauxs *stkaux)
{
    int vdret;
    vdret=fetchcursor(vdselreservadoencodmat);
    if (!vdret) {
        *stkaux=svdstkaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselreservadoencodmat);
    return(VD_EERRORACLE);
}

int STKAUXbuscadisponibleencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseldisponibleencodmat==NULL) init_seldisponibleencodmat();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    strcpy(svdstkaux.unicapac,unicapac);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    svdstkaux.uniemb=uniemb;
    strcpy(svdstkaux.bloqueos,bloqueos);
    vdret=ejefetchcursor(vdseldisponibleencodmat);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch STKAUXbuscadisponibleencodmat vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXnextdisponibleencodmat(vdstkauxs *stkaux)
{
    int vdret;
    vdret=fetchcursor(vdseldisponibleencodmat);
    if (!vdret) {
        *stkaux=svdstkaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdseldisponibleencodmat);
    return(VD_EERRORACLE);
}

int STKAUXbuscastockencodmat(char *codmat,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselstockencodmat==NULL) init_selstockencodmat();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    strcpy(svdstkaux.unicapac,unicapac);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    svdstkaux.uniemb=uniemb;
    strcpy(svdstkaux.bloqueos,bloqueos);
    vdret=ejefetchcursor(vdselstockencodmat);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch STKAUXbuscastockencodmat vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXnextstockencodmat(vdstkauxs *stkaux)
{
    int vdret;
    vdret=fetchcursor(vdselstockencodmat);
    if (!vdret) {
        *stkaux=svdstkaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstockencodmat);
    return(VD_EERRORACLE);
}

int STKAUXbuscastockencodubi(char *codubi,char *unicapac,char *codart,char *codlot,double uniemb,char *bloqueos,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselstockencodubi==NULL) init_selstockencodubi();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codubi,codubi);
    strcpy(svdstkaux.unicapac,unicapac);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    svdstkaux.uniemb=uniemb;
    strcpy(svdstkaux.bloqueos,bloqueos);
    vdret=ejefetchcursor(vdselstockencodubi);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch STKAUXbuscastockencodubi vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXnextstockencodubi(vdstkauxs *stkaux)
{
    int vdret;
    vdret=fetchcursor(vdselstockencodubi);
    if (!vdret) {
        *stkaux=svdstkaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstockencodubi);
    return(VD_EERRORACLE);
}

int STKAUXbuscastocklote(char *codart,char *codlot,char *patronbloqueosori,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselstocklote==NULL) init_selstocklote();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    strcpy(svdstkaux.patronbloqueosori,patronbloqueosori);
    vdret=ejefetchcursor(vdselstocklote);
    if(vdret) {
        v10log(LOGDEBUG,"Ejefetch STKAUXbuscastocklote vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXnextstocklote(vdstkauxs *stkaux)
{
    int vdret;
    vdret=fetchcursor(vdselstocklote);
    if (!vdret) {
        *stkaux=svdstkaux;
        v10log(LOGDEBUG,"Siguiente vdret %d. \n", vdret);
        return(vdret);
    }
    if(vdret!=NOFOUND) cursordebug(vdselstocklote);
    return(VD_EERRORACLE);
}

int STKAUXprocactstockori(long ret,long codmov,long statusaux,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselactstockori==NULL) init_selactstockori();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.ret=ret;
    svdstkaux.codmov=codmov;
    svdstkaux.statusaux=statusaux;
    vdret=ejecutacursor(vdselactstockori);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocactstockori vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocactstockdest(long ret,long codmov,long statusaux,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselactstockdest==NULL) init_selactstockdest();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.ret=ret;
    svdstkaux.codmov=codmov;
    svdstkaux.statusaux=statusaux;
    vdret=ejecutacursor(vdselactstockdest);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocactstockdest vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocrecogestk(long codmov,long statusaux,long ret,char *codrecurso,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselrecogestk==NULL) init_selrecogestk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.codmov=codmov;
    svdstkaux.statusaux=statusaux;
    svdstkaux.ret=ret;
    strcpy(svdstkaux.codrecurso,codrecurso);
    vdret=ejecutacursor(vdselrecogestk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocrecogestk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocdepositastk(long codmov,long statusaux,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseldepositastk==NULL) init_seldepositastk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.codmov=codmov;
    svdstkaux.statusaux=statusaux;
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdseldepositastk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocdepositastk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXproccongela(long ret,long codmov,char *limpiar,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselcongela==NULL) init_selcongela();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.ret=ret;
    svdstkaux.codmov=codmov;
    strcpy(svdstkaux.limpiar,limpiar);
    vdret=ejecutacursor(vdselcongela);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXproccongela vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocdescongela(long codmov,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseldescongela==NULL) init_seldescongela();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    svdstkaux.codmov=codmov;
    vdret=ejecutacursor(vdseldescongela);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocdescongela vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXproctransformastk(char *codmat,long ordenstk,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *observ,char *codart,char *codlot,char *numeroserie,char *bulto,char *marcastk,char *codrecep,double uniemb,long embcont,char *tipoemba,double preciouni,double pesouni,char *bloqueos,char *msjerror,double codmoventrada,double codmovsalida,double codmovinterno,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseltransformastk==NULL) init_seltransformastk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    svdstkaux.ordenstk=ordenstk;
    strcpy(svdstkaux.codconceentrada,codconceentrada);
    strcpy(svdstkaux.fuente,fuente);
    strcpy(svdstkaux.codconcesalida,codconcesalida);
    strcpy(svdstkaux.sumidero,sumidero);
    strcpy(svdstkaux.observ,observ);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    strcpy(svdstkaux.numeroserie,numeroserie);
    strcpy(svdstkaux.bulto,bulto);
    strcpy(svdstkaux.marcastk,marcastk);
    strcpy(svdstkaux.codrecep,codrecep);
    svdstkaux.uniemb=uniemb;
    svdstkaux.embcont=embcont;
    strcpy(svdstkaux.tipoemba,tipoemba);
    svdstkaux.preciouni=preciouni;
    svdstkaux.pesouni=pesouni;
    strcpy(svdstkaux.bloqueos,bloqueos);
    strcpy(svdstkaux.msjerror,msjerror);
    svdstkaux.codmoventrada=codmoventrada;
    svdstkaux.codmovsalida=codmovsalida;
    svdstkaux.codmovinterno=codmovinterno;
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdseltransformastk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXproctransformastk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocregularizastk(char *codmat,long ordenstk,char *codconce,char *codubi,double diff,char *observ,char *msjerror,long codmov,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselregularizastk==NULL) init_selregularizastk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    svdstkaux.ordenstk=ordenstk;
    strcpy(svdstkaux.codconce,codconce);
    strcpy(svdstkaux.codubi,codubi);
    svdstkaux.diff=diff;
    strcpy(svdstkaux.observ,observ);
    strcpy(svdstkaux.msjerror,msjerror);
    svdstkaux.codmov=codmov;
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdselregularizastk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocregularizastk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocdividetk(char *codmat,long ordenstk,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,double diff,char *observ,char *msjerror,double codmoventrada,double codmovsalida,long nuevoordenstk,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseldividetk==NULL) init_seldividetk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    svdstkaux.ordenstk=ordenstk;
    strcpy(svdstkaux.codconceentrada,codconceentrada);
    strcpy(svdstkaux.fuente,fuente);
    strcpy(svdstkaux.codconcesalida,codconcesalida);
    strcpy(svdstkaux.sumidero,sumidero);
    svdstkaux.diff=diff;
    strcpy(svdstkaux.observ,observ);
    strcpy(svdstkaux.msjerror,msjerror);
    svdstkaux.codmoventrada=codmoventrada;
    svdstkaux.codmovsalida=codmovsalida;
    svdstkaux.nuevoordenstk=nuevoordenstk;
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdseldividetk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocdividetk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXproccreastk(char *codmat,long ordenstk,char *codart,char *codlot,char *numeroserie,char *bulto,char *marcastk,char *codrecep,double uniemb,long embcont,char *tipoemba,double preciouni,double pesouni,char *bloqueos,double cantidad,char *codconceentrada,char *fuente,char *observ,char *msjerror,double codmoventrada,long fuerzastock,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselcreastk==NULL) init_selcreastk();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    svdstkaux.ordenstk=ordenstk;
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    strcpy(svdstkaux.numeroserie,numeroserie);
    strcpy(svdstkaux.bulto,bulto);
    strcpy(svdstkaux.marcastk,marcastk);
    strcpy(svdstkaux.codrecep,codrecep);
    svdstkaux.uniemb=uniemb;
    svdstkaux.embcont=embcont;
    strcpy(svdstkaux.tipoemba,tipoemba);
    svdstkaux.preciouni=preciouni;
    svdstkaux.pesouni=pesouni;
    strcpy(svdstkaux.bloqueos,bloqueos);
    svdstkaux.cantidad=cantidad;
    strcpy(svdstkaux.codconceentrada,codconceentrada);
    strcpy(svdstkaux.fuente,fuente);
    strcpy(svdstkaux.observ,observ);
    strcpy(svdstkaux.msjerror,msjerror);
    svdstkaux.codmoventrada=codmoventrada;
    svdstkaux.fuerzastock=fuerzastock;
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdselcreastk);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXproccreastk vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocbloqueosstkbulto(char *bulto,char *codart,char *codlot,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselbloqueosstkbulto==NULL) init_selbloqueosstkbulto();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.bulto,bulto);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    strcpy(svdstkaux.codconceentrada,codconceentrada);
    strcpy(svdstkaux.fuente,fuente);
    strcpy(svdstkaux.codconcesalida,codconcesalida);
    strcpy(svdstkaux.sumidero,sumidero);
    strcpy(svdstkaux.patronbloqueosori,patronbloqueosori);
    strcpy(svdstkaux.bloqueos,bloqueos);
    strcpy(svdstkaux.observ,observ);
    svdstkaux.cantidad=cantidad;
    strcpy(svdstkaux.comentario,comentario);
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdselbloqueosstkbulto);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocbloqueosstkbulto vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocbloqueosstkrecep(char *codrecep,char *codart,char *codlot,char *codconceentrada,char *fuente,char *codconcesalida,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselbloqueosstkrecep==NULL) init_selbloqueosstkrecep();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codrecep,codrecep);
    strcpy(svdstkaux.codart,codart);
    strcpy(svdstkaux.codlot,codlot);
    strcpy(svdstkaux.codconceentrada,codconceentrada);
    strcpy(svdstkaux.fuente,fuente);
    strcpy(svdstkaux.codconcesalida,codconcesalida);
    strcpy(svdstkaux.sumidero,sumidero);
    strcpy(svdstkaux.patronbloqueosori,patronbloqueosori);
    strcpy(svdstkaux.bloqueos,bloqueos);
    strcpy(svdstkaux.observ,observ);
    svdstkaux.cantidad=cantidad;
    strcpy(svdstkaux.comentario,comentario);
    svdstkaux.ret=ret;
    vdret=ejecutacursor(vdselbloqueosstkrecep);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocbloqueosstkrecep vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocactstkns(char *codmat,char *numeroserie,char *codopemodif,char *codrecurso,long codzona,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselactstkns==NULL) init_selactstkns();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    strcpy(svdstkaux.numeroserie,numeroserie);
    strcpy(svdstkaux.codopemodif,codopemodif);
    strcpy(svdstkaux.codrecurso,codrecurso);
    svdstkaux.codzona=codzona;
    vdret=ejecutacursor(vdselactstkns);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocactstkns vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocdelnumleidos(char *codmat,vdstkauxs *stkaux)
{
    int vdret;
    if (vdseldelnumleidos==NULL) init_seldelnumleidos();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    vdret=ejecutacursor(vdseldelnumleidos);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocdelnumleidos vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXproclimpiansstock(char *codmat,vdstkauxs *stkaux)
{
    int vdret;
    if (vdsellimpiansstock==NULL) init_sellimpiansstock();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    vdret=ejecutacursor(vdsellimpiansstock);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXproclimpiansstock vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

int STKAUXprocordenastockconns(char *codmat,long totalnsl,vdstkauxs *stkaux)
{
    int vdret;
    if (vdselordenastockconns==NULL) init_selordenastockconns();
    memset(&svdstkaux,0,sizeof(svdstkaux));
    strcpy(svdstkaux.codmat,codmat);
    svdstkaux.totalnsl=totalnsl;
    vdret=ejecutacursor(vdselordenastockconns);
    if(vdret) {
        v10log(LOGDEBUG,"Ejecuta STKAUXprocordenastockconns vdret %d. \n", vdret);
        return(VD_EERRORACLE);
    }
    *stkaux=svdstkaux;
    return(vdret);
}

char * STKAUXdebug(vdstkauxs *stkaux)
{
    debugestruct(&dstkaux,stkaux,msgdebugstkaux);
    return(msgdebugstkaux);
}


//Codigo incluido explicitamente en el DEF
 //Actualiza el stock origen y deja el movimiento preparado para que pase el actualizador de stock destino.
 VDEXPORT int STKAUXactstockori(void *ptr,int statusfinal) {
   int ret=0;
   vdmovims *mov=ptr;   
   vdstkauxs stock;
    
   ret=STKAUXprocactstockori(ret,mov->codmov, statusfinal, &stock);
   if (ret) {
     *mov->comen=0;   
   	strcpy(mov->comen,"STKactstockori: error ejecutando algoritmo PLSQL VDACTSTOCK.algactstkori\n");
     v10log(LOGERROR,"%s",mov->comen);
   	return(-1);
   }
   return(stock.ret);
 }  
 
 //Actualiza el stock en la ubicaci�n destino.
 VDEXPORT int STKAUXactstockdest(void *ptr,int statusfinal) {
    int ret=0;
    vdmovims *mov=ptr;   
    vdstkauxs stock;
    
    ret=STKAUXprocactstockdest(ret,mov->codmov, statusfinal, &stock);   
    if (ret) {
     *mov->comen=0;
     strcpy(mov->comen,"STKactstockori: error ejecutando algoritmo PLSQL VDACTSTOCK.algactstkdest\n");
   	v10log(LOGERROR,"%s",mov->comen);
   	return(-1);
    }
    return(stock.ret);
 }  
