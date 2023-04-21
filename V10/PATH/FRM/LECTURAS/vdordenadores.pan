# Módulo   : VDORDENADORES.PAN
# Función  : Mantenimiento de tablas de ordenadores
#
# Creación : 11-07-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ORDENADORES
Ordenador                 Escáner   Extra               Ba.  Ultima modificacion
_32______________________ @L@ @L@   _255_______________ @L@  _32____________ ¿D-MM-Y.YYY ________
|
TABLA=VDORDENADORES

ORDERBY=ORDENADOR;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=ORDENADOR,TOOLTIP("Nombre del ordenador"),TITULO("Ordenador")
CAMPO=IDINFOLECTURA,TITULO("Red"),WLONX=20
CAMPO=SCANNER,PROTECT("IMPLANTADOR"),TOOLTIP("Número de scaner de la red de escaners asociado al ordenador"),TITULO("Escaner"),WLONX=34
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente"),TITULO("Extra")
CAMPO=NUMBASC,TITULO("Basc.")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Código del operador o proceso que realizar la operacion de modificacion"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la ultima modificacion")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la ultima modificacion")
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
