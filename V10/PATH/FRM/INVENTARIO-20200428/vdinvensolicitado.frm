# MOdulo   : FINALIZAORDEREC.FRM
# Función  : Finaliza Ordenes de recepción o líneas de Ordenes de recepción
#
# Creación : 13-02-2007
# Autor    : ICC
###########################################
# HistOrico de cambios:
#
BEGINBLOQUE=VDINVENCAB.PAN
  PREREGISTRO=PRESEHIJO
  POSX=1
  POSY=1
ENDBLOQUE
BEGINBLOQUE=VDINVENLIN.PAN
  PADRE=VDINVENCAB.PAN
	PREQUERY=QUERYHIJO
	PREREGISTRO=PRESEHIJO
	REGPAG=25
  POSX=1
  POSY=24
ENDBLOQUE
