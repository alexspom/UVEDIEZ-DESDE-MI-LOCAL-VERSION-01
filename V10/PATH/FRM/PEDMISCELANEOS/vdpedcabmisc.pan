###################################################################
#Módulo: VDPEDCABMISC.PAN
#Funcionalidad : Inserción de pedidos miscelaneos
#Autor: RFD
#Fecha: 24-03-2008
###################################################################
# Histórico de cambios:
CREACION DE PEDIDOS MISCELANEOS
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ DATOS DEL CLIENTE ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                             ³
 ³  Cliente: _20_________________ _60__________________     Tipo: _5___  NIF: _30___________   ³
 ³                                                                                             ³
 ³ ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ           ENTREGA           ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË ³
 ³ ³                                                                                         ³ ³
 ³ ³ Dirección: _40___________________________  _40___________________________               ³ ³
 ³ ³            _40___________________________  _40___________________________               ³ ³
 ³ ³ Población: _40_________________   DP: _10____       País: _5_ _30______________________ ³ ³
 ³ ³ Provincia: _5_ _40__________________    Contacto: _40__________________________________ ³ ³
 ³ ³ Teléfono:  _12_______            Fax: _12______    Email: _40__________________________ ³ ³
 ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ³
 ³                                                                                             ³
 ³ ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ            FACTURA _        ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË ³
 ³ ³                                                                                         ³ ³
 ³ ³ Cliente Fact: _20_________________ _60____________________________ NIF: _30__________   ³ ³
 ³ ³ Dirección: _40___________________________  _40___________________________               ³ ³
 ³ ³            _40___________________________  _40___________________________               ³ ³
 ³ ³ Población: _40___________________________  DP: _10____ País: _5_ _30___________________ ³ ³
 ³ ³ Provincia: _5_ _40__________________    Contacto: _40__________________________________ ³ ³
 ³ ³ Teléfono:  _12_______           Fax: _12______     Email: _40__________________________ ³ ³
 ³ ³                                                                                         ³ ³
 ³ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ³
 ³                                                                                             ³
 ³ Tipo Pedido: ___ Prioridad: @@ Urgencia: @@ Idioma Etiq.: ________ Idioma doc.: ________    ³
 ³ Dcto: ###,##      Recargo: ###,##  NºAlbarán: @@@   Valorado: _    Totales: _  Proforma: _  ³
 ³ Modelo: _ Ref. Modelo: _80______________________ Anul Precintos: _ EDI: _      Backorder: _ ³
 ³ Agrupar: _  Paletizar: _                                                                    ³
 ³                                                                                             ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 División: _20__  _40______________        Pedido: _20___________ Año: @@@@ Secuencia: @@@@  
 Pedido Host:    _60_____________ Pedido Cliente: _60_____________  Fecha: ¿D-MM-Y.YYY 
 Fec. Servicio:  ¿D-MM-Y.YYY     Mensaje Host: _255_____________________________________________
 Datos Agencia:  Agencia: __________ _30______________________     Recargo: ######.##
                 Seguro: _     Reembolso: _ 
                 Portes: _        Aduana: _ 
                 Peso:  #L########.### Kg.      Volumen: #L########.### litros
 Ultima modificación: _32_______  ¿D-MM-Y.YYY  ________
|

TABLA=VDPEDIDOCAB
NOINSERT,PROTECT("ADMINISTRADOR")
NOUPDATE,PROTECT("ADMINISTRADOR")
NODELETE,PROTECT("ADMINISTRADOR")

POSTQUERY=FEJECUTA("+CINTIPESOYVOL","")

WHERE=SWTMISCELANEO='S' AND STATUS = VDST.FPECMISCELANEO;

