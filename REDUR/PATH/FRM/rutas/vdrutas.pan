###################################################################
#M�dulo: VDRUTAS.PAN
#Funcionalidad : Mantenimiento de rutas
###################################################################
#
MANTENIMIENTO DE RUTAS
 C�digo               Descripci�n                                   Ultima modif.
 _20_________________ _100_________________________________________ _32______________ �D-MM-YYY.Y ________  

|

REGPAG=18
PROTECT("ADMINISTRADOR")

TABLA=VDRUTAS
WHERE=ORDER BY CODRUTA;

PREINSERT=FEJECUTA("CMODIF","No puedo asignar fecha de modificaci�n.")
PREUPDATE=FEJECUTA("CMODIF","No puedo asignar fecha de modificaci�n.")

CAMPO=CODRUTA,UPPER,TOOLTIP("C�digo de la ruta"),TITULO("C�digo")
CAMPO=DESRUTA,UPPER,TOOLTIP("Descripci�n de la ruta"),TITULO("Descripci�n")
CAMPO=CODOPEMODIF,NOENTER,TITULO("Ult. Modif."),WLONX=12
CAMPO=FECMODIF,NOENTER,TITULO(""),WLONX=10
CAMPO=HORAMODIF,UPPER,NOENTER,TITULO(""),WLONX=10


CURSOR=CMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                FROM DUAL;

                



