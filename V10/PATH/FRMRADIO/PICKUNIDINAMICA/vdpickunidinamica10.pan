# M�dulo   : VDPICKUNIDINAMICA10.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla de informaci�n de bulto pendiente de stock
#
# Creaci�n : 19-08-2008
# Autor    : FPD
###########################################
# Hist�rico de cambios:
#
PICKING DINAMICA
_10_______ _10_______  

BULTO 
__________________
PENDIENTE DE STOCK
  
PULSE ENTER _
|

POSTQUERY=FEJECUTA(FCARGAFORM(""))


#DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=HAYTECLA,UPPER

