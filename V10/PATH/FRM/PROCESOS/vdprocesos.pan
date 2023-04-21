######
# VDPROCESOS.PAN - Sistema de ventanas de configuración de algoritmos.
#
# Propósito: Ventana para dar crear/modificar/borrar procesos.
#
#
# Autor	   : José Carlos Santos
# Fecha    : 05-11-2007
####
# Modificaciones:
####
MANTENIMIENTO DE PROCESOS
                                                                  Max.
Proceso        Grupo     Función          Librería         Interv. Ej.  Semáforo   A Or Fec. Modif Hora modif. Usuario
_32___________ _20______ _32_____________ _32_____________ #L##### #L## _20_______ _ @@ ¿D-MM-Y.YY _32________ ________
                                                                                       |

TABLA=VDPROCESOS
ORDERBY=GRUPOPROC,ORDENACION;

PREINSERT=FEJECUTA("CSELMODIF","No se puede insertar fecha de modificación.")
PREUPDATE=FEJECUTA("CSELMODIF","No se puede actualizar fecha de modificación.")

CAMPO=PROCESO,UPPER,NOUPDATE, TOOLTIP("Nombre del proceso"),TITULO("Proceso")
CAMPO=GRUPOPROC,TITULO("Grupo")
CAMPO=FUNCIONPROC,MIXED, TOOLTIP("Nombre de la función"),TITULO("Función")
CAMPO=LIBPROCESO,UPPER, TOOLTIP("Librería en la que está implementada la función"),TITULO("Librería")
CAMPO=PERIODO,TOOLTIP("Tiempo en centésimas de segundo entre ejecución consecutivas, -1 sin periodo"),TITULO("Interv.")
CAMPO=EJECUCIONES,TOOLTIP("Número máximo de ejecuciones del proceso. 0 Inlimitadas"),TITULO("MaxEj"),WLONX=20
CAMPO=CODSEMAFORO,TOOLTIP("Semáforo asociado al proceso"),TITULO("Semáforo")
CAMPO=ACTIVO,TOOLTIP("Indica si el proceso esta activo"),TITULO("Act"),CHECKBOX("N","S"),WLONX=10
CAMPO=ORDENACION,UPPER, TOOLTIP ("Orden de aparición en la pantalla"),TITULO("Orden"),WLONX=25
CAMPO=PARAM,UPPER, OCULTO, "_256_"
CAMPO=FECMODIF, NOENTER,TITULO("Ultima modificación")
CAMPO=HORAMODIF, NOENTER
CAMPO=CODOPEMODIF,UPPER, NOENTER

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CEJECUTAINMEDIATO UPDATE VDPROCESOS SET EJECUTAINMEDIATO='X' WHERE PROCESO=:PROCESO;

TECLA=SF2, FEJECUTA ("CEJECUTAINMEDIATO", "NO PUEDO LANZAR EL PROCESO",
                     FCOMMIT, "")
