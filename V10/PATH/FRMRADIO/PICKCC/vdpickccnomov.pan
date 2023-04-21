# Módulo   : VDPICKCCNOMOV.PAN
# Función  : Formulario de recogida de bultos de caja completa.
#            Pantalla para situación de sin movimientos pendientes.
#
# Creación : 13-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
CAJAS COMPLETAS
_10_______ _10_______

  NO HAY 
  MOVIMIENTOS 
  PENDIENTES
  
  PULSE CUALQUIER TECLA _
|


POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("-1"),"ERROR\n AL VOLVER AL MENU")


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY