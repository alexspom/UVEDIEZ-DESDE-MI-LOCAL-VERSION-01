# MOdulo   : VDTIPORDREC.FRM
# Función  : Mantenimiento de tipos de Ordenes de recepción
#
# Creación : 12-02-2007
# Autor    : ICC
###########################################
# HistOrico de cambios:
CAMPO=MSGERROR,OCULTO
BEGINBLOQUE=VDRECCAB.PAN
  PREREGISTRO=PRESEHIJO
  NODELETE
  NOINSERT
    REGPAG=10
  POSX=1
  POSY=1
  WHERE=STATUS=VDST.FRCCACTIVA 
    AND (CODRECEP, CODDIV) IN (SELECT CODRECEP, CODDIV FROM VDRECEPLIN); 

  CAMPO=CODMOV,AUXILIAR,OCULTO,"@L@@@@@@@"
  CAMPO=SECLINORD,AUXILIAR,OCULTO,"@L@@@@@@"
  CAMPO=RET,OCULTO,AUXILIAR,"#"

  TECLA=SF1,FEJECUTA("CCREAMOVREG","ERROR, :V10ERROR \nCREANDO MOVIMIENTO DE CAMBIO DE ESTADO",
                     "-CVERERROR2","ERROR, :V10ERROR",
                     "CCIERRARECEP", "ERROR CERRANDO LA CABECERA DE RECEPCION",
                     "+CSELLINFIN","",
                                FWHILE(FERRORCURSOR("CSELLINFIN"),
                                       FEJECUTA("CCIERRAORDRECEPLIN","ERROR,\nAL CERRAR LA LINEA :SECLINORD DE LA\nORDEN DE RECEPCION :CODORDREC",
                                                          +FFETCHCURSOR("CSELLINFIN"),"ERROR EN FETCH")),"ERROR EN FWHILE",
                     "+CCIERRAORDRECEPCAB","\nERROR,\nAL CERRAR LA CABECERA DE LA\nORDEN DE RECEPCION :CODORDREC",
                     FCOMMIT,"",
                     FIMPRIME("INFORME","$(VDRECEPDATOS)","CODDIV=:CODDIV;CODRECEP=:CODRECEP",""),":V10ERROR",
                     FCOMMIT,"",
                     FFAILURE,"LIBERADA LA RECEPCION :CODRECEP\nRECOJA INFORME DE LA IMPRESORA",
                     FPULSATECLAS("CF2","F2"),"")
  BOTON=B1,1050,20,50,50,"B1",vertis\vertisok.png,SF1,"Validar Recepción",INCLUDECSS="background-color: transparent;border-width:0px"

  TECLA=SF2,FEJECUTA("CCREAMOVANUL","\n ERROR\n\n :V10ERROR\n CREANDO MOVIMIENTO :V10ERROR",
                     "UPDRECLIN", "ERROR, ACTUALIZANDO LA LINEA DE RECEPCION",
                     "UPDRECCAB", "ERROR, ACTUALIZANDO LA CABECERA DE RECEPCION",
                     FCOMMIT,"",
                     FFAILURE," ANULADA LA RECEPCION :CODRECEP ",
                     FPULSATECLAS("F3","F2"))                
  BOTON=B3,1050,140,50,50,"B3",ANULAR.png,SF2,"Anular",INCLUDECSS="background-color: transparent;border-width:0px"

 CURSOR=CCREAMOVREG BEGIN
                        :RET := VDRECEP.LIBERARECEP(:CODRECEP);
                    END;@
  
 CURSOR=CVERERROR2 SELECT :RET RET
                     FROM DUAL
                    WHERE :RET < 0;
  
  
#Cierra la recepción
 CURSOR=CCIERRARECEP UPDATE VDRECEPCAB
                        SET STATUS = VDST.FRCCFINALIZADA
                      WHERE CODRECEP = :CODRECEP;  

#Cierra las líneas finalizadas del mismo artículo y lote, si lo indican.  

  CURSOR=CSELLINFIN SELECT SECLINORD
                      FROM VDORDRECLIN
                     WHERE CODORDREC = :CODORDREC
                       AND CODDIV    = :CODDIV
                       AND VDRECEP.CANTPDTE(:CODORDREC, CODART, :CODDIV, CODLOT, SECLINORD,'S') <= 0;

  CURSOR=CCIERRAORDRECEPLIN UPDATE VDORDRECLIN
                            SET STATUS= VDST.FORLFINALIZADA,
                                CODOPEMODIF = VDUSER.GETUSER,
                                FECMODIF    = VD.FECHASYS,
                                HORAMODIF   = VD.HORASYS
                          WHERE CODORDREC = :CODORDREC
                            AND CODDIV    = :CODDIV
                            AND SECLINORD = :SECLINORD;
  