PREINSERT=FEJECUTA("CCHECKCODDIV","EL CAMPO DIVISION DEL PEDIDO NO PUEDE SER NULO",
                   "CINITCAMPOS","ERROR INICIALIZANDO CAMPOS",
                   "CCHECKPOBLACION","LA POBLACION DE ENVIO NO PUEDE SER NULA",
                   "CCHECKDP","EL Código POSTAL NO PUEDE SER NULO.",
                   "CSELSINCLAVE","ERROR AL OBTENER Código DE PEDIDO",
                   "CINSPEDORIG","ERROR INSERTANDO PEDIDO ORIGINAL",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CCHECKPOBLACION","LA POBLACION DE ENVIO NO PUEDE SER NULA",
                   "CCHECKDP","EL Código POSTAL NO PUEDE SER NULO.",
                   "+CUPDPESOYVOL","",
                   "CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

PREDELETE=FEJECUTA("+CDELLINEASPED","")

CAMPO=CODCLIENTE,TOOLTIP("Es el Código de cliente que realiza el pedido, recibido por el fichero de interfase con el Host"),POSTCHANGE=FDESIGNACION("+CSELTIPOCLI","",FPOSICIONACAMPO(FSUCCESS,"CODDIV"),"")
CAMPO=DESCLIENTE,TOOLTIP("Designación completa del cliente que realiza el pedido. También recibido en el interfase")
CAMPO=TIPOCLI,AUXILIAR,NOENTER,TOOLTIP("Tipo de cliente")
CAMPO=NIF,TOOLTIP("Nif del cliente")
CAMPO=DIRECCION,TOOLTIP("Es la dirección del cliente o dirección destino del pedido. Se recibe en el interfase con el Host. Está descompuesta en cuatro campos de 40 caracteres")
CAMPO=DIRECCION1,TOOLTIP("Línea 2 de la dirección de envio del pedido")
CAMPO=DIRECCION2,TOOLTIP("Línea 3 de la dirección de envio del pedido")
CAMPO=DIRECCION3,TOOLTIP("Línea 4 de la dirección de envio del pedido")
CAMPO=POBLACION,TOOLTIP("Población destino del pedido. Recibido del HOST")
CAMPO=DP,TOOLTIP("Distrito postal de la dirección de envio. Recibido de la interfase")
CAMPO=CODPAIS,TOOLTIP("País de envío"),POSTCHANGE=FDESIGNACION("+CSELPAISDEST","")
CAMPO=DESPAISDEST,AUXILIAR,NOENTER
CAMPO=CODPROV,TOOLTIP("Código de la provincia de envio. Recibido del HOST"),POSTCHANGE=FDESIGNACION("+CSELDESPROVDEST","")
CAMPO=DESPROVDEST,AUXILIAR,NOENTER
CAMPO=CONTACTO,TOOLTIP("Dato recibido en el interfase, de libre introducción. Es el posible contacto con el cliente")
CAMPO=TELEFONO,TOOLTIP("Teléfono correspondiente a dirección de envio. Recibido del HOST")
CAMPO=FAX,TOOLTIP("Número de fax del cliente")
CAMPO=EMAIL,TOOLTIP("Direccion email correspondiente a dirección de envio. Recibido del HOST")

CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores de facturación son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene dirección de facturación"),WPOSX=-292
CAMPO=CODCLIFACTU,TOOLTIP("Código del cliente de la dirección de facturación")
CAMPO=DESCLIFACTU,TOOLTIP("Descripción del cliente de facturación")
CAMPO=NIFFACTU,TOOLTIP("NIF del cliente de dirección de facturación")
CAMPO=DIRFACTU,TOOLTIP("Es la dirección de facturacion del pedido. Esta descompuesta en cuatro campos de 40 caracteres.")
CAMPO=DIRFACTU1,TOOLTIP("Línea 2 de la direccion de facturacion del pedido")
CAMPO=DIRFACTU2,TOOLTIP("Línea 3 de la direccion de facturacion del pedido")
CAMPO=DIRFACTU3,TOOLTIP("Línea 4 de la direccion de facturacion del pedido")
CAMPO=POBFACTU,TOOLTIP("Población de facturación del pedido. Recibido del HOST")
CAMPO=DPFACTU,TOOLTIP("Distrito postal de la dirección de facturación. Recibido de la interfase")
CAMPO=CODPAISFACTU,TOOLTIP("País de facturación"),POSTCHANGE=FDESIGNACION("+CSELPAISFACT","")
CAMPO=DESPAISFACT,AUXILIAR,NOENTER
CAMPO=CODPROVFACTU,TOOLTIP("Código de la provincia de facturación. Recibido del HOST"),POSTCHANGE=FDESIGNACION("+CSELDESPROVFACT","")
CAMPO=DESPROVFACTU,AUXILIAR,NOENTER
CAMPO=CONTAFACTU,TOOLTIP("Contacto de facturación")
CAMPO=TELFACTU,TOOLTIP("Telefono correspondiente a direccion de facturacion.")
CAMPO=FAXFACTU,TOOLTIP("Fax correspondiente a direccion de facturacion.")
CAMPO=EMAILFACTU,TOOLTIP("Email correspondiente a direccion de facturación.")

CAMPO=TIPOPEDIDO,TOOLTIP("Identifica el tipo del pedido según criterio de la compañía. Es recibido del Host y tal como se recibe se introduce en la Base de datos. Tiene utilidad para establecer restricciones a la hora de crear series de pedidos.")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de asignación de stock al pedido: 0 Máxima 99 Mínima. Tiene prioridad sobre la fecha de servicio")
CAMPO=URGENCIA,TOOLTIP("Urgencia del pedido 0 Máxima 99 Mínima")
CAMPO=IDIOMAETIQ,TOOLTIP("Idioma de las etiquetas de envio")
CAMPO=IDIOMADOC,TOOLTIP("Idioma de la documentación de envio")
CAMPO=DESCUENTO,TOOLTIP("Indica el porcentaje de descuento global que se aplicará pedido")
CAMPO=DESCUENTOLIN,AUXILIAR,OCULTO,"###,##"
CAMPO=RECARGO,TOOLTIP("Indica el porcentaje de recargo a nivel global que se aplicará al pedido")
CAMPO=RECARGOLIN,AUXILIAR,OCULTO,"###,##"
CAMPO=IVA,AUXILIAR,OCULTO,"###,##"
CAMPO=NUMALBA,TOOLTIP("Número de albaranes a imprimir automáticamente en verificación")
CAMPO=SWTVALORADO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S', si el pedido debe llevar albarán valorado. 'N' para lo contrario ")
CAMPO=SWTTOTALES,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' imprimir albarán valorado con impuestos y totales 'N' Albarán sólo con líneas valoradas")
CAMPO=SWTPROFORMA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: de 'S' para imprimir una factura proforma que acompañe al pedido (esta factura se añadirá en el momento de impresión de la documentación de envío de las agencias). 'N' para no incluir ninguna factura")
CAMPO=SWTMODELO,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' el pedido ha de llevar documentación adicional, 'N' no lleva documentación adicional")
CAMPO=REFMODELO,TOOLTIP("Referencia de la documentación adicional")
CAMPO=SWTANULAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador con valores: 'S' anular precintos 'N' no anular precintos. Esto es en función de si el pedido debe llevar el precio anulado o no.")
CAMPO=SWTEDI,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar interfase EDI al cliente o 'N' no se debe enviar intefase EDI.")
CAMPO=BACKORDER,TOOLTIP("Indicador recibido del host, que puede tomar los siguientes valores: 'T' todas las líneas \ndel pedido deben servirse en su totalidad(estricto), 'L' todas las líneas deben servirse pero si una línea está servida \no no depende de la política de la línea, 'P' el pedido puede servirse parcialmente ")
CAMPO=SWTAGRUPAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N' en función de si el pedido puede ser agrupado con otros pedidos del mismo cliente, agencia y destino, con el fin de ser facturado por la agencia como un único albarán. Nota: Se agruparán pedidos incluso de diferentes divisiones y empresas.")
CAMPO=SWTPALETIZAR,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que el pedido se debe paletizar o 'N' no se debe paletizar.")
CAMPO=CODDIV,TOOLTIP("Division o compañia del pedido"),POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe.")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=CODPED,TOOLTIP("Código del pedido")
CAMPO=ANOPED,TOOLTIP("Año del pedido")
CAMPO=SEQPED,TOOLTIP("Versión del pedido")
CAMPO=PEDIDOHOST,TOOLTIP("Código interno del pedido para el HOST")
CAMPO=PEDIDOCLIENTE,TOOLTIP("Código interno del pedido para el cliente")
CAMPO=FECPEDIDOCLIENTE,TOOLTIP("Fecha en la que el cliente realizó el pedido")
CAMPO=FECSERVICIO,TOOLTIP("Fecha en que está previsto que se sirva el el pedido, se utiliza para ordenar los pedidos en la pantalla de creación de series")
CAMPO=MENHOST,TOOLTIP("Contiene cualquier mensaje que el Host de la compañía considere oportuno. Va dirigido al personal de la compañía, por tanto, es de uso interno y no es impreso en documento alguno.")
CAMPO=CODAGE,TOOLTIP("Es el Código de la agencia que transportará el pedido. Deberá existir en la tabla de agencias"),POSTCHANGE=FDESIGNACION("CDESAGE","Agencia no existe.")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripción de la agencia de transporte")
CAMPO=RECARGOAGE,TOOLTIP("Cantidad adicional a pagar a la agencia. Utilizado para la autofacturación de agencias")
CAMPO=SWTSEGURO,UPPER,POSTCHANGE=FVERIFICA("FPDN ","Los posibles valores son F(actura), P(agado), D(ebido) y N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'F', el pedido lleva seguro y se factura, 'P', seguro pagado, 'D', seguro debido o 'N', el pedido no lleva seguro. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=SWTREEMBOLSO,UPPER,POSTCHANGE=FVERIFICA("FPDN ","Los posibles valores son F(actura), P(agado), D(ebido) y N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'F', el pedido lleva reembolso y se factura, 'P', reembolso pagado, 'D', reembolso debido o 'N', el pedido no lleva reembolso. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=PORTES,UPPER,POSTCHANGE=FVERIFICA("DPF ","Los posibles valores son 'D' Debidos, 'P' Pagados, 'F' Francos"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'D' Debidos, 'P' Pagados, 'F' Francos")
CAMPO=SWTADUANA,UPPER,POSTCHANGE=FVERIFICA("SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva documentación de la aduana o 'N', el pedido no lleva doumentación de la aduana. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=PESOPEDIDOAUX,AUXILIAR,TOOLTIP("Peso del pedido en Kg.")
CAMPO=PESOPEDIDO,OCULTO,"#L#############"
CAMPO=VOLUMENPEDIDOAUX,AUXILIAR,TOOLTIP("Volumen del pedido en litros.")
CAMPO=VOLUMENPEDIDO,OCULTO,"#L#############"
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")

################################################################################################################

CAMPO=SWTREEXP,OCULTO,"_"
CAMPO=SWTALBEXTERIOR,OCULTO,"_"
CAMPO=SWTALBSELLADO,OCULTO,"_"
CAMPO=SWTCOMUNICAR,OCULTO,"_"
CAMPO=SWTMISCELANEO,OCULTO,"_"
CAMPO=SWTPACKINGLIST,OCULTO,"_"
CAMPO=SWTNOETIQCC,OCULTO,"_"
CAMPO=SWTETIQECI,OCULTO,"_"
CAMPO=SWTBLOQEXP,OCULTO,"_"
CAMPO=SWTMAIL,OCULTO,"_"
CAMPO=SWTFAX,OCULTO,"_"
CAMPO=SWTPREPMONO,OCULTO,"_"
CAMPO=CODAREAEXPED,OCULTO,"_20_"

CAMPO=FECCAPTURA,OCULTO,"@@@@@@@"
CAMPO=HORACAPTURA,OCULTO,"_8_"
CAMPO=FECGRABACION,OCULTO,"@@@@@@@"
CAMPO=HORAGRABACION,OCULTO,"_8_"
CAMPO=FECRECEP,OCULTO,"@@@@@@@"
CAMPO=HORARECEP,OCULTO,"_8_"
CAMPO=STATUS,OCULTO,"@@@@@@"
CAMPO=ANOGRUP,OCULTO,"@@@@"
CAMPO=CODGRUP,OCULTO,"@@@@@@@@"
CAMPO=CODCOMENAUX,AUXILIAR,OCULTO,"@L@@@@@@@"

CURSOR=CINITCAMPOS SELECT 'N' SWTREEXP, 'N' SWTALBEXTERIOR, 'N' SWTALBSELLADO, 'N' SWTCOMUNICAR, 'S' SWTMISCELANEO,
                          'N' SWTPACKINGLIST, 'N' SWTNOETIQCC, 'N' SWTETIQECI, 'N' SWTBLOQEXP, 'N' SWTMAIL,
                          'N' SWTFAX, 'N' SWTPREPMONO, 'EXPED' CODAREAEXPED, VD.FECHASYS FECCAPTURA, VD.HORASYS HORACAPTURA, 
                          VD.FECHASYS FECGRABACION, VD.HORASYS HORAGRABACION, VD.FECHASYS FECRECEP, VD.HORASYS HORARECEP, VDST.FPECMISCELANEO STATUS,
                          0 ANOGRUP, 0 CODGRUP, DECODE(:ANOPED,0,TO_CHAR(SYSDATE,'YYYY'),:ANOPED) ANOPED,
                          DECODE(:SEQPED,0,1,:SEQPED) SEQPED, :PESOPEDIDOAUX*1000 PESOPEDIDO, :VOLUMENPEDIDOAUX*1000 VOLUMENPEDIDO,
                          DECODE(:FECSERVICIO,0,VD.FECHASYS,:FECSERVICIO) FECSERVICIO 
                     FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE
                UNION 
               SELECT NULL DESAGE FROM DUAL WHERE :CODAGE IS NULL;

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

CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELDESTIPOFP SELECT DESCTIPOFORMAPAGO FROM VDTIPOFORMAPAGO WHERE TIPOFORMAPAGO = :TIPOFORMAPAGO
                      UNION
                     SELECT NULL DESCTIPOFORMAPAGO FROM DUAL WHERE :TIPOFORMAPAGO IS NULL;

CURSOR=CCHECKCODDIV SELECT :CODDIV FROM DUAL WHERE :CODDIV IS NOT NULL;


CURSOR=CCHECKPOBLACION SELECT :POBLACION POBLACION FROM DUAL WHERE :POBLACION IS NOT NULL;

CURSOR=CCHECKDP SELECT :DP FROM DUAL WHERE :DP IS NOT NULL;


CURSOR=CCHECKPAIS SELECT :CODPAIS FROM VDPAIS WHERE CODPAIS = :CODPAIS AND DESPAIS = 'PORTUGAL';


CURSOR=CSELSINCLAVE SELECT :CODPED FROM DUAL WHERE :CODPED IS NOT NULL;


CURSOR=CASIGNACLAVE BEGIN :CODPED:=MOVIANTO.DAMESECPEDIDO(:CODDIV); END;@

CURSOR=CDELLINEASPED DELETE FROM VDPEDIDOLIN WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND SEQPED = :SEQPED AND ANOPED = :ANOPED;

CURSOR=CSELTIPOCLI SELECT TIPOCLI FROM VDCLIENTES WHERE CODCLIENTE = :CODCLIENTE;

CURSOR=CUPDPESOYVOL SELECT :PESOPEDIDOAUX*1000 PESOPEDIDO, :VOLUMENPEDIDOAUX*1000 VOLUMENPEDIDO FROM DUAL;

CURSOR=CINTIPESOYVOL SELECT :PESOPEDIDO/1000 PESOPEDIDOAUX, :VOLUMENPEDIDO/1000 VOLUMENPEDIDOAUX FROM DUAL;

CURSOR=CINSPEDORIG INSERT INTO VDPEDIDORIGCAB (CODDIV, ANOPED, CODPED, ANOALB, CODALB, TIPOPEDIDO, NLINEAS, PEDIDOCLIENTE, FECPEDIDOCLIENTE, 
                                               PEDIDOHOST, CODCLIENTE, DESCLIENTE, NIF, CONTACTO, DIRECCION, DIRECCION1, DIRECCION2, DIRECCION3, 
                                               POBLACION, CODPROV, DP, CODPAIS, TELEFONO, FAX, EMAIL, DIRECCIONEDI, IDIOMAETIQ, IDIOMADOC, NUMALBA, MENHOST, 
                                               SWTANULAR, SWTVALORADO, SWTTOTALES, SWTPROFORMA, SWTALBEXTERIOR, SWTALBSELLADO, SWTAGRUPAR, SWTCOMUNICAR, SWTMODELO, 
                                               REFMODELO, SWTMISCELANEO, SWTPACKINGLIST, SWTNOETIQCC, SWTPALETIZAR, SWTETIQECI, SWTBLOQEXP, SWTMAIL, SWTFAX, 
                                               SWTEDI, CODAREAEXPED, BACKORDER, SWTPREPMONO, TPCVERIF, COLCAMBIOVOL, MONEDA, DESCUENTO, DESDESCUENTO, 
                                               RECARGO, DESRECARGO, CONDPAGO, PRIORIDAD, URGENCIA, CODAGE, TRACKINGAGE, DATOSAGE, SWTADUANA, SWTREEXP, CODCLIREEXP, DESCLIREEXP, 
                                               NIFREEXP, CONTAREEXP, DIRREEXP, DIRREEXP1, DIRREEXP2, DIRREEXP3, POBREEXP, CODPROVREEXP, DPREEXP, CODPAISREEXP, TELREEXP, FAXREEXP, 
                                               EMAILREEXP, DIRECCIONEDIREEXP, SWTFACTU, CODCLIFACTU, DESCLIFACTU, NIFFACTU, CONTAFACTU, DIRFACTU, DIRFACTU1, 
                                               DIRFACTU2, DIRFACTU3, POBFACTU, CODPROVFACTU, DPFACTU, CODPAISFACTU, TELFACTU, FAXFACTU, EMAILFACTU, DIRECCIONEDIFACTU, CODCOMEN, FECCAPTURA, 
                                               HORACAPTURA, FECSERVICIO, FECGRABACION, HORAGRABACION, FECRECEP, HORARECEP, FECTERMIN, HORATERMIN, STATUS, VDEXTRA, CODOPEMODIF, FECMODIF, 
                                               HORAMODIF, SWTSEGURO, SWTREEMBOLSO, PORTES) 
                   VALUES (:CODDIV, :ANOPED, :CODPED, 0, NULL, :TIPOPEDIDO, 0, :PEDIDOCLIENTE, :FECPEDIDOCLIENTE, 
                           :PEDIDOHOST, :CODCLIENTE, :DESCLIENTE, :NIF, :CONTACTO, :DIRECCION, :DIRECCION1, :DIRECCION2, :DIRECCION3, 
                           :POBLACION, :CODPROV, :DP, :CODPAIS, :TELEFONO, :FAX, :EMAIL, NULL, :IDIOMAETIQ, :IDIOMADOC, :NUMALBA, :MENHOST, 
                           :SWTANULAR, :SWTVALORADO, :SWTTOTALES, :SWTPROFORMA, :SWTALBEXTERIOR, :SWTALBSELLADO, :SWTAGRUPAR, :SWTCOMUNICAR, :SWTMODELO, 
                           :REFMODELO, :SWTMISCELANEO, :SWTPACKINGLIST, :SWTNOETIQCC, :SWTPALETIZAR, :SWTETIQECI, :SWTBLOQEXP, :SWTMAIL, :SWTFAX, 
                           :SWTEDI, :CODAREAEXPED, :BACKORDER, :SWTPREPMONO, 0, NULL, NULL, :DESCUENTO, NULL, 
                           :RECARGO, NULL, NULL, :PRIORIDAD, :URGENCIA, :CODAGE, NULL, NULL, :SWTADUANA, :SWTREEXP, NULL, NULL, 
                           NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
                           NULL, NULL, :SWTFACTU, :CODCLIFACTU, :DESCLIFACTU, :NIFFACTU, :CONTAFACTU, :DIRFACTU, :DIRFACTU1, 
                           :DIRFACTU2, :DIRFACTU3, :POBFACTU, :CODPROVFACTU, :DPFACTU, :CODPAISFACTU, :TELFACTU, :FAXFACTU, :EMAILFACTU, NULL, :CODCOMENAUX, :FECCAPTURA, 
                           :HORACAPTURA, :FECSERVICIO, :FECGRABACION, :HORAGRABACION, :FECRECEP, :HORARECEP, 0, NULL, VDST.FPECGRABADO, NULL, VDUSER.GETUSER, VD.FECHASYS, 
                           VD.HORASYS, :SWTSEGURO, :SWTREEMBOLSO, :PORTES);




CONTEXTUAL=FLEEMENU("VDPEDCABMISC.ZOO")

AYUDA=INSERCION PEDIDOS MISCELANEOS

ONLINE= {F1} Ayuda             {F2} Consulta       {F4} Grabar pedido SIN lineas  {F6} Introducir lineas de pedido
        {Esc} Cerrar Pantalla  {F9} Borrar pedido  {F5} Borrar Pantalla           {Máy+F10} Menú Contextual ;
