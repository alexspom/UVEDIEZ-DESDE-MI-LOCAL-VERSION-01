#SELECCION DE RECURSO
SELECCION DE RECURSO
Recurso                                 Estado                          S
__________ _40_________________________ @L@@@ _40______________________ _
|

TABLA=VDRECURSO


CAMPO=CODRECURSO,NOUPDATE,TOOLTIP("Código del recurso")
CAMPO=DESRECURSO,NOUPDATE,TOOLTIP("designación del recurso")
CAMPO=STATUS,NOUPDATE,TOOLTIP("Estado del recurso"),POSTCHANGE=FDESIGNACION("CSELESTADO","No existe estado")
CAMPO=DESSTATUS,AUXILIAR,NOENTER,TOOLTIP("Designacion del estado")
CAMPO=SEL,AUXILIAR

CURSOR=CSELESTADO SELECT DESSTATUS FROM VDSTATUS WHERE STATUS=:STATUS AND TIPOSTATUS='REC';


