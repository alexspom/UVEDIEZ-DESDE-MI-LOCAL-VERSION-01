/*
* Módulo : V10INPUT.H
* Objeto:  Entrada de datos estandar V10
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/

//Estructura que soporta un campo de input en V10
typedef struct {
             void *dato;   //Dato sobre el que se realiza input
             windows *w;   //Ventana V10 que contiene la representacion del campo
             int tipo,     //Tipo de dato V10
                 posx,     //Columna en la ventana del campo
				 posy,     //Fila en la ventana del campo
				 lvar,     //Longitud real del dato
				 lpan,     //Longitud del dato en pantalla
                 seleccion,//Indica si el campo es un combo
                 pcar,     //Primer caracter de la representacion que se presenta util para scroll
                 formato,  //Formato del campo
				 dec,      //Numero de decimales
			     color,    //Numero de color del campo si 0 o -1 por defecto
                 desp;     //Desplazamiento util en radios
             int (*triger)(void *,void *); //Triger de validacion del input
             void *trigerdatos; //Punteros de usuario
             int vtriger;  //Indicador de si el triger ha validado el campo 
             int modif,    //Indica si el campo se ha modificado
				 activa,   //Indica si el campo ya tiene memoria asignada
				 enter,    //Entrable o no
                 noinput,  //Indica si el campo es modificable o no
                 autoenter,//Indica si el campo ha de hacer autoenter al rellenarse completamente
				 password, //Indica si el campo es password
				 invisible;//Indica si el campo es visible
             char **lista; //Lista de valores que puede tomar un combo
             void *ant;    //Valor anterior del campo
             void *def;    //Valor por defecto del campo
             int (*finput)(void *,int,int); //Funcion de input del campo si nulo funcion por defecto
             void (*fpresenta)(void *,int,int); //Funcion de presentacion del campo si nulo por defecto
             void *dinput; //Puntero de usuario
          } v10inputs;

//Indica si los menus de ultimos campos modificados estan activos
V10IMPORT int menulista_desactivado;
V10IMPORT int seveventana(v10inputs *v,int tx,int ty);
//Devuelve si el campo de input es visible en pantalla
V10IMPORT int input2a(v10inputs *v,char *tex,int edit);
//Pasa una ventana de input a ascii
V10IMPORT int a2input(v10inputs *v,char *tex);
//Pasa una cadena ascii a ventana de input
V10IMPORT int reposicionavraton(v10inputs *v,int tx,int ty);
//Reposiciona el campo por pulsacion de raton
V10IMPORT int tratascrollv(v10inputs *v,int tx,int ty);
//Trata scroll en un campo
V10IMPORT int llinput(v10inputs *v,int tx,int ty);
//Funcion de bajo nivel de input
V10IMPORT void STDlpresenta(v10inputs *v,int tx,int ty);
//Funcion de bajo nivel de presentacion de campo de input

//Funciones defindas en V10DIALOG.C
//Estructura de dialogo V10
typedef struct v10dialogs {
                windows w;         //Ventana V10 a la que esta asociada el dialogo
                int largo,         //Longitud logica del dialogo
					alto;          //Alto logico del dialogo
                v10inputs *prim,   //Primer campo de input
					      *ult,    //Ultimo campo de input
						  *act,    //Campo de input activo actualmente
						  *ultinp; //Ultimo campo en el que se ha realizado input
                int numinput;      //Numero de campos de input
                int despx,         //Desplazamiento horizontal del dialogo en la ventana V10
					despy;         //Desplazamiento vertical del dialogo en la ventana V10
                int modificado;    //Indica si algun campo del dialogo ha sido modificado
                int salir;         //Indica si se ha de salir del dialogo
                int marco;         //Tipo de marco de la ventana V10 que contiene el dialogo
                char *titulo;      //Titulo del dialogo
                tpixels *pantalla_debajo; //Variable para guadar lo que habia bajo el dialogo
                tpixels *contenido; //Contenido del dialogo sin los campos de input
                void  (*reajusta)(struct v10dialogs *,void *dato); //Funcion para reajustar el dialog ante scroll
                void  *reajdato;   //Puntero a datos de usuario
               } v10dialogs;

/*Macro para inicializar un dialogo
          v         Puntero al dialogo a inicializar
		  p         Pintado de la pantalla de dialogo
		  x1        Posicion horizontal del dialogo
		  y1        Posicion vertical del dialogo
		  num       Numero de la paleta de colores dentro del array defvent
*/
#define initdiaf(v,p,titul,x1,y1,num)  \
           (v)->largo=sizeof(p[0])-1;\
           (v)->alto=sizeof(p)/sizeof(p[0]);\
           initvf(&(v)->w,x1,y1,x1+(v)->largo-1,y1+(v)->alto-1,num);\
           interpretadialogo(v,(char *)p);\
           (v)->titulo=titul;
