###################################################################
#Módulo: VDPEDCAB.PAN
#Funcionalidad : Mantenimiento de cabecera de pedidos
#Autor: RFD      
#Fecha: 24-03-2008
###################################################################
# Histórico de cambios:
CABECERA DE PEDIDO
  Pedido:  _20_________________ División: _20__  _40______________  Año:  @@@@  Secuencia: @@@@    Nº líneas: @@@@ 
 ÏÄÄ Datos básicos ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Albarán:    _20_________          Tipo Pedido:    __________            Serie Preparación: @@@@@@                       ³ 
 ³ Año:        @@@@                  Pedido Host:    _60_____________      Serie Expedición:  @@@@@@                       ³
 ³ Año Agrup.: @@@@                  Pedido Cliente: _60_____________  Agrupación: @@@@@@@@    Fecha:          ¿D-MM-Y.YYY ³ 
 ³ Mensaje Host:  _255_____________________________________________________________________________________________________³
 ³ Datos extra:   _255_____________________________________________________________________________________________________³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄ Datos y direcciones ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³  Cliente: _20_______  _60__________________________________________________ NIF: _30____________                        ³
 ³  Contacto:   _40_________________  Teléfono: ____________ Fax: _12_________ e-mail: _40___________________________      ³
 ³  Dire. EDI:  _40__________________________________                                                                      ³
 ³  Dirección:  _40________________________________  Dirección1: _40________________________________                       ³
 ³  Dirección2: _40________________________________  Dirección3: _40________________________________                       ³
 ³  Población:  _40_________________  País: ____ _30_____________  CP: _____ _40____________ DP: __________                ³
 ³   SWTReexpedición: _  Cliente: _20___________  _60________________________________________________ NIF: _30____________ ³  
 ³   SWTFacturación:  _  Cliente: _20___________  _60________________________________________________ NIF: _30____________ ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄ Documentación ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË   ÏÄÄÄ Preparación ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË   ÏÄ Facturación ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Idioma documentos: __________   ³   ³  Agrupar: _                              ³   ³  Descuento: ###.##  _40__________  ³
 ³  Nº Albaranes: @@@              ³   ³   Prioridad: @@  Urgencia: @@            ³   ³  Recargo:   ###.##  _40__________  ³
 ³  Valorado: _    Proforma: _     ³   ³   Backorder: _   Area Exped.: _20_______ ³   ³  Cond. de Pago: _80________________³
 ³  Totales:  _   Modelo:   _      ³   ³   Demanda: Cod _20______ Tipo  __________³   ³  Importe Total: ###########.##     ³
 ³  Referencia: _80________________³   ³   Anular Precinto: _ Comunicar: _        ³   ³        Mail: _  EDI: _    ECI: _   ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄ Transporte ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³  Agencia: __________ _30______________________ Tracking: _20____________  Seguro: _ Reembolso: _   Aduana: _  Portes: _ ³                 ³
 ³  Datos Adicionales: _80__________________________ Peso: #################   Volúmen: #################  Recargo: @@@@@@@³                           ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
 ÏÄ Seguimiento ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
 ³ Captura:   ¿D-MM-Y.YYY  ________    Servicio:  ¿D-MM-Y.YYY            Grabación: ¿D-MM-Y.YYY  ________    CNT: @@@      ³
 ³ Recepción: ¿D-MM-Y.YYY  ________    Reserva:   ¿D-MM-Y.YYY  ________                                      EMB: @@@      ³
 ³ Terminado: ¿D-MM-Y.YYY  ________    Comunicado:¿D-MM-Y.YYY  ________  Entrega:   ¿D-MM-Y.YYY  ________    UNI: @@@      ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
  Estado: @@@@@  _30____________________________ Ultima modificación: _32_______ ¿D-MM-Y.YYY  ________ Comentario: @@@@@@@@@ 
|

