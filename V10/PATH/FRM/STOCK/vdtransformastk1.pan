###################################################################
#M�dulo: VDTRANSFORMASTK1.PAN
#Funcionalidad :  Transformaciones de stock desde pantalla
#Autor: FGS      
#Fecha: 05-06-2008
###################################################################
# Hist�rico de cambios:
TRANSFORMACIONES DE LAS PROPIEDADES DE STOCK DESDE PANTALLAS
   Ubicaci�n: _20___________ _20_________   Matr�cula: __________________    Orden Stk: @@@@@@@@@ 
 ��������������������������������������  �� DATOS NUEVOS ������������������������� ENTRADA �� SALIDA ����                                  
 �                                    �  �                                                              �
 � Art�culo:     _40_________________ �  �  Art�culo:     _40_________________   __________ __________  �           
 �   Desc:       _100________________ �  �    Desc:       _100________________                          �
 �   Cantidad:   #L######### _10__    �  �                                                              �
 �   Reservado:  #L#########          �  �                                                              �
 � Lote:         _40_________________ �  �    Lote:       _40_________________   __________ __________  �
 �   Bloq:       _________            �  �     Bloq:      _________                                     �
 �   Caducidad:  _________            �  �     Caducidad: _________                                     �
 � N�m.Serie:    _60_______________   �  �    N�m. Serie: _60_______________     __________ __________  �
 � Bulto:        __________________   �  �    Bulto:      __________________     __________ __________  �
 � MarcaStock:   _60_______________   �  �    MarcaStock: _60_______________     __________ __________  �
 � Recepci�n:    ____________________ �  �    Recepci�n:  ____________________   __________ __________  �
 � UnixEmb:      #L15#.##             �  �    UnixEmb:    #L15#.##               __________             �
 � EmbxCont:     #L######             �  �    EmbxCont:   #L######               __________             �
 � Embalaje:     __________           �  �    Embalaje:   __________             __________             �
 �  Desc:        _40_________________ �  �     Desc:      _40_________________                          �
 � Precio                             �  �    Precio                                                    � 
 � Unitario:     #L12#####.###        �  �    Unitario:   #L12#####.###          __________             �   
 � Peso                               �  �    Peso                                                      �
 � Unitario:     #L######.### gr      �  �    Unitario:   #L######.###           __________ gr          �
 �                                    �  �                                                              �
 ��������������������������������������  ����������������������������������������������������������������
   Observ: 
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
   _1024______________________________________________________________________________________
|

TABLA=VDSTOCK

POSTQUERY=FEJECUTA("CSELDATOS","ERROR EN CSELDATOS",                   
                   "CCARGACONCEPTOSDEFECTO","ERROR EN CCARGACONCEPTOSDEFECTO",
                   "CCAMPOSTRANSFORMABLES","ERROR EN CCAMPOSTRANSFORMABLES")

PROTECT("ADMINISTRADOR")

CAMPO=CODUBI,AUXILIAR,NOENTER
CAMPO=CODAREA,AUXILIAR,NOENTER
CAMPO=CODMAT,NOENTER
CAMPO=ORDENSTK,NOENTER
# ARTICULO
CAMPO=CODART,NOENTER
CAMPO=CODARTNUEVO,AUXILIAR,PROTECT("CALIDAD"),POSTCHANGE=FEJECUTA("CSELDESART","ARTICULO :CODARTNUEVO NO EXISTE"),
                           TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='CODART'","ORDENCONCEPTOSART=:ORDEN CODCONCEENTART=:CODCONCEENT CODCONCESALART=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD CODART","S") 
