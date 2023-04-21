/*
* Módulo : V10.H
* Objeto: Include para todos los programas basados en V10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#ifndef __V10__
#define __V10__

//Longitud maxima de una cadena en V10
#define MAXCADENA 32768
//Longitud maxima de un nombre de fichero con path completo
#define MAXPATH     512
#define MAXTECLAMENU 100
typedef struct {
    char *nombre;
    int  tecla;
} teclamenus;
extern teclamenus arrteclamenu[];
extern int nteclamenu;
#ifndef __LINUX__
#include "win/v10windows.h"
#else
#include "linux/v10linux.h"
#endif
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define LOGERROR     0
#define LOGWARNING   1
#define LOGNORMAL    2
#define LOGDEBUG     3
#define LOGAPI       4
#define LOGDEBUGAPI  5
#define LOGORACLE    6
#define LOGDEBUGORA  7
#define LOGWIN       8
#define LOGDEBUGWIN  9


#define MAXNOMBREV10 80
#define LNOMBREORDENADOR		(5*MAX_COMPUTERNAME_LENGTH+1)	

#include "winface.h"
#include "v10keys.h"
#include "wintexto.h"
#include "v10tipos.h"
#include "v10input.h"
#include "v10aborta.h"
#include "codbarras/codes.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern int singrafico;

//Macros auxiliares para depurar la memoria dinamica
#ifdef DEBUG_DINAMICA
  #define free(x)      v10free(x,__FILE__,__LINE__)
  #define malloc(x)    v10malloc(x,__FILE__,__LINE__)
  #define calloc(x,y)  v10calloc(x,y,__FILE__,__LINE__)
  #define realloc(x,y) v10realloc(x,y,__FILE__,__LINE__)
  #define strdup(c)    v10strdup(c,__FILE__,__LINE__)
#endif

//Funciones definidas en V10DINAMICA.C  
V10IMPORT void *v10calloc(unsigned size,unsigned number,char *file,int line);
//Hace calloc pero guarda registro de la memoria asignada
V10IMPORT void *v10malloc(unsigned size,char *file,int line);
//Hace malloc pero guarda registro de la memoria asignada
V10IMPORT char *v10strdup(char *ptr,char *file,int line);
//Hace strdup pero guarda registro de la memoria asignada
V10IMPORT void *v10realloc(void *ptr,unsigned size,char *file,int line);
//Hace realloc pero guarda registro de la memoria asignada
V10IMPORT void v10free(void *ptr,char *file,int line);
V10IMPORT void imprime_dinamica(char *fich_out);
V10IMPORT void initdinamica(char *entorno);

 // Funciones defindas en V10ATEXIT.C
V10IMPORT int v10atexit(void (*fun)(void));
//Funcion auxiliar para lograr que el visual se comporte segun estandar K&R
//#define atexit(x) v10atexit(x)
//Macro para redefinir atexit
V10IMPORT int ejecutaexit(void);
//Funcion que programar para que se ejecute al finalizar el programa mediante 
//  onexit(ejecutaexit);

//Funciones definidas en V10ANSIOEM.C
V10IMPORT int v10usaansi; 
//Variable que indica si las entradas a la aplicacion son en codificacion ANSI o OEM
V10IMPORT char *v10ansitooem(char *source,char *dest);
V10IMPORT char *v10oemtoansi(char *source,char *dest);
V10IMPORT char pasacharoem(char origen);
V10IMPORT char pasaoemchar(char origen);

//Funciones virtualizadas en V10PUNTEROS.C
//Util para permitir interfases web
V10IMPORT int v10versionweb;
V10IMPORT void (*fgotoxy)(int cx,int cy);
V10IMPORT void (*v10error)(char *formato,va_list lista_param_variable,short salir);
V10IMPORT int (*tecla)(void);
V10IMPORT int(*encolatecla)(int valor);
V10IMPORT int(*pushtecla)(int key);
V10IMPORT int (*reposicionaraton)(void *s);
V10IMPORT int (*llselecciona)(void *s);
V10IMPORT void (*pintapaginabloque)(void *s,int resaltado);
V10IMPORT int (*reposicionaraton)(void *s);
V10IMPORT void (*lpresenta)(void *,int,int);
V10IMPORT void (*muestradialog)(void *vi ,int guarda);
V10IMPORT void (*actualizadialog)(void *v);
V10IMPORT int (*blinput)(void *vi);
V10IMPORT int (*reposicionadialograton)(void *vi);
V10IMPORT int (*confirmasn)(int x,int y,char *cadena);
V10IMPORT void (*vmensajefm)(int x,int y,char *cadena,va_list arg);
V10IMPORT int (*initpuerto232)(int com,int velocidad,int paridad,int bits,int parada);
V10IMPORT void (*estado232)(int puerto,long *velocidad,int *paridad,int *parada,int *datos);
V10IMPORT void (*encolach232)(int com,int ch);
V10IMPORT void (*encolaecad232)(int com,char *cadena);
V10IMPORT int (*haycar232)(int com);
V10IMPORT int (*damecar232)(int com);
V10IMPORT void (*ponst232)(int com,long velocidad,int paridad,int stop,int bits);
V10IMPORT void (*printf232)(int com,char *format,...);
V10IMPORT void (*protocolo232)(int port,int xon);
V10IMPORT void (*pondtr232)(int com,int valor);
V10IMPORT void (*ponrts232)(int com,int valor);
V10IMPORT void (*cierrapuerto232)(int com);
V10IMPORT void (*fin232)(void);
V10IMPORT DWORD  (*escribebuffer232)(int com,void *msg, int tam);



//Funciones definidas en V10TIME.C
//Tipo que representa una fecha en juliano
typedef unsigned long v10dates;
//Tipo que representa tiempos en centesimas de segundo con decimales para mayor precision
typedef double v10horas;
V10IMPORT v10dates jultof(v10dates fechajul,int *dia,int *mes,int *ano);
//Pasa a juliano una fecha representada por dia mes ano
V10IMPORT char *jul2a(v10dates fechajul,char *formato,char *donde);
/* Pasa a ascii una fecha en juliano
           fechajul     fecha en juliano
		   formato      cadena que representa el formato 
		                   DD  dia
						   MM  Mes
						   YY  año en dos digitos
						   Y.YY ano en cuatro digitos
						la parte de la cadena que no se puede interpretar se copia tal cual
		   donde        Puntero a donde hay que dejar el resultado
*/
V10IMPORT v10dates f2jul(int dia,int mes,int ano);
//Devuelve el resultado en juliano de convertir dia mes ano
V10IMPORT v10dates damedate(void);
//Devuelve la fecha del sistema
V10IMPORT v10dates a2jul(int tipo,char *lafecha);
/*Pasa una fecha en ascii a juliano
           tipo       tipo de la fecha ascii
		                  1  dd-mm-y.yy
						  2  mm-dd-y.yy
						  3  yy-mm-dd
						  4  dd-mm
						  7  y.yy-mm-dd
*/
V10IMPORT char *cent2a(v10horas centhora,int formato,char separador,char *donde);
/* Pasa una hora expresada en centesimas de segundo a ascii
              centhora   hora en centesimas de segundo
			  formato    0: HH:MM:SS  (horas de 0 a 23)  ­Tipo por defecto!
                         1: HH:MM:SS  (horas de 0 a 11)
                         2: HH:MM:SS am
                         3: HH:MM  (horas de 0 a 23)
                         4: HH:MM  (horas de 0 a 11)
                         5: HH:MM am
                         6: HH:MM:SS:CC (horas de 0 a 23)
                         7: HH:MM:SS:CC (horas de 0 a 11)
						 8: HH:MM:SS:MMM
			  */
