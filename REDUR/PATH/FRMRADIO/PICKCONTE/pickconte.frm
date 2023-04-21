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
BEGINBLOQUE=PICKCONTE.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=PICKCONTE1.PAN
 PADRE=PICKCONTE.PAN
ENDBLOQUE
#2 
BEGINBLOQUE=PICKCONTE2.PAN
 PADRE=PICKCONTE1.PAN
ENDBLOQUE
#3 
BEGINBLOQUE=PICKCONTE3.PAN
 PADRE=PICKCONTE1.PAN
ENDBLOQUE
