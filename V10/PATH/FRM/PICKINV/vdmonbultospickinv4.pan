###################################################################
#Módulo: VDMONBULTOSPICKINV4.PAN
#Funcionalidad : Monitor de bultos de picking inverso, Bultos directos servidos por los bultos de picking inverso 
#Autor: FGS   
#Fecha: 24-06-2008
###################################################################
# Histórico de cambios:
LINEAS DE BULTOS DIRECTOS SERVIDOS POR EL BULTO DE PICK. INVERSO SELECCIONADO
                                                   ÏÄ Cantidad ÄË ÏÄÄÄÄÄÄÄÄÄÄ Movimiento ÄÄÄÄÄÄÄÄË ÏÄÄÄÄ Movto al que espera ÄÄÄÄÄË
Div. CodPed      Año  Sec. Bulto              Lin  Pedida Servida Código   St    O        D        Código   St    O        D         
_20_ _20________ _4__ @@@@ __________________ @L@@ @L@@@@ @L@@@@  @L@@@@@@ @L@@@ _20_____ _20_____ @L@@@@@@ @L@@@ _20_____ _20_____
|


SOLOQUERY
NOCOMMIT
SELECT=SELECT PEC.CODPED,PEC.CODDIV, PEC.ANOPED, PEC.SEQPED, NVL(BUC.CODBULTO,'RESTO') CODBULTOAUX, BUL.SEQLINEA, BUL.CANTPEDIDA, BUL.CANTSERVIDA,
              MOV.CODMOV, MOV.STATUS, MOV.CODUBIORI, MOV.CODUBIDEST,
              MOVESP.CODMOV CODMOVESP, MOVESP.STATUS STATUSESP, MOVESP.CODUBIORI CODUBIORIESP, MOVESP.CODUBIDEST CODUBIDESTESP              
            FROM
              VDPEDIDOCAB PEC, VDBULTOCAB BUC, VDBULTOLIN BUL, VDBULTOCABPINV BPC, VDMOVIM MOV, VDMOVIM MOVESP
            WHERE              
              BPC.CODBULTO   = :CODBULTO AND              
              PEC.CODPED(+)  = BUC.CODPED AND
              PEC.CODDIV(+)  = BUC.CODDIV AND
              PEC.ANOPED(+)  = BUC.ANOPED AND
              PEC.SEQPED(+)  = BUC.SEQPED AND
              BUC.CODBULTO   = BUL.CODBULTO AND
              MOV.CODBULTOORI= BPC.CODBULTO AND
              BUL.CODMOV     = MOV.CODMOV AND              
              MOV.CODMOVESP  = MOVESP.CODMOV(+)                           
        ORDER BY PEC.CODPED,PEC.CODDIV, PEC.ANOPED, PEC.SEQPED, BUC.CODBULTO, BUL.SEQLINEA;

WFRAME(362,-2,127,0,"Cantidad","")
WFRAME(486,-2,264,0,"Movimiento","")
WFRAME(739,-2,245,0,"Movto al que espera","")

WLONX=1000
CAMPO=CODDIV,TITULO("Div.")
CAMPO=CODPED,TITULO("Cod. Pedido")
CAMPO=ANOPED,TITULO("Año"),WLONX=15
CAMPO=SEQPED,TITULO("Sec."),WLONX=15
CAMPO=CODBULTOAUX,TITULO("Bulto")
CAMPO=SEQLINEA,TITULO("Lin"),WLONX=15
CAMPO=CODART,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CANTPEDIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Pedida"),WLONX=20
CAMPO=CANTSERVIDA,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART"),TITULO("Servida"),WLONX=20
CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO  
CAMPO=CODMOV,TITULO("Código")
CAMPO=STATUS,TITULO("St")
CAMPO=CODUBIORI,TITULO("Ubi Orig."),WLONX=25
CAMPO=CODUBIDEST,TITULO("Ubi Dest."),WLONX=25
CAMPO=CODMOVESP,TITULO("Código")
CAMPO=STATUSESP,TITULO("St")
CAMPO=CODUBIORIESP,TITULO("Ubi Orig."),WLONX=25
CAMPO=CODUBIDESTESP,TITULO("Ubi Dest."),WLONX=25
      
 
TECLA=SF9,FEJECUTAFORM("VDMOVIM","S","CODMOV=:CODMOV") 