V10IMPORT v10horas a2cent(char *lahora);
//Pasa una cadena a hora en centesimas de segundo
V10IMPORT v10horas gettime(void);
//Devuelve la hora del dia
V10IMPORT v10horas damecent(void);
//Devuelve el numero de centesimas que ha pasado desde que se arranco el programa

 //Funciones definidas en V10TIMERS.C
 typedef struct V10TIMERS {
        char     *nombre;     // Nombre externo del timer
        v10dates ultfecha,    // Fecha de la ultima ejecucion
                 proxfecha;   // Fecha de la proxima ejecucion
        v10horas   ulthora,   // Hora de la ultima ejecucion
                 proxhora,    // Hora de la proxima ejecucion
                 intervalo;   // Intervalo en centesimas de segundo entre ejecuciones
        int      clase;       // Identificador de tipo de timer
        void     (*triger)(struct V10TIMERS *lt); //Triger que se ejecuta
        void     *dato;       // Puntero a datos definible por el usuario
      } v10timers;

/* Clases de timer. El usuario puede definir tantas como necesite */
#define TIMERTECLA    1 /* Timer que se ejecuta automaticamente desde hay_tecla */
#define TIMERBUCLE    2 /* Timer que ejecuta el usuario desde el bucle principal */
#define TIMERUSER     3 /* Timer de usuario */
#define TIMERTIMEOUT  4 /* Timer que solo se ejecuta cuando pasa un tiempo sin pulsar una tecla */

V10IMPORT void declarav10timer(char *nombre,void (*triger)(v10timers *lt),v10horas intervalo,int clase,void *dato);
/* Declara un timer y lo dispara immediatamente
     Nombre nombre del timer por el que se identificara
     Triger Funcion a ejecutar
     Intervalo Tiempo en centesimas entre ejecuciones
     Clase Tipo de timer.
     Dato Puntero a datos definidos por el usuario
*/
V10IMPORT void declarav10timernt(char *nombre,void (*triger)(v10timers *lt),v10horas intervalo,int clase,void *dato);
// Declara un triger pero no lo dispara immediatamente
V10IMPORT void liberav10timer(char *nombre);
/* Libera el timer especificado */
V10IMPORT v10horas cambiaintervalotimer(char *nombre,v10horas intervalo);
/* Cambia el intervalo del timer */
V10IMPORT void resetuntimer(v10timers *lt);
/* Pone la siguiente ejecucion del timer dentro de intervalo centesimas de segundo
   Esto es olvida el tiempo que ha transcurrido desde la ultima ejecucion */
V10IMPORT void resettimer(char *nombre);
/* Pone la siguiente ejecucion del timer dentro de intervalo centesimas de segundo
   Esto es olvida el tiempo que ha transcurrido desde la ultima ejecucion */
V10IMPORT void resettimers(int clase);
/* Hace reset de todos los timers de una clase */
V10IMPORT void disparatimers(int clase);
/* Dispara todos los timers de una clase determinada */

//Funciones definidas en V10TOOLTIP
V10IMPORT long v10tiempotooltip;
//Indica cuanto tiempo ha de estar el raton sobre un campo antes de que salte el tooltip
V10IMPORT void (*funciontooltip)(mouseposs *raton); 
//Funcion que se ejecuta para mostrar el tooltip
V10IMPORT void *ponfunciontooltip(void *funcion);
V10IMPORT void v10limpiatooltip(HWND hwnd);
V10IMPORT int v10tooltip(mouseposs *raton,char *texto);
V10IMPORT void creatooltip(HWND hwnd);
V10IMPORT void destruyetooltip(HWND hwnd);
V10IMPORT void mueveratontooltip(HWND hwnd,int x,int y);

