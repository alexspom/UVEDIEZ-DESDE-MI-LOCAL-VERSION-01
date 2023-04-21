# Módulo   : VDPERFILTAREA.PAN
# Función  : Mantenimiento de tareas de terminal de radio
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
DEFINICION DE PERFILES DE TAREAS
Perfil                                                 Pantalla         Tarea                Area origen           Area destino          Clasif ubi      Clase ubi origen    Clase ubi destino               Zonas origen                Zonas destino               Clasif. art.   Clase artículo            Privilegios             C E U Max   Min O D S Max P Extra        Coment.   Ultima modificación
_20___________ _40____________________________________ _255____________ _1024_______________ _1024________________ _1024________________ _______________ _1024______________ _1024__________________________ _1024______________________ _1024______________________ ______________ _1024____________________ _1000__________________ _ _ _ @L@@@ @L@@@ _ _ _ @L@ _ _255________ @L@@@@@@@ _32_________ ¿D-MM-Y.YY _8________
|

TABLA=VDPERFILTAREA
ORDERBY=CODPERFIL;

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODPERFIL,NOUPDATE,TOOLTIP("Código del perfil de tarea"),TITULO("Perfil")
CAMPO=DESPERFIL,TOOLTIP("Designación del perfil de la tarea")
CAMPO=NPANTALLA,TOOLTIP("Nombre de la pantalla a ejecutar"),POSTCHANGE=FVALNOCERO("Debe introducir la pantalla"),TITULO("Pantalla")
CAMPO=RANTAREA,TOOLTIP("Tareas a las que se asigna esta pantalla (admite rangos)"),TITULO("Rango Tareas")
CAMPO=RANAREAORI,TOOLTIP("Areas de origen (admite rangos)"),TITULO("Rango Areas Origen")
CAMPO=RANAREADEST,TOOLTIP("Areas destino (admite rangos)"),TITULO("Rango Areas Desino")
CAMPO=CODCLASIFUBI,TOOLTIP("Clasificación de ubicaciones a las que se refieren los rangos"),TITULO("Rango Clasif. Ubi"), WLONX=60
CAMPO=RANCLASEUBIORI,TOOLTIP("Clase de ubicaciones origen (admite rangos)"),TITULO("Rango Clases UbiOri")
CAMPO=RANCLASEUBIDEST,TOOLTIP("Clase de ubicacion destino (admite rangos)"),TITULO("Rango Clases UbiDest")
CAMPO=RANCODZONORI,TOOLTIP("Zonas origen (admite rangos)"),TITULO("Rango Zonas Ori")
CAMPO=RANCODZONDEST,TOOLTIP("Zonas destino (admite rangos)"),TITULO("Rango Zonas Dest")
CAMPO=CODCLASIFART,TOOLTIP("Clasificacion de articulos"),TITULO("Rango Clasif. Art"), WLONX=60
CAMPO=RANCLASEART,TOOLTIP("Clase de articulos (admite rangos"),TITULO("Rango Clases Art")
CAMPO=PRIVILEGIOSTAREA,TOOLTIP("Privilegios necesarios para ejecutar la tarea (admite rangos)"),TITULO("Rango Privilegios")
CAMPO=CONTENEDORES,TOOLTIP("Indica si el perfil puede mover contenedores"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("C")
CAMPO=EMBALAJES,TOOLTIP("Indica si el perfil puede mover embalajes completos"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("E")
CAMPO=UNIDADESSUELTAS,TOOLTIP("Indica si el perfil puede mover unidades sueltas"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("U")
CAMPO=MAXALT,TOOLTIP("Máxima altura que se puede alcanzar en esta tarea -1 indica máxima altura del recurso"),TITULO("Max")
CAMPO=MINALT,TOOLTIP("Mínima altura que se puede alcanzar en esta tarea -1 indica mínima altura del recurso"),TITULO("Min")
CAMPO=AGRUPAORIG,TOOLTIP("Indica si se agrupan movimientos con el mismo origen"),TITULO("O"),
                POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=AGRUPADEST,TOOLTIP("Indica si se agrupan movimientos con el mismo destino"),TITULO("D"),
                POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=AGRUPASERIE,TOOLTIP("Indica si se agrupan movimientos con el mismo C(ualquiera) S(erie) P(edido) N(ada)"),
                POSTCHANGE=FVERIFICA("CSPNT","Debe introducir C(ualquiera) S(erie) P(edido) N(ada)"),TITULO("S")
CAMPO=MAXAGRUPA,TOOLTIP("Maximo numero de movimientos que se agrupan"),TITULO("MaxAgr")
CAMPO=FORMPLANIF,TOOLTIP("Indica si se ha de utilizar el planificador de forms"),POSTCHANGE=FVERIFICA("SN","Debe introcucir S(i) o N(o)"),TITULO("P")
CAMPO=VDEXTRA,TOOLTIP("Informacion extra para el implantador de V10"),TITULO("Info Cliente")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario"),TITULO("Codcomen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



