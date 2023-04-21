// Modulo generado automaticamente a partir de VDGRUPOSERV.DEF

VDEXPORT diccionario dgrs;
#define GRSNUMCOL	13
typedef struct {
        char    rowid[ROWIDLON];
        char    codgruposerv[LCODGRUPOSERV];
        char    desgruposerv[LDESGRUPOSERV];
        char    ordenador[LORDENADOR];
        char    arranque[LARRANQUE];
        char    pathgrupo[LPATHGRUPO];
        char    pathv10grupo[LPATHV10GRUPO];
        char    envgrupo[LENVGRUPO];
        char    paramgrupo[LPARAMGRUPO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdgruposervs;

// Prototipos de funciones definidas en VDGRUPOSERV.C
VDEXPORT diccionario *GRSdamediccionario(void);
VDEXPORT int GRSselcodgruposerv(char *codgruposerv,vdgruposervs *grs);
VDEXPORT int GRSbuscaordenador(char *ordenador,vdgruposervs *grs);
VDEXPORT int GRSnextordenador(vdgruposervs *grs);
VDEXPORT int GRSselvdgruposerv(char *codgruposerv,vdgruposervs *grs);
VDEXPORT char *GRSlog(vdgruposervs *grs);
char * GRSdebug(vdgruposervs *grs);
