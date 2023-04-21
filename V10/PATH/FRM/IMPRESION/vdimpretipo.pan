# Módulo   : VDIMPRETIPO.PAN
# Función  : Mantenimiento de Tipos de Impresoras
#
# Creación : 13-05-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TIPOS DE IMPRESORAS
Tipo          Descripción                                                   Activo  Tipo            Ult. Modificación            
____________  ____________________________________________________________    _      _ _20__________ _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDIMPRETIPO

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=TIPOIMPRE,TOOLTIP("Tipo de Impresión"),TITULO("Tipo")
CAMPO=DESTIPOIMPRE,TOOLTIP("Descripción del Tipo de Impresión"),TITULO("Descripción")
CAMPO=ACTIVO,TOOLTIP("Si está activo el tipo de impresión"),POSTCHANGE=FEJECUTA(FVERIFICA("NS"),"CAMPO ACTIVO DEBE SER 'S' O 'N'"),TITULO("Act"),WLONX=15
CAMPO=TIPODOC,TOOLTIP("Tipo de Documento a Imprimir. (E)tiqueta o (I)nforme (P)rn"),POSTCHANGE=FEJECUTA(FVERIFICA("EIPA"),"CAMPO TIPO DE DOCUMENTO DEBE SER 'E' O 'I' 'A' o 'P'",
                                                                                                  "+CDESTIPODOC",""),TITULO("Tipo Doc.")
CAMPO=DESTIPODOC,AUXILIAR,NOENTER
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

#CURSORES
CURSOR=CDESTIPODOC SELECT DECODE(:TIPODOC,'E','ETIQUETAS','INFORME') DESTIPODOC FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


