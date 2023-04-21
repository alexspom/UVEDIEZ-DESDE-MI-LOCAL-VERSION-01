# Módulo   : VDTIPOEMBA.PAN
# Función  : Mantenimiento de tipos de embalaje
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE TIPOS DE EMBALAJE
Tipo                                         CodComen  Ultima modificación              
_________ _40_______________________________ @@@@@@@@@ _32________ ¿D-MM-Y.YY  ________
|

TABLA=VDTIPOEMBA

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

CAMPO=TIPOEMBA,NOUPDATE,TOOLTIP("Tipo de embalaje"),TITULO("Tipo")
CAMPO=DESTIPOEMBA,TOOLTIP("Designación del tipo de embalaje"),POSTCHANGE=FVALNOCERO("No puede dejar designación en blanco"),TITULO("Designación")
CAMPO=CODCOMEN,NOENTER,TITULO("Comen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


