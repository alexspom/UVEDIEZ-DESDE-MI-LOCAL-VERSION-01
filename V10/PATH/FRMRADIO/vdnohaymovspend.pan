# M�dulo   : VDNOHAYMOVSPEND.PAN
# Funci�n  : Formulario de recogida de bultos de unidades con carro.
#            Pantalla para situacion en la que no hay movimientos pendientes.
#
# Creaci�n : 12-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______  

  NO HAY 
  MOVIMIENTOS 
  PENDIENTES
  
  PULSE ENTER _
|


POSTQUERY=FEJECUTA(FCARGAFORM(""),"ERRRO\n AL VOLVER AL MENU")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=DUMMY