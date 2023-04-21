// Modulo generado automaticamente a partir de VDPEDIDORIGLIN.DEF

VDEXPORT diccionario dpol;
#define POLNUMCOL	37
#define LCOMEN 1026
#define LMIROWID 1
typedef struct {
        char    rowid[ROWIDLON];
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqlinea;
        long    seqlinorig;
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    caduci[LCADUCI];
        double  cantpedida;
        char    unidadeshost[LUNIDADESHOST];
        char    backorder[LBACKORDER];
        char    codagrupa[LCODAGRUPA];
        char    opcionprecio[LOPCIONPRECIO];
        double  preciouni;
        char    unidadesprecio[LUNIDADESPRECIO];
        double  dcto;
        double  iva;
        double  recargo;
        char    swtcreaversion[LSWTCREAVERSION];
        char    marcastk[LMARCASTK];
        char    numeroserie[LNUMEROSERIE];
        char    pedidohost[LPEDIDOHOST];
        char    marcarpt[LMARCARPT];
        char    tiporedondeo[LTIPOREDONDEO];
        long    codcomen;
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    codmat[LCODMAT];
        long    seqped;
        char    swtdcto[LSWTDCTO];
        char    swtpedbon[LSWTPEDBON];
        double  cantpedidacli;
        char    comen[LCOMEN];
    } vdpedidoriglins;

// Prototipos de funciones definidas en VDPEDIDORIGLIN.C
VDEXPORT diccionario *POLdamediccionario(void);
VDEXPORT int POLsellinea(char *coddiv,long anoped,char *codped,long seqlinea,vdpedidoriglins *pol);
VDEXPORT int POLbuscapedido(char *coddiv,long anoped,char *codped,long seqped,vdpedidoriglins *pol);
VDEXPORT int POLnextpedido(vdpedidoriglins *pol);
VDEXPORT int POLbuscastatus(long status,vdpedidoriglins *pol);
VDEXPORT int POLnextstatus(vdpedidoriglins *pol);
VDEXPORT int POLbuscalinpepdte(char *coddiv,long anoped,char *codped,long seqped,long status,vdpedidoriglins *pol);
VDEXPORT int POLnextlinpepdte(vdpedidoriglins *pol);
VDEXPORT int POLselrowid(char *mirowid,vdpedidoriglins *pol);
VDEXPORT int POLselvdpedidoriglin(char *coddiv,long anoped,char *codped,long seqlinea,long seqped,vdpedidoriglins *pol);
VDEXPORT int POLlock(vdpedidoriglins *pol,int wait,int verificar,...);
VDEXPORT int POLactualizastatus(vdpedidoriglins *pol,int error);
VDEXPORT int POLactualizavdpedidoriglin(vdpedidoriglins *pol,int error);
VDEXPORT int POLinsert(vdpedidoriglins *pol,int error);
VDEXPORT int POLdel(vdpedidoriglins *pol,int error);
VDEXPORT int POLinter(vdpedidoriglins *pol);
VDEXPORT char *POLlog(vdpedidoriglins *pol);
char * POLdebug(vdpedidoriglins *pol);
