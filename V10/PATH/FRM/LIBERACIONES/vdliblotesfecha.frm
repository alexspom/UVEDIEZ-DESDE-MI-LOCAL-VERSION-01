CAMPO=POSICION,AUXILIAR,OCULTO,"#L#"
CAMPO=VALORPDTECALIDAD,AUXILIAR,OCULTO,"#L#"
CAMPO=VALORLIBERADO,AUXILIAR,OCULTO,"#L#"
CAMPO=VALORRECHAZADO,AUXILIAR,OCULTO,"#L#"
BEGINBLOQUE=VDLIBFECHAS.PAN
  TECLA=F4,PRESEHIJO
  CAMPO=POSICION,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORPDTECALIDAD,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORLIBERADO,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORRECHAZADO,AUXILIAR,VIRTUAL,OCULTO
  TITULO=CONSULTA DE CAMBIOS DE CALIFICACION DE LOTES POR FECHA
# PRUEBA
  CURSOR=CPRUEBA SELECT 2 POSICION,'2' VALORPDTECALIDAD,'0' VALORLIBERADO,'1' VALORRECHAZADO FROM DUAL;
  PREBLOQUE=FEJECUTA("CPRUEBA","")
# FIN PRUEBA  
ENDBLOQUE
BEGINBLOQUE=VDLOTESHIST.PAN
  PREREGISTRO=PRESEHIJO
  PADRE=VDLIBFECHAS.PAN
  CAMPO=POSICION,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORPDTECALIDAD,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORLIBERADO,AUXILIAR,VIRTUAL,OCULTO
  CAMPO=VALORRECHAZADO,AUXILIAR,VIRTUAL,OCULTO  
  CAMPO=DESDE,VIRTUAL,AUXILIAR,OCULTO
  CAMPO=HASTA,VIRTUAL,AUXILIAR,OCULTO
  CAMPO=LIBERACIONES,VIRTUAL,AUXILIAR,OCULTO
  CAMPO=RECHAZOS,VIRTUAL,AUXILIAR,OCULTO
  CAMPO=MICODART,VIRTUAL("CODART"),AUXILIAR,OCULTO
  CAMPO=MICODLOT,VIRTUAL("CODLOT"),AUXILIAR,OCULTO
WHERE=FECINS BETWEEN :DESDE AND :HASTA AND 
         SUBSTR(BLOQLOTEACTUAL,:POSICION,1)=:VALORPDTECALIDAD AND
         (CODART=:MICODART OR :MICODART IS NULL) AND
         (CODLOT=:MICODLOT OR :MICODLOT IS NULL) AND
         ((:LIBERACIONES='S' AND SUBSTR(BLOQLOTENUEVO,:POSICION,1)=:VALORLIBERADO)
          OR (:RECHAZOS='S' AND SUBSTR(BLOQLOTENUEVO,:POSICION,1)=:VALORRECHAZADO));
  ORDERBY=FECINS DESC, HORAINS DESC;
  POSY=14
  REGPAG=25
ENDBLOQUE    
BEGINBLOQUE=VDLOTESHIST2.PAN
  PADRE=VDLOTESHIST.PAN
  PREQUERY=QUERYHIJO
  POSY=43
  REGPAG=1
ENDBLOQUE    
