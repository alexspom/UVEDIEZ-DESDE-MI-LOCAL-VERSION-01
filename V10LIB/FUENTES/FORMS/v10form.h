/*
* Módulo : V10FORM.H
* Objeto:  Include generico de los forms V10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#ifndef __V10FORM
#define __V10FORM

#include "v10ora.h"
#include "v10db.h"
#include "v10sockssl.h"
V10ORAIMPORT  int actualizasid;
V10ORAIMPORT int ENTERQ;
extern void (*funcxls)(char *);
extern char v10wwwuser[32];
extern char rutaxls[MAXPATH];


#define DESPLAZA 10500

#define NIVEL_EXTERNO  0
#define NIVEL_FORM     1
#define NIVEL_BLOQUE   2
#define NIVEL_REGISTRO 3
#define NIVEL_CAMPO    4

#define FORMNORMAL   10  // Colores de registro normal
#define FORMRESAL    11  // Colores de registro resaltado
#define FORMFUERA    12  // Colores de registro de bloque no seleccionado
#define FORMIMPAR    13  // Colores de registro impar
#define FORMRESALNE  14  // Colores de registro resaltado no enter
#define FORMFUERANE  15  // Colores de registro de bloque no seleccionado no enter
#define FORMIMPARNE  16  // Colores de registro de bloque no seleccionado impar no enter
#define FORMPARNE    17  // Colores de registro de bloque no seleccionado impar no enter


/* Numero de indicadores que se almacenan al final del campo
   1 resultado de triger de comprobacion
   2 Indica si el campo ha sido scaneado o no
   3 Indica numero de decimales del campo 
   4 Indica formato del campo (tipo cadena)
   5 Indica longitud en pantalla del campo
   6 Indica campo entrable o no
   7 Indica campo visible o no
*/
#define NUMINDCAMPO   12
#define CINDERROR     0
#define CINDSCAN      1
#define CINDDEC       2
#define CINDFORMATO   3
#define CINDLPAN      4
#define CINDENTER     5
#define CINDNOINPUT   6
#define CINDINVISIBLE 7
#define CINDNOUPDATE  8
#define CINDCOLOR     9
#define CINDAUTOENTER 10
#define CINDOLD       11


#define FAILURE       1
#define SUCCESS       0
#define IGNORAR       2

#define MAXFCURSORES 200  // Máximo número de cursores definibles en un bloque
#define MAXFTECLAS   30  // Máximo número de trigers a nivel tecla definibles en un bloque
#define MAXBLOQUES   40  // Máximo número de bloques
#define MAXPARAM     200  // Máximo número de parametros en un triger
#define MAXFTRIGERS  200  // Máximo número de trigers definibles
#define MAXOPMENUS   50  // Máximo número de opciones de menú
#define MAXBOTONES   100  // Máximo número de botones en una pantalla
#define MAXBOTONERAS 50  // Máximo número de botoneras en una pantalla
#define MAXSTATS  5   // Máximo número de gráficos por bloque de datos
#define MAXTABS 20

// Definicion de tipos de form WINDOWS/WEB, TELNET O INTERFASE
#define FWINDOWS   0
#define FTELNET    1
#define FINTERFASE 2
/* Tipos de parametros a un ftriger */
#define PARAMCADENA  1
#define PARAMTRIGER  2

#define MAXAJAX		10
#define MAXCOMPHTML 10

/*Si el nombre de cursor en los parametros del triger comienza por un simbolo
  especial se moficia su comportamiento estos simbolos son:

    -  Inviente el sentido del cursor (Si falla devuelve SUCCESS EN caso contrario FAILURE
    $  Devuelve ignore esto es aborta con error pero no saca mensaje.
    @  Si falla el cursor no ejecuta ninguno mas y devuelve SUCCESS.
    +  Devuelve siempre SUCCESS.
    &  No se trata de un cursor sino de una funci¢n
    %  Saca mensaje pero no devuelve error.
    !  Saca pregunta.
*/

#define CINVERSO    1
#define CIGNORE     2
#define CSOLOMEN    4
#define CTERMINA    8
#define CSUCCESS   16
#define CPREGUNTA  32
#define CFUNCION   64
#define CDEBUG    128


#define PPREINSERT    0 
#define PPOSTINSERT   1 
#define PPREUPDATE    2 
#define PPOSTUPDATE   3 
#define PPREDELETE    4 
#define PPOSTDELETE   5 
#define PPREQUERY     6 
#define PPOSTQUERY    7 
#define PFINQUERY     8 
#define PPREREGISTRO  9 
#define PPOSTREGISTRO 10
#define PPREBLOQUE    11
#define PPOSTBLOQUE   12
#define PPREFORM      13
#define PPOSTFORM     14
#define PPRECOMMIT    15
#define PPOSTCOMMIT   16
#define PPREROLLBACK  17
#define PPOSTROLLBACK 18
#define PPOSTCHANGE   19
#define PPREFIELD     20
#define PPOSTFIELD    21
#define PPREPINTA     22
#define PPOSTPINTA    23
#define PONPINTA      24
#define WEBEVENTO	  25
#define PCONTEXTUAL   26


#define CAMPOSEXTRA 5
#define MAXMSGV10 2048
#define WM_LIBERABLOQUE (WM_USER+0)


struct BLOQUESTRUCT;
struct FORMSTRUCT;
//Definicion de un triger form
typedef struct FTRIGERS {
              char *nombre;      // Nombre del triger
              char **param;      // Array de punteros a los parametros del triger
              int  *tipoparam;   // Array con los tipos de cada parametro
              int  nparam;       // Numero de parametros
              char *msg;         // Puntero a un mensaje en caso de que el triger devuelva error (Normalmente puntero a un parametro)
              long opciones;     // Array de bits con las opciones definidas arriba
              int (*fun)(struct BLOQUESTRUCT *,struct FTRIGERS *f); // Funcion C que ejecuta el triger
              struct BLOQUESTRUCT *b;  // Bloque al que esta asociado el triger
              int protegido; // Indica si el triger se puede ejecutar o no
            } ftrigers;

