/****
* VDFORTRIGDEM.C
*                                                    
* Propósito: Triggers de pantalla/radio sobre líneas y cabeceras de demanda                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 21-04-2008                                                         
******
*  Modificaciones:
****/

#include "execproc/vdexec.h"


// anula una línea de demanda
VDEXPORT int vdanulademl(char *nomtrig,char *nomproceso,vddemandalins *deml,char *mensaje, int sincrono)  { 
    void *antlog;
    int ret;    
    ret=0;    
    
    if (DEMLselvddemandalin(deml->tipodemanda,deml->coddemanda,deml->lindemanda,deml)) {
        sprintf(mensaje,"%s: línea de demanda %s no existe",nomtrig,DEMLlog(deml));
        return(-1);
    }

    if (deml->status>=STDELANULADA) {
        sprintf(mensaje,"%s: línea de demanda %s no se puede anular por su estado",nomtrig,DEMLlog(deml));
        return(-1);    
    }  

    antlog=logoracle;
    logoracle=NULL;    
    
    *deml->comendeml=0;
    ret=anulademl(deml);
    if (ret) {
      if (*deml->comendeml==0) {
        sprintf(mensaje,"%s: \n",nomtrig);
        logoracle2cadena(mensaje+strlen(mensaje)); 
      } else {
        strcopia(mensaje,deml->comendeml,strlen(deml->comendeml));   
      }
    }    


    
    if (sincrono>0 && ret==0) { // ejecución síncrona
        // obtiene deml con el estado resultante de anulademl(deml)
        if (DEMLselvddemandalin(deml->tipodemanda,deml->coddemanda,deml->lindemanda,deml)) {
            sprintf(mensaje,"%s: línea de demanda %s no existe",nomtrig,DEMLlog(deml));
            return(-1);
        }

        ret=triggerdemlsync(nomproceso,deml);
        if (ret) {
            if (!buscaproceso(nomproceso)) {
                sprintf(mensaje,"%s: proceso %s no existe",nomtrig,nomproceso);
            } else {
                sprintf(mensaje,"%s: \n",nomtrig);
                logoracle2cadena(mensaje+strlen(mensaje));
            }
        }
    }
    
    logoracle=antlog;
    return(ret);
}


// anula una demanda al completo, anulando sus líneas de demanda
VDEXPORT int vdanulademc(char *nomtrig,char *nomproceso,vddemandacabs *demc,char *mensaje, int sincrono)  { 
    void *antlog;
    int ret;  
    vddemandalins deml;
    ret=0;    
    
    if (DEMCselvddemandacab(demc->tipodemanda,demc->coddemanda,demc)) {
        sprintf(mensaje,"%s: cabecera de demanda %s no existe",nomtrig,DEMClog(demc));
        return(-1);
    }
    
    if (demc->status>=STDECANULADA) {
        sprintf(mensaje,"%s: cabecera de demanda %s no se puede anular por su estado",nomtrig,DEMClog(demc));
        return(-1);    
    }  
    
    antlog=logoracle;
    logoracle=NULL;    
    
    ret=anulademc(demc);
    if (ret) {
        sprintf(mensaje,"%s: \n",nomtrig);
        logoracle2cadena(mensaje+strlen(mensaje)); 
    }    
    
    // va realizando de forma síncrona la anulación de las líneas de demandas anuladas en este momento
    if (sincrono>0 && ret==0) { // ejecución síncrona   
        int salir=0;
        ret=DEMLbuscademandastatus(demc->tipodemanda,demc->coddemanda,STDELANULADA,&deml);
        do {
            if (ret) {
                ret=0;
                salir=1;
                continue;
            }
            ret=triggerdemlsync(nomproceso,&deml);
            if (ret) {
                if (!buscaproceso(nomproceso)) {
                    sprintf(mensaje,"%s: proceso %s no existe",nomtrig,nomproceso);
                } else {
                    sprintf(mensaje,"%s: \n",nomtrig);
                    logoracle2cadena(mensaje+strlen(mensaje));
                }
                break;
            }
            ret=DEMLnextdemandastatus(&deml);
        } while (salir==0);
    }
    
    logoracle=antlog;
    return(ret);
}


// anula una línea de demanda de forma asíncrona
// parámetros:
//    coddemanda: código de la demanda
//    tipodemanda: tipo de la demanda
//    lindemanda: línea de la demanda
VDEXPORT int fanulademl(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    vddemandalins deml;
    
    if (ft->nparam<3) {                
        sprintf(mensaje,"%s: es obligatorio CODDEMANDA,TIPODEMANDA,LINDEMANDA",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&deml,0,sizeof(deml));
    dameparametro(b,ft,0, V10CADENA, deml.coddemanda);
    dameparametro(b,ft,1, V10CADENA, deml.tipodemanda);
    dameparametro(b,ft,2, V10LONG, &deml.lindemanda);
    ret=vdanulademl(ft->nombre, NULL, &deml, mensaje,0);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}



// anula una línea de demanda de forma síncrona
// parámetros:
//    nomproceso: proceso con el que anula la demanda de manera síncrona
//    coddemanda: código de la demanda
//    tipodemanda: tipo de la demanda
//    lindemanda: línea de la demanda
VDEXPORT int fanulademlsync(bloques *b,ftrigers *ft) {
     int ret;   
    char mensaje[MAXCADENA]="",nomproceso[LPROCESO]="";
    vddemandalins deml;
    
    if (ft->nparam<4) {                
        sprintf(mensaje,"%s: es obligatorio PROCESO,CODDEMANDA,TIPODEMANDA,LINDEMANDA",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&deml,0,sizeof(deml));
    dameparametro(b,ft,0, V10CADENA, nomproceso);
    dameparametro(b,ft,1, V10CADENA, deml.coddemanda);
    dameparametro(b,ft,2, V10CADENA, deml.tipodemanda);
    dameparametro(b,ft,3, V10LONG, &deml.lindemanda);
    ret=vdanulademl(ft->nombre, nomproceso, &deml, mensaje,1);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}



// anula una cabecera de demanda de forma asíncrona
// parámetros:
//    coddemanda: código de la demanda
//    tipodemanda: tipo de la demanda
VDEXPORT int fanulademc(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    vddemandacabs demc;
    
    if (ft->nparam<2) {                
        sprintf(mensaje,"%s: es obligatorio CODDEMANDA y TIPODEMANDA",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&demc,0,sizeof(demc));
    dameparametro(b,ft,0, V10CADENA, demc.coddemanda);
    dameparametro(b,ft,1, V10CADENA, demc.tipodemanda);
    ret=vdanulademc(ft->nombre, NULL, &demc, mensaje,0);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}



// anula una cabecera de demanda de forma síncrona
// parámetros:
//    nomproceso: proceso con el que anula la demanda de manera síncrona
//    coddemanda: código de la demanda
//    tipodemanda: tipo de la demanda
VDEXPORT int fanulademcsync(bloques *b,ftrigers *ft) {
     int ret;   
    char mensaje[MAXCADENA]="",nomproceso[LPROCESO]="";
    vddemandacabs demc;
    
    if (ft->nparam<3) {                
        sprintf(mensaje,"%s: es obligatorio PROCESO,CODDEMANDA y TIPODEMANDA",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&demc,0,sizeof(demc));
    dameparametro(b,ft,0, V10CADENA, nomproceso);
    dameparametro(b,ft,1, V10CADENA, demc.coddemanda);
    dameparametro(b,ft,2, V10CADENA, demc.tipodemanda);
    ret=vdanulademc(ft->nombre, nomproceso, &demc, mensaje,1);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}