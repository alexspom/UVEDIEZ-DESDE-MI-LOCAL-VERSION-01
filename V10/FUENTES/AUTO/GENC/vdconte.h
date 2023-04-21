// Modulo generado automaticamente a partir de VDCONTE.DEF

VDEXPORT diccionario dcnt;
#define CNTNUMCOL	23
#define LPTRMSG 1026
typedef struct {
        char    rowid[ROWIDLON];
        char    codmat[LCODMAT];
        char    tipoconte[LTIPOCONTE];
        char    cntsscc[LCNTSSCC];
        char    codubi[LCODUBI];
        long    posconte;
        long    alturaconte;
        long    status;
        long    fecentrada;
        char    horaentrada[LHORAENTRADA];
        long    feccreado;
        char    horacreado[LHORACREADO];
        char    vdextra[LVDEXTRA];
        char    claveext[LCLAVEEXT];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    pesoconte;
        long    largoconte;
        long    anchoconte;
        char    ptrmsg[LPTRMSG];
        long    seccnt;
    } vdcontes;

// Prototipos de funciones definidas en VDCONTE.C
VDEXPORT diccionario *CNTdamediccionario(void);
VDEXPORT int CNTselvdconte(char *codmat,vdcontes *cnt);
VDEXPORT int CNTlock(vdcontes *cnt,int wait,int verificar,...);
VDEXPORT int CNTactualizastatus(vdcontes *cnt,int error);
VDEXPORT int CNTselvdseccnt(long *donde);
VDEXPORT int CNTinsert(vdcontes *cnt,int error);
VDEXPORT int CNTdel(vdcontes *cnt,int error);
VDEXPORT char *CNTlog(vdcontes *cnt);
char * CNTdebug(vdcontes *cnt);
