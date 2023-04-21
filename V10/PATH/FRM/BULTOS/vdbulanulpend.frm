###################################################################
#MOdulo: VDBULANULPEND.PAN
#Funcionalidad : Formulario de anulación de cantidades pendientes de servir
#Autor: JMM      
#Fecha: 04-07-2008
###################################################################
# HistOrico de cambios:
BEGINBLOQUE=VDBULCAB.PAN
PREREGISTRO=PRESEHIJO
  POSX=1
  POSY=7
  PROTECT("ADMINISTRADOR")
  ORDERBY=CODPED,CODDIV,SEQPED,ANOPED,NBULTO;
ENDBLOQUE
BEGINBLOQUE=VDBULANULPEND.PAN
  PADRE=VDBULCAB.PAN
  PREQUERY=QUERYHIJO
  POSX=1
  POSY=33
  REGPAG=15
  PROTECT("ADMINISTRADOR")
ENDBLOQUE
