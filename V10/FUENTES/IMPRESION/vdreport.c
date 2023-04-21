/*******************************************************************************
* Módulo : vdreport.h                                                          *
* Función: Interfase con Report Manager                                        *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 01-10-2007                                                          *
********************************************************************************
* Histórico de cambios
* ====================
*******************************************************************************/
#include "vdreportmg.h"

#define REPINT      3
#define REPDOUBLE   5
#define REPCADENA   256
#define REPNULL     1

#define REPLIB "reportman.ocx"
#define REPINI "C:\\Documents and Settings\\%s\\Datos de programa\\reportman.ini"

HANDLE hmutex=INVALID_HANDLE_VALUE;

#pragma data_seg(".shared")
static char ultimaimpresora[MAXPATH]="";
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,RWS")

int  (*rp_open)(char *cadena);
int (*rp_execute)(int rp,char *cadena,int tipo,int comp);
int (*rp_preview)(int rp,char *titulo);
int (*rp_print)(int rp,char *titulo,int show_progress,int show_print_dialog);
int (*rp_close)(int rp);
char *(*rp_lasterror)(void);
int (*rp_setparamvalue)(int hreport,char *paramname, int paramtype,void *paramvalue);
int (*rp_getparamcount)(int hreport,int *paramcount);
int (*rp_getparamname)(int hreport,int index,char *abuffer);


static void initreportmanager(int impresora,char *destino)
{
    if (hmutex==INVALID_HANDLE_VALUE) {
        hmutex=CreateMutex(NULL,FALSE,"V10REPORTMAN");
    }
    WaitForSingleObject(hmutex,2000);
    if (strcmp(ultimaimpresora,destino) && impresora) {
        char user[MAXPATH],*ptr,fichini[MAXPATH];
        FILE *salida;
        ptr=getenv("USERNAME");
        if (ptr==NULL) strcpy(user,"All Users");
           else        strcpy(user,ptr);
        sprintf(fichini,REPINI,user);
        salida=fopen(fichini,"w");
        fprintf(salida,"[PrinterNames]\nPrinter7=%s\n",destino);
        fclose(salida);
        strcpy(ultimaimpresora,destino);
        unloaddll(REPLIB);
    } else if (impresora && rp_open) {
        ReleaseMutex(hmutex);
        return;
    }
    rp_open=damefundllex(REPLIB,"rp_open",0);
    rp_execute=damefundllex(REPLIB,"rp_execute",0);
    rp_preview=damefundllex(REPLIB,"rp_preview",0);
    rp_print=damefundllex(REPLIB,"rp_print",0);
    rp_close=damefundllex(REPLIB,"rp_close",0);
    rp_lasterror=damefundllex(REPLIB,"rp_lasterror",0);
    rp_setparamvalue=damefundllex(REPLIB,"rp_setparamvalue",0);
    rp_getparamcount=damefundllex(REPLIB,"rp_getparamcount",0);
    rp_getparamname=damefundllex(REPLIB,"rp_getparamname",0);
    ReleaseMutex(hmutex);
}


static int asignavariablesrep(int rp,char *nombre, char *variables,char *msjerror) {
    
    int ret,i;
    char asignacion[MAXCADENA];
    char campo[31]=""; 
    char valor[MAXCADENA]="",valorscc[MAXCADENA]="";


    for (i=1;i<=numpieces(variables,";");i++) {               
        piece(variables,asignacion,";",i);        
        if (strlen(asignacion)==0) break;
        piece(asignacion,campo,"=",1);
        piece(asignacion,valor,"=",2);
        if (*valor=='\'' && *(valor+strlen(valor)-1)=='\'')  {
           strcopia(valorscc , valor+1,strlen(valor+1));
           valorscc[strlen(valorscc)-1]=0;
        }
        else strcopia(valorscc,valor,strlen(valor));
        v10log(LOGDEBUG,"asignavariablesrep: Informe %s, bindeando a campo %s valor %s\n", nombre,campo,valorscc);       
        ret=rp_setparamvalue(rp,campo,REPCADENA,valorscc);
        if (ret==0) {
         sprintf(msjerror,"%s",rp_lasterror());
         return(-1);
        }        
    }

    return(0);
}


