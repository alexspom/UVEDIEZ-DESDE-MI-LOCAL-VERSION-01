# M�dulo   : VDSTOCK.PAN
# Funci�n  : Mantenimiento de stock
#
# Creaci�n : 01-10-2007
# Autor    : EAA
###########################################
# Hist�rico de cambios:
MANTENIMIENTO DE STOCK
Orden  Art�culo       Designaci�n                  Lote          Cantidad  Ultima modificaci�n              Uni/emb E/con Bloqueos   Tipo     Precio        Extra           Coment.
@L9@@@ _40___________ _100________________________ _40__________ #L15##### _32________ �D-MM-Y.YY  ________ #L15### #L### __________ _10_____ #L12#####.### _255___________ @L@@@@@@@
|
TABLA=VDSTOCK
ORDERBY=ORDENSTK;
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")

#NODELETE
NOUPDATE,PROTECT("ADMINISTRADOR")


CAMPO=CODMAT,VIRTUAL,OCULTO
CAMPO=ORDENSTK,TOOLTIP("Orden de la l�nea de stock en el contenedor"),TITULO("Orden")
CAMPO=CODART,NOUPDATE,TOOLTIP("C�digo del art�culo"),POSTCHANGE=FDESIGNACION("CSELDESART","No existe art�culo"),
#                         CONTEXTUAL=FEJECUTAFORM("VDSELART","N","","","CODART=:CODART","Selecci�n de art�culo","S"),
                         TITULO("Art�culo")
CAMPO=DESART,NOUPDATE,AUXILIAR,NOENTER,TOOLTIP("Desgianci�n del articulo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote"),POSTCHANGE=FDESIGNACION("CSELCODLOT","No existe lote"),
#                        CONTEXTUAL=FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT","Selecci�n de lote","S"),
                         TITULO("Lote")
CAMPO=CANTIDAD,NOUPDATE("V10"),TOOLTIP("Cantidad en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Cantidad")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
																							 
																															 
													
CAMPO=CADUCI,NOUPDATE,AUXILIAR,NOENTER,WLONX=20,OCULTO,"________"
CAMPO=UNIEMB,TOOLTIP("Unidades por embalaje en unidades host"),CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Uni/Emb"), WLONX=20
CAMPO=EMBCONT,PROTECT("STOCK"), TOOLTIP("Embalajes por contenedor"),TITULO("Emb/C"),WLONX=20
CAMPO=BLOQUEOS,TOOLTIP("Bloqueos del stock"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEO",":ERROR"),TITULO("Bloqueos")
CAMPO=TIPOEMBA,NOUPDATE,TOOLTIP("Tipo de embalaje"),POSTCHANGE=FDESIGNACION("CSELTIPOEMBA","No existe tipo de embalaje"),TITULO("Tipo Emba"),WLONX=20
CAMPO=PRECIOUNI,NOUPDATE,TOOLTIP("Precio unitario del producto en unidades host"),CONVIERTE=FCONVIERTEINVARTFROMDB(":CODART");FCONVIERTEINVART2DB(":CODART"),TITULO("PrecioUni")
CAMPO=VDEXTRA,NOUPDATE,TOOLTIP("Informaci�n extra disponible para el implantador"),TITULO("Extra")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("C�digo de comentario del contenedor"),TITULO("Comen")
CAMPO=ERROR,AUXILIAR,OCULTO,"_255"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELDESART BEGIN
                   SELECT DESART INTO :DESART
                      FROM VDARTIC WHERE CODART=:CODART;
                  END;@
CURSOR=CSELCODLOT SELECT :CODLOT,CADUCI FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT;

CURSOR=CSELTIPOEMBA SELECT :TIPOEMBA FROM VDTIPOEMBA WHERE TIPOEMBA=:TIPOEMBA;

CURSOR=CVERBLOQUEO SELECT VDART.VALIDABLOQUEO(:BLOQUEOS) ERROR FROM DUAL WHERE VDART.VALIDABLOQUEO(:BLOQUEOS) IS NOT NULL;


TECLA=SF9,FEJECUTAFORM("VDREGULARIZASTK","S","CODMAT=:CODMAT AND ORDENSTK=:ORDENSTK","","","REGULARIZACIONES DE STOCK","S")


