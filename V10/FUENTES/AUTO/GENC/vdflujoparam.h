// Modulo generado automaticamente a partir de VDFLUJOPARAM.DEF

VDEXPORT diccionario dflp;
#define FLPNUMCOL	19
typedef struct {
        char    rowid[ROWIDLON];
        long    codflujo;
        char    tarea[LTAREA];
        char    codareaori[LCODAREAORI];
        char    codareadest[LCODAREADEST];
        char    codclasif[LCODCLASIF];
        char    codclase[LCODCLASE];
        char    patronestado[LPATRONESTADO];
        char    codconce[LCODCONCE];
        long    prioflujo;
        long    subprioflujo;
        long    priomov;
        char    tipostatus[LTIPOSTATUS];
        char    dabstatus[LDABSTATUS];
        long    codcamino;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdflujoparams;

// Prototipos de funciones definidas en VDFLUJOPARAM.C
VDEXPORT diccionario *FLPdamediccionario(void);
VDEXPORT int FLPselvdflujoparam(long codflujo,vdflujoparams *flp);
VDEXPORT char *FLPlog(vdflujoparams *flp);
char * FLPdebug(vdflujoparams *flp);
