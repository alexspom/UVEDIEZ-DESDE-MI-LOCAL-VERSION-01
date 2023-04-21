#include "vd.h"

#if defined (__cplusplus)
extern "C" // incrusto código C en C++
{
#endif

typedef struct {    
    char usuario[32];
    char password[32];
    char conexion[32];
    char variables[MAXCADENA];
    char informe[MAXPATH];
    
} reportmgimpresiones;

#define PREVISUALIZA "WINVIEW"

// funciones en vdcr10.c
__declspec(dllexport) int vdcargainforme(char *orausr, char *orapwd, char *oradb, char *informe, void **ptr, char *msjerror);
__declspec(dllexport) int vdbindinforme(char *variables, void **ptr, char *msjerror);
__declspec(dllexport) int vdwhereinforme(char *where, void **ptr, char *msjerror);
__declspec(dllexport) int vdimprimeinforme(char *codimpre, char *salida, int copias, void **ptr, char *msjerror);
__declspec(dllexport) int vdexportainforme(char *fichero, int abrir, void **ptr, char *msjerror);
__declspec(dllexport) int vdcierrainforme(void **ptr, char *msjerror);


// funciones definidas en vdreport.c
int ejecutareport(char *usr, char *pwd, char *conexion,
                  char *nombre,char *param,int impresora,
                  char *destino,int preview, char *msjerror);

#if defined (__cplusplus)
}
#endif