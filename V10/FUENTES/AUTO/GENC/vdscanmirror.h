// Modulo generado automaticamente a partir de VDSCANMIRROR.DEF

VDEXPORT diccionario dscm;
#define SCMNUMCOL	11
typedef struct {
        char    rowid[ROWIDLON];
        long    orden;
        long    redscan;
        long    scanner;
        long    redscanm;
        long    scannerm;
        char    activo[LACTIVO];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdscanmirrors;

// Prototipos de funciones definidas en VDSCANMIRROR.C
VDEXPORT diccionario *SCMdamediccionario(void);
VDEXPORT int SCMbuscascmaestros(long redscanm,long scannerm,vdscanmirrors *scm);
VDEXPORT int SCMnextscmaestros(vdscanmirrors *scm);
VDEXPORT int SCMselvdscanmirror(vdscanmirrors *scm);
VDEXPORT char *SCMlog(vdscanmirrors *scm);
char * SCMdebug(vdscanmirrors *scm);
