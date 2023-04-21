###################################################################
#Módulo: VDSERIEEXP2.PAN
#Funcionalidad : Mantenimiento de series de expedición
#Autor: FGS      
#Fecha: 03-09-2008
###################################################################
# Histórico de cambios:
DETALLES DE LA SERIE
Pedidos: @L@@@@@ Bultos: @L@@@@ 

Unid   : @@@,@@@ Emb  : @@@,@@@ Cnt: @@@ 

Total Unidades: #L#,###,###

Lanzamiento: _32_____ ¿D-MM-Y.YY ________

Terminación:          ¿D-MM-Y.YY ________ 

Expedición:           ¿D-MM-Y.YY ________

Ult. Modif: _32_____ ¿D-MM-Y.YY ________ 
|

TABLA=VDSERIEEXP

POSTQUERY=FEJECUTA("CCUENTABUL","ERROR OBTENIENDO NUMERO DE BULTOS","CCUENTAPED","","CCUENTAUNID","","CSELDATOS","")


CAMPO=CODSERIEEXP,VIRTUAL,OCULTO
CAMPO=NUMPED,AUXILIAR,NOENTER
CAMPO=BULTOS,AUXILIAR,NOENTER,TOOLTIP("Número total de bultos que componen la serie")
CAMPO=NUMBULUNI,AUXILIAR,NOENTER,TOOLTIP("Número de bultos de unidades aproximados del pedido")
CAMPO=NUMBULEMBA,AUXILIAR,NOENTER,TOOLTIP("Número de bultos de unidades aproximados del pedido")
CAMPO=NUMBULPAL,AUXILIAR,NOENTER,TOOLTIP("Número de bultos de unidades aproximados del pedido")
CAMPO=UNIDADES,AUXILIAR,NOENTER
CAMPO=CODOPELANZA,NOENTER,TOOLTIP("Operario que lanza la serie")
CAMPO=FECLANZA,NOENTER,TOOLTIP("Fecha de lanzamiento de la serie")
CAMPO=HORALANZA,NOENTER,TOOLTIP("Hora de lanzamiento de la serie")
CAMPO=FECTERMIN,NOENTER,TOOLTIP("Fecha de terminación de la serie")
CAMPO=HORATERMIN,NOENTER,TOOLTIP("Hora de terminación de la serie")
CAMPO=FECEXPIDE,TOOLTIP("Fecha de expedición de la serie")
CAMPO=HORAEXPIDE,TOOLTIP("Hora de expedición de la serie")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación a los datos del registro.")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación a los datos del registro.")

CURSOR=CCUENTABUL SELECT COUNT(*) BULTOS
                    FROM VDBULTOCAB BUC,VDPEDIDOCAB PEC
                   WHERE PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND
                         PEC.CODPED=BUC.CODPED AND PEC.SEQPED=BUC.SEQPED AND
                         PEC.CODSERIEEXP=:CODSERIEEXP;

CURSOR=CCUENTAPED SELECT COUNT(*) NUMPED
                    FROM VDPEDIDOCAB PEC
                   WHERE PEC.CODSERIEEXP=:CODSERIEEXP;

CURSOR=CCUENTAUNID SELECT SUM(CANTSERVIDA) UNIDADES FROM VDPEDIDOLIN PEL, VDPEDIDOCAB PEC 
                          WHERE PEC.CODSERIEEXP=:CODSERIEEXP
                          AND PEC.CODDIV=PEL.CODDIV AND PEC.ANOPED=PEL.ANOPED AND
                         PEC.CODPED=PEL.CODPED AND PEC.SEQPED=PEL.SEQPED;
                         

CURSOR=CSELDATOS SELECT SUM(DECODE(TIPOBULTO,'U',1,0)) NUMBULUNI,
                            SUM(DECODE(TIPOBULTO,'E',1,0)) NUMBULEMBA,
                            SUM(DECODE(TIPOBULTO,'C',1,0)) NUMBULPAL
                       FROM VDBULTOCAB BUC,VDPEDIDOCAB PEC
                   WHERE PEC.CODDIV=BUC.CODDIV AND PEC.ANOPED=BUC.ANOPED AND
                         PEC.CODPED=BUC.CODPED AND PEC.SEQPED=BUC.SEQPED AND
                         PEC.CODSERIEEXP=:CODSERIEEXP;

