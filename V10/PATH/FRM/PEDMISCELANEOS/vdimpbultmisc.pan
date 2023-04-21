###################################################################
#M�dulo: VDIMPBULTMISC.PAN
#Funcionalidad : Impresi�n de bultos de pedidos miscelaneos
#Autor: JMM
#Fecha: 13-10-2008
###################################################################
# Hist�rico de cambios:
#
IMPRESION DE BULTOS DE PEDIDOS MISCELANEOS
Pedido       Div.    A�o   Ver.  Cliente                     Serie Agencia           Peso (Kg.) Vol (L.) Pal.  Emb.  Unid.  Imp        
_20_________ _20__   @@@@  @@@   _20_______ _60____________  @@@@@ _40______________ #L##.###  #L##.###  @@@@  @@@@  @@@@   _         
|

TABLA=VDPEDIDOCAB

WHERE=SWTMISCELANEO='S' AND STATUS=VDST.FPECMISCELANEO AND CODSERIEPREP > 0;
ORDERBY=CODSERIEPREP;
NOINSERT
NODELETE
REGPAG=40

SELECT='N' IMPRIMIR;


PREUPDATE=FEJECUTA("@CCHECKIMPRIMIR","",
                   "CCHECKNUMBULTOS","EL NUMERO TOTAL DE BULTOS DEBE SER MAYOR QUE CERO",
                   "+CCHECKPESO","EL PESO DEL PEDIDO DEBE SER MAYOR QUE CERO",
                   "+CCHECKVOLUMEN","EL VOLUMEN DEL PEDIDO DEBE SER MAYOR QUE CERO",
                   "CCREABULTOS","ERROR CREANDO BULTOS DEL PEDIDO\n:CODDIV - :CODPED - :ANOPED - :SEQPED",
                   "CSELBULTOS","ERROR OBTENIENDO BULTOS\n:CODDIV - :CODPED - :ANOPED - :SEQPED",
                   FWHILE(FERRORCURSOR("CSELBULTOS"),
                          FEJECUTA(FIMPRIMEBULTO("ETIQ",":CODBULTO","VD.GEN;XXX.VSQ;CSELBULSINLIN","CODBULTO=:CODBULTO;ESCOPIA='N'","","1"),"ERROR AL IMPRIMIR ETIQUETA\n :V10ERROR",
                                  +FFETCHCURSOR("CSELBULTOS"),"ERROR EN FETCH")),"ERROR EN FWHILE",
                   "+CUPDLINPEDIDO","",
                   "CDAMEORDENADOR","ERROR OBTENIENDO NOMBRE DEL ORDENADOR",
                   "CUPDCABPEDIDO","ERROR ACTUALIZANDO CABECERA DE PEDIDO\n:CODDIV - :CODPED - :ANOPED - :SEQPED")

POSTCOMMIT=FEJECUTA(+FPULSATECLAS("F5"),"")

CAMPO=CODPED,NOUPDATE,TOOLTIP("C�digo del pedido"),TITULO("Pedido")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("C�digo de la divisi�n"),TITULO("Divisi�n"),WLONX=28
CAMPO=ANOPED,NOUPDATE,TOOLTIP("A�o del pedido"),TITULO("A�o"),WLONX=15
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Versi�n del pedido"),TITULO("Vers."),WLONX=20
CAMPO=CODCLIENTE,NOUPDATE,TOOLTIP("C�digo del cliente"),TITULO("Cliente")
CAMPO=DESCLIENTE,NOUPDATE,TOOLTIP("Descripci�n del cliente")
CAMPO=CODSERIEPREP,NOUPDATE,TOOLTIP("C�digo de la serie de preparaci�n en la que se incluye el pedido"),TITULO("Serie"),WLONX=20
CAMPO=CODAGE,OCULTO,"_10_",NOUPDATE,TOOLTIP("C�digo de agencia"),POSTCHANGE=FDESIGNACION("+CSELDESAGE","")
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Descripci�n de la agencia"),TITULO("Agencia")
CAMPO=PESOPEDIDO,TOOLTIP("Peso del pedido"),TITULO("Peso (Kg)"),WLONX=30
CAMPO=VOLUMENPEDIDO,TOOLTIP("Vol�men del pedido"),TITULO("Vol (L)")
CAMPO=NUMBULPAL,AUXILIAR,TOOLTIP("N�mero de bultos de palet completo del pedido"),TITULO("Palets"),WLONX=25
CAMPO=NUMBULEMBA,AUXILIAR,TOOLTIP("N�mero de bultos de embalaje completo del pedido"),TITULO("Cajas"),WLONX=25
CAMPO=NUMBULUNI,AUXILIAR,TOOLTIP("N�mero de bultos de unidades del pedido"),TITULO("Unid."),WLONX=25
CAMPO=IMPRIMIR,AUXILIAR,UPPER,POSTCHANGE=FVERIFICA("SN ","DEBE INTRODUCIR S o N"),TITULO("Impr."),WLONX=30
CAMPO=ORDENADOR,AUXILIAR,OCULTO,"_64_"
CAMPO=CODBULTO,AUXILIAR,OCULTO,"_18_"
CAMPO=CODCOMEN,OCULTO,"@L@@@@@@@"

