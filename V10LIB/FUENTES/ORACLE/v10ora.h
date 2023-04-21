/*
* Módulo : V10ORA.H
* Objeto:  Defincion de funciones y estructura para manejo de ORACLE
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#ifndef __V10ORA__H
#define __V10ORA__H
#include "v10.h" 
#ifndef __STDC__
#define __STDC__ 1
#endif

//Definicion de bits de depuracion de cursores ORACLE
#define NODEPURA        0    //Sin depurar
#define DEPURAPARSE     1    //Depura las operaciones de parse
#define DEPURABIND      2    //Depura las operaciones de bind
#define DEPURADEFINE    4    //Depura las operaciones de define
#define DEPURAEXEC      8    //Depura los exec
#define DEPURAFETCH    16    //Depura los fetch
#define DEPURAPRELOG   32    //Graba en el log antes de una operacion ORACLE
#define DEPURALOG      64    //Graba en el log despues de una operacion ORACLE
#define DEPURAMACRO   128    //En las macros ejecutacursorv y fectchcursorv llama a cursordebug si falla
#define DEPURADEFECTO 256    //Depura segun el valor de oradebug
#define DEPURAEXTERNO 512    //Llama a un debuger externo para PLSQL
#define DEPURAVDNOLOG 1024   //Evitar que se llame a logoracle

//Maxima longitud de un error devuelto por ORACLE
#define MAXERRORORACLE 513

#ifndef __LINUX__


#ifdef __V10ORADLL
   #define V10ORAIMPORT __declspec(dllexport)
#else
   #define V10ORAIMPORT __declspec( dllimport )
#endif
#endif


#define OCI_EV_DEF 0                  /* default single-threaded environment */
#define OCI_EV_TSF 1                              /* thread-safe environment */

//Macro que devuelve el valor de depuracion de un cursor
#define debugcursor(cursor) ((cursor->debug&DEPURADEFECTO)?(oradebug|cursor->debug):cursor->debug)

//Macro que ejecuta un cursor si falla genera un return con el codigo de error
#define ejecutacursorv(cursor) {int ret;\
                                 if ((ret=ejecutacursor(cursor))!=0) {\
                                    if (debugcursor(cursor)&DEPURAMACRO) cursordebug(cursor);\
                                    v10log(LOGERROR,"No puedo ejecutar %s en %s línea %d, error %d\n",#cursor,__FILE__,__LINE__,ret);\
                                    return(ret);\
                                  }\
                                }
//Macro que hace ejefetch en un cursor, si falla genera un return con el codigo de error
#define ejefetchcursorv(cursor) {int ret;\
                                 if ((ret=ejefetchcursor(cursor))!=0) {\
                                    if (debugcursor(cursor)&DEPURAMACRO) cursordebug(cursor);\
                                    v10log(LOGERROR,"No puedo ejefetch %s en %s línea %d, error %d\n",#cursor,__FILE__,__LINE__,ret);\
                                    return(ret);\
                                  }\
                                }
//Macro que hace fetch en un cursor, si falla genera un return con el codigo de error
#define fetchcursorv(cursor) {int ret;\
                                 if ((ret=fetchcursor(cursor))!=0) {\
                                    if (debugcursor(cursor)&DEPURAMACRO) cursordebug(cursor);\
                                    v10log(LOGERROR,"No puedo hacer fetch %s en %s línea %d, error %d\n",#cursor,__FILE__,__LINE__,ret);\
                                    return(ret);\
                                  }\
                                }

//Tipos de dato de ORACLE
#define OCIINT          3 
#define OCICADENA       5
#define OCIDOUBLE       4
#define OCICHAR         1
#define OCINUMBER       2
#define OCILONG         8
#define OCICROWID      11
#define OCIDATE        12
#define OCIRAW         23
#define OCILONGRAW     24
#define OCIUNSIGNED    68
#define NOPAR (void *) -1
#define OCIROWID       20

