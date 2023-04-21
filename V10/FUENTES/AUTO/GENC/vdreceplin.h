// Modulo generado automaticamente a partir de VDRECEPLIN.DEF

VDEXPORT diccionario dlre;
#define LRENUMCOL	21
typedef struct {
        char    rowid[ROWIDLON];
        char    codrecep[LCODRECEP];
        long    seclinrec;
        char    codordrec[LCODORDREC];
        char    coddiv[LCODDIV];
        long    seclinord;
        char    codart[LCODART];
        char    claveext[LCLAVEEXT];
        double  cantidadr;
        double  cantidadt;
        char    codlot[LCODLOT];
        char    caduci[LCADUCI];
        char    bloqstock[LBLOQSTOCK];
        long    codcomen;
        char    vdextra[LVDEXTRA];
        char    observacion1[LOBSERVACION1];
        char    observacion2[LOBSERVACION2];
        char    muestreado[LMUESTREADO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        double  gensum;
    } vdreceplins;

// Prototipos de funciones definidas en VDRECEPLIN.C
VDEXPORT diccionario *LREdamediccionario(void);
VDEXPORT int LREselcantrecep(char *codordrec,char *coddiv,long seclinord,vdreceplins *lre);
VDEXPORT int LREselvdreceplin(char *codrecep,long seclinrec,vdreceplins *lre);
VDEXPORT char *LRElog(vdreceplins *lre);
char * LREdebug(vdreceplins *lre);
