###################################################################
#M�dulo: VDLISTAPEDIDOSERR.PAN
#Funcionalidad : Listado de pedidos en error.
#Autor: JCSR
#Fecha: 28-08-2008
###################################################################
# Hist�rico de cambios:
LISTADO DE PEDIDOS CON ESTADO ERRONEO
Fecha      Hora     Tabla        Pedido          Cliente Error                                                                                                            Estado
�D-MM-Y.YY ________ _20_________ _20____________ _10____ _1024___________________________________________________________________________________________________________ @@@@@ _______________________     
| 


SOLOQUERY

SELECT= SELECT CODCOMEN,CODPED,CODCLIENTE,STATUS,CODDIV,ANOPED,SEQPED ,'VDPEDIDORIGCAB' TABLAERROR
            FROM VDPEDIDORIGCAB POC 
            WHERE STATUS<0
       UNION        
        SELECT CODCOMEN,CODPED,CODCLIENTE,STATUS,CODDIV,ANOPED,SEQPED,'VDPEDIDOCAB' TABLAERROR 
         FROM VDPEDIDOCAB PEC
         WHERE STATUS<0;
         
POSTQUERY=FEJECUTA("+CSELCOMEN","SIN COMENTARIOS")         
  
ORDERBY=CODPED;

CAMPO=FECMODIF,TITULO("Fecha")
CAMPO=HORAMODIF,TITULO("Hora")
CAMPO=TABLAERROR,TITULO("Tabla")
CAMPO=CODPED, NOUPDATE, TOOLTIP("C�digo del pedido"),TITULO("C�digo")
CAMPO=CODCLIENTE,TITULO("Cliente")
CAMPO=COMENTARIO,TITULO("Comentario")
CAMPO=STATUS, POSTCHANGE=FDESIGNACION("+CSELSTATUS",""),TITULO("Estado")
CAMPO=DESSTATUS
CAMPO=CODDIV,AUXILIAR,OCULTO,"_20_"
CAMPO=SEQPED,AUXILIAR,OCULTO,"@@@@"
CAMPO=ANOPED,AUXILIAR,OCULTO,"@@@@"
CAMPO=LINCOMEN,AUXILIAR,OCULTO,"@@@@"
CAMPO=CODCOMEN,AUXILIAR,OCULTO,"@L@@@@@@@"
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='PEC';
CURSOR=CDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE=:CODAGE;

CURSOR=CSELCOMEN SELECT FECMODIF,HORAMODIF,COMENTARIO
                   FROM (SELECT FECMODIF,HORAMODIF,COMENTARIO
                          FROM VDCOMEN WHERE CODCOMEN=:CODCOMEN
                          ORDER BY FECMODIF DESC,HORAMODIF DESC)
                   WHERE ROWNUM=1;


CURSOR=CUPDAPEDCAB UPDATE VDPEDIDOCAB SET STATUS=STATUS*(-1) WHERE CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND :STATUS<0 ;
CURSOR=CUPDAPEDORIGCAB UPDATE VDPEDIDORIGCAB SET STATUS=STATUS*(-1) WHERE CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND :STATUS<0 ;

CURSOR=CSELPEDERR SELECT :CODPED FROM VDPEDIDOCAB WHERE CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND :STATUS<0 ;

CURSOR=CSELPEDORIGERR SELECT :CODPED FROM VDPEDIDORIGCAB WHERE CODDIV=:CODDIV AND CODPED=:CODPED AND ANOPED=:ANOPED AND :STATUS<0 ;

TECLA=AF3,FEJECUTA(FIF("CSELPEDERR","CUPDAPEDCAB",FSUCCESS),"",
                   FIF("CSELPEDORIGERR","CUPDAPEDORIGCAB",FSUCCESS),"",
                   FCOMMIT,"",
                   %FFAILURE, "PEDIDO :CODPED DEL A�O :ANOPED DE LA DIVISION :CODDIV SECUENCIAL :SEQPED REINTENTADO",
                   FPULSATECLAS("F3", "F2"))
				   
BOTON=B1,1100,50,50,50,"Reintentar",refrescar.png,AF3,"Reintentar Pedido",INCLUDECSS="background-color: transparent;border-width:0px"
                   
ONLINE={Alt+F3} Reintentar el pedido;

CURSOR=CESORIG SELECT :TABLAERROR FROM DUAL WHERE :TABLAERROR='VDPEDIDORIGCAB';

CONTEXTUAL=FIF("CESORIG",FEJECUTAFORM("VDPEDIDORIGINAL","S","CODPED=:CODPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED AND SEQPED=:SEQPED"),
                         FEJECUTAFORM("VDPEDIDOSANT","S","CODPED=:CODPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED AND SEQPED=:SEQPED"))

