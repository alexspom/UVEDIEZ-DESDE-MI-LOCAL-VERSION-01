SELECT GVH.SID AS "Sesiones que bloquean: SESSID",
       GVS.SERIAL# SERIAL,
       GVH.INST_ID INSTANCE_ID,
       GVH.CTIME CTIME
  FROM GV$LOCK GVH, GV$LOCK GVW, GV$SESSION GVS
 WHERE     (GVH.ID1, GVH.ID2) IN (SELECT ID1, ID2
                                    FROM GV$LOCK
                                   WHERE REQUEST = 0
                                  INTERSECT
                                  SELECT ID1, ID2
                                    FROM GV$LOCK
                                   WHERE LMODE = 0)
       AND GVH.ID1 = GVW.ID1
       AND GVH.ID2 = GVW.ID2
       AND GVH.REQUEST = 0
       AND GVH.REQUEST = 0
       AND GVW.LMODE = 0
       AND GVH.SID = GVS.SID
       AND GVH.INST_ID = GVS.INST_ID
       AND GVS.TYPE != 'BACKGROUND'
       AND GVH.CTIME > '120'