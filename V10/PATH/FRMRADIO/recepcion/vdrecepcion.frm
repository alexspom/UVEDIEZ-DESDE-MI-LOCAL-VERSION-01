# Módulo   : VDRECEPCION.FRM
# Función  : RECEPCIÓN DE MERCANCÍA
#
###########################################
# Histórico de cambios:
# 
CAMPO=CODOPE,OCULTO,"_10_________"
CAMPO=CODRECURSO,OCULTO,"_10_________"
CAMPO=BLOQUEOS,OCULTO,"_50____________"
CAMPO=BLOQUEOSORIG,OCULTO,"_50____________"
#CAMPO=MULTIARTICULO,OCULTO,"_"

PREFORM=FEJECUTA(FPOSICIONABLOQUE("VDRECPULMON.PAN"),"")
#0 
BEGINBLOQUE=VDRECPULMON.PAN
ENDBLOQUE
#1 
BEGINBLOQUE=VDRECORDEN.PAN
    PADRE=VDRECPULMON.PAN
ENDBLOQUE
#2 
BEGINBLOQUE=VDRECMATRICULA.PAN
    PADRE=VDRECORDEN.PAN
ENDBLOQUE
#3 
BEGINBLOQUE=VDRECARTICULO.PAN
    PADRE=VDRECMATRICULA.PAN
ENDBLOQUE
#4 
BEGINBLOQUE=VDRECCANTIDAD.PAN
    PADRE=VDRECARTICULO.PAN
ENDBLOQUE
#5 
BEGINBLOQUE=VDRECVERIF.PAN
    PADRE=VDRECCANTIDAD.PAN
ENDBLOQUE
#6 
BEGINBLOQUE=VDUBICAENTRADASDESDERECEP.PAN
    PADRE=VDRECVERIF.PAN
ENDBLOQUE
#7 
BEGINBLOQUE=VDREUBIMANUENT.PAN
    PADRE=VDUBICAENTRADASDESDERECEP.PAN
ENDBLOQUE
#8 
BEGINBLOQUE=VDUBICACARRODESDERECEP.PAN
    PADRE=VDRECVERIF.PAN
ENDBLOQUE
#9 
BEGINBLOQUE=VDREUBIMANUCARROENT.PAN
    PADRE=VDUBICACARRODESDERECEP.PAN
ENDBLOQUE
#10
BEGINBLOQUE=VDASIGNAALMACEN.PAN
    PADRE=VDRECVERIF.PAN
ENDBLOQUE