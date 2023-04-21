// Modulo generado automaticamente a partir de VDCOMEN.DEF

VDEXPORT diccionario dcom;
#define COMNUMCOL	9
typedef struct {
        char    rowid[ROWIDLON];
        char    tipocomen[LTIPOCOMEN];
        long    codcomen;
        long    lincomen;
        char    comentario[LCOMENTARIO];
        char    notificar[LNOTIFICAR];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
    } vdcomens;

// Prototipos de funciones definidas en VDCOMEN.C
VDEXPORT diccionario *COMdamediccionario(void);
VDEXPORT int COMbuscatipocomen(char *tipocomen,vdcomens *com);
VDEXPORT int COMnexttipocomen(vdcomens *com);
VDEXPORT int COMbuscacomen(long codcomen,vdcomens *com);
VDEXPORT int COMnextcomen(vdcomens *com);
VDEXPORT int COMbuscacomenytipo(long codcomen,char *tipocomen,vdcomens *com);
VDEXPORT int COMnextcomenytipo(vdcomens *com);
VDEXPORT int COMbuscapornotificar(char *notificar,vdcomens *com);
VDEXPORT int COMnextpornotificar(vdcomens *com);
VDEXPORT int COMselvdcomen(char *tipocomen,long codcomen,long lincomen,vdcomens *com);
VDEXPORT int COMactualizanotificar(vdcomens *com,int error);
VDEXPORT int COMactualizacomentario(vdcomens *com,int error);
VDEXPORT int COMactualizacomentarioynotificar(vdcomens *com,int error);
VDEXPORT int COMactualizavdcomen(vdcomens *com,int error);
VDEXPORT int COMselvdseccomen(long *donde);
VDEXPORT int COMinsert(vdcomens *com,int error);
VDEXPORT int COMdel(vdcomens *com,int error);
VDEXPORT int COMinter(vdcomens *com);
VDEXPORT char *COMlog(vdcomens *com);
char * COMdebug(vdcomens *com);
