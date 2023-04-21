// Fichero generado automaticamente a partir de VDDEMANDAAUX.DEF

VDEXPORT diccionario ddem;
#ifndef LAGRUPALINEAS
#define LAGRUPALINEAS 2
#endif

#ifndef LREABRIRDEML
#define LREABRIRDEML 2
#endif

#ifndef LCODDEMANDA
#define LCODDEMANDA 21
#endif

#ifndef LTIPODEMANDA
#define LTIPODEMANDA 11
#endif

#ifndef LCODDIV
#define LCODDIV 5
#endif

#ifndef LCODPED
#define LCODPED 21
#endif

#ifndef LBACKORDER
#define LBACKORDER 2
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LUNIAGRUPA
#define LUNIAGRUPA 2
#endif

#ifndef LTIPOREDONDEO
#define LTIPOREDONDEO 2
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LVDEXTRA
#define LVDEXTRA 4001
#endif

typedef struct {
        char    agrupalineas[LAGRUPALINEAS];
        long    lineasinsertadas;
        long    statusini;
        long    stdemlfinal;
        long    stdemcfinal;
        char    reabrirdeml[LREABRIRDEML];
        long    stdemlreabrir;
        long    stdemcreabrir;
        long    ret;
        long    anulable;
        char    coddemanda[LCODDEMANDA];
        char    tipodemanda[LTIPODEMANDA];
        long    lindemanda;
        char    coddiv[LCODDIV];
        long    anoped;
        char    codped[LCODPED];
        long    seqped;
        char    backorder[LBACKORDER];
        long    status;
        char    codubi[LCODUBI];
        char    uniagrupa[LUNIAGRUPA];
        double  cantidad;
        char    tiporedondeo[LTIPOREDONDEO];
        char    codart[LCODART];
        char    vdextra[LVDEXTRA];
} vddems; 


VDEXPORT diccionario *DEMdamediccionario(void);
VDEXPORT int DEMbuscademlanulable(char *coddemanda,char *tipodemanda,long lindemanda,vddems *dem);
VDEXPORT int DEMnextdemlanulable(vddems *dem);
VDEXPORT int DEMbuscademcanulable(char *coddemanda,char *tipodemanda,vddems *dem);
VDEXPORT int DEMnextdemcanulable(vddems *dem);
VDEXPORT int DEMprocanulademl(char *coddemanda,char *tipodemanda,long lindemanda,long ret,vddems *dem);
VDEXPORT int DEMprocanulademc(char *coddemanda,char *tipodemanda,long ret,vddems *dem);
VDEXPORT int DEMprocfinalizademl(char *coddemanda,char *tipodemanda,long lindemanda,long statusini,long stdemlfinal,long stdemcfinal,char *reabrirdeml,long stdemlreabrir,long stdemcreabrir,long ret,vddems *dem);
VDEXPORT int DEMproccreademandapedido(char *coddiv,long anoped,char *codped,long seqped,char *backorder,char *tipodemanda,long status,char *codubi,char *agrupalineas,long lineasinsertadas,char *coddemanda,vddems *dem);
VDEXPORT int DEMproccreademandarecarga(char *codubi,char *uniagrupa,double cantidad,char *tiporedondeo,char *codart,char *tipodemanda,long status,long lineasinsertadas,char *coddemanda,vddems *dem);
VDEXPORT int DEMbuscalistacodcomen(char *coddemanda,char *tipodemanda,vddems *dem);
VDEXPORT int DEMnextlistacodcomen(vddems *dem);
VDEXPORT char * DEMdebug(vddems *dem);

//Codigo incluido explicitamente en el DEF
VDEXPORT int creademandapedido(vdpedidocabs *pec,char *tipodemanda,long status,char *codubiexped,char *backorder,char *agrupalineas,char *coddemanda);
VDEXPORT int creademandarecarga(vdrecargas *rec,char *tipodemanda,long status,char *coddemanda);
VDEXPORT int finalizademl(vddemandalins *deml, long statusini,long stdemlfinal, long stdemcfinal, char *reabrir, long stdemlreabrir, long stdemcreabrir);
VDEXPORT int anulademl(vddemandalins *deml);
VDEXPORT int anulademc(vddemandacabs *demc);

