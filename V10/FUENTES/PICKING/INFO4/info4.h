#ifdef WIN32
#include "info4win.h"
#endif

#include "vd.h"
#include <fcntl.h>
#include <sys/types.h>


//Valores por defecto del UNC90
#define TIMEOUTWHO      100
#define TIMEOUTTRAMA    100
#define TENVTRAMA       10
#define TPERRO232       100
#define LIMITACIONLINEA 2000000
#define TCICLO          1
#define TRAMASNULAS     10


//Estados posibles del socket de comunicacion con el PC
#define STSOCKABRIENDO    1
#define STSOCKCONECTANDO  2
#define STSOCKABIERTO     3
#define STSOCKCERRADO     4

//Teclas del display
#define TECLAACEPTA   0
#define TECLAMAS      1
#define TECLAMENOS    2
#define TECLAFUNCION  3

#define WHOPEND      0
#define WHOENV       1
#define WHOREC       2
#define MANDADOTEST  3
#define MANDADOCICLO 4
#define MANDADOPARO  5

#define MAXETHER         10
#define MAXLINEAS        32
#define MAXPUERTOS       16
#define MAXDISPLAYS     250
#define MAXTOTDISPLAYS  (MAXETHER*MAXLINEAS*MAXDISPLAYS)
#define MAXDIGDISPLAY    512
#define MAXSTATUSDISPLAY 10
#define MAXNOMBREDISPLAY 20
#define MAXLUCESDISPLAY   8
#define MAXBOTONESDISPLAY 5
#define MAXBYTESLUZ       ((MAXLUCESDISPLAY+3)/4)
#define MAXTRAMAIDA       (10+MAXDISPLAYS*(MAXDIGDISPLAY+MAXBYTESLUZ))
#define MAXTRAMAVUELTA    (10+MAXDISPLAYS*MAXSTATUSDISPLAY)

#define INITRAMA     0xff
#define FINTRAMA     0xfe

//Comandos UNC90->DISPLAYS
#define  ENCDISP         1
#define  WHO             2
#define  CICLOTRABAJO    3
#define  GRABALOG        4
#define  GRABASERIE      5
#define  TRAMANULA       6
#define  ENCDISP1        7
#define  TRAMANULA1      8

//Comandos DISPLAYS->UNC90
#define RESPST       0X81
#define RESPWHO      0X82
#define RESPLOG      0X83
#define RETERROR     0X84
#define RESPST1      0X85

//Definicion de bits de status en nibble alto
#define BITSTLEN     0X80
#define BITERRHARD   0X40
#define BITERRSOFT   0X20

//Comandos de PC->UNC90
#define STATUSLIN       1
#define STATUSDISP      2
#define PONDISP         3
#define PONMODOTEST     4
#define PAROPUERTO      5
#define MANDACONF       6

//Comandos de UNC90->PC
#define RESPSTLIN       100
#define RESPSTDISP      101
#define RESPESTLIN      102
#define RESPVERSION     103

//Estructura con los ipos de displays soportados
typedef struct TIPODISPS {
          int      tipo;                          //Tipo de display
          char     nombre[MAXNOMBREDISPLAY];      //Nombre completo del tipo de display
	unsigned digitos;                       //Numero de digitos que soporta
	unsigned botones;                       //Numero de botones
	unsigned luces;                         //Numero de luces
	unsigned status;                        //Maximo numero de bytes de status
	// Innecesario. Siempre es el sexto.
	//          int      luzdig;                        //Luz que representa los digitos (Si esta se pone en parpadeo los digitos parpadean)
	long     consumo;                       //Consumo cuando el display esta totalmente apagado
        } tipodisps;

//Estructura de cada display
typedef struct {
         int       tipo;                          //Tipo del display
         tipodisps *tipodisp;                     //Puntero al tipo de display
         char      valor[MAXDIGDISPLAY];          //Valor presentado en el display
         char      status[MAXSTATUSDISPLAY];      //Estado del display segun ultima recepción
         unsigned short luces[MAXLUCESDISPLAY];        //Estado de las luces
         int       modifida;                      //Display ha sido modificado desde la ultima trama enviada
         int       modifvuelta;                   //Estado del display se ha modificado desde la ultima informacion al PC
         unsigned long      serie;                         //Numero de serie
         unsigned long      version;                       //Version del software del display
         unsigned long      errhard;
         unsigned long      errtrama;
         long      consumo;                       //Consumo de los digitos/luces de la ultima trama enviada
      } infodisps;

