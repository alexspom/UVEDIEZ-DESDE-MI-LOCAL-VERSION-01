/*
* M�dulo :  v10httprespuestas.c
* Objeto:   Env�o de respuestas al cliente mediante protocolo http
* 
* 
* Autor	 : Francisco Jos� Guerrero S�nchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"

typedef struct TIPOFICHERO {
	char extension[MAXPATH];
	int tipo;
} tipoficheros;

tipoficheros tfich[]={{".HTML",HTTPHTML},
{".HTM",HTTPHTML},
{".JPG",HTTPIMAGENES},
{".GIF",HTTPIMAGENES},
{".BMP",HTTPIMAGENES},
{".PNG",HTTPPNGS},
{".JS", HTTPJAVASCRIPT},
{".CSS",HTTPCSS},
{".XLS",HTTPEXCEL},
{".CSV",HTTPEXCEL},
{".XLSX",HTTPEXCELX},
{ ".PDF", HTTPPDF },
{ ".HTC", HTTPHTC },
{ ".WAV", HTTPSOUND } };

char mensajenofound[MAXCADENA]="<HTML>\n<HEAD>\n<title>ERROR</title>\n</HEAD>\n<body>\n%s\n</body>\n</HTML>";

#define PATRONIMAGENES "../img"
#define PATRONHTML "../html"

static int dametipofichero(char *fichero)
{
	char *ext;
	int i;

	if (!fichero) return(HTTPHTML);
	ext=strchr(fichero,'.');
	if (!ext) return(HTTPHTML);
    for (i=0;i<sizeof(tfich)/sizeof(tfich[0]);i++) {
		if (!strcmp(tfich[i].extension,strmay(ext))) {
			return(tfich[i].tipo);
		}	
    }
		return(-1);
}


static int lee_fichero(char *fichero,char **cadena)
{
	FILE *entrada;
    char nombrecompleto[MAXPATH];
	v10horas ini;
	long lon;
	ini=damecent();
	entrada=fopenpath(fichero,"rb");
	v10log(LOGNORMAL,"Tiempo en abrir %lf seg.\n",(damecent()-ini)/100);
	if (!entrada) {
		v10log(LOGERROR,"El fichero %s solicitado no existe\n",fichero);
		return(0);
	}
    damenombrecompleto(fichero,nombrecompleto);
    v10log(LOGNORMAL,"Fichero a enviar %s\n",nombrecompleto);
	fseek(entrada,0,SEEK_END);
	lon=ftell(entrada);
	*cadena=calloc(1,lon+1);
	fseek(entrada,0,SEEK_SET);
	fread(*cadena,1,lon,entrada);
	fclose(entrada);
	v10log(LOGNORMAL,"Tiempo en carga de fichero %lf seg.\n",(damecent()-ini)/100);
	return(lon);

}

static void	v10write2file(char *fichero,char *respuesta,unsigned long lon,int comprimir) 
{
	FILE *temp;
    char *ext = comprimir ? "zip" : "html";
	char ficherozip[MAXPATH]="";
	if (!stricmp(v10httpconf.rutazip,"NULO")) return;
	if (fichero) {
		sprintf(ficherozip,"%s//%s.%s",v10httpconf.rutazip,fichero,ext);
	}
	else 	sprintf(ficherozip,"%s//temp.%s",v10httpconf.rutazip,ext);
	temp=fopen(ficherozip,"wb");
	if (temp) {
		fwrite(respuesta,1,lon,temp);
		fclose(temp);
	}
}

static void comandoHTTP(int comando,char *respuesta,char *url,char *accesoAJAX) 
{
	switch (comando) {
		case OK:	
			strcat(respuesta,"HTTP/1.1 200 OK\r\n");		
			break;

		case NOT_FOUND:
			strcat(respuesta,"HTTP/1.1 404 Not Found\r\n");
			break;

		case SEE_OTHER:
			strcat(respuesta,"HTTP/1.1 303 See Other\r\n");
			strcat(respuesta,"Retry-After: 5 \r\n");
            if (es_blanco(v10httpconf.prefijoservicio)) {
                sprintf(url, "%s:%d/%s", v10httpconf.v10servidor, v10httpconf.v10puertov10form, v10httpconf.rutainicial);
            } else {
                sprintf(url, "%s/%s%d/%s", v10httpconf.v10servidor, v10httpconf.prefijoservicio,v10httpconf.v10puertov10form % 1000, v10httpconf.rutainicial);
            }
            break;

		case SEE_OTHER_AJAX:
			strcat(respuesta,"HTTP/1.1 303 See Other\r\n");
			strcat(respuesta,"Retry-After: 5 \r\n");
			sprintf(url,"%s:%s/%s",v10httpconf.v10serverAJAX,v10httpconf.v10puertoAJAX,accesoAJAX);
			break;


		case RELOAD:
            strcat(respuesta, "HTTP/1.1 303 See Other\r\n");
            if (es_blanco(v10httpconf.prefijoservicio)) {
                sprintf(url, "%s:%s/%s&HOST=%s&", v10httpconf.v10servidor, v10httpconf.v10puertoservidor, v10httpconf.acceso, v10httpconf.hostname);
            } else { 
                sprintf(url, "%s/%s/&HOST=%s&", v10httpconf.v10servidor, v10httpconf.acceso, v10httpconf.hostname); 
            }
			break;		

		case NOT_MODIFIED:
			strcat(respuesta,"HTTP/1.1 304 Not Modified\r\n");
			break;
	}

}

static void tipoficheroHTTP(int tipo,char *fichero,char *respuesta) {

    switch (tipo) {
        case HTTPEXCEL:
        case HTTPPDF:
            strcat(respuesta, "Content-Type:application/x-pointplus\r\n");
            break;
        case HTTPJAVASCRIPT:
            strcat(respuesta, "Content-Type:application/x-javascript\r\n");
            break;
        case HTTPHTC:
            strcat(respuesta, "Content-Type:text/x-component\r\n");
            break;
        case HTTPCSS:
            strcat(respuesta, "Content-Type:text/css\r\n");
            break;
        case HTTPHTML:
        case HTTPHELP:
            strcat(respuesta, "Content-Type:text/html; charset=ISO-8859-1\r\n");
            break;
        case HTTPIMAGENES: {
                           char *ch;
                           ch = strchr(fichero, '.');
                           if (ch) sprintf(respuesta + strlen(respuesta), "Content-Type:image/%s\r\n", ch + 1);
                           else strcat(respuesta, "Content-Type:image\r\n");
                           break;
         }
        case HTTPSOUND: {
            strcat(respuesta, "Content-Type:audio/wav\r\n");
            break;
			   }
		case HTTPPNGS: {
			strcat(respuesta,"Content-Type: image/png\r\n");
					   }
	}
}



static void conexionHTTP(int tipofichero,char *respuesta,int conexabierta) {

	switch (tipofichero) {			
		case HTTPJAVASCRIPT:
        case HTTPPDF:
        case HTTPIMAGENES:
        case HTTPSOUND:
		case HTTPPNGS:
		case HTTPCSS:	
		case HTTPEXCEL:	
		case HTTPHTC:
			strcat(respuesta,"Connection: close\r\n");
			//strcat(respuesta,"Connection:Keep-Alive\r\n");	
			break;
		case HTTPHTML:
			if (conexabierta) strcat(respuesta,"Connection: Keep-Alive\r\n");
			else strcat(respuesta,"Connection: close\r\n");
			break;	
		case HTTPHELP:	
			strcat(respuesta,"Connection: Keep-Alive\r\n");
			break;
	}
}


static void cacheHTTP(int tipofichero,char *respuesta,char *fichero,int lon) {

	switch (tipofichero) {
		case HTTPHTML:
			strcat(respuesta,"Cache-Control: no-store");		
			break;
			/*strcat(respuesta,"Cache-Control: no-cache");		
			break;		*/
		case HTTPEXCEL:			
		case HTTPCSS:			
		case HTTPPDF:	
			strcat(respuesta,"Cache-Control: public, max-age: 999999999\r\n");
			strcat(respuesta,"Last-Modified: Tue, 11 Nov 2008 14:44:07 GMT\r\n");
			sprintf(respuesta+strlen(respuesta),"ETag: \"%s%d\"",fichero,lon);
			/*strcat(respuesta,"Expires: Mon, 13 May 2019 20:14:49 GMT\r\n");
			strcat(respuesta,"Last-Modified: Tue, 11 Nov 14:44:07 GMT");*/
			break;
		case HTTPJAVASCRIPT:
		case HTTPHTC:
		case HTTPHELP:		
        case HTTPIMAGENES:
        case HTTPSOUND:
		case HTTPPNGS:
			strcat(respuesta,"Cache-Control: public, max-age: 999999999\r\n");
			strcat(respuesta,"Last-Modified: Tue, 11 Nov 2008 14:44:07 GMT\r\n");
			sprintf(respuesta+strlen(respuesta),"ETag: \"%s%d\"",fichero,lon);
			/*strcat(respuesta,"Expires: Mon, 13 May 2019 20:14:49 GMT\r\n");
			strcat(respuesta,"Last-Modified: Tue, 11 Nov 14:44:07 GMT");*/
			break;

	}
}

