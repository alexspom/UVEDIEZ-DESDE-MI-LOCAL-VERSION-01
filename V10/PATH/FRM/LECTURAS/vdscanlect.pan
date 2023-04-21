# Módulo   : VDSCANLECT.PAN
# Función  : Mantenimiento de lecturas de scanner
#
# Creación : 21-05-2008
# Autor    : Maite González
###########################################
MANTENIMIENTO DE LECTURAS DE SCANNER
Texto                    Red   Scanner Secuencia Status  Ultima modificación
_256____________________ @L@   @L@@@@@ @L,@@@@@@ @L@@    _32________ ¿D-MM-Y.YY ________
|

TABLA=VDSCANLECT

PROTECT("SUPERVISOR")

PREINSERT=FEJECUTA("CSELSEC","No encuentro secuencial",
                   "CSELMODIF","No puedo poner fecha/hora modificacion")
PREUPDATE=FEJECUTA("CSELMODIF","No puedo poner fecha/hora modificacion")

CAMPO=TEXTO,TOOLTIP("Texto leído por el escáner"),TITULO("Texto")
CAMPO=REDSCAN,TOOLTIP("Red de escáneres que realiza la lectura"),TITULO("Red"), WLONX=15
CAMPO=SCANNER,TOOLTIP("Escáner que realiza la lectura"),TITULO("Escaner"), WLONX=30
CAMPO=SEQACCION,NOUPDATE,TOOLTIP("Secuencial de la acción"),TITULO("Secuencia"), WLONX=35
CAMPO=STATUS,TOOLTIP("Estado de la lectura"),TITULO("Estado"), WLONX=20
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSEC SELECT VDSECSCANLECT.NEXTVAL SEQACCION,100 STATUS, DECODE(:REDSCAN,0,1,:REDSCAN) REDSCAN FROM DUAL;


