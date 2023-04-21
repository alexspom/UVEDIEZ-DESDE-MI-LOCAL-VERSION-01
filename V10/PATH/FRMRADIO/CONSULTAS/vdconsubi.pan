# Módulo   : VDCONSUBI.PAN
# Función  : Consulta de ubicaciones
#
# Creación : 05-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
# 
CONSULTA DE UBICACION
_10_______ _10_______ 
CONSULTA DE UBICACION



  UBICACION _12_________
  
  
  
  
|
PREQUERY=FEJECUTA("+CLIMPIACAMPOS","")


POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM(""),FSUCCESS),"ERROR\n AL VOLVER AL MENU",
                   "CSELCODMAT","\nERROR\n NO EXISTE\n LA UBICACION\n :CODUBI",
                   FPOSICIONABLOQUE("VDCONSUBICNT.PAN"),"")								

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL

CAMPO=CODUBI,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\nERROR\n DEBE SCANNEAR\n LA UBICACION")
CAMPO=POSCONTE,OCULTO,"@L@@"


# DEFINICION DE CURSORES
CURSOR=CLIMPIACAMPOS SELECT '' CODUBI
                       FROM DUAL;

CURSOR=CSELCODMAT SELECT 0 POSCONTE
                    FROM VDUBICA 
                   WHERE CODUBI=:CODUBI;

CURSOR=CSELNOTNULL SELECT :CODUBI 
                     FROM DUAL 
                    WHERE :CODUBI IS NULL;
                    
                    
                                            


                    