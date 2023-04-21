// Modulo generado automaticamente a partir de VDCONCEPTOFORM.DEF

VDEXPORT diccionario dcstk;
#define CSTKNUMCOL	19
typedef struct {
        char    rowid[ROWIDLON];
        char    tipoprop[LTIPOPROP];
        long    orden;
        char    destipoprop[LDESTIPOPROP];
        char    activo[LACTIVO];
        char    rangodiv[LRANGODIV];
        char    codclasif[LCODCLASIF];
        char    codclase[LCODCLASE];
        char    codconceent[LCODCONCEENT];
        char    codconcesal[LCODCONCESAL];
        char    fuente[LFUENTE];
        char    sumidero[LSUMIDERO];
        char    privilegios[LPRIVILEGIOS];
        long    cantmax;
        long    pvlmax;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdconceptoforms;

// Prototipos de funciones definidas en VDCONCEPTOFORM.C
VDEXPORT diccionario *CSTKdamediccionario(void);
VDEXPORT int CSTKselvdconceptoform(char *tipoprop,long orden,vdconceptoforms *cstk);
VDEXPORT char *CSTKlog(vdconceptoforms *cstk);
char * CSTKdebug(vdconceptoforms *cstk);
