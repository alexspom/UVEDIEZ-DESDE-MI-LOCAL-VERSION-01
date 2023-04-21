
extern int v10maxpxX,v10maxpxY;

/************************/
/*   V10wwwaborta.c	*/
/************************/

// Mensaje crítico para abortar ejecución aplicación 
void V10wwwerror(char *formato,va_list lista_param_variable,short salir);


/********************/
/*   V10wwwKey.c	*/
/********************/

// Tecla JavaScript (js) a ANSI
// k: código js tecla, ini/fin: rango de valores a recorrer en tabla traducción  
int v10_js2ansi(int k,int ini,int fin);

// Tecla en Evento Javascript (js) a Ansi
// ev: evento js.
// k: código js de la tecla 
int v10js2ansi(char *ev,int k);

// Tecla ANSI a su código Javascript (js) 
int v10ansi2js(int k);

// devuelve si tecla pulsada junta a la tecla k en javascript (js)
// kespecial: cptura tecla pulsada junto a k (SHIFT, ALT, CONTROL, .... )
char *v10comb(char *kespecial,int k);


/********************/
/*   V10wwwMisc.c	*/
/********************/

char *traduceutf8(char *cadena);

// Pixel x a posicion en carecteres
// px: coordenada pixel x
// widtpx: coordenada de un caracter em pixeles
//int v10px2x(int px,int widthpx);

// Posicion x en caracteres a pixel sin margen
//  x: coordenada x en caracteres
//  witdhpx: ancho de un caracter em pixeles
int v10x2pxsm(int x,double widthpx);

// Posicion y en caracteres a pixel sin margen
//  y: coordenada y en caracteres
//  heightpx: altura de un caracter em pixeles
int v10y2pxsm(int y,int heightpx);
// Posicion x en caracteres a pixel con margen
//  x: coordenada x en caracteres
//  witdhpx: ancho de un caracter em pixeles
int v10x2px(int x,double widthpx);

// Posicion y en caracteres a pixel con margen
//  y: coordenada y en caracteres
//  heightpx: altura de un caracter em pixeles
int v10y2px(int y,int heightpx);


// Fija resolución en píxeles
void v10ponresolucion(int x,int y);

// transforma coordenada en pixeles en funcion del ancho del caracter en pixel de la fuente en uso
int v10px2font(int px,int widthpx,double ptofont);


/* tratamientos cadenas html/ascii */
// convierte cadena Ascii a HTML
char *v10wwwoem2ansi(char *cad);

// trasnforma una cadena devuelta por un evento html a ansi 
char *v10evtoansi(char *chtml);

// sustituye caracteres ansi con acentos a su código html
void v10ansitohtml(char *cadena);

// elimina los recuadros de los literales de las pantallas, en oem
void delrecuadrooem(char *cadena);

// reemplaza caracteres 'c' por la cadena 'new_c',dentro de la cadena chtml
char *v10carespeciales(char *cad,char c,char *newc);
char *v10cadespeciales(char *chtml,char *cad,char *newcad);




