# Módulo   : VDUBIBAJOMIN.PAN
# Función  : Consulta de ubicaciones bajo mínimo. Listado de áreas
#
# Creación : 11-07-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
AREA
_20_______ _40_____________________________________
|



SOLOQUERY
SELECT=SELECT DISTINCT CODAREADEST 
         FROM VDFLUJOPARAM FLP
        WHERE FLP.TAREA = 'RECARGAR';
ORDERBY=CODAREADEST;
        
CAMPO=CODAREADEST,NOENTER,TOOLTIP("Código de area"),POSTCHANGE=FDESIGNACION("+CSELDESAREA","")
CAMPO=DESAREA,AUXILIAR,NOENTER,TOOLTIP("Nombre completo del area")

CURSOR=CSELDESAREA SELECT DESAREA FROM VDAREA WHERE CODAREA = :CODAREADEST;

