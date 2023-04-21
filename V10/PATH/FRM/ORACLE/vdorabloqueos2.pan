#
MONITORIZACION  DE SESIONES BLOQUEADAS

Máquina            Programa                         Módulo            Acción              SID  Seg.  
_30_______________ _128____________________________ _48______________ _48______________  @L@@@ @L@@@ _40__________ _40_____________________________
|
                                              
SOLOQUERY
SELECT=SELECT MACHINE, 
       DECODE (SIGN (LENGTH (program) - 40),1, SUBSTR (program, 40),program) PROGRAM,
       C.MODULE,
       C.ACTION,                   
       A.SID SID, 
       serial# serial, 
       ctime tiempo,
       substr(C.SQL_TEXT,1,512) SQLBLOQUEADA,
       DECODE (SIGN (LENGTH (program) - 40),1, SUBSTR (program, 40),program)  PROGRAMA,
       OBJ.OBJECT_NAME,
       (CASE WHEN OBJECT_NAME IS NOT NULL THEN DBMS_ROWID.ROWID_CREATE (1,
                                         B.ROW_WAIT_OBJ#,
                                         B.ROW_WAIT_FILE#,
                                         B.ROW_WAIT_BLOCK#,
                                         B.ROW_WAIT_ROW#) ELSE NULL END)RID
  FROM SYS.V_$LOCK A, SYS.V_$SESSION B, SYS.V_$SQLAREA C,DBA_OBJECTS OBJ
 WHERE A.SID=B.SID AND 
       BLOCK=0 AND 
       A.TYPE IN ('TM', 'TX', 'UL') AND
       B.SQL_ADDRESS=C.ADDRESS AND
       A.ID1= :id1 AND OBJ.OBJECT_ID(+)=B.ROW_WAIT_OBJ# AND
       A.ID2= :id2;
        
CAMPO=MACHINE,TITULO("Máquina")
CAMPO=PROGRAM,AUXILIAR,OCULTO,"_256_____________"
CAMPO=PROGRAMA,TOOLTIP("PROGRAMA=:PROGRAM\nMODULO=:MODULE\nACCION=:ACTION"),TITULO("Programa")
CAMPO=MODULE,TITULO("Módulo")
CAMPO=ACTION,TITULO("Acción")
CAMPO=SID,TITULO("SID")
CAMPO=SERIAL,OCULTO,"@L@@@@@@"
CAMPO=TIEMPO,TITULO("Seg.")
CAMPO=OBJECT_NAME
CAMPO=RID,MIXED
CAMPO=SQLBLOQUEADA,OCULTO,"_512_______________"
CAMPO=ID1,AUXILIAR,VIRTUAL,OCULTO
CAMPO=ID2,AUXILIAR,VIRTUAL,OCULTO
CAMPO=NPANTALLA,AUXILIAR,NOUPDATE,OCULTO,"_100"

CURSOR=CSELPANTALLA SELECT (CASE :OBJECT_NAME 
                             WHEN 'VDBULTOCAB' THEN 'VDBULTOSMA'
                             WHEN 'VDPEDIDOCAB' THEN 'VDPEDIDOS'
                             WHEN 'SMCCPROD' THEN 'VDCCPROD'
                           END) NPANTALLA
                       FROM DUAL
                       WHERE :OBJECT_NAME IS NOT NULL;
                       
CONTEXTUAL=FEJECUTA("@CSELPANTALLA","",FEJECUTAFORM(":NPANTALLA","S","ROWID=:RID"),"")




