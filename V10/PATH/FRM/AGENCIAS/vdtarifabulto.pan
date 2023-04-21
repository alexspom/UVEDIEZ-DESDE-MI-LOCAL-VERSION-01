# Módulo   : VDTARIFABULTO.PAN
# Función  : Mantenimiento de tarifas por rango de bultos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TARIFAS POR RANGO DE BULTOS
 Rango bultos Fijo    Prc. Bulto    Ultima modificación
 @L,@@ @L,@@  #L##.## #L,###.### _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDTARIFABULTO
ORDERBY=DESDEBULTOS,CLASETARIFA;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CAJUSTAHASTA","No puedo ajustar rango de kilos")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CAJUSTAHASTA","No puedo ajustar rango de kilos")

CAMPO=SEQTARIFA,VIRTUAL,OCULTO
CAMPO=ZONATARIF,VIRTUAL,OCULTO
CAMPO=CLASETARIFA,VIRTUAL,OCULTO
CAMPO=DESDEBULTOS,TOOLTIP("Desde cuantos bultos es el rango"),TITULO("Rango Bultos"),WLONX=30
CAMPO=HASTABULTOS,TOOLTIP("Hasta cuantos bultos es el rango")
CAMPO=PRECIOFIJO,TOOLTIP("Precio fijo por albarán"),TITULO("Fijo")
CAMPO=PRECIOBULTO,TOOLTIP("Precio por bulto adicional"),TITULO("Precio Bulto"),WLONX=20
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@@@@@"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CAJUSTAHASTA SELECT DECODE(:HASTABULTOS,0,99999,:HASTABULTOS) HASTABULTOS FROM DUAL;



AYUDA=MANTENIMIENTO TARIFAS POR RANGO DE KILOS

#TECLA=SF10,FLEEMENU("VDTARIFAKG.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
