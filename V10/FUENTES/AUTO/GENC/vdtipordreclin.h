// Modulo generado automaticamente a partir de VDTIPORDRECLIN.DEF

VDEXPORT diccionario dlto;
#define LTONUMCOL	21
//#define LCODART 41
typedef struct {
        char    rowid[ROWIDLON];
        char    tipordrec[LTIPORDREC];
        char    codclasif[LCODCLASIF];
        char    codclase[LCODCLASE];
        char    requiere_orden[LREQUIERE_ORDEN];
        char    recepcion_unica[LRECEPCION_UNICA];
        char    muestrear[LMUESTREAR];
        char    altas_manuales[LALTAS_MANUALES];
        char    crea_lote[LCREA_LOTE];
        char    estados_lote[LESTADOS_LOTE];
        char    estados_stock[LESTADOS_STOCK];
        long    diasantfecprev;
        long    diasretfecprev;
        char    indlote[LINDLOTE];
        char    lotedef[LLOTEDEF];
        char    multiarticulo[LMULTIARTICULO];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    codart[LCODART];
    } vdtipordreclins;

// Prototipos de funciones definidas en VDTIPORDRECLIN.C
VDEXPORT diccionario *LTOdamediccionario(void);
VDEXPORT int LTOselarticulo(char *tipordrec,char *codart,vdtipordreclins *lto);
VDEXPORT int LTOselvdtipordreclin(char *tipordrec,char *codclasif,char *codclase,vdtipordreclins *lto);
VDEXPORT char *LTOlog(vdtipordreclins *lto);
char * LTOdebug(vdtipordreclins *lto);
