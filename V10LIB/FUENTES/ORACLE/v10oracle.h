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
#ifndef __V10ORACLE__H
#define __V10ORACLE__H
#ifndef __STDC__
#define __STDC__ 1
#endif
#include "oci.h"

//Maxima longitud de un error devuelto por ORACLE
#define MAXERRORORACLE 513


#define OCI_EV_DEF 0                  /* default single-threaded environment */
#define OCI_EV_TSF 1                              /* thread-safe environment */


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
//Longitud maxima de un rowid
#define ROWIDLON       19

#define OCI_LM_DEF 0                                        /* default login */
#define OCI_LM_NBL 1                                   /* non-blocking logon */

// Funciones definidas en V10DRVORACLE.C

V10ORACLEIMPORT dbdrivers *damedriveroracle(void);
V10ORACLEIMPORT void  errlda(void);
V10ORACLEIMPORT int analiza_stmt(OCIStmt **stmt,char *sentencia,OCIError *error);
//Analiza una sentencia sql
V10ORACLEIMPORT int reanaliza_stmt(OCIStmt *stmt,char *sentencia,OCIError *error);
//Vuelve a analizar una sentencia sql
V10ORACLEIMPORT int libera_stmt(OCIStmt *stmt);
//Libera una sentencia sql
V10ORACLEIMPORT int describeoci8(OCIStmt *stmt,OCIError *error);
//Describe una sentencia sql necesaria antes de hacer un define
V10ORACLEIMPORT int ejecuta_stmt(OCISvcCtx *lda,OCIStmt *stmt,int iters,int modo,OCIError *error);
//Ejecuta una sentencia sql en un contexto, permite ejecutarla varias veces
V10ORACLEIMPORT int fetch_stmt(OCIStmt *stmt,int numrows,OCIError *error);
//Hace un fetch de numrows filas de un cursor
V10ORACLEIMPORT int v10tipo2ora(int tipo,int lon);
//Convierte tipo v10 a tipo oracle
V10ORACLEIMPORT int ejefetch_stmt(OCISvcCtx *lda,OCIStmt *stmt,OCIError *error);
//Hace un ejefetch de una sentencia sql
V10ORACLEIMPORT int define_stmt(OCIStmt *stmt,int ncamp,void *var,int lon,int tipo,short *indicador,short *err,OCIError *error);
//Hace define de una sentencia sql
V10ORACLEIMPORT int bind_stmt(OCIStmt *stmt,char *ncamp,void *var,int lon,int tipo,OCIError *error);
//Hace bind de una sentencia sql
V10ORACLEIMPORT int rollbackoracle(void);
//Realiza rollback de la ultima conexion utilizada 
V10ORACLEIMPORT int commitoracle(void);
//Realiza commit de la ultima conexion utilizada
V10ORACLEIMPORT int getnumoraerror(OCIError *error);
V10ORACLEIMPORT int ejecutacursorarrayoracle(v10cursors *c,int iter);
// Ejecuta un cursor iter veces  
//Devuelve el numero de error oracle de una  estructura de error
OCIError *OCIERROR(void);
//Devuelve la estructura de error que se esta utilizando
OCISvcCtx *OCILDA(void);
//Devuelve el contexto de servidor que se esta utilizando
OCIEnv *OCIENV(void);
//Devuelve el entorno oracle que se esta utilizando



/* Prototipo de funciones definidas en V10ORACLEHL.C */
V10ORACLEIMPORT void invalidacursoresLDA(void *LDA);
V10ORACLEIMPORT int arreglainvalidooracle(v10cursors *cur);
//Pasa  un tipo de oracle a tipo V10
V10ORACLEIMPORT int rowidcursor(char *tabla,v10cursors *cur,char *donde);
V10ORACLEIMPORT int getlastnumoraerror(void);  
//Devuelve el ultimo error oracle que se ha producido
/* Devuelve el ultimo rowid utilizado por el cursor */
#include "v10db.h"
#endif
