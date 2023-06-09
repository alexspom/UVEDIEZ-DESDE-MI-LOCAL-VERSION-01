######################################################################
#M�dulo: VDPEDORIGCAB.PAN
#Funcionalidad : Consulta de cabecera de pedidos originales
#Autor: RFD      
#Fecha: 24-03-2008
######################################################################
# Hist�rico de cambios:
CABECERA DE PEDIDO ORIGINALES 
 Pedido: _20_______________ Divisi�n: _20__  _40______________ A�o: @L@@ Seqped @L@ N� l�neas: @@@@ 
 ��� Datos b�sicos ���������������������������������������������������������������������������������������������������������
 � Tipo Pedido: __________  Ped. Host: _60__________  Ped. Cliente: _60__________ Su Ped.:_60__________ Fecha: �D-MM-Y.YY  � 
 � Mensaje Host:  _255_____________________________________________________________________________________________________�
 � Datos extra:   _255_____________________________________________________________________________________________________�
 ���������������������������������������������������������������������������������������������������������������������������
 ��� Datos y direcciones ���������������������������������������������������������������������������������������������������
 �  Cliente: _20_______  _60__________________________________________________ NIF: _30____________                        �
 �  Contacto:   _40_________________  Tipo Cliente: _____      Tel�fono: ____________ Fax: _12_________                    �
 �  e-mail: _40___________________________      Dire. EDI:  _40__________________________________                          �
 �  Direcci�n:  _40________________________________  Direcci�n1: _40________________________________                       �
 �  Direcci�n2: _40________________________________  Direcci�n3: _40________________________________                       �
 �  Poblaci�n:  _40_________________  Pa�s: ____ _30_____________  Provincia: _____ _40____________ DP: __________         �
 �   SWTReexpedici�n: _  Cliente: _20___________  _60________________________________________________ NIF: _30____________ �  
 �   SWTFacturaci�n:  _  Cliente: _20___________  _60________________________________________________ NIF: _30____________ �
 ���������������������������������������������������������������������������������������������������������������������������
 ��� Documentaci�n �����������������   ���� Preparaci�n ���������������������������   �� Facturaci�n �����������������������
 � Idioma documentos: __________   �   �                                          �   �                                    � 
 � Packing list: _                 �   �  % Verificaci�n: ###.##                  �   �  Moneda:   __________              �
 � Albar�n:                        �   �  Colec. Volumetr�as: _10_______          �   �  Descuento: ###.##  _40__________  �
 �  N�Albaranes: @@@               �   �   Prioridad: @@  Urgencia: @@            �   �  Recargo:   ###.##  _40__________  �
 �  Valorado: _    Proforma: _     �   �   Backorder: _   Area Exped.: _20_______ �   �  Cond. de Pago: _80________________�
 �  Exterior: _    Sellado:  _     �   �                                          �   �                                    �
 �  Totales:  _                    �   �  Monopedido:       _  Paletizar:  _      �   �  Agrupar: _                        � 
 �  Modelo:   _                    �   �   N�merosSerie:    _  Miscelaneo: _      �   ������������������������������������ĳ
 �  Referencia: _80________________�   �   Anular Precinto: _                     �   � Interfaz:                          �
 � Etiquetas:                      �   �   Bloquear Exped.: _                     �   �   Comunicar: _  Fax: _             �
 �  Idioma Etiqueta: __________    �   �                                          �   �        Mail: _  Aviso Exp.: _      �
 �  ECI: _  No CajasComp: _        �   �                                          �   �                                    �
 �����������������������������������   ��������������������������������������������   ��������������������������������������
 ��� Transporte ������������������������������������������������������������������������������������������������������������
 �  Agencia: __________ _30______________________ Tracking: _20____________   Seg.: _ Tipo _ Base #L###.### Dif #L###.##   �
 �  Datos Adicionales: _80_____________________________________  Reembolso: _   Aduana: _     Portes: _  Recargo: @@@@@@@  �
 ��������������������������������������������������������������������������������������������������������������������������� 
 �� Seguimiento ������������������������������������������������������������������������������������������������������������ 
 � Captura:   �D-MM-Y.YY  ________    Servicio:  �D-MM-Y.YY            Grabaci�n: _32_______ �D-MM-Y.YY  ________          �
 � Recepci�n: �D-MM-Y.YY  ________    Terminado: �D-MM-Y.YY  ________                                                      �
 ���������������������������������������������������������������������������������������������������������������������������
  Estado: @@@@@  _30____________________________ Ultima modificaci�n: _32_______ �D-MM-Y.YY  ________ Comentario: @@@@@@@@@ 