//(3i) 
typedef struct {
	ftrigers *onclick,
			 *onrightclick,
			 *oncenterclick,
			 *onmouseover,
			 *onmouseout,
			 *ondbclick,
			 *onmousemove;
} fWebeventos;

typedef struct {
	int activo;
	char *valor_false;
	char *valor_true;
} checkboxes;	

typedef struct {
  char *select;
  int   posselect;	
} selectcombolists;

typedef struct {
  int 	activo; // 1 Activo, 0 No activo
  char 	*opc[MAXOPMENUS]; // opciones posibles
  int 	nopc;	           // número de opciones
  selectcombolists s[MAXOPMENUS];  // select para extraer datos para la lista 
  int nselects;  // número de selects en la lista
  int index;	 // elemento actualmente seleccionado en la lista
  int regpag;
  int multiple;
  int readonly;
} comboxlists;

//Definicion de una tecla del form
typedef struct {
           int t;                // Código de la tecla
           ftrigers *trig;       // Triger que ejecuta
		   ftrigers *trigpre;    // Triger que se ejecuta al pulsar la tecla (antes de acción por defecto o redefinida)
		   ftrigers *trigpost;   // Triger que se ejecuta al pulsar la tecla (después de acción por defecto o redefinida)
           struct BLOQUESTRUCT *b; // Bloque al que esta asociada
         } fteclas;

// frames dentro del bloque
typedef struct {
		int posx; // en píxeles
		int posy;
		int lonx;
		int lony;
		char nombre[MAXPATH];
		char includecss[MAXCADENA];	// meter en el campo el estilo indicado aquí
		int posinix,posfinx,posiniy,posfiny;
		int estado; // 0 no inciado, 1 encontrada esquina superior izq, 2 encontrada esquina superior derecha => agrup. de campos
		            // 3 encontrada esquina inferior izq. , 4 encontrada esquina inferior derecha => completado frame
	} fframes;

// posicionamiento web en píxeles
typedef struct {
		int posx; // en píxeled
		int posy;
		int lonx;
		int lony;
	} fvipixeles;

typedef struct {
         char *nombre;
         int posx;
         int lonx;
         int posy;
         int lony;
         int protegido;
} formtabs;

//Definicion de un campo del form
typedef struct {
               char     nombre[MAXNOMBREV10]; // Nombre del campo
               char     nvirtual[MAXNOMBREV10]; // Nombre del campo en la tabla padre (Solo para campos virtuales)
               int      off;               // Offset del valor dentro del buffer del bloque
               int      lon;               // Longitud del campo en el buffer
               int      lvar;              // Longitud del campo en pantalla
               int      tipo;              // Tipo del campo V10
               int      format;            // Formato indica si debe llevar puntos de miles y si el caracter decimal es , o .
               int      dec;               // Numero de decimales
               int      tabla,             // 0 auxiliar 1 campo de tabla
                        virtual,           // Indica si el campo es solo un puntero a un campo del bloque padre
                        oculto,            // Campo no presentado en pantalla
                        enter,             // Entrable o no
                        noinput,           // Entrable o no
                        autoenter,         // Pasa al siguiente campo al rellenar completamente sobre todo usado en radios
                        scan,              // Solo en radios permite usar el scanner
                        nscan,             // Indica numero de codigos de barras ya leidos en el campo
                        autotransmit,      // Solo en radios al terminar de leer con scannner autotransmite al host
                        capitaliza,        // Capitalizacion 0 cualquiera FORMATOUPPER solo mayusculas FORMATOLOWER solo minusculas
                        nopref;            // No prefija el campo con el nombre de la tabla al hacer query
               int      noupdate,          // No permite enter en campos de registros antiguos
                        invisible;         // No presenta el campo aunque este visible en pantalla
               char     *traducible;        // Indica el tag de traduccion si NULL no se traduce
               char     *tooltip;          // Puntero a una cadena que contiene el tooltip del campo
               ftrigers *funtooltip;       // Triger que presenta el tooltip del campo
               char     *prefijo;          // Prefijo del campo en select
               v10inputs *v;               // Ventana de input asociada
               ftrigers *change,           // Triger que se ejecuta despues de cada cambio (detectado)
                        *pref,             // Triger que se ejecuta antes de posicionar el cursor en el campo
                        *postf,            // Triger que se ejecuta al abandonar el cursor el campo
                        *prepinta,         // Triger que se ejecuta antes de presentar el campo
                        *postpinta,        // Triger que se ejecuta despues de presentar el campo
                        *onpinta,          // Triger que se ejecuta en lugar de presentar el campo
                        *convfrombd,       // Triger que convierte el campo al salir de la base de datos
                        *conv2bd,          // Triger que convierte el campo para meter en base de datos
                        *contextual;       // Triger que implementa el menu contextual
               fteclas  *teclas;           // Array de trigers tecla asociados al campo
               int       nteclas;          // Numero de teclas asociados al campo
	           fWebeventos feventos;	   // trigers asociados a eventos Web
	           checkboxes *checkbox;       // Indica si es un checkbox
	           comboxlists combox; 
	           char	*titulo;
	           char *where;
               void *datoconv;             //Puntero donde se almacena el dato extraido de la base de datos para posibles conversiones
               struct BLOQUESTRUCT *b;     // Puntero al bloque en el que esta definido el campo
               struct FORMSTRUCT  *f;
			   fvipixeles vipx;
			   char includecss[MAXCADENA];	// meter en el campo el estilo indicado aquí
			   char estilocss[MAXPATH];		// clase css a poner en el estilo del campo
			   int regpag;
               int fichero;
               char nombrefijo[MAXNOMBREV10];
               formtabs *ftab;
              } fcampos;
