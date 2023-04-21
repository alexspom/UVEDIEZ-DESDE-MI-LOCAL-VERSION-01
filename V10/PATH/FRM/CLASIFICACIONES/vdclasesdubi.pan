# Módulo   : VDCLASESDUBI.PAN
# Función  : Clases y clasificaciones de ubicaciones
#
# Creación : 15-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
CLASES Y CLASIFICACIONES DE UBICACIONES
 Ubicación      Clasificación    Clase           Descripción
 _20___________ _15____________  _15____________ _40______________________________________ 
|
TABLA=VDCLASEUBI
REGPAG=40



CAMPO=CODUBI,TOOLTIP("Código de la ubicación clasificada"),TITULO("Ubicación")
CAMPO=CODCLASIF,NOENTER,TOOLTIP("Clasificación a la que pertenece la ubicación"),TITULO("Clasificación")
CAMPO=CODCLASE,NOENTER,TOOLTIP("Clase a la que pertenece la ubicación, dentro de la clasificación"),POSTCHANGE=FEJECUTA("CSELDES","ERROR,\nNO EXISTE DESCRIPCION PARA ESTA CLASE"),TITULO("Clase")
CAMPO=DESCLASE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la clase"),TITULO("Descripción")



CURSOR=CSELDES SELECT DESCLASE FROM VDCLASES WHERE  CODCLASE=:CODCLASE AND CODCLASIF=:CODCLASIF;



