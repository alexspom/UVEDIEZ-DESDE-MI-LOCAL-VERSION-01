#
GESTION DE BULBCE CON ETIQUETA
_10_______ _10_______
CAJA COMPLETA


LLEVE LOS BULTOS 
     
______________________________
|

PREQUERY=FEJECUTA("+CMENSAJE","")                 
                  
POSTQUERY=FEJECUTA(FCARGAFORM(""))
                   
# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CTRLCALIDAD,VIRTUAL,OCULTO
CAMPO=MENSAJE,NOENTER
CAMPO=CODPREPARACION,VIRTUAL,OCULTO


CURSOR=CMENSAJE SELECT DECODE(:CTRLCALIDAD,'S',' A MANIPULACION',' A EXPEDICIONES') MENSAJE FROM DUAL;

