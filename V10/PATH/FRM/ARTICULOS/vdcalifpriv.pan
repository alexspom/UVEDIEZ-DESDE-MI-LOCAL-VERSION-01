# Módulo   : VDCALIFPRIV.PAN
# Función  : Mantenimiento de cambios de calif. con privilegios especiales
#
# Creación : 17-06-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
CAMBIOS DE CALIFICACION CON PRIVILEGIOS ESPECIALES
  Valores Privilegios       Descripción                       Ultima modificación 
  
De _ a _  _1024____________ _40______________________________  _32________ ¿D-MM-Y.YY  ________    
|

TABLA=VDCALIFPRIV

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=INDICADOR,VIRTUAL,OCULTO
CAMPO=VALORCALIF,TOOLTIP("Posición del indicador"),NOUPDATE,TITULO("VALOR"),WLONX=35
CAMPO=NUEVOVALORCALIF,TOOLTIP("Posición del indicador"),NOUPDATE,TITULO("NUEVO VALOR"),WLONX=80
CAMPO=PRIVCALIF,TOOLTIP("Privilegio para el cambio de Calificación"),TITULO("Privilegios")
CAMPO=DESCAMBIO,TOOLTIP("Designación del cambio de calificación"),TITULO("Descripción")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;



