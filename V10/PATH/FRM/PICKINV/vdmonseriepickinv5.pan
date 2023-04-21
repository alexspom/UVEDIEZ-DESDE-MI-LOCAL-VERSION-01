###################################################################
#Módulo: VMONSERIEPICKINV5.PAN
#Funcionalidad : Monitor de series de picking inverso, bultos sin displays
#Autor: FGS   
#Fecha: 24-09-2008
###################################################################
# Histórico de cambios:
MONITOR DE BULTOS PDTES DE SERIE(S) NO ASIGNADOS A DISP. 

 Bulto              Pedido                               Lineas Pdtes.
 __________________ _20___ @L@@ ____________________ @L@@     @L@@@ 
|

SOLOQUERY
SELECT=SELECT BUC.CODBULTO, BUC.CODDIV,BUC.ANOPED,BUC.CODPED,BUC.SEQPED, COUNT(*) LINEASPDTES
       FROM  VDBULTOLIN BUL, VDBULTOCAB BUC, VDPEDIDOCAB PEC 
       WHERE   BUC.CODBULTO    =   BUL.CODBULTO AND 
               NVL(BUC.IDINFOPICK,0)  =   0 AND
               NVL(BUC.NUMDISP,0)     =   0 AND
               BUC.TIPOBULTO   =    'U' AND
               BUC.STATUS      <    VDST.FBUCPREPARADO AND
               BUL.STATUS+0    =    VDST.FBULASERVIR AND
               PEC.CODDIV      =    BUC.CODDIV AND
               PEC.ANOPED      =    BUC.ANOPED AND
               PEC.CODPED      =    BUC.CODPED AND
               PEC.SEQPED      =    BUC.SEQPED AND
               VD.CONTIENECAD(:RANSERIE,PEC.CODSERIEPREP)=1    
        GROUP BY BUC.CODBULTO, BUC.CODDIV,BUC.ANOPED,BUC.CODPED,BUC.SEQPED;   

CAMPO=CODBULTO,CONTEXTUAL=FEJECUTAFORM("VDBULTOMA","S","CODBULTO=:CODBULTO"),TITULO("Bulto")
CAMPO=CODDIV,TITULO("Pedido")
CAMPO=ANOPED
CAMPO=CODPED
CAMPO=SEQPED
CAMPO=LINEASPDTES,TITULO("Líneas Pdtes"),WLONX=60
CAMPO=RANSERIE,AUXILIAR,VIRTUAL,OCULTO

