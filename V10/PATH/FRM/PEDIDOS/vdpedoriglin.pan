###################################################################
#MOdulo: VDPEDIDORIGLIN.PAN
#Funcionalidad : Mantenimiento de líneas de pedido originales     
#Autor: RFD      
#Fecha:26-03-2008
###################################################################
# HistOrico de cambios:
#
LINEAS DE PEDIDO
Sec      Artículo                          Lote     Caduc. Uni Pedida      Pedida Cli. Ped. Host IVA    Recar. Dcto   Precio        Uds.Precio P B C M R Agrup. Marca stk.    NºSerie   Comentario Lin.Orig  Status Ultima modificación
@L@@@@@@ _40_______ _100__________________ _40_____ _8____ _10 #L#,###,### #L#,###,### _60______ #L#.## #L#.## #L#.## #L#,###,#.### _10______  _ _ _ _ _ _10___ _60__________ _60______ @L@@@@@@@  @L@@@@@@@ @L@@@  _32_______ ¿D-MM-YY ________
|

TABLA=VDPEDIDORIGLIN
ORDERBY=SEQLINEA;

#NODELETE

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
                   


CAMPO=CODDIV,VIRTUAL,OCULTO
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO
CAMPO=SEQPED,VIRTUAL,OCULTO

CAMPO=SEQLINEA,TOOLTIP("Número secuencial de linea"),TITULO("NºLínea")
CAMPO=CODART,UPPER,TOOLTIP("Es el Código del artículo a servir"),TITULO("Cod.Art."),
        POSTCHANGE=FDESIGNACION("+CDESART","Código de artículo no existe.")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER,TITULO("Artículo")
CAMPO=CODLOT,UPPER,TOOLTIP("Es el lote del artículo.\nSi viene informado se servirá dicho lote,\nen caso contrario el sistema decide el lote a servir."),TITULO("Lote")
CAMPO=CADUCI,UPPER,TOOLTIP("Caducidad del lote servido"),TITULO("Caducidad"),WLONX=30
CAMPO=UNIDADESHOST,TOOLTIP("Unidades, :UNIDADESHOST ,en que mide el host la cantidad pedida.\nEn la interfase de salida indicaremos\nla cantidad servida en las mismas unidades"),TITULO("Uni"),WLONX=10
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TOOLTIP("Cantidad pedida por el host"),TITULO("Pedida")
CAMPO=CANTPEDIDACLI,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TOOLTIP("Cantidad pedida por el cliente"),TITULO("Pedida Cli")
CAMPO=PEDIDOHOST,TOOLTIP("Agrupación para servir en volumetrias de picking separado"),TITULO("")
CAMPO=IVA,TOOLTIP("Porcentaje de IVA sobre el producto"),TITULO("IVA &euro;")
CAMPO=RECARGO,TOOLTIP("Porcentaje de recargo de equivalencia"),TITULO("Rec &euro;")
CAMPO=DCTO,TOOLTIP("Porcentaje de descuento sobre el precio"),TITULO("Dcto &euro;")
CAMPO=PRECIOUNI,CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART"),TOOLTIP("Indicador de dOnde se toma el precio: 'L' del campo PRECIOUNI de la línea, 'M' del campo PRECIOUNI del maestro de artículos."),TITULO("Precio &euro;")
CAMPO=UNIDADESPRECIO,TOOLTIP("Unidades del precio."),TITULO("Uds.Precio")
CAMPO=OPCIONPRECIO,TOOLTIP("Indicador de precio, que indica de dónde se toma el precio.\nL=del campo PRECIOUNI de la línea.\nM=del campo PRECIOUNI del maestro de artículos."),TITULO("P")
CAMPO=BACKORDER,TOOLTIP("Indicador de la política de preparación de la línea.Puede ser 'E' Exacta se debe servir en su totalidad o 'P' puede servir parcial"),TITULO("B")
CAMPO=SWTCREAVERSION,TOOLTIP("Indica si debe crear otra versión del pedido con el resto de la línea.\nPuede ser,\nS=Crear versiOn con cantidad pendiente.\nN=No crea versiOn con resto"),TITULO("C")
CAMPO=MARCARPT,TOOLTIP("Indicador que permite poner una marca (p.e. un asterisco) para alguna aclaración en cualquier report asociado al pedido"),TITULO("M")
CAMPO=TIPOREDONDEO,TOOLTIP("Tipo de redondeo. 'N' no existe redondeo, 'C' contenedor, 'E' cajas por exceso, 'D' cajas por defecto"),TITULO("R")
CAMPO=CODAGRUPA,TOOLTIP("En las líneas en que está informado y con igual valor indica que las líneas están realcionadas"),TITULO("Agrup.")
CAMPO=MARCASTK,TOOLTIP("Marca del stock. Si se informa el sistema reservará, exclusivamente, stock con esta marca."),TITULO("Marca Stock")
CAMPO=NUMEROSERIE,TOOLTIP("Número de serie de la mercancía"),TITULO("Nº Serie")
CAMPO=CODCOMEN,TOOLTIP("Código de los comentarios a la línea del pedido"),TITULO("Comen")
CAMPO=SEQLINORIG
CAMPO=STATUS,TOOLTIP("Estado de la línea de pedido según tabla de estados tipo LP"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,OCULTO,"_30_"
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")

CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART=:CODART;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;




