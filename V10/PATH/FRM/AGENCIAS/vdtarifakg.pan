# Módulo   : VDTARIFAKG.PAN
# Función  : Mantenimiento de tarifas por rango de bultos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TARIFAS POR RANGO DE KILOS
 Rango kilos     Fijo    Precio Kg. Reexp.     Ultima modificación
 @L,@@@@ @L,@@@@ #L##.## #L,###.### #L,###.### _32________ ¿D-MM-YY  ________
                                                                   |

TABLA=VDTARIFAKG
ORDERBY=DESDEKILOS,HASTAKILOS,CLASETARIFA;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CAJUSTAHASTA","No puedo ajustar rango de kilos")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CAJUSTAHASTA","No puedo ajustar rango de kilos")

CAMPO=SEQTARIFA,VIRTUAL,OCULTO
CAMPO=ZONATARIF,VIRTUAL,OCULTO
CAMPO=CLASETARIFA,VIRTUAL,OCULTO
CAMPO=DESDEKILOS,TOOLTIP("Desde cuantos kilos es el rango"),TITULO("Rango Kilos")
CAMPO=HASTAKILOS,TOOLTIP("Hasta cuantos bultos es el rango")
CAMPO=PRECIOFIJO,TOOLTIP("Precio fijo por albarán"),TITULO("Fijo")
CAMPO=PRECIOKILO,TOOLTIP("Precio por cada kilo adicional"),TITULO("Precio Kg.")
CAMPO=IMPORTEREEXP,TOOLTIP("Importe de reexpedicion si procede"),TITULO("Reexp.")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@@@@@"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CAJUSTAHASTA SELECT DECODE(:HASTAKILOS,0,9999999,:HASTAKILOS) HASTAKILOS FROM DUAL;



AYUDA=MANTENIMIENTO TARIFAS POR RANGO DE KILOS

#TECLA=SF10,FLEEMENU("VDTARIFAKG.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
