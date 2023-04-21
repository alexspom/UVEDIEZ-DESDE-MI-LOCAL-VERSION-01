# MOdulo   : VDRECEPCION.FRM
# Función  : RECEPCION DE MERCANCIA
#
# Creación : 30-01-2008
# Autor    : ICC
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"_10_________"
CAMPO=CODRECURSO,OCULTO,"_10_________"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDSALIR.PAN"),"")
#0 
BEGINBLOQUE=VDSALIR.PAN
ENDBLOQUE
