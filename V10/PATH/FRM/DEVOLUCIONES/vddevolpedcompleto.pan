DEVOLUCION DE PEDIDO COMPLETO

 Pedido ____________________
 
 División: _20__  _40______________  
 
 Año:  @@@@  Secuencia: @@@@    Nº líneas: @@@@ 

 Cliente  _20____________ 
          _60______________________________________________________

 ÏÄ Seguimiento ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
 ³                                                                                                          ³
 ³ Captura:   ¿D-MM-Y.YYY  ________    Servicio:  ¿D-MM-Y.YYY            Grabación: ¿D-MM-Y.YYY  ________   ³
 ³ Recepción: ¿D-MM-Y.YYY  ________    Reserva:   ¿D-MM-Y.YYY  ________                                     ³
 ³ Terminado: ¿D-MM-Y.YYY  ________    Comunicado:¿D-MM-Y.YYY  ________  Entrega:   ¿D-MM-Y.YYY  ________   ³
 ³                                                                                                          ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 
 Ultima modificación: _32___________________ ¿D-MM-Y.YYY  ________

                                                                                                              |
INCLUDEFICHEROCSS="vertis.css"
TABLA=VDPEDIDOCAB
WHERE=STATUS>VDST.FPECFINALIZADO;
POSX=20
WPOSY=120

NOINSERT
NOUPDATE
NODELETE
NOCOMMIT

