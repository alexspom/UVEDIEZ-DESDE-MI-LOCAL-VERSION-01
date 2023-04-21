###################################################################
#M�dulo: VDBULLIN.PAN
#Funcionalidad : Mantenimiento de l�neas de bultos
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# Hist�rico de cambios:
MANTENIMIENTO DE LINEAS DE BULTO
L�nea    Art�culo                                Lote       Movimiento Ubicaci�n  Z. A servir    Servida      Uni Estado                 Fecha Preparaci�n            Ultima modificaci�n              Comentario
@L@@@@@@ _40_________ _100_____________________  _40_______ @@@@@@@@@  _20_______ @L #L#,###,### #L#,###,###  _10 @L@@@  _30____________ _32____  �D-MM-YY.Y ________ _32________  �D-MM-YY.Y ________ @@@@@@@@ 
|
TABLA=VDBULTOLIN

PREINSERT=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR OBTENIENDO LA FECHA DE MODIFICACION")

#PROTECT("SUPALMACEN")

ORDERBY=CODBULTO,SEQLINEA;

CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=SEQLINEA,NOUPDATE,TOOLTIP("Secuencial de l�nea en el bulto"),TITULO("N�L�nea")
CAMPO=CODART,NOUPDATE,UPPER,POSTCHANGE=FDESIGNACION("CDESART","C�digo de art�culo no existe."),TOOLTIP("C�digo del art�culo"),TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER,TOOLTIP("Descripci�n del art�culo"),TITULO("Designaci�n del art�culo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote del art�culo servido contenido en el bulto"),TITULO("Lote")
#,POSTCHANGE=FEJECUTA("CSELCADUCI","")
#CAMPO=CADUCI,AUXILIAR,NOENTER,TOOLTIP("Caducidad del lote servido")
CAMPO=CODMOV,NOUPDATE,POSTCHANGE=FDESIGNACION("CSELCODUBI","Error obteniendo ubicaci�n origen del movimiento :CODMOV"),TOOLTIP("Movimiento de reserva"),TITULO("Movimiento"),WLONX=20
CAMPO=CODUBI,AUXILIAR,NOENTER,TOOLTIP("Ubicaci�n en :CODAREA"),TITULO("Ubicaci�n")
CAMPO=CODZONA,AUXILIAR,NOENTER,TOOLTIP("Ubicaci�n en :CODAREA"),TITULO("Zona"),WLONX=20
CAMPO=CODAREA,AUXILIAR,OCULTO,"_20_"
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE("V10"),TOOLTIP("Cantidad pedida "),TITULO("A servir")
CAMPO=CANTSERVIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOUPDATE("V10"),TOOLTIP("Cantidad servida"),TITULO("Servida")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER,TOOLTIP("Unidades, :UNIDADESHOST ,en que mide el host la cantidad pedida.\nEn la interfase de salida indicaremos\nla cantidad servida en las mismas unidades"),TITULO("Uni."),WLONX=10
CAMPO=STATUS,TOOLTIP("Estado de la l�nea de bulto.\n :DESSTATUS"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),TITULO("Estado"),WLONX=15
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOUPDATE,TOOLTIP("Descripci�n del estado"),TITULO("Desc.")
CAMPO=CODOPEPREPARA,NOENTER,TOOLTIP("Operario que prepara la l�nea"),TITULO("Preparaci�n")
CAMPO=FECPREPARA,NOENTER,TOOLTIP("Fecha de la preparaci�n")
CAMPO=HORAPREPARA,NOENTER,TOOLTIP("Hora de la preparaci�n")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificaci�n")
CAMPO=CODCOMEN,NOUPDATE,TOOLTIP("C�digo de los comentarios a la l�nea del bulto"),TITULO("Comen")


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





