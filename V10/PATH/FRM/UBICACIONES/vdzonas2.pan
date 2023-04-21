# Módulo   : VDZONAS.PAN
# Función  : Mantenimiento de zonas
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
DETALLE DE ZONAS

Activa _    

Zona @L@ _40______________________________ Tipo _   _________________________  Prioridad @L

 ÏÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ Configuración para Picking ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄË  
 ³                                                                                         ³    
 ³  Ident. del controlador ___ ___ @L@@@@@               Tiempo OK  @L@@@                  ³    
 ³                                                       Tiempo fin @L@@@                  ³    
 ³  Máximo Núm. displays simultáneos         @L@@                                          ³    
 ³  Máximo número de operarios simultáneamente @L        Red de scanners @L@  Scanner @L@  ³    
 ³  Máximo número de bultos por operario       @L                                          ³    
 ³  Capacidad máxima de cajas en la zona       @L                                          ³    
 ³  Autoapertura  _                                                                        ³    
 ³                                                                                         ³    
 ³  Privilegios picking _1024_____________________________________________________________ ³    
 ³  Proceso zona        _32__________________________                                      ³    
 ³  Proceso Disp        _32__________________________                                      ³    
 ³  Rango Volumetrías PickInverso: _1024________________________________________________   ³    
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

 ÏÄÄÄÄÄÄÄÄÄÄ Estado Actual del Picking en la Zona ÄÄÄÄÄÄÄÄÄÄÄÄË
 ³                                                            ³
 ³  Menú         __________                                   ³  Comentario  @L@@@@@@@
 ³  Operario     __________                                   ³  Ult. Modif. _32____________  
 ³  Próximo Tick #L38#####.#####                              ³              ¿D-MM-Y.YY  ________
 ³  Estado       @L@@@ _40____________________________________³
 ³                                                            ³
 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

 Extra _255_____________________________________________________________________________ 
|
TABLA=VDZONAS
ORDERBY=CODZONA;

PREINSERT=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR EN FECHA DE MODIFICACION")



CAMPO=ACTIVA,TOOLTIP("Indica si la zona esta activa o no"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)"),CHECKBOX("N","S")
CAMPO=CODZONA,VIRTUAL,NOUPDATE,TOOLTIP("Código de la zona")
CAMPO=DESZONA,TOOLTIP("Designación de la zona"),POSTCHANGE=FVALNOCERO("Debe introducir designacion de la zona")
CAMPO=TIPOZONA,TOOLTIP("Tipo de picking a realizar en la zona\n U: picking directo de unidades\n I: picking inverso\n E: picking de cajas \n R: no tiene picking"),POSTCHANGE=FENRANGO("U,E,I,R","Debe introducir U(nidades), Picking (I)nverso, E(mbalajes) R(esto)"),
               POSTCHANGE=FDESIGNACION(FVERIFICA("IUCR","DEBE INTRODUCIR (I)nverso,(U)nidades,(C)ajas o (R)esto"),"","+CSELDESTIPO",""),
               COMBOX("I - Inverso","U - Unidades","C - Cajas","R - Resto")
