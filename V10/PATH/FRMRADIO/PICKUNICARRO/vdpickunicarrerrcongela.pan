# M�dulo   : VDPICKUNICARRERRCONGELA.PAN
# Funci�n  : Muestra el error de que no puede congelar un movto
#
# Creaci�n : 14-08-2008
# Autor    : FGS
###########################################
# Hist�rico de cambios:
#
PICKING DE CARRO POR TERMINAL
_10_______ _10_______

NO SE PUEDE 
SERVIR MOVTO 
@L@@@@@@@@@@@@@

PULSE ENTER _

|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNICARROART.PAN"),"ERROR\n AL CARGAR BLOQUE\n VDPICKUNICARROART.PAN") 


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMOV,VIRTUAL,NOENTER
CAMPO=SALIR