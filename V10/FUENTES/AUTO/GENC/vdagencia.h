// Modulo generado automaticamente a partir de VDAGENCIA.DEF

VDEXPORT diccionario dag;
#define AGNUMCOL	24
typedef struct {
        char    rowid[ROWIDLON];
        char    codage[LCODAGE];
        char    desage[LDESAGE];
        char    grupoage[LGRUPOAGE];
        char    servicio[LSERVICIO];
        char    producto[LPRODUCTO];
        char    sufijodoc[LSUFIJODOC];
        long    numbol;
        long    numalba;
        long    numfac;
        long    puerto;
        char    buzonout[LBUZONOUT];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    codagerecep[LCODAGERECEP];
        long    numbolind;
        char    agrupaserie[LAGRUPASERIE];
        char    codageexp[LCODAGEEXP];
        char    nombresecuen[LNOMBRESECUEN];
        char    nombrelogo[LNOMBRELOGO];
        long    claveinci;
    } vdagencias;

// Prototipos de funciones definidas en VDAGENCIA.C
VDEXPORT diccionario *AGdamediccionario(void);
VDEXPORT int AGselcodage(char *codage,vdagencias *ag);
VDEXPORT int AGselvdagencia(char *codage,vdagencias *ag);
VDEXPORT char *AGlog(vdagencias *ag);
char * AGdebug(vdagencias *ag);
