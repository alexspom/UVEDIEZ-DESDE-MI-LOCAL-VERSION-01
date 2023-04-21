# Módulo   : VDTARIFA.PAN
# Función  : Mantenimiento de zonas de tarificacion de agencias
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios: 
# (1) 15-04-2008: Adaptar pantallas a las especificaciones de Movianto. Sergio Rojo 
MANTENIMIENTO DE REEXPEDICIONES
C DP       Importe   Ultima modificación
_ _10_____ #L,###.## _32________ ¿D-MM-Y.YY ________ 
                                          |

TABLA=VDTARIFAREEXP

ORDERBY=DP;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=SEQTARIFA,VIRTUAL,OCULTO
CAMPO=CLASETARIFA,TOOLTIP("Tipo de tarifa C(ompra) o V(enta)"),TITULO("CLASE"),POSTCHANGE=FVERIFICA("CV","Debe introducir C(ompra) o V(enta)")
CAMPO=DP,TOOLTIP("Distrito postal afectado"),TITULO("DP")
CAMPO=IMPORTEREEXP,TOOLTIP("Importe de reexpedición"),TITULO("Importe")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
 

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


AYUDA=MANTENIMIENTO DE ZONAS DE TARIFAS

#TECLA=SF10,FLEEMENU("VDTARIFAZONA.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
