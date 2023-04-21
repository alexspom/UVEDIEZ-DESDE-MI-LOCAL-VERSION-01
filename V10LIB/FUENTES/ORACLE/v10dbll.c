/*
* Módulo : V10DBLL.C
* Objeto:  Manejo del bajo nivel de Base de datos DRIVERIZADA
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

#include "v10form.h"
logins    *arrlogin;
int numlogins;


int ABRAZO=60;
int FSELECT=4;
int NOFOUND=1403;
int DUPLICADO=1;
int BLOQUEADO=54;


char ORAUSR[MAXLUSER*3];
char ORAPWD[MAXLUSER*2];
char ORADB[MAXLUSER];
int defparse=0;
short deflang=1;


void (*trigerconecta)(void);
void (*trigerlogout)(void);
#define NOMASCAMPOS -303

static long totcursor,
            numcursor,
            maxcursor;

static long totselect;
static long maxselect;
int ORATECLA=0;
void (*logoracle)(void)=NULL;
static v10cursors *rcursor;
static dbdrivers *defaultdbdrv;

#define MAXBITDEBUG 16
char *(depuracursor[MAXBITDEBUG]);

void pondefaultdrv(dbdrivers *drv)
{
	defaultdbdrv=drv;
}

dbdrivers *damedefaultdrv(void)
{
    return defaultdbdrv;
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


static void finoraarrlogin(void)
{
  free(arrlogin);
}

static void initoraarrlogin(dbdrivers *drv)
{
  arrlogin=calloc(MAXLOGIN,sizeof(logins));
  drv->dbinit();
  atexit(finoraarrlogin);
}

void getlastdberror(char *buffer)
{
	if (DRIVERDB->damelasterror) DRIVERDB->damelasterror(buffer);
	else strcpy(buffer,"");
}

int rollback(void)
{
	return(DRIVERDB->dbrollback());
}
int commit(void)
{
	return(DRIVERDB->dbcommit());
}

void invalidacursoresLDA(void *lda)
{
    v10cursors *ptr=rcursor;
    while (ptr) {
//OJO        if (ptr->lda==lda) ptr->invalido=1;
        ptr=ptr->next;
    }
}

static void libera_arrlogin(void)
{
    invalidacursoresLDA(NULL);
	DRIVERDB->dblogout();
}

int logout(void)
{
   if (numlogins<=0) final(("Logout sin conectar a base de datos"));
   if (trigerlogout) trigerlogout();
   rollback();
   libera_arrlogin();
   numlogins--;
//OJO   if (numlogins) ulterror=ERR;
//   	else     ulterror=NULL;
   return(0);
}

static int lllogin(char *nombre,char *pass,char *db)
{
   char usuario[MAXLUSER*3],password[MAXLUSER*2]="",condb[MAXLUSER]="";
   int err;
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
   err=DRIVERDB->dblogin(usuario,password,condb);
   return(err);
}

static int dblogindrv(char *uid,char *pwd,char *db,int error,dbdrivers *drv)
{
  int ret;
  if (uid==NULL) final(("Debe dar nombre de usuario"));
  if (defaultdbdrv==NULL) {
#ifndef __LINUX__
      defaultdbdrv=damedbdriver("v10oracle;damedriveroracle");
#else
      defaultdbdrv=damedbdriver("libv10oraclelinux;damedriveroracle");
#endif
  }
  if (drv==NULL) drv=defaultdbdrv;
  if (arrlogin==NULL) initoraarrlogin(drv);
  if (numlogins-1>=MAXLOGIN) final(("Demasiados logins Max %d",MAXLOGIN));
  numlogins++;
  DRIVERDB=drv;
  ret=lllogin(uid,pwd,db);
  if (ret) {
//    ret=getnumoraerror(ERR);
//OJO    if (error) errlda();
//     libera_arrlogin();
     numlogins--;
   }  else {
     if (trigerconecta) trigerconecta();
   }
  return(ret);
}

int loginne(char *uid,char *pwd,char *db)
{
  return(dblogindrv(uid,pwd,db,0,NULL));
}

int login(char *uid,char *pwd,char *db)
{
  return(dblogindrv(uid,pwd,db,1,NULL));
}

int damelogins(void)
{
  return(numlogins);
}

int relogin(void)
{
  int ret;
  dbdrivers *olddrv=DRIVERDB;
  ret=login(ORAUSR,ORAPWD,ORADB);
  if (ret==0) DRIVERDB=olddrv;
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
            fprintf(salida,"%-20.20s %-40.40s %4d\n",ptr->nombre,ptr->file,ptr->line);
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
	int err;
    v10horas inicio=damecent();
    if (numlogins<=0) final(("Intentando ejecutar sin conexion a BBDD"));
    ret=calloc(1,sizeof(v10cursors));
    ret->funoci=54;
    debug=damemascaracursor(nombre,debug);
    ret->debug=debug;
    ret->file=strdup((char *)file);
    ret->funcion=strdup((char *)funcion);
    ret->line=line;
	err=DRIVERDB->dbparsecursor(ret,sql,nombre,funcion,file,line,1,debug);
	if (err) {
		free(ret->file);
		free(ret->funcion);
		free(ret);
		return(NULL);
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

int ejecutacursor(v10cursors *c)
{
	int ret;
	v10horas inicio=damecent();
	int nb;
	if (c==NULL) return(-1);
    if (numlogins<=0) final(("Intentando ejecutar sin conexion a BBDD"));
	c->fprocess=0;
	c->sprocess=0;
	c->arrerr=0;
	for (nb=0;nb<c->nbind;nb++) c->bind[nb].indicador=0;
	if (ORATECLA) hay_tecla_normal();
	ret=DRIVERDB->dbejecutacursor(c);
	c->funoci=4;
	c->texec=damecent()-inicio;
	c->totexec+=c->texec;
	c->ejecuciones++;
	if (logoracle && ((debugcursor(c)&DEPURAVDNOLOG)==0)) logoracle();
	if (debugcursor(c)&DEPURALOG) v10log(LOGNORMAL,"Ejecuta %s fich. %s %d tiempo %lf filas %d\n",c->nombre,c->file,c->line,c->texec,procesadascursor(c));
	if ((debugcursor(c)&DEPURAEXEC)) cursordebug(c);
	if (c->errcode && c->errcode!=NOFOUND) {
		detallaerrorcursor(LOGERROR,c,0);
		//cursordebug(c);
	}
	return(ret);
}

void preparaarrayfetch(v10cursors *cur,int nelem)
{
    if (numlogins<=0) final(("Intentando ejecutar sin conexion a BBDD"));
	if (DRIVERDB->dbpreparaarrayfetch) DRIVERDB->dbpreparaarrayfetch(cur,nelem);
}


int cancelacursor(v10cursors *cur)
{
	int ret=0;
    if (cur==NULL) return(-1);
    if (cur->invalido==0) return(0);
    if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Cancela %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    cur->fprocess=0;
    cur->sprocess=0;
    cur->texec=0;
    cur->tfetch=0;
    cur->tejefetch=0;
    cur->funoci=52;
	if (DRIVERDB->dbcancelacursor) ret=DRIVERDB->dbcancelacursor(cur);
    return(ret);
}

int definecursor(v10cursors *cur,int ncamp,void *var,int lon,int v10tipo)
{
	int ret=0;
    campooras *c;
    if (ncamp<=cur->ndef) {
        c=cur->def+ncamp-1;
        c->tipo=v10tipo;
        c->lon=lon;
        c->dato=var;
    } else return(-1);
	if (DRIVERDB->dbdefinecursor) ret=DRIVERDB->dbdefinecursor(cur,ncamp,var,lon,v10tipo);
	return(ret);
}

int bindcursor(v10cursors *c,char *ncamp,void *var,int lon,int v10tipo)
{
	int ret=0;
    campooras *ca;
    ca=campobind(c,ncamp);
    if (ca) {
        ca->tipo=v10tipo;
        ca->lon=lon;
        ca->dato=var;
    } else return(-1);
	if (DRIVERDB->dbbindcursor) ret=DRIVERDB->dbbindcursor(c,ncamp,var,lon,v10tipo);
	return(ret);
}
int ora2v10tipo(int oratipo,int lonoracle,int precision,int escala,int *lon)
{
	int ret;
	ret=DRIVERDB->dbv10tipo(oratipo,lonoracle,precision,escala,lon);
	return(ret);
}

void getcurerror(v10cursors *c,char *buffer)
{
	DRIVERDB->dameerrorcur(c,buffer);
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

void verificanulos(v10cursors *cur)
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
    int ret;
    v10horas inicio=damecent();
    if (cur==NULL) return(-1);
    if (cur->invalido) arreglainvalido(cur);
    if (ORATECLA) hay_tecla_normal();
    if (debugcursor(cur)&DEPURAPRELOG) v10log(LOGNORMAL,"Fetch %s fich %s %d\n",cur->nombre,cur->file,cur->line);
    cur->numfetch++;
    //if (debugcursor(cur)&DEPURAEXTERNO) pondebugexterno();
	ret=DRIVERDB->dbfetchcursor(cur);
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
    if ((debugcursor(cur)&DEPURAFETCH)) cursordebug(cur);
    if (ret && ret!=NOFOUND && ret!=BLOQUEADO) {
        detallaerrorcursor(LOGERROR,cur,0);
    }
    return(ret);
}

int ejefetchcursor(v10cursors *cur)
{
	int ret;
    if (cur==NULL) return(-1);
    if (numlogins<=0) final(("Intentando ejecutar sin conexion a BBDD"));
	if (DRIVERDB->dbejefetchcursor) {
        v10horas inicio=damecent();
		ret=DRIVERDB->dbejefetchcursor(cur);
		if (ret==0) {
			verificanulos(cur);
			cur->errcode=0;
		} else     {
			cur->errcode=(short)ret;
			cur->filasprocesadas=0;
		}
		cur->numejefetch++;
		cur->tejefetch=damecent()-inicio;
        cur->totejefetch = cur->tejefetch;
        if (cur->errcode && handleoraerr) {
            if (handleoraerr(cur->errcode, cur)) {
                if ((debugcursor(cur)&(DEPURAFETCH | DEPURAEXEC)) == 0) cursordebug(cur);
                else if (logoracle) logoracle();
            }
        }
		if (logoracle && ((debugcursor(cur)&DEPURAVDNOLOG)==0)) logoracle();
		if (debugcursor(cur)&DEPURALOG) v10log(LOGNORMAL,"Ejefetch %s fich %s %d tiempo %lf filas %d\n",cur->nombre,cur->file,cur->line,cur->tfetch,procesadascursor(cur));
		if (debugcursor(cur)&(DEPURAFETCH|DEPURAEXEC)) cursordebug(cur);
		if (ret && ret!=NOFOUND && ret!=BLOQUEADO) {
			detallaerrorcursor(LOGERROR,cur,0);
		}
	} else {
		if (debugcursor(cur)&DEPURAPRELOG) v10log(LOGNORMAL,"Ejefetch %s fich %s %d\n",cur->nombre,cur->file,cur->line);
		ret=ejecutacursor(cur);
		if (ret) return(ret);
		ret=fetchcursor(cur);
	}
	return(ret);
}

int arreglainvalido(v10cursors *cur)
{
	if (DRIVERDB->dbarreglainvalido) return(DRIVERDB->dbarreglainvalido(cur));
	return(0);
}

int ejecutacursorarray(v10cursors *cur,int iter)
{
	if (DRIVERDB->dbejecutacursorarray) return(DRIVERDB->dbejecutacursorarray(cur,iter));
	return(DRIVERDB->dbejecutacursor(cur));
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
    if (DRIVERDB->dbcancelacursor) DRIVERDB->dbcancelacursor(cur);
    deslinkacursor(cur);
    if (cur->invalido==0) {
		DRIVERDB->dbliberacursor(cur);
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
	int ret;
    if (numlogins<=0) final(("Intentando ejecutar sin conexxion a BBDD"));
	if (DRIVERDB->dbejecutaimmediatof) {
		ret=DRIVERDB->dbejecutaimmediatof(sql,debug,funcion,file,line);
	} else {
		v10cursors *cur;
		cur=abrecursornombref("IMMEDIATO",sql,funcion,file,line,debug);
		ret=ejecutacursor(cur);
		if (ret) ret=-ret;
		else ret=procesadascursor(cur);
		liberacursor(cur);
	}
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
    if (nombre==NULL) return(-1);
	ret=ejecutaimmediatoparamf("SAVEPOINT %s",debug,funcion,file,line,nombre);
    return(ret);
}

int rollbacksavepointf(char *nombre,int debug,const char *funcion,const char *file,int line)
{
    int ret;
    if (nombre==NULL) return(-1);
    if (ORATECLA) hay_tecla_normal();
	ret=ejecutaimmediatoparamf("ROLLBACK TO %s",debug,funcion,file,line,nombre);
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
    v10cursors **c1 = (void *)a1, **c2 = (void *)a2;
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
    while ((ptr>donde) && (*ptr!=',' && *ptr!='.') && (*ptr=='0')) {
      ptr--;
    }
    if ((ptr == donde) || (*ptr == ',') || (*ptr == '.')) *ptr = 0;
    else *(ptr+1)=0;
  //  if (strlen(donde)) if (donde[strlen(donde)-1] == '.') donde[strlen(donde) - 1] = 0;
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