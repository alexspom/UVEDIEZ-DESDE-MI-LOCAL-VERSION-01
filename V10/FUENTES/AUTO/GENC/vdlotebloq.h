// Modulo generado automaticamente a partir de VDLOTEBLOQ.DEF

VDEXPORT diccionario dlblo;
#define LBLONUMCOL	15
#define LMIROWID 1
typedef struct {
        char    rowid[ROWIDLON];
        long    seqbloq;
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  cantidad;
        char    codmat[LCODMAT];
        char    codrecep[LCODRECEP];
        char    bulto[LBULTO];
        char    bloqini[LBLOQINI];
        char    bloqfin[LBLOQFIN];
        char    tipobloq[LTIPOBLOQ];
        long    status;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdlotebloqs;

// Prototipos de funciones definidas en VDLOTEBLOQ.C
VDEXPORT diccionario *LBLOdamediccionario(void);
VDEXPORT int LBLOselseqbloq(long seqbloq,vdlotebloqs *lblo);
VDEXPORT int LBLObuscastatus(long status,vdlotebloqs *lblo);
VDEXPORT int LBLOnextstatus(vdlotebloqs *lblo);
VDEXPORT int LBLOselrowid(char *mirowid,vdlotebloqs *lblo);
VDEXPORT int LBLOselvdlotebloq(vdlotebloqs *lblo);
VDEXPORT int LBLOlock(vdlotebloqs *lblo,int wait,int verificar,...);
VDEXPORT int LBLOactualizatratado(vdlotebloqs *lblo,int error);
VDEXPORT int LBLOselvdseclotebloq(long *donde);
VDEXPORT int LBLOinsert(vdlotebloqs *lblo,int error);
VDEXPORT int LBLOinter(vdlotebloqs *lblo);
VDEXPORT char *LBLOlog(vdlotebloqs *lblo);
char * LBLOdebug(vdlotebloqs *lblo);
