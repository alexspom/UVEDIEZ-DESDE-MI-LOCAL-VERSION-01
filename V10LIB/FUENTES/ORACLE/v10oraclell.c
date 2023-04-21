/*
* Módulo : V10ORACLELL.C
* Objeto:  Manejo del bajo nivel de ORACLE
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10ora.h"

#define NOSELECT 24333
#define FUNCOMMIT   54
#define FUNROLLBACK 55

#define MAXLUSER    31

#define MAXLOGIN    500
#define LDA (arrlogin[numlogins-1].contexto)
#define ERR (arrlogin[numlogins-1].error)
#define ENV (arrlogin[numlogins-1].env)
#define SERVER (arrlogin[numlogins-1].server)
#define SESSION (arrlogin[numlogins-1].session)


typedef struct {
               OCIError   *error;
               OCISvcCtx  *contexto;
               OCIServer  *server;
               OCISession *session;
               OCIEnv     *env;
              } logins;
static logins    *arrlogin;
static int numlogins;

int ABRAZO=60;
int FSELECT=4;
int NOFOUND=1403;
int DUPLICADO=1;
int BLOQUEADO=54;

static OCIError *ulterror;

char ORAUSR[MAXLUSER*3];
char ORAPWD[MAXLUSER*2];
char ORADB[MAXLUSER];
int defparse=0;
short deflang=1;

static char version[MAXCADENA];

void (*trigerconecta)(void);
void (*trigerlogout)(void);



static void finoraarrlogin(void)
{
//  while (numlogins>0) logout();
  free(arrlogin);
//  OCITerminate(OCI_DEFAULT);
}

static void initoraarrlogin(void)
{
  arrlogin=calloc(MAXLOGIN,sizeof(logins));
  OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,(dvoid * (*)(dvoid *, size_t)) 0,(dvoid * (*)(dvoid *, dvoid *, size_t))0,(void (*)(dvoid *, dvoid *)) 0 );
  atexit(finoraarrlogin);
}

#define CROLLBACKCOND "BEGIN "\
                      " IF dbms_transaction.step_id IS NOT NULL THEN ROLLBACK; "\
                       " END IF; "\
                    "END;"
v10cursors *v10rollback;


int rollback(void)
{
    int ret;
    int(*oldhandleoraerr)(int coderr, v10cursors *c) = handleoraerr;
    handleoraerr = NULL;
    if (v10rollback == NULL) v10rollback = abrecursordebug(CROLLBACKCOND, DEPURAVDNOLOG);
    ret = ejecutacursor(v10rollback);
    handleoraerr = oldhandleoraerr;
    return(ret);
   ret=OCITransRollback(LDA,ERR,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        char mensaje[MAXCADENA];
        int error;
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
	    if (handleoraerr) handleoraerr(error,NULL);
        v10log(LOGERROR,"Error en rollback %s\n",mensaje);
    }
    return(ret);
}

#define CCOMMITCOND "BEGIN "\
                      " IF dbms_transaction.step_id IS NOT NULL THEN COMMIT; "\
                       " END IF; "\
                    "END;"
v10cursors *v10commit;

int commit(void)
{
   int ret;
   int(*oldhandleoraerr)(int coderr, v10cursors *c)=handleoraerr;
   handleoraerr = NULL;
   if (v10commit == NULL) v10commit = abrecursordebug(CCOMMITCOND, DEPURAVDNOLOG);
   ret = ejecutacursor(v10commit);
   handleoraerr = oldhandleoraerr;
   return(ret);
   ret=OCITransCommit(LDA,ERR,OCI_DEFAULT);
   return(ret);
}

static void libera_arrlogin(void)
{
    int ret;
    int error;
    char mensaje[MAXCADENA];
    invalidacursoresLDA(LDA);
    ret=OCISessionEnd(LDA,ERR,SESSION,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
        v10log(LOGERROR,"Error en SessionEnd %s\n",mensaje);
    }
    ret=OCIServerDetach(SERVER,ERR,OCI_DEFAULT);
    if (ret!=OCI_SUCCESS) {
        OCIErrorGet(ERR,1,mensaje,&error,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
        v10log(LOGERROR,"Error en ServerDetach %s\n",mensaje);
    }
    OCIHandleFree(SERVER,OCI_HTYPE_SERVER);
    OCIHandleFree(SESSION,OCI_HTYPE_SESSION);
    OCIHandleFree(LDA,OCI_HTYPE_SVCCTX);
    OCIHandleFree(ENV,OCI_HTYPE_ENV);
}

static int analizaerror(OCIError *error)
{
    char mensaje[MAXCADENA];
    int err;
    OCIErrorGet(error,1,NULL,&err,mensaje,sizeof(mensaje),OCI_HTYPE_ERROR);
    v10log(LOGERROR,"Error Oracle %d %s\n",err,mensaje);
    return(err);
}


int logout(void)
{
   if (numlogins<=0) final(("Logout sin conectar a base de datos"));
   if (trigerlogout) trigerlogout();
   rollback();
   libera_arrlogin();
   numlogins--;
   if (numlogins) ulterror=ERR;
   	else     ulterror=NULL;
   return(0);
}

static int lllogin(char *nombre,char *pass,char *db)
{
   char usuario[MAXLUSER*3],password[MAXLUSER*2]="",condb[MAXLUSER]="";
   static int err;
   strcpy(usuario,nombre);
   if (!es_blanco(pass)) strcpy(password,pass);
      else  {
         char *aux=strchr(usuario,'/');
         if (aux) {
            *aux=0;
            strcpy(password,aux+1);
          }
    }
   if (!es_blanco(db)) strcpy(condb,db);
     else {
         char *aux=strchr(password,'@');
         if (aux) {
            *aux=0;
            strcpy(condb,aux+1);
          }
      }
   strcpy(ORAUSR,usuario);
   strcpy(ORAPWD,password);
   strcpy(ORADB,condb);
// err=OCIEnvInit(&ENV,OCI_DEFAULT,0,0);
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
   err=OCIServerAttach(SERVER,ERR,condb,(sb4)strlen(condb),OCI_DEFAULT);
   if (err==OCI_ERROR) return(-1);
   err=OCIAttrSet(LDA, OCI_HTYPE_SVCCTX, SERVER,0, OCI_ATTR_SERVER,ERR);
   if (err) return(-1);
   err=OCIServerVersion(SERVER,ERR,version,sizeof(version)-1,OCI_HTYPE_SERVER);
   err=OCIHandleAlloc(ENV,(void **)&SESSION,OCI_HTYPE_SESSION,0,0);
   if (err) return(-1);
   err = OCIAttrSet(SESSION, OCI_HTYPE_SESSION, usuario, (ub4)strlen(usuario), OCI_ATTR_USERNAME, ERR);
   if (err) return(-1);
   err = OCIAttrSet(SESSION, OCI_HTYPE_SESSION, password, (ub4)strlen(password), OCI_ATTR_PASSWORD, ERR);
   if (err) return(-1);
   err=OCISessionBegin(LDA,ERR,SESSION,OCI_CRED_RDBMS,OCI_DEFAULT);
   if (err) {
       err=analizaerror(ERR);
       return(err);
   }
   err=OCIAttrSet(LDA,OCI_HTYPE_SVCCTX,SESSION, 0, OCI_ATTR_SESSION,ERR);
   if (err) return(-1);
   return(err);
}

static int oralogin(char *uid,char *pwd,char *db,int error)
{
  int ret;
  if (uid==NULL) final(("Debe dar nombre de usuario"));
  if (arrlogin==NULL) initoraarrlogin();
  if (numlogins-1>=MAXLOGIN) final(("Demasiados logins Max %d",MAXLOGIN));
  numlogins++;
  ret=lllogin(uid,pwd,db);
  ulterror=ERR;
  if (ret) {
     ret=getnumoraerror(ERR);
     if (error) errlda();
     libera_arrlogin();
     numlogins--;
   }  else {
     OCIAttrGet(LDA,OCI_HTYPE_SVCCTX,&ret,NULL,OCI_ATTR_SQLCODE,ERR);
     if (trigerconecta) trigerconecta();
   }
  return(ret);
}

int loginne(char *uid,char *pwd,char *db)
{
  return(oralogin(uid,pwd,db,0));
}

int login(char *uid,char *pwd,char *db)
{
  return(oralogin(uid,pwd,db,1));
}

int damelogins(void)
{
  return(numlogins);
}

int relogin(void)
{
  int ret;
  ret=login(ORAUSR,ORAPWD,ORADB);
  return(ret);
}

int damenumlogin(void)
{
    return(numlogins-1);
}

int reusanumlogin(int ncon)
{
  int ret;
  ret=numlogins-1;
  numlogins=ncon+1;
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
   ret = OCIStmtPrepare(*stmt, error, cadena, (ub4)strlen(cadena), OCI_NTV_SYNTAX, OCI_DEFAULT);
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
		  ret = OCIStmtPrepare(*stmt, error, cadena, (ub4)strlen(cadena), OCI_NTV_SYNTAX, OCI_DEFAULT);
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
  ret = OCIStmtPrepare(stmt, error, sentencia, (ub4)strlen(sentencia), OCI_NTV_SYNTAX, OCI_DEFAULT);
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

int v10tipo2ora(int tipo)
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
         case V10CADENA:oratipo=SQLT_STR;
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
   oratipo=(short)v10tipo2ora(tipo);
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
   oratipo=(short)v10tipo2ora(tipo);
   ret = OCIBindByName(stmt, &bind, error, nombre, (sb4)strlen(nombre), var, lon, oratipo, NULL, NULL, NULL, 0, NULL, OCI_DEFAULT);
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
    err=getnumoraerror(cur->error);
    return(err);
}

int getlastnumoraerror(void)
{
   int err;
   err=getnumoraerror(ulterror);
   return(err);
}

static void getoraerror(char *buffer,OCIError *error)
{
    int err;
    __try {
        OCIErrorGet(error,1,NULL,&err,buffer,MAXERRORORACLE,OCI_HTYPE_ERROR);
        if (buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1]=0;
    } __except(EXCEPTION_CONTINUE_EXECUTION) {};
}

void getcurerror(v10cursors *cur,char *buffer)
{
    getoraerror(buffer,cur->error);
}

void getcurerrornombre(char *nombre,char *buffer)
{
    v10cursors *cur;
    cur=damecursornombre(nombre);
    if (cur==NULL) {
        strcpy(buffer,"");
        return;
    }
    getcurerror(cur,buffer);
}

void getlastdberror(char *buffer)
{
    if (ulterror==NULL) {
        strcpy(buffer,"Ninguna llamada a ORACLE");
        return;
    }
    getoraerror(buffer,ulterror);
    trim(buffer);
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