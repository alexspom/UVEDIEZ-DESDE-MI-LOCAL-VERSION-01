/****
* VDSPOOLIMPRE.C
*                                                    
* Prop�sito: M�dulo de gest�n de spools de impresi�n por grupos de impresoras                                                      
*                                                                              
*                                                                              
* Autor  : FGS                                                          
* Fecha  : 12-05-2008                                                         
******
*  Modificaciones:
****/

#include "vdpedidos.h"
#include "execproc/vdexec.h"


int imprimeporspool(char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif)
{
	long ret;
	vdimpres impre;	
    ret=IMPREprocspool(damehostname(),tipoimpre,codimpre,(!fichero)?"":fichero,documento,params,numcopias,fecplanif,(!horaplanif)?"":horaplanif,0,&impre);
	if (ret) {
		v10log(LOGERROR,"%s","imprimeporspool: Error al ejecutar PLSQL vdimpre.spool\n");
		return(ret);
	} 
	return(impre.ret);	
}


int auditaimpre(char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias) 
{
	long ret;
	vdimpres impre;
    char auditar[MAXCADENA]="";	
    strcpy(auditar,damepropcadena("AUDITAIMPRE"));
    if (*auditar!='S') return(0);
    ret=IMPREprocaudita(damehostname(),tipoimpre,codimpre,(!fichero)?"":fichero,documento,params,numcopias,0,"",0,&impre);
	if (ret) {
		v10log(LOGERROR,"%s","auditaimpre: Error al ejecutar PLSQL vdimpre.audita\n");
		return(ret);
	} 
	return(impre.ret);	
}

#define UPDAFICHERO "UPDATE VDIMPRESPOOL SET FICHERO=:FICHERO WHERE ROWID=:MIROWID"
static v10cursors *v10updafichero;

static void actualizafichero(vdimprespools *imsp, char *fichero)
{
	static vdimprespools simsp;
	if (v10updafichero == NULL) {
		v10updafichero = abrecursor(UPDAFICHERO);
		bindtodo(v10updafichero, "FICHERO", simsp.fichero, sizeof(simsp.fichero), V10CADENA,
			"MIROWID", simsp.rowid, sizeof(simsp.rowid), V10CADENA, NULL);
	}
	simsp = *imsp;
	strcpy(simsp.fichero, fichero);
	ejecutacursor(v10updafichero);
}



VDEXPORT int vdimprimespool(void *ptr, char *param)
{
	int ret, prioridad;
	vdimprespools *imsp = ptr;
	vdstatuss staf, stad, staa;
	char tipocorreo[LTIPOCORREO] = "", asunto[LASUNTO] = "", cuerpo[LCUERPO] = "", cprioridad[10] = "";
	char fichero[MAXPATH];

	if ((ret = damestabreviada("vdprocesaspool", param, 1, "#", NULL, "ISP", &staf, 0))) return(-1);
	if ((ret = damestabreviada("vdprocesaspool", param, 2, "#", NULL, "ISP", &stad, 0))) return(-1);
	if ((ret = damestabreviada("vdprocesaspool", param, 3, "#", NULL, "ISP", &staa, 0))) return(-1);
	piece(param, tipocorreo, "#", 4);
	piece(param, asunto, "#", 5);
	piece(param, cuerpo, "#", 6);
	piece(param, cprioridad, "#", 7);
	if (*cprioridad == 0)  prioridad = 3;
	else prioridad = atoi(cprioridad);

	savepoint("vdimprimespool");
	if (!strcmp(imsp->codimpre, PREVISUALIZA)) {
		char ruta[MAXPATH];
		strcpy(ruta, damepropcadena("RUTAPDF"));
		confpdf2fichero(ORAUSR, 0, ruta, NULL);
		dameficheropdf("PREVISUAL", imsp->fichero, fichero);
		actualizafichero(imsp, fichero);
		staf.status = 200;
	}

	ret = vdimprimedesdespool(imsp->tipoimpre, imsp->documento, imsp->params, imsp->numcopias, imsp->codimpre, imsp->fichero, imsp->comentario, tipocorreo, asunto, cuerpo, prioridad);

	switch (ret) {
	case 0:
		cent2a(gettime(), 0, ':', imsp->horaimp);
            imsp->fecimp=damedate();
		imsp->status = staf.status;
		break;

	case IMPRESORANOSPOOL:
		cent2a(gettime(), 0, ':', imsp->horaimp);
            imsp->fecimp=damedate();
		imsp->status = staa.status;
		break;

	case IMPRENOCONECTADA:
		rollbacksavepoint("vdimprimespool");
		imsp->status = stad.status;
		break;
	default:
		rollbacksavepoint("vdimprimespool");
		v10log(LOGNORMAL, "Error %d imprimiendo %ld %s\n", ret, imsp->seqimpre, imsp->comentario);
		imsp->status = -imsp->status;
		break;
	}

	if (IMSPactualizaimpreso(imsp, NOVERIFICA)) {
		v10log(LOGERROR,"%s","vdimprimespool: Error actualizando estado\n");
		rollback();
	}

	commit();
	return(0);
}

