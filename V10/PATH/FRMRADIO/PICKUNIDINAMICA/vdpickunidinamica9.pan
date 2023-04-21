# Módulo   : VDPICKUNIDINAMICA9.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de información de bulto sin picking pendiente.
#
# Creación : 24-07-2008
# Autor    : JCSR
###########################################
# Histórico de cambios:
#
PICKING DINAMICA
_10_______ _10_______  

BULTO 
__________________
SIN PICKING
PENDIENTE 

PULSAR ENTER _
|

POSTQUERY=FEJECUTA(FCARGAFORM(""))


#DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=HAYTECLA,UPPER,AUXILIAR

