// Modulo generado automaticamente a partir de VDSERIEEXP.DEF

VDEXPORT diccionario dsex;
#define SEXNUMCOL	23
#define LCOMENSEX 1026
typedef struct {
        char    rowid[ROWIDLON];
        long    codserieexp;
        long    codserieprep;
        char    desserie[LDESSERIE];
        long    anoboleta;
        long    codboleta;
        char    codage[LCODAGE];
        long    puerto;
        long    prioridad;
        char    codopelanza[LCODOPELANZA];
        long    feclanza;
        char    horalanza[LHORALANZA];
        long    fectermin;
        char    horatermin[LHORATERMIN];
        long    fecexpide;
        char    horaexpide[LHORAEXPIDE];
        long    status;
        long    codcomen;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    comensex[LCOMENSEX];
    } vdserieexps;

// Prototipos de funciones definidas en VDSERIEEXP.C
VDEXPORT diccionario *SEXdamediccionario(void);
VDEXPORT int SEXbuscastatus(long status,vdserieexps *sex);
VDEXPORT int SEXnextstatus(vdserieexps *sex);
VDEXPORT int SEXselvdserieexp(long codserieexp,vdserieexps *sex);
VDEXPORT int SEXlock(vdserieexps *sex,int wait,int verificar,...);
VDEXPORT int SEXactualizastatus(vdserieexps *sex,int error);
VDEXPORT char *SEXlog(vdserieexps *sex);
char * SEXdebug(vdserieexps *sex);
