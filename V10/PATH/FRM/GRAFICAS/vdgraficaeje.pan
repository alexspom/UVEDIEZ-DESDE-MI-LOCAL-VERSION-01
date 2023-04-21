# Módulo   : VDGRAFICAEJE.PAN
# Función  : PANTALLA DE DEFINICION DE EJES DE GRAFICAS EN V10
#
# Creación : 26-01-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:   
MANTENIMIENTO DE EJES DE GRAFICAS DE ESTADISTICAS   
                                                   
 Tipo de Eje: _  Título:  _255_____________________________________ Clase Css Título:  _32____________        
  
 ÏÄÄÄÄÄÄÄÄ Valores ÄÄÄÄÄÄÄË   ÏÄÄÄÄÄÄÄÄ Cursor Inf. ÄÄÄÄÄÄÄË  ÏÄÄÄÄÄÄÄÄ Rejilla ÄÄÄÄÄÄÄÄË  ÏÄÄÄÄÄÄÄÄÄÄ Formato ÄÄÄÄÄÄÄÄÄË
 ³ Máx      @L@@@@@@@     ³   ³ Texto _32_________________ ³  ³ Grosor   @L             ³  ³ Moneda             _       ³
 ³ Min      @L@@@@@@@     ³   ³ Color Fondo _32___________ ³  ³ Color    _32___________ ³  ³ Decimales Forzados @L      ³
 ³ ClassCss _32__________ ³   ³ Color Texto _32___________ ³  ³ Opacidad @L             ³  ³ Decimales Máximos  @L      ³
 ³                        ³   ³ ClassCss    _32___________ ³  ³                         ³  ³ Separador dec. _  miles. _ ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
   
   Inf. Adiccional: _255__________________  Ult. Modificación: _32_________ ¿D-MM-Y.YY ________ 
   
|

TABLA=VDGRAFICAEJE
PREINSERT=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN CSELMODIF")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=NOMBREGRAF,VIRTUAL,TOOLTIP("Nombre de la gráfica"),OCULTO
CAMPO=EJE,TOOLTIP("Tipo de Eje, X o Y "),COMBOX("X","Y")
CAMPO=TITULOEJE,TOOLTIP("Texto a mostrar en el Eje ")
CAMPO=CSSTITULO,TOOLTIP("Clase CSS del TITULO del eje"),MIXED,COMBOX("ejetitulo")

CAMPO=MAXVALOR,TOOLTIP("Máximo valor del eje (si se informa)")
CAMPO=CURSORTEXTO,TOOLTIP("Prefijo del Texto de información de cursor del eje, NULO no se muestra")
CAMPO=GRIDGROSOR,TOOLTIP("Grosor de la línea de rejilla del eje,NULO no se muestran"),COMBOX("0","1","2","3","4","5","6","7","8","9","10")
CAMPO=VALORESMONEDA,TOOLTIP("Si se informa, valor del eje muestra monedas con este símbolo")
#,COMBOX("$","£","¥","€"),WLONX=16
CAMPO=MINVALOR,TOOLTIP("Mínimo valor del eje (si se informa)")
CAMPO=CURSORCOLOR,TOOLTIP("Color de fondo del texto de cursor del eje  "),COMBOX("COLOR")
CAMPO=GRIDCOLOR,TOOLTIP("Color de las líneas de rejilla  "),COMBOX("COLOR")
CAMPO=VALORESMINDEC,TOOLTIP("Si se informa, número de decimales forzados en valores del eje"),COMBOX("0","1","2","3","4","5")
CAMPO=CSSVALORES,TOOLTIP("Clase CSS de los textos de valores del eje  "),MIXED,COMBOX("ejevalor","ejetitulo2","invisible")
CAMPO=CURSORTEXTCOLOR,TOOLTIP("Color del texto de cursor del eje  "),COMBOX("COLOR")
CAMPO=GRIDOPACIDAD,TOOLTIP("Opacidad de las líneas de rejilla  ")
CAMPO=VALORESMAXDEC,TOOLTIP("Si se informa, número de decimales máximo en valores del eje"),COMBOX("0","1","2","3","4","5")
CAMPO=CURSORCSS
CAMPO=VALORESSEPDEC,TOOLTIP("Si se informa, símbolo separador de decimales"),COMBOX(",",".")
CAMPO=VALORESSEPMIL,TOOLTIP("Si se informa, símbolo separador de miles"),COMBOX(",",".")
CAMPO=VDEXTRA,TOOLTIP("Campo reservado para información adiccional")
CAMPO=CODOPEMODIF,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,TOOLTIP("Fecha en la que se realizó la Ultima modificación")
CAMPO=HORAMODIF,TOOLTIP("Hora en la que se realizó la Ultima modificación")

# PARTE PERSONALIZADA DE LA PANTALLA 