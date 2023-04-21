# Módulo   : VDTIPOCONTE.PAN
# Función  : Mantenimiento de tipos de contenedor
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TIPOS DE CONTENEDOR
Tipo de                                                    ----- Dimensiones en mm -----
Contenedor Descripción                        M Peso       Alto       Largo      Ancho      CodComen  Ultima modificación              
_________  _40_______________________________ _ #L,####### #L,####### #L,####### #L,####### @@@@@@@@@ _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDTIPOCONTE
ORDERBY=TIPOCONTE;
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")




CAMPO=TIPOCONTE,NOUPDATE,TOOLTIP("Tipo del contenedor"),TITULO("Tipo")
CAMPO=DESTIPOCONTE,TOOLTIP("Designación del tipo de contenedor"),POSTCHANGE=FVALNOCERO("No puede dejar designación en blanco"),TITULO("Descripción")
CAMPO=MOVIBLE,TOOLTIP("Movible (S/N)"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)"),TITULO("M")
CAMPO=PESOCONTE,TOOLTIP("Peso del contenedor en gramos"),TITULO("Peso")
CAMPO=ALTOCONTE,TOOLTIP("Alto del contenedor en mm"),TITULO("Alto")
CAMPO=LARGOCONTE,TOOLTIP("Largo del contenedor en mm"),TITULO("Largo")
CAMPO=ANCHOCONTE,TOOLTIP("Ancho del contenedor en mm"),TITULO("Ancho")
CAMPO=CODCOMEN,NOENTER,TITULO("Comen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


