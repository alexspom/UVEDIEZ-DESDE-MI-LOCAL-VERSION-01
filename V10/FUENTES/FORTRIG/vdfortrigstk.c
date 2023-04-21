/****
* VDFORTRIGSTK.C
*                                                    
* Propósito: Triggers de transformaciones, regularizaciones de stock.                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 13-06-2008                                                         
******
*  Modificaciones:
****/

#include "vd.h"

#define MAXPROPSTK 11

typedef struct {
    void *ptrstkaux;
    void *ptrstknuevo;
    vdconceptoforms cstk;
    int tratado;
    int tipo;
} diffstk;

static diffstk diffstks[MAXPROPSTK];


VDEXPORT int vdcreastk(vdstocks *stk,
              char *conceptoentrada, 
              char *fuente, 
              char *observ, 
			  int fuerzastock,
              char *msjerror,
              double *codmoventrada) {
    
    vdstkauxs stkaux;

	if (STKAUXproccreastk(stk->codmat,stk->ordenstk,stk->codart,stk->codlot,
		                  stk->numeroserie,stk->bulto,stk->marcastk,stk->codrecep,
						  stk->uniemb,stk->embcont,stk->tipoemba,stk->preciouni,stk->pesouni,
						  stk->bloqueos,stk->cantidad,conceptoentrada,fuente,observ,
						  "",0.0,fuerzastock,0,&stkaux)) {
        v10log(LOGERROR,"%s","vddividestk: Error al ejecutar VDSTK.CREASTK\n");
        return(-1);
    }
    
    if (stkaux.ret) {
        v10log(LOGERROR,"vdcreastk: Error al Crear cantidad %lf de stock en contenedor %s y línea de stock %ld\n Error: %s.\n",
            stk->cantidad,stk->codmat,stk->ordenstk,stkaux.msjerror);
        strcopia(msjerror,stkaux.msjerror,strlen(stkaux.msjerror));
        return(stkaux.ret);
    } 
    
    *codmoventrada=stkaux.codmoventrada;
    return(0);
}


VDEXPORT int vddividestk(char *codmat,long ordenstk,
                char *conceptoentrada, 
                char *fuente, 
                char *conceptosalida, 
                char *sumidero, 
                double cantidad,
                char *observ, 
                char *msjerror,
                double *codmoventrada,
                double *codmovsalida,
                long *nuevoordenstk) {
    
    vdstkauxs stkaux;

    if (STKAUXprocdividetk(codmat,ordenstk,conceptoentrada,fuente,conceptosalida,sumidero,
                            cantidad,observ,msjerror,0,0,0,0,&stkaux)) {
        v10log(LOGERROR,"%s","vddividestk: Error al ejecutar VDSTK.DIVIDESTK\n");
        return(-1);
    }
    
    if (stkaux.ret) {
        v10log(LOGERROR,"vddividestk: Error al Dividir cantidad %lf de stock en contenedor %s y línea de stock %ld\n Error: %s.",
            cantidad,codmat,ordenstk,stkaux.msjerror);
        strcopia(msjerror,stkaux.msjerror,strlen(stkaux.msjerror));
        return(stkaux.ret);
    } 
    
    *codmoventrada=stkaux.codmoventrada;
    *codmovsalida=stkaux.codmovsalida;
    *nuevoordenstk=stkaux.nuevoordenstk;
    return(0);
}