|


TABLA=VDPEDIDORIGCAB
ORDERBY=FECMODIF DESC,HORAMODIF DESC;

NOINSERT 

PROTECT("SUPERVISOR")

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")


CAMPO=CODPED,TOOLTIP("C�digo del pedido"),CONTEXTUAL=FEJECUTAFORM("VDPEDIDOS","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED","","","","S"),TOOLTIP("C�digo del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=CODDIV,TOOLTIP("Division o compa�ia del pedido"),POSTCHANGE=FDESIGNACION("CDESDIV","C�digo de divisi�n no existe.","+CSELTIPCLI",""),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la divisi�n o compa��a del pedido")
CAMPO=ANOPED,TOOLTIP("A�o del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=SEQPED
CAMPO=NLINEAS,TOOLTIP("Es el n�mero original de l�neas del pedido que se recibio del host. Este n�mero no se modifica por los desgloses de lote ni en las nuevas versiones de pedidos.")
CAMPO=TIPOPEDIDO,TOOLTIP("Identifica el tipo del pedido seg�n criterio de la compa��a. Es recibido del Host y tal como se recibe se introduce en la Base de datos. Tiene utilidad para establecer restricciones a la hora de crear series de pedidos.")
CAMPO=PEDIDOHOST,TOOLTIP("C�digo interno del pedido para el HOST")
CAMPO=PEDIDOCLIENTE,TOOLTIP("C�digo interno del pedido para el cliente")
CAMPO=REFERENCIACLI,UPPER
CAMPO=FECPEDIDOCLIENTE,TOOLTIP("Fecha en la que el cliente realiz� el pedido")
CAMPO=MENHOST,TOOLTIP("Contiene cualquier mensaje que el Host de la compa��a considere oportuno. Va dirigido al personal de la compa��a, por tanto, es de uso interno y no es impreso en documento alguno.")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a VD y �tiles para el cliente")

CAMPO=CODCLIENTE,TOOLTIP("Es el C�digo de cliente que realiza el pedido, recibido por el fichero de interfase con el Host.")
CAMPO=DESCLIENTE,TOOLTIP("Designaci�n completa del cliente que realiza el pedido. Tambi�n recibido en el interfase.")
CAMPO=NIF,TOOLTIP("NIF del cliente")
CAMPO=CONTACTO,TOOLTIP("Dato recibido en el interfase, de libre introducci�n. Es el posible contacto con el cliente.")
CAMPO=TIPOCLI,AUXILIAR,UPPER,NOENTER,TITULO("TipoCli"),WLONX=20
CAMPO=TELEFONO,TOOLTIP("Telefono correspondiente a direccion de envio. Recibido del HOST")
CAMPO=FAX,TOOLTIP("Fax correspondiente a direccion de envio. Recibido del HOST")
CAMPO=DIRECCIONEDI,TOOLTIP("Direcci�n EDI correspondiente a direccion de envio. Recibido del HOST")
CAMPO=EMAIL,TOOLTIP("e-mail correspondiente a direccion de envio. Recibido del HOST")
CAMPO=DIRECCION,TOOLTIP("Es la direcci�n del cliente o direcci�n destino del pedido. Se recibe en el interfase con el Host. Esta descompuesta en cuatro campos de 40 caracteres.")
CAMPO=DIRECCION1,TOOLTIP("L�nea 2 de la direccion de envio del pedido")
CAMPO=DIRECCION2,TOOLTIP("L�nea 3 de la direccion de envio del pedido")
CAMPO=DIRECCION3,TOOLTIP("L�nea 4 de la direccion de envio del pedido")
CAMPO=POBLACION,TOOLTIP("Poblacion destino del pedido. Recibido del HOST")
CAMPO=CODPAIS,TOOLTIP("Pais de envio"),POSTCHANGE=FDESIGNACION("CDESPAIS","Pa�s no existe.")
CAMPO=DESPAIS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del pa�s de envio")
CAMPO=CODPROV,TOOLTIP("C�digo de la provincia de envio. Recibido del HOST."),POSTCHANGE=FDESIGNACION("CDESPROV","C�digo de provincia no existe.")
CAMPO=DESPROV,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la provincia de envio")
CAMPO=DP,TOOLTIP("Distrito postal de la direccion de envio. Recibido de la interfase.")

CAMPO=SWTREEXP,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de reexpedici�n son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido ha de reexpedirse una vez en el cliente"),CHECKBOX("N","S")
CAMPO=CODCLIREEXP,TOOLTIP("C�digo del cliente de reexpedici�n"),CONTEXTUAL=FEJECUTAFORM("VDPEDCABDET","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED","","","","S"),INCLUDECSS="background-color:#F7BE81;border-style:ridge;"
CAMPO=DESCLIREEXP,TOOLTIP("Caso de reexpedirse el pedido, contiene el nombre del destinatario de la reexpedici�n")
CAMPO=NIFREEXP,TOOLTIP("NIF del cliente de reexpedici�n")
CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de facturaci�n son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene direcci�n de facturaci�n"),CHECKBOX("N","S")
CAMPO=CODCLIFACTU,TOOLTIP("C�digo del cliente de la direcci�n de facturaci�n"),CONTEXTUAL=FEJECUTAFORM("VDPEDCABDET","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED","","","","S"),INCLUDECSS="background-color:#F7BE81;border-style:ridge;"
CAMPO=DESCLIFACTU,TOOLTIP("Destinatario de la direcci�n de facturaci�n")
CAMPO=NIFFACTU,TOOLTIP("NIF del cliente de direcci�n de facturaci�n")

CAMPO=IDIOMADOC,TOOLTIP("Idioma de la documentaci�n de envio")
CAMPO=SWTPACKINGLIST,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe a�adir un parking list al �ltimo bulto o 'N' no se debe a�adir packing list."),CHECKBOX("N","S")
CAMPO=TPCVERIF,TOOLTIP("Tanto por ciento de bulto que se deben enviar a verifiaci�n.")
CAMPO=MONEDA,TOOLTIP("Moneda en la que se expresan los precios del pedido. Actualmente sin uso")
CAMPO=COLCAMBIOVOL,TOOLTIP("Colecci�n de volumetrias de sustituci�n para el pedido.")
CAMPO=DESCUENTO,TOOLTIP("Indica el porcentaje de descuento global que se aplicar� pedido")
CAMPO=DESDESCUENTO,TOOLTIP("Descripci�n del descuento")
CAMPO=NUMALBA,TOOLTIP("N�mero de albaranes a imprimir autom�ticamente en verificaci�n")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de asignaci�n de stock al pedido: 0 M�xima 99 M�nima. Tiene prioridad sobre la fecha de servicio")
CAMPO=URGENCIA,TOOLTIP("Urgencia del pedido 0 M�xima 99 M�nima")
CAMPO=RECARGO,TOOLTIP("Indica el porcentaje de recargo a nivel global que se aplicar� al pedido")
CAMPO=DESRECARGO,TOOLTIP("Descripci�n  del recargo")
CAMPO=SWTVALORADO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S', si el pedido debe llevar albar�n valorado. 'N' para lo contrario "),CHECKBOX("N","S")
CAMPO=SWTPROFORMA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: de 'S' para imprimir una factura proforma que acompa�e al pedido (esta factura se a�adir� en el momento de impresi�n de la documentaci�n de env�o de las agencias). 'N' para no incluir ninguna factura"),CHECKBOX("N","S")
CAMPO=BACKORDER,TOOLTIP("Indicador recibido del host, que puede tomar los siguientes valores: 'T' todas las l�neas \ndel pedido deben servirse en su totalidad(estricto), 'L' todas las l�neas deben servirse pero si una l�nea est� servida \no no depende de la pol�tica de la l�nea, 'P' el pedido puede servirse parcialmente ")
CAMPO=CODAREAEXPED,TOOLTIP("Area desde la que se expedir� el pedido")
CAMPO=CONDPAGO,TOOLTIP("Condiciones de pago del pedido")
CAMPO=SWTALBEXTERIOR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S', si el pedido debe llevar el albar�n en el exterior. 'N' el albaran no debe estar en el exterior"),CHECKBOX("N","S")
CAMPO=SWTALBSELLADO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S', si el albar�n del pedido se debe retornar sellado. 'N' el albar�n no debe retornarse sellado"),CHECKBOX("N","S")
CAMPO=SWTTOTALES,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' imprimir albar�n valorado con impuestos y totales 'N' Albar�n s�lo con l�neas valoradas"),CHECKBOX("N","S")
CAMPO=SWTPREPMONO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' la preparaci�n debe ser mono pedido, 'N' la preparaci�n no debe ser mono pedido"),CHECKBOX("N","S")
CAMPO=SWTPALETIZAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que el pedido se debe paletizar o 'N' no se debe paletizar."),CHECKBOX("N","S")
CAMPO=SWTAGRUPAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N' en funci�n de si el pedido puede ser agrupado con otros pedidos del mismo cliente, agencia y destino, con el fin de ser facturado por la agencia como un �nico albar�n. Nota: Se agrupar�n pedidos incluso de diferentes divisiones y empresas."),CHECKBOX("N","S")
CAMPO=SWTMODELO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' el pedido ha de llevar documentaci�n adicional, 'N' no lleva documentaci�n adicional"),CHECKBOX("N","S")
CAMPO=SWTNUMEROSERIE,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador de si se deben recoger los n�meros de serie o no. Posibles valores S o N"),CHECKBOX("N","S")
CAMPO=SWTMISCELANEO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica si el pedido se tendr� en cuenta en el momento de comuptar la miscelaneo o, 'N' no se tendr� en cuenta en el momento de computar la miscelaneo."),CHECKBOX("N","S")
CAMPO=REFMODELO,TOOLTIP("Referencia de la documentaci�n adicional")
CAMPO=SWTANULAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador con valores: 'S' anular precintos 'N' no anular precintos. Esto es en funci�n de si el pedido debe llevar el precio anulado o no."),CHECKBOX("N","S")
CAMPO=SWTBLOQEXP,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que no se permite expedir si el indicador est� a 'S' o 'N' se permite expedir el pedido."),CHECKBOX("N","S")
CAMPO=SWTCOMUNICAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N' en funci�n de si el pedido se debe comunicar al Host o no"),CHECKBOX("N","S")
CAMPO=SWTFAX,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar fax a la direcci�n o 'N' no se debe enviar fax."),CHECKBOX("N","S")
CAMPO=IDIOMAETIQ,TOOLTIP("Idioma de las etiquetas de envio")
CAMPO=SWTMAIL,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar mail a la direcci�n o 'N' no se debe enviar mail."),CHECKBOX("N","S")
CAMPO=SWTEDI,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar interfase EDI al cliente o 'N' no se debe enviar intefase EDI."),CHECKBOX("N","S")
CAMPO=SWTETIQECI,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se deben imprimr las etiquetas del ECI o 'N' se no se deben imprimen etiquetas del ECI."),CHECKBOX("N","S")
CAMPO=SWTNOETIQCC,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que no se deben imprimr etiquetas de caja completa (fuerza preparaci�n monopedido) o 'N' se imprimen etiquetas de caja completa normalmente."),CHECKBOX("N","S")
CAMPO=CODAGE,TOOLTIP("Es el C�digo de la agencia que transportar� el pedido. Deber� existir en la tabla de agencias"),POSTCHANGE=FDESIGNACION("+CDESAGE","Agencia no existe.")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la agencia de transporte")
CAMPO=TRACKINGAGE,TOOLTIP("C�digo identificativo del pedido para la agencia de transporte")
CAMPO=SWTSEGURO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva seguro o 'N', el pedido no lleva seguro. Utilizado informar a la agencia y para la autofacturaci�n de agencias"),CHECKBOX("N","S")
CAMPO=TIPOBASESEGURO,UPPER,POSTCHANGE=FVERIFICA("SPF ","Los posibles valores son\n S(tandard) Importe total del pedido * Porseguro\n P(ortes) Portes del pedido * Porseguro\n F(ijo) Cantidad fija indicada en base"),TOOLTIP("Los posibles valores son\n S(tandard) Importe total del pedido * %seguro\n P(ortes) Portes del pedido * %seguro|n F(ijo) Cantidad fija indicada en base. Utilizado informar a la agencia y para la autofacturaci�n de agencias"),CHECKBOX("N","S")
CAMPO=BASESEGURO,UPPER,TOOLTIP("Base del seguro si es % y va a 0 se toma el indicada en la tarifa de la agencia. Utilizado informar a la agencia y para la autofacturaci�n de agencias"),CHECKBOX("N","S")
CAMPO=DIFAGENCIA,TOOLTIP("Diferencia con autofacturacion de agencia aceptada")
CAMPO=DATOSAGE,TOOLTIP("Campo que guarda datos adiciones de la agencia de transporte para imprimir en la etiqueta, tales como rutas, C�digos etc. En principio es generados por el propio sistema")
CAMPO=SWTREEMBOLSO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido tiene reembolso o 'N', el pedido no tiene reembolso, Utilizado para informar a la agencia y para la autofacturaci�n de agencias"),CHECKBOX("N","S")
CAMPO=SWTADUANA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva documentaci�n de la aduana o 'N', el pedido no lleva doumentaci�n de la aduana. Utilizado para informar a la agencia y para la autofacturaci�n de agencias"),CHECKBOX("N","S")
CAMPO=PORTES,UPPER,POSTCHANGE=FVERIFICA("DPF ","Los posibles valores son 'D' Debidos, 'P' Pagados, 'F' Francos"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'D' Debidos, 'P' Pagados, 'F' Francos")
CAMPO=RECARGOAGE,TOOLTIP("Cantidad adicional a pagar a la agencia. Utilizado para la autofacturaci�n de agencias")
CAMPO=FECCAPTURA,TOOLTIP("Fecha de captura en HOST del pedido")
CAMPO=HORACAPTURA,TOOLTIP("Hora de captura en HOST del pedido")
CAMPO=FECSERVICIO,TOOLTIP("Fecha en que est� previsto que se sirva el el pedido, se utiliza para ordenar los pedidos en la pantalla de creaci�n de series")
CAMPO=CODOPEALTA,TOOLTIP("Usuario de grabaci�n del pedido en el HOST")
CAMPO=FECGRABACION,TOOLTIP("Fecha de grabaci�n del pedido en el HOST")
CAMPO=HORAGRABACION,TOOLTIP("Hora de grabaci�n del pedido en el HOST")
CAMPO=FECRECEP,TOOLTIP("Fecha de recepci�n del pedido desde el HOST")
CAMPO=HORARECEP,TOOLTIP("Hora de recepci�n del pedido desde el HOST")
CAMPO=FECTERMIN,TOOLTIP("Fecha de terminaci�n del pedido, �ltimo bulto finalizado")
CAMPO=HORATERMIN,TOOLTIP("Hora de terminaci�n del pedido, �ltimo bulto finalizado")
CAMPO=STATUS,TOOLTIP("Es el estado en que se encuentra el pedido en el momento de la consulta."),POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado incorrecto."),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado en el que se encuentra el pedido")

CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la �ltima modificacion")
CAMPO=CODCOMEN,TOOLTIP("C�digo de los comentarios a la cabecera del pedido")
CAMPO=FRIO,AUXILIAR,OCULTO,"____",UPPER,NOENTER,TITULO("Frio"),WLONX=15

CURSOR=CSELTIPCLI SELECT TIPOCLI FROM VDCLIENTES WHERE CODCLIENTE=:CODCLIENTE AND :FRIO=DECODE(TIPOPEDIDO,'T',:FRIO,'F','S','N');

CURSOR=CLISTASTATUS SELECT STATUS,DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='PEC' ORDER BY STATUS;

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

CURSOR=CDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE;
CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='PEC';


TECLA=SF10,FLEEMENU("VDPEDCAB.ZOO")

