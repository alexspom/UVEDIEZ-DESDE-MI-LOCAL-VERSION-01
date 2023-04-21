# MOdulo   : VDCONSCNT.FRM
# Función  : Formulario de consulta de contenedor
#
# Creación : 30-04-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODRECURSO,OCULTO,"__________"
CAMPO=CODOPE,OCULTO,"__________"
PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDCONSCNT.PAN"),"")
                    
#0 
BEGINBLOQUE=VDCONSCNT.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDCONSCNTSTK.PAN
 PADRE=VDCONSCNT.PAN
ENDBLOQUE
