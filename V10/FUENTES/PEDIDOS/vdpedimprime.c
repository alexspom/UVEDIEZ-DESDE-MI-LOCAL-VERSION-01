/****
* VDPEDIMPRIME.C
*                                                    
* Propósito: Funciones para la impresión de informes y etiquetas de bultos y pedidos
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 11-08-2008                                                         
******
*  Modificaciones:
****/

#include "vdpedidos.h"

#define SUFIJOEMP		"#E"
#define SUFIJODIV		"#D"
#define SUFIJOAGE		"#A"
#define SUFIJOPED		"#P"
#define SUFIJOTIPOBULTO	"#B"

int damedriverimpresora(char *tipoimpre,char *documento ,char *fichero,char *codimpre, char *driver, char *msjerror)
{
	int ret;
	char fichetiqueta[MAXPATH]="",fichvsq[MAXPATH],ncursor[MAXCADENA]="";
    char midocumento[LDOCUMENTO]="";
    vdimpretipos imtp;
    vdimpresorass impr;
    vdimpregrupos imgr; 
    vdimpreasigs imas;
	*driver=0;
	ret=dametipoimpre(tipoimpre, &imtp, documento, fichero, fichetiqueta, fichvsq, ncursor, midocumento, msjerror);
	if (ret) return(-1);
    ret=dameasignacion(tipoimpre,midocumento,codimpre,&imas,0,msjerror);
    if (ret) return(-1);
    // comprueba que la impresora existe y está activa
    ret=dameimpresora(codimpre,&impr,&imgr,msjerror);
    if (ret) return(-1);
	strcopia(driver,impr.driver,strlen(impr.driver));
	return(0);
}

static int existefichero(char *midocumento,int esetiqueta,char *empsufijodoc,char *divsufijodoc,char *agesufijodoc,
						 char *pecsufijodoc,char *tipobulto,char *msjerror,char *nombredocumento, char *driver) 
{
	FILE *f;
	char ext[MAXCADENA]="",nombresinetiqueta[MAXCADENA]="",*ptr;
	*nombredocumento=0;
	strcpy(nombredocumento,midocumento);
	ptr=strchr(nombredocumento,'.');
	if (ptr) { // me guardo la extensión del fichero
		strcpy(ext,ptr+1);
		*ptr=0;
	}	
	if (esetiqueta) strcpy(ext,driver);
	if (*empsufijodoc) sprintf(nombredocumento+strlen(nombredocumento),"%s%s",SUFIJOEMP,empsufijodoc);
	if (*divsufijodoc) sprintf(nombredocumento+strlen(nombredocumento),"%s%s",SUFIJODIV,divsufijodoc);
	if (*agesufijodoc) sprintf(nombredocumento+strlen(nombredocumento),"%s%s",SUFIJOAGE,agesufijodoc);
	if (*pecsufijodoc) sprintf(nombredocumento+strlen(nombredocumento),"%s%s",SUFIJOPED,pecsufijodoc);
	if (*tipobulto) sprintf(nombredocumento+strlen(nombredocumento),"%s%s",SUFIJOTIPOBULTO,tipobulto);
	strcpy(nombresinetiqueta,nombredocumento);	
	if (*ext) {
		strcat(nombredocumento,".");
		strcat(nombredocumento,ext);
		f=fopenpath(nombredocumento,"rb");
		if (f) {
			fclose(f);
			v10log(LOGNORMAL,"Encontrado fichero %s\n",	nombredocumento);
			return(1);
		} else sprintf(msjerror+strlen(msjerror),"No se encuentra fichero %s\n",nombredocumento);
	}
	if (esetiqueta) {
		strcpy(nombredocumento,nombresinetiqueta);
		strcat(nombredocumento,".GEN");
		f=fopenpath(nombredocumento,"rb");
		if (f) {
			fclose(f);
			v10log(LOGNORMAL,"Encontrado fichero %s\n",	nombredocumento);
			return(1);
		} else sprintf(msjerror+strlen(msjerror),"No se encuentra fichero %s\n",nombredocumento);
	}
	return(0);	
}

