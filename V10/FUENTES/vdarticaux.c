/*******************************************************************************
* Módulo : VDARTICAUX.C                                                        *
* Función: Rutinas auxiliares sobre la tabla de articulos                      *
*                                                                              *
*                                                                              *
* Autor	 : Eduardo Alsina                                                      *
* Revisado por:                                                                *
* Fecha  : 12-02-2008                                                          *
********************************************************************************

*******************************************************************************/
#include "vdradio.h"

static int traducecodigo(char *codartalt,char *codart)
{
    vdtradcodigos trc;
//	vdartics art;
    int ret;

	//Comprobamos primero si el código introducido es un EAN:
//	ret=ARTbuscacodean(codartalt, &art);
//	if (ret==0) {
//		strcpy(codart,art.codart);
//		if (ARTnextcodean(&art)== 0) return -2;	
//	}
//	else {
		ret=TRCselcodartalt(codartalt,&trc);
        if (ret==0) strcpy(codart,trc.codart);
//	}

    return(ret);
}

static int dameporcodean(char *codean,char *codart,char *esperado)
{
    int ret;
	int primero=1;
    vdartics art;
    ret=ARTbuscacodean(codean,&art);
    if (ret) return(ret);
	while (ret==0) {
		if (strcmp(art.codart,esperado)==0) {
			strcpy(codart,art.codart);
			return 0;
		}
        ret=ARTnextcodean(&art);
		if (ret==0) primero=0;
	}
	if (primero==0) return -1;
    strcpy(codart,art.codart);
    return(0);
}

int leearticulo(bloques *b,char *codbarras,char *codart,char *codesperado)
{
    int ret;
    char micodart[LCODART]="";
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
				ret=dameporcodean(micodart,micodart,codesperado);
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
		ret=dameporcodean(micodart,micodart,codesperado);
		if (ret) {
		   ret=traducecodigo(micodart,micodart);
		   if (ret!=0) return(-1);
		}
	}
    if (codart) strcpy(codart,micodart);
    return(0);
}

int pasaacampo(bloques *b,char *destino,char *valor,int scaneado,ftrigers *ft)
{
    char *dir;
    fcampos *cdest;
    conexiones *con=numcon(b->form->extraform);
    int ret=0;
    if ((dir=existecampo(b,destino))) {
        cdest=b->c+damecampo(b,destino);
        *FSCAN(b,cdest)=scaneado;
        a2bcampo(b,destino,valor);
        if (cdest->change) {
           ret=*FERROR(b,cdest)=ejecutatrigerradio(con,b,cdest->change,PPOSTCHANGE,cdest,1);
           if (cdest->change->msg && ft) ft->msg=cdest->change->msg;
           if (ret) return(ret);
        }
    }
    return(ret);
}

int fleearticulo(bloques *b,ftrigers *ft)
{
    char codart[LCODART],esperado[LCODART];
    char codlot[LCODLOT];
    char codbarras[LCADENA];
    char destino[MAXNOMBREV10],origen[MAXNOMBREV10];
    char *dir;
    fcampos *cori;
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
        ft->msg="FLEEARTICULO: campo origen debe existir";
        return(-1);
    }
    cori=b->c+damecampo(b,origen);
    if (ft->nparam>2) {
        dameparametro(b,ft,2,V10CADENA,esperado);
    } else strcpy(esperado,"");
    ret=leearticulo(b,codbarras,codart,esperado);
	if (ret) {
		return(ret);
	}
    ret=pasaacampo(b,destino,codart,*FSCAN(b,cori),ft);
    if (ret==0) {
       if (ft->nparam>3) {
           dameparametro(b,ft,3,V10CADENA,destino);
           ret=damecampoean(codbarras,"10",codlot);
           if (ret==0) {
               ret=pasaacampo(b,destino,codlot,*FSCAN(b,cori),ft);
           }
       }
    }
    return(ret);
}