//Estructura de botones del forms
typedef struct {
    char *nombre;  // Nombre del boton
	char *grupo;
    int posx,        // Posicion X si es -1 boton visible solo activable desde botonera
        posy,        // Posicion Y
        lonx,        // Longitud del boton
        lony;        // Alto del boton
    char *texto; // Texto del boton
    char *image;     // Fichero con el bitmap del boton
	char *tooltip; // Tooltip asociado al boton
    int tecla;     // Tecla que ha de ejecutar
	char includecss[MAXPATH];	// meter en el campo el estilo indicado aquí
	char estilocss[MAXPATH];		// clase css a poner en el estilo del campo
	int oculto;
	int disabled;
} fbotones;
// Estructura de botonera del forms
typedef struct {
    char *nombre;  //Nombre de la botonera
    int  posx,       // Posicion X de la botonera
         posy,       // Posicion Y de la botonera
         lonx,       // Longitud de la botonera si 0 suma de las longitudes de los botones
         lony;       // Alto de la botonera si 0 maximo de alto de botones
    int  numbotones; // Numero de botones en la botonera
    fbotones **b;  // Array de punteros a los botones
} fbotoneras;

typedef struct {
	char *nombre;
	int posx;
	int posy;
	int lonx;
	int lony;
	int enmarcado;
} fstats;

// componente AJAX del bloque
typedef struct {
	char *id;
	char *objetojs;
	char *tipo; // (C)ursor, (F)unción o (Q)uery.
	char *modulo; // módulo DLL en el que se encuentar la función, si procede
	char *nombre; // nombre de la función o query 
	char *params; // parámetros de la función
	double  frecuencia; // intervalo en segundos entre invocaciones consecutivas a este objeto AJAX.
	                 // -1, solo se invoca una vez
    int frecuenciaint;
    v10horas ultimaeje;
    struct BLOQUESTRUCT *b;
} v10ajax;

// componente HTML del bloque
typedef struct {
	char *id;
	char *tipo; // (F)unción o (Q)uery.
	char *modulo; // módulo DLL en el que se encuentar la función, si procede
	char *nombre; // nombre de la función o query 
	char *params; // parámetros de la función
	int visible; // 0 oculto, 1 visible
} v10comphtml;

// Estructura de cursores FORMS
typedef struct {
                    char nombre[MAXNOMBREV10];     // Nombre del cursor
                    v10cursors *cur;            // Cursor asociado si esta analizado
                    char *sql;                  // Sentencia SQL del cursor solo util si todavia no esta analizado
                    struct BLOQUESTRUCT *b;     // Puntero al bloque en el que esta definido el cursor
                  } fcursores;
