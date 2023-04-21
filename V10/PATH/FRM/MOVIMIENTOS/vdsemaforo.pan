# Módulo   : VDSEMAFORO.PAN
# Función  : Mantenimiento de semaforos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO SEMAFOROS
Código         Designación                       T E Sid       Serial    Programa                 Ordenador             Terminal               Ultima Modificación
_20___________ _40______________________________ _ @ @L@@@@@@@ @L@@@@@@@ _64_____________________ _64__________________ _64___________________ _32________ ¿D-MM-Y.YY  ________
|
TABLA=VDSEMAFORO

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CODSEMAFORO,NOUPDATE,TOOLTIP("Código del semáforo"),TITULO("Código")
CAMPO=DESSEMAFORO,TOOLTIP("Designación"),TITULO("Designación")
CAMPO=TIPOSEMAFORO,TOOLTIP("Tipo del semáforo puede ser a nivel (S)esión o a nivel (G)lobal"),POSTCHANGE=FENRANGO("S,G","Debe introducir S(esion) o G(lobal)"),TITULO("T")
CAMPO=ESTADO,TOOLTIP("Estado del semáforo puede ser 0 libre o 1 ocupado"),TITULO("E")
CAMPO=SID,TOOLTIP("Sid de la sesion que ha tomado el semaforo"),TITULO("SID")
CAMPO=SERIAL,TOOLTIP("Serial de la sesion que ha tomado el semaforo"),TITULO("Serial")
CAMPO=PROGRAM,TOOLTIP("Programa que ha tomado el semáforo"),TITULO("Programa")
CAMPO=MACHINE,TOOLTIP("Ordenador en el que se ejecuta el programa"),TITULO("Ordenador")
CAMPO=TERMINAL,TOOLTIP("Terminal desde el que se ejecuta el programa"),TITULO("Terminal")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




