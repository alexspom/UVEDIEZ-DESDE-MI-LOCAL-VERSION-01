#
# VDINVENUBI.PAN
#
INVENTARIO
__________ __________

##### - ________________________________

VAYA A LA UBICACION

  _12_________
  _12_________

|

PREQUERY=FEJECUTA("CINICIALIZA","",
                  FIF("CSELINVENPRIV", FSUCCESS,
                                       FEJECUTA(FIF("-CSELINVEN",FEJECUTA(%FFAILURE,"\n\nNO HAY PENDIENTE\nNINGUN INVENTARIO",
                                                                          FCARGAFORM(""),"")),"")),"",
                  "CSELDESINVEN", "ERROR SELECCIONANDO\nINVENTARIO :CODINVEN")

#POSTQUERY=FEJECUTA("CUPDINVEN", "ERROR ACTUALIZANDO INVENTARIO",
#                   FCOMMIT,"")

CAMPO=CODRECURSO,NOENTER
CAMPO=CODOPE,NOENTER
CAMPO=CODINVEN,NOENTER
CAMPO=DESINVEN,NOENTER
CAMPO=CODUBI,NOENTER
CAMPO=CODUBILEIDA,UPPER,SCAN,POSTCHANGE=FDESIGNACION(FIF("CSELNOTNULL",FCARGAFORM("")),"",
                                                     FIF("CVALCODUBI", FEJECUTA(FPOSICIONABLOQUE("1"),""),
                                                                       FEJECUTA(%FFAILURE, "ERROR,\nUBICACION LEIDA INCORRECTA\nVAYA A LA UBICACION :CODUBI")),"")            
CAMPO=FECINI,OCULTO,"#######"
CAMPO=HORAINI,OCULTO,"_8______"

CURSOR=CINICIALIZA SELECT '' CODUBILEIDA, '' CODUBI, 0 CODINVEN, '' DESINVEN FROM DUAL;

#Si el operario tiene privilegio de realizar el último inventario, se le envían primero a estas ubicaciones.
CURSOR=CSELINVENPRIV SELECT A.CODINVEN,A.CODUBI
                       FROM (SELECT CODINVEN, CODUBI, CODMAT, COUNT(*) RECUENTOS
                               FROM VDINVENCONTEO
                              WHERE STATUS IN (VDST.FINONOOK,VDST.FINOSRECONTEO)
                              GROUP BY CODINVEN, CODUBI, CODMAT) A,
                            VDUBICA UBI
                      WHERE VDUSER.TIENEPRIVILEGIO(:CODOPE, VD.GETPROP('PRIVULTIMOINVEN')) = 1
                        AND UBI.CODUBI = A.CODUBI
                        AND A.RECUENTOS >= TO_NUMBER(VD.GETPROP('PMAXRECUENTOS'))
                      ORDER BY UBI.ORDENMOVIM;

CURSOR=CSELINVEN SELECT A.CODINVEN, A.CODUBI
                   FROM VDUBICA UBI,
                       ((SELECT CODINVEN, CODUBI,CODMAT
                          FROM VDINVENLIN
                         WHERE STATUS = VDST.FINLCREADO
                            OR (STATUS = VDST.FINLENCURSO AND (CODRECURSO IS NULL OR CODRECURSO = :CODRECURSO))
                        MINUS
                       SELECT INVO.CODINVEN, INVO.CODUBI, INVL.CODMAT
                         FROM VDINVENCONTEO INVO,  VDINVENLIN INVL
                        WHERE INVO.STATUS IN (VDST.FINONOOK)
                          AND INVO.CODOPE   = :CODOPE
                          AND INVO.CODINVEN = INVL.CODINVEN
                          AND INVO.CODUBI   = INVL.CODUBI
                          AND INVO.CODMAT   = NVL(INVL.CODMAT, INVO.CODMAT))
                        UNION
                       SELECT INVO.CODINVEN, INVO.CODUBI, INVL.CODMAT
                         FROM VDINVENCONTEO INVO,  VDINVENLIN INVL
                        WHERE INVO.STATUS IN (VDST.FINOSRECONTEO)
                          AND INVO.CODINVEN = INVL.CODINVEN
                          AND INVO.CODUBI   = INVL.CODUBI
                          AND INVO.CODMAT   = NVL(INVL.CODMAT, INVO.CODMAT)) A
                  WHERE A.CODUBI = UBI.CODUBI
                  ORDER BY UBI.ORDENMOVIM;
                  
CURSOR=CSELDESINVEN SELECT DESINVEN, VD.FECHASYS FECINI, VD.HORASYS HORAINI
                      FROM VDINVENCAB
                     WHERE CODINVEN = :CODINVEN;

CURSOR=CSELNOTNULL SELECT :CODUBILEIDA FROM DUAL WHERE :CODUBILEIDA IS NULL;

CURSOR=CVALCODUBI SELECT :CODUBILEIDA
                    FROM DUAL
                   WHERE :CODUBI = :CODUBILEIDA;


ONLINE=F1 AYUDA F10 LOGOUT ;