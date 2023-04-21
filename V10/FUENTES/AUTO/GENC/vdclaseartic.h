// Modulo generado automaticamente a partir de VDCLASEARTIC.DEF

VDEXPORT diccionario dcla;
#define CLANUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    codclasif[LCODCLASIF];
        char    codclase[LCODCLASE];
        char    codart[LCODART];
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdclaseartics;

// Prototipos de funciones definidas en VDCLASEARTIC.C
VDEXPORT diccionario *CLAdamediccionario(void);
VDEXPORT int CLAselcodartclasif(char *codart,char *codclasif,vdclaseartics *cla);
VDEXPORT int CLAselvdclaseartic(vdclaseartics *cla);
VDEXPORT int CLAactualizavdclaseartic(vdclaseartics *cla,int error);
VDEXPORT int CLAinsert(vdclaseartics *cla,int error);
VDEXPORT int CLAdel(vdclaseartics *cla,int error);
VDEXPORT int CLAinter(vdclaseartics *cla);
VDEXPORT char *CLAlog(vdclaseartics *cla);
char * CLAdebug(vdclaseartics *cla);
