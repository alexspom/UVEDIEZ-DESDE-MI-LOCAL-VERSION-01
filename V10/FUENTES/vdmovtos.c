/*******************************************************************************
* Módulo : VDMOVTOS.C                                                          *
* Función: Procesos y algoritmos principales sobre los movimientos             *
*                                                                              *
* Autor	 : Paco Guerrero                                                       *
* Revisado por:                                                                *
* Fecha  : 08-04-2008                                                          *
********************************************************************************

*******************************************************************************/

#include "execproc/vdexec.h"

// cambia el estado de un movto
VDEXPORT int vdcambiastmov(void *ptr,char *param) {
    int ret;
    vdstatuss stnuevoestado;
    vdmovims *mov=ptr;  
    
    if ((ret=damestabreviada("vdcambiastmov",param, 1, "#", mov, "MOV", &stnuevoestado, 0))) return(ret);
	mov->status=stnuevoestado.status;
	return(MOVactualizastatus(mov,0));
}


// ALGORITMO: Asigna flujo a un movimiento ptr
// PARAM1: (ptr) puntero al movto
// PARAM2: (param) parámetros del algoritmo
VDEXPORT int vdasignaflujo(void *ptr,char *param) {
    int ret;
    vdrutass rutas;
    vdubicas ubiori, ubidest;
    vdstatuss stconflujo;
    vdmovims *mov=ptr;  
    
    if ((ret=damestabreviada("v10damecaminomov",param, 1, "#", mov, "MOV", &stconflujo, STMOVPDTERUTA))) return(ret);
 
    ret=RUTASprocasignaflujo(mov->codmov,stconflujo.status,&rutas);
    if (ret) v10log(LOGERROR,"vdasignaflujo: Error ejecutando VDMOV.ASIGNAFLUJO(%ld,%ld)\n",mov->codmov, stconflujo.status);
    MOVselvdmovim(mov->codmov,mov);
    if (mov->status<0 || ret) {
        UBIselvdubica(mov->codubiori,&ubiori);
        UBIselvdubica(mov->codubidest,&ubidest);   
        v10logcomen(LOGERROR,mov->comen,"vdasignaflujo: No puede asignarse flujo a Movimiento %ld con origen %s, destino %s, y calif. de stock %s\n",
            mov->codmov, ubiori.codarea, ubidest.codarea, mov->bloqueosori);
        return(0);
    } else {
        v10log(LOGNORMAL,"vdasignaflujo: Movto %ld asignado flujo\n",mov->codmov);
    }
    return(0);  
}  
  

// ALGORITMO: Enrutador de un movto ptr
// PARAM1: (ptr) puntero al movto
// PARAM2: (param) parámetros del algoritmo 
VDEXPORT int vdenrutamov(void *ptr,char *param)
{
    int ret;
    char fuerzamismopasillo[2]="";  
    vdstatuss stesperarutaesp,stfinal;
    
    vdmovims *mov=ptr;  
    if ((ret=damestabreviada("v10damecaminomov",param, 1, "#", mov, "MOV", &stesperarutaesp, STMOVESPERARUTA))) return(ret);
    if ((ret=damestabreviada("v10damecaminomov",param, 2, "#", mov, "MOV", &stfinal, STMOVPDTERECOGE))) return(ret);
    piece(param,fuerzamismopasillo,"#",3); 
    
    ret=llvdenrutamov(mov, stesperarutaesp.status, stfinal.status, fuerzamismopasillo);
    return(ret);
}


// ALGORITMO. Recoge el stock de origen del movto, a la ubicación intermedia.
// PARAM 1: Estado final del movto
VDEXPORT int vdstockori(void *ptr,char *param) {
    int ret;
    void *antlog=logoracle;
    char cadenalog[MAXCADENA]="";
    vdmovims *mov=ptr;
    vdstatuss stfinal;
    
    if ( (ret=damestabreviada("vdstockori",param, 1, "#", "VDMOVIM", "MOV", &stfinal, STMOVENUBIINTER))) return(ret);        
    logoracle=NULL;
    *mov->comen=0;
    ret=STKAUXactstockori(mov,stfinal.status);
    logoracle2cadena(cadenalog);
    v10log(LOGNORMAL,"%s\n",cadenalog);
    if (ret!=0 && *mov->comen==0) strcpy(mov->comen,cadenalog);
    logoracle=antlog;
    return(ret);
}


