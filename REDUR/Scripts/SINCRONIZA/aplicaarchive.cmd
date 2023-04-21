SET ORACLE_SID=ORCL
D:\oracle\product\12.1.0\dbhome_1\BIN\sqlplus "sys/sys as sysdba" @D:\SMCL\SCRIPTS\SINCRONIZA\aplicaarchive.sql >>D:\SMCL\SCRIPTS\SINCRONIZA\logaplica.txt
D:\oracle\product\12.1.0\dbhome_1\BIN\RMAN target=SYS/SYS @D:\SMCL\Scripts\SINCRONIZA\borraarchive.RMAN >>D:\SMCL\Scripts\SINCRONIZA\logaplica.txt
CALL D:\SMCL\SCRIPTS\SINCRONIZA\ABREREADONLY
rem pendiente de que lo revise Edu.
CALL D:\SMCL\SCRIPTS\SINCRONIZA\COMPRUEBABACK
CALL D:\SMCL\SCRIPTS\SINCRONIZA\CLOSEDB
EXIT