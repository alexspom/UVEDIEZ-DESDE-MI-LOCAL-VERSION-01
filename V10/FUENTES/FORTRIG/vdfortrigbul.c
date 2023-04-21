/****
* VDFORTRIGBUL.C
*                                                    
* Propósito: Triggers de pantalla/radio sobre bultos
*                                                                              
*                                                                              
* Autor  : JMM                                                          
* Fecha  : 21-08-2008                                                         
******
*  Modificaciones:
****/

#include "vdpedidos.h"


//Resuelve un bulto ejecutando todos sus movimientos
VDEXPORT int vdresuelvebulto(char *nomtrig,char *nomprocesoori,char *nomprocesodest,vdbultocabs *buc,char *mensaje) {
    int ret=0,ret2=0;
    vdmovauxs movaux;
    vdmovims mov;
    vdbultolins bul;
	vdbultolins bul2;
    vdrecursos rec;
    //long nuevomov=0;
    
    memset(&bul,0,sizeof(bul));
	memset(&bul2,0,sizeof(bul2));
    memset(&mov,0,sizeof(mov));
    memset(&movaux,0,sizeof(movaux));
    memset(&rec,0,sizeof(rec));
    
    if (BUCselvdbultocab(buc->codbulto,buc)) {
        sprintf(mensaje,"%s: No he podido obtener informacion del bulto %s",nomtrig,buc->codbulto);
        return(-1);
    }
    
    //Si el bulto es de caja completa, en primer lugar debemos partir el movimiento para crear
    //el correspondiente a nuestro bulto con la cantidad pedida y dejar el resto de bultos
    if(!strcmp(buc->tipobulto,"E")) {
        ret=BULbuscalinbulpdte(buc->codbulto,&bul);
        if (ret) {
            sprintf(mensaje,"%s: No puedo obtener informacion de las lineas del bulto %s",nomtrig,buc->codbulto);
            return(-1);
        }
        ret=MOVselvdmovim(bul.codmov,&mov);
        if (ret) {
            sprintf(mensaje,"%s: No puedo obtener informacion del movimiento %ld del bulto %s",nomtrig,bul.codmov,buc->codbulto);
            return(-1);
        }
        //Recupero los bultos del movimiento para restaurarlos correctamente tras la ejecucion de VDMOV.PARTEMOV
		ret2=BULbuscacodmov(bul.codmov,&bul2);
		//Parto el movimiento para obtener uno con la cantidad de nuestro movimiento.
        ret=MOVAUXprocpartemov(bul.codmov,mov.cantidad-bul.cantpedida,movaux.nuevomov,"N",&movaux);
        if (ret) {
            sprintf(mensaje,"%s: No puedo partir movimiento %ld para bulto %s",nomtrig,bul.codmov,buc->codbulto);
            return(-1);
        }
        //A nuestro bulto le asginamos el nuevo movimiento
		bul.codmov=movaux.nuevomov;
		ret=BULactualizacodmov(&bul,NOVERIFICA);
	    if (ret) {
		    sprintf(mensaje,"%s: No puedo dejar movimiento %ld al bulto %s",nomtrig,movaux.nuevomov,bul2.codbulto);
			return(-1);
		}
		//A los otros bultos del movimiento original los dejamos con el que tenían.
		while(ret2==0) {
			if (strcmp(bul.codbulto,bul2.codbulto)) {
				bul2.codmov=movaux.codmov;
				ret=BULactualizacodmov(&bul2,NOVERIFICA);
				if (ret) {
			        sprintf(mensaje,"%s: No puedo asignar movimiento %ld al bulto %s",nomtrig,movaux.nuevomov,bul2.codbulto);
				    return(-1);
				}
			}
			ret2=BULnextcodmov(&bul2);
		}
    }
    //Recupero las lineas del bulto y ejecuto sus movimientos
      ret=BULbuscalinbulpdte(buc->codbulto,&bul);

    if (ret) {
        sprintf(mensaje,"%s: No puedo obtener informacion de las lineas del bulto %s para resolverlas",nomtrig,buc->codbulto);
        return(ret);
    }
    do {
        ret=MOVselvdmovim(bul.codmov,&mov);
        if (ret) {
            sprintf(mensaje,"%s: No puedo recuperar informacion del movimiento %ld para bulto %s",nomtrig,bul.codmov,buc->codbulto);
            return(-1);
        }
        ret=vdejecutamov(nomtrig,nomprocesoori,nomprocesodest,&mov,&rec,mensaje,1);
        if (ret) {
            sprintf(mensaje,"%s: Error ejecutando movimiento %ld para bulto %s",nomtrig,bul.codmov,buc->codbulto);
            return(-1);
        }
    }while(!BULnextlinbulpdte(&bul));
    return(ret);

}

