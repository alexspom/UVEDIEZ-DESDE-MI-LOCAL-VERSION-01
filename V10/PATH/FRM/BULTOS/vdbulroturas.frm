# MOdulo   : VDBULROTURAS.FRM              
# Función  : Roturas de bultos
#                                          
# Creación : 01-09-2008                    
# Autor    : MGM                           
###########################################
BEGINBLOQUE=VDBULCABRED.PAN
PREREGISTRO=PRESEHIJO
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=1
  NOENTER
  WHERE=CODBULTO IN (SELECT CODBULTO FROM VDBULTOLIN WHERE STATUS = VDST.FBULSERVIDA) AND 
        (CODPED,CODDIV,ANOPED,SEQPED) IN (SELECT CODPED,CODDIV,ANOPED,SEQPED FROM VDPEDIDOCAB PEC, VDSERIEEXP SEX WHERE PEC.CODSERIEEXP = SEX.CODSERIEEXP AND SEX.STATUS <= VDST.FSEXIMPRESA);
  ORDERBY=CODPED,CODDIV,SEQPED,ANOPED,NBULTO;
ENDBLOQUE
BEGINBLOQUE=VDBULLINROTURA.PAN
  PADRE=VDBULCABRED.PAN
  WHERE=STATUS=VDST.FBULSERVIDA;
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
  POSX=1
  POSY=10
  REGPAG=15
ENDBLOQUE
BEGINBLOQUE=VDSTKROTURA.PAN
  PADRE=VDBULLINROTURA.PAN
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=28
  REGPAG=28
ENDBLOQUE
