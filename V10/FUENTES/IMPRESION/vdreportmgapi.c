/****
* VDREPORTMGAPI.C
*                                                    
* Propósito: Define e implemente aquellas funciones exportadas de la DLL                                                       
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 23-06-2008                                                         
******
*  Modificaciones:
****/

#include "vdreportmg.h"

#if defined (__cplusplus)
extern "C" // incrusto código C en C++
{
#endif


static int liberaptr(reportmgimpresiones **ptr, int ret, char *msjerror) {
    if (ret) v10log(LOGERROR,"%s",msjerror);
    if (*ptr) free(*ptr);
    ptr=NULL;
    return(ret);
}


int vdcargainforme(char *orausr, char *orapwd, char *oradb, char *informe, void **ptr, char *msjerror) {
    
    reportmgimpresiones **rpm;

    *ptr=calloc(1,sizeof(reportmgimpresiones));
    rpm=(reportmgimpresiones **)ptr;
    strcpy((*rpm)->usuario,orausr);
    strcpy((*rpm)->password,orapwd);
    strcpy((*rpm)->conexion,oradb);
    strcpy((*rpm)->informe,informe);
    return(0);
}


// variables viene en formato CAMPO=VALOR;CAMPO=VALOR;CAMPO=VALOR; ....
int vdbindinforme(char *variables, void **ptr, char *msjerror) {
    strcpy((*(reportmgimpresiones **)ptr)->variables,variables);
    return(0);
}


int vdwhereinforme(char *where, void **ptr, char *msjerror) {
    return(0);
}


int vdimprimeinforme(char *codimpre, char *salida, int copias, void **ptr, char *msjerror) {
    
    int ret;
    reportmgimpresiones **rpm;
    rpm=(reportmgimpresiones **)ptr;

    ret=ejecutareport((*rpm)->usuario,(*rpm)->password, (*rpm)->conexion,(*rpm)->informe, (*rpm)->variables,
        1, salida,!strcmp(codimpre,PREVISUALIZA)?1:0, msjerror);
    if (ret) return(liberaptr(rpm,ret,msjerror));
    return(ret);

}


int vdexportainforme(char *fichero, int abrir, void **ptr, char *msjerror) {
    int ret;
    reportmgimpresiones **rpm;
    rpm=(reportmgimpresiones **)ptr;

    ret=ejecutareport((*rpm)->usuario,(*rpm)->password, (*rpm)->conexion,(*rpm)->informe, (*rpm)->variables,
        0, fichero,abrir, msjerror);
    if (ret) return(liberaptr((reportmgimpresiones **)ptr,ret,msjerror));
    return(ret);
}


int vdcierrainforme(void **ptr, char *msjerror) {
    return(liberaptr((reportmgimpresiones **)ptr,0,msjerror));
}

#if defined (__cplusplus)
}
#endif