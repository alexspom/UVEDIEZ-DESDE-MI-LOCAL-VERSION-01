BEGINBLOQUE=VDLISTAPEDIDOSPREPFILTRO.PAN
 PREREGISTRO=PRESEHIJO
  CAMPO=EXCLUIR,OCULTO,"________________"
ENDBLOQUE

BEGINBLOQUE=VDLISTAPEDIDOSPREP.PAN
 PADRE=VDLISTAPEDIDOSPREPFILTRO.PAN
#CAMPO=SERIE,OCULTO,"@L@@@@" 
 PREREGISTRO=PRESEHIJO
 NOINSERT
 NODELETE
 NOUPDATE
 POSY=09
 REGPAG=30
ENDBLOQUE
