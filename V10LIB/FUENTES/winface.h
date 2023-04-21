/*
* Módulo : WINFACE.H
* Objeto: Include para funciones windows bajo nivel
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#ifndef ESTILOV10
#define ESTILOV10   (WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL)
#endif
#define SINCURSOR     0
#define CURSORNORMAL  1
#define CURSORSOLIDO  2

//Numero del icono a asociar a la aplicacion
V10IMPORT int NUMEROICONO;
//Numero de columnas de la pantalla principal de la aplicacion
V10IMPORT unsigned COLUMNASPANTALLA;
//NUmero de lineas de la pantalla principal de la aplicacion
V10IMPORT unsigned LINEASPANTALLA;
//Modo en que se muestra la ventana principal
V10IMPORT int MODOSHOW;

//Estado del cursor
V10IMPORT int  statuscursor;
//Caracter utilizado como fondo al limpiar una ventana
V10IMPORT char charblanco;
//Indica si el titulo ha de ir centrado al enmarcar una ventana V10
V10IMPORT int centrar_titulo;

//Puntero a instancias de programa WINDOWS
V10IMPORT HINSTANCE v10hinst,v10hprev;
//Handle de la ventana principal del programa
V10IMPORT HWND hwnddefecto;
//Titulo de la ventana principal del programa.
V10IMPORT char TITULOVENTANA[];
//Definicion de los caracteres utilizados para enmarcar una ventana
#define SUPIZQ    0
#define SUPDER    1
#define INFIZQ    2
#define INFDER    3
#define BARRAVER  4
#define BARRAHOR  5
V10IMPORT char v10marco[6][5];

// Estructura del color en el que se pinta en pantalla
typedef struct {
            int tinta; //Color de escritura
            int papel; //Color de fondo
} colventanas;
//Estructura con un caracter representado en pantalla
typedef struct {
          char        ch; //Caracter
          colventanas c;  //Color con el que se pinta
} tpixels;

//Estructura con las variables extra que se guardan con cada ventana WINDOWS.
typedef struct {
        tpixels      *texto; //Contenido de la pantalla en formato 1 byte caracter int RGB de la la tinta int RGB del papel
        int          lineas,columnas; //Lineas y columnas de la ventana de texto
        int          cursorx,cursory; //Posicion del cursor
        int          origenx,origeny; //Origen de coordenadas en la ventana
        int          posx,posy; //Posicion de la ventana
        int          colordefecto; //Color por defecto de la escritura
        int          altofont,anchofont; //Alto y ancho del font utilizado por defecto
        int          modocursor; //Modo del cursor
        HDC          hdc;  //Handle al contexto WINDOWS de la ventana
        HFONT        hfont,hfontold; //Handle al font y uno al font antiguo para cambios de font
        LOGFONT      lfo;
        HBITMAP      hbitmap,hbitmapold; //Handle al bitmap de fondo y uno al altiguo para cambios de bitmap
        HDC          mdc;
      } extrawins;
//Estructura con las pulsaciones del raton      
typedef struct {
	      int winx,winy; // Posición del ratón en coordenadas windows 
          int boton;     // 1 Izquierdo 2 Centro 3 Derecho 
          int posx,posy; // Posición del ratón en caracteres 
          int action;    // 1 Click 2 Doble click 
          HWND hwnd;     //Handle de la ventana
       } mouseposs;
V10IMPORT mouseposs mousepos;       
       
//Estructura con las caracteristicas del tipo de letra de los mensajes
typedef struct {
	        int alto; //Alto de la letra
	        int ancho;//Ancho de la letra
	        char font[LF_FACESIZE];//Tipo de letra
} fontmensajes;

//Guarda el tipo de letra utilizado en los mensajes
V10IMPORT fontmensajes fontmensaje;
//1 Si se activa el menu de cerrar la ventana y el aspa
V10IMPORT int menucerrar;
//Color interpretado por la libreria como transparente que permite ver el bitmap de fondo
V10IMPORT colventanas COLORTRANSP;
//BMP que se utiliza de fondo de las ventanas
V10IMPORT char *V10BMP;
V10IMPORT void cambiafontdefecto(char *facename,int alto,int ancho);

