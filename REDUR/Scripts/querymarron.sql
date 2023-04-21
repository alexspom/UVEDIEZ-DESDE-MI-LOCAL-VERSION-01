  SELECT CB.CODPED,
         CB.NBULTO,
         CB.NUMUNI,
         SUM (PEDIDA),
         COUNT (DISTINCT LB.ROWID)
    FROM SGLCABBU CB, SGLLINBU LB
   WHERE     LB.CODPED = CB.CODPED
         AND LB.CODDIV = CB.CODDIV
         AND LB.ANOPED = CB.ANOPED
         AND LB.SEQPED = CB.SEQPED
         AND LB.NBULTO = CB.NBULTO
         AND TIPOBULTO = 'U'
         AND (LB.CODPED, LB.CODART || '') IN (SELECT CODPED, CODART
                                                FROM (  SELECT PEL.CODPED,
                                                               PEL.CODDIV,
                                                               PEL.CODART,
                                                               SUM (PEL.PEDIDA)
                                                                  PEDIDA,
                                                               (  SELECT SUM (
                                                                            BUL.PEDIDA)
                                                                    FROM SGLLINBU BUL
                                                                   WHERE     BUL.CODPED =
                                                                                PEL.CODPED
                                                                         AND BUL.CODDIV =
                                                                                PEL.CODDIV
                                                                         AND PEL.CODART =
                                                                                BUL.CODART
                                                                GROUP BY BUL.CODPED,
                                                                         BUL.CODART)
                                                                  ENBULTOS
                                                          FROM SGLCABPE PEC,
                                                               SGLLINPE PEL
                                                         WHERE     PEC.FECRECEP >
                                                                        FECHASYS
                                                                      - 5
                                                               AND PEC.FECAPER =
                                                                      FECHASYS
                                                               AND PEL.CODPED =
                                                                      PEC.CODPED
                                                               AND PEL.CODDIV =
                                                                      PEC.CODDIV
                                                               AND PEL.ANOPED =
                                                                      PEC.ANOPED
                                                      GROUP BY PEL.CODPED,
                                                               PEL.CODDIV,
                                                               PEL.CODART)
                                               WHERE PEDIDA < ENBULTOS)
GROUP BY CB.CODPED, CB.NBULTO, CB.NUMUNI
  HAVING CB.NUMUNI != SUM (PEDIDA);

SELECT * FROM SGLCABBU;


SELECT DISTINCT CODPED,CODART
  FROM (  SELECT PEL.CODPED,
                 PEL.CODDIV,
                 PEL.CODART,
                 SUM (PEL.PEDIDA) PEDIDA,
                 (  SELECT SUM (BUL.PEDIDA)
                      FROM SGLLINBU BUL
                     WHERE     BUL.CODPED = PEL.CODPED
                           AND BUL.CODDIV = PEL.CODDIV
                           AND PEL.CODART = BUL.CODART
                  GROUP BY BUL.CODPED, BUL.CODART)
                    ENBULTOS
            FROM SGLCABPE PEC, SGLLINPE PEL
           WHERE     PEC.FECRECEP > FECHASYS - 10
                 AND PEC.FECAPER = FECHASYS
                 AND PEL.CODPED = PEC.CODPED
                 AND PEL.CODDIV = PEC.CODDIV
                 AND PEL.ANOPED = PEC.ANOPED
        GROUP BY PEL.CODPED, PEL.CODDIV, PEL.CODART)
 WHERE PEDIDA < ENBULTOS;

UPDATE SGLUBICA SET RESERVA=(SELECT NVL (SUM (PEDIDA - SERVIDA), 0)
               FROM SGLCABBU CB, SGLLINBU LB
              WHERE     CB.STATUS + 0 < 1000
                    AND CB.CODPED = LB.CODPED
                    AND CB.ANOPED = LB.ANOPED
                    AND CB.SEQPED = LB.SEQPED
                    AND CB.CODDIV = LB.CODDIV
                    AND CB.NBULTO = LB.NBULTO
                    AND LB.CODUBI || '' = SGLUBICA.CODUBI
                    AND CB.STATUS NOT IN (175,
                                          180,
                                          260,
                                          360)
                    AND LB.STATUS = 50)
          + (SELECT NVL (SUM (CANTIDAD), 0)
               FROM SGLCABMV CM, SGLLINMV LM
              WHERE     CM.STATUS < 1250
                    AND CM.CODMOV = LM.CODMOV
                    AND CODUBIORIG || '' = SGLUBICA.CODUBI
                    AND NVL (CODUBIDEST, 'NOUBI') != SGLUBICA.CODUBI) 
 WHERE TIPOUBI='PU' AND RESERVA !=
            (SELECT NVL (SUM (PEDIDA - SERVIDA), 0)
               FROM SGLCABBU CB, SGLLINBU LB
              WHERE     CB.STATUS + 0 < 1000
                    AND CB.CODPED = LB.CODPED
                    AND CB.ANOPED = LB.ANOPED
                    AND CB.SEQPED = LB.SEQPED
                    AND CB.CODDIV = LB.CODDIV
                    AND CB.NBULTO = LB.NBULTO
                    AND LB.CODUBI || '' = SGLUBICA.CODUBI
                    AND CB.STATUS NOT IN (175,
                                          180,
                                          260,
                                          360)
                    AND LB.STATUS = 50)
          + (SELECT NVL (SUM (CANTIDAD), 0)
               FROM SGLCABMV CM, SGLLINMV LM
              WHERE     CM.STATUS < 1250
                    AND CM.CODMOV = LM.CODMOV
                    AND CODUBIORIG || '' = SGLUBICA.CODUBI
                    AND NVL (CODUBIDEST, 'NOUBI') != SGLUBICA.CODUBI);