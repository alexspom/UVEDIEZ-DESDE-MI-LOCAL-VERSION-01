###################################################################
#MOdulo: VDPICKINVRES.FRM
#Funcionalidad : Cambio de reserva de un bulto de picking inverso
#Autor: FGS
#Fecha: 10-03-2009
###################################################################
# HistOrico de cambios:
BEGINBLOQUE=VDBULCABPINV.PAN
  PREREGISTRO=PRESEHIJO
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=1
  AQUERY
ENDBLOQUE
BEGINBLOQUE=VDPICKINVRESSTK.PAN
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
  PADRE=VDBULCABPINV.PAN
  POSY=1
  POSX=81
  REGPAG=1
ENDBLOQUE  
BEGINBLOQUE=VDBULLINPINV.PAN
  WHERE = STATUS IN (VDST.FBPLASERVIR,VDST.FBPLRESTOS);
  PADRE=VDBULCABPINV.PAN
  POSY=16
  REGPAG=10
ENDBLOQUE  
BEGINBLOQUE=VDPICKINVRES.PAN
  PADRE=VDPICKINVRESSTK.PAN
  POSY=28
  REGPAG=20
ENDBLOQUE  
