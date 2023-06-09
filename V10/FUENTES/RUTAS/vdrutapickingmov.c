/****
* VDMOVIMRUTASPICKING.C
*                                                    
* Prop�sito: Reengancha bultos de pedidos con stock disponible en �reas de       
*          de picking, en caso de que el movto no se pueda descomponer         
*          por el proceso de RUTAS 
*                                            
* Autor  : FGS e ICC                                  
* Fecha  : 5-11-2007                                                          
******
*  Modificaciones:
****/

#include "vdpedidos.h"

// Asigna a la l�nea de bulto pasada (lb) un nuevo movto con origen la ubicaci�n y matr�cula pasadas,
// cre�ndolo o si ya existe, a�adi�ndole la cantidad 
// PARAM1: (codubiori) ubicaci�n origen del nuevo movimiento
// PARAM2: (codmat) matr�cula origen del nuevo movimiento
// PARAM3: (statusnuevomov) estado en el que se crea el nuevo movimiento
// PARAM4: (mov) movimiento inicialmente asignado a la l�nea de bulto
// PARAM5: (lb) l�nea de bulto que se est� tratando
// PARAM6: (movaux) apunta al nuevo movimiento o al ya existente si lo hay
static int cambiabultospendientes(char *codubiori,char *codmat,long statusnuevomov,vdmovims *mov,vdbultolins *lb,vdmovims *movaux)
{
    int ret;
   
    
    v10log(LOGNORMAL,"cambiabultospendientes - Inicio Intercambio bulto %s de art�culo %s y lote %s desde movimiento %ld\n",
								lb->codbulto,lb->codart,lb->codlot,mov->codmov);	
    
    // hay ya movto creado de reenganche ?
    if (movaux->codmov==0){
        *movaux=*mov;
        movaux->codmov=0;
        strcopia(movaux->codubiori,codubiori,strlen(codubiori));
        strcpy(movaux->codmatori,codmat);
        movaux->status=statusnuevomov;
        movaux->cantidad=0;
        if (ret=MOVinsert(movaux,NOVERIFICA)) {
            v10log(LOGERROR,"cambiabultospendientes: Error insertando movto de matricula %s a ubicacion %s y matricula %s al duplicar movto %ld\n",
               mov->codmatori, mov->codubidest, mov->codmatdest, mov->codmov);
            return(ret);
        }
		v10log(LOGNORMAL,"cambiabultospendientes: Creado nuevo movto de reenganche %ld en matricula %s\n",
                movaux->codmov, mov->codmatori);         
    }
    
    MOVselvdmovim(movaux->codmov,movaux);
    movaux->cantidad+=lb->cantpedida;
    mov->cantidad-=lb->cantpedida;
    lb->codmov=movaux->codmov;
    if (ret=BULactualizacodmov(lb,NOVERIFICA)) {
        v10log(LOGERROR,"cambiabultospendientes: Error actualizando movimiento %ld en l�nea de bulto %s %ld\n",
            lb->codmov, lb->codbulto, lb->seqlinea);
        return(ret);
    }
	v10log(LOGNORMAL,"cambiabultospendientes: Reenganchada l�nea de bulto de expediciones %s %ld de movto %ld a %ld\n",
		lb->codbulto,lb->seqlinea,mov->codmov,movaux->codmov); 
    
    if (ret=MOVactualizacantidad(movaux,NOVERIFICA)) {
        v10log(LOGERROR,"cambiabultospendientes: Error al actualizar cantidad a %lf en movto %ld\n",
            movaux->cantidad, movaux->codmov);
        return(ret);
    }
    
    if (mov->cantidad==0) {
        mov->status=STMOVANULADO;
        if (ret=MOVactualizastatus(mov,NOVERIFICA)) {
            v10log(LOGERROR,"cambiabultospendientes: Error al actualizar estado a %ld de movto %ld\n",
                mov->status, mov->codmov); 
            return(ret);
        }
        v10log(LOGNORMAL,"cambiabultospendientes: anulando movto %ld al reenganchar toda su cantidad\n", mov->codmov);
    } else {
        if (ret=MOVactualizacantidad(mov,NOVERIFICA)) {
            v10log(LOGERROR,"cambiabultospendientes: Error al actualizar cantidad a %lf en movto %ld\n",
                mov->cantidad, mov->codmov); 
            return(ret);
        }
        v10log(LOGNORMAL,"cambiabultospendientes: Actualizada a %lf ( descontandole %lf) cantidad en movto %ld \n", mov->cantidad, lb->cantpedida, mov->codmov);
    }
    
    
    v10log(LOGNORMAL,"cambiabultospendientes - Intercambiado bulto %s de art�culo %s y lote %s desde movimiento %ld a movimiento %ld \n",
								lb->codbulto,lb->codart,lb->codlot,mov->codmov,lb->codmov);	
    return(ret);
}




