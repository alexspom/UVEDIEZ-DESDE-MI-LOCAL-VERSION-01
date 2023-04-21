/****
* VDPEDPICKINV.C
*                                                    
* Prop�sito: Procesos, algoritmos y funciones propias del picking inverso
*                                            
* Autor  : FGS
* Fecha  : 2-9-2008                                                        
******
*  Modificaciones:
****/

#include "vdpedidos.h"

int pickinvfinvolumetria(vdpedidocabs *pec,char *forzarpickinv, int *haypickinv,int *pickinvret) {
	
	vdpickinvs pickinv;

	if (PICKINVprocfinvolumetria(pec->coddiv,pec->anoped,pec->codped,pec->seqped,forzarpickinv,0,0,&pickinv)) {
		v10log(LOGERROR,"%s","pickinvfinvolumetria: Error ejecutando procedimiento PLSQL VDPCIKINV.FINVOLUMETRIA");
		return(-1);
	}
  
	*haypickinv=pickinv.haypickinv;
	*pickinvret=pickinv.ret;
	return(0);
}


// Algoritmo que asigna los bultos de picking inverso a displays y equilibra la asignaci�n
// par�metros
// PARAM1: Estado final en el caso de que no haya que reorganizar movtos de la serie y queden bultos por asignar a displays.
// PARAM2: Estado final en el caso de que haya que reorganizar movtos de la serie.
// PARAM3: Estado final en el caso de que NO haya que reorganizar movtos de la serie y NO queden bultos por asignar a displays.
// PARAM4: factor de equilibrado
VDEXPORT int vdequilibraserie(void *ptr,char *param) 
{
	char cadfactor[10]="";
    vdstatuss stpdteequili,stpdtebulinv,stpickinv;
	vdseriepreps *spr=ptr; 
	vdpickinvs pickinv;
	int ret;
	char fuerzasprpickinv[2]="N";
    
	if (ret=damestabreviada("vdequilibraserie",param, 1, "#", NULL, "SPR", &stpdteequili, 0)) return(-1);
	if (ret=damestabreviada("vdequilibraserie",param, 2, "#", NULL, "SPR", &stpdtebulinv, 0)) return(-1);
	if (ret=damestabreviada("vdequilibraserie",param, 3, "#", NULL, "SPR", &stpickinv, 0)) return(-1);
	// FACTOR entre 0 y 100, > 0 va dando mas prioridad a las unidades; = 0 igual de prioritario
	piece(param,cadfactor,"#",4);
	if (*damepropcadena("FUERZASPRPICKINV")) strcopia(fuerzasprpickinv,damepropcadena("FUERZASPRPICKINV"),1);

	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocequilibraserie(spr->codserieprep,
		                          STPECSPRPICKINV,
								  STPECPREPARANDO,
								  stpdteequili.status,stpdtebulinv.status,stpickinv.status,
								  0,fuerzasprpickinv,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdequilibraserie: Error ejecutando procedimiento PLSQL pickinv.equilibraserie\n");
		return(-1);
	}
	return(pickinv.ret);
 }


// crea los bultos de picking inverso, a partir de los movtos pdtes de contenedor y el stock disponible en este
VDEXPORT int vdcreabultospinvconte(char *codmat,char *codrecurso,char *tarea,long stmov,
								   char *codubirestos,char *mitarearestos,char *micodconcerestos,long maxbultos) {
	vdpickinvs pickinv;
	int ret;

	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVproccreabultospinvconte(codmat,codrecurso,tarea,stmov,
									   codubirestos,mitarearestos,micodconcerestos,maxbultos,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdcreabultospinvconte: Error ejecutando procedimiento PLSQL pickinv.vdcreabultospinvconte\n");
		return(-1);
	}
	return(pickinv.ret);
}

// parte un movto desde RP a EXPED, es 2, de RP a PI y de PI a EXPED
VDEXPORT int vdpartemovpinv(long codmov,char *ubipickinv,char *codmatbulto,double *codmovout,char *msjerror) {
	vdpickinvs pickinv;
	int ret;

	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocpartemovpinv(codmov,ubipickinv,codmatbulto,0,"",0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdpartemovpinv: Error ejecutando procedimiento PLSQL pickinv.PICKINVprocpartemovpinv\n");
		return(-1);
	}
	*codmovout=pickinv.nuevocodmov;
	if (*pickinv.comentario) strcpy(msjerror,pickinv.comentario);
	return(pickinv.ret);
}

// regulariza la cantidad de una linea de stock, y  si la matricula 
// es la de un bulto de picking inverso, adapta este al nuevo stock
// (crea linea de picking inverso, actualiza linea de restos, .... )
VDEXPORT int vdregularizastkpinv(char *codmat,
								 long ordenstk,
								 char *codconce,
								 char *codubicodconce,
								 double cantidad,
								 char *observ,
								 double *codmovout,
								 char *codubidest,
								 char *comentario,
								 char *msjerror) {
	vdpickinvs pickinv;
	int ret;

	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocregularizastkpinv(codmat,ordenstk,codconce,codubicodconce,cantidad,observ,0,codubidest,comentario,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdregularizastkpinv: Error ejecutando procedimiento PLSQL pickinv.PICKINVprocregularizastkpinv\n");
		return(-1);
	}
	*codmovout=pickinv.nuevocodmov;
	if (*pickinv.comentario) strcpy(msjerror,pickinv.comentario);
	return(pickinv.ret);
}
// regulariza un bulto de picking inverso, anulando las lineas que sean necesarias,
// y el stock sobrante en la matr�cula origen