// ALGORITMO. Trara el movto pdte de stock, y mira si puede avanzar, en cuyo caso lo pasa al estado pasado como parámetro
// PARAM 1: Estado final del movto
VDEXPORT int vdmovpdtestock(void *ptr,char *param) 
{
    int ret;
	char codubireserva[LCODUBI]="";
    vdstatuss stfinal;
    vdstatuss stsinstk;
	vdcntauxs cntaux;		
	vdmovauxs vdmovaux;
	vdmovims *mov=ptr;
	vdubicas ubi;
    
    if ( (ret=damestabreviada("vdmovpdtestock",param, 1, "#", "VDMOVIM", "MOV", &stfinal, STMOVPDTESTOCK))) return(ret);        
    piece(param,codubireserva,"#",2); 
    if ( (ret=damestabreviada("vdmovpdtestock",param, 3, "#", "VDMOVIM", "MOV", &stsinstk, STMOVPDTESTOCK))) return(ret);
	
	v10log(LOGNORMAL,"vdmovpdtestock: Tratando movto %ld con cantidad %lf de articulo %s y matricula origen \n",mov->codmov,mov->cantidad,mov->codart,mov->codmatori);
	*mov->comen=0;
	if (*codubireserva && strcmp(codubireserva,mov->codubiori)) {
		if (UBIselvdubica(codubireserva,&ubi)) {
			v10log(LOGNORMAL,"vdmovpdtestock: Error, Ubicacion %s no existe\n",codubireserva);		
			return(0);
		}
		
		if (CNTAUXbuscadamecntnomovible(codubireserva,&cntaux)) {
			v10log(LOGNORMAL,"vdmovpdtestock: Error, Ubicacion %s sin contenedores no movibles\n",codubireserva);		
			return(0);
		}
		rollback();
		strcpy(mov->codubiori,codubireserva);		
		strcpy(mov->codmatori,cntaux.codmat);
		ret=MOVactualizareenganchamov(mov,0);
		if (ret) return(ret);
		commit();
	}
	savepoint("vdmovpdtestock");
	ret=MOVAUXprocreservamov(mov->codmov,stfinal.status,0,&vdmovaux);	
	if (ret) {
		rollbacksavepoint("vdmovpdtestock");
		v10log(LOGERROR,"%s","Error ejecutando procedimiento PLSQL VDRESMOV.RESERVAMOV\n\n");
		return(0);
	} 
	if (vdmovaux.reservado>0) {
		v10log(LOGNORMAL,"vdmovpdtestock:\t Reservado %lf para el movto \n",vdmovaux.reservado);
		if (!strcmp(mov->tarea,"PEDUNIDIF")) { 
			strcpy(mov->tarea,"PEDUNI");
			MOVactualizatarea(mov,NOVERIFICA);
		}
	} else 	{
		rollbacksavepoint("vdmovpdtestock");
		v10log(LOGNORMAL,"%s","vdmovpdtestock:\t  No se ha reservado nada para el movto \n");
        if (stsinstk.status!=STMOVPDTESTOCK) {
            mov->status=stsinstk.status;
            MOVactualizastatus(mov,0);
        }
	}
    return(0);
}

// ALGORITMO. Deposita el stock en la ubicación destino del movto.
// PARAM 1: Estado final del movto
VDEXPORT int vdstockdest(void *ptr,char *param) {
    int ret;
    void *antlog=logoracle;
    char cadenalog[MAXCADENA]=""; 
    vdmovims *mov=ptr;
    vdstatuss stfinal;

    if ( (ret=damestabreviada("vdstockdest",param, 1, "#", "VDMOVIM", "MOV", &stfinal, STMOVACTUALIZA))) return(ret);    
    logoracle=NULL;
    *mov->comen=0;  
    ret=STKAUXactstockdest(mov,stfinal.status);
    logoracle2cadena(cadenalog);
    v10log(LOGNORMAL,"%s\n",cadenalog);
    if (ret!=0 && *mov->comen==0) strcpy(mov->comen,cadenalog);
    logoracle=antlog;
    return(ret);
}


