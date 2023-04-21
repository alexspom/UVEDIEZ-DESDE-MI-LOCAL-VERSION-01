// Modulo generado automaticamente a partir de VDBASCULAS.DEF

VDEXPORT diccionario dbas;
#define BASNUMCOL	15
//#define LDATOS      101
//#define LCODOPESOL   33
//#define LHORASOL      9
//#define LCODOPELEE   33
//#define LHORALEE      9
typedef struct {
        char    rowid[ROWIDLON];
        long    numbasc;
        char    activa[LACTIVA];
        char    dirip[LDIRIP];
        char    puertotcp[LPUERTOTCP];
        long    puerto232;
        long    velocidad;
        long    status;
        char    datos[LDATOS];
        char    codopesol[LCODOPESOL];
        long    fecsol;
        char    horasol[LHORASOL];
        char    codopelee[LCODOPELEE];
        long    feclee;
        char    horalee[LHORALEE];
    } vdbasculass;

// Prototipos de funciones definidas en VDBASCULAS.C
VDEXPORT diccionario *BASdamediccionario(void);
VDEXPORT int BASbuscastatus(long status,vdbasculass *bas);
VDEXPORT int BASnextstatus(vdbasculass *bas);
VDEXPORT int BASbuscatodo(vdbasculass *bas);
VDEXPORT int BASnexttodo(vdbasculass *bas);
VDEXPORT int BASselvdbasculas(long numbasc,vdbasculass *bas);
VDEXPORT int BASactualizastatusypeso(vdbasculass *bas,int error);
VDEXPORT char *BASlog(vdbasculass *bas);
char * BASdebug(vdbasculass *bas);
