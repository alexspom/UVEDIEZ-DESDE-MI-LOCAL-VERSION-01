#include "vdform.h"

#define LIPETIQ 16

#define ROMAN  1
#define HELVE  2
#define PRESE  3
#define GOTIC  4
#define PREST  5
#define COURI  6

#define TCODE39    1
#define INTER25    2
#define CODE128    8
#define EAN13      7
#define DATAMATRIX 9
#define PDF417     4
#define TCODABAR   3

// Status posibles de impresora de etiquetas
#define STTERMICAOK        0 // Impresora lista
#define STTERMICASINPAPEL  1 // Impresora sin papel
#define STTERMICASINCINTA  2 // Impresora sin cinta
#define STTERMICACARGADA   4 // Impresora con etiqueta cargada
#define STTERMICAATASCO    8 // Impresora atascada
#define STTERMICAAPAGADA  16 // Impresora no responde
#define STTERMICAABIERTA  32 // Impresora con cabezal abierto
#define STTERMICAPAUSA    64 // Impresora termica en pausa
#define STTERMICABUFFER  128 // Impresora con buffer lleno
#define STTERMICAHARD    256 // Impresora con error hardware
#define STTERMICAENCURSO 512 // El status ha sido solicitado pero no se ha devuelto

typedef struct {
           char ip[LIPETIQ];
           char puertotcpenv[MAXNOMBREV10];
           char puertotcprec[MAXNOMBREV10];
           v10socks *pipeenv;
           v10socks *piperec;
         } tcpipetiq;


typedef struct IDRIVER {
         char *nfile;
         FILE *salida;
         int tx,ty;   // tama�o de la etiqueta en 1/10 mm.
         int ex,ey;   // Numero de etiquetas por p�gina si procede
         int px,py;   // Posicion del cursor
         int font;    // Tipo de font
         int color;  // Color del caracter, positivo o negativo/*(1) Fin */
         int fx,fy;   // Tama�o del font en x e y
         int tipocb;  // Tipo de codigo de barras
         int ancb;    // Ancho de la barra fina
         int alcb;    // Alto del codigo de barras
         int ratiocb; // Ratio entre barra fina y gruesa
         int angulo;  // Angulo de escritura
         int numcad;  // Numero de cadena si procede
         int numcb;   // Numero de codigo de barras si procede
         int repiteetiq;
	     void (*asignatametiq)(struct IDRIVER *id,char **ptrsal);
         void (*imprimecadena)(struct IDRIVER *id,char *cadena,char *fin,char *ptrsal);
		 void (*imprimecadenainv)(struct IDRIVER *id, char *cadena, char *fin, char *ptrsal);
         void (*imprimebarras)(struct IDRIVER *id,char *cadena,char *fin,char **ptrsal);
         void (*imprimelogo)(struct IDRIVER *id,char **cadena,int px, int py, int tx, int ty, char *nombre);
         void (*imprimelogohp)(struct IDRIVER *id,char **cadena,int px, int py, char *nombre);
         void (*imprimelinea)(struct IDRIVER *id,char **ptrsal,int lx,int ly,int ancho,int tipo);
         void (*cambiamaxetiq)(struct IDRIVER *id,char **ptrsal,int maxx,int maxy);
         void (*tiraetiq)(struct IDRIVER *id,char **ptrsal);
         void (*initetiq)(struct IDRIVER *id,char **ptrsal);
         int  (*statusimpre)(struct IDRIVER *id,int PUERTO,tcpipetiq *tcpip);
         void (*cancelatrabajo)(struct IDRIVER *id,int PUERTO,tcpipetiq *tcpip);
         void (*abre)(struct IDRIVER *id, char *cadena,FILE **salida);
         void (*cierra) (struct IDRIVER *id,FILE **salida);
         void (*finaliza) (struct IDRIVER *id);
      } idrivers;

typedef struct {
           char nombre[MAXNOMBREV10];
           int lon;
           int inicio;
         } idatos;

//Funciones definidas en v10cursordin.c
char *vgeneraetiqueta(idatos **lplpidatos,v10cursors *cur,char *params);

//Funciones definidas en v10genetiq.c
char *realizaimpresionetiq(idatos *idato,idrivers *id,char *datosetiq,char *nfile,int *lon);

//Funciones definidas en v10ZPL.C
void pondriverzplii(idrivers *id);
void pondriverzpliiv(idrivers *id);
void pondriverzplii300(idrivers *id);
void pondriversato(idrivers *id);
//Funciones definidas en V10METO.C
void pondrivermeto(idrivers *id);
void pondrivermeto2(idrivers *id);
void pondrivermarkpoint(idrivers *id);
//Funciones definidas en V10TEC.C
void pondrivertec(idrivers *id);
//Funciones definidas en V10CAB.C
void pondrivercab(idrivers *id);


//Funciones definidas en v10impreetiq.c
void cargadriver(char *driver,idrivers *id);
VDEXPORT int vimprimeetiqueta(char *driver,idatos **idatoetiq,char *cursor,char *fichgen,char *salida,int verificastatus,int tipoconex,char *dirrip,int puerto,int velocidad,int numetiq,char *msjerror,char *params);

