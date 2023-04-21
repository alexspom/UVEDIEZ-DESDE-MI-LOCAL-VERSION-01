/****
* VDCR10CARGAINFORME.C
*                                                    
* Propósito: Carga un informe en memoria, y reengancha sus tablas, subreport, secciones ... a la conexión actual de base de datos                                                      
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


char  *CR10damecadenahandle (HANDLE hsql, short lon)
{
	char *ptr = NULL;
    if (hsql == 0) return (NULL);
    ptr=(char*)calloc(1,lon+1);
    if (ptr == NULL) return(NULL);
    if (PEGetHandleString (hsql, ptr, lon))  return(ptr);
    free(ptr);
	return(NULL);
}



int CR10damesqlsubreport(cr10impresiones *imp, char *msjerror) {
    
    short lon;
    char *misql=NULL;
    char logsql[MAXPATH]="",fichlog[MAXPATH]="",dirlog[MAXPATH]="",extlog[MAXPATH]="",hora[MAXPATH]="";
    FILE *flog=NULL;
    HANDLE hsql;
    
    v10log(LOGDEBUG,"CR10damesqlsubreport: obteniendo SQL de informe %s, subreport %s\n",imp->informe,imp->nomsubreport);
    if( PEGetSQLQuery( imp->idsubreport, &hsql, &lon)) {
        misql = CR10damecadenahandle (hsql, lon);
        if (misql) {
            strcpy(imp->sql, misql);
            free(misql);
        } else {
            sprintf(msjerror,"CR10damesqlsubreport: error obteniendo SQL en informe %s, subreport %s\n",imp->informe,imp->nomsubreport);
            return(-1);
        }
    } else {
        sprintf(msjerror,"CR10damesqlsubreport: error obteniendo SQL mediante PEGetSQLQuery en informe %s, subreport %s\nError: %s",imp->informe,imp->nomsubreport,CR10error(imp,imp->id));
        return(-1);
    }

    v10log(LOGDEBUG,"CR10damesqlsubreport: obtenida SQL: %s\n\n en informe %s, subreport %s\n",imp->sql,imp->informe,imp->nomsubreport);
    strcpy(logsql,damepropcadena("CR10SQLDEBUG"));
    // si se indica un fichero de debug-log de SQL de CRYSTAL
    if (*logsql) {
        if (getenv("DIRLOG")!=NULL) strcpy(dirlog,getenv("DIRLOG"));
        else strcat(dirlog,".\\");
        jul2a(damedate(),"Y.YYMMDD",extlog);
        sprintf(fichlog,"%s%s%s%s.log",dirlog,(dirlog[strlen(dirlog)-1]=='\\')?"":"\\",logsql,extlog);
        if ((flog=fopen(fichlog,"a"))==NULL) 
            sprintf(msjerror,"CR10damesqlsubreport: Error abriendo fichero %s\n",fichlog); 
        else {
		   memset(hora,0,MAXPATH);
           cent2a(gettime(),6,':',hora);
           fprintf(flog,"%s: Informe %s Subreport \'%s\'\n","CR10damesqlsubreport",imp->informe,imp->nomsubreport);
           fprintf(flog,"  Hora: %s\n",hora);
           fprintf(flog,"  SQL: %s\n\n",imp->sql); 
           fprintf(flog,"Fin de Informe %s Subreport \'%s\'\n\n",imp->informe,imp->nomsubreport);           
		   fclose(flog);
        }
    }
    return(0);
}

int CR10reenganchasubreport(cr10impresiones *imp, char *msjerror) {

    short ret,ntablas,itabla;
	char *tablasinprefijo;
	char nuevonombretabla[PE_CONNECTION_BUFFER_LEN];
    char nuevaconn[PE_CONNECTION_BUFFER_LEN]="";    
    PETableLocation  tabla, nuevatabla;
   
//    PEDiscardSavedData ( imp->idsubreport );
    ntablas=PEGetNTables (imp->idsubreport);
    for( itabla=0; itabla<ntablas; itabla++ ){ // recorre las tablas del informe 
		
        tabla.StructSize=PE_SIZEOF_TABLE_LOCATION;
        nuevatabla.StructSize=PE_SIZEOF_TABLE_LOCATION;
        *nuevatabla.Location = 0;
        *nuevatabla.SubLocation = 0;
        *nuevatabla.ConnectBuffer = 0;

		PESetNthTableLogOnInfo  ( imp->idsubreport, itabla, &connactual, TRUE );
        PEGetNthTableLocation( imp->idsubreport, itabla, &tabla );
		if( (tablasinprefijo=strstr( tabla.Location, "." )) == NULL ) continue;//tablasinprefijo = tabla.Location;
        else tablasinprefijo++;	
        wsprintf( nuevonombretabla,"%s.%s", connactual.UserID, tablasinprefijo);
		strcpy( nuevatabla.Location, nuevonombretabla );
		strcpy( nuevatabla.SubLocation, nuevonombretabla ); 
        wsprintf( nuevaconn,"Server=%s;;User ID=%s;;Password=%s;;PreQEServerType=Oracle Server;;PreQEServerName=%s;;UserId=%s", 
                connactual.ServerName,
                connactual.UserID,
                connactual.Password, connactual.ServerName, connactual.UserID );
        
        strcpy( nuevatabla.ConnectBuffer, nuevaconn );
        if (PESetNthTableLocation( imp->idsubreport, itabla, &nuevatabla )==0) {
//            sprintf(msjerror,"CR10reenganchasubreport: error reenganchando tabla %s en conexion %s para informe %s, subreport %s\n",nuevonombretabla,nuevaconn,imp->informe,imp->nomsubreport);
            sprintf(msjerror,"CR10reenganchasubreport: error reenganchando tabla %s\n en conexion %s\n para informe %s,\n subreport %s\n%s\n",nuevonombretabla,nuevaconn,imp->informe,imp->nomsubreport,CR10error( imp, imp->id));
//            return(-1);
        }      else v10log(LOGDEBUG,"CR10reenganchasubreport: reenganchada tabla %s en conexion %s para informe %s, subreport %s\n", nuevonombretabla,nuevaconn,imp->informe,imp->nomsubreport);
    }

    ret = PEVerifyDatabase(imp->id);
    if (ret == 0 ){
       sprintf(msjerror,"CR10reenganchasubreport: Error al Verificar Base de Datos %s:  \n\ten informe %s subreport\n", nuevaconn,CR10error(imp,imp->idsubreport) );
//       return(-1);
    } else v10log(LOGNORMAL,"CR10reenganchasubreport: Reenganchada conexión de tablas con éxito en informe %s subreport %s \n",imp->informe,imp->nomsubreport );
	return(0);
}
	

int CR10reenganchainforme(cr10impresiones *imp,char *msjerror, int sqlsubreport) {

    // si imp->nomsubreport es NULL, se trata del report principal
    short ret,nsecciones,iseccion,nsubreports,isubreport,idseccion,idsubreport;
    PEDWORD subreportseccion;
    PESubreportInfo  subreport;

    subreport.StructSize = sizeof (PESubreportInfo);
     
    v10log(LOGNORMAL,"CR10reenganchainforme: Reenganchando informe %s\n",imp->informe);
    
    // reengancha el report principal
    imp->idsubreport=imp->id;
    *imp->nomsubreport=0;
	ret=CR10reenganchasubreport(imp,msjerror);
    if (ret) return(ret);
	ret=CR10damesqlsubreport(imp,msjerror);
    if (ret) return(ret);
    
    // recorres las secciones del informe para ir reenganchándolas
    nsecciones = PEGetNSections( imp->id );
    for( iseccion=0; iseccion < nsecciones; iseccion++ ) {
        idseccion = PEGetSectionCode( imp->id, iseccion );
	    nsubreports = PEGetNSubreportsInSection( imp->id, idseccion );
	    for( isubreport=0; isubreport < nsubreports; isubreport++ ){
		  subreportseccion = PEGetNthSubreportInSection( imp->id, idseccion, isubreport ) ;
          memset(&subreport,0,sizeof (PESubreportInfo));
		  subreport.StructSize = sizeof (PESubreportInfo);
          PEGetSubreportInfo ( imp->id, subreportseccion, &subreport );
		  idsubreport= PEOpenSubreport( imp->id, subreport.name ); 
          v10log(LOGNORMAL,"CR10reenganchainforme: Reenganchando SubReport %s\n",subreport.name );				
          if (idsubreport) {
            imp->idsubreport=idsubreport;
            strcopia(imp->nomsubreport,subreport.name,strlen(subreport.name));			
			ret=CR10reenganchasubreport(imp,msjerror);
			if (sqlsubreport) {
				ret=CR10damesqlsubreport(imp,msjerror);
				if (ret) {
					sprintf(msjerror,"CR10reenganchainforme: Error Reenganchando SubReport %s\n",subreport.name );				
					PECloseSubreport( idsubreport);
					return(ret);
				}
			}
			PECloseSubreport( idsubreport);
            if (ret) {
                sprintf(msjerror,"CR10reenganchainforme: Error Reenganchando SubReport %s\n",subreport.name );				            
                return(ret);
            }
          }
          v10log(LOGNORMAL,"CR10reenganchainforme:Fin de Reenganche de SubReport %s\n",subreport.name );	    
        }
    }

    // recupero el SQL del report principal del informe
    imp->idsubreport=imp->id;
    *imp->nomsubreport=0;
    ret=CR10damesqlsubreport(imp,msjerror);
    if (ret) return(ret);
    v10log(LOGNORMAL,"CR10reenganchainforme: Final de Reenganche del informe %s\n",imp->informe);
    return(0);
}


int CR10cargainforme(char *informe,cr10impresiones *imp,char *msjerror) {
    
    int ret;
    ret=CR10revisaconexionamotor(msjerror);
    if (ret) return(ret);
    if (damenombrecompleto(informe, imp->informe)<0) {
        sprintf(msjerror,"CR10cargainforme: Informe %s no encontrado\n",informe);
        return(-1);
    }
    v10log(LOGDEBUG,"CR10cargainforme: Inicio carga de informe %s\n", imp->informe);
	imp->id = PEOpenPrintJob(imp->informe);
    if( imp->id ){
        imp->informeabierto=1;
		ret=CR10reenganchainforme(imp,msjerror,0);
        if (ret) return(ret);
		v10log(LOGNORMAL,"CR10cargainforme: El informe %s se cargo en memoria\n", imp->informe );
		imp->opt.StructSize = sizeof (PEReportOptions);
		PEGetReportOptions( imp->id, &imp->opt );
		PESetReportOptions( imp->id, &imp->opt );
		PEDiscardSavedData ( imp->id );
    }  else{
		sprintf(msjerror,"CR10cargainforme: informe %s no se pudo cargar en memoria: %s\n", informe,CR10error( imp, 0 ) );
        return(-1);
	}
    v10log(LOGDEBUG,"CR10cargainforme: Fin de carga de informe %s\n", imp->informe);
    return(0); 
}


int CR10cierrainforme (cr10impresiones *imp,char *msjerror) {

    int ret;

    ret=CR10revisaconexionamotor(msjerror);
    if (ret) return(ret);

    ret = PEClosePrintJob( imp->id );
    if( ret == 0 ){ // error
        sprintf(msjerror,"CR10cierrainforme: Error %s\n\t cerrando informe %s\n", CR10error( imp, imp->id ), imp->informe );
        return(-1);		
    }
    return(0);
}


#if defined (__cplusplus)
}
#endif










