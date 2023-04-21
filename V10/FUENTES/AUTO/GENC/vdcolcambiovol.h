// Modulo generado automaticamente a partir de VDCOLCAMBIOVOL.DEF

VDEXPORT diccionario dccv;
#define CCVNUMCOL	8
typedef struct {
        char    rowid[ROWIDLON];
        char    codcolcambiovol[LCODCOLCAMBIOVOL];
        char    tipovolorig[LTIPOVOLORIG];
        char    tipovoldest[LTIPOVOLDEST];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdcolcambiovols;

// Prototipos de funciones definidas en VDCOLCAMBIOVOL.C
VDEXPORT diccionario *CCVdamediccionario(void);
VDEXPORT int CCVselcodcolcambiovol(char *codcolcambiovol,vdcolcambiovols *ccv);
VDEXPORT int CCVbuscatipovolorig(char *codcolcambiovol,char *tipovolorig,vdcolcambiovols *ccv);
VDEXPORT int CCVnexttipovolorig(vdcolcambiovols *ccv);
VDEXPORT int CCVselvdcolcambiovol(char *codcolcambiovol,char *tipovolorig,char *tipovoldest,vdcolcambiovols *ccv);
VDEXPORT int CCVinsert(vdcolcambiovols *ccv,int error);
VDEXPORT int CCVdel(vdcolcambiovols *ccv,int error);
VDEXPORT char *CCVlog(vdcolcambiovols *ccv);
char * CCVdebug(vdcolcambiovols *ccv);
