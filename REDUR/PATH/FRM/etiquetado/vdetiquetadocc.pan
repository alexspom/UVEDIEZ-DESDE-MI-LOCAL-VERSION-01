LECTURA DE MATRICULA
Matricula:     _20_________________

|

TABLA=DUAL
NOINSERT
NODELETE
NOUPDATE
NOCOMMIT
NOUPDATE,PROTECT("SUPERVISOR")



CAMPO=CNTSSCC,AUXILIAR,POSTCHANGE=FEJECUTA("CELIMINA00", "ERROR AL TRATAR LECTURA",
                                           "+CSELCNTSSCC","MATRICULA NO ASOCIADA A BULTOS\nPENDIENTES DE ETIQUETAR",
                                           PRESEHIJO,"",
                                           FPULSATECLAS("F6"),"")

                  
CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CNTSSCC)=20 AND :CNTSSCC LIKE '00%' THEN SUBSTR(:CNTSSCC,3) ELSE :CNTSSCC END CNTSSCC FROM DUAL;

CURSOR=CSELCNTSSCC SELECT CNTSSCC FROM VDBULTOCAB WHERE CNTSSCC=:CNTSSCC AND TIPOBULTO='E' AND STATUS=VDST.FBUCAETIQUETAR;
				  
CURSOR=CSELLECTURA DECLARE 
                   MITEXTO VARCHAR2(1024); 
                   MIROWIDSCAN VARCHAR2(1024);  
                    BEGIN
                     :V10EVAJAX:=-1;
                     SELECT NVL(LTRIM(TEXTO,'0'),'0'),ROWID INTO MITEXTO,MIROWIDSCAN FROM VDSCANLECT 
                     WHERE MIROWIDSCAN IS NULL AND (REDSCAN, SCANNER) IN
                           (SELECT ORD.IDINFOLECTURA, ORD.SCANNER
                               FROM VDORDENADORES ORD
                                 WHERE ORD.ORDENADOR =VDUSER.GETHOSTNAME)
                        AND ROWNUM=1;
                     IF MITEXTO IS NOT NULL THEN
                         DELETE VDSCANLECT WHERE ROWID=MIROWIDSCAN; 
                         IF :MIROWID IS NULL THEN  
                             :V10EVAJAX:=3000;
                             :CNTSSCC:=MITEXTO;
                         END IF;
                         COMMIT;
                     ELSE 
                      :V10EVAJAX:=-1;
                     END IF; 
                     EXCEPTION WHEN NO_DATA_FOUND THEN NULL;
                    END;@ 
                        
AJAX(SCANNER,"","C","","CSELLECTURA","CNTSSCC",100)
