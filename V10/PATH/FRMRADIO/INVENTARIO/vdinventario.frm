######
# VDUBIENTRADAS.FRM 
# 
# PropOsito: UBICACION DE CONTENEDORES RECEPCIONADOS
#               
#           
# Autor	   : RFD
# Fecha    : 21-04-2008
####
# Modificaciones:
####
# 
CAMPO=CODOPE,OCULTO,"_10_________"
CAMPO=CODRECURSO,OCULTO,"_10_________"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDINVENUBI.PAN"),"")
#0 
BEGINBLOQUE=VDINVENUBI.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDINVENMAT.PAN
    PADRE=VDINVENUBI.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDINVENDISTUBI.PAN
    PADRE=VDINVENMAT.PAN
ENDBLOQUE
#2
BEGINBLOQUE=VDINVENART.PAN
    PADRE=VDINVENMAT.PAN
ENDBLOQUE

#3
BEGINBLOQUE=VDINVENCANT.PAN
    PADRE=VDINVENART.PAN
ENDBLOQUE
#4
BEGINBLOQUE=VDINVENOK.PAN
    PADRE=VDINVENCANT.PAN
ENDBLOQUE
#5
BEGINBLOQUE=VDINVENINCUMPLE.PAN
    PADRE=VDINVENCANT.PAN
ENDBLOQUE
#6
BEGINBLOQUE=VDINVENAJUSTE.PAN
    PADRE=VDINVENCANT.PAN
ENDBLOQUE
#7