#include "vdinterfase.h"

static void formateanumerico(char *donde, double valor, int longitud, int decimales,char *formatonum,char *formateo)
{
    sprintf(donde, "%0*.0lf", longitud, valor*pow(10, decimales));
    if (*formatonum == ',' && decimales) {
        strins(donde + (strlen(donde) - decimales), ",");
        strcpy(donde, donde + 1);
    }
    if (*formateo == 'T') {
        trim(donde);
    }
    if (*formateo == 'N' && valor == 0) {
        strfill(donde, ' ', longitud);
    }
}

static void formateacampointer(bloques *b,vdinterfasecabs *vdc,vdinterfaselins *vdl,char *donde)
{
    int nc=damecampo(b,vdl->campo);
    fcampos *c;
    double valor;
    if (*vdl->swtactivo!='S') return;
    if (nc<0) {
        v10log(LOGERROR,"No existe campo %s en bloque %s\n",vdl->campo,b->fichero);
        return;
    }
    c=b->c+nc;
    switch (c->tipo) {
        case V10CADENA: if (*vdl->formateo=='D' && !es_blanco(direccampoptr(b,c))) {
                            sprintf(donde,"%-*.*s",vdl->longitud,vdl->longitud,(char *)direccampoptr(b,c));
                        } else {
                            sprintf(donde,"%-*.*s",vdl->longitud,vdl->longitud,vdl->defecto);
                        }
                        if (*vdl->formateo=='I') {
                            trim(donde);
                            lpadcar(donde,vdl->longitud,' ');
                        }
                        if (*vdl->formateo=='T') {
                            trim(donde);
                        }
                        break;
        case V10DOUBLE: valor = *(double *)direccampoptr(b, c);
            formateanumerico(donde, valor, vdl->longitud, vdl->decimales, vdc->formatonum, vdl->formateo);
            break;
        case V10LONG: valor = *(long *)direccampoptr(b, c);
            formateanumerico(donde, valor, vdl->longitud, vdl->decimales, vdc->formatonum, vdl->formateo);
            break;
        case V10INT: valor = *(int *)direccampoptr(b, c);
            formateanumerico(donde, valor, vdl->longitud, vdl->decimales, vdc->formatonum, vdl->formateo);
            break;
    }
    if (*vdc->swtlongfija=='N') trim(donde);
    if (*vdc->separador!=' ') strcat(donde,vdc->separador);
}

static int generalineainter(bloques *b,char *tipointerfase,char *formato,char *donde)
{
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    int ret;
    strcpy(donde,"");
    ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    if (ret) {
        v10log(LOGERROR,"No existe la cabecera de interfase %s %s\n",tipointerfase,formato);
        return -1;
    }
    ret=INTLbuscatipoformato(tipointerfase,formato,&vdlin);
    while (ret==0) {
        formateacampointer(b,&vdcab,&vdlin,donde+strlen(donde));
        ret=INTLnexttipoformato(&vdlin);
    }
    return(0);
}

static int fgeneralineainter(bloques *b,ftrigers *ft)
{
    int ret;
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char *salida=direcncampo(b,SALIDAINTER);
    carganombreinterfase(b,tipointerfase,formato);
    ret=generalineainter(b,tipointerfase,formato,salida);
    v10log(LOGNORMAL,"Salida: %s\n",salida);
    return(ret);
}

#define TIPOFICHEROPLANO  0
#define TIPOFICHEROEXCEL  1
#define TIPOFICHEROXML    2
typedef struct {
           int  tipofichero;
           char tipointerfase[LTIPOINTERFASE];
           char formato[LFORMATO];
           char directorio[MAXPATH];
           char nombre[MAXPATH];
           char nombretotal[MAXPATH];
           char ext[MAXPATH];
           int  transac;
           int  tamano;
           int  lincommit,
                linactual;
		   int  tagdefecto;
		   int  xmlcompacto;
		   int  nivelxml;
		   int  xmlindent;
		   char taginicial[MAXPATH];
		   int  abierto;
           FILE *salida;
           IDispatch *app,*wb,*hoja;
} fichinterfases;

