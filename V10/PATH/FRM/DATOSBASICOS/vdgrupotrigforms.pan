# Módulo   : VDGRUPOTRIGFORMS.PAN
# Función  : Consulta de tipo de trigers del forms
#
# Creación : 09-07-2006
# Autor    : FGS
###########################################
# Histórico de cambios:
GRUPO DE TRIGERS DE FORMS

Grupo       
________________________________
|

SOLOQUERY
SELECT=SELECT * FROM (SELECT DISTINCT GRUPOTRIGER FROM VDTRIGFORMS 
                      UNION
                      SELECT '%' GRUPOTRIGER FROM DUAL);
ORDERBY=DECODE(GRUPOTRIGER, '%','ZZZZZZ',GRUPOTRIGER);

CAMPO=GRUPOTRIGER,TOOLTIP("GRUPO AL QUE PERTENECE EL TRIGGER"),TITULO("Grupo")


