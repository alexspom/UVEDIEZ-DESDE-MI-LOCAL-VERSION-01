#include "vd.h"
#include "windows.h"
#include "Winbase.h"
//#include "Commdlg.h"
#include "crpe.h"
#include "Winspool.h"
#include "Uxddisk.h"

#if defined (__cplusplus)
extern "C" // incrusto código C en C++
{
#endif


typedef struct {    
    short id;
    char informe[MAXPATH];
    char codimpre[LCODIMPRE];
    char salidaimpresora[MAXPATH];
    char fichexport[MAXPATH];
    int  abrirfichero;
    int informeabierto;
    char cadenabind[MAXCADENA];
    char nuevowhere[MAXCADENA];
    char sql[MAXSQL];
    int copias;
    PEReportOptions  opt;
    short idsubreport;
    char nomsubreport[MAXPATH];  
} cr10impresiones;

// funciones en vdcr10.c
__declspec(dllexport) int vdcargainforme(char *orausr, char *orapwd, char *oradb, char *informe, void **ptr, char *msjerror);
__declspec(dllexport) int vdbindinforme(char *variables, void **ptr, char *msjerror);
__declspec(dllexport) int vdwhereinforme(char *where, void **ptr, char *msjerror);
__declspec(dllexport) int vdimprimeinforme(char *codimpre, char *salida, int copias, void **ptr, char *msjerror);
__declspec(dllexport) int vdexportainforme(char *fichero, int abrir, void **ptr, char *msjerror);
__declspec(dllexport) int vdcierrainforme(void **ptr, char *msjerror);

// funciones en vdcr10imprimeinforme.c
int CR10imprime(char *codimpre, char *salida, int copias, cr10impresiones *imp, char *msjerror);

// funciones en vdcr10whereinforme.c
int CR10cambiawhere(char *where, cr10impresiones *imp, char *msjerror);

// funciones vdcr10motor.c
char *CR10error( cr10impresiones *imp, short id);
int CR10revisaconexionamotor(char *msjerror);
int CR10conectaamotor(char *orausr,char *orapwd,char *oradb,cr10impresiones *imp, char *msjerror);
extern PELogOnInfo connactual;

// funciones en vdcr10cargainforme.c
char  *CR10damecadenahandle (HANDLE hsql, short lon);
int CR10reenganchainforme(cr10impresiones *imp, char *msjerror,int sqlsubreport);
int CR10damesqlsubreport(cr10impresiones *imp, char *msjerror);
int CR10cargainforme(char *informe,cr10impresiones *imp, char *msjerror);
int CR10cierrainforme (cr10impresiones *imp, char *msjerror);

// funciones de vdcr10bindinforme.c
int CR10damevalorcampo( cr10impresiones *imp, char* campo, char *valor, char *msjerror );
int CR10bindvariables(char *variables,cr10impresiones *imp, char *msjerror);

// funciones en vdcr10exportainforme.c
int CR10exportainforme(cr10impresiones *imp, char *msjerror);
int CR10exportaeimprimeinforme( cr10impresiones *imp, char *msjerror);

#if defined (__cplusplus)
}
#endif