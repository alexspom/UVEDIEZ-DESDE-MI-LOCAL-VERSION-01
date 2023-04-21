// Modulo generado automaticamente a partir de VDINTERFASECAB.DEF

VDEXPORT diccionario dintc;
#define INTCNUMCOL	24
#define LREG 2049
typedef struct {
        char    rowid[ROWIDLON];
        char    tipointerfase[LTIPOINTERFASE];
        char    formato[LFORMATO];
        char    formatopadre[LFORMATOPADRE];
        long    orden;
        long    nregistros;
        char    swtactualiza[LSWTACTUALIZA];
        char    preffichero[LPREFFICHERO];
        char    tipofichero[LTIPOFICHERO];
        long    secuencial;
        char    separador[LSEPARADOR];
        char    swtlongfija[LSWTLONGFIJA];
        long    longformato;
        char    funcion[LFUNCION];
        char    libreria[LLIBRERIA];
        char    formatofich[LFORMATOFICH];
        char    extfichero[LEXTFICHERO];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    formatonum[LFORMATONUM];
        char    reg[LREG];
    } vdinterfasecabs;

// Prototipos de funciones definidas en VDINTERFASECAB.C
VDEXPORT diccionario *INTCdamediccionario(void);
VDEXPORT int INTCselhijo(char *tipointerfase,char *formatopadre,vdinterfasecabs *intc);
VDEXPORT int INTCselselformato(char *tipointerfase,char *reg,vdinterfasecabs *intc);
VDEXPORT int INTCbuscatipofichero(char *tipofichero,vdinterfasecabs *intc);
VDEXPORT int INTCnexttipofichero(vdinterfasecabs *intc);
VDEXPORT int INTCbuscatipointerfase(char *tipointerfase,vdinterfasecabs *intc);
VDEXPORT int INTCnexttipointerfase(vdinterfasecabs *intc);
VDEXPORT int INTCbuscaraiz(vdinterfasecabs *intc);
VDEXPORT int INTCnextraiz(vdinterfasecabs *intc);
VDEXPORT int INTCselvdinterfasecab(char *tipointerfase,char *formato,vdinterfasecabs *intc);
VDEXPORT int INTCactualizasecuencial(vdinterfasecabs *intc,int error);
VDEXPORT char *INTClog(vdinterfasecabs *intc);
char * INTCdebug(vdinterfasecabs *intc);
