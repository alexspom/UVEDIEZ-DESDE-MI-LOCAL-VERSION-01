######
# VDASISTUBI1.PAN - Seleción de Filtros para clasificar Ubicaciones
#
# Propósito: Inroduccir los filtros de selección de ubicaciones a clasificar
#
#
# Autor	   : FGS
# Fecha    : 14-07-2008
####
# Modificaciones:
####
CRITERIOS DE FILTRADO
Rangos de Areas: _100__________  Máscara COd: _100______________________   Rango Código: _100_______________________________

Mostrar solo Ubicaciones sin clasificar en esta Clasificación: _

Mostrar solo Ubicaciones clasificados en esta Clasificación en el rango de clases: _100______________________________________

|

NOQUERY

CAMPO=RANGOAREAS,TOOLTIP("Rango de áreas de las ubicaciones a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=MASCARA,TOOLTIP("Máscara para LIKE del Código de Ubicación. Si es NULO equivale a %")
CAMPO=RANGOCODUBI,TOOLTIP("Rango de Código de las ubicaciones a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=SINCLASIFICAR,TOOLTIP("S: solo muestra ubicaciones sin clasificar. Si es NULO no filtra")
CAMPO=RANGOCLASES,TOOLTIP("Rango de Clases de ubicaciones a mostrar. Si es NULO no filtra")
CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO

TECLA=F4,FPULSATECLAS("F6","F3","F2")



