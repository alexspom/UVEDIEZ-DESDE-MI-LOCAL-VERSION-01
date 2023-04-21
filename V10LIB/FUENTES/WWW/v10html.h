#ifndef __v10html
#define __v10html
typedef struct { // configuración básica de envios HTML
	char user[100];
	int ventanalogin;
	int mostrarbotonera;
	int resolucionx;
	int resoluciony;
	int pixelesfila;
	double pixelescol;
	int multiventana;
	int ayudatamanox;
	int ayudatamanoy;
	int ayudaposx;
	int ayudaposy;
	int sinceros;
	char hojaestilos[MAXPATH];
} v10htmlconfigs;


V10WWWIMPORT v10htmlconfigs v10htmlconf;


V10WWWIMPORT void v10punterosweb(void (*func)(char *, void *),
								 int (*func2)(int nstat,void *,char *, char *),
								 double timeout);

extern int v10htmlenviado;
extern int v10htmlencurso;

int leefichero(char *fichero,char *data);
int leeficheropath(char *fichero,char *data);
int v10cargaplantillahtml(char *plantillafrm,char *plantilladefecto,char *data);
void v10reemplazapatron(char *data,char *patron,char *texto,int eliminar);

	
extern char v10html[MAXCADENAHTML*2];
extern char v10javascript[MAXCADENAHTML*2];
extern char v10datoshtml[MAXCADENAHTML];
extern char v10botoneshtml[MAXCADENA];


extern char idanterior[100];
extern int filaactiva,colactiva;
extern int maxfilas,maxcolumnas;
extern int ventanamodal;

#endif