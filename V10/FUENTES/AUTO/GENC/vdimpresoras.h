// Modulo generado automaticamente a partir de VDIMPRESORAS.DEF

VDEXPORT diccionario dimpr;
#define IMPRNUMCOL	19
typedef struct {
        char    rowid[ROWIDLON];
        char    codimpre[LCODIMPRE];
        char    grupoimpre[LGRUPOIMPRE];
        char    desimpre[LDESIMPRE];
        char    spool[LSPOOL];
        char    driver[LDRIVER];
        char    fichero[LFICHERO];
        long    tipoconex;
        char    dirip[LDIRIP];
        long    puertoconex;
        long    baudios;
        long    bits;
        long    paridad;
        long    bitstop;
        char    activo[LACTIVO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdimpresorass;

// Prototipos de funciones definidas en VDIMPRESORAS.C
VDEXPORT diccionario *IMPRdamediccionario(void);
VDEXPORT int IMPRselvdimpresoras(char *codimpre,vdimpresorass *impr);
VDEXPORT char *IMPRlog(vdimpresorass *impr);
char * IMPRdebug(vdimpresorass *impr);
