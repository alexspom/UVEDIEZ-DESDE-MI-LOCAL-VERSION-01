###################################################################
#Módulo: VDBULCABPINV2.PAN
#Funcionalidad : Bultos a los que abastece un bulto de picking inverso
#Autor: MGM   
#Fecha: 03-06-2008
###################################################################
# Histórico de cambios:
BULTOS A LOS QUE ABASTECE 
  
CodPed      Div. Año  Sec. Bulto             
_20________ _20_ @@@@ @@@@ __________________ 

|

SOLOQUERY
SELECT=SELECT PEC.CODPED,PEC.CODDIV, PEC.ANOPED, PEC.SEQPED, BUC.CODBULTO CODBULTOAUX
                FROM
                   VDPEDIDOCAB PEC, VDBULTOCAB BUC, VDBULTOLIN BUL, VDMOVIM MOV 
                WHERE
                   PEC.CODPED = BUC.CODPED AND
                   PEC.CODDIV = BUC.CODDIV AND
                   PEC.ANOPED = BUC.ANOPED AND
                   PEC.SEQPED = BUC.SEQPED AND
                   BUC.CODBULTO = BUL.CODBULTO AND
                   BUL.CODMOV = MOV.CODMOV AND                   
                   MOV.CODBULTOORI=:CODBULTO;
 
CAMPO=CODBULTO,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODPED,TITULO("Cod. Pedido")
CAMPO=CODDIV,TITULO("Div.")
CAMPO=ANOPED,TITULO("Año")
CAMPO=SEQPED,TITULO("Sec.")
CAMPO=CODBULTOAUX,TITULO("Bulto Expediciones")



