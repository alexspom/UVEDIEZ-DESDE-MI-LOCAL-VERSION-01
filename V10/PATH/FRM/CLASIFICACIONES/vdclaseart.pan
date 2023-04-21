# Módulo   : VDCLASEART.PAN
# Función  : Mantenimiento de clases
#
# Creación : 14-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
MANTENIMIENTO DE ARTICULOS PARA UNA CLASE
 Artículo      Descripción                     Ultima modificación
 _40_________  _100___________________________ _32_________ ¿D-MM-Y.YY ________ 
                                                                  |
TABLA=VDCLASEARTIC


PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF,VIRTUAL,OCULTO
CAMPO=CODCLASE,VIRTUAL,OCULTO
CAMPO=CODART, TOOLTIP("Código del artículo clasificado"),
      CONTEXTUAL=FLEEMENU("VDARTICLASIF.ZOO"),
      POSTCHANGE=FVALNOCERO("El Código de artículo \nES OBLIGATORIO"),
	    POSTCHANGE=FDESIGNACION("CDESART","No encuentro descripción del artículo"),
	    TITULO("Artículo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Descripción del artículo clasificado"),TITULO("Descripción")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;
CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;


