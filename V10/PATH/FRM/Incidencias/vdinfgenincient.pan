# Módulo   : VDINFGENINCIENT.PAN
# Función  : ENTRADA DE DATOS PARA INCIDENCIAS
#
# Creación : 04/10/2011 17:07:51
# Autor    : JCSR
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
ENTRADA DE DATOS
CLIENTE                                        FECHA INICIO   FECHA FIN
_50__________________ _50__________________    ¿D-MM-Y.YY     ¿D-MM-Y.YY
|

NOQUERY
NOINSERT
NODELETE
NOUPDATE
NOCOMMIT
TABLA=DUAL
WLONX = 650

CAMPO = NOMBRE, AUXILIAR, POSTCHANGE =FDESIGNACION("+CSELCLIENTE", ""), TITULO ("Nombre comercial")
CAMPO = CODCLIENTE, AUXILIAR, TITULO ("CONSIGNATARIO")
CAMPO = FECINI, AUXILIAR, TITULO ("Fecha inicio del intervalo"), COMBOX("CALENDARIO"), WLONX = 100
CAMPO = FECFIN, AUXILIAR, TITULO ("Fecha fin del intervalo"), COMBOX("CALENDARIO"), WLONX = 100

CURSOR = CSELCLIENTE SELECT CODCLI CODCLIENTE FROM VDCLIENTES WHERE NOMBRE = :NOMBRE;

TECLA = SF4, FPULSATECLAS ("F6", "F2")