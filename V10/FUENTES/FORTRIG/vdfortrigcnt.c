/****
* VDFORTRIGCNT.C
*                                                    
* Propósito: Triggers de contenedores                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 4-07-2008                                                         
******
*  Modificaciones:
****/

#include "vd.h"

// rengancha un movto de un contenedor a otro con el mismo stock, de la misma ubic. o no
VDEXPORT int freenganchaconte(bloques *b,ftrigers *ft) {
    char mensaje[MAXCADENA]="";
    vdmovims mov;
    char codmat[LCODMAT]="";
    char verificaubi[LVERIFICAUBI]="S";
    vdcntauxs cntaux;

    memset(&mov,0,sizeof(mov));
    if (ft->nparam<2) {                
        sprintf(mensaje,"%s: es obligatorio CODMOV y CODMAT",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }       
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
    dameparametro(b,ft,1, V10CADENA, codmat);
    if (ft->nparam>2)  dameparametro(b,ft,2, V10CADENA, verificaubi);
    if (CNTAUXprocreenganchaconte(mov.codmov,codmat,verificaubi,"",0,&cntaux)) {
        sprintf(mensaje,"%s: error ejecutando PLSQL VDCONTE.REENCHANCHACONTE",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1); 
    }
    if (cntaux.ret) {
        sprintf(mensaje,"%s: %s",ft->nombre,cntaux.comentario);
        ponerrorbloque(b,mensaje); 
    }    
    return(cntaux.ret);
}


int vdbloqueosconte(char *codmat, char *codart, char *codlot,
                           char *codconce, char *patronbloqueosori, char *bloqueos,
                           char *observ, char *msjerror, double cantidad) {
    vdcontes cnt;
    vdcntauxs cntaux;

    if (CNTselvdconte(codmat,&cnt)) {
        sprintf(msjerror,"Contenedor %s no existe",codmat);
        return(-1);
    }
    if (CNTAUXprocbloqueosstkconte(codmat,codart,codlot,
                               codconce,"",codconce,"",
                               patronbloqueosori,bloqueos,observ,cantidad,msjerror,0,&cntaux)) {
        strcat(msjerror,"Error ejecutando PLSQL VDCNT.BLOQUEOSSTKCONTE");
        v10log(LOGERROR,"%s", msjerror);
        return(-1);
    }
    if (cntaux.ret) {
        strcpy(msjerror,cntaux.comentario);
        v10log(LOGERROR,"%s",msjerror);        
    }                               
    return(cntaux.ret);
}


// cambia la calif. de stock del artículo y lote de una matrícula
VDEXPORT int fbloqueosconte(bloques *b,ftrigers *ft) {
    
    int ret;
    char codmat[LCODMAT]="",codart[LCODART]="", codlot[LCODLOT]="",codconce[LCODCONCE]="";
    char patronbloqueosori[LPATRONESTADO]="",bloqueos[LBLOQUEOS]="",observ[MAXCADENA];
    char msjerror[MAXCADENA]="",mensaje[MAXCADENA]="";
    double cantidad=0.0;

    if (ft->nparam<7) {                
        sprintf(mensaje,"%s: son obligatorios 7 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }     
    
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, codart);
    dameparametro(b,ft,2, V10CADENA, codlot);
    dameparametro(b,ft,3, V10CADENA, codconce);
    dameparametro(b,ft,4, V10CADENA, patronbloqueosori);
    dameparametro(b,ft,5, V10CADENA, bloqueos);
    dameparametro(b,ft,6, V10CADENA, observ);    
    if (ft->nparam>7) dameparametro(b,ft,7, V10DOUBLE, &cantidad);

    ret=vdbloqueosconte(codmat,codart,codlot,codconce,patronbloqueosori,bloqueos,observ,msjerror,cantidad);
    if (ret) ponerrorbloque(b,msjerror); 
    return(ret);
}
 
// determina si una matrícula está dada de alta en el sistema y es usable
VDEXPORT int fusaconte(bloques *b,ftrigers *ft) {
	char codmat[LCODMAT],codubi[LCODUBI],tipoconte[LTIPOCONTE];
	char mensaje[MAXCADENA]="";
	vdcntauxs cntaux;

    if (ft->nparam<3) {                
        sprintf(mensaje,"%s: es obligatorio CODMAT,CODUBI Y TIPOCONTE",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }       
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, codubi);
	dameparametro(b,ft,2, V10CADENA, tipoconte);// puede ser ""
    if (CNTAUXprocusaconte(codmat,codubi,tipoconte,"",0,&cntaux)) {
        sprintf(mensaje,"%s: error ejecutando PLSQL VDCONTE.USACONTE",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1); 
    }
    if (cntaux.ret) {
        sprintf(mensaje,"%s: %s",ft->nombre,cntaux.comentario);
        ponerrorbloque(b,mensaje); 
    }    
    return(cntaux.ret);
}


