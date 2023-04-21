#Módulo: VDCLIENTESRES.FRM
#Funcionalidad : Resumen del maestro de clientes
#Autor: JMM
#Fecha: 06-10-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
MANTENIMIENTO DE CLIENTES

 Cliente:_20_________________ _60___________________________ @@@ 
 Tipo:   _5___  _40_________________  NIF: _30___________
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ENVIO ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Dirección: _40___________________________  _40___________________________               ³
 ³            _40___________________________  _40___________________________               ³
 ³ Población: _40_________________ DP: _10____        Provincia: _5_ _40__________________ ³
 ³ País: _5_ _30_________________  Contacto: _40_____________________________________      ³
 ³ Teléfono: _12_______            Fax: _12______     Email: _40__________________________ ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ FACTURA ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ FACTURA _                                                                               ³ 
 ³ Cliente Fact: _20_________________ _60____________________________ NIF: _30___________  ³
 ³ Dirección: _40___________________________  _40___________________________               ³
 ³            _40___________________________  _40___________________________               ³
 ³ Población: _40_________________ DP: _10____        Provincia: _5_ _40__________________ ³
 ³ País: _5_ _30_________________  Contacto: _40_____________________________________      ³
 ³ Teléfono: _12_______            Fax: _12______     Email: _40__________________________ ³
 ³ Serie: _7_____  Forma Pago: ____ _40_____________________________________               ³
 ³                                                                                         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
| 

TABLA=VDCLIENTES

NOINSERT                                 
NODELETE
NOUPDATE

POSX=10
POSY=2

CAMPO=CODCLIENTE,TOOLTIP("Código de cliente."),POSTCHANGE=FVALNOCERO("EL CAMPO Código DE CLIENTE\nNO PUEDE ESTAR VACIO")
CAMPO=DESCLIENTE,UPPER,TOOLTIP("Nombre del cliente."),POSTCHANGE=FVALNOCERO("EL CAMPO DESCRIPCION DEL CLIENTE\nNO PUEDE ESTAR VACIO")
CAMPO=SEQCODCLI,TOOLTIP("Secuencial del Código de Cliente, para los casos de múltiples direcciones para el cliente.")
CAMPO=TIPOCLI,TOOLTIP("Tipo de cliente sobre una clasificación."),POSTCHANGE=FDESIGNACION("CDESTIPOCLI","EL CAMPO TIPO DE CLIENTE DEBE DE EXISTIR",FPOSICIONACAMPO(FSUCCESS,"SEQCODCLI"),"")
CAMPO=DESCTIPOCLI,UPPER,AUXILIAR,NOENTER
CAMPO=NIF,UPPER,TOOLTIP("NIF/CIF del cliente.")
CAMPO=DIRECCION,TOOLTIP("Es la dirección del cliente o dirección destino del pedido. Se recibe en el interfase con el Host. Está descompuesta en cuatro campos de 40 caracteres")
CAMPO=DIRECCION1,TOOLTIP("Línea 2 de la dirección de envio del pedido")
CAMPO=DIRECCION2,TOOLTIP("Línea 3 de la dirección de envio del pedido")
CAMPO=DIRECCION3,TOOLTIP("Línea 4 de la dirección de envio del pedido")
CAMPO=POBLACION,TOOLTIP("Población destino del pedido. Recibido del HOST")
CAMPO=DP,TOOLTIP("Distrito postal de la dirección de envio. Recibido de la interfase")
CAMPO=CODPROV,TOOLTIP("Código de la provincia de envio. Recibido del HOST"),POSTCHANGE=FDESIGNACION("+CSELDESPROVDEST","")
CAMPO=DESPROVDEST,AUXILIAR,NOENTER
CAMPO=CODPAIS,TOOLTIP("País de envío"),POSTCHANGE=FDESIGNACION("+CSELPAISDEST","")
CAMPO=DESPAISDEST,AUXILIAR,NOENTER
CAMPO=CONTACTO,TOOLTIP("Dato recibido en el interfase, de libre introducción. Es el posible contacto con el cliente")
CAMPO=TELEFONO,TOOLTIP("Teléfono correspondiente a dirección de envio. Recibido del HOST")
CAMPO=FAX,TOOLTIP("Número de fax del cliente")
CAMPO=EMAIL,TOOLTIP("Direccion email correspondiente a dirección de envio. Recibido del HOST")

CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de facturación son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene dirección de facturación")
CAMPO=CODCLIFACTU,TOOLTIP("Código del cliente de la dirección de facturación")
CAMPO=DESCLIFACTU,TOOLTIP("Descripción del cliente de facturación")
CAMPO=NIFFACTU,TOOLTIP("NIF del cliente de dirección de facturación")
CAMPO=DIRFACTU,TOOLTIP("Es la dirección de facturacion del pedido. Esta descompuesta en cuatro campos de 40 caracteres.")
CAMPO=DIRFACTU1,TOOLTIP("Línea 2 de la direccion de facturacion del pedido")
CAMPO=DIRFACTU2,TOOLTIP("Línea 3 de la direccion de facturacion del pedido")
CAMPO=DIRFACTU3,TOOLTIP("Línea 4 de la direccion de facturacion del pedido")
CAMPO=POBFACTU,TOOLTIP("Población de facturación del pedido. Recibido del HOST")
CAMPO=DPFACTU,TOOLTIP("Distrito postal de la dirección de facturación. Recibido de la interfase")
CAMPO=CODPROVFACTU,TOOLTIP("Código de la provincia de facturación. Recibido del HOST"),POSTCHANGE=FDESIGNACION("+CSELDESPROVFACT","")
CAMPO=DESPROVFACTU,AUXILIAR,NOENTER
CAMPO=CODPAISFACTU,TOOLTIP("País de facturación"),POSTCHANGE=FDESIGNACION("+CSELPAISFACT","")
CAMPO=DESPAISFACT,AUXILIAR,NOENTER
CAMPO=CONTAFACTU,TOOLTIP("Contacto de facturación")
CAMPO=TELFACTU,TOOLTIP("Telefono correspondiente a direccion de facturacion.")
CAMPO=FAXFACTU,TOOLTIP("Fax correspondiente a direccion de facturacion.")
CAMPO=EMAILFACTU,TOOLTIP("Email correspondiente a direccion de facturación.")
CAMPO=SERIEFACTURA,TOOLTIP("Serie de facturación aplicable a los pedidos del cliente.")
CAMPO=TIPOFORMAPAGO,TOOLTIP("Tipo de Forma de pago. Determina la forma en la que el cliente realizará el pago de sus pedidos."),POSTCHANGE=FDESIGNACION("+CSELDESTIPOPAGO","")
CAMPO=DESCTIPOFORMAPAGO,AUXILIAR,NOENTER

CURSOR=CDESTIPOCLI SELECT DESCTIPOCLI 
                     FROM VDTIPOCLIENTE 
                    WHERE TIPOCLI=:TIPOCLI;

CURSOR=CSELDESPROVDEST SELECT DESPROV DESPROVDEST
                         FROM VDPROVI 
                        WHERE CODPROV = :CODPROV AND CODPAIS = :CODPAIS;

CURSOR=CSELDESPROVFACT SELECT DESPROV DESPROVFACTU
                         FROM VDPROVI 
                        WHERE CODPROV = :CODPROVFACTU AND CODPAIS = :CODPAISFACTU;

CURSOR=CSELPAISDEST SELECT DESPAIS DESPAISDEST
                      FROM VDPAIS
                     WHERE CODPAIS = :CODPAIS;
                     
CURSOR=CSELPAISFACT SELECT DESPAIS DESPAISFACT
                      FROM VDPAIS
                     WHERE CODPAIS = :CODPAISFACTU;

CURSOR=CSELDESTIPOPAGO SELECT DESCTIPOFORMAPAGO FROM VDTIPOFORMAPAGO WHERE TIPOFORMAPAGO =:TIPOFORMAPAGO;

AYUDA=MANTENIMIENTO DE CLIENTES
ONLINE=     {F1} Ayuda {F2} Consulta {F5} Borrar pantalla {Esc} Salir;