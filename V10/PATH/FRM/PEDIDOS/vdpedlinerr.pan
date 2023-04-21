###################################################################
#Módulo: VDPEDLIN.PAN
#Funcionalidad : Mantenimiento de líneas de pedido     
#Autor: RFD      
#Fecha:26-03-2008
###################################################################
#Histórico de cambios:
LINEAS DE PEDIDO
Sec      Artículo                         Lote     Caduc.   Uni Pedida          Status IVA    Recar. Dcto   Precio        Uds.Precio P B C M R Expositor       Marca stk.    NºSerie   Comentario Ultima modificación           VDExtra
@L@@@@@@ _40_____________ _100___________ _40_____ _8______ _10 #L#,###,###.##  @L@@@  #L#.## #L#.## #L#.## #L#,###,#.### _10______  _ _ _ _ _ _20____________ _60__________ _60______ @L@@@@@@@   _32_______ ¿D-MM-YY ________  __250____
|

TABLA=VDPEDIDORIGLIN
ORDERBY=SEQLINEA;

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
                
PROTECT("ADMINISTRADOR")

CAMPO=CODDIV,VIRTUAL,OCULTO
CAMPO=ANOPED,VIRTUAL,OCULTO
CAMPO=CODPED,VIRTUAL,OCULTO

CAMPO=SEQLINEA,TOOLTIP("Número secuencial de linea"),TITULO("Sec Linea")
CAMPO=CODART,UPPER,TOOLTIP("Es el Código del artículo a servir"),TITULO("Artículo"),
        POSTCHANGE=FDESIGNACION("+CDESART","Código de artículo no existe.")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER
CAMPO=CODLOT,UPPER,TOOLTIP("Es el lote del artículo.\nSi viene informado se servirá dicho lote,\nen caso contrario el sistema decide el lote a servir."),TITULO("Lote")
CAMPO=CADUCI,UPPER,TOOLTIP("Caducidad del lote servido"),TITULO("Caduci")
CAMPO=UNIDADESHOST,TOOLTIP("Unidades, :UNIDADESHOST ,en que mide el host la cantidad pedida.\nEn la interfase de salida indicaremos\nla cantidad servida en las mismas unidades"),TITULO("Uni")
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE,TOOLTIP("Cantidad pedida "),TITULO("Pedida")
CAMPO=STATUS,TOOLTIP("Estado de la línea de pedido según tabla de estados tipo LP"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,OCULTO,"_30_"
CAMPO=IVA,TOOLTIP("Porcentaje de IVA sobre el producto"),TITULO("IVA &euro;")
CAMPO=RECARGO,TOOLTIP("Porcentaje de recargo de equivalencia"),TITULO("Rec &euro;")
CAMPO=DCTO,TOOLTIP("Porcentaje de descuento sobre el precio"),TITULO("Dcto &euro;")
CAMPO=PRECIOUNI,CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART"),TOOLTIP("Indicador de dónde se toma el precio: 'L' del campo PRECIOUNI de la línea, 'M' del campo PRECIOUNI del maestro de artículos."),TITULO("Precio &euro;")
CAMPO=UNIDADESPRECIO,TOOLTIP("Unidades del precio."),TITULO("Uds. Precio")
CAMPO=OPCIONPRECIO,TOOLTIP("Indicador de precio, que indica de dónde se toma el precio.\nL=del campo PRECIOUNI de la línea.\nM=del campo PRECIOUNI del maestro de artículos."),TITULO("P")
CAMPO=BACKORDER,TOOLTIP("Indicador de la política de preparación de la línea.Puede ser 'E' Exacta se debe servir en su totalidad o 'P' puede servir parcial"),TITULO("B")
CAMPO=SWTCREAVERSION,TOOLTIP("Indica si debe crear otra versión del pedido con el resto de la línea.\nPuede ser,\nS=Crear versión con cantidad pendiente.\nN=No crea versión con resto"),TITULO("C")
CAMPO=MARCARPT,TOOLTIP("Indicador que permite poner una marca (p.e. un asterisco) para alguna aclaración en cualquier report asociado al pedido"),TITULO("M")
CAMPO=TIPOREDONDEO,TOOLTIP("Tipo de redondeo. 'N' no existe redondeo, 'C' contenedor, 'E' cajas por exceso, 'D' cajas por defecto"),TITULO("R")
CAMPO=CODAGRUPA,TOOLTIP("En las líneas en que está informado y con igual valor indica que las líneas están realcionadas"),TITULO("Agrup.")
CAMPO=MARCASTK,TOOLTIP("Marca del stock. Si se informa el sistema reservará, exclusivamente, stock con esta marca."),TITULO("Marca Stock")
CAMPO=NUMEROSERIE,TOOLTIP("Número de serie de la mercancía"),TITULO("Número de serie")
CAMPO=CODCOMEN,TOOLTIP("Código de los comentarios a la línea del pedido"),TITULO("Comen")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")
CAMPO=VDEXTRA



CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART=:CODART;


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;






