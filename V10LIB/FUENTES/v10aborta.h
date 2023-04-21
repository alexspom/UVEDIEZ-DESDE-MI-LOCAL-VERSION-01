/*
* Módulo : V10ABORTA.H
* Objeto:  Define funciones para abortar un programa presentando mensaje de error
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
//Funcion que se ejecuta antes de ejecutar final
V10IMPORT void (*prefinal)(char *error);  
//Funcion que se ejecuta antes de ejecutar warning
V10IMPORT void (*prewarning)(char *error);
//Macro para abortar un programa y presentar un mensaje de error formateado segun printf
#define final(x) {pon_puntero_error(__FILE__,__LINE__); \
                  mifinal x;}
//Macro dar un aviso no fatal y presentar un mensaje de error formateado segun printf
#define warning(x) {pon_puntero_error(__FILE__,__LINE__); \
                    miwarning x;}

//Funciones definidas en V10ABORTA.C
V10IMPORT void pon_puntero_error(char *fichero,int linea);
//Funcion auxiliar para recoger el fichero y la linea en la que se produce un error
V10IMPORT void STDv10error(char *formato,va_list lista_param_variable,short salir);
//Funcion principal de presentacion de errores
V10IMPORT void mifinal(char *formato,...);
//Funcion auxiliar de la macro final
V10IMPORT void miwarning(char *formato,...);
//Funcion auxiliar de la macro warning