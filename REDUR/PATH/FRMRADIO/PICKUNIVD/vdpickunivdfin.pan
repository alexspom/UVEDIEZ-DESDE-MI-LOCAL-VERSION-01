# Módulo   : VDPICKUNIVDFIN.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de finalización de bulto.
#
# Creación : 13-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
PICKING DE UNIDADES
_10_______ _10_______  

BULTO ACABADO

DEPOSITE EL BULTO
CON MATRICULA 
____________________

EN MESA DE EMPAQUETADO

PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("0"),"\n\n ERROR\n AL CARGAR BLOQUE VDPICKUNIVDMAT.PAN")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=MATCAJA,NOENTER,VIRTUAL
CAMPO=DUMMY
CAMPO=CODBULTO,VIRTUAL,OCULTO
