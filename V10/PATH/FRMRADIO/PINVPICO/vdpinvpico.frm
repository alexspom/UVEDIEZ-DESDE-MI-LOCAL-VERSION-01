# MOdulo   : VDPINVPICO.FRM
# Función  : Formulario de recogida de picos para picking inverso.
#
# Creación : 19-09-2008
# Autor    : FGS
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________________"
CAMPO=CODRECURSO,OCULTO,"_________________"

BEGINBLOQUE=VDPINVPICOART.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVPICOMAT.PAN
    PADRE=VDPINVPICOART.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVPICOCONF.PAN
    PADRE=VDPINVPICOART.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVPICONOMOV.PAN
    PADRE=VDPINVPICOART.PAN
ENDBLOQUE