//Funciones definidas en V10TRANS.C
#define LIDIOMAV10 21
//Idiama de la aplicacion
V10IMPORT char idiomav10[LIDIOMAV10];
//Puntero a funcion que realiza la traduccion de una cadena
V10IMPORT char *(*v10translate)(char *cadena);
//Puntero a la funcion de traduccion inversa de una cadena
V10IMPORT char *(*v10untranslate)(char *cadena);
V10IMPORT void setv10trans(char *(ftrans)(char *cadena),char *(funtrans)(char *cadena));

//Funciones defindas en V10FICHERO.C
V10IMPORT int precalculaficheros;
V10IMPORT int damenombrecompleto(char *nombre,char *completo);
// Devuelve en la variable completo el nombre con path del fichero identificado por nombre
V10IMPORT FILE *fopenpath(char *nombre,char *modo);
// Sustituta de fopen que busca en el path el fichero a abrir
V10IMPORT FILE *fopenseguro(char *nombre,char *modo);
 // Lo mismo que fopenpath pero aborta si el fichero no se puede abrir 
V10IMPORT FILE *fopenlog(char *nombre,char *modo);
 // Lo mismo que fopenpath pero si no puede abrir graba una linea de log
V10IMPORT char *fgetss(char *linea,int n,FILE *entrada);
 // Igual que fgets pero elimina el \n del final
V10IMPORT int copiafich( char *fdesde, char *fhasta );
// copia un fichero 
V10IMPORT int muevefich( char *fdesde, char *fhasta );
// mueve un fichero a otro

//Funciones defindas en V10CADENAS.C
V10IMPORT char pasacarmay(int ch);
//Pasa un caracter a mayusculas
V10IMPORT char pasacarmin(int ch);
//Pasa un caracter a minusculas
V10IMPORT char *strfill(char *cadena,char ch,unsigned leng);
//Rellena cadena con el caracter ch repetido leng veces, termina la cadena en \0
V10IMPORT char *trunca(char *cadena,unsigned leng);
//Trunca una cadena a len caracteres
V10IMPORT char *padcar(char *cadena,unsigned leng,char ch);
//Rellena la cadena hasta longitud len con caracter ch por la derecha
V10IMPORT char *pad(char *cadena,unsigned leng);
//Rellena una cadena por la derecha hasta longitud leng con espacios
V10IMPORT char *lpadcar(char *cadena,unsigned leng,char ch);
//Rellena una cadena por la izquierda hasta longitud leng con caracter ch
V10IMPORT char *lpad(char *cadena,unsigned len);
//Rellena una cadena por la izquierda hasta longitud len con espacios
V10IMPORT char *centra(char *cadena,unsigned leng);
//Centra una cadena en longitud leng rellenando a izq. y/o der. con espacios
V10IMPORT char *trim(char *cadena);
//Quita los espacios finales de una cadena
V10IMPORT char *ltrim(char *cadena);
//Quita los espacios iniciales de una cadena
V10IMPORT char *eliminasp(char *cadena);
//Quita los espacios iniciales y finales de una cadena
V10IMPORT char *strinserta(char *cadena,unsigned desde,unsigned leng);
//Inserta leng espacios en la cadena a partir del caracter desde conservando la longitud de la cadena
V10IMPORT char *strins(char *destino,char *fuente);
//Inserta la cadena fuente en destino al principio
V10IMPORT char *strdel(char *cadena,unsigned desde,unsigned leng);
//Borra leng caracteres de una cadena desde la posicion desde respetando la longitud original
V10IMPORT char *strerase(char *cadena,unsigned desde,unsigned leng);
//Borra leng caracteres de una cadena desde la posicion desde modificando la longitud original
V10IMPORT char *strcopia(char *destino,char *fuente,size_t leng);
//Copia leng caracteres de fuente a destino terminando destino en \0
V10IMPORT char *irfin(char *cadena);
//Devuelve un puntero al ultimo caracter no blanco de la cadena
V10IMPORT char *sigpal(char *posact);
//Devuelve un puntero a la siguiente palabra de la cadena
V10IMPORT char *antpal(char *inicio,char *posact);
//Devuelve un puntero a la palabra anteriro a posact de la cadena inicio
V10IMPORT char *strmay(char *cadena);
//Pasa una cadena a mayusculas en español
V10IMPORT char *strmin(char *cadena);
//Pasa una cadena a minusculas en español
V10IMPORT int stricomp(char *destino,char *fuente);
//Compara las cadenas destino y fuente sin tener en cuenta mayusculas y minusculas
V10IMPORT int strnicomp(char *destino,char *fuente,unsigned leng);
//Compara leng caracteres de las cadenas destino y fuente sin tener en cuenta mayusculas y minusculas
V10IMPORT int es_blanco(char *cadena);
//Devuelve 1 si la cadena es vacia o solo blancos 0 en otro caso.
V10IMPORT int piece(char *buffer,char *donde,char *sep,int parte);
//Parte una cadena buffer en piezas devolviendo el resultado en donde, sep es el separador de las piezas y
//parte el numero de la pieza en la que estamos interesados
V10IMPORT int numpieces(char *buffer,char *sep);
//Devuelve el numero de piezas que tiene una cadena
V10IMPORT int damenumeropieza(char *cadena,char *pieza,char *separador);
//Devuelve el numero que ocupa la cadena pieza en el buffer
V10IMPORT int contieneex(char *cadenain,char *comparar,char *separador,char *seprango,int admitenulo);
//Devuelve 1 si comparar esta en cadenain in considerada como rangos 
V10IMPORT int contiene(char *cadenain,char *comparar);
//Devuelve 1 si comparar esta en cadenain in considerada como rangos
V10IMPORT int contienenumex(char *cadenain,double comparar,char *separador,char *seprango,int admitenulo);
//Devuelve 1 si comparar esta en cadenain in considerada como rangos
V10IMPORT int contienenum(char *cadenain,double comparar);
//Devuelve 1 si comparar esta en cadenain in considerada como rangos



