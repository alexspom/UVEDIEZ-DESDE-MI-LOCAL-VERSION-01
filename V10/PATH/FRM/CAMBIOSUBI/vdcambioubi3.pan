# M�dulo   : VDCAMBIOUBI2.PAN
# Funci�n  : Cambios de Ubicaci�n Parciales
#
# Creaci�n : 29-02-2008
# Autor    : FGS
###########################################
# Hist�rico de cambios:
SELECCION DE L�NEA DE STOCK PARA CAMBIO DE UBICACI�N PARCIAL
Ord. Bulto                Art�culo             Lote       Marcastk    Cantidad  Cajas Pico  Uni Bloqueos   U/emb.   E/C.
@L@@ ____________________ _40_________________ _40_______ _20________ #L15##### @L@@@ @L@@@ _10 __________ #L15#.## @L@@@                 


|
  
TABLA=VDSTOCK
ORDERBY=ORDENSTK;
AQUERY

POSTQUERY=FDESIGNACION("CCALCULA","NO PUEDO CALCULAR PICO")

CURSOR=CCALCULA SELECT :CANTIDAD/:UNIEMB CAJAS,MOD(:CANTIDAD,:UNIEMB) PICO FROM DUAL;

CAMPO=CODMAT,VIRTUAL,OCULTO
CAMPO=ORDENSTK,NOENTER,TITULO("Orden")
CAMPO=BULTO,NOENTER,TITULO("Bulto")
CAMPO=CODART,NOENTER,TOOLTIP(":DESART"),POSTCHANGE=FDESIGNACION("CSELDESART","No existe articulo"),TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,NOENTER,OCULTO,"_60_______"
CAMPO=CODLOT,NOENTER,TITULO("Lote")
CAMPO=MARCASTK,NOENTER,TITULO("Marcastk")
CAMPO=CANTIDAD,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Cantidad")
CAMPO=CAJAS,NOENTER,AUXILIAR,TITULO("Cajas")
CAMPO=PICO,NOENTER,AUXILIAR,TITULO("Pico")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER,TOOLTIP("Unidades en que mide el stock el host")
CAMPO=BLOQUEOS,NOENTER,TOOLTIP("CALIFICACION DEL STOCK\n :DESBLOQUEOS "),TITULO("Bloqueos")
CAMPO=DESBLOQUEOS,AUXILIAR,OCULTO,"_400_"
CAMPO=TIPOEMBA,NOENTER,OCULTO,"_10______"
CAMPO=UNIEMB,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("U/Emb")
CAMPO=EMBCONT,NOENTER,TITULO("E/C")

CAMPO=CODCONCE,AUXILIAR,VIRTUAL,OCULTO
CAMPO=PRIOMOV,AUXILIAR,VIRTUAL,OCULTO
CAMPO=STATUS,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODMOV,AUXILIAR,VIRTUAL,OCULTO
CAMPO=TAREA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CHEQUEAFLUJOS,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CHEQUEACOMPATIBILIDAD,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODRECURSO,AUXILIAR,VIRTUAL,OCULTO

CURSOR=CSELDESART SELECT DESART,UNIDADESHOST FROM VDARTIC WHERE CODART=:CODART;







