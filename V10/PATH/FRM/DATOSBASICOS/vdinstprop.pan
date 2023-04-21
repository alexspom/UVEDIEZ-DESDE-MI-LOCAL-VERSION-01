# Módulo   : VDGINSTPROP.PAN
# Función  : Mantenimiento de instancias de propiedades
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
INSTANCIAS DE CONFIGURACION
Instancia               
_40____________________________
|

SOLOQUERY
SELECT=SELECT DISTINCT INSTANCIA FROM VDCONFI WHERE GRUPOPROP=:GRUPOPROP;

ORDERBY=INSTANCIA;

CAMPO=GRUPOPROP,VIRTUAL,OCULTO
CAMPO=INSTANCIA,TOOLTIP("Instancia\nTecla SF8 copia la instancia"),TITULO("Instancia")

TECLA=SF8,FEJECUTAFORM("VDCOPIAINST","S","","ORIGEN=:INSTANCIA GRUPOPROP=:GRUPOPROP")




