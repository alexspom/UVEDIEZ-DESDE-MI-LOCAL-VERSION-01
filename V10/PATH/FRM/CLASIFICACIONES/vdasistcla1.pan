######
# VDASISTCLA2.PAN - Seleci�n de Filtros para clasificar Art�culos
#
# Prop�sito: Inroduccir los filtros de selecci�n de art�culos a clasificar
#
#
# Autor	   : FGS
# Fecha    : 14-07-2008
####
# Modificaciones:
####
CRITERIOS DE FILTRADO
Rangos de Divisiones: _100__________  M�scara COd: _100______________________   Rango C�digo: _100_______________________________

Mostrar solo Art�culos sin clasificar en esta Clasificaci�n: _

Mostrar solo Art�culos clasificados en esta Clasificaci�n en el rango de clases: _100____________________________________________

|

NOQUERY

CAMPO=RANGODIV,TOOLTIP("Rango de divisiones de los art�culos a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=MASCARA,TOOLTIP("M�scara para LIKE del C�digo de Art�culo. Si es NULO equivale a %")
CAMPO=RANGOCODART,TOOLTIP("Rango de C�digo de los art�culos a clasificar. Lista separada por , o rango entre -. Si es NULO no filtra")
CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=SINCLASIFICAR,TOOLTIP("S: solo muestra art�culos sin clasificar. Si es NULO no filtra")
CAMPO=RANGOCLASES,TOOLTIP("Rango de Clases de art�culos a mostrar. Si es NULO no filtra")

TECLA=F4,FPULSATECLAS("F6","F3","F2")