VDEXPORT int vdspoolfich(void *ptr, char *param)
{
	int ret=0;
	vdimprespools *imsp = ptr;
	vdstatuss staf;
	char codped[LCODPED]="", coddiv[LCODDIV]="";
	long anoped=0, seqped=0;
	char codbulto[LCODBULTO]="";
	char asignacion[MAXCADENA];
	char tipobulto[LTIPOBULTO] = "";
	char driver[LDRIVER] = "";
	char campo[MAXCADENA] = "";
	char valor[MAXCADENA] = "", valorcc[MAXCADENA] = "",msjerror[MAXCADENA];
	char pathcompleto[MAXPATH] = "";
	int i;
	if ((ret = damestabreviada("vdprocesaspool", param, 1, "#", NULL, "ISP", &staf, 0))) return(-1);
	savepoint("vdpoolfich");
	for (i = 1; i <= numpieces(imsp->params, ";"); i++) {
		piece(imsp->params, asignacion, ";", i);
		if (strlen(asignacion) == 0) break;
		piece(asignacion, campo, "=", 1);
		piece(asignacion, valor, "=", 2);
		if (*valor != '\'')  sprintf(valorcc, "\'%s\'", valor);
		else strcpy(valorcc, valor);
		if (strcmp(campo, "CODPED") == 0) strcpy(codped, valor);
		if (strcmp(campo, "CODDIV") == 0) strcpy(coddiv, valor);
		if (strcmp(campo, "ANOPED") == 0) anoped=atol(valor);
		if (strcmp(campo, "SEQPED") == 0) seqped = atol(valor);
		if (strcmp(campo, "CODBULTO") == 0) strcpy(codbulto, valor);
	}
	if (!es_blanco(codbulto)) {
		vdbultocabs buc;
		ret = BUCselvdbultocab(codbulto, &buc);
		if (ret == 0) {
			strcpy(codped, buc.codped);
			strcpy(coddiv, buc.coddiv);
			anoped = buc.anoped;
			seqped = buc.seqped;
			strcpy(tipobulto, buc.tipobulto);
		}
	}
	if (damedriverimpresora(imsp->tipoimpre, imsp->documento, imsp->fichero, imsp->codimpre, driver, msjerror)) return(-1);
	piece(param, pathcompleto, "#", 2);
	damenombredocumento(imsp->tipoimpre, coddiv, anoped, codped, seqped,tipobulto, imsp->documento, imsp->fichero,driver, msjerror);
	if (*pathcompleto == 'S') damenombrecompleto(imsp->documento, imsp->documento);
	if (ret == 0) {
		imsp->status = staf.status;
	} else {
		rollbacksavepoint("vdpoolfich");
		imsp->status = -imsp->status;

	}
	if (IMSPactualizadocumento(imsp, NOVERIFICA)) {
		v10log(LOGERROR,"%s","vdimprimespool: Error actualizando estado\n");
		rollback();
	}
	commit();
	return(0);
}



VDEXPORT void vdprocesaspool(procesos *proceso)
{  
    int ret;
    char tipocomen[LTIPOCOMEN]="",msjerror[MAXCADENA]="";
    vdstatuss stai;    
    vdimpregrupos imgr;
    vdimprespools imsp;
    
    memset(&imgr,0,sizeof(imgr));

    piece(proceso->proc.param,imgr.grupoimpre,"#",1);   
    if ((ret=damestabreviada("vdprocesaspool",proceso->proc.param, 2, "#", NULL, "ISP", &stai, 0))) return;
    piece(proceso->proc.param,tipocomen,"#",3);

    if (IMGRselvdimpregrupo(imgr.grupoimpre,&imgr)) {
        v10log(LOGERROR,"vdprocesaspool: Grupo de Impresoras %s no existe\n",imgr.grupoimpre);
        return;
    }

    if (*imgr.activo!='S') {
        v10log(LOGERROR,"vdprocesaspool: Grupo de Impresoras %s Inactivo\n",imgr.grupoimpre);
        return;    
    }

    ret=IMSPbuscapendiente(stai.status,imgr.grupoimpre,&imsp);
    while (ret==0) {
        *imsp.comentario=0;
        v10log(LOGNORMAL,"vdprocesaspool: Tratando impresi�n %ld de tipo %s a impresora %s\n",imsp.seqimpre,imsp.tipoimpre,imsp.codimpre);
        VDEXECejecuta(proceso,&imsp,"#","%s#%s#%s#%s#%s", imsp.fichero,imsp.documento,imsp.codimpre,imsp.ordenador,imsp.tipoimpre);
        
        if (*imsp.comentario && *tipocomen) {
            v10comen("VDIMPRESPOOL",imsp.codcomen,tipocomen,0,imsp.comentario,msjerror);                         
            commit();
        }

        v10log(LOGNORMAL,"vdprocesaspool: Fin de impresi�n %ld de tipo %s a impresora %s\n\n",imsp.seqimpre,imsp.tipoimpre,imsp.codimpre);
        ret=IMSPnextpendiente(&imsp);
    }
}
