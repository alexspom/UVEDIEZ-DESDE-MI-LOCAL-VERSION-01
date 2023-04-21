MONITOR DE ESTADISTICAS DE SENTENCIAS EN EL SGA

Esquema  SQL                                               Módulo           Acción          Ejecuciones BufferGets  DiskRead   
_30_____ _1000____________________________________________ _64_____________ _64_____________ #L########  #L######## #L########   
|
          																			   
SOLOQUERY
SELECT=SELECT DISTINCT VS.SQL_TEXT, VS.MODULE, VS.ACTION, VS.BUFFER_GETS, VS.DISK_READS, VS.LOADS,
                VS.SHARABLE_MEM, VS.PERSISTENT_MEM,VS.RUNTIME_MEM, VS.SORTS, VS.EXECUTIONS, VS.PARSE_CALLS,
                VS.VERSION_COUNT, VS.LOADED_VERSIONS, VS.OPEN_VERSIONS,                         
                VS.USERS_OPENING, VS.USERS_EXECUTING,VS.INVALIDATIONS, VS.SERIALIZABLE_ABORTS, VS.COMMAND_TYPE,
                TO_CHAR(VS.FIRST_LOAD_TIME) FIRST_LOAD_TIME,                                    
                RAWTOHEX (VS.ADDRESS) ADDRESS,                                              
                VS.HASH_VALUE HASH_VALUE,                                              
                VS.PARSING_USER_ID, ROWS_PROCESSED, OPTIMIZER_MODE,                             
                VS.IS_OBSOLETE, VS.ELAPSED_TIME, VS.CPU_TIME, VS.CHILD_LATCH,                
                VS.FETCHES, VS.PROGRAM_ID, VS.JAVA_EXEC_TIME,
                VS.PLSQL_EXEC_TIME, VS.USER_IO_WAIT_TIME,                                       
                VS.CLUSTER_WAIT_TIME, VS.CONCURRENCY_WAIT_TIME,                                 
                VS.APPLICATION_WAIT_TIME,VS.DIRECT_WRITES,VS.END_OF_FETCH_COUNT,
                PARSING_SCHEMA_NAME,
                VS.BUFFER_GETS/DECODE(VS.EXECUTIONS,0,1,VS.EXECUTIONS)RATIO_BUFFERGETS,
                DECODE(SIGN(VS.BUFFER_GETS/DECODE(VS.EXECUTIONS,0,1,VS.EXECUTIONS)-100),1,18,-1) SQL_TEXT__COLOR                 
         FROM V$SQLAREA VS           
         WHERE VS.PARSING_USER_ID>0; 


CAMPO=PARSING_SCHEMA_NAME,TITULO("Esquema")
CAMPO=SQL_TEXT,TOOLTIP(":SQLTEXT\nFirst thousand characters of the SQL text for the current cursor"),TITULO("Texto SQL")
CAMPO=MODULE,TOOLTIP(":MODULE\nContains the name of the module that was executing at the time that the SQL statement was first parsed as set by calling DBMS_APPLICATION_INFO.SET_MODULE"),TITULO("Módulo")
CAMPO=ACTION,TOOLTIP(":ACTION\nContains the name of the action that was executing at the time that the SQL statement was first parsed as set by calling DBMS_APPLICATION_INFO.SET_ACTION"),TITULO("Acción")
CAMPO=EXECUTIONS,TOOLTIP("Total number of executions, totalled over all the child cursors"),TITULO("Ejecuciones"),WLONX=26
CAMPO=BUFFER_GETS,TOOLTIP("Sum of bugger gets over all child cursos"),TITULO("Buffer Gets"),WLONX=25
CAMPO=DISK_READS,TOOLTIP("Sum of the number of disk reads over all child cursors"),TITULO("DiskReads"),WLONX=25
CAMPO=LOADS,OCULTO,"#L########"
CAMPO=SHARABLE_MEM,OCULTO,"#L########"
CAMPO=PERSISTENT_MEM,OCULTO,"#L########"
CAMPO=RUNTIME_MEM,OCULTO,"#L########"
CAMPO=SORTS,OCULTO,"#L########"
CAMPO=PARSE_CALLS,OCULTO,"#L########"
CAMPO=VERSION_COUNT,OCULTO,"#L########"
CAMPO=LOADED_VERSIONS,OCULTO,"#L########"
CAMPO=OPEN_VERSIONS,OCULTO,"#L########"
CAMPO=USERS_OPENING,OCULTO,"#L########"
CAMPO=USERS_EXECUTING,OCULTO,"#L########"
CAMPO=INVALIDATIONS,OCULTO,"#L########"
CAMPO=SERIALIZABLE_ABORTS,OCULTO,"#L########"
CAMPO=COMMAND_TYPE,OCULTO,"#L########"
CAMPO=FIRST_LOAD_TIME,OCULTO,"_100______________________"
CAMPO=ADDRESS,OCULTO,"_100_______________________"
CAMPO=HASH_VALUE,OCULTO,"_100_______________________"
CAMPO=PARSING_USER_ID,OCULTO,"#L########"
CAMPO=ROWS_PROCESSED,OCULTO,"#L########"
CAMPO=OPTIMIZER_MODE,OCULTO,"_10____"
CAMPO=IS_OBSOLETE,OCULTO,"_"
CAMPO=ELAPSED_TIME,OCULTO,"#L########"
CAMPO=CPU_TIME,OCULTO,"#L########"
CAMPO=CHILD_LATCH,OCULTO,"#L########"
CAMPO=FETCHES,OCULTO,"#L########"
CAMPO=PROGRAM_ID,OCULTO,"#L########"
CAMPO=JAVA_EXEC_TIME,OCULTO,"#L########"
CAMPO=PLSQL_EXEC_TIME,OCULTO,"#L########"
CAMPO=USER_IO_WAIT_TIME,OCULTO,"#L########"
CAMPO=CLUSTER_WAIT_TIME,OCULTO,"#L########"
CAMPO=CONCURRENCY_WAIT_TIME,OCULTO,"#L########"
CAMPO=APPLICATION_WAIT_TIME,OCULTO,"#L########"
CAMPO=DIRECT_WRITES,OCULTO,"#L########"
CAMPO=END_OF_FETCH_COUNT,OCULTO,"#L########"
CAMPO=RATIO_BUFFERGETS,OCULTO,"#L#,###,###.##"
         
