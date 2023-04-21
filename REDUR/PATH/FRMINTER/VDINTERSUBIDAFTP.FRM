CAMPO=HFICHERO,AUXILIAR,OCULTO,"@L@@@@@@@@@@"

BEGINBLOQUEFRM=VDINTERLIN
   TABLA=DUAL
   SOLOQUERY

   SELECT=SELECT 'X' DUMMY
          FROM DUAL;

   CAMPO=DUMMY,AUXILIAR,OCULTO,"_20"

   POSTBLOQUE=FEJECUTA(FWINEXEC("D:\V10\REDUR\CMD\SUBIDAFTP.CMD","0"),"Error realizando subida FTP de fichero",
                       FWINEXEC("D:\V10\REDUR\CMD\SUBIDAFTPBELLOTA.CMD","0"),"Error subiendo albaranes",
                       FWINEXEC("D:\V10\REDUR\CMD\SUBIDAFTPALB.CMD","0"),"Error realizando subida FTP de fichero")
					   
   PREBLOQUE=FEJECUTA(FWINEXEC("D:\V10\REDUR\CMD\COPYBAK.CMD","0"),"Error realizando subida FTP de fichero",
					   FWINEXEC("D:\V10\REDUR\CMD\COPYBAKBEL.CMD","0"),"Error realizando subida FTP de fichero")
   
ENDBLOQUE



