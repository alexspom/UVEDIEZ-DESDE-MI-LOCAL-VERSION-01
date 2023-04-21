# Módulo   : VDETIQUBI.PAN
# Función  : Impresión de etiquetas de ubicación. Selecció de criterios
#
# Creación : 05-08-2008
# Autor    : JCSR
###########################################
# Histórico de cambios:
SELECCIÓN DE UBICACIONES PARA IMPRESIÓN DE ETIQUETAS

  ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  
  ³                                                     ³ 
  ³                      Desde            Hasta         ³ 
  ³ Ubicación            _20_________     _20_________  ³ 
  ³ Zona                 @L@              @L@           ³ 
  ³ Planta               @L@@             @L@@          ³ 
  ³ Pasillo              @L@@             @L@@          ³ 
  ³ Columna              @L@@             @L@@          ³ 
  ³ Altura               @L@@             @L@@          ³ 
  ³ Profundidad          @L@@             @L@@          ³ 
  ³ Órden de entrada     @L@@@@@@@        @L@@@@@@@     ³ 
  ³ Órden de salida      @L@@@@@@@        @L@@@@@@@     ³ 
  ³ Órden de movimiento  @L@@@@@@@        @L@@@@@@@     ³ 
  ³                                                     ³ 
  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
                                                            
  Artículo _40___________________ 
           _100___________________________________ 

      Área _20_______ 
           _40____________________________________ 
           
  Número de etiquetas que queremos imprimir @L@
      
|


TABLA=DUAL


CAMPO=CODUBIDESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicación desde la cual \nqueremos hacer la impresión de etiquetas")
CAMPO=CODUBIHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicación hasta la cual \nqueremos hacer la impresión de etiquetas")
CAMPO=ZONADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya zona se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")
CAMPO=ZONAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya zona se encuentra \nen un intervalo que termina \ncon el valor de este campo.")
CAMPO=PLANTADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya planta se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=PLANTAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya planta se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=PASILLODESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo pasillo se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=PASILLOHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo pasillo se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=COLUMNADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya columna se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=COLUMNAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya columna se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=ALTURADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya altura se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=ALTURAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya altura se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=PROFUNDIDADDESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya  profundidad se encuentra \nen un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=PROFUNDIDADHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuya profundidad se encuentra \nen un intervalo que termina \ncon el valor de este campo.")        
CAMPO=ORDENENTRADADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de entrada \nse encuentra en un intervalo que \ncomienza con el valor de este campo.")       
CAMPO=ORDENENTRADAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de entrada \nse encuentra en un intervalo que termina \ncon el valor de este campo.")        
CAMPO=ORDENSALIDADESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de salida \nse encuentra en un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=ORDENSALIDAHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de salida \nse encuentra en un intervalo que termina \ncon el valor de este campo.")        
CAMPO=ORDENMOVIMIENTODESDE,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de movimiento \nse encuentra en un intervalo que comienza \ncon el valor de este campo.")       
CAMPO=ORDENMOVIMIENTOHASTA,NOUPDATE, AUXILIAR, TOOLTIP("Ubicaciones cuyo órden de movimiento \nse encuentra en un intervalo que termina \ncon el valor de este campo.")        
CAMPO=CODART,NOUPDATE, AUXILIAR,TOOLTIP("Artículo asociado a la ubicación"),POSTCHANGE=FDESIGNACION("CSELARTIC","No existe artículo"),
                         CONTEXTUAL=FEJECUTAFORM("VDSELART","N","","","CODART=:CODART","Selección de artículo","S")
CAMPO=DESART,NOUPDATE, AUXILIAR, TOOLTIP("")
CAMPO=CODAREAREQ,NOUPDATE, AUXILIAR,TOOLTIP("Código del área al que pertenece la ubicación"),POSTCHANGE=FDESIGNACION("CSELAREA","No existe area"),
                         CONTEXTUAL=FEJECUTAFORM("VDSELAREA","N","","","CODAREA=:CODAREA","Selección de area","S")
CAMPO=DESAREA,NOUPDATE, AUXILIAR, TOOLTIP("")
CAMPO=NUMETIQAIMPRIMIR,NOUPDATE, AUXILIAR, TOOLTIP("Número de etiquetas que vamos a querer imprimir")
                         

CURSOR=CSELAREA SELECT DESAREA FROM VDAREA WHERE CODAREA=:CODAREAREQ
                   UNION
                 SELECT '' DESAREA FROM DUAL WHERE :CODAREAREQ IS NULL;

CURSOR=CSELARTIC SELECT DESART FROM VDARTIC WHERE CODART=:CODART
                   UNION
                 SELECT '' DESART FROM DUAL WHERE :CODART IS NULL;



