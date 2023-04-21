// Modulo generado automaticamente a partir de VDSCANLECT.DEF

VDEXPORT diccionario dscl;
#define SCLNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        long    seqaccion;
        long    redscan;
        long    scanner;
        char    texto[LTEXTO];
        long    status;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    idinfogest;
    } vdscanlects;

// Prototipos de funciones definidas en VDSCANLECT.C
VDEXPORT diccionario *SCLdamediccionario(void);
VDEXPORT int SCLbuscaidinfogest(long idinfogest,vdscanlects *scl);
VDEXPORT int SCLnextidinfogest(vdscanlects *scl);
VDEXPORT int SCLbuscaescanerystatus(long status,vdscanlects *scl);
VDEXPORT int SCLnextescanerystatus(vdscanlects *scl);
VDEXPORT int SCLselvdscanlect(long seqaccion,vdscanlects *scl);
VDEXPORT int SCLactualizastatus(vdscanlects *scl,int error);
VDEXPORT int SCLselvdsecscanlect(long *donde);
VDEXPORT int SCLinsert(vdscanlects *scl,int error);
VDEXPORT int SCLdel(vdscanlects *scl,int error);
VDEXPORT char *SCLlog(vdscanlects *scl);
char * SCLdebug(vdscanlects *scl);
