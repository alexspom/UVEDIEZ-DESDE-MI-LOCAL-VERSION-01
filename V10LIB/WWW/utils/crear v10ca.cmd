CLS
REM 
REM ESTABLECE EL FICHERO DE CONFIGURACIÓN 
SET OPENSSL_CONF=I:\V10LIB\V10WEB\UTILS\OPENSSL.CFG
set
PAUSE
REM
REM Limpiar el fichero ./V10CA/index.txt
REM Guardar en ./V10CA/serial, el valor 01
REM Dejar ./V10CA/private, el fichero .rnd a blanco
REM Cuidado con el parámetro #crlnumber	= $dir/crlnumber	# the current crl number
REM del fichero openssl.cnf, en un principio debe estar comentado
REM
REM Genera el fichero dh1024.pem					
openssl dhparam -out dh1024.pem 1024
REM
PAUSE
cls
REM Genera unas claves públicas y privadas para nuestra autoridad certificadores, V10CA
REM Poner como ORganization Name,V10 SUPPLY CHANNEL
REM Poner como Common Name: grupov10  
openssl req -new -x509 -keyout v10cakey.pem -out v10cacert.pem -days 3650
REM
PAUSE
REM AUTOFIRMAR EL CERTIFICADO
REM
openssl req -new -key v10cakey.pem -x509 -days 3650 -out grupov10.crt
pause






