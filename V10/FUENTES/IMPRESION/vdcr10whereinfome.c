/****
* VDCR10WHEREINFORME.C
*                                                    
* Propósito: Estable nuevas condicciones adiccionales a la where del informe                                                 
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

#define CR10ORDERBY     "ORDER BY"
#define CR10WHERE       "WHERE"
#define CR10NUEVOWHERE  " WHERE "
#define CR10AND         " AND "


int CR10cambiawhere(char *where, cr10impresiones *imp, char *msjerror) {
    
    int ret;
    char *ptrorderby;
    char cadenaorderby[MAXSQL]="";

    ret=CR10revisaconexionamotor(msjerror);
    if (ret) return(ret);

    strcpy(imp->nuevowhere,where);
    v10log(LOGNORMAL,"CR10cambiawhere: Informe %s, cadena adiccional de where es: %s\n", imp->nuevowhere);

    imp->idsubreport=imp->id;
    *imp->nomsubreport=0;

    ret=CR10damesqlsubreport(imp,msjerror);
    if (ret) return(ret);

    *cadenaorderby=0;
    if (ptrorderby=strstr(imp->sql,CR10ORDERBY)) {
        strcopia(cadenaorderby,ptrorderby,strlen(ptrorderby));
        *ptrorderby=0;
    }

    if (strstr(imp->sql,CR10WHERE)) strcat( imp->sql, CR10AND);
    else strcat( imp->sql,CR10NUEVOWHERE);
    strcat(imp->sql,imp->nuevowhere);
    strcat(imp->sql," \n");
    strcat(imp->sql,cadenaorderby);
    
    if (PESetSQLQuery( imp->id, imp->sql ) == 0 ) {
        sprintf(msjerror,"CR10cambiawhere: Informe %s, error guardando nueva select %s\nError: %s\n",
                imp->informe,imp->sql,CR10error(imp,imp->id));

        return(-1);	
    }
    return(0);
}


#if defined (__cplusplus)
}
#endif
