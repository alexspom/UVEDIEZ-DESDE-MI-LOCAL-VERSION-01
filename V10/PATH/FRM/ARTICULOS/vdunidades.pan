# Módulo   : VDUNIDADES.PAN
# Función  : Mantenimiento de unidades de medida
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE UNIDADES
Unidad                                       Ultima modificación
_________ _40_______________________________ _32________ ¿D-MM-Y.YY ________
|

TABLA=VDUNIDADES

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")




CAMPO=UNIDAD,NOUPDATE,TOOLTIP("Unidad de medida"),TITULO("Unidad")
CAMPO=DESUNIDAD,TOOLTIP("Designación de la unidad de medida"),POSTCHANGE=FVALNOCERO("Debe introducir la designación de la unidad"),TITULO("Designación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


