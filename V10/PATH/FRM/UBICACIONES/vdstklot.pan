# Módulo   : VDSTKLOT.PAN
# Función  : Selección de Lotes del Articulo a consultar stock
#
# Creación : 01-04-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
SELECCION DE ARTICULO Y LOTE
Codart             Lote                                            BloqLote   Caducidad
_40_______________ _40_________ _100______________________________ __________ ________
                                                                                         |

TABLA=VDLOTES
WHERE=(CODART,CODLOT) IN (SELECT CODART,CODLOT FROM VDSTOCK);
ORDERBY=CODART,CADUCI,CODLOT;


CAMPO=CODART,TOOLTIP("Código del artículo"),POSTCHANGE=FEJECUTA("+CDESART",""),
                                            CONTEXTUAL=FEJECUTAFORM("VDSELART","N","","","CODART=:CODART","SELECCION DE ARTICULOS","S"),TITULO("Artículo")
CAMPO=CODLOT,TOOLTIP("Lote del Artículo"),CONTEXTUAL=FEJECUTA(FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT","SELECCION DE LOTES DEL ARTICULO :CODART","S"),"",
                                                     FPULSATECLAS("F2")) ,TITULO("Lote")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designación del artículo"),TITULO("Des.Artículo")
CAMPO=BLOQLOTE,TOOLTIP("Bloqueo del Lote"),TITULO("Bloq.Lote")
CAMPO=CADUCI,TOOLTIP("Caducidad del Lote"),TITULO("Caducidad"),WLONX=16

CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

#IMPRIME MATRICULA CON ARTICULO (SE LE LLAMA DESDE EL MENU VDCONTE.ZOO)				 
CURSOR=CIMPREETIQ DECLARE
                  FICHERO VARCHAR2(100);
                  MIUNIEMB NUMBER;
                  MICODIMPRE VARCHAR2(100);
                  MINUMALBA VARCHAR2(20);
                  MICODLOT VARCHAR2(20);
                  MICODART VARCHAR2(20);
                BEGIN
                  SELECT ART.CODART, LOT.CODLOT, ART.UNIEMB  INTO MICODART, MICODLOT, MIUNIEMB FROM VDARTIC ART, VDLOTES LOT WHERE ART.CODART = LOT.CODART AND ART.CODART=:CODART AND LOT.CODLOT=:CODLOT;
                  FICHERO:='VDPRODUCTO.GEN;VDETIART.VSQ;CSELNUEART';
                  VDIMPRIME.IMPRIME('ETIQ',FICHERO,'CODART='||MICODART||';CODLOT='||MICODLOT||';UNIEMB='||MIUNIEMB||';ESCOPIA=''S''',1,MICODIMPRE,'',:V10ERROR);    
                  COMMIT;
                END;@
CURSOR=CHECKERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL; 

TECLA=SF9,FEJECUTAFORM("VDSTKCALIFLOT.FRM","N","ART.CODART=:CODART AND LOT.CODLOT=:CODLOT","","","DESGLOSE DE STOCK POR CALIFICACION DE ARTICULO :CODART","S")                        
 