CAMPO=DESTIPOZONA,AUXILIAR,NOENTER
CAMPO=PRIOZONA,TOOLTIP("Prioridad de la zona")
CAMPO=IDINFOGEST,TOOLTIP("Identificador de gestor de displays\n\n SF10: consultar display hardware"),CONTEXTUAL=FEJECUTAFORM("VDINFOHARDDISP","S","IDINFOGEST=:IDINFOGEST AND IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP","","","","S")
CAMPO=IDINFOPICK,TOOLTIP("Identificador de programa de picking hardware\n\n SF10: consultar display hardware"),CONTEXTUAL=FEJECUTAFORM("VDINFOHARDDISP","S","IDINFOGEST=:IDINFOGEST AND IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP","","","","S")
CAMPO=NUMDISP,TOOLTIP("Numero de display del controlador de zona\n\n SF10: consultar display hardware"),CONTEXTUAL=FEJECUTAFORM("VDINFOHARDDISP","S","IDINFOGEST=:IDINFOGEST AND IDINFOPICK=:IDINFOPICK AND NUMDISP=:NUMDISP","","","","S")
CAMPO=TIEMPOOK,TOOLTIP("Tiempo que permanecera el OK en el display en centesimas de segundo")
CAMPO=TIEMPOFIN,TOOLTIP("Tiempo que permancera el FIN encendido en centesimas de segundo")
CAMPO=DISPILUMINADOS,TOOLTIP("Máximo numero de displays iluminados simultaneamente")
CAMPO=MAXOPER,TOOLTIP("Máximo número de operarios por zona")
CAMPO=REDSCAN,TOOLTIP("Identificador de la red de scanners\n\n SF10 Cola de lecturas del Escaner de la Zona"),CONTEXTUAL=FEJECUTAFORM("VDSCANLECT","S","REDSCAN=:REDSCAN AND SCANNER=:SCANNER","","","","S")
CAMPO=SCANNER,TOOLTIP("Numero del scanner asociado a la zona\n\n SF10 Cola de lecturas del Escaner de la Zona"),CONTEXTUAL=FEJECUTAFORM("VDSCANLECT","S","REDSCAN=:REDSCAN AND SCANNER=:SCANNER","","","","S")
CAMPO=MAXBULTOSOPER,TOOLTIP("Máximo número de bultos por operario")
CAMPO=MAXCAPACIDAD,TOOLTIP("Capacidad máxima de cajas en la zona")
CAMPO=AUTOAPERTURA,TOOLTIP("Indica si la zona es obligatorio abrirla"),POSTCHANGE=FENRANGO("S,N","Debe introducir S(i) o N(o)")
CAMPO=PRIVPICKING,TOOLTIP("Privilegios necesarios para hacer picking en la zona (admite rangos)")
CAMPO=PROCESOZONA,TOOLTIP("Proceso que controla la zona")
CAMPO=PROCESODISP,TOOLTIP("Tarea que esta controlando los displays")
CAMPO=RANGOTIPOVOL,TOOLTIP("Rango de Volumetrías de bultos a asignar a displays de esas zonas en picking inverso, Blanco sin restricción"),COMBOXMULTIPLE("CLISTATIPOVOL")
CAMPO=IDMENU,TOOLTIP("Menu cargado en el controlador de zona\n\n SF10: menus de la zona"),CONTEXTUAL=FEJECUTAFORM("VDINFOMENUS","N","","","IDMENU=:IDMENU","","S")
CAMPO=CODCOMEN,TOOLTIP("Código de comentario asociado a la zona")
CAMPO=CODOPE,TOOLTIP("Operario identificado en la zona")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=NEXTTICK,TOOLTIP("Tiempo del proximo tick a la zona")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro")
CAMPO=STATUS,TOOLTIP("Estado de la zona"),POSTCHANGE=FDESIGNACION("CSELSTATUS","No existe estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Designación del estado de la zona")
CAMPO=VDEXTRA,TOOLTIP("Campo extra disponible para el implantador")

CURSOR=CLISTATIPOVOL SELECT DISTINCT TIPOVOL FROM VDVOLUMETRIA ORDER BY TIPOVOL;

CURSOR=CSELDESTIPO SELECT DECODE (:TIPOZONA,'I','PICKING INVERSO',
                                            'U','PICKING DIRECTO DE UNIDADES',
                                            'C','PICKING DE CAJAS',
                                            'SIN PICKING') DESTIPOZONA FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CURSOR=CSELSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='ZON';

CURSOR=CDELBULTOZONA DELETE VDBULTOZONA WHERE CODZONA=:CODZONA AND :TIPOZONA IN ('U','I');

CURSOR=CIERRAZONA UPDATE VDZONAS SET CODOPE=NULL,STATUS=VDST.FZONCERRADA, CODOPEMODIF=VDUSER.GETUSER,FECMODIF=VD.FECHASYS,HORAMODIF=VD.HORASYS WHERE CODZONA=:CODZONA AND :TIPOZONA IN ('U','I');



#{May-F10} Menú contextual;

