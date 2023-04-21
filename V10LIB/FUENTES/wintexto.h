/*
* Módulo : WINTEXTO.H
* Objeto: Gestiona ventanas de texto en windows
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

	 /* Definición del significado de las posiciones del array
            definido en paletas. paletas es una gama de colores
            definida como un array en el que los primeros nueve colores
            tienen un significado definido. */

#define CENUSO      0 /* Tinta en curso */
#define CNORMAL     1 /* Tinta normal */
#define CINPUTINAC  2 /* Tinta de un campo de input normal */
#define CINPUTACT   3 /* Tinta de un campo de input resaltada */
#define CNOENTER    4 /* Tinta de un campo de input resaltada */
#define CMARCA      5 /* Tinta de un campo de input marcado */
#define CMARCON     6 /* Tinta de marco normal */
#define CMARCOR     7 /* Tinta de marco resaltado */
#define CTITULON    8 /* Tinta de título normal */
#define CTITULOR    9 /* Tinta de título resaltado */

//Macros para determinar el ancho y el alto de una ventana
#define WANCHO(w) ((w)->x2-(w)->x1+1)
#define WALTO(w)  ((w)->y2-(w)->y1+1)

         /* Definición de los modos de debug de ventana */

#define WNORMAL  0 /* No hace caso de caracterrres de control */
#define WASCII   1
#define WCONTROL 2
#define WTTY     3

//Maximo numero de colores en la paleta de una ventana
#define MAXCOLVENTANA 31

//Maximo numero de paletas definidas para las ventanas
#define MAXVENT 200


	      /*  DEFINICION DE ESTRUCTURAS  */

//Paleta de una ventana
typedef struct {
	       colventanas t[MAXCOLVENTANA]; //Array con los colores definidos para una ventana
	       } paletas;

//Definicion de una paleta accesible por nombre
typedef struct {
	  char nombre[MAXNOMBREV10];
	  paletas t;
	 } defvents;
//Ventana V10
typedef struct {
          int x1,y1; //Esquina superior derecha
          int x2,y2; //Esquina inferior inquierda
          int cursorx,cursory; //Posicion actual del cursor
          paletas t; // Paleta de colores de la ventana
          int mododebug; //Modo de representacion de los caracteres
          HWND hwnd; //Handle windows de la ventana
          void *debajo; //Puntero a lo que hay debajo de la ventana
	    } windows;
	 /* 
		   mododebug=WNORMAL  normal
		   mododebug=WASCII   ascii
		   mododebug=WCONTROL control
		   mododebug=WTTY     tty
	 */

//Array con las paletas definidas
V10IMPORT defvents defvent[MAXVENT]; 


/* Funciones definidas en LLWINDOWS.C */

