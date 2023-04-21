// Modulo generado automaticamente a partir de VDTIPOCOMEN.DEF

VDEXPORT diccionario dtco;
#define TCONUMCOL	13
typedef struct {
        char    rowid[ROWIDLON];
        char    tablacomen[LTABLACOMEN];
        char    tipocomen[LTIPOCOMEN];
        char    destipocomen[LDESTIPOCOMEN];
        long    orden;
        long    maxlineas;
        char    notificable[LNOTIFICABLE];
        char    privilegiosver[LPRIVILEGIOSVER];
        char    privilegiosmod[LPRIVILEGIOSMOD];
        char    privilegiosins[LPRIVILEGIOSINS];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdtipocomens;

// Prototipos de funciones definidas en VDTIPOCOMEN.C
VDEXPORT diccionario *TCOdamediccionario(void);
VDEXPORT int TCObuscatipocomen(char *tipocomen,vdtipocomens *tco);
VDEXPORT int TCOnexttipocomen(vdtipocomens *tco);
VDEXPORT int TCOselvdtipocomen(char *tablacomen,char *tipocomen,vdtipocomens *tco);
VDEXPORT int TCOinsert(vdtipocomens *tco,int error);
VDEXPORT char *TCOlog(vdtipocomens *tco);
char * TCOdebug(vdtipocomens *tco);
