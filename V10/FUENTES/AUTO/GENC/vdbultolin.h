// Modulo generado automaticamente a partir de VDBULTOLIN.DEF

VDEXPORT diccionario dbul;
#define BULNUMCOL	20
typedef struct {
        char    rowid[ROWIDLON];
        char    codbulto[LCODBULTO];
        long    seqlinea;
        char    codart[LCODART];
        long    codmov;
        long    codmovexp;
        char    codlot[LCODLOT];
        double  cantpedida;
        double  cantservida;
        char    numeroserie[LNUMEROSERIE];
        char    bulto[LBULTO];
        long    status;
        char    codopeprepara[LCODOPEPREPARA];
        long    fecprepara;
        char    horaprepara[LHORAPREPARA];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdbultolins;

// Prototipos de funciones definidas en VDBULTOLIN.C
VDEXPORT diccionario *BULdamediccionario(void);
VDEXPORT int BULbuscacodmov(long codmov,vdbultolins *bul);
VDEXPORT int BULnextcodmov(vdbultolins *bul);
VDEXPORT int BULbuscabulcodart(char *codbulto,char *codart,vdbultolins *bul);
VDEXPORT int BULnextbulcodart(vdbultolins *bul);
VDEXPORT int BULbuscabulcodartcodlot(char *codbulto,char *codart,char *codlot,vdbultolins *bul);
VDEXPORT int BULnextbulcodartcodlot(vdbultolins *bul);
VDEXPORT int BULbuscalinbulto(char *codbulto,vdbultolins *bul);
VDEXPORT int BULnextlinbulto(vdbultolins *bul);
VDEXPORT int BULbuscalinbulpdte(char *codbulto,vdbultolins *bul);
VDEXPORT int BULnextlinbulpdte(vdbultolins *bul);
VDEXPORT int BULselvdbultolin(char *codbulto,long seqlinea,vdbultolins *bul);
VDEXPORT int BULactualizacodmov(vdbultolins *bul,int error);
VDEXPORT int BULactualizacantpedida(vdbultolins *bul,int error);
VDEXPORT int BULinsert(vdbultolins *bul,int error);
VDEXPORT int BULdel(vdbultolins *bul,int error);
VDEXPORT char *BULlog(vdbultolins *bul);
char * BULdebug(vdbultolins *bul);
