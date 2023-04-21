// Modulo generado automaticamente a partir de VDINFODISP.DEF

VDEXPORT diccionario didi;
#define IDINUMCOL	32
typedef struct {
        char    rowid[ROWIDLON];
        long    idinfopick;
        long    numdisp;
        long    codzona;
        long    idinfopickpadre;
        long    dpadre;
        long    idinfopickluz;
        long    numluz;
        long    ordendisp;
        long    maxcantdisp;
        char    cantaleatoria[LCANTALEATORIA];
        long    tiempook;
        long    tiempofin;
        char    nexttick[LNEXTTICK];
        char    invcont[LINVCONT];
        char    codubi[LCODUBI];
        char    codbulto[LCODBULTO];
        char    confirmado[LCONFIRMADO];
        long    cantpedidadisp;
        long    cantvalidadadisp;
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    codmov;
        long    quedan;
        long    idinfopickalt;
        char    codubialt[LCODUBIALT];
        char    codmat[LCODMAT];
        long    idinfogest;
    } vdinfodisps;

// Prototipos de funciones definidas en VDINFODISP.C
VDEXPORT diccionario *IDIdamediccionario(void);
VDEXPORT int IDIselcodbulto(char *codbulto,vdinfodisps *idi);
VDEXPORT int IDIbuscatick(long idinfogest,vdinfodisps *idi);
VDEXPORT int IDInexttick(vdinfodisps *idi);
VDEXPORT int IDIbuscastatuszona(long status,long codzona,vdinfodisps *idi);
VDEXPORT int IDInextstatuszona(vdinfodisps *idi);
VDEXPORT int IDIbuscadisplayszona(long codzona,vdinfodisps *idi);
VDEXPORT int IDInextdisplayszona(vdinfodisps *idi);
VDEXPORT int IDIbuscaluzpadre(long idinfopickluz,long numluz,vdinfodisps *idi);
VDEXPORT int IDInextluzpadre(vdinfodisps *idi);
VDEXPORT int IDIselvdinfodisp(long idinfopick,long numdisp,vdinfodisps *idi);
VDEXPORT int IDIactualizastatus(vdinfodisps *idi,int error);
VDEXPORT int IDIactualizacodbulto(vdinfodisps *idi,int error);
VDEXPORT int IDIactualizacantidades(vdinfodisps *idi,int error);
VDEXPORT int IDIactualizacodbultoycantidades(vdinfodisps *idi,int error);
VDEXPORT int IDIactualizaconfirmado(vdinfodisps *idi,int error);
VDEXPORT char *IDIlog(vdinfodisps *idi);
char * IDIdebug(vdinfodisps *idi);
