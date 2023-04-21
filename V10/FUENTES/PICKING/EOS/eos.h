/*
* Módulo : EOS.H
* Objeto: Include generico para los displays EOS
*
*
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-12-2007

* MODIFICACIONES
* --
*/

#ifndef EOS_H_
#define EOS_H_

#ifdef __WIN32__
#include "eoswin.h"
#else
#define v10log miescribelog
#endif
#ifdef __LINUX__
#include "eoslinux.h"
#endif
#ifdef __NETOS__
#include "eosnetos.h"
#endif

#include <fcntl.h>
#include <sys/types.h>

#include "eosconst.h"
#define escribe_log miescribelog


#define BAUDRATE     57600

#define LOGDEPURATRAMA 6

#define WHOPEND      0
#define WHOENV       1
#define WHOREC       2

#define MANDADOTEST  3

#define MANDADOCICLO 4

#define MANDADOPARO  5

#define MAXTRAMAIDA       (10+MAXDISPLAYS*(MAXDIGDISPLAY+MAXBYTESLUZ))
#define MAXTRAMAVUELTA    (10+MAXDISPLAYS*MAXSTATUSDISPLAY)

#define INITRAMA     0xFF
#define FINTRAMA     0xFE

//Comandos UNC90->DISPLAYS
#define  ENCDISP         1
#define  WHO             2
#define  CICLOTRABAJO    3
#define  GRABALOG        4
#define  GRABASERIE      5
#define  TRAMANULA       6
#define  ENCDISP1        7
#define  TRAMANULA1      8
#define  WHOEXTENDIDO	 9

//Comandos DISPLAYS->UNC90
#define RESPST       0X81
#define RESPWHO      0X82
#define RESPLOG      0X83
#define RETERROR     0X84
#define RESPST1      0X85
#define RESPWHOEXT   0X86


//Estados posibles del socket de comunicacion con el PC
#define STSOCKABRIENDO    1
#define STSOCKCONECTANDO  2
#define STSOCKABIERTO     3
#define STSOCKCERRADO     4

//Comandos de PC->UNC90
#define STATUSLIN       1
#define STATUSDISP      2
#define PONDISP         3
#define PONMODOTEST     4
#define PAROPUERTO      5
#define MANDACONF       6
#define DIRYVEL			7
#define RESTRICTED      8


// Posibles sentidos para la tralación de la cadena en los displays.
#define STOP 0
#define PLAY 1
#define PAUSE 2
#define REVERSE 3
#define MOVSIEMPRE 4
#define MOVCONDICIONAL 5

#define MAXPORTREAL   32

//Comandos de UNC90->PC
#define RESPSTLIN       100
#define RESPSTDISP      101
#define RESPESTLIN      102
#define RESPVERSION     103
//Estructura con los ipos de displays soportados
typedef struct TIPODISPS {
          int      tipo;                          //Tipo de display
          char     nombre[MAXNOMBREDISPLAY];      //Nombre completo del tipo de display
          int      digitos;                       //Numero de digitos que soporta
          int      botones;                       //Numero de botones
          int      luces;                         //Numero de luces
          int      status;                        //Maximo numero de bytes de status
          // Innecesario. Siempre es el sexto.
//          int      luzdig;                        //Luz que representa los digitos (Si esta se pone en parpadeo los digitos parpadean)
          long     consumo;                       //Consumo cuando el display esta totalmente apagado
        } tipodisps;

#define LUZDIGITOS	6

//Estructura de cada display
typedef struct {
         int       tipo;                          //Tipo del display
         tipodisps *tipodisp;                     //Puntero al tipo de display
         char      valor[MAXDIGDISPLAY];          //Valor presentado en el display
         char      status[MAXSTATUSDISPLAY];      //Estado del display segun ultima recepción
         unsigned short luces[MAXLUCESDISPLAY];   //Estado de las luces
         int       modifida;                      //Display ha sido modificado desde la ultima trama enviada
         int       modifvuelta;                   //Estado del display se ha modificado desde la ultima informacion al PC
         unsigned long      serie;                //Numero de serie
         unsigned long      version;              //Version del software del display
         unsigned long      errhard;              //Numero de errores hard enviados por el display
         unsigned long      errtrama;             //Numero de errores de trama detectados por el display
         long      consumo;                       //Consumo de los digitos/luces de la ultima trama enviada
      } eosdisps;


typedef struct V10SOCKETS {
           char            *npipe;       // Nombre del pipe
           short           port;         // Puerto del pipe
           struct sockaddr origen,       // Origen del pipe
                           destino;      // Destino del pipe
           SOCKET          soc;          // Socket Berkeley del pipe
           int             status;       // Estado del pipe
           pthread_t       thread;       // Thread del socket para accept y connect
           char            *bufrec;      // Buffer de recepcion
           int             tambufrec;    // Tamaño del buffer de recepcion
           int             nrec;         // Numero de caracteres recibidos
         } v10sockets;
extern v10sockets *v10slog;