//Funciones defindas en V10LOG.c
//Define el maximo nivel de log que se genera
V10IMPORT int maxnivellog;
V10IMPORT void ponprefijolog(char *cadena);
//Define la linea en la que comienza la ventana de log
V10IMPORT int filalog;
V10IMPORT int logfun;
V10IMPORT int logfile;
V10IMPORT void *ponfnlog(void (*mifnlog)(char *strlog));
//Establece una funcion que se ejecuta cada vez que se hace log
V10IMPORT void initv10logparam(char *nflog,int logx,int logy,int logdx,int logdy);
/*Inicializa el log
              nflog     Nombre del fichero de log
			  logx      Columna en la que empieza la ventana de log
			  logy      Fila en la que empieza la ventana de log
			  logdx     Numero de columnas de la ventana de log
			  logdy     Numero de filas de la ventana de log
*/
V10IMPORT void initv10log(char *nflog);
//Inicializa el fichero de log por defecto
V10IMPORT void dimenombrelog(char *nlog);
//Devuelve el nombre completo del fichero de log
V10IMPORT void editalog(void);
//Edita el fichero de log en editor estandar
V10IMPORT void vv10logchf(int nivel, int conhora, const char *funcion, char *file, int line, char *format, va_list arg);
//Escribe en el log en formato vprintf
V10IMPORT void v10logchf(int nivel,int conhora,const char *funcion,char *file,int line,char *format,...);
//Escribe en fichero de log en formato printf
V10IMPORT void vv10logf(int nivel,const char *funcion,char *file,int line,char *format,va_list arg);
//Escribe en el log en formato vprintf
V10IMPORT void v10logf(int nivel,const char *funcion,char *file,int line,char *format,...);
//Escribe en fichero de log en formato printf
#define vv10logch(nivel,conhora,format,arg) vv10logchf(nivel,conhora,__FUNCTION__,__FILE__,__LINE__,format,arg)
#define vv10log(nivel,format,arg) vv10logf(nivel,__FUNCTION__,__FILE__,__LINE__,format,arg)
#define v10logch(nivel,conhora,format,...) v10logchf(nivel,conhora,__FUNCTION__,__FILE__,__LINE__,format,__VA_ARGS__)
#define v10log(nivel,format,...) v10logf(nivel,__FUNCTION__,__FILE__,__LINE__,format,__VA_ARGS__)


//Funciones definidas en V10VIRTSEL.C
typedef struct {
          windows   v;  /* Ventana real de paginación */
          windows   *v1;  /* Ventana que el usuario pasa */
          int       ulin;  /* Ultima línea lógica en pantalla */
          int       plin;  /* Primera línea lógica en pantalla */
          int       clin;  /* Línea lógica del cursor */
          int       numlin;  /* Número total de líneas lógicas del array de paginación */
          int       linreg;  /* Líneas físicas por línea lógica */
          int       lppag;  /* Número de líneas lógicas por pantalla */
          int       ucol;  /* Ultima columna lógica en pantalla */
          int       pcol;  /* Primera columna lógica en pantalla */
          int       ccol;  /* Columna lógica del cursor */
          int       numcol;  /* Número total de columnas lógicas */
          int       colreg;  /* Columnas físicas por columna lógica */
          int       cppag;  /* Número de columas lógicas por pantalla */
          int       sobran;  /* Elementos en la última fila lógica */
          int       numero; /* Número total de elementos de usuario a paginar */
          int       hayinput; /* Presentacion o input */
          int       marco;
          int       modo; /* 0 salva enmarca y recupera al salir
                             1 Solo pone doble marco al entrar y lo
                             quita al salir */
          int       salir;  /* Variable interna para control de bucles */
          char      *titulo;  /* Titulo de la pantalla */
          void      (*pinta)(void *,short); /* Función que se invoca cada vez
                                          que se posiciona un elemento en
                                          la ventana. Recibe un puntero a
                                          la propia selección y un short
                                          que indica si est  resaltado
                                            0 no resaltado
                                            1 resaltado
                                          Esta función
                                          est  a disposioción del programador
                                          para que pinte el elemento que
                                          desee. */
          int       (*tecla)(void *); /* Función que se invoca antes de procesar
                                    una tecla. Permite que el programador la
                                    gestione y devuelva la que él desee. */
          void      *dato; /* Puntero abierto a cualquier uso */
        } virtsels;

#define VIRTPOS(vs) ((vs)->clin * (vs)->numcol + (vs)->ccol)

