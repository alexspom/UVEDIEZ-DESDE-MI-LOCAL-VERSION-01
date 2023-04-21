// Modulo generado automaticamente a partir de VDGRAFICAEJE.DEF

VDEXPORT diccionario dgrae;
#define GRAENUMCOL	26
typedef struct {
        char    rowid[ROWIDLON];
        char    nombregraf[LNOMBREGRAF];
        char    eje[LEJE];
        char    tituloeje[LTITULOEJE];
        long    maxvalor;
        long    minvalor;
        char    cssvalores[LCSSVALORES];
        char    csstitulo[LCSSTITULO];
        char    cursortexto[LCURSORTEXTO];
        char    cursorcolor[LCURSORCOLOR];
        char    cursortextcolor[LCURSORTEXTCOLOR];
        char    cursorcss[LCURSORCSS];
        long    gridgrosor;
        char    gridcolor[LGRIDCOLOR];
        long    gridopacidad;
        char    valoresmoneda[LVALORESMONEDA];
        long    valoresmindec;
        long    valoresmaxdec;
        char    valorespos[LVALORESPOS];
        char    valoressepdec[LVALORESSEPDEC];
        char    valoressepmil[LVALORESSEPMIL];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdgraficaejes;

// Prototipos de funciones definidas en VDGRAFICAEJE.C
VDEXPORT diccionario *GRAEdamediccionario(void);
VDEXPORT int GRAEbuscanombregraf(char *nombregraf,vdgraficaejes *grae);
VDEXPORT int GRAEnextnombregraf(vdgraficaejes *grae);
VDEXPORT int GRAEselvdgraficaeje(vdgraficaejes *grae);
VDEXPORT char *GRAElog(vdgraficaejes *grae);
char * GRAEdebug(vdgraficaejes *grae);
