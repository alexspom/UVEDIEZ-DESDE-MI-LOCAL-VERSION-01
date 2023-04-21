# Módulo   : VDINFOLECTURAS
# Función  : Mantenimiento de líneas de scaners del sistema
#
# Creación : 23-09-2008
# Autor    : FGS
###########################################
MANTENIMIENTO DE LINEAS DE ESCANERS
                                                       Car. Escape    Long.   Long.
ID  IP                Puerto TCP  Puerto 232 Velocidad STX ETX SOH  Id Scaner Datos Librería             VdExtra       Ult. modificación
@L@ _64______________ _32_______     ###       #####    _   __  _      ###     ###  _256________________ _255________  _32_______ ¿D-MM-Y.YYY _8_       
|

TABLA=VDINFOLECTURAS
ORDERBY=IDINFOLECTURA;
WFRAME(141,-2,110,0,"Puertos","")
WFRAME(316,-2,87,0,"Car. Escape","")
WFRAME(402,-2,93,0,"LOngitudes","")


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=IDINFOLECTURA,TOOLTIP("Identidicador de la Red de Escaners"),TITULO("Id")
CAMPO=DIRIP,TOOLTIP("IP de la red de escáner (si va por TCP)"),TITULO("Dirección IP")
CAMPO=PUERTOTCP,TOOLTIP("Puerto TCP de la IP indicada, si IP no es nulo"),TITULO("TCP")
CAMPO=PUERTO232,TOOLTIP("Puerto 232 Si Dir IP es NULO, y es no NULO"),TITULO("232"), WLONX=15
CAMPO=VELOCIDAD,TOOLTIP("Velocidad en Baudios a la que trabaja por 232 la Red"),TITULO("Velocidad"),WLONX=32
CAMPO=CHSTX,TOOLTIP("Caracter de Inicio de una lectura de la Red"),TITULO("STX"), WLONX=15
CAMPO=CHETX,TOOLTIP("Caracter de Final de una lectura de la Red"),TITULO("ETX"), WLONX=15
CAMPO=CHSOH,TOOLTIP("Caracter de Separación de ID Scaner y Datos en la Red. Si es NULO, no hay separación"),TITULO("SOH"), WLONX=15
CAMPO=LONIDSCAN,TOOLTIP("Longitud del identificador de Escaner en la Red. Si es 0 no se envia"),TITULO("Id Scan"), WLONX=32
CAMPO=LONDATA,TOOLTIP("Longitud Máxima permitida para los datos de la lectura. A NULO si no hay límite"),TITULO("Datos"),WLONX=20
CAMPO=LIBPROCESO,TOOLTIP("DLL que trata físicamente la red de scaners"),TITULO("Librería")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Extra")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que la realiza la Ultima modificación en la tabla"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha de la Ultima modificación en la tabla")
CAMPO=HORAMODIF,TOOLTIP("Hora de la Ultima modificación en la tabla")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

