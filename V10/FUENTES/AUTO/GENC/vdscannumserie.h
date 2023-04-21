// Modulo generado automaticamente a partir de VDSCANNUMSERIE.DEF

VDEXPORT diccionario dnsl;
#define NSLNUMCOL	10
typedef struct {
        char    rowid[ROWIDLON];
        char    codope[LCODOPE];
        char    codrecurso[LCODRECURSO];
        long    codzona;
        char    numeroserie[LNUMEROSERIE];
        char    codmat[LCODMAT];
        char    recepcionado[LRECEPCIONADO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        double  gencount;
    } vdscannumseries;

// Prototipos de funciones definidas en VDSCANNUMSERIE.C
VDEXPORT diccionario *NSLdamediccionario(void);
VDEXPORT int NSLselcontns(char *codmat,vdscannumseries *nsl);
VDEXPORT int NSLbuscacodmat(char *codmat,vdscannumseries *nsl);
VDEXPORT int NSLnextcodmat(vdscannumseries *nsl);
VDEXPORT int NSLselvdscannumserie(vdscannumseries *nsl);
VDEXPORT int NSLdel(vdscannumseries *nsl,int error);
VDEXPORT char *NSLlog(vdscannumseries *nsl);
char * NSLdebug(vdscannumseries *nsl);
