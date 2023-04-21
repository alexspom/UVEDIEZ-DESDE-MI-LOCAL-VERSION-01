###################################################################
#Módulo: VDREGULARIZASTK.PAN
#Funcionalidad :  Pantalla de Regularizaciones de cantidades de Stock
#Autor: FGS      
#Fecha: 18-06-2008
###################################################################
# Histórico de cambios:
DIVISION DE LINEAS DE STOCK DESDE PANTALLAS

   Ubicación: _20___________ _20_________   
   Matrícula: __________________    
   Orden Stk: @@@@@@@@@ 
                                                                              
   Artículo:  _40_________________  _100______________________________________
   
   Lote:      _40_________________  BloqLote: _________  Caducidad:  _________            
   
   Bloqueos:  __________  
   
   UnixEmb:   #L15#.##      EmbxCont:  #L###### 
   
   
   Cantidad:   #L######### _10__    
   Reservado:  #L#########          
   
   Cantidad a Dividir: #L######.###   
   
   Conceptos: __________  __________
      
   Observ: 
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
|

TABLA=VDSTOCK

POSTQUERY=FEJECUTA("CSELDATOS","ERROR EN CSELDATOS","+CCARGACONCEPTOSDEFECTO","")

CAMPO=CODUBI,AUXILIAR,NOENTER
CAMPO=CODAREA,AUXILIAR,NOENTER
CAMPO=CODMAT,NOENTER
CAMPO=ORDENSTK,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART,AUXILIAR,NOENTER
CAMPO=CODLOT,NOENTER
CAMPO=BLOQLOTE,AUXILIAR,NOENTER
CAMPO=CADUCI,AUXILIAR,NOENTER
CAMPO=BLOQUEOS,NOENTER
CAMPO=UNIEMB,NOENTER,TOOLTIP("Unidades por embalaje en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=EMBCONT,NOENTER
CAMPO=CANTIDAD,NOENTER,TOOLTIP("Cantidad en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER
CAMPO=RESERVADO,AUXILIAR,NOENTER
CAMPO=CANTAMOVER,PROTECT("ADMINISTRADOR"),AUXILIAR,TOOLTIP("Cantidad a Regularizar"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=ORDENCONCEPTOFORM,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENT,AUXILIAR,NOENTER
CAMPO=CODCONCESAL,AUXILIAR,NOENTER 
CAMPO=NUEVOORDENSTK,AUXILIAR,OCULTO,"@L@@@"
# OBSERVACIONES
CAMPO=OBSERV1,AUXILIAR
CAMPO=OBSERV2,AUXILIAR
CAMPO=OBSERV3,AUXILIAR
CAMPO=OBSERV4,AUXILIAR
CAMPO=OBSERV,AUXILIAR,OCULTO,"_4096______"


CURSOR=CSELDATOS SELECT LOT.BLOQLOTE, LOT.CADUCI, UBI.CODUBI, UBI.CODAREA,ART.DESART, ART.UNIDADESHOST,
                        VDART.VD2HOST(VDSTK.STKRESERVADO(:CODMAT,:ORDENSTK),:CODART) RESERVADO,
                        VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'DIVIDIR') CANTAMOVER__ENTER 
                   FROM VDLOTES LOT, VDARTIC ART, VDCONTE CNT, VDUBICA UBI
                     WHERE ART.CODART = :CODART AND
                           LOT.CODART = :CODART AND
                           LOT.CODLOT = :CODLOT AND
                           CNT.CODMAT = :CODMAT AND
                           CNT.CODUBI = UBI.CODUBI;

CURSOR=CCARGACONCEPTOSDEFECTO DECLARE
                                  BEGIN                                 
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'DIVIDIR', :CODCONCEENT, :CODCONCESAL,:ORDENCONCEPTOFORM);
                              END;@   
         
CURSOR=CMOVTOSHUERFANOS SELECT :RESERVADO FROM DUAL WHERE :RESERVADO>0;

CURSOR=CDAMEOBSERV SELECT TRIM(:OBSERV1) || ' ' || TRIM(:OBSERV2) || ' ' || TRIM(:OBSERV3) || ' ' || TRIM(:OBSERV4) OBSERV FROM DUAL;

CURSOR=CCANTNEGATIVO SELECT :CANTAMOVER FROM DUAL WHERE :CANTAMOVER > 0;

CURSOR=CCODCONCENULO SELECT :CODCONCE FROM DUAL WHERE :CODCONCE IS NULL;

CURSOR=CSUPERACANTMAX SELECT :CANTMAX FROM DUAL WHERE :CANTMAX>0 AND ABS(:DIFF)>:CANTMAX;

CURSOR=CSUPERAPVLMAX SELECT (ART.PVPVIGENTE*ABS(:DIFF)) PVPDIFF FROM VDARTIC ART WHERE :PVPMAX>0 AND CODART=:CODART AND (ART.PVPVIGENTE*ABS(:DIFF)) > :PVPMAX;

CURSOR=CBULTO SELECT :ORDENSTK FROM VDSTOCK WHERE CODMAT=:CODMAT AND ORDENSTK=:ORDENSTK AND BULTO IS NOT NULL;

CURSOR=CNUMEROSERIE SELECT :ORDENSTK FROM VDSTOCK WHERE CODMAT=:CODMAT AND ORDENSTK=:ORDENSTK AND NUMEROSERIE IS NOT NULL;


PRECOMMIT=FEJECUTA("-CBULTO","NO SE PUEDE DIVIDIR STOCK CON Código DE BULTO",
                   "-CNUMEROSERIE","NO SE PUEDE DIVIDIR STOCK CON NUMERO DE SERIE",
                   "!-CMOVTOSHUERFANOS","Hay movtos pdtes del stock transformado.\n ¿ Desea Confirmar la Tranformación ?",
                   "+CDAMEOBSERV","",
                   "CCANTNEGATIVO","LA CANTIDAD A DIVIDIR NO PUEDE SER MENOR O IGUAL A 0",
                   FDIVIDESTK (":CODMAT",":ORDENSTK",":ORDENCONCEPTOFORM",":CANTAMOVER",":OBSERV","NUEVOORDENSTK"),"\n ERROR EN TRIGER FDIVIDESTK\n\n :V10ERROR",                  
                   FCOMMIT,"",
                   %FFAILURE,"DIVISION REALIZADA. CREADA LINEA DE STOCK :NUEVOORDENSTK",
                   +FPULSATECLAS("ESC","F3","F2"),"")
                                  
BOTON=B1,385,265,32,32,"P",miok.png,F4,"Confirmar ",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,425,265,32,32,"P",minook.png,ESC,"Deshacer ",INCLUDECSS="background-color: transparent;border-width:0px"


TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='DIVIDIR'","ORDENCONCEPTOFORM=:ORDEN CODCONCEENT=:CODCONCEENT CODCONCESAL=:CODCONCESAL","SELECCION DE CONCEPTOS PARA DIVISIONES DE LINEAS DE STOCK","S")                           