// Estructura de un bloque del FORMS
typedef struct BLOQUESTRUCT {
            char   fichero[MAXPATH];    // Nombre del fichero de definicion
            char   nombre[MAXNOMBREV10];   // Tabla principal del bloque
            char   *ayuda,              // Clave para acceder a la ayuda ONLINE
                   *online;             // Cadena de ayuda online (Dos ultimas lineas de la pantalla)
            struct BLOQUESTRUCT *padre; // Puntero al bloque padre
			int    regpadre;            // Registro del bloque padre del que extraigo los datos
            fcampos *c;                 // Array de campos del bloque
            int  ncamp;             // Numero de campos en array
            FILE *fbuffer,              // Fichero con los registros leidos, se guarda el buffer real y el leido de la BD
                  *fdelete;             // Fichero con los registro borrados.
            char *fname,                // Nombre del fichero de registros leidos.
                 *fndelete;             // Nombre del fichero con registros borrados.
            char *buffer,               // Buffer en memoria con el registro actual (contiene valores actuales y leidos de BD)
                 *ant;                  // Buffer con el registro actual antes de editar.
            char *bufuquery;            // Buffer de la ultima query generada
            unsigned long tamano;       // Tamaño de un registro
            v10dialogs vi;                     // Puntero a una estructura dialog 
            virtsels *s;                // Puntero a un grid 
            char *where;                // Cadena de where por defecto
            char *orderby;              // Orderby por defecto
            char *groupby;              // Group by por defecto
            char *having;               // Having por defecto
            char *extraselect;          // Cadena que se añade a la select antes del FROM normalmente para extraer constantes
            v10cursors *insert,         // Cursor que hace el insert de un registro
                       *delete,         // Cursor que hace el delete de un registro
                       *update,         // Cursor que hace el update de un registro
                       *select,         // Cursor de select de la pantalla
                       *count,          // Cursor que realiza el count de registro seleccionados en una pantalla
                       *lock,           // Cursor que bloquea un registro (SELECT ... FOR UPDATE)
                       *reload;         // Cursor que recarga el resitro en pantalla de la BD
            long       total;           // Numero total de registros ya extraidos en bloque
            int        enterquery;      // 0 en modo normal 1 en modo enterquery
            int        enquery;         // 0 una query en curso 1 sin query en curso
            int        quedan;          // 0 Se ha extraido el ultimo registro 1 en caso contrario (O no se sabe)
            int        regpag;          // Numero de registros visibles en pantalla simultaneamente
            int        modif;           // 0 Ningun registro del bloque ha sido modificado 1 algun registro modificado
            int        noinsert,        // 1 No se permite insert 1 se permite (Por defecto 1 a menos que soloquery)
                       noorains,        // 1 Se permite insert y se realiza insert a ORACLE 0 solo se ejecutan los trigers preinsert y postinsert
                       nooradel,        // 1 Se permite delete y se realiza insert a ORACLE 0 solo se ejecutan los trigers predelete y postdelete
                       noupdate,        // 1 Se permite update 0 si no se permite update
                       nodelete,        // 1 Se permite delete 0 si no
                       nocommit,        // 1 Se permite commit 0 no
                       sicommit,        // 1 Se fuerza que se elija entre commit o rollback aunque no se halla modificado
                       noquery,         // 1 no se permite query 0 se permite
                       nolock,          // 1 No se bloquean los registro aunque se halla modificado
                       aquery,          // 1 Query automatica al entrar y al detectar que no hay query (Por ejemplo al pulsar F5 para limpiar pantalla)
                       tquery,          // 1 Se extraen todos los registros al hacer query 0 se extraen solo los registros cuando halla que presentar
                       pquery,          // 1 Se hace query nada mas entrar en la pantalla pero no al limpiar pantalla
                       soloquery,       // La select no se genera hay que escribirla explicitamente no se permite insert.
                       noinput,         // No se permite input en ningun campo
                       noenter,         // No se permite posicionar en el bloque
                       invisible,
					   capitaliza,
                       norowid;         // Indica si ha de recuperar el rowid de la tabla principal
            fcursores  *fcur;           // Array de cursores del bloque
            int        ncur;            // Numero de cursores del bloque
            ftrigers   *ftimeout;       // Puntero a un triger de timeout
            long       timeout;         // Tiempo de timeout en 1/100 Sg.
            ftrigers   *fpreinsert,     // Triger que se ejecuta antes de hacer insert
                       *fpostinsert,    // Triger que se ejecuta despues de hacer un insert
                       *fpreupdate,     // Triger que se ejecuta antes de hacer un update a un registro
                       *fpostupdate,    // Triger que se ejecuta despues de hacer un update
                       *fpredelete,     // Triger que se ejecuta antes de hacer un delete
                       *fpostdelete,    // Triger que se ejecuta despues de hacer el delete
                       *fprequery,      // Triger que se ejecuta antes de ejecutar el cursor del query
                       *fpostquery,     // Triger que se ejecuta despues de extraer un registro del query
                       *ffinquery,      // Triger que se ejecuta despues de extraer el ultimo registro de la query
                       *fpreregistro,   // Triger que se ejecuta antes de posicionarse en un registro (Ojo el registro ya esta en memoria)
                       *fpostregistro,  // Triger que se ejecuta al salir de un registro
                       *fprebloque,     // Triger que se ejecuta al posicionarse en un bloque
                       *fpostbloque,    // Triger que se ejecuta al abandonar un bloque
                       *fprecommit,     // Triger que se ejecuta antes de hacer commit en un bloque
                       *fpostcommit,    // Triger que se ejecuta despues de haber realizado todos los insert update y delete de un bloque pero antes de commit fisico
                       *fprerollback,   // Triger que se ejecuta antes de hacer rollback de un bloque
                       *fpostrollback,  // Triger que se ejecuta despues de hacer el roolback de un bloque
                       *fprepinta,      // Triger que se ejecuta antes de presentar un registro
                       *fpostpinta,     // Triger que se ejecuta despues de presentar un registro
                       *fonpinta,       // Triger que se ejecuta en luger de presentar un registro
                       *contextual;     // Triger que presenta el menu contextual del bloque
         int           resaltado;       // Toma el valor 0 antes de imprimir un registro que no tiene el cursor y 1 antes de imprimir uno que tiene el cursor para que lo usen los trigers
         fteclas       *teclas;         // Array de trigers de teclas definidos en el bloque
         int           nteclas;         // Numero de trigers en el array anterior
         struct FORMSTRUCT  *form;      // Puntero al forms que contiene el bloque
         ftrigers   **ftriger;          // Array de trigers definidos para el form (NO SE USA ACTUALMENTE)
         int        ntrigers;           // Numero de trigers en el array anterior
         fbotones   *fb;                // Array de botones
         int numbotones;                // Numero de botones en el array 
         fbotoneras *fbot;              // Array de botoneras
         int numbotoneras;              // Numero de botones en el array		 
		 fWebeventos feventos;			// trigers asociados a eventos Web
		 char color[MAXNOMBREV10];
		 fvipixeles vipx;				// posicionamiento del bloque en píxeles
		 fframes *frames;				// frames en el bloque de datos, cardados dinámicamente, buscando caracteres de pintado
		 int nbframes;
		 fframes *framesfile;			// frames en el bloque de datos, cargados con sentencia WFRAMES		 
		 int nbframesfile;
		 int wregpag;					// número de regpag para versión web
		 int pxcol;						// número de píxeles por columna
		 int pxfila;					// número de píxeles por fila
		 int visiblescroll;				// si las barras de desplazamiento están visibles
		 int wtitulos;					// en bloques multiregistros, si se muestra los títulos como <THEAD> de la tabla
         int  wtipomarco;					// tipo de marco del bloque de datos, 0 NORMAL
		 char includeficherocss[MAXPATH];	// fichero de estilos CSS para el bloque
		 char includetdcss[MAXPATH];		//  estilos CSS para la tabla del bloque		 
		 char includecss[MAXPATH];		//  estilos CSS para el bloque
		 char includehtml[MAXCADENA];		// código HTML a incrustar para el bloque
		 char includeficherohtml[MAXPATH];		// fichero de código HTML a incrustar para el bloque
		 int wplegado;					// cargado desde la pantalla. si el bloque se puede plegar o desplegar. 0 ignorar, 1 plegado, 2 desplegado	
		 int wtemplegado;               // estado actual del bloque, 1 plegado, 0 no 
		 fstats *stats;                  // gráficas estadísticas
		 int nbstats;
		 char htmlalert[MAXPATH];
		 char htmlconfirm[MAXPATH];
		 int sidebaroculto;
		 // se encola código JS o HTML, y cuando se envía la sgte página HTML se flashea		 
		 char bufferhtml[MAXCADENA];
		 // tratamiento de objetos AJAX
         v10ajax *ajax;
         int ajaxactivo;
         v10sockssls *ajaxsock;
		 int nbajax;
		 // tratamiento de componentes WEB
		 v10comphtml *comphtml;
		 int nbcomphtml;		 
         formtabs *ftab;
         int nformtabs;
         int maxlontabx;
         int maxlontaby;
} bloques;

