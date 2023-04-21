/****
* VDPEDIDOSORIG.C
*                                                    
* Propósito: Procesos y algoritmos en C para el tratamiento de pedidos originales 
*                                            
* Autor  : RFD
* Fecha  : 25-3-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"


static int insertacabecerapedido(char *coddiv,long anoped,char *codped,long seqped,long status) {

	int ret=0;
	vdporis pori;
	
/*	secuencia=0;
	ret=PORIbuscasecuencia(coddiv,anoped,codped,seqped,&pori);
	if (ret) {
		v10log(LOGERROR,"insertacabecerapedido - ERROR PLSQL en PORIbuscasecuencia \n");
		return(ret);
	}
	secuencia=pori.secuencia;*/
    PORIprocinsertacabecera(coddiv, anoped, codped, seqped, status, 0, &pori);
	if (pori.retorna) { 
		v10log(LOGERROR,"%s","insertacabecerapedido - ERROR PLSQL en PORIprocinsertacabecera \n");
		return(pori.retorna);
	}
	return(ret);
}

static int insertalineapedido(char *coddiv,long anoped,char *codped,long seqped,long seqlinea) {
	
	vdporis pori;
	
    PORIprocinsertalinea(coddiv,anoped,codped,seqped,seqlinea,0,&pori);
	if (pori.retorna) { 
		v10log(LOGERROR,"%s","insertalineapedido - ERROR PLSQL en PORIprocinsertalinea \n");
		return(pori.retorna);
	}
	return(0);
}


static int grabapedido (vdpedidorigcabs *poc,long status) {

	vdpedidoriglins pol;
//	int creacabecera=1;
	int ret;

	if (*poc->swtmiscelaneo!='S') {
		ret=POLbuscapedido(poc->coddiv,poc->anoped,poc->codped,poc->seqped,&pol);
		if (ret) {
			v10log(LOGERROR,"grabapedido: ERROR no existen líneas de pedido original %s %d %s \n ",poc->coddiv,poc->anoped,poc->codped);
			return(ret);
		}
	}
    ret=insertacabecerapedido(poc->coddiv,poc->anoped,poc->codped,poc->seqped,status);
	if (ret){
		v10log(LOGERROR,"grabapedido: ERROR insertando cabecera de pedido %s %d %s  \n",poc->coddiv,poc->anoped,poc->codped);
		return(ret);			
	}
	if (*poc->swtmiscelaneo!='S') {
		do{
			ret=insertalineapedido(pol.coddiv,pol.anoped,pol.codped,poc->seqped,pol.seqlinea);
			if (ret){
				v10log(LOGERROR,"grabapedido: ERROR insertando linea de pedido %s %d %s %d línea %d \n",pol.coddiv,pol.anoped,pol.codped,pol.seqped,pol.seqlinea);
				return(ret);			
			}
		}while(!POLnextpedido(&pol));
	}
	v10log(LOGNORMAL,"grabapedido: Insertado pedido %s %d %s %d en estado %d  correctamente\n",poc->coddiv,poc->anoped,poc->codped,poc->seqped,status);
	return(0);
}


