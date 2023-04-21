# Módulo   : VDSELDIVIS.PAN
# Función  : Selección de divisiones
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
Selección de división
Div. Designacion                    Emp Designación.
_20_ _40___________________________ ___ _40__________________________________________
|

TABLA=VDDIVIS



CAMPO=CODDIV,TOOLTIP("Código de la división")
CAMPO=DESDIV,TOOLTIP("Designación de la división")
CAMPO=CODEMP,TOOLTIP("Empresa"),POSTCHANGE=FDESIGNACION("CSELEMP","No existe empresa")
CAMPO=DESEMP,AUXILIAR,NOENTER,TOOLTIP("Designación de la empresa")

CURSOR=CSELEMP SELECT DESEMP FROM VDEMPRE WHERE CODEMP=:CODEMP;



