# Módulo   : VDCLASIFICACIONES.PAN
# Función  : Mantenimiento de clasificaciones
#
# Creación : 14-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CLASIFICACIONES
 Clasificación    Descripción                     Tabla Clasificación   O T Or Privilegio Ver  Privilegio Mod. Ultima modificación
 _20____________  _40____________________________ _40__________________ _ _ @L _1000__________ _10000_________ _32_________ ¿D-MM-Y.YY ________ 
|
TABLA=VDCLASIFICACIONES
ORDERBY=TABLACLASIF,SWTOBLIG,ORDENCLASIF,CODCLASIF;
WHERE=VDUSER.TENGOPRIVILEGIO(PRIVILEGIOSVER)=1;


PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

CAMPO=CODCLASIF, TOOLTIP("Código de la clasificación"), 
      POSTCHANGE=FVALNOCERO("EL Código DE CLASIFICACION ES OBLIGATORIO"),TITULO("Clasificación")
CAMPO=DESCLASIF, TOOLTIP("Designación de la clasificación"),
      POSTCHANGE=FVALNOCERO("LA DESCRIPCION DE LA CLASIFICACION \nES OBLIGATORIA"),TITULO("Descripción")
CAMPO=TABLACLASIF,TOOLTIP("Tabla sobre la que se clasifica pude valer VDARTIC o VDUBICA"),POSTCHANGE=FENRANGO("VDARTIC,VDUBICA,VDDIVIS,TRABAJOS","Debe introducir VDARTIC, VDUBICA o VDDIVIS"),TITULO("Tabla Clasificación")
CAMPO=SWTOBLIG,TOOLTIP("Indica si es obligatorio clasificar segun esta clasificación"),POSTCHANGE=FVERIFICA("S ","Debe introducir S(i) o blanco"),TITULO("O")
CAMPO=TIPOCLASIF,TOOLTIP("Tipo de clasificacion A compatibilidad de articulos C compatibilidad de contenedores S compatibilidad de estados E compatibilidad de embalajes O otras"),TITULO("T")
CAMPO=ORDENCLASIF,TOOLTIP("Orden en el que aparecen las clasificaciones en pantalla"),TITULO("Or")
CAMPO=PRIVILEGIOSVER,NOUPDATE("IMPLANTADOR"),TOOLTIP("Privilegios necesarios para ver la clasificación"),TITULO("Privilegio Ver"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVILEGIOSMOD,NOUPDATE("IMPLANTADOR"),TOOLTIP("Privilegios para clasificar segun esta clasificación"),TITULO("Privilegio Modif"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=CODOPEMODIF,NOENTER, TOOLTIP("Usuario que ha realizado la ultima modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER, TOOLTIP("Fecha  en que se efectuó alguna modificación a los datos del registro")
CAMPO=HORAMODIF,NOENTER, TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro")
CAMPO=SUBTITULO,AUXILIAR,OCULTO,"_64____"

#CURSORES

CURSOR=CLISTAPRIV SELECT PRIVILEGIO,COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


