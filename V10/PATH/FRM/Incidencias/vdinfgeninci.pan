# M�dulo   : VDINFGENINCI.PAN
# Funci�n  : INFORME GENERAL DE INCIDENCIAS
#
# Creaci�n : 06-10-2009
# Autor    : JCSR
# Fichero generado por el Asistente de Generaci�n de Pantallas V10 
###########################################
# Hist�rico de cambios:
INFORME GENERAL DE INCIDENCIAS
CODINCI   CODCLI            CODMANTENI DESCRIPCION            GR FECCREADO  HORACREA FECCERRADO HORACERR P CONTACTO               HORASFAC      HORASNOF      HORAS REP
@L@@@@@@@ _50______ _50____ __________ _500__________________ @L �D-MM-Y.YY ________ �D-MM-Y.YY ________ _ _100__________________ _30__________ _30__________ _30__________
|

SOLOQUERY
SELECT = SELECT CODINCI,
                TO_CHAR(FLOOR (TIEMPOFACTURABLE/ 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPOFACTURABLE,60)) || ' min.' HORASFACTURABLES,
                TO_CHAR(FLOOR (TIEMPONOFACTURABLE / 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPONOFACTURABLE,60)) || ' min.' HORASNOFACTURABLES, 
				CODCLI,CODMANTENIMIENTO, DESCRIPCION, GRAVEDAD, FECCREADO, HORACREADO, FECCERRADO, HORACERRADO, PRESENCIAL , STATUS, CONTACTO,
                    TIEMPOFACTURABLE, TIEMPONOFACTURABLE
				FROM(
		SELECT INC.CODINCI,
				SUM(DECODE (NVL(INC.FACTURABLE, 'N'), 'S',ILO.TIEMPO, DECODE(ILO.FACTURABLE, 'S', ILO.TIEMPO, 0))) TIEMPOFACTURABLE, 
				SUM(DECODE (NVL(INC.FACTURABLE, 'N'), 'S',0, DECODE(ILO.FACTURABLE, 'N', ILO.TIEMPO, 0))) TIEMPONOFACTURABLE , 
				INC.CODCLI, INC.CODMANTENIMIENTO, INC.DESCRIPCION, INC.GRAVEDAD, INC.FECCREADO, INC.HORACREADO, 
				INC.FECCERRADO, INC.HORACERRADO, NVL(INC.PRESENCIAL, 'N') PRESENCIAL, INC.STATUS, INC.CONTACTO 
		   FROM VDINCICAB INC ,VDINCILINOPE ILO 
		  WHERE     ILO.CODINCI = INC.CODINCI 
                  AND (INC.CODCLI  = :CODCLIENTE OR :CODCLIENTE IS NULL)
                  AND STATUS <= 500
                  AND (INC.FECCREADO BETWEEN :FECINI AND :FECFIN OR (:FECINI = 0 AND :FECFIN = 0))
         GROUP BY INC.CODINCI, INC.CODCLI, INC.CODMANTENIMIENTO, INC.DESCRIPCION, 
		        INC.GRAVEDAD, INC.FECCREADO, INC.HORACREADO, INC.FECCERRADO, INC.HORACERRADO, INC.PRESENCIAL, 
				INC.STATUS, INC.CONTACTO, INC.FACTURABLE 
	    ORDER BY CODINCI DESC);

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO = CODINCI, TITULO ( "Incid." ), TOOLTIP ( "N�mero de la incidencia" ), WLONX = 10
CAMPO = CODCLI, TITULO ( "CONSIGNATARIO" ), TOOLTIP ( "C�digo del CONSIGNATARIO" ), POSTCHANGE = FDESIGNACION("CSELCLIENTE", "")
CAMPO = NOMBRE, AUXILIAR, TOOLTIP("Nombre comercial"), NOENTER
CAMPO = CODMANTENIMIENTO, TITULO ( "Mant." ), TOOLTIP ( "Contrato de mantenimiento asociado a la incidencia" ), WLONX = 20
CAMPO = DESCRIPCION, TITULO ( "Descripcion" ), TOOLTIP ( "Descripci�n de la incidencia" )
CAMPO = GRAVEDAD, TITULO ( "Grav." ), TOOLTIP ( "Gravedad de la incidencia" ), WLONX = 22
CAMPO = FECCREADO, TITULO ( "Creada el" ), TOOLTIP ( "Fecha de creaci�n" )
CAMPO = HORACREADO, TOOLTIP ( "Hora de creaci�n" )
CAMPO = FECCERRADO, TITULO ( "Cerrada el" ), TOOLTIP ( "Fecha de cierre de incidencia" )
CAMPO = HORACERRADO, TOOLTIP ( "Hora de cierre de incidencia" )
CAMPO = PRESENCIAL, TITULO ( "Pre." ), TOOLTIP ( "La incidencia ha requerido que personal se presente en la planta para resolverla" ), WLONX = 20
CAMPO = STATUS, TITULO ( "Estado" ), TOOLTIP ( "Estado" ) , WLONX = 10, POSTCHANGE = FDESIGNACION ("CSELDESSTATUS", "NO ENCUENTRO EL ESTADO"), OCULTO, "@L@@@"
CAMPO = DESSTATUS, TOOLTIP (" Descripci�n del estado"), WLONX = 20, OCULTO, "_30_"
CAMPO = CONTACTO, TITULO ( "Contacto en el CONSIGNATARIO" ), TOOLTIP ( "Contacto" ), WLONX = 20
CAMPO = HORASFACTURABLES, TITULO ( "T. facturable" ), TOOLTIP ( "Horas facturables (sumatorio)" ), WLONX = 20
CAMPO = HORASNOFACTURABLES, TITULO ( "T. no facturable" ), TOOLTIP ( "Horas no facturables (sumatorio)" ), WLONX = 20
CAMPO = HORASNULASFACTURABLES, AUXILIAR, TITULO ( "T. prepago" ), TOOLTIP ( "Horas facturables a contratos prepago" ), WLONX = 20
CAMPO = CODCLIENTE, AUXILIAR, VIRTUAL, OCULTO
CAMPO = FECINI, AUXILIAR, VIRTUAL, OCULTO
CAMPO = FECFIN, AUXILIAR, VIRTUAL, OCULTO
CAMPO = TIEMPOFACTURABLE, AUXILIAR, OCULTO, "#L######,####.###", TITULO("Tiempo facturable en minutos")
CAMPO = TIEMPONOFACTURABLE, AUXILIAR, OCULTO, "#L######,####.###", TITULO("Tiempo no facturable en minutos")
CAMPO = TIEMPONULO, AUXILIAR, OCULTO, "#L######,####.###", TITULO("Tiempo nulo para incidencias prepago en minutos")

# PARTE PERSONALIZADA DE LA PANTALLA 

CURSOR = CSELDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS = :STATUS AND TIPOSTATUS = 'IND';

CURSOR = CSELCLIENTE SELECT  NOMBRE FROM VDCLIENTES WHERE CODCLI = :CODCLI;