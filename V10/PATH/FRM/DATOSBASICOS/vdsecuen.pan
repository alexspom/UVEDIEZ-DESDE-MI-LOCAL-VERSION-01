# Módulo   : VDSECUEN.PAN
# Función  : Mantenimiento de secuenciales
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE SECUENCIALES
Nombre               Valor     Inicio    Máximo    Ultima modificación
____________________ @L@@@@@@@ @L@@@@@@@ @L@@@@@@@ _32__________ ¿D-MM-Y.YY _8________
|

TABLA=VDSECUEN


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=NOMBRESECUEN,NOUPDATE,TOOLTIP("Nombre del secuencial")
CAMPO=SECUENCIAL,TOOLTIP("Valor actual del secuencial")
CAMPO=PRIMSECUEN,TOOLTIP("Inicio de la secuencia")
CAMPO=MAXSECUEN,TOOLTIP("Máximo valor de la secuencia")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


