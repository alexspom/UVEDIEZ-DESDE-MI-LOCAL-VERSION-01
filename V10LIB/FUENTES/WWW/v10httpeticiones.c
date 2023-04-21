/*
* Módulo :  v10httppeticiones.c
* Objeto:   Recibe y atiende peticiones http del cliente
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"

#define TIMEOUT 300

static int damelon(char *buffer)
{
    char *ptr;
    ptr=strstr(buffer,"Content-Length:");
    if (ptr) {
        return(atoi(ptr+15));
    }
    return(0);
}

static char *memstr(char *haystack, char *needle, int size)
{
	char *p;
	char needlesize = (char)strlen(needle);

	for (p = haystack; p <= (haystack-needlesize+size); p++)
	{
		if (memcmp(p, needle, needlesize) == 0)
			return p; /* found */
	}
	return NULL;
}

static int cargatrozo(v10sockssls *v10server,char *donde,int lon)
{
  int ret=0;
  v10horas ultrec;
  ultrec=damecent();
  while (ret==0) {
      ret=v10socksslread(v10server,donde,16384);
      if (damecent()-ultrec>TIMEOUT) return 0;
  }
  donde[ret]=0;
  return(ret);
}

static char *tratacampo(char *cadena,v10sockssls *v10server,int *leidos,char *boundary,char *campo,char *fichero,char *accion)
{
    char *inicio,*fin,*nombre,*ret=NULL,*path="c:\\PROYECTOS\\ALCURA\\V10LIB\\WWW\\FORMULARIO\\";
    FILE *salida;
    int quedan,lboundary,enviado=0;
    lboundary=(long)strlen(boundary);
    inicio=strchr(cadena+lboundary,'\n');
    if (inicio==NULL) {
        return(NULL);
    }
    fin=strchr(inicio+1,'\n');
    if (fin) *fin=0;
    nombre=strstr(inicio,"filename=");
    if (nombre && !es_blanco(nombre)) {
        char sinpath[MAXPATH],conpath[MAXPATH],*envpath;
        int i;
        envpath=getenv("UPLOADHTML");
        if (envpath) path=envpath;
        fin=strchr(nombre,'\n');
        nombre+=10;
        if (fin) *fin=0;
        fin=nombre;
        while (*fin) {
            if (*fin=='"') *fin=0;
            fin++;
        }
        i=numpieces(nombre,"\\");
        piece(nombre,sinpath,"\\",i);
        v10log(LOGNORMAL,"Nombre del fichero %s boundary %s lboundary %d\n",nombre,boundary,lboundary);
        strcpy(fichero,sinpath);
        inicio=nombre+strlen(nombre)+3;
        inicio=strchr(inicio,'\n');
        inicio+=3;
        sprintf(conpath,"%s%s",path,sinpath);
        quedan=*leidos-(int)(inicio-cadena);
        salida=fopen(conpath,"wb");
        if (salida==NULL) {
            v10log(LOGERROR,"No puedo abrir fichero %s\n",conpath);
            //return NULL;
        }
        fin=inicio;
        while ((ret=memstr(fin,boundary,quedan))==NULL) {
            int ret;
            char *poserr;
            if (salida) fwrite(inicio,quedan-lboundary,1,salida);
            if ((poserr=memchr(inicio,0,quedan))!=NULL) {
                v10log(LOGNORMAL,"Te pille enviado total %ld poserr %d lboundary %d\n",enviado,poserr-inicio,lboundary);
            }
            enviado+=quedan-lboundary;
            memmove(inicio,inicio+quedan-lboundary,lboundary);
            fin=inicio;
            ret=cargatrozo(v10server,inicio+lboundary,16384);
            v10log(LOGNORMAL,"Escrito %d recibido %d total %d\n",quedan-lboundary,ret,enviado);
            quedan=lboundary;
            quedan+=ret;
            if (ret==0) return NULL;
        }
        if (salida) fwrite(inicio,ret-inicio-4,1,salida);
        enviado+=(int)(ret-inicio)-4;
        v10log(LOGNORMAL,"Escrito %d total %d\n",ret-inicio-4,enviado);
        if (salida) fclose(salida);
        if (salida==NULL) strcpy(accion,"9999");

    } else {
        if (fin) {
            ret=strstr(fin+1,boundary);
            if (ret) *leidos-=(int)(ret-cadena);
            nombre=strstr(inicio,"name=\"campo\"");
            if (nombre) {
               nombre+=5;
               strcopia(campo,fin+3,(int)(ret-fin)-7);
            }
            nombre=strstr(inicio,"name=\"accion\"");
            if (nombre) {
               nombre+=5;
               strcopia(accion,fin+3,(int)(ret-fin)-7);
            }
        } else {
            ret=NULL;
        }
    }
   return(ret);
}

