/****
* VDFORTRIGMOV.C
*                                                    
* Propósito: Triggers de pantalla/radio sobre stock y movtos, recogida de ubic. origen, depositar en ubic. destino, .... .                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 21-02-2008                                                         
******
*  Modificaciones:
****/

#include "execproc/vdexec.h"


VDEXPORT int vdrecogestk(char *nomtrig,char *nomproceso, vdmovims *mov, vdrecursos *rec, char *mensaje,int sincrono) {
    void *antlog;
    int ret;
    vdstkauxs stock;
    
    ret=0;    
    
    if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }    
    
    if (*rec->codrecurso==0) strcpy(rec->codrecurso,mov->codrecurso);
    if (*rec->codrecurso && RECselcodrecurso(rec->codrecurso,rec)) {
        sprintf(mensaje,"%s: recurso %s no existe",nomtrig,rec->codrecurso);
        return(-1);
    }    
    
    antlog=logoracle;
    logoracle=NULL;    
    ret=STKAUXprocrecogestk(mov->codmov,STMOVRECOGIDO,0,rec->codrecurso,&stock);
    if (ret) {
        sprintf(mensaje,"%s: error al llamar a procedimiento VDMOV.RECOGESTK",nomtrig);     
    } else {
        ret=stock.ret;
        if (ret) {
            sprintf(mensaje,"%s: error al actualizar movto en el procedimiento VDMOV.RECOGESTK",nomtrig);    
        }
    }    
    
    if (sincrono>0 && ret==0) { // ejecución síncrona
        ret=triggermovsync(nomproceso,mov);
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


VDEXPORT int vddepositastk(char *nomtrig,char *nomproceso, vdmovims *mov, char *mensaje, int sincrono) {
    void *antlog;
    int ret;
    vdstkauxs stock;
    
    ret=0;
        
    if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }
   
    antlog=logoracle;
    logoracle=NULL;    
    ret=STKAUXprocdepositastk(mov->codmov,STMOVDEPOSITADO,0,&stock);
    if (ret) {
        sprintf(mensaje,"%s: error al llamar a procedimiento VDMOV.FDEPOSITASTK",nomtrig);     
    } else {
        ret=stock.ret;
        if (ret) {
            sprintf(mensaje,"%s: error al actualizar movto en el procedimiento VDMOV.FDEPOSITASTK",nomtrig);    
        }
    }        
       if (sincrono>0 && ret==0) { // ejecución síncrona
        ret=triggermovsync(nomproceso,mov);
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


VDEXPORT int vdejecutamov(char *nomtrig,char *nomprocesoori,char *nomprocesodest, vdmovims *mov, vdrecursos *rec, char *mensaje, int sincrono)  {
    int ret=0;    
    ret=vdrecogestk(nomtrig,nomprocesoori,mov,rec,mensaje,1); // debe de hacer el recoger de origen de forma síncrona a la fuerza
    if (ret) return(ret);
    return(vddepositastk(nomtrig,nomprocesodest,mov,mensaje,sincrono));
}


int descongela(char *nomtrig, vdmovims *mov, char *mensaje)  {

    void *antlog;
    int ret;
	vdstkauxs stock;
    
    ret=0;
	
	if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }
   
    antlog=logoracle;
    logoracle=NULL;    
    ret=STKAUXprocdescongela(mov->codmov,&stock);
    if (ret) {
        sprintf(mensaje,"%s: error al llamar a procedimiento VDMOV.DESCONGELA",nomtrig);     
    } 
    logoracle=antlog;
    return(ret);
}

int congela(char *nomtrig, vdmovims *mov, char *limpiamov, char *mensaje)  {

    void *antlog;
    int ret;
    vdstkauxs stock;
    
    ret=0;
	
	if (*limpiamov!='S' && *limpiamov!='N') {
		sprintf(mensaje,"El parámetro limpiamov debe ser S o N, y no %s",limpiamov);
		return(-1);
	}
        
    if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }
   
    antlog=logoracle;
    logoracle=NULL;    
    ret=STKAUXproccongela(0,mov->codmov,limpiamov,&stock);
    if (ret) {
        sprintf(mensaje,"%s: error al llamar a procedimiento VDMOV.CONGELA",nomtrig);     
    } else {
        ret=stock.ret;
        if (ret) {
           sprintf(mensaje,"%s: \n",nomtrig);
           logoracle2cadena(mensaje+strlen(mensaje));
        }
    }        

    logoracle=antlog;
    return(ret);
}

