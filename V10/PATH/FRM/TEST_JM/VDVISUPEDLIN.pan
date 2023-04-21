#*****************************************************************
#Módulo: VDVISUPEDLIN.PAN
#Funcionalidad : Consulta de las líneas de bultos
#Autor: VEGA Y JOTA
#Fecha: 05-07-2022
#*****************************************************************
#* Histórico de cambios
#* ====================
LINEAS DE BULTOS
Fecha		Hora	  Linea Articulo     Designacion       Cantidad Lote 	      Status  Descripcion				
¿D-MM-Y.YY  ________  @8@@@ _20_________ _100_____________ @15@@@@@ _20_________  @5@@@   _30______________ 
|
TABLA=VDBULTOLIN
ORDERBY=SEQLINEA ASC;

CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=FECMODIF,NOENTER,TOOLTIP("Es la fecha  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas"),TITULO("Fecha")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Es la hora  en que se efectuó alguna modificación. Es utilizado para depuración y control de los registros en las tablas"),TITULO("Hora")
CAMPO=SEQLINEA,NOENTER,TOOLTIP("Linea del pedido"),TITULO("Linea")
CAMPO=CODART,NOENTER,TOOLTIP("Articulo del pedido"),TITULO("Articulo")
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Descripcion articulo"),POSTCHANGE=FDESIGNACION("CDESART","ERROR, NO EXISTE EL ARTICULO"),TITULO("Designacion")
CAMPO=CANTPEDIDA,NOENTER,TOOLTIP("Cantidad del articulo"),TITULO("Cantidad")
CAMPO=CODLOT,NOENTER,TOOLTIP("Lote del articulo"),TITULO("Lote")
CAMPO=STATUS,NOENTER,TOOLTIP("Codigo de Estado"),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion Estado"),POSTCHANGE=FDESIGNACION("CDESSTATUS","ERROR, NO EXISTE EL STATUS"),TITULO("Descripcion")


CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='BUL' AND STATUS=:STATUS;
CURSOR=CDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;