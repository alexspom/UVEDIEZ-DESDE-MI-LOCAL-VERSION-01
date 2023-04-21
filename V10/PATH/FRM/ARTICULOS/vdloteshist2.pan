# Módulo   : VDLOTESHIST2.PAN
# Función  : Detalles del Histórico de cambios de propiedades de lotes
#
# Creación : 01-07-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
DETALLES DEL HISTORICO DE CAMBIOS DE CALIFICACIONES DE LOTES
Artículo: _40________________ _100___________________________
Lote:     _40________________          
                                                  Código Documento: #L#######
Caducidad de ________ a ________                  Insercción:       _32________ ¿D-MM-Y.YY  ________
Retest de    ________ a ________                  Mod/Acción Ins:   _32________________ _64___________________________
Bloqueos de  __________ a __________              Procesamiento:    ¿D-MM-Y.YY  ________
Estado       #L### _30_________________________   Mod/Acción Proc:  _32________________ _64___________________________

Extra: _255__________________________________________________  Ult. Modif: _32________ ¿D-MM-Y.YY  ________  
|

TABLA=VDLOTESHIST

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")


CAMPO=SEQ,VIRTUAL,OCULTO
CAMPO=CODART,TOOLTIP("Código del artículo"),NOUPDATE,POSTCHANGE=FDESIGNACION("CSELDESART","No existe artículo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designación del artículo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote")
CAMPO=CODDOCUMENTO,NOENTER,TOOLTIP("Código del documento que relacciona sus movtos")
CAMPO=CADUCIACTUAL,NOENTER,TOOLTIP("Caducidad Actual en formato AAAAMMDD")
CAMPO=CADUCINUEVO,TOOLTIP("Nueva Caducidad en formato AAAAMMDD")
CAMPO=CODOPEINS,NOENTER,TOOLTIP("Operario que insertó el registro")
CAMPO=FECINS,NOENTER,TOOLTIP("Fecha en la que se insertó el registro")
CAMPO=HORAINS,NOENTER,TOOLTIP("Hora en la que se insertó el registro")
CAMPO=RETESTACTUAL,NOENTER,TOOLTIP("Fecha Actual de retest del lote en formato AAAAMMDD")
CAMPO=RETESTNUEVO,TOOLTIP("Nueva Fecha de retest del lote en formato AAAAMMDD")
CAMPO=MODULOINS,NOENTER,TOOLTIP("Módulo desde el que se insertó el registro")
CAMPO=ACCIONINS,NOENTER,TOOLTIP("Acción en la que se insertó el registro")
CAMPO=BLOQLOTEACTUAL,NOENTER,TOOLTIP("Bloqueos actuales del lote")
CAMPO=BLOQLOTENUEVO,TOOLTIP("Nuevos Bloqueos del lote")
CAMPO=FECFIN,NOENTER,TOOLTIP("Fecha en la que se procesó el registro")
CAMPO=HORAFIN,NOENTER,TOOLTIP("Hora en la que se procesó el registro")
CAMPO=STATUS,POSTCHANGE=FDESIGNACION("CSELSTATUS","ERROR EN CSELSTATUS"),TOOLTIP("Estado del cambio de propiedades del lote")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado")
CAMPO=MODULOFIN,NOENTER,TOOLTIP("Módulo desde el que se procesó el registro")
CAMPO=ACCIONFIN,NOENTER,TOOLTIP("Acción desde la que se procesó el registro")
CAMPO=VDEXTRA,TOOLTIP("Información adiccional del usuario")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='LOH';



