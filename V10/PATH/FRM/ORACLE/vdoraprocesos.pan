PROCESOS DE LA BASE DE DATOS

Dir  PID S.O       Username          Nº  Equipo         Programa
____ @@@ _9_______ _15_____________ @L@@ _16___________ _64_____________________________________ 
|
	               																			   
TABLA=V$PROCESS

CAMPO=ADDR,NOENTER,TOOLTIP("Dirección del proceso"),TITULO("Dir"), WLONX=18
CAMPO=PID,NOENTER,TOOLTIP("Identificador del proceso"),TITULO("PID"), WLONX=19
CAMPO=SPID,NOENTER,TOOLTIP("Identificador del proceso del Sistema Operativo"),TITULO("S.O.")
CAMPO=USERNAME,NOENTER,TOOLTIP("Nombre de usuario del Sistema Operativo"),TITULO("Username")
CAMPO=SERIAL#,NOENTER,TOOLTIP("Número de serie del proceso"),TITULO("Nº")
CAMPO=TERMINAL,NOENTER,TOOLTIP("Identificador del terminal del Sistema Operativo"),TITULO("Terminal")
CAMPO=PROGRAM,NOENTER,TOOLTIP("Programa en proceso"),TITULO("Programa")

