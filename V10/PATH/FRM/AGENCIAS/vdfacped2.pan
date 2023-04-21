# Módulo   : VDFACPED.PAN
# Función  : Listado de Facturacion
#
# Creación : 01-10-2007
# Autor    : EAA
#
# Comentarios:
#  Si es un pedido de REPALETIZACION, el pedido original lo marcaremos con 'R' en el 
#  campo REPALETIZACION y con 'S' en REPALETIZACION del pedido nuevo. Los pedidos
#  marcados con 'S' no se facturara la manipulacion ni transporte en SAP. Nos basaremos
#  en el pedido original  ya que facturamos por peso y no por bultos.
# OJO IMPMENVENTA E IMPMENCOSTE SON DE UNA TABLA AUXILIAR
###########################################
DATOS FACTURA
Pedido _20__________ Importe total #L,#####.##  Exento Iva _  Dif. Acep. #L,###.##
Fijo #L,#####.##  Peso  #L,#####.## Bultos #L,#####.## Reexp #L,#####.##
P.O.D. #L,#####.##  Firma #L,###.## Reembolso  #L,###.## Seguro  #L,#####.## Dua  #L,#####.##  
Error _1024_____________________________________________________________
|
   
 
TABLA=DUAL
REGPAG=1

CAMPO=CODPED,AUXILIAR,VIRTUAL,NOENTER,TITULO("Pedido")
CAMPO=PRECTOTAL,AUXILIAR,VIRTUAL,NOENTER,TITULO("Total")
CAMPO=EXENTOIVAC,AUXILIAR,VIRTUAL,NOENTER,TITULO("Exento Iva")
CAMPO=DIFAGENCIA,AUXILIAR,VIRTUAL,NOENTER,TITULO("Diferencia aceptada")
CAMPO=PRECFIJO,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Fijo")
CAMPO=PRECPESO,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Peso")
CAMPO=PRECBULTOS,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Bultos")
CAMPO=PRECREEXP,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Bultos")
CAMPO=PRECSELLAR,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Sellar")
CAMPO=PRECFIRMA,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Firma")
CAMPO=PRECREEMB,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Reemb.")
CAMPO=PRECSEGURO,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Seguro")
CAMPO=PRECDUA,AUXILIAR,VIRTUAL,NOENTER,TITULO("Precio Dua")
CAMPO=MENSAJE,AUXILIAR,VIRTUAL,NOENTER,TITULO("Mensaje")


######################################################################################################
####################### CAMPOS OCULTOS ###############################################################
######################################################################################################

TECLA=SF10,FEJECUTAFORM("VDPEDIDOS","S","CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND SEQPED=:SEQPED","","","","S")

ONLINE=       {F5} Borra pantalla    {F11} Exportar a Excel    {May-F10} Consultar Pedido    {Esc} Salir;