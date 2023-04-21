# Módulo   : VDSELAGE.PAN
# Función  : Seleccion multiple de agencias
#
# Creación : 05-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
SELECCION DE AGENCIA
COd.        Designación                 Sel 
_10________ _30________________________  _

|

TABLA=VDAGENCIA

ORDERBY=CODAGE;


CAMPO=CODAGE,UPPER,TITULO("COd.")
CAMPO=DESAGE,UPPER,TITULO("Designación")
CAMPO=SEL,AUXILIAR,UPPER,TOOLTIP(":RANAGE"),POSTCHANGE=FDESIGNACION("CCHECKVALUES","Debe introducir S(i) o N(o)",
                                                                    FIF("CSELINCLUDE",FIF("-CCHECKRANAGE","CAPENDAGE"),
                                                                                      FIF("CCHECKRANAGE","CELIMINAAGE")),
                                                                        "ERROR MODIFICANDO VARIABLE RANDIV"),TITULO("Sel"),WLONX=10

CURSOR=CCHECKVALUES SELECT :SEL FROM DUAL WHERE :SEL IS NULL OR :SEL IN ('S','N');

CURSOR=CSELINCLUDE SELECT :SEL FROM DUAL WHERE :SEL = 'S';

CURSOR=CCHECKRANAGE SELECT :CODAGE FROM DUAL WHERE VD.CONTIENECAD(:RANAGE,:CODAGE) = 1 AND :RANAGE IS NOT NULL;

CURSOR=CAPENDAGE SELECT DECODE(:RANAGE,NULL,:CODAGE,:RANAGE||','||:CODAGE) RANAGE FROM DUAL;

CURSOR=CELIMINAAGE SELECT VD.ELIMINAPIEZA(:RANAGE,:CODAGE) RANAGE FROM DUAL;

