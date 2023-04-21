###################################################################
#Módulo: VDBULLIN.PAN
#Funcionalidad : Mantenimiento de líneas de bultos
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Histórico de cambios:
MANTENIMIENTO DE LINEAS DE BULTO
Línea    Artículo                                Lote       Movimiento Ubicación  Z. A servir    Servida      Uni Estado                 Fecha Preparación            Ultima modificación              Comentario
@L@@@@@@ _40_________ _100_____________________  _40_______ @@@@@@@@@  _20_______ @L #L#,###,### #L#,###,###  _10 @L@@@  _30____________ _32____  ¿D-MM-YY.Y ________ _32________  ¿D-MM-YY.Y ________ @@@@@@@@ 
|
TABLA=VDBULTOLIN

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

#PROTECT("SUPALMACEN")

ORDERBY=CODBULTO,SEQLINEA;

CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=SEQLINEA,NOUPDATE,TOOLTIP("Secuencial de línea en el bulto"),TITULO("NºLínea")
CAMPO=CODART,NOUPDATE,UPPER,POSTCHANGE=FDESIGNACION("CDESART","Código de artículo no existe."),TOOLTIP("Código del artículo"),TITULO("Artículo")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER,TOOLTIP("Descripción del artículo"),TITULO("Designación del artículo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote del artículo servido contenido en el bulto"),TITULO("Lote")
#,POSTCHANGE=FEJECUTA("CSELCADUCI","")
#CAMPO=CADUCI,AUXILIAR,NOENTER,TOOLTIP("Caducidad del lote servido")
CAMPO=CODMOV,NOUPDATE,POSTCHANGE=FDESIGNACION("CSELCODUBI","Error obteniendo ubicación origen del movimiento :CODMOV"),TOOLTIP("Movimiento de reserva"),TITULO("Movimiento"),WLONX=20
CAMPO=CODUBI,AUXILIAR,NOENTER,TOOLTIP("Ubicación en :CODAREA"),TITULO("Ubicación")
CAMPO=CODZONA,AUXILIAR,NOENTER,TOOLTIP("Ubicación en :CODAREA"),TITULO("Zona"),WLONX=20
CAMPO=CODAREA,AUXILIAR,OCULTO,"_20_"
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE("V10"),TOOLTIP("Cantidad pedida "),TITULO("A servir")
CAMPO=CANTSERVIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE("V10"),TOOLTIP("Cantidad servida"),TITULO("Servida")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER,TOOLTIP("Unidades, :UNIDADESHOST ,en que mide el host la cantidad pedida.\nEn la interfase de salida indicaremos\nla cantidad servida en las mismas unidades"),TITULO("Uni."),WLONX=10
CAMPO=STATUS,TOOLTIP("Estado de la línea de bulto.\n :DESSTATUS"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),TITULO("Estado"),WLONX=15
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOUPDATE,TOOLTIP("Descripción del estado"),TITULO("Desc.")
CAMPO=CODOPEPREPARA,NOENTER,TOOLTIP("Operario que prepara la línea"),TITULO("Preparación")
CAMPO=FECPREPARA,NOENTER,TOOLTIP("Fecha de la preparación")
CAMPO=HORAPREPARA,NOENTER,TOOLTIP("Hora de la preparación")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("Código de los comentarios a la línea del bulto"),TITULO("Comen")


CURSOR=CSELCODUBI SELECT CODUBIORI CODUBI,CODAREA,CODZONA FROM VDUBICA UBI,VDMOVIM MOV
                   WHERE MOV.CODMOV=:CODMOV AND UBI.CODUBI=MOV.CODUBIORI;

CURSOR=CDESART SELECT DESART,UNIDADESHOST
                 FROM VDARTIC
                WHERE CODART=:CODART;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUL';
 
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELCADUCI SELECT CADUCI FROM VDLOTES WHERE CODART = :CODART AND CODLOT = :CODLOT
                   UNION
                  SELECT NULL CADUCI FROM DUAL WHERE :CODLOT IS NULL;





