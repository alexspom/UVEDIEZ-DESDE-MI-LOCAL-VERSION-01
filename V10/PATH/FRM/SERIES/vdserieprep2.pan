###################################################################
#Módulo: VDSERIEPREP2.PAN
#Funcionalidad : Mantenimiento de series de preparación
#Autor: FGS
#Fecha: 03-09-2008
###################################################################
# Histórico de cambios:
SERIE PREPARACION

 Zonas:
 _1000_____________________________________
 Creada:      _32_____ ¿D-MM-Y.YY ________
 Prevista              ¿D-MM-Y.YY
 Iniciada:    _32_____ ¿D-MM-Y.YY ________
 Cerrada:     _32_____ ¿D-MM-Y.YY ________
 Terminada:            ¿D-MM-Y.YY ________
 
 Ultima modificación.: _32_____ ¿D-MM-Y.YY ________

|

TABLA=VDSERIEPREP

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")


CAMPO=CODSERIEPREP,VIRTUAL,OCULTO
CAMPO=RANGOZONASPICKINV,TOOLTIP("Rango de Zonas de Pciking Inverso donde se prepara, si es de picking inverso")
CAMPO=CODOPECREADA,NOENTER,TOOLTIP("Operario que creó la serie")
CAMPO=FECCREADA,NOENTER,TOOLTIP("Fecha de creación de la serie de preparación")
CAMPO=HORACREADA,NOENTER,TOOLTIP("Hora de creación de la serie de preparación")
CAMPO=FECPREVISTA
CAMPO=CODOPELANZA,NOENTER,TOOLTIP("Operario que lanzó la serie")
CAMPO=FECLANZA,NOENTER,TOOLTIP("Fecha de lanzamiento de la serie de preparación")
CAMPO=HORALANZA,NOENTER,TOOLTIP("Hora de lanzamiento de la serie de preparación")
CAMPO=CODOPECIERRE,NOENTER
CAMPO=FECCIERRE,NOENTER,TOOLTIP("Fecha de lanzamiento de la serie de preparación")
CAMPO=HORACIERRE,NOENTER,TOOLTIP("Hora de lanzamiento de la serie de preparación")
CAMPO=FECTERMIN,NOENTER,TOOLTIP("Fecha de finalización de la serie de preparación")
CAMPO=HORATERMIN,NOENTER,TOOLTIP("Hora de finalización de la serie de preparación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro.")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro.")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='SPR';