// Busca l�neas de bulto asociadas al movto trat�ndose, y busca si existe  
// mas stock de este art�culo en el �rea de picking para evitar que los bultos se 
// queden esperando la descomposici�n del movto.
// PARAM1: (ptr) movimiento trat�ndose
// PARAM2: (param) informa de la lista de par�metros del algoritmo
static int vdcaminosdepicking(void *ptr,char *param)
{
    int ret,salir;
    vdmovims *movlb=ptr,mov,movaux;
    vdbultolins lb;
    vdflujoparams flp;
    vdrutass tramo;
    vdubicas ubi;
	char codubireengancha[LCODUBI]="";    
    movaux.codmov=0;
    if (MOVbuscacodmovesp(movlb->codmov,&mov)) mov=*movlb;
	v10log(LOGNORMAL,"vdcaminosdepicking: Movimiento a intentar reenganchar es %ld\n",mov.codmov); 
    FLPselvdflujoparam(mov.codflujo,&flp);
    UBIselvdubica(mov.codubiori,&ubi);
    
	if (BULbuscacodmov(mov.codmov,&lb)) return(0);
    do {
		salir=0;
        if (lb.status != STBULASERVIR) continue; 
        //Buscamos el �rea de picking, que es la pen�ltima del camino
        if (ret=RUTASbuscaareaspicking(flp.codcamino,ubi.codarea,&tramo)) continue;    
        do { 
            if (!strcmp(ubi.codarea,tramo.codareaori)) continue; //ya es el �rea de picking y no hacemos nada
            // Buscamos ubicaci�n con stock del art�culo en el �rea del picking                        
			if (ret=RUTASbuscacontesflujos(mov.codmov,flp.codflujo,tramo.codareaori,&tramo)) continue;

            do {     
				strcopia(codubireengancha,tramo.codubi,strlen(tramo.codubi));
				ret=RUTASbuscastkdisponible(tramo.codmat,mov.codmov,&tramo);
				if (ret) {
					v10log(LOGERROR,"%s","Error en funci�n RUTASbuscastkdisponible\n");
					return(ret);
				} else {
					if (tramo.cantidadtotal>0) {  
						v10log(LOGNORMAL,"Encontrada matr�cula %s en ubicacion %s con stock disponible %lf suficiente para reenganchar el movto %ld\n",
							tramo.codmat,codubireengancha,tramo.cantidadtotal,mov.codmov);
						// si el movto est� asignado a un bulto de picking inverso, debe de tener 
						// en cuenta que la cantidad del stock debe ser mayor que la suma de los movtos del bulto de picking inverso
						if (tramo.cantidadtotal<lb.cantpedida ) {
							v10log(LOGNORMAL,"Descartando reenganche al tratarse de un movto de una l�nea de bulto %s \n con cantidad %lf > disponible (%lf)\n",
									lb.codbulto,lb.cantpedida,tramo.cantidadtotal);											
							continue;			
						}
				
						v10log(LOGNORMAL,"Encontrada matr�cula %s en ubicacion %s con stock %lf suficiente para reenganchar el movto %ld\n",
							tramo.codmat,codubireengancha,tramo.cantidadtotal,mov.codmov);                
						if (movaux.codmov>0 && strcmp(movaux.codmatori,tramo.codmat)) memset(&movaux,0,sizeof(movaux)); 
						if (ret=cambiabultospendientes(codubireengancha, tramo.codmat,STMOVPDTERUTA,&mov,&lb,&movaux)) return(ret);
						salir=1;
					}
				}
            } while (!salir && !RUTASnextcontesflujos(&tramo));			
        } while(!salir && !RUTASnextareaspicking(&tramo)); 
    }while(!BULnextcodmov(&lb));
    return(0);
}



// Algoritmo que ejecuta vdenrutamov estandard y despues reengancha los bultos, si 
// fuese necesario, porque el movto se queda esperando descomposici�n
// PARAM1: (ptr) movimiento trat�ndose
// PARAM2: (param) informa de la lista de par�metros del algoritmo
VDEXPORT int vddamecaminopicking(void *ptr,char *param)
{
    int ret,statusori;
    char fuerzamismopasillo[2]="";  
    vdstatuss stesperarutaesp,stfinal;
    
    vdmovims *mov=ptr;  
    if (ret=damestabreviada("v10damecaminomov",param, 1, "#", mov, "MOV", &stesperarutaesp, STMOVESPERARUTA)) return(ret);
    if (ret=damestabreviada("v10damecaminomov",param, 2, "#", mov, "MOV", &stfinal, STMOVPDTERECOGE)) return(ret);
    piece(param,fuerzamismopasillo,"#",3); 
    
    statusori=mov->status;
    if (ret=vdenrutamov(ptr,param)) return(ret);
    // si el movto ha pasado de 1200 (STMOVPDTERUTA) a 1250 (STMOVESPERARUTA), intenta reenganchar los bultos en el �rea de picking
    if (mov->status!=statusori && mov->status == stesperarutaesp.status) ret=vdcaminosdepicking(ptr,param);
    return(ret);
}


    
