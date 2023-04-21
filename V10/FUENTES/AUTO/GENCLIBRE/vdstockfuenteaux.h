// Fichero generado automaticamente a partir de VDSTOCKFUENTEAUX.DEF

VDEXPORT diccionario dstkfteaux;
#ifndef LCREARCONTE
#define LCREARCONTE 3
#endif

#ifndef LCREARLOTE
#define LCREARLOTE 3
#endif

#ifndef LTIPOFUENTE
#define LTIPOFUENTE 11
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LTIPOCONTE
#define LTIPOCONTE 11
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LUNIDADESHOST
#define LUNIDADESHOST 11
#endif

#ifndef LTIPOEMBA
#define LTIPOEMBA 11
#endif

#ifndef LBLOQUEOS
#define LBLOQUEOS 11
#endif

#ifndef LBULTO
#define LBULTO 19
#endif

#ifndef LMARCASTK
#define LMARCASTK 61
#endif

#ifndef LNUMEROSERIE
#define LNUMEROSERIE 61
#endif

#ifndef LCODRECEP
#define LCODRECEP 21
#endif

#ifndef LCODLOTPROV
#define LCODLOTPROV 41
#endif

#ifndef LCADUCI
#define LCADUCI 9
#endif

#ifndef LRETEST
#define LRETEST 9
#endif

#ifndef LBLOQLOTE
#define LBLOQLOTE 11
#endif

#ifndef LSWTPRECIO
#define LSWTPRECIO 2
#endif

#ifndef LMUESTREADO
#define LMUESTREADO 2
#endif

#ifndef LVDEXTRA
#define LVDEXTRA 256
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

typedef struct {
        long    ret;
        char    crearconte[LCREARCONTE];
        char    crearlote[LCREARLOTE];
        char    tipofuente[LTIPOFUENTE];
        char    codubi[LCODUBI];
        char    codmat[LCODMAT];
        char    tipoconte[LTIPOCONTE];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  cantidadhost;
        char    unidadeshost[LUNIDADESHOST];
        double  uniembhost;
        long    embcont;
        char    tipoemba[LTIPOEMBA];
        double  preciouni;
        char    bloqueos[LBLOQUEOS];
        char    bulto[LBULTO];
        char    marcastk[LMARCASTK];
        char    numeroserie[LNUMEROSERIE];
        char    codrecep[LCODRECEP];
        double  pesouni;
        char    codlotprov[LCODLOTPROV];
        char    caduci[LCADUCI];
        char    retest[LRETEST];
        char    bloqlote[LBLOQLOTE];
        double  potencia;
        char    swtprecio[LSWTPRECIO];
        char    muestreado[LMUESTREADO];
        char    vdextra[LVDEXTRA];
        char    comentario[LCOMENTARIO];
        long    seqfuente;
        char    codconce[LCODCONCE];
        long    codmov;
} vdstkfteauxs; 


VDEXPORT diccionario *STKFTEAUXdamediccionario(void);
VDEXPORT int STKFTEAUXprocfuentestk(char *tipofuente,char *codubi,char *codmat,char *tipoconte,char *codart,char *codlot,double cantidadhost,char *unidadeshost,double uniembhost,long embcont,char *tipoemba,double preciouni,char *bloqueos,char *bulto,char *marcastk,char *numeroserie,char *codrecep,double pesouni,char *codlotprov,char *caduci,char *retest,char *bloqlote,double potencia,char *swtprecio,char *muestreado,char *vdextra,char *comentario,long ret,vdstkfteauxs *stkfteaux);
VDEXPORT int STKFTEAUXproccreastk(long seqfuente,char *codconce,char *codubi,char *crearconte,char *crearlote,char *vdextra,char *comentario,long codmov,long ret,vdstkfteauxs *stkfteaux);
VDEXPORT char * STKFTEAUXdebug(vdstkfteauxs *stkfteaux);
