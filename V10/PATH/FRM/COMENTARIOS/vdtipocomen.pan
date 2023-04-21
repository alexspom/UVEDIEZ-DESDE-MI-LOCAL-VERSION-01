# Módulo   : VDTIPOCOMEN.PAN
# Función  : Mantenimiento de tipo de comentarios
#
# Creación : 20-11-2007
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TIPOS DE COMENTARIO
                                        Max.                                              
Ord Tabla          Tipo           Not. Líneas Descripción               Priv. Ver     Priv. Modif   Priv. Insertar Ultima modificación
@L  _32___________ _32___________  _   @L@@@@ _40______________________ _1000________ _1000________ _1000________  _32_________ ¿D-MM-Y.YY ________
 
|

TABLA=VDTIPOCOMEN
ORDERBY=TABLACOMEN,ORDEN;


PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

CAMPO=ORDEN,TOOLTIP("Orden en el que se muestran el tipo de comentario"),TITULO("Ord"), WLONX=15
CAMPO=TABLACOMEN,TOOLTIP("Tabla a la que se asocia el tipo de comentario"),TITULO("Tabla")
CAMPO=TIPOCOMEN,TOOLTIP("Tipo de comentario"),TITULO("Tipo")
CAMPO=NOTIFICABLE,UPPER,TOOLTIP("Indica si los eventos de este tipo de comentario deben notificarse automáticamente.\n"
                                "Valores posibles S(í), N(o) o blanco"),
                        POSTCHANGE=FVERIFICA("SN ","Valores posibles S(í) N(o) o blanco"),TITULO("Not"), WLONX=15
CAMPO=MAXLINEAS,TOOLTIP("Numero máximo de lineas de comentarios que puede tener un objeto de este tipo; 0 ilimitado"),TITULO("Max Lineas"),WLONX=35
CAMPO=DESTIPOCOMEN,TOOLTIP("Descripción del comentario"),POSTCHANGE=FVALNOCERO("Debe introducir designacion del tipo de comentario"),TITULO("Descripción")
CAMPO=PRIVILEGIOSVER,PROTECT("IMPLANTADOR"),TITULO("Priv. Ver"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVILEGIOSMOD,PROTECT("IMPLANTADOR"),TITULO("Priv. Modif"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=PRIVILEGIOSINS,PROTECT("IMPLANTADOR"),TITULO("Priv. Insert"),COMBOXMULTIPLE("CLISTAPRIV")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en la que se realizó la Ultima modificación")

CURSOR=CLISTAPRIV SELECT PRIVILEGIO,COMENTARIO FROM VDPRIVILEGIO ORDER BY PRIVILEGIO;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


