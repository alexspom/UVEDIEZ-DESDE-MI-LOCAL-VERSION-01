###################################################################
#M�dulo: VDCLIENTESRUTA.PAN
#Funcionalidad : Clientes pertenecientes a una ruta
###################################################################
# Hist�rico de cambios:
CLIENTES PERTENECIENTES A LA RUTA
 Divis. Cliente              Descripci�n                        Direcci�n                      Poblaci�n            DP
 _20___ _20_________________ _40_______________________________ _40___________________________ _40_________________ _10____
|  

REGPAG=20

NOCOMMIT

TABLA=VDCLIENTES
ORDERBY=CODCLIENTE;

CAMPO=CODRUTA,VIRTUAL,OCULTO

CAMPO=CODDIV,NOUPDATE,TOOLTIP("Division o compa�ia del pedido"),TITULO("Divis.")
CAMPO=CODCLIENTE,NOUPDATE,TOOLTIP("Es el C�digo de cliente que realiza el pedido"),TITULO("Cliente")
CAMPO=DESCLIENTE,TOOLTIP("Designaci�n completa del cliente que realiza el pedido"),TITULO("Descripcion")
CAMPO=DIRECCION,TOOLTIP("Es la direcci�n del cliente o direcci�n destino del pedido"),TITULO("Direccion")
CAMPO=POBLACION,TOOLTIP("Poblaci�n destino del pedido. Recibido del HOST"),TITULO("Poblacion")
CAMPO=DP,TOOLTIP("Distrito postal de la direcci�n de envio. Recibido de la interfase"),TITULO("DP")


CURSOR=CUPDCLIENTERUTA UPDATE VDCLIENTES SET CODRUTA=:CODRUTA WHERE CODDIV=:CODDIV AND CODCLIENTE=:CODCLIENTE;


CONTEXTUAL=FEJECUTAFORM("VDCLIENTES","N","","","CODDIV=:CODDIV CODCLIENTE=:CODCLIENTE DESCLIENTE=:DESCLIENTE DIRECCION=:DIRECCION POBLACION=:POBLACION DP=:DP")

TECLA=F4,FEJECUTA("CUPDCLIENTERUTA","ERROR ACTUALIZANDO RUTA EN CLIENTE",%FFAILURE,"CLIENTE ACTUALIZADO A RUTA",FCOMMIT,"")