typedef struct FORMSTRUCT {
          bloques  *b[MAXBLOQUES];      // Array con punteros a bloques del forms
          char     nombre[MAXPATH];   // Nombre del forms
          unsigned nbloques;            // Numero de bloques del forms
          fcampos  *c;                  // Array de campos definidos a nivel FORMS
          unsigned ncamp;               // Numero de campos del array
          char     *buffer,
                   *ant;                // Buffer con los valores de los campos
          char *bufuquery;              // Buffer de la ultima query generada */
          unsigned long tam;            // Tamaño del buffer
          int      act;                 // Numero del bloque en el que esta el cursor
          int      nivel;               // 0 FORM 1 BLOQUE 2 REGISTRO 3 CAMPO
          int      term;                // Numero del terminal que tiene asignado el form solo para radio
          int      validar;             // Variable interna para decidir si validar los trigers al salir de un form
          int      modif;               // 0 Ningun bloque modificado 1 Algun bloque modificado
          ftrigers *precommit,          // Triger que se ejecuta antes de realizar commit en ningun bloque
                   *postcommit,         // Triger que se ejecuta despues de ejecutar commit en todos los bloques y antes del commit fisico
                   *prerollback,        // Triger que se ejecuta antes de hacer rollback
                   *postrollback,       // Triger que se ejecuta despues de hace rollback
                   *preform,            // Triger que se ejecuta antes de ejecutar el form
                   *postform;           // Triger que se ejecuta antes de descargar el form
          int      tipotriger;          // Tipo del ultimo triger ejecutado
          bloques  *berror;             // Bloque en el que se produjo el último error
          bloques  *binput;             // Bloque en el que se ejecuto el ultimo triger
          ftrigers *terror;             // Ultimo triger que se ejecuto
          fcampos  *cerror,             // Campo en el que se produjo el último error
                   *cinput;             // Campo en el que se ejecuto el último triger
          unsigned nupdate,             // Numero de registros updateados en el ultimo commit
                   ninsert,             // Numero de registros insertados en el ultimo commit
                   ndelete;             // Numero de registros borrados en el ultimo commit
          int      oraerr;              // Ultimo error oracle
          int      formerr;             // Ultimo error form
          windows  wmensaje;            // Ventana de mensajes form
          char     *copiamensaje;       // Puntero a memoria en la que se guarda lo que habia bajo mensaje
          int      sucio;               // Indicador de si la ventana de mensajes esta escrita
          int      preguntar;           // 1 Si hay que preguntar por cambios 0 en caso contrario
          int      tipo;                // Indica el tipo de form analizado 0 pantalla 1 radio
          void     (*mensaje)(struct FORMSTRUCT *f,char *cadena); // Puntero a funcion que procesa los mensajes de error (En radios se modifica)
          void     *extraform;          // Puntero a datos utilizable por el usuario
 		  char includeficherocss[MAXPATH];	// fichero de estilos CSS para el form
	 	  char includecss[MAXPATH];		//  estilos CSS para el form
		  char includehtml[MAXCADENA];		// código HTML a incrustar para el bloque
		  char includeficherohtml[MAXPATH];		// fichero de código HTML a incrustar para el bloque		        
	} forms;


// Estructuras para tratar los menus ZOOM
typedef struct {
          char *opcion;    // Nombre de la opcion
          ftrigers *ft;    // Triger que se ejecuta al seleccionar la opcion
        } opcionesmenu;

typedef struct {
         opcionesmenu *op;  // Array de opciones de menu
         int nopciones;     // Numero de opciones en el array
         bloques *b;        // Bloque al que esta asociado en zoom
         char *titulo;      // Titulo del zoom
       } formenus;


/* Estructura del buffer de un registro
     CABECERA (registro tipo cabregs)
     Datos Un array con los datos seguidos de un byte con el codigo de error
           devuelto por el triger postchange y otro byte indicando el metodo de lectura 0 teclado 1 scan
*/

typedef struct {        /* Cabecera de un registro en forms indica si el registro ha sido */
         int modif,     /* Modificado */
             antiguo,   /* Ha sido extraido de la base de datos */
             borrado,   /* Ha sido eliminado */
             lock,      /* La fila esta bloqueada por form */
             updated;   /* La fila ha sido modificada por otro usuario */
        } cabregs;

#define CABECERA(b) ((cabregs *)((b)->buffer))  /* Macro que accede a la cabecera de un registro */
#define CABANT(b) ((cabregs *)((b)->ant))
#define FORM(b) ((forms *)((b)->form))

#define damecon() GetCurrentProcessId()


//Funciones definidas en V10TRIGERAUX.C
V10ORAIMPORT int formsuena;
V10ORAIMPORT ftrigers *declaratriger(char *nombre,int (*fun)(bloques *b,ftrigers *ft),char *msg);
V10ORAIMPORT void liberatrigermsg(ftrigers *f);
V10ORAIMPORT void liberatriger(ftrigers *f);
V10ORAIMPORT ftrigers *duplicatriger(bloques *b,ftrigers *source);
V10ORAIMPORT ftrigers *dametriger(char *nombre);
V10ORAIMPORT ftrigers *cambiafuntriger(char *nombre,void *fun);
V10ORAIMPORT void wmensajeform(bloques *b,char *msg,...);
V10ORAIMPORT int wconfirmaform(bloques *b,char *msg);
V10ORAIMPORT int resultadotriger(bloques *b,int ret,long opcion,char *msg);
V10ORAIMPORT int ejecutaftriger(bloques *b,int tipo,ftrigers *f,fcampos *c);
V10ORAIMPORT int ejecutapostchange(bloques *b);

//Funciones definidas en V10FORCAMPOS.C
V10ORAIMPORT int esnulo(void *var,int tipo);
V10ORAIMPORT int damecampo(bloques *b,char *nombre);
V10ORAIMPORT int damecamposeguro(bloques *b,char *nombre);
V10ORAIMPORT void *direccampo(bloques *b,int camp);
V10ORAIMPORT void *direclockcampo(bloques *b,int camp);
V10ORAIMPORT void *direcantcampo(bloques *b,int camp);
V10ORAIMPORT void *direcuquerycampo(bloques *b,int camp);
V10ORAIMPORT void *direccampoptr(bloques *b,fcampos *c);
V10ORAIMPORT void *existecampo(bloques *b,char *nombre);
V10ORAIMPORT void *direcncampo(bloques *b,char *nombre);
V10ORAIMPORT int esnuloregistro(bloques *b);
V10ORAIMPORT int entrablebloque(bloques *b);
V10ORAIMPORT int damecampoform(forms *f,char *nombre);
V10ORAIMPORT void recuperacampo(bloques *b,fcampos *c,void *donde);
V10ORAIMPORT void copiacampo(bloques *b,fcampos *c,void *donde);
V10ORAIMPORT void *salvacampo(bloques *b,fcampos *c);
V10ORAIMPORT int *indicadorcampo(bloques *b,fcampos *c,int numind);
V10ORAIMPORT int dameindcampo(bloques *b,fcampos *c,char *indicador);
V10ORAIMPORT int *FERROR(bloques *b,fcampos *c);
V10ORAIMPORT int *FSCAN(bloques *b,fcampos *c);
V10ORAIMPORT int comparacampo(bloques *b,fcampos *c,void *donde);
V10ORAIMPORT int compararegistrolock(bloques *b);
V10ORAIMPORT int compararegistro(bloques *b);
V10ORAIMPORT int numeroindicadorcampo(char *nombre);
V10ORAIMPORT int damebase(char *nombre,char *base);
V10ORAIMPORT char *direccampoind(bloques *b,int ncamp,int indicador);
V10ORAIMPORT int validocampo(bloques *b,fcampos *c);
V10ORAIMPORT void liberacampo(fcampos *c);

