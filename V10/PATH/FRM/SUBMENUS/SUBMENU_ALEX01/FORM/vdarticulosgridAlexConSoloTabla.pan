# Módulo   : vdarticulosgridalexConSoloTabla.PAN
# Función  : Listado de articulos REDUR
#
# Creación : 28-03-2020
# Autor    : infanahe
###########################################
# Histórico de cambios:
#
lista prueba alexader solo tabla
 CODDIV 	  CODART     DESART             CODARTDIV
 _20__________ _20______  _10______________  _10___    
 |
 
 TABLA=VDARTIC_POCASCOLUMNAS_ALEX_TEST
 WHERE=CODDIV IS NOT NULL;
 
 WLONX=1000
 
CAMPO=CODDIV,NOENTER,TOOLTIP("PRueba campo2"),TITULO("CAMPO CODDIV"), WLONX=30
CAMPO=CODART,TOOLTIP("PRueba campo1"),TITULO("CAMPO CODART"), WLONX=10
CAMPO=CODARTDIV,TOOLTIP("PRueba campo3"),TITULO("CAMPO CODARTDIV"), WLONX=30
CAMPO=DESARTALT,TOOLTIP("PRueba campo4"),TITULO("CAMPO DESARTALT"), WLONX=30



