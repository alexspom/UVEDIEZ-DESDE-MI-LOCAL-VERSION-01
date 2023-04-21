/*
* Módulo : V10DRVORACLE.C
* Objeto:  Manejo del bajo nivel de ORACLE
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10db.h"
#include "v10ora.h"
#include "v10oracle.h"
typedef struct {
               OCIError   *error;
               OCISvcCtx  *contexto;
               OCIServer  *server;
               OCISession *session;
               OCIEnv     *env;
} oradatoscon;

typedef struct {
         OCIStmt    *stmt;        // Puntero a sentencia V8
         OCISvcCtx  *lda;         // Puntero a context del servidor de la sentencia
         OCIError   *error;       // Puntero a error
} oradatoscursor;

#define LDA (((oradatoscon *)arrlogin[numlogins-1].extra)->contexto)
#define ERR (((oradatoscon *)arrlogin[numlogins-1].extra)->error)
#define ENV (((oradatoscon *)arrlogin[numlogins-1].extra)->env)
#define SERVER (((oradatoscon *)arrlogin[numlogins-1].extra)->server)
#define SESSION (((oradatoscon *)arrlogin[numlogins-1].extra)->session)

static OCIError *ulterror;
static char version[MAXCADENA];

#define orasmt(cur) (((oradatoscursor *)(cur->extra))->stmt)
#define oraerror(cur) (((oradatoscursor *)(cur->extra))->error)
#define oralda(cur) (((oradatoscursor *)(cur->extra))->lda)

void dbinitoracle(void)
{  
	OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,(dvoid * (*)(dvoid *, size_t)) 0,(dvoid * (*)(dvoid *, dvoid *, size_t))0,(void (*)(dvoid *, dvoid *)) 0 );
}

int rollbackoracle(void)
{
   int ret;
   ret=OCITransRollback(LDA,ERR,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        char mensaje[MAXCADENA];
        int error;
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
        v10log(LOGERROR,"Error en rollback %s\n",mensaje);
    }
    return(ret);
}

int commitoracle(void)
{
   int ret;
   ret=OCITransCommit(LDA,ERR,OCI_DEFAULT);
   return(ret);
}
static void getoraerror(char *buffer, OCIError *error)
{
	int err;
#ifndef __LINUX__
	__try {
#endif
		OCIErrorGet(error, 1, NULL, &err, buffer, MAXERRORORACLE, OCI_HTYPE_ERROR);
		if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = 0;
#ifndef __LINUX__
	} __except(EXCEPTION_CONTINUE_EXECUTION) {}
	;
#endif

}

int logoutoracle(void)
{
    int ret;
    int error;
    char mensaje[MAXCADENA];
    ret=OCISessionEnd(LDA,ERR,SESSION,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
        v10log(LOGERROR,"Error en SessionEnd %s\n",mensaje);
    }
    ret=OCIServerDetach(SERVER,ERR,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
        v10log(LOGERROR,"Error en ServerDetach %s\n",mensaje);
		return(ret);
    }
    OCIHandleFree(SERVER,OCI_HTYPE_SERVER);
    OCIHandleFree(SESSION,OCI_HTYPE_SESSION);
    OCIHandleFree(LDA,OCI_HTYPE_SVCCTX);
    OCIHandleFree(ENV,OCI_HTYPE_ENV);
	free(EXTRA);
	return(0);
}

static int analizaerror(OCIError *error)
{
    char mensaje[MAXCADENA];
    int err;
    OCIErrorGet(error,1,NULL,&err,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
    v10log(LOGERROR,"Error Oracle %d %s\n",err,mensaje);
    return(err);
}

int llloginoracle(char *usuario,char *password,char *condb)
{
	int err;
	EXTRA=calloc(1,sizeof(oradatoscon));
	err=OCIEnvCreate(&ENV,OCI_DEFAULT,NULL,NULL,NULL,NULL,0,NULL);
	if (err) {
		err=analizaerror((void *)ENV);
	}
	err=OCIHandleAlloc(ENV,(void **)&LDA,OCI_HTYPE_SVCCTX,0,0);
	if (err) return(-1);
	err=OCIHandleAlloc(ENV,(void **)&SERVER,OCI_HTYPE_SERVER,0,0);
	if (err) return(-1);
	err=OCIHandleAlloc(ENV,(void **)&ERR,OCI_HTYPE_ERROR,0,0);
	if (err) return(-1);
	ulterror=ERR;
	err=OCIServerAttach(SERVER,ERR,condb,strlen(condb),OCI_DEFAULT);
	if (err==OCI_ERROR) return(-1);
	err=OCIAttrSet(LDA, OCI_HTYPE_SVCCTX, SERVER,0, OCI_ATTR_SERVER,ERR);
	if (err) return(-1);
	err=OCIServerVersion(SERVER,ERR,version,sizeof(version)-1,OCI_HTYPE_SERVER);
	err=OCIHandleAlloc(ENV,(void **)&SESSION,OCI_HTYPE_SESSION,0,0);
	if (err) return(-1);
	err=OCIAttrSet(SESSION,OCI_HTYPE_SESSION,usuario,strlen(usuario),OCI_ATTR_USERNAME,ERR);
	if (err) return(-1);
	err=OCIAttrSet(SESSION,OCI_HTYPE_SESSION,password,strlen(password),OCI_ATTR_PASSWORD,ERR);
	if (err) return(-1);
	err=OCISessionBegin(LDA,ERR,SESSION,OCI_CRED_RDBMS,OCI_DEFAULT);
	if (err) {
		err=analizaerror(ERR);
		return(err);
	}
	err=OCIAttrSet(LDA,OCI_HTYPE_SVCCTX,SESSION, 0, OCI_ATTR_SESSION,ERR);
	if (err) return(-1);
	OCIAttrGet(LDA,OCI_HTYPE_SVCCTX,&err,NULL,OCI_ATTR_SQLCODE,ERR);
    ulterror=ERR;
	return(err);
}

int loginoracle(char *usuario,char *password,char *condb)
{
	int ret;
	ret=llloginoracle(usuario,password,condb);
	if (ret) {
		char destino[MAXCADENA];
		getoraerror(destino, ERR);
		v10log(LOGERROR, "Error al conectar %s\n", destino);
		if (SESSION) OCIHandleFree(SESSION,OCI_HTYPE_SESSION);
		if (ERR) OCIHandleFree(ERR,OCI_HTYPE_ERROR);
		if (SERVER) OCIHandleFree(SERVER,OCI_HTYPE_SERVER);
		if (LDA) OCIHandleFree(ENV,OCI_HTYPE_SVCCTX);
		if (ENV) OCIHandleFree(ENV,OCI_HTYPE_ENV);
		if (EXTRA) free(EXTRA);
	}
	return(ret);
}

int libera_stmt(OCIStmt *stmt)
{
   int ret;
   if (stmt) {
      ret=OCIHandleFree((void *)stmt,OCI_HTYPE_STMT);
      if (ret) return(ret);
    }
   return(0);
}

int describeoci8(OCIStmt *stmt,OCIError *error)
{
  OCIStmtExecute(LDA,stmt,error,1,0,NULL,NULL,OCI_DESCRIBE_ONLY);
  return(0);
}


int analiza_stmt(OCIStmt **stmt,char *cadena,OCIError *error)
{
   int ret;
   short funcion;
   *stmt=NULL;
   if (numlogins==0) return(NOTLOGGED);
   ret=OCIHandleAlloc(ENV,(void **)stmt,OCI_HTYPE_STMT,0,0);
   if (ret) {
      OCIHandleFree(*stmt,OCI_HTYPE_STMT);
      *stmt=NULL;
      v10log(LOGERROR,"No puedo alocar handle error %d\n",ret);
      return(ret);
    }
   ret=OCIStmtPrepare(*stmt,error,cadena,strlen(cadena),OCI_NTV_SYNTAX,OCI_DEFAULT);
   ulterror=error;
   if (ret) {
       int err;
       err=analizaerror(error);
       return(err);
    }
   if (ret!=OCI_SUCCESS) return(ret);
   if (strcmp(version,"Oracle8i")<0) {
      ret=OCIStmtExecute(LDA,*stmt,error,1,0,NULL,NULL,OCI_DESCRIBE_ONLY);
      if (ret==OCI_SUCCESS) return(0);
      if ((ret=getnumoraerror(error))==NOSELECT) return(0);
    } else {
      ret=OCIStmtExecute(LDA,*stmt,error,1,0,NULL,NULL,OCI_PARSE_ONLY);
      OCIAttrGet(*stmt,OCI_HTYPE_STMT,&funcion,NULL,OCI_ATTR_SQLFNCODE,OCIERROR());
      if (funcion==4) {
         ret=OCIStmtPrepare(*stmt,error,cadena,strlen(cadena),OCI_NTV_SYNTAX,OCI_DEFAULT);
         ret=OCIStmtExecute(LDA,*stmt,error,1,0,NULL,NULL,OCI_DESCRIBE_ONLY);
       }
      if (ret==OCI_SUCCESS) return(0);
      if ((ret=getnumoraerror(error))==NOSELECT) return(0);
    }
   return(ret);
}


int reanaliza_stmt(OCIStmt *stmt,char *sentencia,OCIError *error)
{
  int ret;
  ret=OCIStmtPrepare(stmt,error,sentencia,strlen(sentencia),OCI_NTV_SYNTAX,OCI_DEFAULT);
  ulterror=error;
  return(ret);
}

int ejecuta_stmt(OCISvcCtx *lda,OCIStmt *stmt,int iters,int modo,OCIError *error)
{
  int ret;
  ret=OCIStmtExecute(lda,stmt,error,iters,0,NULL,NULL,modo);
  ulterror=error;
   if (ret==OCI_ERROR || ret==OCI_NO_DATA) {
      ret=getnumoraerror(error);
    } else ret=0;
  return(ret);
}

int fetch_stmt(OCIStmt *stmt,int numrows,OCIError *error)
{
   int ret;
   ret=OCIStmtFetch(stmt,error,numrows,OCI_FETCH_NEXT,OCI_DEFAULT);
   ulterror=error;
   if (ret==OCI_ERROR || ret==OCI_NO_DATA) {
      ret=getnumoraerror(error);
    } else ret=0;
   return(ret);
}

int ejefetch_stmt(OCISvcCtx *lda,OCIStmt *stmt,OCIError *error)
{
  int ret;
  ret=ejecuta_stmt(lda,stmt,1,OCI_DEFAULT,error);
  return(ret);
}

int v10tipo2ora(int tipo,int lon)
{
   int oratipo=0;
   switch (tipo) {
         case V10INT:
         case V10SHORT:
         case V10LONG:
         case V10FECHA:
         case V10BYTE:oratipo=SQLT_INT;
             break;
         case V10UINT:
         case V10USHORT:
         case V10ULONG:oratipo=SQLT_UIN;
             break;
         case V10FLOAT:
         case V10HORA:
         case V10DOUBLE:oratipo=SQLT_FLT;
             break;
         case V10CADENA:if (lon < 32000000) oratipo = SQLT_STR; else oratipo = SQLT_LNG;
             break;
         case OCIROWID:oratipo=SQLT_RDD;
             break;
    }
   return(oratipo);
}


int define_stmt(OCIStmt *stmt,int pos,void *var,int lon,int tipo,short *indicador,short *err,OCIError *error)
{
   int ret;
   OCIDefine *def=NULL;
   short oratipo;
   oratipo=(short)v10tipo2ora(tipo,lon);
   ret=OCIDefineByPos(stmt,&def,error,pos,var,lon,oratipo,indicador,NULL,(ub2 *)err,OCI_DEFAULT);
   ulterror=error;
   if (ret==OCI_ERROR) {
      ret=getnumoraerror(error);
    } else ret=0;
   return(ret);
}

int bind_stmt(OCIStmt *stmt,char *nombre,void *var,int lon,int tipo,OCIError *error)
{
   OCIBind *bind=NULL;
   short oratipo;
   int ret;
   oratipo=(short)v10tipo2ora(tipo,lon);
   ret=OCIBindByName(stmt,&bind,error,nombre,strlen(nombre),var,lon,oratipo,NULL,NULL,NULL,0,NULL,OCI_DEFAULT);
   ulterror=error;
   if (ret==OCI_ERROR) {
      ret=getlastnumoraerror();
    } else ret=0;
   return(ret);
}

int getnumoraerror(OCIError *error)
{
   char texto[MAXCADENA];
   int err,ret;
   ret=OCIErrorGet(error,1,NULL,&err,texto,sizeof(texto),OCI_HTYPE_ERROR);
   if (ret==100) return(0);
   return(err);
}

int getcurnumerror(v10cursors *cur)
{
    int err;
    err=getnumoraerror(oraerror(cur));
    return(err);
}

int getlastnumoraerror(void)
{
   int err;
   err=getnumoraerror(ulterror);
   return(err);
}


void getcurerrororacle(v10cursors *cur,char *buffer)
{
    getoraerror(buffer,oraerror(cur));
}


void getlastoraerror(char *buffer)
{
    if (ulterror==NULL) {
        strcpy(buffer,"Ninguna llamada a ORACLE");
        return;
    }
    getoraerror(buffer,ulterror);
}


OCIError *OCIERROR(void)
{
  return(ERR);
}

OCISvcCtx *OCILDA(void)
{
  return(LDA);
}

OCIEnv *OCIENV(void)
{
  return(ENV);
}

#define MAXDEBUGID 101
#define MAXBITDEBUG 16
char *(depuracursor[MAXBITDEBUG]);
#define PONDEBUGPID "DECLARE RET VARCHAR2(50);BEGIN RET:=DBMS_DEBUG.INITIALIZE(:PID);DBMS_DEBUG.DEBUG_ON;END;"
static v10cursors *v10pondebugpid;
static char spid[MAXDEBUGID];
#define PONDEBUGOFF "BEGIN DBMS_DEBUG.DEBUG_OFF;END;"
static v10cursors *v10pondebugoff;

static void finoraclehl(void)
{
    int i;
    liberacursor(v10pondebugpid);
    liberacursor(v10pondebugoff);
    for (i=0;i<MAXBITDEBUG;i++) free(depuracursor[i]);
}

static void initoraclehl(void)
{
    v10pondebugpid=abrecursordebug(PONDEBUGPID,0);
    bindtodo(v10pondebugpid,"PID",spid,sizeof(spid),V10CADENA,
        NULL);
    sprintf(spid,"AA%ld",GetCurrentProcessId());
    v10pondebugoff=abrecursordebug(PONDEBUGOFF,0);
    atexit(finoraclehl);
}
/*
void anadecursordebug(int mascara,char *listacur)
{
    int i;
    v10cursors *ptr=rcursor;
    for (i=0;i<MAXBITDEBUG;i++) {
        if (mascara&(1<<i)) {
            if (depuracursor[i]==NULL) {
                depuracursor[i]=strdup(listacur);
            } else {
                depuracursor[i]=realloc(depuracursor[i],strlen(depuracursor[i])+strlen(listacur)+1);
                strcat(depuracursor[i],listacur);
            }
        }
    }
    while (ptr) {
        if (contiene(listacur,ptr->nombre)) {
            ptr->debug=mascara;
        }
        ptr=ptr->next;
    }
}

static void pondebugexterno(void)
{
    if (v10pondebugpid==NULL) initoraclehl();
    ejecutacursor(v10pondebugpid);
}

static void pondebugoff(void)
{
    if (v10pondebugoff==NULL) initoraclehl();
    ejecutacursor(v10pondebugoff);
}
*/

