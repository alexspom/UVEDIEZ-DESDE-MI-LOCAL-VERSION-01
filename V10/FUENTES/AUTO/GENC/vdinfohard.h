// Modulo generado automaticamente a partir de VDINFOHARD.DEF

VDEXPORT diccionario diha;
#define IHANUMCOL	38
typedef struct {
        char    rowid[ROWIDLON];
        long    idinfopick;
        long    delaycab;
        long    delaycar;
        long    prepeat;
        long    srepeat;
        long    tparpade;
        long    tparpada;
        long    maxerror;
        long    ratioerr;
        long    statgaps;
        long    tciclo;
        long    limitelinea;
        long    tenvtrama;
        long    timeouttrama;
        long    timeoutwho;
        char    dirip1[LDIRIP1];
        char    dirip2[LDIRIP2];
        char    dirip3[LDIRIP3];
        char    dirip4[LDIRIP4];
        char    dirip5[LDIRIP5];
        char    dirip6[LDIRIP6];
        char    dirip7[LDIRIP7];
        char    dirip8[LDIRIP8];
        char    dirip9[LDIRIP9];
        char    dirip10[LDIRIP10];
        char    dirip11[LDIRIP11];
        char    dirip12[LDIRIP12];
        char    dirip13[LDIRIP13];
        char    dirip14[LDIRIP14];
        char    dirip15[LDIRIP15];
        char    libproceso[LLIBPROCESO];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    rangolineas[LRANGOLINEAS];
    } vdinfohards;

// Prototipos de funciones definidas en VDINFOHARD.C
VDEXPORT diccionario *IHAdamediccionario(void);
VDEXPORT int IHAselvdinfohard(long idinfopick,vdinfohards *iha);
VDEXPORT char *IHAlog(vdinfohards *iha);
char * IHAdebug(vdinfohards *iha);
