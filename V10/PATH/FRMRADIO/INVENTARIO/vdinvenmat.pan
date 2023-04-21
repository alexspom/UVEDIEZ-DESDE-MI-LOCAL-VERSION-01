#
# VDINVENMAT.PAN
#
INVENTARIO
__________ __________

##### - ________________________________

LEA LA MATRICULA
 _18_______________
 _18_______________
 
|

PREQUERY=FEJECUTA("CINICIALIZA","",
                  FIF("CSELCODMAT", FEJECUTA(FIF("-CSELCODMAT2", FPOSICIONABLOQUE("VDINVENUBI.PAN")),"")),"",
                  "CUPDINVEN", "ERROR ACTUALIZANDO INVENTARIO",
                  FCOMMIT,"")

CAMPO=CODRECURSO,NOENTER,VIRTUAL
CAMPO=CODOPE,NOENTER,VIRTUAL
CAMPO=CODINVEN,NOENTER,VIRTUAL
CAMPO=DESINVEN,NOENTER,VIRTUAL
CAMPO=CODMAT,NOENTER
CAMPO=CODMATLEIDA,SCAN,POSTCHANGE=FDESIGNACION(FIF("CSELNOTNULL", FEJECUTA(FIF("CSELFININVL", FEJECUTA(FIF("CSELFININVL2", FEJECUTA("CUPDFININVENLIN", "ERROR ACTUALIZANDO VDINVENLIN",
                                                                                                                                    FCOMMIT,"")),"")),"",
                                                                           FPOSICIONABLOQUE("VDINVENUBI.PAN"), "")),"",
                                               "CACTCODMAT", "",
                                               FIF("CCODMATINVEN", FEJECUTA("CCODMATINVEN2", "MATRICULA :CODMATLEIDA\nYA INVENTARIADA")),"",                                                                   
                                               FIF("CVALCODMAT", FEJECUTA(FIF("-CVALCODMAT2", FEJECUTA(%FFAILURE, "ERROR,\nMATRICULA LEIDA INCORRECTA")),"")),"",
                                               FIF("CUBIMAT",FEJECUTA(FIF("CTIENEPRIV", FEJECUTA(FPOSICIONABLOQUE("VDINVENDISTUBI.PAN"),""),
                                                                                        FEJECUTA(FFAILURE,"LA MATRICULA NO SE\nENCUENTRA EN\nESTA UBICACION, LEA OTRA")),""),
                                                             FEJECUTA(FPOSICIONABLOQUE("VDINVENART.PAN"),"")),"")
CAMPO=CODUBI,OCULTO,VIRTUAL
CAMPO=FECINI,OCULTO,VIRTUAL
CAMPO=HORAINI,OCULTO,VIRTUAL
CAMPO=STATUS,OCULTO,"#####"
CAMPO=CODOPEANT,OCULTO,"_20____________"
CAMPO=CODUBITEORICA,OCULTO,"_12__________"
                     
CURSOR=CINICIALIZA SELECT '' CODMAT, '' CODMATLEIDA FROM DUAL;

CURSOR=CSELNOTNULL SELECT :CODMATLEIDA FROM DUAL WHERE :CODMATLEIDA IS NULL;

#Si ya se ha hecho un conteo válido de la matrícula o ha llegado, se finaliza el inventario.                                  
CURSOR=CSELFININVL SELECT STATUS
                     FROM VDINVENCONTEO
                    WHERE CODINVEN = :CODINVEN
                      AND CODUBI   = :CODUBI
                    ORDER BY DECODE(STATUS,VDST.FINONOOK,1,VDST.FINOSRECONTEO,1,2);

CURSOR=CSELFININVL2 SELECT :STATUS FROM DUAL WHERE :STATUS NOT IN (VDST.FINONOOK,VDST.FINOSRECONTEO);

CURSOR=CUPDFININVENLIN UPDATE VDINVENLIN
                          SET STATUS      = VDST.FINLFINALIZADO,
                              CODOPEMODIF = :CODOPE,
                              FECMODIF    = VD.FECHASYS,
                              HORAMODIF   = VD.HORASYS
                        WHERE CODINVEN    = :CODINVEN
                          AND CODUBI      = :CODUBI
                          AND CODMAT IS NULL;
                        
CURSOR=CUBIMAT SELECT CODUBI CODUBITEORICA
                 FROM VDCONTE
                WHERE CODMAT = :CODMATLEIDA
                  AND CODUBI != :CODUBI
                  AND CODUBI IS NOT NULL;

CURSOR=CTIENEPRIV SELECT :CODOPE
                   FROM DUAL
                   WHERE VDUSER.TIENEPRIVILEGIO(:CODOPE, VD.GETPROP('PRIVCAMBIOUBI')) = 1;

CURSOR=CACTCODMAT SELECT DECODE(SUBSTR(:CODMATLEIDA,1,2), '00', SUBSTR(:CODMATLEIDA,3), :CODMATLEIDA) CODMATLEIDA FROM DUAL;

CURSOR=CCODMATINVEN SELECT STATUS, CODOPE CODOPEANT
                      FROM VDINVENCONTEO
                     WHERE CODINVEN = :CODINVEN
                       AND CODUBI   = :CODUBI
                       AND CODMAT   = :CODMATLEIDA
                     ORDER BY DECODE(STATUS,VDST.FINONOOK,1,2), DECODE(CODOPE, :CODOPE,1,2);

CURSOR=CCODMATINVEN2 SELECT :STATUS FROM DUAL 
                      WHERE (:STATUS = VDST.FINONOOK AND :CODOPEANT != :CODOPE)
                        OR (:STATUS = VDST.FINOSRECONTEO);

#Selecciona la matrícula y la pone visible.
CURSOR=CSELCODMAT SELECT CODMAT
                    FROM VDINVENLIN
                   WHERE CODINVEN = :CODINVEN
                     AND CODUBI   = :CODUBI
                     AND CODMAT IS NOT NULL;

CURSOR=CSELCODMAT2 SELECT CODMAT
                    FROM VDINVENLIN
                   WHERE CODINVEN = :CODINVEN
                     AND CODUBI   = :CODUBI
                     AND CODMAT IS NOT NULL
                     AND STATUS <= VDST.FINLENCURSO
                     AND (CODINVEN,CODUBI,CODMAT) NOT IN (SELECT CODINVEN,CODUBI,CODMAT
                                                            FROM VDINVENCONTEO
                                                           WHERE CODINVEN = :CODINVEN
                                                             AND CODUBI   = :CODUBI
                                                             AND CODOPE   = :CODOPE
                                                             AND STATUS  != VDST.FINOSRECONTEO)
                   ORDER BY STATUS;

CURSOR=CUPDINVEN UPDATE VDINVENLIN
                    SET STATUS      = VDST.FINLENCURSO,
                        CODRECURSO  = :CODRECURSO,
                        CODOPEMODIF = :CODOPE,
                        FECMODIF    = VD.FECHASYS,
                        HORAMODIF   = VD.HORASYS
                  WHERE CODINVEN    = :CODINVEN
                    AND CODUBI      = :CODUBI
                    AND NVL(CODMAT,NVL(:CODMAT,'@')) = NVL(:CODMAT,'@');

CURSOR=CVALCODMAT SELECT :CODMAT FROM DUAL WHERE :CODMAT IS NOT NULL;

CURSOR=CVALCODMAT2 SELECT :CODMATLEIDA
                     FROM DUAL
                    WHERE :CODMAT = :CODMATLEIDA;


ONLINE=F1 AYUDA F10 LOGOUT ;