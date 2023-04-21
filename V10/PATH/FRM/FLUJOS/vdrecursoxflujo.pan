#Módulo: VDRECURSOXFLUJO.PAN
#Función: Recursos por flujo
#
# Creación : 13-11-2007
# Autor    : ICC
###########################################
# Histórico de cambios:
Recursos
Cod.recurso
__________ 
|                                  


SOLOQUERY
SELECT=SELECT CODRECURSO FROM VDTRAMOSRECURSO WHERE CODAREADEST=:CODAREADEST AND CODAREAORI=:CODAREAORI; 

CAMPO=CODAREAORI,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODAREADEST,VIRTUAL,AUXILIAR,OCULTO
CAMPO=CODRECURSO,NOENTER

