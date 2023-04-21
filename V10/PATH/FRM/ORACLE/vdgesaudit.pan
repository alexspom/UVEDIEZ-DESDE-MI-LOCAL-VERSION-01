# Módulo   : VDGESAUDIT.PAN
# Función  : GESTION DE AUDITS V10 ORACLE
#
# Creación : 03-02-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
GESTION DE AUDITS V10 ORACLE
TABLENAME              
_30___________________ _18_______ _18_________
|

WLONX=350
SOLOQUERY
SELECT =  SELECT TABLE_NAME TABLENAME,'NO EXISTE' EXISTETABLA, 'NO EXISTE' TRIGERAUDIT
              FROM USER_TABLES WHERE TABLE_NAME NOT LIKE '%$%' AND TABLE_NAME NOT LIKE 'TOAD_PLAN%' AND TABLESPACE_NAME IS NOT NULL AND
             (TABLE_NAME LIKE :TABLENAME OR :TABLENAME IS NULL);

POSTQUERY=FEJECUTA("CSELDESC","","+CSELTABLA","","+CTRIGERAUDIT","")

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=TABLENAME,NOUPDATE,TITULO("Tabla"),AUXILIAR
CAMPO=MIDESC,AUXILIAR,NOENTER,OCULTO,"_150_"
CAMPO=EXISTETABLA,NOENTER,TOOLTIP("Si existe la tabla de audit"),TITULO("Tabla $AUD")
CAMPO=TRIGERAUDIT,NOENTER,TOOLTIP("Si esta habilitado el triger de audit"),WLONX=8,TITULO("Triger $AUD")

BOTON=B1,585,242,25,25,"B1",crear.png,SF1,"Crear Tabla de audit y trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B2,620,242,25,25,"B2",borrar.png,SF2,"Borrar tabla y trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B3,585,297,25,25,"B3",activar.png,SF3,"Activar Trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B4,620,297,25,25,"B4",desactivar.png,SF4,"Desactivar Trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     

BOTON=B5,730,240,170,40,"Crear todas las tablas",NO,SF5,"Crear todas las tablas"
BOTON=B6,730,290,170,40,"Borrar todas las tablas",NO,SF6,"Borrar todas las tablas"
BOTON=B7,730,340,170,40,"Activar todos los trigger",NO,SF7,"Activar todos los triggers"
BOTON=B8,730,390,170,40,"Desactivar todos los triggers",NO,SF8,"Desactivar todos los triggers"
BOTON=B8,480,330,120,120,"",RADAR.PNG,SF10,INCLUDECSS="background-color: transparent; border-width:0px"

CURSOR=CDEFECTO SELECT 'NO EXISTE' EXISTETABLA,17  EXISTETABLA__COLOR, 'NO EXISTE' TRIGERAUDIT,17 TRIGERAUDIT__COLOR FROM DUAL;

CURSOR=CSELTABLA SELECT 'EXISTE' EXISTETABLA,19 EXISTETABLA__COLOR FROM ALL_TABLES WHERE TABLE_NAME = :TABLENAME || '$AUD' AND OWNER= USER || '$AUD';

CURSOR=CTRIGERAUDIT SELECT DECODE(STATUS,'ENABLED','ACTIVADO', 'DESACTIVADO') TRIGERAUDIT,
                           DECODE(STATUS,'ENABLED',19, 18) TRIGERAUDIT__COLOR  FROM USER_TRIGGERS WHERE TRIGGER_NAME = :TABLENAME || '$AUD';  


                                    
CURSOR=CSELDESC SELECT SUBSTR(COM.COMMENTS,1,150) MIDESC FROM USER_TAB_COMMENTS COM  WHERE COM.TABLE_NAME(+)=:TABLENAME;

CURSOR=CDUMMY SELECT :TABLENAME FROM DUAL WHERE 1=2;

# PARTE PERSONALIZADA DE LA PANTALLA 


									
CURSOR=CCREAUNATABLA BEGIN
                    V10CREAHIST.CREAUNATABLA(:TABLENAME,1,1,1);
									END;@
																		