VDEXPORT int vdregularizabpc(char *codbulto,char *codmat,char *codart,char *codlot,long uniemb,
							 char *codubidest,char *codubireserva,long total,char *codconce,char *ubicodconce,
							 char *observ,char *msjerror)
{
	vdpickinvs pickinv;
	int ret;

	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocregularizabpc(codbulto,codmat,codart,codlot,uniemb,codubidest,codubireserva, total,
		                         codconce,ubicodconce,observ,"",0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdregularizabpc: Error ejecutando procedimiento PLSQL pickinv.PICKINVprocregularizabpc\n");
		return(-1);
	}
	if (*pickinv.comentario) strcpy(msjerror,pickinv.comentario);
	return(pickinv.ret);
}

// reengancha los movtos de una serie de picking inverso, a los bultos de picking inverso existente
// si es reserva diferida, los mvotos de la serie no se encuentran reservados, por lo que se reservan
// seg�n la tarea tareadiferida
VDEXPORT int vdreenganchasprpinv(long codserieprep,long stpdteequili,long stpdtebulinv,long stpickinv,
								 char *diferido,char *tareadiferidauni, char *tareadiferidaemba,long stpedido, char *ejecmovemba) 
{
	vdpickinvs pickinv;
	int ret;
	
	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocreenganchasprpinv(codserieprep,stpdteequili,stpdtebulinv,stpickinv,
		                             diferido,tareadiferidauni,tareadiferidaemba,stpedido,ejecmovemba,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdreenganchasprpinv: Error ejecutando procedimiento PLSQL pickinv.vdreenganchasprpinv\n");
		return(-1);
	}
	return(pickinv.ret);
}

// reengancha los movtos de una art�culo y serie, reservando los motos seg�n la tarea pasada
// y reenganch�ndolos a los bultos de picking inverso existentes, si existen
VDEXPORT int vdreenganchapinv(long codserieprep,char *codart,char *mitareauni) {
	vdpickinvs pickinv;
	int ret;
	
	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocreenganchapinv(codserieprep,codart,mitareauni,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdreenganchapinv: Error ejecutando procedimiento PLSQL pickinv.vdreenganchapinv\n");
		return(-1);
	}
	return(pickinv.ret);
}

// reengancha los movtos de una art�culo y serie, reservando los motos seg�n la tarea pasada
// y reenganch�ndolos a los bultos de picking inverso existentes, si existen
VDEXPORT int vdreenganchaemba(long codserieprep,char *codart,char *mitareaemba, char *ejecmovemba) {
	vdpickinvs pickinv;
	int ret;
	
	memset(&pickinv,0,sizeof(vdpickinvs));
	ret=PICKINVprocreenganchaemba(codserieprep,codart,mitareaemba,ejecmovemba,0,&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","vdreenganchaemba: Error ejecutando procedimiento PLSQL pickinv.vdreenganchapinv\n");
		return(-1);
	}
	return(pickinv.ret);
}

// Algoritmo que reengancha los movtos de una serie de picking inverso a los bultos existentes
// y si la reserva es diferida, reserva los movtos de la serie antes de intentar reengancharlos
// par�metros
// PARAM1: Estado de la serie en caso de quedar bultos por asignar a display
// PARAM2: Estado de la serie si debe seguir intent�ndose reenganchar movtos
// PARAM3: Estado de la serie una vez finalizado el proceso de picking inverso ( equilibrado + reenganche )
// PARAM4: Si la reserva de la serie ha sido diferida, en cuyo caso se intentan reservar movtos
// PARAM5: Tarea de la reserva diferida, si se realiza esta
// PARAM6: Estado final de los pedidos cuando pasa por el reenganche de la serie 
VDEXPORT int vdreenganchaserie(void *ptr,char *param) 
{
    vdstatuss stpdteequili,stpdtebulinv,stpickinv,stpec;
	char diferido[2]="",tareadiferidauni[LTAREA]="",tareadiferidaemba[LTAREA]="",ejecmovemba[2]="";
	vdseriepreps *spr=ptr; 
	int ret;
    
	if (ret=damestabreviada("vdreenganchaserie",param, 1, "#", NULL, "SPR", &stpdteequili, 0)) return(-1);
	if (ret=damestabreviada("vdreenganchaserie",param, 2, "#", NULL, "SPR", &stpdtebulinv, 0)) return(-1);
	if (ret=damestabreviada("vdreenganchaserie",param, 3, "#", NULL, "SPR", &stpickinv, 0)) return(-1);
	piece(param,diferido,"#",4);   
	piece(param,tareadiferidauni,"#",5);   
	piece(param,tareadiferidaemba,"#",6);   
	if (ret=damestabreviada("vdreenganchaserie",param, 7, "#", NULL, "PEC", &stpec, 0)) return(-1);  
	piece(param,ejecmovemba,"#",8);  
	ret=vdreenganchasprpinv(spr->codserieprep,stpdteequili.status,stpdtebulinv.status,stpickinv.status,diferido,tareadiferidauni,tareadiferidaemba,stpec.status,ejecmovemba);
	return(ret);
 }

int creabpc(char *codmat,int status,char *msjerror) {
	int ret;
	vdpickinvs pickinv;
	
	memset(&pickinv,0,sizeof(pickinv));
	ret=PICKINVproccreabpc(codmat,status,"",&pickinv);
	if (ret) {
		v10log(LOGERROR,"%s","creabpc: Error ejecutando procedimiento PLSQL pickinv.PICKINVproccreabpc\n");
		return(-1);
	}
	if (*pickinv.msjerror) {
		strcpy(msjerror,pickinv.msjerror); 
		return(-1);
	}
	return(0);
}
