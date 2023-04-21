# Módulo   : VDCALIF.PAN
# Función  : Mantenimiento de calificaciones de stock
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CALIFICACIONES DE STOCK
I. Designación                    Privilegios cambio           Extra                            Coment.  Ultima modificación
@L _40___________________________ _1024_______________________ _255____________________________ @L@@@@@@ _32________ ¿D-MM-Y.YY  ________
|
TABLA=VDCALIF

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=INDICADOR,TOOLTIP("Posición del indicador"),NOUPDATE,TITULO("I")
CAMPO=DESINDICADOR,TOOLTIP("Designación del indicador"),TITULO("Designación")
CAMPO=PRIVCALIF,TOOLTIP("Privilegios necesarios para cambiar el indicador"),TITULO("Priv. cambio")
CAMPO=VDEXTRA,TOOLTIP("Campo extra para el implantador"),TITULO("Extra")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario del contenedor"),TITULO("Comen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




