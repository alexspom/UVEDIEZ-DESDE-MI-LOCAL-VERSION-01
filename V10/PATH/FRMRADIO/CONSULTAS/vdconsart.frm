# MOdulo   : VDCONSART.FRM
# Función  : Formulario de consulta de articulo
#
# Creación : 05-05-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

#0
BEGINBLOQUE=VDCONSART.PAN
ENDBLOQUE
#1
BEGINBLOQUE=VDCONSARTDET.PAN
    PADRE=VDCONSART.PAN
ENDBLOQUE

