// Modulo generado automaticamente a partir de VDDEMANDATIPO.DEF

VDEXPORT diccionario ddemt;
#define DEMTNUMCOL	7
typedef struct {
        char    rowid[ROWIDLON];
        char    tipodemanda[LTIPODEMANDA];
        char    destipo[LDESTIPO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vddemandatipos;

// Prototipos de funciones definidas en VDDEMANDATIPO.C
VDEXPORT diccionario *DEMTdamediccionario(void);
VDEXPORT int DEMTselvddemandatipo(char *tipodemanda,vddemandatipos *demt);
VDEXPORT char *DEMTlog(vddemandatipos *demt);
char * DEMTdebug(vddemandatipos *demt);
