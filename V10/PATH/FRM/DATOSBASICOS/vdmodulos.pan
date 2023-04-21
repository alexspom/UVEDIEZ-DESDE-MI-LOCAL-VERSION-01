# Módulo   : VDMODULOS.PAN
# Función  : Mantenimiento de modulos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE MODULOS
Cod. Designación                       Abreviada   Ultima modificación
@L@@ _40______________________________ ___________ _32_________ ¿D-MM-Y.YY _8________
|

TABLA=VDMODULOS


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=MODULO,NOUPDATE,TOOLTIP("Código del módulo"),TITULO("Cod.")
CAMPO=DESMODULO,TOOLTIP("Designación del módulo"),TITULO("Designación")
CAMPO=ABREVIADA,TOOLTIP("Abreviatura del modulo para generación de mensajes"),TITULO("Abreviada")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


