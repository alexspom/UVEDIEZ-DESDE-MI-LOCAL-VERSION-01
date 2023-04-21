// Modulo generado automaticamente a partir de VDINFODISPBULTO.DEF

VDEXPORT diccionario didb;
#define IDBNUMCOL	12
typedef struct {
        char    rowid[ROWIDLON];
        long    idinfopick;
        long    numdisp;
        long    idinfogest;
        char    codbulto[LCODBULTO];
        long    status;
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codzona;
    } vdinfodispbultos;

// Prototipos de funciones definidas en VDINFODISPBULTO.C
VDEXPORT diccionario *IDBdamediccionario(void);
VDEXPORT int IDBbuscastatus(long status,vdinfodispbultos *idb);
VDEXPORT int IDBnextstatus(vdinfodispbultos *idb);
VDEXPORT int IDBbuscadispstatus(long idinfopick,long numdisp,long status,vdinfodispbultos *idb);
VDEXPORT int IDBnextdispstatus(vdinfodispbultos *idb);
VDEXPORT int IDBbuscadisplay(long idinfopick,long numdisp,vdinfodispbultos *idb);
VDEXPORT int IDBnextdisplay(vdinfodispbultos *idb);
VDEXPORT int IDBbuscacodzona(long codzona,vdinfodispbultos *idb);
VDEXPORT int IDBnextcodzona(vdinfodispbultos *idb);
VDEXPORT int IDBbuscabultozona(char *codbulto,long codzona,vdinfodispbultos *idb);
VDEXPORT int IDBnextbultozona(vdinfodispbultos *idb);
VDEXPORT int IDBselvdinfodispbulto(vdinfodispbultos *idb);
VDEXPORT int IDBlock(vdinfodispbultos *idb,int wait,int verificar,...);
VDEXPORT int IDBactualizacodbulto(vdinfodispbultos *idb,int error);
VDEXPORT int IDBactualizastatus(vdinfodispbultos *idb,int error);
VDEXPORT int IDBinsert(vdinfodispbultos *idb,int error);
VDEXPORT int IDBdel(vdinfodispbultos *idb,int error);
VDEXPORT char *IDBlog(vdinfodispbultos *idb);
char * IDBdebug(vdinfodispbultos *idb);