int partemov(char *nomtrig, vdmovims *mov, double cantidad, char *limpiamov, char *mensaje)  {

    void *antlog;
    int ret;
    vdmovauxs movaux;
    
    ret=0;
	
	if (*limpiamov!='S' && *limpiamov!='N') {
		sprintf(mensaje,"El parámetro limpiamov debe ser S o N, y no %s",limpiamov);
		return(-1);
	}
        
    if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }
   
    antlog=logoracle;
    logoracle=NULL;  
	ret=MOVAUXprocpartemov(mov->codmov,cantidad,0,limpiamov,&movaux);
    if (ret) {
        sprintf(mensaje,"%s: error al llamar a procedimiento VDMOV.PARTEMOV",nomtrig);     
    } else {
        ret=movaux.ret;
        if (ret) {
           sprintf(mensaje,"%s: \n",nomtrig);
           logoracle2cadena(mensaje+strlen(mensaje));
        }
    }        

    logoracle=antlog;
    return(ret);
}

// anula un movto y los que le esperan
VDEXPORT int vdanulamov(char *nomtrig,char *nomproceso,vdmovims *mov,char *mensaje, int sincrono)  
{ 
    void *antlog;
    int ret;    
    ret=0;    
    
    if (MOVselvdmovim(mov->codmov,mov)) {
        sprintf(mensaje,"%s: movto %ld no existe",nomtrig,mov->codmov);
        return(-1);
    }
    
    if (mov->status>STMOVPRESENTADO) {
        sprintf(mensaje,"%s: movto %ld no se puede anular por su estado",nomtrig,mov->codmov);
        return(-1);    
    }
    
    antlog=logoracle;
    logoracle=NULL;    
    
    *mov->comen=0;
    ret=MOVanulamov(mov);
    if (ret) {
      if (*mov->comen==0) {
        sprintf(mensaje,"%s: \n",nomtrig);
        logoracle2cadena(mensaje+strlen(mensaje)); 
      } else {
        strcopia(mensaje,mov->comen,strlen(mov->comen));   
      }
    }    
    
    if (sincrono>0 && ret==0) { // ejecución síncrona
        ret=triggermovsync(nomproceso,mov);
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


// triggers de pantalla

// recogida ASÍNCRONA de stock en origen a ubic. temporal
// parámetros:
//    codmov: código del movto
//    codrecurso: recurso que ejecuta el movto
VDEXPORT int frecogestk(bloques *b,ftrigers *ft) {    
    int ret;
    char mensaje[MAXCADENA]="";
    vdrecursos rec;
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    memset(&rec,0,sizeof(rec));       
    if (ft->nparam<2) {                
      sprintf(mensaje,"%s: son obligatorios CODMOV y CODRECURSO",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }
    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
    dameparametro(b,ft,1, V10CADENA, rec.codrecurso); 
    ret=vdrecogestk(ft->nombre,"",&mov,&rec,mensaje,0);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}


// recogida SÍNCRONA de stock en origen a ubic. temporal
// parámetros:
//    nomproceso: nombre del proceso que recoge de origen
//    codmov:    código del movto
//    codrecurso: recurso que ejecuta el movto
VDEXPORT int frecogestksync(bloques *b,ftrigers *ft) {
    int ret; 
    char mensaje[MAXCADENA]="",nomproceso[LPROCESO]="";
    vdrecursos rec;
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    memset(&rec,0,sizeof(rec));       
    if (ft->nparam<3) {                
      sprintf(mensaje,"%s: son obligatorios PROCESO, CODMOV y CODRECURSO",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }    
    dameparametro(b,ft,0, V10CADENA, nomproceso);    
    dameparametro(b,ft,1, V10LONG, &mov.codmov);
    dameparametro(b,ft,2, V10CADENA, rec.codrecurso); 

    ret=vdrecogestk(ft->nombre,nomproceso,&mov,&rec,mensaje,1);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}
  

   
// deposita de modo ASÍNCRONO stock en ubic. destino
// parámetros:
//    codmov: código del movto
VDEXPORT int fdepositastk(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<1) {                
      sprintf(mensaje,"%s: es obligatorio CODMOV",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
    ret=vddepositastk(ft->nombre,"",&mov,mensaje,0);  
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}


// deposita de modo SÍNCRONO stock en ubic. destino
// parámetros:
//    nomproceso: nombre del proceso que recoge de origen
//    codmov: código del movto
VDEXPORT int fdepositastksync(bloques *b,ftrigers *ft) {    
    int ret; 
    char mensaje[MAXCADENA]="",nomproceso[LPROCESO]="";
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<2) {                
      sprintf(mensaje,"%s: son obligatorios PROCESO y CODMOV",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }
    
    dameparametro(b,ft,0, V10CADENA, nomproceso);      
    dameparametro(b,ft,1, V10LONG, &mov.codmov);

    ret=vddepositastk(ft->nombre,nomproceso,&mov,mensaje,1); 
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}


// ejecución ASÍNCRONA de un movto, recogida de origen y depositar en ubic. destino
// parámetros:
//    nomproceso recogida stock: nombre del proceso que recoge de origen
//    codmov: código del movto
//    codrecurso: recurso que ejecuta el movto
VDEXPORT int fejecutamov(bloques *b,ftrigers *ft) {    
    int ret; 
    char mensaje[MAXCADENA]="",nomproceso[LPROCESO]="";   
    vdrecursos rec;
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    memset(&rec,0,sizeof(rec));       
    if (ft->nparam<3) {                
      sprintf(mensaje,"%s: son obligatorios PROCESO, CODMOV y CODRECURSO",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }    
    dameparametro(b,ft,0, V10CADENA, nomproceso);    
    dameparametro(b,ft,1, V10LONG, &mov.codmov);
    dameparametro(b,ft,2, V10CADENA, rec.codrecurso);  
   
    ret=vdejecutamov(ft->nombre,nomproceso,"",&mov,&rec,mensaje,0);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

 
  
// ejecución SÍNCRONA de un movto, recogida de origen y depositar en ubic. destino
// parámetros:
//    nomproceso recogida stock: nombre del proceso que recoge de origen
//    nomproceso deposita stock: nombre del proceso que deposita en destino
//    codmov: código del movto
//    codrecurso: recurso que ejecuta el movto
VDEXPORT int fejecutamovsync(bloques *b,ftrigers *ft) {    
    int ret; 
    char mensaje[MAXCADENA]="",nomprocesoori[LPROCESO]="",nomprocesodest[LPROCESO]="";   
    vdrecursos rec;
    vdmovims mov;
   
    memset(&mov,0,sizeof(mov));
    memset(&rec,0,sizeof(rec));       
    if (ft->nparam<4) {                
      sprintf(mensaje,"%s: son obligatorios PROCESO ACTSTKORI,PROCESO ACTSTKDEST, CODMOV y CODRECURSO",ft->nombre);
      ponerrorbloque(b,mensaje); 
      return(-1);
    }    
    dameparametro(b,ft,0, V10CADENA, nomprocesoori);    
    dameparametro(b,ft,1, V10CADENA, nomprocesodest);    
    dameparametro(b,ft,2, V10LONG, &mov.codmov);
    dameparametro(b,ft,3, V10CADENA, rec.codrecurso);    
   
    ret=vdejecutamov(ft->nombre,nomprocesoori,nomprocesodest,&mov,&rec,mensaje,1);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}
  

// descongela un movto, limpiándolo según su linea de demanda asociada
// parámetros:
//    codmov: código del movto
VDEXPORT int fdescongelamov(bloques *b,ftrigers *ft) {
    int ret;
	char mensaje[MAXCADENA]="";
    vdmovims mov;
    
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<1) {                
        sprintf(mensaje,"%s: es obligatorio CODMOV",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
	ret=descongela(ft->nombre, &mov, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

// congela un movto en función del stock en su matrícula origen
// parámetros:
//    codmov: código del movto
//    limpiamov: si se limpia lel nuevo movto que se genera al partir el movto original, al congelarse
VDEXPORT int fcongelamov(bloques *b,ftrigers *ft) {
    int ret;
	char limpiamov[2]="S";   
    char mensaje[MAXCADENA]="";
    vdmovims mov;
    
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<1) {                
        sprintf(mensaje,"%s: es obligatorio CODMOV",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
	if (ft->nparam>1) dameparametro(b,ft,1, V10CADENA, limpiamov);
    ret=congela(ft->nombre, &mov, limpiamov, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

// parte un movto en una cantidad del stock 
// parámetros:
//    codmov: código del movto
//    cantidad: cantidad a mantener en el movto
//    limpiamov: si se limpia el nuevo movto que se genera al partir el movto original, al partirse
VDEXPORT int fpartemov(bloques *b,ftrigers *ft) {
    int ret;
	double cantidad;
	char limpiamov[2]="S";   
    char mensaje[MAXCADENA]="";
    vdmovims mov;
    
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<2) {                
        sprintf(mensaje,"%s: es obligatorio CODMOV y CANTIDAD",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
	dameparametro(b,ft,1, V10DOUBLE, &cantidad);
	if (ft->nparam>2) dameparametro(b,ft,2, V10CADENA, limpiamov);
    ret=partemov(ft->nombre, &mov, cantidad, limpiamov, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

// anula un movto de forma asíncrona
// parámetros:
//    codmov: código del movto
VDEXPORT int fanulamov(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    vdmovims mov;
    
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<1) {                
        sprintf(mensaje,"%s: es obligatorio CODMOV",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }    
    dameparametro(b,ft,0, V10LONG, &mov.codmov);
    ret=vdanulamov(ft->nombre, NULL, &mov, mensaje,0);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

// anula un movto de forma síncrona
// parámetros:
//    codmov: código del movto
//    proceso: proceso que anula movto

VDEXPORT int fanulamovsync(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="",proceso[LPROCESO]="";
    vdmovims mov;
    
    memset(&mov,0,sizeof(mov));
    if (ft->nparam<2) {                
        sprintf(mensaje,"%s: es obligatorio PROCESO y CODMOV",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }        

    dameparametro(b,ft,0, V10CADENA, proceso);
    dameparametro(b,ft,1, V10LONG, &mov.codmov);

    ret=vdanulamov(ft->nombre, proceso, &mov, mensaje,1);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

