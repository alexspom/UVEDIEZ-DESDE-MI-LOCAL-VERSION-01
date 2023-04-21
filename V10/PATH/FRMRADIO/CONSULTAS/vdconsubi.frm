# MOdulo   : VDCONSUBI.FRM
# Función  : Formulario de consulta de ubicaciones
#
# Creación : 05-05-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDCONSUBI.PAN"),"")
                    
#0 
BEGINBLOQUE=VDCONSUBI.PAN
ENDBLOQUE
BEGINBLOQUE=VDCONSUBI1.PAN
   PADRE=VDCONSUBI.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDCONSUBICNT.PAN
 PADRE=VDCONSUBI.PAN
ENDBLOQUE