//Maximo numero de campos en un cursor
#define MAXCAMPOS     400
//Longitud maxima de una sentencia que se asigna a un cursor
#define MAXSQL       (MAXCADENA*4)
//Longitud maxima de un rowid
#define ROWIDLON       19

//Errores de ORACLE
V10ORAIMPORT int ABRAZO;
V10ORAIMPORT int FSELECT;
V10ORAIMPORT int NOFOUND;
V10ORAIMPORT int DUPLICADO;
V10ORAIMPORT int BLOQUEADO;
#define DATOSTRUNCADOS 1406
#define NOTLOGGED      -1


#define OCI_LM_DEF 0                                        /* default login */
#define OCI_LM_NBL 1                                   /* non-blocking logon */

//Usuario y password con el que nos hemos conectado
V10ORAIMPORT char ORAUSR[],ORAPWD[],ORADB[];

// Indica si hemos devolver control a windows (Para repintar) antes de cada llamada a ORACLE
V10ORAIMPORT int ORATECLA;
//Funcion que hace log C de los log generados en PLSQL
V10ORAIMPORT void (*logoracle)(void);
//Flags por defecto parasados a parse
V10ORAIMPORT int defparse;
//Flags por defecto del lenguaje que utiliza ORACLE
V10ORAIMPORT short deflang;
//Funcion que se ejecuta cada vez que se conecta a la base de datos.
V10ORAIMPORT void (*trigerconecta)(void);
//Funcion que se ejecuta cada vez que se hace logout de la base de datos.
V10ORAIMPORT void (*trigerlogout)(void);

//Estructura de un campo de un cursor V10, vale tanto para defines como para binds
typedef struct {
         char nombre[MAXNOMBREV10];  // Nombre del campo
         int oratipo;             // Tipo del campo segun ORACLE (especificaciones OCI)
         unsigned oralen;         // Longitud del campo para ORACLE
         int tipo;                // Tipo del campo V10
         unsigned lon;            // Longitud del campo V10
         int disp;                // No utilizado
         void *dato;              // Puntero al campo
         short indicador;         // Indicador que se pasa a ORACLE para detectar nulos
         unsigned short error;    // Warning a nivel campo que devuelve ORACLE detecta truncamientos etc.
         short prec;              // Precision de campo (Numero de caracteres y digitos totales)
         short scale;             // Escala indica cuantos digitos son decimales
         short nullok;            // Permite nulos
         int   meminterna;        // Indica si la memoria asignada al campo es interna 1 o externa 0
       } campooras;


//Estructura de un cursor V10
typedef struct V10CURSORS {
	     struct V10CURSORS *next;  //Siguiente cursor en la lista de cursores encadenados
         char nombre[MAXNOMBREV10];  // Nombre del cursor solo vale para depurar
         char *sql;               // Sentencia sql asociada al cursor en memoria dinamica
         int  parseerror;         // Posicion en el que se produce error de parse
         int  funoci;             // Funcion oci que se ejecuta
         int  errcode;            // Codigo de error
         int  filasprocesadas;    // Numero de filas procesadas por el cursor
         int  funsql;             // Función SQL
         int invalido;            // Si esta a 1 indica que el cursor no es valido y ha de ser reanalizado.
         int ndef;                // Numero de campos define (Los que se extraen de una select)
         campooras *def;          // Array con los campos
         int nbind;               // Numero de campos bind (Los que se pasan a ORACLE como variable prefinados con :)
         campooras *bind;         // Array de campos bind 
         char *buffer;            // buffer para array fetch
         unsigned nelem;          // Numero de elementos del array
         unsigned fprocess;       // Numero de elementos que faltan por procesar pero ya se han extraido de ORACLE
         unsigned sprocess;       // Siguiente fila a procesar por array fetch
         long tam;                // Tamaño de un registro para arrayfetch
         int  arrerr;             // Error devuelto por array fetch
         unsigned ejecuciones;    // Numero de ejecuciones del cursor
         unsigned numfetch;       // Numero de fetch ejecutados en el cursor
		 unsigned numejefetch;    // Numero de ejefetch ejecutados en el cursor
         v10horas texec;          // Tiempo del ultimo exec
         v10horas tfetch;         // Tiempo del ultimo fetch
         v10horas tejefetch;      // Tiempo del ultimo ejefetch
         v10horas totexec;        // Tiempo total dedicado a exec
         v10horas totfetch;       // Tiempo total dedicado a fetch
         v10horas totejefetch;    // Tiempo total dedicado a ejefetch
         v10horas tparse;         // Tiempo total dedicado a ejefetch
         char     *funcion;       // Funcion que analizo el cursor
         char     *file;          // Fichero en el que se analizo el cursor
         int      line;           // Linea en la que se analizo el cursor
         int      debug;          // Modo debug del cursor
		 void     *extra;         // Datos propios de cada base de datos
       } v10cursors;



