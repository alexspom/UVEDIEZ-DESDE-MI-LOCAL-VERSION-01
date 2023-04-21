// Fichero generado automaticamente a partir de VDORAERR.DEF

VDEXPORT diccionario doraerr;
#ifndef LRANGOEXE
#define LRANGOEXE 1025
#endif

#ifndef LRANGOERROR
#define LRANGOERROR 1025
#endif

#ifndef LDESCERROR
#define LDESCERROR 257
#endif

#ifndef LLIBALGORITMO
#define LLIBALGORITMO 257
#endif

#ifndef LFUNCIONALG
#define LFUNCIONALG 33
#endif

#ifndef LPARAM
#define LPARAM 257
#endif

typedef struct {
        long    orden;
        long    nivelerr;
        char    rangoexe[LRANGOEXE];
        char    rangoerror[LRANGOERROR];
        char    descerror[LDESCERROR];
        char    libalgoritmo[LLIBALGORITMO];
        char    funcionalg[LFUNCIONALG];
        char    param[LPARAM];
        long    tiempoespera;
} vdoraerrs; 


VDEXPORT diccionario *ORAERRdamediccionario(void);
VDEXPORT int ORAERRbuscahandleerror(char *rangoexe,vdoraerrs *oraerr);
VDEXPORT int ORAERRnexthandleerror(vdoraerrs *oraerr);
VDEXPORT char * ORAERRdebug(vdoraerrs *oraerr);
