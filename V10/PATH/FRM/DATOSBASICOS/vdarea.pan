# Módulo   : VDAREA.PAN
# Función  : Mantenimiento de áreas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE AREAS
Código           Designación                    Orden  M.Lib Area de Ref. Ultima modificación
_20____________  _40___________________________ @L@@@  @L@@@ _20_________ _32_________ ¿D-MM-Y.YY ________

|
TABLA=VDAREA
ORDERBY=CODAREA;

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")



CAMPO=CODALM,VIRTUAL,OCULTO
CAMPO=CODAREA,NOUPDATE,TOOLTIP("Código del área"),TITULO("Código")
CAMPO=DESAREA,TOOLTIP("Designación del área"),TITULO("Designación")
CAMPO=ORDENAREA,TOOLTIP("Orden del área para calculo de distancias"),TITULO("Orden"),WLONX=20
CAMPO=MINLIBRE,TOOLTIP("Minimo de ubicaciones libres por pasillo"),TITULO("Ubi.Lib.Pas."),WLONX=35
CAMPO=CODAREAREF,TOOLTIP("Area de Referencia para calcular distancia entre ubic. candidatas y preasignadas con el artículo en dicha área al ubicar"),TITULO("Area de Ref.")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



