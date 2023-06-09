######
# VDUCABIENTRADASCARRO2.PAN 
# 
# Prop�sito: UBICACION DE ART�CULOS DE CARRO
#               
#           
# Autor	   : CGG
# Fecha    : 16-07-2015
####
# Modificaciones:
####
# 
  UBICACI�N DE ART�CULO
  ________ ________________ 
  
 MATR�CULA: _18_______________ 
 QUEDAN: @@@@@
 
 ART:  _40___________________
       _40_____________________________
 LOTE: _20___________________

 CANTIDAD: @@@@@@@
 
 LEA ART�CULO-LOTE
 ART:  _255____________________________________________________________________________________________________________
 LOTE: _255____________________________________________________________________________________________________________
  
 UBI: _12__________ 
      _12__________
 X: VOLVER    S: SIGUIENTE
              M: MANUAL
|

PREQUERY=FEJECUTA("CLIMPIAR","ERROR LIMPIANDO DATOS",
                  "CSELCODUBIDEST","\nNO SE ENCUENTRAN\nART�CULOS QUE UBICAR",
                  "CSELQUEDAN","\nERROR CALCULANDO RESTANTES",
                  FPOSICIONACAMPO(FSUCCESS,"CODART"),"")

POSTQUERY=FEJECUTA(FIF("CSALIR",FEJECUTA("CANULAMOVS","ERROR ANULANDO MOVIMIENTOS",
                                         "CACTCARRO","\nERROR ACTUALIZANDO\nSTATUS DE CONTENEDOR",
										 FCOMMIT,"",
                                         FPOSICIONABLOQUE("VDUBICAENTRADASCARRO1.PAN"),"ERROR SALIENDO DE PANTALLA")),"",
                   FIF("CSIGUIENTE",FEJECUTA("CANULAMOVACTUAL","ERROR ANULANDO MOVIMIENTO :CODMOV"),
                                    FEJECUTA("CSELNOTNULLART","ERROR, INFORME ART�CULO\n\nPARA VOLVER ATRAS PULSE 'X'",
#                                             "CSELNOTNULLLOT","ERROR, INFORME LOTE\n\nPARA VOLVER ATRAS PULSE 'X'",
                                             "CSELNOTNULLUBI","ERROR, INFORME UBICACI�N\n\nPARA VOLVER ATRAS PULSE 'X'",
                                             "CVERIFART","ERROR\n ART�CULO INCORRECTO",
#                                             "CVERIFLOT","ERROR\n LOTE INCORRECTO",
                                             FIF("CMANUAL",FPOSICIONABLOQUE("VDREUBIMANUCARRO.PAN"), FEJECUTA("CVERIFUBI","ERROR\nUBICACI�N INCORRECTA","CUPDMOV","\nERROR ACTUALIZANDO MOVIMIENTO")),"ERROR CARGANDO BLOQUE VDREUBIMANUCARRO"
                                             
                                             )),"ERROR EN FIF",
                   FCOMMIT,"",
                   "CLIMPIAR","ERROR LIMPIANDO DATOS",
                   "CSELQUEDAN","\nERROR CALCULANDO RESTANTES",
                   FPOSICIONACAMPO(FSUCCESS,"CODART"),"",
                   FIF("CSELCODUBIDEST",FSUCCESS,
                                        FEJECUTA("CACTCARRO","\nERROR ACTUALIZANDO\nSTATUS DE CONTENEDOR",
                                                 FCOMMIT,"",
                                                 %FFAILURE,"\nNO SE ENCUENTRAN M�S\nART�CULOS QUE UBICAR",
                                                 FPOSICIONABLOQUE("VDUBICAENTRADASCARRO1.PAN"),"")),"")
  
CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL 
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=QUEDAN,AUXILIAR,NOENTER
CAMPO=CODARTDEST,NOENTER
CAMPO=DESARTDEST,NOENTER,AUXILIAR
CAMPO=CODLOTDEST,NOENTER
CAMPO=CANTIDADDEST,NOENTER
#CAMPO=CODART,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FFUERZASCAN("ART"),"DEBE SCANEAR ARTICULO")
CAMPO=CODBARRAS1,SCAN,POSTCHANGE=FDESIGNACION(+FLEEARTICULO("CODBARRAS1", "CODART",""),"ERROR :V10ERROR",
                                              +FANALIZAEANRAD("CODBARRAS1", "37","UNIEMB","17", "CADUCI","10","CODLOT"),"\nERROR,\nEN LECTURA DEL\nCODIGO DE BARRAS") 