extern CRITICAL_SECTION v10servercritical;

void httpenviarespuesta(int comando,char *fichero,int tipofichero,v10sockssls *v10server,char *datos,int lon,int comprimir,int conexabierta,char *accesoAJAX) 
{

	char *respuesta;
	int i;
	int lonhead,lontotal;	
	char url[MAXPATH]="";
	respuesta=calloc(1,MAXCADENA*4+lon+1);
	//v10log(LOGNORMAL, "INICIO la respuesta a socket %p\n", v10server);
	comandoHTTP(comando,respuesta,url,accesoAJAX);
	tipoficheroHTTP(tipofichero,fichero,respuesta);	
	if (*url)	sprintf(respuesta+strlen(respuesta),"Location:%s\r\n",url);	
	if (comprimir) strcat(respuesta,"Content-Encoding: gzip\r\n");
	sprintf(respuesta+strlen(respuesta),"Content-Length: %d\r\n",lon);	
	conexionHTTP(tipofichero,respuesta,conexabierta);
	cacheHTTP(tipofichero,respuesta,fichero,lon);
	strcat(respuesta,"\r\n\r\n");
	lonhead=strlen(respuesta);
	memcpy(respuesta+lonhead,datos,lon);
	lontotal=lonhead+lon;
	//v10log(LOGNORMAL, "ANTES DE CRITICO la respuesta a socket %p\n", v10server);
	initcritical();
	EnterCriticalSection(&v10servercritical);  
	//v10log(LOGNORMAL, "ENTRADO EN CRITICO la respuesta a socket %p\n", v10server);
	if (v10server->v10sock->status!=STSOCKREADY) {
		LeaveCriticalSection(&v10servercritical);  
		v10log(LOGNORMAL, "%s", "Respuesta no envida por socket roto\n");
		free(respuesta);
		return;
	}
	i=0;
	//v10log(LOGNORMAL, "INICIO ESCRITURA a socket %p\n", v10server);
	while (i<lontotal) {
		if (lontotal-i<20000) v10socksslescribe(v10server,respuesta+i,lontotal-i);
		else v10socksslescribe(v10server,respuesta+i,20000);
		i+=20000;
	}
	//v10log(LOGNORMAL, "FIN ESCRITURA a socket %p\n", v10server);
	v10write2file(fichero,datos,lon,comprimir);
	//v10log(LOGNORMAL, "FIN FICHERO la respuesta a socket %p\n", v10server);
	LeaveCriticalSection(&v10servercritical); 
	//	v10log(LOGNORMAL,"Envio %s %ld caracteres\n", respuesta, lontotal); 
	if (fichero) v10log(LOGNORMAL,"Fichero %s enviado\n",fichero);
    else         v10log(LOGNORMAL,"Enviada la respuesta a socket %p\n",v10server);
	free(respuesta);

}