CAMPO=ORDENCONCEPTOSART,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTART,AUXILIAR,NOENTER
CAMPO=CODCONCESALART,AUXILIAR,NOENTER
CAMPO=DESART,AUXILIAR,NOENTER
CAMPO=DESARTNUEVO,AUXILIAR,NOENTER
CAMPO=CANTIDAD,NOENTER,TOOLTIP("Cantidad en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER
CAMPO=RESERVADO,AUXILIAR,NOENTER
# LOTE
CAMPO=CODLOT,NOENTER
CAMPO=CODLOTNUEVO,PROTECT("CALIDAD"),AUXILIAR,POSTCHANGE=FEJECUTA("CSELLOTE","LOTE :CODLOTNUEVO NO EXISTE"),
                           CONTEXTUAL=FEJECUTAFORM("VDLOTES","N","CODART=:CODARTNUEVO","","CODLOTNUEVO=:CODLOT","SELECCION LOTES DEL ARTICULO :CODARTNUEVO","S"),
                           TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='CODLOT'","ORDENCONCEPTOSLOT=:ORDEN CODCONCEENTLOT=:CODCONCEENT CODCONCESALLOT=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD CODLOT","S") 
CAMPO=ORDENCONCEPTOSLOT,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTLOT,AUXILIAR,NOENTER
CAMPO=CODCONCESALLOT,AUXILIAR,NOENTER
CAMPO=BLOQLOTE,AUXILIAR,NOENTER
CAMPO=BLOQLOTENUEVO,AUXILIAR,NOENTER
CAMPO=CADUCI,AUXILIAR,NOENTER
CAMPO=CADUCINUEVO,AUXILIAR,NOENTER
# NUMERO DE SERIE
CAMPO=NUMEROSERIE,NOENTER
CAMPO=NUMEROSERIENUEVO,AUXILIAR,TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='NUMEROSERIE'","ORDENCONCEPTOSSERIE=:ORDEN CODCONCEENTSERIE=:CODCONCEENT CODCONCESALSERIE=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD NUMEROSERIE","S") 
CAMPO=ORDENCONCEPTOSSERIE,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTSERIE,AUXILIAR,NOENTER
CAMPO=CODCONCESALSERIE,AUXILIAR,NOENTER
# BULTO
CAMPO=BULTO,NOENTER
CAMPO=BULTONUEVO,AUXILIAR,TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='BULTO'","ORDENCONCEPTOSBULTO=:ORDEN CODCONCEENTBULTO=:CODCONCEENT CODCONCESALBULTO=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD BULTO","S") 
CAMPO=ORDENCONCEPTOSBULTO,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTBULTO,AUXILIAR,NOENTER
CAMPO=CODCONCESALBULTO,AUXILIAR,NOENTER
# MARCA DE STOCK
CAMPO=MARCASTK,NOENTER
CAMPO=MARCASTKNUEVO,AUXILIAR,TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='MARCASTK'","ORDENCONCEPTOSMARCA=:ORDEN CODCONCEENTMARCA=:CODCONCEENT CODCONCESALMARCA=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD MARCASTK","S") 
CAMPO=ORDENCONCEPTOSMARCA,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTMARCA,AUXILIAR,NOENTER
CAMPO=CODCONCESALMARCA,AUXILIAR,NOENTER
# C�digo DE RECEPCION
CAMPO=CODRECEP,NOENTER
CAMPO=CODRECEPNUEVO,AUXILIAR,POSTCHANGE=FEJECUTA("CVERIFCODRECEP1","RECEPCION :CODRECEPNUEVO NO EXISTE"),
                    TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='CODRECEP'","ORDENCONCEPTOSRECEP=:ORDEN CODCONCEENTRECEP=:CODCONCEENT CODCONCESALRECEP=:CODCONCESAL","SELECCION DE CONCEPTOS PARA PROPIEDAD CODRECEP","S") 
CAMPO=ORDENCONCEPTOSRECEP,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEENTRECEP,AUXILIAR,NOENTER
CAMPO=CODCONCESALRECEP,AUXILIAR,NOENTER
# UNIDADES POR EMBALAJE
CAMPO=UNIEMB,NOENTER,TOOLTIP("Unidades por embalaje en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=ORDENCONCEPTOSUNIEMB,AUXILIAR,OCULTO,"@L@"
CAMPO=UNIEMBNUEVO,AUXILIAR,POSTCHANGE=FVALNOCERO("Las unidades por embalaje no pueden ser 0"),
                           TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='UNIEMB'","ORDENCONCEPTOSUNIEMB=:ORDEN CODCONCEUNIEMB=:CODCONCEENT","SELECCION DE CONCEPTOS PARA PROPIEDAD UNIEMB","S") 
CAMPO=CODCONCEUNIEMB,AUXILIAR,NOENTER
# EMBALAJES POR CONTENEDOR
CAMPO=EMBCONT,NOENTER
CAMPO=ORDENCONCEPTOSEMBCONT,AUXILIAR,OCULTO,"@L@"
CAMPO=EMBCONTNUEVO,AUXILIAR,POSTCHANGE=FVALNOCERO("Los Embalajes por Contenedor no pueden ser 0"),
                            TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='EMBCONT'","ORDENCONCEPTOSEMBCONT=:ORDEN CODCONCEEMBCONT=:CODCONCEENT","SELECCION DE CONCEPTOS PARA PROPIEDAD EMBCONT","S") 
CAMPO=CODCONCEEMBCONT,AUXILIAR,NOENTER
# TIPO DE EMBALAJE
CAMPO=TIPOEMBA,NOENTER
CAMPO=TIPOEMBANUEVO,AUXILIAR,POSTCHANGE=FEJECUTA("CDESTIPOEMBA","TIPO DE EMBALAJE :TIPOEMBANUEVO NO EXISTE"),
                             CONTEXTUAL=FEJECUTAFORM("VDTIPOEMBA","N","","","TIPOEMBANUEVO=:TIPOEMBA","SELECCION DE TIPO DE EMBALAJE","S"),
                             TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='TIPOEMBA'","ORDENCONCEPTOSTIPOEMBA=:ORDEN CODCONCETIPOEMBA=:CODCONCEENT","SELECCION DE CONCEPTOS PARA PROPIEDAD TIPOEMBA","S") 
CAMPO=ORDENCONCEPTOSTIPOEMBA,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCETIPOEMBA,AUXILIAR,NOENTER
CAMPO=DESTIPOEMBA,AUXILIAR,NOENTER
CAMPO=DESTIPOEMBANUEVO,AUXILIAR,NOENTER
# PRECIO UNITARIO
CAMPO=PRECIOUNI,NOENTER,TOOLTIP("Precio unitario del producto en unidades host"),CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART")
CAMPO=PRECIOUNINUEVO,AUXILIAR,TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='PRECIOUNI'","ORDENCONCEPTOSPRECIOUNI=:ORDEN CODCONCEPRECIOUNI=:CODCONCEENT","SELECCION DE CONCEPTOS PARA PROPIEDAD PRECIOUNI","S") 
CAMPO=ORDENCONCEPTOSPRECIOUNI,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEPRECIOUNI,AUXILIAR,NOENTER
# PESO UNITARIO
CAMPO=PESOUNI,NOENTER,TOOLTIP("Peso unitario del producto en gramos"),CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART")
CAMPO=PESOUNINUEVO,AUXILIAR,TECLA=F9,FEJECUTAFORM("VDSELCONCEPTOFORM","N","","CODART=:CODART CAMPO='PESOUNI'","ORDENCONCEPTOSPESOUNI=:ORDEN CODCONCEPESOUNI=:CODCONCEENT","SELECCION DE CONCEPTOS PARA PROPIEDAD PESOUNI","S") 
CAMPO=ORDENCONCEPTOSPESOUNI,AUXILIAR,OCULTO,"@L@"
CAMPO=CODCONCEPESOUNI,AUXILIAR,NOENTER
# OBSERVACIONES
CAMPO=OBSERV1,AUXILIAR
CAMPO=OBSERV2,AUXILIAR
CAMPO=OBSERV3,AUXILIAR
CAMPO=OBSERV4,AUXILIAR
CAMPO=OBSERV,AUXILIAR,OCULTO,"_4096______"

CURSOR=CSELDATOS SELECT LOT.BLOQLOTE, LOT.CADUCI, UBI.CODUBI, UBI.CODAREA,ART.DESART, ART.UNIDADESHOST, EMB.DESTIPOEMBA,
                        VDART.VD2HOST(VDSTK.STKRESERVADO(:CODMAT,:ORDENSTK),:CODART) RESERVADO,
                        :CODART CODARTNUEVO,
                        :CODLOT CODLOTNUEVO,  
                        :NUMEROSERIE NUMEROSERIENUEVO,
                        :MARCASTK MARCASTKNUEVO,
                        :BULTO BULTONUEVO,
                        :CODRECEP CODRECEPNUEVO,
                        :UNIEMB UNIEMBNUEVO,
                        :EMBCONT EMBCONTNUEVO,
                        :PRECIOUNI PRECIOUNINUEVO,
                        :PESOUNI PESOUNINUEVO,
                        :TIPOEMBA TIPOEMBANUEVO
                   FROM VDLOTES LOT, VDARTIC ART, VDCONTE CNT, VDUBICA UBI, VDTIPOEMBA EMB
                     WHERE ART.CODART = :CODART AND
                           LOT.CODART = :CODART AND
                           LOT.CODLOT = :CODLOT AND
                           EMB.TIPOEMBA = :TIPOEMBA AND
                           CNT.CODMAT = :CODMAT AND
                           CNT.CODUBI = UBI.CODUBI;
                           
CURSOR=CCAMPOSTRANSFORMABLES 
                        SELECT  VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'CODART') CODARTNUEVO__ENTER, 
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'CODLOT')  CODLOTNUEVO__ENTER, 
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'NUMEROSERIE')  NUMEROSERIENUEVO__ENTER,                                        
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'BULTO')  BULTONUEVO__ENTER,                                        
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'MARCASTK')  MARCASTKNUEVO__ENTER,                                      
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'CODRECEP')  CODRECEPNUEVO__ENTER,                                      
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'UNIEMB')  UNIEMBNUEVO__ENTER,
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'EMBCONT')  EMBCONTNUEVO__ENTER,
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'TIPOEMBA')  TIPOEMBANUEVO__ENTER,
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'PRECIOUNI')  PRECIOUNINUEVO__ENTER,
                                VDSTK.CAMPOTRANSFORMABLE(:CODMAT, :ORDENSTK,'PESOUNI')  PESOUNINUEVO__ENTER
                     FROM DUAL; 
                     
