# M�dulo   : VDPICKUNIDINAMICA9.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla de informaci�n de bulto sin picking pendiente.
#
# Creaci�n : 24-07-2008
# Autor    : JCSR
###########################################
# Hist�rico de cambios:
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