CAMPO=CODBARRAS2,SCAN,POSTCHANGE=FDESIGNACION(+FLEEARTICULO("CODBARRAS2", "CODART",""),"ERROR :V10ERROR",
                                              +FANALIZAEANRAD("CODBARRAS2", "37","UNIEMB","17", "CADUCI","10","CODLOT"),"\nERROR,\nEN LECTURA DEL\nCODIGO DE BARRAS") 

CAMPO=CODART,AUXILIAR,OCULTO,"_40_"
CAMPO=CODLOT,AUXILIAR,OCULTO,"_20_"
CAMPO=CADUCI,AUXILIAR,OCULTO,"_8_"
CAMPO=UNIEMB,AUXILIAR,OCULTO,"#L############"
CAMPO=CODUBIDEST,NOENTER
CAMPO=CODUBI,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CSALIR",FEJECUTA("CANULAMOVS","ERROR ANULANDO MOVIMIENTOS",
                                                                      "CACTCARRO","\nERROR ACTUALIZANDO\nSTATUS DE CONTENEDOR",
																	  FCOMMIT,"",
                                                                      FPOSICIONABLOQUE("VDUBICAENTRADASCARRO1.PAN"),"ERROR SALIENDO DE PANTALLA")),"",
                                                FIF("CSELNOTNULLUBI",FIF("CMANUAL",FSUCCESS,FFUERZASCAN("UBI"))),"DEBE SCANEAR UBICACION")
CAMPO=CODMOV,AUXILIAR,OCULTO,"@L@@@@@@@@"
#CAMPO=MENSAJE,VIRTUAL,OCULTO
CAMPO=DUMMY,OCULTO,"_"

CURSOR=CANULAMOVACTUAL UPDATE VDMOVIM SET STATUS=7000 WHERE CODMOV=:CODMOV;
CURSOR=CANULAMOVS UPDATE VDMOVIM
                  SET STATUS = 7000
				  WHERE CODMATORI = :CODMAT
			      AND STATUS = 2000
			      AND CODCONCE = 'RECEP'
			      AND CODRECURSO = :CODRECURSO;

CURSOR=CLIMPIAR SELECT '' CODBARRAS1, '' CODBARRAS2, '' CODUBI FROM DUAL;

CURSOR=CSELCODUBIDEST SELECT M.CODUBIDEST, M.CODART CODARTDEST, M.CODMOV, M.CODLOT CODLOTDEST, A.DESART DESARTDEST, M.CANTIDAD CANTIDADDEST
                      FROM VDMOVIM M, VDUBICA B, VDARTIC A
                      WHERE M.CODART = A.CODART
                      AND M.CODUBIDEST = B.CODUBI
                      AND CODMATORI = :CODMAT
                      AND STATUS = 2000
                      AND CODCONCE = 'RECEP'
                      AND CODRECURSO = :CODRECURSO 
					  ORDER BY M.PRIOMOV ASC,B.ORDENENTRADA ; 
                      
CURSOR=CSELQUEDAN SELECT COUNT(*) QUEDAN
                      FROM VDMOVIM M
                      WHERE CODMATORI = :CODMAT
                      AND STATUS BETWEEN 1100 AND 2000
                      AND CODCONCE = 'RECEP'
                      AND CODRECURSO = :CODRECURSO; 
                      
CURSOR=CSALIR SELECT 'X' DUMMY FROM DUAL WHERE :CODBARRAS1='X' OR :CODBARRAS2='X' OR :CODUBI='X';
CURSOR=CMANUAL SELECT 'X' DUMMY FROM DUAL WHERE :CODUBI='M';
CURSOR=CSIGUIENTE SELECT 'X' DUMMY FROM DUAL WHERE :CODBARRAS1='S' OR :CODBARRAS2='S' OR :CODUBI='S';

CURSOR=CSELNOTNULLART SELECT 'X' DUMMY FROM DUAL WHERE :CODBARRAS1 IS NOT NULL;
CURSOR=CSELNOTNULLLOT SELECT 'X' DUMMY FROM DUAL WHERE :CODBARRAS2 IS NOT NULL;
CURSOR=CSELNOTNULLUBI SELECT 'X' DUMMY FROM DUAL WHERE :CODUBI IS NOT NULL;

CURSOR=CVERIFART SELECT 'X' DUMMY FROM DUAL WHERE :CODART = :CODARTDEST;
CURSOR=CVERIFLOT SELECT 'X' DUMMY FROM DUAL WHERE :CODLOT = :CODLOTDEST;
CURSOR=CVERIFUBI SELECT 'X' DUMMY FROM DUAL WHERE :CODUBI = :CODUBIDEST;

CURSOR=CACTCARRO UPDATE VDCONTE SET STATUS = 0 WHERE CODMAT=:CODMAT;

CURSOR=CUPDMOV UPDATE VDMOVIM SET STATUS=2300 WHERE CODMOV=:CODMOV;
