#################################################################################
#MOdulo: VDRETROPED.FRM
#Funcionalidad : Seleccion de pedidos para retrodecederlos y extraerlos de serie
#Autor: JMM      
#Fecha: 30-07-2008
#################################################################################
# HistOrico de cambios:
#
BEGINBLOQUE=VDRETROPED.PAN
    PREREGISTRO=PRESEHIJO
    REGPAG=20
    POSX=1
    POSY=1
ENDBLOQUE

BEGINBLOQUE=VDBULRETROPED.PAN
 PADRE=VDRETROPED.PAN
 PREQUERY=QUERYHIJO
 POSX=16
 POSY=26
 REGPAG=19
ENDBLOQUE



