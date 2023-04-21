# Módulo   : VDPICKUNIFIN.PAN
# Función  : Formulario de recogida de bultos de unidades.
#            Pantalla de finalización de bulto.
#
# Creación : 13-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______  

BULTO ACABADO

DEPOSITE EL BULTO 
____________________
EN VERIFICACION

PULSE ENTER _
|

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDPICKUNIBUL.PAN"),"ERROR\n AL CARGAR BLOQUE VDPICKUNIBUL.PAN")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,NOENTER,VIRTUAL
CAMPO=DUMMY
