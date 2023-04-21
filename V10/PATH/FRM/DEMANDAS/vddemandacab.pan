# Módulo   : VDDEMANDACAB.PAN
# Función  : Mantenimiento de Cabeceras de Demanda
#
# Creación : 25-03-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
MANTENIMIENTO DE CABECERAS DE DEMANDA

 Código __________ Tipo __________ _40________________________________________________
 
 Estado #L### _30____________________ Backorder _ Prioridad #L###  Comentario #L#######
 
 Fecha Necesidad: ¿D-MM-Y.YY  Datos externos: _50_____________________________________ 
 Inicio:   ¿D-MM-Y.YY  ________       Insercción: _32________ ¿D-MM-Y.YY  ________ 
 Finaliz:  ¿D-MM-Y.YY  ________       Ult. Modif: _32________ ¿D-MM-Y.YY  ________  
|


TABLA=VDDEMANDACAB
ORDERBY=TO_NUMBER(CODDEMANDA) DESC;

PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CODDEMANDA,NOUPDATE,TOOLTIP("Código de la Cabacera de Demanda")
CAMPO=TIPODEMANDA,NOUPDATE,TOOLTIP("Tipo de Demanda")
CAMPO=DESTIPO,AUXILIAR,NOENTER,TOOLTIP("Descripción del Tipo de Cabecera de Demanda"),POSTCHANGE=FDESIGNACION("+CTIPODEM","")
CAMPO=STATUS,TOOLTIP("Estado de la Cabecera de Demanda"),POSTCHANGE=FDESIGNACION("+CSTATUS","")

CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado de la Cabecera de Demanda")
CAMPO=BACKORDER,NOENTER,TOOLTIP("Backorder de la Cabecera de Demanda")
CAMPO=PRIORI,TOOLTIP("Prioridad de la Cabecera de Demanda")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("Código de Comentario asociado a la Cabecera de Demanda")
CAMPO=FECNEC,NOUPDATE,TOOLTIP("Fecha en la que se programa que se active la demanda, para demandas diferidas")
CAMPO=CLAVEEXT,NOENTER,TOOLTIP("Clave externa que permite relacionar con otros sistemas")
CAMPO=FECINI,NOUPDATE,TOOLTIP("Fecha en la que se reserva por primera vez una línea de esta cabecera de Demanda")
CAMPO=HORAINI,NOUPDATE,TOOLTIP("Hora en la que se reserva por primera vez una línea de esta cabecera de Demanda")
CAMPO=CODOPEINSERT,NOENTER,TOOLTIP("Operario que realizó la insercción de la cabecera de demanda")
CAMPO=FECINSERT,NOENTER,TOOLTIP("Fecha en la que se insertaron los datos del registro")
CAMPO=HORAINSERT,NOENTER,TOOLTIP("Hora en la que se insertaron los datos del registro")
CAMPO=FECFIN,NOUPDATE,TOOLTIP("Fecha en la que se cierra la última línea pendiente de esta cabecera de Demanda")
CAMPO=HORAFIN,NOUPDATE,TOOLTIP("Hora en la que se cierra la última línea pendiente de esta cabecera de Demanda")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CTIPODEM SELECT DESTIPO FROM VDDEMANDATIPO WHERE TIPODEMANDA=:TIPODEMANDA;

CURSOR=CSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='DEC';

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDUMMY SELECT :CODDEMANDA  FROM DUAL WHERE 1=1;


TECLA=SF8,FEJECUTA("!-CDUMMY","¿ ESTA SEGURO DE ANULAR TODA LA DEMANDA ?",
									 FANULADEMCSYNC("FINDEMLANULADAS",":CODDEMANDA",":TIPODEMANDA"),":V10ERROR",
                   FCOMMIT,"",
                   %FFAILURE,"ANULACION REALIZADA") 
                   
             

