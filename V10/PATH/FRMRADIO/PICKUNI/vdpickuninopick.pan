# M�dulo   : VDPICKUNINOPICK.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla de situacion sin picking pendiente.
#
# Creaci�n : 13-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______

	NO HAY PICKING
  PENDIENTE DEL
  BULTO 
_18_______________  

   PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIBUL.PAN"),"ERROR AL CARGAR \nFORMULARIO POR DEFECTO")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,VIRTUAL,NOENTER
CAMPO=PULSACION
