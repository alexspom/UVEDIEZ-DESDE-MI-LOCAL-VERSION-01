# M�dulo: VDREUBIMANU.PAN
# Funci�n: Ubicacion manual del palet recepcionado
# Fecha: 01-02-2011
# Autor: RFD
# Hist�rico de cambios
#
#
  UBICACION DE CONTENEDOR
  ________ ________________ 
  
 MATRICULA _18_______________

 A UBICACION: ____________
 
  X: volver atras

|

PREQUERY=FEJECUTA("+CSELLIMPIA","")

POSTQUERY=FEJECUTA(FIF("CSALIR",FPOSICIONABLOQUE("VDUBICAENTRADAS1.PAN")),"ERROR SALIENDO DE PANTALLA", 
                   "CSELUBI","UBICACION NO EXISTE",
                   FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"",
                   FUBICOMPATIBLE(":CODMAT",":CODUBIDEST"),"Contenedor incompatible\n con destino",
                   FCAMBIOUBICONTE(":CODMAT",":CODUBIDEST",":TAREA","CODMOV","S","S",
                                   "CU","10","2000",":CODRECURSO"),"ERROR DEVUELTO POR FCAMBIOUBICNT",
                   FEJECUTAMOVSYNC("ACTSTKORIGEN","ACTSTKDESTINO",":CODMOV",":CODRECURSO"),"",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("VDUBICAENTRADAS1.PAN"),"ERROR CARGANDO BLOQUE 1")
  


CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL 
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODUBI,SCAN,POSTCHANGE=FPULSATECLAS("335","331")
CAMPO=CODUBIDEST,OCULTO,"_12_"

CAMPO=CODMOV,OCULTO,"@L@@@@@@@@"
CAMPO=TAREA,VIRTUAL,OCULTO
CAMPO=STATUS,OCULTO,"@L@@@@"
CAMPO=DOMMY,OCULTO,"_"


CURSOR=CSELLIMPIA SELECT '' CODUBIDEST, 0 CODMOV , '' CODUBI FROM DUAL;

CURSOR=CSELUBI SELECT :CODUBI CODUBIDEST FROM VDUBICA WHERE CODUBI=:CODUBI;

CURSOR=CSELNOTNULL SELECT 1 DOMMY FROM DUAL WHERE :CODUBIDEST IS NULL;

CURSOR=CSALIR SELECT :CODUBI FROM DUAL WHERE :CODUBI='X';

