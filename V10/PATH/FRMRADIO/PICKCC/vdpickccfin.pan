# Módulo   : VDPICKCCNOFIN.PAN
# Función  : Formulario de recogida de bultos de caja completa.
#            Pantalla para fin de picking.
#
# Creación : 13-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
CAJAS COMPLETAS
  ______________ __________________ 

  
  FIN DE RECOGIDA
  LLEVE LAS CAJAS 
  A EXPEDICIONES
  
  
  PULSE CUALQUIER TECLA _
|


POSTQUERY=FEJECUTA(FCARGAFORM(""),"ERROR\n AL VOLVER AL MENU")


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY
