# MOdulo   : VDMOVIM.PAN
# Función  : Mantenimiento de movimientos
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# HistOrico de cambios:
MANTENIMIENTO DE MOVIMIENTOS

  Código   @L@@@@@@@   Estado   @L@@@@  _40______________________________________     Recurso ____________   Prioridad @L@@@
  
  Tarea    _32____________ _40___________________________       Concepto __________ _40_____________________________________        
  
                    ÏÄÄÄÄÄÄÄÄÄÄÄ Origen ÄÄÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄÄÄÄÄÄÄ Intermedio ÄÄÄÄÄÄÄÄÄÄË ÏÄÄÄÄÄÄÄÄÄÄÄ Destino ÄÄÄÄÄÄÄÄÄÄÄÄË
                    ³                               ³ ³                               ³ ³                                ³ 
  Ubicación - área: ³  _20__________ - _20_______   ³ ³  _20__________ - _20_______   ³ ³  _20__________ - _20_______    ³
  Matrícula:        ³  __________________           ³ ³  __________________           ³ ³  __________________            ³
  Bulto:            ³  __________________           ³ ³                               ³ ³  __________________            ³
                    ³                               ³ ³                               ³ ³                                ³
                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Enrutamiento   ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  ÏÄÄÄÄÄ Agrupación  ÄÄÄÄÄË  ÏÄÄÄÄÄÄÄ Demanda  ÄÄÄÄÄÄÄÄË
 ³ Flujo              @L@@@@@@@@  Solo mueve      _              ³  ³                       ³  ³                         ³ 
 ³ Mov. al que espera @L@@@@@@@@  Tipo contenedor __________     ³  ³ Documento   @L@@@@@@@ ³  ³ Código: _20____________ ³
 ³ Siguiente paso     @L@@@@@@@@                                 ³  ³ Interfase   @L@@@@@@@ ³  ³ Tipo:   _10_______      ³
 ³                                                               ³  ³ Preparación @L@@@@@@@ ³  ³ Línea:  @@@@@@@         ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Seguimiento  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË 
 ³                 Operario          Fecha       Hora       Modulo                      Acción                           ³  
 ³   Creación      _32____________   ¿D-MM-Y.YY  ________   _64______________________   _64____________________________  ³  
 ³   Planificación                   ¿D-MM-Y.YY  ________   _64______________________   _64____________________________  ³  
 ³   Recogido      _32____________   ¿D-MM-Y.YY  ________   _64______________________   _64____________________________  ³  
 ³   Depositado                      ¿D-MM-Y.YY  ________   _64______________________   _64____________________________  ³  
 ³                                                                                                                       ³ 
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ   
 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ   Propiedades   ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË
 ³ Artículo _40___________ _100______________________________    Lote _40_________________    Cantidad #15L########      ³
 ³                                                                                                                       ³
 ³ Uni/emb #L15#######  Emb. conte. @L@@@ Tipo emba __________   Bloqueos:    Origen __________  Destino __________      ³
 ³                                                                                                                       ³
 ³ Peso #L10#########        Número de serie _60_____________________              Marca _60_____________________        ³
 ³                                                                                                                       ³
 ³ Recepción _20_________________          Bulto (Trazabilidad) __________________     Cajas: @@@@@@  Pico:@@@@@         ³
 ³                                                                                                                       ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

  Host _40______________________________ Extra _255__________________________________________________ Comentario @L@@@@@@@

  Ultima modificación _32________ ¿D-MM-Y.YY  ________ Creación Documento: _32_____________ ¿D-MM-Y.YY  ________
|
TABLA=VDMOVIM
#ORDERBY=CODMOV DESC;
ORDERBY=FECFINMOV DESC,HORAFINMOV DESC,STATUS,CODMOV DESC;
WLONX=1000

NODELETE,PROTECT("V10")

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION","CSELCODMOV","No puedo calcular numero de movimiento")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=CODMOV,NOUPDATE,TOOLTIP("Código del movimiento"),POSTCHANGE=FDESIGNACION("+CSELINS","","+CSELDATOS","")

CAMPO=STATUS,UPDATE("STATUS"),TOOLTIP("Estado del movimiento"),POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe el estado"),
#                CONTEXTUAL=FEJECUTAFORM("VDSTATUS","N","TIPOSTATUS='MOV'","","STATUS=:STATUS","Selección de status","S"),
                COMBOX("CLISTASTATUS")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Designación del estado del movimiento")
CAMPO=CODRECURSO,TOOLTIP("Recurso que ejecuta el movimiento") ,COMBOX("CLISTARECURSO")
CAMPO=PRIOMOV,UPDATE("STATUS"),TOOLTIP("Prioridad del movimiento")
CAMPO=TAREA,TOOLTIP("Tarea del movomiviento"),POSTCHANGE=FDESIGNACION("+CSELTAREA","No existe tarea")
CAMPO=DESTAREA,AUXILIAR,NOENTER,TOOLTIP("Designación de la tarea")
CAMPO=CODCONCE,TOOLTIP("Concepto del movimiento"),POSTCHANGE=FDESIGNACION("CSELCONCE","No existe concepto"),
                CONTEXTUAL=FEJECUTAFORM("VDCONCEPTO","N","","","CODCONCE=:CODCONCE","Selección de concepto","S"),COMBOX("CLISTACONCE")                
CAMPO=DESCONCE,AUXILIAR,NOENTER,TOOLTIP("Designación del concepto")

