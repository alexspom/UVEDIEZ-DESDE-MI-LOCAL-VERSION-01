###################################################################
#Módulo: VDRUTAS.PAN
#Funcionalidad : Mantenimiento de rutas
###################################################################
#
MANTENIMIENTO DE RUTAS
 Código               Descripción                                   Ultima modif.
 _20_________________ _100_________________________________________ _32______________ ¿D-MM-YYY.Y ________  

|

REGPAG=18
PROTECT("ADMINISTRADOR")

TABLA=VDRUTAS
WHERE=ORDER BY CODRUTA;

PREINSERT=FEJECUTA("CMODIF","No puedo asignar fecha de modificación.")
PREUPDATE=FEJECUTA("CMODIF","No puedo asignar fecha de modificación.")

CAMPO=CODRUTA,UPPER,TOOLTIP("Código de la ruta"),TITULO("Código")
CAMPO=DESRUTA,UPPER,TOOLTIP("Descripción de la ruta"),TITULO("Descripción")
CAMPO=CODOPEMODIF,NOENTER,TITULO("Ult. Modif."),WLONX=12
CAMPO=FECMODIF,NOENTER,TITULO(""),WLONX=10
CAMPO=HORAMODIF,UPPER,NOENTER,TITULO(""),WLONX=10


CURSOR=CMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF
                FROM DUAL;

                