CAMPO=CODPED,TOOLTIP("Código del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=CODDIV,NOENTER,TOOLTIP("Division o compañia del pedido"),POSTCHANGE=FDESIGNACION("CDESDIV","Código de división no existe."),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=DESDIV,NOENTER,AUXILIAR,NOENTER,TOOLTIP("Descripción de la división o compañía del pedido")
CAMPO=ANOPED,NOENTER,TOOLTIP("Año del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=SEQPED,NOENTER,TOOLTIP("Versión del pedido"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;"
CAMPO=NLINEAS,NOENTER,TOOLTIP("Es el número original de líneas del pedido que se recibio del host. Este número no se modifica por los desgloses de lote ni en las nuevas versiones de pedidos.")
CAMPO=CODCLIENTE,NOENTER,TOOLTIP("Es el Código de cliente que realiza el pedido, recibido por el fichero de interfase con el Host."),CONTEXTUAL=FEJECUTAFORM("VDPEDCABDET","S","CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED","","","","S"),INCLUDECSS="background-color:#F7BE81;border-style:ridge;"
CAMPO=DESCLIENTE,NOENTER,TOOLTIP("Designación completa del cliente que realiza el pedido. También recibido en el interfase.")
CAMPO=FECCAPTURA,NOENTER,TOOLTIP("Fecha de captura en HOST del pedido"),COMBOX("CALENDARIO")
CAMPO=HORACAPTURA,NOENTER,TOOLTIP("Hora de captura en HOST del pedido")
CAMPO=FECSERVICIO,NOENTER,TOOLTIP("Fecha en que está previsto que se sirva el el pedido, se utiliza para ordenar los pedidos en la pantalla de creación de series"),COMBOX("CALENDARIO")
CAMPO=FECGRABACION,NOENTER,TOOLTIP("Fecha de grabación del pedido en el HOST"),COMBOX("CALENDARIO")
CAMPO=HORAGRABACION,NOENTER,TOOLTIP("Hora de grabación del pedido en el HOST")
CAMPO=FECRECEP,NOENTER,TOOLTIP("Fecha de recepción del pedido desde el HOST"),COMBOX("CALENDARIO")
CAMPO=HORARECEP,NOENTER,TOOLTIP("Hora de recepción del pedido desde el HOST")
CAMPO=FECRESERVA,NOENTER,TOOLTIP("Fecha de lanzamiento de la serie en la que se encuentra el pedido"),COMBOX("CALENDARIO")
CAMPO=HORARESERVA,NOENTER,TOOLTIP("Hora de lanzamiento de la serie en la que se encuentra el pedido")
CAMPO=FECTERMIN,NOENTER,TOOLTIP("Fecha de terminación del pedido, último bulto finalizado"),COMBOX("CALENDARIO")
CAMPO=HORATERMIN,NOENTER,TOOLTIP("Hora de terminación del pedido, último bulto finalizado")
CAMPO=FECCOMUNICA,NOENTER,TOOLTIP("Fecha de devolucion del pedido al HOST"),COMBOX("CALENDARIO")
CAMPO=HORACOMUNICA,NOENTER,TOOLTIP("Hora de devolucion del pedido al HOST")
CAMPO=FECENTREGA,NOENTER,TOOLTIP("Fecha en que la agencia entrega el pedido al cliente"),COMBOX("CALENDARIO")
CAMPO=HORAENTREGA,NOENTER,TOOLTIP("Hora en que la agencia entrega el pedido al cliente")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la última modificacion")
CAMPO=CONTACTO,OCULTO,"_40_"
CAMPO=DIRECCION,OCULTO,"_40_"
CAMPO=DIRECCION1,OCULTO,"_40_"
CAMPO=DIRECCION2,OCULTO,"_40_"
CAMPO=DIRECCION3,OCULTO,"_40_"
CAMPO=POBLACION,OCULTO,"_40_"
CAMPO=TELEFONO,OCULTO,"_12_"
CAMPO=CODPAIS,OCULTO,"_5_"
CAMPO=CODPROV,OCULTO,"_5_"
CAMPO=DP,OCULTO,"_10_"
CAMPO=PESOPEDIDO,OCULTO,"@L@@@"
CAMPO=NUMUNIDEV,AUXILIAR,OCULTO,"@L@@@"
CAMPO=NUMBULTOSDEV,AUXILIAR,OCULTO,"@L@@@"
CAMPO=SEQDEVOL,AUXILIAR,OCULTO,"@L@@@@@@@"
CAMPO=CODOPEINS,AUXILIAR,OCULTO,"_32_"
CAMPO=FECINS,AUXILIAR,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAINS,AUXILIAR,OCULTO,"________"
CAMPO=CODOPEMODIFDEV,AUXILIAR,OCULTO,"_32_"
CAMPO=FECMODIFDEV,AUXILIAR,OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAMODIFDEV,AUXILIAR,OCULTO,"________"




CURSOR=CDESDIV SELECT DESDIV
                 FROM VDDIVIS
                WHERE CODDIV=:CODDIV;

CURSOR=CSELDEFECTO SELECT VDSEQDEVOL.NEXTVAL SEQDEVOL,VDUSER.GETUSER CODOPEINS,VD.FECHASYS FECINS,VD.HORASYS HORAINS,
                          VDUSER.GETUSER CODOPEMODIFDEV,VD.FECHASYS FECMODIFDEV,VD.HORASYS HORAMODIFDEV
                     FROM DUAL;
                     
CURSOR=CSELDATOSBUC SELECT COUNT(*) NUMBULTOSDEV
                      FROM VDBULTOCAB BUC
                     WHERE BUC.CODPED=:CODPED AND BUC.SEQPED=:SEQPED AND
                           BUC.ANOPED=:ANOPED AND BUC.CODDIV=:CODDIV;
                           
CURSOR=CSELDATOSBUL SELECT SUM(CANTSERVIDA) NUMUNIDEV
                      FROM VDBULTOLIN BUL,VDBULTOCAB BUC
                     WHERE BUL.CODBULTO=BUC.CODBULTO AND
                           BUC.CODPED=:CODPED AND BUC.SEQPED=:SEQPED AND
                           BUC.ANOPED=:ANOPED AND BUC.CODDIV=:CODDIV;                           
                          
CURSOR=CINSDEVOLCAB INSERT INTO VDDEVOLCAB 
                           (SEQDEVOL,CODDIV,CODCLIENTE,DESCLIENTE,CONTACTO,DIRECCION,DIRECCION1,DIRECCION2,DIRECCION3,
                            POBLACION,TELEFONO,CODPAIS,CODPROV,DP,STATUS,NUMUNI,PRECIODEV,NUMBULTOS,CODOPEINS,FECINS,HORAINS,
                            CODCOMEN,CODPED,CODOPEMODIF,FECMODIF,HORAMODIF)
                    VALUES (:SEQDEVOL,:CODDIV,:CODCLIENTE,:DESCLIENTE,:CONTACTO,:DIRECCION,:DIRECCION1,:DIRECCION2,:DIRECCION3,
                            :POBLACION,:TELEFONO,:CODPAIS,:CODPROV,:DP,200,:NUMUNIDEV,0,:NUMBULTOSDEV,:CODOPEINS,:FECINS,:HORAINS,
                            0,:CODPED,:CODOPEMODIFDEV,:FECMODIFDEV,:HORAMODIFDEV);
                            
CURSOR=CINSDEVOLLIN INSERT INTO VDDEVOLLIN
                           SELECT :SEQDEVOL,CODART,CODLOT,'0','0','EALMACEN',CANTSERVIDA,NULL,NULL,NULL,
                                  NBULTO,:CODOPEINS,:FECINS,:HORAINS,NULL,0,NULL,NULL,0,NULL,NULL,0,NULL,NULL,0,NULL,
                                  100,0,:CODOPEMODIFDEV,:FECMODIFDEV,:HORAMODIFDEV
                             FROM VDBULTOLIN BUL,VDBULTOCAB BUC
                            WHERE BUL.CODBULTO=BUC.CODBULTO AND
                                  BUC.CODPED=:CODPED AND BUC.SEQPED=:SEQPED AND
                                  BUC.ANOPED=:ANOPED AND BUC.CODDIV=:CODDIV AND
                                  BUL.STATUS=VDST.FBULSERVIDA;

TECLA=SF6,FEJECUTA("CSELDEFECTO","ERROR OBTENIENDO DATOS POR DEFECTO",
                   "CSELDATOSBUC","ERROR OBTENIENDO NUMERO DE BULTOS DEL PEDIDO",
                   "CSELDATOSBUL","ERROR OBTENIENDO UNIDADES DE BULTOS DEL PEDIDO",
                   "CINSDEVOLCAB","ERROR INSERTANDO CABECERA DE DEVOLUCION",
                   "CINSDEVOLLIN","ERROR INSERTANDO LINEA DE DEVOLUCION",
                   +FCOMMIT,"",
                   %FFAILURE,"DEVOLUCION :SEQDEVOL CREADA")


BOTON=VALIDAR,700,160,80,80,"Confirmar",vertis\vertisok.png,SF6,"Crear devolución" ,INCLUDECSS="border-style:outset;background-color:transparent"
BOTON=SALIR,800,160,80,80,"Salir",vertis\vertissalir.png,27,"Salir de la pantalla" ,INCLUDECSS="border-style:outset;background-color:transparent"

