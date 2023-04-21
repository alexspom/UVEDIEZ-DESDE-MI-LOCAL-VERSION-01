# M�dulo   : VDCLASES.PAN
# Funci�n  : Mantenimiento de clases
#
# Creaci�n : 14-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE CLASES
Clase             Decripci�n                                 D Extra                                    Ultima modificaci�n
_15______________ _40_______________________________________ _ _255____________________________________ _32_________ �D-MM-Y.YY ________   
|

TABLA=VDCLASES

ORDERBY=CODCLASE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE, TOOLTIP("C�digo de la clase"),POSTCHANGE=FVALNOCERO("EL C�digo DE CLASE ES OBLIGATORIO"),TITULO("Clase")
CAMPO=DESCLASE, TOOLTIP("Descipci�n de la clase"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASE \nES OBLIGATORIA"),TITULO("Descripci�n")
CAMPO=SWTDEFECTO,TOOLTIP("Indica si la clase es la por defecto de la clasificaci�n debe valer S o blanco"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco"),TITULO("D")
CAMPO=VDEXTRA,UPPER,TOOLTIP("Mensaje informativo que actualmente se usa en la Factura Proforma INSULAR"),TITULO("Extra")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;


