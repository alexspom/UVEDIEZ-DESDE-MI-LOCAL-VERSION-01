# M�dulo   : VDINSERTALINEAINCI.FRM
# Funci�n  : PANTALLA PARA INSERTAR UNA L�NEA DE INCIDENCIA
#
# Creaci�n : 17-09-2009
# Autor    : JCSR
###########################################
# Hist�rico de cambios:
CAMPO = CODINCI, OCULTO, "@L@@@@@@@"
BEGINBLOQUE = VDINSERTALINEAINCI.PAN
	POSX = 27
	WPOSY = 100
	WLONY = 170	
	POSTCOMMIT = FPULSATECLAS ("F6")
	PREREGISTRO = PRESEHIJO
ENDBLOQUE
BEGINBLOQUE = VDOPEACTUACION.PAN
	POSX = 16
	POSY = 23
	PADRE = VDINSERTALINEAINCI.PAN
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO
ENDBLOQUE
	