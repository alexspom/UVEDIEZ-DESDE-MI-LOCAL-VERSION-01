# Módulo   : VDCORREOSPOOL2.PAN
# Función  : Mantenimiento Detallado de spool de envío de correos
#
# Creación : 04-07-2008
# Autor    : FGS
###########################################
Mantenimiento Detallado de spool de envío de correos
Estado:    #L### _30_______________________    Prioridad: ###

De: ________________________________                        Para: _200______________________________________________________ 
CC: _1000_________________________________________________  CCO:  _1000_____________________________________________________ 

Asunto:    _1000____________________________________________________________________________________________________________
Adjunto:   _  _50_______________________ _256____________________________________________ _256______________________________
Texto:     
_4000_______________________________________________________________________________________________________________________

Inserción:     _32_________ ¿D-MM-Y.YYY ________ Ord: _32___________  Módulo/Acción: _64_______________ _64_________________   
Planificado:   ¿D-MM-Y.YYY ________        Inf. Extra: _255_________________________________________________________________
Enviado:       ¿D-MM-Y.YYY ________   Cod. Comentario: @L@@@@@@@      Ult. Modif.: _32_________ ¿D-MM-Y.YYY ________
|

TABLA=VDCORRSMTP
#WPLEGADO

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")

CAMPO=IDMSG,VIRTUAL,OCULTO,TOOLTIP("Secuencial del correo")
CAMPO=STATUS,TOOLTIP("Estado del correo en el spool"),POSTCHANGE=FDESIGNACION("+CDESSTATUS","ERROR OBTENIENDO DESCRICION DEL ESTADO")
CAMPO=DESSTATUS,AUXILIAR,NOENTER
CAMPO=PRIORIDAD,TOOLTIP("Prioridad del correo")
CAMPO=CUENTA,TOOLTIP("Cuenta Remitente del correo")
CAMPO=PARA,TOOLTIP("Destinatarios del correo")
CAMPO=CC,TOOLTIP("Direcciones en copia del correo")
CAMPO=CCO,TOOLTIP("Direcciones en copia oculta del correo")
CAMPO=ASUNTO,MIXED,TOOLTIP("Asunto del correo")
CAMPO=ADJUNTO,TOOLTIP("Ficheros adjunto que se incluyen en el correo")
CAMPO=MIME,TOOLTIP("Tipo de MIME usado")
CAMPO=DIRECTORIO,MIXED,TOOLTIP("Directorio en donde se encuentra el fichero. NOTA: Es un DIRECTORIO ORACLE.")
CAMPO=FICHERO,MIXED,TOOLTIP("Nombre del Fichero a adjuntar")
CAMPO=CUERPO,MIXED,TOOLTIP("Texto que se envía en el correo")
CAMPO=CODOPEINS,NOENTER,TOOLTIP("Operario que realizó la insercción")
CAMPO=FECINS,NOENTER,TOOLTIP("Fecha en la que se realizó la insercción")
CAMPO=HORAINS,NOENTER,TOOLTIP("Hora en la que se realizó la insercción")
CAMPO=ORDENADOR,NOENTER,TOOLTIP("Ordenador desde el que se inserta el envío del correo")
CAMPO=MODULOINS,NOENTER,TOOLTIP("Módulo desde el que se inserta el correo")
CAMPO=ACCIONINS,NOENTER,TOOLTIP("Acción desde la que se inserta el correo")
CAMPO=FECPLANIF,TOOLTIP("Fecha prevista de envío del correo, si NULL cuando se pueda")
CAMPO=HORAPLANIF,TOOLTIP("Hora prevista de envío del correo, NULL idem.")
CAMPO=VDEXTRA,TOOLTIP("Datos adicionales externos a V10 y útiles para el cliente")
CAMPO=FECENVIO,NOENTER,TOOLTIP("Fecha en la que se ha enviado el correo")
CAMPO=HORAENVIO,NOENTER,TOOLTIP("Hora en la que se ha enviado el correo")
CAMPO=CODCOMEN,NOENTER,TOOLTIP("Comentario asociado al correo")
CAMPO=CODOPEMODIF,NOENTER,NOENTER,TOOLTIP("Operario que realizó la última modificación")
CAMPO=FECMODIF,NOENTER,NOENTER,TOOLTIP("Fecha de la Ultima modificación")
CAMPO=HORAMODIF,NOENTER,TOOLTIP("Hora de la Ultima modificación")

CURSOR=CDESSTATUS SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='CSP';

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;
