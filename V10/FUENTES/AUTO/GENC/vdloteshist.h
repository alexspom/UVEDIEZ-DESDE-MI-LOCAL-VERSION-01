// Modulo generado automaticamente a partir de VDLOTESHIST.DEF

VDEXPORT diccionario dloh;
#define LOHNUMCOL	27
#define LCOMENLOH 1025
typedef struct {
        char    rowid[ROWIDLON];
        long    seq;
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    caduciactual[LCADUCIACTUAL];
        char    retestactual[LRETESTACTUAL];
        char    bloqloteactual[LBLOQLOTEACTUAL];
        char    caducinuevo[LCADUCINUEVO];
        char    retestnuevo[LRETESTNUEVO];
        char    bloqlotenuevo[LBLOQLOTENUEVO];
        long    status;
        char    codopeins[LCODOPEINS];
        char    moduloins[LMODULOINS];
        char    accionins[LACCIONINS];
        long    fecins;
        char    horains[LHORAINS];
        char    modulofin[LMODULOFIN];
        char    accionfin[LACCIONFIN];
        long    fecfin;
        char    horafin[LHORAFIN];
        long    codcomen;
        char    vdextra[LVDEXTRA];
        long    coddocumento;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    comenloh[LCOMENLOH];
    } vdloteshists;

// Prototipos de funciones definidas en VDLOTESHIST.C
VDEXPORT diccionario *LOHdamediccionario(void);
VDEXPORT int LOHbuscastatus(long status,vdloteshists *loh);
VDEXPORT int LOHnextstatus(vdloteshists *loh);
VDEXPORT int LOHselvdloteshist(long seq,vdloteshists *loh);
VDEXPORT int LOHlock(vdloteshists *loh,int wait,int verificar,...);
VDEXPORT int LOHactualizatratado(vdloteshists *loh,int error);
VDEXPORT char *LOHlog(vdloteshists *loh);
char * LOHdebug(vdloteshists *loh);
