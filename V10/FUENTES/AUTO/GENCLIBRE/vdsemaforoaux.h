// Fichero generado automaticamente a partir de VDSEMAFOROAUX.DEF

VDEXPORT diccionario dsema;
#ifndef LCODSEMAFORO
#define LCODSEMAFORO 21
#endif

typedef struct {
        char    codsemaforo[LCODSEMAFORO];
} vdsemas; 


VDEXPORT diccionario *SEMAdamediccionario(void);
VDEXPORT int SEMAprocdamesemaforo(char *codsemaforo,vdsemas *sema);
VDEXPORT int SEMAprocliberasemaforo(char *codsemaforo,vdsemas *sema);
VDEXPORT char * SEMAdebug(vdsemas *sema);

//Codigo incluido explicitamente en el DEF
VDEXPORT int damesemaforo(char *semaforo);
VDEXPORT int liberasemaforo(char *semaforo);
