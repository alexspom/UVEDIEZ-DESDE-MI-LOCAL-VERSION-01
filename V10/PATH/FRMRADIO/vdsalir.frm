# MOdulo   : VDRECEPCION.FRM
# Funci�n  : RECEPCION DE MERCANCIA
#
# Creaci�n : 30-01-2008
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
