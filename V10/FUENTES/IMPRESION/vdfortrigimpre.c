/****
* VDFORTRIGIMPRE.C
*                                                    
* Propósito: Triggers de impresión de etiquetas e informes.                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 07-05-2008                                                         
******
*  Modificaciones:
****/

#include "vdimpresion.h"


// impresión de etiquetas e informes
VDEXPORT int fimprime(bloques *b,ftrigers *ft) {
    int ret; 
    long numcopias=1;
    char tipoimpre[LTIPOIMPRE]="",documento[LDOCUMENTO]="";
    char params[MAXCADENA]="",sustparams[MAXCADENA]="";    
    char codimpre[LCODIMPRE]="",msjerror[MAXCADENA]="";
    vdimpretipos imtp;

    if (ft->nparam<4) {                
      sprintf(msjerror,"%s: son obligatorios TIPO IMPRESION, DOCUMENTO, PARAMETROS E IMPRESORA\n OPCIONAL: NUMERO DE COPIAS",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

    dameparametro(b,ft,0, V10CADENA, tipoimpre);
    dameparametro(b,ft,1, V10CADENA, documento);
    dameparametro(b,ft,2, V10CADENA, params);    
    dameparametro(b,ft,3, V10CADENA, codimpre);
    if (ft->nparam>4) dameparametro(b,ft,4, V10LONG, &numcopias);
    
    if (IMTPselvdimpretipo(tipoimpre,&imtp)) {
        sprintf(msjerror,"tipo de impresion %s no encontrado",tipoimpre);
        ponerrorbloque(b,msjerror);
        return(-1);
    }

    if (*imtp.tipodoc=='E') sustituyevariablessc(b,params,sustparams);
    else sustituyevariables(b,params,sustparams);

    ret=vdimprime(tipoimpre,documento,sustparams,numcopias,codimpre, NULL,0,msjerror);
    if (ret) ponerrorbloque(b,msjerror);
    return(ret);
}



// exporta un documento a un fichero
VDEXPORT int fexporta(bloques *b,ftrigers *ft) {
    int ret; 
    long modospool=0; // modospool: 0. crear, 1. crear y abrir, 2. vía spool
    char tipoimpre[LTIPOIMPRE]="",documento[LDOCUMENTO]="",fichero[MAXPATH]="";
    char params[MAXCADENA]="",sustparams[MAXCADENA]="",msjerror[MAXCADENA]="";
    vdimpretipos imtp;

    if (ft->nparam<4) {                
      sprintf(msjerror,"%s: son obligatorios TIPO IMPRESION, DOCUMENTO, PARAMETROS Y FICHERO A CREAR\nOPCIONAL: ABRIR FICHERO",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

    dameparametro(b,ft,0, V10CADENA, tipoimpre);
    dameparametro(b,ft,1, V10CADENA, documento);
    dameparametro(b,ft,2, V10CADENA, params);
    dameparametro(b,ft,3, V10CADENA, fichero);
    if (ft->nparam>4) dameparametro(b,ft,4, V10LONG, &modospool);   

    if (IMTPselvdimpretipo(tipoimpre,&imtp)) {
        sprintf(msjerror,"tipo de impresion %s no encontrado",tipoimpre);
        ponerrorbloque(b,msjerror);
        return(-1);
    }

    if (*imtp.tipodoc=='E') sustituyevariablessc(b,params,sustparams);
    else sustituyevariables(b,params,sustparams);
    
    ret=vdimprime(tipoimpre,documento,sustparams,1, "WINFILE",fichero,modospool,msjerror);
    if (ret) ponerrorbloque(b,msjerror);
    return(ret);
}











