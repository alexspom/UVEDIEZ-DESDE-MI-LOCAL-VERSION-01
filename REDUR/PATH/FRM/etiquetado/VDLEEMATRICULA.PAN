###################################################################
#Módulo: VDLEEMATRICULA.PAN
#Funcionalidad : LEctura de matricula de contenedor
#Autor: JMM 
#Fecha: 19-09-2008
###################################################################
# Histórico de cambios:
#
LECTURA DE PALETA 
Matricula:     _20_________________

|

TABLA=DUAL
NOINSERT
NODELETE
NOUPDATE
NOCOMMIT

CAMPO=CODMATLEIDO,AUXILIAR,POSTCHANGE=FEJECUTA("CELIMINA00", "ERROR AL TRATAR LECTURA",
                                               "CSELCNT","MATRICULA NO ASOCIADA A BULTO\nPENDIENTE DE ETIQUETAR",
                                               PRESEHIJO,"",
                                               FPULSATECLAS("F6"),"")

CURSOR=CELIMINA00 SELECT CASE WHEN LENGTH(:CODMATLEIDO)=20 AND :CODMATLEIDO LIKE '00%' THEN SUBSTR(:CODMATLEIDO,3) ELSE :CODMATLEIDO END CODMATLEIDO FROM DUAL;

CURSOR=CSELCNT SELECT :CODMATLEIDO FROM VDBULTOCAB WHERE STATUS IN (VDST.FBUCPREPARADO, VDST.FBUCAETIQUETAR) AND TIPOBULTO='C' AND CODBULTO IN 
               (SELECT CODBULTO FROM VDBULTOLIN BUL, VDMOVIM MOV WHERE MOV.CODMATORI = :CODMATLEIDO AND MOV.CODMOV = BUL.CODMOV);

				  
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
                             :CODMATLEIDO:=MITEXTO;
                         END IF;
                         COMMIT;
                     ELSE 
                      :V10EVAJAX:=-1;
                     END IF; 
                     EXCEPTION WHEN OTHERS THEN NULL;
                    END;@ 
                        
AJAX(SCANNER,"","C","","CSELLECTURA","CODMATLEIDO",50)


