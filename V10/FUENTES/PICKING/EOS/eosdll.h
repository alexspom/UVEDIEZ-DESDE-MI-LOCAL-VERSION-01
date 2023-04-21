#include "eosconst.h"

#ifdef _EOSDLL
  #define EOSIMPORT __declspec( dllexport )
#else
#ifdef _EOSUSADLL
  #define EOSIMPORT __declspec(dllimport)
#else
  #define EOSIMPORT extern 
#endif 
#endif

#define LDIRIP  16

//Indica si los comandos se pasan al ethernet-box en numero de serie o numero de display
// Un numero de display viene en la forma XXYYZZZ
// donde XX es el numero de la ethernex-box
//       YY es la linea dentro de la ethernet-box
//       ZZZ es el numero de display dentro de la linea 
#define TIPOIDNUMDISP 0
#define TIPOIDSERIE   1

#define MAXTECLAS     200

#define CAUSAOPER     1
#define CAUSAREPEAT   2

//Tipos de autonumeracion
#define AUTONONUMERA  0
#define AUTONUMDISP   1
#define AUTONUMSERIE  2


typedef struct  LWSOCKETS lwsockets;
typedef struct TIPODISPS tipodisps;

typedef struct ETHERBOXS etherboxs;

//Estructura de una linea de un ethernet-box
typedef struct ETHLINEAS {
                  int           port;               // Puerto de la linea
                  int           numdisp;            // Numero de displays de la linea
                  int           initlinea;          // Indicador de si la linea ya ha sido inicializada
                  v10sockets     *v10s;               // Socket con el que nos comunicamos con la linea
                  struct ETHERBOXS  *eth;        // Puntero a la estructura ethernet-box que contiene la linea
                  unsigned long tramasida,       // Estadisticas de la linea
                                tramasvuelta,
                                bytesida,
                                bytesvuelta,
                                bucles,
                                reconexiones,
                                creatramas,
                                lonida,
                                errtrama,
                                consumo,
                                consumo232;
                  char          stglob,stcon;
                  v10horas      hultstat;
                  unsigned long version;              // Version del programa de comunicacion con los displays de la linea
                  int           autonumera;           // Reservado
                  int           ciclotrabajo[MAXLUCESDISPLAY];  //Ciclo de trabajo de cada luz de los displays de la linea
                  unsigned long limitacionlinea;          // Limitacion en micro-A a 23 V
                  unsigned long tciclo;                   // Tiempo de ciclo de la linea
                  unsigned long tenvtrama;                // Tiempo entre tramas que la linea envia a los displays
                  unsigned long timeouttrama;             // Timeout al recibir trama
                  unsigned long timeoutwho;               // Timeout al recdibir un who de los displays
                  char          velocidad;		  //Velocidad de la cadena dentro del display
                  int           velmodificado;		  //Modificada la velocidad del display
                } ethlineas;

//Estructura de un ethernet-box
typedef struct ETHERBOXS {
                char          dirip[LDIRIP];       // Direccion IP
                ethlineas     lin[MAXLINEAS];      // Array de lineas del ethernet-box
                unsigned long version;             // Minima version de los programas que ejecutan las lineas
                int           autonumera;          // Reservado
              } etherboxs;

// Estructura de un display
typedef struct {
                unsigned long      serie;       // numero de serie
                unsigned long      version;     // Version del firmware
                unsigned long      errhard;     // NUmero de errores hardware detectados
                unsigned long      errtrama;    // Numero de errores de trama detectados
                unsigned long      consumo;     // consumo en micro-A a 23 V
                long               numdisp;              // Numero del display
                int                tipo;                 // Tipo de display 0 PL0D 4 PL4D 6 PL6D 16 PL16D
                tipodisps          *ptipo;               // Reservado
                char               valor[MAXDIGDISPLAY]; // Valor de los digitos representados actualmente en display
                unsigned short     luces[MAXLUCESDISPLAY]; //Valor de las luces del display
                char               status[MAXSTATUSDISPLAY]; //Estado de los botones del display
                int                modificado; // MOdificado el valor desde el PC
                int                modifstatus;  // Modificado el estatus
             } displays;

