#include "vd.h"
#define COMCORR       0X20
#define HARDOK        0X10
#define HARDRESET     0X40  // códigos de error en el estado de los displays

#define MAXDIGDISPLAY 21	// lóngitud máxima de dígitos en un display
#define MAXLUCESDISPLAY 4

#define BYTESPORDISP  2		// número de bytes devueltos por display
#define TIPOSDISP     5		// númmero de tipos de displays distintos

//codigos de comandos del protocolo HOST<->RABBIT para cada línea de displays
#define START			1   // inicia envío de tramas a los displays
#define CSTOP			2   // detiene envío de tramas a los displays
#define LONG_BUFFER		3   // nº de bytes a enviar a los displays
#define MOD_DISP		4   // actualzia datos del buffer de envío desde op1 con longitud op2
#define DAM_EST			5   // solicita datos del buffer de recepción desde op1 con longitud op2
#define RESP_DISP		6   // recibe datos en el buffer de recepción desde op1 con longitud op2 	 
#define RESET			7   // resetea la línea de displays
#define STATS			8   // solicita estadísticas
#define RESP_STATS		9   // recibe estadísticas
#define CWHO			10  // envía tramas de who a los displays
#define CONF			11  // establece configuración de la tarjeta Rabbit
#define RESET_STATS		12	// resetea las estadísticas 
#define RESET_ERROR		13  // resetea los errores encontrados hasta el momento
#define ERROR_MSG		14  // indica una trama perdida en la línea de displays
#define PARPADEO		15

#define MAXREDESTARJ    12
#define INFOTMAXTECLAS	40  // número máximo de pulsaciones consecutivas de botones en los displays a tratar
#define MAXELEMRED	600	// máximo número de displays por líneas 600 RCM2100

#define INFOTBPULSANDO   1	// automata para la detección de pulsación de botones
#define INFOTBPULSADO    2
#define INFOTBSOLTANDO   3
#define INFOTBNOPULSADO  0
#define INFOCPRIMERA     0
#define INFOCREPEAT      1

#define TIPOIDNUMDISP    1

#define MAX_BUFFER_ENV 2000 // capacidad en bytes del buffer de envío
#define MAX_BUFFER_REC 602  // capacidad en bytes del buffer de recepción 602 RCM2100

#pragma pack(push)		// Estructuras que se intercambian con la tarjeta Rabbit
#pragma pack(1)
typedef struct {		// Estructura para la configuración de las líneas de displays
	unsigned long reset_miliseconds_1;	// tiempo de reseteo de la línea de displays
	unsigned long reset_miliseconds_2;	// tiempo de establecimiento después del reseteo de las líneas de displays
	short delay_car;					// retardo en el envío entre carateres
	short delay_cab;					// retardo en el envío entre cabeceras
} configurations;

typedef struct { // Estructura para recoger las estadísticas de cada línea de displays
	unsigned long sent_frames;		// tramas enviadas a la línea de displays
	unsigned long received_frames;	// tramas recibidas de la línea de displays
	short nbover;					// número de overruns producidos
	byte error;						// se ha perdido alguna trama
	byte pending;					// número de tramas pendienet de ser recibidas
} serial_stats;
#pragma pack(pop)


