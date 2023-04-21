// Modulo generado automaticamente a partir de VDPREPOSTALGORITMOS.DEF

VDEXPORT diccionario dprepost;
#define PREPOSTNUMCOL	15
typedef struct {
        char    rowid[ROWIDLON];
        char    proceso[LPROCESO];
        char    nombrealg[LNOMBREALG];
        char    tipoalg[LTIPOALG];
        char    funcionalg[LFUNCIONALG];
        char    desalg[LDESALG];
        char    paramalg[LPARAMALG];
        char    libalgoritmo[LLIBALGORITMO];
        char    activo[LACTIVO];
        long    prioridad;
        char    infoextra[LINFOEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdprepostalgoritmoss;

// Prototipos de funciones definidas en VDPREPOSTALGORITMOS.C
VDEXPORT diccionario *PREPOSTdamediccionario(void);
VDEXPORT int PREPOSTbuscaalgoritmo(char *tipoalg,char *proceso,char *nombrealg,vdprepostalgoritmoss *prepost);
VDEXPORT int PREPOSTnextalgoritmo(vdprepostalgoritmoss *prepost);
VDEXPORT int PREPOSTselvdprepostalgoritmos(char *proceso,char *nombrealg,char *tipoalg,long prioridad,vdprepostalgoritmoss *prepost);
VDEXPORT char *PREPOSTlog(vdprepostalgoritmoss *prepost);
char * PREPOSTdebug(vdprepostalgoritmoss *prepost);
