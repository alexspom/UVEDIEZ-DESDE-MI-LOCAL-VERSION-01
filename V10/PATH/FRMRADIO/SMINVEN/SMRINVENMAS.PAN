INVENTARIO POR RADIOFRECUENCIA
_10_______ _10______
INVENTARIO
UBICACION: ________________
MATRICULA: ________________
HAY MAS ARTICULOS
_


|


                  

CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=CODINVEN,VIRTUAL,OCULTO
CAMPO=SEQINVEN,VIRTUAL,OCULTO
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=SOLOUNO,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODUBI,VIRTUAL,OCULTO
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=HAYMAS,POSTCHANGE=FEJECUTA(FIF("CSI",FEJECUTA("CREANUEVOCONTEO","NO PUEDO CREAR CONTEO",
                                                    FCOMMIT,"",
                                                    "+CDAMEINVEN","",
                                                    FPOSICIONABLOQUE(":NPANTALLA"),"NO ME PUEDO POSICIONAR"),
                                           FEJECUTA("CTERMINAUBI","NO PUEDO TERMINAR CONTEOS",
                                                    FCOMMIT,"",
                                                    FPOSICIONABLOQUE("SMRINVEN1.PAN"),"")
                                    ),""
                                )
CAMPO=NPANTALLA,AUXILIAR,OCULTO,"_1000"
                                           
CURSOR=CSI SELECT :HAYMAS FROM DUAL WHERE :HAYMAS='S';

CURSOR=CREANUEVOCONTEO DECLARE
                        MICONTEO VDINVENCONTEO%ROWTYPE;
                      BEGIN
                        SELECT * INTO MICONTEO FROM VDINVENCONTEO WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                        SELECT MAX(SEQINVEN)+1 INTO MICONTEO.SEQINVEN FROM VDINVENCONTEO WHERE CODINVEN=:CODINVEN;
                        MICONTEO.CODARTTEORICO:='';MICONTEO.CODARTREAL:='';MICONTEO.CANTREAL:=0;MICONTEO.STATUS:=200;
                        INSERT INTO VDINVENCONTEO VALUES MICONTEO;
                      END;@
                      
CURSOR=CTERMINAUBI UPDATE VDINVENCONTEO SET STATUS=300 WHERE STATUS=350 AND CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                 
CURSOR=CDAMEINVEN DECLARE
                    MICODUBI VDUBICA.CODUBI%TYPE;
                    MICODMAT VDCONTE.CODMAT%TYPE;
                  BEGIN
                   :NPANTALLA:='-1';
                   IF :SOLOUNO=1 THEN RETURN;
                    END IF;
                    :NPANTALLA:='SMRINVEN1.PAN';
                   MICODUBI:=SMINVEN.DAMEINVEN(:CODRECURSO,:CODINVEN,:SEQINVEN,:SOLOUNO);
                   IF MICODUBI IS NULL THEN 
                     :NPANTALLA:='-1';
                     RETURN;
                    END IF;
                   SELECT CODMAT INTO MICODMAT FROM VDINVENCONTEO WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                   IF MICODUBI=:CODUBI THEN 
                      :NPANTALLA:='SMRINVEN2.PAN';
                     END IF;
                   IF MICODMAT=:CODMAT THEN 
                      :NPANTALLA:='SMRINVEN3.PAN';
                    END IF;
                  END;@
                                         