CAMPO=CODUBIORI,TOOLTIP("Ubicación origen"),POSTCHANGE=FDESIGNACION("CSELUBIORI","No existe ubicación origen"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;",
                                            CONTEXTUAL=FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBIORI","","","Consulta de Ubicación Origen","S")
CAMPO=CODAREAORI,AUXILIAR,NOENTER,TOOLTIP("Area origen"),WHERE=CODUBIORI IN (SELECT CODUBI FROM VDUBICA WHERE CODAREA=:CODAREAORI);
CAMPO=CODUBITEMP,TOOLTIP("Ubicación temporal"),POSTCHANGE=FDESIGNACION("+CSELUBITEMP","No existe ubicación temporal"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;",
                                            CONTEXTUAL=FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBITEMP","","","Consulta de Ubicación Intermedia","S")
CAMPO=CODAREATEMP,AUXILIAR,NOENTER,TOOLTIP("Area temporal"),WHERE=CODUBITEMP IN (SELECT CODUBI FROM VDUBICA WHERE CODAREA=:CODAREATEMP);
CAMPO=CODUBIDEST,TOOLTIP("Ubicación destino"),POSTCHANGE=FDESIGNACION("CSELUBIDEST","No existe ubicación destino"),INCLUDECSS="border-style:ridge;background-color:#F7BE81;",
                                            CONTEXTUAL=FEJECUTAFORM("VDUBICA","S","CODUBI=:CODUBIDEST","","","Consulta de Ubicación Destino","S")
CAMPO=CODAREADEST,AUXILIAR,NOENTER,TOOLTIP("Area destino"),WHERE=CODUBIDEST IN (SELECT CODUBI FROM VDUBICA WHERE CODAREA=:CODAREADEST);
CAMPO=CODMATORI,TOOLTIP("Matrícula origen"),CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMATORI","","","Consulta de Contenedor Origen","S")
CAMPO=CODMATTEMP,TOOLTIP("Matrícula temporal"),CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMATTEMP","","","Consulta de Contenedor Temporal","S")
CAMPO=CODMATDEST,TOOLTIP("Matrícula destino"),CONTEXTUAL=FEJECUTAFORM("VDCONTE","S","CODMAT=:CODMATDEST","","","Consulta de Contenedor Destino","S")
CAMPO=CODBULTOORI,TOOLTIP("Bulto origen"),CONTEXTUAL=FEJECUTAFORM("VDBULTOSPINVMA","S","CODBULTO=:CODBULTOORI","","","Consulta de Contenedor Origen","S")
CAMPO=CODBULTODEST,TOOLTIP("Bulto destino"),CONTEXTUAL=FEJECUTAFORM("VDBULTOSPINVMA","S","CODBULTO=:CODBULTODEST","","","Consulta de Contenedor Destino","S")
CAMPO=CODFLUJO,TOOLTIP("Código del flujo")                
CAMPO=SOLOMUEVE,TOOLTIP("Indica si el movmiento solo mueve la mercancia y no la reserva"),POSTCHANGE=FVERIFICA("SN","Debe introducir S(i) o N(o)")
CAMPO=CODMOVESP,TOOLTIP("Movimiento al que espera el movimiento actual")
CAMPO=TIPOCONTE,TOOLTIP("Tipo de contenedor")          
CAMPO=CODDOCUMENTO,TOOLTIP("Código del documento V10 al que pertenece el documento")
CAMPO=CODDEMANDA,TOOLTIP("Código de la demanda de traslado")
CAMPO=CODMOVPPASO,TOOLTIP("Movimiento que realiza el siguiente paso si se parte por ruta")
CAMPO=CODINTERFASE,TOOLTIP("Código del interfase en el que se ha transmitido al host") 
CAMPO=TIPODEMANDA,TOOLTIP("Tipo  de la demanda de traslado")
CAMPO=CODPREPARACION,TOOLTIP("Código de preparacion del movimiento,\ntodos los movimientos con el mismo Código se han ejecutado a la vez")
CAMPO=LINDEMANDA,TOOLTIP("Línea de la demanda de traslado")
CAMPO=CODOPEINS,NOUPDATE,TOOLTIP("Operario que crea el movimiento")
CAMPO=FECINS,NOUPDATE,TOOLTIP("Fecha de creación del movmiviemto")
CAMPO=HORAINS,NOUPDATE,TOOLTIP("Hora de creación del movimiento")
CAMPO=MODULOINS,NOUPDATE,TOOLTIP("MOdulo que inserta el movimiento")
CAMPO=ACCIONINS,NOUPDATE,TOOLTIP("Accción en la que se inserta el movimiento")
CAMPO=FECPLANMOV,NOUPDATE,TOOLTIP("Fecha de planificación del movimiento")
CAMPO=HORAPLANMOV,NOUPDATE,TOOLTIP("Hora de planificación del movimiento")
CAMPO=MODULOPLANMOV,NOUPDATE,TOOLTIP("MOdulo que planifica el movimiento")
CAMPO=ACCIONPLANMOV,NOUPDATE,TOOLTIP("Acción que planifica el movimiento")
CAMPO=CODOPEEJEMOV,NOUPDATE,TOOLTIP("Operario que ejecuta el movimiento")
CAMPO=FECINIMOV,NOUPDATE,TOOLTIP("Fecha de recogida del movmiento")
CAMPO=HORAINIMOV,NOUPDATE,TOOLTIP("Hora de recogida del movimiento")
CAMPO=MODULOINIMOV,NOUPDATE,TOOLTIP("MOdulo que recoge el movimiento")
CAMPO=ACCIONINIMOV,NOUPDATE,TOOLTIP("Acción que recoge el movimiento")
CAMPO=FECFINMOV,NOUPDATE,TOOLTIP("Fecha de finalizacion del movimiento")
CAMPO=HORAFINMOV,NOUPDATE,TOOLTIP("Hora de finalización del movimiento")
CAMPO=MODULOFINMOV,NOUPDATE,TOOLTIP("MOdulo de finalización del movimiento")
CAMPO=ACCIONFINMOV,NOUPDATE,TOOLTIP("Acción de finalización del movimiento")
CAMPO=CODART,TOOLTIP("Código del artículo"),POSTCHANGE=FDESIGNACION("CSELDESART","No existe artículo"),
                CONTEXTUAL=FEJECUTAFORM("VDSELART","N","","","CODART=:CODART","Selección de articulo","N")
#                COMBOX("CLISTAART"),COMBOXREGPAG=10
CAMPO=DESART,AUXILIAR,NOENTER,TOOLTIP("Designación del artículo")
CAMPO=CODLOT,TOOLTIP("Lote"),POSTCHANGE=FDESIGNACION("CSELCODLOT","No existe el lote"),
                CONTEXTUAL=FEJECUTAFORM("VDLOTES","N","CODART=:CODART","","CODLOT=:CODLOT","Selección de lote","S") 
CAMPO=CANTIDAD,TOOLTIP("Cantidad en unidades host")
CAMPO=UNIEMB,TOOLTIP("Unidades por embalaje en unidades host")
CAMPO=EMBCONT,TOOLTIP("Embalajes por contenedor")
CAMPO=TIPOEMBA,TOOLTIP("Tipo de embalaje"),POSTCHANGE=FDESIGNACION("CSELTIPOEMBA","No existe el tipo de embalaje"),
                CONTEXTUAL=FEJECUTAFORM("VDTIPOEMBA","N","","","TIPOEMBA=:TIPOEMBA","Selección de tipo de embalaje","S") 
CAMPO=BLOQUEOSORI,TOOLTIP("Bloqueo de la mercancia"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEOORI",":V10ERROR")
CAMPO=BLOQUEOSDEST,TOOLTIP("Bloqueo de la mercancia"),POSTCHANGE=FDESIGNACION("-CVERBLOQUEODEST",":V10ERROR")
CAMPO=PESOUNI,TOOLTIP("Peso unitario por unidad host")
CAMPO=PRECIOUNI,OCULTO,"#L#########.###",TOOLTIP("Precio unitario por unidad host")
CAMPO=NUMEROSERIE,TOOLTIP("Numero de serie")
CAMPO=MARCASTK,TOOLTIP("Marca de stock")
CAMPO=CODRECEP,TOOLTIP("Código de la recepción")
CAMPO=BULTO,TOOLTIP("Código de bulto, para productos que exigen trazabilidad de bulto")
CAMPO=CAJAS,AUXILIAR,NOENTER
CAMPO=UNIDSUELTAS,AUXILIAR,NOENTER
CAMPO=DATOSHOST,TOOLTIP("Datos para devolver al host")
CAMPO=VDEXTRA,TOOLTIP("Campo extra disponible para el implantador")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario asociado al producto")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizO la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=CODOPEINSA,AUXILIAR,NOENTER,TOOLTIP("Operario que realizO la última modificación")
CAMPO=FECINSA,AUXILIAR,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAINSA,AUXILIAR,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")

CURSOR=CSELINS SELECT CODOPEINS CODOPEINSA,FECINS FECINSA,HORAINS HORAINSA 
                  FROM VDLOTESHIST WHERE CODDOCUMENTO=:CODDOCUMENTO AND CODDOCUMENTO!=0;

CURSOR=CLISTAART SELECT CODART,CODDIV,DESART FROM VDARTIC;

CURSOR=CLISTACONCE SELECT CODCONCE,SUBSTR(DESCONCE,1,40),DECODE(TIPOCONCE,'I','INT','E','ENT','S','SAL') TIPOCONCE,
                          DECODE(SWTTRAZA,'S','TRAZA','N','NO TRAZA') SWTTRAZA FROM VDCONCEPTO;

CURSOR=CLISTARECURSO SELECT CODRECURSO,DESRECURSO FROM VDRECURSO WHERE ACTIVO='S' ORDER BY CODRECURSO;

CURSOR=CLISTASTATUS SELECT STATUS, DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='MOV' ORDER BY STATUS;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELCODMOV SELECT VDSECMOVIM.NEXTVAL CODMOV FROM DUAL;

CURSOR=CSELTAREA SELECT DESTAREA FROM VDTAREAS WHERE TAREA=:TAREA
                  UNION
                 SELECT '' DESTAREA FROM DUAL WHERE :TAREA IS NULL;

CURSOR=CSELCONCE SELECT DESCONCE FROM VDCONCEPTO WHERE CODCONCE=:CODCONCE;

CURSOR=CSELUBIORI SELECT CODAREA CODAREAORI FROM VDUBICA WHERE CODUBI=:CODUBIORI
                   UNION
                  SELECT '' CODAREAORI FROM DUAL WHERE :CODUBIORI IS NULL;

CURSOR=CSELUBITEMP SELECT CODAREA CODAREATEMP FROM VDUBICA WHERE CODUBI=:CODUBITEMP
                   UNION
                  SELECT '' CODAREAORI FROM DUAL WHERE :CODUBITEMP IS NULL;

CURSOR=CSELUBIDEST SELECT CODAREA CODAREADEST FROM VDUBICA WHERE CODUBI=:CODUBIDEST
                   UNION
                  SELECT '' CODAREAORI FROM DUAL WHERE :CODUBIDEST IS NULL;
                  
CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE TIPOSTATUS='MOV' AND STATUS=:STATUS;

CURSOR=CSELDESART SELECT DESART FROM VDARTIC WHERE CODART=:CODART;

CURSOR=CSELCODLOT SELECT :CODLOT FROM VDLOTES WHERE CODART=:CODART AND CODLOT=:CODLOT
                   UNION
                  SELECT '' CODLOT FROM DUAL WHERE :CODLOT IS NULL;
                  
CURSOR=CSELTIPOEMBA SELECT :TIPOEMBA FROM VDTIPOEMBA WHERE TIPOEMBA=:TIPOEMBA
                   UNION
                  SELECT '' TIPOEMBA FROM DUAL WHERE :TIPOEMBA IS NULL;
				  
CURSOR=CSELDATOS SELECT FLOOR(MOV.CANTIDAD/ART.UNIEMB) CAJAS,MOD(SUM(CANTIDAD),ART.UNIEMB) UNIDSUELTAS FROM VDMOVIM MOV, VDARTIC ART WHERE CODMOV=:CODMOV AND ART.CODART=MOV.CODART
               GROUP BY MOV.CANTIDAD,ART.UNIEMB;				  
				  
CURSOR=CPUEDOANULAR SELECT :CODMOV
                      FROM VDMOVIM MOV
                      WHERE STATUS BETWEEN VDST.FMOVPDTERUTA AND VDST.FMOVENUBIINTER AND CODMOV=:CODMOV AND 
           CODUBIORI IN (SELECT CODUBI FROM VDUBICA WHERE STOCK='S' AND TIPOUBI='R') AND CODUBIDEST IN (SELECT CODUBI FROM VDUBICA WHERE STOCK='S' AND TIPOUBI='R'); 
		   
TECLA=CF1,FEJECUTA(FIMPRIME("INFORME","$(VDMOVIMIENTO)","CODMOV=:CODMOV",""),":V10ERROR",
                  FCOMMIT,"")

BOTON=B1,915,100,70,70,"P",miimprimir.png,CF1,"ImpresiOn del movimiento",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B2,920,200,60,60,"P",micomentarios.png,SF7,"Consulta de comentarios",INCLUDECSS="background-color: transparent;border-width:0px"
BOTON=B3,920,300,60,60,"P",mizoom.png,SF10,"Menú de zoom",INCLUDECSS="background-color: transparent;border-width:0px"

                  
CURSOR=CVERBLOQUEOORI SELECT VDART.VALIDABLOQUEO(:BLOQUEOSORI) V10ERROR FROM DUAL WHERE VDART.VALIDABLOQUEO(:BLOQUEOSORI) IS NOT NULL AND :BLOQUEOSORI IS NOT NULL;
CURSOR=CVERBLOQUEODEST SELECT VDART.VALIDABLOQUEO(:BLOQUEOSDEST) V10ERROR FROM DUAL WHERE VDART.VALIDABLOQUEO(:BLOQUEOSDEST) IS NOT NULL AND :BLOQUEOSDEST IS NOT NULL;