static void tratamultipart(char *peticion,v10sockssls *v10server,int *leidos,int lon)
{
    char boundary[MAXPATH],*ptr,*fin;
    v10log(LOGNORMAL,"Recibida multipart longitud %d %200.200s\n",*leidos,peticion);
    if ((ptr=strstr(peticion,"boundary="))) {
       fin=strchr(ptr,'\n');
       if (fin) *fin=0;
       fin=strchr(ptr,'\r');
       if (fin) *fin=0;
       strcpy(boundary,ptr+9);
       v10log(LOGNORMAL,"Boundary=%s\n",boundary);
       ptr=memstr(fin+1,boundary,*leidos);
       if (ptr) *leidos=*leidos-(int)(ptr-peticion);
       while (ptr==NULL) { 
           *leidos=cargatrozo(v10server,fin,16384);
           if (*leidos==0) return;
           ptr=memstr(fin,boundary,*leidos);
           if (ptr) {
               *leidos=*leidos-(int)(ptr-fin);
           }
       }
       if (ptr) {
           char campo[MAXPATH]="",fichero[MAXPATH]="",accion[MAXPATH]="3000";
           while (ptr) {
                  ptr=tratacampo(ptr,v10server,leidos,boundary,campo,fichero,accion);
           }
           if (!es_blanco(campo)) {
               bloques *b;
               fcampos *fc;
               v10httpeventos ev;
               strcpy(ev.objeto,campo);
               b=v10evdamebloque(&ev);
               if (b==NULL) {
                   b=v10damebloqueactual();
                   a2bcampo(b,campo,fichero);
               } else {
                   fc=v10evdamecampo(b,&ev);
                   a2bcampo(b,fc->nombre,fichero);
               }
               v10evtecla(traducetecla(accion));
           }
       }
    }
}

int recibecaracteres(v10sockssls *v10server, char *peticion,char *buffer, int *leidos)
{
	char temporal[MAXCADENA]="";
	char *ptr;	
	int peticioncompleta=0,lon;
	while (v10socksslhaycar(v10server)) {		
		*leidos+=v10socksslread(v10server,buffer+*leidos,16384);
		*(buffer+*leidos)=0;
        if (strstr(buffer,"\r\n\r\n")) break;
	}
	if ((ptr=strstr(buffer,"\r\n\r\n"))!=NULL) { // fin de peticion
        lon=damelon(buffer);
        if (strstr(buffer,"Content-Type: multipart/form-data")) {
            tratamultipart(buffer, v10server, leidos, lon);
            v10log(LOGNORMAL, "Recibecaracteres: Server cambia de valor de %p a %p\n", v10formserver, v10server);
            v10formserver=v10server;
//            v10evencola("bl0f1c1","keyup","27","bl0f1c1","");
            //httpenviarespuesta(OK,NULL,0,v10server,respuesta,strlen(respuesta),0,0,NULL);
            *leidos=0;
            return(0);
        }
		ptr+=4;
        if (lon==0) lon=(long)strlen(ptr);
        if (strlen(ptr)==lon) {
            peticioncompleta=1;
            strcopia(peticion,buffer,(int)(ptr-buffer));
            *temporal = 0;
            strcopia(temporal,ptr,(int)((buffer+strlen(buffer))-ptr));
            *leidos=(int)strlen(temporal);
            *buffer = 0;
            strcopia(buffer,temporal,*leidos);
            *leidos=0;
            v10log(LOGNORMAL,"Conexion %p recibe petición\n%s",v10server,peticion);
        }
	} else 
		v10log(LOGNORMAL,"Datos raros en Conexion %ld %s\n",*leidos, buffer);
	return(peticioncompleta);
}

static int dameversionbrowser(char *peticion) 
{
	char *cadbrowser=strstr(peticion,"User-Agent:");
	if (!cadbrowser) return(0);
	if (strstr(cadbrowser,"User-Agent: Mozilla")) return(0);
	if (strstr(cadbrowser,"User-Agent: Mozilla")) { 
		if (strstr(cadbrowser,"Opera")) return(-1);
		return(-1);
	}
	if (strstr(cadbrowser,"Netscape")) return(-1);
	if (strstr(cadbrowser,"MSIE")) {
		if (strstr(cadbrowser,"Windows CE")) return(-1);
		else return(IEXPLORER);
	}	
	return(0);
}

int tratapeticion(int numsesion, v10sockssls *v10server, char *peticion, char *extradata) 
{
	int comando;
    char getajax[MAXPATH];
	comando=-1;
    if (strncmp(peticion,"OPTIONS",7)==0 || strncmp(peticion,"PROPFIND",8)==0) {
        atiendeGET(numsesion,v10server, peticion,  eslistener,1);
        return(0);
    }
    if (strncmp(peticion,"HEAD",4)==0) {
        httpenviarespuesta(OK,NULL,0,v10server,NULL,0,0,0,NULL); 
        return(-1);
    }
	if (strncmp(peticion,"GET",3)==0) comando=GET;
	if (strncmp(peticion,"POST",4)==0) comando=POST;
    sprintf(getajax, "GET %s/ajax", es_blanco(v10httpconf.prefijoservicio)?"":"/");
    if (strstr(peticion, getajax)) return(atiendeGetAJAX(numsesion, v10server, peticion));
    v10log(LOGNORMAL, "Tratapeticion: Server cambia de valor de %p a %p\n", v10formserver, v10server);
    v10formserver = v10server;
	if (eslistener && comando!=GET) return(funcdebug(numsesion,v10server,"No se ha recibido comando HTTP GET"));
	if (comando!=POST && comando!=GET) return(funcdebug(numsesion,v10server,"No se ha recibido comando HTTP GET o POST"));
	if (eslistener) capturahostname(numsesion, peticion);
	if (dameversionbrowser(peticion)!=IEXPLORER) return(funcdebug(numsesion,v10server,"Versión de Navegador no soportada"));
	if (comando==GET) return(atiendeGET(numsesion,v10server, peticion,  eslistener,0));
	if (comando==POST) atiendePOST(numsesion,v10server, peticion, extradata, eslistener);
	return(0);
}			