TABLA=VDPEDIDOCAB
ORDERBY=FECMODIF DESC,HORAMODIF DESC;
WDESPLEGADO
WLONX=1000

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODPED,TOOLTIP("Código del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=CODDIV,TOOLTIP("Division o compañia del pedido"),POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe.","+CSELDATOS",""),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=ANOPED,TOOLTIP("Año del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=SEQPED,TOOLTIP("Versión del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=NLINEAS,TOOLTIP("Es el número original de líneas del pedido que se recibio del host. Este número no se modifica por los desgloses de lote ni en las nuevas versiones de pedidos.")
CAMPO=CODALB,TOOLTIP("Código del albarán")
CAMPO=TIPOPEDIDO,TOOLTIP("Identifica el tipo del pedido según criterio de la compañía. Es recibido del Host y tal como se recibe se introduce en la Base de datos. Tiene utilidad para establecer restricciones a la hora de crear series de pedidos.")
CAMPO=CODSERIEPREP,TOOLTIP("Código de la serie de preparación en la que se incluye el pedido. Si aún no está incluido en serie el valor es 0")
CAMPO=ANOALB,TOOLTIP("Año del albarán")
CAMPO=PEDIDOHOST,TOOLTIP("Código interno del pedido para el HOST")
CAMPO=CODSERIEEXP,TOOLTIP("Código de la serie de expedición (es automática) en la que se incluye el pedido al lanzarse la serie de preparación. Si aún no está incluido en serie el valor es 0")
CAMPO=ANOGRUP,TOOLTIP("Año del grupaje en el que se incluye el pedido")
CAMPO=PEDIDOCLIENTE,TOOLTIP("Código interno del pedido para el cliente")
CAMPO=CODGRUP,TOOLTIP("Código del grupaje en el que se incluye el pedido")
CAMPO=FECPEDIDOCLIENTE,TOOLTIP("Fecha en la que el cliente realizó el pedido")
CAMPO=MENHOST,TOOLTIP("Contiene cualquier mensaje que el Host de la compañía considere oportuno. Va dirigido al personal de la compañía, por tanto, es de uso interno y no es impreso en documento alguno.")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a VD y útiles para el cliente")

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

CAMPO=SWTREEXP,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de reexpedición son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido ha de reexpedirse una vez en el cliente"),CHECKBOX("N","S")
CAMPO=CODCLIREEXP,TOOLTIP("Código del cliente de reexpedición"),CONTEXTUAL=FEJECUTAFORM("VDPEDCABDET","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED","","","","S"),INCLUDECSS="background-color:#F7BE81;border-style:ridge;"
CAMPO=DESCLIREEXP,TOOLTIP("Caso de reexpedirse el pedido, contiene el nombre del destinatario de la reexpedición")
CAMPO=NIFREEXP,TOOLTIP("NIF del cliente de reexpedición")
CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de facturación son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene dirección de facturación"),CHECKBOX("N","S")
CAMPO=CODCLIFACTU,TOOLTIP("Código del cliente de la dirección de facturación"),CONTEXTUAL=FEJECUTAFORM("VDPEDCABDET","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED","","","","S"),INCLUDECSS="background-color:#F7BE81;border-style:ridge;"
CAMPO=DESCLIFACTU,TOOLTIP("Destinatario de la dirección de facturación")
CAMPO=NIFFACTU,TOOLTIP("NIF del cliente de dirección de facturación")
CAMPO=IDIOMADOC,TOOLTIP("Idioma de la documentación de envio")
CAMPO=SWTAGRUPAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N' en función de si el pedido puede ser agrupado con otros pedidos del mismo cliente, agencia y destino, con el fin de ser facturado por la agencia como un único albarán. Nota: Se agruparán pedidos incluso de diferentes divisiones y empresas."),CHECKBOX("N","S")
CAMPO=DESCUENTO,TOOLTIP("Indica el porcentaje de descuento global que se aplicará pedido")
CAMPO=DESDESCUENTO,TOOLTIP("Descripción del descuento")
CAMPO=NUMALBA,TOOLTIP("Número de albaranes a imprimir automáticamente en verificación")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de asignación de stock al pedido: 0 Máxima 99 Mínima. Tiene prioridad sobre la fecha de servicio")
CAMPO=URGENCIA,TOOLTIP("Urgencia del pedido 0 Máxima 99 Mínima")
CAMPO=RECARGO,TOOLTIP("Indica el porcentaje de recargo a nivel global que se aplicará al pedido")
CAMPO=DESRECARGO,TOOLTIP("Descripción del recargo")
CAMPO=SWTVALORADO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S', si el pedido debe llevar albarán valorado. 'N' para lo contrario "),CHECKBOX("N","S")
CAMPO=SWTPROFORMA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: de 'S' para imprimir una factura proforma que acompañe al pedido (esta factura se añadirá en el momento de impresión de la documentación de envío de las agencias). 'N' para no incluir ninguna factura"),CHECKBOX("N","S")
CAMPO=BACKORDER,TOOLTIP("Indicador recibido del host, que puede tomar los siguientes valores: 'T' todas las líneas \ndel pedido deben servirse en su totalidad(estricto), 'L' todas las líneas deben servirse pero si una línea está servida \no no depende de la política de la línea, 'P' el pedido puede servirse parcialmente ")
CAMPO=CODAREAEXPED,TOOLTIP("Area desde la que se expedirá el pedido")
CAMPO=CONDPAGO,TOOLTIP("Condiciones de pago del pedido")
CAMPO=SWTTOTALES,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' imprimir albarán valorado con impuestos y totales 'N' Albarán sólo con líneas valoradas"),CHECKBOX("N","S")
CAMPO=SWTMODELO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' el pedido ha de llevar documentación adicional, 'N' no lleva documentación adicional"),CHECKBOX("N","S")
CAMPO=CODDEMANDA,TOOLTIP("Indica el Código de demanda de traslado realizado para reservar la mercancía a servir")
CAMPO=TIPODEMANDA,TOOLTIP("Indica el tipo de demanda de traslado realizado para reservar la mercancía a servir")
CAMPO=IMPORTEPEDIDO,TOOLTIP("Importe total del pedido")
CAMPO=REFMODELO,TOOLTIP("Referencia de la documentación adicional")
CAMPO=SWTANULAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador con valores: 'S' anular precintos 'N' no anular precintos. Esto es en función de si el pedido debe llevar el precio anulado o no."),CHECKBOX("N","S")
CAMPO=SWTCOMUNICAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N' en función de si el pedido se debe comunicar al Host o no"),CHECKBOX("N","S")
CAMPO=SWTMAIL,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar mail a la dirección o 'N' no se debe enviar mail."),CHECKBOX("N","S")
CAMPO=SWTEDI,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar interfase EDI al cliente o 'N' no se debe enviar intefase EDI."),CHECKBOX("N","S")
CAMPO=SWTETIQECI,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se deben imprimr las etiquetas del ECI o 'N' se no se deben imprimen etiquetas del ECI."),CHECKBOX("N","S")
CAMPO=CODAGE,TOOLTIP("Es el Código de la agencia que transportará el pedido. Deberá existir en la tabla de agencias"),POSTCHANGE=FDESIGNACION("CDESAGE","Agencia no existe.")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la agencia de transporte")
CAMPO=TRACKINGAGE,TOOLTIP("Código identificativo del pedido para la agencia de transporte")
CAMPO=SWTSEGURO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva seguro o 'N', el pedido no lleva seguro. Utilizado informar a la agencia y para la autofacturación de agencias"),CHECKBOX("N","S")
CAMPO=SWTREEMBOLSO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido tiene reembolso o 'N', el pedido no tiene reembolso, Utilizado para informar a la agencia y para la autofacturación de agencias"),CHECKBOX("N","S")
CAMPO=SWTADUANA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva documentación de la aduana o 'N', el pedido no lleva doumentación de la aduana. Utilizado para informar a la agencia y para la autofacturación de agencias"),CHECKBOX("N","S")
CAMPO=PORTES,UPPER,POSTCHANGE=FVERIFICA("DPF ","Los posibles valores son 'D' Debidos, 'P' Pagados, 'F' Francos"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'D' Debidos, 'P' Pagados, 'F' Francos")
CAMPO=DATOSAGE,TOOLTIP("Campo que guarda datos adiciones de la agencia de transporte para imprimir en la etiqueta, tales como rutas, Códigos etc. En principio es generados por el propio sistema")
CAMPO=PESOPEDIDO,TOOLTIP("Peso del pedido en gramos. Se calcula a partir de los pesos de las cajas completas, de las unidades sueltas, el peso de las cajas de unidades sueltas en vacío y del relleno. Es un dato calculado una vez terminado el pedido.")
CAMPO=VOLUMENPEDIDO,TOOLTIP("Volumen del pedido en litros. Es un dato calculado una vez terminado el pedido.")
CAMPO=RECARGOAGE,TOOLTIP("Cantidad adicional a pagar a la agencia. Utilizado para la autofacturación de agencias")
CAMPO=FECCAPTURA,TOOLTIP("Fecha de captura en HOST del pedido"),COMBOX("CALENDARIO")
CAMPO=HORACAPTURA,TOOLTIP("Hora de captura en HOST del pedido")
CAMPO=FECSERVICIO,TOOLTIP("Fecha en que está previsto que se sirva el el pedido, se utiliza para ordenar los pedidos en la pantalla de creación de series"),COMBOX("CALENDARIO")
CAMPO=FECGRABACION,TOOLTIP("Fecha de grabación del pedido en el HOST"),COMBOX("CALENDARIO")
CAMPO=HORAGRABACION,TOOLTIP("Hora de grabación del pedido en el HOST")
CAMPO=NUMBULPAL,AUXILIAR,NOENTER,TOOLTIP("Número de palets aproximados del pedido")
CAMPO=FECRECEP,TOOLTIP("Fecha de recepción del pedido desde el HOST"),COMBOX("CALENDARIO")
CAMPO=HORARECEP,TOOLTIP("Hora de recepción del pedido desde el HOST")
CAMPO=FECRESERVA,TOOLTIP("Fecha de lanzamiento de la serie en la que se encuentra el pedido"),COMBOX("CALENDARIO")
CAMPO=HORARESERVA,TOOLTIP("Hora de lanzamiento de la serie en la que se encuentra el pedido")
CAMPO=NUMBULEMBA,AUXILIAR,NOENTER,TOOLTIP("Número de cajas aproximadas del pedido")
CAMPO=FECTERMIN,TOOLTIP("Fecha de terminación del pedido, último bulto finalizado"),COMBOX("CALENDARIO")
CAMPO=HORATERMIN,TOOLTIP("Hora de terminación del pedido, último bulto finalizado")
CAMPO=FECCOMUNICA,TOOLTIP("Fecha de devolucion del pedido al HOST"),COMBOX("CALENDARIO")
CAMPO=HORACOMUNICA,TOOLTIP("Hora de devolucion del pedido al HOST")
CAMPO=FECENTREGA,TOOLTIP("Fecha en que la agencia entrega el pedido al cliente"),COMBOX("CALENDARIO")
CAMPO=HORAENTREGA,TOOLTIP("Hora en que la agencia entrega el pedido al cliente")
CAMPO=NUMBULUNI,AUXILIAR,NOENTER,TOOLTIP("Número de bultos de unidades aproximados del pedido")
CAMPO=STATUS,TOOLTIP("Es el estado en que se encuentra el pedido en el momento de la consulta."),POSTCHANGE=FDESIGNACION("CDESSTATUS","Estado incorrecto."),COMBOX("CLISTASTATUS"),COMBOXREGPAG=6
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripción del estado en el que se encuentra el pedido")

CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")
CAMPO=CODCOMEN,TOOLTIP("Código de los comentarios a la cabecera del pedido")

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

CURSOR=CSELALBARAN SELECT '$(VDALBARAN)' ALBARAN, 'C:\ALBARAN_'||:CODPED||'.PDF' RUTA
                     FROM DUAL;

CURSOR=CSELDATOS SELECT SUM(DECODE(TIPOBULTO,'U',1,0)) NUMBULUNI,
                            SUM(DECODE(TIPOBULTO,'E',1,0)) NUMBULEMBA,
                            SUM(DECODE(TIPOBULTO,'C',1,0)) NUMBULPAL
                       FROM VDBULTOCAB
                      WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND
                            SEQPED = :SEQPED AND ANOPED = :ANOPED;




BOTON=B2,920,300,60,60,"P",micomentarios.png,SF7,"Consulta de comentarios",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,920,400,60,60,"P",mizoom.png,SF10,"Menú de zoom",INCLUDECSS="background-color: transparent;border-width:0px"

TECLA=SF6,FEJECUTA(FIMPRIMEPEDIDO("INFORME",":CODDIV",":ANOPED",":CODPED",":SEQPED","$(VDALBARAN)","CODDIV=:CODDIV;ANOPED=:ANOPED;CODPED=:CODPED;SEQPED=:SEQPED",""),":V10ERROR")
