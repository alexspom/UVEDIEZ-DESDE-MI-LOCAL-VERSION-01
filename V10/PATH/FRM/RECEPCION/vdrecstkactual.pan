#*****************************************************************
#Módulo: VDRECSTKORI.PAN
#Funcionalidad : 
#Autor: ICC      
#Fecha: 12-02-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
STOCK ACTUAL DE LA RECEPCION
Matrícula          Artículo          Lote              Cantidad          
_18_______________ _40______________ _40______________ ############       
|
SOLOQUERY
SELECT=SELECT CODMAT, CODART, CODLOT, SUM(CANTIDAD) CANTIDAD
         FROM VDSTOCK;
GROUPBY=CODMAT, CODART, CODLOT, BLOQUEOS;


CAMPO=CODRECEP,VIRTUAL,OCULTO
CAMPO=CODMAT,TOOLTIP("Número de recepción dentro de la misma orden de recepción"),TITULO("Matrícula")
CAMPO=CODART,TOOLTIP("Código de artículo"),TITULO("Artículo")
CAMPO=CODLOT,TOOLTIP("Código del Lote"),TITULO("Lote")
CAMPO=CANTIDAD,TOOLTIP("Cantidad recepcionada"),TITULO("Cantidad")



CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMAT")

