# Módulo   : VDGESAUDIT.PAN
# Función  : GESTION DE AUDITS V10 ORACLE
#
# Creación : 03-02-2010
# Autor    : FGS
# Fichero generado por el Asistente de Generación de Pantallas V10 
###########################################
# Histórico de cambios:
GESTION DE AUDITS V10 ORACLE
 
 _30_________________
 ________________________________________________________________________________  
 
  
  
  
 Tabla Audit   _________________ 
 
 
 
 Trigger Audit _________________



|
POSX=50
POSY=10
WLONY=320
REGPAG=1
TABLA = DUAL
NOINSERT
NOUPDATE
NODELETE
NOORAINS

# LISTA DE CAMPOS DE LA PANTALLA
CAMPO=TABLENAME,VIRTUAL,AUXILIAR,NOENTER,INCLUDECSS="HEIGHT:20px;font-size:14px; font-style:bolder;  background-color: transparent"
CAMPO=MIDESC,VIRTUAL,AUXILIAR,NOENTER,REGPAG=3,INCLUDECSS="font-style:italic; background-color: transparent",WPOSY=8
CAMPO=EXISTETABLA,NOENTER,AUXILIAR,VIRTUAL,INCLUDECSS="HEIGHT:26px;font-size:18px;",WPOSY=-4
CAMPO=TRIGERAUDIT,NOENTER,AUXILIAR,VIRTUAL,INCLUDECSS="HEIGHT:26px;font-size:18px;",WPOSY=-4

# PARTE PERSONALIZADA DE LA PANTALLA 
BOTON=B1,585,242,25,25,"B1",crear.png,SF1,"Crear Tabla de audit y trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B2,620,242,25,25,"B2",borrar.png,SF2,"Borrar tabla y trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B3,585,297,25,25,"B3",activar.png,SF3,"Activar Trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B4,620,297,25,25,"B4",desactivar.png,SF4,"Desactivar Trigger",INCLUDECSS="background-color:transparent; border-style:outset; border-width:1px"     
BOTON=B5,730,240,170,40,"Crear todas las tablas",NO,SF5,"Crear todas las tablas"
BOTON=B6,730,290,170,40,"Borrar todas las tablas",NO,SF6,"Borrar todas las tablas"
BOTON=B7,730,340,170,40,"Activar todos los trigger",NO,SF7,"Activar todos los triggers"
BOTON=B8,730,390,170,40,"Desactivar todos los triggers",NO,SF8,"Desactivar todos los triggers"
BOTON=B8,480,330,120,120,"",RADAR.PNG,SF10,INCLUDECSS="background-color: transparent; border-width:0px"

TECLA=SF1,FPULSATECLAS("CF6","SF1")
TECLA=SF2,FPULSATECLAS("CF6","SF2")
TECLA=SF3,FPULSATECLAS("CF6","SF3")
TECLA=SF4,FPULSATECLAS("CF6","SF4")
TECLA=SF5,FPULSATECLAS("CF6","SF5")
TECLA=SF6,FPULSATECLAS("CF6","SF6")
TECLA=SF7,FPULSATECLAS("CF6","SF7")
TECLA=SF8,FPULSATECLAS("CF6","SF8")				
									
																								

