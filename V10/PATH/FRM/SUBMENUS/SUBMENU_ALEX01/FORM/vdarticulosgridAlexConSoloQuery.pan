# Módulo   : vdarticulosgridalexConSoloTabla.PAN
# Función  : Listado de articulos REDUR
#
# Creación : 28-03-2020
# Autor    : infanahe
###########################################
# Histórico de cambios:
#
lista prueba alexader solo QUERY
 CODDIV 	  CODART          DESART             CODARTDIV CALCULO
 _20__________ _20__________  _20______________  _20___    _20______
 |
 
 PQUERY
 TABLA=ALEX
 SOLOQUERY
 SELECT = select ALEX.CODDIV, ALEX.CODART, ALEX.DESARTALT, ALEX.CODARTDIV from VDARTIC_POCASCOLUMNAS_ALEX_TEST ALEX
		  WHERE UPPER(ALEX.CODART) LIKE NVL(:CODART,'BEL%');
 
 WLONX=1000
 
CAMPO=CODDIV,NOENTER,TOOLTIP("PRueba campo2"),TITULO("CAMPO CODDIV"), WLONX=30
CAMPO=CODART,TOOLTIP("PRueba campo1"),TITULO("CAMPO CODART"), WLONX=100
CAMPO=CODARTDIV,LOWER,NOENTER,TOOLTIP("PRueba campo3"),TITULO("CAMPO CODARTDIV"), WLONX=30
CAMPO=DESARTALT,NOENTER,TOOLTIP("PRueba campo4"),TITULO("CAMPO DESARTALT"), WLONX=30
CAMPO=CALCULO,AUXILIAR,NOENTER,TOOLTIP("PRueba campo5"),TITULO("CAMPO CALCULO"), WLONX=30, POSTCHANGE=FDESIGNACION("ALE")

CURSOR=ALE SELECT 'PRUEBA CALULO' AS "CALCULO" FROM DUAL;
CURSOR=mensaje select CODDIV from VDARTIC_POCASCOLUMNAS_ALEX_TEST WHERE 1=0;

TECLA=F8, FEJECUTA("!mensaje","CUIDADO: Prueba de mensaje disparador.\n ¿ Funciono y aparecio el mensaje  ? \n ")


ONLINE= {F1} Ayuda    {F2} Consulta    {F5} Borrar Pantalla    {Esc} Cerrar Pantalla ;




