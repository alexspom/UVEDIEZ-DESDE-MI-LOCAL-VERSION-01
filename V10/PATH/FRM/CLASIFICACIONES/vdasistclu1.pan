######
# VDASISTUBI1.PAN - Seleci�n de Filtros para clasificar Ubicaciones
#
# Prop�sito: Inroduccir los filtros de selecci�n de ubicaciones a clasificar
#
#
# Autor	   : FGS
# Fecha    : 14-07-2008
####
# Modificaciones:
####
CRITERIOS DE FILTRADO
Rangos de Areas: _100__________  M�scara COd: _100______________________   Rango C�digo: _100_______________________________

Mostrar solo Ubicaciones sin clasificar en esta Clasificaci�n: _

Mostrar solo Ubicaciones clasificados en esta Clasificaci�n en el rango de clases: _100______________________________________

|

NOQUERY

CAMPO=RANGOAREAS,TOOLTIP("Rango de �reas de las ubicaciones a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=MASCARA,TOOLTIP("M�scara para LIKE del C�digo de Ubicaci�n. Si es NULO equivale a %")
CAMPO=RANGOCODUBI,TOOLTIP("Rango de C�digo de las ubicaciones a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=SINCLASIFICAR,TOOLTIP("S: solo muestra ubicaciones sin clasificar. Si es NULO no filtra")
CAMPO=RANGOCLASES,TOOLTIP("Rango de Clases de ubicaciones a mostrar. Si es NULO no filtra")
CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO

TECLA=F4,FPULSATECLAS("F6","F3","F2")



