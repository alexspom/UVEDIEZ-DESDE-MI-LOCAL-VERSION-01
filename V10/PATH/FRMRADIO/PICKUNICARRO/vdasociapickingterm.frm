# MOdulo   : VDASOCIAPICKINGTERM.FRM
# Función  : Formulario de asociación de bultos a terminal por radio
#
# Creación : 12-05-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"________________"

#0
BEGINBLOQUE=VDASOCIAPICKINGTERM0.PAN
ENDBLOQUE
#1
BEGINBLOQUE=VDASOCIAPICKINGTERM1.PAN
    PADRE=VDASOCIAPICKINGTERM0.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDASOCIAPICKINGTERM2.PAN
	PADRE=VDASOCIAPICKINGTERM1.PAN
ENDBLOQUE
#3
BEGINBLOQUE=VDASOCIAPICKINGTERM3.PAN
	PADRE=VDASOCIAPICKINGTERM2.PAN
ENDBLOQUE