VDEXPORT int vdtransformstk(char *codmat,int ordenstk,vdstocks *nuevostk, 
                   char *conceptoentrada, 
                   char *fuente, 
                   char *conceptosalida, 
                   char *sumidero, 
                   char *observ, 
                   char *msjerror,
                   double *codmoventrada,
                   double *codmovsalida,
                   double *codmovinterno) {

    vdstkauxs stkaux;

    if (STKAUXproctransformastk(codmat,ordenstk,conceptoentrada,fuente,conceptosalida,sumidero,observ,nuevostk->codart,nuevostk->codlot,nuevostk->numeroserie,
                            nuevostk->bulto,nuevostk->marcastk,nuevostk->codrecep,nuevostk->uniemb,nuevostk->embcont,
                            nuevostk->tipoemba,nuevostk->preciouni,nuevostk->pesouni,nuevostk->bloqueos,
                            msjerror,0,0,0,0,&stkaux)) {
        v10log(LOGERROR,"%s","vdtransformstk: Error al ejecutar VDSTK.TRANSFORMASTK\n");
        return(-1);
    }

    if (stkaux.ret) {
        v10log(LOGERROR,"vdtransformstk: Error al Transformación de stock en contenedor %s y línea de stock %ld\n Error: %s.",
              codmat,ordenstk,stkaux.msjerror);
        strcopia(msjerror,stkaux.msjerror,strlen(stkaux.msjerror));
        return(stkaux.ret);
    } 

    *codmoventrada=stkaux.codmoventrada;
    *codmovsalida=stkaux.codmovsalida;
    *codmovinterno=stkaux.codmovinterno;
    return(0);

}

VDEXPORT int vdregularizastk(char *codmat,int ordenstk,                    
                    char *concepto, 
                    char *ubiconcepto, 
                    double diff, // en unidades V10
                    char *observ, 
                    char *msjerror,
                    double *codmov) {
    vdstkauxs stkaux;

    if (STKAUXprocregularizastk(codmat,ordenstk,concepto,ubiconcepto,diff,observ,msjerror,(long)*codmov,0,&stkaux)) {
        v10log(LOGERROR,"%s","vdregularizastk: Error al ejecutar VDSTK.REGULARIZASTK\n");
        return(-1);
    }

    if (stkaux.ret) {
        v10log(LOGERROR,"vdregularizastk: Error al Regularizar %lf de stock en contenedor %s y línea de stock %ld\n Error: %s.",
              diff,codmat,ordenstk,stkaux.msjerror);
        strcopia(msjerror,stkaux.msjerror,strlen(stkaux.msjerror));
        return(stkaux.ret);
    } 

    *codmov=stkaux.codmov;
    return(0);
}
 

// devuelve si el stock de este campo, cambia con respecto al nuevo stk
static int esstocktransformado(int ncampo, char *campo, void *ptrstkaux, void *ptrstknuevo, int ordenconcepto, int *distintos, int tipo, 
                                void *valororig, void *valornuevo) {
    
    switch (tipo) {
        case V10CADENA:            
            if (strcmp((char *)valororig,(char *)valornuevo) ) {
                if (ordenconcepto==0) return(-1);
                CSTKselvdconceptoform(campo,ordenconcepto,&diffstks[ncampo].cstk);
                diffstks[ncampo].ptrstkaux=ptrstkaux;
                diffstks[ncampo].ptrstknuevo=ptrstknuevo;
                diffstks[ncampo].tipo=V10CADENA;
                (*distintos)++;
                diffstks[ncampo].tratado=0;
            } else  // son iguales o no se ha encontrado conceptos para cambiarse el valor
                diffstks[ncampo].tratado=1;
            break;

        case V10LONG:
            if (*((long *)valororig)!=*((long *)valornuevo)) {
                if (ordenconcepto==0) return(-1);        
                CSTKselvdconceptoform(campo,ordenconcepto,&diffstks[ncampo].cstk);
                diffstks[ncampo].ptrstkaux=ptrstkaux;
                diffstks[ncampo].ptrstknuevo=ptrstknuevo;
                diffstks[ncampo].tipo=V10LONG;
                (*distintos)++;
                diffstks[ncampo].tratado=0;
            } else  // son iguales o no se ha encontrado conceptos para cambiarse el valor
                diffstks[ncampo].tratado=1;
            break;

        case V10DOUBLE:
            if (*((double *)valororig)!=*((double *)valornuevo)) {
                if (ordenconcepto==0) return(-1);                     
                CSTKselvdconceptoform(campo,ordenconcepto,&diffstks[ncampo].cstk);
                diffstks[ncampo].ptrstkaux=ptrstkaux;
                diffstks[ncampo].ptrstknuevo=ptrstknuevo;
                diffstks[ncampo].tipo=V10DOUBLE;
                (*distintos)++;
                diffstks[ncampo].tratado=0;
            } else  // son iguales o no se ha encontrado conceptos para cambiarse el valor
                diffstks[ncampo].tratado=1;
            break;
    }
    return(0);
}


