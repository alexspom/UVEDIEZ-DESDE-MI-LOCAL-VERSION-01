// Modulo generado automaticamente a partir de VDCAJAS.DEF

VDEXPORT diccionario dcaj;
#define CAJNUMCOL	22
typedef struct {
        char    rowid[ROWIDLON];
        char    tipovol[LTIPOVOL];
        char    tipocaja[LTIPOCAJA];
        char    tipoemba[LTIPOEMBA];
        char    descaja[LDESCAJA];
        long    largocaja;
        long    anchocaja;
        long    altocaja;
        long    pesocaja;
        long    pesorelleno;
        double  margenpeso;
        long    maxllenado;
        long    minllenado;
        long    maxpicos;
        long    maxpeso;
        char    voldinamica[LVOLDINAMICA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        double  volumencaj;
        long    altura;
    } vdcajass;

// Prototipos de funciones definidas en VDCAJAS.C
VDEXPORT diccionario *CAJdamediccionario(void);
VDEXPORT int CAJbuscademayoramenor(char *tipovol,vdcajass *caj);
VDEXPORT int CAJnextdemayoramenor(vdcajass *caj);
VDEXPORT int CAJselvdcajas(char *tipovol,char *tipocaja,vdcajass *caj);
VDEXPORT int CAJinsert(vdcajass *caj,int error);
VDEXPORT int CAJdel(vdcajass *caj,int error);
VDEXPORT char *CAJlog(vdcajass *caj);
char * CAJdebug(vdcajass *caj);