V10IMPORT void poncursorsel(virtsels *s);
V10IMPORT void repintapagina(virtsels *s);
V10IMPORT void representapagina(virtsels *s);
V10IMPORT int enrango(int x,int x1,int x2);
V10IMPORT int STDreposicionaraton(virtsels *s);
V10IMPORT int reselecciona(virtsels *s,int (*fprocesaposttecla)(int));
V10IMPORT int STDllselecciona(virtsels *s);
V10IMPORT void reposiciona(virtsels *s,int elemento);
V10IMPORT void initselec(virtsels *s,int margen_izdo,int margen_sup,int margen_dcho,int margen_inf,int modo,windows *v_user,int numero,int lin_reg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato);
V10IMPORT int selecciona(int margen_izdo,int margen_sup,int margen_dcho,int margen_inf,int modo,windows *v_user,int numero,int lin_reg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato);
V10IMPORT int presseleccion(int margen_izdo,int margen_sup,int margen_dcho,int margen_inf,int modo,windows *v_user,int numero,int lin_reg,int col,int ancho,char *titulo,void *pinta,void *tecla,int princ,void *dato);

//Funciones definas en V10HELP.C

V10IMPORT char file_help[MAXPATH];

V10IMPORT void v10help(void);
V10IMPORT void v10quitaayuda(void);
V10IMPORT int v10ponayuda(char *texto);
V10IMPORT void pintaonline(char *cadena);
V10IMPORT void borraonline(void);

//Funciones definidas en V10VIRTLISTA.C
V10IMPORT int v10busca(void *lista,char *(*indexa)(void *,int),char *buffer,int *unico);

//Funfiones defindas en V10MENUS.C
V10IMPORT int MENUHLP;
typedef struct {
         void *opciones;
         char *(*indexa)(void *opciones,int indice);
         int  (*busca)(void *opciones,char *(*indexa)(void *opciones,int indice),char *buffer,int *unico);
         void (*pinta)(virtsels *s,int resal);
         int (*tecla)(virtsels *s);
         char *buffer;
         void *dato;
       } menustructs;


V10IMPORT int menucabecera(void *opciones,int primera,int centrar,int margensup,char *textosup,int x1,int y1,int x2,int y2,int salvar,
			     char *(*indexa)(void *dato,int indice),int (*buscar)(virtsels *s),
			     void (*pinta)(virtsels *s,int indice),int (*sutecla)(virtsels *s),
			     void *dato);
V10IMPORT int menutotal(void *opciones,int primera,int x1,int y1,int x2,int y2,int salvar,
			   char *(*indexa)(void *dato,int indice),int (*buscar)(virtsels *s),
			   void (*pinta)(virtsels *s,int indice),int (*sutecla)(virtsels *s),
			   void *dato);
V10IMPORT int menugenerico(void *opciones,int primera,int x1,int y1,int x2,int y2,int salvar,
                           char *(indexa)(void *s,int indice),int (*sutecla)(virtsels *s),void *dato);
V10IMPORT int menu(char **opciones,int primera,int x,int y);
V10IMPORT int menuanidado(char **opciones,int primera,int x,int y,...);

//Funciones definidas en V10FORMAT.C 
#define COMADECIMAL  1
#define MARCAMILES   2
#define SIGNODERECHA 4
#define FUERZASIGNO  8

V10IMPORT unsigned v10formatdef;

V10IMPORT char *v10lformat(long numero,int longitud,int tipo,char relleno,char *donde,int base);
V10IMPORT char *v10uformat(unsigned long numero,int longitud,int tipo,char relleno,char *donde,int base);
V10IMPORT long v10lval(char *cadena,int tipo,int base);
V10IMPORT unsigned long v10uval(char *cadena,int tipo,int base);
V10IMPORT char *v10dformat(double numero,int decimales,int longitud,int tipo,char relleno,char *donde);
V10IMPORT double v10dval(char *cadena,int tipo);

//Funciones definidas en V10LISTAMENUS.C
typedef struct {
               char *nombre; 
               char **p; 
               int num; 
               int maximo; 
               } menulistas;


V10IMPORT menulistas *crea_menulista(char *nombre,unsigned maximo);
V10IMPORT void libera_menulista(menulistas *menulista);
V10IMPORT int esta_en_menulista(menulistas *menulista,char *cadena);
V10IMPORT int mete_en_menulista(menulistas *menulista,char *cadena);
V10IMPORT int salva_menulista(menulistas *menulista);
V10IMPORT int carga_menulista(menulistas *menulista);
V10IMPORT char *valor_menulista(menulistas *menulista,int elemento);
V10IMPORT int saca_menu(menulistas *menulista,int x,int y);

//Funciones V10CLIPBOARD.C
V10IMPORT void mete_en_clipboard(char *cadena);
V10IMPORT void apilaclipboard(int estiponum,int formato);

//Funciones definidas en V10EDITOR.C
V10IMPORT char *editorv10;
V10IMPORT int editormonofichero;
V10IMPORT int ejecutacomando(char *cadena, char flags, char *dirini);
V10IMPORT void vinvocaeditor(char *fichero,va_list arg);
V10IMPORT void invocaeditormultiple(char **fichero,int numfich);
V10IMPORT void invocaeditor(char *fichero,...);

//Funciones definidas en V10MENSAJE.C
V10IMPORT int STDconfirmasn(int x,int y,char *cadena);
V10IMPORT int confirmasnf(int x,int y,char *cadena,...);
V10IMPORT int confirmasnfc(int y,char *cadena,...);
V10IMPORT void STDvmensajefm(int x,int y,char *cadena,va_list arg);
V10IMPORT void mensajefm(int x,int y,char *cadena,...);
V10IMPORT void vmensajefcm(int y,char *cadena,va_list arg);
V10IMPORT void mensajefcm(int y,char *cadena,...);
V10IMPORT void mensajesistema(long err);
V10IMPORT void dameerrsistema(long err,char *donde);
V10IMPORT int debugmsg;

