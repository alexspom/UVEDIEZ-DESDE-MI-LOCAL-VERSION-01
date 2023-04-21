#####
# VDCLIENTES.PAN
#                                                    
# Propósito: Mantenimiento de la tabla de clientes                          
#                                                                              
# Autor  : JMM                                                           
# Fecha  : 06-10-2008                                                          
#####
#  Modificaciones:
#  DFL 29/01/2020: AJUSTAR PORQUE EL ESTANDAR NO FUNCIONA BIEN
#                  * AÑADIR CODDIV-DESDIV
#                  * INCLUIR DATOS POR DEFECTO OBLIGATORIOS
#
#####
MANTENIMIENTO DE CLIENTES
 División:_20___  _40_______________________________   
 Cliente: _20_________________ _60__________________ @@@@@ Tipo: _5___  NIF: _30___________
 Ruta: _20_________________ _100___________________________________________________________ 
 
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ENVIO ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                                                         ³
 ³ Dirección: _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³            _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³ Población: _40_________________ DP: _10____        Provincia: _5_ _40__________________ ³
 ³                                                                                         ³
 ³ País: _5_ _30_________________  Contacto: _40_____________________________________      ³
 ³                                                                                         ³
 ³ Teléfono: _12_______            Fax: _12______     Email: _40__________________________ ³
 ³                                                                                         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ FACTURA ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ FACTURA _                                                                               ³
 ³ Cliente Fact: _20_________________ _60____________________________ NIF: _30___________  ³
 ³                                                                                         ³
 ³ Dirección: _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³            _40___________________________  _40___________________________               ³
 ³                                                                                         ³
 ³ Población: _40_________________ DP: _10____        Provincia: _5_ _40__________________ ³
 ³                                                                                         ³
 ³ País: _5_ _30_________________  Contacto: _40_____________________________________      ³
 ³                                                                                         ³
 ³ Teléfono: _12_______            Fax: _12______     Email: _40__________________________ ³
 ³                                                                                         ³
 ³ Serie: _7_____  Forma Pago: ____ _40_____________________________________               ³
 ³                                                                                         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 Tipo Pedido: ___   Prioridad: @@ Urgencia: @@ Idioma Etiq.: __________ Idioma doc.: __________
 
 Descuento Cab: ###,## Descuento línea: ###,##  Recargo Cab: ###,## Recargo línea:###,## IVA: ###,## 
 
 NºAlbaranes: @@@   Preparación: _     Anular Precintos: _  Valorado: _  Totales: _   Proforma: _ 
 
 Agrupar: _ Paletizar: _    Modelo: _  Ref.Modelo: _80___   Bloq Dev. _ Scan _ Admite dev _
 
 Portes: _  Seguro: _ Tipo _ Base #L###.###       EDI: _     Reembolso: _ Aduana: _ Activo _
 
 Agencia: _10_______  _30_________________________ Recargo Agen.: ######.##  % Verificacion: @@@@@

 Observaciones: _256_________________________________________________________________________________ 
 
 Ultima modificación: _32________________ ¿D-MM-YY.Y ________

|

TABLA=VDCLIENTES

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION",
                   "+CSELINI","",
                   "CVERIFCODAGE","LA AGENCIA :CODAGE NO EXISTE O NO HA SIDO INFORMADA")

PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION",
                   "+CSELINI","",
                   "CVERIFCODAGE","LA AGENCIA :CODAGE NO EXISTE O NO HA SIDO INFORMADA")

CAMPO=CODDIV,TOOLTIP("Division o compañia del pedido"),POSTCHANGE=FDESIGNACION("+CDESDIV","Código de división no existe."),COMBOX("CLISTADIV"),WLONX=10
CAMPO=DESDIV,AUXILIAR,NOENTER,TITULO("Descripción") ,CONTEXTUAL=FEJECUTAFORM("VDSELDIVIS","N","","","CODDIV=:CODDIV","Selección de división","S"), WHERE=CODDIV IN (SELECT CODDIV FROM VDDIVIS WHERE DESDIV LIKE '%'||:DESDIV||'%');
CAMPO=CODCLIENTE,TOOLTIP("Es el Código de cliente que realiza el pedido, recibido por el fichero de interfase con el Host")
CAMPO=DESCLIENTE,TOOLTIP("Designación completa del cliente que realiza el pedido. También recibido en el interfase")
CAMPO=SEQCODCLI,TOOLTIP("Secuencial de cliente para el caso en el que tenga más de una direccion")
CAMPO=TIPOCLI,TOOLTIP("Tipo de cliente")
CAMPO=NIF,TOOLTIP("Nif del cliente")
CAMPO=CODRUTA,TOOLTIP("Código de la ruta asignada al cliente"),POSTCHANGE=FEJECUTA("+CSELRUTA","ERROR OBTENIENDO DATOS DE RUTA"),COMBOX("CRUTAS")
CAMPO=DESRUTA,AUXILIAR,NOENTER,TOOLTIP("Descripción de la ruta asignada al cliente")
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

