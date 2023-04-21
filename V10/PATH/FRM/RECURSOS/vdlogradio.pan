# Módulo   : VDLOGRADIO.PAN
# Función  : Mantenimiento de login de radio
#
# Creación : 01-10-2007
# Autor    : EAA
###########################################
# Histórico de cambios:
MANTENIMIENTO DE LOGINS EN TERMINALES
Usuario    Recurso    Login               Logout              Terminal         Sid       Serial
__________ __________ ¿D-MM-Y.YY ________ ¿D-MM-Y.YY ________ ________________ @L@@@@@@@ @L@@@@@@@
|
TABLA=VDLOGRADIO


CAMPO=CODOPE,TOOLTIP("Usuario que realiza el login")
CAMPO=CODRECURSO,TOOLTIP("Recurso en el que se realiza el login")
CAMPO=FECLOGIN,TOOLTIP("Fecha en la que se realiza el login")
CAMPO=HORALOGIN,TOOLTIP("Hora en la que se realiza el login")
CAMPO=FECLOGOUT,TOOLTIP("Fecha del logout")
CAMPO=HORALOGOUT,TOOLTIP("Hora del logout")
CAMPO=TERMINAL,TOOLTIP("Maquina en la que se ejecuta el programa de radios")
CAMPO=SID,TOOLTIP("SID Oracle del programa de radios")
CAMPO=SERIALNUM,TOOLTIP("SERIAL# de Oracle del programa de radios")