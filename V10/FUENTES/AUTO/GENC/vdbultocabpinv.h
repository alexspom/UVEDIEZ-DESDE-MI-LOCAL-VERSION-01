// Modulo generado automaticamente a partir de VDBULTOCABPINV.DEF

VDEXPORT diccionario dbpc;
#define BPCNUMCOL	24
typedef struct {
        char    rowid[ROWIDLON];
        char    codbulto[LCODBULTO];
        char    codmat[LCODMAT];
        char    cajacompleta[LCAJACOMPLETA];
        long    feccreado;
        char    horacreado[LHORACREADO];
        long    fecfinaliza;
        char    horafinaliza[LHORAFINALIZA];
        long    status;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    tarabulto;
        long    pesobulto;
        char    monoref[LMONOREF];
        char    observ[LOBSERV];
        char    verifforzada[LVERIFFORZADA];
        long    largobulto;
        long    altobulto;
        long    anchobulto;
        char    destinoplc[LDESTINOPLC];
        char    puntoplc[LPUNTOPLC];
    } vdbultocabpinvs;

// Prototipos de funciones definidas en VDBULTOCABPINV.C
VDEXPORT diccionario *BPCdamediccionario(void);
VDEXPORT int BPCselcodmat(char *codmat,vdbultocabpinvs *bpc);
VDEXPORT int BPCbuscastatus(long status,vdbultocabpinvs *bpc);
VDEXPORT int BPCnextstatus(vdbultocabpinvs *bpc);
VDEXPORT int BPCbuscacodmatactiva(char *codmat,long status,vdbultocabpinvs *bpc);
VDEXPORT int BPCnextcodmatactiva(vdbultocabpinvs *bpc);
VDEXPORT int BPCselvdbultocabpinv(char *codbulto,vdbultocabpinvs *bpc);
VDEXPORT int BPClock(vdbultocabpinvs *bpc,int wait,int verificar,...);
VDEXPORT int BPCactualizastatus(vdbultocabpinvs *bpc,int error);
VDEXPORT char *BPClog(vdbultocabpinvs *bpc);
char * BPCdebug(vdbultocabpinvs *bpc);
