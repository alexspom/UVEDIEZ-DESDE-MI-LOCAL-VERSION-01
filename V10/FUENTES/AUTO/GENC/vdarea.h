// Modulo generado automaticamente a partir de VDAREA.DEF

VDEXPORT diccionario dare;
#define ARENUMCOL	10
typedef struct {
        char    rowid[ROWIDLON];
        char    codarea[LCODAREA];
        char    codalm[LCODALM];
        char    desarea[LDESAREA];
        long    ordenarea;
        char    codarearef[LCODAREAREF];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdareas;

// Prototipos de funciones definidas en VDAREA.C
VDEXPORT diccionario *AREdamediccionario(void);
VDEXPORT int AREselvdarea(char *codarea,vdareas *are);
VDEXPORT char *ARElog(vdareas *are);
char * AREdebug(vdareas *are);
