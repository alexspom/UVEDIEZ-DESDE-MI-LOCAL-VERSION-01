# Módulo   : VDPROVI.PAN
# Función  : Mantenimiento de provincias
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
TABLA DE PROVINCIAS
Provincia                                      Ultima modificación
_____ _40_____________________________________ _32__________ ¿D-MM-Y.YY _8________
|

TABLA=VDPROVI

#SELECT=DECODE(MOD(CODPROV,3),0,18,1,19,2,20,-1) CODOPEMODIF__COLOR,DECODE(MOD(CODPROV,2),0,1,0) FECMODIF__INVISIBLE;



PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODPAIS,NOUPDATE,VIRTUAL,OCULTO
CAMPO=CODPROV,NOUPDATE,TOOLTIP("Código de la provincia"),TITULO("Provincia")
CAMPO=DESPROV,TOOLTIP("Designación de la provincia")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


