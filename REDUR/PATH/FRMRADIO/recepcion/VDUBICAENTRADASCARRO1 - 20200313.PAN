######
# VDUCABIENTRADASCARRO1.PAN 
# 
# Propósito: UBICACION DE ARTÍCULOS DE CARRO
#               
#           
# Autor	   : CGG
# Fecha    : 16-07-2015
####
# Modificaciones:
####
# 
UBICACION DE CONTENEDORES
________ ________________ 

UBICACIÓN DE CARRO

 MATRICULA: _18_______________
|

PREQUERY=FEJECUTA("CLIMPIAR","ERROR LIMPIANDO DATOS")

POSTQUERY=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM("")),"ERROR COMPROBANDO VALORES NULOS",
                   "CSELCODMAT","\nERROR. CARRO VACIO",
				   "-CHAYMOVS","EL TERMINAL :TERMINAL\nTIENE MOVIMIENTOS PENDIENTES",
                   FIF("-CSELMOVFIN",FEJECUTA("CCREAMOVIM","ERROR CREANDO MOVIMIENTOS",
                                              FCOMMIT,"",
                                              FIF("CCOMPRUEBAMOV",FFAILURE),"ERROR COMPROBANDO MOVIMIENTOS\n:MENSAJE",
                                              "CACTUALIZACONTE","ERROR ACTUALIZANDO CONTENEDOR",
                                              FCOMMIT,"",
                                              "CCOMPRUEBAMOV2","ERROR COMPROBANDO\nCREACION DE MOVIMIENTOS",
                                              FIF("CCOMPRUEBAMOV",FFAILURE),"TIMEOUT\nCOMPROBANDO MOVIMIENTOS")),"",
                   FIF("CSELMOVFIN",FSUCCESS,FIF("CSELMOVPROC",FEJECUTA(FFAILURE,"MOVIMIENTOS\nEN TRAMITACIÓN\nINTÉNTELO MÁS TARDE"),
                                                               FEJECUTA(FFAILURE,"NO SE ENCUENTRAN\nMOVIMIENTOS QUE UBICAR"))),"",
                   FPOSICIONABLOQUE("VDUBICAENTRADASCARRO2.PAN"),"ERROR CARGANDO BLOQUE VDUBICAENTRADASCARRO2.PAN")




CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL

CAMPO=CODMAT,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CSELNOTNULL",FCARGAFORM("")),"ERROR COMPROBANDO VALORES NULOS",FFUERZASCAN("MAT"),"\nDEBE SCANEAR MATRICULA")
CAMPO=TERMINAL,OCULTO,"_50"
CAMPO=MENSAJE,OCULTO,"_256_"
CAMPO=DUMMY,OCULTO,"_"
CAMPO=SALIDA,OCULTO,"@"

CURSOR=CANULAMOVS UPDATE VDMOVIM
                  SET STATUS = 7000
				  WHERE CODMATORI = :CODMAT
			      AND STATUS = 2000
			      AND CODCONCE = 'RECEP'
			      AND CODRECURSO = :CODRECURSO;

CURSOR=CHAYMOVS SELECT CODRECURSO TERMINAL
                FROM VDMOVIM
                WHERE CODMATORI = :CODMAT
                AND STATUS = 2000
                AND CODCONCE = 'RECEP'
                AND ROWNUM = 1
				AND CODRECURSO <> :CODRECURSO;			

CURSOR=CLIMPIAR SELECT '' CODMAT,'' MENSAJE FROM DUAL;

CURSOR=CSELNOTNULL SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NULL;

CURSOR=CSELCODMAT SELECT 'X' DUMMY
                  FROM VDTIPOCONTE TCO,VDUBICA UBI,VDCONTE CNT 
                  WHERE CNT.CODMAT=:CODMAT 
                  AND TCO.TIPOCONTE=CNT.TIPOCONTE 
                  AND MOVIBLE='S' 
                  AND CNT.CODUBI=UBI.CODUBI;

CURSOR=CSELCREAMOV SELECT 'X' DUMMY FROM VDCONTE WHERE CODMAT=:CODMAT AND NVL(STATUS,0) <> 0;

CURSOR=CCREAMOVIM BEGIN
                     :SALIDA := RDRUBICA.REUBICACONTE(:CODMAT,:CODRECURSO,:MENSAJE); 
                  END;@
                  
CURSOR=CCOMPRUEBAMOV SELECT 1 SALIDA FROM DUAL WHERE :SALIDA <> 0;

CURSOR=CACTUALIZACONTE UPDATE VDCONTE SET STATUS = 200 WHERE CODMAT=:CODMAT;

CURSOR=CSELMOVFIN SELECT 'X' DUMMY
                  FROM VDMOVIM
                  WHERE CODMATORI = :CODMAT
                  AND STATUS = 2000
                  AND CODCONCE = 'RECEP'
                  AND CODRECURSO = :CODRECURSO
                  AND ROWNUM = 1;
                  
CURSOR=CSELMOVPROC SELECT 'X' DUMMY
                   FROM VDMOVIM
                   WHERE CODMATORI = :CODMAT
                   AND STATUS >= 1100
                   AND STATUS < 2000
                   AND CODCONCE = 'RECEP'
                   AND CODRECURSO = :CODRECURSO
                   AND ROWNUM = 1;

#Se buscan los movimientos hasta que el enrutador los trate

CURSOR=CCOMPRUEBAMOV2 DECLARE
                          I NUMBER := 1;
                      BEGIN
                          :SALIDA := 1;
                          LOOP
                              DBMS_LOCK.SLEEP(1);
                              
                              BEGIN
                                  SELECT 1
                                  INTO :SALIDA
                                  FROM VDMOVIM
                                  WHERE CODMATORI = :CODMAT
                                  AND STATUS >= 1100
                                  AND STATUS < 2000
                                  AND CODCONCE = 'RECEP'
                                  AND CODRECURSO = :CODRECURSO
                                  AND ROWNUM = 1;
                              EXCEPTION
                                  WHEN NO_DATA_FOUND THEN
                                      :SALIDA := 0;
                              END;
                              
                              EXIT WHEN I = 10 OR :SALIDA = 0;
                              I := I + 1;
                          END LOOP;
                      END;@