//Funciones definidas en V10DEFINE.C
V10IMPORT void leedefines(char *nombre);
V10IMPORT void sustituyedefines(char *linea);

//Funciones definidas en V10DLL.C
V10IMPORT void unloaddll(char *libreria);
V10IMPORT void *damefundllex(char *libreria,char *funcion,int decora);
V10IMPORT void *damefundll(char *libreria,char *funcion);

//Funciones definidas en V10232.C
#define MAXPUERTOS232 40

V10IMPORT void STDfin232(void);
V10IMPORT HANDLE damepuerto232(int puerto);
V10IMPORT void STDcierrapuerto232(int com);
V10IMPORT int STDinitpuerto232(int com,int velocidad,int paridad,int bits,int parada);
V10IMPORT void STDestado232(int puerto,long *velocidad,int *paridad,int *parada,int *datos);
V10IMPORT void trataerror232(int com);
V10IMPORT void STDencolach232(int com,int ch);
V10IMPORT void STDencolaecad232(int com,char *cadena);
V10IMPORT DWORD STDescribebuffer232(int com,void *msg, int tam);
V10IMPORT int STDhaycar232(int com);
V10IMPORT int STDdamecar232(int com);
V10IMPORT void STDponst232(int com,long velocidad,int paridad,int stop,int bits);
V10IMPORT void STDprintf232(int com,char *format,...);
V10IMPORT void STDprotocolo232(int port,int xon);
V10IMPORT void STDpondtr232(int com,int valor);
V10IMPORT void STDponrts232(int com,int valor);

//Funciones definidas en V10ARGV.C
/* Indica si se ha de avisar al programador de casos especiales
   0 Intenta continuar sin avisar
   1 Avisa de escrituras fuera de pantalla
     Clave primaria modificable
     Campo con nombre existente en la base de datos y formato incompatible
     Privilegio definido en pantalla no existe
   2 Pantalla sin ONLINE o sin AYUDA
   3 Campo sin titulo o traduccion excel
     Campo en bloque hijo com mismo nombre que campo en bloque padre y no VIRTUAL
*/
V10IMPORT int MODODEBUG;
// Indica si los mensajes y finales se han de poner en ventana diferente o la misma
V10IMPORT int MODOSERVICIO;
V10IMPORT int trataparammain(char *cadena);
V10IMPORT int trataparampremain(char *cadena);
V10IMPORT int trataparamstd(int argc,char *argv[],...);

//Funciones defindias en V10SOCK.C
#define TAMRECSERVER 16384
//Numero de veces que se intenta cerrar un socket antes de abandornar
#define NUMREINTCIERRA 10
//Posibles eventos de un socket
#define SOCKOPEN   0
#define SOCKREAD   1
#define SOCKBREAK  3
#define SOCKCLOSE  4

//Posibles estados de un socket
#define STSOCKCONCLSOCK  1   //Esperando a conectar cliente
#define STSOCKREADY      2   //Socket listo para comunicarse
#define STSOCKROTA       3   //Socket roto
#define STSOCKSERROMPE   4   //Server rompe socket
#define STSOCKSEMIROTA   5   //Socket roto

typedef struct V10SOCKS v10socks;
typedef struct SERVIDORSOCKS servidorsocks;

typedef void (*trigsocks)(struct V10SOCKS *p,int op,int bytes,char *buffer);
//Estructura de un socket V10 cliente
typedef struct V10SOCKS {
           char       *nombresock;       // Nombre del v10sock
           int        port;         // Puerto del v10sock
           struct sockaddr origen,  // Origen del v10sock
                           destino; // Destino del v10sock
           SOCKET     soc;         // Socket Berkeley del v10sock 
           int        status;       // Estado del v10sock
           char       *bufrec;     // Buffer de recepcion
           int        nrec;        // Numero de caracteres en buffer
           int        tamrec;      // Tamaño del buffer de recepcion
           HANDLE     threadtrata; // Handle al thread de recepcion
           trigsocks  fnopen,   // Funcion que se llama al open solo la primera vez
                      fnreconecta, // Funcion que se llama en cada conexion (incluyendo la primera)
                      fnread,   // Funcion que se llama al leer
                      fnbreak,  // Funcion que se llama cuando se rompe
                      fnclose;  // Funcion que se llama al cerrar
           int        reconecta;   // 0 No se reconecta en perdida 1 se reconecta
           int        numrecon;    // Numero de reconexiones solo si reconecta es 1
           servidorsocks *servidor;// Puntero al servidor solo si conexiones tipo server
           CRITICAL_SECTION critsock;// Seccion critica interna del v10sock
           int        suspendida;  // 1 Thread de tratamiento suspendida 0 en marcha Se suspende el thread cuando se reciben mas caracteres que el buffer
                                   // y no se tratan
           void       *extradata;
         } v10socks;

//Lista de sockets para servidores
typedef struct LISTASOCKS {
         struct LISTASOCKS *next,*prev;
         v10socks   *valor;
} listasocks;
//Estructura de un servidor de sockets servidor
typedef struct SERVIDORSOCKS {
          SOCKET        soc;         // Socket servidor
          int           status;      // Estado del servidor
          int           port;        // Puerto de escucha
          HANDLE        threadopen;  // Thread de tratamiento de conexiones nuevas
          CRITICAL_SECTION critopen; // Seccion critica para evitar problemas de concurrencia
          listasocks    *listapend;  // Lista de conexiones recibidas pendientes de tratar
          int           nconpend;    // Numero de conexiones pendientes de tratar
          int           conservar;   // 0 Las conexiones las trata el programa cliente 1 las trata el propio servidor
          listasocks    *listaopen;  // Lista de conexiones abiertas que trata el servidor
          int           nconopen;    // Numero de conexiones abiertas
          int           tamrec;      // Tamaño de buffer de recepcion
          trigsocks  fnopen,      // Trigers que se pasan a los sockets hijo
                        fnreconecta,
                        fnread,
                        fnbreak,
                        fnclose;
} servidorsocks;

