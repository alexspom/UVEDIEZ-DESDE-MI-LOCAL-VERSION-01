CAMPO=HFICHERO,AUXILIAR,OCULTO,"@L@@@@@@@@@@"

BEGINBLOQUEFRM=VDINTERLIN
   TABLA=DUAL
   SOLOQUERY

   SELECT=SELECT 'X' DUMMY
          FROM DUAL;

   CAMPO=DUMMY,AUXILIAR,OCULTO,"_20"

   POSTBLOQUE=FEJECUTA(FWINEXEC("D:\V10\REDUR\CMD\BAJADAFTP.CMD"),"Error realizando bajada FTP de fichero")
   
ENDBLOQUE