CURSOR=CBORRAUNATABLA BEGIN
                    V10CREAHIST.BORRAUNATABLA(:TABLENAME);
									END;@			
									
CURSOR=CACTIVAUNTRIGER BEGIN
                    V10CREAHIST.ACTIVAUNTRIGER(:TABLENAME,1);
									END;@		
									
CURSOR=CDESACTIVAUNTRIGER BEGIN
                    V10CREAHIST.ACTIVAUNTRIGER(:TABLENAME,0);
									END;@						
									
CURSOR=CCREATABLAS BEGIN
                    V10CREAHIST.CREATABLAS;
									END;@

CURSOR=CBORRATABLAS BEGIN
                    V10CREAHIST.BORRATABLAS;
									END;@							

									
CURSOR=CACTIVATRIGERS BEGIN
                    V10CREAHIST.ACTIVATRIGERS;
									END;@																				
									
CURSOR=CDESACTIVATRIGERS BEGIN
                    V10CREAHIST.DESACTIVATRIGERS;
									END;@																				


TECLA=SF1,FEJECUTA("CCREAUNATABLA","",                   
                   "CDEFECTO","ERROR1",
                   "+CSELTABLA","ERROR2",
                   "+CTRIGERAUDIT","ERROR3",              
                   %FFAILURE,"TABLA DE AUDIT CREADA")
                   
TECLA=SF2,FEJECUTA("CBORRAUNATABLA","",                   
                   "CDEFECTO","ERROR1",
                   "+CSELTABLA","ERROR2",
                   "+CTRIGERAUDIT","ERROR3", 
                   %FFAILURE,"TABLA DE AUDIT BORRADA")         
                   
TECLA=SF3,FEJECUTA("CACTIVAUNTRIGER","",                   
                   "CDEFECTO","ERROR1",
                   "+CSELTABLA","ERROR2",
                   "+CTRIGERAUDIT","ERROR3",    
                   %FFAILURE,"TRIGER DE AUDIT ACTIVADO")
                   
TECLA=SF4,FEJECUTA("CDESACTIVAUNTRIGER","",                   
                   "CDEFECTO","ERROR1",
                   "+CSELTABLA","ERROR2",
                   "+CTRIGERAUDIT","ERROR3",
                   %FFAILURE,"TRIGER DE AUDIT DESACTIVADO")       
                   

TECLA=SF5,FEJECUTA(FEJECUTA("!CDUMMY","¿ ESTA SEGURO DE CREAR TODAS LAS TABLAS ?. </BR> ESTO PUEDE TARDAR UNOS MINUTOS"),"OPERACION CANCELADA",
                   "CCREATABLAS","",        
                   %FFAILURE,"TABLAS CREADAS",
                   FPULSATECLAS("CF2","F2"))   
                   
TECLA=SF6,FEJECUTA(FEJECUTA("!CDUMMY","¿ ESTA SEGURO DE BORRAR TODAS LAS TABLAS ?. </BR> ESTO PUEDE TARDAR UNOS MINUTOS"),"OPERACION CANCELADA",
                   "CBORRATABLAS","",        
                   %FFAILURE,"TABLAS BORRADAS",
                   FPULSATECLAS("CF2","F2")) 
                   
TECLA=SF7,FEJECUTA(FEJECUTA("!CDUMMY","¿ ESTA SEGURO DE ACTIVAR TODOS LOS TRIGERS ?. </BR> ESTO PUEDE TARDAR UNOS MINUTOS"),"OPERACION CANCELADA",
                   "CACTIVATRIGERS","",        
                   %FFAILURE,"TRIGERS ACTIVADOS",
                   FPULSATECLAS("CF2","F2"))   
                   
TECLA=SF8,FEJECUTA(FEJECUTA("!CDUMMY","¿ ESTA SEGURO DE DESACTIVAR TODOS LOS TRIGERS ?. </BR> ESTO PUEDE TARDAR UNOS MINUTOS"),"OPERACION CANCELADA",
                   "CDESACTIVATRIGERS","",        
                   %FFAILURE,"TRIGERS DESACTIVADOS",
                   FPULSATECLAS("CF2","F2"))                                                                                                          