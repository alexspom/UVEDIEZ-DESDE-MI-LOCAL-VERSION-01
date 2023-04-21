// Modulo generado automaticamente a partir de VDORDRECCAB.DEF

VDEXPORT diccionario dorc;
#define ORCNUMCOL	20
typedef struct {
        char    rowid[ROWIDLON];
        char    codordrec[LCODORDREC];
        char    coddiv[LCODDIV];
        char    tipordrec[LTIPORDREC];
        char    claveext[LCLAVEEXT];
        char    codprove[LCODPROVE];
        char    desprove[LDESPROVE];
        long    fecordrec;
        long    feccreado;
        char    horacreado[LHORACREADO];
        long    status;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    fecfin;
        char    horafin[LHORAFIN];
        long    fecini;
        char    horaini[LHORAINI];
    } vdordreccabs;

// Prototipos de funciones definidas en VDORDRECCAB.C
VDEXPORT diccionario *ORCdamediccionario(void);
VDEXPORT int ORCselvdordreccab(char *codordrec,char *coddiv,vdordreccabs *orc);
VDEXPORT int ORCactualizavdordreccab(vdordreccabs *orc,int error);
VDEXPORT int ORCinsert(vdordreccabs *orc,int error);
VDEXPORT int ORCdel(vdordreccabs *orc,int error);
VDEXPORT int ORCinter(vdordreccabs *orc);
VDEXPORT char *ORClog(vdordreccabs *orc);
char * ORCdebug(vdordreccabs *orc);
