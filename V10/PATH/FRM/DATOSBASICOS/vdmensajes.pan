# Módulo   : VDMENSAJES.PAN
# Función  : Mantenimiento de mensajes
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE MENSAJES
Cod.   T Abreviada   Designación                 Ultima modificación
@L,@@@ _ ___________ _255_______________________ _32_________ ¿D-MM-Y.YY _8________
|

TABLA=VDMENSAJES



PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=MODULO,NOUPDATE,VIRTUAL,OCULTO
CAMPO=CODERROR,NOUPDATE,TOOLTIP("Código del error"),TITULO("Cod.")
CAMPO=TIPOERROR,TOOLTIP("Tipo de error I(nfo) W(arning) E(rror)"),TITULO("T")
CAMPO=ABREVIADA,TOOLTIP("Abreviatura del error"),TITULO("Abreviada")
CAMPO=MENSAJE,MIXED,TOOLTIP("Mensaje de error"),TITULO("Designación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