CURSOR=CCARGACONCEPTOSDEFECTO DECLARE
                                  BEGIN                                 
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'CODART', :CODCONCEENTART, :CODCONCESALART,:ORDENCONCEPTOSART);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'CODLOT', :CODCONCEENTLOT, :CODCONCESALLOT,:ORDENCONCEPTOSLOT);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'NUMEROSERIE', :CODCONCEENTSERIE, :CODCONCESALSERIE,:ORDENCONCEPTOSSERIE);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'MARCASTK', :CODCONCEENTMARCA, :CODCONCESALMARCA,:ORDENCONCEPTOSMARCA);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'BULTO', :CODCONCEENTBULTO, :CODCONCESALBULTO,:ORDENCONCEPTOSBULTO);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'CODRECEP', :CODCONCEENTRECEP, :CODCONCESALRECEP,:ORDENCONCEPTOSRECEP);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'UNIEMB', :CODCONCEUNIEMB, :CODCONCEUNIEMB,:ORDENCONCEPTOSUNIEMB);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'EMBCONT', :CODCONCEEMBCONT, :CODCONCEEMBCONT, :ORDENCONCEPTOSEMBCONT);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'PRECIOUNI', :CODCONCEPRECIOUNI, :CODCONCEPRECIOUNI, :ORDENCONCEPTOSPRECIOUNI);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'PESOUNI', :CODCONCEPESOUNI, :CODCONCEPESOUNI, :ORDENCONCEPTOSPESOUNI);
                                   VDSTK.PREASIGNACONCEPTOCAMPO(:CODMAT, :ORDENSTK, 'TIPOEMBA', :CODCONCETIPOEMBA, :CODCONCETIPOEMBA, :ORDENCONCEPTOSTIPOEMBA);
                                  END;@                  

