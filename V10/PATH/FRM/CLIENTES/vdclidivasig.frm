#MOdulo: VDCLIDIVASIG.FRM
#Funcionalidad : Asignacion rapida de clientes a divisiones
#Autor: JMM
#Fecha: 06-10-2008
#*****************************************************************
#* HistOrico de cambios
#* ====================
#
BEGINBLOQUE=VDCLIENTESRES.PAN
  PREREGISTRO=PRESEHIJO
ENDBLOQUE
BEGINBLOQUE=VDCLIDIVASIG.PAN
  PADRE=VDCLIENTESRES.PAN
  PREQUERY=QUERYHIJO
  POSX=10
  POSY=26
  REGPAG=14
  NODELETE
  NOINSERT
ENDBLOQUE