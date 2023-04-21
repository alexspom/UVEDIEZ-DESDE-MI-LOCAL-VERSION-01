# Módulo   : VDCALIFVALOR.PAN
# Función  : Mantenimiento de calificaciones de stock
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CALIFICACIONES DE STOCK
V Designación                    Ultima modificación
_ _40___________________________ _32________ ¿D-MM-Y.YY  ________
|
TABLA=VDCALIFVALOR

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=INDICADOR,VIRTUAL,OCULTO
CAMPO=VALORCALIF,TOOLTIP("Posición del indicador"),NOUPDATE,TITULO("V")
CAMPO=DESVALOR,TOOLTIP("Designación del indicador"),TITULO("Designación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




