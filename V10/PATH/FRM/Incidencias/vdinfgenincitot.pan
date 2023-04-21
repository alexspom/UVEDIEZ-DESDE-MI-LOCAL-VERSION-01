# Módulo   : VDINFGENINCITOT.PAN
# Función  : TOTALES
#
# Creación : 15/11/2011 11:56:58
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
TOTALES
CANTIDAD  CANTIDADF  CANTIDADNF  HORASFAC           HORASNOF            HORASPREP 
@L@@@@@@  @L@@@@@@   @L@@@@@@    _30______________  _30______________   _30______________
|

SOLOQUERY
REGPAG = 2
WLONX=1047
SELECT = SELECT CANTIDAD,TO_CHAR(FLOOR (TIEMPOFACTURABLE/ 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPOFACTURABLE,60)) || ' min.' HORASFACTURABLES,
                TO_CHAR(FLOOR (TIEMPONOFACTURABLE / 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPONOFACTURABLE,60)) || ' min.' HORASNOFACTURABLES,
                TO_CHAR(FLOOR (TIEMPONULO / 60)) || ' horas, '|| TO_CHAR(MOD(TIEMPONULO,60)) || ' min.' HORASNULASFACTURABLES,
                CANTIDADFACTURABLE, CANTIDADNOFACTURABLE
                FROM(
                SELECT COUNT(DISTINCT INC.CODINCI) CANTIDAD,
                       SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'S',ILO.TIEMPO, DECODE(NVL(ILO.FACTURABLE, 'K'), 'S', ILO.TIEMPO, 0))) TIEMPOFACTURABLE, 
                       SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'S',0,  DECODE(NVL(ILO.FACTURABLE, 'K'), 'N', ILO.TIEMPO, 0))) TIEMPONOFACTURABLE,
                       SUM(DECODE (NVL(INC.FACTURABLE, 'K'), 'K', DECODE (NVL(ILO.FACTURABLE, 'K'), 'K' , ILO.TIEMPO, 0))) TIEMPONULO,
                       SUM(DECODE (NVL(INC.FACTURABLE, 'N'), 'S',1, 0)) CANTIDADFACTURABLE, 
                       SUM(DECODE (NVL(INC.FACTURABLE, 'N'), 'S',0, 1)) CANTIDADNOFACTURABLE
                  FROM VDINCICAB INC ,VDINCILINOPE ILO 
                 WHERE     ILO.CODINCI = INC.CODINCI 
                       AND (INC.CODCLI  = :CODCLIENTE OR :CODCLIENTE IS NULL)
                       AND STATUS <= 500
                       AND (INC.FECCREADO BETWEEN :FECINI AND :FECFIN OR (:FECINI = 0 AND :FECFIN = 0)));
                  
CAMPO = CANTIDAD, AUXILIAR, TITULO ("Cantidad total"), TOOLTIP("Total de incidencias"), WLONX = 80
CAMPO = CANTIDADFACTURABLE, AUXILIAR, TITULO ("Líneas facturables"), TOOLTIP("Total de incidencias facturables"), WLONX = 120
CAMPO = CANTIDADNOFACTURABLE, AUXILIAR, TITULO ("Líneas no facturables"), TOOLTIP("Total de incidencias no facturables"), WLONX = 120
CAMPO = HORASFACTURABLES, AUXILIAR, TITULO ( "Horas facturables" ), TOOLTIP ( "Horas facturables (sumatorio)" ), WLONX = 60
CAMPO = HORASNOFACTURABLES, AUXILIAR, TITULO ( "Horas no facturables" ), TOOLTIP ( "Horas no facturables (sumatorio)" ), WLONX = 60
CAMPO = HORASNULASFACTURABLES, AUXILIAR, TITULO ( "Horas prepago" ), TOOLTIP ( "Horas facturables a contratos prepago" ), WLONX = 60
CAMPO = CODCLIENTE, TITULO ( "CONSIGNATARIO" ), AUXILIAR, VIRTUAL, OCULTO
CAMPO = FECINI, AUXILIAR, VIRTUAL, OCULTO
CAMPO = FECFIN, AUXILIAR, VIRTUAL, OCULTO
CAMPO = NOMBRE, AUXILIAR, VIRTUAL, OCULTO


