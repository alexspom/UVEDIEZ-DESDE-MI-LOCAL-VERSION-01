# Módulo   : VDLOTESPARAM.PAN
# Función  : Configuración de cambios de bloqueos de lotes
#
# Creación : 01-07-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CONFIGURACION DE CAMBIOS DE CALIFICACIONES DE STOCK DE LOTES

Ord Clase                           Rango Div.     Rango Areas    Bloqueos                                  Patrón     Concepto   Ultima modificación
@L@ _______________ _______________ _1024_________ _1024_________ ____________________ ____________________ __________ __________ _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDLOTESPARAM
ORDERBY=ORDEN;

PREINSERT=FEJECUTA("-CCLASIF","SOLO PUEDE HABER UNA CLASIFICACION PARA LA CONFIGURACION",
                   "CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("-CCLASIF","SOLO PUEDE HABER UNA CLASIFICACION PARA LA CONFIGURACION",
                   "CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=ORDEN,TOOLTIP("Orden de preferencia de los patrones"),TITULO("Ord"), WLONX=15
CAMPO=CODCLASIF,TOOLTIP("Clasificación de los artículos"),TITULO("Clase")
CAMPO=CODCLASE,TOOLTIP("Clase de los artículos")
CAMPO=RANGODIV,TOOLTIP("Rango de Divisiones de los artículos"),TITULO("Rango Div.")
CAMPO=RANGOAREA,TOOLTIP("Rango de áreas donde se encuentra el stock de los lotes de los articulos"),TITULO("Rango Areas")
CAMPO=PATRONBLOQORI,TOOLTIP("Patrón de los bloqueos orígen del cambio de bloqueos, a cumplir"),TITULO("Bloqueos"),
                     POSTCHANGE=FEJECUTA("CCHECKORILONG20","La longitud del patrón de bloqueos origen debe ser de 20")
CAMPO=PATRONBLOQDEST,TOOLTIP("Patrón de los bloqueos destino del cambio de bloqueos, a cumplir"),
                     POSTCHANGE=FEJECUTA("CCHECKDESTLONG20","La longitud del patrón de bloqueos destino debe ser de 20")
CAMPO=PATRONBLOQUEOS,MIXED,TOOLTIP("Patrón de propagación de los cambios de bloqueos.\n N: en esa posición no se propagan\n S: se propaga en la posición si el valor actual coincide con el del lote\n F: siempre se propaga para esa posición\nEn minusculas solo se propagan los cambios si el indicador se modifica"),
                     POSTCHANGE=FEJECUTA("CCHECKVALORES","LOS VALORES POSIBLES SON N,S o F"),TITULO("Patrón")
CAMPO=CODCONCE,TOOLTIP("Concepto de los movtos en la transformación de bloqueos del stock"),TITULO("Concepto")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CCHECKORILONG20 SELECT :PATRONBLOQORI FROM DUAL WHERE LENGTH(:PATRONBLOQORI)=20;

CURSOR=CCHECKDESTLONG20 SELECT :PATRONBLOQDEST FROM DUAL WHERE LENGTH(:PATRONBLOQDEST)=20;


CURSOR=CCHECKVALORES SELECT :PATRONBLOQUEOS FROM DUAL WHERE VDART.VERIFPATRONPROP(UPPER(:PATRONBLOQUEOS))=1;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CCLASIF SELECT :CODCLASIF FROM VDLOTESPARAM WHERE CODCLASIF!=NVL(:CODCLASIF,'-');



