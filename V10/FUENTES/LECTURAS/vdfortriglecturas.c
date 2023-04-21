#include "vdlecturas.h"

static int semaforo=0;

static int limpialecturas(char *msjerror ) {
	int ret;
	vdscanlects scl;

	semaforo=1;
	
	memset(&scl,0,sizeof(scl));
	ret=SCLbuscaescanerystatus(STSCLPENDIENTE,&scl);
	while (!ret) {
		scl.status=STSCLTRATADA;
		ret=SCLdel(&scl,0);
		if (ret) {			 
			sprintf(msjerror,"Error actualizando estado de lectura %ld\n",scl.seqaccion);
			semaforo=0;
			return(-1);
		}
		ret=SCLnextescanerystatus(&scl);
	}
	semaforo=0;
	return(0);
}

VDEXPORT int flimpialecturas(bloques *b,ftrigers *ft) {
    int ret;   
    char msjerror[MAXCADENA]="";

    ret=limpialecturas(msjerror);
	if (ret) mensajefcm(10,msjerror);
	return(ret);
}


static int fanalizaeanform(bloques *b,ftrigers *f)
{
    int np;
    fcampos *c;
    int nc,scan;
    nc=damecampo(b,f->param[0]);
    if (nc<0) {
        f->msg="FANALIZAEAN- NO EXISTE ORIGEN";
        return(-1);
    }
    c=b->c+nc;
    scan=*FSCAN(b,c);
    if (c->tipo!=V10CADENA) {
        f->msg="FANALIZAEAN- ORIGEN DEBE SER CADENA";
        return(-1);
    }
    for (np=1;np<f->nparam;np+=2) {
        int nc1;
        char cadena[MAXCADENA]="";
        fcampos *campo;
        nc1=damecampo(b,f->param[np+1]);
        if (nc1<0) {
            f->msg="FANALIZAEAN- DESTINO NO EXISTE";
            return(-1);
        }
        campo=b->c+nc1;
        if (damecampoean(direcncampo(b,f->param[0]),f->param[np],cadena)==0) {
            a2bcampo(b,f->param[np+1],cadena);
            *FSCAN(b,campo)=scan;
        }
    } 
    return(0);
}

VDEXPORT int flecturas(bloques *b,ftrigers *ft) 
{
	int ret,numcampo;
    char campolectura[LNOMBRE]="",msjerror[MAXCADENA]="";
	vdscanlects scl;
    
	if (semaforo==1) return(-1);

	dameparametro(b,ft,0, V10CADENA, campolectura);
	
	savepoint("flecturas");

	memset(&scl,0,sizeof(scl));
	ret=SCLbuscaescanerystatus(STSCLPENDIENTE,&scl);
	if (ret) return(-1); // si no hay lectura, devuelve error
	scl.status=STSCLTRATADA;
//	ret=SCLactualizastatus(&scl,0);
	ret=SCLdel(&scl,0);
	if (ret) {	
	  rollbacksavepoint("flecturas");		
	  mensajefcm(10,"Error actualizando estado de lectura %ld\n",scl.seqaccion);	  
	  return(ret);
	}

	numcampo=damecampo(b, campolectura);
    if (numcampo<0) {
        rollbacksavepoint("flecturas");
		mensajefcm(10,"No se encuentra campo %s en la pantalla",campolectura);
        return(-1);
    } 
    
	strcopia((char *)direcncampo(b,campolectura),scl.texto,strlen(scl.texto));
    ret=limpialecturas(msjerror);
	if (ft->nparam>1) {
		ret=fanalizaeanform(b,ft);
		if (ret) mensajefcm(10,ft->msg);
	}
	return(ret);
}