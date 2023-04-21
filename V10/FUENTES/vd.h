#ifndef __VD__
#define __VD__
#include "v10form.h"

#ifndef __LINUX__

#define VDEXPORT __declspec( dllexport )
#endif

#include "vddef.h"
#include "vderror.h"
#include "diccionario/vddiccionario.h"
/* Tipos de bloqueo y verificaci�n de bloqueo */
#define	WAIT		1
#define NOWAIT		0
#define VERIFICA	1
#define NOVERIFICA	0
#define VALIDA      1
#define NOVALIDA    0


#define LCADENABIG	    (8192+1)
#define LCADENA		      (512+1)
#define LCADENASMALL		(64+1)




#include "vdauto.h"


#define LMIPASSWORD    21
#define LMAXHASH       51


//Funciones definidas en VDLOG.C
VDEXPORT int quitalogoracle(int quita);
VDEXPORT void vdlogoracle(void);

//Funciones definidas en VDGENAUX.C
VDEXPORT int vverificacampos(void *d1,void *d2,diccionarios *dic,va_list arg);

//Funciones definidas en VDCONVERSIONESAUX.C
VDEXPORT double convierteunidades(double cantidad,char *unidadorigen,char *unidaddestino);
VDEXPORT double conviertearticulo2host(double cantidad,char *codart,int *decimales);
VDEXPORT double conviertearticulo2v10(double cantidad,char *codart);

//Funciones VDCONFIAUX.C
VDEXPORT int damepropenteroinst(char *propiedad,char *instancia);
VDEXPORT int damepropentero(char *propiedad);
VDEXPORT double damepropdobleinst(char *propiedad,char *instancia);
VDEXPORT double damepropdoble(char *propiedad);                    
VDEXPORT v10dates damepropfechainst(char *propiedad,char *instancia);
VDEXPORT v10dates damepropfecha(char *propiedad);                   
VDEXPORT char *damepropcadenainst(char *propiedad,char *instancia);
VDEXPORT char *damepropcadena(char *propiedad); 
VDEXPORT char *resuelveconf(char *cadena,char *instancia);
VDEXPORT v10horas dameprophorasinst(char *propiedad,char *instancia);
VDEXPORT v10horas dameprophoras(char *propiedad);

// Funciones de VDCOMENAUX.C
VDEXPORT void v10logcomen(int nivel, char *comentario, char *format,...);
VDEXPORT int v10comen(char *tabla,long codcomen,char *tipocomen,long lincomen, char *comentario,char *msjerror);
VDEXPORT int v10comenrelogin(char *tabla,long codcomen,char *tipocomen,long lincomen, char *comentario,char *msjerror);
VDEXPORT int v10damecomen(long codcomen,char *tipocomen,long lincomen,char *msjerror,vdcomens *com);
VDEXPORT int v10comenpropcadena(long codcomen,char *tipocomen,char *comentario);
VDEXPORT int v10comenpropentero(long codcomen,char *tipocomen,long *valor);
// borra todos los comentarios de un objeto de un tipo determinado
VDEXPORT int v10deletecomenportipo(long codcomen, char *tipocomen,char *msjerror);

//Funciones definidas en VDEAN128
VDEXPORT int damecampoean(char *codigo,char *codidean,char *donde);

// Funciones de VDLOG.C
VDEXPORT void initlogoracle(void);
VDEXPORT void logoracle2cadena(char *cadena);
VDEXPORT int damenivel(void);
VDEXPORT int ponnivel(int nivel);

