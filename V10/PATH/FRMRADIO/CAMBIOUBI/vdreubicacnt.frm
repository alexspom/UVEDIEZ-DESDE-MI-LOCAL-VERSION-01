# MOdulo   : VDREUBICACNT.FRM
# Función  : Formulario de cambio de ubicación de contenedor
#
# Creación : 06-05-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDREUBICACNT.PAN"),"")
                    
#0 
BEGINBLOQUE=VDREUBICACNT.PAN
ENDBLOQUE