VDEXPORT int vdimprimebultosdemov(char *nomtrig,long codmov,char *codimpre,char *mensaje) {
    int ret;
    vdmovims mov;
    vdbultolins bul;
    vdbultocabs buc;
	vdconfis conf;
//    long numcopias=1;
    char tipoimpre[LTIPOIMPRE]="";
    char documento[LDOCUMENTO]="";
    char params[MAXCADENA]="";
    
    memset(&mov,0,sizeof(mov));
    memset(&bul,0,sizeof(bul));
    memset(&buc,0,sizeof(buc));
    memset(tipoimpre,0,sizeof(tipoimpre));
	memset(&conf, 0, sizeof(conf));
	strcpy(tipoimpre, "ETIQ");
    // comprobamos que exista el moviento
    ret=MOVselvdmovim(codmov,&mov);
    if (ret) {
        sprintf(mensaje,"%s: Error obteniendo datos del movimiento %ld",nomtrig,codmov);
        return(-1);
    }
    // obtenemos los bultos asociados al mismo
    ret=BULbuscacodmov(mov.codmov,&bul);
    if (ret) {
        sprintf(mensaje,"%s: Error no hay bultos asociados al movimiento %ld",nomtrig,codmov);
        return(-1);
    }
    
	//Se buscan los documentos utilizados para la impresión de etiqueta de bulto
	ret = CONFselpropiedad("ETIQUETABULTO", &conf);
	if (ret) {
		sprintf(mensaje, "%s: No puedo obtener datos de la propiedad ETIQEUTABULTO");
		return(-1);
	}

	do {
        //formamos los parámetros de impresion
        memset(params,0,sizeof(params));
        sprintf(params,"CODBULTO=%s;ESCOPIA=N",bul.codbulto);
        //obtenemos el nombre de la etiqueta
        memset(documento,0,sizeof(documento));
        ret=BUCselvdbultocab(bul.codbulto,&buc);
        if (ret) {
            sprintf(mensaje,"%s: No puedo obtener datos de la cabecera del bulto %s asociado al movimiento %ld",nomtrig,bul.codbulto,codmov);
            return(-1);
        }

		strcpy(documento, conf.valor);
		ret=vdimprimebulto(&buc,tipoimpre,documento,params,"",codimpre,1,mensaje);
		if (ret) return(ret);
    } while(!BULnextcodmov(&bul));
    
    return(0);
}
    
//TRIGGERS DE PANTALLA

// trigger de form que resuelve un bulto ejecutando sus movimientos.
// parámetros:
//    nombre proceso actualizador de stock origen
//    nombre proceso actualizador de stock destino
//    codigo de bulto

