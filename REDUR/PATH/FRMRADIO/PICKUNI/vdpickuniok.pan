# M�dulo   : VDPICKUNIOK.PAN
# Funci�n  : Formulario de recogida de bultos de unidades.
#            Pantalla confirmaci�n de picking.
#
# Creaci�n : 13-05-2008
# Autor    : JMM
###########################################
# Hist�rico de cambios:
#
PICKING POR TERMINAL
_10_______ _10_______  

BULTO: _18_______________
UBICACION: _20____________
MATRICULA: _20___________
ARTICULO: _20_________________
  _20_________________________
  _20_________________________

LOTE: _20_________________
CANTIDAD: #L#############

STOCK RESTANTE
  @L@@@@

|

PREQUERY=FEJECUTA("CLIMPIAERRORES","")

POSTQUERY=FEJECUTA("CINCERRORES","",
                   FIF("-CVERIFICA",FIF("CMAXERROR",FEJECUTA("CCALCTOTAL","","CBLOQUBI","NO PUEDO BLOQUEAR UBICACION"),
                                                    FFAILURE)),"CANTIDAD INCORRECTA",
                   "CEJECUTAMOV","NO PUEDO EJECUTAR",
                   FIF("CSELLINEASPEND",FPOSICIONABLOQUE("VDPICKUNIDEC.PAN"),
                                        FPOSICIONABLOQUE("VDPICKUNIFIN.PAN")),"ERROR\n CARGANDO SIGUIENTE\n BLOQUE")

# DEFINICION DE CAMPOS
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODBULTO,NOENTER,VIRTUAL
CAMPO=CODUBI,VIRTUAL,NOENTER
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODMOV,VIRTUAL,NOENTER,OCULTO
CAMPO=CODART,VIRTUAL,NOENTER
CAMPO=DESART1,VIRTUAL,NOENTER
CAMPO=DESART2,VIRTUAL,NOENTER
CAMPO=CODLOT,VIRTUAL,NOENTER
CAMPO=CANTIDAD,VIRTUAL,NOENTER,CONVIERTE=FCONVIERTEARTFROMDB(":CODART");FCONVIERTEART2DB(":CODART")
CAMPO=RESTO
CAMPO=ERRORES,AUXILIAR,OCULTO,"@L"
CAMPO=TOTAL,AUXILIAR,OCULTO,"@L"

# DEFINICION DE CURSORES

CURSOR=CLIMPIAERRORES SELECT 0 ERRORES,0 RESTO FROM DUAL;

CURSOR=CINCERRORES SELECT :ERRORES+1 ERRORES FROM DUAL;

CURSOR=CMAXERROR SELECT :ERRORES FROM DUAL WHERE :ERRORES>=3;

CURSOR=CCALCTOTAL SELECT NVL(SUM(CANTIDAD),0)-:CANTIDAD TOTAL FROM VDSTOCK WHERE CODMAT=:CODMAT;

CURSOR=CVERIFICA SELECT :RESTO FROM VDSTOCK WHERE CODMAT=:CODMAT HAVING SUM(CANTIDAD)-:CANTIDAD=:RESTO;

CURSOR=CBLOQUBI DECLARE
                  RET NUMBER;
                BEGIN
                 UPDATE VDUBICA SET BLOQUEOSS='S'
                  WHERE CODUBI=:CODUBI;
                 VDCORREOS.CORREO('INCPICKING','ALCURA','Incidencia de picking','Error en ubicacion '||:CODUBI||' stock real '||:TOTAL||' informado por operario '||:RESTO||' Operario '||:CODOPE,NULL,NULL,1,'TEXT/HTML',NULL,NULL,:V10ERROR,RET);
                 COMMIT;
                END;@
                
CURSOR=CEJECUTAMOV DECLARE
                     RET NUMBER;
                   BEGIN
                     RET:=VDACTSTOCK.EJECUTAMOV(:CODMOV,:V10ERROR);
                     IF RET!=0 THEN RAISE NO_DATA_FOUND;
                     END IF;
                     COMMIT;
                   END;@
                                    

CURSOR=CSELLINEASPEND SELECT :CODBULTO
                        FROM VDBULTOCAB CB, VDBULTOLIN LB
                       WHERE CB.CODBULTO = :CODBULTO AND
                             LB.CODBULTO = CB.CODBULTO AND
                             LB.STATUS = VDST.FBULASERVIR;
