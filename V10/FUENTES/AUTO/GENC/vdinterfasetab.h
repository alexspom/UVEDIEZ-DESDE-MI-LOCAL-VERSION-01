// Modulo generado automaticamente a partir de VDINTERFASETAB.DEF

VDEXPORT diccionario dintt;
#define INTTNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        char    tabla[LTABLA];
        char    tablaalias[LTABLAALIAS];
        char    abreviatura[LABREVIATURA];
        long    ordeninsupd;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    libreria[LLIBRERIA];
        long    codcomen;
    } vdinterfasetabs;

// Prototipos de funciones definidas en VDINTERFASETAB.C
VDEXPORT diccionario *INTTdamediccionario(void);
VDEXPORT int INTTbuscatodo(vdinterfasetabs *intt);
VDEXPORT int INTTnexttodo(vdinterfasetabs *intt);
VDEXPORT int INTTselvdinterfasetab(char *tabla,char *tablaalias,vdinterfasetabs *intt);
VDEXPORT char *INTTlog(vdinterfasetabs *intt);
char * INTTdebug(vdinterfasetabs *intt);
