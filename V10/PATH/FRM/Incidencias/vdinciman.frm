# Módulo   : VDINCIDENCIAS.FRM
# Función  : MONITOR DE INCIDENCIAS
#
# Creación : 10-09-2009
# Autor    : JCSR
###########################################
# Histórico de cambios:
BEGINBLOQUE = VDINCICABMAN.PAN
	WLONX=630
	POSX = 1
	PREREGISTRO = PRESEHIJO
	NOORAINS
    NODELETE
#	BOTON = FACTURABLE,750,60,70,45,"FACTURAR",carte_rouge.png,F8,"Mandar a facturación",INCLUDECSS="background-color: transparent;border-width:0px"
	BOTON = CERRAR,650,60,70,70,"CERRAR INCIDENCIA",lock.png,CF7,"Cerrar incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
	BOTON = ANULAR,750,60,70,70,"ANULAR INCIDENCIA",ANULAR.png,AF8,"Anular incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
    BOTON = B1,850,60,70,70,"P",miimprimir.png,CF1,"Impresión de la Incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = RAQUETAZO,650,160,70,70,"CAMBIAR ASIGNACION",Users.png,CF8,"Cambiar el operario a quien \n está asignada",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = INFOCLI,750,160,70,70,"INFORMACION DEL CLIENTE",Agenda_icono.PNG,CF6,"Datos del cliente",INCLUDECSS="background-color: transparent;border-width:0px"
    BOTON = B5,450,545,50,50,"B5",adjuntar1.png,CF8,"Adjuntar archivos",INCLUDECSS="background-color: transparent;border-width:0px"
ENDBLOQUE
BEGINBLOQUE = VDLINEASINCI.PAN
	PADRE = VDINCICABMAN.PAN
	WLONX = 890
	POSY = 44
	REGPAG = 10
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO
	BOTON = AÑADIR,650,545,70,70,"AÑADIR LINEA",editpaste.png,AF7,"Añadir línea de incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
ENDBLOQUE
BEGINBLOQUE = VDOPEACTUACION.PAN
	PADRE = VDLINEASINCI.PAN
	POSX = 130
	POSY = 44
	WLONX= 600
    REGPAG = 10	
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO
ENDBLOQUE
BEGINBLOQUE = VDLINEASINCIART.PAN
	PADRE = VDINCICABMAN.PAN
	WLONX = 850
	WLONY = 350 
    POSX = 91
	POSY = 11
	REGPAG = 10
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO	
ENDBLOQUE
	