static int generalineaexcel(bloques *b,char *tipointerfase,char *formato,fichinterfases *finter)
{
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    int ret;
    int ncamp;
    ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    if (ret) {
        v10log(LOGERROR,"No existe la cabecera de interfase %s %s\n",tipointerfase,formato);
        return -1;
    }
    ret=INTLbuscatipoformato(tipointerfase,formato,&vdlin);
    ncamp=0;
    while (ret==0) {
        char valor[MAXCADENA],direxcel[MAXLRANGO];
        formateacampointer(b,&vdcab,&vdlin,valor);
        trim(valor);
        pasarangoexcel(ncamp,finter->linactual+1,ncamp,finter->linactual+1, direxcel);
        setvalorstring(finter->hoja,direxcel,valor);
        ret=INTLnexttipoformato(&vdlin);
        ncamp++;
    }
    finter->linactual++;
    return(0);
}

static int tienehijos(bloques *b)
{
	forms *f=b->form;
	unsigned nb;
	for (nb=0;nb<f->nbloques;nb++) {
		if (f->b[nb]->padre==b) return(1);
	}
	return(0);
}

static void fprintxmlnivel(fichinterfases *finter,char *format,...)
{
	int i;
	va_list arg;
	if (finter->xmlindent) for (i=0;i<finter->nivelxml;i++) fprintf(finter->salida,"   ");
	va_start(arg,format);
	vfprintf(finter->salida,format,arg);
	va_end(arg);
}

