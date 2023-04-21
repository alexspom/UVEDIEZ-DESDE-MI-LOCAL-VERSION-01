# Módulo   : VDMONIPEDIDOSCAB.PAN
# Función  : Monitor de pedidos pendientes. Cabeceras de pedidos
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
PEDIDOS EN EL ESTADO SELECCIONADO

 Pedido    Tipo Etiq            Cliente    Designacion                  Poblacion           Fecha               Bultos Uni.Emba.Conte. Causa         
 _20______ ____ @@@@ _40__________ _20_____ _40_________________________ _40_________________ ¿D-MM-YY ________ @L@@ @L@@ @L@@ @L@@ _100_____________________________ 
|
TABLA=VDPEDIDOCAB

ORDERBY=FECCOMUNICA,CODPED;

CAMPO=STATUS,VIRTUAL,OCULTO
CAMPO=ANOPED,OCULTO,"@L@@"
CAMPO=CODDIV,NOUPDATE,TOOLTIP("Código de la división del pedido"),TITULO("Div"),OCULTO,"_20___"
CAMPO=CODPED,NOUPDATE,TOOLTIP("Código del pedido"),TITULO("Pedido")
CAMPO=SEQPED,OCULTO,"@@@"
CAMPO=TIPOPEDIDO,NOUPDATE,TOOLTIP("Tipo de pedido"),TITULO("Tipo"),WLONX=5
CAMPO=SECLABEL,TITULO("Etiq"),NOUPDATE,WLONX=10
CAMPO=CODAGE,OCULTO,"_10_",POSTCHANGE=FDESIGNACION("+CSELDESAGE","")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Agencia del pedido"),TITULO("Agencia")
CAMPO=CODCLIENTE,NOUPDATE,TOOLTIP("Código del cliente"),TITULO("Código")
CAMPO=DESCLIENTE,NOUPDATE,TOOLTIP("Descripción del cliente"),TITULO("Descripción")
CAMPO=POBLACION,TITULO("Poblacion"),NOUPDATE,WLONX=20
CAMPO=FECCOMUNICA ,TITULO("Terminación"),WLONX=10,NOUPDATE
CAMPO=HORACOMUNICA ,WLONX=10,NOUPDATE
CAMPO=BULTOS,TITULO("Bultos"),AUXILIAR,NOUPDATE,WLONX=15
CAMPO=NBULUNI,AUXILIAR,NOENTER,TOOLTIP("Numero de bultos de unidades del pedido"),TITULO("Uni."),WLONX=15
CAMPO=NBULEMBA,AUXILIAR,NOENTER,TOOLTIP("Numero de bultos de caja completa del pedido"),TITULO("Caj."),WLONX=15
CAMPO=NBULCONTE,AUXILIAR,NOENTER,TOOLTIP("Numero de bultos de palet completo del pedido"),TITULO("Tar."),WLONX=15
CAMPO=DATOSAGE,TITULO("Causa")

CONTEXTUAL=FEJECUTAFORM("VDPEDIDOS","S","CODPED=:CODPED")

CURSOR=CSELDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE = :CODAGE;

CURSOR=CSELBULTOS SELECT SUM(DECODE(TIPOBULTO,'U',1,0)) NBULUNI,
                         SUM(DECODE(TIPOBULTO,'E',1,0)) NBULEMBA,
                         SUM(DECODE(TIPOBULTO,'C',1,0)) NBULCONTE,
                         COUNT(*) BULTOS 
                    FROM VDBULTOCAB
                   WHERE CODPED=:CODPED;

POSTQUERY=FEJECUTA("CSELBULTOS","No puedo determinar bultos")