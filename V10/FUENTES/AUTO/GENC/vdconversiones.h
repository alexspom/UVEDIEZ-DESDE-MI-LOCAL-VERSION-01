// Modulo generado automaticamente a partir de VDCONVERSIONES.DEF

VDEXPORT diccionario dcon;
#define CONNUMCOL	8
typedef struct {
        char    rowid[ROWIDLON];
        char    unidadorigen[LUNIDADORIGEN];
        char    unidaddestino[LUNIDADDESTINO];
        double  factorconversion;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdconversioness;

// Prototipos de funciones definidas en VDCONVERSIONES.C
VDEXPORT diccionario *CONdamediccionario(void);
VDEXPORT int CONselunidades(char *unidadorigen,char *unidaddestino,vdconversioness *con);
VDEXPORT int CONselvdconversiones(char *unidadorigen,char *unidaddestino,vdconversioness *con);
VDEXPORT char *CONlog(vdconversioness *con);
char * CONdebug(vdconversioness *con);
