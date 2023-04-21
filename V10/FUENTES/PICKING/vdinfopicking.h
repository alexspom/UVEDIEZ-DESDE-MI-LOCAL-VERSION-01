#include "vd.h"
#include "execproc\vdexec.h"
#include "vdimpresion.h"

#define INFOMENTECLA  0

#define NEXTTICKZONA	 300
#define NEXTTICKZONAEXT  500
#define STIHDAPAGADO    100
#define STIHDPENDIENTE  200
#define STIHDPRESENTADO 300

// Definición tecla 
#define TVALIDA   0
#define TMAS      1
#define TMENOS    2
#define TFUNC     3
#define TREFRESCA  98
#define TESTADOBOT 99
#define TINIT     1000
#define TTICK     1001

//Longitud de los displays 
#define MAXLONDISPZONA 16     // Longitud display de zona
#define MAXLONDISP		4       // Longitud display normal

//Tipos de tick
#define TICK_OK		2
#define TICK_FIN	1
#define SIN_TICK	0


// Identificadores de las luces de los displays
#define LUZMAS    0
#define LUZMENOS  1
#define LUZAZUL   2
#define LUZVERDE  3
#define LUZROJA   4
#define LUZFUNC   5

typedef struct {
      int idinfopick;
		  int numdisp;
		  int tipomensaje;
		  int nmensaje;
		  int causa;
		  void *param;
		  void (*funlibera)(void *param);
	} vdinfomensajes;



extern int idinfogest;	
	
//funciones definidas en VDINFOHARDDISPAUX.C
VDEXPORT int vdinfoencolatecla(int idinfopick,int numdisp,int nboton,int causa);
VDEXPORT int vdinfoprintf(int idinfopick,int numdisp,char *format,...);
char *damenombretecla(int ntecla);
VDEXPORT int vdinfodametecla(int idinfogest,vdinfomensajes *ite);

