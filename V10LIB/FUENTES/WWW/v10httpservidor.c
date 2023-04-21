/*
* Módulo :  v10httpservidor.c
* Objeto:   Servidor http que corre dentro de v10form.exe
* 
* 
* Autor	 : Francisco José Guerrero Sánchez
* Fecha  : 25-09-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10wwwform.h"



static servidorsockssls *v10nuevoservidor=NULL;

CRITICAL_SECTION v10servercritical; // manejo de la sección crítica entre hebras
static int v10initserver=0;
static int finalizando=0;
static v10httpsesiones c[MAXHTTPSESIONES];

v10sockssls *v10formserver;


void initcritical(void)
{
	if (v10initserver) return;
	InitializeCriticalSection(&v10servercritical);
	v10initserver=1;
}



static void v10recibepeticion(int i)
{
	int ret;
	if (c[i].status>STIDDLE) { 
        if (c[i].v10server->v10sock->status == STSOCKROTA || c[i].v10server->v10sock->status == STSOCKSEMIROTA) {
            v10log(LOGNORMAL, "Sesion %d socket %p Finalizada por rotura de conexion %d\n", i, c[i].v10server,c[i].v10server->v10sock->status);
			v10sockssllibera(c[i].v10server);
			c[i].v10server=NULL;			
			c[i].status=STIDDLE;
			return;
		}
	}
	switch (c[i].status) {
	case STCONNECTED:
		c[i].ultrecepcion=damecent();
		c[i].status=STWAITING;
		c[i].leidos=0;
		memset(c[i].peticion,0,sizeof(c[i].peticion));
		memset(c[i].buffer,0,sizeof(c[i].buffer));
	case STWAITING:
		if (!v10socksslhaycar(c[i].v10server)) {}
		if (c[i].v10server->v10sock->status==STSOCKREADY && v10socksslhaycar(c[i].v10server)) {
            if (recibecaracteres(c[i].v10server, c[i].peticion, c[i].buffer, &(c[i].leidos))>0) {
                v10log(LOGNORMAL,"La conexion %d recibe peticion en socket %p\n",i,c[i].v10server);
				ret=tratapeticion(i, c[i].v10server, c[i].peticion, c[i].buffer);		
				if  (ret) {
                    v10sockssllibera(c[i].v10server);
                    v10log(LOGNORMAL, "Sesion %d socket %p AUTO-Finalizada por rotura de conexion\n", i, c[i].v10server->v10sock);
					c[i].v10server=NULL;			
					c[i].status=STIDDLE;
				}
            }
		}
	}
	return;
}

void v10finconexiones(void) 
{
	int i;
	finalizando=1;
	EnterCriticalSection(&v10servercritical);  
	for (i=0;i<MAXHTTPSESIONES;i++) {
		if (c[i].status) {
			if (c[i].v10server) v10sockssllibera(c[i].v10server);		
			c[i].status=STIDDLE;
			c[i].v10server=NULL;
		}
	}
	LeaveCriticalSection(&v10servercritical);
	v10liberacon( v10httpconf.v10puertov10form - atoi(v10httpconf.v10puertoinicial));
}

void v10trataservidores(char *param)
{
	int i;
	v10sockssls *v10server;
	do {
		Sleep(10);
		if (finalizando==1) break;
		v10server	= v10sockssldameconexion(v10nuevoservidor);
        if (v10server) {
            EnterCriticalSection(&v10servercritical);
            for (i = 0; i < MAXHTTPSESIONES; i++) {
                if (c[i].status == STIDDLE) {
                    memset(&c[i], 0, sizeof(v10httpsesiones));
                    v10log(LOGNORMAL, "Sesion %d Conectada socket %p\n", i, v10server);
                    c[i].v10server = v10server;
                    c[i].status = STCONNECTED;
                    break;
                }
            }
            LeaveCriticalSection(&v10servercritical);
		}
	} while (1);
}

void v10atiendeconexiones(char *param) 
{
	int i;
	do {
	   EnterCriticalSection(&v10servercritical); 
       for (i = 0; i<MAXHTTPSESIONES; i++) {
           if (c[i].status>STIDDLE) {
               v10recibepeticion(i);
           }
       }
       LeaveCriticalSection(&v10servercritical);
	   Sleep(1);
	} while(1);
}

static void dameparametrohttp(char *cadena, char *destino) 
{
	char *ptr;
	if ((ptr=strchr(cadena,' ')) || (ptr=strchr(cadena,'\0'))) {
			strcopia(destino,cadena,(int)(ptr-cadena));
	}
}

 int v10wwwdameSW() 
 {
	switch (v10httpconf.visibleexe) {
		case 1: return(SW_HIDE);
		case 2:	return(SW_SHOWMINIMIZED);	
		case 3: return(SW_SHOWMAXIMIZED);
	}
	return(SW_SHOWMINIMIZED);	
}

V10WWWIMPORT int trataparamweb(char *cadena)
{
	
	if (toupper(*cadena)=='F' && toupper(cadena[1])=='W') {
		v10versionweb=1;
		if (!memicmp(cadena+2,"FICHERO=",8)) {
			*ficheroconf=0;
			dameparametrohttp(cadena+2+8,ficheroconf);
			v10configurahttp(ficheroconf);
		}		
		if (!memicmp(cadena+2,"VISIBLE=",8)) {
			char visible[10]="";
			dameparametrohttp(cadena+2+8,visible);
			v10httpconf.visibleexe=atoi(visible);
		}
		if (!memicmp(cadena+2,"SESION=",7))
			dameparametrohttp(cadena+2+7,v10httpconf.idsesion);
		if (!memicmp(cadena+2,"PUERTO=",7)) {
			dameparametrohttp(cadena+2+7,v10httpconf._v10puertov10form);
			v10httpconf.v10puertov10form=atoi(v10httpconf._v10puertov10form);
		}
		if (!memicmp(cadena+2,"HOST=",5)){
			dameparametrohttp(cadena+2+5,v10httpconf.hostname);				
		}
		if (!memicmp(cadena+2,"TECLADO=1",9)) {
			v10httpconf.tecladovirtual=1;
		}
	}
  return(0);
}

#define TESPERA 6000


V10WWWIMPORT void v10runserverhttp(void)
{
	v10horas hconex;
	servidorsocks *servidorinicial=NULL;
	v10socks	  *v10servidorinicial=NULL;
	v10sockssls	  *v10server;	
	memset(c,0,MAXHTTPSESIONES*sizeof(v10httpsesiones));
	//SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS	); 
	v10log(LOGNORMAL,"Escuchando en el puerto %s\n",v10httpconf._v10puertov10form);
	// se establece conexión inicial
	servidorinicial=v10socknuevoservidor(v10httpconf._v10puertov10form,0,NULL,NULL,NULL,NULL,NULL);
	if (!servidorinicial) exit(0);
	do {
		v10servidorinicial=v10sockdameconexion(servidorinicial);
		hay_tecla();
		Sleep(1);
	} while (!v10servidorinicial);
	v10log(LOGNORMAL,"Conectado Listener en el puerto %s\n",v10httpconf._v10puertov10form);
	v10sockcierraservidor(servidorinicial);
	v10socklibera(v10servidorinicial);
    v10initssl(v10httpconf.ssl, v10httpconf.sslkeyfile, v10httpconf.sslcertfile, v10httpconf.sslpassword, v10httpconf.dhfile, v10httpconf.ca_list);
	hconex=damecent();
	v10log(LOGNORMAL,"Abriendo conexion HTTP en el puerto %s\n",v10httpconf._v10puertov10form);
	v10nuevoservidor=v10socksslnuevoservidor(v10httpconf._v10puertov10form,0,NULL,NULL,NULL,NULL,NULL);
	v10log(LOGNORMAL, "Abierta conexion HTTP en el puerto %s\n", v10httpconf._v10puertov10form);
	do {
		v10server	= v10sockssldameconexion(v10nuevoservidor);
		if (v10server) {
			c->v10server=	v10server;
			while (c->v10server->v10sock->status!=STSOCKREADY){
				Sleep(1); 
                if (damecent()-hconex>TESPERA) { // 20 segundos de espera máxima
	                v10log(LOGERROR, "%s", "Agotado el tiempo maximo de espera para que el socket este ready\n");
                    exit(0);
                }
			}  
			break;
        }
        if (damecent()-hconex>TESPERA)  { // 20 segundos de espera máxima
	        v10log(LOGERROR, "%s", "Agotado el segundo tiempo maximo de espera para que el socket este ready\n");
            exit(0);
        }
		Sleep(1);
	} while (1);

	v10log(LOGNORMAL, "%s", "Conexión de cliente establecida\n");
//	v10formserver=c->v10server;
	v10log(LOGNORMAL,"v10formserver vale %x\n",v10formserver);
	c->status=STCONNECTED;	
	initcritical(); 
	_beginthread(v10trataservidores,0,v10httpconf._v10puertov10form);
	_beginthread(v10atiendeconexiones,0,v10httpconf._v10puertov10form);
	atexit(v10finconexiones);	
}

