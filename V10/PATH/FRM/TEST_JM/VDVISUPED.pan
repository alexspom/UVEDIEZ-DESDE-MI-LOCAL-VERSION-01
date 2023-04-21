#*****************************************************************
#M�dulo: VDVISUPED.PAN
#Funcionalidad : Visualizacion de pedidos en curso.
#Autor: VEGA Y JOTA      
#Fecha: 05-07-2022
#*****************************************************************
#* Hist�rico de cambios
#* ====================
CABECERA DE PEDIDOS
 Fecha       Hora       Pedido        Cliente       Albaran       Tipo.Ped 							
 �D-MM-Y.YY  ________	_20_________  _20_________  _20_________  _10_________   	
|
TABLA=VDPEDIDOCAB
ORDERBY=CODPED ASC;


CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectu� alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas"),TITULO("Fecha")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectu� alguna modificaci�n. Es utilizado para depuraci�n y control de los registros en las tablas"),TITULO("Hora")
CAMPO=CODPED,NOENTER,VIRTUAL,TOOLTIP("N�mero �nico de pedido"),NOUPDATE
CAMPO=CODCLIENTE,NOENTER,TOOLTIP("N�mero de cliente que realiza el pedido"),NOUPDATE,TITULO("Cod. Cliente")
CAMPO=CODALB,NOENTER,TOOLTIP("N�mero de albaran del pedido"),NOUPDATE,TITULO("Cod. Albaran")
CAMPO=TIPOPEDIDO,NOENTER,TOOLTIP("Tipo Pedido"),NOUPDATE,TITULO("Tipo.Ped")
