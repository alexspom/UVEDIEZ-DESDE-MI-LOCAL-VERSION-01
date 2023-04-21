// Modulo generado automaticamente a partir de VDDEMANDACAB.DEF

VDEXPORT diccionario ddemc;
#define DEMCNUMCOL	21
#define LCOMENDEMC 1025
typedef struct {
        char    rowid[ROWIDLON];
        char    tipodemanda[LTIPODEMANDA];
        char    coddemanda[LCODDEMANDA];
        char    claveext[LCLAVEEXT];
        char    backorder[LBACKORDER];
        long    priori;
        long    status;
        char    codopeinsert[LCODOPEINSERT];
        long    fecinsert;
        char    horainsert[LHORAINSERT];
        long    fecini;
        char    horaini[LHORAINI];
        long    fecfin;
        char    horafin[LHORAFIN];
        long    fecnec;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    comendemc[LCOMENDEMC];
    } vddemandacabs;

// Prototipos de funciones definidas en VDDEMANDACAB.C
VDEXPORT diccionario *DEMCdamediccionario(void);
VDEXPORT int DEMCbuscasinlineaspdtes(char *coddemanda,char *tipodemanda,vddemandacabs *demc);
VDEXPORT int DEMCnextsinlineaspdtes(vddemandacabs *demc);
VDEXPORT int DEMCbuscasinlineasporfinalizar(char *coddemanda,char *tipodemanda,vddemandacabs *demc);
VDEXPORT int DEMCnextsinlineasporfinalizar(vddemandacabs *demc);
VDEXPORT int DEMCbuscatipoystatus(char *tipodemanda,long status,vddemandacabs *demc);
VDEXPORT int DEMCnexttipoystatus(vddemandacabs *demc);
VDEXPORT int DEMCselvddemandacab(char *tipodemanda,char *coddemanda,vddemandacabs *demc);
VDEXPORT int DEMClock(vddemandacabs *demc,int wait,int verificar,...);
VDEXPORT int DEMCactualizastatus(vddemandacabs *demc,int error);
VDEXPORT int DEMCactualizafechainicio(vddemandacabs *demc,int error);
VDEXPORT int DEMCactualizafechafinal(vddemandacabs *demc,int error);
VDEXPORT char *DEMClog(vddemandacabs *demc);
char * DEMCdebug(vddemandacabs *demc);