// Trigers Forms/Radio sobre movto en VDFORTRIGMOV.C
// funci�n que recoge stock en origen a ubic. temporal
VDEXPORT int vdrecogestk(char *nomtrig,char *nomproceso, vdmovims *mov, vdrecursos *rec, char *mensaje,int sincrono);
// funci�n que deposita stock en ubic. destino
VDEXPORT int vddepositastk(char *nomtrig,char *nomproceso, vdmovims *mov, char *mensaje, int sincrono);
// funci�n que ejecuta un movto, recogiendo de origen y depositando en ubic. destino
VDEXPORT int vdejecutamov(char *nomtrig,char *nomprocesoori,char *nomprocesodest, vdmovims *mov, vdrecursos *rec, char *mensaje, int sincrono);
// funci�n que congela un movto en funci�n del stock en su matr�cula origen
VDEXPORT int congela(char *nomtrig, vdmovims *mov,char *limpiamov, char *mensaje);
// TRIGGER de recogida AS�NCRONA de stock en origen a ubic. temporal
VDEXPORT int frecogestk(bloques *b,ftrigers *ft);
// TRIGGER de recogida S�NCRONA de stock en origen a ubic. temporal
VDEXPORT int frecogestksync(bloques *b,ftrigers *ft);  
// TRIGGER que deposita de modo AS�NCRONO stock en ubic. destino
VDEXPORT int fdepositastk(bloques *b,ftrigers *ft);
// TRIGGER que deposita de modo S�NCRONO stock en ubic. destino
VDEXPORT int fdepositastksync(bloques *b,ftrigers *ft);
// TRIGGER de ejecuci�n AS�NCRONA de un movto, recogida de origen y depositar en ubic. destino
VDEXPORT int fejecutamov(bloques *b,ftrigers *ft); 
// TRIGGER de ejecuci�n S�NCRONA de un movto, recogida de origen y depositar en ubic. destino
VDEXPORT int fejecutamovsync(bloques *b,ftrigers *ft);
// TRIGGER que congela un movto en funci�n del stock en su matr�cula origen
VDEXPORT int fcongelamov(bloques *b,ftrigers *ft);


// Trigers Forms/Radio de ubicar/reubicar en VDFORTRIGUBI.C
// coloca en el campo V10ERROR de la pantalla el contenedo de "mensaje"
VDEXPORT void ponerrorbloque(bloques *b, char *mensaje);
// TRIGGER de reubicaci�n de un contenedor completo
VDEXPORT int freubiconte(bloques *b,ftrigers *ft);
// TRIGGER de reubicaci�n parcial de stock
VDEXPORT int freubistk(bloques *b,ftrigers *ft);
// TRIGGER de cambio de ubicaci�n de un contenedor
VDEXPORT int fcambioubiconte(bloques *b,ftrigers *ft);
// TRIGGER de cambio de ubicaci�n parcial
VDEXPORT int fcambioubistk(bloques *b,ftrigers *ft);
// TRIGGER que verifica si uan matr�cula, articulo y lote es compatible en una ubicacion
VDEXPORT int fubicompatible(bloques *b,ftrigers *ft);

// VDORAERRAUX.c
VDEXPORT int vdhandleoraerr(int coderr,v10cursors *c);
// gestiona un error oracle al hacerle cursor_Debug

// Funciones en VDRUTAMOV.C
int llvdenrutamov(vdmovims *mov, long stesperaruta, long stfinal, char *fuerzamismopasillo);

// Funciones en VDSTATUSPARAM.C
// realiza la carga en "st" de los valores del estado pasado por su descripci�n abreviada 
VDEXPORT int damestabreviada(char *algoritmo,char *param, int pos, char *sep, void *obj, char *tipost, vdstatuss *st, int valordefecto);

// Algoritmos en VDMOVTOS.C
// ALGORITMO que Enruta un movto ptr
VDEXPORT int vdenrutamov(void *ptr,char *param);
// ALGORITMO que Asigna flujo a un movimiento ptr
VDEXPORT int vdasignaflujo(void *ptr,char *param);
// ALGORITMO que Recoge el stock de origen del movto, a la ubicaci�n intermedia.
VDEXPORT int vdstockori(void *ptr,char *param);
// ALGORITMO que Deposita el stock en la ubicaci�n destino del movto.
VDEXPORT int vdstockdest(void *ptr,char *param);
// funci�n para la ejecuci�n de algoritmos (por discriminnate) de un proceso dado para un movto, desde un trigger s�ncrono
VDEXPORT int triggermovsync(char *nomproceso,vdmovims *mov);


// Funciones en VDFORTRIGSTK.C


VDEXPORT int vdcreastk(vdstocks *stk, char *conceptoentrada,char *fuente,char *observ,int fuerzastock,char *msjerror,double *codmoventrada);
VDEXPORT int vddividestk(char *codmat,long ordenstk,char *conceptoentrada, char *fuente, char *conceptosalida, 
						 char *sumidero,double cantidad,char *observ, char *msjerror,double *codmoventrada,double *codmovsalida,long *nuevoordenstk);
VDEXPORT int vdtransformstk(char *codmat,int ordenstk,vdstocks *nuevostk, char *conceptoentrada, char *fuente, 
							char *conceptosalida, char *sumidero,  char *observ, char *msjerror,double *codmoventrada,
							double *codmovsalida,double *codmovinterno);
