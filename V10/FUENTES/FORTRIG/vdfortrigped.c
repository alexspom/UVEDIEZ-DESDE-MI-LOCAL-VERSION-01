/****
* VDFORTRIGPED.C
*                                                    
* Propósito: Triggers de pantalla/radio sobre pedidos
*                                                                              
*                                                                              
* Autor  : JMM                                                          
* Fecha  : 03-08-2008                                                         
******
*  Modificaciones:
****/

#include "vdpedidos.h"

//Actualiza las lineas del pedido con las cantidades servidas
VDEXPORT int vdactlineaspedido(char *nomtrig, vdpedidocabs *pec, char *mensaje) {
    int ret=0;
    vdpedidos pedido;
    
    if (PECselvdpedidocab(pec->coddiv,pec->anoped,pec->codped,pec->seqped,pec)) {
        sprintf(mensaje,"%s: No he podido obtener informacion del pedido %s %ld %s %ld",nomtrig,pec->coddiv,pec->anoped,pec->codped,pec->seqped);
        return(-1);
    }
    
	memset(&pedido,0,sizeof(pedido));
    strcpy(pedido.coddiv,pec->coddiv);
    strcpy(pedido.codped,pec->codped);
    pedido.anoped=pec->anoped;
    pedido.seqped=pec->seqped;
    
    ret=PEDIDOprocactlineaspedido(pedido.coddiv,pedido.anoped,pedido.codped,pedido.seqped,pedido.ret,&pedido);
    if (ret || pedido.ret)  {
        sprintf(mensaje,"%s: ERROR actualizando las lineas del pedido %s %ld %s %ld",nomtrig,pec->coddiv,pec->anoped,pec->codped,pec->seqped);
        return(-1);
    }
    
    return(ret);

}

//anula de la linea de bulto pasada por parámetros, la cantidad indicada
VDEXPORT int vdanulcantpendiente(char *nomtrig, vdbultolins *bul, long cantaregularizar,char *mensaje) {
	int ret=0;
	vdbultos bulto;

	if(BULselvdbultolin(bul->codbulto,bul->seqlinea,bul)) {
        sprintf(mensaje,"%s: No he podido obtener informacion de la linea %ld del bulto %s",nomtrig,bul->seqlinea,bul->codbulto);
        return(-1);
    }

	memset(&bulto,0,sizeof(bulto));
	strcpy(bulto.codbulto,bul->codbulto);
	bulto.seqlinea = bul->seqlinea;

	ret=BULTOprocanulacantpendservir(bulto.codbulto,bulto.seqlinea,cantaregularizar,bulto.ret,&bulto);

    if (ret || bulto.ret)  {
        sprintf(mensaje,"%s: ERROR regularizando cantidad %ld de la linea %ld del bulto %s",nomtrig,cantaregularizar,bul->seqlinea,bul->codbulto);
        return(-1);
    }
	return(ret);
}

//TRIGGERS DE PANTALLA

// trigger de form que actualiza las lineas de pedido con las cantidades servidas
// parámetros:
//    coddiv: código de division del pedido
//    codped: codigo del pedido
//    anoped: año del pedido
//    seqped: version del pedido

