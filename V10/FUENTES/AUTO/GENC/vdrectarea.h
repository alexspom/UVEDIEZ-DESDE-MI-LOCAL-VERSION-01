// Modulo generado automaticamente a partir de VDRECTAREA.DEF

VDEXPORT diccionario dret;
#define RETNUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    codrecurso[LCODRECURSO];
        char    codperfil[LCODPERFIL];
        long    priotarea;
        char    activa[LACTIVA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdrectareas;

// Prototipos de funciones definidas en VDRECTAREA.C
VDEXPORT diccionario *RETdamediccionario(void);
VDEXPORT int RETbuscacodrecurso(char *codrecurso,vdrectareas *ret);
VDEXPORT int RETnextcodrecurso(vdrectareas *ret);
VDEXPORT int RETselvdrectarea(char *codrecurso,char *codperfil,vdrectareas *ret);
VDEXPORT char *RETlog(vdrectareas *ret);
char * RETdebug(vdrectareas *ret);
