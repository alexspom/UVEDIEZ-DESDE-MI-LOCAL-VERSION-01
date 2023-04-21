MONITORIZACION DE SESIONES QUE BLOQUEAN

Máquina     Programa                                Módulo            Modo       Usuario   Host      B SID     Serial Tipo Segundos 
_30________ _64____________________________________ _48______________ _15_______ _32______ _32______ @ @L@@@@@ @L@@@@  __  @L@@@@@@ 
|

#TM DML enqueue lock.
#TX Transaction enqueue lock.
#UL User supplied lock.
#All other locks are system locks, which are held for extremely short periods of time.

#LMODE tipos
########################################################
#Lock mode in which the session holds the lock:
#0, None
#1, Null (NULL)
#2, Row-S (SS)
#3, Row-X (SX)
#4, Share (S)
#5, S/Row-X (SSX)
#6, Exclusive (X) 
#########################################################

SOLOQUERY
SELECT=SELECT MACHINE, DECODE (SIGN (LENGTH (program) - 40),
                      1, SUBSTR (program, 40),
                      program
                     ) program,
       DECODE (lmode,
               0, 'None',
               1, 'Null',
               2, 'Row Shared',
               3, 'Row Exclusive',
               4, 'Shared',
               5, 'Share row exclusive',
               6, 'Exclusive'
              ) modo,
       A.SID,
       serial# serial, 
       ctime tiempo, 
       A.TYPE, 
       A.id1,
       A.id2,
       B.MODULE,
       SQL_TEXT SQLBLOQUEA,
       B.CLIENT_INFO USUARIO,BLOCK
    FROM SYS.GV_$LOCK A,SYS.GV_$SESSION B,SYS.GV_$SQLAREA C
  WHERE A.SID=B.SID AND 
        B.PREV_SQL_ADDR=C.ADDRESS(+) AND
        A.TYPE IN ('TM', 'TX', 'UL');
ORDERBY=BLOCK DESC;        

POSTQUERY=FEJECUTA("CMATASESION","")

CAMPO=MACHINE,TITULO("Máquina")
CAMPO=PROGRAM,TITULO("Programa")
CAMPO=MODULE,TITULO("Módulo")
CAMPO=MODO,TITULO("Modo")
CAMPO=USUARIO,TITULO("Usuario")
CAMPO=HOST,TITULO("Ordenador")
CAMPO=BLOCK,TITULO("Bl")
CAMPO=SID,TITULO("SID")
CAMPO=SERIAL,AUXILIAR,TITULO("Serial")
CAMPO=TYPE,TITULO("Tipo"),WLONX=18,PREFIJO=A
CAMPO=TIEMPO,TITULO("Segundos"),WLONX=40,AUXILIAR
CAMPO=SQLBLOQUEA,AUXILIAR,OCULTO,"_512_________________________________"
CAMPO=MATADOR,AUXILIAR,OCULTO,"_80___"
CAMPO=ID1,OCULTO,"@L@@@@@@@"
CAMPO=ID2,OCULTO,"@L@@@@@@@"

CURSOR=CMATASESION SELECT 'ALTER SYSTEM KILL SESSION ''' || :SID ||',' || :SERIAL ||'''' MATADOR FROM DUAL;

TECLA=F8,FEJECUTA(FEJECUTACAMPO("MATADOR","SESION NO SE HA PODIDO MATAR"),"SESION NO SE HA PODIDO MATAR",
                   %FFAILURE,"SESION MATADA CON ÉXITO",
                   FPULSATECLAS("F3","F2"))

