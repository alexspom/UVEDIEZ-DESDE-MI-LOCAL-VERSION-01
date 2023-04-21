// Modulo generado automaticamente a partir de VDORDRECLIN.DEF

VDEXPORT diccionario dorl;
#define ORLNUMCOL	30
typedef struct {
        char    rowid[ROWIDLON];
        char    codordrec[LCODORDREC];
        char    coddiv[LCODDIV];
        long    seclinord;
        char    claveext[LCLAVEEXT];
        char    codart[LCODART];
        long    fecrecpre;
        double  cantidad;
        char    unidadeshost[LUNIDADESHOST];
        char    codlot[LCODLOT];
        char    tipolote[LTIPOLOTE];
        char    caduci[LCADUCI];
        char    vdextra[LVDEXTRA];
        double  tolerexc;
        double  tolerdef;
        long    status;
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    motivo;
        char    dvd_in[LDVD_IN];
        char    dvd_in_orden[LDVD_IN_ORDEN];
        char    hu_status[LHU_STATUS];
        char    codmat[LCODMAT];
        long    peso;
        long    alto;
        long    ancho;
        long    largo;
        char    codbulto[LCODBULTO];
    } vdordreclins;

// Prototipos de funciones definidas en VDORDRECLIN.C
VDEXPORT diccionario *ORLdamediccionario(void);
VDEXPORT int ORLselclave(char *codordrec,char *coddiv,long seclinord,vdordreclins *orl);
VDEXPORT int ORLselvdordreclin(char *codordrec,char *coddiv,long seclinord,vdordreclins *orl);
VDEXPORT int ORLactualizavdordreclin(vdordreclins *orl,int error);
VDEXPORT int ORLinsert(vdordreclins *orl,int error);
VDEXPORT int ORLdel(vdordreclins *orl,int error);
VDEXPORT int ORLinter(vdordreclins *orl);
VDEXPORT char *ORLlog(vdordreclins *orl);
char * ORLdebug(vdordreclins *orl);
