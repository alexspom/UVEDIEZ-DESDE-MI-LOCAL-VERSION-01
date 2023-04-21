# Módulo   : VDCLASES.PAN
# Función  : Mantenimiento de clases
#
# Creación : 14-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CLASES
Clase             Decripción                                 D Extra                                    Ultima modificación
_15______________ _40_______________________________________ _ _255____________________________________ _32_________ ¿D-MM-Y.YY ________   
|

TABLA=VDCLASES

ORDERBY=CODCLASE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE, TOOLTIP("Código de la clase"),POSTCHANGE=FVALNOCERO("EL Código DE CLASE ES OBLIGATORIO"),TITULO("Clase")
CAMPO=DESCLASE, TOOLTIP("Descipción de la clase"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASE \nES OBLIGATORIA"),TITULO("Descripción")
CAMPO=SWTDEFECTO,TOOLTIP("Indica si la clase es la por defecto de la clasificación debe valer S o blanco"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco"),TITULO("D")
CAMPO=VDEXTRA,UPPER,TOOLTIP("Mensaje informativo que actualmente se usa en la Factura Proforma INSULAR"),TITULO("Extra")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;


