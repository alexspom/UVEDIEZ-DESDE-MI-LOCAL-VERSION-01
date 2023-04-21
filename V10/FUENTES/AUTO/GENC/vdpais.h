// Modulo generado automaticamente a partir de VDPAIS.DEF

VDEXPORT diccionario dpais;
#define PAISNUMCOL	7
typedef struct {
        char    rowid[ROWIDLON];
        char    codpais[LCODPAIS];
        char    despais[LDESPAIS];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdpaiss;

// Prototipos de funciones definidas en VDPAIS.C
VDEXPORT diccionario *PAISdamediccionario(void);
VDEXPORT int PAISbuscadespais(char *despais,vdpaiss *pais);
VDEXPORT int PAISnextdespais(vdpaiss *pais);
VDEXPORT int PAISselvdpais(char *codpais,vdpaiss *pais);
VDEXPORT char *PAISlog(vdpaiss *pais);
char * PAISdebug(vdpaiss *pais);
