###################################################################
#Módulo: VDPEDCAB.PAN
#Funcionalidad : Mantenimiento de cabecera de pedidos
#Autor: RFD      
#Fecha: 24-03-2008
###################################################################
# Histórico de cambios:
DATOS DE ENTREGA, REEXPEDICION Y FACTURACION DEL PEDIDO
 
  Pedido:  _20_________ División: _20__  _40______________  Año:  @@@@  Secuencia: @@@@ 
 
 ÏÄÄ Entrega ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                                                    ³ 
 ³  Cliente: _20_______  _60__________________________________________________ NIF: _30____________                   ³
 ³  Contacto:   _40_________________  Teléfono: ____________ Fax: _12_________ e-mail: _40___________________________ ³
 ³  Dire. EDI:  _40__________________________________                                                                 ³
 ³  Dirección:  _40________________________________  Dirección1: _40________________________________                  ³
 ³  Dirección2: _40________________________________  Dirección3: _40________________________________                  ³
 ³  Población:  _40_________________  País: ____ _30_____________  CP: _____ _40____________ DP: __________           ³
 ³                                                                                                                    ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 ÏÄÄ  Reexpedición ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                                                    ³
 ³  SWTReexpedición: _ Cliente: _20_______  _60________________________________ NIF: _30____________                  ³
 ³  Contacto:  _40_________________  Teléfono: ____________  Fax: _12_________ e-mail: _40___________________________ ³
 ³  Dire. EDI:  _40________________________________                                                                   ³
 ³  Dirección:  _40________________________________  Dirección1: _40________________________________                  ³
 ³  Dirección2: _40________________________________  Dirección3: _40________________________________                  ³
 ³  Población:  _40_________________  País: ____ _30_____________  CP: _____ _40____________ DP: __________           ³
 ³                                                                                                                    ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
 
 ÏÄÄ  Facturación ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  
 ³                                                                                                                    ³ 
 ³  SWTFacturación: _ Cliente: _20_______  _60_________________________________ NIF: _30____________                  ³
 ³  Contacto:  _40_________________  Teléfono: ____________  Fax: _12_________ e-mail: _40___________________________ ³
 ³  Dire. EDI:  _40________________________________                                                                   ³
 ³  Dirección:  _40________________________________  Dirección1: _40________________________________                  ³
 ³  Dirección2: _40________________________________  Dirección3: _40________________________________                  ³
 ³  Población:  _40_________________  País: ____ _30_____________  CP: _____ _40____________ DP: ___________          ³
 ³                                                                                                                    ³
 ÀÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
 
 Estado: @@@@@ _30___________________________    Ultima modificación: _32_______  ¿D-MM-Y.YYY  ________

|


TABLA=VDPEDIDOCAB


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODPED,TOOLTIP("Código del pedido")
CAMPO=CODDIV,TOOLTIP("Division o compañia del pedido"),POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe.")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=ANOPED,TOOLTIP("Año del pedido")
CAMPO=SEQPED,TOOLTIP("Versión del pedido")

CAMPO=CODCLIENTE,TOOLTIP("Es el Código de cliente que realiza el pedido, recibido por el fichero de interfase con el Host.")
CAMPO=DESCLIENTE,TOOLTIP("Designación completa del cliente que realiza el pedido. También recibido en el interfase.")
CAMPO=NIF,TOOLTIP("NIF del cliente")
CAMPO=CONTACTO,TOOLTIP("Dato recibido en el interfase, de libre introducción. Es el posible contacto con el cliente.")
CAMPO=TELEFONO,TOOLTIP("Telefono correspondiente a direccion de envio. Recibido del HOST")
CAMPO=FAX,TOOLTIP("Fax correspondiente a direccion de envio. Recibido del HOST")
CAMPO=EMAIL,TOOLTIP("e-mail correspondiente a direccion de envio. Recibido del HOST")
CAMPO=DIRECCIONEDI,TOOLTIP("Dirección EDI correspondiente a direccion de envio. Recibido del HOST")
CAMPO=DIRECCION,TOOLTIP("Es la dirección del cliente o dirección destino del pedido. Se recibe en el interfase con el Host. Esta descompuesta en cuatro campos de 40 caracteres.")
CAMPO=DIRECCION1,TOOLTIP("Línea 2 de la direccion de envio del pedido")
CAMPO=DIRECCION2,TOOLTIP("Línea 3 de la direccion de envio del pedido")
CAMPO=DIRECCION3,TOOLTIP("Línea 4 de la direccion de envio del pedido")
CAMPO=POBLACION,TOOLTIP("Poblacion destino del pedido. Recibido del HOST")
CAMPO=CODPAIS,TOOLTIP("Pais de envio"),POSTCHANGE=FDESIGNACION("CDESPAIS","País no existe.")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Descripción del país de envio")
CAMPO=CODPROV,TOOLTIP("Código de la provincia de envio. Recibido del HOST."),POSTCHANGE=FDESIGNACION("CDESPROV","Código de provincia no existe.")
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la provincia de envio")
CAMPO=DP,TOOLTIP("Distrito postal de la direccion de envio. Recibido de la interfase.")

