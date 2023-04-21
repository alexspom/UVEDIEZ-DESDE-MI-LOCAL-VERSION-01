create table tiempos as 
SELECT 1 valor,
   s.username,
   t.sid,
   s.serial#,
   SUM(VALUE/100) as "cpu"
FROM
   v$session s,
   v$sesstat t,
   v$statname n
WHERE
   t.STATISTIC# = n.STATISTIC#
AND
   NAME like '%CPU used by this session%'
AND
   t.SID = s.SID
AND
   s.status='ACTIVE'
AND
   s.username is not null
GROUP BY username,t.sid,s.serial#


begin 
  FOR I IN 2..10 LOOP
      INSERT INTO TIEMPOS 
SELECT I valor,
   s.username,
   t.sid,
   s.serial#,
   SUM(VALUE/100) as "cpu"
FROM
   v$session s,
   v$sesstat t,
   v$statname n
WHERE
   t.STATISTIC# = n.STATISTIC#
AND
   NAME like '%CPU used by this session%'
AND
   t.SID = s.SID
AND
   s.status='ACTIVE'
AND
   s.username is not null
GROUP BY username,t.sid,s.serial#;
END LOOP;
END;

SELECT * FROM TIEMPOS;
