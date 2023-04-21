// Modulo generado automaticamente a partir de VDOPEACTIVIDAD.DEF

VDEXPORT diccionario doact;
#define OACTNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        char    codope[LCODOPE];
        long    codzona;
        long    feciniact;
        char    horainiact[LHORAINIACT];
        long    fecfinact;
        char    horafinact[LHORAFINACT];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdopeactividads;

// Prototipos de funciones definidas en VDOPEACTIVIDAD.C
VDEXPORT diccionario *OACTdamediccionario(void);
VDEXPORT int OACTbuscazonaabierta(long codzona,char *codope,vdopeactividads *oact);
VDEXPORT int OACTnextzonaabierta(vdopeactividads *oact);
VDEXPORT int OACTbuscaopezona(long codzona,vdopeactividads *oact);
VDEXPORT int OACTnextopezona(vdopeactividads *oact);
VDEXPORT int OACTselvdopeactividad(char *codope,long codzona,long feciniact,char *horainiact,vdopeactividads *oact);
VDEXPORT int OACTactualizacierrezona(vdopeactividads *oact,int error);
VDEXPORT int OACTinsert(vdopeactividads *oact,int error);
VDEXPORT char *OACTlog(vdopeactividads *oact);
char * OACTdebug(vdopeactividads *oact);
