// Modulo generado automaticamente a partir de VDLOTES.DEF

VDEXPORT diccionario dlot;
#define LOTNUMCOL	16
typedef struct {
        char    rowid[ROWIDLON];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    codlotprov[LCODLOTPROV];
        char    caduci[LCADUCI];
        char    retest[LRETEST];
        char    bloqlote[LBLOQLOTE];
        double  potencia;
        char    swtprecio[LSWTPRECIO];
        char    muestreado[LMUESTREADO];
        long    codcomen;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    status;
    } vdlotess;

// Prototipos de funciones definidas en VDLOTES.C
VDEXPORT diccionario *LOTdamediccionario(void);
VDEXPORT int LOTselcodlotartordr(char *codlot,char *codart,long status,vdlotess *lot);
VDEXPORT int LOTselvdlotes(char *codart,char *codlot,vdlotess *lot);
VDEXPORT int LOTactualizavdlotes(vdlotess *lot,int error);
VDEXPORT int LOTinsert(vdlotess *lot,int error);
VDEXPORT int LOTdel(vdlotess *lot,int error);
VDEXPORT int LOTinter(vdlotess *lot);
VDEXPORT char *LOTlog(vdlotess *lot);
char * LOTdebug(vdlotess *lot);
