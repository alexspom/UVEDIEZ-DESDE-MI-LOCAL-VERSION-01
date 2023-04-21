// Modulo generado automaticamente a partir de VDASIGNAGE.DEF

VDEXPORT diccionario dasa;
#define ASANUMCOL	25
typedef struct {
        char    rowid[ROWIDLON];
        long    secasignage;
        long    prioridadregla;
        char    codage[LCODAGE];
        char    rangocliente[LRANGOCLIENTE];
        char    rangodp[LRANGODP];
        char    rangozonageo[LRANGOZONAGEO];
        char    rangopeso[LRANGOPESO];
        char    rangovolumen[LRANGOVOLUMEN];
        char    rangobultos[LRANGOBULTOS];
        char    rangotipopedido[LRANGOTIPOPEDIDO];
        char    rangocoddivped[LRANGOCODDIVPED];
        char    rangocodart[LRANGOCODART];
        char    rangocoddivart[LRANGOCODDIVART];
        char    rangocodclase[LRANGOCODCLASE];
        char    rangocodage[LRANGOCODAGE];
        char    rangocodpais[LRANGOCODPAIS];
        long    urgencia;
        long    prioridad;
        char    vdextra[LVDEXTRA];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
        char    entorno[LENTORNO];
    } vdasignages;

// Prototipos de funciones definidas en VDASIGNAGE.C
VDEXPORT diccionario *ASAdamediccionario(void);
VDEXPORT int ASAbuscacodage(char *codage,vdasignages *asa);
VDEXPORT int ASAnextcodage(vdasignages *asa);
VDEXPORT int ASAselvdasignage(long secasignage,vdasignages *asa);
VDEXPORT char *ASAlog(vdasignages *asa);
char * ASAdebug(vdasignages *asa);