typedef char* IPsv4; // dirección IPv4
typedef struct {
         int    maxerror; // Cada cuantos errores seguidos de comunicacion se debe resetear la red
         int    delaycab; // Delay entre cabeceras
         int    delaycar; // Delay entre caracteres
         int    hardcheck;// Si se debe hacer chequeo hardware cuando se haga who
         v10horas  tpulsa;   // Tiempo que ha de estar pulsado un boton para considerarse pulsado
         v10horas  tsuelta;  // Tiempo que ha de estar no pulsado un boton para considerarse no pulsado
         v10horas  prepeat;  // Tiempo que ha de estar pulsado un boton para primer autorepeat
         v10horas  srepeat;  // Tiempo que ha de estar pulsado un boton para siguientes autorepeat
         v10horas  tparpade; // Tiempo de parpadeo encendido
         v10horas  tparpada; // Tiempo de parpadeo apagado
         long      espera;   // Tiempo de espera del thread de infopick en ms.
         v10horas  uparpad;  // Hora del ultimo parpadeo		 
         int	espwho;	  // espera en el who	
		 int	espreset; // espera en el reseteo de las líneas
		 int    espreset1;// Sleep en reset alto
         int    espreset2;// Sleep antes de start
         int    fichwho;  // El who se lee de un fichero
         int    ratioerr; // intervalo de tiempo para controlar si el nº de errores ha superado el máximo
		 int	statsgap; // intervalo de tiempo para el envío de estadísticas
         int    acelera;  // si acelera incremento/decremento en los displays si se mantiene el botón pulsado
		 int	showstats; // muestra estadísticas recibidas de cada red de displays
         long	quantum;   // tiempo que permanece recepcionando una línea
		 int	queue;	  // Cola máxima tcpip antes de enviarla	
		 int	queue_timeout;	  // Tiempo máximo tcpip antes de enviarla	
		 long	watchdog;	  // Tiempo si comunicación tras el cual recupera conexión
		 IPsv4	tarj[15]; // dirección IP de hasta 15 tarjetas Rabbit
		 IPsv4	services[15]; // dirección IP de hasta 15 tarjetas Rabbit
		 long   puertos[15];
		 char infopick[15]; // nombre del fichero infopick
         int releeconf;     // Tiempo entre lecturas de configuracion
		 int tipodir; //0 Por numdisp 1 por rabit,linea,display
	} infotconfigs;	  // estructura para la configuración de la comunicación con los displays

typedef struct {
         char *nombre;
         int  digitosa;
         int  digitosn;
         int  botones;
         int  luces;
         int  bytes;
		 char  baile[MAXDIGDISPLAY];
      } infotdefdisps;

typedef struct INFOTREDDISPS;
typedef struct INFOTSIOS;

typedef struct {
        int   estado;	
        v10horas horaestado;	
        int   numrep;	
        v10horas hurepeat;
        v10horas sigrepeat;
     } infotbotones;	// tipos de botones disponibles en un display


typedef struct {
        char			valor[MAXDIGDISPLAY];// buffer a asignar al display
        infotdefdisps	*tipo;				 // puntero al tipo del display
        int				dirsal;				 // dirección en el buffer de salida que corresponde a los bytes de este display en la red
		int				dirent;				 // dirección en el buffer de entrada que corresponde a los bytes de este display en la red
        infotbotones	*bot;				 // puntero a los botones del display
        struct     INFOTREDDISPS *r;		 // información sobre la línea de dispositivos en la que se encuentra	
     } infotdisplays;	// displays físicos disponibles en la red					

typedef struct INFOTREDDISPS {		// red de displays conectados a un puero serie
        int				numdisp;	// número de displays en la red
        int          numdispreal;
		v10socks		*pipe;		// puerta de enlace para el envío de comandos para esa red de displays
		infotdisplays	*d;			// primer display en la red
        char			buffer_salida [MAX_BUFFER_ENV]; // buffer de envío a los displays
		char			buffer_entrada[MAX_BUFFER_REC]; // buffer de recepción de los displays
		int				long_buffer;					// número de bytes a enviar de los contenidos en el bufefr de envío
		struct			INFOTSIOS *t;// Toda la red de displays
		v10horas			hulterror;   // hora del último error producido   
		int				udisp;		 // último dispositivo en la red
        unsigned int	numerror;	 // número de errores desde el último reset en la red de displays		
        unsigned int	toterror;	 // número total de errores en la red
		serial_stats	stats;		 // estadísticas sobre la red
		long			ptr_tcpip;
		int				nbmsg_tcpip;
		v10horas        ultimo_tcpip;
		v10horas        stats_pend;
		char			buffer_tcpip[64*1024];
	} infotreddisps;


typedef struct {
        int   linea;	// línea de displays
        int   disp;		// número de display en la línea	
        int   boton;	// número de botón en el display
        int   causa;	// causa de su pulsación
	} infotteclas;

typedef struct INFOTSIOS {
        IPsv4         dir_IP;		// Dirección IP o nombre de host
        infotreddisps r[MAXREDESTARJ];	// redes de displays
		int numred;
        infotteclas   *tec;			// teclas pulsadas
        int           numteclas;	// número de teclas pulsadas
	} infotsios;	// Identifica una tarjeta Rabbit

