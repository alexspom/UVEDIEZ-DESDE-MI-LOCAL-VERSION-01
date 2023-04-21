/*
* Módulo : v10keys.H
* Objeto: Definicion de las teclas especiales
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#define back          8   /* Retroceso */
#define tab           9   /* Tabulador */
#define lf           10  /* Line feed */
#define cr           13  /* Retorno de carro */
#define esc          27  /* Escape */
#define cback       127 /* Control retroceso */
#define stab        271 /* Shift tabulador */
#define home        327 /* Home */
#define cuu         328 /* Cursor arriba */
#define pgup        329 /* Página arriba */
#define cui         331 /* Cursor izquierda */
#define cud         333 /* Cursor derecha */
#define end         335 /* End */
#define cua         336 /* Cursor abajo */
#define pgdn        337 /* Página abajo */
#define inse        338 /* Insert */
#define dele        339 /* Delete */
#define ccud        372 /* Control flecha derecha */
#define ccui        371 /* Control flecha izquierda */
#define cend        373 /* Control end */
#define cpgdn       374 /* Control p gina abajo */
#define chome       375 /* Control home */
#define cpgup       388 /* Control p gina arriba */
#define cinse      1010
#define cdele      1011
#define ccua       1012
#define ccuu       1013
#define sinse      1014
#define sdele      1015
#define scui       1016
#define scud       1017
#define scuu       1018
#define scua       1019
#define shome      1020
#define shend      1021
#define spgup      1022
#define spgdn      1023
#define MOUSEPOS   2000 /* Se ha pulsado uno de los botones del ratón */
#define MOUSEPOSD  2001 /* Se ha pulsado uno de los botones del ratón */
#define MOUSEPOSM  2002 /* Se ha pulsado uno de los botones del ratón */
#define MUEVERATON 2003
#define MOUSEPOSMV 2004 
#define copiatodo  2100
#define F(i)      (3100+(i)) /* Tecla de función i */
#define S_F(i)    (3120+(i)) /* Shift tecla de función i */
#define C_F(i)    (3140+(i)) /* Control tecla de función i */
#define A_F(i)    (3160+(i)) /* Alt Control tecla de función i */
#define CS_F(i)   (3180+(i)) /* Shift + Ctrl + tecla de función i */
#undef CTRL
#define CTRL(a)   (a-'A'+1)         /* Control cualquier letra */
#define ALT(a)    (alter[toupper(a)-'A']) /* Alt cualquier letra */
#define ALTN(x)   (378+x)  /* Alt y un número */
#define TECLATIMEOUT 3000


#define ESFUNC(tecla) ((tecla)<256?0:1)
    /* Devuelve 1 si es tecla especial y 0 si no. */



#define CTRL_BREAK 0xFFFF /* Es el código devuelto cuando se pulsa
                             Control_Break */


#define CLICK      1  /* Acción click */
#define DOBLECLICK 2  /* Doble click */

#define BOTONI     1  /* Boton izquierdo */
#define BOTOND     2  /* Boton derecho */
#define BOTONM     3  /* Boton central */


V10IMPORT int alter[50];  /* Array con los todos los codigos pertenecientes
                          a la combinación Alt y una letra. El primero
                          es el perteneciente a Alt-a y el último el de
                          Alt-z. */

V10IMPORT int ult_pul;  /* Variable global que almacena la última pulsación
                        procesada por la función tecla(). */

V10IMPORT int ins;  /* Variable global con el estado de insert. Si es
                     nula (ins==0) sobreescribe y si es no nula
                     (ins!=0) inserta. */
V10IMPORT unsigned long ttimeout;
                /* Tiempo que se debe esperar sin consumir procesador
                   Cuando se esta esperando una tecla */                     

V10IMPORT int (*triger_tecla_antes)();
     /* Puntero a una función que si es distinto de nulo provoca la
        ejecución de dicha función al comenzar la función tecla.
        Si dicha función devuelve 0 se ejecutar  tecla, pero si devuelve
        algo no nulo ese es el valor que devolver  la función tecla. */

V10IMPORT int (*triger_tecla_despues)(int);
     /* Puntero a una función que si es distinto de nulo provoca la
        ejecución de dicha función al finalizar la función tecla.
        Dicha función recibe la tecla procesada por la función tecla
        y devuelve otra tecla que se asume como la procesada por la
        tecla original. */



V10IMPORT int esperamensaje(int espera);
/* Detiene la ejecucion del programa hasta que pasen espera milisegundos o se reciba un mensaje de WINDOWS
   Los mensajes de WINDOWS pueden ser tecla, hay que repintar pantalla, caracter recibido por un puerto etc*/

