# Módulo   : VDGRAFICASERIE.PAN
# Función  : PANTALLA DE DEFINICION DE SERIES DE GRAFICAS EN V10
#
# Creación : 26-01-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
MANTENIMIENTO DE SERIES DE GRAFICAS DE ESTADISTICAS

 Número: @L Tipo: __________ Campo: _32___________  Título: _255____________________________________  Offset X: @L@ Offset Y: @L@              
 
 ÏÄÄÄÄ Leyenda ÄÄÄË  ÏÄÄÄÄÄÄ Valores ÄÄÄÄÄÄË  ÏÄÄÄÄ Graf. Barras ÄÄÄË  ÏÄÄÄ Series y Líneas ÄÄÄË  ÏÄÄÄÄÄ Graf. Pastel ÄÄÄÄÄË
 ³                ³  ³ Color: _32_________ ³  ³                     ³  ³ Punto                 ³  ³                        ³
 ³ Visible:   _   ³  ³ Ancho:       @L     ³  ³ Agrupar Barras: _   ³  ³   tamaño:@L           ³  ³ Porc. Ancho: @L        ³
 ³ Desglosar: _   ³  ³ Opacidad:    @L     ³  ³ Orientación:    _   ³  ³   color: _32_________ ³  ³ Porc. Alto:  @L        ³
 ³                ³  ³ Ancho Borde: @L     ³  ³                     ³  ³ Borde Punto           ³  ³ Posición: _32________  ³
 ³                ³  ³ Opac. Borde: @L     ³  ³                     ³  ³   tamaño:@L           ³  ³ Ver Etiq.     _        ³
 ³                ³  ³                     ³  ³                     ³  ³   color: _32_________ ³  ³                        ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
                                                                      
  Inf. Adiccional: _255__________________  Ult. Modificación: _32_________ ¿D-MM-Y.YY ________   


|                                                                   

TABLA=VDGRAFICASERIE
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=NOMBREGRAF,VIRTUAL,TOOLTIP("Nombre de la gráfica"),OCULTO
CAMPO=NUMSERIE,TOOLTIP("Número de serie en la gráfica")
CAMPO=TIPOSERIE,TOOLTIP("Tipo de Serie: Linea, Barras, Area o Pastel"),COMBOX("BARRAS","LINEA","AREAS","PASTEL")
CAMPO=CAMPOSERIE,TOOLTIP("Campo del bloque del cual se muestran los valores en la serie")
CAMPO=TITULOSERIE,TOOLTIP("Titulo de la serie")
CAMPO=PADDINGX,TOOLTIP("Desplazamiento de los valores en el eje X (horizotalmente)")
CAMPO=PADDINGY,TOOLTIP("Desplazamiento de los valores de la gráfica en el eje Y (verticalmente)")

CAMPO=COLORVALORSERIE,TOOLTIP("Color de los valores de la serie"),COMBOX("COLOR")
CAMPO=LEYENDASERIE,TOOLTIP("Si se incluye la serie en la leyenda de la gráfica"),CHECKBOX("N","S")
CAMPO=ANCHOVALORSERIE
CAMPO=AGRUPARBARRAS,TOOLTIP("En serie de barras, si se agrupan barras "),CHECKBOX("N","S")
CAMPO=TAMAÑOPUNTO,TOOLTIP("Tamaño de los puntos"),COMBOX("0","1","2","3","4","5","6","7","8","9","10")
CAMPO=ANCHOPIE,TOOLTIP("Porcentaje de anchura del pastel de 0(100) a 99")
CAMPO=LEYENDAARBOL,TOOLTIP("Si se despliegan los valores de la serie en el leyenda, a modo de árbol"),CHECKBOX("N","S")
CAMPO=OPACIDADVALORSERIE,TOOLTIP("Opacidad de los valores de la serie (linea, barra o sector de pastel) ")
CAMPO=ORIENTACION,COMBOX("CORIENTACION")
CAMPO=COLORPUNTO,TOOLTIP("Color de los puntos de las líneas o áreas "),COMBOX("COLOR")
CAMPO=ALTOPIE,TOOLTIP("Porcentaje de altura del pastel de 0(100) a 99")
CAMPO=ANCHOBORDESERIE,TOOLTIP("Ancho del borde de los valores de la serie  ")
CAMPO=POSICIONPIE,TOOLTIP("Posición del pasten en el DIV de la gráfica"),MIXED,COMBOX("left","right","center","topLeft","topCenter","topRight","centerLeft","centerRight","bottomLeft","bottomCenter","bottomRight")
CAMPO=OPACIDADBORDERSERIE,TOOLTIP("Opacidad del borde de los valores de la serie")
CAMPO=ANCHOBORDEPUNTO,TOOLTIP("Ancho del borde de los puntos"),COMBOX("0","1","2","3","4","5","6","7","8","9","10")
CAMPO=VERLABELPIE,TOOLTIP("Muestra etiquetas de sectores del pastel S/N"),CHECKBOX("N","S")

CAMPO=COLORBORDEPUNTO,TOOLTIP("Color de los bordes de estos puntos "),COMBOX("COLOR")


CAMPO=VDEXTRA,TOOLTIP("Campo V10 para información adiccional")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

# PARTE PERSONALIZADA DE LA PANTALLA 
CURSOR=CORIENTACION SELECT 'V','VERTICAL' FROM DUAL UNION SELECT 'H','HORIZONTAL' FROM DUAL;