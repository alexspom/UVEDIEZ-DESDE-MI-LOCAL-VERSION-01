# Módulo   : VDMONIBULTOSST.PAN
# Función  : Monitor de bultos pendientes. Desglose por estados
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
ESTADO DE LOS PEDIDOS PENDIENTES EXPEDIR
 Estado                                Total
 @L@@@@ _30___________________________ @L@@@@
|

SOLOQUERY
AQUERY
SELECT=SELECT PEC.STATUS,COUNT(PEC.CODPED) TOTAL
         FROM VDPEDIDOCAB PEC
        WHERE PEC.STATUS BETWEEN VDST.FPECESPFACTURA AND VDST.FPECEXPEDIDO-1;
        
GROUPBY=PEC.STATUS;
ORDERBY=PEC.STATUS DESC;

CAMPO=STATUS,NOENTER,TOOLTIP("Estado del pedido"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS",""),TITULO("Estado"),WLONX=18
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estado del pedido"),TITULO("Descripción")
CAMPO=TOTAL,AUXILIAR,NOENTER,TOOLTIP("Numero total de bultos que estan en este estado"),TITULO("Total")

CURSOR=CSELDESSTATUS SELECT DESSTATUS
                       FROM VDSTATUS
                      WHERE STATUS = :STATUS AND TIPOSTATUS = 'PEC';



