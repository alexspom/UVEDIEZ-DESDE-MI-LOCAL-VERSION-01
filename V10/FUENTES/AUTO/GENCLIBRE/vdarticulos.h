// Fichero generado automaticamente a partir de VDARTICULOS.DEF

VDEXPORT diccionario darticulo;
#ifndef LRETEST
#define LRETEST 9
#endif

#ifndef LSOLOSTOCK
#define LSOLOSTOCK 2
#endif

#ifndef LMSJERROR
#define LMSJERROR 1025
#endif

#ifndef LCOMENMOV
#define LCOMENMOV 2
#endif

#ifndef LCADUCI
#define LCADUCI 9
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LBLOQLOTE
#define LBLOQLOTE 11
#endif

typedef struct {
        char    retest[LRETEST];
        char    solostock[LSOLOSTOCK];
        char    msjerror[LMSJERROR];
        long    ret;
        char    comenmov[LCOMENMOV];
        char    caduci[LCADUCI];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    bloqlote[LBLOQLOTE];
        long    seq;
} vdarticulos; 


VDEXPORT diccionario *ARTICULOdamediccionario(void);
VDEXPORT int ARTICULObuscadameretest(char *caduci,char *codart,vdarticulos *articulo);
VDEXPORT int ARTICULOnextdameretest(vdarticulos *articulo);
VDEXPORT int ARTICULOprocnuevobloqlote(char *codart,char *codlot,char *bloqlote,char *solostock,char *msjerror,long ret,vdarticulos *articulo);
VDEXPORT int ARTICULOproctrataloteshist(long seq,char *comenmov,vdarticulos *articulo);
VDEXPORT char * ARTICULOdebug(vdarticulos *articulo);
