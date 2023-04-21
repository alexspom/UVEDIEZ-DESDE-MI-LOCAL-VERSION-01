# Módulo   : VDTARIFA.PAN
# Función  : Mantenimiento de tarifas de agencia
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios: 
# (1) 15-04-2008: Adaptar pantallas a las especificaciones de Movianto. Sergio Rojo 
MANTENIMIENTO DE TARIFAS
 Código    Tarifa               Entorno                    Validez     Hasta       Ultima modificación
 @L@@@@@@@ _20_________________ _30_______________________ ¿D-MM-Y.YY  ¿D-MM-Y.YY  _32________ ¿D-MM-Y.YY ________ 
|

TABLA=VDTARIFA
ORDERBY=SEQTARIFA ASC;

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CSELSECTARIFA","No puedo generar siguiente tarifa")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
#(1)I
PREDELETE=FEJECUTA("-CSELVDTARIFAAG"  ," No puede borrar esta tarifa !!! \n\n En bloque 2 tiene AGENCIAS asignadas. \n",
                   "-CSELVDTARIFADIV" ," No puede borrar esta tarifa !!! \n\n En bloque 3 tiene DIVISIONES asignadas. \n",
                   "-CSELVDTARIFAZONA"," No puede borrar esta tarifa !!! \n\n En bloque 4 tiene ZONAS asignadas. \n")
#(1)F                   
                   

CAMPO=SEQTARIFA,NOUPDATE,TITULO("Código")
CAMPO=CODTARIFA,TOOLTIP("Código de la tarifa"),TITULO("Tarifa")
CAMPO=ENTORNO,TOOLTIP("Entorno de simulacion REAL es la tarifa vigente")
CAMPO=FECDESDE,TOOLTIP("Fecha inicio de validez de la tarifa"),TITULO("Validez"),COMBOX("CALENDARIO"),WLONX=30
CAMPO=FECHASTA,TOOLTIP("Fecha de final de validez de la tarifa"),TITULO("Hasta"),COMBOX("CALENDARIO"),WLONX=30
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODCOMEN,OCULTO,"@@@@@"
#(1)I
CURSOR=CSELVDTARIFAAG SELECT SEQTARIFA FROM VDTARIFAAG WHERE SEQTARIFA=:SEQTARIFA;

CURSOR=CSELVDTARIFADIV SELECT SEQTARIFA FROM VDTARIFADIV WHERE SEQTARIFA=:SEQTARIFA;

CURSOR=CSELVDTARIFAZONA SELECT SEQTARIFA FROM VDTARIFAZONA WHERE SEQTARIFA=:SEQTARIFA;
#(1)F 

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSECTARIFA SELECT VDSECTARIFA.NEXTVAL SEQTARIFA FROM DUAL;

AYUDA=MANTENIMIENTO DE TARIFAS

TECLA=SF10,FLEEMENU("VDTARIFA.ZOO")

ONLINE=   {F4} Confirmar Cambios   {F6} Cambio de pantalla   {F9} Borrar Registro   {May-F10} Menú contextual;
