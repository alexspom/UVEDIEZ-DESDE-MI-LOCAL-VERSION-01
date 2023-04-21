# Módulo   : VDGRAFICA.PAN
# Función  : PANTALLA DE DEFINICI'ON DE GRAFICAS EN V10
#
# Creación : 26-01-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
MANTENIMIENTO DE GRAFICAS DE ESTADISTICAS
NOMBREGRAF   DESGRAFICA             TITULOGRAF          LEYENDAGRAF  L CAMPOX        VDEXTRA   Ult. Modificación  
_32_________ _1024_________________ _255_______________ _255________ @ _32__________ _255_____ _32___ ¿D-MM-Y.YY ________
|

TABLA=VDGRAFICA
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=NOMBREGRAF,TOOLTIP("Nombre de la gráfica"),TITULO("Gráfica")
CAMPO=DESGRAFICA,TOOLTIP("Descripción de la gráfica"),TITULO("Descripción")
CAMPO=TITULOGRAF,TOOLTIP("Título a mostrar en la gráfica"),TITULO("Título")
CAMPO=LEYENDAGRAF,TOOLTIP("Título de la Leyenda de la gráfica;  NULL no se muestra"),TITULO("Leyenda")
CAMPO=LEYENDAESTADO,TOOLTIP("Estado de la leyenda del grafico; 0 oculta, 1 minimizada, 2 maximizada"),COMBOX("CLEYENDAESTADO"),WLONX=16
CAMPO=CAMPOX,TOOLTIP("Campo del bloque de los valores del eje x de la gráfica (eje y si orientacion es horizontal)"),TITULO("Campo")
CAMPO=VDEXTRA,TOOLTIP("Campo extra para información adiccional"),TITULO("Inf. Adicc.")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ult. Modif.")
CAMPO=FECMODIF,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora de la Ultima modificación")

# PARTE PERSONALIZADA DE LA PANTALLA 
CURSOR=CLEYENDAESTADO SELECT '0','OCULTO' FROM DUAL UNION
                      SELECT '1','MINIMIZADO' FROM DUAL UNION 
                      SELECT '2','MAXIMIZADO' FROM DUAL; 