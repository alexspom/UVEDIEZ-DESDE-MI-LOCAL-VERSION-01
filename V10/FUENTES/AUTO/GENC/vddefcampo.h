// Modulo generado automaticamente a partir de VDDEFCAMPO.DEF

VDEXPORT diccionario ddec;
#define DECNUMCOL	20
typedef struct {
        char    rowid[ROWIDLON];
        char    ncampo[LNCAMPO];
        char    tipopantalla[LTIPOPANTALLA];
        char    ttitulo[LTTITULO];
        char    ttooltip[LTTOOLTIP];
        char    ftooltip[LFTOOLTIP];
        char    fconvierte[LFCONVIERTE];
        char    capitaliza[LCAPITALIZA];
        char    fcontextual[LFCONTEXTUAL];
        char    estraducible[LESTRADUCIBLE];
        char    esscan[LESSCAN];
        char    fpostchange[LFPOSTCHANGE];
        char    ftecla[LFTECLA];
        char    privmodif[LPRIVMODIF];
        char    privver[LPRIVVER];
        char    fauxiliar[LFAUXILIAR];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vddefcampos;

// Prototipos de funciones definidas en VDDEFCAMPO.C
VDEXPORT diccionario *DECdamediccionario(void);
VDEXPORT int DECselncampo(char *ncampo,char *tipopantalla,vddefcampos *dec);
VDEXPORT int DECselvddefcampo(char *ncampo,char *tipopantalla,vddefcampos *dec);
VDEXPORT char *DEClog(vddefcampos *dec);
char * DECdebug(vddefcampos *dec);
