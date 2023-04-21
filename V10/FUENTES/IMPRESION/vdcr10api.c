/****
* VDCR10API.C
*                                                    
* Propósito: Define e implemente aquellas funciones exportadas de la DLL                                                       
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


static int liberaptr(cr10impresiones **ptr, int ret, char *msjerror) {
    if (ret) v10log(LOGERROR,"%s",msjerror);
    if ((*ptr)->informeabierto) CR10cierrainforme (*ptr,msjerror);
    if (*ptr) free(*ptr);
    ptr=NULL;
    return(ret);
}


int vdcargainforme(char *orausr, char *orapwd, char *oradb, char *informe, void **ptr, char *msjerror) {
    
    int ret;

    *ptr=calloc(1,sizeof(cr10impresiones));
    ret=CR10conectaamotor(orausr,orapwd,oradb,*ptr,msjerror);
    if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    
    ret=CR10cargainforme(informe,*ptr,msjerror);
    if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    return(ret);
}


// variables viene en formato CAMPO=VALOR;CAMPO=VALOR;CAMPO=VALOR; ....
int vdbindinforme(char *variables, void **ptr, char *msjerror) {

    int ret;

    ret=CR10bindvariables(variables,*ptr,msjerror);
    if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    return(ret);
}


int vdwhereinforme(char *where, void **ptr, char *msjerror) {

    int ret=0;

    if (*where) {
        ret=CR10cambiawhere(where,*ptr,msjerror);
        if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    }
    return(ret);
}


int vdimprimeinforme(char *codimpre, char *salida, int copias, void **ptr, char *msjerror) {
    
    int ret;

    ret=CR10imprime(codimpre,salida,copias,*ptr,msjerror);
    if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    return(ret);
}


int vdexportainforme(char *fichero, int abrir, void **ptr, char *msjerror) {
    int ret;

    strcpy(((cr10impresiones *)(*ptr))->fichexport,fichero);    
    ((cr10impresiones *)(*ptr))->abrirfichero=abrir;

    ret=CR10exportaeimprimeinforme(*ptr,msjerror);
    if (ret) return(liberaptr((cr10impresiones **)ptr,ret,msjerror));
    return(ret);
}


int vdcierrainforme(void **ptr, char *msjerror) {
    return(liberaptr((cr10impresiones **)ptr,0,msjerror));
}

#if defined (__cplusplus)
}
#endif