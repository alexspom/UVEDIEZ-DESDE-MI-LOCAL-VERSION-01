# MOdulo   : VDREUBICAPARPU.FRM
# Función  : Formulario de cambio de ubicación parcial de stock
#            en area de picking
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDREUBICAPARPU.PAN"),"")

#0
BEGINBLOQUE=VDREUBICAPARPU.PAN
ENDBLOQUE
#1
BEGINBLOQUE=VDREUBICAPARPU2.PAN
 PADRE=VDREUBICAPARPU.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDREUBICAPARPUOK.PAN
 PADRE=VDREUBICAPARPU2.PAN
ENDBLOQUE

