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
CAMPO=TEXTOTAREA,AUXILIAR,OCULTO,"______________"

#1
BEGINBLOQUE=VDASOCIAPICKINGTERM1.PAN
  CURSOR=CSELNAVE SELECT 'DINDES' TEXTOTAREA FROM DUAL;
ENDBLOQUE
#2
BEGINBLOQUE=VDASOCIAPICKINGTERM2.PAN
	PADRE=VDASOCIAPICKINGTERM1.PAN
ENDBLOQUE
#3
BEGINBLOQUE=VDASOCIAPICKINGTERM3.PAN
	PADRE=VDASOCIAPICKINGTERM2.PAN
ENDBLOQUE