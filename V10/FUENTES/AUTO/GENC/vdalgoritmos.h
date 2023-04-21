// Modulo generado automaticamente a partir de VDALGORITMOS.DEF

VDEXPORT diccionario dalg;
#define ALGNUMCOL	14
typedef struct {
        char    rowid[ROWIDLON];
        char    proceso[LPROCESO];
        char    nombrealg[LNOMBREALG];
        char    desalg[LDESALG];
        char    discriminante[LDISCRIMINANTE];
        char    paramalg[LPARAMALG];
        char    funcionalg[LFUNCIONALG];
        char    libalgoritmo[LLIBALGORITMO];
        char    activo[LACTIVO];
        char    infoextra[LINFOEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdalgoritmoss;

// Prototipos de funciones definidas en VDALGORITMOS.C
VDEXPORT diccionario *ALGdamediccionario(void);
VDEXPORT int ALGbuscaalgoritmo(char *proceso,char *activo,vdalgoritmoss *alg);
VDEXPORT int ALGnextalgoritmo(vdalgoritmoss *alg);
VDEXPORT int ALGselalgproc(char *proceso,char *nombrealg,vdalgoritmoss *alg);
VDEXPORT int ALGselvdalgoritmos(char *proceso,char *nombrealg,vdalgoritmoss *alg);
VDEXPORT char *ALGlog(vdalgoritmoss *alg);
char * ALGdebug(vdalgoritmoss *alg);
