//Formatos de campos
#define FORMATOLOWER     1 //Todo minusculas
#define FORMATOUPPER     2 //Todo mayusculas
#define FORMATORAW       4 //Transforma en Hexa
#define FORMATONUM       8 //Fuerza que una cadena solo pueda contener digitos +/- .,
#define FORMATODATE     16 //Fuerza que una cadena solo pueda contener fechas
#define FORMATONULL    128 //Hace que una cadena no se represente
#define F4ANO            1 //Año con 4 digitos

#define V10INT      0  //Tipo entero nativo
#define V10UINT     1  //Unsigned int
#define V10SHORT    2 
#define V10USHORT   3
#define V10LONG     4
#define V10ULONG    5
#define V10FLOAT    6
#define V10DOUBLE   7
#define V10CHAR     8
#define V10BYTE     9
#define V10CADENA  10
#define V10FECHA   11  //Fecha en julinano
#define V10ENUM    12  //Tipo utilizado para los combo
#define V10HORA    13  //Hora en centesimas de segundo con decimales
#define V10DATE    14  //Tipo DATE de Oracle
#define V10RAW     15  //Tipo RAW de Oracle
#define V10WCADENA 16  //Unicode

V10IMPORT int tamv10tipo(int tipo,int lon);
//Devuelve la longitud en bytes de un tipo si es V10CADENA,V10DATE,V10RAW devuelve lon
V10IMPORT int esv10tiponum(int tipo);
//Devuelve 1 si es un tipo numerico 0 en caso contrario
V10IMPORT void v10tipo2a(void *dato,int tipo,int lvar,int formato,int dec,char *donde,int edit);
/*Pasa un tipo a ASCII
          dato    puntero al dato a representar.
		  tipo    tipo v10 del dato
		  lvar    longitud del dato
		  formato formato de representacion como or de los formatos definidos arriba.
		  dec     numero de decimales
		  donde   puntero a la zona de memoria donde ha de dejar la representacion
		  edit    indica si la representacion va a ser para editar (Formatea numeros a la izquierda
*/
V10IMPORT int a2v10tipo(void *dato,int tipo,int formato,int dec,char *donde);
/*Pasa de ascii a tipo v10
          dato    puntero al dato destino
		  tipo    tipov10 del dato
		  formato formato del campo
		  dec     decimales
		  donde   posicion de la cadena a transformar
*/
V10IMPORT int comparav10tipo(void *t1,void *t2,int tipo);
/* Devuelve -1,0 1 dependiendo que tipo sea mayor como strcmp */
V10IMPORT void copiav10tipo(void *t1,void *t2,int tipo,int lvar);
/* Copia un tipo v10 en otro */
V10IMPORT int esnulov10tipo(void *var,int tipo);
/* Devuelve 1 si el tipo es nulo. Una cadena con solo blancos se considera nula
   ojo los tipos numericos y fecha se consideran nulos si 0 */