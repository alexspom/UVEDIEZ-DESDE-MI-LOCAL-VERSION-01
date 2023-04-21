# Módulo   : VDSELCLASE.PAN
# Función  : Seleccion de clases de una clasificacion
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
SELECCION DE CLASES
Clase             Decripción                                 D Ultima modificación
_15______________ _40_______________________________________ _ _32_________ ¿D-MM-Y.YY ________   
|
TABLA=VDCLASES
ORDERBY=CODCLASE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,OCULTO,"_15"
CAMPO=CODCLASE, TOOLTIP("Código de la clase"),POSTCHANGE=FVALNOCERO("EL Código DE CLASE ES OBLIGATORIO")
CAMPO=DESCLASE, TOOLTIP("Descipción de la clase"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASE \nES OBLIGATORIA")
CAMPO=SWTDEFECTO,TOOLTIP("Indica si la clase es la por defecto de la clasificación debe valer S o blanco"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco")      
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;



