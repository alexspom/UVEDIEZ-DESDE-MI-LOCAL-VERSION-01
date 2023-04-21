#*****************************************************************
#Módulo: VDTIPOCLIENTE.PAN
#Funcionalidad : mantenimiento de la tabnla de tipos de clientes
#Autor: JMM      
#Fecha: 10-12-2007
#*****************************************************************
#* Histórico de cambios
#* ====================
#
#*****************************************************************
#
#
#*****************************************************************
MANTENIMIENTO DE TIPOS DE CLIENTE
 Tipo      Designación                     Ultima modificacion
 _5___     _40___________________________  _32_______________ ¿D-MM-YY.Y ________ 

|

POSX=17
POSY=10
REGPAG=20

TABLA=VDTIPOCLIENTE
ORDERBY=TIPOCLI ASC;
PQUERY



PREINSERT=FEJECUTA("CSELMODIF","No puedo asignar fecha de modificación.")
PREUPDATE=FEJECUTA("CSELMODIF","No puedo asignar fecha de modificación.")

CAMPO=TIPOCLI,UPPER,TOOLTIP("Tipo de cliente")
CAMPO=DESCTIPOCLI,TOOLTIP("Descripción del tipo de cliente")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que hizo la ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,UPPER,NOENTER,TOOLTIP("Hora de la Ultima modificación")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF, VD.FECHASYS FECMODIF, VD.HORASYS HORAMODIF FROM DUAL;

AYUDA=MANTENIMIENTO DE TIPOS DE CLIENTE
ONLINE=     {F1} Ayuda {F2} Consulta {F4} Confirmar cambios {F9} Borrar registro {Ctrl-F7} Copia {Esc} Salir;
