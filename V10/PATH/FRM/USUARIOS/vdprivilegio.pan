# Módulo   : VDPRIVILEGIO.PAN
# Función  : Mantenimiento de privilegios
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE PRIVILEGIOS
Privilegio          Descripción                       Ultima modificación
___________________ _255_____________________________ _32__________ ¿D-MM-Y.YY _8________
|

TABLA=VDPRIVILEGIO

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=PRIVILEGIO,NOUPDATE,TOOLTIP("Nombre del privilegio"),POSTCHANGE=FVALNOCERO("Debe introducir nombre del privilegio"),TITULO("Privilegio")
CAMPO=COMENTARIO,TOOLTIP("Descripción del privilegio"),POSTCHANGE=FVALNOCERO("Debe introducir descripción del privilegio"),TITULO("Descripción")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


