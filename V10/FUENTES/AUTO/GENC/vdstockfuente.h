// Modulo generado automaticamente a partir de VDSTOCKFUENTE.DEF

VDEXPORT diccionario dfte;
#define FTENUMCOL	36
#define LCOMEN 1026
typedef struct {
        char    rowid[ROWIDLON];
        long    seqfuente;
        char    tipofuente[LTIPOFUENTE];
        char    codubi[LCODUBI];
        char    codmat[LCODMAT];
        char    tipoconte[LTIPOCONTE];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    cantidadhost[LCANTIDADHOST];
        char    unidadeshost[LUNIDADESHOST];
        char    uniembhost[LUNIEMBHOST];
        long    embcont;
        char    tipoemba[LTIPOEMBA];
        double  preciouni;
        char    bloqueos[LBLOQUEOS];
        char    bulto[LBULTO];
        char    marcastk[LMARCASTK];
        char    numeroserie[LNUMEROSERIE];
        char    codrecep[LCODRECEP];
        double  pesouni;
        char    codlotprov[LCODLOTPROV];
        char    caduci[LCADUCI];
        char    retest[LRETEST];
        char    bloqlote[LBLOQLOTE];
        double  potencia;
        char    swtprecio[LSWTPRECIO];
        char    muestreado[LMUESTREADO];
        long    status;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    fecentrada;
        char    horaentrada[LHORAENTRADA];
        char    comen[LCOMEN];
    } vdstockfuentes;

// Prototipos de funciones definidas en VDSTOCKFUENTE.C
VDEXPORT diccionario *FTEdamediccionario(void);
VDEXPORT int FTEbuscastatus(long status,vdstockfuentes *fte);
VDEXPORT int FTEnextstatus(vdstockfuentes *fte);
VDEXPORT int FTEselvdstockfuente(long seqfuente,vdstockfuentes *fte);
VDEXPORT int FTElock(vdstockfuentes *fte,int wait,int verificar,...);
VDEXPORT int FTEactualizastatus(vdstockfuentes *fte,int error);
VDEXPORT int FTEactualizavdstockfuente(vdstockfuentes *fte,int error);
VDEXPORT int FTEinsert(vdstockfuentes *fte,int error);
VDEXPORT int FTEdel(vdstockfuentes *fte,int error);
VDEXPORT int FTEinter(vdstockfuentes *fte);
VDEXPORT char *FTElog(vdstockfuentes *fte);
char * FTEdebug(vdstockfuentes *fte);
