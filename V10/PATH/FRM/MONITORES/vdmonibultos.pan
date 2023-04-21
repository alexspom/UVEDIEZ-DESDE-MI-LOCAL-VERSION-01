# Módulo   : VDMONIBULTOS.PAN
# Función  : Monitor de bultos pendientes. Desglose por tipo de butlos
#
# Creación : 04-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
TIPOS DE BULTO PENDIENTES
 Tipo                   Total   Lineas
  _    ________________ @L@@@@@ @L,@@@
|

SOLOQUERY
SELECT=SELECT BUC.TIPOBULTO, COUNT(BUC.CODBULTO) TOTAL
         FROM VDBULTOCAB BUC, VDPEDIDOCAB PEC
        WHERE PEC.CODPED = BUC.CODPED AND PEC.CODDIV = BUC.CODDIV AND
              PEC.ANOPED = BUC.ANOPED AND PEC.SEQPED = BUC.SEQPED AND
              BUC.STATUS < VDST.FBUCFINALIZADO AND
              VD.CONTIENECAD(:RANDIV,PEC.CODDIV) = 1 AND
              VD.CONTIENECAD(:RANAGE,PEC.CODAGE) = 1;
        
GROUPBY=TIPOBULTO;
ORDERBY=DECODE(TIPOBULTO,'U',0,'E',1,2);

POSTQUERY=FEJECUTA("CSELLINEAS","")
        

CAMPO=TIPOBULTO,NOENTER,TOOLTIP("Tipo de bulto"),POSTCHANGE=FDESIGNACION("+CSELTIPO",""),TITULO("Tipo"),WLONX=10
CAMPO=TIPO,AUXILIAR,NOENTER,TITULO("Descripción")
CAMPO=TOTAL,NOENTER,TOOLTIP("Numero total de bultos pendiente de este tipo"),TITULO("Total")
CAMPO=LINEAS,NOENTER,TOOLTIP("Numero de lienas"),TITULO("Lineas")

CURSOR=CSELTIPO SELECT DECODE(:TIPOBULTO,'U','UNIDADES SUELTAS',
                                         'F','UNIDADES DE FRIO',
                                         'E','CAJA COMPLETA',
                                         'C','PALET COMPLETO') TIPO
                  FROM DUAL;
                  
CURSOR=CSELLINEAS SELECT COUNT(*) LINEAS FROM VDBULTOLIN BUL,VDBULTOCAB BUC WHERE BUL.CODBULTO=BUC.CODBULTO AND BUC.TIPOBULTO=:TIPOBULTO AND BUC.STATUS<VDST.FBUCFINALIZADO;                  