V10IMPORT servidorsocks *v10socknuevoservidor(char *servicio,int conservar,trigsocks fnopen,trigsocks fnreconecta,trigsocks fnread,
                             trigsocks fnbreak,trigsocks fnclose);
/*Crea un nuevo servidor socket
            servicio     nombre del servicio debe estar definido en services. o ser un valor numerico del numero de puerto
			conservar    Indica si el socket servidor ha de conservar la lista de conexiones o cada conexion se trata individualmente
			fnopen       Funcion que se llama cuando se abre la primera conexion
			fnreconecta  Funcion que se llama en cada reconexion.
			fnread       Funcion que se llama cada vez que el socket puede leer bytes.
			fnbreak      Funcion que se llama cuando se rompe una conexion (No se usa en la actualidad)
			fnclose      Funcion que se llama cada vez que se cierra una conexion
*/
V10IMPORT v10socks *v10sockdameconexion(servidorsocks *ns);
// Devuelve una conexion realizada a un servidor y la elimina de la lista de conexiones pendientes
V10IMPORT v10socks *v10socknuevocliente(char *host,char *service,int reconecta,int tamrec,trigsocks fnopen,trigsocks fnreconecta,
                       trigsocks fnread,trigsocks fnbreak,trigsocks fnclose);
/* Crea un nuevo socket cliente
        host        Nombre del host servidor o su direccion ip
		service     Nombre del servicio o su valor numerico
		reconecta   Indica si el socket ha de intentar reconectarse cuando pierda conexion con el servidor
		tamrec      Tamaño del buffer de recepción
		fnopen      Funcion que se llama cuando el cliente se conecta por primera vez al servidor
		fnreconecta Funcion que se llama en cada reconexion
		fnread      Funcion que llama en cada lectura
		fnbreak     Funcion que se llama cuando se pierde la conexion
		fnclose     Funcion que se llama cuando se cierra el socket
*/
V10IMPORT void v10socklibera(v10socks *p);
/* Libera la memoria asociada a un socket y lo cierra si es preciso */
V10IMPORT void v10sockcierraservidor(servidorsocks *servidor);
/* Cierra un socket servidor */
V10IMPORT int v10sockhaycar(v10socks *p);
/* Devuelve el numero de caracteres esperando en el buffer de recepcion de un socket */
V10IMPORT int v10socksigcar(v10socks *p);
//Devuelve el siguiente caracter en la cola de recepcion y lo elimina de la cola 
V10IMPORT int v10sockread(v10socks *p,char *buffer,int len);
//Lee len bytes de un socket en buffer, devuelve el numero de bytes leidos 
V10IMPORT char *v10sockgets(char *donde,int n,v10socks *p);
//Lee una linea entera de un socket, espera hasta que se reciba el \n
V10IMPORT int v10sockescribe(v10socks *p,void *buffer,int tam);
//Escribe tam bytes de buffer en un socket, devuelve el numero de bytes escritos
V10IMPORT int v10sockencola(v10socks *p,int ch);
//Escribe un byte en socket
V10IMPORT int v10sockencolac(v10socks *p,char *cadena);
//Escribe una cadena terminada en \0 en socket (El \0 no se escribe
V10IMPORT int vv10sockprintf(v10socks *p,char *format,va_list arg);
//Escribe en un socket formateado como vprintf
V10IMPORT int v10sockprintf(v10socks *p,char *format,...);
//Escribe en un socket formateado como printf
V10IMPORT int v10socklisto(v10socks *p);
//Devuelve 1 si el socket esta listo para lectura/escritura 0 en caso contrario
V10IMPORT void v10socknuggle(v10socks *p,int on);
//Pone o quita el protocolo nuggle de un socket
V10IMPORT void v10sockopt(v10socks *p,int level,int opcion,char *valor,int len);
//Llama al la funcion de socker setsockopt
V10IMPORT char *v10sockpintadir(SOCKADDR *origen,char *donde);
//Devuelve el donde la direccion indicada por SOCKADDR escrita en formato canonico xxx.xxx.xxx.xxx
V10IMPORT char *v10sockpintaorigen(v10socks *p,char *donde);
//Devuelve el donde la direccion origen del socket escrita en formato canonico xxx.xxx.xxx.xxx
V10IMPORT char *v10sockpintadestino(v10socks *p,char *donde);
//Devuelve el donde la direccion destino del socket escrita en formato canonico xxx.xxx.xxx.xxx

//Funciones definidas en V10VISUALIZA.C
V10IMPORT servidorsocks *arrancaserverlog(char *puerto);
V10IMPORT servidorsocks *arrancaserverpantalla(char *puerto);
#ifndef __LINUX__
//Funciones definidas en V10OLE.C
// use this flag when adding arguments to indicate that the arg
// contents should NOT automatically be freed/released.
#define DISPARG_NOFREEVARIANT 0x01
#define V10IDISPATCH 30

