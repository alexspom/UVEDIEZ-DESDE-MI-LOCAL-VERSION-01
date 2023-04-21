# Módulo   : VDTIPODEMANDA.PAN
# Función  : Mantenimiento de tipo de Demandas
#
# Creación : 25-03-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TIPO DE DEMANDAS
 Tipo                                          Ult. Modificación   
 __________ _40_______________________________ _32________ ¿D-MM-Y.YY  ________
|


TABLA=VDDEMANDATIPO

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=TIPODEMANDA,NOUPDATE,TOOLTIP("Tipo de Cabacera de Demanda"),TITULO("Tipo")
CAMPO=DESTIPO,TOOLTIP("Descripción del Tipo de Cabacera de Demanda")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




