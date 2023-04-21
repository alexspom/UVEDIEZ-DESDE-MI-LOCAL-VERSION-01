// Modulo generado automaticamente a partir de VDTAREAS.DEF

VDEXPORT diccionario dtar;
#define TARNUMCOL	8
typedef struct {
        char    rowid[ROWIDLON];
        char    tarea[LTAREA];
        char    destarea[LDESTAREA];
        char    codclasif[LCODCLASIF];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdtareass;

// Prototipos de funciones definidas en VDTAREAS.C
VDEXPORT diccionario *TARdamediccionario(void);
VDEXPORT int TARselvdtareas(char *tarea,vdtareass *tar);
VDEXPORT char *TARlog(vdtareass *tar);
char * TARdebug(vdtareass *tar);
