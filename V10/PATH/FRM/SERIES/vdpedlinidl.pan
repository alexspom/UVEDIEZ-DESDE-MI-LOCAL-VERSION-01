###################################################################
#Módulo: VDPEDLINIDL.PAN
#Funcionalidad : Mantenimiento de líneas de pedido
#Autor: RFD
#Fecha:26-03-2008
###################################################################
#Histórico de cambios:
LINEAS DE PEDIDO
 Sec      Artículo                                         Pedida    A servir    Servida. Estado Ultima modificación
 @L@@@@@@ _20__________ _40_____________________________ #L#,###.## #L#,###.## #L#,###.## @L@@@  _32_______ ¿D-MM-YY ________
|

TABLA=VDPEDIDOLIN
ORDERBY=SEQLINEA;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

PROTECT("ADMINISTRADOR")
NODELETE
CAMPO=CODDIV,VIRTUAL,OCULTO
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO
CAMPO=SEQPED,VIRTUAL,OCULTO

CAMPO=SEQLINEA,TOOLTIP("Número secuencial de linea"),TITULO("NºLínea")
CAMPO=CODART,UPPER,TOOLTIP("Es el Código del artículo a servir"),TITULO("Artículo"),
        POSTCHANGE=FDESIGNACION("CDESART","Código de artículo no existe.")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER
CAMPO=CODLOT,UPPER,TOOLTIP("Es el lote del artículo.\nSi viene informado se servirá dicho lote,\nen caso contrario el sistema decide el lote a servir."),TITULO("Lote"),OCULTO,"_20_________"
CAMPO=CADUCI,UPPER,TOOLTIP("Caducidad del lote servido"),TITULO("Caducidad"),WLONX=20,OCULTO,"_8______"
CAMPO=UNIDADESHOST,TOOLTIP("Unidades, :UNIDADESHOST ,en que mide el host la cantidad pedida.\nEn la interfase de salida indicaremos\nla cantidad servida en las mismas unidades"),TITULO("Uni"),WLONX=10,OCULTO,"_10"
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE,TOOLTIP("Cantidad pedida "),TITULO("Pedida")
CAMPO=CANTASERVIR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TOOLTIP("Cantidad a servir"),TITULO("A servir")
CAMPO=CANTSERVIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE,TOOLTIP("Cantidad servida"),TITULO("Servida")
CAMPO=STATUS,TOOLTIP("Estado de la línea de pedido según tabla de estados tipo LP"),TITULO("Estado"),WLONX=20
CAMPO=DESSTATUS,AUXILIAR,OCULTO,"_30_"
CAMPO=IVA,TOOLTIP("Porcentaje de IVA sobre el producto"),TITULO("IVA &euro;"),OCULTO,"#L#.##"
CAMPO=RECARGO,TOOLTIP("Porcentaje de recargo de equivalencia"),TITULO("Rec &euro;"),OCULTO,"#L#.##"
CAMPO=DCTO,TOOLTIP("Porcentaje de descuento sobre el precio"),TITULO("Dcto &euro;"),OCULTO,"#L#.##"
CAMPO=PRECIOUNI,CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART"),TOOLTIP("Indicador de dónde se toma el precio: 'L' del campo PRECIOUNI de la línea, 'M' del campo PRECIOUNI del maestro de artículos."),TITULO("Precio &euro;"),OCULTO,"#L#,###,#.###"
CAMPO=UNIDADESPRECIO,WLONX=20,TOOLTIP("Unidades del precio."),TITULO("Uds. Precio"),OCULTO,"_10______"
CAMPO=OPCIONPRECIO,TOOLTIP("Indicador de precio, que indica de dónde se toma el precio.\nL=del campo PRECIOUNI de la línea.\nM=del campo PRECIOUNI del maestro de artículos."),TITULO("P"),OCULTO,"_"
CAMPO=BACKORDER,TOOLTIP("Indicador de la política de preparación de la línea.Puede ser 'E' Exacta se debe servir en su totalidad o 'P' puede servir parcial"),TITULO("B"),OCULTO,"_"
CAMPO=SWTCREAVERSION,TOOLTIP("Indica si debe crear otra versión del pedido con el resto de la línea.\nPuede ser,\nS=Crear versión con cantidad pendiente.\nN=No crea versión con resto"),TITULO("C"),OCULTO,"_"
CAMPO=MARCARPT,TOOLTIP("Indicador que permite poner una marca (p.e. un asterisco) para alguna aclaración en cualquier report asociado al pedido"),TITULO("M"),OCULTO,"_"
CAMPO=TIPOREDONDEO,TOOLTIP("Tipo de redondeo. 'N' no existe redondeo, 'C' contenedor, 'E' cajas por exceso, 'D' cajas por defecto"),TITULO("R"),OCULTO,"_"
CAMPO=CODAGRUPA,TOOLTIP("En las líneas en que está informado y con igual valor indica que las líneas están realcionadas"),TITULO("Agrup."),OCULTO,"_20____________"
CAMPO=MARCASTK,TOOLTIP("Marca del stock. Si se informa el sistema reservará, exclusivamente, stock con esta marca."),TITULO("Marca Stock"),OCULTO,"_60____________"
CAMPO=NUMEROSERIE,WLONX=20,TOOLTIP("Número de serie de la mercancía"),TITULO("Núm Serie"),OCULTO,"_60____________"
CAMPO=CODCOMEN,TOOLTIP("Código de los comentarios a la línea del pedido"),TITULO("Comen"),OCULTO,"@L@@@@@@@"
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiza la modificación"),TITULO("Ultima Modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la última modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")
CAMPO=VDEXTRA,OCULTO,"__250____"



CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART=:CODART;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CONTEXTUAL=FLEEMENU("VDPEDLIN.ZOO")