CAMPO=SWTREEXP,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de reexpedición son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido ha de reexpedirse una vez en el cliente")
CAMPO=CODCLIREEXP,TOOLTIP("Código del cliente de reexpedición")
CAMPO=DESCLIREEXP,TOOLTIP("Caso de reexpedirse el pedido, contiene el nombre del destinatario de la reexpedición")
CAMPO=NIFREEXP,TOOLTIP("NIF del cliente de reexpedición")
CAMPO=CONTAREEXP,TOOLTIP("Contacto que figura en albarán si hay reexpedición")
CAMPO=TELREEXP,TOOLTIP("Teléfono que figura en albarán si hay reexpedición")
CAMPO=FAXREEXP,TOOLTIP("Fax correspondiente a direccion de reexpedición. Recibido del HOST")
CAMPO=EMAILREEXP,TOOLTIP("email correspondiente a direccion de reexpedición. Recibido del HOST")
CAMPO=DIRECCIONEDIREEXP,TOOLTIP("Dirección EDI correspondiente a direccion de reexpedición. Recibido del HOST")
CAMPO=DIRREEXP,TOOLTIP("Es la dirección de la reexpedición. En cuatro campos")
CAMPO=DIRREEXP1,TOOLTIP("Línea 2 de la dirección que figura en albarán si hay reexpedición")
CAMPO=DIRREEXP2,TOOLTIP("Línea 3 de la dirección que figura en albarán si hay reexpedición")
CAMPO=DIRREEXP3,TOOLTIP("Línea 4 de la dirección que figura en albarán si hay reexpedición")
CAMPO=POBREEXP,TOOLTIP("Población que figura en albarán si hay reexpedición")
CAMPO=CODPAISREEXP,TOOLTIP("País que figura en albarán si hay reexpedición"),POSTCHANGE=FDESIGNACION("CDESPAISREEXP","País no existe.")
CAMPO=DESPAISREEXP,AUXILIAR,NOENTER,TOOLTIP("Descripción del país de reexpedición")
CAMPO=CODPROVREEXP,TOOLTIP("Código de provincia que figura en albarán si hay reexpedición"),POSTCHANGE=FDESIGNACION("CDESPROVREEXP","Código de provincia no existe.")
CAMPO=DESPROVREEXP,AUXILIAR,NOENTER,TOOLTIP("Descripción de la provincia de reexpedición")
CAMPO=DPREEXP,TOOLTIP("Distrito postal que figura en albarán si hay reexpedición")

CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de facturación son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene dirección de facturación")
CAMPO=CODCLIFACTU,TOOLTIP("Código del cliente de la dirección de facturación")
CAMPO=DESCLIFACTU,TOOLTIP("Destinatario de la dirección de facturación")
CAMPO=NIFFACTU,TOOLTIP("NIF del cliente de dirección de facturación")
CAMPO=CONTAFACTU,TOOLTIP("Contacto de la dirección de facturación")
CAMPO=TELFACTU,TOOLTIP("Teléfono de la dirección de facturación")
CAMPO=FAXFACTU,TOOLTIP("Fax correspondiente a direccion de facturación. Recibido del HOST")
CAMPO=EMAILFACTU,TOOLTIP("email correspondiente a direccion de facturación. Recibido del HOST")
CAMPO=DIRECCIONEDIFACTU,TOOLTIP("Dirección EDI correspondiente a direccion de facturación. Recibido del HOST")
CAMPO=DIRFACTU,TOOLTIP("Es la dirección de la facturación. En cuatro campos")
CAMPO=DIRFACTU1,TOOLTIP("Línea 2 de la dirección de facturación")
CAMPO=DIRFACTU2,TOOLTIP("Línea 3 de la dirección de facturación")
CAMPO=DIRFACTU3,TOOLTIP("Línea 4 de la dirección de facturación")
CAMPO=POBFACTU,TOOLTIP("Población de la dirección de facturación")
CAMPO=CODPAISFACTU,TOOLTIP("País de la dirección de facturación"),POSTCHANGE=FDESIGNACION("CDESPAISFACTU","País no existe.")
CAMPO=DESPAISFACTU,AUXILIAR,NOENTER,TOOLTIP("Descripción del país de facturación")
CAMPO=CODPROVFACTU,TOOLTIP("Código de provincia de la dirección de facturación"),POSTCHANGE=FDESIGNACION("CDESPROVFACTU","Código de provincia no existe.")
CAMPO=DESPROVFACTU,AUXILIAR,NOENTER,TOOLTIP("Descripción de la provincia de facturación")
CAMPO=DPFACTU,TOOLTIP("Distrito postal de la dirección de facturación")
CAMPO=STATUS,TOOLTIP("Es el estado en que se encuentra el pedido en el momento de la consulta."),POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado incorrecto."),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado en el que se encuentra el pedido")

CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")

CAMPO=ALBARAN,AUXILIAR,OCULTO,"_20_"
CAMPO=RUTA,AUXILIAR,OCULTO,"_256_"

CURSOR=CLISTASTATUS SELECT STATUS,DESSTATUS,TIPOSTATUS FROM VDSTATUS WHERE TIPOSTATUS='PEC' ORDER BY STATUS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESPROV SELECT DESPROV
                  FROM VDPROVI
                 WHERE CODPROV=:CODPROV AND CODPAIS=:CODPAIS
                 UNION ALL
                 SELECT '' DESPROV
                 FROM DUAL WHERE :CODPROV IS NULL;
CURSOR=CDESPROVREEXP SELECT DESPROV DESPROVREEXP
                  FROM VDPROVI
                 WHERE CODPROV=:CODPROVREEXP AND CODPAIS=:CODPAISREEXP
                 UNION ALL
                 SELECT '' DESPROVREEXP
                 FROM DUAL WHERE :CODPROVREEXP IS NULL;
CURSOR=CDESPROVFACTU SELECT DESPROV DESPROVFACTU
                  FROM VDPROVI
                 WHERE CODPROV=:CODPROVFACTU AND CODPAIS=:CODPAISFACTU
                 UNION ALL
                 SELECT '' DESPROVFACTU
                 FROM DUAL WHERE :CODPROVFACTU IS NULL;

CURSOR=CDESPAIS SELECT DESPAIS FROM VDPAIS WHERE CODPAIS=:CODPAIS 
                     UNION ALL
                     SELECT '' DESPAIS  FROM DUAL WHERE :CODPAIS IS NULL;
CURSOR=CDESPAISREEXP SELECT DESPAIS DESPAISREEXP FROM VDPAIS WHERE CODPAIS=:CODPAISREEXP 
                     UNION ALL
                     SELECT '' DESPAISREEXP  FROM DUAL WHERE :CODPAISREEXP IS NULL;
CURSOR=CDESPAISFACTU SELECT DESPAIS DESPAISFACTU FROM VDPAIS WHERE CODPAIS=:CODPAISFACTU
                     UNION ALL
                     SELECT '' DESPAISFACTU  FROM DUAL WHERE :CODPAISFACTU IS NULL;

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;
CURSOR=CDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE
                UNION
               SELECT '' DESAGE FROM VDAGENCIA WHERE :CODAGE IS NULL;

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='PEC';

#Se selecciona así el albarán hasta que el sufijodoc se incluya en vdpedidocaborig y se pueda cargar por interfase
CURSOR=CSELALBARAN SELECT CASE WHEN :TIPOPEDIDO IN ('VP', 'P2') THEN
                                    '$(VDALBARAN)'
                               WHEN :TIPOPEDIDO ='PX' THEN
                                    'ALBARAN DE ENVIO POR CANJE'
                               WHEN :TIPOPEDIDO ='PA' THEN
                                    'ALBARAN DE ENVIO ALMACENES PULMON'
                          END ALBARAN, 'C:\ALBARAN_'||:CODPED||'.PDF' RUTA
                     FROM DUAL
                     WHERE :TIPOPEDIDO IN ('VP', 'P2','PX','PA');


TECLA=F10,FEJECUTA("CSELALBARAN", "ERROR OBTENIENDO EL ALBARAN",
                   FIMPRIMEPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED",":ALBARAN","FORMCODDIV=:CODDIV;FORMANOPED=:ANOPED;FORMCODPED=:CODPED;FORMSEQPED=:SEQPED",""),":V10ERROR")

TECLA=F11,FEJECUTA("CSELALBARAN", "ERROR OBTENIENDO EL ALBARAN",
                   FEXPORTAPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED",":ALBARAN","FORMCODDIV=:CODDIV;FORMANOPED=:ANOPED;FORMCODPED=:CODPED;FORMSEQPED=:SEQPED",":RUTA","1"),":V10ERROR")