#include "v10db.h"

// Funciones definidas en V10DBLL.C
V10ORAIMPORT int loginne(char *uid,char *pwd,char *db);
 /* Conecta con la base de datos
    char * uid es el nombre de ususario, puede llevar /passwd.
    char * pwd es el password si ya lo lleva el usuario pasar NULL
    Devuelve el codigo de error ORACLE al realizar la conexion
 */
V10ORAIMPORT int login(char *uid,char *pwd,char *db);
 /* Conecta con la base de datos
    char * uid es el nombre de ususario, puede llevar /passwd.
    char * pwd es el password si ya lo lleva el usuario pasar NULL
    char * db cadena de conexion, si va en el usuario puede ir a NULL
    Si no logra conectar aborta el programa con un mensaje de error
 */
V10ORAIMPORT int damelogins(void);
// Devuelve el numero de conexiones actuales a oracle 
V10ORAIMPORT int relogin(void);
/* Apila una conexion nueva con el mismo usuario y password, util cuando queremos realizar transacciones diferentes
    Devuelve el numero de conexion en la pila de conexiones */
V10ORAIMPORT int damenumlogin(void);
// Devuelve el numero de la conexion ORACLE en la que estamos, el numero lo puede utilizar reusaconexion 
V10ORAIMPORT int reusanumlogin(int ncon);
// Usa una conexion de la pila 
V10ORAIMPORT int logout(void);
// Desconecta de la base de datos la conexion ultima conexion 
V10ORAIMPORT void getcurerror(v10cursors *cur,char *buffer);
//Devuelve el mensaje de error de un cursor
V10ORAIMPORT void getcurerrornombre(char *nombre,char *buffer);
//Devuelve el mensaje de error de un cursor por nombre del cursor
//Hace bind de una sentencia sql
V10ORAIMPORT void getlastdberror(char *buffer);
V10ORAIMPORT int arreglainvalido(v10cursors *cur);
V10ORAIMPORT int ejecutacursorarray(v10cursors *cur,int iter);
V10ORAIMPORT int rollback(void);
//Realiza rollback de la ultima conexion utilizada 
V10ORAIMPORT int commit(void);
//Realiza commit de la ultima conexion utilizada


