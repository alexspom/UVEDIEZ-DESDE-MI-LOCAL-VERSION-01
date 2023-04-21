# Módulo   : VDPEDPENDKIT.PAN
# Función  : Monitor de pedidos pendientes de kits. Desglose por estados
#
# Creación : 16-12-2022
# Autor    : JAG
###########################################
# Histórico de cambios:
#
PEDIDOS PENDIENTES
 Pedido          Div. Año  Sec.  
 _20____________ _20_ @@@@ @@@
|

SOLOQUERY
SELECT=SELECT PEC.CODPED,PEC.CODDIV,PEC.ANOPED,PEC.SEQPED
         FROM VDPEDIDOCAB PEC
        WHERE PEDIDOHOST=:CODORDKIT
		  AND STATUS=:STATUS;
ORDERBY=PEC.CODPED;


CAMPO=CODPED,NOUPDATE,TOOLTIP("Código del pedido"),TITULO("Cod. del Pedido")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Division o compañia del pedido"),TITULO("Div.")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("Año del pedido"),TITULO("Año")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versión del pedido"),TITULO("Sec."), WLONX=20

CAMPO=CODORDKIT,AUXILIAR,VIRTUAL,OCULTO 
CAMPO=STATUS,AUXILIAR,VIRTUAL,OCULTO


CONTEXTUAL=FEJECUTAFORM("VDPEDIDOS","S","CODPED=:CODPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED AND SEQPED=:SEQPED")


					 
                      