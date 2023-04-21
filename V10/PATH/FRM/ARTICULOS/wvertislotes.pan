# Módulo   : VDLOTES.PAN
# Función  : Mantenimiento de lotes
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE LOTES
Artículo            Designación                               Lote               Caduci   
_40________________ _100_____________________________________ _40_______________ ________ 
|
TABLA=VDLOTES
NOUPDATE
NOINSERT
NODELETE
REGPAG=62
INCLUDEFICHEROCSS="vertissimple.css"
WLONX=700
WLONY=900

CAMPO=CODART,TOOLTIP("Código del artículo"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;",NOUPDATE,POSTCHANGE=FDESIGNACION("CSELDESART","No existe artículo"),TITULO("Artículo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designación del artículo")
CAMPO=CODLOT,POSTCHANGE=FVALNOCERO("Debe informar un lote"),NOUPDATE,TOOLTIP("Lote"),TITULO("Lote")
CAMPO=CADUCI,TOOLTIP("Caducidad en formato DDMMAAAA"),TITULO("Caducidad"),WLONX=50

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;
