# Módulo   : VDSELAREA.PAN
# Función  : Selección de areas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
Selección de area
Código       Designacion                    Almacen    Designación.
_20_________ _40___________________________ __________ _40__________________________________________
|

TABLA=VDAREA



CAMPO=CODAREA,TOOLTIP("Código del área")
CAMPO=DESAREA,TOOLTIP("Designación del área")
CAMPO=CODALM,TOOLTIP("Almacén"),POSTCHANGE=FDESIGNACION("CSELALM","No exsiste almacén")
CAMPO=DESALM,AUXILIAR,NOENTER,TOOLTIP("Designación del almacén")

CURSOR=CSELALM SELECT DESALM FROM VDALMA WHERE CODALM=:CODALM;