typedef struct {
           char            *npipe;       // Nombre del pipe
           short           port;         // Puerto del pipe
           struct sockaddr origen,       // Origen del pipe
                           destino;      // Destino del pipe
           SOCKET          soc;          // Socket Berkeley del pipe (POR FIN)
           int             status;       // Estado del pipe
           DWORD       thread;
           char            *bufrec;
           int             tambufrec;
           int             nrec;
         } vdsockets;
extern vdsockets *vdslog;

//Estructura de una linea de displays
typedef struct INFOLINEAS {
         int        port;                         //Puerto serie de comunicacion con la red de displays
         int        dirserie;                     //Direccion del puerto serie
         int        numdisp;                      //Numero de displays reportados por el ultimo who
         infodisps  disp[MAXDISPLAYS];            //Array de displays en linea
         int        modifida;                     //Indica si se ha modificado algun display desde la ultima trama enviada
         int        modifvuelta;                  //Indica si ha variado el estado de algun display desde la ultima informacion al PC
         int        modifestruc;                  //Indica si ha variado la estructura fisica de la linea desde la ultima informacion al PC
         int        modifestrucpc;
         int        recwho;                       //Estado de recepcion del who 0 Pendiente 1 Enviado 2 Recibido
         v10horas      hultwho;                      //Hora en la que se mando el ultimo who
         char       tramaida[MAXTRAMAIDA];        //Trama de ida fisica
         unsigned long   lonida;                       //Longitud de la trama de ida
         char       tramavuelta[MAXTRAMAVUELTA];  //Trama de vuelta fisica
         char       *ptrvuelta;
         int        lonvuelta;
         v10horas      hulttramavuelta;
         int        status;
         v10horas      hultbyte;                     // Hora de recepcion del ultimo caracter
         unsigned char       check;
         v10horas      hulttrama;
         unsigned long       tramasida;
         unsigned long       tramasvuelta;
         unsigned long       bytesida;
         unsigned long       bytesvuelta;
         unsigned long       bucles;
         unsigned long       reconexiones;
         unsigned long       creatramas;
         unsigned long       errtrama;
         unsigned long       perdidos;
         int                 numwho;
         long                consumo232;
         unsigned long       consumo;
         int                 ciclotrabajo[MAXLUCESDISPLAY];
         unsigned long       limitacionlinea;
         unsigned long       tciclo;
         unsigned long       tenvtrama;
         unsigned long       timeouttrama;
         unsigned long       timeoutwho;
         int                 modotest;
         int                 paropuerto;
         char                numcartrama;
         vdsockets           *vds;       
         int                 llevonulas;
         int                 tramasnulas;
         int                 tipotrama;
         unsigned long       minversion;
      } infolineas;

extern unsigned long version;      
      
//Funciones definidas en INFO4.C
void lindisplayprintf(infolineas *linea,int disp,char *format,...);   
void linponlucesdisplay(infolineas *linea,int disp,int luz,int valor);

//Funciones definidas en INFO4COM.C
void initlinea(infolineas *linea);
int automatalinea(infolineas *linea);

//Funciones definidas en INFOCONSUMO.C
long consumolinea(infolineas *linea);

//Funciones definidas en INFO4PC.C
void automatapc(infolineas *linea);

//Funciones definidas en VDSOCKET.C
vdsockets *creaservidor(char *servicio);  
int verificasocket(vdsockets *s); 
int sendvdsocket(vdsockets *s,char *donde,int bytes);
int reabreservidor (vdsockets *vds);
int haycarsocket(vdsockets *s);
int sigcarsocket(vdsockets *s);
int leebufsocket(vdsockets *s,char *buffer,int len);
vdsockets *creacliente(char *ordenador,char *servicio);
int reabrecliente(vdsockets *vds);
int leebufsocketw(vdsockets *s,char *buffer,int len);

//Funciones definidas en INFO4COMUN.C
tipodisps *dametipo(int  mitipo);
char *recogelong(char *cadena,unsigned long *p);
char *infodameversion(unsigned long version);
char *mandashort(char *cadena,unsigned short p); 
char *mandalong(char *cadena,unsigned long p);
char *recogeshort(char *cadena,unsigned short *p);
