MANDAR MENSAJE A TERMINAL
Terminal   Mensaje
_10_______ _100__________________________________
|

TABLA=VDMSGRAD

PREINSERT=FEJECUTA("CSELMODIF","")

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=MENSAJE
CAMPO=CODOPEMODIF,OCULTO,"_32"
CAMPO=FECMODIF,OCULTO,"�D-MM-Y.YY"
CAMPO=HORAMODIF,OCULTO,"________"
CAMPO=STATUS,OCULTO,"@L@@@"

CURSOR=CSELMODIF SELECT VDUSER.GETUSER CODOPEMODIF,VD.FECHASYS FECMODIF,VD.HORASYS HORAMODIF,100 STATUS FROM DUAL;