#define MAXTARJ 15
typedef struct {
        infotsios *t[MAXTARJ];	// tarjetas Rabbit
        int       numcards;		// número de tarjetas Rabbit
        HANDLE    tid;			// manejador de hebras para atender al alto y bajo nivel
        int       ultdisp;		// último display disponible en infopick
        int       numdisp;		// número global de displays manejados 
		v10horas	  hultstats;	// hora de la últimas estadísticas solicitadas 	
	} infopicks; // Infopick
extern infopicks infopick;

extern infotconfigs   infotconfig;	// configuración de la comunicación con los displays
extern infotdefdisps infotdef[];	// tipo de displays existentes	
extern unsigned infotascii8[];
extern unsigned infotascii16[];
extern unsigned infotan16[];

/* Funciones definidas en INFOHARD.C */
void watchdog(infotreddisps *r);
void envia_tcpip(infotreddisps *r);
// Envía los mensajes de tcpip encolados para la red de displays
int  infohreceive(infotsios *t,infotreddisps *r,int red);
// Recibe y procesa un comando enviado desde la tarjeta
// Argumento 1: tarjeta con la que se comunica
// Argumento 2: red de displays dentro de la tarjeta
// Argumento 3: número de la red de displays
// Retorno: comando recibido
void infohsend(char command,infotreddisps *r, int op1, int op2,byte *buffer);
// Envía un comando a la tarjeta Rabbit
// Argumento 1: comando a enviar
// Argumento 2: red de displays a la que se envía
// Argumento 3: primer parámetro del comando enviado
// Argumento 4: segundo parámetro del comando enviado
// Argumento 5: tercer parámetro del comando enviado
void infohstart(infotreddisps *r);	
// Inicia el envío de tramas de datos a una línea de displays
// Argumento : línea de displays a enviar tramas
void infohstop(infotreddisps *r);		
// Detiene el envío de tramas a una red de displays
// Argumento : línea de displays a detener el envío de tramas
void infohwho(infotreddisps *r);	    
// Activa el envío de tramas de who a una red de displays	
// Argumento : línea de displays a enviar tramas who
void infohreset(infotreddisps *r);
// Resetea una red de displays
// Argumento : línea de displays a resetear
void infohlongbuffer(infotreddisps *r,int value_env,int value_rec);
// Establece la longitud de los buffer de envío y recepción de una red de displays;
// Argumento 1: red de displays tratada
// Argumento 2: longitud del buffer de envío en la red
// Argumento 3: longitud del buffer de recepción en la red
void infohlimpia(infotreddisps *r);		
// Limpia los buffers de una red de displays
// Argumento : línea de displays
void infohresetstats(infotreddisps *r);	
// Resetea las estadísticas de la red de displays
// Argumento : línea de displays
void infohreseterror(infotreddisps *r);	
// Resetea los errores de una red de displays
// Argumento : línea de displays
v10socks *abrecliente(char *dirip,char *servicio);
void recupera_conexion(infotreddisps *r);
// Chequea si la conexión con rabbit está preparada
// Argumentos: red de displays

/* Funciones definidas en INFODISP.C */

void infotgrabaconfig(infotsios *t); 
// Envía configuración a una tarjeta
// Argumento: tarjeta a enviar la configuración actual
infotsios *infotidentifica(int ninfo,IPsv4 IPv4,int redes,v10socks *pipe[],int *pdisp);
// Identifica e inicializa los displays de una tarjetas en infopick
// Argumento 1: número infopick
// Argumento 2: dirección IP de la tarjeta
// Argumento 3: pipes abiertos con las líneas de displays en la tarjeta
// Argumento 4:  número total de displays en infopick
// Retorno: la tarjeta inicializada
void infotlibera(infotsios *t);
// Libera una comunicación con una tarjeta
// Argumento: Tarjeta

// Recupera en los displays el valor que tiene en caso de reseteo del Rabbit
void infotinicializa(infotsios *t,int red,int disp);

// Envío de cadenas a un display
void infotimprime(infotsios *t,int red,int disp,char *cad);
void infotvprintf(infotsios *t,int red,int disp,char *format,va_list arg);
void infotprintf(infotsios *t,int red,int disp,char *format,...);

