# M�dulo   : VDSELCLASE.PAN
# Funci�n  : Seleccion de clases de una clasificacion
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
SELECCION DE CLASES
Clase             Decripci�n                                 D Ultima modificaci�n
_15______________ _40_______________________________________ _ _32_________ �D-MM-Y.YY ________   
|
TABLA=VDCLASES
ORDERBY=CODCLASE;

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,OCULTO,"_15"
CAMPO=CODCLASE, TOOLTIP("C�digo de la clase"),POSTCHANGE=FVALNOCERO("EL C�digo DE CLASE ES OBLIGATORIO")
CAMPO=DESCLASE, TOOLTIP("Descipci�n de la clase"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASE \nES OBLIGATORIA")
CAMPO=SWTDEFECTO,TOOLTIP("Indica si la clase es la por defecto de la clasificaci�n debe valer S o blanco"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco")      
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificaci�n")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;



