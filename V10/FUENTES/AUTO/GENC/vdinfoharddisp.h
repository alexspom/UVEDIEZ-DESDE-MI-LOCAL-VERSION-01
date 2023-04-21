// Modulo generado automaticamente a partir de VDINFOHARDDISP.DEF

VDEXPORT diccionario dihd;
#define IHDNUMCOL	17
typedef struct {
        char    rowid[ROWIDLON];
        long    idinfopick;
        long    numdisp;
        long    idinfogest;
        char    texto[LTEXTO];
        char    luces[LLUCES];
        char    teclas[LTECLAS];
        long    status;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    idinfopickm;
        long    numdispm;
        long    codcomen;
        long    estadobot;
        char    rangolineas[LRANGOLINEAS];
    } vdinfoharddisps;

// Prototipos de funciones definidas en VDINFOHARDDISP.C
VDEXPORT diccionario *IHDdamediccionario(void);
VDEXPORT int IHDbuscastatus(long idinfopick,long status,vdinfoharddisps *ihd);
VDEXPORT int IHDnextstatus(vdinfoharddisps *ihd);
VDEXPORT int IHDbuscarango(long idinfopick,long status,char *rangolineas,vdinfoharddisps *ihd);
VDEXPORT int IHDnextrango(vdinfoharddisps *ihd);
VDEXPORT int IHDbuscadispmirror(long idinfopickm,long numdispm,vdinfoharddisps *ihd);
VDEXPORT int IHDnextdispmirror(vdinfoharddisps *ihd);
VDEXPORT int IHDbuscateclas(long idinfogest,vdinfoharddisps *ihd);
VDEXPORT int IHDnextteclas(vdinfoharddisps *ihd);
VDEXPORT int IHDselvdinfoharddisp(long idinfopick,long numdisp,vdinfoharddisps *ihd);
VDEXPORT int IHDlock(vdinfoharddisps *ihd,int wait,int verificar,...);
VDEXPORT int IHDactualizastatus(vdinfoharddisps *ihd,int error);
VDEXPORT int IHDactualizastytexto(vdinfoharddisps *ihd,int error);
VDEXPORT int IHDactualizateclas(vdinfoharddisps *ihd,int error);
VDEXPORT char *IHDlog(vdinfoharddisps *ihd);
char * IHDdebug(vdinfoharddisps *ihd);
