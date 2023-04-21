# Módulo   : VDCORRCUEN.PAN
# Función  : Cuentas de correo del sistema
#
# Creación : 08-07-2008
# Autor    : FGS
###########################################
Cuentas de Correo del sistema                                    
                                                                   ÏÄÄÄÄÄÄÄÄ SMT ÄÄÄÄÄÄÄÄÄÄÄË   ÏÄÄÄÄÄÄÄÄ POP3 ÄÄÄÄÄÄÄÄÄË    
Cuenta                       Dominio       Usuario      Pwd        Servidor       Puerto Au C E Servidor      Puerto      Au C E Ult. Modif. 
_32__________ _60___________ _256_________ _32_________ _16______  _256__________ #####  _1 _ _ _256_________ ##########  _  _ _ _32_________ ¿D-MM-Y.YYY ________       
|
TABLA=VDCORRCUEN
WLONX=1500

PREINSERT=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
PREUPDATE=FEJECUTA("CSELMODIF","ERROR AL OBTENER LA FECHA DE MODIFICACION")
POSTQUERY=FEJECUTA("+CPASSWORD","")

CAMPO=CUENTA,TOOLTIP("Direccion de Correo"),TITULO("Cuenta")
CAMPO=DESCUENTA,TOOLTIP("Descripcion de la Direccion/Cuenta de Correo"),TITULO("")
CAMPO=DOMINIO,MIXED,TOOLTIP("Dominio Global de los Servidores"),TITULO("Dominio")
CAMPO=USUARIO,MIXED,TOOLTIP("Usuario de la direccion de Correo"),TITULO("Uauario")
CAMPO=CLAVE,MIXED,TOOLTIP("Contraseña/Clave del Usuario"),TITULO("Password")
CAMPO=SMTP,MIXED,TOOLTIP("Direccion del protocolo SMTP"),TITULO("Smtp")
CAMPO=SMTP_PUERTO,TOOLTIP("Puerto del Servidor SMTP"),TITULO("Puerto")
CAMPO=SMTP_AUTEN,TOOLTIP("Si el Servidor SMTP requiere Autentificacion "),TITULO("Au")
CAMPO=SMTP_CIFRADA,TOOLTIP("Si la Autentificacion es Cifrada"),TITULO("C")
CAMPO=SMTP_ENTRECOMILLADO,TITULO("E")
CAMPO=POP3,MIXED,TOOLTIP("Direccion del protocolo POP3"),TITULO("Serv.POP3")
CAMPO=POP_PUERTO,TOOLTIP("Puerto del Servidor POP3"),TITULO("Puerto POP3")
CAMPO=POP_AUTEN,TOOLTIP("Si el Servidor POP requiere Autentificacion"),TITULO("Au")
CAMPO=POP_CIFRADA,TOOLTIP("Si la Autentifacion es Cifrada"),TITULO("C")
CAMPO=POP_ENTRECOMILLADO,TITULO("E")
CAMPO=CODOPEMODIF,TOOLTIP(""),TITULO("Ult. Modificacion")
CAMPO=FECMODIF,TOOLTIP("")
CAMPO=HORAMODIF,TOOLTIP("")

CURSOR=CPASSWORD SELECT DECODE(VDUSER.TENGOPRIVILEGIO('IMPLANTADOR'),1,0,1) CLAVE__INVISIBLE FROM DUAL;
CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF FROM DUAL;

