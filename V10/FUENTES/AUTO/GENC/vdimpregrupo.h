// Modulo generado automaticamente a partir de VDIMPREGRUPO.DEF

VDEXPORT diccionario dimgr;
#define IMGRNUMCOL	8
typedef struct {
        char    rowid[ROWIDLON];
        char    grupoimpre[LGRUPOIMPRE];
        char    desgrupoimpre[LDESGRUPOIMPRE];
        char    activo[LACTIVO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdimpregrupos;

// Prototipos de funciones definidas en VDIMPREGRUPO.C
VDEXPORT diccionario *IMGRdamediccionario(void);
VDEXPORT int IMGRselvdimpregrupo(char *grupoimpre,vdimpregrupos *imgr);
VDEXPORT char *IMGRlog(vdimpregrupos *imgr);
char * IMGRdebug(vdimpregrupos *imgr);