// Algoritmo que a partir de los datos de un pedido recibido del HOST insertará un pedido en las tablas de pedidos.
// PARAM1: Estado en el que dejar el pedido original si todo ha ido correctamente
// PARAM2: Estado en el que dejar el pedido grabado a partir del original
VDEXPORT int grabapedidosorig(void *ptr,char *param) {

    vdpedidorigcabs *poc=ptr;
    vdstatuss sta,sta2;
	int ret;


    if ((ret=damestabreviada("grabapedidosorig",param, 1, "#",NULL, "PEC", &sta, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta.status,&sta))) {
		v10logcomen(LOGERROR,poc->comen,"grabapedidosorig - ERROR Status PEC %s de pedido no existe para algoritmo grabapedidosorig \n",sta.dabstatus);
		return(-1);
	}
    if ((ret=damestabreviada("grabapedidosorig",param, 2, "#",NULL, "PEC", &sta2, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta2.status,&sta2))) {
		v10logcomen(LOGERROR,poc->comen,"grabapedidosorig - ERROR Status PEC %s de pedido no existe para algoritmo grabapedidosorig \n",sta2.dabstatus);
		return(-1);
	}
    savepoint("grabapedidosorig");
    //buscamos versiones del pedido original que esten en estado < PDTELANZAR, si los hay se borran.
	//RIK hay que cambiar este api porque los negativos se los carga...ABS(STATUS)
 /*   ret=PECbuscastatusmenor(poc->coddiv,poc->anoped,poc->codped,STPECPDTELANZAR,&pec);
	if (!ret) {
		do {
			v10log(LOGNORMAL,"grabapedidosorig: Encontrado pedido %s %d %d %s, en estado %d se borra y se genera el nuevo pedido recibido\n ",pec.coddiv,pec.anoped,pec.seqped,pec.codped,pec.status);
            ret=PELbuscapedido(pec.coddiv,pec.anoped,pec.codped,pec.seqped,&pel);
			if (!ret) {
				do {
					if (PELdel(&pel,NOVERIFICA))			
						v10log(LOGERROR,"grabapedidosorig: ERROR al borrar línea de pedido %s %d %d %s %d \n",pel.coddiv,pel.anoped,pel.seqped,pel.codped,pel.seqlinea);
					else 
						v10log(LOGNORMAL,"grabapedidosorig: Borrada línea de pedido %s %d %d %s %d \n",pel.coddiv,pel.anoped,pel.seqped,pel.codped,pel.seqlinea);
				}while(!PELnextpedido(&pel));
			}
			if (ret=PECdel(&pec,NOVERIFICA)){
	            v10log(LOGERROR,"grabapedidosorig: ERROR al borrar cabecera de pedido %s %d %d %s  \n",pec.coddiv,pec.anoped,pec.seqped,pec.codped);
				return(ret);	
			}
			else 
				v10log(LOGNORMAL,"grabapedidosorig: Borrada cabecera de pedido %s %d %d %s  \n",pec.coddiv,pec.anoped,pec.seqped,pec.codped);
		}while(!PECnextstatusmenor(&pec));
	}
	ret=PECbuscastatusmayor(poc->coddiv,poc->anoped,poc->codped,STPECPDTESERIE,&pec);
	if (!ret) {
		v10log(LOGERROR,"grabapedidosorig: Encontrado pedido %s %d %d %s  en estado %d, no se modifica\n",pec.coddiv,pec.anoped,pec.seqped,pec.codped,pec.status); 
		sprintf(msj,"Encontrado Pedido %s %d %d %s  en estado %d, YA HA SIDO RECIBIDO",pec.coddiv,pec.anoped,pec.seqped,pec.codped,pec.status); 
		v10comenrelogin("VDPEDIDORIGCAB",poc->codcomen,"INCIDENCIA",0,msj,msjerror);
		poc->status=-poc->status;
	}
	else {*/
    ret=grabapedido(poc,sta2.status);
	if (ret) {
			rollbacksavepoint("grabapedidosorig");
			poc->status=-poc->status;
			v10log(LOGERROR,"grabapedidosorig: ERROR al grabar pedido %s %d %s  \n",poc->coddiv,poc->anoped,poc->codped);
		} else {
			poc->status=sta.status;
	}
	ret=POCactualizastatus(poc,NOVERIFICA);
	return(0);
}

