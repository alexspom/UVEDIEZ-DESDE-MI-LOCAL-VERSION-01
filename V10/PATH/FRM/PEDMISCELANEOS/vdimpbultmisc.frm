###################################################################
#MOdulo: VDIMPBULTMISC.FRM
#Funcionalidad : ImpresiOn de bultos de pedidos miscelaneos
#Autor: RFD      
#Fecha: 29-09-2009
###################################################################
# HistOrico de cambios:

BEGINBLOQUE=VDIMPBULTMISC.PAN
  PREBLOQUE=FEJECUTA(FLIMPIALECTURAS,"ERROR EN TRIGER FLIMPIALECTURAS",
                     FCOMMIT,"ERROR HACIENDO COMMIT")
  
  TIMEOUT=FEJECUTATIME(@FLECTURAS("CODBULTO","00","CODBULTO"),"ERROR EN TRIGER FLECTURAS",
                       FCOMMIT,"",
                       FPULSATECLAS("F2"),"ERROR EN FPULSATECLAS"),100

  POSX=1
  POSY=7
ENDBLOQUE