#define DISP_FREEARGS 0x01
#define DISP_NOSHOWEXCEPTIONS 0x02
#define MAXOLECADENA 4000
V10IMPORT void ClearVariant(VARIANTARG *pvarg);
V10IMPORT void ReleaseVariant(VARIANTARG *pvarg);
V10IMPORT void ClearAllArgs(void);
V10IMPORT void AddArgumentCommon(char *lpszArgName, WORD wFlags, VARTYPE vt);
V10IMPORT BOOL AddArgumentDispatch(char *lpszArgName, WORD wFlags, IDispatch * pdisp);
V10IMPORT BOOL AddArgumentInt2(char *lpszArgName, int i);
V10IMPORT BOOL AddArgumentInt4(char *lpszArgName, int i);
V10IMPORT BOOL AddArgumentDouble(char *lpszArgName, double d);
V10IMPORT BOOL AddArgumentarray(char *lpszArgName, SAFEARRAY *psa);
V10IMPORT BOOL AddArgumentString(char *lpszArgName, WORD wFlags, char *cadena);
V10IMPORT BOOL AddArgumentBool(char *lpszArgName, BOOL b);
V10IMPORT BOOL Invoke(IDispatch *pdisp, char *funcion, VARIANTARG * pvargReturn,WORD wInvokeAction,WORD wFlags);
V10IMPORT void variant2string(VARIANTARG *pvarg,char *donde);
V10IMPORT double variant2double(VARIANTARG *pvarg);
V10IMPORT int invocametodoex(IDispatch *id,char *funcion,VARIANTARG *resul,short op,va_list arg);
V10IMPORT int invocametodo(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT int getproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT int putproperty(IDispatch *id,char *funcion,VARIANTARG *resul,...);
V10IMPORT void liberaidispatch(IDispatch *id);
V10IMPORT void finole(void);
V10IMPORT IDispatch *startole(char *nombre,int reusar);

//Funciones definidas en V10EXCEL.C
#define xlWorksheet -4167
#define xl3DColumn -4100
#define xlRows 1
#define MAXLRANGO  20
V10IMPORT int setvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor);
V10IMPORT int setvalorarray(IDispatch *pdispWs, char *lpszRef, SAFEARRAY *psa);
V10IMPORT int getvalorstring(IDispatch *pdispWs, char *lpszRef, char *valor);
V10IMPORT int getvalorarray(IDispatch *pdispWs, char *lpszRef,VARIANTARG  *valor);
V10IMPORT int getvalorvararg(IDispatch *pdispWs, char *lpszRef,VARIANTARG *ret);
V10IMPORT int gettipo(IDispatch *pdispWs, char *lpszRef);
V10IMPORT void pasadirexcel(int col,int fila, char *cadena);
V10IMPORT void pasarangoexcel(int colori,int filaori,int coldest,int filadest, char *cadena);
V10IMPORT IDispatch *damerangoexcel(IDispatch *hoja,int colori,int filaori,int coldest,int filadest);
V10IMPORT void visibleexcel(IDispatch *id,BOOL visible);
V10IMPORT void salvaexcel(IDispatch *wb,char *nombre);
V10IMPORT int cargaexcel(IDispatch *id,IDispatch **wb,IDispatch **hoja,char *nombre);
V10IMPORT IDispatch *anadehoja(IDispatch *wb,int after,char *plantilla);
V10IMPORT int numhojas(IDispatch *wb);
#endif

//Funciones definidas en V10ENTORNOC
V10IMPORT char *STDnombreordenador(void);
V10IMPORT void traduceentorno(char *cadena, char *destino); 

//Funciones definidas en V10BUFFER.C
//Leen de un buffer un tipo y eliminan lo leido del buffer.
V10IMPORT int BUFFERCONSP;

V10IMPORT double buffer2double(char *cadena,int lon,int dec,int sep);
//si separador vale 1 el punto decimal viene en la cadena, en caso contrario se supone
V10IMPORT long buffer2long(char *cadena,int lon);
V10IMPORT void buffer2cadena(char *cadena,char *donde,int lon);
V10IMPORT v10dates buffer2fecha(char *cadena,int tipo);
V10IMPORT void buffer2hora(char *cadena,char *donde);


#define MAXHASH 50

#ifndef __LINUX__
//Funciones definidas en V10ENCRIPTA.C
#include "wincrypt.h"


#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

V10IMPORT int damehash(char *origen,char *hash);
V10IMPORT int compruebahash(char *origen,char *hash);
V10IMPORT HCRYPTKEY dameclave(char *pass);
V10IMPORT int genfirma(HCRYPTKEY keysesion,char *priv,char *pub);
V10IMPORT int encriptasesion(HCRYPTKEY hkey,char *cadena,char *destino);
V10IMPORT int desencriptasesion(HCRYPTKEY hkey,char *cadena,char *destino);
V10IMPORT int recodificafirma(char *oldpwd,char *newpwd,char *cpriv);
V10IMPORT HCRYPTKEY dameclavepublica(char *pub);
V10IMPORT HCRYPTKEY dameclaveprivada(HCRYPTKEY hkey,char *priv);
V10IMPORT int firmadatosh(HCRYPTKEY hpriv,char *cadena,char *destino);
V10IMPORT int firmadatos(HCRYPTKEY hpriv,char *cadena,char *destino);
V10IMPORT int verificafirmah(HCRYPTKEY hpub,char *cadena,char *firma);
V10IMPORT int verificafirma(HCRYPTKEY hpub,char *cadena,char *firma);

#endif
V10IMPORT int servervisu;

#ifdef __cplusplus
}
#endif


#endif