V10IMPORT void creaventana(char *titulo,windows *w,int x1,int y1,int x2,int y2,char *color);
// Crea una nueva ventana windows a partir de una ventana V10
V10IMPORT void liberaventana(windows *w);
//Libera una ventana windows asociada a una ventana V10
V10IMPORT void wset_cursor(HWND hwnd,int modo);
//Pone el modo del cursor en una ventana WINDOWS
V10IMPORT void wcurr_cursor(HWND hwnd,int *x,int *y);
//Devuelve la posicion del cursor en una ventana WINDOWS
V10IMPORT void wfgotoxy(HWND hwnd,int x,int y);
//Situa el cursor en una ventana windows
V10IMPORT void wcls(HWND hwnd,int x1,int y1,int x2,int y2,int color);
//Borra una ventana windows utilizando el color indicado
V10IMPORT int wplotext(HWND hwnd, int x, int y, int ch, int tinta, int papel, int invalida, extrawins *t);
V10IMPORT void wplot(HWND hwnd,int x,int y,int ch,int tinta,int papel);
//Pone un caracter con sus caracteristicas de color en una posicion de una ventana windows.
V10IMPORT int wscreen(HWND hwnd,int x ,int y);
//Devuelve el caracter en una posicion de una ventana windows.
V10IMPORT char *wimprime(HWND hwnd,int x,int y,int tinta,int papel,char *cadena);
//Escribe una cadena en una ventana WINDOWS en una posicion determinada y con un color
V10IMPORT char *wimprimep(HWND hwnd,int x,int y,int tinta,int papel,char *cadena,int desde,int numchars);
//Imprime parte de una cadena
V10IMPORT void whorizontal(HWND hwnd,int x,int y,int l,int tinta,int papel,int tipo);
//Dibuja una linea texto horizontal
V10IMPORT void wvertical(HWND hwnd,int x,int y,int l,int tinta,int papel,int tipo);
//Dibuja una linea texto vertical
V10IMPORT void wscrollu(HWND hwnd,int numlin,int x1,int y1,int x2,int y2,int papel);
//Hace scroll hacia arriba de una ventana un determinado numero de caracteres
V10IMPORT void wscrolld(HWND hwnd,int numlin,int x1,int y1,int x2,int y2,int papel);
//Hace scroll hacia abajo de una ventana un determinado numero de caracteres
V10IMPORT void wscrollr(HWND hwnd,int numcol,int x1,int y1,int x2,int y2,int papel);
//Hace scroll hacia la derecha de una ventana un determinado numero de caracteres
V10IMPORT void wscrolll(HWND hwnd,int numcol,int x1,int y1,int x2,int y2,int papel);
//Hace scroll hacia la izquierda de una ventana un determinado numero de caracteres
V10IMPORT void wmarco(HWND hwnd,int x1,int y1,int base,int altura,int tipo,int tmarco,int pmarco,int ttitulo,int ptitulo,char *titulo);
//Pinta un marco texto en una posicion, de un tamaño, color (tmarco,pmarco) y con un titulo
V10IMPORT void wsalvapantalla(HWND hwnd,void *p,int x1,int y1,int x2,int y2);
//Guarda en p el contenido (Caracteres y colores) de un rectangulo el usuario ha de proporcionar
//suficiente memoria
V10IMPORT void *wsalvapantallad(HWND hwnd,int x1,int y1,int x2,int y2);
//Devuelve un puntero a memoria obtenida con mallo que guarda el contenido de un rectangulo
V10IMPORT void wrecuperapantalla(HWND hwnd,void *p,int x1,int y1,int x2,int y2);
//Restaura el contenido de un rectangulo extrayendo la informacion de p
V10IMPORT void wrecuperapantallaansi(HWND hwnd,void *p,int x1,int y1,int x2,int y2);
V10IMPORT void wrecuperapantallad(HWND hwnd,int x1,int y1,int x2,int y2,void *donde);
//Restaura el contenido de un rectangulo y libera la memoria utilizada

/* Funciones definidas en WINMSG.C */
V10IMPORT extrawins *dameextrawin(HWND hwnd);
V10IMPORT void declarateclamenu(char *nombre,int mitecla);
V10IMPORT void creamenuclipboard(int x,int y,int copiar,int pegar);
long CALLBACK textproc(HWND hwnd,UINT message,WPARAM wParam,
							LPARAM lParam);
V10IMPORT int defaultprinter(char *nombre);
V10IMPORT HWND initprgex(HINSTANCE hinst,int cmdshow,char *titulo,int posx,int posy,
             int tamx,int tamy,
             int numcol,int numlin,DWORD estilo,DWORD estiloex,HWND padre,
             int anchof,int altof,char *font);
V10IMPORT HWND initprg(HINSTANCE hinst,int cmdshow,char *titulo,int posx,int posy,
             int tamx,int tamy,
             int numcol,int numlin,DWORD estilo,HWND padre,
             int anchof,int altof,char *font);
V10IMPORT void initapptxt(HINSTANCE hinst, HINSTANCE hprev,int cmdshow,char *titulo,
                int posx,int posy,int tamx,int tamy,int numcol,int numlin,
                DWORD estilo,DWORD estiloex,HWND padre,int anchof,int altof,
                char *nombrefont);
V10IMPORT void initv10lib(HINSTANCE hinst,HINSTANCE hprev);





//Funciones definidas en WINSIMU.C
V10IMPORT void presentacursor(HWND hwnd);
V10IMPORT void set_cursor(int modo);
V10IMPORT void curr_cursor(int *x,int *y);
V10IMPORT void STDfgotoxy(int x,int y);
V10IMPORT void cls(int x1,int y1,int x2,int y2,int color);
V10IMPORT void plot(int x,int y,int ch,int tinta,int papel);
V10IMPORT int screen(int x ,int y);
V10IMPORT char *imprime(int x,int y,int tinta,int papel,char *cadena);
V10IMPORT char *imprimep(int x,int y,int tinta,int papel,char *cadena,int desde,int numchars);
V10IMPORT void horizontal(int x,int y,int l,int tinta,int papel,int tipo);
V10IMPORT void vertical(int x,int y,int l,int tinta,int papel,int tipo);
V10IMPORT void scrollu(int numlin,int x1,int y1,int x2,int y2,int color);
V10IMPORT void scrolld(int numlin,int x1,int y1,int x2,int y2,int color);
V10IMPORT void scrollr(int numcol,int x1,int y1,int x2,int y2,int color);
V10IMPORT void scrolll(int numcol,int x1,int y1,int x2,int y2,int color);
V10IMPORT void marco(int x1,int y1,int base,int altura,int tipo,int tmarco,int pmarco,int ttitulo,int ptitulo,char *titulo);
V10IMPORT void salvapantalla(void *p,int x1,int y1,int x2,int y2);
V10IMPORT void *salvapantallad(int x1,int y1,int x2,int y2);
V10IMPORT void recuperapantalla(void *p,int x1,int y1,int x2,int y2);
V10IMPORT void recuperapantallaansi(void *p,int x1,int y1,int x2,int y2);
V10IMPORT void recuperapantallad(int x1,int y1,int x2,int y2,void *donde);
V10IMPORT void pintapantallav10(char *cadena);


	      /*  PROTOTIPOS DE FUNCIONES DEFINIDAS EN WINTEXTO.C */

