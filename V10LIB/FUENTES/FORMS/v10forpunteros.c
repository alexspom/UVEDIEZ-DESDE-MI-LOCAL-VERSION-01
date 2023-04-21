/*
* Módulo : V10FORPUNTEROS.C                                             
* Objeto:  Vritualizacion de funciones para multiples presentaciones
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 08-08-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

int ENTERQ=1;

void dummy(void)
{
   return;
}

int dummy1(void *a)
{
   return(0);
}

void dummy2(void *a)
{
   return;
}

void dummy4(char *a,void *b)
{
   return;
}


char *dummy3(void *a) {
   return NULL;
}


void (*rellenadefault)(void)=dummy;
void (*cursordebug)(void *c)=(void *)STDcursordebug;
void(*ldadebug)(void *c, int funcion) = NULL;// (void *)STDldadebug;
int(*presentamenucontex)(void *f) = (void *)STDpresentamenucontex;
void(*presentamenu)(void *m) = (void *)STDpresentamenu;
int (*llbloquearegistroaux)(void *b)=NULL; 
void (*limpiamensaje)(void *f) = (void *)STDlimpiamensaje;
void (*formerror)(void *f, char *msg) = (void *)STDformerror;
void (*forminfo)(void *f) = (void *)STDforminfo;
void (*mensajeform)(void *f, char *mensaje, ...) = (void *)STDmensajeform;
void (*cargahtmlconf)(void)=dummy;
void (*borraregistroaux)(void *b) = (void *)STDactualizabloque;
int  (*reinicia)(char *cadena,int concepto);
int (*commitsino)(void *f) = (void *)STDcommitsino;
void (*actualizabloque)(void *b) = (void *)STDactualizabloque;
void (*resetencolados)(void)=dummy;
int (*reposicionaregraton)(void *v)=dummy1;
int (*reposratonform)(void *f) = (void *)STDreposratonform;
int (*finputregistroaux)(void *b)=dummy1;
void (*recuperatodosenter)(void *b)=dummy2;
void (*guardatodosenter)(void *b)=dummy2;
void (*frecalcpadreaux)(void *b,void *padre)=NULL;
void (*fdesignacionaux)(void *b)=NULL;
int (*insertregistro)(void *b, ftrigers *ft) = (void *) STDinsertregistro;
void (*fejecutaformaux)(void *b,void *f,int *ret)=NULL;
void (*muestrapantalla)(void)=dummy;
int (*editwhere)(char *textowhere,char *textoorder,char *textohaving,char *titulowhere)=NULL;
int (*selwhere)(char **opciones,int primera,int x,int y)=menu;
char *(*damehostname)(void)=STDnombreordenador;
int (*pabrelink)(char *)=STDabrelink;
int (*pprocesaposttecla)(int)=procesaposttecla;