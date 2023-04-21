INVENTARIO POR RADIOFRECUENCIA
_12_______ _12______
INVENTARIO

UBICACION: ___________________
           ___________________

 

|

PREQUERY=FEJECUTA("CSELTIPO","",
                  "CLIMPIA","ERROR EN LIMPIA",
                  FIF("-CDAMEINVEN",FEJECUTA(FPOSICIONABLOQUE("-1"),"ERROR AL POSICIONAR")),"NO ME PUEDO POSICIONAR",
                  FCOMMIT,"")
                  
POSTQUERY=FEJECUTA("CVERIFICAUBI","  UBICACION ERRONEA", 
                   "CTOMAFOTO","ERROR EN FOTO",
                   FCOMMIT,"",
                   "CVERERROR",":V10ERROR",
                   FIF("CESMATVIRT",FPOSICIONABLOQUE("SMRINVEN3.PAN"),FPOSICIONABLOQUE("SMRINVEN2.PAN")),"NO ME PUEDO POSICIONAR")                  

CURSOR=CTOMAFOTO UPDATE VDINVENCONTEO ICO 
                     SET (CODMAT,CODARTTEORICO,CANTTEORICO)=(SELECT * FROM 
                                                                (SELECT CNT.CODMAT,CODART,NVL(SUM(CANTIDAD),0)
                                                                     FROM VDSTOCK STK,VDCONTE CNT
                                                                     WHERE CNT.CODMAT=STK.CODMAT AND CNT.CODUBI=ICO.CODUBI
                                                                     GROUP BY CNT.CODMAT,CODART
                                                                     ORDER BY DECODE(CNT.CODMAT,ICO.CODMAT,0,1))
                                                              WHERE ROWNUM=1
                                                             )
                                                    WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;                   
                   
CURSOR=CLIMPIA BEGIN
                SELECT '' INTO :CODUBILEE FROM DUAL;
                UPDATE VDRECURSO SET CODMAT='' WHERE CODRECURSO=:CODRECURSO;
               END;@

CURSOR=CDAMEINVEN BEGIN
                   IF :SOLOUNO=1 THEN
                       SELECT :SOLOUNO INTO :SOLOUNO FROM VDINVENCONTEO WHERE STATUS=200 AND CODRECURSO=:CODRECURSO;
                    END IF;
                   :CODUBI:=SMINVEN.DAMEINVEN(:CODRECURSO,:CODINVEN,:SEQINVEN,:SOLOUNO);
                   IF :CODUBI IS NULL THEN RAISE NO_DATA_FOUND;
                    END IF;
                   :PINTAUBI:=VDCLIPKG.PINTAUBICA(:CODUBI);
                  END;@
                  
CURSOR=CESMATVIRT DECLARE
                   CUANTAS NUMBER;
                  BEGIN
                    SELECT COUNT(*) INTO CUANTAS FROM VDCONTE WHERE CODUBI=:CODUBI;
                    IF CUANTAS>1 THEN 
                       :CODMAT:=VDUBI.DAMECODMATUBI(:CODUBI);
                       RETURN;
                    END IF;
                    SELECT CODUBI INTO :CODUBI FROM VDUBICA WHERE CODUBI=:CODUBI AND CODAREA IN ('PU','SRP','RPPU');                  
                    :CODMAT:=VDUBI.DAMECODMATUBI(:CODUBI);
                  END;@
                  
CURSOR=CESUBINULA SELECT :CODUBILEE FROM DUAL WHERE :CODUBILEE IS NULL;                  
                  

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODINVEN,OCULTO,"@L@@@@@"
CAMPO=SEQINVEN,OCULTO,"@L@@@@@"
CAMPO=SOLOUNO,VIRTUAL,OCULTO
CAMPO=CODUBI,AUXILIAR,OCULTO,"_20"
CAMPO=PINTAUBI,NOENTER
CAMPO=CODUBILEE,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CESUBINULA",FPOSICIONABLOQUE("-1")),"",
                                                   "CVERIFICAUBI","  UBICACION ERRONEA",                                     
                                                   FFUERZASCAN("UBI"),"   DEBE SCANNEAR UBICACION")
CAMPO=CODMAT,OCULTO,"_20__________"
                                                   
                               
CURSOR=CVERIFICAUBI BEGIN
                   IF :CODUBILEE!=:CODUBI THEN 
                      :V10ERROR:='UBICACION INCORRECTA';
                     ELSE
                      :V10ERROR:='';
                   END IF;
                 END;@    
                 
CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL;            
                      
