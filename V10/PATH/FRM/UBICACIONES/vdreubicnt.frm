# MOdulo   : VDREUBICNT.FRM
# Función  : Reubica palets compeltos
#
# Creación : 14-07-2008
# Autor    : ICC
###########################################
# HistOrico de cambios:
#
BEGINBLOQUE=VDREUBICARCNT.PAN
  PREREGISTRO=PRESEHIJO
  REGPAG=15
ENDBLOQUE
BEGINBLOQUE=VDSTOCK.PAN
  PREQUERY=QUERYHIJO
  PADRE=VDREUBICARCNT.PAN
  POSY=21
  REGPAG=20
ENDBLOQUE  