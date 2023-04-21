// Modulo generado automaticamente a partir de VDINFOOPECOLOR.DEF

VDEXPORT diccionario dioc;
#define IOCNUMCOL	10
typedef struct {
        char    rowid[ROWIDLON];
        char    codope[LCODOPE];
        long    prioridad;
        char    colorope[LCOLOROPE];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        long    codzona;
    } vdinfoopecolors;

// Prototipos de funciones definidas en VDINFOOPECOLOR.C
VDEXPORT diccionario *IOCdamediccionario(void);
VDEXPORT int IOCbuscacolor(char *codope,long codzona,vdinfoopecolors *ioc);
VDEXPORT int IOCnextcolor(vdinfoopecolors *ioc);
VDEXPORT int IOCbuscacolorope(char *codope,vdinfoopecolors *ioc);
VDEXPORT int IOCnextcolorope(vdinfoopecolors *ioc);
VDEXPORT int IOCselvdinfoopecolor(char *codope,char *colorope,vdinfoopecolors *ioc);
VDEXPORT char *IOClog(vdinfoopecolors *ioc);
char * IOCdebug(vdinfoopecolors *ioc);
