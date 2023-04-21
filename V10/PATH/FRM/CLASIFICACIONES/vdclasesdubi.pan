# M�dulo   : VDCLASESDUBI.PAN
# Funci�n  : Clases y clasificaciones de ubicaciones
#
# Creaci�n : 15-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
CLASES Y CLASIFICACIONES DE UBICACIONES
 Ubicaci�n      Clasificaci�n    Clase           Descripci�n
 _20___________ _15____________  _15____________ _40______________________________________ 
|
TABLA=VDCLASEUBI
REGPAG=40



CAMPO=CODUBI,TOOLTIP("C�digo de la ubicaci�n clasificada"),TITULO("Ubicaci�n")
CAMPO=CODCLASIF,NOENTER,TOOLTIP("Clasificaci�n a la que pertenece la ubicaci�n"),TITULO("Clasificaci�n")
CAMPO=CODCLASE,NOENTER,TOOLTIP("Clase a la que pertenece la ubicaci�n, dentro de la clasificaci�n"),POSTCHANGE=FEJECUTA("CSELDES","ERROR,\nNO EXISTE DESCRIPCION PARA ESTA CLASE"),TITULO("Clase")
CAMPO=DESCLASE,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la clase"),TITULO("Descripci�n")



CURSOR=CSELDES SELECT DESCLASE FROM VDCLASES WHERE  CODCLASE=:CODCLASE AND CODCLASIF=:CODCLASIF;