// Algoritmo para pedidos miscelaneos que a partir de los datos de un pedido recibido del HOST insertará un pedido en las tablas de pedidos.
// PARAM1: Estado en el que dejar el pedido original si todo ha ido correctamente
// PARAM2: Estado en el que dejar el pedido grabado a partir del original
VDEXPORT int grabapedidosorigmisc(void *ptr,char *param) {

    vdpedidorigcabs *poc=ptr;
    vdstatuss sta,sta2;
	int ret;

    if ((ret=damestabreviada("grabapedidosorigmisc",param, 1, "#",NULL, "PEC", &sta, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta.status,&sta))) {
		v10logcomen(LOGERROR,poc->comen,"grabapedidosorigmisc - ERROR Status PEC %s de pedido no existe para algoritmo grabapedidosorig \n",sta.dabstatus);
		return(-1);
	}
    if ((ret=damestabreviada("grabapedidosorigmisc",param, 2, "#",NULL, "PEC", &sta2, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta2.status,&sta2))) {
		v10logcomen(LOGERROR,poc->comen,"grabapedidosorigmisc - ERROR Status PEC %s de pedido no existe para algoritmo grabapedidosorig \n",sta2.dabstatus);
		return(-1);
	}
    savepoint("grabapedidosorigmisc");
 /*   //buscamos versiones del pedido original que esten en estado < PDTELANZAR, si los hay se borran.
    ret=PECbuscastatusmenor(poc->coddiv,poc->anoped,poc->codped,STPECPDTELANZAR,&pec);
	if (!ret) {
		if (ret=PECdel(&pec,NOVERIFICA)){
	            v10log(LOGERROR,"grabapedidosorigmisc: ERROR al borrar cabecera de pedido %s %d %d %s  \n",pec.coddiv,pec.anoped,pec.seqped,pec.codped);
				return(ret);	
			}
			else 
				v10log(LOGNORMAL,"grabapedidosorigmisc: Borrada cabecera de pedido %s %d %d %s  \n",pec.coddiv,pec.anoped,pec.seqped,pec.codped);
	}
	ret=PECbuscastatusmayor(poc->coddiv,poc->anoped,poc->codped,STPECPDTESERIE,&pec);
	if (!ret) {
		v10log(LOGERROR,"grabapedidosorigmisc: Encontrado pedido %s %d %d %s  en estado %d, no se modifica\n",pec.coddiv,pec.anoped,pec.seqped,pec.codped,pec.status);
		poc->status=-poc->status;
	}
	else {*/
		ret=grabapedido(poc,sta2.status);
		if (ret) {
			rollbacksavepoint("grabapedidosorig");
			poc->status=-poc->status;
			v10log(LOGERROR,"grabapedidosorig: ERROR al grabar pedido %s %d %s  \n",poc->coddiv,poc->anoped,poc->codped);
		} else {
			poc->status=sta.status;
	}
	ret=POCactualizastatus(poc,NOVERIFICA);
	return(0);
}

// Algoritmo que revisa los datos de un pedido recibido del HOST. Si están bien, avanzará el pedido de estado.
// PARAM1: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int validapedidorig(void *ptr,char *param) {

    vdpedidorigcabs *poc=ptr;
    vdpedidoriglins pol;
    vdstatuss sta;
	vdporis poric,poril;
    char msjerror[MAXCADENA]="";
	int ret,linea=0;
	
    if ((ret=damestabreviada("validapedidorig",param, 1, "#",NULL, "PEC", &sta, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta.status,&sta))) {
		v10logcomen(LOGERROR,poc->comen,"validapedidorig - ERROR Status PEC %s de pedido orginal no existe para algoritmo validapedidorig \n",sta.dabstatus);
		return(-1);
	}
