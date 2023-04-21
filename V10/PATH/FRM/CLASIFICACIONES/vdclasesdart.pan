# M�dulo   : VDCLASEART.PAN
# Funci�n  : Consulta de clases y clasificaciones de art�culos
#
# Creaci�n : 14-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
CLASES Y CLASIFICACIONES DE ARTICULOS
 Art�culo             Clasificaci�n    Clase           Descripci�n
 _40_________________ _15____________  _15____________ _40______________________________________ 
| 
TABLA=VDCLASEARTIC
ORDERBY=CODART,CODCLASIF,CODCLASE;



CAMPO=CODART,TOOLTIP("C�digo del art�culo clasificado"),TITULO("Art�culo")
CAMPO=CODCLASIF,NOUPDATE,TOOLTIP("Clasificaci�n a la que pertenece el art�culo"),TITULO("Clasificaci�n")
CAMPO=CODCLASE,TOOLTIP("Clase a la que pertenece el art�culo, dentro de la clasificaci�n"),POSTCHANGE=FEJECUTA("CSELDES","ERROR,\nNO EXISTE DESCRIPCION PARA ESTA CLASE"),TITULO("Clase")
CAMPO=DESCLASE,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la clase"),TITULO("Descripci�n")


CURSOR=CSELDES SELECT DESCLASE FROM VDCLASES WHERE  CODCLASE=:CODCLASE AND CODCLASIF=:CODCLASIF;


