# Módulo   : VDSELAREA.PAN
# Función  : Seleccion multiple de areas
#
# Creación : 05-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
SELECCION DE AREAS
 Cod.            Designación                 Sel
 _20____________ _30________________________  _

|

TABLA=VDAREA


CAMPO=CODAREA,UPPER
CAMPO=DESAREA,UPPER
CAMPO=SEL,AUXILIAR,UPPER,TOOLTIP(":RANAREA"),POSTCHANGE=FDESIGNACION("CCHECKVALUES","Debe introducir S(i) o N(o)",
                                                                     FIF("CSELINCLUDE",FIF("-CCHECKRANAREA","CAPENDAREA"),
                                                                                       FIF("CCHECKRANAREA","CELIMINAAREA")),
                                                                         "ERROR MODIFICANDO VARIABLE RANAREA")

CURSOR=CCHECKVALUES SELECT :SEL FROM DUAL WHERE :SEL IS NULL OR :SEL IN ('S','N');

CURSOR=CSELINCLUDE SELECT :SEL FROM DUAL WHERE :SEL = 'S';

CURSOR=CCHECKRANAREA SELECT :CODAREA FROM DUAL WHERE VD.CONTIENECAD(:RANAREA,:CODAREA) = 1 AND :RANAREA IS NOT NULL;

CURSOR=CAPENDAREA SELECT DECODE(:RANAREA,NULL,:CODAREA,:RANAREA||','||:CODAREA) RANAREA FROM DUAL;

CURSOR=CELIMINAAREA SELECT VD.ELIMINAPIEZA(:RANAREA,:CODAREA) RANAREA FROM DUAL;