int ejecutareport(char *usr, char *pwd, char *conexion,
                  char *nombre,char *param,int impresora,
                  char *destino,int preview, char *msjerror)
{
    int rp,ret;
    char completo[MAXCADENA],*ptr;
    if (rp_open==NULL || impresora) initreportmanager(impresora,destino);
    
    ptr=strchr(nombre,'.');
    if (ptr) *ptr=0;
    strcat(nombre,".REP");
    ret=damenombrecompleto(nombre,completo);
    if (ret) {
        sprintf(msjerror,"No se encuentra informe %s",nombre);
        v10log(LOGERROR,msjerror);
        return(ret);
    }

    
    
    rp=rp_open(completo);
    if (rp==0) {
        sprintf(msjerror,"En ejecuta report %s error %s\n",nombre,rp_lasterror());
        v10log(LOGERROR,msjerror);
        return(rp);
    }
    
    v10log(LOGNORMAL,"Ejecutando report %s con %s %s %s\n",completo,usr,pwd,conexion);
    ret=rp_setparamvalue(rp,"DBPARAM_USER_NAME",REPCADENA,usr);
    if (ret==0) {
        sprintf(msjerror,"En ejecuta report %s error %s\n",nombre,rp_lasterror());
        v10log(LOGERROR,msjerror);
        return(-1);
    }
    ret=rp_setparamvalue(rp,"DBPARAM_PASSWORD",REPCADENA,pwd);
    if (ret==0) {
        sprintf(msjerror,"En ejecuta report %s error %s\n",nombre,rp_lasterror());
        v10log(LOGERROR,msjerror);
        return(-1);
    }
    ret=rp_setparamvalue(rp,"DBPARAM_DATABASE",REPCADENA,conexion);
    if (ret==0) {
        sprintf(msjerror,"En ejecuta report %s error %s\n",nombre,rp_lasterror());
        v10log(LOGERROR,msjerror);
        return(-1);
    }

    ret=asignavariablesrep(rp,nombre,param,msjerror);
    if (ret) {
        v10log(LOGERROR,msjerror);
        return(ret);
    }
    
    
    if (impresora) {
        if (preview) ret=rp_preview(rp,nombre);
        else ret=rp_print(rp,nombre,0,0);
    } else {
        /*
        0 PDF output (compressed or uncompressed) 
        1 Metafile 
        2 CSV output 
        3 HTML output 
        4 SVG output 
        5 Bitmap output 
        6 Plain text 
        7 Custom text 
        8 Excel multiple sheet 
        9 Excel, one sheet 
        10 HTML output one file only  
            */
            int tipofichero=0,comprimido=0;
            char ejecutable[MAXCADENA]="",cadenaexec[MAXCADENA]="";
           
            memset(ejecutable,0,sizeof(ejecutable));
            if (strstr( strmay(destino), ".PDF" )) {
                tipofichero=0;
                comprimido=1;
                strcpy(ejecutable,"AcroRd32.exe"); 
            }
            if (strstr( strmay(destino), ".XLS" )) {
                tipofichero=9;
                strcpy(ejecutable,"excel.exe");
            }
            //if (strstr( strmay(fichero), ".DOC" )) 
            if (strstr( strmay(destino), ".TXT" )) {
                tipofichero=6;
                strcpy(ejecutable,"notepad.exe");
            }
            if (strstr( strmay(destino), ".HTM" )) {
                tipofichero=10;
                strcpy(ejecutable,"iexplorer.exe");
            }
            if (strstr( strmay(destino), ".BMP" )) {
                tipofichero=5;  
                strcpy(ejecutable,"mspaint.exe");
            }
            ret=rp_execute(rp,destino,tipofichero,comprimido);
            if (ret && preview) {
                sprintf(cadenaexec,"start %s %s",ejecutable,destino);
                system(cadenaexec);
            }       
    }
    if (ret==0) {
        sprintf(msjerror,"En ejecuta report %s error %s\n",nombre,rp_lasterror());
        v10log(LOGERROR,msjerror);
        return(-1);
    }
    rp_close(rp);
    return(0);    
}
