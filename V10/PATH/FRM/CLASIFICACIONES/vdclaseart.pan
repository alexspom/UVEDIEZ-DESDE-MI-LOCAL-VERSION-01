# M�dulo   : VDCLASEART.PAN
# Funci�n  : Mantenimiento de clases
#
# Creaci�n : 14-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE ARTICULOS PARA UNA CLASE
 Art�culo      Descripci�n                     Ultima modificaci�n
 _40_________  _100___________________________ _32_________ �D-MM-Y.YY ________ 
                                                                  |
TABLA=VDCLASEARTIC


PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=CODART, TOOLTIP("C�digo del art�culo clasificado"),
      CONTEXTUAL=FLEEMENU("VDARTICLASIF.ZOO"),
      POSTCHANGE=FVALNOCERO("El C�digo de art�culo \nES OBLIGATORIO"),
	    POSTCHANGE=FDESIGNACION("CDESART","No encuentro descripci�n del art�culo"),
	    TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del art�culo clasificado"),TITULO("Descripci�n")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;


