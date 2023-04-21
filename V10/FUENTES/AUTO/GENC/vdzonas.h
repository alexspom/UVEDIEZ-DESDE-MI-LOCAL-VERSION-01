// Modulo generado automaticamente a partir de VDZONAS.DEF

VDEXPORT diccionario dzon;
#define ZONNUMCOL	41
typedef struct {
        char    rowid[ROWIDLON];
        long    codzona;
        char    deszona[LDESZONA];
        char    tipozona[LTIPOZONA];
        char    activa[LACTIVA];
        long    priozona;
        long    idinfogest;
        long    idinfopick;
        long    numdisp;
        long    maxoper;
        long    maxbultosoper;
        long    dispiluminados;
        long    redscan;
        long    scanner;
        long    maxcapacidad;
        char    autoapertura[LAUTOAPERTURA];
        long    tiempook;
        long    tiempofin;
        char    nexttick[LNEXTTICK];
        char    privpicking[LPRIVPICKING];
        char    procesozona[LPROCESOZONA];
        char    procesodisp[LPROCESODISP];
        char    idmenu[LIDMENU];
        long    status;
        char    codope[LCODOPE];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    rangotipovol[LRANGOTIPOVOL];
        long    codmov;
        long    numbasc;
        char    activabasc[LACTIVABASC];
        char    codimpre[LCODIMPRE];
        double  cantquedabasc;
        long    menuprin;
        char    datosmenu[LDATOSMENU];
        char    textomenu[LTEXTOMENU];
        long    capacidad;
        char    colorzona[LCOLORZONA];
    } vdzonass;

// Prototipos de funciones definidas en VDZONAS.C
VDEXPORT diccionario *ZONdamediccionario(void);
VDEXPORT int ZONselscanner(long redscan,long scanner,vdzonass *zon);
VDEXPORT int ZONselnumdisp(long idinfopick,long numdisp,vdzonass *zon);
VDEXPORT int ZONbuscatick(long idinfogest,vdzonass *zon);
VDEXPORT int ZONnexttick(vdzonass *zon);
VDEXPORT int ZONselvdzonas(long codzona,vdzonass *zon);
VDEXPORT int ZONactualizacodope(vdzonass *zon,int error);
VDEXPORT int ZONactualizaidmenu(vdzonass *zon,int error);
VDEXPORT int ZONactualizastatus(vdzonass *zon,int error);
VDEXPORT int ZONactualizaprocesos(vdzonass *zon,int error);
VDEXPORT int ZONinsert(vdzonass *zon,int error);
VDEXPORT int ZONdel(vdzonass *zon,int error);
VDEXPORT char *ZONlog(vdzonass *zon);
char * ZONdebug(vdzonass *zon);
