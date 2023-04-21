# Módulo   : VDINFGENINCI.FRM
# Función  : MONITOR DE INCIDENCIAS
#
# Creación : 10-09-2009
# Autor    : JCSR
###########################################
# Histórico de cambios:
BEGINBLOQUE = VDINFGENINCIENT.PAN
	BOTON = BUSCAR,680,10,70,70,"Buscar",buscar.png,SF4,"Buscar",INCLUDECSS="background-color: transparent;border-width:0px"
	REGPAG =2
	PREREGISTRO = PRESEHIJO
ENDBLOQUE
BEGINBLOQUE = VDINFGENINCI.PAN
TECLA = SF10, FEJECUTAFORM ("VDINCIDENCIAS", "S","CODINCI=:CODINCI","","DATOS DE LA INCIDENCIA :CODINCI")
SELECT = SELECT CODINCI,
                TO_CHAR(FLOOR (TIEMPOFACTURABLE/ 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPOFACTURABLE,60)) || ' min.' HORASFACTURABLES,
                TO_CHAR(FLOOR (TIEMPONOFACTURABLE / 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPONOFACTURABLE,60)) || ' min.' HORASNOFACTURABLES, 
                TO_CHAR(FLOOR (TIEMPONULO / 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPONULO,60)) || ' min.' HORASNULASFACTURABLES,
				CODCLI,CODMANTENIMIENTO, DESCRIPCION, GRAVEDAD, FECCREADO, HORACREADO, FECCERRADO, HORACERRADO, PRESENCIAL , STATUS, CONTACTO,
        TIEMPOFACTURABLE, TIEMPONOFACTURABLE, TIEMPONULO
				FROM(
		SELECT INC.CODINCI,
				SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'S',ILO.TIEMPO, DECODE(NVL(ILO.FACTURABLE, 'K'), 'S', ILO.TIEMPO, 0))) TIEMPOFACTURABLE, 
                       SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'S',0,  DECODE(NVL(ILO.FACTURABLE, 'K'), 'N', ILO.TIEMPO, 0))) TIEMPONOFACTURABLE,
                       SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'K', DECODE (NVL(ILO.FACTURABLE, 'K'), 'K' , ILO.TIEMPO, 0))) TIEMPONULO,
                       INC.CODCLI, INC.CODMANTENIMIENTO, INC.DESCRIPCION, INC.GRAVEDAD, INC.FECCREADO, INC.HORACREADO, 
				INC.FECCERRADO, INC.HORACERRADO, NVL(INC.PRESENCIAL, 'N') PRESENCIAL, INC.STATUS, INC.CONTACTO 
		   FROM VDINCICAB INC ,VDINCILINOPE ILO 
		  WHERE     ILO.CODINCI = INC.CODINCI 
                  AND (INC.CODCLI  = :CODCLIENTE OR :CODCLIENTE IS NULL)
                  AND STATUS BETWEEN 100 AND 500
                  AND (INC.FECCREADO BETWEEN :FECINI AND :FECFIN OR (:FECINI = 0 AND :FECFIN = 0))
         GROUP BY INC.CODINCI, INC.CODCLI, INC.CODMANTENIMIENTO, INC.DESCRIPCION, 
		        INC.GRAVEDAD, INC.FECCREADO, INC.HORACREADO, INC.FECCERRADO, INC.HORACERRADO, INC.PRESENCIAL, 
				INC.STATUS, INC.CONTACTO, INC.FACTURABLE 
	    ORDER BY CODINCI DESC);
  PADRE = VDINFGENINCIENT.PAN
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO
	POSX = 1
	POSY = 7
	REGPAG =35
  WLONX = 1300
	BOTON = LIMPIAR,680,10,70,70,"LIMPIAR PANTALLA",terminal.png,F5,"Limpiar la pantalla para hacer búsquedas",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = BUSCAR,680,10,70,70,"Buscar",buscar.png,SF4,"Buscar",INCLUDECSS="background-color: transparent;border-width:0px"
	BOTON = EXPORTAR,780,10,70,70,"EXPORTAR",EXCEL.png,F11,"Exportar a Excel",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = IMPRIMIR,650,160,70,70,"IMPRIMIR DATOS",miok.png,CF7,"Cerrar incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = ANULAR,850,160,70,70,"ANULAR INCIDENCIA",ANULAR.png,AF8,"Anular incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = RAQUETAZO,650,290,70,70,"CAMBIAR ASIGNACION",Users.png,CF8,"Cambiar el operario a quien \n está asignada",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = PEDIRINFO,850,290,70,70,"PEDIR INFORMACION",info.png,F7,"Pedir información al cliente",INCLUDECSS="background-color: transparent;border-width:0px"
ENDBLOQUE
BEGINBLOQUE = VDINFGENINCITOT.PAN
  PADRE = VDINFGENINCIENT.PAN
	PREQUERY = QUERYHIJO
	PREREGISTRO = PRESEHIJO
	POSX = 1
	POSY = 47
	BOTON = LIMPIAR,680,10,70,70,"LIMPIAR PANTALLA",terminal.png,F5,"Limpiar la pantalla para hacer búsquedas",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = BUSCAR,680,10,70,70,"Buscar",buscar.png,SF4,"Buscar",INCLUDECSS="background-color: transparent;border-width:0px"
	BOTON = EXPORTAR,780,10,70,70,"EXPORTAR",EXCEL.png,F11,"Exportar a Excel",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = IMPRIMIR,650,160,70,70,"IMPRIMIR DATOS",miok.png,CF7,"Cerrar incidencia",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = ANULAR,850,160,70,70,"ANULAR INCIDENCIA",ANULAR.png,AF8,"Anular incidencia",INCLUDECSS="background-color: transparent;border-width:0px"

#	BOTON = RAQUETAZO,650,290,70,70,"CAMBIAR ASIGNACION",Users.png,CF8,"Cambiar el operario a quien \n está asignada",INCLUDECSS="background-color: transparent;border-width:0px"
#	BOTON = PEDIRINFO,850,290,70,70,"PEDIR INFORMACION",info.png,F7,"Pedir información al cliente",INCLUDECSS="background-color: transparent;border-width:0px"


ENDBLOQUE