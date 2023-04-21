/****
* VDFORTRIGART.C
*                                                    
* Propósito: Triggers de articulos
*                                            
* Autor  : FPD
* Fecha  : 23-10-2008                                                        
******
*  Modificaciones:
****/
#include "vd.h"

static int traducecodigo(char *codartalt,char *codart)
{
    vdtradcodigos trc;
	vdartics art;
    int ret;

	//Comprobamos primero si el código introducido es un EAN:
	ret=ARTbuscacodean(codartalt, &art);
	if (ret==0) {
		strcpy(codart,art.codart);
		if (ARTnextcodean(&art)== 0) return -2;	
	}
	else {
		ret=TRCselcodartalt(codartalt,&trc);
		if (ret==0) strcpy(codart,trc.codart);
	}

    return(ret);
}

static int dameduplicadoean(char *codean,char *codart)
{
    int ret;
    vdartics art;
    ret=ARTbuscacodean(codean,&art);
    if (ret) return(ret);
    ret=ARTnextcodean(&art);
    if (ret==0) return(-1);
    strcpy(codart,art.codart);
    return(0);
}

int leearticform(bloques *b,char *codbarras,char *codart,char *codesperado)
{
    int ret;
    char micodart[LCODART];
    char msjerror[MAXCADENA];
    vdartics art;
    if (codart) strcpy(codart,"");
    ret=damecampoean(codbarras,"240",micodart);
    if (ret!=0) {
        ret=damecampoean(codbarras,"02",micodart);
        if (ret==0) {
            if (!es_blanco(codesperado)) {
                ret=ARTselcodart(codesperado,&art);
				if (!ret) {
					if (strcmp(art.codean,micodart)) ret=-1;
					else strcpy(micodart,art.codart);
				}
			} else {
				ret=dameduplicadoean(micodart,micodart);
				if (ret) {
			        strcpy(msjerror,"CODIGO EAN DUPLICADO\nUTILICE ETIQUETA\nCON IDENTIFICADOR 240\nPARA EL ARTICULO\n");
					ponerrorbloque(b,msjerror);
				}
			}
        }
        if (ret!=0) {
            strncpy(micodart,codbarras,LCODART-1);
        }
    }
    ret=ARTselcodart(micodart,&art);
	if (ret!=0) {
		ret=traducecodigo(micodart,micodart);
		if (ret!=0) return(-1);
	}
    if (codart) strcpy(codart,micodart);
    return(0);
}

int pasaacampoform(bloques *b,char *destino,char *valor,ftrigers *ft)
{
    char *dir;
    fcampos *cdest;
    int ret=0;
    if ((dir=existecampo(b,destino))) {
        cdest=b->c+damecampo(b,destino);
        a2bcampo(b,destino,valor);
        if (cdest->change) {
           if (cdest->change->msg && ft) ft->msg=cdest->change->msg;
           if (ret) return(ret);
        }
    }
    return(ret);
}

VDEXPORT int fleearticform(bloques *b,ftrigers *ft)
{
    char codart[LCODART],esperado[LCODART];
    char codbarras[LCADENA];
    char destino[MAXNOMBREV10],origen[MAXNOMBREV10];
    char *dir;
    int ret;
    if (ft->nparam<2) {
        ft->msg="Debe introducir al menos 2 parametros";
        return(-1);
    }
    dameparametro(b,ft,0,V10CADENA,origen);
    dameparametro(b,ft,1,V10CADENA,destino);
    if ((dir=existecampo(b,origen))) {
        strcpy(codbarras,dir);
    } else {
        ft->msg="FLEEARTICFORM: campo origen debe existir";
        return(-1);
    }
    if (ft->nparam>2) {
        dameparametro(b,ft,2,V10CADENA,esperado);
    } else strcpy(esperado,"");
    ret=leearticform(b,codbarras,codart,esperado);
	if (ret) {
		return(ret);
	}
    ret=pasaacampoform(b,destino,codart,ft);
    return(ret);
}
