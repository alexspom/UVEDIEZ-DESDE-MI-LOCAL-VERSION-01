# Módulo   : VDREUBICAPAROKPU.PAN
# Función  : Cambio de ubicación parcial de stock. 
#            Pantalla de confirmación del cambio.
#
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


POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDREUBICAPARPU.PAN"),"ERROR\n CARGANDO VDREUBICAPARPU.PAN")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY