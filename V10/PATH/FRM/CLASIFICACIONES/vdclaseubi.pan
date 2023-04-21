# Módulo   : VDCLASEUBI.PAN
# Función  : Mantenimiento de clases
#
# Creación : 14-11-2007
# Autor    : ICC
###########################################
MANTENIMIENTO DE UBICACIONES PARA UNA CLASE
 Ubicación       Area         Tipo Ubicación  Tr. B.E. B.S. Ultima modificación
 _20___________  _20_________      _           _   _    _   _32_________ ¿D-MM-Y.YY ________ 
|
TABLA=VDCLASEUBI

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=CODUBI, TOOLTIP("Código de la ubicación clasificada"),
      POSTCHANGE=FVALNOCERO("El Código de ubicación \nES OBLIGATORIO"),
	    POSTCHANGE=FDESIGNACION("CCALCUBI","No encuentro datos de la ubicación"),
	    TITULO("Ubicación")
CAMPO=CODAREA,AUXILIAR,NOENTER,TOOLTIP("Area en que se localiza la ubicación\n:DESAREA"),
      POSTCHANGE=FEJECUTA("CSELAREA","No se encuentran datos del Area"),
      TITULO("Area")
CAMPO=TIPOUBI,AUXILIAR,NOENTER,TOOLTIP("Indica si es una ubicación normal, manantial o sumidero"),TITULO("Tipo Ubi."), WLONX=50
CAMPO=TRANSITO,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicación es de tránsito, en cuyo caso \nla mercancía que contenga se reubicará automáticamente según los flujos vigentes"),TITULO("Tr."), WLONX=15
CAMPO=BLOQUEOSE,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicación se encuentra bloqueada para entradas"),TITULO("B.E."), WLONX=18
CAMPO=BLOQUEOSS,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicación se encuentra bloqueada para salidas"),TITULO("B.S."), WLONX=18
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")
CAMPO=DESAREA,AUXILIAR,OCULTO,"_40_"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCALCUBI SELECT CODAREA,TRANSITO,BLOQUEOSE,BLOQUEOSS,
                       DECODE(STOCK,'S','Normal',DECODE(BLOQUEOSS,'N','Fuente ') ||
					                             DECODE(BLOQUEOSE,'N','Sumidero')) TIPOUBI
                FROM VDUBICA WHERE CODUBI=:CODUBI;
CURSOR=CSELAREA SELECT DESAREA FROM VDAREA WHERE CODAREA=:CODAREA;

