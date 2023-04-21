#include "info4.h"

#define LDIRIPINFO4  16

#define MAXTECLAS     200

#define CAUSAOPER     1
//#define CAUSAREPEAT   2

//Tipos de autonumeracion
#define AUTONONUMERA  0
#define AUTONUMDISP   1
#define AUTONUMSERIE  2

//typedef struct ETHERBOXS etherboxs;

typedef struct {
	unsigned long      serie;
	unsigned long      version;
	unsigned long      errhard;
	unsigned long      errtrama;
	unsigned long      consumo;
	long      numdisp;
	int       tipo;
	tipodisps *ptipo;
	char      valor[MAXDIGDISPLAY];
	unsigned short  luces[MAXLUCESDISPLAY];
	char      status[MAXSTATUSDISPLAY];
	int       stdisp;
	int       modificado; // MOdificado el valor desde el PC
	int       modifstatus;  // Modificado el estatus
} displays;

typedef struct {
	long      numdisp;
	long      serie;
	long      version;
	int       boton;
	int       causa;
} tecladisps;


typedef struct ETHLINEAS {
                  int        port;
                  int        numdisp;
                  int        initlinea;
                  vdsockets  *vds;
				  displays disp[MAXDISPLAYS];
                  struct ETHERBOXS  *eth;
                  unsigned long tramasida,
                                tramasvuelta,
                                bytesida,
                                bytesvuelta,
                                bucles,
                                reconexiones,
                                creatramas,
                                lonida,
                                errtrama,
                                consumo,
                                consumo232;
                  char          stglob,stcon;
                  v10horas         hultstat;
                  unsigned long version;
                  int           autonumera;
                  int           ciclotrabajo[MAXLUCESDISPLAY];
                  unsigned long       limitacionlinea;
                  unsigned long       tciclo;
                  unsigned long       tenvtrama;
                  unsigned long       timeouttrama;
                  unsigned long       timeoutwho;
                } ethlineas;

typedef struct ETHERBOXS {
                char      dirip[LDIRIP];
                ethlineas    lin[MAXLINEAS];
                unsigned long version;
                int           autonumera;
              } etherboxs;



extern etherboxs eth[MAXETHER];
extern  int modotest;

//extern tecladisps tecdisp[MAXTECLAS];
extern int numetherbox;
extern int numteclasdisp;
extern int MODIFICADOINFO;

//Funciones definidas en INFOPCDISP.C
void lucesdisplayid(long iddisplay,int numluz,int valor);
int vdisplayprintfid(long iddisplay,char *format,va_list arg);
int haytecladisp(void);
int tecladisp(tecladisps *tec);
displays *damedisplayid(long iddisplay);
displays *revisadisp(long serie,long numdisp,int tipo);
void encolatecladispp(displays *p,int boton,int causa);
int displayprintfid(long iddisplay,char *format,...);
void togglelucesdisplayid(long iddisplay,int numluz);
int displayprintfp(displays *p,char *format,...);
void togglelucesdisplayp(displays *p,int numluz);
void lucesdisplayp(displays *p,int numluz,int valor);



//Funciones definidas en INFO4HL.C
int initinfopick(int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *rangolineas,char *tarj1,...);
int displayprintf(long iddisplay,char *format,...);
void lucesdisplay(long iddisplay,int numluz,int valor);
int numdisp(void);

//Funciones definidas en INFOETH.C
void initeth(etherboxs *eth,int tciclo,int tenvtrama,int timeouttrama,int timeoutwho,int limitacionlinea,char *rangolineas);
void tickhleth(void);
void ticketh(etherboxs *eth);
int dimedatosdisp(int ndisp,int *neth,int *nlin,int *numdisp);
int pdisplin(ethlineas *lin);
void pidestatusdisp(ethlineas *lin,int numdisp);


//Funciones definidas en INFOCOMUN.C
char *llinfodameversion(unsigned long version,int adisp);
