# M�dulo   : VDMONIBULTOSST.PAN
# Funci�n  : Monitor de bultos pendientes. Desglose por estados
#
# Creaci�n : 04-08-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
ESTADO DE LOS BULTOS PENDIENTES
Tipo  Estado                           Total  Lineas
 _    @L@@@@ _30______________________ @L@@@@ @L,@@@
|

SOLOQUERY
SELECT=SELECT BUC.STATUS,COUNT(BUC.CODBULTO) TOTAL
         FROM VDBULTOCAB BUC, VDPEDIDOCAB PEC
        WHERE PEC.CODPED = BUC.CODPED AND PEC.CODDIV = BUC.CODDIV AND
              PEC.ANOPED = BUC.ANOPED AND PEC.SEQPED = BUC.SEQPED AND
              BUC.STATUS < VDST.FBUCFINALIZADO AND
              BUC.TIPOBULTO = :TIPOBULTO AND
              VD.CONTIENECAD(:RANDIV,PEC.CODDIV) = 1 AND
              VD.CONTIENECAD(:RANAGE,PEC.CODAGE) = 1;

GROUPBY=BUC.STATUS;
ORDERBY=BUC.STATUS;

POSTQUERY=FEJECUTA("CSELLINEAS","")

CAMPO=TIPOBULTO,AUXILIAR,VIRTUAL,NOENTER,TOOLTIP("Tipo de bulto"),TITULO("Tipo"),WLONX=15
CAMPO=STATUS,NOENTER,TOOLTIP("Estado del bulto"),POSTCHANGE=FDESIGNACION("+CSELDESSTATUS",""),TITULO("Estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Descripcion del estado del bulto"),TITULO("Desc.Estado")
CAMPO=TOTAL,NOENTER,TOOLTIP("Numero total de bultos que estan en este estado"),TITULO("Total")
CAMPO=LINEAS,NOENTER,TOOLTIP("Numero de lienas"),TITULO("Lineas")

CURSOR=CSELDESSTATUS SELECT DESSTATUS 
                       FROM VDSTATUS 
                      WHERE STATUS = :STATUS AND TIPOSTATUS = 'BUC';
                      
CURSOR=CSELLINEAS SELECT COUNT(*) LINEAS FROM VDBULTOLIN BUL,VDBULTOCAB BUC WHERE BUL.CODBULTO=BUC.CODBULTO AND BUC.TIPOBULTO=:TIPOBULTO AND BUC.STATUS=:STATUS;   

TECLA=SF10,FEJECUTAFORM("VDBULTOSMA","S","STATUS = :STATUS AND TIPOBULTO = :TIPOBULTO")