VDEXPORT int fresuelvebulto(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="",nomprocesoori[LPROCESO]="",nomprocesodest[LPROCESO]="";
    vdbultocabs buc;
    
    memset(&buc,0,sizeof(buc));
    if (ft->nparam<3) {                
        sprintf(mensaje,"%s: es obligatorio PROCESO ACTSTKORI,PROCESO ACTSTKDEST Y CODBULTO",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    dameparametro(b,ft,0, V10CADENA, nomprocesoori);
    dameparametro(b,ft,1, V10CADENA, nomprocesodest);
    dameparametro(b,ft,2, V10CADENA, buc.codbulto);

    ret=vdresuelvebulto(ft->nombre, nomprocesoori, nomprocesodest, &buc, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}

// trigger de radio que imprime los bultos asociados a un movimiento
// parámetros:
//    codmov

VDEXPORT int fimprebultosdemov(bloques *b,ftrigers *ft) {
    int ret;   
    char mensaje[MAXCADENA]="";
    long codmov;
    char codimpre[LCODIMPRE]="";
    
    if (ft->nparam<2) {                
        sprintf(mensaje,"%s: es obligatorio CODIGO DE MOVIMIENTO, CODIGO DE IMPRESORA",ft->nombre);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }

    dameparametro(b,ft,0,V10LONG,&codmov);
    dameparametro(b,ft,1,V10CADENA,codimpre);

    ret=vdimprimebultosdemov(ft->nombre, codmov, codimpre, mensaje);
    if (ret) ponerrorbloque(b,mensaje);
    return(ret);
}



// impresión de etiquetas e informe de bultos
VDEXPORT int fimprimebulto(bloques *b,ftrigers *ft) {
    int ret; 
    long numcopias=1;
	vdbultocabs cb;
    char tipoimpre[LTIPOIMPRE]="",documento[LDOCUMENTO]="";
    char params[MAXCADENA]="";
	//,sustparams[MAXCADENA]="";    
    char codimpre[LCODIMPRE]="",msjerror[MAXCADENA]="",fichero[MAXPATH]="";

    if (ft->nparam<5) {                
      sprintf(msjerror,"%s: son obligatorios TIPO IMPRESION, CÓDIGO DE BULTO, DOCUMENTO, PARAMETROS E IMPRESORA\n OPCIONAL: NUMERO DE COPIAS",ft->nombre);
      ponerrorbloque(b,msjerror); 
      return(-1);
    }    

	memset(&cb,0,sizeof(cb));
    dameparametro(b,ft,0, V10CADENA, tipoimpre);
    dameparametro(b,ft,1, V10CADENA, cb.codbulto);
	dameparametro(b,ft,2, V10CADENA, documento);
    dameparametro(b,ft,3, V10CADENA, params);    
	dameparametro(b, ft, 4, V10CADENA, codimpre);
	if (ft->nparam>5) dameparametro(b, ft, 5, V10LONG, &numcopias);
	if (ft->nparam>6) dameparametro(b, ft, 6, V10LONG, fichero);
    
	ret=vdimprimebulto(&cb,tipoimpre,documento,params,fichero,codimpre,numcopias,msjerror);
	if (ret) ponerrorbloque(b,msjerror); 
	return(ret);	
}

// Gestiona las roturas
VDEXPORT int fbultorotura(bloques *b,ftrigers *ft) {
	int ret=0;
	void *antlog;
	char mensaje[MAXCADENA*10];
	vdbultos bul;
	vdprocesoss proc,procsemaforo;
	vdalgoritmoss alg;

	if (ft->nparam<14) {                
		sprintf(mensaje,"FROTURABULTOS: son obligatorios 14 parametros");
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	memset(&proc,0,sizeof(proc));
	memset(&alg,0,sizeof(alg));

	dameparametro(b,ft,0, V10CADENA, bul.codbulto);
	dameparametro(b,ft,1, V10LONG, &bul.seqlinea);
	dameparametro(b,ft,2, V10DOUBLE, &bul.cantrotura);
	dameparametro(b,ft,3, V10DOUBLE, &bul.cantasustituir);
	dameparametro(b,ft,4, V10CADENA, procsemaforo.proceso);   	
	dameparametro(b,ft,5, V10CADENA, proc.proceso);   
	dameparametro(b,ft,6, V10CADENA, alg.nombrealg);   
	dameparametro(b,ft,7, V10LONG, &bul.statusconte);
	dameparametro(b,ft,8, V10LONG, &bul.statusemba);
	dameparametro(b,ft,9, V10LONG, &bul.statusuni);
	dameparametro(b,ft,10, V10LONG, &bul.statusnuevouni);   
	dameparametro(b,ft,11, V10CADENA, bul.codconce);
	dameparametro(b,ft,12, V10CADENA, bul.codubi);
	dameparametro(b,ft,13, V10LONG, &bul.stnuevomov);

	if (PROselvdprocesos(procsemaforo.proceso,&procsemaforo)) {
		sprintf(mensaje,"FROTURABULTOS: Proceso %s para adquirir sermáforo  no encontrado\n",procsemaforo.proceso);
		ponerrorbloque(b,mensaje); 
		return(-1);
	}
	if (PROselvdprocesos(proc.proceso,&proc)) {
		sprintf(mensaje,"FROTURABULTOS: Proceso %s no encontrado\n",proc.proceso);
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	if (ALGselalgproc(proc.proceso,alg.nombrealg,&alg)) {
		sprintf(mensaje,"FROTURABULTOS: No encontrado algoritmo %s de proceso %s\n",alg.nombrealg,proc.proceso);
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	if (strcmp("vdresdemlpedstd",alg.funcionalg)) {
		sprintf(mensaje,"FROTURABULTOS: Algoritmo %s a cargar parámetros no ejecuta la función vdresdemlpedstd\n",alg.nombrealg);
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	piece(alg.paramalg,bul.tareaconte,"#",1);
	piece(alg.paramalg,bul.tareaemba,"#",2);
	piece(alg.paramalg,bul.tareauni,"#",5);
	piece(alg.paramalg,bul.uniagrupaemba,"#",6);	
	piece(alg.paramalg,bul.uniagrupauni,"#",7);	
	piece(alg.paramalg,bul.monoformato,"#",8);
	piece(alg.paramalg,bul.revisarcompleto,"#",9);
	
	antlog=logoracle;
	logoracle=NULL;
	ret=BULTOprocroturabulto(bul.codbulto,bul.seqlinea,bul.cantrotura,bul.cantasustituir,
						 bul.tareaconte,bul.tareaemba,bul.tareauni,
						 bul.statusconte,bul.statusemba,bul.statusuni,bul.statusnuevouni,
						 bul.uniagrupaemba,bul.uniagrupauni,bul.monoformato,bul.revisarcompleto,procsemaforo.codsemaforo,
						 bul.codconce,bul.codubi,bul.stnuevomov,bul.ret,&bul);
	*mensaje=0;
	logoracle2cadena(mensaje);
	logoracle=antlog;
	
	if (ret) {rollback(); return ret;}
	if (bul.ret) {
		if(*mensaje) ponerrorbloque(b,mensaje);
		rollback(); return bul.ret;
	}	
	return 0;
}




// Gestiona las roturas
VDEXPORT int fbultoroturastk(bloques *b,ftrigers *ft) {
	int ret=0;
	void *antlog;
	char mensaje[MAXCADENA*10];
	vdbultos bul;

	if (ft->nparam<8) {                
		sprintf(mensaje,"FROTURABULTOSSTK: son obligatorios 8 parametros");
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	dameparametro(b,ft,0, V10CADENA, bul.codbulto);
	dameparametro(b,ft,1, V10LONG, &bul.seqlinea);
	dameparametro(b,ft,2, V10DOUBLE, &bul.cantrotura);
	dameparametro(b,ft,3, V10DOUBLE, &bul.cantasustituir);
	dameparametro(b,ft,4, V10CADENA, bul.codmat);
	dameparametro(b,ft,5, V10LONG, &bul.ordenstk);	
	dameparametro(b,ft,6, V10CADENA, bul.codconce);
	dameparametro(b,ft,7, V10CADENA,  bul.codubi);
	bul.ret=0;
	
	antlog=logoracle;
	logoracle=NULL;
	ret=BULTOprocroturabultostk(bul.codbulto,bul.seqlinea,bul.cantrotura,bul.cantasustituir,bul.codmat,bul.ordenstk,"","","",bul.codconce,bul.codubi,ret,&bul);
	*mensaje=0;
	logoracle2cadena(mensaje);
	logoracle=antlog;
	
	if (ret) {rollback(); return ret;}
	if (bul.ret) {
		if(*mensaje) ponerrorbloque(b,mensaje);
		rollback(); return bul.ret;
	}	
	return 0;
}


// Cambia la Reserva de una línea de bulto por servir
VDEXPORT int fcambioreserva(bloques *b,ftrigers *ft) {
	int ret=0;
	void *antlog,*ptrcampo;
	char mensaje[MAXCADENA*10];
	vdbultos bul;
	char campocodmovout [MAXCADENA]="";

	if (ft->nparam<9) {                
		sprintf(mensaje,"FCAMBIORESERVA: son obligatorios 9 parametros");
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	dameparametro(b,ft,0, V10CADENA, bul.codbulto);
	dameparametro(b,ft,1, V10LONG, &bul.seqlinea);
	dameparametro(b,ft,2, V10DOUBLE, &bul.cantrotura);
	dameparametro(b,ft,3, V10CADENA, bul.codmat);
	dameparametro(b,ft,4, V10LONG, &bul.ordenstk);	
	dameparametro(b,ft,5, V10CADENA, bul.codconce);
	dameparametro(b,ft,6, V10CADENA,  bul.codubi);
	dameparametro(b,ft,7, V10LONG,  &bul.ejecmov);
	dameparametro(b,ft,8, V10CADENA,  campocodmovout);

	ptrcampo=(long *)direcncampo(b,campocodmovout);
    if (!ptrcampo) {
        sprintf(mensaje,"FCAMBIORESERVA: No se encuentra campo %s en la pantalla",campocodmovout);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    *(long *)ptrcampo=0;
	
	bul.ret=0;	
	antlog=logoracle;
	logoracle=NULL;
	ret=BULTOproccambioreserva(bul.codbulto,bul.seqlinea,bul.cantrotura,bul.codmat,bul.ordenstk,bul.codconce,bul.codubi,ret,bul.ejecmov,0,&bul);
	*mensaje=0;
	logoracle2cadena(mensaje);
	logoracle=antlog;
	
	if (ret) {rollback(); return ret;}
	if (bul.ret) {
		if(*mensaje) ponerrorbloque(b,mensaje);
		rollback(); return bul.ret;
	}	
	*(long *)ptrcampo=bul.codmovout;
	return 0;
}



// Cambia la Reserva de una línea de bulto por servir
VDEXPORT int fcambioreservapi(bloques *b,ftrigers *ft) {
	int ret=0;
	void *antlog,*ptrcampo;
	char mensaje[MAXCADENA*10];
	vdbultos bul;
	char campocodmovout [MAXCADENA]="";

	if (ft->nparam<8) {                
		sprintf(mensaje,"FCAMBIORESERVAPI: son obligatorios 8 parametros");
		ponerrorbloque(b,mensaje); 
		return(-1);
	}

	dameparametro(b,ft,0, V10CADENA, bul.codbulto);
	dameparametro(b,ft,1, V10CADENA, bul.codmatpi);
	dameparametro(b,ft,2, V10DOUBLE, &bul.cantrotura);
	dameparametro(b,ft,3, V10CADENA, bul.codmat);
	dameparametro(b,ft,4, V10LONG, &bul.ordenstk);	
	dameparametro(b,ft,5, V10CADENA, bul.codconce);
	dameparametro(b,ft,6, V10CADENA,  bul.codubi);
	dameparametro(b,ft,7, V10CADENA,  campocodmovout);

	ptrcampo=(long *)direcncampo(b,campocodmovout);
    if (!ptrcampo) {
        sprintf(mensaje,"FCAMBIORESERVAPI: No se encuentra campo %s en la pantalla",campocodmovout);
        ponerrorbloque(b,mensaje); 
        return(-1);
    }
    *(long *)ptrcampo=0;

	bul.ret=0;	
	antlog=logoracle;
	logoracle=NULL;
	ret=BULTOproccambioreservapi(bul.codbulto,bul.codmatpi,bul.cantrotura,bul.codmat,bul.ordenstk,bul.codconce,bul.codubi,ret,0,&bul);
	*mensaje=0;
	logoracle2cadena(mensaje);
	logoracle=antlog;
	if (ret) {rollback(); return ret;}
	if (bul.ret) {
		if(*mensaje) ponerrorbloque(b,mensaje);
		rollback(); return bul.ret;
	}	
	*(long *)ptrcampo=bul.codmovout;
	return 0;
}