# M�dulo   : vdresumenseriefiltro.pan
# Funci�n  : Selecci�n de criterios para b�squeda
#
# Creaci�n : 03/04/2023
# Autor    : infmansu
###########################################
# Hist�rico de cambios:
 Busqueda Pedidos Preparados 

  Fecha Inicial: �D-MM-Y.YY          
  Fecha Final:   �D-MM-Y.YY            
|
NOQUERY
NOINSERT
NODELETE

CAMPO=FECHA_D,AUXILIAR,TOOLTIP("Fecha de pedido desde la cual buscar"),COMBOX("CALENDARIO"),TITULO("Fecha Inicial")
CAMPO=FECHA_H,AUXILIAR,TOOLTIP("Fecha de pedido hasta la cual buscar"),COMBOX("CALENDARIO"),TITULO("Fecha Final")

ONLINE={F1} Ayuda  {F4} Aplicar Filtro y refrescar consulta;