//Funciones defindias en V10FORBLOQUE.C
V10ORAIMPORT char ultimoerrorbloque[MAXCADENA];

V10ORAIMPORT int damenumbloque(bloques *b);
V10ORAIMPORT char  *dameultimoerrorbloque(void); 
V10ORAIMPORT void ponultimoerrorbloque(char *formato,...);
V10ORAIMPORT bloques *creabloque();
V10ORAIMPORT bloques *damebloque(forms *f,char *nombre);
V10ORAIMPORT int asignacolorbloque(bloques *b,char *color);
V10ORAIMPORT int poncolorbloque(bloques *b,char *color);
V10ORAIMPORT fcampos *primerinvalido(bloques *b);
V10ORAIMPORT int validobloque(bloques *b,ftrigers *ft);
V10ORAIMPORT int borraregistro(bloques *b,ftrigers *ft);
V10ORAIMPORT int borrabloque(bloques *b, ftrigers *ft);
V10ORAIMPORT int countquery(bloques *b, ftrigers *ft);
V10ORAIMPORT void liberabloque(bloques *b);

//Funciones defindas en V10BOTON.C
V10ORAIMPORT fbotones *buscaboton(char *nombre);
V10ORAIMPORT int duplicaboton(char *nombre,fbotones *b);
V10ORAIMPORT void declaraboton(char *nombre,int posx,int posy,int lonx,int lony,char *texto,char *image,int tec);
V10ORAIMPORT fbotoneras *buscabotonera(char *nombre);
V10ORAIMPORT void declarabotonera(char *nombre,int posx,int posy,int lonx,int lony,...);
V10ORAIMPORT int duplicabotonera(char *nombre,fbotoneras *b);
V10ORAIMPORT fbotones *damebotonbloque(bloques *b,char *nombre);

//Funciones definidas en V10FORCURSOR.C
V10ORAIMPORT fcursores *buscafcursor(bloques *b,char *nombre);
V10ORAIMPORT int describebloque(bloques *b,v10cursors *lc);
V10ORAIMPORT int conviertefromdb(bloques *b,v10cursors *lc);
V10ORAIMPORT int convierte2db(bloques *b,v10cursors *lc);
V10ORAIMPORT v10cursors *bindbloque(bloques *b,char *sql,char *nombre);
V10ORAIMPORT v10cursors *bindquery(bloques *b,char *sql,char *nombre);
V10ORAIMPORT int describebloque(bloques *b, v10cursors *lc);
V10ORAIMPORT int ejecutafcursor(bloques *b,char *nombre);
V10ORAIMPORT int fetchfcursor(bloques *b,char *nombre);
V10ORAIMPORT long procesadasfcursor(bloques *b,char *nombre);
V10ORAIMPORT void liberafcursor(bloques *b,char *nombre);

//Funciones definidas en V10FORPARSEAUX.C
V10ORAIMPORT int eszoom;
V10ORAIMPORT int defcapitaliza;
V10ORAIMPORT char *(*extraparser)(bloques *b,char *funcion,char *param);
V10ORAIMPORT char *(*damecaracextracampo)(fcampos *campo);
V10ORAIMPORT char *(*damecaracextrabloque)(forms *f,bloques *b, int paso);
V10ORAIMPORT int (*damedefaulttabla)(bloques *b);
V10ORAIMPORT int (*funcionproteccion)(char *cadena);
V10ORAIMPORT int (*funcionparsecampo)(bloques *b,fcampos *c);
V10ORAIMPORT int (*funcionparsebloque)(bloques *b);
V10ORAIMPORT int (*funcionparsetecla)(bloques *b,fteclas *f,int protegido);
V10ORAIMPORT int (*funcionparsezoom)(formenus *m,opcionesmenu *op,int protegido);
V10ORAIMPORT ftrigers *defineteclaformdef(int mitecla,char *ntriger);
V10ORAIMPORT void anadeparamtriger(ftrigers *ft,...);
V10ORAIMPORT void damepostab(bloques *b,int x,int y,int *posx,int *posy,formtabs **ftab);
V10ORAIMPORT forms *leeformcadena(char *nombre,char *cadena,int tipo);
V10ORAIMPORT forms *leeform(char *nombre,char *opciones);
V10ORAIMPORT forms *leeformtelnet(char *nombre,char *opciones);
V10ORAIMPORT forms *leeforminter(char *nombre,char *opciones);
V10ORAIMPORT formenus *leemenu(bloques *b,char *nombre);
V10ORAIMPORT ftrigers *dametrigerdll(char *libreria,char *funcion);

//Funciones definidas en V10FORCONTEXT.C
V10ORAIMPORT void liberaforcontext(formenus*f);
V10ORAIMPORT int STDpresentamenucontex(formenus *f);
V10ORAIMPORT int fleemenucontextual(bloques *b,ftrigers *ft);

//Funciones definidas en V10FORVARIABLES.C
V10ORAIMPORT int bcampo2aex(bloques *b,char *ncampo,char *tex,int convierte,int formato);
V10ORAIMPORT int bcampo2a(bloques *b,char *ncampo,char *tex,int convierte);
V10ORAIMPORT int a2bcampo(bloques *b,char *ncampo,char *tex);
V10ORAIMPORT int sustituyevariables(bloques *b,char *origen,char *destino);
V10ORAIMPORT int sustituyevariablessc(bloques *b,char *origen,char *destino);
V10ORAIMPORT void asignavariablesext(bloques *b,char *linea,int err);
V10ORAIMPORT void asignavariables(bloques *b,char *linea);