// devuelve el nombre de documento con la concatenación de sufijos, comprobando que exista
int damenombredocumento(char *tipoimpre,char *coddiv,long anoped,char *codped,long seqped, 
						char *tipobulto,char *documento, char *fichero, char *driver,char *msjerror) 
{
	int ret,encontrado=0;
	vdimpretipos imtp;
	vdempres emp;
	vddiviss div;
	vdagencias age;
	vdpedidocabs pec;
	char fichvsq[MAXCADENA]="",ncursor[MAXCADENA]="",midocumento[MAXCADENA]="",nombredocumento[MAXCADENA]="";
    strcpy(msjerror,"");
	ret = dametipoimpre(tipoimpre, &imtp, documento, fichero, midocumento, fichvsq, ncursor, midocumento, msjerror);
	strcpy(midocumento, resuelveconf(midocumento, ""));
	if (ret) return(ret);
	if ((ret=PECselvdpedidocab(coddiv,anoped,codped,seqped,&pec))) {
		sprintf(msjerror,"Pedido %s %d %s %d no existe",coddiv,anoped,codped,seqped);
		return(ret);
	}
	if ((ret=AGselvdagencia(pec.codage,&age))) {
		sprintf(msjerror,"Agencia %s no existe",pec.codage);
		return(ret);
	}
	if ((ret=DIVselvddivis(pec.coddiv,&div))) {
		sprintf(msjerror,"División %s no existe",pec.coddiv);
		return(ret);
	}
	if ((ret=EMPREselvdempre(div.codemp,&emp))) {
		sprintf(msjerror,"Empresa %s no existe",div.codemp);
		return(ret);
	}
	encontrado=existefichero(midocumento,*fichvsq?1:0,emp.sufijodoc,div.sufijodoc,age.sufijodoc,pec.sufijodoc,tipobulto,msjerror,nombredocumento,driver);
	if (encontrado==0) encontrado=existefichero(midocumento,*fichvsq?1:0,emp.sufijodoc,div.sufijodoc,age.sufijodoc,pec.sufijodoc,"",msjerror,nombredocumento,driver);
	if (encontrado==0) encontrado=existefichero(midocumento,*fichvsq?1:0,emp.sufijodoc,div.sufijodoc,age.sufijodoc,"","",msjerror,nombredocumento,driver);
	if (encontrado==0) encontrado=existefichero(midocumento,*fichvsq?1:0,emp.sufijodoc,div.sufijodoc,"","","",msjerror,nombredocumento,driver);
	if (encontrado == 0 && !es_blanco(pec.sufijodoc)) encontrado = existefichero(midocumento, *fichvsq ? 1 : 0, "", "", "", pec.sufijodoc, "", msjerror, nombredocumento, driver);
    if (encontrado == 0 && !es_blanco(age.sufijodoc)) encontrado = existefichero(midocumento, *fichvsq ? 1 : 0, "", "", age.sufijodoc, "", "", msjerror, nombredocumento, driver);
    if (encontrado == 0) encontrado = existefichero(midocumento, *fichvsq ? 1 : 0, "", "", age.sufijodoc, "", tipobulto, msjerror, nombredocumento, driver);
    if (encontrado == 0) encontrado = existefichero(midocumento, *fichvsq ? 1 : 0, "", "", "", "", tipobulto, msjerror, nombredocumento, driver);
	if (encontrado==0) encontrado=existefichero(midocumento,*fichvsq?1:0,"","","","","",msjerror,nombredocumento,driver);
	if (encontrado==0) {
		v10log(LOGERROR,"%s",msjerror);
		return(-1);
	} else {
		*msjerror=0;
		if (*fichvsq)	sprintf(documento,"%s;%s;%s",nombredocumento,fichvsq,*age.vdextra==0?ncursor:age.vdextra);		
		else sprintf(documento,"%s",nombredocumento);	
		v10log(LOGERROR,"Se ha formado nombre de documento %s\n",documento);		
	}
	return(0);
}


// imprime un documento de un bulto, concatenando los sufijos del mismo
int vdimprimebulto(vdbultocabs *cb,char *tipoimpre,char *documento,char *params,char *fichero,char *codimpre,int copias,char *msjerror) 
{
	int ret;
	char driver[LDRIVER]="";
	if ((ret=BUCselvdbultocab(cb->codbulto,cb))) {
		sprintf(msjerror,"vdimprimebulto: No se encuentra bulto %s",cb->codbulto);		
		return(ret);
	}	
	if (damedriverimpresora(tipoimpre,documento ,fichero,codimpre,driver,msjerror)) return(-1);
	ret=damenombredocumento(tipoimpre,cb->coddiv,cb->anoped,cb->codped,cb->seqped,cb->tipobulto,documento,"",driver,msjerror);
	if (ret) return(ret);
    return(vdimprime(tipoimpre,documento,params,copias,codimpre,fichero,0,msjerror));
}


int vdimprimepedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *codimpre,int copias,char *msjerror)
{
	int ret;
	char driver[LDRIVER]="";

	if ((ret=PECselvdpedidocab(pec->coddiv,pec->anoped,pec->codped,pec->seqped,pec))) {
		sprintf(msjerror,"vdimprimepedido: No se encuentra pedido %s %d %s %d",pec->coddiv,pec->anoped,pec->codped,pec->seqped);		
		return(ret);
	}
	if (damedriverimpresora(tipoimpre,documento ,"",codimpre,driver,msjerror)) return(-1);
	ret=damenombredocumento(tipoimpre,pec->coddiv,pec->anoped,pec->codped,pec->seqped,"",documento,"",driver,msjerror);
	if (ret) return(ret);
    return(vdimprime(tipoimpre,documento,params,copias,codimpre,"",0,msjerror));
}



int vdexportapedido(vdpedidocabs *pec,char *tipoimpre,char *documento,char *params,char *fichero,int copias,int modospool,char *msjerror)
{
	int ret;
	if ((ret=PECselvdpedidocab(pec->coddiv,pec->anoped,pec->codped,pec->seqped,pec))) {
		sprintf(msjerror,"vdexportapedido: No se encuentra pedido %s %d %s %d",pec->coddiv,pec->anoped,pec->codped,pec->seqped);		
		return(ret);
	}
	ret=damenombredocumento(tipoimpre,pec->coddiv,pec->anoped,pec->codped,pec->seqped,"",documento,fichero,"",msjerror);
	if (ret) return(ret);
    return(vdimprime(tipoimpre,documento,params,copias,"WINFILE",fichero,modospool,msjerror));
}