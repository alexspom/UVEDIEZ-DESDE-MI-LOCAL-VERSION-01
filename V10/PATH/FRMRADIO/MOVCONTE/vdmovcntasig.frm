# MOdulo   : VDMOVCNTASIG.FRM
# Función  : Formulario de movimiento de palets completos asignados a recurso
#
# Creación : 19-05-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

#0 
BEGINBLOQUE=VDMOVCNTASIG.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDRECOGECNTORI.PAN
 PADRE=VDMOVCNTASIG.PAN
ENDBLOQUE
#2 
BEGINBLOQUE=VDDEPOSITACNTDEST.PAN
 PADRE=VDRECOGECNTORI.PAN
ENDBLOQUE
