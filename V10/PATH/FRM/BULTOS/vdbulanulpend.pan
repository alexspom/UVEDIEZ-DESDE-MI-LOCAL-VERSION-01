###################################################################
#M�dulo: VDBULANULPEND.PAN
#Funcionalidad : Anulaci�n de cantidades pendientes de servir
#Autor: JMM      
#Fecha: 04-07-2008
###################################################################
# Hist�rico de cambios:
ANULACION DE CANTIDADES PENDIENTES DE SERVIR
L�nea    Art�culo                              Lote            A servir       Regularizar     Unids.  Estado                   Ultima modificaci�n              
@L@@@@@@ _40____________ _100________________  _40____________ #L#,###,###.## #L#,###,###.##  _10____ @L@@@  _30______________ _32________  �D-MM-YY.Y ________ 
|
TABLA=VDBULTOLIN

WHERE=STATUS=100;

PREUPDATE=FEJECUTA("CCHECKCANTIDAD","LA CANTIDAD A REGULARIZAR NO PUEDE SER MAYOR QUE LA PENDIENTE DE SERVIR",
                   FANULCANTPENDIENTE(":CODBULTO",":SEQLINEA",":CANTAREGULARIZAR"),"ERROR EN FANULCANTPENDIENTE\n :V10ERROR",
                   FIF("-CCHECKLINEASPEND",FIF("CCHECKLINEASSERV","CUPDSTABULTOVERIF","CUPDSTABULTOANUL")),"ERROR DETERMINANDO ESTADO DEL BULTO",
                   FIF("-CCHECKPEDIDO","CUPDSTAPEDANUL",
                                       FEJECUTA("@-CCHECKBULPEND","",
                                                "CSELBULPEND","ERROR SELECCIONANDO BULTO PENDIENTE",
                                                "CUPDSTABULTPED","ERROR ACTUALIZANDO ESTADO DE BULTO PENDIENTE",
                                                %FFAILURE,"BUSQUE EL BULTO :BULTOPEND\n Y LLEVELO A VERIFICACION")),"ERROR AL TRATAR EL PEDIDO DEL BULTO",
                  +FCOMMIT,"",
                   %FFAILURE,"ANULACION REALIZADA CON �XITO")

                   


ORDERBY=SEQLINEA;

CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=SEQLINEA,NOUPDATE,TOOLTIP("Secuencial de l�nea en el bulto"),TITULO("L�nea")
CAMPO=CODART,NOUPDATE,UPPER,POSTCHANGE=FDESIGNACION("CDESART","C�digo de art�culo no existe."),TOOLTIP("C�digo del art�culo"),TITULO("Art�culo")
CAMPO=DESART,AUXILIAR,UPPER,NOENTER,TOOLTIP("Descripci�n del art�culo")
CAMPO=CODLOT,NOUPDATE,TOOLTIP("Lote del art�culo servido contenido en el bulto"),TITULO("Lote")
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),NOENTER,TOOLTIP("Cantidad pedida "),TITULO("A servir")
CAMPO=CANTAREGULARIZAR,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),AUXILIAR,TOOLTIP("Cantidad a regularizar"),TITULO("Regularizar")
CAMPO=UNIDADESHOST,AUXILIAR,NOENTER,TITULO("Unids.")
CAMPO=STATUS,TOOLTIP("Estado de la l�nea de bulto.\n :DESSTATUS"),POSTCHANGE=FDESIGNACION("CSELSTATUS","Estado no existe"),TITULO("Estado")
CAMPO=DESSTATUS,UPPER,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del estado")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiz� la �ltima modificaci�n"),TITULO("Ultima modificaci�n")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificaci�n")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificaci�n")

CAMPO=CODPED,AUXILIAR,VIRTUAL,OCULTO
CAMPO=ANOPED,AUXILIAR,VIRTUAL,OCULTO
CAMPO=SEQPED,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODDIV,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODMOV,OCULTO,"@L@@@@@@@"
CAMPO=BULTOPEND,AUXILIAR,OCULTO,"_18_"

CURSOR=CDESART SELECT DESART, UNIDADESHOST
                 FROM VDARTIC
                WHERE CODART=:CODART;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='BUL';

CURSOR=CCHECKCANTIDAD SELECT :CANTPEDIDA FROM DUAL WHERE :CANTPEDIDA >= :CANTAREGULARIZAR;

CURSOR=CCHECKLINEASPEND SELECT :CODBULTO FROM VDBULTOLIN WHERE CODBULTO = :CODBULTO AND STATUS = VDST.FBULASERVIR;

CURSOR=CCHECKLINEASSERV SELECT :CODBULTO FROM VDBULTOLIN WHERE CODBULTO = :CODBULTO AND STATUS = VDST.FBULSERVIDA AND CANTSERVIDA > 0;

CURSOR=CUPDSTABULTOVERIF UPDATE VDBULTOCAB 
                            SET STATUS = VDST.FBUCAVERIF, CODOPEMODIF = VDUSER.GETUSER,
                                FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                          WHERE CODBULTO = :CODBULTO;

CURSOR=CUPDSTABULTOANUL UPDATE VDBULTOCAB 
                           SET STATUS = VDST.FBUCANULADO,PESOTEORICO=0,VOLUMEN=0,
                               CODOPEMODIF = VDUSER.GETUSER,FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                         WHERE CODBULTO = :CODBULTO;

CURSOR=CCHECKPEDIDO SELECT :CODPED 
                      FROM VDBULTOCAB 
                     WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND
                           SEQPED = :SEQPED AND ANOPED = :ANOPED AND
                           STATUS != VDST.FBUCANULADO; 

CURSOR=CUPDSTAPEDANUL UPDATE VDPEDIDOCAB 
                         SET STATUS = 6200,CODSERIEPREP=NULL,CODSERIEEXP=NULL,FECTERMIN=VD.FECHASYS, CODOPEMODIF = VDUSER.GETUSER,
                             FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                       WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND
                             SEQPED = :SEQPED AND ANOPED = :ANOPED;
                           
 
CURSOR=CCHECKBULPEND SELECT :CODPED
                       FROM VDBULTOCAB 
                      WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND
                            ANOPED = :ANOPED AND SEQPED = :SEQPED AND 
                            STATUS <= VDST.FBUCAVERIF;

CURSOR=CSELBULPEND SELECT CODBULTO BULTOPEND
                     FROM VDBULTOCAB 
                    WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND
                          ANOPED = :ANOPED AND SEQPED = :SEQPED AND 
                          STATUS BETWEEN VDST.FBUCAVERIF AND VDST.FBUCFINALIZADO
                    ORDER BY FECMODIF DESC, TO_DATE(HORAMODIF,'HH24:MI:SS') DESC;

CURSOR=CUPDSTABULTPED UPDATE VDBULTOCAB 
                         SET STATUS = VDST.FBUCAVERIF, CODOPEMODIF = VDUSER.GETUSER,
                             FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                       WHERE CODBULTO = :BULTOPEND;