// transformación de las propiedades del stock
/* Parámetros:
 1. Matrícula   
 2. Orden de stock                           
 3. orden del concepto a elegir              
 4. código de artículo                       
 5. orden del concepto a elegir              
 6. código de lote                           
 7. orden del concepto a elegir              
 8. número de serie                          
 9. orden del concepto a elegir              
 10.bulto                                     
 11.orden del concepto a elegir               
 12.marca de stock                            
 13.orden del concepto a elegir               
 14.código de recepción                       
 15.orden del concepto a elegir               
 16.unidades por embalaje                     
 17.orden del concepto a elegir               
 18.embalajes por contenedor                  
 19.orden del concepto a elegir               
 20.tipo de embalaje                          
 21.orden del concepto a elegir               
 22.precio                                    
 23.orden del concepto a elegir               
 24.peso                                      
 25.observaciones                        
*/
VDEXPORT int ftransformastk(bloques *b,ftrigers *ft) {
    int ret,i, ncampo=0,distintos=0;   
    char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="";
    char observ[MAXCADENA]="";
    int ordenconceptoform;
    vdstocks stk,stknuevo,stkaux;
    char codconceentactual[LCODCONCEENT]="",codconcesalactual[LCODCONCESAL]="";
    char fuenteactual[LFUENTE]="",sumideroactual[LSUMIDERO]="";
    double codmoventrada,codmovsalida,codmovinterno;
     
    if (ft->nparam<25) {                
        sprintf(mensaje,"%s: es obligatorio 25 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&stk,0,sizeof(stk));
    dameparametro(b,ft,0, V10CADENA, stk.codmat);
    dameparametro(b,ft,1, V10LONG, &stk.ordenstk);
    // si no existe el stock original, no lo puede transformar
    if (STKselvdstock(stk.codmat,stk.ordenstk,&stk)) {
        sprintf(mensaje,"No existe stock CODMAT: %s, ORDENSTK: %ld",stk.codmat, stk.ordenstk);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    memset(&stkaux,0,sizeof(stk));

    // carga los campos del stock, guardándose si se han transformado
    dameparametro(b,ft,2, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,3, V10CADENA, stkaux.codart);
    if (esstocktransformado(ncampo++, "CODART", (void *)stkaux.codart, (void *)stknuevo.codart,  ordenconceptoform, 
        &distintos, V10CADENA, (void *)stk.codart, (void *)stkaux.codart)) {
        sprintf(mensaje,"No informado concepto para prop. de stock CODART");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }
    dameparametro(b,ft,4, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,5, V10CADENA, stkaux.codlot);
    if (esstocktransformado(ncampo++, "CODLOT", (void *)stkaux.codlot, (void *)stknuevo.codlot, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.codlot, (void *)stkaux.codlot)) {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock CODLOT");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }
    dameparametro(b,ft,6, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,7, V10CADENA, stkaux.numeroserie);
    if (esstocktransformado(ncampo++, "NUMEROSERIE", (void *)stkaux.numeroserie, (void *)stknuevo.numeroserie, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.numeroserie, (void *)stkaux.numeroserie)) {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock NUMEROSERIE");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }    
    dameparametro(b,ft,8, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,9, V10CADENA, stkaux.bulto);
    if (esstocktransformado(ncampo++, "BULTO", (void *)stkaux.bulto, (void *)stknuevo.bulto, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.bulto, (void *)stkaux.bulto)) {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock BULTO");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }        
    dameparametro(b,ft,10, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,11, V10CADENA, stkaux.marcastk);
    if (esstocktransformado(ncampo++, "MARCASTK", (void *)stkaux.marcastk, (void *)stknuevo.marcastk, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.marcastk, (void *)stkaux.marcastk)) {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock MARCASTK");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }    
    dameparametro(b,ft,12, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,13, V10CADENA, stkaux.codrecep);
    if (esstocktransformado(ncampo++, "CODRECEP", (void *)stkaux.codrecep, (void *)stknuevo.codrecep, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.codrecep, (void *)stkaux.codrecep))  {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock CODRECEO");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }  
    dameparametro(b,ft,14, V10LONG, &ordenconceptoform);  
    dameparametro(b,ft,15, V10DOUBLE, &stkaux.uniemb);
    if (esstocktransformado(ncampo++, "UNIEMB", (void *)&stkaux.uniemb,  (void *)&stknuevo.uniemb, ordenconceptoform, 
                        &distintos, V10DOUBLE, (void *)&stk.uniemb, (void *)&stkaux.uniemb)) {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock UNIEMB");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }    
    dameparametro(b,ft,16, V10LONG, &ordenconceptoform); 
    dameparametro(b,ft,17, V10LONG, &stkaux.embcont);
    if (esstocktransformado(ncampo++, "EMBCONT", (void *)&stkaux.embcont, (void *)&stknuevo.embcont, ordenconceptoform, 
                        &distintos, V10LONG, (void *)&stk.embcont, (void *)&stkaux.embcont))  {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock EMBCONT");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }  
    dameparametro(b,ft,18, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,19, V10CADENA, stkaux.tipoemba);
    if (esstocktransformado(ncampo++, "TIPOEMBA", (void *)stkaux.tipoemba,  (void *)stknuevo.tipoemba, ordenconceptoform, 
                        &distintos, V10CADENA, (void *)stk.tipoemba, (void *)stkaux.tipoemba))  {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock TIPOEMBA");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }  
    dameparametro(b,ft,20, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,21, V10DOUBLE, &stkaux.preciouni);
    if (esstocktransformado(ncampo++, "PRECIOUNI", (void *)&stkaux.preciouni, (void *)&stknuevo.preciouni, ordenconceptoform, 
                        &distintos, V10DOUBLE, (void *)&stk.preciouni, (void *)&stkaux.preciouni))  {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock PRECIOUNI");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }  
    dameparametro(b,ft,22, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,23, V10DOUBLE, &stkaux.pesouni);
    if (esstocktransformado(ncampo++, "PESOUNI", (void *)&stkaux.pesouni, (void *)&stknuevo.pesouni, ordenconceptoform, 
                        &distintos, V10DOUBLE, (void *)&stk.pesouni, (void *)&stkaux.pesouni))  {
        sprintf(mensaje,"%s","No informado concepto para prop. de stock PESOUNI");
        ponerrorbloque(b,mensaje); 
        return(-1);   
    }  
    dameparametro(b,ft,24, V10CADENA, observ);
 
    // no hay diferencias en el stock
    if (distintos==0) {
      sprintf(mensaje,"%s","No existen propiedades del stock cambiadas a transformar");
      ponerrorbloque(b,mensaje); 
      return(-1);
    }

    do {
        STKselvdstock(stk.codmat,stk.ordenstk,&stk);
        memcpy(&stknuevo,&stk,sizeof(stk));
        *codconceentactual=0;
        *codconcesalactual=0;
        *fuenteactual=0;
        *sumideroactual=0;
        for (i=0;i<MAXPROPSTK;i++) {
            // va a tratar las diferencias de stock de la transformación
            // agrupando las llamadas por conceptos y ubic. idénticas, para ahorrar movtos
            if (diffstks[i].tratado==0 &&
               (*codconceentactual==0 || !strcmp(codconceentactual,diffstks[i].cstk.codconceent)) &&
               (*codconcesalactual==0 || !strcmp(codconcesalactual,diffstks[i].cstk.codconcesal)) &&
               (*fuenteactual==0      || !strcmp(fuenteactual,diffstks[i].cstk.fuente)) &&
               (*sumideroactual==0    || !strcmp(sumideroactual,diffstks[i].cstk.sumidero))) {
                    // modifica en stknuevo el valor nuevo de este campo, para que se regularize
                    switch  (diffstks[i].tipo) {
                        case V10CADENA:
                            strcopia(diffstks[i].ptrstknuevo, diffstks[i].ptrstkaux, strlen(diffstks[i].ptrstkaux));
                            break;
                        case V10LONG:
                            *((long *)diffstks[i].ptrstknuevo)=*((long *)diffstks[i].ptrstkaux);
                            break;
                        case V10DOUBLE:
                            *(double *)diffstks[i].ptrstknuevo=*(double *)diffstks[i].ptrstkaux;
                            break;
                    }
                    if (*codconceentactual==0) {
                        // se guarda el concepto actual
                        strcopia(codconceentactual,diffstks[i].cstk.codconceent,strlen(diffstks[i].cstk.codconceent));
                        strcopia(codconcesalactual,diffstks[i].cstk.codconcesal,strlen(diffstks[i].cstk.codconcesal));
                        strcopia(fuenteactual,diffstks[i].cstk.fuente,strlen(diffstks[i].cstk.fuente));
                        strcopia(sumideroactual,diffstks[i].cstk.sumidero,strlen(diffstks[i].cstk.sumidero));
                    }
                   diffstks[i].tratado=1;
             
            }

        }

        if (*codconceentactual==0) break;
        else  {
            ret=vdtransformstk(stknuevo.codmat,stknuevo.ordenstk,&stknuevo, 
                   codconceentactual, fuenteactual, codconcesalactual, sumideroactual, 
                   observ,msjerror,&codmoventrada,&codmovsalida,&codmovinterno);
            if (ret) {
                sprintf(mensaje,"vdtransformstk:\n %s",msjerror);  
                ponerrorbloque(b,mensaje); 
                return(-1);
            }
        }
    } while (1);    
    return(0);
}



int vdnuevobloqlote (char *codart, char *codlot, char *bloqlote, char *solostock, char *msjerror) {
    
    vdarticulos art;

    if (ARTICULOprocnuevobloqlote(codart,codlot,bloqlote,solostock,msjerror,0, &art)) {
        *msjerror=0;
        strcpy(msjerror,"Error ejecutando PLSQL VDART.BLOQUEOSLOTE");
        v10log(LOGERROR,"%s",msjerror);
        return(-1);
    }

    if (art.ret) { 
        *msjerror=0;
        strcpy(msjerror,art.msjerror);      
    }

    return(art.ret);
}


// Cambios de calificación de bloqueos
VDEXPORT int fbloqueosstk(bloques *b,ftrigers *ft) {
    int ret;
    char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="";
    char observ[MAXCADENA]="";
    int ordenconceptoform;    
    vdstocks stk,stkaux;
    vdconceptoforms cstk;
    double codmoventrada,codmovsalida,codmovinterno;

    if (ft->nparam<5) {                
        sprintf(mensaje,"%s: es obligatorio 5 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&stk,0,sizeof(stk));
    dameparametro(b,ft,0, V10CADENA, stk.codmat);
    dameparametro(b,ft,1, V10LONG, &stk.ordenstk);
    
    // si no existe el stock original, no lo puede transformar
    if (STKselvdstock(stk.codmat,stk.ordenstk,&stk)) {
        sprintf(mensaje,"No existe stock CODMAT: %s, ORDENSTK: %ld ",stk.codmat, stk.ordenstk);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    memcpy(&stkaux,&stk,sizeof(stk));

    dameparametro(b,ft,2, V10LONG, &ordenconceptoform);
    dameparametro(b,ft,3, V10CADENA, stkaux.bloqueos);
    dameparametro(b,ft,4, V10CADENA, observ);
 
    if (!strcmp(stk.bloqueos,stkaux.bloqueos))  {
        sprintf(mensaje,"%s","No existen cambios en las calificaciones de stock");
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    if (CSTKselvdconceptoform("BLOQUEOS",ordenconceptoform,&cstk)) {
        sprintf(mensaje,"No existe orden de concepto %ld para campo BLOQUEOS",ordenconceptoform);
        ponerrorbloque(b,mensaje); 
        return(-1);    
    }

    ret=vdtransformstk(stk.codmat,stk.ordenstk,&stkaux, 
        cstk.codconceent, cstk.fuente, cstk.codconcesal, cstk.sumidero, 
        observ,msjerror,&codmoventrada,&codmovsalida,&codmovinterno);
    if (ret) {
        sprintf(mensaje,"vdtransformstk:\n %s",msjerror);  
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    return(0);
}


VDEXPORT int fregularizastk(bloques *b,ftrigers *ft) {
    int ret;
    void *ptr;
    char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="";
    char observ[MAXCADENA]="";
    char codconce[LCODCONCE]="",ubicodconce[LCODUBI]="",campocodmovout[MAXCADENA]="";
    double diff=0.0,codmovout=0;
    vdstocks stk;

    if (ft->nparam<7) {                
        sprintf(mensaje,"%s: es obligatorio 7 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&stk,0,sizeof(stk));
    dameparametro(b,ft,0, V10CADENA, stk.codmat);
    dameparametro(b,ft,1, V10LONG, &stk.ordenstk);
    
    // si no existe el stock original
    if (STKselvdstock(stk.codmat,stk.ordenstk,&stk)) {
        sprintf(mensaje,"No existe stock CODMAT: %s, ORDENSTK: %ld ",stk.codmat, stk.ordenstk);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    dameparametro(b,ft,2, V10CADENA, codconce);
    dameparametro(b,ft,3, V10CADENA, ubicodconce);
    dameparametro(b,ft,4, V10DOUBLE, &diff); // se obtienen ya en unidades V10
    dameparametro(b,ft,5, V10CADENA, observ);
    dameparametro(b,ft,6, V10CADENA, campocodmovout);

    ret=vdregularizastk(stk.codmat,stk.ordenstk,codconce, ubicodconce, diff, observ, msjerror, &codmovout);
    if (ret) {
        sprintf(mensaje,"%s",msjerror);  
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    // guarda en CODMOVOUT, el código de movto generado
    ptr=direcncampo(b,campocodmovout);
    if (ptr) *(double *)ptr=codmovout;
    return(0);
}



VDEXPORT int fdividestk(bloques *b,ftrigers *ft) {
    int ret,ordenconcepto;
    long nuevoordenstk=0;
    void *ptr;
    char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="";
    char observ[MAXCADENA]="";
    char camponuevoorden[MAXCADENA]="";
    double cantamover=0.0,codmoventrada,codmovsalida;
    vdconceptoforms cstk;
    vdstocks stk;

    if (ft->nparam<6) {                
        sprintf(mensaje,"%s: es obligatorio 6 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

    memset(&stk,0,sizeof(stk));
    dameparametro(b,ft,0, V10CADENA, stk.codmat);
    dameparametro(b,ft,1, V10LONG, &stk.ordenstk);
    
    // si no existe el stock original
    if (STKselvdstock(stk.codmat,stk.ordenstk,&stk)) {
        sprintf(mensaje,"No existe stock CODMAT: %s, ORDENSTK: %ld",stk.codmat, stk.ordenstk);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    memset(&cstk,0,sizeof(cstk));
    dameparametro(b,ft,2, V10LONG, &ordenconcepto);
    dameparametro(b,ft,3, V10DOUBLE, &cantamover); // se obtienen ya en unidades V10
    dameparametro(b,ft,4, V10CADENA, observ);
    dameparametro(b,ft,5, V10CADENA, camponuevoorden);

    if (ordenconcepto==0) {
        sprintf(mensaje,"%s","No se han seleccionado conceptos para la división de la línea de stock");
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    if (CSTKselvdconceptoform("DIVIDIR",ordenconcepto,&cstk)) {
        sprintf(mensaje,"No existe orden de concepto %ld para campo DIVIDIR",ordenconcepto);
        ponerrorbloque(b,mensaje); 
        return(-1);    
    }

    ret=vddividestk(stk.codmat,stk.ordenstk,cstk.codconceent,cstk.fuente, cstk.codconcesal, cstk.sumidero,
                    cantamover,observ, msjerror, &codmoventrada, &codmovsalida, &nuevoordenstk);
    if (ret) {
        sprintf(mensaje,"%s",msjerror);  
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    // guarda el Nuevo OrdenStk de la nueva línea de stock en camponuevoorden
    ptr=direcncampo(b,camponuevoorden);
    if (ptr) *(long *)ptr=nuevoordenstk;
    return(0);
}


VDEXPORT int fnuevobloqlote(bloques *b,ftrigers *ft) {
    int ret;
    char codart[LCODART]="",codlot[LCODLOT]="",bloqlote[LBLOQLOTE]="",solostock[2]="";
    char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="";

    if (ft->nparam<4) {                
        sprintf(mensaje,"%s: es obligatorio 4 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }  
    
    dameparametro(b,ft,0, V10CADENA, codart);
    dameparametro(b,ft,1, V10CADENA, codlot); 
    dameparametro(b,ft,2, V10CADENA, bloqlote);
    dameparametro(b,ft,3, V10CADENA, solostock);

    ret=vdnuevobloqlote(codart,codlot,bloqlote,solostock,msjerror);
    if (ret)  ponerrorbloque(b,msjerror); 
    return(ret);
}


VDEXPORT int fcreastk(bloques *b,ftrigers *ft) {
	int ret,ordenconcepto,fuerzastock=0;
	char mensaje[MAXCADENA]="",msjerror[MAXCADENA]="",campocodmovout[MAXCADENA]="";
	char observ[MAXCADENA]="";
	void *ptr;
	vdcontes cnt;
	vdconceptoforms cstk;
	vdstocks stk;
	double codmovout;

	if (ft->nparam<18) {                
        sprintf(mensaje,"%s: son obligatorios 18 parámetros",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    

	memset(&stk,0,sizeof(stk));
	dameparametro(b,ft,0, V10CADENA,	stk.codmat);

	// comprueba que la matrícula exista
	if (CNTselvdconte(stk.codmat,&cnt)) {
		sprintf(mensaje,"Matrícula %s no existe",stk.codmat);
		return(-1);
	}

	dameparametro(b,ft,1, V10LONG,		&stk.ordenstk);
	dameparametro(b,ft,2, V10LONG,		&ordenconcepto);
	
	 if (ordenconcepto==0) {
        sprintf(mensaje,"%s","No se ha seleccionado concepto para la creación de stock");
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    if (CSTKselvdconceptoform("CREAR",ordenconcepto,&cstk)) {
        sprintf(mensaje,"No existe orden de concepto %ld para campo CREAR",ordenconcepto);
        ponerrorbloque(b,mensaje); 
        return(-1);    
    }

	dameparametro(b,ft,3, V10CADENA,	stk.codart);
	dameparametro(b,ft,4, V10CADENA,	stk.codlot);
	dameparametro(b,ft,5, V10CADENA,	stk.numeroserie);
	dameparametro(b,ft,6, V10CADENA,	stk.bulto);
	dameparametro(b,ft,7, V10CADENA,	stk.marcastk);
	dameparametro(b,ft,8, V10CADENA,	stk.codrecep);
	dameparametro(b,ft,9, V10DOUBLE,	&stk.uniemb); // ya en unidades v10
	dameparametro(b,ft,10, V10LONG,		&stk.embcont); 
	dameparametro(b,ft,11, V10CADENA,	stk.tipoemba);
	dameparametro(b,ft,12, V10DOUBLE,	&stk.preciouni);
	dameparametro(b,ft,13, V10DOUBLE,	&stk.pesouni);
	dameparametro(b,ft,14, V10CADENA,	stk.bloqueos);
	dameparametro(b,ft,15, V10DOUBLE,	&stk.cantidad); // ya en unidades v10
	dameparametro(b,ft,16, V10CADENA,	observ);
	dameparametro(b,ft,17, V10CADENA,	campocodmovout);	
	if (ft->nparam>18)	dameparametro(b,ft,18, V10LONG,	&fuerzastock);	


	*msjerror=0;
	ret=vdcreastk(&stk,cstk.codconceent,cstk.fuente,observ,fuerzastock,msjerror,&codmovout); 
	if (ret) {
		ponerrorbloque(b,msjerror); 
		return(ret);
	}

	ptr=direcncampo(b,campocodmovout);
    if (ptr) *(long *)ptr=(long)codmovout;
    return(0);
}
