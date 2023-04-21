// Modulo generado automaticamente a partir de VDUBICA.DEF

VDEXPORT diccionario dubi;
#define UBINUMCOL	38
typedef struct {
        char    rowid[ROWIDLON];
        char    codubi[LCODUBI];
        long    codzona;
        char    codarea[LCODAREA];
        char    transito[LTRANSITO];
        long    planta;
        long    pasillo;
        long    columna;
        long    altura;
        long    profundidad;
        long    ordenentrada;
        long    ordensalida;
        long    ordenmovim;
        char    bloqueose[LBLOQUEOSE];
        char    bloqueoss[LBLOQUEOSS];
        char    multiarticulo[LMULTIARTICULO];
        char    multiformato[LMULTIFORMATO];
        char    uniagrupae[LUNIAGRUPAE];
        char    unicapac[LUNICAPAC];
        char    swtetiq[LSWTETIQ];
        long    stkmax;
        long    stkmin;
        long    stkurg;
        char    codart[LCODART];
        char    stock[LSTOCK];
        char    recargar[LRECARGAR];
        char    agrupalin[LAGRUPALIN];
        char    confpicking[LCONFPICKING];
        char    tipoubi[LTIPOUBI];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    fecultinven;
        long    fecultmov;
        char    swtubimarcada[LSWTUBIMARCADA];
        long    pasilloaux;
    } vdubicas;

// Prototipos de funciones definidas en VDUBICA.C
VDEXPORT diccionario *UBIdamediccionario(void);
VDEXPORT int UBIselvdubica(char *codubi,vdubicas *ubi);
VDEXPORT int UBIactualizarecargar(vdubicas *ubi,int error);
VDEXPORT int UBIinsert(vdubicas *ubi,int error);
VDEXPORT char *UBIlog(vdubicas *ubi);
char * UBIdebug(vdubicas *ubi);
