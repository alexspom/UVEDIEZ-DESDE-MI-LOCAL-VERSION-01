# MOdulo   : VDORDENESRECEP.FRM
# Función  : Mantenimiento de las Ordenes de recepción
#
# Creación : 12-02-2007
# Autor    : ICC
###########################################
# HistOrico de cambios:
#  CAMPO=CODORDREC,OCULTO
CAMPO=SECLINORD,OCULTO
BEGINBLOQUE=VDORDRECCAB.PAN
  PREREGISTRO=PRESEHIJO
	REGPAG=5
  POSX=1
  POSY=1
ENDBLOQUE
BEGINBLOQUE=VDORDRECLIN.PAN
  PADRE=VDORDRECCAB.PAN
	PREQUERY=QUERYHIJO
	PREREGISTRO=PRESEHIJO
	REGPAG=11
  POSX=1
  POSY=12
ENDBLOQUE
BEGINBLOQUE=VDRECLINORDEN.PAN
  PADRE=VDORDRECLIN.PAN
	PREQUERY=QUERYHIJO
	PREREGISTRO=PRESEHIJO
	REGPAG=6
  POSX=1
  POSY=28
#  ORDERBY=CODART,CODLOT;
  ORDERBY=SECLINORD;
#  CAMPO=CODORDREC,VIRTUAL,OCULTO 
#  CAMPO=SECLINORD,VIRTUAL,OCULTO 
#  CAMPO=CODRECEP,OCULTO,"_20______",TOOLTIP("Numero de recepcion dentro de la misma orden de recepcion")
ENDBLOQUE
BEGINBLOQUE=VDFALTAREC.PAN
  PADRE=VDORDRECCAB.PAN
	PREQUERY=QUERYHIJO
	PREREGISTRO=PRESEHIJO
	REGPAG=10
  POSX=1
  POSY=38
ENDBLOQUE
