#ifndef __VDRADIO__
#define __VDRADIO__
#include "vdform.h"

#define MAXLDRIVER      21
#define LSERVICIOTCP    31

#define MAXBUFTEC MAXCADENA 
#define MAXRECURSOS 500
#define MAXTECLASDRIVER 20

#define OPPENDIENTE  1
#define OPENCURSO    2
#define OPVERIFICADO 3
#define OPCONFIRMADO 4


#define REINITFRM -2
#define LOADFRM   -3


typedef struct {
          vdrecursos rec;  // Recurso asociado al terminal de radio
          vdusuarios op;  // Operario del recurso
          vdperfiltareas perfil; //Perfil cargado en la pantalla
          int   pideusr;   // Estado de la peticion de usuario
          forms *f;        // Forms que esta ejecutando el recurso
          v10horas pmensaje; // Hora a la que se recibio el primer mensaje del recurso
          v10horas umensaje; // Hora a la que se recibio el ultimo mensaje del recurso;
          v10horas ubusqueda; // Hora a la que se realizo la ultima busqueda de trabajo
          v10socks *v10sock;
          char buffer[MAXCADENA];
          char buffer232[MAXCADENA];
          char *ptr,*ptr232;
          int  status;
          int  mensaje;
          char *contenidomensaje;
          int  buftec[MAXBUFTEC];
          int  nbuftec;
          int  scanning;
          int  en232;
          int  mostrar;
          int  modificado;
        } conexiones;
VDEXPORT conexiones *con[MAXRECURSOS];
VDEXPORT int ncon;
VDEXPORT char PRINSCAN;
VDEXPORT char FINSCAN;
VDEXPORT char PRIN232;
VDEXPORT char FIN232;
VDEXPORT int CSUENA;
VDEXPORT char codrecursodef[LCODRECURSO];

typedef struct {
             int t;
             int (*funcion)(conexiones *c);
} tecladrivers;

typedef struct RADDRIVERS {
         char nombre[MAXLDRIVER];
         int  (*init)(void);
         int  (*tick)(void);
         int  (*findriver)(void);
         int  (*initterm)(conexiones *c);
         int  (*mensaje)(conexiones *c,int suena,char *texto,va_list arg);
         int  (*pasaformaterm)(conexiones *c,int suena);
         void (*damecadenaform)(conexiones *c,char *cadena);
         int  (*pasatermaform)(conexiones *c);
         void  (*encolatecla)(conexiones *c,int tec);
         void (*presentacampo)(conexiones *c,int resaltado,int lon,int pass);
         char serviciotcp[LSERVICIOTCP];
         int  nteclas;
         int  numports;
         tecladrivers tec[MAXTECLASDRIVER];
} raddrivers;

VDEXPORT raddrivers dr;
VDEXPORT int MODIFRADIO;
#define MAXPORTRADIO  1000

//Funciones definidas en VDRADTELNETCON.C
VDEXPORT int logoutterminal(conexiones *c);
VDEXPORT int loginterminal(conexiones *c);
VDEXPORT void liberaconexion(conexiones *c);
VDEXPORT conexiones *numcon(char *codrecurso);
VDEXPORT void tratanuevatcp(void);
VDEXPORT int initradiotcp(void);
VDEXPORT int hayteclaconexion(conexiones *c);
VDEXPORT int sigcarconexion(conexiones *c);
VDEXPORT void encolateclaconexion(conexiones *c,int tec);


//Funciones definidas en VDRADTRATA.C
VDEXPORT void liberaterminal(conexiones *c);
VDEXPORT void restauraterminal(conexiones *c);
VDEXPORT void gestionaterminal(int immediato,conexiones *c);

//Funciones definidas en VDRADFRM.C
#define ejecutatrigerradio(c,b,ft,tipo,campo,mostrar) ejecutatrigerradionombre(c,b,ft,#tipo,tipo,campo,mostrar)
VDEXPORT void ponrecurso(char *micodrecurso);
VDEXPORT int haycampoenter(conexiones *c);
VDEXPORT void vmensajeradioc(conexiones *c,int suena,char *texto,va_list arg);
VDEXPORT void mensajeradioc(conexiones *c,int suena,char *texto,...);
VDEXPORT int ejecutatrigerradionombre(conexiones *c,bloques *b,ftrigers *ft,char *nombre,int tipo,fcampos *campo,int mostrar);
VDEXPORT void ponindicadoresbloque(bloques *b);
VDEXPORT int mandabloqueradio(conexiones *c);
VDEXPORT int cargaradfrm(char *nombre,conexiones *c,int restaura,int salva);
VDEXPORT void empiezainputcampo(conexiones *c);
VDEXPORT int terminainputcampo(conexiones *c,int mostrar,int post);
VDEXPORT int siguientecampo(conexiones *c);
VDEXPORT int anteriorcampo(conexiones *c);
VDEXPORT int tratafuncion(conexiones *c,int ret);
VDEXPORT int tratateclaconexion(conexiones *c,int ret);
VDEXPORT int tratafrm(conexiones *c);

//Funciones definidas en VDRADTRIG.C
VDEXPORT void declaratecladriver(int tec,int (*funcion)(conexiones *c));
int fdesconecta(conexiones *c);
VDEXPORT void inittrigradio(void);


//Funciones definidas en VDRADTELNETAUX.C
VDEXPORT void posicionaconexion(conexiones *c);
VDEXPORT void presentacampotelnet(conexiones *c,int resaltado,int lon,int pass);
VDEXPORT int form2telnet(conexiones *conex,int suena);
VDEXPORT int mensajetelnet(conexiones *c,int suena,char *texto,va_list arg);
VDEXPORT void cargadrivertelnet(raddrivers *dr);

//Funciones definidas en VDRADTELNETTICK.C
void vaciabuffertelnet(conexiones *c);
VDEXPORT int telnettick(void);

//Funciones definidas en VDRADPRESE.C
VDEXPORT int presentapantalla(void);

// Funciones definidas en VDEAN128.C
VDEXPORT int damecampoean(char *codigo,char *codidean,char *donde);

//Funciones definidas en VDRADSCAN.C
VDEXPORT int ffuerzascan(bloques *b,ftrigers *ft);

//funciones definidas en VDARTICAUX.C
VDEXPORT int fleearticulo(bloques *b,ftrigers *ft);

#endif