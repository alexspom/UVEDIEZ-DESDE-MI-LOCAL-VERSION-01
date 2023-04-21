###################################################################
#Módulo: VDPEDIDOESPSTOCK1.PAN
#Funcionalidad : Lista de Bultos en estado de Esperando Stock     
#Autor: FGS      
#Fecha:26-03-2008
###################################################################
#Histórico de cambios:
PEDIDOS EN ESPERA DE STOCK
ÏÄÄÄÄÄÄÄÄÄÄ Pedido ÄÄÄÄÄÄÄÄÄÄË 
 Código                Div.  Año  Sec.  Líneas Con Falta
 _20__________________ _20__  @@@@ @L@@      @L@@@
|


TABLA=VDPEDIDOCAB
WHERE=STATUS=VDST.FPECPDTESTOCK;
ORDERBY=CODDIV,ANOPED,CODPED,SEQPED;
WFRAME(8,-2,200,0,"Pedido","")

POSTQUERY=FEJECUTA("CSUMALINEAS","")
CAMPO=CODPED,TITULO("Código")
CAMPO=CODDIV,TITULO("Div.")
CAMPO=ANOPED,TITULO("Año")
CAMPO=SEQPED,TITULO("Sec."),WLONX=-40
CAMPO=SUMALINEAS,AUXILIAR,NOENTER,TITULO("Lin. con Falta"),WLONX=60

CURSOR=CSUMALINEAS SELECT COUNT(*) SUMALINEAS FROM VDPEDIDOLIN PEL, VDCOMEN COM WHERE 
                               PEL.CODDIV=:CODDIV AND
                               PEL.ANOPED=:ANOPED AND
                               PEL.CODPED=:CODPED AND
                               PEL.SEQPED=:SEQPED AND
                               PEL.CODCOMEN=COM.CODCOMEN AND
                               COM.TIPOCOMEN='RESERVA'; 
#zoom para consultar el pedido
#opción de reintentar un pedido esperando stock
#opción de reintentar todos los pedidos esperando stock

CURSOR=CUPDPEDIDO UPDATE VDPEDIDOCAB 
                     SET STATUS=VDST.FPECLANZADO,CODOPEMODIF=VDUSER.GETUSER, 
                         FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                   WHERE CODDIV=:CODDIV AND ANOPED=:ANOPED AND CODPED=:CODPED AND SEQPED=:SEQPED;
                                                             

CURSOR=CUPDTODOSLOSPEDIDO UPDATE VDPEDIDOCAB 
                             SET STATUS=VDST.FPECLANZADO,CODOPEMODIF=VDUSER.GETUSER, 
                                 FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS 
                           WHERE STATUS=VDST.FPECPDTESTOCK;
                                                             
TECLA=AF3,FEJECUTA("CUPDPEDIDO","",
                   FCOMMIT,"",
                   %FFAILURE, "PEDIDO :CODDIV :ANOPED :CODPED :SEQPED REINTENTADO",
                   FPULSATECLAS("F5"))

TECLA=AF5,FEJECUTA("CUPDTODOSLOSPEDIDO","",
                   FCOMMIT,"",
                   %FFAILURE, "TODOS LOS PEDIDOS REINTENTADOS",
                   FPULSATECLAS("F5"))

                   



