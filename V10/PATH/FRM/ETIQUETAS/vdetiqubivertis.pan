# Módulo   : VDETIQUBIVERTIS.PAN
# Función  : Impresión de etiquetas de ubicación en VERTIS
#
# Creación : 30-03-2011
# Autor    : FPD 
###########################################
# Histórico de cambios:
SELECCION DE UBICACIONES PARA IMPRESION DE ETIQUETAS

  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  
  ³                                                     ³ 
  ³                      Desde            Hasta         ³ 
  ³ Ubicación            _20_________     _20_________  ³ 
  ³ Pasillo              @L@@             @L@@          ³ 
  ³ Columna              @L@@             @L@@          ³ 
  ³ Altura               @L@@             @L@@          ³ 
  ³                                                     ³ 
  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
                                                            
  Número de etiquetas que queremos imprimir @L@
      
|


TABLA=DUAL

CAMPO=CODUBIDESDE, AUXILIAR, TOOLTIP("Ubicación desde la cual \nqueremos hacer la impresión de etiquetas")
CAMPO=CODUBIHASTA, AUXILIAR, TOOLTIP("Ubicación hasta la cual \nqueremos hacer la impresión de etiquetas")
CAMPO=PASILLODESDE, AUXILIAR, TOOLTIP("Ubicaciones cuyo pasillo se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=PASILLOHASTA, AUXILIAR, TOOLTIP("Ubicaciones cuyo pasillo se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=COLUMNADESDE, AUXILIAR, TOOLTIP("Ubicaciones cuya columna se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=COLUMNAHASTA, AUXILIAR, TOOLTIP("Ubicaciones cuya columna se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=ALTURADESDE, AUXILIAR, TOOLTIP("Ubicaciones cuya altura se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=ALTURAHASTA, AUXILIAR, TOOLTIP("Ubicaciones cuya altura se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=NUMETIQAIMPRIMIR, AUXILIAR, TOOLTIP("Número de etiquetas que vamos a querer imprimir")

TECLA=SF6,FPULSATECLAS("F6","F2")
                         
BOTON=BUSCAR,250,260,120,120,"Buscar ubicaciones",vertis\confprotolin.png,SF6,"Buscar ubicaciones",INCLUDECSS="border-style:outset;background-color:transparent"
