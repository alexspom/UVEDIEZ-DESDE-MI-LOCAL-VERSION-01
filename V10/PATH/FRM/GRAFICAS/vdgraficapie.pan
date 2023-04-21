# Módulo   : VDGRAFICAPIE.PAN
# Función  : DEFINICION DE COLORES DE LOS SECTORES DE GRAFICAS DE PASTEL
#
# Creación : 27-01-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
COLORES SECTORES
N  COLORPIE      
   @L _32________ 
|

TABLA=VDGRAFICAPIE
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=NOMBREGRAF,VIRTUAL,TOOLTIP("Nombre de la gráfica"),OCULTO
CAMPO=NUMCOLOR,TITULO("N"),TOOLTIP("Número de color en la gráfica"),NOUPDATE
CAMPO=COLORPIE,TITULO("COLOR"),TOOLTIP("Color de la gráfica "),COMBOX("COLOR")
CAMPO=VDEXTRA,TITULO("INF. ADICCIONAL"),TOOLTIP("Campo reservado para información adiccional"),OCULTO,"_255___"
CAMPO=CODOPEMODIF,TITULO("ULT. MODIFICACION"),TOOLTIP("Operario que realizó la última modificación"),OCULTO,"_32___"
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación"),OCULTO,"¿D-MM-Y.YY"
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación"),OCULTO,"________"

# PARTE PERSONALIZADA DE LA PANTALLA 