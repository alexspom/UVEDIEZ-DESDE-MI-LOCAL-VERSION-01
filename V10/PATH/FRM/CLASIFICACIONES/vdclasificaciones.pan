# M�dulo   : VDCLASIFICACIONES.PAN
# Funci�n  : Mantenimiento de clasificaciones
#
# Creaci�n : 14-11-2007
# Autor    : ICC
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE CLASIFICACIONES
 Clasificaci�n    Descripci�n                     Tabla Clasificaci�n   O T Or Privilegio Ver  Privilegio Mod. Ultima modificaci�n
 _20____________  _40____________________________ _40__________________ _ _ @L _1000__________ _10000_________ _32_________ �D-MM-Y.YY ________ 
|
TABLA=VDCLASIFICACIONES
ORDERBY=TABLACLASIF,SWTOBLIG,ORDENCLASIF,CODCLASIF;
WHERE=VDUSER.TENGOPRIVILEGIO(PRIVILEGIOSVER)=1;


PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF, TOOLTIP("C�digo de la clasificaci�n"), 
      POSTCHANGE=FVALNOCERO("EL C�digo DE CLASIFICACION ES OBLIGATORIO"),TITULO("Clasificaci�n")
CAMPO=DESCLASIF, TOOLTIP("Designaci�n de la clasificaci�n"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASIFICACION \nES OBLIGATORIA"),TITULO("Descripci�n")
CAMPO=TABLACLASIF,TOOLTIP("Tabla sobre la que se clasifica pude valer VDARTIC o VDUBICA"),POSTCHANGE=FENRANGO("VDARTIC,VDUBICA,VDDIVIS,TRABAJOS","Debe introducir VDARTIC, VDUBICA o VDDIVIS"),TITULO("Tabla Clasificaci�n")
CAMPO=SWTOBLIG,TOOLTIP("Indica si es obligatorio clasificar segun esta clasificaci�n"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco"),TITULO("O")
CAMPO=TIPOCLASIF,TOOLTIP("Tipo de clasificacion A compatibilidad de articulos C compatibilidad de contenedores S compatibilidad de estados E compatibilidad de embalajes O otras"),TITULO("T")
CAMPO=ORDENCLASIF,TOOLTIP("Orden en el que aparecen las clasificaciones en pantalla"),TITULO("Or")
CAMPO=PRIVILEGIOSVER,NOUPDATE("IMPLANTADOR"),TOOLTIP("Privilegios necesarios para ver la clasificaci�n"),TITULO("Privilegio Ver"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVILEGIOSMOD,NOUPDATE("IMPLANTADOR"),TOOLTIP("Privilegios para clasificar segun esta clasificaci�n"),TITULO("Privilegio Modif"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n a los datos del registro")
CAMPO=SUBTITULO,AUXILIAR,OCULTO,"_64____"

#CURSORES

CURSOR=CLISTAPRIV SELECT PRIVILEGIO,COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


