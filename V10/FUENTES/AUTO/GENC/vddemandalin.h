// Modulo generado automaticamente a partir de VDDEMANDALIN.DEF

VDEXPORT diccionario ddeml;
#define DEMLNUMCOL	43
#define LCOMENDEML 1025
typedef struct {
        char    rowid[ROWIDLON];
        char    tipodemanda[LTIPODEMANDA];
        char    coddemanda[LCODDEMANDA];
        long    lindemanda;
        char    claveext[LCLAVEEXT];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  uniemb;
        char    tipoemba[LTIPOEMBA];
        char    marcastk[LMARCASTK];
        char    marcastkorigen[LMARCASTKORIGEN];
        char    bloqueos[LBLOQUEOS];
        char    numeroserie[LNUMEROSERIE];
        char    codmat[LCODMAT];
        char    bulto[LBULTO];
        char    codrecep[LCODRECEP];
        double  preciouni;
        char    backorder[LBACKORDER];
        char    uniagrupa[LUNIAGRUPA];
        char    tiporedondeo[LTIPOREDONDEO];
        char    ordenreserva[LORDENRESERVA];
        char    ordenreservaubi[LORDENRESERVAUBI];
        char    codubiori[LCODUBIORI];
        char    codareaori[LCODAREAORI];
        char    codubidest[LCODUBIDEST];
        char    codareadest[LCODAREADEST];
        double  cantidad;
        long    status;
        char    codopeinsert[LCODOPEINSERT];
        long    fecinsert;
        char    horainsert[LHORAINSERT];
        long    fecini;
        char    horaini[LHORAINI];
        long    fecfin;
        char    horafin[LHORAFIN];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    pedidohost[LPEDIDOHOST];
        char    comendeml[LCOMENDEML];
        double  reservado;
    } vddemandalins;

// Prototipos de funciones definidas en VDDEMANDALIN.C
VDEXPORT diccionario *DEMLdamediccionario(void);
VDEXPORT int DEMLbuscademandastatus(char *tipodemanda,char *coddemanda,long status,vddemandalins *deml);
VDEXPORT int DEMLnextdemandastatus(vddemandalins *deml);
VDEXPORT int DEMLbuscastatus(long status,vddemandalins *deml);
VDEXPORT int DEMLnextstatus(vddemandalins *deml);
VDEXPORT int DEMLbuscalineaspendientes(char *coddemanda,char *tipodemanda,vddemandalins *deml);
VDEXPORT int DEMLnextlineaspendientes(vddemandalins *deml);
VDEXPORT int DEMLselvddemandalin(char *tipodemanda,char *coddemanda,long lindemanda,vddemandalins *deml);
VDEXPORT int DEMLlock(vddemandalins *deml,int wait,int verificar,...);
VDEXPORT int DEMLactualizastatus(vddemandalins *deml,int error);
VDEXPORT int DEMLactualizafechainicio(vddemandalins *deml,int error);
VDEXPORT int DEMLactualizafechafinal(vddemandalins *deml,int error);
VDEXPORT char *DEMLlog(vddemandalins *deml);
char * DEMLdebug(vddemandalins *deml);