/*Macro para inicializar un dialogo
          v         Puntero al dialogo a inicializar
		  p         Pintado de la pantalla de dialogo
		  x1        Posicion horizontal del dialogo
		  y1        Posicion vertical del dialogo
		  color     Nombre de la paleta de colores dentro del array defvent
*/
#define initdian(v,p,titul,x1,y1,color)  \
           (v)->largo=sizeof(p[0])-1;\
           (v)->alto=sizeof(p)/sizeof(p[0]);\
           initvn(&(v)->w,x1,y1,x1+(v)->largo-1,y1+(v)->alto-1,color);\
           interpretadialogo(v,(char *)p);\
           (v)->titulo=titul;

V10IMPORT void initbloque(v10dialogs *v);
V10IMPORT void flechasdialog(v10dialogs *vi);
//Pone las flechas de desplazamiento en la ventana V10 que contiene el dialog
V10IMPORT void STDmuestradialog(v10dialogs *vi ,int guarda);
//Presenta un dialog y guarda el contenido de la pantalla del dialogo si guarda=1
V10IMPORT void vasignadialog(v10dialogs *vi ,va_list ap);
//Presenta un dialog y guarda el contenido de la pantalla del dialogo si guarda=1
V10IMPORT void pasignadialog(v10dialogs *vi ,void **ap);
//Asigna variables a un dialog
V10IMPORT void asignadialog(v10dialogs *vi,...);
//Asigna las variables indicadas por el numero indefinido de parametros terminados en NULL
V10IMPORT void liberadialog(v10dialogs *vi);
//Libera toda la memoria asignada a un dialog
V10IMPORT int enumeradialog(v10dialogs *vi,void *var,char **lista);
//Inicializa un combo de un dialog a los valores indicados por lista
V10IMPORT void entrabledialog(v10dialogs *vi,void *var,int permite);
//Pone un campo de input a entrable o no dentro de un dialogo
V10IMPORT void STDactualizadialog(v10dialogs *v);
//Actualiza las variables de un dialogo en pantalla
V10IMPORT void ajustaventana(v10dialogs *vi,v10inputs *v);
//Ajusta la ventana de un dialogo al realizar input
V10IMPORT int STDreposicionadialograton(v10dialogs *vi);
//Reposiciona el campo de input de un dialogo dependiendo de pulsaciones del raton
V10IMPORT int STDblinput(v10dialogs *v);
//Hace input del campo activo en un dialogo
V10IMPORT int dialoginput(v10dialogs *vi);
//Hace input de los campos de un dialogo
V10IMPORT int dialoginputpres(v10dialogs *vi);
//Hace input de los campos de un dialogo y lo presenta
V10IMPORT void posicionadialog(v10dialogs *vi,void *var);
//Posiciona el cursor en un campo de input de un dialogo
V10IMPORT int v10dialogsalir(void *a,v10dialogs *vi);
//Fuerza la salida de un dialogo
V10IMPORT void antinput(v10dialogs *vi);
//Posiciona el cursor en el campo de input anterior al actual en un dialogo
V10IMPORT void siginput(v10dialogs *vi);
//Posiciona el cursor en el campo siguiente al actual en un dialogo

//Funciones definidas en V10COMBO.C
int selecinp(v10inputs *v,int despx,int despy);
//Ejecuta input en un combo
void presinp(v10inputs *v,int despx,int despy);
//Presenta el valor de un combo

//Funciones definidas en V10INTDIALOG.C
V10IMPORT char *analizatokendia(char *token,char **donde,int *tipo,int *formato,int *dec,int *lon,int *lpan,int *password);
//Analiza un campo segun su presentacion estandar V10
V10IMPORT void interpretadialogo(v10dialogs *vi ,char *contenido);
//Analiza un dialogo completo a partir de un pintado