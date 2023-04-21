# Módulo   : VDCLASEART.PAN
# Función  : Consulta de clases y clasificaciones de artículos
#
# Creación : 14-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
CLASES Y CLASIFICACIONES DE ARTICULOS
 Artículo             Clasificación    Clase           Descripción
 _40_________________ _15____________  _15____________ _40______________________________________ 
| 
TABLA=VDCLASEARTIC
ORDERBY=CODART,CODCLASIF,CODCLASE;



CAMPO=CODART,TOOLTIP("Código del artículo clasificado"),TITULO("Artículo")
CAMPO=CODCLASIF,NOUPDATE,TOOLTIP("Clasificación a la que pertenece el artículo"),TITULO("Clasificación")
CAMPO=CODCLASE,TOOLTIP("Clase a la que pertenece el artículo, dentro de la clasificación"),POSTCHANGE=FEJECUTA("CSELDES","ERROR,\nNO EXISTE DESCRIPCION PARA ESTA CLASE"),TITULO("Clase")
CAMPO=DESCLASE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la clase"),TITULO("Descripción")


CURSOR=CSELDES SELECT DESCLASE FROM VDCLASES WHERE  CODCLASE=:CODCLASE AND CODCLASIF=:CODCLASIF;


