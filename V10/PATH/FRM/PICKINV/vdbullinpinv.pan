###################################################################
#Módulo: VDBULLINPINV.PAN
#Funcionalidad : Mantenimiento de líneas de bultos de picking inverso
#Autor: Maite González      
#Fecha: 03-06-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE MOVIMIENTOS DEL BULTO DE PICKING INVERSO
Mov.      Artículo                           Lote             Cantidad       Estado                  Fecha Preparación            Ultima modificación              Comentario
@L@@@@@@@ _40__________ _100________________ _40_____________ #L#,###,###.## @L@@@ _30______________ _32____  ¿D-MM-YY.Y ________ _32________  ¿D-MM-YY.Y ________ @@@@ 
|
TABLA=VDMOVIM


PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")


ORDERBY=CODMOV;

CAMPO=CODBULTOORI,VIRTUAL("CODBULTO"),OCULTO
CAMPO=CODMOV,NOUPDATE,TOOLTIP("Secuencial de línea en el bulto"),TITULO("Línea")
CAMPO=CODART,NOUPDATE,UPPER,POSTCHANGE=FDESIGNACION("CDESART","Código de artículo no existe."),TOOLTIP("Código del artículo"),TITULO("Artículo")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER,TOOLTIP("Descripción del artículo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote del artículo servido contenido en el bulto"),TITULO("Lote")
CAMPO=CANTIDAD,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE,TOOLTIP("Cantidad"),TITULO("Cantidad")
CAMPO=STATUS,TOOLTIP("Estado de la línea de bulto.\n :DESSTATUS"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),TITULO("Estado")
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOUPDATE,TOOLTIP("Descripción del estado")
CAMPO=CODOPEEJEMOV,NOENTER,TOOLTIP("Operario que prepara la línea")
CAMPO=FECINIMOV,NOENTER,TOOLTIP("Fecha de la preparación"),TITULO("Fecha preparación")
CAMPO=HORAINIMOV,NOENTER,TOOLTIP("Hora de la preparación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la línea del bulto"),TITULO("Comen")

CURSOR=CSELMOV SELECT CODMOV FROM VDMOVIM WHERE CODMOV=:CODMOV AND :STATUS<>VDST.FBPLANULADA;

CURSOR=CSELCODBULTO SELECT CODBULTO CODBULTOCLI FROM VDBULTOLIN WHERE CODMOV=:CODMOV;

CURSOR=CDESART SELECT DESART
                 FROM VDARTIC
                WHERE CODART=:CODART;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='MOV';
 
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;






