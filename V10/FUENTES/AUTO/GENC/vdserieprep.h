// Modulo generado automaticamente a partir de VDSERIEPREP.DEF

VDEXPORT diccionario dspr;
#define SPRNUMCOL	27
#define LCOMENSPR 1026
typedef struct {
        char    rowid[ROWIDLON];
        long    codserieprep;
        long    prioridad;
        char    swtpickinginv[LSWTPICKINGINV];
        char    swtpickingagr[LSWTPICKINGAGR];
        char    desserie[LDESSERIE];
        char    rangozonaspickinv[LRANGOZONASPICKINV];
        char    tipopuerto[LTIPOPUERTO];
        char    codopecreada[LCODOPECREADA];
        long    feccreada;
        char    horacreada[LHORACREADA];
        char    codopelanza[LCODOPELANZA];
        long    feclanza;
        char    horalanza[LHORALANZA];
        long    fectermin;
        char    horatermin[LHORATERMIN];
        long    status;
        long    codcomen;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    codopecierre[LCODOPECIERRE];
        long    feccierre;
        char    horacierre[LHORACIERRE];
        char    swtbloqetiq[LSWTBLOQETIQ];
        char    comenspr[LCOMENSPR];
    } vdseriepreps;

// Prototipos de funciones definidas en VDSERIEPREP.C
VDEXPORT diccionario *SPRdamediccionario(void);
VDEXPORT int SPRbuscastatus(long status,vdseriepreps *spr);
VDEXPORT int SPRnextstatus(vdseriepreps *spr);
VDEXPORT int SPRselvdserieprep(long codserieprep,vdseriepreps *spr);
VDEXPORT int SPRlock(vdseriepreps *spr,int wait,int verificar,...);
VDEXPORT int SPRactualizastatus(vdseriepreps *spr,int error);
VDEXPORT char *SPRlog(vdseriepreps *spr);
char * SPRdebug(vdseriepreps *spr);
