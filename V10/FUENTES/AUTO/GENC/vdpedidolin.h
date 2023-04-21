// Modulo generado automaticamente a partir de VDPEDIDOLIN.DEF

VDEXPORT diccionario dpel;
#define PELNUMCOL	49
#define LCOMEN 1026
#define LCDEMANDA 11
#define LTDEMANDA 11
typedef struct {
        char    rowid[ROWIDLON];
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        long    seqlinea;
        long    seqlinorig;
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    caduci[LCADUCI];
        double  cantpedida;
        char    unidadeshost[LUNIDADESHOST];
        double  cantaservir;
        double  cantservida;
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
        char    manipespe[LMANIPESPE];
        long    secfact;
        char    timbre[LTIMBRE];
        char    fichero[LFICHERO];
        char    factura[LFACTURA];
        char    ficheroremi[LFICHEROREMI];
        double  impfact;
        char    swtdcto[LSWTDCTO];
        char    swtpedbon[LSWTPEDBON];
        double  cantpedidacli;
        char    comen[LCOMEN];
        char    cdemanda[LCDEMANDA];
        char    tdemanda[LTDEMANDA];
        long    ldemanda;
    } vdpedidolins;

// Prototipos de funciones definidas en VDPEDIDOLIN.C
VDEXPORT diccionario *PELdamediccionario(void);
VDEXPORT int PELsellinea(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,vdpedidolins *pel);
VDEXPORT int PELbuscapedido(char *coddiv,long anoped,char *codped,long seqped,vdpedidolins *pel);
VDEXPORT int PELnextpedido(vdpedidolins *pel);
VDEXPORT int PELbuscastatus(long status,vdpedidolins *pel);
VDEXPORT int PELnextstatus(vdpedidolins *pel);
VDEXPORT int PELbuscapedlinpdte(char *coddiv,long anoped,char *codped,long seqped,long status,vdpedidolins *pel);
VDEXPORT int PELnextpedlinpdte(vdpedidolins *pel);
VDEXPORT int PELbuscapedlinpordemanda(char *tdemanda,char *cdemanda,long ldemanda,vdpedidolins *pel);
VDEXPORT int PELnextpedlinpordemanda(vdpedidolins *pel);
VDEXPORT int PELselvdpedidolin(char *coddiv,long anoped,char *codped,long seqped,long seqlinea,vdpedidolins *pel);
VDEXPORT int PELlock(vdpedidolins *pel,int wait,int verificar,...);
VDEXPORT int PELactualizastatus(vdpedidolins *pel,int error);
VDEXPORT int PELactualizaseqped(vdpedidolins *pel,int error);
VDEXPORT int PELinsert(vdpedidolins *pel,int error);
VDEXPORT int PELdel(vdpedidolins *pel,int error);
VDEXPORT char *PELlog(vdpedidolins *pel);
char * PELdebug(vdpedidolins *pel);