V10IMPORT void initvt(windows *v,int x1,int y1,int x2,int y2,paletas *t);
	 /* Función que inicializa la ventana v con una estructura
        paletas t definida expl¡citamente por el usuario en
        su programa. Rellena los datos sobre el tama¤o de la ventana
	    y sitúa el cursor en la esquina superior izquierda. El debug
	    se inicializa seg£n se trate de MSDOS o UNIX. */


V10IMPORT void initvf(windows *v,int x1,int y1,int x2,int y2,int numero);
	 /* Función que inicializa la ventana v con el índice del
            array predefinido de gamas de colores defvent. El resto
            de la inicialización es igual que en initvt(). */

V10IMPORT int damepaleta(char *nombre);

V10IMPORT void initvn(windows *v,int x1,int y1,int x2,int y2,char *nombre);
	 /* Función que inicializa la ventana v a partir del nombre
	    de una gama de colores almacenada en el array defvent.
	    El resto de la inicialización es igual que en initvt(). */

V10IMPORT void winitvn(HWND hwnd,windows *v,int x1,int y1,int x2,int y2,char *nombre);
V10IMPORT void winitvt(HWND hwnd,windows *v,int x1,int y1,int x2,int y2,paletas *t);

V10IMPORT void usa_colores(char *nom_fichero);
         /* Función que lee del fichero fichero la matriz defvent.
            Seg£n el tipo de monitor toma nom_fichero.mon si detecta
            un monitor monocromo o nom_fichero.col si detecta un monitor
            en color. El fichero con la matriz puede ser creado o modificado
            con el programa colores.exe. */


V10IMPORT void salva_colores(char *nom_fichero);
	 /* Función que graba en el fichero fichero la matriz defvent.
	    Seg£n el tipo de monitor toma nom_fichero.mon si detecta
	    un monitor monocromo o nom_fichero.col si detecta un monitor
	    en color. El fichero con la matriz puede ser creado o modificado
	    con el programa colores.exe. */


V10IMPORT void clv(windows *v);
	 /* Función que borra el contenido de la ventana v y coloca
	    el cursor de la ventana en la esquina superior izquierda. */


V10IMPORT void escribe(windows *v,int ch);
	 /* Función que escribe el car cter ch en la ventana v en
	    la posición del cursor dentro de la ventana, actualizando
	    dicha posición. */


V10IMPORT void escribec(windows *v,char *cadena);
	 /* Función que escribe la cadena cadena en la ventana v a
	    partir de la posición del cursor dentro de la ventana.
	    Actualiza la posición de dicho cursor. */

V10IMPORT char *imprimev(windows *v,int x,int y,char *cadena);
	 /* Función que imprime la cadena cadena en la ventana v.
	    La imprime a partir de la columna x y la fila y de la
	    ventana. Devuelve el puntero a la propia cadena original. */


V10IMPORT char *imprimevp(windows *v,int x,int y,char *cadena,int desde,int numchars);
	 /* Función que imprime parcialmente la cadena cadena en la
	    ventana v. Imprime numchars caracteres de la cadena desde
	    la posición desde en la columna x y la fila y de la
	    ventana. Devuelve el puntero a la propia cadena original. */


V10IMPORT int vv10printf(windows *v,char *format,va_list arg);
V10IMPORT int v10printf(windows *v,char *format,...);
	 /* Función que hace un printf dentro de la ventana v.
	    Acepta, por tanto, cualquier formato que acepte la
	    función printf(). Devuelve el número de caracteres
	    escritos en la ventana. */


