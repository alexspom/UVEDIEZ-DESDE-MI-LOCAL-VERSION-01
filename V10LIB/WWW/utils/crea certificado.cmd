CLS
REM la palabra de paso siempre es meliton
REM 
REM ESTABLECE EL FICHERO DE CONFIGURACIÓN 
SET OPENSSL_CONF=I:\V10LIB\WWW\UTILS\OPENSSL.CFG
set
PAUSE
REM
CLS
REM Creo las claves privadas y la petición para firmar
REM Utiliza el mismo ORganization Name (V10 SUPPLY CHANNEL)
REM Poner como Common Name:  nombre del equipo servidor para el que se crea el certificado, o IP (sin http), 
REM (pero sin el www si fuese extranet) y sin el puerto
openssl req -new -days 3650 -out server.req -keyout server.pem
REM
PAUSE
CLS
REM FIRMA EL CERTIFICADO
openssl ca -days 3650 -keyfile v10cakey.pem -cert v10cacert.pem -in server.req -out v10.crt
rem
pause
CLS
REM AÑADIR AL FINAL DE SERVER.PEM EL CERTIFICADO PUBLICO CONTENDIDO EN V10.CRT
REM
REM RENOMBRAR V10CACERT.PEM A ROOT.PEM
REM







