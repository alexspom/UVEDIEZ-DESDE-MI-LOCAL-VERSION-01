###################################################################
#MOdulo: VDBULTOSMA.PAN
#Funcionalidad : Mantenimiento de bultos
#Autor: RFD      
#Fecha: 08-04-2008
###################################################################
# HistOrico de cambios:
BEGINBLOQUE=VDBULCAB.PAN
PREREGISTRO=PRESEHIJO
#PREBLOQUE=FEJECUTA(FLIMPIALECTURAS,"ERROR EN TRIGER FLIMPIALECTURAS",
#                   FCOMMIT,"ERROR HACIENDO COMMIT")

#TIMEOUT=FEJECUTATIME(@FLECTURAS("CODBULTO","00","CODBULTO"),"ERROR EN TRIGER FLECTURAS",
#                   FCOMMIT,"",
#                   FPULSATECLAS("F2"),"ERROR EN FPULSATECLAS"),10          

  POSX=1
  POSY=7
ENDBLOQUE
BEGINBLOQUE=VDBULLIN.PAN
  PADRE=VDBULCAB.PAN
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=31
  WLONX=1390
  REGPAG=15
ENDBLOQUE
