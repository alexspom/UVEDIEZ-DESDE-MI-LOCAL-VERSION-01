# M�dulo   : VDCONSART.PAN
# Funci�n  : Consulta de articulo
#
# Creaci�n : 05-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
# 
CONSULTA DE ARTICULO
_10_______ _10_______  
LECTURA DE ARTICULO

ARTICULO _255______________________________________________________________
|


PREQUERY=FEJECUTA("CSELLIMPIAC","")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",
                   +FLEEARTICULO("CODBARRAS", "CODART"),"",
                   "CSELART","\nERROR,\n NO EXISTE EL ARTICULO\n :CODART",
                   FPOSICIONABLOQUE("VDCONSARTDET.PAN"),"ERROR AL CARGAR \n VDCONSARTDET.PAN") 

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBARRAS,SCAN,AUTOENTER
CAMPO=CODART,OCULTO,"_40_"
CAMPO=DESART,OCULTO,"_100"
CAMPO=DESART2,OCULTO,"_100"
CAMPO=NROFILA,OCULTO,"@@@@"

# DEFINICION DE CURSORES
CURSOR=CSELNOTNULL SELECT :CODBARRAS FROM DUAL WHERE :CODBARRAS IS NULL ; 

CURSOR=CSELLIMPIAC SELECT NULL CODART,NULL CODBARRAS,1 NROFILA FROM DUAL ;

CURSOR=CSELART SELECT CODART,VD.DIVIDEXBUSQUEDA(1,DESART,' ',30,0) DESART,VD.DIVIDEXBUSQUEDA(2,DESART,' ',30,0) DESART2
                 FROM VDARTIC
                WHERE CODART = :CODART;
