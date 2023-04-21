###################################################################
#Módulo: VDMONBULTOSPICKINV2.PAN
#Funcionalidad : Monitor de bultos de picking inverso por estado y series
#Autor: FGS   
#Fecha: 24-06-2008
###################################################################
# Histórico de cambios:
BULTOS DE PICKING INVERSO POR SERIE(S)
       
 Estado                       Bultos    
 @L@@@ _30___________________ @L@@@@  
|

SOLOQUERY
SELECT= SELECT  STATUS, DESSTATUS, COUNT(*) BULTOS
          FROM (SELECT BPC.CODBULTO,BPC.STATUS, STA.DESSTATUS
                 FROM VDBULTOCABPINV BPC,
                      VDMOVIM MOV,
                      VDBULTOCAB BUC,
                      VDBULTOLIN BUL,
                      VDPEDIDOCAB PEC,
                      VDSERIEPREP SPR,
                      VDSTATUS STA 
                WHERE VD.CONTIENECAD(:RANSERIE,SPR.CODSERIEPREP) = 1 AND
                      PEC.CODSERIEPREP = SPR.CODSERIEPREP AND
                      BUC.CODPED       =    PEC.CODPED AND
                      BUC.CODDIV       =    PEC.CODDIV AND
                      BUC.ANOPED       =    PEC.ANOPED AND
                      BUC.SEQPED       =    PEC.SEQPED AND            
                      SWTPICKINGINV='S' AND 
                      BUL.CODBULTO = BUC.CODBULTO AND
                      MOV.CODMOV   = BUL.CODMOV AND
                      BPC.CODMAT=MOV.CODMATORI AND
                      BPC.STATUS   <=VDST.FBPCHDS AND
                      BPC.STATUS=STA.STATUS AND 
                      STA.TIPOSTATUS='BPC'
                GROUP BY BPC.CODBULTO,BPC.STATUS, STA.DESSTATUS)
           GROUP BY STATUS,DESSTATUS
           ORDER BY STATUS;


CAMPO=STATUS,TITULO("Estado")
CAMPO=DESSTATUS
CAMPO=BULTOS,TITULO("Bultos")
CAMPO=RANSERIE,AUXILIAR,VIRTUAL,OCULTO
 


