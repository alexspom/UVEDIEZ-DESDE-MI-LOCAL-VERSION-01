// Modulo generado automaticamente a partir de VDINTERFCARGACAB.DEF

VDEXPORT diccionario dicc;
#define ICCNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        long    codinterfase;
        char    tipointerfase[LTIPOINTERFASE];
        char    formato[LFORMATO];
        char    fichero[LFICHERO];
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdinterfcargacabs;

// Prototipos de funciones definidas en VDINTERFCARGACAB.C
VDEXPORT diccionario *ICCdamediccionario(void);
VDEXPORT int ICCselcodinterfase(char *tipointerfase,char *formato,char *fichero,vdinterfcargacabs *icc);
VDEXPORT int ICCselfmtofich(char *formato,char *fichero,vdinterfcargacabs *icc);
VDEXPORT int ICCselvdinterfcargacab(long codinterfase,vdinterfcargacabs *icc);
VDEXPORT int ICCactualizastatus(vdinterfcargacabs *icc,int error);
VDEXPORT int ICCselvdsecinterf(long *donde);
VDEXPORT int ICCinsert(vdinterfcargacabs *icc,int error);
VDEXPORT int ICCdel(vdinterfcargacabs *icc,int error);
VDEXPORT char *ICClog(vdinterfcargacabs *icc);
char * ICCdebug(vdinterfcargacabs *icc);
