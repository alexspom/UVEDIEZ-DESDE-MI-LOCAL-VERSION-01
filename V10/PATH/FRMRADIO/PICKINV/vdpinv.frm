# MOdulo   : VDPINV.FRM
# Función  : Formulario de recogida de picking inverso sin cubeta.
#
# Creación : 09-06-2009
# Autor    : FGS
###########################################
# HistOrico de cambios:
# 
CAMPO=CODOPE,OCULTO,"__________________"
CAMPO=CODRECURSO,OCULTO,"_________________"

BEGINBLOQUE=VDPINV.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVCAJAART.PAN
    PADRE=VDPINV.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVCAJANOMOV.PAN
    PADRE=VDPINVCAJAART.PAN
ENDBLOQUE
BEGINBLOQUE=VDPINVPICOART.PAN
    PADRE=VDPINV.PAN
ENDBLOQUE