CURSOR=CDAMEOBSERV SELECT TRIM(:OBSERV1) || ' ' || TRIM(:OBSERV2) || ' ' || TRIM(:OBSERV3) || ' ' || TRIM(:OBSERV4) OBSERV FROM DUAL;

CURSOR=CSELDESART SELECT DESART DESARTNUEVO FROM VDARTIC WHERE CODART=:CODARTNUEVO;

CURSOR=CSELLOTE SELECT CADUCI CADUCINUEVO, BLOQLOTE BLOQLOTENUEVO FROM VDLOTES WHERE CODART=:CODARTNUEVO AND CODLOT=:CODLOTNUEVO;

CURSOR=CVERIFCODRECEP1 SELECT :CODRECEP FROM DUAL 
                        WHERE 
                           NVL(:CODRECEP,'-')=NVL(:CODRECEPNUEVO,'-') OR
                           EXISTS (SELECT 1 FROM VDRECEPCAB WHERE  CODRECEP=NVL(:CODRECEPNUEVO,'-'));
 

CURSOR=CDESTIPOEMBA SELECT DESTIPOEMBA DESTIPOEMBANUEVO FROM VDTIPOEMBA WHERE TIPOEMBA=:TIPOEMBANUEVO;

PRECOMMIT=FEJECUTA("CCHECKARTYLOTE","No existe art�culo Y LOTE INTRODUCIDO",
                   "!-CMOVTOSHUERFANOS","Hay movtos pdtes del stock transformado.\n � Desea Confirmar la Tranformaci�n ?",
                   "+CDAMEOBSERV","",
                   FTRANSFORMASTK(":CODMAT",":ORDENSTK",
                                  ":ORDENCONCEPTOSART",":CODARTNUEVO",
                                  ":ORDENCONCEPTOSLOT",":CODLOTNUEVO", 
                                  ":ORDENCONCEPTOSSERIE",":NUMEROSERIENUEVO",
                                  ":ORDENCONCEPTOSBULTO",":BULTONUEVO", 
                                  ":ORDENCONCEPTOSMARCA",":MARCASTKNUEVO",  
                                  ":ORDENCONCEPTOSRECEP",":CODRECEPNUEVO", 
                                  ":ORDENCONCEPTOSUNIEMB",":UNIEMBNUEVO",
                                  ":ORDENCONCEPTOSEMBCONT",":EMBCONTNUEVO",  
                                  ":ORDENCONCEPTOSTIPOEMBA",":TIPOEMBANUEVO", 
                                  ":ORDENCONCEPTOSPRECIOUNI",":PRECIOUNINUEVO", 
                                  ":ORDENCONCEPTOSPESOUNI",":PESOUNINUEVO", 
                                  ":OBSERV"),"\nERROR EN TRIGER FTRANSFORMASTK\n\n :V10ERROR",
                  FCOMMIT,"",
                  %FFAILURE,"TRANSFORMACION DE STOCK REALIZADA",
                  +FPULSATECLAS("F3","F2"),"")
                                  
                   
CURSOR=CCHECKARTYLOTE SELECT :CODART FROM VDLOTES WHERE CODART=:CODARTNUEVO AND CODLOT=:CODLOTNUEVO;

CURSOR=CMOVTOSHUERFANOS SELECT :RESERVADO FROM DUAL WHERE :RESERVADO>0;
BOTON=B1,695,415,32,32,"P",miok.png,F4,"Confirmar Transformaci�n",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,735,415,32,32,"P",minook.png,ESC,"Deshacer Transformaci�n",INCLUDECSS="background-color: transparent;border-width:0px"

# PUEDE DESEAR IMPRIMIR EN PAPEL LA REGULARIZACION ??
# EN REGULAR. DE STOCK, CHEQUEAR QUE LA DIFF. NO SUPERA LA MAXIMA, NI EL PRECIO MAXIMO QUE SE PUEDE REGULARIZAR, POR ESOS CONCEPTOS