int parsecursororacle(v10cursors *ret,char *sql,char *nombre,const char *funcion,const char *file,int line,int error,int debug)
{
    int ncamp;
    OCIError *ocierr;
    campooras *campo;
    int err;
    int nbind=0;
    OCIStmt *stmt;
    if (sql==NULL) return(-1);
    if (damelogins()==0) {
        final(("No conectado a ORACLE"));
        return(-1);
    }
    err=OCIHandleAlloc(OCIENV(),(void **)&ocierr,OCI_HTYPE_ERROR,0,0);
    err=analiza_stmt(&stmt,sql,ocierr);
    if (err==NOTLOGGED) {
        if (error) final(("No esta conectado a la BASE DE DATOS"));
        return(-1);
    }
    campo=calloc(sizeof(campooras),MAXCAMPOS);
	ret->extra=calloc(1,sizeof(oradatoscursor));
    oraerror(ret)=ocierr;
    strcpy(ret->nombre,nombre);
    ret->sql=strdup(sql);
    if (ORATECLA) hay_tecla_normal();
    orasmt(ret)=stmt;
    oralda(ret)=OCILDA();
    OCIAttrGet(orasmt(ret),OCI_HTYPE_STMT,&ret->parseerror,NULL,OCI_ATTR_PARSE_ERROR_OFFSET,OCIERROR());
    OCIAttrGet(orasmt(ret),OCI_HTYPE_STMT,&ret->funsql,NULL,OCI_ATTR_SQLFNCODE,OCIERROR());
    if (debugcursor(ret)&DEPURAPRELOG) v10log(LOGNORMAL,"Parse %s fich. %s %d\n",ret->nombre,ret->file,ret->line);
    if (err==0) ret->errcode=0;
    else     ret->errcode=(short)getcurnumerror(ret);
    if (debugcursor(ret)&DEPURAPARSE) cursordebug(ret);
    if (ret->errcode) {
        if (error) cursordebug(ret);
        libera_stmt(orasmt(ret));
        free(campo);
        free(ret->sql);
		free(ret->extra);
        return(-1);
    }
    OCIAttrGet(orasmt(ret),OCI_HTYPE_STMT,&ret->ndef,NULL,OCI_ATTR_PARAM_COUNT,OCIERROR());
    for (ncamp=0;;ncamp++) {
        char *nombre;
        int lnombre;
        short dbsize=0;
        short tipo=0;
        short prec=0,scale=0,nulos=0;
        OCIParam *param=NULL;
        campooras *c=campo+ncamp;
        err=OCIParamGet(orasmt(ret),OCI_HTYPE_STMT,OCIERROR(),(void **)&param,ncamp+1);
        if (err!=OCI_SUCCESS || param==NULL) break;
        OCIAttrGet(param,OCI_DTYPE_PARAM,&nombre,(ub4 *)&lnombre,OCI_ATTR_NAME,OCIERROR());
        OCIAttrGet(param,OCI_DTYPE_PARAM,&dbsize,0,OCI_ATTR_DATA_SIZE,OCIERROR());
        OCIAttrGet(param,OCI_DTYPE_PARAM,&tipo,0,OCI_ATTR_DATA_TYPE,OCIERROR());
        OCIAttrGet(param,OCI_DTYPE_PARAM,&prec,0,OCI_ATTR_PRECISION,OCIERROR());
        OCIAttrGet(param,OCI_DTYPE_PARAM,&scale,0,OCI_ATTR_SCALE,OCIERROR());
        OCIAttrGet(param,OCI_DTYPE_PARAM,&nulos,0,OCI_ATTR_IS_NULL,OCIERROR());
        c->oratipo=tipo;
        c->oralen=dbsize;
        c->prec=prec;
        c->scale=scale;
        c->nullok=nulos;
        if (lnombre>=MAXNOMBREV10) lnombre=MAXNOMBREV10-1;
        strcopia(c->nombre,nombre,lnombre);
    }
    ret->ndef=ncamp;
    ret->def=campo;
    if (ncamp) ret->def=realloc(campo,ncamp*sizeof(campooras));
    else    {
        free(campo);
        ret->def=NULL;
    }
    campo=calloc(sizeof(campooras),MAXCAMPOS);
    for (ncamp=0;;ncamp++) {
        int cuantos;
        char *nombre,*indicator;
        char lon,lindicator,dup;
        int err;
        OCIBind *handle;
        campooras *c=campo+nbind;
        err=OCIStmtGetBindInfo(orasmt(ret),OCIERROR(),1,ncamp+1,&cuantos,(OraText **)&nombre,&lon,(OraText **)&indicator,&lindicator,&dup,&handle);
        if (err!=OCI_SUCCESS) break;
        if (dup) continue;
        nbind++;
        if (lon>=MAXNOMBREV10) lon=MAXNOMBREV10-1;
        strcopia(c->nombre,nombre,lon);

    }
    ret->bind=campo;
    ret->nbind=nbind;
    if (nbind) ret->bind=realloc(campo,nbind*sizeof(campooras));
    else {
        free(campo);
        ret->bind=NULL;
    }
    return(0);
}

int definecursororacle(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo)
{
    OCIDefine *def=NULL;
    short oratipo;
    int ret;
    campooras *c=cur->def+ncamp-1;
    if (cur->invalido) arreglainvalidooracle(cur);
    if (cur->ndef) describeoci8(orasmt(cur),oraerror(cur));
    oratipo=(short) v10tipo2ora(v10tipo,lon);
    ret=OCIDefineByPos(orasmt(cur),&def,OCIERROR(),ncamp,var,lon,oratipo,&c->indicador,NULL,&c->error,OCI_DEFAULT);
    cur->funoci=6;
    if (ret==0) cur->errcode=0;
    else     cur->errcode=(short)getcurnumerror(cur);
    return(ret);
}

int arreglainvalidooracle(v10cursors *cur)
{
    OCIStmt *stmt;
    OCIError *ocierr;
    int err;
    int nc;
    if (cur->invalido==0) return(0);
    if (cur==NULL) return(-1L);
    cur->invalido=0;
    err=OCIHandleAlloc(OCIENV(),(void **)&ocierr,OCI_HTYPE_ERROR,0,0);
    err=analiza_stmt(&stmt,cur->sql,ocierr);
    orasmt(cur)=stmt;
    oraerror(cur)=ocierr;
    oralda(cur)=OCILDA();
    OCIAttrGet(orasmt(cur),OCI_HTYPE_STMT,&cur->parseerror,NULL,OCI_ATTR_PARSE_ERROR_OFFSET,OCIERROR());
    OCIAttrGet(orasmt(cur),OCI_HTYPE_STMT,&cur->funsql,NULL,OCI_ATTR_SQLFNCODE,OCIERROR());
    for (nc=0;nc<cur->ndef;nc++) {
        definecursor(cur,nc+1,cur->def[nc].dato,cur->def[nc].lon,cur->def[nc].tipo);
    }
    for (nc=0;nc<cur->nbind;nc++) {
        bindcursor(cur,cur->bind[nc].nombre,cur->bind[nc].dato,cur->bind[nc].lon,cur->bind[nc].tipo);
    }
    return(0);
}

int bindcursororacle(v10cursors *c,char *ncamp,void *var,int lon,int v10tipo)
{
    OCIBind *bind=NULL;
    short oratipo;
    int ret;
    campooras *ca;
    ca=campobind(c,ncamp);
    if (c->invalido) arreglainvalidooracle(c);
    oratipo=(short)v10tipo2ora(v10tipo,lon);
    ca->oratipo=oratipo;
    ret=OCIBindByName(orasmt(c),&bind,OCIERROR(),ncamp,strlen(ncamp),var,lon,oratipo,&ca->indicador,NULL,(ub2 *)&ca->error,0,NULL,OCI_DEFAULT);
    c->funoci=8;
    if (ret==0) c->errcode=0;
    else     c->errcode=(short)getcurnumerror(c);
    return(ret);
}

int oracle2v10tipo(int oratipo,int lonoracle,int precision,int escala,int *lon)
{
    switch (oratipo) {
        case OCIINT:
            *lon=sizeof(long);
            return(V10LONG);
            break;
    	case OCIUNSIGNED:
            *lon=sizeof(unsigned long);
            return(V10ULONG);
            break;
        case OCIDOUBLE:
            *lon=sizeof(double);
            return(V10DOUBLE);
            break;
        case OCINUMBER:
            if ((precision==0 && escala==0) || escala != 0) {
               *lon=sizeof(double);
               return(V10DOUBLE);
            } else {
              *lon=sizeof(long);
              return(V10LONG);
            }
            break;
        case OCIDATE:
            *lon=sizeof(char) * (20);
            return(V10CADENA);
            break;
        case OCILONG:
        case OCILONGRAW:
        case OCIRAW:
        case OCIROWID:
        case OCICADENA:
        case OCICHAR:
            *lon=sizeof(char) * (lonoracle + 1);
            return(V10CADENA);
            break;
        default:
            *lon=sizeof(char) * (lonoracle + 1);
            return(V10CADENA);
            break;
    }
}


int ejecutacursorarrayoracle(v10cursors *c,int iter)
{
  int ret;
  if (c->invalido) arreglainvalidooracle(c);
  if (c->funsql==FSELECT) {
     long prefetch=10;
     iter=0;
     OCIAttrSet(orasmt(c), OCI_HTYPE_STMT, &prefetch,0,OCI_ATTR_PREFETCH_ROWS,OCIERROR());
   }
  if (iter>1) {
      int nb;
      for (nb=0;nb<c->nbind;nb++) {
          campooras *ca=c->bind+nb;
          OCIBind *bind=NULL;
          ret=OCIBindByName(orasmt(c),&bind,OCIERROR(),ca->nombre,strlen(ca->nombre),ca->dato,ca->lon,(short)ca->oratipo,NULL,NULL,(ub2 *)&ca->error,0,NULL,OCI_DEFAULT);
      }
  }
  if (debugcursor(c)&DEPURAPRELOG) v10log(LOGNORMAL,"Ejecuta %s fich. %s %d\n",c->nombre,c->file,c->line);
// if (debugcursor(c)&DEPURAEXTERNO) pondebugexterno();
  ret=ejecuta_stmt(oralda(c),orasmt(c),iter,OCI_DEFAULT,oraerror(c));
//  if (debugcursor(c)&DEPURAEXTERNO) pondebugoff();
  if (ret==0) {
     OCIAttrGet(orasmt(c),OCI_HTYPE_STMT,&c->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
     c->errcode=0;
   } else {
     c->filasprocesadas=0;
     c->errcode=(short)getcurnumerror(c);
   }
  if (contienenum(ERRINVALIDA,c->errcode)==1) c->invalido=1;
  return(c->errcode);
}

int ejecutacursororacle(v10cursors *c)
{
  int ret;
  ret=ejecutacursorarray(c,1);
  return(ret);
}

void preparaarrayfetchoracle(v10cursors *cur,int nelem)
{
  unsigned lon;
  int nc,ret;
  if (cur==NULL) return;
  if (cur->invalido) arreglainvalidooracle(cur);
  cur->nelem=nelem;
  if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Array fetch %s fich. %s %d elem %d\n",cur->nombre,cur->file,cur->line,cur->nelem);
  lon=0;
  for (nc=0;nc<cur->ndef;nc++) {
      lon+=cur->def[nc].lon;
      lon+=sizeof(short)+sizeof(short);
    }
  cur->tam=lon;
  if (cur->buffer) free(cur->buffer);
  cur->buffer=calloc(lon,nelem);
  cur->fprocess=0;
  cur->sprocess=0;
  lon=0;
  for (nc=0;nc<cur->ndef;nc++) {
      int  tipo=cur->def[nc].tipo;
      int lon1=lon+cur->def[nc].lon;
      int lon2=lon1+sizeof(short);
      ret=define_stmt(orasmt(cur),nc+1,cur->buffer+lon*nelem,cur->def[nc].lon,tipo,(short *)(cur->buffer+lon1*nelem),(short *)(cur->buffer+lon2*nelem),oraerror(cur));
      if (ret) final(("Error al definir para array fetch"));
      lon=lon2+sizeof(short);
   }
}


int fetchcursororacle(v10cursors *cur)
{
    int ret,nc;
    unsigned lon;
    long antcount=cur->filasprocesadas;
    if (cur->nelem==0) {
        ret=fetch_stmt(orasmt(cur),1,oraerror(cur));
        OCIAttrGet(orasmt(cur),OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
    } else {
        if (cur->fprocess==0) {
            if (cur->arrerr==0) {
                cur->arrerr=fetch_stmt(orasmt(cur),cur->nelem,oraerror(cur));
                OCIAttrGet(orasmt(cur),OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
                cur->funoci=12;
            }
            cur->fprocess=(unsigned)(cur->filasprocesadas-antcount);
            cur->sprocess=0;
            cur->filasprocesadas=antcount;
        }
        if (cur->fprocess==0) {
            ret=cur->errcode=(short)cur->arrerr;
        } else {
            campooras *c=cur->def;
            lon=0;
            for (nc=0;nc<cur->ndef;nc++) {
                int lon1=lon+c->lon;
                int lon2=lon1+sizeof(short);
                memmove(c->dato,cur->buffer+lon*cur->nelem+cur->sprocess*c->lon,c->lon);
                c->indicador=*(short *)(cur->buffer+lon1*cur->nelem+cur->sprocess*sizeof(short));
                c->error=*(short *)(cur->buffer+lon2*cur->nelem+cur->sprocess*sizeof(short));
                lon+=c->lon+2*sizeof(short);
                c++;
            }
            cur->sprocess++;
            cur->fprocess--;
			cur->filasprocesadas++;
            ret=0;
        }
    }
    return(ret);
}

int ejefetchcursororacle(v10cursors *cur)
{
    int ret;
    if (cur->invalido) arreglainvalidooracle(cur);
//   if (debugcursor(cur)&DEPURAEXTERNO) pondebugexterno();
    ret=ejefetch_stmt(oralda(cur),orasmt(cur),oraerror(cur));
//    if (debugcursor(cur)&DEPURAEXTERNO) pondebugoff();
    if (ret==0) {
        OCIAttrGet(orasmt(cur),OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
    }
    if (contienenum(ERRINVALIDA,cur->errcode)==1) cur->invalido=1;
    cur->funoci=56;
    return(ret);
}

int liberacursororacle(v10cursors *cur)
{
	cancelacursor(cur);
    if (cur->invalido==0) {
        libera_stmt(orasmt(cur));
        OCIHandleFree((void *)oraerror(cur),OCI_HTYPE_ERROR);
		free(cur->extra);
    }
    return(0);
}

static dbdrivers dboracle={"ORACLE",dbinitoracle,getcurerrororacle,getcurerrororacle,getlastoraerror,commitoracle,rollbackoracle,logoutoracle,
                           loginoracle,parsecursororacle,ejecutacursororacle,preparaarrayfetchoracle,
                           definecursororacle, bindcursororacle, oracle2v10tipo, fetchcursororacle, ejefetchcursororacle, ejecutacursorarrayoracle,
						   arreglainvalidooracle,NULL,liberacursororacle,NULL,1};

dbdrivers *damedriveroracle(void)
{
	return(&dboracle);
}