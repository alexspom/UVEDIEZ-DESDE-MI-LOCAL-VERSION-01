#*****************************************************************
#Módulo: VDCLIENTESDIVIS.PAN
#Funcionalidad : 
#Autor: JMM      
#Fecha: 06-10-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
ASGINACION DE CLIENTES A DIVISIONES
Cliente      Sec.                             Cod. Lab.    Division                       Ultima Modif.
_12_________ ###  _60________________________ _20_________ _20_ _40______________________ _32_________  ¿D-MM-Y.YYY _8______ 
|
TABLA=VDCLIENTESDIVIS

PQUERY
POSX=1
POSY=1
REGPAG=20
PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=CODCLIENTE,POSTCHANGE=FDESIGNACION("+CSELVDCLIENTESDESCLI","ERROR AL EJECUTAR CURSOR CSELVDCLIENTESDESCLI"),TOOLTIP("Código del Cliente"),TITULO("Cod.Cliente")
CAMPO=SEQCODCLI,TOOLTIP("Secuencial del Cliente"),TITULO("Secuencia")
CAMPO=DESCLIENTE,AUXILIAR,NOENTER,TOOLTIP("Designación completa del cliente que realiza el pedido. También recibido en el interfase"),TITULO("Des.Cliente")
CAMPO=CODCLIDIV,TOOLTIP("Código del Cliente para la division"),TITULO("Cod.cliente Div.")
CAMPO=CODDIV,POSTCHANGE=FDESIGNACION("+CSELVDDIVISDESDIV","ERROR AL EJECUTAR CURSOR CSELVDDIVISDESDIV"),TOOLTIP("Código de la Division a la que pertenece el cliente"),TITULO("División Cliente")
CAMPO=DESDIV,AUXILIAR,NOENTER,TOOLTIP("Nombre completo de la división"),TITULO("Des. División")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Modificado por ...")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Modificacion")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Modificacion")

CURSOR=CSELVDDIVISDESDIV SELECT DESDIV FROM VDDIVIS WHERE CODDIV=:CODDIV;

CURSOR=CSELVDCLIENTESDESCLI SELECT DESCLIENTE FROM VDCLIENTES WHERE CODCLIENTE=:CODCLIENTE AND SEQCODCLI = :SEQCODCLI;

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

CONTEXTUAL=FLEEMENU("VDCLIENTESDIVIS.ZOO")

ONLINE= {F1} Ayuda   {F2} Consulta   {F4} Confirmar cambios   {Esc} Cerrar Pantalla   {F9} Borrar un registro   {F5} Borrar Pantalla    ;
