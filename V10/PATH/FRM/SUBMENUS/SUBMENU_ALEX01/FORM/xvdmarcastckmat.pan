# Módulo   : xvdmarcastckmat.PAN
# Función  : Ventana de mantenimiento de Tabla xvdmarcastc
#
# Creación : 10-04-2023
# Autor    : AGonzalez
###########################################
# Histórico de cambios:
#
MANTENIMIENTO DE LA TABLA XVDMARCASTCK
 CODDIV 	  MARCASTCK       DESCRIPCION        Fecha Creación  Hora Creacion Usuario	      Fecha Modificacion  Hora Modificacion
 _20__________ _60_________   _60______________  ¿D-MM-Y.YY      _8_________   _32___________ ¿D-MM-Y.YY          _8_________
 |
 

PQUERY 
TABLA=XVDMARCASTCK
 
WLONX=1055
 
PREINSERT=FEJECUTA("CEXISTEDIV","DEBE EXISTIR LA DIVISION","CSELINSERTA","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CEXISTEDIV","DEBE EXISTIR LA DIVISION","CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")
 
CAMPO=CODDIV,TOOLTIP("Código de la division"),TITULO("Div"), WLONX=100
CAMPO=MARCASTCK,TOOLTIP("Código Marca"),TITULO("Marca"), WLONX=100
CAMPO=DESCRIPCION,TOOLTIP("Descripcion la Marca"),TITULO("Descripcion"), WLONX=200
CAMPO=FECINSER,NOENTER,TOOLTIP("Fecha en que se crearon los datos del registro"),TITULO("Fecha Creacion"), WLONX=100
CAMPO=HORINSER,NOENTER,TOOLTIP("Hora en que se crearon a los datos del registro"),TITULO("Hora Creacion"), WLONX=100
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realiza la Última modificación"),TITULO("Operario"), WLONX=100
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha en que se modificaron los datos del registro"),TITULO("Fecha Modificacion"), WLONX=105
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora en que se modificaron a los datos del registro"),TITULO("Hora Modificacion"), WLONX=105

CURSOR=CSELINSERTA SELECT VDUSER.GETUSER CODOPEMODIF, 
						VD.FECHASYS FECINSER,
						VD.HORASYS HORINSER,
						VD.FECHASYS FECMODIF,
						VD.HORASYS HORAMODIF							
				   FROM DUAL;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, 
						VD.FECHASYS FECMODIF,
						VD.HORASYS HORAMODIF					
				   FROM DUAL;
				   
CURSOR=CEXISTEDIV SELECT CODDIV					
				   FROM VDDIVIS
				   WHERE CODDIV = :CODDIV;

ONLINE= {F2} Consulta   {Esc} Cerrar Pantalla    {F4} Guardar {F5} Borrar Pantalla    ;


