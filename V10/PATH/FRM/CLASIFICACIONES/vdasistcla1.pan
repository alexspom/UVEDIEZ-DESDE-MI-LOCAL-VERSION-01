######
# VDASISTCLA2.PAN - Seleción de Filtros para clasificar Artículos
#
# Propósito: Inroduccir los filtros de selección de artículos a clasificar
#
#
# Autor	   : FGS
# Fecha    : 14-07-2008
####
# Modificaciones:
####
CRITERIOS DE FILTRADO
Rangos de Divisiones: _100__________  Máscara COd: _100______________________   Rango Código: _100_______________________________

Mostrar solo Artículos sin clasificar en esta Clasificación: _

Mostrar solo Artículos clasificados en esta Clasificación en el rango de clases: _100____________________________________________

|

NOQUERY

CAMPO=RANGODIV,TOOLTIP("Rango de divisiones de los artículos a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=MASCARA,TOOLTIP("Máscara para LIKE del Código de Artículo. Si es NULO equivale a %")
CAMPO=RANGOCODART,TOOLTIP("Rango de Código de los artículos a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=SINCLASIFICAR,TOOLTIP("S: solo muestra artículos sin clasificar. Si es NULO no filtra")
CAMPO=RANGOCLASES,TOOLTIP("Rango de Clases de artículos a mostrar. Si es NULO no filtra")

TECLA=F4,FPULSATECLAS("F6","F3","F2")



