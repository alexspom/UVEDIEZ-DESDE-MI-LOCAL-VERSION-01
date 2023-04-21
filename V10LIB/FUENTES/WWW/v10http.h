#ifndef __v10http
#define __v10http
#define MAXV10FORMS 1000
#define MAXIDSESION			200
#define MAXPAGINAHTML		1024*100 // 100 KBytes

#define CACHE_EXPIRATION		"Expires: Tue, 23 Sep 2050 8:00:00 GMT\r\n"
				
#define MAXHTTPSESIONES			300

// Tipos de Navegador soportados
#define IEXPLORER		0

// Comandos del protoclo HTTP
#define OK					0
#define NOT_FOUND			1
#define SEE_OTHER			2
#define RELOAD				3
#define NOT_MODIFIED		4
#define UNAUTHORIZED		5
#define SEE_OTHER_AJAX		6

// Comando de HTTP
#define GET 0
#define POST 1

// estado del semáforo de eventos
#define SEMAFIDDLE 	0
#define SEMAFON1		1
#define SEMAFON2		2

// Tipo de los archivos a enviar
#define HTTPHTML				0
#define HTTPIMAGENES			1
#define HTTPJAVASCRIPT			2
#define HTTPCSS					3
#define HTTPEXCEL				4
#define HTTPEXCELX				4
#define HTTPPDF					5
#define HTTPHELP				6
#define HTTPPNGS				7
#define HTTPHTC					8
#define HTTPSOUND				9



// Estado de las conexiones de los clientes
#define STIDDLE			0 
#define STWAITING		1
#define STCONNECTED     2 // ACTIVO
#define STRUNNING		3
#define STPIPEFORM 	3
#define STFIN			  4


typedef struct { // configuración del servidor HTTP 
	int  releeconfig;
	char acceso[MAXPATH];			// cadena de acceso con la aplicación
	char idsesion[MAXIDSESION];		// identificador de la sesión abierta con el browser
	int nivellog;	
	int protegido;
	int debughttp;					// se muestran mensajes de error al cliente www
	int visibleexe;
	char v10servidor[MAXPATH];		// host en el que se encuentra lanzado el servidor HTTP
    char prefijoservicio[MAXPATH];
	char v10puertoservidor[6];	  	// puerto del host donde espera el servidor principal (Listener) HTTP
	char v10puertomisc[6];	  		// puerto del host donde espera el servidor principal HTTP de imágenes,ficheros js, etc...
	char v10puertoinicial[6];		// puerto de inicial a partir de cual se utilizan para las conexiones
	int  v10puertov10form;			// puerto que se va asignando a cada form que se arranca
	char  _v10puertov10form[6];
	char v10serverhtml[MAXPATH];	// servidor de ficheros html, js y css
	char v10serverimg[MAXPATH];		// servidor de ficheros de imágenes
    char v10serverxls[MAXPATH];		// servidor de ficheros Excel
	char v10serverpdf[MAXPATH];		// servidor de ficheros PDF
	char ficheroexe[MAXPATH];
	char conexionBD[MAXPATH];
	char hostname[32];				// nombre del host del cliente
	int  version_browser;			// versión browser se da la ejecución por finalizada
	int  fileexpired;				// cada cuando expira los ficheros css,js, htmls,.... enviados
	int  autorefresh;				// tiempo en minutos de refresco de a página si no se recibe evento
	int  tiempoespera;				// espera máxima de un evento o una conexion, tras la cual se cierra la conexión
	char rutainicial[MAXPATH];		// ruta con la que debe conectarse al listener
	char libreriaV10[MAXPATH];		// nombre de la libreria v10 que debe de enviar
	char libreriamenuV10[MAXPATH];		// nombre de la libreria del menu v10 que debe de enviar
	char ficheromenujs[MAXPATH];		// fichero incluido en la libreriamenuV10
	int	 versiondistribuida;        // si es una versión distribuida, o local en la máquina
	char rutazip[MAXPATH];			// ruta en la que se guarda el fichero zip copia de lo que se ha enviado
	char rutaplantillas[MAXPATH*10];// ruta donde se encuentran las plantillas de MENUS, FRMs y PANs.
	char rutaxls[MAXPATH];			// ruta donde se generan ficheros xls
	char rutapdf[MAXPATH];			// ruta donde se generan ficheros xls
	char rutahelp[MAXPATH];			// ruta donde se encuentran los ficheros de ayuda
	/* parámetros para arrancar directamente los forms logeado y con un menú pasado */
	char usuario[MAXPATH];			
	char password[MAXPATH];
	char menu[MAXPATH];
	/* configuración para el SSL */
    int ssl;
    char sslkeyfile[MAXPATH];
    char sslcertfile[MAXPATH];
	char sslpassword[MAXPATH];
	char dhfile[MAXPATH];
	char ca_list[MAXPATH];
	char extra[MAXCADENA];
	int tecladovirtual;
	char prefijoplantilla[MAXPATH];
	char v10serverAJAX[MAXPATH];
	char v10puertoAJAX[MAXPATH];
	char AJAXsidebarFRM[MAXPATH*4];
	int  AJAXsidebarFRMvisible;	
	char AJAXsidebarMENU[MAXPATH*4];
	int  AJAXsidebarMENUvisible;
	int comprimir;
} v10httpconfigs;


