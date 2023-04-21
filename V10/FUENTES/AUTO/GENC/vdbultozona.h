// Modulo generado automaticamente a partir de VDBULTOZONA.DEF

VDEXPORT diccionario dbzo;
#define BZONUMCOL	12
typedef struct {
        char    rowid[ROWIDLON];
        long    seqbulto;
        long    codzona;
        char    codbulto[LCODBULTO];
        char    codope[LCODOPE];
        char    colorope[LCOLOROPE];
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        double  gencount;
    } vdbultozonas;

// Prototipos de funciones definidas en VDBULTOZONA.C
VDEXPORT diccionario *BZOdamediccionario(void);
VDEXPORT int BZOselbulto(char *codbulto,vdbultozonas *bzo);
VDEXPORT int BZOseldameopebulto(long codzona,char *codbulto,vdbultozonas *bzo);
VDEXPORT int BZOselzonapend(long codzona,vdbultozonas *bzo);
VDEXPORT int BZOselnumbul(long codzona,vdbultozonas *bzo);
VDEXPORT int BZObuscacodbulto(char *codbulto,vdbultozonas *bzo);
VDEXPORT int BZOnextcodbulto(vdbultozonas *bzo);
VDEXPORT int BZObuscazonaope(long codzona,char *codope,vdbultozonas *bzo);
VDEXPORT int BZOnextzonaope(vdbultozonas *bzo);
VDEXPORT int BZObuscafinbulto(long codzona,vdbultozonas *bzo);
VDEXPORT int BZOnextfinbulto(vdbultozonas *bzo);
VDEXPORT int BZObuscacodzona(long codzona,vdbultozonas *bzo);
VDEXPORT int BZOnextcodzona(vdbultozonas *bzo);
VDEXPORT int BZObuscazonstat(long codzona,long status,vdbultozonas *bzo);
VDEXPORT int BZOnextzonstat(vdbultozonas *bzo);
VDEXPORT int BZOselvdbultozona(long seqbulto,vdbultozonas *bzo);
VDEXPORT int BZOactualizastatus(vdbultozonas *bzo,int error);
VDEXPORT int BZOactualizacodope(vdbultozonas *bzo,int error);
VDEXPORT int BZOselvdsecbultozona(long *donde);
VDEXPORT int BZOinsert(vdbultozonas *bzo,int error);
VDEXPORT int BZOdel(vdbultozonas *bzo,int error);
VDEXPORT char *BZOlog(vdbultozonas *bzo);
char * BZOdebug(vdbultozonas *bzo);
