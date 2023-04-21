# Módulo   : VDCONVERSIONES.PAN
# Función  : Mantenimiento de conversiones de unidad de medida
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CONVERSIONES DE UNIDADES
Origen                                  Destino                                 Factor          Ultima modificación              
_________ _40__________________________ _________ _40__________________________ #L,########.### _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDCONVERSIONES

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")




CAMPO=UNIDADORIGEN,TOOLTIP("Unidad origen"),POSTCHANGE=FDESIGNACION("CSELUNIORI","No existe la unidad origen"),TITULO("Unidad Origen")
CAMPO=DESUNIDADORIGEN,AUXILIAR,NOENTER,TOOLTIP("Designación de la unidad origen")
CAMPO=UNIDADDESTINO,TOOLTIP("Unidad destino"),POSTCHANGE=FDESIGNACION("CSELUNIDEST","No existe la unidad destino"),TITULO("Unidad Destino")
CAMPO=DESUNIDADDESTINO,AUXILIAR,NOENTER,TOOLTIP("Designación de la unidad destino")
CAMPO=FACTORCONVERSION,TOOLTIP("Factor para convertir unidades de origen en unidades destino"),TITULO("Factor")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELUNIORI SELECT DESUNIDAD DESUNIDADORIGEN FROM VDUNIDADES WHERE UNIDAD=:UNIDADORIGEN;
CURSOR=CSELUNIDEST SELECT DESUNIDAD DESUNIDADDESTINO FROM VDUNIDADES WHERE UNIDAD=:UNIDADDESTINO;




CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


