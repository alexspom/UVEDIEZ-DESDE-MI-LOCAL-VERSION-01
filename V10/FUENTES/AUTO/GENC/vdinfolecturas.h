// Modulo generado automaticamente a partir de VDINFOLECTURAS.DEF

VDEXPORT diccionario dilt;
#define ILTNUMCOL	17
typedef struct {
        char    rowid[ROWIDLON];
        long    idinfolectura;
        char    dirip[LDIRIP];
        char    puertotcp[LPUERTOTCP];
        long    puerto232;
        long    velocidad;
        char    chstx[LCHSTX];
        char    chetx[LCHETX];
        char    chsoh[LCHSOH];
        long    lonidscan;
        long    londata;
        char    libproceso[LLIBPROCESO];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdinfolecturass;

// Prototipos de funciones definidas en VDINFOLECTURAS.C
VDEXPORT diccionario *ILTdamediccionario(void);
VDEXPORT int ILTselvdinfolecturas(long idinfolectura,vdinfolecturass *ilt);
VDEXPORT char *ILTlog(vdinfolecturass *ilt);
char * ILTdebug(vdinfolecturass *ilt);