#Cierra la cabecera de la orden si ya se han cerrado todas sus líneas.
  CURSOR=CCIERRAORDRECEPCAB UPDATE VDORDRECCAB
                            SET STATUS = CASE WHEN CODORDREC NOT IN (SELECT CODORDREC FROM  VDORDRECLIN
                                                                      WHERE CODORDREC = :CODORDREC
                                                                        AND CODDIV    = :CODDIV 
                                                                        AND STATUS    < VDST.FORLFINALIZADA) THEN
                                                   VDST.FORCFINALIZADA
                                              ELSE VDST.FORCACTIVA END,
                                CODOPEMODIF = VDUSER.GETUSER,
                                FECMODIF    = VD.FECHASYS,
                                HORAMODIF   = VD.HORASYS
                          WHERE CODORDREC = :CODORDREC
                            AND CODDIV    = :CODDIV
                            AND (NOT EXISTS(SELECT CODORDREC
                                              FROM VDORDRECLIN
                                             WHERE CODORDREC = :CODORDREC
                                               AND CODDIV    = :CODDIV 
                                               AND STATUS    < VDST.FORLFINALIZADA)
                             OR STATUS = VDST.FORCPENRECEP);

CURSOR=CCREAMOVANUL DECLARE
                     CURSOR C1 IS
                          SELECT STK.CODMAT, STK.CODART, STK.CODLOT, STK.UNIEMB, STK.CANTIDAD,STK.MARCASTK
                            FROM VDSTOCK STK, VDCONTE CNT
                           WHERE STK.CODRECEP = :CODRECEP
                             AND STK.CODMAT   = CNT.CODMAT;
                      RET NUMBER;
                     BEGIN
                        FOR I IN C1 LOOP
                            IF I.CANTIDAD > 0 THEN
                               :CODMOV := 0;
                               VDMOV.CREAMOV(:CODMOV, VD.GETPROP('TAREARECEP'), VD.GETPROP('REGULARIZA-'), VDST.FMOVPDTERECOGE, I.CODMAT, 'REGULARIZA',
                                             I.CODMAT, I.CODART, I.CODLOT,I.UNIEMB,'',I.CANTIDAD,0,0, NULL,MIMARCASTK=>I.MARCASTK);
                               IF :CODMOV > 0 THEN
                                  UPDATE VDMOVIM
                                     SET CODRECEP = :CODRECEP
                                   WHERE CODMOV   = :CODMOV;
                                  RET:=VDACTSTOCK.EJECUTAMOV(:CODMOV,:V10ERROR);
                                  IF RET!=0 THEN RAISE NO_DATA_FOUND;
                                   END IF;
                               ELSE
                                 RAISE NO_DATA_FOUND;
                               END IF;
                            END IF;
                        END LOOP;
                     END;@

CURSOR=UPDRECLIN UPDATE VDRECEPLIN
                    SET CANTIDADR = 0,
                        CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                  WHERE CODRECEP = :CODRECEP;

CURSOR=UPDRECCAB UPDATE VDRECEPCAB
                    SET STATUS = VDST.FRCCANULADA,
                        CODOPEMODIF = VDUSER.GETUSER, FECMODIF = VD.FECHASYS, HORAMODIF = VD.HORASYS 
                  WHERE CODRECEP = :CODRECEP;
                  
CURSOR=CMANDACORREO DECLARE
                      MIEMAIL ALCENSAYO.EMAILRECEP%TYPE;
                    BEGIN
                      SELECT EMAILRECEP INTO MIEMAIL FROM ALCENSAYO WHERE CODENSAYO=
                      VDCORREOS.CORREO('DEVOLUCIONES',VDUSER.GETHOSTNAME,'Recepcion de devolucion '||:REMOVAL,'Hemos recepcionado '||:NUMBULTOS||' bultos correspondientes a la removal '||:REMOVAL,'','',1,'',0,'',:V10ERROR,:RET);
                    END;@


ONLINE= {F1} Ayuda    {F2} Consulta    {F4} Confirmar cambios   {May-F7} Documentación {May+F8} Imprimir  {F5} Borrar Pantalla
        {May-F1} Validar recepción  {May-F2} Anular recepción   {Esc} Cerrar Pantalla;

ENDBLOQUE
BEGINBLOQUE=VDRECARTIC.PAN
  PADRE=VDRECCAB.PAN
    PREQUERY=QUERYHIJO
    PREREGISTRO=PRESEHIJO
    REGPAG=12
  POSX=1
  POSY=16
ENDBLOQUE
BEGINBLOQUE=VDRECMAT.PAN
  PADRE=VDRECARTIC.PAN
    PREQUERY=QUERYHIJO
    PREREGISTRO=PRESEHIJO
    REGPAG=10
  POSX=1
  POSY=32
ENDBLOQUE
BEGINBLOQUE=VDRECSTOCK.PAN
  PADRE=VDRECMAT.PAN
    PREQUERY=QUERYHIJO
    PREREGISTRO=PRESEHIJO
    REGPAG=8
  POSX=1
  POSY=46
ENDBLOQUE
