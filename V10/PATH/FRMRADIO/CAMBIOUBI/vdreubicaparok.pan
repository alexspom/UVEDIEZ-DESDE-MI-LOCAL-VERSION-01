# M�dulo   : VDREUBICAPAROK.PAN
# Funci�n  : Cambio de ubicaci�n parcial de stock. 
#            Pantalla de confirmaci�n del cambio.
#
# Creaci�n : 08-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
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