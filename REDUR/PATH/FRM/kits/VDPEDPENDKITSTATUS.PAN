# Módulo   : VDPEDPENDKIT.PAN
# Función  : Monitor de pedidos pendientes de kits. Desglose por estados
#
# Creación : 16-12-2022
# Autor    : JAG
###########################################
# Histórico de cambios:
#
ESTADO DE LOS PEDIDOS PENDIENTES
     Estado                                Total  
     @L@@@@ _30___________________________ @L@@@@ 
|

SOLOQUERY
SELECT=SELECT PEC.STATUS,COUNT(PEC.CODPED) TOTAL
         FROM VDPEDIDOCAB PEC
        WHERE PEC.STATUS < VDST.FPECFINALIZADO
		  AND PEDIDOHOST=:CODORDKIT;
GROUPBY=PEC.STATUS;
ORDERBY=PEC.STATUS;


CAMPO=CODORDKIT,AUXILIAR,VIRTUAL,OCULTO 
CAMPO=STATUS,NOENTER,TOOLTIP("Estado del pedido"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS",""),TITULO("Estado"),WLONX=18
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estado del pedido"),TITULO("Descripción")
CAMPO=TOTAL,AUXILIAR,NOENTER,TOOLTIP("Numero total de bultos que estan en este estado"),TITULO("Total"),WLONX=18


CURSOR=CSELDESSTATUS SELECT DESSTATUS
                       FROM VDSTATUS
                      WHERE STATUS = :STATUS AND TIPOSTATUS = 'PEC';

					 
                      