# Módulo   : VDASOCIAPICKINGTERM3.PAN
# Función  : Formulario de asociación de bultos a terminal por radio
#
# Creación : 12-05-2008
# Autor    : JMM
###########################################
# Histórico de cambios:
# 
ASOCIAR BULTOS A TERMINAL
_10_______ _10_______ 
_____________________
  
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
CAMPO=TEXTOPAN,NOENTER,VIRTUAL
CAMPO=TEXTOTAREA,VIRTUAL,OCULTO
CAMPO=NBULTOS,VIRTUAL,NOENTER
CAMPO=NLINEAS,VIRTUAL,OCULTO
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
                    CURSOR SELBULTOS IS SELECT DISTINCT BUC.MATCAJA 
                                          FROM VDBULTOCAB BUC,VDBULTOLIN BUL, VDMOVIM MOV 
                                         WHERE BUC.CODBULTO=BUL.CODBULTO AND BUL.CODMOV=MOV.CODMOV AND MOV.STATUS=VDST.FMOVASIGNADO AND 
                                               MOV.CODRECURSO=:CODRECURSO AND MOV.TAREA=VD.GETPROP('TAREAPEDUNI');                  
                 BEGIN
                  NUMERO:=0;
                  FOR REG IN SELBULTOS LOOP
                   CASE NUMERO
                     WHEN 0 THEN
                          :BULTO1:=REG.MATCAJA;
                     WHEN 1 THEN
                          :BULTO2:=REG.MATCAJA;
                     WHEN 2 THEN
                          :BULTO3:=REG.MATCAJA;
                     WHEN 3 THEN
                          :BULTO4:=REG.MATCAJA;
                     WHEN 4 THEN
                          :BULTO5:=REG.MATCAJA;
                     WHEN 5 THEN
                          :BULTO6:=REG.MATCAJA;
                     WHEN 6 THEN
                          :BULTO7:=REG.MATCAJA;
                     WHEN 7 THEN
                          :BULTO8:=REG.MATCAJA;
                     WHEN 8 THEN
                          :BULTO9:=REG.MATCAJA;
                     WHEN 9 THEN
                          :BULTO10:=REG.MATCAJA;
                     WHEN 10 THEN
                          :BULTO11:=REG.MATCAJA;
                     WHEN 11 THEN
                          :BULTO12:=REG.MATCAJA;
                     ELSE 
                       NULL;
                   END CASE;
                   NUMERO:=NUMERO+1;
                  END LOOP;
                END;@  

