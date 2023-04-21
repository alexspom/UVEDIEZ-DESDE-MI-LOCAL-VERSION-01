// Modulo generado automaticamente a partir de VDINFOPARAMCC.DEF

VDEXPORT diccionario dipc;
#define IPCNUMCOL	8
typedef struct {
        char    rowid[ROWIDLON];
        long    codzona;
        char    texto[LTEXTO];
        char    param[LPARAM];
        long    prioridad;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdinfoparamccs;

// Prototipos de funciones definidas en VDINFOPARAMCC.C
VDEXPORT diccionario *IPCdamediccionario(void);
VDEXPORT int IPCselvdinfoparamcc(vdinfoparamccs *ipc);
VDEXPORT int IPCactualizatextoyparam(vdinfoparamccs *ipc,int error);
VDEXPORT int IPCactualizatextoparamyprioridad(vdinfoparamccs *ipc,int error);
VDEXPORT int IPCinsert(vdinfoparamccs *ipc,int error);
VDEXPORT int IPCdel(vdinfoparamccs *ipc,int error);
VDEXPORT char *IPClog(vdinfoparamccs *ipc);
char * IPCdebug(vdinfoparamccs *ipc);