//Funciones definidas en V10TEMPORAL.C

V10ORAIMPORT char DIRTEMP[MAXPATH];
V10ORAIMPORT int FORMCON;

V10ORAIMPORT void cierraficheroaux(bloques *b);
V10ORAIMPORT void reabreficheroaux(bloques *b);
V10ORAIMPORT void abreficheroaux(bloques *b);
V10ORAIMPORT void pordefectoregistro(bloques *b);
V10ORAIMPORT int insertaregistropos(bloques *b,long pos);
V10ORAIMPORT int insertaregistro(bloques *b);
V10ORAIMPORT void grabareg(bloques *b,int pos);
V10ORAIMPORT int grabaregistro(bloques *b,int pos);
V10ORAIMPORT int leeregistroi(bloques *b,int i);
V10ORAIMPORT int marcadelete(bloques *b);

//Funciones definidas en V10FORFORM.C
V10ORAIMPORT forms *formglobal;
V10ORAIMPORT int protegidoform;

V10ORAIMPORT int limpiaform(forms *f,ftrigers *ft);
V10ORAIMPORT int rollbackform(forms *f,ftrigers *ft);
V10ORAIMPORT int commitform(forms *f, ftrigers *ft);
V10ORAIMPORT int mirasimodif(forms *f);
V10ORAIMPORT void liberaform(forms *f);
V10ORAIMPORT int teclaform(int ret);
V10ORAIMPORT void cargaform(char *nombre,char *opciones);
V10ORAIMPORT void initform(void);
V10ORAIMPORT int STDcommitsino(forms *f);

//Funciones definidas en V10FORCOMMIT.C

V10ORAIMPORT int commitbloque(bloques *b);
V10ORAIMPORT int terminacommitbloque(bloques *b);
V10ORAIMPORT int terminarollbackbloque(bloques *b);

//Funciones definidas en V10FORMMSG
V10ORAIMPORT void STDformerror(forms *f,char *msg);
V10ORAIMPORT void STDforminfo(forms *f);
V10ORAIMPORT void STDmensajeform(forms *f,char *mensaje,...);
V10ORAIMPORT void STDlimpiamensaje(forms *f);

//Funciones definidas en V10FORGENERA.C
V10ORAIMPORT void gensolowhere(bloques *b, char *ptro, int haywhere);
V10ORAIMPORT void genwhere(bloques *b,char *ptro,int haywhere);
V10ORAIMPORT int genselect(bloques *b);
V10ORAIMPORT int gencount(bloques *b);
V10ORAIMPORT void geninsert(bloques *b);
V10ORAIMPORT int genupdate(bloques *b);
V10ORAIMPORT void gendelete(bloques *b);
V10ORAIMPORT void genlock(bloques *b);
V10ORAIMPORT void genreload(bloques *b);

//Funciones definidas en V10FORSEL.C
V10ORAIMPORT int numtimeoutform;

V10ORAIMPORT void reajustapagina(v10dialogs *vi,void *dato);
V10ORAIMPORT void STDpintapaginabloque(virtsels *s,int resaltado);
V10ORAIMPORT int selectpagina(bloques *b, ftrigers *ft);
V10ORAIMPORT int procesateclabloque(bloques *b,int ret);
V10ORAIMPORT int procesapreteclabloque(bloques *b,int ret);
V10ORAIMPORT int procesapostteclabloque(bloques *b,int ret);
V10ORAIMPORT int procesaposttecla(int ret);
V10ORAIMPORT int deleteregistro(bloques *b, ftrigers *ft);
V10ORAIMPORT int STDinsertregistro(bloques *b, ftrigers *ft);
V10ORAIMPORT int copiaregistro(bloques *b, ftrigers *ft);
V10ORAIMPORT int finputregistro(bloques *b);
V10ORAIMPORT int teclapaginabloque(virtsels *s);
V10ORAIMPORT int paginabloque(bloques *b);
V10ORAIMPORT int presentabloque(bloques *b,int query);
V10ORAIMPORT int STDreposratonform(forms *f);
V10ORAIMPORT char *dametooltipcampo(bloques *b,fcampos *c,char *donde);
V10ORAIMPORT int finputform(forms *f);

//Funciones definidas en V10FORDIALOG.C
V10ORAIMPORT void recargadefectos(bloques *b,fcampos *c);
V10ORAIMPORT void preparaenter(bloques *b);
V10ORAIMPORT int enterq(bloques *b);
V10ORAIMPORT void llactualizabloque(bloques *b);
V10ORAIMPORT void STDactualizabloque(bloques *b);
V10ORAIMPORT void STDactualizabloquebis(bloques *b);
V10ORAIMPORT int procesateclacampo(bloques *b,fcampos *c,int ret);
V10ORAIMPORT int finputcampo(bloques *b);

V10ORAIMPORT void (*muestrapantalla)(void);
V10ORAIMPORT int (*editwhere)(char *textowhere,char *textoorder,char *textohaving,char *titulowhere);
V10ORAIMPORT int (*selwhere)(char **opciones,int primera,int x,int y);

V10ORAIMPORT int (*reinicia)(char *cadena,int concepto);
//Funciones definidas en V10FORPIDEVAR.C
V10ORAIMPORT void pidevwhere(char *where);

//Funciones definidas en V10FORTRIGER.C
V10ORAIMPORT int dameparametro(bloques *b,ftrigers *ft,int npar,int tipopar,void *var);
V10ORAIMPORT int fejecutaparam(bloques *b,ftrigers *f,int numpar,long *opcion);
int STDabrelink(char *link);
V10ORAIMPORT int reiniciaform(char *param,void *dato);
V10ORAIMPORT void inittriger();

