######
# VDUBIENTRADAS.FRM 
# 
# Propůsito: UBICACION DE CONTENEDORES RECEPCIONADOS
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

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDUBICAENTRADAS1.PAN"),"")
#0 
BEGINBLOQUE=VDUBICAENTRADAS1.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDUBICAENTRADAS2.PAN
    PADRE=VDUBICAENTRADAS1.PAN
ENDBLOQUE
BEGINBLOQUE=VDREUBIMANU.PAN
    PADRE=VDUBICAENTRADAS2.PAN
ENDBLOQUE