int v10httprespuesta(int comando,v10sockssls *v10server,char *fichero,char *paramdatos,char *accesoAJAX,int soloheader) 
{
	char *datos=NULL,*midatos=NULL,*inicio;
	int lon=0,conexabierta=0;
	int comprimir=0;	
	char v10cadenazip[MAXCADENAHTML]="";
	int tipofichero=dametipofichero(fichero);
	if (fichero && !strcmp(fichero,"/HTML/")) {
		httpenviarespuesta(OK,fichero,0,v10server,midatos,lon,0,0,accesoAJAX);		
		Sleep(10);
		return(-1);
	}
	if (tipofichero!=HTTPIMAGENES && tipofichero!=HTTPPDF && tipofichero!=HTTPPNGS && tipofichero!=HTTPEXCEL && v10httpconf.comprimir) comprimir=1;
	// si hay datos ficho prevalecen
	if (paramdatos) {
		conexabierta=1;
		datos=strdup(paramdatos);
		lon=strlen(datos);
    } else {
		if (fichero!=NULL && comando!=NOT_FOUND && soloheader==0) {
			lon=lee_fichero(trim(fichero),&datos);
		}
    }
	if (comando==NOT_FOUND && fichero) {
		comando=OK;
		datos=calloc(1,MAXCADENA);
		sprintf(datos,mensajenofound,fichero);
		lon=strlen(datos);
	}
	// comprime los datos
	if (!datos) comprimir=0;
	else { // sustituye ../html y ../img por los servidores configurados
		if ((strcmp(v10httpconf.v10serverimg,"NULL") || strcmp(v10httpconf.v10serverhtml,"NULL")) 
			&& (strstr(datos,PATRONIMAGENES) || strstr(datos,PATRONHTML))) {
			char datosaux[MAXCADENAHTML]="";
            memset(datosaux, 0, sizeof(datosaux));
			memcpy(datosaux,datos,lon);		
		//	v10log(LOGNORMAL, "reemplazo de imagenes inicio\n", lon / 1024.0);
			while ((inicio=strstr(datosaux,PATRONIMAGENES))) 
				v10reemplazapatron(datosaux, PATRONIMAGENES, v10httpconf.v10serverimg, 1);
			//v10log(LOGNORMAL, "reemplazo de imagenes fin\n", lon / 1024.0);
			while ((inicio=strstr(datosaux,PATRONHTML))) 
				v10reemplazapatron(datosaux, PATRONHTML, v10httpconf.v10serverhtml, 1);
			//v10log(LOGNORMAL, "reemplazo de html fin\n", lon / 1024.0);
			free(datos);
			datos=strdup(datosaux);
			lon=strlen(datos);
		}
	}
	midatos=datos;	
	if (comprimir && lon<1024*1024) {
		memset(v10cadenazip,0,sizeof(v10cadenazip));
		lon = v10compress(midatos, lon, v10cadenazip);
		v10log(LOGNORMAL, "Compresion fin\n", lon / 1024.0);
		midatos=v10cadenazip;			
	}
	v10log(LOGNORMAL,"Envio un total de %.2lf KB\n",lon/1024.0);
#ifndef __LINUX__
	__try {//RIK
#endif
		httpenviarespuesta(comando,fichero,tipofichero,v10server,midatos,lon,comprimir,conexabierta,accesoAJAX);
#ifndef __LINUX__
	} __except(EXCEPTION_EXECUTE_HANDLER) {return -1;};
#endif
	if (datos) free(datos);	
	return(0);
}


int funcdebug(int numsesion,v10sockssls *v10server,char *error)
{
	v10log(LOGERROR, "Error en peticion %s\n", error);
	if(!eslistener) return(0);
	if (v10httpconf.debughttp) {
		char *cad=NULL,*ptr,*ptr2;
		char respuesta[MAXCADENA]="";
        *respuesta = 0;
		lee_fichero("debughttp.html",&cad);
		cad=realloc(cad,strlen(cad)+strlen(error)+1);
		ptr=strstr(cad,"_v10mensaje_");
		ptr2=ptr+strlen("_v10mensaje_");
		strcopia(respuesta,cad,(int)(ptr-cad));
		strcat(respuesta,error);
		strcat(respuesta,ptr2);
		v10log(LOGNORMAL,"Sesion %d: Debug %s\n",numsesion,respuesta);		
		v10httprespuesta(OK,v10server,NULL,respuesta,NULL,0);
		free(cad);
	}
	s[numsesion].status=STFIN;	
	return(0);
}

int v10reiniciaform(char *cadena,int concepto) 
{
	return(v10httprespuesta(RELOAD,v10formserver,NULL,"",NULL,0));
}
