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

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FPOSICIONABLOQUE("-1"),
                      FEJECUTA("CSELCODMAT","\nERROR\n NO EXISTE UBICACION\nINTRODUZCA UNA CORRECTA",
                               FPOSICIONABLOQUE("VDCONSUBICNT.PAN"),"")),"")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL

CAMPO=CODUBI,VIRTUAL,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("UBI"),"\nERROR\n DEBE SCANNEAR\n LA UBICACION")
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
                    
                    

CURSOR=CANADEF1 SELECT TRANSLATE(:CODUBI,' IE',' ')||'I' CODUBI FROM DUAL;
CURSOR=CANADEF2 SELECT TRANSLATE(:CODUBI,' IE',' ')||'E' CODUBI FROM DUAL;
                   
TECLA=F1,FEJECUTA("CANADEF1","",
                  FPULSATECLAS("CR"),"")  
                   
TECLA=F2,FEJECUTA("CANADEF2","",
                  FPULSATECLAS("CR"),"")                                              


                    