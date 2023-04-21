# Modulo   : vdlistadopedidosfiltro.pan
# Funcion  : Seleccion de criterios para busqueda
#
# Creacion : 03/04/2023
# Autor    : infmansu
###########################################
# HistÃ³rico de cambios:
 Busqueda Pedidos 

  Fecha Inicial: ¿D-MM-Y.YY          
  Fecha Final:   ¿D-MM-Y.YY            
|
NOQUERY
NOINSERT
NODELETE

CAMPO=FECHA_D,AUXILIAR,TOOLTIP("Fecha de pedido desde la cual buscar"),COMBOX("CALENDARIO"),TITULO("Fecha Inicial")
CAMPO=FECHA_H,AUXILIAR,TOOLTIP("Fecha de pedido hasta la cual buscar"),COMBOX("CALENDARIO"),TITULO("Fecha Final")

ONLINE={F1} Ayuda  {F4} Aplicar Filtro y refrescar consulta;