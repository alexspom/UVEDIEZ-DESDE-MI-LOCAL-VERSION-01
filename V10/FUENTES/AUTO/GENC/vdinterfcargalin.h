// Modulo generado automaticamente a partir de VDINTERFCARGALIN.DEF

VDEXPORT diccionario dicl;
#define ICLNUMCOL	14
typedef struct {
        char    rowid[ROWIDLON];
        long    codinterfase;
        char    tipointerfase[LTIPOINTERFASE];
        char    formato[LFORMATO];
        long    numreg;
        char    registro[LREGISTRO];
        char    mensaje[LMENSAJE];
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    statuscab;
        double  gencount;
    } vdinterfcargalins;

// Prototipos de funciones definidas en VDINTERFCARGALIN.C
VDEXPORT diccionario *ICLdamediccionario(void);
VDEXPORT int ICLbuscabuscareg(char *tipointerfase,char *formato,long status,long statuscab,vdinterfcargalins *icl);
VDEXPORT int ICLnextbuscareg(vdinterfcargalins *icl);
VDEXPORT int ICLbuscacodinterfase(long codinterfase,vdinterfcargalins *icl);
VDEXPORT int ICLnextcodinterfase(vdinterfcargalins *icl);
VDEXPORT int ICLselnumlineas(long codinterfase,vdinterfcargalins *icl);
VDEXPORT int ICLselvdinterfcargalin(long codinterfase,long numreg,vdinterfcargalins *icl);
VDEXPORT int ICLactualizastmsg(vdinterfcargalins *icl,int error);
VDEXPORT int ICLinsert(vdinterfcargalins *icl,int error);
VDEXPORT int ICLdel(vdinterfcargalins *icl,int error);
VDEXPORT char *ICLlog(vdinterfcargalins *icl);
char * ICLdebug(vdinterfcargalins *icl);