// ALGORITMO. Finaliza un movto, pasándolo a estado con o sin interfase
// PARAM 1: Estado del movto una vez se ha finalizado
VDEXPORT int vdfinalizamov(void *ptr,char *param) {
    int ret;
    void *antlog=logoracle;
    char cadenalog[MAXCADENA]=""; 
    vdmovims *mov=ptr;
    vdstatuss stfinalizado;
    vdstatuss stdemlmvfinal,stdemcmvfinal;

    if ( (ret=damestabreviada("vdfinalizamov",param, 1, "#", "VDMOVIM", "MOV", &stfinalizado, STMOVFINALIZADO))) return(ret);    
    if ( (ret=damestabreviada("vdfinalizamov",param, 2, "#", "VDDEMANDALIN", "DEL", &stdemlmvfinal, STDELMVFINAL))) return(ret);    
    if ( (ret=damestabreviada("vdfinalizamov",param, 3, "#", "VDDEMANDACAB", "DEC", &stdemcmvfinal, STDECMVFINAL))) return(ret);    

    logoracle=NULL;
    *mov->comen=0;  
    ret=MOVfinalizamov(mov,stfinalizado.status,stdemlmvfinal.status,stdemcmvfinal.status);
    
    logoracle2cadena(cadenalog);
    v10log(LOGNORMAL,"%s\n",cadenalog);
    if (ret!=0 && *mov->comen==0) strcpy(mov->comen,cadenalog);
    logoracle=antlog;
    return(ret);
}

// ALGORITMO. Determina como se debe de interfasar un movto
// PARAM 1: Estado del movto una vez se ha finalizado
VDEXPORT int vdinterfasamov(void *ptr,char *param) {
    int ret;
    void *antlog=logoracle;
    char cadenalog[MAXCADENA]=""; 
    vdmovims *mov=ptr;
    vdstatuss strevision,stpdteinter,stsininter;
  

    if ( (ret=damestabreviada("vdfinalizamov",param, 1, "#", "VDMOVIM", "MOV", &strevision, STMOVREVISION))) return(ret);    
    if ( (ret=damestabreviada("vdfinalizamov",param, 2, "#", "VDMOVIM", "MOV", &stpdteinter, STMOVPDTEINTER))) return(ret);    
    if ( (ret=damestabreviada("vdfinalizamov",param, 3, "#", "VDMOVIM", "MOV", &stsininter, STMOVSININTER))) return(ret);    

    logoracle=NULL;
    *mov->comen=0;  
    ret=MOVinterfasamov(mov,strevision.status,stpdteinter.status,stsininter.status);    
    logoracle2cadena(cadenalog);
    v10log(LOGNORMAL,"%s\n",cadenalog);
    if (ret!=0 && *mov->comen==0) strcpy(mov->comen,cadenalog);
    logoracle=antlog;
    return(ret);
}



static int ejecutaalgoritmos(procesos *proceso,vdmovims *mov,vdclaseartics *cla) {
    
    int ret;
    vdubicas ubio,ubid;
    
    memset(&ubio,0,sizeof(ubio));
    memset(&ubid,0,sizeof(ubid));

    *cla->codclase=0;

    if (*cla->codclasif && CLAselcodartclasif(mov->codart,cla->codclasif,cla)) {
        v10log(LOGERROR,"ejecutaalgoritmos: Articulo %s no clasificado en Clasificación %s\n",
            mov->codart,cla->codclasif);         
    }    
    UBIselvdubica(mov->codubiori,&ubio);
    UBIselvdubica(mov->codubidest,&ubid);
    
    ret=VDEXECejecuta(proceso,mov,"#","%s#%s#%s#%s#%s#%s#%s#%s",
                     mov->tarea,
                     mov->codconce,
                     mov->codubiori,
                     ubio.codarea,
                     mov->codubidest,
                     ubid.codarea,
                     mov->codart,
                     cla->codclase);
    
    return(ret);
}


// ejecución de algoritmos (por discriminnate) de un proceso dado para un movto, desde un trigger síncrono
VDEXPORT int triggermovsync(char *nomproceso,vdmovims *mov) {
    procesos *miproceso;
    vdclaseartics cla;

    if (cargaproceso(nomproceso)==0) {  
        miproceso=buscaproceso(nomproceso);
        if (!miproceso) return(-1);
    } else return(-1);

    memset(&cla,0,sizeof(cla));
    piece(miproceso->proc.param,cla.codclasif,"#",3);
    return(ejecutaalgoritmos(miproceso,mov,&cla));    
}


