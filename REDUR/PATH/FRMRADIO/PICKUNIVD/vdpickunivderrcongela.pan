# M�dulo   : VDPICKUNIVDERRCONGELA.PAN
# Funci�n  : Muestra el error de que no puede congelar un movto
#
# Creaci�n : 14-08-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
PICKING DE UNIDADES
_10_______ _10_______

NO SE PUEDE 
SERVIR MOVTO 
@L@@@@@@@@@@@@@

PULSE ENTER _

|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIVDPDTE.PAN"),"\n\n ERROR\n AL CARGAR BLOQUE\n VDPICKUNIVDPDTE.PAN") 


# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=CODMOV,VIRTUAL,NOENTER
CAMPO=SALIR