//tratamos la cabecera
	v10log(LOGNORMAL,"validapedidorig: Comienza validación de pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	ret=PORIprocvalpedidorigcab(poc->coddiv,poc->anoped,poc->codped,poc->seqped,0,&poric);
	if (ret || poric.retorna) 
		v10log(LOGERROR,"%s","validapedidorig - ERROR PLSQL en PORIprocvalpedidorigcab");
//tratamos las líneas    
    ret = POLbuscalinpepdte(poc->coddiv, poc->anoped, poc->codped,poc->seqped, STPELASERVIR, &pol);
	if (!ret) {
		do {
			ret=PORIprocvalpedidoriglin(pol.coddiv,pol.anoped,pol.codped,pol.seqped,pol.seqlinea,0,&poril);
			if (ret) 
				v10log(LOGERROR,msjerror,"%s","validapedidorig - ERROR PLSQL en PORIprocvalpedidoriglin \n");
			if (poril.retorna) linea=1;	
		}while (!POLnextlinpepdte(&pol));
	}
	else  {
		v10log(LOGERROR,"validapedidorig - ERROR pedido %s %d %s sin líneas pendientes\n ",poc->coddiv,poc->anoped,poc->codped);
		v10comenrelogin("VDPEDIDORIGCAB",poc->codcomen,"INCIDENCIA",0,"PEDIDO SIN LINEAS PENDIENTES",msjerror);
	}
	if (poric.retorna || linea || ret) {
		poc->status=-poc->status;
		ret=POCactualizastatus(poc,NOVERIFICA);
		v10log(LOGERROR,"validapedidorig: Error validando pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	}
	else {
		poc->status=sta.status;
		ret=POCactualizastatus(poc,NOVERIFICA);
		v10log(LOGNORMAL,"validapedidorig: Validado pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	}
	return(ret);
}
// Algoritmo que revisa los datos de un pedido miscelaneo recibido del HOST. Si están bien, avanzará el pedido de estado.
// PARAM1: Estado en el que dejar el pedido si todo ha ido correctamente
VDEXPORT int validapedidorigmisc(void *ptr,char *param) {

    vdpedidorigcabs *poc=ptr;
    vdstatuss sta;
	vdporis poric;
//    char msjerror[MAXCADENA]="";
	int ret;
	//,linea=0;
	
    if ((ret=damestabreviada("validapedidorigmisc",param, 1, "#",NULL, "PEC", &sta, 0))) return(-1);
    if ((ret=STAselvdstatus("PEC",sta.status,&sta))) {
		v10logcomen(LOGERROR,poc->comen,"validapedidorigmisc - ERROR Status PEC %s de pedido orginal no existe para algoritmo validapedidorig \n",sta.dabstatus);
		return(-1);
	}
//tratamos la cabecera
	v10log(LOGNORMAL,"validapedidorigmisc: Comienza validación de pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	ret=PORIprocvalpedidorigcab(poc->coddiv,poc->anoped,poc->codped,poc->seqped,0,&poric);
	if (ret || poric.retorna) {
		v10log(LOGERROR,"%s","validapedidorigmisc - ERROR PLSQL en PORIprocvalpedidorigcab");
		poc->status=-poc->status;
		ret=POCactualizastatus(poc,NOVERIFICA);
		v10log(LOGERROR,"validapedidorigmisc: Error validando pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	}
	else {
		poc->status=sta.status;
		ret=POCactualizastatus(poc,NOVERIFICA);
		v10log(LOGNORMAL,"validapedidorigmisc: Validado pedido recibido por interfase %s %d %s \n",poc->coddiv,poc->anoped,poc->codped);
	}
	return(ret);
}


static int ejecutaalgoritmos(procesos *proceso,vdpedidorigcabs *poc) {
    
    int ret;
	vdagencias ag;
	
	memset(&ag,0,sizeof(ag));
    
	ret=VDEXECejecuta(proceso,poc,"#","%s#%s#%s#%s#%s#%s#%s",
		poc->tipopedido,poc->coddiv,poc->codage,ag.grupoage,poc->codareaexped,poc->backorder,poc->swtmiscelaneo);  
    return(ret);
}



// Proceso que busca pedidos originales en un estado concreto y llama al algoritmo que corresponda
// parámetros
// PARAM1: estado de los pedidos a tratar
// PARAM2: semáforo, se comprueba en el vdexec
VDEXPORT void vdbuscapedorigst(procesos *proceso)
{
    int ret;
//    char msjerror[MAXCADENA]="",
//	char	borracomentarios[2]="";    
    vdpedidorigcabs poc;
    vdstatuss sta;
    
    if ((ret=damestabreviada("vdbuscapedorigst",proceso->proc.param, 1, "#",NULL, "PEC", &sta, 0))) return;
    if (POCbuscastatus(sta.status,&poc)) return;
    
    do { 
        savepoint("vdbuscapedorigst");
        if (ret=POClock(&poc,NOWAIT,VALIDA,"STATUS",NULL)){
            v10log(LOGERROR,"vdbuscapedorigst:Error bloqueando cabecera de pedido. %s\n\t%s\n",POClog(&poc),
                ret==VD_EERRBLOQUEO ? "El campo status ha sido modificado por otro proceso":"Error Oracle bloqueando campo status" );
            rollbacksavepoint("vdbuscapedorigst");        
            continue;
        }      
        v10log(LOGNORMAL,"vdbuscapedorigst: Procesando cabecera de pedido. %s en estado %ld\n",POClog(&poc),sta.status);
        ret=ejecutaalgoritmos(proceso,&poc);
        if (ret) {
            rollbacksavepoint("vdbuscapedorigst");
            if (ret!=VD_ESINALG) {
                v10log(LOGERROR,"vdbuscapedorigst: ERROR %ld procesando pedido. %s \n",ret,POClog(&poc));                    
                poc.status=-poc.status;
                ret=POCactualizastatus(&poc,0);
                if (ret) {
                    rollback();
                    v10log(LOGERROR,"vdbuscapedorigst: ERROR %ld actualizando a estado %ld pedido. %s \n",ret,poc.status,POClog(&poc));
                    continue;
                }               
            }
        }
        commit();
    }while (POCnextstatus(&poc)==0);
}