// Estructura de las teclas devueltas por el display
typedef struct {
                long      numdisp;   //Numero de display
                long      serie;     //Numero de serie del display
                long      version;   //Version del firmware
                int       boton;     // Boton pulsado
                int       causa;     //Siempre CAUSAOPER
              } tecladisps;


EOSIMPORT etherboxs eth[MAXETHER];  //Array de ethernet box
EOSIMPORT int modotest;             //1 los displays se ponen en modo test 0 Normal
//extern EOSIMPORT int maxnivellog;
EOSIMPORT int TSTATLINEA;
EOSIMPORT int tipoidentdisp;


//Funciones definidas en INFOPCDISP.C
//Funciones de bajo nivel para tratamiento de displays
EOSIMPORT displays *damedisplayid(int tipoid,long iddisplay);
EOSIMPORT displays *damedisplay(long iddisplay);
EOSIMPORT int vdisplayprintfp(displays *p,char *format,va_list arg);
EOSIMPORT int displayprintfp(displays *p,char *format,...);
EOSIMPORT int vdisplayprintfid(int tipoid,long iddisplay,char *format,va_list arg);
EOSIMPORT int displayprintfid(int tipoid,long iddisplay,char *format,...);
EOSIMPORT void lucesdisplayp(displays *p,int numluz,int valor);
EOSIMPORT void lucesdisplayid(int tipoid,long iddisplay,int numluz,int valor);
EOSIMPORT void togglelucesdisplayp(displays *p,int numluz);
EOSIMPORT void togglelucesdisplayid(int tipoid,long iddisplay,int numluz);
EOSIMPORT int statusdisplayp(displays *p);
EOSIMPORT int statusdisplayid(int tipoid,long iddisplay);
EOSIMPORT void encolatecladispp(displays *p,int boton,int causa);
EOSIMPORT void encolatecladispid(int tipoid,long iddisplay,int boton,int causa);
// Devuelve el numero de teclas que se han pulsado en los displays y estan esperando para ser tratadas.
EOSIMPORT int haytecladisp(void);
// Devuelve una estructura con la siguiente tecla pulsada.
EOSIMPORT int tecladisp(tecladisps *tec);

//Funciones definidas en INFO4HL.C
//Inicializa el sistema
//   Tciclo el tiempo deseado de ciclo del ethernet-box (Normalmente 1)
//   Tenvtrama centesimas de segundo entre tramas (Normalmente 5)
//   Timeout trama tiempo en centesimas de segundo para considerar timeourt (Normalmente 200)
//   Limitacion linea microamperios a 23 V maximos que da la linea.
//   Tarj1 ... Direciones IP de los ethernet-box TERMINADOS EN NULL                                                       
EOSIMPORT int initinfopickex(int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *tarj1,...);
EOSIMPORT int initinfopick(char *tarj1,...);
//Devuelve el numero de displays colgados de una ethernet-box
EOSIMPORT int numdispeth(etherboxs *peth);
//Devuelve el numero de displays total en la instalacion
EOSIMPORT int numdisp(void);
//Funcion que hay que llamar periodicamente (Cada 1-2 centesimas de segundo) para tratar los mensajes de las ethernet-box
EOSIMPORT void tickhleth(void);
//Imprime en un display en formato printf utilizando un va_list
EOSIMPORT int vdisplayprintf(long iddisplay,char *format,va_list arg);
//Imprime en un display como si fuera un printf
EOSIMPORT int displayprintf(long iddisplay,char *format,...);
// Cambia el valor de una luz de un display valor puede ser 0 apagado 1 Parpadeo 2 Flash
EOSIMPORT void lucesdisplay(long iddisplay,int numluz,int valor);
// Cambia el estado de una luz de un display Si estaba encendida la apaga y si estaba apagada la enciende
EOSIMPORT void togglelucesdisplay(long iddisplay,int numluz);
// Devuelve el estado de un display Cada bit del nibble inferior representa un boton.
EOSIMPORT int statusdisplay(long iddisplay);
// Hace que el sistema crea que un display ha pulsado una tecla
EOSIMPORT void encolatecladisp(long iddisplay,int boton,int causa);


