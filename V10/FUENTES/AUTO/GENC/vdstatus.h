// Modulo generado automaticamente a partir de VDSTATUS.DEF

VDEXPORT diccionario dsta;
#define STANUMCOL	10
typedef struct {
        char    rowid[ROWIDLON];
        char    tipostatus[LTIPOSTATUS];
        long    status;
        char    desstatus[LDESSTATUS];
        char    dabstatus[LDABSTATUS];
        char    tipoapp[LTIPOAPP];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdstatuss;

// Prototipos de funciones definidas en VDSTATUS.C
VDEXPORT diccionario *STAdamediccionario(void);
VDEXPORT int STAselabreviada(char *tipostatus,char *dabstatus,vdstatuss *sta);
VDEXPORT int STAselvdstatus(char *tipostatus,long status,vdstatuss *sta);
VDEXPORT char *STAlog(vdstatuss *sta);
char * STAdebug(vdstatuss *sta);
