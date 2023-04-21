# Ejemplo simple con SOLOQUERY solo lectura
#
USUARIOS Y PRIVILEGIOS
Codigo Usuario  Nombre     Apellido1   Apellido2   Caducidad   Privilegio
______________  _30_______ _30_______  _30_______  ¿D-MM-Y.YY  ____________________
|

SOLOQUERY

SELECT=SELECT A.CODOPE,A.NOMBRE,A.APELLIDO1,A.APELLIDO2,A.FECCADUC,B.PRIVILEGIO
		 FROM VDUSUARIO A JOIN VDPRIVOPE B
		   ON A.CODOPE=B.CODOPE;
		   
REGPAG=20
WLONX=650

CAMPO=CODOPE,TITULO("Codigo Usuario")
CAMPO=NOMBRE,TITULO("Nombre")
CAMPO=APELLIDO1,TITULO("Apellido1")
CAMPO=APELLIDO2,TITULO("Apellido2")
CAMPO=FECCADUC,TITULO("Caducidad")
CAMPO=PRIVILEGIO,TITULO("Privilegio")
