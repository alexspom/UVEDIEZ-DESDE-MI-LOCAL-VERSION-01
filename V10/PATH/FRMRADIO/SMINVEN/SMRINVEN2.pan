INVENTARIO POR RADIOFRECUENCIA
_10_______ _10______
INVENTARIO

UBI: ____________________
     ____________________
	 
MAT: ____________________



|

PREQUERY=FEJECUTA("+CLIMPIA","ERROR EN LIMPIA")
                  
POSTQUERY=FEJECUTA(FPOSICIONABLOQUE(":SIGPANTALLA"),"NO ME PUEDO POSICIONAR")                  

CURSOR=CLIMPIA BEGIN
                :CODMAT:='';
                IF VDUSER.TENGOPRIVILEGIO('JEFEEQUIPO')>0 OR SMINVEN.ESMULTIREF(:CODUBI)=1 THEN
                   SELECT CODMAT INTO :CODMATREAL FROM VDCONTE WHERE CODUBI=:CODUBI AND ROWNUM=1;
                 ELSE
                   :CODMATREAL:='';
                END IF;
                EXCEPTION WHEN NO_DATA_FOUND THEN NULL;
               END;@


CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODINVEN,VIRTUAL,OCULTO
CAMPO=SOLOUNO,AUXILIAR,VIRTUAL,OCULTO
CAMPO=SEQINVEN,VIRTUAL,OCULTO
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODUBI,VIRTUAL,OCULTO
CAMPO=CODMATREAL,NOENTER
CAMPO=CODMAT,VIRTUAL,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA(FIF("CVERNULA",FEJECUTA(FCOMMIT,"",FPOSICIONABLOQUE("SMRINVEN1.PAN"),"")),"",
                                                        FFUERZASCAN("MAT"),"DEBE SCANNEAR MATRICULA",
														"CELIMINA00", "ERROR AL TRATAR MATRICULA",
                                                        "CVERMAT","MATRICULA ERRONEA",
                                                        "CSELPANTALLA","PANTALLA ERRONEA", 
                                                        "CVERERROR",":V10ERROR")
CAMPO=SIGPANTALLA,AUXILIAR,OCULTO,"_255"


CURSOR=CSELPANTALLA SELECT 'SMRINVEN3.PAN' SIGPANTALLA FROM DUAL; 

CURSOR=CVERMAT SELECT :CODMAT FROM DUAL WHERE :CODMAT=:CODMATREAL OR SMINVEN.ESMULTIREF(:CODUBI)=0;

CURSOR=CVERNULA BEGIN
                  IF :CODMAT='0000' THEN                                                  
                     UPDATE VDINVENCONTEO SET STATUS=300,CODOPE=:CODOPE,FECFIN=VD.FECHASYS,HORAFIN=VD.HORASYS,
                                                       CODARTREAL='',CANTREAL=0
                                WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                   ELSE
                     RAISE NO_DATA_FOUND;
                   END IF;
                 END;@
                                                   
CURSOR=CVERIFMAT DECLARE
                  UBIMAT VDUBICA.CODUBI%TYPE;
                  CODMATR VDCONTE.CODMAT%TYPE;
                 BEGIN
                   BEGIN
                      SELECT CODMAT INTO CODMATR FROM VDCONTE WHERE CODUBI=:CODUBI;
                      EXCEPTION WHEN NO_DATA_FOUND THEN
                        IF :CODMAT IS NULL THEN
                           UPDATE VDINVENCONTEO SET STATUS=500,CODOPE=:CODOPE,FECFIN=VD.FECHASYS,HORAFIN=VD.HORASYS,CODARTREAL='-' 
                              WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                           COMMIT;
                           :SIGPANTALLA:='SMRINVEN1.PAN';
                           RETURN;
                         END IF;
                   END;
                  :SIGPANTALLA:='SMRINVEN3.PAN';
                  SELECT CODUBI INTO UBIMAT FROM VDCONTE WHERE CODMAT=:CODMAT;
                  IF UBIMAT!=:CODUBI THEN 
                     :V10ERROR:='MATRICULA '||:CODMAT||'\nDEBE ESTAR EN UBICACION '||UBIMAT;
                   ELSE
                     :V10ERROR:='';
                  END IF;
                  EXCEPTION WHEN NO_DATA_FOUND THEN BEGIN
                      SELECT CODUBI INTO :CODUBI FROM VDCONTE WHERE CODUBI=:CODUBI;
                      :V10ERROR:='UBICACION OCUPADA CON OTRA MATRICULA';
                      EXCEPTION WHEN NO_DATA_FOUND THEN :V10ERROR:='';
                  END;
                 END;@

CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL;                                                   
                                                   
CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMAT)=20 AND :CODMAT LIKE '00%' THEN SUBSTR(:CODMAT,3) ELSE :CODMAT END CODMAT FROM DUAL;