CURSOR=CSELDESAGE SELECT DESAGE FROM VDAGENCIA WHERE CODAGE = :CODAGE;

CURSOR=CCHECKIMPRIMIR SELECT :IMPRIMIR FROM DUAL WHERE :IMPRIMIR = 'S';

CURSOR=CCHECKNUMBULTOS SELECT :NUMBULPAL FROM DUAL WHERE :NUMBULPAL + :NUMBULEMBA + :NUMBULUNI > 0;

CURSOR=CCHECKPESO SELECT  :PESOPEDIDO FROM DUAL WHERE :PESOPEDIDO > 0;

CURSOR=CCHECKVOLUMEN SELECT :VOLUMENPEDIDO FROM DUAL WHERE :VOLUMENPEDIDO > 0;


CURSOR=CCREABULTOS DECLARE
                       RET NUMBER;
                   BEGIN
                       RET:=VDBULTO.CREABULTOSMISC(:CODDIV,:ANOPED,:CODPED,:SEQPED,VD.GETPROP('DIGITOEAN'),:NUMBULUNI,:NUMBULEMBA,:NUMBULPAL,:PESOPEDIDO,:VOLUMENPEDIDO);
                       IF RET != 0 THEN
                           RAISE NO_DATA_FOUND;
                       END IF;
                   END;@

CURSOR=CSELBULTOS SELECT CODBULTO
                    FROM VDBULTOCAB
                   WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND ANOPED = :ANOPED AND SEQPED = :SEQPED;

CURSOR=CCHECKAGESEUR SELECT :CODAGE FROM VDAGENCIA WHERE CODAGE = :CODAGE AND GRUPOAGE = 'SEUR';

CURSOR=CSELTRACKINGSEUR DECLARE
                            RET NUMBER;
                        BEGIN
                            RET := VDTRANSPORTE.DAMETRACKINGSEUR(:CODPED,:CODDIV,:SEQPED,:ANOPED);
                            IF RET != 0 THEN
                                RAISE NO_DATA_FOUND;
                            END IF;
                        END;@
                   
CURSOR=CDAMEORDENADOR SELECT TERMINAL ORDENADOR
                        FROM SYS.V_$SESSION
                       WHERE AUDSID=USERENV('SESSIONID');
                       

CURSOR=CUPDLINPEDIDO UPDATE VDPEDIDOLIN
                        SET STATUS = VDST.FPELSERVIDA, CANTASERVIR=CANTPEDIDA, CANTSERVIDA=CANTPEDIDA,
                            CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND ANOPED = :ANOPED AND SEQPED = :SEQPED;

CURSOR=CUPDCABPEDIDO UPDATE VDPEDIDOCAB 
                        SET STATUS = VDST.FPECENEXPED, CODALB = DECODE(CODALB,NULL,VDPED.DAMEC�digoALBARAN,CODALB),
                            ANOALB = DECODE(ANOALB,NULL,TO_CHAR(SYSDATE,'YYYY'),ANOALB), CODOPEMODIF = VDUSER.GETUSER, 
                            FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS
                      WHERE CODPED = :CODPED AND CODDIV = :CODDIV AND ANOPED = :ANOPED AND SEQPED = :SEQPED;


CURSOR=CPONIMPIMIR SELECT 'S' IMPRIMIR FROM DUAL;

                      
CONTEXTUAL=FEJECUTAFORM("VDPEDIDOS","N","CODPED=:CODPED AND CODDIV=:CODDIV AND ANOPED=:ANOPED AND SEQPED=:SEQPED")