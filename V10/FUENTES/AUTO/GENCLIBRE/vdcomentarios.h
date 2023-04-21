// Fichero generado automaticamente a partir de VDCOMENTARIOS.DEF

VDEXPORT diccionario dplsqlcomen;
#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LMSJERROR
#define LMSJERROR 1025
#endif

#ifndef LMITABLA
#define LMITABLA 31
#endif

#ifndef LMICAMPOCOMEN
#define LMICAMPOCOMEN 31
#endif

#ifndef LMIWHERE
#define LMIWHERE 1025
#endif

#ifndef LLISTACODCOMEN
#define LLISTACODCOMEN 1025
#endif

#ifndef LTIPOCOMEN
#define LTIPOCOMEN 33
#endif

#ifndef LTABLACOMEN
#define LTABLACOMEN 33
#endif

#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

typedef struct {
        char    comentario[LCOMENTARIO];
        long    valor;
        long    ret;
        char    msjerror[LMSJERROR];
        char    mitabla[LMITABLA];
        char    micampocomen[LMICAMPOCOMEN];
        char    miwhere[LMIWHERE];
        long    relogin;
        char    listacodcomen[LLISTACODCOMEN];
        long    codcomen;
        char    tipocomen[LTIPOCOMEN];
        long    lincomen;
        char    tablacomen[LTABLACOMEN];
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        char    codubi[LCODUBI];
} vdplsqlcomens; 


VDEXPORT diccionario *PLSQLCOMENdamediccionario(void);
VDEXPORT int PLSQLCOMENbuscadamecomen(long codcomen,char *tipocomen,long lincomen,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENnextdamecomen(vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENbuscadameret(vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENnextdameret(vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENproccreacomen(char *tablacomen,long codcomen,char *tipocomen,long lincomen,char *comentario,long relogin,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENprocborracomenportipo(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENbuscacomenpropcadena(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENnextcomenpropcadena(vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENbuscacomenpropentero(long codcomen,char *tipocomen,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENnextcomenpropentero(vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENprocmuevecomendeml2pel(char *coddiv,long anoped,char *codped,long seqped,char *listacodcomen,char *tipocomen,vdplsqlcomens *plsqlcomen);
VDEXPORT int PLSQLCOMENprocmuevecomendeml2ubi(char *codubi,char *listacodcomen,char *tipocomen,char *comentario,vdplsqlcomens *plsqlcomen);
VDEXPORT char * PLSQLCOMENdebug(vdplsqlcomens *plsqlcomen);