VDEXPORT int vdregularizastk(char *codmat,int ordenstk, char *concepto,char *ubiconcepto, double diff, // en unidades V10
							 char *observ, char *msjerror,double *codmov);

// triger que transforma el stock de una l�nea de stock
VDEXPORT int ftransformastk(bloques *b,ftrigers *ft);
// transforma las calificaciones de una l�nea de stock
VDEXPORT int fbloqueosstk(bloques *b,ftrigers *ft);
// regulariza la cantidad de una l�nea de stock
VDEXPORT int fregularizastk(bloques *b,ftrigers *ft);
// divide una l�nea de stock, en 2, pas�ndo cierta cantidad de la primera l�nea de stock a la segunda
VDEXPORT int fdividestk(bloques *b,ftrigers *ft);
// cambia las calificaciones de un lote
VDEXPORT int fnuevobloqlote(bloques *b,ftrigers *ft);


// Funciones en VDFORTRIGPROC.C
// lanza la ejecuci�n de un proceso de manena s�ncrona
VDEXPORT int flanzaprocesosync(bloques *b,ftrigers *ft);
// lanza la ejecuci�n de un proceso de manena As�ncrona
VDEXPORT int flanzaproceso(bloques *b,ftrigers *ft);
// lanza la ejecuci�n de una lista de tarea de manera s�ncrona
VDEXPORT int flanzatareassync(bloques *b,ftrigers *ft);
// lanza la ejecuci�n de una lista de tarea de manera As�ncrona
VDEXPORT int flanzatareas(bloques *b,ftrigers *ft);


// Funciones en VDFORTRIGIMPRE.C
// impresi�n de etiquetas e informes
VDEXPORT int fimprime(bloques *b,ftrigers *ft);
// exporta un documento a un fichero
VDEXPORT int fexporta(bloques *b,ftrigers *ft);


// funciones en VDFORTRIGDEM.C
// anula una l�nea de demanda de forma as�ncrona
VDEXPORT int fanulademl(bloques *b,ftrigers *ft);
// anula una l�nea de demanda de forma s�ncrona
VDEXPORT int fanulademlsync(bloques *b,ftrigers *ft);
// anula una cabecera de demanda de forma as�ncrona
VDEXPORT int fanulademc(bloques *b,ftrigers *ft);
// anula una cabecera de demanda de forma s�ncrona
VDEXPORT int fanulademcsync(bloques *b,ftrigers *ft);

// funciones en VDFORTRIGCNT.C
// rengancha un movto de un contenedor a otro con el mismo stock, de la misma ubic. o no
VDEXPORT int freenganchaconte(bloques *b,ftrigers *ft);
// cambia la calif. de stock del art�culo y lote de una matr�cula
VDEXPORT int fbloqueosconte(bloques *b,ftrigers *ft);

//funciones en VDFORTRIGCORREO.C
// env�a un correo de un tipo
VDEXPORT int vdcorreo(char *tipocorreo,char *asunto, char *cuerpo, char *mime, char *dir, char *fichero, int prioridad,long fecplanif, char *horaplanif, char *mensaje);
// env�a un correo sin tipo, pas�ndole cuenta y destinatarios
VDEXPORT int vdcorreodet(char *cuenta,char *para,char *cc,char *cco,char *asunto,char *cuerpo,char *mime, char *dir,char *fichero,int prioridad,long fecplanif,char *horaplanif,char *mensaje); 
// env�a un correo de un tipo
VDEXPORT int fcorreo(bloques *b,ftrigers *ft);
// env�a un correo sin tipo, pas�ndole cuenta y destinatarios
VDEXPORT int fcorreodet(bloques *b,ftrigers *ft);

// VDORAERRAUX.C
VDEXPORT void cargahandleoraerr(char *programa,char **argv,int arg);
// carga en memoria las definiciones de manejadores de errores oracle

// v10host.c
VDEXPORT void ponhostname(void);
VDEXPORT void ponhostnameext(char *cad);

// v10sid.c
VDEXPORT void funcactualizasid(void);

// v10fortrigstk.c
VDEXPORT int vdnuevobloqlote (char *codart, char *codlot, char *bloqlote, char *solostock, char *msjerror);

// vdfortrigcnt.c
VDEXPORT int vdbloqueosconte(char *codmat, char *codart, char *codlot,
                           char *codconce, char *patronbloqueosori, char *bloqueos,
                           char *observ, char *msjerror, double cantidad);

//vdtraduce.c
VDEXPORT int ponv10traduce(void);

    
#endif