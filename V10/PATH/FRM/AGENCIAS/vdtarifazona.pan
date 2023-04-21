# Módulo   : VDTARIFA.PAN
# Función  : Mantenimiento de zonas de tarificacion de agencias
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios: 
# (1) 15-04-2008: Adaptar pantallas a las especificaciones de Movianto. Sergio Rojo 
MANTENIMIENTO DE ZONAS
Zona Rango de zonas                      Pri. EIVA Ultima modificación
 @L@ _1024______________________________ @L@     _ _32________ ¿D-MM-Y.YY ________ 
                                                                                 |

TABLA=VDTARIFAZONA

ORDERBY=ZONATARIF;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CSELZONATARIF","No puedo calcular siguiente zona")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
#(1)I
PREDELETE=FEJECUTA("-CSELVDTARIFADEF"," No puede borrar esta tarifa !!! \n\n En bloque 5 tiene MANTENIMIENTO DE PRECIOS asignados. \n")
#(1)F


CAMPO=SEQTARIFA,VIRTUAL,OCULTO
CAMPO=ZONATARIF,NOUPDATE,TOOLTIP("Zona de tarificación"),NOENTER,TITULO("Zona"),WLONX=20
CAMPO=RANGOZONAS,TECLA=SF10,FEJECUTAFORM("VDSELCABZONGEO","S","","RANGOZONAS=:RANGOZONAS","RANGOZONAS=:RANGOZONAS","","S"),TOOLTIP("Rango de zonas geográficas"),TITULO("Rango Zonas")
CAMPO=PRIOZONATARIF,TOOLTIP("Prioridad de la zona de tarificación"),TITULO("Prioridad"),WLONX=45
CAMPO=EXENTOIVA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indica si la zona esta exenta de IVA, valores posibles 'S' o 'N'"),TITULO("Exento IVA"),WLONX=80
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@@@@@"

#(1)I
CURSOR=CSELVDTARIFADEF SELECT SEQTARIFA FROM VDTARIFADEF WHERE SEQTARIFA=:SEQTARIFA AND ZONATARIF=:ZONATARIF;
#(1)F 

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELZONATARIF SELECT NVL(MAX(ZONATARIF),0)+1 ZONATARIF FROM VDTARIFAZONA WHERE SEQTARIFA=:SEQTARIFA;


AYUDA=MANTENIMIENTO DE ZONAS DE TARIFAS

#TECLA=SF10,FLEEMENU("VDTARIFAZONA.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
