# Módulo   : VDIMPRESPOOLDET.PAN
# Función  : Mantenimiento de Spool de Impresión V10. Detallado
#
# Creación : 13-05-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
DETALLES DE SPOOL DE IMPRESION V10

 Secuencia:  #L#######     Ordenador: _32___________   Tipo Imp.:  ____________   Impresora:  _______________
 
  Fichero: _256________________________________________  Documento: _256______________________________________________
 
 Parámetros: _1024_____________________________________________________________________________________________________
 
 Estado: @L@@@@ _30_________________   Número de Copias: #L###      Comentario: #L#######

 Inserción:  __32_________ ¿D-MM-Y.YY ________    Planificado: ¿D-MM-Y.YY ________ Vdextra: _255___________                 
 
 Ult. Modificación: __32_________ ¿D-MM-Y.YY ________    Impreso:     ¿D-MM-Y.YY ________  
|

TABLA=VDIMPRESPOOL
ORDERBY=SEQIMPRE DESC;
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=SEQIMPRE,VIRTUAL,NOENTER,TOOLTIP("Número de Secuencia de la Impresión")
CAMPO=ORDENADOR,TOOLTIP("Ordenador desde el que se insertó en el spool")
CAMPO=TIPOIMPRE,TOOLTIP("Tipo de impresión")
CAMPO=CODIMPRE,TOOLTIP("Impresora V10 en la que se imprime")
CAMPO=FICHERO,TOOLTIP("Fichero al que se exporta la impresión")
CAMPO=DOCUMENTO,TOOLTIP("Documento que se imprime")
CAMPO=PARAMS,TOOLTIP("Parámetros de la impresión; valores a bidear, where, .... ")
CAMPO=STATUS,TOOLTIP("Estado de la impresión en la cola"),POSTCHANGE=FDESIGNACION("+CDESSTATUS","")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=NUMCOPIAS,TOOLTIP("Número de Copias a Imprimir")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("Código del comentario asociado a la impresión spool")
CAMPO=CODOPEINS,NOENTER,TOOLTIP("Usuario que insertó la impresión en el spool")
CAMPO=FECINS,NOENTER,TOOLTIP("Fecha de insercción de la impresión en el spool")
CAMPO=HORAINS,NOENTER,TOOLTIP("Hora de insercción de la impresión en el spool")
CAMPO=FECPLANIF,TOOLTIP("Fecha prevista de impresión")
CAMPO=HORAPLANIF,TOOLTIP("Hora prevista de impresión")
CAMPO=VDEXTRA
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en la que se realizó la Ultima modificación")
CAMPO=FECIMP,NOENTER,TOOLTIP("Fecha en la que fue impreso correctamente")
CAMPO=HORAIMP,NOENTER,TOOLTIP("Hora en la que fue impreso correctamente")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='ISP' AND STATUS=:STATUS;


