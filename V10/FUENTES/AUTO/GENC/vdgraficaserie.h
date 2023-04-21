// Modulo generado automaticamente a partir de VDGRAFICASERIE.DEF

VDEXPORT diccionario dgras;
#define GRASNUMCOL	31
typedef struct {
        char    rowid[ROWIDLON];
        char    nombregraf[LNOMBREGRAF];
        long    numserie;
        char    tiposerie[LTIPOSERIE];
        char    camposerie[LCAMPOSERIE];
        char    tituloserie[LTITULOSERIE];
        char    colorvalorserie[LCOLORVALORSERIE];
        long    anchovalorserie;
        long    opacidadvalorserie;
        long    anchobordeserie;
        long    opacidadborderserie;
        long    paddingx;
        long    paddingy;
        char    leyendaserie[LLEYENDASERIE];
        char    leyendaarbol[LLEYENDAARBOL];
        char    agruparbarras[LAGRUPARBARRAS];
        char    orientacion[LORIENTACION];
        long    tamanopunto;
        char    colorpunto[LCOLORPUNTO];
        long    anchobordepunto;
        char    colorbordepunto[LCOLORBORDEPUNTO];
        long    anchopie;
        long    altopie;
        char    posicionpie[LPOSICIONPIE];
        char    verlabelpie[LVERLABELPIE];
        char    csslabelpie[LCSSLABELPIE];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdgraficaseries;

// Prototipos de funciones definidas en VDGRAFICASERIE.C
VDEXPORT diccionario *GRASdamediccionario(void);
VDEXPORT int GRASbuscanombregraf(char *nombregraf,vdgraficaseries *gras);
VDEXPORT int GRASnextnombregraf(vdgraficaseries *gras);
VDEXPORT int GRASselvdgraficaserie(vdgraficaseries *gras);
VDEXPORT char *GRASlog(vdgraficaseries *gras);
char * GRASdebug(vdgraficaseries *gras);