static int generalineaxml(bloques *b,char *tipointerfase,char *formato,fichinterfases *finter,int xmlcompacto,int tagdefecto)
{
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    int ret;
    int ncamp;
	if (finter->linactual==0) {
		fprintf(finter->salida,"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
		if (!es_blanco(finter->taginicial)) {
			fprintxmlnivel(finter,"<%s>\n",finter->taginicial);
			finter->nivelxml++;
		}
	}
    ret=INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    if (ret) {
        v10log(LOGERROR,"No existe la cabecera de interfase %s %s\n",tipointerfase,formato);
        return -1;
    }
	if (tagdefecto) {
		if (xmlcompacto) {
			fprintxmlnivel(finter,"<%s",formato);
		} else {
			fprintxmlnivel(finter,"<%s>\n",formato);
		}
	}
    ret=INTLbuscatipoformato(tipointerfase,formato,&vdlin);
    ncamp=0;
	finter->nivelxml++;
    while (ret==0) {
        char valor[MAXCADENA];
        formateacampointer(b,&vdcab,&vdlin,valor);
        trim(valor);
		if (xmlcompacto && tagdefecto) {
			fprintf(finter->salida," %s=\"%s\"",vdlin.campohost,valor);
		} else {
			fprintxmlnivel(finter,"<%s>%s</%s>\n",vdlin.campohost,valor,vdlin.campohost);
		}
        ret=INTLnexttipoformato(&vdlin);
        ncamp++;
    }
	finter->nivelxml--;
	if (tienehijos(b)) {
		finter->nivelxml++;
		if (xmlcompacto && tagdefecto) fprintf(finter->salida,">\n");
	} else {
		if (xmlcompacto && tagdefecto) {
			fprintf(finter->salida,"/>\n");
		} else {
			if (tagdefecto) fprintxmlnivel(finter,"</%s>\n",formato);
		}
	}
    finter->linactual++;
    return(0);
}


static int generatituloexcel(bloques *b,fichinterfases *finter)
{
    vdinterfasecabs vdcab;
    vdinterfaselins vdlin;
    int ret;
    int ncamp;
    ret=INTCselvdinterfasecab(finter->tipointerfase,finter->formato,&vdcab);
    if (ret) {
        v10log(LOGERROR,"No existe la cabecera de interfase %s %s\n",finter->tipointerfase,finter->formato);
        return -1;
    }
    ret=INTLbuscatipoformato(finter->tipointerfase,finter->formato,&vdlin);
    ncamp=0;
    while (ret==0) {
        char valor[MAXCADENA],direxcel[MAXLRANGO];
        trim(valor);
        pasarangoexcel(ncamp,1,ncamp,1, direxcel);
        setvalorstring(finter->hoja,direxcel,vdlin.campohost);
        ret=INTLnexttipoformato(&vdlin);
        ncamp++;
    }
    finter->linactual=1;
    return(0);
}

static void damenombrefichero(char *directorio,vdinterfasecabs *vdcab,char *donde)
{
    char fechahora[MAXPATH];
    char fecha[MAXPATH];
	char horaaux[MAXPATH];
	char hora[MAXPATH];
	char ext[MAXPATH],*aux;
    vdinterfasecabs vdpadre;
    jul2a(damedate(),"DDMMY.YY",fechahora);
    cent2a(gettime(),0,'_',fechahora+strlen(fechahora));
    while ((aux=strchr(fechahora,'_'))!=NULL) strcpy(aux,aux+1);
	sprintf(ext,"%s%s",strchr(vdcab->extfichero,'.')?"":".",vdcab->extfichero);
    if (!es_blanco(vdcab->formatopadre)) {
        INTCselvdinterfasecab(vdcab->tipointerfase,vdcab->formatopadre,&vdpadre);
        vdcab->secuencial=vdpadre.secuencial;
    }
    switch (*vdcab->formatofich) {
		   case '0': sprintf(donde,"%s\\%s%s",directorio,vdcab->preffichero,ext);
                     break;
           case '1': sprintf(donde,"%s\\%s%ld%s",directorio,vdcab->preffichero,vdcab->secuencial,ext);
                     break;
           case '2': sprintf(donde,"%s\\%s%s%s",directorio,vdcab->preffichero,fechahora,ext);
                     break;
           case '3': sprintf(donde,"%s\\%s%ld%s%s",directorio,vdcab->preffichero,vdcab->secuencial,fechahora,ext);
                     break;
		   case '4': {jul2a(damedate(),"YYMMDD",fecha);
	                 cent2a(gettime(),6,':',horaaux);
	                 //sprintf(hora,"%2.2s%2.2s%2.2s%2.2s",horaaux,horaaux+3,horaaux+6,horaaux+9);
                     sprintf(hora,"%2.2s%2.2s1314",horaaux,horaaux+3);
                     sprintf(donde,"%s\\%s%s_%s%s",directorio,vdcab->preffichero,fecha,hora,ext);
					 break;
					 }
		   case '5': {jul2a(damedate(),"DDMMYY",fecha);
	                 sprintf(donde,"%s\\%s%s%02ld%s",directorio,vdcab->preffichero,fecha,vdcab->secuencial,ext);
					 break;
					 }
		   case '6': break;//Añadido por si el nombre se le pasa, no es calculado
           case '7': {jul2a(damedate(),"DDMMYY",fecha);
	                 cent2a(gettime(),6,':',horaaux);
                     sprintf(hora,"%2.2s%2.2s",horaaux,horaaux+3);
                     sprintf(donde,"%s\\%s%s%s%s",directorio,vdcab->preffichero,fecha,hora,ext);
					 break;
					 }  
    }
}

static fichinterfases *abrefichero(char *directorio,char *nombre,char *ext,char *modo,int tipofichero)
{
    char nombretotal[MAXPATH];
    FILE *salida;
    fichinterfases *finter;
    sprintf(nombretotal,"%s\\%s.TRC",directorio,nombre);
    salida=fopenpath(nombretotal,modo);
    if (salida==NULL) {
        v10log(LOGERROR,"No puedo abrir fichero %s\\%s.TRC\n",directorio,nombre);
        return(NULL);
    }
    finter=calloc(1,sizeof(fichinterfases));
    strcpy(finter->directorio,directorio);
    strcpy(finter->nombre,nombre);
    strcpy(finter->ext,ext);
    finter->salida=salida;
	finter->abierto = 1;
    finter->transac=1;
    finter->tipofichero=tipofichero;
	finter->xmlcompacto=1;
    v10log(LOGDEBUG,"Abierto fichero %s\\%s.TRC\n",directorio,nombre);
    return(finter);
}

static fichinterfases *abreficheroexcel(char *directorio,char *nombre,char *ext)
{
    char nombretotal[MAXPATH];
    fichinterfases *finter;
    IDispatch *id,*wb,*hoja;
    int ret;
    sprintf(nombretotal,"%s\\%s.TRC",directorio,nombre);
    id=startole("Excel.Application",1);
    ret=cargaexcel(id,&wb,&hoja,"");
        visibleexcel(id,TRUE);
    if (ret) {
        v10log(LOGERROR,"%s","No puedo abrir llamar a Excel\n");
        return(NULL);
    }
    finter=calloc(1,sizeof(fichinterfases));
    finter->app=id;
    finter->wb=wb;
    finter->hoja=hoja;
    strcpy(finter->directorio,directorio);
    strcpy(finter->nombre,nombre);
    strcpy(finter->ext,ext);
    finter->transac=1;
    finter->tipofichero=TIPOFICHEROEXCEL;
    v10log(LOGDEBUG,"%s","Abierta aplicacion Excel\n");
    return(finter);
}

static int fabreficheroexcel(bloques *b,ftrigers *ft)
{
    char directorio[MAXPATH],
         nombref[MAXPATH],
         ext[MAXPATH],
         nombrec[MAXNOMBREV10],
         modo[MAXNOMBREV10];
    char handle[MAXMSGV10];
    fichinterfases *finter;
    dameparametro(b,ft,0,V10CADENA,directorio);
    dameparametro(b,ft,1,V10CADENA,nombref);
    dameparametro(b,ft,2,V10CADENA,ext);
    dameparametro(b,ft,3,V10CADENA,modo);
    dameparametro(b,ft,4,V10CADENA,nombrec);
    finter=abreficheroexcel(directorio,nombref,ext);
    sprintf(handle, "%s=%lf", nombrec, (double)(size_t)finter);
    asignavariables(b,handle);
    if (finter) return(0);
    return(-1);
}

static int existefichero(char *nombre)
{
    FILE *entrada;
    entrada=fopen(nombre,"r");
    if (entrada==NULL) return(0);
    fclose(entrada);
    return(1);
}

static int dametipofichero(char *tipofichero)
{
	if (strcmp(tipofichero,"XML")==0) return (TIPOFICHEROXML);
	return(TIPOFICHEROPLANO);
}

static int fabreficheronombre(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10];
	int tagdefecto=0,xmlcompacto=0,xmlindent=0;
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];
	char nfich[MAXPATH],tipofichero[MAXPATH]="PLANO",taginicial[MAXPATH]="";

    carganombreinterfase(b,tipointerfase,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    dameparametro(b,ft,0,V10CADENA,directorio);
    dameparametro(b,ft,1,V10CADENA,nombrec);
    dameparametro(b,ft,2,V10CADENA,nfich);
	if (ft->nparam>3) {
		dameparametro(b,ft,3,V10CADENA,tipofichero);
		dameparametro(b,ft,4,V10CADENA,taginicial);
		dameparametro(b,ft,5,V10INT,&tagdefecto);
		dameparametro(b,ft,6,V10INT,&xmlcompacto);
		dameparametro(b,ft,7,V10INT,&xmlindent);
	} 
	if (!*nfich) {
        v10log(LOGERROR,"%s","Debe indicar nombre de fichero\n");
        return(-1);
	}
	else { 
		sprintf(nombredef,"%s\\%s%s%s",directorio,nfich,strchr(vdcab.extfichero,'.')?"":".",vdcab.extfichero);		
	}
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
		finter=NULL;
	} else {
	  finter=abrefichero(directorio,nfich,vdcab.extfichero,"w",dametipofichero(tipofichero));
	}
    sprintf(handle, "%s=%lf", nombrec, (double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
	strcpy(finter->taginicial,taginicial);
	finter->tagdefecto=tagdefecto;
	finter->xmlcompacto=xmlcompacto;
	finter->xmlindent=xmlindent;
    return(0);
}

static int fabreficheronombreinter(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10];
	int tagdefecto=0,xmlcompacto=0,xmlindent=0;
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];
	char nfich[MAXPATH],tipofichero[MAXPATH]="PLANO",taginicial[MAXPATH]="";

    dameparametro(b, ft, 0, V10CADENA, directorio);
    dameparametro(b, ft, 1, V10CADENA, nombrec);
    dameparametro(b, ft, 2, V10CADENA, nfich);
    dameparametro(b, ft, 3, V10CADENA, tipointerfase);
    dameparametro(b, ft, 4, V10CADENA, formato);
    //carganombreinterfase(b,tipointerfase,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
	if (ft->nparam>5) {
		dameparametro(b,ft,5,V10CADENA,tipofichero);
		dameparametro(b,ft,6,V10CADENA,taginicial);
		dameparametro(b,ft,7,V10INT,&tagdefecto);
		dameparametro(b,ft,8,V10INT,&xmlcompacto);
		dameparametro(b,ft,9,V10INT,&xmlindent);
	} 
	if (!*nfich) {
        v10log(LOGERROR,"%s","Debe indicar nombre de fichero\n");
        return(-1);
	}
	else { 
		sprintf(nombredef,"%s\\%s%s%s",directorio,nfich,strchr(vdcab.extfichero,'.')?"":".",vdcab.extfichero);		
	}
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
		finter=NULL;
	} else {
	  finter=abrefichero(directorio,nfich,vdcab.extfichero,"w",dametipofichero(tipofichero));
	}
    sprintf(handle, "%s=%lf", nombrec, (double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
	strcpy(finter->taginicial,taginicial);
	finter->tagdefecto=tagdefecto;
	finter->xmlcompacto=xmlcompacto;
	finter->xmlindent=xmlindent;
    return(0);
}

static int fabreficherostd(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10],tipofichero[MAXPATH]="PLANO",taginicial[MAXPATH]="";
	int tagdefecto=0,xmlcompacto=0,xmlindent=0;
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];

    carganombreinterfase(b,tipointerfase,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    dameparametro(b,ft,0,V10CADENA,directorio);
    dameparametro(b,ft,1,V10CADENA,nombrec);
	if (ft->nparam>2) {
		dameparametro(b,ft,2,V10CADENA,tipofichero);
		dameparametro(b,ft,3,V10CADENA,taginicial);
		dameparametro(b,ft,4,V10INT,&tagdefecto);
		dameparametro(b,ft,5,V10INT,&xmlcompacto);
		dameparametro(b,ft,6,V10INT,&xmlindent);
	} 
	damenombrefichero(directorio,&vdcab,nombredef);
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
        return(-1);
    }
	finter=abrefichero(directorio,vdcab.preffichero,vdcab.extfichero,"w",dametipofichero(tipofichero));
	sprintf(handle, "%s=%lf", nombrec, (double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
	strcpy(finter->taginicial,taginicial);
	finter->tagdefecto=tagdefecto;
	finter->xmlcompacto=xmlcompacto;
	finter->xmlindent=xmlindent;
    return(0);
}

static int fabreficherointer(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10],tipofichero[MAXPATH]="PLANO",taginicial[MAXPATH]="";
	int tagdefecto=0,xmlcompacto=0,xmlindent;
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];
    dameparametro(b,ft,0,V10CADENA,tipointerfase);
    dameparametro(b,ft,1,V10CADENA,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    dameparametro(b,ft,2,V10CADENA,directorio);
    dameparametro(b,ft,3,V10CADENA,nombrec);
	if (ft->nparam>4) {
		dameparametro(b,ft,4,V10CADENA,tipofichero);
		dameparametro(b,ft,5,V10CADENA,taginicial);
		dameparametro(b,ft,6,V10INT,&tagdefecto);
		dameparametro(b,ft,7,V10INT,&xmlcompacto);
		dameparametro(b,ft,8,V10INT,&xmlindent);
	} 
    damenombrefichero(directorio,&vdcab,nombredef);
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
        return(-1);
    }
    finter=abrefichero(directorio,vdcab.preffichero,vdcab.extfichero,"w",dametipofichero(tipofichero));
    sprintf(handle,"%s=%lf",nombrec,(double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
	strcpy(finter->taginicial,taginicial);
	finter->tagdefecto=tagdefecto;
	finter->xmlcompacto=xmlcompacto;
	finter->xmlindent=xmlindent;
    return(0);
}

static int fabreficherostdexcel(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10];
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];
    carganombreinterfase(b,tipointerfase,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    dameparametro(b,ft,0,V10CADENA,directorio);
    dameparametro(b,ft,1,V10CADENA,nombrec);
    damenombrefichero(directorio,&vdcab,nombredef);
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
        return(-1);
    }
    finter=abreficheroexcel(directorio,vdcab.preffichero,vdcab.extfichero);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
    generatituloexcel(b,finter);
    sprintf(handle, "%s=%lf", nombrec, (double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    return(0);
}

static int fabreficherointerexcel(bloques *b,ftrigers *ft)
{
    char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    char directorio[MAXPATH],
         nombrec[MAXNOMBREV10];
    char handle[MAXMSGV10];
    fichinterfases *finter;
    vdinterfasecabs vdcab;
    char nombredef[MAXPATH];
    dameparametro(b,ft,0,V10CADENA,tipointerfase);
    dameparametro(b,ft,1,V10CADENA,formato);
    INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    dameparametro(b,ft,2,V10CADENA,directorio);
    dameparametro(b,ft,3,V10CADENA,nombrec);
    damenombrefichero(directorio,&vdcab,nombredef);
    if (existefichero(nombredef)) {
        v10log(LOGERROR,"Fichero %s ya existe\n",nombredef);
        return(-1);
    }
    finter=abreficheroexcel(directorio,vdcab.preffichero,vdcab.extfichero);
    sprintf(handle,"%s=%lf",nombrec,(double)(size_t)finter);
    asignavariables(b,handle);
    if (finter==NULL) return(-1);
    strcpy(finter->tipointerfase,tipointerfase);
    strcpy(finter->formato,formato);
    return(0);
}

static int appendfichero(char *origen,char *destino)
{
    FILE *salida,*entrada;
    char buffer[MAXCADENA];
    int ret, lon;
    salida = fopen(destino, "ab");
    entrada = fopen(origen, "rb");
    if (entrada != NULL) {
        while ((ret = (int)fread(buffer, 1, sizeof(buffer), entrada)) != 0) {
            fwrite(buffer, ret, 1, salida);
        }
        fclose(entrada);
    }
    fseek(salida,0,SEEK_END);
    lon=ftell(salida);
    fclose(salida);
    return(lon);
}

static int llcommitfichero(fichinterfases *finter)
{
    char nombretrans[MAXPATH],nombretotal[MAXPATH];
    if (finter->transac==0) return(0);
    if (finter->tipofichero==TIPOFICHEROPLANO || finter->tipofichero==TIPOFICHEROXML) {
        fclose(finter->salida);
        sprintf(nombretotal,"%s\\%s.TMP",finter->directorio,finter->nombre);
        sprintf(nombretrans,"%s\\%s.TRC",finter->directorio,finter->nombre);
        finter->tamano=appendfichero(nombretrans,nombretotal);
        finter->salida=fopen(nombretrans,"w");
    } else {
        finter->lincommit=finter->linactual;
    }
    return(0);
}

static int llrollbackfichero(fichinterfases *finter)
{
    char nombretrans[MAXPATH];
    if (finter->transac==0) return(0);
    if (finter->tipofichero==TIPOFICHEROPLANO || finter->tipofichero==TIPOFICHEROXML) {
        fclose(finter->salida);
        sprintf(nombretrans,"%s\\%s.TRC",finter->directorio,finter->nombre);
        finter->salida=fopen(nombretrans,"w");
    } else {
        IDispatch *rango;
        rango=damerangoexcel(finter->hoja,0,finter->lincommit+1,100,finter->linactual+1);
        invocametodo(rango,"Clear",NULL,-1);
        finter->linactual=finter->lincommit;
        liberaidispatch(rango);
    }
    return(0);
}

static int fcommitfichero(bloques *b,ftrigers *ft)
{
    fichinterfases *finter;
    int ret;
    char nombrec[MAXCADENA];
    int param;
    for (param=0;param<ft->nparam;param++) {
        dameparametro(b,ft,param,V10CADENA,nombrec);
        finter=(fichinterfases *)(long long)atof(nombrec);
        if (finter) {
            ret=llcommitfichero(finter);
        } else {
            v10log(LOGERROR,"No existe fichero %s\n",nombrec);
			ret = -1;
        }
    }
    return(ret);
}

static int frollbackfichero(bloques *b,ftrigers *ft)
{
    fichinterfases *finter;
    int ret;
    char nombrec[MAXCADENA];
    dameparametro(b,ft,0,V10CADENA,nombrec);
    finter=(fichinterfases *)(long long)atof(nombrec);
    ret=llrollbackfichero(finter);
    return(ret);
}

static int fcierrafichero(bloques *b,ftrigers *ft)
{
	char tamano[MAXPATH]="";
    char nombrec[MAXCADENA];
    char nombretrans[MAXPATH],nombreback[MAXPATH],nombretotal[MAXPATH],nombredef[MAXPATH]="";
    fichinterfases *finter;
    int ret;
    vdinterfasecabs vdcab;
    int error,param;
    for (param=0;param<ft->nparam;param++) {
        dameparametro(b,ft,param,V10CADENA,nombrec);
        finter = (fichinterfases *)(long long)atof(nombrec);
		piece(nombrec,tamano,"$",2);
		if (finter==NULL) return(-1);
		error=*(int *)direcncampo(b,ERRORINTER);
		if (finter->tipofichero==TIPOFICHEROXML && finter->linactual>0 && !es_blanco(finter->taginicial)) {
			fprintf(finter->salida,"</%s>\n",finter->taginicial);
		}
        if (error==0) llcommitfichero(finter);
        else          llrollbackfichero(finter);
        if (finter->tipofichero==TIPOFICHEROPLANO || finter->tipofichero==TIPOFICHEROXML) {
           fclose(finter->salida);
		   finter->abierto = 0;
           sprintf(nombretrans,"%s\\%s.TRC",finter->directorio,finter->nombre);
           unlink(nombretrans);
        } else {
            char destino[MAXPATH];
            sprintf(destino,"%s\\%s.TMP",finter->directorio,finter->nombre);
            salvaexcel(finter->wb,destino);
            Invoke(finter->app, "Quit", NULL, DISPATCH_METHOD, 0);
            finter->tamano=finter->lincommit;
            finole();
        }
        sprintf(nombretotal,"%s\\%s.TMP",finter->directorio,finter->nombre);
        if (finter->tamano || *tamano!=0) {
            if (!es_blanco(finter->tipointerfase)) {
				memset(&vdcab, 0, sizeof(vdcab));
				ret = INTCselvdinterfasecab(finter->tipointerfase, finter->formato, &vdcab);
                if (error==0) {
                   damenombrefichero(finter->directorio,&vdcab,nombredef);
                   if (!*nombredef) 
                       sprintf(nombredef,"%s\\%s%s%s",finter->directorio,finter->nombre,*finter->ext?(strchr(finter->ext,'.')?"":"."):"",finter->ext);
				   sprintf(nombreback,"%s\\BAK\\%s%ld.%s",finter->directorio,finter->nombre,vdcab.secuencial,finter->ext);
                   CopyFile(nombretotal,nombreback,0);
                   unlink(nombredef);
                   MoveFile(nombretotal,nombredef);
                   vdcab.secuencial++;
                   INTCactualizasecuencial(&vdcab,0);
                   commit();
                } else {
                    rollback();
                    sprintf(nombreback,"%s\\ERR\\%s%ld.%s",finter->directorio,finter->nombre,vdcab.secuencial,finter->ext);
                    MoveFile(nombretotal,nombreback);
                }
            }
        } else {
            DeleteFile(nombretotal);
        }
        free(finter);
    }
    return(0);
}

static int escribefichero(bloques *b,fichinterfases *finter,char *tipointerfase,char *formato,int xmlcompacto,int tagdefecto,int concr)
{
    int ret;
    char *salida=direcncampo(b,SALIDAINTER);
    if (finter==NULL) return(-1);
	switch (finter->tipofichero) {
		case TIPOFICHEROPLANO: ret=generalineainter(b,tipointerfase,formato,salida);
                               if (concr) fprintf(finter->salida,"%s\n",salida);
							   else fprintf(finter->salida, "%s", salida);
							   break;
		case TIPOFICHEROEXCEL: ret=generalineaexcel(b,tipointerfase,formato,finter);
			                   break;
		case TIPOFICHEROXML:   ret=generalineaxml(b,tipointerfase,formato,finter,xmlcompacto,tagdefecto);
			                   break;
    }
    v10log(LOGDEBUG,"Salida: %s\n",salida);
    return(ret);
}

static int fescribefichero(bloques *b,ftrigers *ft)
{
    int ret;
    char nombrec[MAXCADENA];
	int xmlcompacto,tagdefecto;
    fichinterfases *finter;
    dameparametro(b,ft,0,V10CADENA,nombrec);
    finter = (fichinterfases *)(long long)atof(nombrec);
    if (finter==NULL) return(-1);
	if (ft->nparam>1) {
        dameparametro(b,ft,1,V10INT,&xmlcompacto);
		if (ft->nparam>2) {
			dameparametro(b,ft,2,V10INT,&tagdefecto);
		} else {
			tagdefecto=finter->tagdefecto;
		}
	} else {
		xmlcompacto=finter->xmlcompacto;
		tagdefecto=finter->tagdefecto;
	}
	ret=escribefichero(b,finter,finter->tipointerfase,finter->formato,xmlcompacto,tagdefecto,1);
	return(ret);
}


static int fdecxml(bloques *b,ftrigers *ft)
{
    char nombrec[MAXCADENA];
    fichinterfases *finter;
    dameparametro(b,ft,0,V10CADENA,nombrec);
    finter = (fichinterfases *)(long long)atof(nombrec);
    finter->nivelxml--;
    return(0);
}


static int fcierraxml(bloques *b,ftrigers *ft)
{
    fichinterfases *finter;
	char formato[LFORMATO];
    char nombrec[MAXCADENA];
    dameparametro(b,ft,0,V10CADENA,nombrec);
    finter = (fichinterfases *)(long long)atof(nombrec);
    if (finter==NULL) return(-1);
	if (ft->nparam>1) {
		dameparametro(b,ft,1,V10CADENA,formato);
	} else {
		strcpy(formato,finter->formato);
	}
	finter->nivelxml--;
	fprintxmlnivel(finter,"</%s>\n",formato);
	finter->nivelxml++;
    return(0);
}

static int fescribeficherointer(bloques *b,ftrigers *ft)
{
    int ret;
	int concr=1;
    char nombrec[MAXCADENA],tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
    fichinterfases *finter;
	int xmlcompacto,tagdefecto;
    dameparametro(b,ft,0,V10CADENA,nombrec);
    dameparametro(b,ft,1,V10CADENA,tipointerfase);
    dameparametro(b,ft,2,V10CADENA,formato);
	if (ft->nparam>3) dameparametro(b, ft, 3, V10INT, &concr);
    finter = (fichinterfases *)(long long)atof(nombrec);
    if (finter==NULL) return(-1);
	if (ft->nparam>3) {
        dameparametro(b,ft,3,V10INT,&xmlcompacto);
		if (ft->nparam>4) {
			dameparametro(b,ft,4,V10INT,&tagdefecto);
		} else {
			tagdefecto=finter->tagdefecto;
		}
	} else {
		xmlcompacto=finter->xmlcompacto;
		tagdefecto=finter->tagdefecto;
	}
	ret=escribefichero(b,finter,tipointerfase,formato,xmlcompacto,tagdefecto,concr);
	return(ret);
}


int fcreafichero(bloques *b,ftrigers *ft)
{
    char nombre[MAXPATH];
    FILE *salida;
    dameparametro(b,ft,0,V10CADENA,nombre);
    salida=fopen(nombre,"w");
    if (salida==NULL) {
        v10log(LOGERROR,"No puedo abrir fichero %s\n",nombre);
        return(-1);
    }
    fclose(salida);
    return(0);
}

static int fdamenombreficherointer(bloques *b,ftrigers *ft)
{
    char *nombre;
    char nombrec[MAXCADENA];
    char nombrefichero[MAXCADENA];
	char tipointerfase[LTIPOINTERFASE],formato[LFORMATO];
	vdinterfasecabs vdcab;
    dameparametro(b,ft,0,V10CADENA,nombrec);
    dameparametro(b,ft,1,V10CADENA,nombrefichero);
    carganombreinterfase(b,tipointerfase,formato);
	nombre=existecampo(b,nombrefichero);
	if (nombre==NULL) return(-1);
	INTCselvdinterfasecab(tipointerfase,formato,&vdcab);
    damenombrefichero("",&vdcab,nombrefichero);
    strcpy(nombre,nombrefichero+1);
    return(0);
}


int fborrafichero(bloques *b,ftrigers *ft)
{
    char nombre[MAXPATH];
    int ret;
    dameparametro(b,ft,0,V10CADENA,nombre);
    ret=unlink(nombre);
    return(ret);
}

int fmuevefichero(bloques *b,ftrigers *ft)
{
    char nombre[MAXPATH],destino[MAXPATH];
    int ret;
    dameparametro(b,ft,0,V10CADENA,nombre);
    dameparametro(b,ft,0,V10CADENA,destino);
    ret=MoveFile(nombre,destino);
    return(ret);
}



void inittrigerinter(void)
{
	declaratriger("FDAMENOMBREFICHEROINTER",fdamenombreficherointer,NULL);
	declaratriger("FABREFICHERONOMBRE",fabreficheronombre,NULL);
	declaratriger("FABREFICHERONOMBREINTER",fabreficheronombreinter,NULL);
    declaratriger("FABREFICHEROSTD",fabreficherostd,NULL);
    declaratriger("FABREFICHEROINTER",fabreficherointer,NULL);
    declaratriger("FABREFICHEROSTDEXCEL",fabreficherostdexcel,NULL);
    declaratriger("FGENERALINEAINTER",fgeneralineainter,NULL);
    declaratriger("FESCRIBEFICHERO",fescribefichero,NULL);
    declaratriger("FDECXML",fdecxml,NULL);
    declaratriger("FESCRIBEFICHEROINTER",fescribeficherointer,NULL);
    declaratriger("FCIERRAXML",fcierraxml,NULL);
    declaratriger("FCIERRAFICHERO",fcierrafichero,NULL);
    declaratriger("FCOMMITFICHERO",fcommitfichero,NULL);
    declaratriger("FROLLBACKFICHERO",frollbackfichero,NULL);
    declaratriger("FCREAFICHERO",fcreafichero,NULL);
    declaratriger("FBORRAFICHERO",fborrafichero,NULL);
    declaratriger("FMUEVEFICHERO",fborrafichero,NULL);
}