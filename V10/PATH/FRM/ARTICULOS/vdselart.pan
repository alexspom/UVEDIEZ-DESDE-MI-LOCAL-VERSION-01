# Módulo   : VDSELART.PAN
# Función  : Selección de artículos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
Selección de artículo
Código            Designacion           Nacional      Ean            Div.   Designacion           Código para div.
_40______________ _100_________________ _____________ ______________ _20___ _40__________________ _20______________
|

TABLA=VDARTIC



CAMPO=CODART,TOOLTIP("Código del artículo"),TITULO("Referencia")
CAMPO=DESART,TOOLTIP("Designación del artículo"),TITULO("Artículo")
CAMPO=CODNAC,TOOLTIP("Código nacional"),TITULO("Código Nac.")
CAMPO=CODEAN,TOOLTIP("Código EAN"),TITULO("EAN")
CAMPO=CODDIV,TOOLTIP("División"),POSTCHANGE=FDESIGNACION("CSELDIVIS","No exsiste división"),TITULO("División")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Designación de la división"),TITULO("Des. División")
CAMPO=CODARTDIV,TOOLTIP("Código del artículo para la división"), TITULO("Artículo-División")

CURSOR=CSELDIVIS SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;



