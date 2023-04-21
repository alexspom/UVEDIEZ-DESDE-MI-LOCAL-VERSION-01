# Módulo   : VDSTKLOT.PAN
# Función  : Selección de Lotes del Articulo a consultar stock
#
# Creación : 01-04-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
DESGLOSE DE STOCK DE ARTICULO Y LOTE POR CALIFICACION DE STOCK
Codart       Lote                                       Caduc.   Calific.   Cantidad       
_40_________ _40_________ _100_________________________ ________ __________ #15######.### _10__
|                                                                                   
 
SOLOQUERY
TABLA=LOT
SELECT=SELECT CODART, CODLOT, CADUCI, DESART, BLOQUEOS, UNIDADESHOST, CANTIDAD
          FROM (SELECT LOT.CODART,LOT.CODLOT,LOT.CADUCI,ART.DESART,STK.BLOQUEOS,ART.UNIDADESHOST,VDART.VD2HOST(SUM(CANTIDAD),LOT.CODART) CANTIDAD,STK.MARCASTK
               FROM VDARTIC ART, VDLOTES LOT, VDSTOCK STK 
               WHERE ART.CODART=LOT.CODART AND
                     LOT.CODART = STK.CODART AND
                     LOT.CODLOT = STK.CODLOT
              GROUP BY LOT.CODART, LOT.CODLOT, LOT.CADUCI, ART.DESART, ART.UNIDADESHOST, STK.BLOQUEOS,STK.MARCASTK) LOT
              WHERE 1=1;
ORDERBY=CODART, CODLOT, BLOQUEOS;
                     
#TABLA=VDLOTES


CAMPO=CODART,TOOLTIP("Código del artículo"),TITULO("Artículo")
CAMPO=CODLOT,TOOLTIP("Lote del Artículo"),TITULO("Lote")
CAMPO=DESART,NOENTER,AUXILIAR,TOOLTIP("Designación del artículo"),TITULO("Desart")
CAMPO=CADUCI,TOOLTIP("Caducidad del lote"),TITULO("Caduc")
CAMPO=BLOQUEOS,NOENTER,TITULO("Bloqueos")
CAMPO=CANTIDAD,TOOLTIP("Cantidad del Lote de este Calificación"),TITULO("Cantidad")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades Host del Artículo")



