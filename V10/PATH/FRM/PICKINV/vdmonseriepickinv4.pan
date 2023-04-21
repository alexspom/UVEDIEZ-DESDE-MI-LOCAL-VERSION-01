###################################################################
#Módulo: VMONSERIEPICKINV4.PAN
#Funcionalidad : Monitor de series de picking inverso, bultos con displays
#Autor: FGS   
#Fecha: 24-09-2008
###################################################################
# Histórico de cambios:
MONITOR DE BULTOS PDTES DE SERIE(S) ASIGNADOS A DISP. DE LA ZONA
                                 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄ Pedido ÄÄÄÄÄÄÄÄÄÄÄÄ‘
   Display    Bulto                                                   Lineas Pdtes.
   @L @L@@@@@ __________________ _20_ @L@@ ____________________ @L@@      @L@@@ 
|

SOLOQUERY
SELECT=SELECT DSP.IDINFOPICK, DSP.NUMDISP, BUC.CODBULTO, BUC.CODDIV,BUC.ANOPED,BUC.CODPED,BUC.SEQPED, COUNT(*) LINEASPDTES
         FROM VDINFODISP DSP, VDBULTOLIN BUL, VDBULTOCAB BUC, VDPEDIDOCAB PEC 
         WHERE BUC.CODBULTO      =   BUL.CODBULTO AND 
               BUC.IDINFOPICK  =   DSP.IDINFOPICK AND
               BUC.NUMDISP     =   DSP.NUMDISP AND
               BUC.TIPOBULTO   =   'U' AND     
               BUC.STATUS      <    VDST.FBUCPREPARADO AND
               DSP.CODZONA     = :CODZONA AND
               BUL.STATUS+0    =    VDST.FBULASERVIR AND
               PEC.CODDIV      =    BUC.CODDIV AND
               PEC.ANOPED      =    BUC.ANOPED AND
               PEC.CODPED      =    BUC.CODPED AND
               PEC.SEQPED      =    BUC.SEQPED AND
               VD.CONTIENECAD(:RANSERIE,PEC.CODSERIEPREP)=1    
         GROUP BY DSP.IDINFOPICK, DSP.NUMDISP,ORDENDISP, BUC.CODBULTO, BUC.CODDIV,BUC.ANOPED,BUC.CODPED,BUC.SEQPED  
         ORDER BY ORDENDISP;
#WFRAME(212,-2,240,0,"Pedido","")
TABLA=VDBULTOCABPINV

CAMPO=IDINFOPICK,TITULO("Display")
CAMPO=NUMDISP
CAMPO=CODBULTO,CONTEXTUAL=FEJECUTAFORM("VDBULTOMA","S","CODBULTO=:CODBULTO"),TITULO("Bulto")
CAMPO=CODDIV,TITULO("Pedido")
CAMPO=ANOPED
CAMPO=CODPED
CAMPO=SEQPED
CAMPO=LINEASPDTES,TITULO("Líneas Pdtes"),WLONX=52
CAMPO=CODZONA,AUXILIAR,VIRTUAL,OCULTO
CAMPO=RANSERIE,AUXILIAR,VIRTUAL,OCULTO