#ifndef __LINUX__
//Funciones definidas en V10FOROLE.C
V10ORAIMPORT void presentaxlsweb(bloques *b,IDispatch *id,IDispatch *wb);
V10ORAIMPORT int reusaexcel;
V10ORAIMPORT void initolefrm(void);
V10ORAIMPORT void confexcel2fichero(char *_user,int _puerto, char *_rutaxls, void (* mifunc)(char *) );
#endif
V10ORAIMPORT void initasfrm(void);
//Funciones definidas en v10forcvs.c
V10ORAIMPORT void initcsvfrm(void);
V10ORAIMPORT void confexcel2fichero(char *_user,int _puerto, char *_rutaxls, void (* mifunc)(char *) );


//Funciones definidas en V10FORMPDF.C
V10ORAIMPORT void dameficheropdf(char *informe,char *dondeconruta,char *dondesinruta);
V10ORAIMPORT void ponmensajepdf(char *fichero);
V10ORAIMPORT void confpdf2fichero(char *_user,int _puerto, char *_rutapdf, void (* mifunc)(char *) );

//Funciones definidas en V10FORMENU.C
typedef struct {
	  char *nombreop; /* Nombre de la opción */
	  int  tipo;      /* Tipo de la opción */
	  char *param;    /* Parámetros si ha lugar */
	} opmenus;

typedef struct {
	 char    *titulo; /* Título del menú */
	 opmenus *op;     /* Puntero al array de "numop" opciones "opmenus" */
     int     numop;   /* Número de opciones de ese menú */
	 void *html_menu;
     char *fichero; /* Fichero del menu*/
} menus;

typedef struct {
         char nombre[MAXNOMBREV10];
         int  (*fun)(char *param,void *dato);
         void *dato;
       } menutrigers;
typedef struct {
	     char opcion;
		 void (*fun)(char *param,void *dato);
		 void *dato;
} defopciones;
V10ORAIMPORT void declaramenutriger(char *nombre,int (*fun)(char *param,void *dato),void *dato);
V10ORAIMPORT void declaraopciontriger(char opcion,void (*fun)(char *param,void *dato),void *dato);
V10ORAIMPORT void STDpresentamenu(menus *m);
V10ORAIMPORT int elige(virtsels *s);
V10ORAIMPORT int eligeop(opmenus *op);
V10ORAIMPORT void presentamenuform(char *nombre,char *cadena,char *opciones);
V10ORAIMPORT void editamenus(void);

//Funciones definidas en V10FOREJECUTA.C
V10ORAIMPORT int fcejecutaform(bloques *b,char *pantalla,char *opciones,char *where,char *order,char *asigna,char *devuelve,char *titulo,char *aquery);
V10ORAIMPORT int fejecutaform(bloques *b,ftrigers *f);



/* Funciones definidas en V10EXPORT */
#define LNUMERO 18
#define MAXLCAMPO 100
#define MAXBCAMPOS 50
#define EXPORT      0
#define IMPORT      1
#define NONE  0
#define TRIM  1
#define HNONE   0
#define HIMPORT 1
#define MAXLCAMPO 100
#define MAXBCAMPOS 50
#define EXPORT      0
#define IMPORT      1

V10ORAIMPORT int COMPRESS;
V10ORAIMPORT int HEADERS;
V10ORAIMPORT int VERBOSE;
V10ORAIMPORT char EXSEPARADOR;
V10ORAIMPORT unsigned COMMITPOINT;
V10ORAIMPORT unsigned NOINDICES;
V10ORAIMPORT unsigned TAMBUFFER;
V10ORAIMPORT unsigned ANALISIS;
V10ORAIMPORT unsigned LOGGING;
V10ORAIMPORT char NOMBRETABLA[];
V10ORAIMPORT unsigned INFORMA;

V10ORAIMPORT long export(char *select,char *fich,char *tabla,char *param,unsigned tambuffer);
V10ORAIMPORT long exporttabla(char *nombre,char *where,char *param,char *nfichero);
V10ORAIMPORT void exportuser(char *where,char *param);
V10ORAIMPORT void importuser(char **genconst);

/* Funciones definidas en V10IMPORT */

V10ORAIMPORT long recupera(char *nombre,unsigned tambuffer,char **genconst);

// Funciones definidas en v10lex.c
V10ORAIMPORT int creabuffercadena(char *cadena);

//Funciones definidas en V10FORSELTABLA.C
void initformseltabla(void);

//Funciones definidas en V10FORPUNTEROS.C
//Puntero utilizados para virtualizar el comportamiento del modo web
V10ORAIMPORT int(*presentamenucontex)(void *f);
V10ORAIMPORT void(*presentamenu)(void *f);
V10ORAIMPORT int(*llbloquearegistroaux)(void *b);

V10ORAIMPORT void(*limpiamensaje)(void *f);
V10ORAIMPORT void(*formerror)(void *f, char *msg);
V10ORAIMPORT void(*forminfo)(void *f);
V10ORAIMPORT void(*mensajeform)(void *f, char *mensaje, ...);
V10ORAIMPORT void(*rellenadefault)(void);
V10ORAIMPORT void(*borraregistroaux)(void *b);
V10ORAIMPORT int(*commitsino)(void *f);
V10ORAIMPORT void(*actualizabloque)(void *b);
V10ORAIMPORT void(*frecalcpadreaux)(void *b, void *padre);
V10ORAIMPORT void(*fdesignacionaux)(void *b);
V10ORAIMPORT int(*insertregistro)(void *b, ftrigers *ft);
V10ORAIMPORT void(*cargahtmlconf)(void);
V10ORAIMPORT void(*resetencolados)(void);
V10ORAIMPORT int(*reposicionaregraton)(void *v);
V10ORAIMPORT int(*reposratonform)(void *f);
V10ORAIMPORT int(*finputregistroaux)(void *b);
V10ORAIMPORT void(*recuperatodosenter)(void *b);
V10ORAIMPORT void(*guardatodosenter)(void *b);
V10ORAIMPORT void(*fejecutaformaux)(void *b, void *f, int *ret);
V10ORAIMPORT char *(*damehostname)(void);
V10ORAIMPORT int(*pabrelink)(char *);
V10ORAIMPORT int(*pprocesaposttecla)(int);
V10ORAIMPORT int(*psemueveelraton)(bloques *b);

#endif