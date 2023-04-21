// Modulo generado automaticamente a partir de VDORDENADORES.DEF

VDEXPORT diccionario dord;
#define ORDNUMCOL	10
typedef struct {
        char    rowid[ROWIDLON];
        char    ordenador[LORDENADOR];
        long    idinfolectura;
        long    scanner;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    numbasc;
    } vdordenadoress;

// Prototipos de funciones definidas en VDORDENADORES.C
VDEXPORT diccionario *ORDdamediccionario(void);
VDEXPORT int ORDselvdordenadores(char *ordenador,vdordenadoress *ord);
VDEXPORT char *ORDlog(vdordenadoress *ord);
char * ORDdebug(vdordenadoress *ord);
