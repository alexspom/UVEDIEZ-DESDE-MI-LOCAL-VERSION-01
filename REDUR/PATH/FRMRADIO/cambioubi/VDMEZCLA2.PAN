MEZCLA DE PALETS
 _10_______ _10_______
MEZCLA DE PALETS
ORIGEN: ______________________
ARTICULO: ____________________
______________________________
______________________________
CANTIDAD @L@@@
    LEA MATRICULA 
      DESTINO
  ____________________
_____ _30___________________________
|

PREQUERY=FEJECUTA("CLIMPIA","","CSELDATOS","","CSELSTOCK","MATRICULA SIN STOCK")
POSTQUERY=FEJECUTA("CMEZCLA","ERROR AL MEZCLAR",
                   "-CVERERROR",":V10ERROR",
                   FCOMMIT,"",
                   FPOSICIONABLOQUE("VDMEZCLA1.PAN"),"")


CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODMATORI,VIRTUAL,NOENTER
CAMPO=CODART,NOENTER
CAMPO=DESART1,NOENTER
CAMPO=DESART2,NOENTER
CAMPO=CANTIDAD,NOENTER
CAMPO=CODMATDEST,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CESNULA",FPOSICIONABLOQUE("VDMEZCLA1.PAN")),"",
                                                    "CELIMINA00", "ERROR AL TRATAR MATRICULA",
                                                    FIF("CSELCODUBI",FIF("-CESUBIMULTI",FFAILURE)),"DEBE INTRODUCIR MATRICULA\nUBICACION MULTIPLE",                                                    
                                                    FIF("-CSELMATRICULA","CCREAMAT"),"MATRICULA NO EXISTE",
                                                    "-CVERIGUAL","ORIGEN Y DESTINO\nNO PUEDEN SER IGUAL",
                                                    "-CHAYMOV","MATRICULA CON MOVIMIENTOS PENDIENTES") 
CAMPO=MCANTIDAD
CAMPO=MDESART
CAMPO=CODUBI,AUXILIAR,OCULTO,"_20____________"  


CURSOR=CCREAMAT DECLARE
                  MIPOSCONTE NUMBER;
                BEGIN
                  IF LENGTH(:CODMATDEST)!=VD.GETPROP('LONMAT') THEN RAISE NO_DATA_FOUND;
				   END IF;
				  SELECT NVL(MAX(POSCONTE),0)+1 INTO MIPOSCONTE FROM VDCONTE WHERE CODUBI='PULMONN1401';
				  INSERT INTO VDCONTE (CODMAT, TIPOCONTE, CNTSSCC, CODUBI, POSCONTE, ALTURACONTE, STATUS, FECENTRADA, HORAENTRADA, FECCREADO, HORACREADO, 
				                       VDEXTRA, CLAVEEXT, CODCOMEN, CODOPEMODIF, FECMODIF, HORAMODIF, PESOCONTE, LARGOCONTE, ANCHOCONTE, ULTSCAN, FECULTSCAN, HORAULTSCAN, CODBAREXT, CODMATEXT)
                            VALUES (:CODMATDEST, 'EUR', NULL, 'PULMONN1401', MIPOSCONTE, 0, 0, VD.FECHASYS, VD.HORASYS, VD.FECHASYS, VD.HORASYS,
        							NULL, NULL, 0, VDUSER.GETUSER, VD.FECHASYS, VD.HORASYS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		         END;@



CURSOR=CHAYMOV1 BEGIN
                 BEGIN
                   SELECT :CODRECURSO INTO :CODRECURSO
                     FROM VDCONTE CNT,VDSTOCK STK
                     WHERE CNT.CODMAT=STK.CODMAT AND STK.CODART NOT IN (SELECT CODART FROM VDSTOCK WHERE CODMAT=:CODMATORI) AND CNT.CODMAT=:CODMATDEST;
                   RAISE TOO_MANY_ROWS;
                   EXCEPTION WHEN NO_DATA_FOUND THEN 
                     BEGIN
                       SELECT :CODRECURSO INTO :CODRECURSO
                        FROM VDMOVIM
                        WHERE STATUS<VDST.FMOVFINALIZADO AND CODMATDEST=:CODMATDEST;
                       RAISE TOO_MANY_ROWS;
                       EXCEPTION WHEN NO_DATA_FOUND THEN NULL;
                     END;
                 END;
               END;@

CURSOR=CVERIGUAL SELECT :CODMATORI FROM DUAL WHERE :CODMATORI=:CODMATDEST;

CURSOR=CLIMPIA SELECT '' CODMATDEST FROM DUAL;

CURSOR=CESNULA SELECT :CODMATDEST FROM DUAL WHERE :CODMATDEST IS NULL;

CURSOR=CSELCODUBI SELECT CODUBI FROM VDUBICA WHERE CODUBI=:CODMATDEST;

CURSOR=CESUBIMULTI SELECT MAX(CODMAT) CODMATDEST FROM VDCONTE WHERE CODUBI=:CODUBI GROUP BY CODUBI HAVING MAX(CODMAT)=MIN(CODMAT);

CURSOR=CSELMATRICULA SELECT CODMAT CODMATDEST FROM VDCONTE WHERE CODMAT=:CODMATDEST;

CURSOR=CSELDATOS SELECT STK.CODART,VD.DIVIDEXBUSQUEDA(1,DESART,' ',30,0) DESART1,VD.DIVIDEXBUSQUEDA(2,DESART,' ',30,0) DESART2,
                        CANTIDAD
                     FROM VDSTOCK STK,VDCONTE CNT,VDARTIC ART
                     WHERE STK.CODMAT=CNT.CODMAT AND  STK.CODART=ART.CODART AND CNT.CODMAT=:CODMATORI
                     ORDER BY ORDENSTK;

CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NOT NULL;                     
                     
CURSOR=CMEZCLA BEGIN
                 VDCLIPKG.MEZCLAMAT(:CODMATORI,:CODMATDEST,:V10ERROR);
               END;@
               
CURSOR=CHAYMOV SELECT :CODRECURSO FROM VDMOVIM WHERE CODMATDEST=:CODMATDEST AND STATUS<VDST.FMOVACTUALIZA AND ROWNUM=1;               


CURSOR=CSELSTOCK SELECT LPAD(STK.CANTIDAD,5,'.') MCANTIDAD,ART.DESART MDESART
                  FROM VDARTIC ART,VDSTOCK STK
                  WHERE STK.CODMAT=:CODMATORI AND ART.CODART=STK.CODART
                  ORDER BY STK.ORDENSTK;
                  
CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMATDEST)=20 THEN SUBSTR(:CODMATDEST,3) ELSE :CODMATDEST END CODMATDEST FROM DUAL;