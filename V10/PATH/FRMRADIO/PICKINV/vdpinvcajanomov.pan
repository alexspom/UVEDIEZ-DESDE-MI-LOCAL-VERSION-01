# Módulo   : VDPINVCAJANOMOV.PAN
# Función  : Formulario de recogida de cajas para pickig inverso.
#
# Creación : 19-09-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
#
CAJAS COMPLETAS PARA PICKING INVERSO
_10_______ _10_______
CAJAS PARA PICKING INVERSO

  NO HAY 
  MOVIMIENTOS 
  PENDIENTES
  
  PULSE CUALQUIER TECLA _
|


POSTQUERY=FEJECUTA(FCARGAFORM(""),"ERROR\n AL VOLVER AL MENU")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY