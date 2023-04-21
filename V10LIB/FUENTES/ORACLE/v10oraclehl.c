/*
* Módulo : V10ORACLEHL.C                                             
* Objeto:  Funciones de alto nivel de ORACLE
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define ERRINVALIDA "1003,942,1001"
#define NOMASCAMPOS -303
#define MAXDEBUGID 101

static long totcursor,
            numcursor,
            maxcursor;

static long totselect;
static long maxselect;
int ORATECLA=1;
void (*logoracle)(void)=NULL;
static v10cursors *rcursor;

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

static void linkacursor(v10cursors *cur)
{
    cur->next=rcursor;
    rcursor=cur;
}

static void deslinkacursor(v10cursors *cur)
{
    v10cursors *ptr=rcursor,*ant=NULL;
    while (ptr!=NULL) {
        if (ptr==cur) {
            if (ant==NULL) {
                rcursor=cur->next;
            } else {
                ant->next=cur->next;
            }
            return;
        }
        ant=ptr;
        ptr=ptr->next;
    }
    v10log(LOGERROR,"Cursor %s fich. %s %d error al deslinkar\n",cur->nombre,cur->file,cur->line);
}

void invalidacursoresLDA(void *LDA)
{
    v10cursors *ptr=rcursor;
    while (ptr) {
        if (ptr->lda==LDA) ptr->invalido=1;
        ptr=ptr->next;
    }
}


void imprime_orastd()
{
    FILE *salida;
    v10cursors *ptr=rcursor;
    salida=fopen("V10ORASTAT.TXT","w");
    fprintf(salida,"Numero total de cursores %ld\n",totcursor);
    fprintf(salida,"Numero maximo de cursores %ld\n",maxcursor);
    fprintf(salida,"Numero actual de cursores %ld\n",numcursor);
    if (totcursor)
        fprintf(salida,"Tamaño medio de sentencia sql %ld\n",totselect/totcursor);
    fprintf(salida,"Tamaño maximo de sentencia sql %ld\n",maxselect);
    if (numcursor) {
        fprintf(salida,"Cursores no liberados:\nNombre            Fichero                   Linea\n");
        while (ptr) {
            fprintf(salida,"%-20.20s %-40.40s %4ld\n",ptr->nombre,ptr->file,ptr->line);
            ptr=ptr->next;
        }
    }
    fclose(salida);
}

campooras *campodefine(v10cursors *c,char *n)
{
    int ncamp;
    if (c==NULL) return(NULL);
    for (ncamp=0;ncamp<c->ndef;ncamp++) {
        if (strcmp(c->def[ncamp].nombre,n)==0) return(c->def+ncamp);
    }
    return(NULL);
}

campooras *campobind(v10cursors *c,char *n)
{
    int ncamp;
    if (c==NULL) return(NULL);
    for (ncamp=0;ncamp<c->nbind;ncamp++) {
        if (strcmp(c->bind[ncamp].nombre,n)==0) return(c->bind+ncamp);
    }
    return(NULL);
}

static int damemascaracursor(char *nombre,int debug)
{
    int i;
    int mascara;
    mascara=0;
    for (i=0;i<MAXBITDEBUG;i++) {
        if (depuracursor[i]) {
            if (contiene(depuracursor[i],nombre)) mascara|=1<<i;
        }
    }
    if (mascara==0) mascara=debug;
    return(mascara);
}

v10cursors *llparsecursornombref(char *sql,char *nombre,const char *funcion,const char *file,int line,int error,int debug)
{
    v10cursors *ret;
    v10horas inicio=damecent();
    int ncamp;
    OCIError *ocierr;
    campooras *campo;
    int err;
    int nbind=0;
    OCIStmt *stmt;
    if (sql==NULL) return(NULL);
    if (damelogins()==0) {
        final(("No conectado a ORACLE"));
        return(NULL);
    }
    err=OCIHandleAlloc(OCIENV(),(void **)&ocierr,OCI_HTYPE_ERROR,0,0);
    err=analiza_stmt(&stmt,sql,ocierr);
    if (err==NOTLOGGED) {
        if (error) final(("No esta conectado a la BASE DE DATOS"));
        return(NULL);
    }
    campo=calloc(sizeof(campooras),MAXCAMPOS);
    ret=calloc(1,sizeof(v10cursors));
    ret->error=ocierr;
    strcpy(ret->nombre,nombre);
    ret->sql=strdup(sql);
    if (ORATECLA) hay_tecla_normal();
    ret->stmt=stmt;
    ret->lda=OCILDA();
	if (handleoraerr) handleoraerr(err,ret);
    OCIAttrGet(ret->stmt,OCI_HTYPE_STMT,&ret->parseerror,NULL,OCI_ATTR_PARSE_ERROR_OFFSET,OCIERROR());
    OCIAttrGet(ret->stmt,OCI_HTYPE_STMT,&ret->funsql,NULL,OCI_ATTR_SQLFNCODE,OCIERROR());
    ret->funoci=54;
    debug=damemascaracursor(nombre,debug);
    ret->debug=debug;
    ret->file=strdup((char *)file);
    ret->funcion=strdup((char *)funcion);
    ret->line=line;
    if (debugcursor(ret)&DEPURAPRELOG) v10log(LOGNORMAL,"Parse %s fich. %s %d\n",ret->nombre,ret->file,ret->line);
    if (err==0) ret->errcode=0;
    else     ret->errcode=(short)getcurnumerror(ret);
    if (debugcursor(ret)&DEPURAPARSE) cursordebug(ret);
    if (ret->errcode) {
        if (error) cursordebug(ret);
        libera_stmt(ret->stmt);
        free(campo);
        free(ret->sql);
        free(ret->file);
        free(ret);
        return(NULL);
    }
    OCIAttrGet(ret->stmt,OCI_HTYPE_STMT,&ret->ndef,NULL,OCI_ATTR_PARAM_COUNT,OCIERROR());
    for (ncamp=0;;ncamp++) {
        char *nombre;
        int lnombre;
        short dbsize=0;
        short tipo=0;
        short prec=0,scale=0,nulos=0;
        OCIParam *param=NULL;
        campooras *c=campo+ncamp;
        err=OCIParamGet(ret->stmt,OCI_HTYPE_STMT,OCIERROR(),(void **)&param,ncamp+1);
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
        err=OCIStmtGetBindInfo(ret->stmt,OCIERROR(),1,ncamp+1,&cuantos,(OraText **)&nombre,&lon,(OraText **)&indicator,&lindicator,&dup,&handle);
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
    totcursor++;
    numcursor++;
    {int lselect=strlen(ret->sql);
    totselect+=lselect;
    if (lselect>maxselect) maxselect=lselect;
    }
    ret->tparse=damecent()-inicio;
    if (numcursor>maxcursor) maxcursor=numcursor; 
    if (debugcursor(ret)&DEPURALOG) v10log(LOGNORMAL,"Parse %s fich. %s %d tiempo %lf\n",ret->nombre,ret->file,ret->line,ret->tparse);
    linkacursor(ret);
    return(ret);
}

v10cursors *parsecursornombref(char *sql,char *nombre,const char *funcion,const char *file,int line,int debug)
{
    return(llparsecursornombref(sql,nombre,funcion,file,line,1,debug));
}

v10cursors *abrecursornombref(char *nombre,char *sql,const char *funcion,const char *file,int line,int debug)
{
    v10cursors *ret;
    if ((ret=parsecursornombref(sql,nombre,funcion,file,line,debug))==NULL) final(("No puedo abrir cursor %s",nombre));
    return(ret);
}


int definecursor(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo)
{
    OCIDefine *def=NULL;
    short oratipo;
    int ret;                                                             
    campooras *c;
    if (cur->invalido) arreglainvalido(cur);
    if (cur->ndef) describeoci8(cur->stmt,cur->error);
    oratipo=(short) v10tipo2ora(v10tipo);
    if (ncamp<=cur->ndef) {
        c=cur->def+ncamp-1;
        c->tipo=v10tipo;
        c->lon=lon;
        c->dato=var;
    } else return(-1);
    ret=OCIDefineByPos(cur->stmt,&def,OCIERROR(),ncamp,var,lon,oratipo,&c->indicador,NULL,&c->error,OCI_DEFAULT);
    cur->funoci=6;
    if (ret==0) cur->errcode=0;
    else     cur->errcode=(short)getcurnumerror(cur);
	if (handleoraerr) handleoraerr(cur->errcode,cur);
    return(ret);
}


int definetodo(v10cursors *cur,...)
{
    va_list arg;
    int nc;
    int ret;
    if (cur==NULL) return(-1);
    va_start(arg,cur);
    for (nc=0;nc<cur->ndef;nc++) {
        void *var;
        int lon;
        int v10tipo;
        var=va_arg(arg,void *);
        if (var==NULL) {
            cursordebug(cur);
            final(("Pocas variables en define espero %d ultima %s",cur->ndef,nc==0?"-----":cur->def[nc-1].nombre));
        }
        lon=va_arg(arg,int);
        v10tipo=va_arg(arg,int);
        ret=definecursor(cur,nc+1,var,lon,v10tipo);
        if (ret) {
            cursordebug(cur);
            final(("Error en define %d",ret));
        }
    }
    if (va_arg(arg,void *)!=NULL) {
        cursordebug(cur);
        final(("Demasiadas variables define espero %d",cur->ndef));
    }
    if (debugcursor(cur)&DEPURADEFINE) cursordebug(cur);
    return(0);
}


int bindcursor(v10cursors *c,char *ncamp,void *var,int lon,int v10tipo)
{
    OCIBind *bind=NULL;
    short oratipo;
    int ret;
    campooras *ca;
    if (c->invalido) arreglainvalido(c);
    oratipo=(short)v10tipo2ora(v10tipo);
    ca=campobind(c,ncamp);
    if (ca) {
        ca->oratipo=oratipo;
        ca->tipo=v10tipo;
        ca->lon=lon;
        ca->dato=var;
    } else return(-1);
    ret=OCIBindByName(c->stmt,&bind,OCIERROR(),ncamp,strlen(ncamp),var,lon,oratipo,&ca->indicador,NULL,(ub2 *)&ca->error,0,NULL,OCI_DEFAULT);
    c->funoci=8;
    if (ret==0) c->errcode=0;
    else     c->errcode=(short)getcurnumerror(c);
	if (handleoraerr) handleoraerr(c->errcode,c);
    return(ret);
}

int bindtodo(v10cursors *cur,...)
{
    va_list arg;
    int nc;
    int ret;
    if (cur==NULL) return(-1);
    va_start(arg,cur);
    for (nc=0;nc<cur->nbind;nc++) {
        char *nombre;
        void *var;
        int lon;
        int v10tipo;
        nombre=va_arg(arg,char *);
        var=va_arg(arg,void *);
        lon=va_arg(arg,int);
        v10tipo=va_arg(arg,int);
        if (nombre==NULL || var==NULL) {
            cursordebug(cur);
            final(("Pocas variables bind espero %d ultima %s",cur->nbind,nc==0?"------":cur->bind[nc-1].nombre));
        }
        ret=bindcursor(cur,nombre,var,lon,v10tipo);
        if (ret) {
            cursordebug(cur);
            final(("Error en bind %d",ret));
        }
    }
    if (va_arg(arg,void *)!=NULL) {
        cursordebug(cur);
        final(("Demasiadas variables bind espero %d",cur->nbind));
    }
    if (debugcursor(cur)&DEPURABIND) cursordebug(cur);
    return(0);
}

int arreglainvalido(v10cursors *cur)
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
    cur->stmt=stmt;
    cur->error=ocierr;
    cur->lda=OCILDA();
    OCIAttrGet(cur->stmt,OCI_HTYPE_STMT,&cur->parseerror,NULL,OCI_ATTR_PARSE_ERROR_OFFSET,OCIERROR());
    OCIAttrGet(cur->stmt,OCI_HTYPE_STMT,&cur->funsql,NULL,OCI_ATTR_SQLFNCODE,OCIERROR());
    for (nc=0;nc<cur->ndef;nc++) {
        definecursor(cur,nc+1,cur->def[nc].dato,cur->def[nc].lon,cur->def[nc].tipo);
    }
    for (nc=0;nc<cur->nbind;nc++) {
        bindcursor(cur,cur->bind[nc].nombre,cur->bind[nc].dato,cur->bind[nc].lon,cur->bind[nc].tipo);
    }
    return(0);
}

int bindvarios(v10cursors *cur,...)
{
  va_list arg;
  int nc;
  int ret;
  if (cur==NULL) return(-1);
  va_start(arg,cur);
  for (nc=0;nc<cur->nbind;nc++) {
      char *nombre;
      void *var;
      int lon;
      int v10tipo;
      nombre=va_arg(arg,char *);
      if (nombre==NULL) return(0);
      var=va_arg(arg,void *);
      lon=va_arg(arg,int);
      v10tipo=va_arg(arg,int);
      ret=bindcursor(cur,nombre,var,lon,v10tipo);
      if (ret) {
         cursordebug(cur);
         final(("Error en bind %d",ret));
       }
   }
  if (va_arg(arg,void *)!=NULL) {
     cursordebug(cur);
     final(("Demasiadas variables bind espero %d",cur->nbind));
   }
  if (debugcursor(cur)&DEPURABIND) cursordebug(cur);
  return(0);
}

int ora2v10tipo(int oratipo,int lonoracle,int precision,int escala,int *lon)
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

int definetododinamico(v10cursors *cur)
{
	int n;
   campooras *c;
   void *midato;
   int ret;
   int v10tipo;
   int len;
   v10log(LOGNORMAL,"Leyendo %ld campos del cursor %s\n",cur->ndef,cur->nombre);
   for (n=0,c=cur->def;n <cur->ndef;c++,n++) {
       if (c->dato) continue;
       v10tipo=ora2v10tipo(c->oratipo,c->oralen,c->prec,c->scale,&len);
       midato=calloc(1,len);
       c->meminterna=1;
       ret=definecursor(cur,n+1,midato,len,v10tipo);
       v10log(LOGNORMAL,"CAMPO : %s TIPO : %ld LONGITUD :%ld  PRECISION : %ld  ESCALA : %ld RET=%ld\n",
        				c->nombre, c->oratipo,c->oralen,c->prec,c->scale,ret);
       if (ret!=0) {
          return(ret);
        }
    }
    return(0);
}

int binddinamico(v10cursors *cur,int v10tipo,int lon,char *nombre)
{
  	int ret;
   campooras *c;
   c=campobind(cur,nombre);
   if (c == NULL) {
    	return(-1);
    } else {
      c->dato=calloc(1,lon);
      c->meminterna=1;
      ret=bindcursor(cur,c->nombre,c->dato,lon,v10tipo);
      if (ret) v10log(LOGERROR,"Error ejecutando bind_cursor. Error %ld\n",ret);
    }
	return(ret);
}



int ejecutacursorarray(v10cursors *c,int iter)
{
  int ret;
  v10horas inicio=damecent();
  int nb;
  if (c->invalido) arreglainvalido(c);
  if (c==NULL) return(-1);
  c->fprocess=0;
  c->sprocess=0;
  c->arrerr=0;
  for (nb=0;nb<c->nbind;nb++) c->bind[nb].indicador=0;
  if (ORATECLA) hay_tecla_normal();
  if (c->funsql==FSELECT) {
     long prefetch=0;
     iter=0;
     OCIAttrSet(c->stmt, OCI_HTYPE_STMT, &prefetch,0,OCI_ATTR_PREFETCH_ROWS,OCIERROR());
   }
  if (iter>1) {
      int nb;
      for (nb=0;nb<c->nbind;nb++) {
          campooras *ca=c->bind+nb;
          OCIBind *bind=NULL;
          ret=OCIBindByName(c->stmt,&bind,OCIERROR(),ca->nombre,strlen(ca->nombre),ca->dato,ca->lon,(short)ca->oratipo,NULL,NULL,(ub2 *)&ca->error,0,NULL,OCI_DEFAULT);
      }
  }
  if (debugcursor(c)&DEPURAPRELOG) v10log(LOGNORMAL,"Ejecuta %s fich. %s %d\n",c->nombre,c->file,c->line);
  if (debugcursor(c)&DEPURAEXTERNO) pondebugexterno();
  ret=ejecuta_stmt(c->lda,c->stmt,iter,OCI_DEFAULT,c->error);
  if (handleoraerr) handleoraerr(ret,c);
  if (debugcursor(c)&DEPURAEXTERNO) pondebugoff();
  if (ret==0) OCIAttrGet(c->stmt,OCI_HTYPE_STMT,&c->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
  if (ret==0) {
     c->errcode=0;
   } else  {
     c->filasprocesadas=0;
     c->errcode=(short)getcurnumerror(c);
   }
  if (contienenum(ERRINVALIDA,c->errcode)==1) c->invalido=1;
  c->funoci=4;
  c->texec=damecent()-inicio;
  c->totexec+=c->texec;
  c->ejecuciones++;
  if (logoracle && ((debugcursor(c)&DEPURAVDNOLOG)==0)) logoracle();
  if (debugcursor(c)&DEPURALOG) v10log(LOGNORMAL,"Ejecuta %s fich. %s %d tiempo %lf filas %d\n",c->nombre,c->file,c->line,c->texec,procesadascursor(c));
  if ((debugcursor(c)&DEPURAEXEC)) cursordebug(c);
  if (c->errcode && c->errcode!=NOFOUND && c->errcode!=54) {	  
	  detallaerrorcursor(LOGERROR,c,0);
	  //cursordebug(c);
  }
  return(c->errcode);
}

int ejecutacursor(v10cursors *c)
{
  int ret;
  ret=ejecutacursorarray(c,1);
  return(ret);
}

void preparaarrayfetch(v10cursors *cur,int nelem)
{
  unsigned lon;
  int nc,ret;
  if (cur==NULL) return;
  if (cur->invalido) arreglainvalido(cur);
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
      ret=define_stmt(cur->stmt,nc+1,cur->buffer+lon*nelem,cur->def[nc].lon,tipo,(short *)(cur->buffer+lon1*nelem),(short *)(cur->buffer+lon2*nelem),cur->error);
      if (ret) final(("Error al definir para array fetch"));
      lon=lon2+sizeof(short);
   }
}

static void verificanulos(v10cursors *cur)
{
  int ndef;
  for (ndef=0;ndef<cur->ndef;ndef++) {
      campooras *c=cur->def+ndef;
      if (c->indicador==-1) {
         switch (c->tipo) {
             case V10INT:
             case V10UINT    :*(int *)c->dato=0;
                              break;
             case V10SHORT:
             case V10USHORT  :*(short *)c->dato=0;
                              break;
             case V10LONG:
             case V10ULONG   :*(int *)c->dato=0;
                              break;
             case V10CADENA  :strcpy(c->dato,"");
                              break;
             case V10CHAR:
             case V10BYTE    :*(char *)c->dato=0;
                              break;
             case V10FECHA   :*(v10dates *)c->dato=0;
                              break;
             case V10HORA    :*(v10horas *)c->dato=0;
                              break;
             case V10FLOAT   :*(float *)c->dato=0;
                              break;
             case V10DOUBLE  :*(double *)c->dato=0;
                              break;
          }
       }
    }
}

int fetchcursor(v10cursors *cur)
{
    int ret,nc;
    unsigned lon;
    long antcount=cur->filasprocesadas;
    v10horas inicio=damecent();
    if (cur==NULL) return(-1);
    if (cur->invalido) arreglainvalido(cur);
    if (ORATECLA) hay_tecla_normal();
    if (debugcursor(cur)&DEPURAPRELOG) v10log(LOGNORMAL,"Fetch %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    cur->numfetch++;
    if (cur->nelem==0) {
        if (debugcursor(cur)&DEPURAEXTERNO) pondebugexterno();
        ret=fetch_stmt(cur->stmt,1,cur->error);
		if (handleoraerr) handleoraerr(ret,cur);
        if (debugcursor(cur)&DEPURAEXTERNO) pondebugoff();
        OCIAttrGet(cur->stmt,OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
        if (ret==0) {
            verificanulos(cur);
            cur->errcode=0;
        } else {
            cur->errcode=(short)ret;
        }
        cur->funoci=12;
        cur->tfetch=damecent()-inicio;
        cur->totfetch+=cur->tfetch;
        if (logoracle && ((debugcursor(cur)&DEPURAVDNOLOG)==0)) logoracle();
        if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Fetch %s fich %s %d tiempo %lf filas %d\n",cur->nombre,cur->file,cur->line,cur->tfetch,procesadascursor(cur));
    } else {
        if (cur->fprocess==0) {
            if (cur->arrerr==0) {
                cur->arrerr=fetch_stmt(cur->stmt,cur->nelem,cur->error);
                if (handleoraerr) handleoraerr(cur->arrerr,cur);
                OCIAttrGet(cur->stmt,OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
                cur->funoci=12;
            }
            cur->fprocess=(unsigned)(cur->filasprocesadas-antcount);
            cur->sprocess=0;
            cur->filasprocesadas=antcount;
            if (logoracle && ((debugcursor(cur)&DEPURAVDNOLOG)==0)) logoracle();
            if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Fetch %s fich %s %d tiempo %lf filas %d\n",cur->nombre,cur->file,cur->line,cur->tfetch,procesadascursor(cur));
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
            verificanulos(cur);
            cur->sprocess++;
            cur->fprocess--;
            cur->filasprocesadas++;
            ret=0;
            cur->tfetch=damecent()-inicio;
            cur->totfetch+=cur->tfetch;
            if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"AFetch %s fich %s %d tiempo %lf filas %d\n",cur->nombre,cur->file,cur->line,cur->tfetch,procesadascursor(cur));
        }
    }  
    if ((debugcursor(cur)&DEPURAFETCH)) cursordebug(cur);
    if (ret && ret!=NOFOUND && ret!=BLOQUEADO) {		
        detallaerrorcursor(LOGERROR,cur,0);
//		cursordebug(cur);
    }
    return(ret);
}

int ejefetchcursor(v10cursors *cur)
{
    int ret;
    v10horas inicio=damecent();
    if (cur==NULL) return(-1);
    if (cur->invalido) arreglainvalido(cur);
    if (debugcursor(cur)&DEPURAPRELOG) v10log(LOGNORMAL,"Ejefetch %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    if (debugcursor(cur)&DEPURAEXTERNO) pondebugexterno();
    ret=ejefetch_stmt(cur->lda,cur->stmt,cur->error);
	if (handleoraerr) handleoraerr(ret,cur);
    if (debugcursor(cur)&DEPURAEXTERNO) pondebugoff();
    if (ret==0) {
        verificanulos(cur);
        OCIAttrGet(cur->stmt,OCI_HTYPE_STMT,&cur->filasprocesadas,NULL,OCI_ATTR_ROW_COUNT,OCIERROR());
        cur->errcode=0;
    } else     {
        cur->errcode=(short)ret;
        cur->filasprocesadas=0;
    }
    if (contienenum(ERRINVALIDA,cur->errcode)==1) cur->invalido=1;
    cur->funoci=56;
    cur->numejefetch++;
    cur->tejefetch=damecent()-inicio;
    cur->totejefetch=cur->tejefetch;
    if (logoracle && ((debugcursor(cur)&DEPURAVDNOLOG)==0)) logoracle();
    if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Ejefetch %s fich %s %d tiempo %lf filas %d\n",cur->nombre,cur->file,cur->line,cur->tfetch,procesadascursor(cur));
    if (debugcursor(cur)&(DEPURAFETCH|DEPURAEXEC)) cursordebug(cur);
    if (ret && ret!=NOFOUND && ret!=BLOQUEADO) {
		detallaerrorcursor(LOGERROR,cur,0);
//		cursordebug(cur);       
    }
    return(ret);
}
int cancelacursor(v10cursors *cur)
{
    if (cur==NULL) return(-1);
    if (cur->invalido==0) return(0);
    if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Cancela %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    cur->fprocess=0;
    cur->sprocess=0;
    cur->texec=0;
    cur->tfetch=0;
    cur->tejefetch=0;
    cur->funoci=52;
    return(0);
}

int liberacursor(v10cursors *cur)
{
    int n;
    if (cur==NULL) return(0);
    if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Libera %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    for (n=0;n <cur->ndef;n++) {
        campooras *c=cur->def+n;
        if (c->meminterna==0) continue;
        if (c->dato) {
            free(c->dato);
            c->dato=NULL;
        }
    }
    for (n=0;n <cur->nbind;n++) {
        campooras *c=cur->bind+n;
        if (c->meminterna==0) continue;
        if (c->dato) {
            free(c->dato);
            c->dato=NULL;
        }
    }
    cancelacursor(cur);
    deslinkacursor(cur);
    if (cur->invalido==0) {
        libera_stmt(cur->stmt);
        OCIHandleFree((void *)cur->error,OCI_HTYPE_ERROR);
    }
    free(cur->def);
    free(cur->bind);
    free(cur->sql);
    free(cur->buffer);
    free(cur->file);
    free(cur->funcion);
    free(cur);
    numcursor--;
    return(0);
}

int procesadascursor(v10cursors *cur)
{
    return(cur->filasprocesadas);
}

int ejecutaimmediatof(char *sql,int debug,const char *funcion,const char *file,int line)
{
    v10cursors *cur;
    int ret;
    if (sql==NULL) return(-1);
    cur=abrecursornombref("IMMEDIATO",sql,funcion,file,line,debug);
    ret=ejecutacursor(cur);
    if (ret) ret=-ret;
    else ret=procesadascursor(cur);
    liberacursor(cur);
    return(ret);
}

int ejecutaimmediatoparamf(char *sql,int debug,const char *funcion,const char *file,int line,...)
{
    char comando[MAXCADENA];
    int ret;
    va_list arg;
    va_start(arg,line);
    vsprintf(comando,sql,arg);
    ret=ejecutaimmediatof(comando,debug,funcion,file,line);
    va_end(arg);
    return(ret);
}

int savepointf(char *nombre,int debug,const char *funcion,const char *file,int line)
{
    int ret;
    v10cursors *lcsave;
    char linea[MAXCADENA];
    if (nombre==NULL) return(-1);
    sprintf(linea,"SAVEPOINT %s",nombre);
    lcsave=parsecursornombref(linea,"SAVEPOINT",funcion,file,line,debug);
    if (lcsave==NULL) return(-1);
    ret=ejecutacursor(lcsave);
    if (ret) {
        cursordebug(lcsave);
    }
    liberacursor(lcsave);
    return(ret);
}

int rollbacksavepointf(char *nombre,int debug,const char *funcion,const char *file,int line)
{
    int ret;
    v10cursors *lcroll;
    char linea[MAXCADENA];
    if (nombre==NULL) return(-1);
    if (ORATECLA) hay_tecla_normal();
    sprintf(linea,"ROLLBACK TO %s",nombre);
    lcroll=parsecursornombref(linea,"ROLLBACKSAVE",funcion,file,line,debug);
    if (lcroll==NULL)  final(("No puedo hacer ROLLBACK TO SAVEPOINT"));
    ret=ejecutacursor(lcroll);
    liberacursor(lcroll);
    return(ret);
}


int pondebugcursor(v10cursors *cur,int debug)
{
    int ret=cur->debug;
    cur->debug=debug;
    return(ret);
}


int errorcursor(v10cursors *cur)
{
    return(cur->errcode);
}

int funcioncursor(v10cursors *cur)
{
    return(cur->funsql);
}

int rowidcursor(char *tabla,v10cursors *cur,char *donde)
{
    OCIRowid *row=NULL;
    int len=1;
    int ret;
    v10cursors *curtransforma;
    char buffer[MAXCADENA];
    OCIDescriptorAlloc((void *)(OCIENV()),(void *)&row,OCI_DTYPE_ROWID,0,NULL);
    ret=OCIAttrGet((void *)cur->stmt,OCI_HTYPE_STMT,(void *)row,(void *)&len,OCI_ATTR_ROWID,OCIERROR());
    if (ret) {
        strcpy(donde,"");
        return(ret);
    }
    sprintf(buffer,"SELECT ROWID FROM %s WHERE ROWID=:MIROWID",tabla);
    curtransforma=abrecursornombre("CROWID",buffer);
    definetodo(curtransforma,donde,ROWIDLON,V10CADENA,
        NULL);
    bindtodo(curtransforma,"MIROWID",&row,sizeof(row),OCIROWID,
        NULL);
    ejefetchcursor(curtransforma);
    liberacursor(curtransforma);
    return(0);
}

static void prescursores(virtsels *s,int resaltado)
{
    windows *w=&s->v;
    int pos=VIRTPOS(s);
    char presdebug[MAXNOMBREV10];
    v10cursors **avc=s->dato;
    v10cursors *vc=avc[pos];
    v10lformat(vc->debug,11,0,'0',presdebug,2);
    if (resaltado) poncolorv(w,CINPUTACT);
    v10printf(w,"%-30.30s %-11.11s",vc->nombre,presdebug);
    poncolorv(w,CINPUTINAC);
}

static int teclacursores(virtsels *s)
{
    windows wselect;
    tpixels *copia;
    int ret,salir=0;
    int pos=VIRTPOS(s);
    v10cursors **avc=s->dato;
    v10cursors *vc=avc[pos];
    initvn(&wselect,1,31,COLUMNASPANTALLA-2,LINEASPANTALLA-5,"ORADEBUG");
    copia=salvavd(&wselect);
    enmarca(&wselect,1,"SELECT");
    presentaselect(vc,&wselect);
    while (!salir) {
        ret=tecla();
        switch (upper(ret)) {
                 case '0':
                 case '1':
                 case '2':
                 case '3':
                 case '4':
                 case '5':
                 case '6':
                 case '7':
                 case '8':
                 case '9':vc->debug=vc->debug^(1<<(ret-'0'));
                     ret=0;
                     salir=1;
                     break;
                 case 'A':vc->debug=vc->debug^(1<<(ret+10-'A'));
                     ret=0;
                     salir=1;
                     break;
                 case 'd':
                 case 'D':cursordebug(vc);
                     break;
                 default: salir=1;
                     break;
        }
    }
    recuperavd(&wselect,copia);
    return(ret);
}

static int comparacursor(const void *a1,const void *a2)
{
    const v10cursors **c1=a1,**c2=a2;
    return(strcmp((*c1)->nombre,(*c2)->nombre));
}

void menucursores(void)
{
    v10cursors **ac,*ptr;
    int i;
    windows w;
    initvn(&w,5,3,50,28,"DEFECTO");
    ptr=rcursor;
    ac=calloc(numcursor,sizeof(v10cursors *));
    for (i=0;i<numcursor;i++) {
        ac[i]=ptr;
        ptr=ptr->next;
    }
    qsort(ac,numcursor,sizeof(v10cursors *),comparacursor);
    pintaonline("{D}- Debug {0} Parse {1} Bind {2} Define {3} Exec {4} Fetch {5} Prelog {6} Postlog {7} Macro {8} Defecto {9} Toad {Esc} Salir");
    selecciona(1,1,1,1,0,&w,numcursor,1,1,44,"Cursores de la aplicacion",prescursores,teclacursores,0,ac);
    borraonline();
    free(ac);
}

v10cursors *damecursornombre(char *nombre)
{
    v10cursors *ptr=rcursor;
    while (ptr) {
        if (strcmp(nombre,ptr->nombre)==0) return(ptr);
        ptr=ptr->next;
    }
    return(NULL);
}

// datos necesarios para v10www, para la pantalla de cursores
v10cursors *damercursor(int *_numcursor) {
	*_numcursor=numcursor;
	return(rcursor);
}
static int formateanatural(char *donde,double numero)
{
    char *ptr;
    v10dformat(numero,30,60,v10formatdef,' ',donde);
    ltrim(donde);
    ptr=donde+strlen(donde)-1;
    while ((ptr>donde) && (*ptr!=',') && (*ptr=='0')) {
      ptr--;
    }
    if ((ptr==donde) || (*ptr==',')) *ptr='\0';
    else *(ptr+1)='\0';
    return(strlen(donde));
}


char *pasaoracampo2ascii(campooras *c,char *buffer,int comillas,int fechas)
{
  switch (c->tipo) {
    case V10INT   :formateanatural(buffer,*(int *)c->dato);
                break;                     
    case V10UINT   :formateanatural(buffer,(double)*(unsigned int *)c->dato);
                break; 
    case V10SHORT:formateanatural(buffer,*(short *)c->dato);
                break; 
    case V10USHORT:formateanatural(buffer,(long)*(short *)c->dato);
                break;
    case V10LONG:formateanatural(buffer,*(long *)c->dato);
                break;                      
    case V10ULONG   :formateanatural(buffer,*(unsigned long *)c->dato);
                break;    
    case V10DOUBLE:formateanatural(buffer,*(double *)c->dato);
                break;
    case V10FLOAT :formateanatural(buffer,*(float *)c->dato);
                break;
    case V10BYTE   :formateanatural(buffer,(int)*(char *)c->dato);
                break;
    case V10CHAR  :if (comillas) sprintf(buffer,"'%c'",*(char *)c->dato);
		              else       sprintf(buffer,"%c",*(char *)c->dato);
                break;
    case V10CADENA: if (comillas) sprintf(buffer,"'%s'",(char *)c->dato);
		               else       strcopia(buffer,c->dato,100);
                break;
    case V10FECHA :if (fechas) {
                      jul2a(*(v10dates *)c->dato,"DD-MM-Y.",buffer);
		              if (comillas) {
                         strins(buffer,"TO_CHAR(TO_DATE('"); 
					     strcat(buffer,"','DD-MM-YYYY'),'J')");
				      }
                   } else {
                     formateanatural(buffer,*(long *)c->dato);
                   }
                   break;
    case V10HORA  :
                cent2a(*(v10horas *)c->dato,0,':',buffer);
                break;
    case OCIROWID:strcpy(buffer,"");
                  break;
    default:    v10tipo2a(c->dato,c->tipo,0,0,0,buffer,1);
                break;
   }
  return(buffer);
}