VDEXPORT int factlineaspedido(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    vdpedidocabs pec;
    
    memset(&pec,0,sizeof(pec));
    if (ft->nparam<4) {                
        sprintf(mensaje,"%s: es obligatorio CODDIV, ANOPED, CODPED  y SEQPED",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    dameparametro(b,ft,0, V10CADENA, pec.coddiv);
    dameparametro(b,ft,1, V10LONG, &pec.anoped);
	dameparametro(b,ft,2, V10CADENA, pec.codped);    
    dameparametro(b,ft,3, V10LONG, &pec.seqped);

    ret=vdactlineaspedido(ft->nombre, &pec, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}


VDEXPORT int fanulcantpendiente(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
	vdbultolins bul;
	long cantaregularizar;

	memset(&bul,0,sizeof(bul));

	if (ft->nparam<3) {                
        sprintf(mensaje,"%s: es obligatorio CODBULTO, SEQLINEA y CANTAREGULARIZAR",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    dameparametro(b,ft,0, V10CADENA, bul.codbulto);
    dameparametro(b,ft,1, V10LONG, &bul.seqlinea);
    dameparametro(b,ft,2, V10LONG, &cantaregularizar);

    ret=vdanulcantpendiente(ft->nombre, &bul, cantaregularizar,mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}





// impresión de etiquetas e informe de pedidos
VDEXPORT int fimprimepedido(bloques *b,ftrigers *ft) {
    int ret; 
    long numcopias=1;
	vdpedidocabs pec;
    char tipoimpre[LTIPOIMPRE]="",documento[LDOCUMENTO]="";
    char params[MAXCADENA]="";
		//,sustparams[MAXCADENA]="";    
    char codimpre[LCODIMPRE]="",msjerror[MAXCADENA]="";

    if (ft->nparam<8) {                
      sprintf(msjerror,"%s: son obligatorios TIPO IMPRESION, CODDIV, AÑO DEL PEDIDO, CÓDIGO DEL PEDIDO, SEC. DEL PEIDO, DOCUMENTO, PARAMETROS E IMPRESORA\n OPCIONAL: NUMERO DE COPIAS",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

	memset(&pec,0,sizeof(pec));
    dameparametro(b,ft,0, V10CADENA, tipoimpre);
    dameparametro(b,ft,1, V10CADENA, pec.coddiv);
    dameparametro(b,ft,2, V10LONG,   &pec.anoped);
	dameparametro(b,ft,3, V10CADENA, pec.codped);
	dameparametro(b,ft,4, V10LONG,   &pec.seqped);
	dameparametro(b,ft,5, V10CADENA, documento);
    dameparametro(b,ft,6, V10CADENA, params);    
    dameparametro(b,ft,7, V10CADENA, codimpre);
    if (ft->nparam>8) dameparametro(b,ft,8, V10LONG, &numcopias);
    
	ret=vdimprimepedido(&pec,tipoimpre,documento,params,codimpre,numcopias,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);	
}


// exporta informes de pedidos a fichero
VDEXPORT int fexportapedido(bloques *b,ftrigers *ft) {
    int ret; 
    long numcopias=1,modospool;
	vdpedidocabs pec;
    char tipoimpre[LTIPOIMPRE]="",documento[LDOCUMENTO]="";
    char params[MAXCADENA]="";
	//,sustparams[MAXCADENA]="";    
    char fichero[LFICHERO]="",msjerror[MAXCADENA]="";

    if (ft->nparam<8) {                
      sprintf(msjerror,"%s: son obligatorios TIPO IMPRESION, CODDIV, AÑO DEL PEDIDO, CÓDIGO DEL PEDIDO, SEC. DEL PEIDO, DOCUMENTO, PARAMETROS E IMPRESORA\n OPCIONAL: NUMERO DE COPIAS",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

	memset(&pec,0,sizeof(pec));
    dameparametro(b,ft,0, V10CADENA, tipoimpre);
    dameparametro(b,ft,1, V10CADENA, pec.coddiv);
    dameparametro(b,ft,2, V10LONG,   &pec.anoped);
	dameparametro(b,ft,3, V10CADENA, pec.codped);
	dameparametro(b,ft,4, V10LONG,   &pec.seqped);
    dameparametro(b,ft,5, V10CADENA, documento);
    dameparametro(b,ft,6, V10CADENA, params);
    dameparametro(b,ft,7, V10CADENA, fichero);
    if (ft->nparam>8) dameparametro(b,ft,8, V10LONG, &modospool);  
    
	ret=vdexportapedido(&pec,tipoimpre,documento,params,fichero,numcopias,modospool,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);	
}



// exporta informes de pedidos a fichero
VDEXPORT int fcreabultospinvconte(bloques *b,ftrigers *ft) {
    int ret; 
	char codmat[LCODMAT]="",codrecurso[LCODRECURSO]="",tarea[LTAREA]="",
		 codubirestos[LCODUBI]="",tarearestos[LTAREA]="",codconcerestos[LCODCONCE]="",msjerror[MAXCADENA]="";
	long stmov,maxbultos;

    if (ft->nparam<8) {                
      sprintf(msjerror,"%s: son obligatorios 8 parámetros",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

	dameparametro(b,ft,0, V10CADENA,	codmat);
    dameparametro(b,ft,1, V10CADENA,	codrecurso);
    dameparametro(b,ft,2, V10CADENA,	tarea);
	dameparametro(b,ft,3, V10LONG,		&stmov);
    dameparametro(b,ft,4, V10CADENA,	codubirestos);
    dameparametro(b,ft,5, V10CADENA,	tarearestos);
    dameparametro(b,ft,6, V10CADENA,	codconcerestos);
    dameparametro(b,ft,7, V10LONG,		&maxbultos);

     
	ret=vdcreabultospinvconte(codmat,codrecurso,tarea,stmov,codubirestos,tarearestos,codconcerestos, maxbultos); 
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);	
}


// exporta informes de pedidos a fichero
VDEXPORT int fpartemovpinv(bloques *b,ftrigers *ft) {
    int ret; 
	long codmov;
	void *ptr;
	char ubipickinv[LCODUBI]="",codmatbulto[LCODMAT]="",msjerror[LCOMENTARIO]="",campocodmovout[MAXCADENA]="";
	double codmovout=0;

    if (ft->nparam<4) {                
      sprintf(msjerror,"%s: son obligatorios 4 parámetros",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    
	dameparametro(b,ft,0, V10LONG,	&codmov);
    dameparametro(b,ft,1, V10CADENA,ubipickinv);
    dameparametro(b,ft,2, V10CADENA,codmatbulto);
	dameparametro(b,ft,3, V10CADENA, campocodmovout);
	ret=vdpartemovpinv(codmov,ubipickinv,codmatbulto,&codmovout,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	ptr=direcncampo(b,campocodmovout);
    if (ptr) *(double *)ptr=codmovout;
	return(ret);	
}

							
VDEXPORT int fcreabpc(bloques *b,ftrigers *ft) {
	char codmat[LCODMAT]="",
		 msjerror[LCOMENTARIO]="";
	int status,ret;

	if (ft->nparam<2) {                
      sprintf(msjerror,"%s: son obligatorios 2 parámetros",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    
	dameparametro(b,ft,0, V10CADENA,codmat);
	dameparametro(b,ft,1, V10LONG, &status);
	
	ret=creabpc(codmat,status,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);
}


VDEXPORT int fregularizastkpinv(bloques *b,ftrigers *ft) {
	int ret;
	long ordenstk;
	double cantidad=0,codmovout=0; // debe capturar el 
	char codmat[LCODMAT]="",
		 codconce[LCODCONCE]="",
		 codubicodconce[LCODUBI]="",
		 observ[MAXCADENA]="",
		 codubidest[LCODUBI]="",		 
		 msjerror[LCOMENTARIO]="",
		 campocodmovout[MAXCADENA]="",
		 *ptr;

	if (ft->nparam<8) {                
      sprintf(msjerror,"%s: son obligatorios 10 parámetros",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    
	dameparametro(b,ft,0, V10CADENA,codmat);
	dameparametro(b,ft,1, V10LONG, &ordenstk);
	dameparametro(b,ft,2, V10CADENA,codconce);
	dameparametro(b,ft,3, V10CADENA,codubicodconce);
	dameparametro(b,ft,4, V10DOUBLE, &cantidad);	
	dameparametro(b,ft,5, V10CADENA,observ);
	dameparametro(b,ft,6, V10CADENA,campocodmovout);
	dameparametro(b,ft,7, V10CADENA,codubidest);

	ret=vdregularizastkpinv(codmat,ordenstk,codconce,codubicodconce,cantidad,observ,&codmovout, codubidest,"",msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	ptr=direcncampo(b,campocodmovout);
    if (ptr) *(double *)ptr=codmovout;
	return(ret);	
}

VDEXPORT int fregularizabpc(bloques *b,ftrigers *ft) {
    int ret; 
	long total,uniemb;
	char codbulto[LCODBULTO]="",
		 codmat[LCODMAT]="",
		 codart[LCODART]="",
		 codlot[LCODLOT]="",
		 codubidest[LCODUBI]="",
		 codubireserva[LCODUBI]="",		 
		 codconce[LCODCONCE]="",
		 ubicodconce[LCODUBI]="",
		 observ[LCOMENTARIO]="",
		 msjerror[LCOMENTARIO]="";

    if (ft->nparam<10) {                
      sprintf(msjerror,"%s: son obligatorios 11 parámetros",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    
	dameparametro(b,ft,0, V10CADENA,codbulto);
	dameparametro(b,ft,1, V10CADENA,codmat);
	dameparametro(b,ft,2, V10CADENA,codart);
	dameparametro(b,ft,3, V10CADENA,codlot);
	dameparametro(b,ft,4, V10LONG,	&uniemb);
	dameparametro(b,ft,5, V10CADENA,codubidest);
	dameparametro(b,ft,6, V10CADENA,codubireserva);
	dameparametro(b,ft,7, V10LONG,	&total);
	dameparametro(b,ft,8, V10CADENA,codconce);
	dameparametro(b,ft,9, V10CADENA,ubicodconce);
	dameparametro(b,ft,10, V10CADENA,observ);
 
	ret=vdregularizabpc(codbulto,codmat,codart,codlot,uniemb,codubidest,codubireserva,total,codconce,ubicodconce,observ,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);	
}