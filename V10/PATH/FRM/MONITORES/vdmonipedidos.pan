# Módulo   : VDMONIBULTOSST.PAN
# Función  : Monitor de bultos pendientes. Desglose por estados
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
ESTADO DE LOS PEDIDOS PENDIENTES
 Estado                                Total  Lineas
 @L@@@@ _30___________________________ @L@@@@ @L@@@@
|

SOLOQUERY
SELECT=SELECT PEC.STATUS,COUNT(PEC.CODPED) TOTAL
         FROM VDPEDIDOCAB PEC
        WHERE PEC.STATUS < VDST.FPECEXPEDIDO AND
              VD.CONTIENECAD(:RANDIV,PEC.CODDIV) = 1 AND
              VD.CONTIENECAD(:RANAGE,PEC.CODAGE) = 1 AND
              VD.CONTIENENUM(:RANSERIEEXP,PEC.CODSERIEEXP) = 1;
GROUPBY=PEC.STATUS;
ORDERBY=PEC.STATUS;

CAMPO=STATUS,NOENTER,TOOLTIP("Estado del pedido"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS","","CSELTOTAL",""),TITULO("Estado"),WLONX=18
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estado del pedido"),TITULO("Descripción")
CAMPO=TOTAL,AUXILIAR,NOENTER,TOOLTIP("Numero total de bultos que estan en este estado"),TITULO("Total"),WLONX=18
CAMPO=LINEAS,AUXILIAR,NOENTER,TITULO("Lineas")

CURSOR=CSELDESSTATUS SELECT DESSTATUS
                       FROM VDSTATUS
                      WHERE STATUS = :STATUS AND TIPOSTATUS = 'PEC';
                      
CURSOR=CSELTOTAL SELECT COUNT(*) LINEAS
                  FROM VDPEDIDOLIN PEL,VDPEDIDOCAB PEC
                  WHERE PEL.CODPED=PEC.CODPED AND PEL.CODDIV=PEC.CODDIV AND PEL.ANOPED=PEC.ANOPED AND PEL.SEQPED=PEC.SEQPED AND PEC.STATUS=:STATUS;                  



