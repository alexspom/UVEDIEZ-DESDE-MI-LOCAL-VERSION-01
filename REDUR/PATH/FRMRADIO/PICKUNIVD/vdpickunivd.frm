# MOdulo   : VDPICKUNIVD.FRM
# Función  : Formulario de recogida de bultos de unidades
#            con volumetría dinámica
#
# Creación : 20-03-2020
# Autor    : FPD
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________"
CAMPO=CODRECURSO,OCULTO,"__________"

#0
BEGINBLOQUE=VDPICKUNIVDMAT.PAN
ENDBLOQUE
#1
BEGINBLOQUE=VDPICKUNIVDPDTE.PAN
 PADRE=VDPICKUNIVDMAT.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDPICKUNIVDNOPICK.PAN
 PADRE=VDPICKUNIVDPDTE.PAN
ENDBLOQUE
#3
BEGINBLOQUE=VDPICKUNIVDUBI.PAN
 PADRE=VDPICKUNIVDPDTE.PAN
ENDBLOQUE
#4
BEGINBLOQUE=VDPICKUNIVDART2.PAN
 PADRE=VDPICKUNIVDUBI.PAN
ENDBLOQUE
#5
BEGINBLOQUE=VDPICKUNIVDART.PAN
 PADRE=VDPICKUNIVDART2.PAN
ENDBLOQUE
#6
BEGINBLOQUE=VDPICKUNIVDREG.PAN
 PADRE=VDPICKUNIVDART.PAN
ENDBLOQUE
#7
BEGINBLOQUE=VDPICKUNIVDANUL.PAN
 PADRE=VDPICKUNIVDART2.PAN
ENDBLOQUE
#8
BEGINBLOQUE=VDPICKUNIVDFIN.PAN
 PADRE=VDPICKUNIVDART.PAN
ENDBLOQUE
#9
BEGINBLOQUE=VDPICKUNIVDERRCONGELA.PAN
 PADRE=VDPICKUNIVDUBI.PAN
ENDBLOQUE
#10
BEGINBLOQUE=VDPICKUNIVDPDTESTOCK.PAN
 PADRE=VDPICKUNIVDPDTE.PAN
ENDBLOQUE