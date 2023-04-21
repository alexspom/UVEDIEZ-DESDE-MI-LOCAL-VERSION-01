// Modulo generado automaticamente a partir de VDSTOCK.DEF

VDEXPORT diccionario dstk;
#define STKNUMCOL	21
typedef struct {
        char    rowid[ROWIDLON];
        char    codmat[LCODMAT];
        long    ordenstk;
        char    bulto[LBULTO];
        char    marcastk[LMARCASTK];
        char    numeroserie[LNUMEROSERIE];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  cantidad;
        char    bloqueos[LBLOQUEOS];
        char    tipoemba[LTIPOEMBA];
        double  uniemb;
        long    embcont;
        double  preciouni;
        double  pesouni;
        char    codrecep[LCODRECEP];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        double  gencount;
    } vdstocks;

// Prototipos de funciones definidas en VDSTOCK.C
VDEXPORT diccionario *STKdamediccionario(void);
VDEXPORT int STKselcontns(char *codmat,vdstocks *stk);
VDEXPORT int STKbuscacodmat(char *codmat,vdstocks *stk);
VDEXPORT int STKnextcodmat(vdstocks *stk);
VDEXPORT int STKselvdstock(char *codmat,long ordenstk,vdstocks *stk);
VDEXPORT int STKactualizamatricula(vdstocks *stk,int error);
VDEXPORT char *STKlog(vdstocks *stk);
char * STKdebug(vdstocks *stk);