void infotponluz(infotsios *t,int red,int disp,int numluz,int valor);
// Establece el valor de una luz de un display
// Argumento 1: tarjeta donde se encuentra el display
// Argumento 2: nº de red en la tarjeta
// Argumento 3: nº de display en la red
// Argumento 4: º de luz en el display
// Argumento 5: valor a asignar a la luz
int  infotstluz(infotsios *t,int red,int disp,int numluz);
// Retorna el estado de una luz en un display
// Argumento 1: tarjeta donde se encuentra el display
// Argumento 2: nº de red en la tarjeta
// Argumento 3: nº de display en la red
// Argumento 4: º de luz en el display
// Retorno: valor de la luz
void infottoggleluz( infotsios *t,int red,int disp,int numluz,int valor,char *cadena,int parpadea);
// Hace una inversión del valor asignado a la luz de un display
// Argumento 1: tarjeta donde se encuentra el display
// Argumento 2: nº de red en la tarjeta
// Argumento 3: nº de display en la red
// Argumento 4: º de luz en el display
// Argumento 5: valor a asignar a la luz
// Argumento 6: cadena con el mensaje a enviar
char *infotvalor(infotsios *t,int red,int disp);
// Retorna el valor (cadena mostrada) actualmente de un display
// Argumento 1: tarjeta donde se encuentra el display
// Argumento 2: nº de red en la tarjeta
// Argumento 3: nº de display en la red
// Retorno: valor mostrado en el display
int valorentdisp(infotsios *t,int red,int disp);		
// Idem. al anterior
int	 infotstatus(int ntarj,int red,infotreddisps *r);	
// Retorna el estado en una línea de displays
// Argumento 1: nº de tarjeta
// Argumento 2: nº de red de displays
// Argumento 3: red de displays
// Retorno: estado de la red de displays (OR lógico del estado de los displays en la red)
int  infotstdisplay(infotsios *t,int red,int disp);
// Retorna estado de un display (primer byte)
// Argumento 1: tarjeta
// Argumento 2: nº de red de displays
// Argumento 3: nº de display en la red
// Retorno: estado de display
void infotencolatecla(infotsios *t,int red,int disp,int boton,int causa);
// Encola la pulsación de un botón en un display de la tarjeta
// Argumento 1: tarjeta
// Argumento 2: nº de red de displays
// Argumento 3: nº de display en la red
// Argumento 4: número de botón en el display
// Argumento 5: causa de la pulsación del botón
void infottratateclas(infotsios *t);
// Trata la pulsación de un botón en un display de la tarjeta
// Argumento 1: tarjeta
int  infothaytecla(infotsios *t);
// Comprueba si hay algún botón pulsado en los displays de la tarjeta
// Argumento 1: tarjeta
// Retorno: número de pulsaciones encoladas
int  infottecla(infotsios *t,infotteclas *donde);
// Recoge la siguiente tecla de las encoladas en una tarjeta, eliminándola
// Argumento 1: tarjeta
// Argumento 2: sgte.tecla pulsada
// retorno: 0 si no hay teclas encoladas, 1 si las ahy
void infotTCPIP(infotsios *t,infotreddisps *r,int red);
// Atiende mensajes procedentes de una red de displays
// Argumento 1: tarjeta
// Argumento 2: red de displays
// Argumento 3: nº de red de displays
void pintatarj(int tarj,infotreddisps *r,int red);
// Muestra información de cada red de displays en pantalla	
// Argumento 1: nº de tarjeta
// Argumento 2: de red de displays
// Argumento 1: nº de red de displays
int  buscatarj(infotsios *t);
// Devuelve el número de tarjeta				
// Argumento 1: tarjeta
// Retorno: nº de la tarjeta en infopick
void infotstart(infotsios *t);	
// Envío de tramas de datos en una tarjeta
// Argumento: tarjeta
void infotstop(infotsios *t);
// Detiene el envío de tramas en una tarjeta
// Argumento: tarjeta
void infotwho(infotsios *t);	
// Envío de tramas who en una tarjeta
// Argumento: tarjeta
void infotreset(infotsios *t);	
// Resetea las líneas de displays de una tarjeta	
// Argumento: tarjeta
void infotresetn(int max_tarjetas);	
// Resetea un número determinado de tarjetas en infopick
// Argumento: número de tarjetas a resetear
void infotlongbuffer(infotsios *t); 
// Establece la longitud de los buffers en una tarjeta	
// Argumento: tarjeta
void infotlimpia(infotsios *t);		
// Límpia buffers en las redes de displays de una tarjeta
// Argumento: tarjeta
void infotresetstats(infotsios *t);	
// Resetea estadísticas en una tarjeta	
// Argumento: tarjeta
void infotreseterror(infotsios *t);	
// Resetea errores en una tarjeta
// Argumento: tarjeta
void tratastats(infotsios *t,infotreddisps *r,int red);
// Trata las estadísticas sobre cada red de displays
// Argumento 1: tarjeta
// Argumento 2: red de displays
// Argumento 3: nº de red de displays

