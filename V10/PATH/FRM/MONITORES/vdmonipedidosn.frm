# MOdulo   : VDMONIPEDIDOS.FRM
# Función  : Monitor de pedidos pendientes
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# HistOrico de cambios:
#
BEGINBLOQUE=VDMONIPEDIDOSN.PAN
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSY=1
  REGPAG=5
  WLONX=345
  WLONY=85
  TIMEOUT=QUERYAUTOM,3000
  NOINSERT
  NODELETE
  NOUPDATE
  NOLOCK
ENDBLOQUE
BEGINBLOQUE=VDMONIPEDIDOSCABN.PAN
   PADRE=VDMONIPEDIDOSN.PAN
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSY=9
  REGPAG=37
  WLONX=1200
  WLONY=555
  NOINSERT
  NODELETE
ENDBLOQUE
