// Modulo generado automaticamente a partir de VDGRAFICA.DEF

VDEXPORT diccionario dgra;
#define GRANUMCOL	12
typedef struct {
        char    rowid[ROWIDLON];
        char    nombregraf[LNOMBREGRAF];
        char    desgrafica[LDESGRAFICA];
        char    titulograf[LTITULOGRAF];
        char    leyendagraf[LLEYENDAGRAF];
        long    leyendaestado;
        char    campox[LCAMPOX];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdgraficas;

// Prototipos de funciones definidas en VDGRAFICA.C
VDEXPORT diccionario *GRAdamediccionario(void);
VDEXPORT int GRAselnombregraf(char *nombregraf,vdgraficas *gra);
VDEXPORT int GRAselvdgrafica(vdgraficas *gra);
VDEXPORT char *GRAlog(vdgraficas *gra);
char * GRAdebug(vdgraficas *gra);
