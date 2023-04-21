INVENTARIO POR RADIOFRECUENCIA
_10_______ _10______
INVENTARIO

UBICACION: ______________
MATRICULA: __________
______________
_100_______________________________________________________
ARTICULO
___________________________________________________________



|

PREQUERY=FEJECUTA("CLIMPIA","ERROR EN LIMPIA")
                  
POSTQUERY=FEJECUTA(FPOSICIONABLOQUE("SMRINVEN4.PAN"),"NO ME PUEDO POSICIONAR")                  

CURSOR=CLIMPIA BEGIN
                :SCANART:='';
                IF VDUSER.TENGOPRIVILEGIO('JEFEEQUIPO')>0 OR SMINVEN.ESMULTIREF(:CODUBI)=1 THEN
                   IF SMINVEN.ESMULTIREF(:CODUBI)=0 THEN
                      SELECT CODART INTO :CODARTREAL FROM VDSTOCK WHERE CODMAT=:CODMAT;
                     ELSE
                      SELECT CODARTTEORICO,ART.DESART INTO :CODARTREAL,:DESART 
                        FROM VDINVENCONTEO INO,VDARTIC ART
                        WHERE INO.CODARTTEORICO=ART.CODART AND CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                   END IF;
                 ELSE
                   :CODARTREAL:='';
                   :DESART:='';
                END IF;
                EXCEPTION WHEN NO_DATA_FOUND THEN 
                   :CODARTREAL:=NULL;
                   :DESART:=NULL;
               END;@


CAMPO=CODRECURSO,VIRTUAL,NOENTER
CAMPO=CODOPE,VIRTUAL,NOENTER
CAMPO=PINTAUBI,VIRTUAL,NOENTER
CAMPO=CODUBI,VIRTUAL,OCULTO
CAMPO=SOLOUNO,AUXILIAR,VIRTUAL,OCULTO
CAMPO=CODINVEN,VIRTUAL,OCULTO
CAMPO=SEQINVEN,VIRTUAL,OCULTO
CAMPO=CODMAT,VIRTUAL,NOENTER
CAMPO=CODARTREAL,NOENTER
CAMPO=DESART,NOENTER
CAMPO=SCANART,SCAN,AUTOENTER,POSTCHANGE=FEJECUTA("CBORRAART","",
                                                 FIF("CVALIDANULO",
                                                     FIF("CNOESULTIMA",FPOSICIONABLOQUE("SMRINVEN1.PAN"),
                                                                       FPOSICIONABLOQUE("SMRINVENMAS.PAN"))
                                                      ),"",
                                                 "CEXISTEART","\n NO EXISTE ARTICULO",
                                                 "CARTCORRECTO","ARTICULO INCORRECTO",
                                                 FIF("CARTUNIEMB",FPOSICIONABLOQUE("SMRINVENNOEMB.PAN")),"",
                                                 FFUERZASCAN("ART"),"DEBE SCANEAR EL ARTICULO")
CAMPO=CODART,OCULTO,"_20"

CURSOR=CARTUNIEMB SELECT :CODART FROM VDARTIC WHERE UNIEMB=0 AND CODART=:CODART;

CURSOR=CARTCORRECTO SELECT :CODART FROM DUAL WHERE NVL(:CODARTREAL,:CODART)=:CODART OR SMINVEN.ESMULTIREF(:CODUBI)=0;

CURSOR=CNOESULTIMA SELECT :CODRECURSO
                    FROM DUAL 
                    WHERE SMINVEN.ESMULTIREF(:CODUBI)=0 OR SMINVEN.ESULTIMAREF(:CODINVEN,:SEQINVEN)=0;

CURSOR=CVALIDANULO DECLARE
                      CODARTREAL VDARTIC.CODART%TYPE;
                   BEGIN
                           IF :SCANART='0000' THEN
                              UPDATE VDINVENCONTEO SET STATUS=DECODE(SMINVEN.ESMULTIREF(:CODUBI),1,350,300),CODOPE=:CODOPE,FECFIN=VD.FECHASYS,HORAFIN=VD.HORASYS,
                                                       CODARTREAL=CODARTTEORICO,CANTREAL=0
                                WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN;
                               COMMIT;
                               RETURN;
                            END IF;
                     SELECT CODART INTO CODARTREAL FROM VDSTOCK WHERE CODMAT=:CODMAT AND CODART=(SELECT NVL(CODARTTEORICO,:CODART) FROM VDINVENCONTEO WHERE CODINVEN=:CODINVEN AND SEQINVEN=:SEQINVEN);
                     RAISE TOO_MANY_ROWS;
                   END;@
                                                      

CURSOR=CBORRAART SELECT '' CODART FROM DUAL;
                               

CURSOR=CVERERROR SELECT :V10ERROR FROM DUAL WHERE :V10ERROR IS NULL;       

CURSOR=CEXISTEART SELECT CODART FROM VDARTIC WHERE (CODART=VDART.DAMEART(:SCANART) OR CODART=VDART.DAMEART('0'||:SCANART));
                  
CURSOR=CCOMPRUEBAART SELECT :CODART
                      FROM VDSTOCK 
                      WHERE CODMAT=:CODMAT AND CODART=:CODART
                     UNION
                     SELECT :CODART
                       FROM VDUBICA
                      WHERE CODUBI=:CODUBI AND CODART=:CODART;                                                             
                                                   