/* Prototipo de funciones definidas en V10ORACLEHL.C */
//MACROS de acceso a ORACLE
#define abrecursor(nombre) abrecursornombre(#nombre,nombre)
//Abre un cursor con un define el define indica la sentencia y el nombre del define se utiliza como nombre de cursor
#define abrecursordebug(nombre,debug) abrecursornombredebug(#nombre,nombre,debug)
//Abre un cursor con un define el define indica la sentencia y el nombre del define se utiliza como nombre de cursor
//Ademas indica el nivel de debug del cursor
#define abrecursornombre(nombre,sql) abrecursornombref(nombre,sql,__FUNCTION__,__FILE__,__LINE__,DEPURADEFECTO) 
//Abre un cursor le pasamos el nombre que le queremos dar al cursor y la sentencia a analizar
#define abrecursornombredebug(sql,nombre,debug) abrecursornombref(sql,nombre,__FUNCTION__,__FILE__,__LINE__,debug) 
//Abre un cursor le pasamos el nombre que le queremos dar al cursor y la sentencia a analizar ademas indicamos el nivel de debug
#define llparsecursornombre(sql,nombre,error) llparsecursornombref(sql,nombre,__FUNCTION__,__FILE__,__LINE__,error,DEPURADEFECTO)
//Analiza un cursor si en error pasamos diferente de 0 muestra un cursor debug si falla
#define llparsecursornombredebug(sql,nombre,error,debug) llparsecursornombref(sql,nombre,__FUNCTION__,__FILE__,__LINE__,error,debug)
//Analiza un cursor si en error pasamos diferente de 0 muestra un cursor debug si falla, le pasamos tambien el nivel de debug
#define parsecursornombre(sql,nombre) parsecursornombref(sql,nombre,__FUNCTION__,__FILE__,__LINE__,DEPURADEFECTO)
//Analiza un cursor muestra un cursor debug si falla
#define parsecursornombredebug(sql,nombre) parsecursornombrefdebug(sql,nombre,__FUNCTION__,__FILE__,__LINE__,debug) 
//Analiza un cursor muestra un cursor debug si falla, pasamos tambien el nivel de debug
#define ejecutaimmediato(sql) ejecutaimmediatof(sql,DEPURADEFECTO,__FUNCTION__,__FILE__,__LINE__)  
//Ejecuta de manera immediate una sentencia sql
#define ejecutaimmediatoparam(sql,...) ejecutaimmediatoparamf(sql,DEPURADEFECTO,__FUNCTION__,__FILE__,__LINE__,__VA_ARGS__)  
//Ejecuta de manera immediate una sentencia sql
#define ejecutaimmediatodebug(sql,debug) ejecutaimmediatof(sql,debug,__FUNCTION__,__FILE__,__LINE__)  
//Ejecuta de manera immediate una sentencia sql
#define ejecutaimmediatoparamdebug(sql,debug,...) ejecutaimmediatoparamf(sql,debug,__FUNCTION__,__FILE__,__LINE__,__VA_ARGS__)  
//Ejecuta de manera immediate una sentencia sql
#define savepoint(nombre) savepointf(nombre,DEPURADEFECTO,__FUNCTION__,__FILE__,__LINE__) 
//Crea un savepoint con nombre
#define rollbacksavepoint(nombre) rollbacksavepointf(nombre,DEPURADEFECTO,__FUNCTION__,__FILE__,__LINE__)
//Hace rollback al savepoint nombre
#define savepointdebug(nombre,debug) savepointf(nombre,debug,__FUNCTION__,__FILE__,__LINE__) 
//Crea un savepoint con nombre
#define rollbacksavepointdebug(nombre,debug) rollbacksavepointf(nombre,debug,__FUNCTION__,__FILE__,__LINE__)
//Hace rollback al savepoint nombre
V10ORAIMPORT void anadecursordebug(int mascara,char *listacur);
//Modifica el modo debug de una lista de cursores
V10ORAIMPORT v10cursors *llparsecursornombref(char *sql,char *nombre,const char *funcion,const char *file,int line,int error,int debug);
//Funciones de bajo nivel para abrir cursores, reciben todas ellas el fichero y la linea en la que se abren
V10ORAIMPORT v10cursors *parsecursornombref(char *sql,char *nombre,const char *funcion,const char *file,int line,int debug);
V10ORAIMPORT v10cursors *abrecursornombref(char *nombre,char *sql,const char *funcion,const char *file,int line,int debug);
V10ORAIMPORT campooras *campodefine(v10cursors *c,char *n);
/* Devuelve el campo define de un cursor de nombre n o NULL si no existe */
V10ORAIMPORT campooras *campobind(v10cursors *c,char *n);
/* Devuelve el campo bind de un cursor de nombre n o NULL si no existe */
V10ORAIMPORT int definecursor(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo);
/* Asigna una variable a un campo define
     cur cursor a asignar
     ncam numero del campo a asignar
     var direccion de la variable a asignar
     lon longitud de la variable
     v10tipo tipo V10 de la variable
     devuelve el error ORACLE */
V10ORAIMPORT int definetodo(v10cursors *cur,...);
/* Define todos los campos de un cursor
      cur cursor a asignar
      resto de los parametros ternas del tipo var,lon,v10tipo
      al final debe ir un NULL para indicar ultima variable.
      Devuelve 0 si no hay error o aborta el programa con un debug_oracle si se produce un error o no coincide el numero de variables
      con las que espera */
V10ORAIMPORT int bindcursor(v10cursors *cur,char *ncamp,void *var,int lon,int v10tipo);
/* Asigna una variable a un campo bind
     cur cursor a asignar
     ncam nombre de la variavle bind a asignar
     var direccion de la variable a asignar
     lon longitud de la variable
     v10tipo tipo V10 de la variable
     devuelve el error ORACLE */
V10ORAIMPORT int bindtodo(v10cursors *cur,...);
/* Hace bind de todos los campos de un cursor
      cur cursor a asignar
      resto de los parametros cuaternas del tipo ncamp,var,lon,v10tipo
      al final debe ir un NULL para indicar ultima variable.
      Devuelve 0 si no hay error o aborta el programa con un debug_oracle si se produce un error o no coincide el numero de variables
      con las que espera */
V10ORAIMPORT int bindvarios(v10cursors *cur,...);
/* Hace bind de algunos campos de un cursor
      cur cursor a asignar
      resto de los parametros cuaternas del tipo ncamp,var,lon,v10tipo
      al final debe ir un NULL para indicar ultima variable.
      Devuelve 0 si no hay error o aborta el programa con un debug_oracle si se produce un error o no coincide el numero de variables
      con las que espera */  
V10ORAIMPORT int arreglainvalido(v10cursors *cur);
V10ORAIMPORT int ora2v10tipo(int oratipo,int lonoracle,int precision,int escala,int *lon);
//Pasa  un tipo de oracle a tipo V10
V10ORAIMPORT int definetododinamico(v10cursors *cur);  
//Define un cursor de manera dinamica
V10ORAIMPORT int binddinamico(v10cursors *cur,int v10tipo,int lon,char *nombre);
//Hace bind de un cursor de manera dinamica
V10ORAIMPORT int ejecutacursor(v10cursors *c);
/* Ejecuta un cursor devuelve el error ORACLE */
V10ORAIMPORT void preparaarrayfetch(v10cursors *v10,int nelem);
/* Prepara un cursor para realizar en array fetch sobre el, el programador no nota ninguna diferencia, pero las
   llamadas a ORACLE se agilizan si se extraen muchos registros de una select, si de una select multiregistro se utiliza solo uno
   no utilizar pues iria mas lento pues ORACLE hace realmente el fetch de n registros.
   v10cursor a preparar
   nelem numero de filas a extraer de golpe de oracle */
V10ORAIMPORT int fetchcursor(v10cursors *cur);
/* Realiza el fetch de una select en los campos asignados como define tenemos los datos extraidos de ORACLE
   c cursor sobre el que realizar el fetch.
   Devuelve el error ORACLE del fetch */
V10ORAIMPORT int ejefetchcursor(v10cursors *cur);
/* Realiza en una sola pasada la ejecucion y el fetch
   c cursor sobre el que realizar el fetch.
   Devuelve el error ORACLE */
V10ORAIMPORT int cancelacursor(v10cursors *cur);
/* Libera todos los recursos ORACLE asignados al cursor, no libera los recursos V10 pues el cursor para nosostros sigue activo.
   c cursor sobre el que realizar el fetch.
   Devuelve el error ORACLE */
V10ORAIMPORT int liberacursor(v10cursors *cur);
/* Libera todos los recursos ORACLE y V10 destinados al cursor a partir de este punto no se puede volver a acceder a el
   c cursor sobre el que realizar el fetch.
   Devuelve el error ORACLE */
V10ORAIMPORT int ejecutaimmediatof(char *sql,int debug,const char *funcion,const char *file,int line);
/* Ejecuta de forma immediata una sentencia ORACLE, la sentencia no puede tener campos ni bind ni define
   sql sentencia a ejecutar
   Devuelve el error ORACLE */   
V10ORAIMPORT int ejecutaimmediatoparamf(char *sql,int debug,const char *funcion,const char *file,int line,...);
/* Analogo al anterior pero admite parametros tipo printf */
V10ORAIMPORT int savepointf(char *nombre,int debug,const char *funcion,const char *file,int line);
/* Prepara un savepoint ORACLE para efectuar un rollback_savepoint
   nombre el nombre del savepoint a preparar
   Devuelve el error ORACLE */
V10ORAIMPORT int rollbacksavepointf(char *nombre,int debug,const char *funcion,const char *file,int line);
/* Realiza un rollbac al savepoint especificado
   nombre el nombre del savepoint a hacer rollback
   Devuelve el error ORACLE */
V10ORAIMPORT void getlastdberror(char *buffer);
// devuelve el texto de error correspondiente a la operacion ORACLE 
V10ORAIMPORT void imprime_orastd(void);
/* Imprime estadisticas sobre cursores utilizados etc. */
V10ORAIMPORT int procesadascursor(v10cursors *cur);
/* Devuelve el numero de filas tratadas por un cursor */
V10ORAIMPORT int pondebugcursor(v10cursors *cur,int debug);
V10ORAIMPORT int errorcursor(v10cursors *cur);
/* Devuelve el error del cursor */
V10ORAIMPORT int funcioncursor(v10cursors *cur);
/* Devuelve la funcion SQL (tipo de sentencia) ejecutada en el cursor */
V10ORAIMPORT void menucursores(void);
//Saca el menu de cursores actualmente abiertos
V10ORAIMPORT v10cursors *damecursornombre(char *nombre);
//Devuelve un cursor actualmente abierto por el nombre
V10ORAIMPORT v10cursors *damercursor(int *_numcursor);
// devuelve el puntero a rcursor, y captura el número de cursores
V10ORAIMPORT char *pasaoracampo2ascii(campooras *c,char *buffer,int comillas,int fechas); 
// Pasa un campo de un cursor a una buffer

// Funciones definidas en V10ORADEBUG.C 
V10ORAIMPORT int (*handleoraerr)(int coderr,v10cursors *c);
// Puntero a función del manejador de errores oracle
V10ORAIMPORT int oradebug;
//Variable de debug de Oracle global
V10ORAIMPORT char *dameoratipo(int tipo);;
//Devuelve un literal con el tipo oracle indicado por tipo
V10ORAIMPORT void toggleoradebug(int dummy);
//Pone y quita la variable global oradebug
V10ORAIMPORT void presentaselect(v10cursors *c,windows *w);
//Presenta la select asociada a un cursor en una ventana que pasa el usuario
V10ORAIMPORT int editaselect(v10cursors *c,windows *w);
//Presenta la select asociada a un cursor y permite desplazarse por ella
V10ORAIMPORT void STDcursordebug(v10cursors *c);
//Funcion que llama al debuger de oracle para conexiones
V10ORAIMPORT void detallaerrorcursor(int nivel,v10cursors *cur,int soloerror);
//Funcion que hace los de los errores de un cursor

// Funciones definidas en V10LEESQL.C 
V10ORAIMPORT v10cursors *damevsq(char *nombre);
//Devuelve un cursor leido de un fichero vsq.
V10ORAIMPORT v10cursors *damevsqnum(int num);
//Devuelve el n-esimo cursor leido.
V10ORAIMPORT void leevsq(char *nombre);
//Lee todos los cursores definidos en un fichero vsq.
V10ORAIMPORT v10cursors *damevsqseguro(char *nombre);
//Devuelve un cursor leido de un fichero vsq, aborta si no existe.

//Funciones definidas en V10ORAMODULO
#define LMODULE  65
#define LACTION 100
V10ORAIMPORT int setmodule(char *module,char *action);
//Pone las variables modulo y accion en la tabla sys.v_$session
V10ORAIMPORT int setaction(char *action);
//Pone solo la variable accion sin modificar el modulo


//Funciones definidas en V10ORAARGV.C
dbdrivers *damedbdriver(char *cadena);
V10ORAIMPORT int trataparamoracle(char *param);
/*Tratamiento de los parametros estandar de oracle
        D Pone oradebug al valor que se presenta a continuacion en hexa, si el valor es blanco lo pone a depurar todo
        R Numero de reintentos de conexion a la base de datos.
        F Fichero de inicializacion en el que se indica usuario/password codificados.
        I Ejecuta la sentencia que va a continuacion de modo immmediato
        U Conecta a oracle con el usuario/password o identificador de conexion que se pasa a continuacion.
        C Pone una lista de cursores a depurar Sintaxis: Cmascara,lista de cursores
*/
//Funciones definidas en V10ORAEXCEL.C
V10ORAIMPORT char *(*traducecamposole)(char *nombre,int dir);
//Puntero a funcion de traduccion de campos cuando se pasa una sentencia sql a Excel
V10ORAIMPORT int bloqcur2excel(void *b,v10cursors *cur,char *plantilla,char *destino,int salir);
V10ORAIMPORT int cur2excel(v10cursors *cur,char *plantilla,char *destino,int salir);
//Pasa un cursor a Excel segun una pantilla, permite grabar en fichero destino, salir indica si se ha de salir de Excel al terminar
V10ORAIMPORT int bloqsql2excel(void *b,char *sql,char *plantilla,char *destino,int salir);
V10ORAIMPORT int sql2excel(char *sql,char *plantilla,char *destino,int salir);
//Pasa una sentencia sql a Excel. Resto parametros igual que la funcion anterior.
#ifndef __LINUX__
//Funciones definidas en V10ORAWORD.C
V10ORAIMPORT int cadenaword(IDispatch *doc,char *estilo,char *cadena);
//Pone una cadena en Word al final del documento con el estilo estilo, admite \n para separar lineas
V10ORAIMPORT IDispatch *creatabla(IDispatch *doc,int filas,int columnas,char *estilotabla,char *estilotitulo,char *titulo,char *comentario);
//Crea una tabla word
V10ORAIMPORT void pasacursorword(IDispatch *id,IDispatch *doc,v10cursors *v10sel,char *estilotabla,char *estilotitulo,char *titulo,char *comentario);
//Pasa un cursor a una tabla word
V10ORAIMPORT void pasaselectword(IDispatch *id,IDispatch *doc,char *select,char *estilotabla,char *estilotitulo,char *titulo,char *comentario);
//Pasa una select a una tabla word.
#endif
//Funciones definidas en V10EXCEL2ORA.C
V10ORAIMPORT int excel2ora(char *nombre,char *destino,int crear,int std);
//Pasa una hoja de calculo excel a una tabla oracle
V10ORAIMPORT void pondefaultdrv(dbdrivers *drv);

V10ORAIMPORT void(*cursordebug)(void *c);
V10ORAIMPORT void(*ldadebug)(void *c, int funcion);

#endif
