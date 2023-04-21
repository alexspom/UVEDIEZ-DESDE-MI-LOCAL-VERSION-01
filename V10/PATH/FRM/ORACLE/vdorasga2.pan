DETALLE DE LAS ESTADISTICAS DE LA SENTENCIAS EN EL SGA

Esquema: _30_____  Optimizer Mode: __________  IsObsolete: _  ProgramId: #L########  FirstLoadTime: _100______________________   

SQL:#L## _1000_______________________________________________________________________________________________________________





Módulo: _64___________________________ Acción:  _64___________________________   

Ejecuciones:#L########   Sharablemem:   #L########  Rowsprocessed: #L#######  Javaexectime: #L#######
Buffergets: #L########   Persistentmem: #L########  Fetches:       #L#######  Plsqlexectime:#L#######
Diskread:   #L########   Runtimemem:    #L########                            Elapsedtime:  #L#######
Loads:      #L########                                                        Cputime:      #L####### 
Sorts:      #L########   VersionCount:  #L########         
Parsecalls: #L########   LoadedVersions:#L########                            Useriowaittime:     #L####### 
Rat.Bufget: #L########   OpenVersions:  #L########                            Clusterwaittime:    #L####### 
                         UsersOpening:  #L########                            Concurrencywaittime:#L####### 
                         UsersExecuting:#L########                            Applicationwaittime:#L####### 
|

          																			   
TABLA=DUAL   
NOQUERY

CAMPO=PARSING_SCHEMA_NAME,VIRTUAL
CAMPO=OPTIMIZER_MODE,VIRTUAL
CAMPO=IS_OBSOLETE,VIRTUAL
CAMPO=PROGRAM_ID,VIRTUAL
CAMPO=FIRST_LOAD_TIME,VIRTUAL
CAMPO=COMMAND_TYPE,VIRTUAL
CAMPO=SQL_TEXT,REGPAG=5,VIRTUAL,TOOLTIP(":SQLTEXT\nFirst thousand characters of the SQL text for the current cursor")
CAMPO=MODULE,VIRTUAL,TOOLTIP(":MODULE\nContains the name of the module that was executing at the time that the SQL statement was first parsed as set by calling DBMS_APPLICATION_INFO.SET_MODULE")
CAMPO=ACTION,VIRTUAL,TOOLTIP(":ACTION\nContains the name of the action that was executing at the time that the SQL statement was first parsed as set by calling DBMS_APPLICATION_INFO.SET_ACTION")

CAMPO=EXECUTIONS,VIRTUAL,TOOLTIP("Total number of executions, totalled over all the child cursors")
CAMPO=SHARABLE_MEM,VIRTUAL
CAMPO=ROWS_PROCESSED,VIRTUAL
CAMPO=JAVA_EXEC_TIME,VIRTUAL
CAMPO=BUFFER_GETS,VIRTUAL,TOOLTIP("Sum of bugger gets over all child cursos")
CAMPO=PERSISTENT_MEM,VIRTUAL
CAMPO=FETCHES,VIRTUAL
CAMPO=PLSQL_EXEC_TIME,VIRTUAL
CAMPO=DISK_READS,VIRTUAL,TOOLTIP("Sum of the number of disk reads over all child cursors") 
CAMPO=RUNTIME_MEM,VIRTUAL
CAMPO=ELAPSED_TIME,VIRTUAL
CAMPO=LOADS,VIRTUAL
CAMPO=CPU_TIME,VIRTUAL
CAMPO=SORTS,VIRTUAL
CAMPO=VERSION_COUNT,VIRTUAL
CAMPO=PARSE_CALLS,VIRTUAL
CAMPO=LOADED_VERSIONS,VIRTUAL
CAMPO=USER_IO_WAIT_TIME,VIRTUAL
CAMPO=RATIO_BUFFERGETS,VIRTUAL
CAMPO=OPEN_VERSIONS,VIRTUAL
CAMPO=CLUSTER_WAIT_TIME,VIRTUAL
CAMPO=USERS_OPENING,VIRTUAL
CAMPO=CONCURRENCY_WAIT_TIME,VIRTUAL
CAMPO=USERS_EXECUTING,VIRTUAL
CAMPO=APPLICATION_WAIT_TIME,VIRTUAL

#CAMPO=INVALIDATIONS,OCULTO,"#L########"
#CAMPO=SERIALIZABLE_ABORTS,OCULTO,"#L########"
#CAMPO=PARSING_USER_ID,OCULTO,"#L########"
#CAMPO=CHILD_LATCH,OCULTO,"#L########"
#CAMPO=DIRECT_WRITES,OCULTO,"#L########"
#CAMPO=END_OF_FETCH_COUNT,OCULTO,"#L########"


           