// Proceso que busca movtos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// 1 Estado de los movtos
// 2 Tipo de Comentario
// 3 Semáforo 
VDEXPORT void vdbuscamovst(procesos *proceso)
{  
    int ret;  
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss sta;
    vdmovims mov;
    vdclaseartics cla;    
     
    memset(&cla,0,sizeof(cla));
    
    if ((ret=damestabreviada("vdbuscamovst",proceso->proc.param, 1, "#", NULL, "MOV", &sta, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",2);
    piece(proceso->proc.param,cla.codclasif,"#",3);

    if (MOVbuscastatus(sta.status,&mov)) return;
    
      do {

        savepoint("vdbuscamovst");

        if ((ret=MOVlock(&mov,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"Error bloqueando movimiento %ld\n\t%s\n",mov.codmov,
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            continue;
        }
        
        *mov.comen=0;
        v10log(LOGNORMAL,"vdbuscamovst: Procesando movimiento %ld \n",mov.codmov);
        ret=ejecutaalgoritmos(proceso,&mov,&cla);
        if (ret) {
            rollbacksavepoint("vdbuscamovst");
            mov.status=-mov.status;
            ret=MOVactualizastatus(&mov,0);
            if (ret) {
                rollback();
                v10log(LOGERROR,"vdbuscamovst: movto %ld actualizado a estado %ld\n",mov.codmov,mov.status);
            }
            v10log(LOGERROR,"vdbuscamovst: ERROR %ld procesando movimiento %ld \n",ret,mov.codmov);            
        }
            
        // siempre guarda el comentario
        if (*mov.comen) {
            if (*tipocomen==0) v10log(LOGERROR,"vdbuscamovst: NO SE PUEDEN TRATAR COMENTARIOS del Movimiento. %s\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",MOVlog(&mov));            
            else {
                if (mov.codcomen==0) v10log(LOGERROR,"vdbuscamovst: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del Movimiento. %s\n\tCODCOMEN del movto es 0\n",tipocomen,MOVlog(&mov));            
                else v10comen("VDMOVIM",mov.codcomen,tipocomen,0,mov.comen,NULL); 
            }
        }    

        commit();
    } while (0==MOVnextstatus(&mov));
}


// Proceso que busca movtos en un estado concreto y llama al algoritmo que corresponda
// parámetros
// 1 Estado de los movtos
// 2 Tipo de Comentario
// 3 Semáforo 
/*VDEXPORT void vdbuscamovstpinv(procesos *proceso)
{  
    int ret;  
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss sta,stafinal,stesperarutaesp;
    vdmovims mov;
    vdclaseartics cla;    
	vdrutass bultos,movbpl;
	int bultpinv;
	int error;
     
    memset(&cla,0,sizeof(cla));
    
    if (ret=damestabreviada("vdbuscamovst",proceso->proc.param, 1, "#", NULL, "MOV", &sta, 0)) return;
    piece(proceso->proc.param,tipocomen,"#",2);
    piece(proceso->proc.param,cla.codclasif,"#",3);
	if (ret=damestabreviada("vdbuscamovst",proceso->proc.param, 4, "#", NULL, "MOV", &stafinal, STMOVPDTERECOGE)) return;    
	if (ret=damestabreviada("vdbuscamovst",proceso->proc.param, 5, "#", NULL, "MOV", &stesperarutaesp, STMOVESPERARUTA)) return;    

	// saca movtos ordenador por codmov
	ret=RUTASbuscamovtosbultos(sta.status,&bultos);
	if (ret) return;
	do {				
		MOVselvdmovim(bultos.codmov,&mov);
		if (mov.status!=sta.status) continue; // ya ha cambiado el estado, paso a otro
		savepoint ("vdbuscamovst");
		bultpinv=(*bultos.codbulto==0)?0:1;
		error=0;
		if (bultpinv) RUTASbuscamovtosbpl(sta.status,bultos.codbulto,&movbpl);    	
		do {	
			if (!bultpinv) savepoint ("vdbuscamovst");
			if (error==1) {
				v10log(LOGNORMAL,"vdbuscamovstpinv: Ignorado movto %ld al no poder enrutarse por completo el bulto de picking inverso %s\n",
					movbpl.codmov, bultos.codbulto);
				continue;
			}
			if (bultpinv) MOVselvdmovim(movbpl.codmov,&mov);			
			v10log(LOGNORMAL,"vdbuscamovstpinv: Enrutando movto %ld\n",mov.codmov);
			if (ret=MOVlock(&mov,NOWAIT,VALIDA,"STATUS",NULL)){
				v10log(LOGERROR,"Error bloqueando movimiento %ld\n\t%s\n",mov.codmov,
					ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
				error=1;
				if (!bultpinv) rollbacksavepoint("vdbuscamovst");
				break;
			}			
			*mov.comen=0;
			v10log(LOGNORMAL,"vdbuscamovstpinv: Procesando movimiento %ld \n",mov.codmov);
			ret=ejecutaalgoritmos(proceso,&mov,&cla);
			if (ret) {
				if (!bultpinv) rollbacksavepoint("vdbuscamovst");
				mov.status=-mov.status;
				ret=MOVactualizastatus(&mov,0);
				error=1;
				if (ret) {
					rollback();
					v10log(LOGERROR,"vdbuscamovstpinv: movto %ld actualizado a estado %ld\n",mov.codmov,mov.status);
				}
				v10log(LOGERROR,"vdbuscamovstpinv: ERROR %ld procesando movimiento %ld \n",ret,mov.codmov);            
			}  else {
				//MOVselvdmovim(bultos.codmov,&movaux);
				//if (bultpinv && movaux.status!=STMOVANULADO && movaux.status!=STMOVPDTEMOVIM && movaux.status != stafinal.status) {
				if (bultpinv && mov.status!=STMOVPDTEMOVIM && mov.status != stafinal.status) {
					v10log(LOGNORMAL,"vdbuscamovstpinv: Movto %ld del bulto de picking inverso %s no se ha podido enrutar. Ignorará el resto\n",
					movbpl.codmov, bultos.codbulto);
					error=1;
					break;
				}
			}
			if (*mov.comen) {
				if (*tipocomen==0) v10log(LOGERROR,"vdbuscamovstpinv: NO SE PUEDEN TRATAR COMENTARIOS del Movimiento. %s\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",MOVlog(&mov));            
				else {
					if (mov.codcomen==0) v10log(LOGERROR,"vdbuscamovstpinv: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del Movimiento. %s\n\tCODCOMEN del movto es 0\n",tipocomen,MOVlog(&mov));            
					else v10comen("VDMOVIM",mov.codcomen,tipocomen,0,mov.comen,NULL); 
				}	
			}    
			if (!bultpinv) {
				commit();	
				break;
			}			
		} while (RUTASnextmovtosbpl(&movbpl)==0);
		if (bultpinv) {
			if (error==1) {
				rollbacksavepoint("vdbuscamovst");
				// pasa los estados de los movtos del bulto de pinv, de 1200 a 1250
				RUTASprocupdmovtosbpc(bultos.codbulto,&movbpl);	
				v10log(LOGNORMAL,"vdbuscamovstpinv: Movtos del bulto de picking inverso %s  pasan de 1200 a 1250\n",bultos.codbulto);
			}
			commit();
		}
	} while (RUTASnextmovtosbultos(&bultos)==0);
}
*/



VDEXPORT void vdbuscamovpdtestock(procesos *proceso)
{  
    int ret;  
    char tipocomen[LTIPOCOMEN]="";
    vdstatuss sta;
    vdmovims mov;
    vdclaseartics cla;    
     
    memset(&cla,0,sizeof(cla));
    
    if ((ret=damestabreviada("vdbuscamovst",proceso->proc.param, 1, "#", NULL, "MOV", &sta, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",2);
    piece(proceso->proc.param,cla.codclasif,"#",3);

    if (MOVbuscastatusartmat(sta.status,&mov)) return;
    do {
        savepoint("vdbuscamovst");
        if ((ret=MOVlock(&mov,NOWAIT,VALIDA,"STATUS",NULL))) {
            v10log(LOGERROR,"Error bloqueando movimiento %ld\n\t%s\n",mov.codmov,
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            continue;
        }        
        *mov.comen=0;
        v10log(LOGNORMAL,"vdbuscamovst: Procesando movimiento %ld \n",mov.codmov);
        ret=ejecutaalgoritmos(proceso,&mov,&cla);
        if (ret) {
            rollbacksavepoint("vdbuscamovst");
            mov.status=-mov.status;
            ret=MOVactualizastatus(&mov,0);
            if (ret) {
                rollback();
                v10log(LOGERROR,"vdbuscamovst: movto %ld actualizado a estado %ld\n",mov.codmov,mov.status);
            }
            v10log(LOGERROR,"vdbuscamovst: ERROR %ld procesando movimiento %ld \n",ret,mov.codmov);            
        }            
        // siempre guarda el comentario
        if (*mov.comen) {
            if (*tipocomen==0) v10log(LOGERROR,"vdbuscamovst: NO SE PUEDEN TRATAR COMENTARIOS del Movimiento. %s\n\tNO SE HA INDICADO TIPO DE COMENTARIO\n",MOVlog(&mov));            
            else {
                if (mov.codcomen==0) v10log(LOGERROR,"vdbuscamovst: NO SE PUEDEN TRATAR COMENTARIOS de tipo %s del Movimiento. %s\n\tCODCOMEN del movto es 0\n",tipocomen,MOVlog(&mov));            
                else v10comen("VDMOVIM",mov.codcomen,tipocomen,0,mov.comen,NULL); 
            }
        }   
        commit();
    } while (0==MOVnextstatusartmat(&mov));
}
