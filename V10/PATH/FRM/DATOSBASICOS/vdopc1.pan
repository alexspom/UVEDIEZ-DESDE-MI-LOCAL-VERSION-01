-- USUARIOS --
Codigo Usuario   Nombre     Apellido1   Apellido2   Caducidad
______________  _30_______  _30_______  _30_______  �D-MM-Y.YY 
|

TABLA=VDUSUARIO 
#REGPAG=17

PREINSERT=FEJECUTA("CSELMODIF","ERROR INSERTANDO ULTIMA MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR ACTUALIZANDO ULTIMA MODIFICACION")

CAMPO=CODOPE,NOENTER,TOOLTIP("Codigo Usuario"),TITULO("Codigo Usuario")
CAMPO=NOMBRE,NOENTER,TOOLTIP("Nombre"),TITULO("Nombre")
CAMPO=APELLIDO1,NOENTER,TOOLTIP("Apellido1"),TITULO("Apellido1")
CAMPO=APELLIDO2,NOENTER,TOOLTIP("Apellido2"),TITULO("Apellido2")
CAMPO=FECCADUC,NOENTER,TITULO("Caducidad")



CAMPO=INICIALES,OCULTO,"_"
CAMPO=TEMA,OCULTO,"_"
CAMPO=TEMA,OCULTO,"_"
CAMPO=NIVEL,OCULTO,"_"
CAMPO=BLOQUEOPE,OCULTO,"_"
CAMPO=MENUASOCIADO,OCULTO,"_"
CAMPO=TPCVERIF,OCULTO,"_"
CAMPO=CONTERRSUC,OCULTO,"_"
CAMPO=CONTERRTOT,OCULTO,"_"
CAMPO=CONTLOG,OCULTO,"_"
CAMPO=FECPASSWORD,OCULTO,"_"
CAMPO=HORAPASSWORD,OCULTO,"_"
CAMPO=HPASSWORD,OCULTO,"_"
CAMPO=CPUB,OCULTO,"_"
CAMPO=CPRIV,OCULTO,"_"
CAMPO=CODOPEMODIF,OCULTO,"_"
CAMPO=FECMODIF,OCULTO,"_"
CAMPO=HORAMODIF,OCULTO,"_"


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, 
						VD.FECHASYS FECMODIF,
						VD.HORASYS HORAMODIF 
				   FROM DUAL;


ONLINE= {F2} Consulta   {Esc} Cerrar Pantalla    {F5} Borrar Pantalla    ;
