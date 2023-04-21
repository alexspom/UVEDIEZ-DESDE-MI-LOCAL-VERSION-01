# MOdulo   : VDIMPRESPOOLPDRE.FRM
# Función  : Spool de impresiones pdtes
#
# Creación : 20-05-2007
# Autor    : FGS
###########################################
# HistOrico de cambios:
BEGINBLOQUE=VDIMPRESPOOL.PAN
  PREREGISTRO=PRESEHIJO
  WHERE= STATUS<1000;
  ORDERBY= STATUS, PRIORIDAD, SEQIMPRE;
  PQUERY
  REGPAG=36
  POSX=1
  POSY=1
#  TIMEOUT=QUERYAUTOM,1000
  CONTEXTUAL=FEJECUTAFORM("VDIMPRESPOOLIMPRE","S","CODIMPRE=:CODIMPRE","","","Impresiones pendientes de impresora :CODIMPRE","S")
ONLINE={F1} Ayuda  {F4} Confirmar Cambios  {F6} Cambio de pantalla {Máy-F10} Impresiones pendientes de la impresora; 
ENDBLOQUE
BEGINBLOQUE=VDIMPRESPOOLDET.PAN
  PADRE=VDIMPRESPOOL.PAN
  PREQUERY=QUERYHIJO
  PREREGISTRO=PRESEHIJO
  POSY=41
  POSX=1
ENDBLOQUE 
