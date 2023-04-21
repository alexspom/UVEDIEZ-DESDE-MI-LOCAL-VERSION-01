# Módulo   : VDIMPREGRUPO.PAN
# Función  : Mantenimiento de Grupos de Impresoras
#
# Creación : 13-05-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE GRUPOS DE IMPRESORAS
Grupo            Descripción                                                   Activo  Ult. Modificación            
_______________  ____________________________________________________________    _     _32_________ ¿D-MM-Y.YY ________
|

TABLA=VDIMPREGRUPO
ORDERBY=GRUPOIMPRE;

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=GRUPOIMPRE,TOOLTIP("Nombre del Grupo de Impresoras"),TITULO("Grupo")
CAMPO=DESGRUPOIMPRE,TOOLTIP("Descripción del Grupo de Impresoras"),TITULO("Descripción")
CAMPO=ACTIVO,TOOLTIP("Si está activo el grupo de impresoras"),POSTCHANGE=FEJECUTA(FVERIFICA("NS"),"CAMPO ACTIVO DEBE SER 'S' O 'N'"),TITULO("Activo"),WLONX=30,CHECKBOX("N","S")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



