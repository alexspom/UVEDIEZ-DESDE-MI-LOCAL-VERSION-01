// Modulo generado automaticamente a partir de VDCONFI.DEF

VDEXPORT diccionario dconf;
#define CONFNUMCOL	14
typedef struct {
        char    rowid[ROWIDLON];
        char    propiedad[LPROPIEDAD];
        char    grupoprop[LGRUPOPROP];
        char    comentario[LCOMENTARIO];
        char    tipodato[LTIPODATO];
        char    valor[LVALOR];
        char    activo[LACTIVO];
        char    privilegiosver[LPRIVILEGIOSVER];
        char    privilegiosmod[LPRIVILEGIOSMOD];
        char    permitidos[LPERMITIDOS];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdconfis;

// Prototipos de funciones definidas en VDCONFI.C
VDEXPORT diccionario *CONFdamediccionario(void);
VDEXPORT int CONFselpropiedad(char *propiedad,vdconfis *conf);
VDEXPORT int CONFselvdconfi(char *propiedad,vdconfis *conf);
VDEXPORT char *CONFlog(vdconfis *conf);
char * CONFdebug(vdconfis *conf);
