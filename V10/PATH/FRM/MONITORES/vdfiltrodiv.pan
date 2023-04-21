# Módulo   : VDSELDIV.PAN
# Función  : Seleccion multiple de divisiones
#
# Creación : 05-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
SELECCION DE DIVISION
Cod. Designación                  Sel 
_20__ _40_________________________  _

|

TABLA=VDDIVIS

ORDERBY=CODDIV;


CAMPO=CODDIV,UPPER,TITULO("Cod.")
CAMPO=DESDIV,UPPER,TITULO("Designación")
CAMPO=SEL,AUXILIAR,UPPER,TOOLTIP(":RANDIV"),POSTCHANGE=FDESIGNACION("CCHECKVALUES","Debe introducir S(i) o N(o)",
                                                                    FIF("CSELINCLUDE",FIF("-CCHECKRANDIV","CAPENDDIV"),
                                                                                      FIF("CCHECKRANDIV","CELIMINADIV")),
                                                                        "ERROR MODIFICANDO VARIABLE RANDIV"),TITULO("Sel"),WLONX=10

CURSOR=CCHECKVALUES SELECT :SEL FROM DUAL WHERE :SEL IS NULL OR :SEL IN ('S','N');

CURSOR=CSELINCLUDE SELECT :SEL FROM DUAL WHERE :SEL = 'S';

CURSOR=CCHECKRANDIV SELECT :CODDIV FROM DUAL WHERE VD.CONTIENECAD(:RANDIV,:CODDIV) = 1 AND :RANDIV IS NOT NULL;

CURSOR=CAPENDDIV SELECT DECODE(:RANDIV,NULL,:CODDIV,:RANDIV||','||:CODDIV) RANDIV FROM DUAL;

CURSOR=CELIMINADIV SELECT VD.ELIMINAPIEZA(:RANDIV,:CODDIV) RANDIV FROM DUAL;


