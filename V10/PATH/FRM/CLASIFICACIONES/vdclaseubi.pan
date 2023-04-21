# M�dulo   : VDCLASEUBI.PAN
# Funci�n  : Mantenimiento de clases
#
# Creaci�n : 14-11-2007
# Autor    : ICC
###########################################
MANTENIMIENTO DE UBICACIONES PARA UNA CLASE
 Ubicaci�n       Area         Tipo Ubicaci�n  Tr. B.E. B.S. Ultima modificaci�n
 _20___________  _20_________      _           _   _    _   _32_________ �D-MM-Y.YY ________ 
|
TABLA=VDCLASEUBI

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=CODUBI, TOOLTIP("C�digo de la ubicaci�n clasificada"),
      POSTCHANGE=FVALNOCERO("El C�digo de ubicaci�n \nES OBLIGATORIO"),
	    POSTCHANGE=FDESIGNACION("CCALCUBI","No encuentro datos de la ubicaci�n"),
	    TITULO("Ubicaci�n")
CAMPO=CODAREA,AUXILIAR,NOENTER,TOOLTIP("Area en que se localiza la ubicaci�n\n:DESAREA"),
      POSTCHANGE=FEJECUTA("CSELAREA","No se encuentran datos del Area"),
      TITULO("Area")
CAMPO=TIPOUBI,AUXILIAR,NOENTER,TOOLTIP("Indica si es una ubicaci�n normal, manantial o sumidero"),TITULO("Tipo Ubi."), WLONX=50
CAMPO=TRANSITO,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicaci�n es de tr�nsito, en cuyo caso \nla mercanc�a que contenga se reubicar� autom�ticamente seg�n los flujos vigentes"),TITULO("Tr."), WLONX=15
CAMPO=BLOQUEOSE,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicaci�n se encuentra bloqueada para entradas"),TITULO("B.E."), WLONX=18
CAMPO=BLOQUEOSS,AUXILIAR,NOENTER,TOOLTIP("Indica si la ubicaci�n se encuentra bloqueada para salidas"),TITULO("B.S."), WLONX=18
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=DESAREA,AUXILIAR,OCULTO,"_40_"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CCALCUBI SELECT CODAREA,TRANSITO,BLOQUEOSE,BLOQUEOSS,
                       DECODE(STOCK,'S','Normal',DECODE(BLOQUEOSS,'N','Fuente ') ||
					                             DECODE(BLOQUEOSE,'N','Sumidero')) TIPOUBI
                FROM VDUBICA WHERE CODUBI=:CODUBI;
CURSOR=CSELAREA SELECT DESAREA FROM VDAREA WHERE CODAREA=:CODAREA;

