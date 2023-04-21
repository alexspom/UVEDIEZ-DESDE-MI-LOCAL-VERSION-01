/****
* VDREUBI.C
*                                                    
* Propósito: Reubicación de contenedore completos.                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 21-02-2008                                                         
******
*  Modificaciones:
****/


#include "execproc/vdexec.h"

VDEXPORT int vdreubicaconte(void *ptr,char *param) {
    int pasillo=0,ret;
    vdcontes *cnt=ptr;
    char tarea[LTAREA]="",areaforzada[LCODAREA]="",cpasillo[10]="",uniagrupae[LUNIAGRUPAE]="";
    vdubicars ubicar;


    piece(param,tarea,"#",1);
    if (*tarea==0) {
        v10log(LOGERROR,"%s","vdreubicaconte: Parametro 1, tarea es obligatorio y no está infromado\n");
        return(0);
    }
    
    if (numpieces(param,"#")>1) piece(param,areaforzada,"#",2);
    if (numpieces(param,"#")>2) piece(param,cpasillo,"#",3);
    if (*cpasillo) pasillo=atoi(cpasillo);       
    if (numpieces(param,"#")>3) piece(param,uniagrupae,"#",4);


    ret=UBICARprocreubiconte(cnt->codmat,tarea,0,areaforzada, pasillo,uniagrupae,&ubicar);
    if (ret) {
        v10log(LOGERROR,"vdreubicaconte: ERROR EJECUTANDO PLSQ REUBICACONTE, reubicando contenedor %s\n en area forzada %s por tarea %s, pasillo forzado %d y unidad de agrupacion %s\n",
               cnt->codmat,areaforzada,tarea,pasillo,uniagrupae);
        ret=VD_ESINALG;
    } else {
        if (ubicar.codmov>0) {
            v10log(LOGNORMAL,"vdreubicaconte: Reubicado contenedor %s con movto %ld\n, con area forzada %s por tarea %s, pasillo forzado %d y unidad de agrupacion %s\n",
               cnt->codmat,ubicar.codmov,areaforzada,tarea,pasillo,uniagrupae);
        } else {
            v10log(LOGERROR,"vdreubicaconte: No se puede Reubicar contenedor %s con area forzada %s por tarea %s, pasillo forzado %d y unidad de agrupacion %s\n",
               cnt->codmat,areaforzada,tarea,pasillo,uniagrupae);   
            ret=-1;
        }
    }

    return(ret);
}

static int ejecutaalgoritmosreubi(procesos *proceso,vdcontes *cnt) {

  int ret;
  vdubicas ubi;

  memset(&ubi,0,sizeof(ubi));

  UBIselvdubica(cnt->codubi,&ubi);

  ret=VDEXECejecuta(proceso,cnt,"#","%s#%s#%s#%s",cnt->codmat,cnt->tipoconte,ubi.codubi,ubi.codarea);

  if (ret==VD_ESINALG) v10log(LOGERROR,"ejecutaalgoritmosreubi: No existe algoritmo Activo para reubicar contenedor %lf con discriminante %s#%s#%s#%s\n",cnt->codmat,cnt->codmat,cnt->tipoconte,ubi.codubi,ubi.codarea);            
      
  return(ret);
}


// Proceso que busca contenedores a reubicar en ubic. de trásito
  // param 1 lista de almacenes,verificar que existen los almacenes pasados
  // param 2 obj comentario
  // param 3 tipo comentario
  // param 4 linea de comentario
VDEXPORT void vdbuscacntalm(procesos *proceso)
{  
    char almacenes[MAXCADENA]="";
    char codalm[MAXCADENA]="";
    vdcontes cnt;
    vdubicars ubicar;
    vdalmas alm;
    int ret,numalma=0,i=0;
    
    // param 1 lista de almacenes,verificar que existen los almacenes pasados
    
    piece(proceso->proc.param,almacenes,"#",1);
    numalma=numpieces(almacenes,"$");
    if (numalma==0) {
        v10log(LOGERROR,"%s","vdreubiconte: debes indicar los almacenes para reubicar contenedores\n");
        return;
    }   
    
    do {
        piece(almacenes,codalm,"$",++i);
        
        // verificar que existe el almacén
        ret=ALMselvdalma(codalm,&alm);
        if (ret) {
            v10log(LOGERROR,"vdreubiconte: Almacen %s pasado en la lista de parametros no existe\n",codalm);
            continue;
        }
        
        v10log(LOGNORMAL,"vdreubiconte: Tratando contenedores del almacén %s\n",codalm);
        
        // busca contenedores a reubicar de este almacén
        ret=UBICARbuscaconteaubicar(codalm,&ubicar);
        while (ret==0) {            
            CNTselvdconte(ubicar.codmat,&cnt);
            if ((ret=CNTlock(&cnt,NOWAIT,VALIDA,NULL))) {
                v10log(LOGERROR,"Error bloqueando contenedor %s\n\t%s\n",cnt.codmat,
                    ret==VD_EERRBLOQUEO ? "El contenedor ha sido modificado por otro proceso": "Error Oracle al bloquear contenedor" );
                continue;
            }    
            
            // mirar si el contenedor tiene stock, si no lo tiene, me lo cargo y log
            
            v10log(LOGNORMAL,"vdreubiconte: Ubicando contenedor %s\n",cnt.codmat);
            
            ret=ejecutaalgoritmosreubi(proceso,&cnt);
            if (ret && ret!=VD_ESINALG) {
                v10log(LOGERROR,"vdreubiconte: ERROR %ld procesando contenedor, se bloqueará el contenedor %s \n",ret,cnt.codmat);            
                cnt.status=100; // BLOQUEA CONTENEDOR
                CNTactualizastatus(&cnt,NOVERIFICA);
            }  
            if (ret!=VD_ESINALG) commit();
            else rollback();
            ret=UBICARnextconteaubicar(&ubicar);
        }  // end while

         v10log(LOGNORMAL,"vdreubiconte: Finalizan contenedores del almacén %s\n",codalm);       
    } while (i<numalma);
    
}
