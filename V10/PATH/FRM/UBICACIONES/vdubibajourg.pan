# Módulo   : VDUBIBAJOMIN.PAN
# Función  : Consulta de ubicaciones bajo urgente. Listado de áreas
#
# Creación : 11-07-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
AREA
_20_______ _40_____________________________________
|



SOLOQUERY
SELECT=SELECT DISTINCT CODAREADEST CODAREA
         FROM VDFLUJOPARAM FLP
        WHERE FLP.TAREA = 'RECARGAR' AND CODAREADEST IN ('PU','RP')
        ORDER BY CODAREADEST;
        
CAMPO=CODAREA,NOENTER,TOOLTIP("Código de area"),POSTCHANGE=FDESIGNACION("+CSELDESAREA","")
CAMPO=DESAREA,AUXILIAR,NOENTER,TOOLTIP("Nombre completo del area")

CURSOR=CSELDESAREA SELECT DESAREA FROM VDAREA WHERE CODAREA = :CODAREA;

