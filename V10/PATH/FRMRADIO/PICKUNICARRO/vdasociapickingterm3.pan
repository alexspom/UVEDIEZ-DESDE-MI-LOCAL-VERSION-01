# Módulo   : VDASOCIAPICKINGTERM3.PAN
# Función  : Formulario de asociación de bultos a terminal por radio
#
# Creación : 12-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
# 
  LISTA DE BULTOS ASIGNADOS
  ___________ ________________
  
  TOTAL: #L######  _
  BULTOS:
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
  ____________________
|

PREQUERY=FEJECUTA("+CBULTOS","")

POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("VDASOCIAPICKINGTERM2.PAN"),"ERROR\n AL CARGAR BLOQUE VDASOCIAPICKINGTERM2.PAN")


CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=NBULTOS,VIRTUAL,NOENTER
CAMPO=NLINEAS,VIRTUAL,OCULTO
CAMPO=CODBULTO,VIRTUAL,OCULTO
CAMPO=OPCION

CAMPO=BULTO1,NOENTER
CAMPO=BULTO2,NOENTER
CAMPO=BULTO3,NOENTER
CAMPO=BULTO4,NOENTER
CAMPO=BULTO5,NOENTER
CAMPO=BULTO6,NOENTER
CAMPO=BULTO7,NOENTER
CAMPO=BULTO8,NOENTER
CAMPO=BULTO9,NOENTER
CAMPO=BULTO10,NOENTER
CAMPO=BULTO11,NOENTER
CAMPO=BULTO12,NOENTER
                   
CURSOR=CBULTOS DECLARE                  
                    NUMERO NUMBER;
                    CURSOR SELBULTOS IS SELECT DISTINCT BUL.CODBULTO 
                                          FROM VDBULTOLIN BUL, VDMOVIM MOV 
                                         WHERE BUL.CODMOV=MOV.CODMOV AND MOV.STATUS=VDST.FMOVASIGNADO AND 
                                               MOV.CODRECURSO=:CODRECURSO AND MOV.TAREA=VD.GETPROP('TAREAPEDUNI');                  
                 BEGIN
                  NUMERO:=0;
                  FOR REG IN SELBULTOS LOOP
                   CASE NUMERO
                     WHEN 0 THEN
                          :BULTO1:=REG.CODBULTO;
                     WHEN 1 THEN
                          :BULTO2:=REG.CODBULTO;
                     WHEN 2 THEN
                          :BULTO3:=REG.CODBULTO;
                     WHEN 3 THEN
                          :BULTO4:=REG.CODBULTO;
                     WHEN 4 THEN
                          :BULTO5:=REG.CODBULTO;
                     WHEN 5 THEN
                          :BULTO6:=REG.CODBULTO;
                     WHEN 6 THEN
                          :BULTO7:=REG.CODBULTO;
                     WHEN 7 THEN
                          :BULTO8:=REG.CODBULTO;
                     WHEN 8 THEN
                          :BULTO9:=REG.CODBULTO;
                     WHEN 9 THEN
                          :BULTO10:=REG.CODBULTO;
                     WHEN 10 THEN
                          :BULTO11:=REG.CODBULTO;
                     WHEN 11 THEN
                          :BULTO12:=REG.CODBULTO;
                     ELSE 
                       NULL;
                   END CASE;
                   NUMERO:=NUMERO+1;
                  END LOOP;
                END;@  