V10IMPORT int hay_tecla(void);
         /* Función que devuelve 0 si no hay una tecla preparada en el
            buffer de teclas y el codigo de la tecla en caso de que
            haya alguna. La función mira primero en el buffer interno
            de la librería y si éste est  vacío mira en el buffer del
            teclado.En cualquiera de los dos casos no retira la tecla del
            buffer. */

V10IMPORT int hay_tecla_normal(void);
         /* Esta función actúa igual que hay_tecla() s¢lo que si hay
            tecla y tiene asignada alguna función, quita del buffer
            la tecla y ejecuta la función. */

V10IMPORT int hay_tecla_contimeout(void);
         /* Esta función actúa igual que hay_tecla() s¢lo que si no hay
            tecla y est  puesto el timeout teclado, comprueba si se
            consumi¢ el timeout y dispara el triger. */


V10IMPORT int hay_tecla_normalcontimeout(void);
         /* Esta función actúa igual que hay_tecla_normal() s¢lo que si
            no hay tecla y est  puesto el timeout teclado, comprueba si
            se consumi¢ el timeout y dispara el triger. */


V10IMPORT int STDtecla(void);
         /* Función que devuelve el c¢digo de la última tecla pulsada. Si
            es una tecla normal devuelve el c¢digo que le da el DOS, esto
            es, su c¢digo ASCII y si es una tecla de función especial, de-
            vuelve el codigo que le da el DOS, su scancode, aumentado en
            256. Si es una tecla o combinación de teclas que tenga asignada
            una función especial, nuestros función_trigers, realiza la
            función y espera otra tecla. */


V10IMPORT int STDpushtecla(int cual);
         /* Función que introduce la tecla cual en el buffer de
            teclado. Devuelve 0 si cabe en el buffer y -1 si el
            buffer est  lleno y no la almacena. LIFO*/

V10IMPORT int STDencolatecla(int cual);
         /* Función que introduce la tecla cual en el buffer de
            teclado. Devuelve 0 si cabe en el buffer y -1 si el
            buffer est  lleno y no la almacena. FIFO*/


V10IMPORT void vaciateclado(void);
         /* Función que vac¡a el buffer de teclado. Tanto el de la
            librer¡a como el del DOS. */


V10IMPORT void pontrigervivo(void *triger);
         /* Función que activa la ejecución de una función, triger,
	    ante cualquier espera de tecla, esto es, la función
	    triger se ejecutar  siempre que se llame a hay_tecla(). */

V10IMPORT void *dametrigervivo(void);


V10IMPORT void timeoutteclado(unsigned time,void *triger);
	 /* Función que dispara un triger con un timeout, esto es, una
	    función que se ejecuta cuando se lleva esperando por una
	    tecla m s del tiempo del timeout. time es el timeout en
	    centesimas de segundo y triger es el puntero a la función
	    a ejecutar. */


V10IMPORT void dametimeoutteclado(unsigned *time,void **triger);
	 /* Función que coloca en la dirección timeout y en la
	    dirección triger los contenidos del timeout y del
	    triger que se dispara tras el timeout. Estos valores
	    se asignan con la ayuda de la función timeout_teclado(). */


V10IMPORT int asignatecla(int key,void (*funcion)(int mikey));
	 /* Función para definir nuestros función_trigers. Asigna a un
	    c¢digo de teclas key una función función que se ejecutar 
	    cuando se pulse dicha tecla o combinación de teclas. A partir
	    de ese momento esa tecla o combinación queda reservada para la
	    función y no puede usarse para otro fin. Devuelve el número de
	    teclas asignadas hasta el momento. El m ximo de teclas asigna-
	    bles est  definido en el m¢dulo teclado.h en la definición
	    de MAX_ESPECIAL, actualmente est  a 10. */



V10IMPORT int alttecla(int a);
	 /* Esta función devuelve el c¢digo de la tecla que produce el
	    c¢digo a al pulsarla con Alt, o 0 si no es el c¢digo de
	    ninguna combinación Alt-letra. */

V10IMPORT int traducetecla(char *nombre);
     /* Traduce un nombre de tecla a su valor numerico trata:
	    CR, LF,ESC TAB CUA, CUU PGUP PGDN
		Fn  Teclas de funcion
		CFn Control tecla de funcion
		SFn Shift tecla de funcion
		AFn Alt tecla de funcion
		Al  Alt letra
	*/