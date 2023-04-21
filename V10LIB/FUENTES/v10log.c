/*
* Módulo : v10log.c
* Objeto:  Soporte para ficheros de log
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

static char dirlog[MAXPATH+1];

static FILE *flog = NULL;
static char nfichlog[MAXPATH];
static windows wlog;
static int init_wlog = 0;
static int initexit=0;
static char mensaje[4*MAXCADENA+1];
static v10dates ultfechalog=0;
static CRITICAL_SECTION slog;
static int initslog=0;
int maxnivellog=LOGNORMAL;
int filalog=2;
int logfun=0;
int logfile=0;
static void (*fnlog)(char *strlog);
char prefijolog[MAXCADENA]="";

void *ponfnlog(void (*mifnlog)(char *strlog))
{
    void *ret;
    ret=fnlog;
    fnlog=mifnlog;
    return ret;
}

void ponprefijolog(char *cadena)
{
	strcpy(prefijolog,cadena);
	if (*prefijolog!=0) strcat(prefijolog," ");
}

static void fin_log(void)
{
    if (flog) {
        char hora[20];
        cent2a(gettime(),8,':',hora);
        fprintf(flog,"\n");
        fprintf(flog,"00 %s %s\n\n",hora,v10translate("Fichero de log cerrado."));
        fclose(flog);
        flog=NULL;
    }
}

static void snombrelog(char *dir,char *nfich,char *extlog,char *dest)
{
    char nombre[MAXPATH];
    char *aux;
    strcpy(nombre,nfich);
    aux=strchr(nombre,'.');
    if (aux) strins(aux,extlog);
    else  {
        strcat(nombre,extlog);
        strcat(nombre,".LOG");
    }
    sprintf(dest,"%s%s%s",dir,dir[strlen(dir)-1]=='/'?"":"/",nombre);
}

static void abrelog(char *nflog)
{
    char extlog[12];
	char nfich[MAXPATH];
    jul2a(damedate(),"Y.YYMMDD",extlog);
    ultfechalog=damedate();
    if (es_blanco(dirlog)) {
        char *aux;
        if ((aux=getenv("DIRLOG"))!=NULL) strcpy(dirlog,aux);
        else strcpy(dirlog,"./");
    }
    if (nflog) {
        if (!es_blanco(nflog)) {
            snombrelog(dirlog,nflog,extlog,nfich);
            if ((flog=fopen(nfich,"a"))==NULL) final(("Abriendo %s",nfich));
            strcpy(nfichlog,nflog);
            v10log(LOGERROR,"%s PID %ld\n\n",v10translate("Fichero de log abierto"),GetCurrentProcessId());
        }
    }
}

static void sv10logf(windows *w, int nivel, int conhora, FILE **f, const char *funcion, const char *file, int line, char *format, va_list arg)
{
    char hora[MAXPATH],*ptr,*miformat;
    if (nivel>maxnivellog) return;
    if (conhora) {
        sprintf(hora,"%02d ",nivel);
        ptr=hora+strlen(hora);
        cent2a(gettime(),8,':',ptr);
        strcat(hora," ");
    } else strcpy(hora,"");
    if (logfun && funcion) {
        sprintf(hora+strlen(hora),"%s: ",funcion);
    }
    if (logfile && file) {
        sprintf(hora+strlen(hora),"%s %d ",file,line);
    }
	miformat = strdup(format);
    v10translate(miformat);
    vsprintf(mensaje, miformat, arg);
	free(miformat);
	strins(mensaje,prefijolog);
    if (w) v10printf(w,"%s%s",hora,mensaje);
    if (*f) {
        if (fprintf(*f,"%s%s",hora,mensaje)==EOF) perror(v10translate("Al escribir en flog."));
        fflush(*f);
        if (fnlog) {
            strins(mensaje,hora);
            fnlog(mensaje);
        }
    }
}

void initv10logparam(char *nflog,int logx,int logy,int logdx,int logdy)
{

    if (initexit==1) fin_log();
    if (logy>0) {
        initvn(&wlog,logx,logy,logx+logdx-1,logy+logdy-1,"LOGS");
        enmarca(&wlog,0," Log normal ");
        poncolorv(&wlog,CNORMAL);
        init_wlog=1;
    }
    abrelog(nflog);
    if (initexit==0) {
        atexit(fin_log);
        initexit=1;
    }
}


void initv10log(char *nflog)
{
    initv10logparam(nflog,1,filalog,COLUMNASPANTALLA-3,(LINEASPANTALLA-filalog-5));
}


void dimenombrelog(char *nlog)
{
    char extlog[12];
    jul2a(damedate(),"Y.YYMMDD",extlog);
    if (nfichlog!=NULL) snombrelog(dirlog,nfichlog,extlog,nlog);
    else strcpy(nlog, "");
}

void editalog(void)
{
    char nombrelog[MAXPATH];
    dimenombrelog(nombrelog);
    invocaeditor(nombrelog,NULL);
}

void vv10logchf(int nivel,int conhora,const char *funcion,char *file,int line,char *format,va_list arg)
{            
    windows *w;
    if (initslog==0) {
        InitializeCriticalSection(&slog);
        initslog=1;
    }		
    EnterCriticalSection(&slog);
    if (damedate()!=ultfechalog) {
        fin_log();
        abrelog(nfichlog);
    }  
    if (init_wlog) w=&wlog;
    else        w=NULL;
    sv10logf(w,nivel,conhora,&flog,funcion,file,line,format,arg);
    LeaveCriticalSection(&slog);
}

void vv10logf(int nivel,const char *funcion,char *file,int line,char *format,va_list arg)
{  
    vv10logchf(nivel,1,funcion,file,line,format,arg);
}

void v10logchf(int nivel,int conhora,const char *funcion,char *file,int line,char *format,...)
{  
    va_list arg;
    va_start(arg,format);
    vv10logchf(nivel,conhora,funcion,file,line,format,arg);
}

void v10logf(int nivel,const char *funcion,char *file,int line,char *format,...)
{  
    va_list arg;
    va_start(arg,format);
    vv10logf(nivel,funcion,file,line,format,arg);
}

                   