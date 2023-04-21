// Fichero generado automaticamente a partir de VDBULTOSPINV.DEF

VDEXPORT diccionario dbupinv;
#ifndef LCODBULTOOUT
#define LCODBULTOOUT 19
#endif

#ifndef LCODCONCEAUX
#define LCODCONCEAUX 11
#endif

#ifndef LCODUBIREG
#define LCODUBIREG 13
#endif

#ifndef LMIDIGEAN
#define LMIDIGEAN 3
#endif

#ifndef LCODBULTOPINV
#define LCODBULTOPINV 19
#endif

#ifndef LCODBULTOPEXP
#define LCODBULTOPEXP 19
#endif

#ifndef LOBSERV
#define LOBSERV 1025
#endif

#ifndef LCODOPE
#define LCODOPE 11
#endif

#ifndef LPRIVILEGIO
#define LPRIVILEGIO 21
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LZONASPDTES
#define LZONASPDTES 4001
#endif

#ifndef LCODBULTO
#define LCODBULTO 19
#endif

#ifndef LTIPOCAJA
#define LTIPOCAJA 11
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCODBULTOEXP
#define LCODBULTOEXP 19
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

typedef struct {
        long    cantidad;
        char    codbultoout[LCODBULTOOUT];
        char    codconceaux[LCODCONCEAUX];
        char    codubireg[LCODUBIREG];
        long    ret;
        long    stbucpreparado;
        long    stbpcfinalizado;
        long    esfinpicking;
        long    esfinbulto;
        long    esfinbultopinvenzona;
        long    esfinbultopinv;
        long    esbultopinvsinstock;
        char    midigean[LMIDIGEAN];
        char    codbultopinv[LCODBULTOPINV];
        char    codbultopexp[LCODBULTOPEXP];
        long    pdtecaja;
        long    modoregularizacion;
        long    cantregularizar;
        char    observ[LOBSERV];
        long    uniemb;
        long    tieneprivilegio;
        char    codope[LCODOPE];
        char    privilegio[LPRIVILEGIO];
        long    numope;
        long    numbultoszona;
        long    numbultosope;
        long    codzona;
        long    numbultos;
        long    idinfopick;
        char    codmat[LCODMAT];
        char    zonaspdtes[LZONASPDTES];
        char    codbulto[LCODBULTO];
        long    numdisp;
        char    tipocaja[LTIPOCAJA];
        char    tarea[LTAREA];
        long    status;
        char    codconce[LCODCONCE];
        char    codbultoexp[LCODBULTOEXP];
        char    codubi[LCODUBI];
        long    codmov;
} vdbupinvs; 


VDEXPORT diccionario *BUPINVdamediccionario(void);
VDEXPORT int BUPINVselprivilegio(char *codope,char *privilegio,vdbupinvs *bupinv);
VDEXPORT int BUPINVseldatosope(char *codope,long codzona,vdbupinvs *bupinv);
VDEXPORT int BUPINVselpdteszona(long idinfopick,char *codmat,long codzona,vdbupinvs *bupinv);
VDEXPORT int BUPINVselzonaspdtes(char *codbulto,vdbupinvs *bupinv);
VDEXPORT int BUPINVselcantdisplay(char *codbulto,long codzona,long idinfopick,long numdisp,vdbupinvs *bupinv);
VDEXPORT int BUPINVselcantdisplayservida(char *codbulto,long codzona,long idinfopick,long numdisp,vdbupinvs *bupinv);
VDEXPORT int BUPINVselstockbulto(char *codbulto,vdbupinvs *bupinv);
VDEXPORT int BUPINVseltipocaja(char *codbulto,char *tipocaja,vdbupinvs *bupinv);
VDEXPORT int BUPINVprocejecutamovpinv(char *tarea,long status,char *codbulto,long codzona,long idinfopick,long numdisp,long stbucpreparado,long stbpcfinalizado,long modoregularizacion,char *midigean,long ret,vdbupinvs *bupinv);
VDEXPORT int BUPINVprocdameestadobultopinv(char *codbultopinv,long idinfopick,long numdisp,char *codbulto,long esfinbulto,long esfinpicking,long esfinbultopinvenzona,long esfinbultopinv,long esbultopinvsinstock,long ret,vdbupinvs *bupinv);
VDEXPORT int BUPINVproccambiacaja(long codzona,char *codbulto,char *codmat,char *tarea,char *codconce,long ret,vdbupinvs *bupinv);
VDEXPORT int BUPINVprocactplanifmov(char *codbulto,long codzona,long idinfopick,long numdisp,long ret,vdbupinvs *bupinv);
VDEXPORT int BUPINVbuscadispaencenderenzona(char *codbulto,long codzona,vdbupinvs *bupinv);
VDEXPORT int BUPINVnextdispaencenderenzona(vdbupinvs *bupinv);
VDEXPORT int BUPINVbuscadipsservidosenzona(char *codbulto,long codzona,vdbupinvs *bupinv);
VDEXPORT int BUPINVnextdipsservidosenzona(vdbupinvs *bupinv);
VDEXPORT int BUPINVbuscaregularizarestospinv(long codzona,char *codmat,long cantregularizar,char *codconce,char *codubi,char *observ,long codmov,long ret,vdbupinvs *bupinv);
VDEXPORT int BUPINVnextregularizarestospinv(vdbupinvs *bupinv);
VDEXPORT int BUPINVbuscabultopinvpdteservir(char *codbulto,vdbupinvs *bupinv);
VDEXPORT int BUPINVnextbultopinvpdteservir(vdbupinvs *bupinv);
VDEXPORT int BUPINVbuscauniembbultopinv(char *codbulto,vdbupinvs *bupinv);
VDEXPORT int BUPINVnextuniembbultopinv(vdbupinvs *bupinv);
VDEXPORT char * BUPINVdebug(vdbupinvs *bupinv);
