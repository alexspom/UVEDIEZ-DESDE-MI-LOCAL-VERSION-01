# Módulo   : VDCOMPVISUAL.FRM
# Función  : COMPROBACION VISUAL DE LA MERCANCIA
#
###########################################
# Histórico de cambios:
# 
CAMPO=CODOPE,OCULTO,"_10_________"
CAMPO=CODRECURSO,OCULTO,"_10_________"


#0 
BEGINBLOQUE=VDCOMPVISUAL0.PAN  
ENDBLOQUE
#1 
BEGINBLOQUE=VDCOMPVISUAL1.PAN
    PADRE=VDCOMPVISUAL0.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDCOMPVISUAL2.PAN
    PADRE=VDCOMPVISUAL0.PAN
ENDBLOQUE
#3
BEGINBLOQUE=VDCOMPVISUAL3.PAN
    PADRE=VDCOMPVISUAL0.PAN
ENDBLOQUE
#4
BEGINBLOQUE=VDCOMPVISUAL4.PAN
    PADRE=VDCOMPVISUAL0.PAN
ENDBLOQUE
