#*****************************************************************
#Módulo: VDTIPOFORMAPAGO.PAN
#Funcionalidad : Mantenimiento de la tabla de tipos de forma de pago
#Autor: JMM
#Fecha: 06-10-2008
#*****************************************************************
#* Histórico de cambios
#* ====================
#
MANTENIMIENTO DE TIPOS DE FORMA DE PAGO

 Tipo  Descripción                                  DP   D1   D2   D3   Ultima Modificacion
 ____  _40_____________________________________     ###  ###  ###  ###  _32____________ ¿D-MM-Y.YYY  ________ 
|
TABLA=VDTIPOFORMAPAGO

PQUERY
POSX=1
POSY=5
REGPAG=30
PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TIPOFORMAPAGO,TOOLTIP("Tipo de Forma de pago. Determina la forma en la que el cliente realizará el pago de sus pedidos.")
CAMPO=DESCTIPOFORMAPAGO,TOOLTIP("Descripción de la forma en el que el cliente realiza el pago de sus pedidos")
CAMPO=DIASPAGO,TOOLTIP("Dias que transcurren hasta efectuar el pago.")
CAMPO=DIAUNO,TOOLTIP("Dias que transcurren hasta efectuar el primer pago. En caso de dividir el pago")
CAMPO=DIADOS,TOOLTIP("Dias que transcurren hasta efectuar el segundo pago. En caso de dividir el pago")
CAMPO=DIATRES,TOOLTIP("Dias que transcurren hasta efectuar el tercer pago. En caso de dividir el pago")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación.")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación.")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

ONLINE= {F1} Ayuda   {F2} Consulta   {Ctrl-F2} Cond. Busqueda   {F4} Confirmar cambios
      {F5} Borrar Pantalla      {F9} Borrar Registro   {Esc} Cerrar Pantalla       ;