//Estructura de una linea de displays
typedef struct EOSLINEAS {
         int        port;                         //Puerto serie de comunicacion con la red de displays
         int        dirserie;                     //Direccion del puerto serie
         int        numdisp;                      //Numero de displays reportados por el ultimo who
         eosdisps   disp[MAXDISPLAYS];            //Array de displays en linea
         int        modifida;                     //Indica si se ha modificado algun display desde la ultima trama enviada
         int        modifvuelta;                  //Indica si ha variado el estado de algun display desde la ultima informacion al PC
         int        modifestruc;                  //Indica si ha variado la estructura fisica de la linea desde la ultima informacion al PC
         int        modifestrucpc;
         int        recwho;                       //Estado de recepcion del who 0 Pendiente 1 Enviado 2 Recibido
         v10horas      hultwho;                      //Hora en la que se mando el ultimo who
         char       tramaida[MAXTRAMAIDA];        //Trama de ida fisica
         unsigned long   lonida;                  //Longitud de la trama de ida
         char       tramavuelta[MAXTRAMAVUELTA];  //Trama de vuelta fisica
         char       *ptrvuelta;                   //Puntero a la posicion en la que se ha de meter el siguiente byte de la trama de vuelta
         int        lonvuelta;                    //Longitud de la trama de vuelta
         v10horas      hulttramavuelta;              //Hora de la ultima trama de vuelta
         int        status;                       //Status de la linea
         v10horas      hultbyte;                     //Hora de recepcion del ultimo caracter
         unsigned char       check;               //Checksum calculado de la trama
         v10horas      hulttrama;                    //Hora en la que se mando la ultima trama
         v10horas      nexttrama;                    //Hora en la que se mandara la siguiente trama
         unsigned long       tramasida;           //Numero de tramas de inda enviadas
         unsigned long       tramasvuelta;        //Numero de tramas de vuelta enviadas
         unsigned long       bytesida;            //Numero de bytes enviados
         unsigned long       bytesvuelta;         //Numero de bytes recibidos
         unsigned long       bucles;              //Numero de bucles realizados
         unsigned long       reconexiones;        //Numero de reconexiones de los puertos
         unsigned long       creatramas;          //Numero de veces que se ha tenido que recalcular la trama
         unsigned long       errtrama;            //Numero de errores de tramas
         unsigned long       perdidos;            //Numero de bytes mal recibidos
         int                 numwho;              //Numero de whos realizados
         long                consumo232;          //Consumo de la linea debido al 232
         unsigned long       consumo;             //Consumo de la linea debido a luces encendidas o displays alimentados
         int                 ciclotrabajo[MAXLUCESDISPLAY];  //Ciclo de trabajo de cada una de las luces de los displays
         unsigned long       limitacionlinea;     //Maximo numero de microamperios a 23,20 V que debe soportar la linea
         unsigned long       tciclo;              //Tiempo de bucle
         unsigned long       tenvtrama;           //Tiempo de envio de trama
         unsigned long       timeouttrama;        //Timeout de trama
         unsigned long       timeoutwho;          //Timeout de who
         int                 modotest;            //Indica que la linea esta en modo test
         int                 paropuerto;          //Indica si la linea ha de parar un puerto serie es el numero de display a parar
         char                numcartrama;         //Numero de caracteres de una trama de vuelta
         v10sockets           *v10s;              //Socket de conexion con el PC
         int                 llevonulas;          //Numero de tramas nulas enviadas en desde la ultima trama completa
         int                 tramasnulas;         //Numero de tramas nulas a enviar despues de cada trama completa
         int                 tipotrama;           //Tipo de trama
         unsigned long       minversion;          //Minima version de los displays conectados
         char                velocidad;           //Velocidad de la cadena dentro del display
         int                 modifvel;            //Indica si se ha modificado la velocidad de presentación de la cadena en el display
         v10sockets           *vdsockvirt;
      } eoslineas;

extern unsigned long version;

//Funciones definidas en EOS232.C
int dame232(int port);
void reset232(int port);

//Funciones definidas en EOSPRINTF.C
void vlindisplayprintf(eoslineas *linea,int disp,char *format,va_list arg);
void lindisplayprintf(eoslineas *linea,int disp,char *format,...);
void linponlucesdisplay(eoslineas *linea,int disp,int luz,int valor);


//Funciones definidas en EOSCOM.C
void miescribelog(int nivel,char *format,...);
void initlinea(eoslineas *linea);
int automatalinea(eoslineas *linea);

//Funciones definidas en EOSCONSUMO.C
long consumolinea(eoslineas *linea);

//Funciones definidas en EOSPC.C
void automatapc(eoslineas *linea);


//Funciones definidas en EOSSSOCKET.C
int reabreservidor(v10sockets *v10s);
v10sockets *creaservidor(char *servicio);
int reabrecliente(v10sockets *v10s);
int verificasocket(v10sockets *s);
v10sockets *creacliente(char *ordenador,char *servicio);
int sendv10socket(v10sockets *s,char *donde,int bytes);
int haycarsocket(v10sockets *s);
int sigcarsocket(v10sockets *s);
int sigcarsocketw(v10sockets *s);
int leebufsocket(v10sockets *s,char *buffer,int len);
int leebufsocketw(v10sockets *s,char *buffer,int len);
int vprintfv10socket(v10sockets *s,char *format,va_list arg);
int printfv10socket(v10sockets *s,char *format,...);
void liberav10socket(v10sockets *s);

//Funciones definidas en EOSCOMUN.C
tipodisps *dametipo(int  mitipo);
void aniadetipo(int nuevotipo, char* nuevonombre, int nuevosdigitos, int nuevosbotones, int nuevasluces, int nuevostatus);
char *recogelong(char *cadena,unsigned long *p);
char *mandalong(char *cadena,unsigned long p);
char *recogeshort(char *cadena,unsigned short *p);
char *mandashort(char *cadena,unsigned short p);
char *llinfodameversion(unsigned long version,int adisp);
char *infodameversion(unsigned long version);

//funciones defindas en eosmain.c
void tratasocket(eoslineas *linea);
#endif /*EOS_H_*/

//#endif
