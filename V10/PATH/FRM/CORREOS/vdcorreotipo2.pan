# Módulo   : VDCORREOTIPO2.PAN
# Función  : Mantenimiento de Tipos de Correos que se envía el sistema
#
# Creación : 04-07-2008
# Autor    : FGS
###########################################
# Histórico de cambios:
Mantenimiento de Tipos de Correos
Tipo:   ____________  Activo: _
Desc:   ________________________________________ 

Cuenta:  _100_________________________________ 
Para _200___________________________________________________
CC:  _1000__________________________________________________ 
CCO: _1000__________________________________________________

Ult. Modif. __32_____ ¿D-MM-Y.YY ________ 

|
TABLA=VDCORRTIPOS


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=TIPOCORREO,VIRTUAL,TOOLTIP("Tipo de Correo")
CAMPO=ACTIVO,TOOLTIP("Si el tipo de correo está activo para ser utilizado por el sistema")
CAMPO=DESTIPOCORREO,TOOLTIP("Descripción del tipo de Correo")
CAMPO=CUENTA,TOOLTIP("Cuenta Remitente del Correo"),MIXED
CAMPO=PARA,TOOLTIP("Destinatario del Correo")
CAMPO=CC,TOOLTIP("Direcciones en copia del correo")
CAMPO=CCO,TOOLTIP("Direcciones en copia oculta del correo")
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;


