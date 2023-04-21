// Modulo generado automaticamente a partir de VDIMPRETIPO.DEF

VDEXPORT diccionario dimtp;
#define IMTPNUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    tipoimpre[LTIPOIMPRE];
        char    destipoimpre[LDESTIPOIMPRE];
        char    activo[LACTIVO];
        char    tipodoc[LTIPODOC];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdimpretipos;

// Prototipos de funciones definidas en VDIMPRETIPO.C
VDEXPORT diccionario *IMTPdamediccionario(void);
VDEXPORT int IMTPselvdimpretipo(char *tipoimpre,vdimpretipos *imtp);
VDEXPORT char *IMTPlog(vdimpretipos *imtp);
char * IMTPdebug(vdimpretipos *imtp);
