# Módulo   : VDCORREOSPOOL1.PAN
# Función  : Mantenimiento de COLA de envío de correos
#
# Creación : 04-07-2008
# Autor    : FGS
###########################################
Mantenimiento de COLA de envío de correos
Secuencia Ordenador    Cuenta Remitente Para              CC               CCO              Status Ult. Modif.
######### _32_________ _100_____________ _200_____________ _1000___________ _1000___________ #####  _32_________ ¿D-MM-Y.YYY ________
|
TABLA=VDCORRSMTP
ORDERBY=IDMSG DESC;
#WPLEGADO


PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=IDMSG,NOENTER,TOOLTIP("Secuencial del correo"),TITULO("Secuencia"), WLONX=32
CAMPO=ORDENADOR,TOOLTIP("Ordenador desde el que se inserta el envío del correo"),TITULO("Ordenador")
CAMPO=TIPOCORREO,VIRTUAL,OCULTO,TOOLTIP("Tipo de correo a enviar")
CAMPO=CUENTA,TOOLTIP("Remitente del correo"),TITULO("Cuenta Remitente"), WLONX=50,MIXED
CAMPO=PARA,TOOLTIP("Destinatarios del correo"),TITULO("Para")
CAMPO=CC,TOOLTIP("Direcciones en copia del correo"),TITULO("CC")
CAMPO=CCO,TOOLTIP("Direcciones en copia oculta del correo"),TITULO("CCO")
CAMPO=STATUS,TOOLTIP("Estado del correo en el spool"),TITULO("Estado"), WLONX=20
CAMPO=CODOPEMODIF,NOENTER,TOOLTIP("Operario que realizó la última modificación"),TITULO("Ultima modificación")
CAMPO=FECMODIF,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")


CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