CAMPO=SWTFACTU,UPPER,POSTCHANGE=FVERIFICA("SN ","Los posibles valores de facturación son S(i) N(o)."),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' o 'N', si el pedido tiene dirección de facturación")
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
CAMPO=TIPOFORMAPAGO,TOOLTIP("Tipo de Forma de pago. Determina la forma en la que el cliente realizará el pago de sus pedidos.")
CAMPO=DESCTIPOFORMAPAGO,AUXILIAR,NOENTER
CAMPO=TIPOPEDIDO,TOOLTIP("Identifica el tipo del pedido según criterio de la compañía. Es recibido del Host y tal como se recibe se introduce en la Base de datos. Tiene utilidad para establecer restricciones a la hora de crear series de pedidos.")
CAMPO=PRIORIDAD,TOOLTIP("Prioridad de asignación de stock al pedido 0 Máxima 99 Mínima")
CAMPO=URGENCIA,TOOLTIP("Urgencia del pedido 0 Máxima 99 Mínima")
CAMPO=IDIOMAETIQ,TOOLTIP("Idioma de las etiquetas de envio")
CAMPO=IDIOMADOC,TOOLTIP("Idioma de la documentación de envio")
CAMPO=DESCUENTOCAB,TOOLTIP("Indica el porcentaje de descuento global que se aplicará pedido")
CAMPO=DESCUENTOLIN,TOOLTIP("Indica el porcentaje de descuento que se aplicará a las líneas del pedido")
CAMPO=RECARGOCAB,TOOLTIP("Indica el porcentaje de recargo a nivel global que se aplicará al pedido")
CAMPO=RECARGOLIN,TOOLTIP("Indica el porcentaje de recargo que se aplicará a las líneas del pedido")
CAMPO=IVA,TOOLTIP("Porcentaje de IVA sobre el producto")
CAMPO=NUMALBA,TOOLTIP("Número de albaranes a imprimir automáticamente en verificación")
CAMPO=BACKORDER,TOOLTIP("Indicador recibido del host, que puede tomar los siguientes valores: 'T' todas las líneas \ndel pedido deben servirse en su totalidad(estricto), 'L' todas las líneas deben servirse pero si una línea está servida \no no depende de la política de la línea, 'P' el pedido puede servirse parcialmente ")
CAMPO=SWTANULAR,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("Indica si deben anularse los precintos de la seguridad social")
CAMPO=SWTVALORADO,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("Puede tomar los valores de: S, si el pedido debe llevar albarán valorado. N para lo contrario")
CAMPO=SWTTOTALES,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("S imprimir albarán valorado con impuestos y totales, N Albarán sólo con líneas valoradas")
CAMPO=SWTPROFORMA,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: de 'S' para imprimir una factura proforma que acompañe al pedido (esta factura se añadirá en el momento de impresión de la documentación de envío de las agencias). 'N' para no incluir ninguna factura")
CAMPO=SWTAGRUPAR,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("Sus posibles valores son 'S' o 'N' en función de si el pedido puede ser agrupado con otros pedidos del mismo cliente, agencia y destino, con el fin de ser facturado por la agencia como un único albarán. Nota: Se agruparán pedidos incluso de diferentes divisiones y empresas")
CAMPO=SWTPALETIZAR,UPPER,POSTCHANGE=FVERIFICA("SN ","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que el pedido se debe paletizar o 'N' no se debe paletizar.")
CAMPO=SWTMODELO,POSTCHANGE=FVERIFICA(" SN","El indicador puede tomar dos valores: S(i) o N(o)"),TOOLTIP("S El pedido ha de llevar documentación adicional, N no la lleva")
CAMPO=REFMODELO,TOOLTIP("Referencia de la documentación adicional")
CAMPO=SWTBLOQDEV,POSTCHANGE=FVERIFICA(" SN","Debe introducir S(i) o N(o)")
CAMPO=SWTBLOQSCAN,POSTCHANGE=FVERIFICA(" SN","Debe introducir S(i) o N(o)")
CAMPO=ADMITEDEF,POSTCHANGE=FVERIFICA(" SN","Debe introducir S(i) o N(o)")
CAMPO=PORTES,TOOLTIP("D debidos P pagados F franco"),POSTCHANGE=FVERIFICA("DPF ","Los posibles valores son 'D' Debidos, 'P' Pagados, 'F' Francos")
CAMPO=SWTSEGURO,POSTCHANGE=FVERIFICA("FPDN ","Los posibles valores son F(actura), P(agado), D(ebido) y N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'F', el pedido lleva seguro y se factura, 'P', seguro pagado, 'D', seguro debido o 'N', el pedido no lleva seguro. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=TIPOBASESEGURO,UPPER,POSTCHANGE=FVERIFICA(" SPF","Los posibles valores son\nBlanco\n S(tandard) Importe total del pedido * Porseguro\n P(ortes) Portes del pedido * Porseguro\n F(ijo) Cantidad fija indicada en base"),TOOLTIP("Los posibles valores son\n S(tandard) Importe total del pedido * %seguro\n P(ortes) Portes del pedido * %seguro|n F(ijo) Cantidad fija indicada en base. Utilizado informar a la agencia y para la autofacturación de agencias")
CAMPO=BASESEGURO,UPPER,TOOLTIP("Base del seguro si es % y va a 0 se toma el indicada en la tarifa de la agencia. Utilizado informar a la agencia y para la autofacturación de agencias")
CAMPO=SWTEDI,UPPER,POSTCHANGE=FVERIFICA(" SN","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguientes valores: 'S' indica que se debe enviar interfase EDI al cliente o 'N' no se debe enviar intefase EDI.")
CAMPO=SWTREEMBOLSO,UPPER,POSTCHANGE=FVERIFICA("FPDN ","Los posibles valores son F(actura), P(agado), D(ebido) y N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'F', el pedido lleva reembolso y se factura, 'P', reembolso pagado, 'D', reembolso debido o 'N', el pedido no lleva reembolso. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=SWTADUANA,UPPER,POSTCHANGE=FVERIFICA("SN ","Los posibles valores son S(i) N(o)"),TOOLTIP("Indicador que puede tomar los siguentes valores 'S', el pedido lleva documentación de la aduana o 'N', el pedido no lleva doumentación de la aduana. Utilizado para informar a la agencia y para la autofacturación de agencias")
CAMPO=ACTIVO
CAMPO=CODAGE,POSTCHANGE=FDESIGNACION("+CDESAGE","Código de agencia no existe."),TOOLTIP("Es el Código de la agencia que transportará el pedido. Deberá existir en la tabla de agencias. A su derecha aparece el tipo de la agencia, N=normal, F=frío o A=ambos y el nombre completo de la misma. El tipo de agencia debe ser compatible con los artículos del pedido, en caso contrario el programa de carga de la interfase del HOST lo dejará en estado erroneo: ERROR ASIGNANDO AGENCIA")
CAMPO=DESAGE,NOENTER,AUXILIAR,TOOLTIP("Nombre completo de la agencia")
CAMPO=RECARGOAGE,TOOLTIP("Cantidad adicional a pagar a la agencia. Utilizado para la autofacturación de agencias")
CAMPO=TPCVERIF
CAMPO=OBSERVACIONES,TOOLTIP("observaciones al cliente")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación. Es utilizado para depuración y control de los registros en las tablas")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación. Es utilizado para depuración y control de los registros en las tablas")

CURSOR=CVERIFCODAGE SELECT :CODAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE
                     UNION 
                   SELECT :CODAGE FROM DUAL WHERE :CODAGE IS NULL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CDESAGE SELECT DESAGE
                 FROM VDAGENCIA
                WHERE CODAGE=:CODAGE;

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

CURSOR=CINICIALIZA SELECT '' TIPOPEDIDO, 'ESP' IDIOMAETIQ, 'ESP' IDIOMADOC, 'S' SWTVALORADO, 1 NUMALBA, 'S' SWTTOTALES,
                          'N' SWTPROFORMA, 'P' INDPORTES, 'N' SWTANULAR, 'N' SWTPALETIZAR, 
                          'N' SWTAGRUPAR, 50 PRIORIDAD, 50 URGENCIA, 'N' SWTMODELO, '' REFMODELO,
                          DECODE(:CODPAIS,NULL,'034',:CODPAIS) CODPAIS, 
                          DECODE(:CODPAISFACTU,NULL,'034',:CODPAISFACTU) CODPAISFACTU,
                          'T' BACKORDER, 'N' SWTFACTU, 'N' SWTSEGURO, 'N' SWTEDI, 'N' SWTREEMBOLSO, 'N' SWTADUANA
                          FROM DUAL;

CURSOR=CDESDIV SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CLISTADIV SELECT CODDIV,DESDIV,DESEMP FROM VDDIVIS DIV,VDEMPRE EMP WHERE EMP.CODEMP=DIV.CODEMP AND DIV.SWTACTIVA='S' ORDER BY CODDIV;

CURSOR=CSELINI SELECT NVL(:SWTFACTU,'N') SWTFACTU, NVL(:SWTPALETIZAR,'N') SWTPALETIZAR, NVL(:SWTADUANA,'N') SWTADUANA FROM DUAL;

CURSOR=CSELRUTA SELECT DESRUTA FROM VDRUTAS WHERE CODRUTA=:CODRUTA;

CURSOR=CRUTAS SELECT CODRUTA,DESRUTA FROM VDRUTAS;


CONTEXTUAL=FLEEMENU("VDCLIENTES.ZOO")

TECLA=F7,FDESIGNACION("CINICIALIZA","ERROR INICIALIZANDO DATOS")

AYUDA=MANTENIMIENTO DE CLIENTES
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F5} Borrar pantalla
              {F9} Borrar registro {Ctrl-F7} Copia {Esc} Salir;

