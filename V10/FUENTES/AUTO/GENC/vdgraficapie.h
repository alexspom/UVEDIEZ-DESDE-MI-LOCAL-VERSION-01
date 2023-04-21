// Modulo generado automaticamente a partir de VDGRAFICAPIE.DEF

VDEXPORT diccionario dgrap;
#define GRAPNUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    nombregraf[LNOMBREGRAF];
        long    numcolor;
        char    colorpie[LCOLORPIE];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdgraficapies;

// Prototipos de funciones definidas en VDGRAFICAPIE.C
VDEXPORT diccionario *GRAPdamediccionario(void);
VDEXPORT int GRAPbuscanombregraf(char *nombregraf,vdgraficapies *grap);
VDEXPORT int GRAPnextnombregraf(vdgraficapies *grap);
VDEXPORT int GRAPselvdgraficapie(vdgraficapies *grap);
VDEXPORT char *GRAPlog(vdgraficapies *grap);
char * GRAPdebug(vdgraficapies *grap);
