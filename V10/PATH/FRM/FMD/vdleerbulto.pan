###################################################################
#Módulo: VDLEERBULTO.PAN
#Funcionalidad : Escanear bulto con FMD
#Autor: DFL      
#Fecha: 22-08-2018
###################################################################
# Histórico de cambios:
# ---------------------
#
###################################################################
LEER BULTO CON FMD
 Código Bulto: _18_________________                                           
|

TABLA=VDBULTOCAB

NOQUERY
NOINSERT
NOCOMMIT

CAMPO=CODBULTO,POSTCHANGE=FEJECUTA("CVERFMDBULTO","EL BULTO NO TIENE FMD PENDIENTE DE LEER",
                                   FPULSATECLAS("F6"),"")
CAMPO=TIENEFMD,AUXILIAR,OCULTO, "_" 

CURSOR=CVERFMDBULTO BEGIN 
                       IF VDFMD.TIENEFMD (NULL,NULL,:CODBULTO) = 'N' THEN RAISE NO_DATA_FOUND; END IF; 
					END;@

#                       IF VDFMD.COMPROBARFMD (NULL,:CODBULTO) = 'N' THEN RAISE NO_DATA_FOUND; END IF; 

