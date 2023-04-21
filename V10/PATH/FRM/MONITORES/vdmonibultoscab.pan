# M�dulo   : VDMONIBULTOSCAB.PAN
# Funci�n  : Monitor de bultos pendientes. Cabeceras de bulto
#
# Creaci�n : 04-08-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
BULTOS EN EL ESTADO SELECCIONADO
Bulto              N.Bul Lineas Vol.      A�o  Div  C�digo              Ver Urg  Agencia         Cod.  Prio    C�digo     Descripci�n   
_18_______________ @L@@@ @L,@@@ _20______ @L@@ _20__ _20________________ @@@  @@  _40__________   @L@@@@  @@    _12_______ _40__________
|

SOLOQUERY
TABLA=BUC
SELECT=SELECT BUC.CODBULTO, BUC.NBULTO, BUC.TIPOVOL,BUC.ANOPED, BUC.CODDIV, BUC.CODPED, BUC.SEQPED 
         FROM VDBULTOCAB BUC, VDPEDIDOCAB PEC
        WHERE PEC.CODPED = BUC.CODPED AND PEC.CODDIV = BUC.CODDIV AND
              PEC.ANOPED = BUC.ANOPED AND PEC.SEQPED = BUC.SEQPED AND
              BUC.STATUS+0 = :STATUS AND
              BUC.TIPOBULTO = :TIPOBULTO AND
              VD.CONTIENECAD(:RANDIV,PEC.CODDIV) = 1 AND
              VD.CONTIENECAD(:RANAGE,PEC.CODAGE) = 1;

ORDERBY=BUC.CODPED,BUC.SEQPED,BUC.NBULTO;

POSTQUERY=FEJECUTA("CSELLINEAS","")


CAMPO=TIPOBULTO,VIRTUAL,OCULTO
CAMPO=STATUS,VIRTUAL,OCULTO
CAMPO=CODBULTO,NOUPDATE,TOOLTIP("C�digo de bulto"),TITULO("Bulto")
CAMPO=NBULTO,NOUPDATE,TOOLTIP("Numero de bulto dentro del pedido"),TITULO("N.Bul"),WLONX=25
CAMPO=LINEAS,NOENTER,TOOLTIP("Numero de lienas"),TITULO("Lineas")
CAMPO=TIPOVOL,NOUPDATE,TITULO("Volum.")
CAMPO=ANOPED,NOUPDATE,TOOLTIP("A�o del pedido"),TITULO("A�o")
CAMPO=CODDIV,NOUPDATE,TOOLTIP("C�digo de la divisi�n del pedido"),TITULO("Div")
CAMPO=CODPED,NOUPDATE,TOOLTIP("C�digo del pedido"),POSTCHANGE=FDESIGNACION("CSELPEDIDO","ERROR OBTENIENDO DATOS DEL PEDIDO :CODPED"),TITULO("Pedido")
CAMPO=SEQPED,NOUPDATE,TOOLTIP("Version del pedido"),TITULO("Ver."),WLONX=15
CAMPO=URGENCIA,AUXILIAR,NOENTER,TOOLTIP("Urgencia del pedido"),TITULO("Urg"),WLONX=15
CAMPO=DESAGE,AUXILIAR,NOENTER,TOOLTIP("Agencia del pedido"),TITULO("Agencia")
CAMPO=CODSERIEEXP,AUXILIAR,NOENTER,TOOLTIP("C�digo de la serie de expedicion"),TITULO("S.Exp")
CAMPO=PRIORIDAD,AUXILIAR,NOENTER,TOOLTIP("Prioridad de la serie de expedicion"),TITULO("Prio"),WLONX=16
CAMPO=CODCLIENTE,AUXILIAR,NOENTER,TOOLTIP("C�digo del cliente"),TITULO("Cliente"),WLONX=35
CAMPO=DESCLIENTE,AUXILIAR,NOENTER,TOOLTIP("Descripci�n del cliente"),TITULO("Descripci�n")

CURSOR=CSELPEDIDO SELECT URGENCIA, AGE.DESAGE, PEC.CODSERIEEXP, SEX.PRIORIDAD, PEC.CODCLIENTE, PEC.DESCLIENTE
                    FROM VDPEDIDOCAB PEC, VDSERIEEXP SEX, VDAGENCIA AGE
                   WHERE PEC.CODPED = :CODPED AND PEC.CODDIV = :CODDIV AND
                         PEC.ANOPED = :ANOPED AND PEC.SEQPED = :SEQPED AND
                         AGE.CODAGE = PEC.CODAGE AND SEX.CODSERIEEXP = PEC.CODSERIEEXP;
                         
CURSOR=CSELLINEAS SELECT COUNT(*) LINEAS FROM VDBULTOLIN BUL WHERE BUL.CODBULTO=:CODBULTO;


