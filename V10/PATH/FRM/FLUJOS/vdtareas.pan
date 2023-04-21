#Módulo: VDTAREAS.PAN
#Función: Mantenimiento de tipos de flujos
#
# Creación : 13-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TAREAS
 Tarea                           Descripción                    Clasificación     Ultima modificación 
 _32___________________________  _40___________________________ _15______________ _32_________ ¿D-MM-Y.YY ________ 
|

TABLA=VDTAREAS
ORDERBY=TAREA;


PREINSERT=FEJECUTA("CMODIF","")
PREUPDATE=FEJECUTA("CMODIF","")


CAMPO=TAREA,TOOLTIP("Tarea que trata el flujo\n:DESTAREA"),TITULO("Tarea")
CAMPO=DESTAREA,TOOLTIP("Descripción del flujo"),POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA TAREA \nES OBLIGATORIA"),TITULO("Descripción")
CAMPO=CODCLASIF,COMBOX("CSELCLASE"),TOOLTIP("Clasificación de artículos a utilizar por el flujo"),POSTCHANGE=FDESIGNACION("CSELCLASIF","ERROR, NO EXISTE LA CLASIFICACION :CODCLASIF"),TITULO("Clasificación")
CAMPO=CODOPEMODIF, NOENTER, TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF, NOENTER, TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro.")
CAMPO=HORAMODIF, NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro.")
CAMPO=DUMMY,AUXILIAR,OCULTO, "@"

CURSOR=CMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF 
                  FROM DUAL;

CURSOR=CSELCLASE SELECT CODCLASIF FROM VDCLASIFICACIONES;
 
CURSOR=CSELCLASIF SELECT 1 DUMMY FROM VDCLASIFICACIONES WHERE CODCLASIF = :CODCLASIF;

#CONTEXTUAL=FLEEMENU("IPFLUJOSPMA.ZOO")