/* Funciones definidas en INFOPICK.C */

#define ERRNOINFO 1 // códigos de error del estado global de infopick
#define ERRLUZ    2
#define ERRBOTON  3
#define ERRTARJ   4

void infograbaconfig(void);
// Graba  configuracion hardware en la tarjeta
int datosdisp(int disp,int *tarjeta,int *linea,int *ndisp);
int damedirtipo(int numdisp);
void infowho(void);
// Pregunta a la red cuantos y qué displays hay (la llama infoinit)
void inforeset(void);
// Hace reset de todas las tarjetas
int  infostatus(void);

// Recupera valores actuales de los displays
void infoinicializa(void);

// Devuelve el status global del infopick 1 nibble parametros de configuracion 1 nible teclas
void infovprintf(int ndisp,char *format,va_list arg);
void infoprintf(int ndisp,char *format,...);
// Imprimen información en un display 
// Argumento 1: nº de display en infopick
void infoponluz(int disp,int numluz,int valor);
// Pone la luz numluz del display disp a valor siendo
// 0 apagado 1 encendido fijo 2 parpadeo
// Argumento 1: nº de display en infopick
// Argumento 2: nº de luz en el display
// Argumento 3: valor a signar a la luz
void infotoggleluz(int disp,int numluz,int valor);
// Identica a la anterior
int  infostluz(int disp,int numluz);
// Devuelve el estado de la luz numluz del display disp
// Argumento 1: nº de display en infopick
// Argumento 2: nº de luz en el display
int  infostdisplay(int disp);
// Devuelve el status de un display 1 nibble parametros de comunicacion
//   (HARDOK, COMMCORR)
// el nibble bajo el estado de los botones un bit por boton
// Argumento 1: nº del display en infopick
// Retorno: status del display
infotdisplays *infodisplay(int disp); 
// Obtiene un puntero a un display
// Argumento 1: nº del display en infopick
// Retorno: display encontrado
infotdefdisps *infotipo(int disp);
// Obtiene el tipo de un display	
// Argumento 1: nº del display en infopick
// Retorno: tipo encontrado
char *infovalor(int disp);
// Devuelve la cadena que está siendo mostrada en el display
// Argumento 1: nº del display en infopick
// Retorno: cadena mostrada
void infoencolatecla(int disp,int boton,int causa);
// Mete una tecla en la cola de teclas de los displays
// Argumento 1: nº del display en infopick
// Argumento 2; nº de botón en el display
// Argumento 3: causa de la pulsación de la tecla
int  infohaytecla(void);
// Devuelve si hay tecla: 0 no hay tecla !=0 si hay
int  infotecla(infotteclas *tec);
// Devuelve !=0 si hay tecla y carga la estructura tec
void infotratateclas(void);
// Atiende los botones pulsadas en los displays
int  infonumdisp(void);
// Devuelve el numero total de displays en el sistema
int  infonextboton(void); 
// Devuelve el nº de display con el siguiente botón pulsado
int infonexterror(void);
// Busca un display que devuevla un estado erróneo
void infoinit(int ninfo);
// Inicializa el sistema de displays y hebras

void infoinit3(int ninfo,...);

// infoconf.c
void leeconf(char *nombre);
