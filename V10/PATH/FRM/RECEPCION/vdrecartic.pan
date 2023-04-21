#*****************************************************************
#Módulo: VDRECARTIC.PAN
#Función : muestra los artículos recepcionados
#Autor: ICC      
#Fecha: 12-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
ARTICULOS RECEPCIONADOS

 Artículo                                           Lote                 Caducidad Cantidad recep.   Cant.regularizada Cantidad final
 _40___________ _100_______________________________ _40_________________ ________  ################# ################# #################
|

SOLOQUERY
SELECT=SELECT CODART, CODLOT, CADUCI, SUM(CANTIDADR) CANTIDADR
         FROM VDRECEPLIN;
GROUPBY= CODART, CODLOT, CADUCI;
ORDERBY=CODART;

POSTQUERY=FDESIGNACION("+CCALCULAREG","Error calculando regularizaciónes",
                       "CTOTAL","Error calculando total")


CAMPO=CODORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=TIPORDREC,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODDIV,VIRTUAL,AUXILIAR,OCULTO

CAMPO=CODRECEP,VIRTUAL,OCULTO,TOOLTIP("Número de recepción dentro de la misma orden de recepción")
CAMPO=CODART,TOOLTIP("Código de artículo"),POSTCHANGE=FEJECUTA("CDESART","ERROR CONSULTANDO LA DESCRIPCION DEL ARTICULO"),TITULO("Artículo")
CAMPO=DESART,TOOLTIP("Descripción del artículo")
CAMPO=CODLOT,TOOLTIP("Lote")
CAMPO=CADUCI,TOOLTIP("Caducidad")
CAMPO=CANTIDADR,TOOLTIP("Cantidad recibida en esta recepción, incluidas las muestras si las hubiese"),TITULO("Cantidad")
CAMPO=CANTIDADREG,AUXILIAR,NOENTER,TOOLTIP("Cantidad regularizada"),TITULO("Cant. regularizada")
CAMPO=CANTIDADFIN,AUXILIAR,NOENTER,TOOLTIP("Cantidad tras regularizazción"),TITULO("Cant. final")


CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART = :CODART;

CURSOR=CCALCULAREG SELECT SUM(DECODE(MOV.CODCONCE,'REGENT+',MOV.CANTIDAD,MOV.CANTIDAD*-1)) CANTIDADREG
                      FROM VDMOVIM MOV
                    WHERE MOV.CODCONCE IN ('REGENT+','REGENT-')
                    AND MOV.CODRECEP = :CODRECEP
                    AND MOV.CODART = :CODART AND MOV.CODLOT=:CODLOT
                    AND STATUS BETWEEN 0 AND 7000;

CURSOR=CTOTAL SELECT :CANTIDADR + :CANTIDADREG CANTIDADFIN FROM DUAL;

CONTEXTUAL=FEJECUTAFORM("VDARTIC","S","CODART=:CODART")