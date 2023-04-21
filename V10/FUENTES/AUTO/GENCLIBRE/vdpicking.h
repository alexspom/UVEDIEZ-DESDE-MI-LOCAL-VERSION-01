// Fichero generado automaticamente a partir de VDPICKING.DEF

VDEXPORT diccionario dpicking;
#ifndef LCODOPE
#define LCODOPE 11
#endif

#ifndef LPRIVILEGIO
#define LPRIVILEGIO 21
#endif

#ifndef LPARAM
#define LPARAM 4001
#endif

#ifndef LUNICAPAC
#define LUNICAPAC 2
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

typedef struct {
        long    error;
        char    codope[LCODOPE];
        long    tieneprivilegio;
        char    privilegio[LPRIVILEGIO];
        long    numope;
        long    numbultoszona;
        long    numbultosope;
        long    codzona;
        char    param[LPARAM];
        char    unicapac[LUNICAPAC];
        long    canttotal;
        char    codubi[LCODUBI];
        char    codmat[LCODMAT];
        long    posconte;
        long    ordenstk;
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  uniemb;
        long    embcont;
        long    bultbocacanal;
        long    cantbocacanal;
        long    idinfopick;
        long    numdisp;
} vdpickings; 


VDEXPORT diccionario *PICKINGdamediccionario(void);
VDEXPORT int PICKINGbuscaopepicking(char *codope,vdpickings *picking);
VDEXPORT int PICKINGnextopepicking(vdpickings *picking);
VDEXPORT int PICKINGselprivilegio(char *codope,char *privilegio,vdpickings *picking);
VDEXPORT int PICKINGseldatosope(char *codope,long codzona,vdpickings *picking);
VDEXPORT int PICKINGseldameparammenu(long codzona,vdpickings *picking);
VDEXPORT int PICKINGbuscadatoscanal(char *codubi,vdpickings *picking);
VDEXPORT int PICKINGnextdatoscanal(vdpickings *picking);
VDEXPORT int PICKINGbuscadatosbocacanal(char *codubi,vdpickings *picking);
VDEXPORT int PICKINGnextdatosbocacanal(vdpickings *picking);
VDEXPORT int PICKINGbuscadatosultmov(char *codubi,vdpickings *picking);
VDEXPORT int PICKINGnextdatosultmov(vdpickings *picking);
VDEXPORT int PICKINGbuscadispactzona(long codzona,vdpickings *picking);
VDEXPORT int PICKINGnextdispactzona(vdpickings *picking);
VDEXPORT int PICKINGbuscahijosluz(long idinfopick,long numdisp,vdpickings *picking);
VDEXPORT int PICKINGnexthijosluz(vdpickings *picking);
VDEXPORT char * PICKINGdebug(vdpickings *picking);
