# Módulo   : VDTARIFA.PAN
# Función  : Mantenimiento de tarifas de agencia
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios: 
# (1) 15-04-2008: Adaptar pantallas a las especificaciones de Movianto. Sergio Rojo 
MANTENIMIENTO DE TARIFAS
Código    Tarifa     Validez    Hasta      Ultima modificación
@L@@@@@@@ _20_______ ¿D-MM-Y.YY ¿D-MM-Y.YY _32________ ¿D-MM-Y.YY  ________
                                                                            |

NOINSERT
NODELETE
NOUPDATE

TABLA=VDTARIFA
ORDERBY=SEQTARIFA ASC;

                
                   

CAMPO=SEQTARIFA,NOUPDATE,TITULO("Código")
CAMPO=CODTARIFA,TOOLTIP("Código de la tarifa"),TITULO("Tarifa")
CAMPO=FECDESDE,TOOLTIP("Fecha inicio de validez de la tarifa"),TITULO("Validez"),COMBOX("CALENDARIO")
CAMPO=FECHASTA,TOOLTIP("Fecha de final de validez de la tarifa"),TITULO("Hasta"),COMBOX("CALENDARIO")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


ONLINE={F1} Ayuda  {F4} Confirmar Cambios  {F6} Cambio de pantalla
                {F9} Borrar Registro {May-F10} Menú contextual;
