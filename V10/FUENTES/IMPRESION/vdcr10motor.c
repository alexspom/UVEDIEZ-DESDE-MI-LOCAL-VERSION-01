/****
* VDCR10MOTOR.C
*                                                    
* Propósito: Gestiona la conexión/desconexión al motor del Crystal Report                                                  
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 12-05-2008                                                         
******
*  Modificaciones:
****/


#include "vdcr10.h"

#if defined (__cplusplus)
extern "C" // incrusto código C en C++
{
#endif

PELogOnInfo connactual;  
static int conectadomotor=0;
char msjerror[MAXCADENA]="";

char *CR10error( cr10impresiones *imp, short id )
{
    short  lon;
    char nfich[MAXPATH]="",dirlog[MAXPATH]="",extlog[MAXPATH]="",hora[MAXPATH]="",*ptr=NULL;
    HANDLE herror;
    FILE *fich=NULL;

    *msjerror=0;
    if( PEGetErrorText ( id, &herror, &lon ) ) {
        ptr=CR10damecadenahandle (herror, lon);
        if (ptr) {
            strcopia(msjerror,ptr,strlen(ptr));
            free(ptr);
            if (getenv("DIRLOG")!=NULL) strcpy(dirlog,getenv("DIRLOG"));
            else strcat(dirlog,".\\");
            jul2a(damedate(),"Y.YYMMDD",extlog);
            sprintf(nfich,"%s%sCR10err%s.log",dirlog,(dirlog[strlen(dirlog)-1]=='\\')?"":"\\",extlog);
            if ((fich=fopen(nfich,"a"))==NULL) 
                sprintf(msjerror,"CR10error: Error abriendo fichero %s\n",nfich); 
            else {
				memset(hora,0,MAXPATH);
                cent2a(gettime(),6,':',hora);
                fprintf(fich,"%s: Informe %s Subreport \'%s\'\n","CR10error",imp->informe,imp->nomsubreport);
                fprintf(fich,"  Hora: %s\n", hora); 
                fprintf(fich,"  Error: %s\n\n", msjerror); 
                fprintf(fich,"Fin de Informe %s Subreport \'%s\'\n",imp->informe,imp->nomsubreport);           
		        fclose(fich);
            }
        }
    }

	return(msjerror);
}



int CR10revisaconexionamotor(char *msjerror) {
    if (conectadomotor==0) {
        sprintf(msjerror,"CR10revisaconexionamotor: no conectado a motor\n");
        return(-1);
    }
    return(0);
}


static void CR10desconectademotor(void) { 
    
    v10log(LOGNORMAL,"CR10desconestademotor: Intentando cerrar motor\n"); 
    conectadomotor = 0;
    if( PECanCloseEngine () ) {
		PECloseEngine();
	     v10log(LOGNORMAL,"CR10desconestademotor: Cerrado motor\n"); 
	} else  sprintf(msjerror,"CR10desconestademotor: NO se ha cerrado\n"); 
}



int CR10conectaamotor(char *miorausr,char *miorapwd,char *mioradb,cr10impresiones *imp,char *msjerror) {

    int ret;

    if (conectadomotor==0) {
        conectadomotor=PEOpenEngine();
        memset(&connactual,0,sizeof(connactual));
        if (conectadomotor) {
            //atexit(CR10desconectademotor);
            v10log(LOGNORMAL,"CR10conectaamotor: Conexión a motor correcta\n");
        }
        else {
            sprintf(msjerror,"CR10conectaamotor: Conexión a motor errónea: %s\n", CR10error( imp, 0 ) );	
            CR10desconectademotor();
            return(-1);
        }
    }
    // mantiene la conexión actual
	if(	!strcmp(connactual.UserID, miorausr) &&
		!strcmp(connactual.Password, miorapwd) &&
        !strcmp(connactual.ServerName, mioradb)) {
			return(0);   
	}
    // me guardo conexión con la que voy a trabajar
    memset(&connactual,0,sizeof(connactual));
 	connactual.StructSize = sizeof(connactual);
	strcpy(connactual.UserID, miorausr);
	strcpy(connactual.Password, miorapwd);	
    strcpy(connactual.ServerName, mioradb);
    
    setmodule("REPORTS","");
    ret = PELogOnServer ( "crdb_oracle.dll", &connactual);
    setmodule("VDCR10.DLL","");
    if (ret==0) {
        sprintf(msjerror,"CR10conectaamotor: no se puede conectar a Base de Datos\nError: %s\n",CR10error(imp,0));
        return(-1);
    }
    
    v10log(LOGDEBUG,"CR10conectaamotor: CR10 conectado a motor como usuario/servidor: %s/%s\n", miorausr, mioradb );
    return(0);
}

#if defined (__cplusplus)
}
#endif