V10IMPORT void renmarca(windows *v,int tipo,char *titulo);
	 /* Función que pone un marco de tipo tipo con el t¡tulo
	    titulo a la ventana v sin borrarla. Los tipos
	    disponibles son:

		   tipo=0 - Barra doble vertical y horizontal.
		   tipo=1 Ä Barra sencilla vertical y horizontal.
		   tipo=2 Ä Barra doble vertical y sencilla horizontal.
		   tipo=3 - Barra sencilla vertical y doble horizontal.

	  Los colores son tomados de la gama de colores definida en
	  paletas. Adem s borra el contenido de la ventana. */

V10IMPORT void enmarca(windows *v,int tipo,char *titulo);
	 /* Función que act£a igual que renmarca pero adem s borra la
	    la ventana. */


V10IMPORT void scrollv(windows *v,int numlin);
	 /* Función que hace el scroll de numlin l¡neas de la
	    ventana v, hacia arriba si numlin es positivo y
	    hacia abajo si es negativo. Caso de ser numlin nulo
	    borra la ventana. */


V10IMPORT void scrollh(windows *v,int numcol);
	 /* Función que hace el scroll de numcol columnas de la
	    ventana v, hacia la derecha si numcol es positivo y
	    hacia la derecha si es negativo. Caso de ser numcol
	    nulo borra la ventana. */


V10IMPORT void salvav(windows *v,void *donde);
	 /* Salva la ventana v en la dirección apuntada por p.
	    Asume que se ha reservado previamente espacio para ella. */


V10IMPORT void *salvavd(windows *v);
	 /* Salva la ventana v en memoria din mica. La propia rutina
	    busca espacio para ella y guarda el contenido. Devuelve el
	    puntero al inicio de la zona de memoria donde ha guardado
	    la información de la ventana. */
V10IMPORT void *salvavdm(windows *v,int marco);
V10IMPORT void recuperavm(windows *v,void *donde,int marco);
V10IMPORT void recuperavdm(windows *v,void *donde,int marco);

V10IMPORT void recuperav(windows *v,void *donde);
	 /* Recupera en la ventana v la ventana almacenada en la
	    dirección apuntada por donde. Es la operación comple-
	    mentaria de salvav(). NO libera la memoria ocupada por
	    la ventana restaurada. */

V10IMPORT void recuperavd(windows *v,void *donde);
	 /* Recupera en la ventana v la ventana almacenada en la
	    dirección apuntada por donde. Es la operación comple-
	    mentaria de salvavd(). SI libera la memoria ocupada
	    por la ventana restaurada. */


V10IMPORT void pon_curf(windows *v);
	 /* Pone el cursor fisico del DOS en la misma posición en la
	    que se encuentra el cursor interno de la ventana v. */

V10IMPORT void pon_curv(windows *v,int cx,int cy);
	 /* Pone el cursor de la ventana en la posición determinada
	    por cx y cy. */

V10IMPORT void pos_curv(windows *v,int *cx,int *cy);
	 /* Coloca en las variables cx y cy la posicion actual
	    del cursor de la ventana. */


V10IMPORT void poncolorv(windows *v,int color);
	 /* Función que pone el color t[color] de la gama de colores
	    asociada a la ventana v como color de escritura, esto es,
	    copia a t[0] el color de t[color]. */


V10IMPORT void inviertew(windows *v);
	 /* Función que cambia la tinta y el papel normales de la ventana
	    v por la tinta y el papel resaltado de la gama asociada a
	    dicha ventana. */


V10IMPORT void inviertewm(windows *);
	 /* Función que cambia la tinta y el papel normales de la ventana
	    v por la tinta y el papel del marco dentro de la gama asociada
	    a dicha ventana. */


V10IMPORT void mensajev_color(windows *v,char *mensaje,int terminal);
	 /* Función que imprime la cadena mensaje centrada en l¡nea
	    m s inferior de la ventana v, en el color definido por
	    terminal que puede ser elegido de entre las posiciones
	    de paletas. */


V10IMPORT void mensajev(windows *v,char *mensaje);
	 /* Función que imprime la cadena mensaje centrada en l¡nea
	    m s inferior de la ventana v, usando el color designado
	    por la posición de paletas TTNORMAL. */


V10IMPORT void flechas(windows *v,long ini_limite,long fin_limite,long ini,long fin,short tipo_marco,short color);
         /* Función que gestiona la colocación de dos flechas en el margen
            derecho de la ventana v, dando por echo que est  enmarcada.
            Si ini es mayor que ini_limite coloca la flecha superior
            y si fin es menor que fin_limite coloca la flecha inferior.
            La función también precisa el tipo de marco elegido entre los
	    tipos de marcos soportados por la librería, y el color color
            de las flechas, este color se pasa como un índice a la estructura
            paletas asociada a la ventana v, y por tanto se puede
            pasar una de las posiciones de paletas. */
