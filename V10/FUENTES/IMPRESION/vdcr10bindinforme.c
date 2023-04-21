/****
* VDCR10BINDINFORME.C
*                                                    
* Propósito: Enlaza las variables pasadas al informe con el mismo                                                      
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


int CR10damevalorcampo( cr10impresiones *imp, char* campo, char *valor, char *msjerror )
{
    HANDLE hcampo;
    short  lon;
    char *ptr;

	if( PEGetFormula( imp->id, campo, &hcampo, &lon ) ){
		ptr=CR10damecadenahandle(hcampo,lon);
        if (ptr) {
            strcopia(valor,ptr,strlen(ptr));
            free(ptr);
        }        
    } else {
        //sprintf(msjerror,"CR10damevalorcampo: Informe %s, Error obteniendo valor del campo %s\nError: %s\n", imp->informe,campo,CR10error(imp,imp->id));
        return(-1);
    }
	return(0);
}

static int ponvalorparam(short printjob,char *campo,char *valor)
{
	PEValueInfo pevalor;
	int ret;
	memset(&pevalor,0,sizeof(pevalor));
	pevalor.StructSize=sizeof(pevalor);
	pevalor.valueType=PE_VI_STRING;
	strcpy(pevalor.viString,valor);
	ret=PEAddParameterCurrentValue(printjob,campo,NULL,&pevalor);
	return(ret);
}

int CR10bindvariables(char *variables,cr10impresiones *imp, char *msjerror) {
    
    int ret,i;
    char asignacion[MAXCADENA];
    char campo[31]=""; 
    char valor[MAXCADENA]="",valorcc[MAXCADENA]="";

    ret=CR10revisaconexionamotor(msjerror);
    if (ret) return(ret);

    strcpy(imp->cadenabind,variables);
    v10log(LOGNORMAL,"CR10bindvariables: Informe %s, cadena de valores de bind: %s\n", imp->informe,imp->cadenabind);
     

    for (i=1;i<=numpieces(variables,";");i++) {               
        piece(variables,asignacion,";",i);        
        if (strlen(asignacion)==0) break;
        piece(asignacion,campo,"=",1);
        piece(asignacion,valor,"=",2);
        if (*valor!='\'')  sprintf(valorcc,"\'%s\'",valor);
        else strcopia(valorcc,valor,strlen(valor));
        v10log(LOGDEBUG,"CR10bindvariables: Informe %s, bindeando a campo %s valor %s\n", imp->informe,campo,valorcc);
        if (PESetFormula( imp->id, campo, valorcc )==0) {
           /* sprintf(msjerror,"CR10bindvariables: Error al bindear en campo %s el valor %s en informe %s\nError: %s\n\n",
                                     campo,valorcc,imp->informe,CR10error(imp,imp->id));*/
			ret=ponvalorparam(imp->id,campo,valor);
			if (ret==0) {
               sprintf(msjerror,"CR10bindvariables: Error al bindear en campo %s el valor %s en informe %s\nError: %s\n\n",
                                        campo,valorcc,imp->informe,CR10error(imp,imp->id));
                return(-1);
			}
        }
    }

    return(0);
}


#if defined (__cplusplus)
}
#endif

