// Modulo generado automaticamente a partir de VDINTERFASELIN.DEF

VDEXPORT diccionario dintl;
#define INTLNUMCOL	24
typedef struct {
        char    rowid[ROWIDLON];
        char    tipointerfase[LTIPOINTERFASE];
        char    formato[LFORMATO];
        long    orden;
        char    campohost[LCAMPOHOST];
        char    campo[LCAMPO];
        char    desccampo[LDESCCAMPO];
        char    tabla[LTABLA];
        char    swtactivo[LSWTACTIVO];
        char    swtactualiza[LSWTACTUALIZA];
        char    accion[LACCION];
        long    longitud;
        char    tipodato[LTIPODATO];
        long    decimales;
        char    formateo[LFORMATEO];
        char    defecto[LDEFECTO];
        char    funcion[LFUNCION];
        char    libreria[LLIBRERIA];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    parametros[LPARAMETROS];
    } vdinterfaselins;

// Prototipos de funciones definidas en VDINTERFASELIN.C
VDEXPORT diccionario *INTLdamediccionario(void);
VDEXPORT int INTLbuscatipoformato(char *tipointerfase,char *formato,vdinterfaselins *intl);
VDEXPORT int INTLnexttipoformato(vdinterfaselins *intl);
VDEXPORT int INTLselvdinterfaselin(char *tipointerfase,char *formato,char *campo,char *tabla,vdinterfaselins *intl);
VDEXPORT char *INTLlog(vdinterfaselins *intl);
char * INTLdebug(vdinterfaselins *intl);