typedef struct HTTPSESIONES {
	v10sockssls *v10server;
	int status;
	v10horas ultrecepcion;
	//char hostname[LNOMBREORDENADOR];					
	char puerto[MAXPATH];
	char peticion[MAXCADENA],buffer[MAXCADENA];
	int leidos;
	char extraparam[MAXCADENA];
	char hostname[32];				// nombre del host del cliente	
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE tid;
} v10httpsesiones;


typedef struct {
    bloques *b;
	char sesion[MAXPATH];
	char objeto[MAXPATH];
	char evento[MAXPATH];
	char valor[MAXPATH];
	char antid[MAXPATH];
	char antvalor[MAXCADENA];
    v10sockssls *sock;
} v10httpeventos;

extern int eslistener;
V10WWWIMPORT v10httpconfigs v10httpconf;
extern v10httpsesiones s[MAXHTTPSESIONES]; // sesiones en v10listener

// v10httpconfig.c
V10WWWIMPORT void v10configurahttp(char *fichero);

// v10httpeticiones.c
int recibecaracteres(v10sockssls *v10server, char *peticion,char *buffer, int *leidos);
int tratapeticion(int numsesion, v10sockssls *v10server, char *peticion, char *extradata);

// v10httpget.c
int atiendeGET(int numsesion,v10sockssls *v10server, char *peticion, int eslistener,int soloheader);

// v10httpListener.c
void capturahostname(int numsesion, char *peticion);
void creav10form(int numsesion);
void matahebra(int numsesion);
V10WWWIMPORT int v10runlistener(char *ficheroconf);
V10WWWIMPORT int v10runserverfiles(char *param_ficheroconf);

// v10httppost.c
void atiendePOST(int numsesion, v10sockssls *v10server, char *peticion, char *extradata, int eslistener);

// v10httprespuestas.c
int v10httprespuesta(int comando,v10sockssls *v10server,char *fichero,char *paramdatos,char *accesoAJAX,int soloheader);
int funcdebug(int numsesion,v10sockssls *v10server,char *error);
int v10reiniciaform(char *cadena,int concepto);


// v10httpservidor.c
V10WWWIMPORT int v10wwwdameSW();
int v10esperaevento(virtsels *v,v10sockssls **s,v10httpeventos *_v10ev);
V10WWWIMPORT int trataparamweb(char *cadena);
V10WWWIMPORT void v10runserverhttp(void);
void initcritical(void);

// v10wwwforcon.c
int v10damecon(int port);
void v10liberacon(int i);

extern v10sockssls *v10formserver; // servidor ssl del form
int atiendeGetAJAX(int numsesion,v10sockssls *v10server, char *peticion);
int trataajax(v10dialogs *v,v10httpeventos *ev);

#endif