# Módulo   : VDERVICIOS.PAN
# Función  : Mantenimiento de servicios
#
# Creación : 12-07-2008
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE SERVICIOS
Servicio         Designación               A Estado                  PID       SID       SERIAL    Ejecutable                  Entorno                        Path  V10                      Path                      Parámetros                Ultima modificación
_32_____________ _32______________________ _ @L@@@ _40______________ @L@@@@@@@ @L@@@@@@@ @L@@@@@@@ _512_______________________ _512__________________________ _512__________________________ _512_____________________ _512_____________________ _32_________ ¿D-MM-Y.YY _8________
|


TABLA=VDSERVICIOS


PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODGRUPOSERV,NOUPDATE,VIRTUAL,OCULTO
CAMPO=CODSERVICIO,NOUPDATE,TOOLTIP("Código del servicio"),TITULO("Servicio")
CAMPO=DESSERVICIO,TOOLTIP("Designación del servicio"),POSTCHANGE=FVALNOCERO("Debe introducir la designación del servicio"),TITULO("Designación")
CAMPO=ACTIVO,TOOLTIP("Indica si el servicio se puede ejecutar"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("Act."),WLONX=15
CAMPO=STATUS,TOOLTIP("Estado del servicio"),POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe el estado"),TITULO("Estado"),WLONX=20
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Designación del estado del servicio"),TITULO("Descripción")
CAMPO=PID,TOOLTIP("El PID del programa"),TITULO("PID")
CAMPO=SID,TOOLTIP("SID de la conexion ORACLE"),TITULO("SID")
CAMPO=SERIAL,TOOLTIP("SERIAL de la conexión ORACLE"),TITULO("Serial")
CAMPO=EJECUTABLE,TOOLTIP("Ejecutable que implementa el servicio"),TITULO("Ejecutable"),MIXED
CAMPO=ENVSERVICIO,MIXED,TOOLTIP("Variables de entorno del servicio separadas por \n"),TITULO("Entorno"),MIXED
CAMPO=PATHV10SERVICIO,TOOLTIP("Path V10 particular del servicio, se añade al path genérico del grupo"),TITULO("Path V10")
CAMPO=PATHSERVICIO,TOOLTIP("Path particular del servicio, se añade al path genérico del grupo"),TITULO("Path")
CAMPO=PARAMSERVICIO,TOOLTIP("Parámetros particulares del servicio, se añade a los parámetros genéricos del grupo"),TITULO("Parámetros")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='SER' AND STATUS=:STATUS;




