# Módulo   : VDSELPERFILRAD.PAN
# Función  : Seleccion multiple de perfiles de tareas
#
# Creación : 05-08-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
#
SELECCION DE PERFILES DE TAREAS
 Cod.        Designación                 Sel
 _10________ _40________________________  _

|

TABLA=VDPERFILTAREA


CAMPO=CODPERFIL,UPPER
CAMPO=DESPERFIL,UPPER
CAMPO=SEL,AUXILIAR,UPPER,TOOLTIP(":RANPERFIL"),POSTCHANGE=FDESIGNACION("CCHECKVALUES","Debe introducir S(i) o N(o)",
                                                                    FIF("CSELINCLUDE",FIF("-CCHECKRANPERFIL","CAPENDPERFIL"),
                                                                                      FIF("CCHECKRANPERFIL","CELIMINAPERFIL")),
                                                                        "ERROR MODIFICANDO VARIABLE RANPERFIL")

CURSOR=CCHECKVALUES SELECT :SEL FROM DUAL WHERE :SEL IS NULL OR :SEL IN ('S','N');

CURSOR=CSELINCLUDE SELECT :SEL FROM DUAL WHERE :SEL = 'S';

CURSOR=CCHECKRANPERFIL SELECT :CODPERFIL FROM DUAL WHERE VD.CONTIENECAD(:RANPERFIL,:CODPERFIL) = 1 AND :RANPERFIL IS NOT NULL;

CURSOR=CAPENDPERFIL SELECT DECODE(:RANPERFIL,NULL,:CODPERFIL,:RANPERFIL||','||:CODPERFIL) RANPERFIL FROM DUAL;

CURSOR=CELIMINAPERFIL SELECT VD.ELIMINAPIEZA(:RANPERFIL,:CODPERFIL) RANPERFIL FROM DUAL;


