// Modulo generado automaticamente a partir de VDTRADCODIGO.DEF

VDEXPORT diccionario dtrc;
#define TRCNUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    codart[LCODART];
        char    codartalt[LCODARTALT];
        char    swtactivo[LSWTACTIVO];
        char    tipobarras[LTIPOBARRAS];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdtradcodigos;

// Prototipos de funciones definidas en VDTRADCODIGO.C
VDEXPORT diccionario *TRCdamediccionario(void);
VDEXPORT int TRCselcodartalt(char *codartalt,vdtradcodigos *trc);
VDEXPORT int TRCselvdtradcodigo(char *codart,char *codartalt,vdtradcodigos *trc);
VDEXPORT int TRCactualizavdtradcodigo(vdtradcodigos *trc,int error);
VDEXPORT int TRCinsert(vdtradcodigos *trc,int error);
VDEXPORT int TRCdel(vdtradcodigos *trc,int error);
VDEXPORT int TRCinter(vdtradcodigos *trc);
VDEXPORT char *TRClog(vdtradcodigos *trc);
char * TRCdebug(vdtradcodigos *trc);
