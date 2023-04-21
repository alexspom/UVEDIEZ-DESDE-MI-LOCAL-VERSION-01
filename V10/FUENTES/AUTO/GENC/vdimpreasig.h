// Modulo generado automaticamente a partir de VDIMPREASIG.DEF

VDEXPORT diccionario dimas;
#define IMASNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        char    codopeasig[LCODOPEASIG];
        char    ordenador[LORDENADOR];
        char    tipoimpre[LTIPOIMPRE];
        char    documento[LDOCUMENTO];
        char    codimpre[LCODIMPRE];
        char    activo[LACTIVO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdimpreasigs;

// Prototipos de funciones definidas en VDIMPREASIG.C
VDEXPORT diccionario *IMASdamediccionario(void);
VDEXPORT int IMASbuscaimpresorauser(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas);
VDEXPORT int IMASnextimpresorauser(vdimpreasigs *imas);
VDEXPORT int IMASbuscaimpresoradefecto(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas);
VDEXPORT int IMASnextimpresoradefecto(vdimpreasigs *imas);
VDEXPORT int IMASbuscaimpresora(char *ordenador,char *tipoimpre,char *documento,vdimpreasigs *imas);
VDEXPORT int IMASnextimpresora(vdimpreasigs *imas);
VDEXPORT int IMASselvdimpreasig(char *codopeasig,char *ordenador,char *tipoimpre,char *documento,char *codimpre,vdimpreasigs *imas);
VDEXPORT char *IMASlog(vdimpreasigs *imas);
char * IMASdebug(vdimpreasigs *imas);
