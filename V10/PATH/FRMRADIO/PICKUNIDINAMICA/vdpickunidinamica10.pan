# Módulo   : VDPICKUNIDINAMICA10.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de información de bulto pendiente de stock
#
# Creación : 19-08-2008
# Autor    : FPD
###########################################
# Histórico de cambios:
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

