# Módulo   : VDREUBICAPAROK.PAN
# Función  : Cambio de ubicación parcial de stock. 
#            Pantalla de confirmación del cambio.
#
# Creación : 08-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
# 
CAMBIOS DE UBICACION
_10_______ _10_______
REUBICACION PARCIAL DE STOCK

  REUBICACION PARCIAL 
  DE STOCK
  REALIZADO _
|


POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDREUBICAPAR.PAN"),"ERROR\n CARGANDO VDREUBICAPAR.PAN")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY