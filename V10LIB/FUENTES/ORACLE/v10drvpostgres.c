/*
* Módulo : V10DRVPOSTGRES.C
* Objeto:  Manejo del bajo nivel de ORACLE
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10ora.h"
#include "v10db.h"
#include "postgres.h"

typedef struct {
               PGconn   *conexion;
} postgredatoscon;
#define CONNPG (((postgredatoscon *)arrlogin[numlogins-1].extra)->conexion)

typedef struct {
	PGconn *conn;
	PGresult *res;
} postgredatoscursor;

#define pgrescur(cur) (((postgredatoscursor *)cur->extra)->res)
#define pgconcur(cur) (((postgredatoscursor *)cur->extra)->conn)

// Funciones de definir por puntero
void dbinitpostgre(void)
{  
	//	OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,(dvoid * (*)(dvoid *, size_t)) 0,(dvoid * (*)(dvoid *, dvoid *, size_t))0,(void (*)(dvoid *, dvoid *)) 0 );
}

void dameerrorpostgre(void *error,char *mensaje)
{
}

int dbcommitpostgre(void)
{
	PGresult   *res;
    return(0);
	res=PQexec(CONNPG, "COMMIT;");
	PQclear(res);
   // PQexec(CONNPG, "START TRANSACTION;");
	return(0);
}

int dbrollbackpostgre(void)
{
	PGresult   *res;
    return(0);
	res=PQexec(CONNPG,"ROLLBACK;");
	PQclear(res);
 //   PQexec(CONNPG, "START TRANSACTION;");
	return(0);
}

int dblogoutpostgre(void)
{
	PQfinish(CONNPG);
	free(EXTRA);
	return(0);
}

int dbloginpostgre(char *usuario,char *password,char *condb)
{
	PGconn *conn;
	ConnStatusType ret;
	char coninfo[MAXPATH];
    char *dbname;
    dbname=strchr(condb,':');
    if (dbname) {
        *dbname=0;
	    sprintf(coninfo,"host =%s dbname =%s user=%s password=%s",condb,dbname+1,usuario,password);
        *dbname=':';
    } else {
	    sprintf(coninfo,"dbname =%s user=%s password=%s",condb,usuario,password);
    }
    v10log(LOGDEBUG,"Intento conectar con postgres conninfo %s\n",coninfo);
	conn = PQconnectdb(coninfo);
	ret=PQstatus(conn);
	if (ret != CONNECTION_OK) {
		PQfinish(conn);
		return (-1);
	}
	EXTRA = v10calloc(1, sizeof(postgredatoscon), __FILE__, __LINE__);
	CONNPG=conn;
  //  PQexec(CONNPG, "START TRANSACTION");
	return(0);
}


static int isvariable(char valor)
{
	if (valor>='a' && valor<='z') return(1);
	if (valor>='A' && valor<='Z') return(1);
	if (valor>='0' && valor<='9') return(1);
	if (valor=='_' || valor=='$') return(1);
	return(0);
}

static void traduceparam(v10cursors *cur,char *sqlin)
{
	char *aux,*inicio;
	char variable[MAXPATH];
	cur->nbind=0;
	aux=sqlin;
	cur->bind=calloc(sizeof(campooras),MAXCAMPOS);
	while ((aux=strchr(aux,':'))!=NULL) {
		inicio=++aux;
		while (isvariable(*aux)) aux++;
		if (aux>inicio+1) {
		   strcopia(variable,inicio,aux-inicio);
		   if (campobind(cur,variable)==NULL) {
		      strcpy(cur->bind[cur->nbind].nombre,variable);
			  cur->nbind++;
			  v10log(LOGDEBUG,"Variable bind %s\n",variable);
		   }
		}
	}
}

static void creasqlpostgre(v10cursors *cur,char *sql)
{
	int i;
	char *ptr=sql,*inicio;
	strcpy(sql,cur->sql);
	for (i=0;i<cur->nbind;i++) {
		char variable[MAXPATH],param[MAXPATH];
		ptr=sql;
		sprintf(param,"$%d",i+1);
		sprintf(variable,":%s",cur->bind[i].nombre);
		while ((inicio=strstr(ptr,variable))!=NULL) {
			if (isvariable(inicio[strlen(variable)])==0) {
				strcpy(inicio,inicio+strlen(variable));
				strins(inicio,param);
			    ptr=inicio;
			} else ptr=inicio+1;
		}
	}
	v10log(LOGDEBUG,"Sentencia %s %s\n",cur->nombre ,sql);
	if (strncmp(sql,"BEGIN",5)==0 || strncmp(sql,"DECLARE",7)==0) {
		strins(sql,"DO LANGUAGE PLPGSQL $$");
		strcat(sql,"$$");
	}
}



int dbparsecursorpostgre(v10cursors *ret, char *sql, char *nombre, const char *funcion, const char *file, int line, int error, int debug)
{
    char sqlpostgre[MAXSQL];
    int ncamp;
    campooras *campo;
    int err;
    int *parametros;
    if (sql == NULL) return(-1);
    if (damelogins() == 0) {
        final(("No conectado a POSTGRE"));
        return(-1);
    }
    ret->sql = strdup(sql);
    sprintf(ret->nombre, "%s-%X", nombre, (int)((size_t)ret));
    traduceparam(ret, sql);
    creasqlpostgre(ret, sqlpostgre);
    ret->extra = calloc(1, sizeof(postgredatoscursor));
    pgconcur(ret) = CONNPG;
    parametros = calloc(ret->nbind, sizeof(int *));
    for (ncamp = 0; ncamp < ret->nbind; ncamp++) parametros[ncamp] = 1043;
    pgrescur(ret) = PQprepare(CONNPG, ret->nombre, sqlpostgre, ret->nbind, parametros);
    free(parametros);
    ret->errcode = PQresultStatus(pgrescur(ret));
    if (ret->errcode != PGRES_COMMAND_OK) {
        v10log(LOGERROR, "DECLARE CURSOR %s failed: %s", ret->nombre ,PQerrorMessage(CONNPG));
        if (error) cursordebug(ret);
        PQclear(pgrescur(ret));
        pgrescur(ret) = NULL;
        free(ret->extra);
        free(ret->sql);
        return(-1);
    }
    PQclear(pgrescur(ret));
    pgrescur(ret) = PQdescribePrepared(CONNPG, ret->nombre);
    err = PQresultStatus(pgrescur(ret));
    if (err != PGRES_COMMAND_OK) {
        v10log(LOGERROR, "DECLARE CURSOR %s failed: %s", ret->nombre ,PQerrorMessage(CONNPG));
        PQclear(pgrescur(ret));
        free(ret->extra);
        free(ret->sql);
        return(-1);
    }
    ret->ndef = PQnfields(pgrescur(ret));
    if (ret->ndef > 0) {
        ret->def = campo=calloc(sizeof(campooras), ret->ndef);
        if (ORATECLA) hay_tecla_normal();
        if (debugcursor(ret)&DEPURAPRELOG) v10log(LOGNORMAL, "Parse %s fich. %s %d\n", ret->nombre, ret->file, ret->line);
        if (debugcursor(ret)&DEPURAPARSE) cursordebug(ret);
        for (ncamp = 0; ncamp < ret->ndef; ncamp++) {
            campooras *c = campo + ncamp;
            strcpy(c->nombre, PQfname(pgrescur(ret), ncamp));
            c->oratipo = PQftype(pgrescur(ret), ncamp);
            c->oralen = PQfsize(pgrescur(ret), ncamp);
        }
        if (ret->ndef) ret->funsql = FSELECT;
        PQclear(pgrescur(ret));
        pgrescur(ret) = NULL;
    }
//	v10log(LOGNORMAL, "Analizado cursor %s\n", ret->nombre);
    return(0);
}

int dbejecutacursorpostgre(v10cursors *c)
{
	int ret;
	void **parametros;
	int nb;
    int antformat = v10formatdef;
	if (c==NULL) return(-1);
	if (pgrescur(c)) {
		PQclear(pgrescur(c));
		pgrescur(c)=NULL;
	}
	parametros=calloc(c->nbind,sizeof(void *));
    v10formatdef = v10formatdef & (~COMADECIMAL);
	for (nb=0;nb<c->nbind;nb++) {
		campooras *ca=c->bind+nb;
		if (ca->dato==NULL) final(("Variable %s sin bind\n",ca->nombre));
		if (ca->tipo!=V10CADENA) {
			parametros[nb]=calloc(1,MAXPATH);
			pasaoracampo2ascii(ca,parametros[nb],0,0);
		} else {
			parametros[nb]=ca->dato;
		}
	}
    v10formatdef = antformat;
    pgrescur(c)=PQexecPrepared(pgconcur(c),c->nombre,c->nbind,(void *)parametros,NULL,NULL,0);
	ret=PQresultStatus(pgrescur(c));
	if (ret!= PGRES_TUPLES_OK && ret!=PGRES_COMMAND_OK) {
		//v10log(LOGERROR, "FETCH ALL %s failed: %s\n", c->nombre,PQerrorMessage(pgconcur(c)));
		//PQclear(pgrescur(c));
		c->errcode=-1;
		return(-1);
	} else ret=0;
    c->filasprocesadas =atoi( PQcmdTuples(pgrescur(c)));
	c->fprocess=PQntuples(pgrescur(c));
	c->sprocess=0;
	//PQsetSingleRowMode(pgconcur(c));
	for (nb=0;nb<c->nbind;nb++) {
		campooras *ca=c->bind+nb;
		if (ca->tipo!=V10CADENA) {
			free(parametros[nb]);
		} 
	}
	free(parametros);
	c->errcode=0;
	return(ret);
}

int dbfetchcursorpostgre(v10cursors *c)
{
	int nd;
	if (c->sprocess>=c->fprocess) {
	    PQclear(pgrescur(c));
		pgrescur(c)=NULL;
	    return(NOFOUND);
	}
	for (nd=0;nd<c->ndef;nd++) {
		campooras *ca=c->def+nd;
		int tipo=ca->tipo;
		if (tipo==V10FECHA) tipo=V10LONG;
		a2v10tipo(ca->dato,tipo,0,0,PQgetvalue(pgrescur(c),c->sprocess,nd));
	}
	c->sprocess++;
	return(0);
}

int dbliberacursorpostgre(v10cursors *c)
{
	char sql[MAXPATH];
	int ret;
	if (c==NULL) return(-1);
	if (pgrescur(c)) {
		PQclear(pgrescur(c));
	}
	sprintf(sql,"DEALLOCATE \"%s\"",c->nombre);
	pgrescur(c)=PQexec(pgconcur(c),sql);
	ret = PQresultStatus(pgrescur(c));
	if (ret != PGRES_TUPLES_OK && ret != PGRES_COMMAND_OK) {
		v10log(LOGERROR, "DEALLOCATE %s failed: %s\n", c->nombre, PQerrorMessage(pgconcur(c)));
		//PQclear(pgrescur(c));
		c->errcode = -1;
		return (-1);
	} else ret = 0;
	PQclear(pgrescur(c));
	free(c->extra);
	return(0);
}

void dbdamecurerrorpostgre(v10cursors *c,char *buffer)
{
	strcpy(buffer,PQresultErrorMessage(pgrescur(c)));
}

dbdrivers dbpostgre={"POSTGRES",dbinitpostgre,dameerrorpostgre,dbdamecurerrorpostgre,NULL,dbcommitpostgre,dbrollbackpostgre,dblogoutpostgre,dbloginpostgre,
                      dbparsecursorpostgre,dbejecutacursorpostgre,NULL,NULL,NULL,
                      NULL,dbfetchcursorpostgre,NULL,NULL,NULL,NULL,dbliberacursorpostgre,NULL,0};

dbdrivers *damedriverpostgre(void)
{
	return(&dbpostgre);
}
/*
typedef struct {
	void (*dbinit)(void);
	void (*dameerror)(void   *error,char *mensaje);
	int (*dbcommit)(void);
	int (*dbrollback)(void);
	int (*dblogout)(void);
	int (*dblogin)(char *usuario,char *password,char *condb);
	v10cursors *(*dbparsecursor)(char *sql,char *nombre,const char *funcion,const char *file,int line,int error,int debug);
	int (*dbejecutacursor)(v10cursors *c);
	void (*dbpreparaarrayfetch)(v10cursors *cur,int nelem);
	int (*dbdefinecursor)(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo);
	int (*dbbindcursor)(v10cursors *c,char *ncamp,void *var,int lon,int v10tipo);
	int (*dbv10tipo)(int oratipo,int lonoracle,int precision,int escala,int *lon);
	int (*dbfetchcursor)(v10cursors *cur);
	int (*dbejefetchcursor)(v10cursors *cur);
	int (*dbcancelacursor)(v10cursors *cur);
	int (*dbliberacursor)(v10cursors *cur);
	int (*dbejecutaimmediatof)(char *sql,int debug,const char *funcion,const char *file,int line);
} dbdrivers;*/