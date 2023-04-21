// Modulo generado automaticamente a partir de VDPROCESOS.DEF

VDEXPORT diccionario dpro;
#define PRONUMCOL	17
typedef struct {
        char    rowid[ROWIDLON];
        char    grupoproc[LGRUPOPROC];
        char    proceso[LPROCESO];
        char    param[LPARAM];
        char    funcionproc[LFUNCIONPROC];
        char    libproceso[LLIBPROCESO];
        long    ordenacion;
        long    periodo;
        char    codsemaforo[LCODSEMAFORO];
        long    ejecuciones;
        char    ejecutainmediato[LEJECUTAINMEDIATO];
        char    infoextra[LINFOEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    activo[LACTIVO];
    } vdprocesoss;

// Prototipos de funciones definidas en VDPROCESOS.C
VDEXPORT diccionario *PROdamediccionario(void);
VDEXPORT int PROselejecutainmediato(char *proceso,vdprocesoss *pro);
VDEXPORT int PROselvdprocesos(char *proceso,vdprocesoss *pro);
VDEXPORT int PROactualizaejecutainmediato(vdprocesoss *pro,int error);
VDEXPORT char *PROlog(vdprocesoss *pro);
char * PROdebug(vdprocesoss *pro);
