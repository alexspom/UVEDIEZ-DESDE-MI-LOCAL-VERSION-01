# MOdulo   : VDINVENTARIOS.FRM
# Función  : Monitor de conteos de inventario
#
# Creación : 03-02-2010
# Autor    : ICC
###########################################
# HistOrico de cambios:
#
BEGINBLOQUE=SMINVENTARIO1.PAN
  PREREGISTRO=PRESEHIJO
	REGPAG=10
  POSX=1
  POSY=1
ENDBLOQUE
BEGINBLOQUE=SMINVENTARIO2.PAN
  PADRE=SMINVENTARIO1.PAN
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
	REGPAG=31
  POSX=1
  POSY=15
ENDBLOQUE
