# Módulo   : VDPERFILTAREA.PAN
# Función  : Mantenimiento de tareas de terminal de radio
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
DEFINICION DE PERFILES DE TAREAS
Perfil  __________ _40_______________________________________  Pantalla _255_____________________________
Tarea  _1024________________________________________________________________________
Areas: Origen _1024__________________________________ destino _1024__________________________________
Clasif ubi _______________   Clase ubi origen _1024______________   Clase ubi destino _1024__________________________
Zonas origen _1024______________________  Zonas destino _1024______________________
Clasif. art. ______________    Clase artículo  _1024____________________
Privilegios   _1000__________________
Puede mover: Contenedores _ Embalajes _ Unidades _
Alturas: Max @L@ Min @L@ Priomov Max @L@@@ Min @L@@@ Asignamov _
Agrupa: Origen _ Destino _ Serie _  Máximo num @L@ Planifica _ Funplanif _60__________________
Extra _255____________________________     Coment. @L@@@@@@@
Ultima modificación _32_________ ¿D-MM-Y.YY _8________
|

TABLA=VDPERFILTAREA
#WPLEGADO

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODPERFIL,NOUPDATE,VIRTUAL,TOOLTIP("Código del perfil de tarea")
CAMPO=DESPERFIL,TOOLTIP("Designación del perfil de la tarea")
CAMPO=NPANTALLA,TOOLTIP("Nombre de la pantalla a ejecutar"),POSTCHANGE=FVALNOCERO("Debe introducir la pantalla")
CAMPO=RANTAREA,TOOLTIP("Tareas a las que se asigna esta pantalla (admite rangos)")
CAMPO=RANAREAORI,TOOLTIP("Areas de origen (admite rangos)")
CAMPO=RANAREADEST,TOOLTIP("Areas destino (admite rangos)")
CAMPO=CODCLASIFUBI,TOOLTIP("Clasificación de ubicaciones a las que se refieren los rangos")
CAMPO=RANCLASEUBIORI,TOOLTIP("Clase de ubicaciones origen (admite rangos)")
CAMPO=RANCLASEUBIDEST,TOOLTIP("Clase de ubicacion destino (admite rangos)")
CAMPO=RANCODZONORI,TOOLTIP("Zonas origen (admite rangos)")
CAMPO=RANCODZONDEST,TOOLTIP("Zonas destino (admite rangos)")
CAMPO=CODCLASIFART,TOOLTIP("Clasificacion de articulos")
CAMPO=RANCLASEART,TOOLTIP("Clase de articulos (admite rangos")
CAMPO=PRIVILEGIOSTAREA,TOOLTIP("Privilegios necesarios para ejecutar la tarea (admite rangos)")
CAMPO=CONTENEDORES,TOOLTIP("Indica si el perfil puede mover contenedores"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=EMBALAJES,TOOLTIP("Indica si el perfil puede mover embalajes completos"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=UNIDADESSUELTAS,TOOLTIP("Indica si el perfil puede mover unidades sueltas"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=MAXALT,TOOLTIP("Máxima altura que se puede alcanzar en esta tarea -1 indica máxima altura del recurso")
CAMPO=MINALT,TOOLTIP("Mínima altura que se puede alcanzar en esta tarea -1 indica mínima altura del recurso")
CAMPO=MAXPRIOMOV,TOOLTIP("Maxima prioridad de movimiento asignable")
CAMPO=MINPRIOMOV,TOOLTIP("Minima prioridad de movimiento asignable")
CAMPO=ASIGNAMOV,TOOLTIP("Asigna los movimientos"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=AGRUPAORIG,TOOLTIP("Indica si se agrupan movimientos con el mismo origen"),
                POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=AGRUPADEST,TOOLTIP("Indica si se agrupan movimientos con el mismo destino"),
                POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=AGRUPASERIE,TOOLTIP("Indica si se agrupan movimientos con el mismo C(ualquiera) S(erie) P(edido) N(ada)"),
                POSTCHANGE=FVERIFICA("CSPNT","Debe introducir C(ualquiera) S(erie) P(edido) N(ada) T(odo)")
CAMPO=MAXAGRUPA,TOOLTIP("Maximo numero de movimientos que se agrupan")
CAMPO=FORMPLANIF,TOOLTIP("Indica si se ha de utilizar el planificador de forms"),POSTCHANGE=FVERIFICA("SN","Debe introcucir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=FUNPLANIF,TOOLTIP("Funcion de planificacion en caso de no ser la estandard")
CAMPO=VDEXTRA,TOOLTIP("Informacion extra para el implantador de V10")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



