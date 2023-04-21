/****
* VDFORTRIGUBI.C
*                                                    
* Propósito: Triggers de pantalla/radio para reubicación y cambio manuales de conteendores y stock.                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 21-02-2008                                                         
******
*  Modificaciones:
****/

#include "vd.h"


VDEXPORT void ponerrorbloque(bloques *b, char *mensaje) 
{
  void *ptr;
  int campo;
  campo = damecampo(b, "V10ERROR");
  if (campo < 0) return;
  ptr=direcncampo(b,"V10ERROR");
  if (ptr) strcopia(ptr,mensaje,b->c[campo].lon-1);  
  v10log(LOGERROR,"%s",mensaje);
}


// devuelve el código de ubic. a partir de una máscara de 
// la misma, y la planta,pasillo,columna,altura y profundidad.
// se utiliza en el asistente de creación de ubicaciones
VDEXPORT int fmascaracodubi(bloques *b,ftrigers *ft) {
    char mascara[MAXCADENA]="",campocodubi[MAXCADENA]="",mensaje[MAXCADENA]="";
    void *ptrcampo;
    int valor,planta,pasillo,columna,altura,profundidad;
    char *ptr,*ultptr,miformato[MAXCADENA]="",mipatron[MAXCADENA]=""; 

    if (ft->nparam<7) {                
        sprintf(mensaje,"FMASCARACODUBI: se reciben %d parametros, se esperan 7",ft->nparam);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    direcncampo(b,"V10ERROR");

    dameparametro(b,ft,0, V10CADENA,    mascara);
    dameparametro(b,ft,1, V10LONG,      &planta);
    dameparametro(b,ft,2, V10LONG,      &pasillo);
    dameparametro(b,ft,3, V10LONG,      &columna);
    dameparametro(b,ft,4, V10LONG,      &altura);
    dameparametro(b,ft,5, V10LONG,      &profundidad);
    dameparametro(b,ft,6, V10CADENA,    campocodubi);

    ptrcampo=(long *)direcncampo(b,campocodubi);
    if (!ptrcampo) {
        sprintf(mensaje,"FMASCARACODUBI: No se encuentra campo %s en la pantalla",campocodubi);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    *(char *)ptrcampo=0;
    ultptr=mascara;
    while ((ptr=strstr(ultptr,"%"))) {
	    if (ptr > ultptr) strncat(ptrcampo, ultptr, ((size_t)ptr - (size_t)ultptr));        
        if (isdigit(ptr[4])) {
            sprintf(miformato,"%%0%cd",ptr[4]);
            ultptr=ptr+5;
        }
        else  {
           sprintf(miformato,"%%d");
           ultptr=ptr+4;
        }
        strcopia(mipatron,ptr,4);        
        if (!strcmp(mipatron,"%pla")) valor=planta;
        if (!strcmp(mipatron,"%pas")) valor=pasillo;
        if (!strcmp(mipatron,"%col")) valor=columna;
        if (!strcmp(mipatron,"%alt")) valor=altura;
        if (!strcmp(mipatron,"%pro")) valor=profundidad;        
        sprintf((char *)ptrcampo+strlen((char *)ptrcampo),miformato,valor);        
       
    }
    if (strlen(ultptr)>0) strcat(ptrcampo,ultptr);
    return(0);
}

// reubicación de un contenedor completo
VDEXPORT int freubiconte(bloques *b,ftrigers *ft)
{
    void *antlog,*ptr;
    int numcampo,ret;
    long pasillo=0;
    char codmat[LCODMAT];
    char tarea[LTAREA]="",uniagrupa[LUNIAGRUPAE]="",codarea[LCODAREA]="";
    char campocodmov[LNOMBRE]="";
    vdubicars ubicar;
    char mensaje[MAXCADENA]="";
    
    
    if (ft->nparam<3) {                
        sprintf(mensaje,"FREUBICONTE: se reciben %d parametros, se esperan minimo 3",ft->nparam);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, tarea);
    dameparametro(b,ft,2, V10CADENA, campocodmov);
    if (ft->nparam>3) dameparametro(b,ft,3, V10CADENA, codarea);
    if (ft->nparam>4) dameparametro(b,ft,4, V10LONG,   &pasillo);
    if (ft->nparam>5) dameparametro(b,ft,5, V10CADENA, &uniagrupa);
    
    numcampo=damecampo(b, campocodmov);
    if (numcampo<0) {
        sprintf(mensaje,"FREUBICONTE: no se encuentra campo %s en la pantalla",campocodmov);
        ponerrorbloque(b,mensaje);       
        return(-1);
    } 
    
    ptr=(long *)direcncampo(b,campocodmov);
    
    antlog=logoracle;
    logoracle=NULL;
    
    ret=UBICARprocreubiconte(codmat,tarea,*(long *)ptr,codarea, pasillo,uniagrupa,&ubicar);
    if (ret) {
        sprintf(mensaje,"FREUBICONTE: Error PLSQL al ejecutar VDUBI.REUBICONTE");
        ponerrorbloque(b,mensaje);       
        ret=-1;
    } else {
        if (ubicar.codmov==0) {
            *(long *)ptr=0;
            logoracle2cadena(mensaje);
            ponerrorbloque(b,mensaje);
            ret=-1; 
        } else {
            *(long *)ptr=ubicar.codmov;
        }
    }
    
    logoracle=antlog;
    return(ret);
}

// reubicación parcial de stock
VDEXPORT int freubistk(bloques *b,ftrigers *ft) {
    void *antlog,*ptr;
    int numcampo,ret;
    long pasillo=0;
    char codmat[LCODMAT];
    double cantidad=0,uniemb=0;
    char tarea[LTAREA]="",uniagrupa[LUNIAGRUPAE]="",codarea[LCODAREA]="";
    char codart[LCODART]="",codlot[LCODLOT]="",bloqueos[LBLOQUEOS]="";
    char campocodmov[LNOMBRE]="";
    vdubicars ubicar;
    char mensaje[MAXCADENA]="";
    
    
    if (ft->nparam<8) {                
        sprintf(mensaje,"FREUBISTK: se reciben %d parametros, se esperan minimo 8",ft->nparam);
        ponerrorbloque(b,mensaje);       
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, tarea);
    dameparametro(b,ft,2, V10CADENA, codart);
    dameparametro(b,ft,3, V10CADENA, codlot);
    dameparametro(b,ft,4, V10DOUBLE, &uniemb);  
	dameparametro(b,ft,5, V10CADENA, bloqueos);  
    dameparametro(b,ft,6, V10DOUBLE, &cantidad);
    dameparametro(b,ft,7, V10CADENA, campocodmov);
    if (ft->nparam>8) dameparametro(b,ft,8, V10CADENA, codarea);
    if (ft->nparam>9) dameparametro(b,ft,9, V10LONG,   &pasillo);
    if (ft->nparam>10) dameparametro(b,ft,10, V10CADENA, &uniagrupa);
    
    numcampo=damecampo(b, campocodmov);
    if (numcampo<0) {
        sprintf(mensaje,"FREUBISTK: no se encuentra campo %s en la pantalla",campocodmov);
        ponerrorbloque(b,mensaje);       
        return(-1);
    } 
    
    ptr=(long *)direcncampo(b,campocodmov);
    
    antlog=logoracle;
    logoracle=NULL;
    
    ret=UBICARprocreubistk(codmat,tarea,codart,codlot,uniemb,bloqueos,cantidad,*(long *)ptr,codarea,pasillo,uniagrupa,&ubicar);
    if (ret) {
        sprintf(mensaje,"FREUBISTK: Error PLSQL al ejecutar VDUBI.REUBISTK");
        ponerrorbloque(b,mensaje);       
        ret=-1;
    } else {
        if (ubicar.codmov==0) {
            *(long *)ptr=0;
            logoracle2cadena(mensaje);
            ponerrorbloque(b,mensaje);
            ret=-1; 
        } else {
            *(long *)ptr=ubicar.codmov;
        }
    }
    
    logoracle=antlog;
    return(ret);

}




// cambio de ubicación de un contenedor
VDEXPORT int fcambioubiconte(bloques *b,ftrigers *ft) 
{
    void *antlog,*ptr;
    int numcampo,ret;
    long priomov=1000,status=0;
    char verifcomp[2]="",verifflujo[2]="";
    char codmat[LCODMAT];
    char tarea[LTAREA]="",codubidest[LCODUBIDEST]="",codconce[LCODCONCE]="",codrecurso[LCODRECURSO]="";
    char campocodmov[LNOMBRE]="";
    vdubicars ubicar;
    char mensaje[MAXCADENA]="";
    
    
    if (ft->nparam<4) {                
        sprintf(mensaje,"FCAMBIOUBICONTE: se reciben %d parametros, se esperan minimo 4",ft->nparam);
        ponerrorbloque(b,mensaje);       
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, codubidest);    
    dameparametro(b,ft,2, V10CADENA, tarea);
    dameparametro(b,ft,3, V10CADENA, campocodmov);
    if (ft->nparam>4) dameparametro(b,ft,4, V10CADENA,   verifflujo);
    if (ft->nparam>5) dameparametro(b,ft,5, V10CADENA,   verifcomp);   
    if (ft->nparam>6) dameparametro(b,ft,6, V10CADENA, codconce);
    if (ft->nparam>7) dameparametro(b,ft,7, V10LONG,   &priomov);
    if (ft->nparam>8) dameparametro(b,ft,8, V10LONG,   &status);
    if (ft->nparam>9) dameparametro(b,ft,9, V10CADENA, codrecurso);
   
    numcampo=damecampo(b, campocodmov);
    if (numcampo<0) {
        sprintf(mensaje,"FCAMBIOUBICONTE: no se encuentra campo %s en la pantalla",campocodmov);
        ponerrorbloque(b,mensaje);       
        return(-1);
    } 
    
    ptr=(long *)direcncampo(b,campocodmov);
    
    antlog=logoracle;
    logoracle=NULL;
    
    ret=UBICARproccambioubiconte(codmat,codubidest,tarea,*(long *)ptr,verifflujo,verifcomp,codconce,priomov,status,codrecurso,&ubicar);
    if (ret) {
        sprintf(mensaje,"FCAMBIOUBICONTE: Error PLSQL al ejecutar VDUBI.FCAMBIOUBICONTE");
        ponerrorbloque(b,mensaje); 
        ret=-1;
    } else {
        if (ubicar.codmov==0) {
            *(long *)ptr=0;
            logoracle2cadena(mensaje);
            ponerrorbloque(b,mensaje);    
            ret=-1; 
        } else {
            *(long *)ptr=ubicar.codmov;
        }
    }
    
    logoracle=antlog;
    return(ret);
}


// cambio de ubicación parcial
VDEXPORT int fcambioubistk(bloques *b,ftrigers *ft) {

    void *antlog,*ptr;
    int numcampo,ret;
    long priomov=1000,status=0;
    char verifcomp[2]="",verifflujo[2]="";
    char codmat[LCODMAT]="",codmatdest[LCODMAT]="";
    double cantidad=0,uniemb=0;
    char tarea[LTAREA]="",codubidest[LCODUBIDEST]="",codconce[LCODCONCE]="",codrecurso[LCODRECURSO]="";
    char codart[LCODART]="",codlot[LCODLOT]="",bloqueos[LBLOQUEOS]="";  
    char campocodmov[LNOMBRE]="";
    vdubicars ubicar;
    char mensaje[MAXCADENA]="";
    
    
    if (ft->nparam<10) {                
        sprintf(mensaje,"FCAMBIOUBISTK: se reciben %d parametros, se esperan minimo 10",ft->nparam);
        ponerrorbloque(b,mensaje);       
        return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, codubidest);   
    dameparametro(b,ft,2, V10CADENA, codmatdest);
    dameparametro(b,ft,3, V10CADENA, tarea);
    dameparametro(b,ft,4, V10CADENA, codart);
    dameparametro(b,ft,5, V10CADENA, codlot);
    dameparametro(b,ft,6, V10DOUBLE, &uniemb); 
	dameparametro(b,ft,7, V10CADENA, bloqueos);
    dameparametro(b,ft,8, V10DOUBLE, &cantidad); 
    dameparametro(b,ft,9, V10CADENA, campocodmov);
    if (ft->nparam>10) dameparametro(b,ft,10, V10CADENA,   verifflujo);
    if (ft->nparam>11) dameparametro(b,ft,11, V10CADENA,   verifcomp);  
    if (ft->nparam>12) dameparametro(b,ft,12, V10CADENA, codconce);
    if (ft->nparam>13) dameparametro(b,ft,13, V10LONG,   &priomov);
    if (ft->nparam>14) dameparametro(b,ft,14, V10LONG,   &status);
    if (ft->nparam>15) dameparametro(b,ft,15, V10CADENA, codrecurso);
    
    numcampo=damecampo(b, campocodmov);
    if (numcampo<0) {
        sprintf(mensaje,"FCAMBIOUBISTK: no se encuentra campo %s en la pantalla",campocodmov);
        ponerrorbloque(b,mensaje);       
        return(-1);
    } 
    
    ptr=(long *)direcncampo(b,campocodmov);
    
    antlog=logoracle;
    logoracle=NULL;
    
    ret=UBICARproccambioubistk(codmat,codubidest,codmatdest,tarea,codart,codlot,uniemb,bloqueos,cantidad,*(long *)ptr,verifflujo,verifcomp,codconce,priomov,status,codrecurso,&ubicar);
    if (ret) {
        sprintf(mensaje,"FCAMBIOUBISTK: Error PLSQL al ejecutar VDUBI.FCAMBIOUBISTK");
        ponerrorbloque(b,mensaje); 
        ret=-1;
    } else {
        if (ubicar.codmov==0) {
            *(long *)ptr=0;
            logoracle2cadena(mensaje);
            ponerrorbloque(b,mensaje); 
            ret=-1; 
        } else {
            *(long *)ptr=ubicar.codmov;
        }
    }
    
    logoracle=antlog;
    return(ret);
}


// verifica si uan matrícula, articulo y lote es compatible en una ubicacion
VDEXPORT int fubicompatible(bloques *b,ftrigers *ft) {

    void *antlog;
    int ret;
    
    char codmat[LCODMAT]="";
    double cantidad=0,uniemb=0;
    char codubi[LCODUBI]="",codart[LCODART]="",codlot[LCODLOT]="",bloqueos[LBLOQUEOS]="";  
    vdubicars ubicar;
    char mensaje[MAXCADENA]="";
    
    
    if (ft->nparam<2) {                
        sprintf(mensaje,"FUBICOMPATIBLE: son obligatorios CODMAT y CODUBI %d",ft->nparam);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    
  
    dameparametro(b,ft,0, V10CADENA, codmat);
    dameparametro(b,ft,1, V10CADENA, codubi);   
    if (ft->nparam>2) dameparametro(b,ft,2, V10CADENA, codart);
    if (ft->nparam>3) dameparametro(b,ft,3, V10CADENA, codlot);
    if (ft->nparam>4) dameparametro(b,ft,4, V10DOUBLE, &uniemb); 
	if (ft->nparam>5) dameparametro(b,ft,5, V10CADENA, bloqueos);
    if (ft->nparam>6) dameparametro(b,ft,6, V10DOUBLE, &cantidad); 
    
    antlog=logoracle;
    logoracle=NULL;
 
    ret=UBICARbuscaubicompatible(codmat,codubi,codart,codlot,uniemb,bloqueos,cantidad,&ubicar);

    if (ret) {
        sprintf(mensaje,"FUBICOMPATIBLE: Error PLSQL al ejecutar VDCOMP.ESCOMPATIBLE");
        ponerrorbloque(b,mensaje); 
        ret=-1;
    } else {
        if (ubicar.compatible!=0) {
            logoracle2cadena(mensaje);
            ponerrorbloque(b,mensaje);  
            ret=-1; 
        } 
    }
    
    logoracle=antlog;
    return(ret);
}