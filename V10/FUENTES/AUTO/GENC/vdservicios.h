// Modulo generado automaticamente a partir de VDSERVICIOS.DEF

VDEXPORT diccionario dser;
#define SERNUMCOL	31
typedef struct {
        char    rowid[ROWIDLON];
        char    codgruposerv[LCODGRUPOSERV];
        char    codservicio[LCODSERVICIO];
        char    desservicio[LDESSERVICIO];
        char    activo[LACTIVO];
        char    visualizado[LVISUALIZADO];
        char    ejecutable[LEJECUTABLE];
        char    pathservicio[LPATHSERVICIO];
        char    pathv10servicio[LPATHV10SERVICIO];
        char    envservicio[LENVSERVICIO];
        char    paramservicio[LPARAMSERVICIO];
        long    status;
        long    pid;
        long    sid;
        long    serial;
        char    arranque[LARRANQUE];
        char    cierre[LCIERRE];
        char    ejecutar[LEJECUTAR];
        char    patronplanif[LPATRONPLANIF];
        char    horainicio[LHORAINICIO];
        char    horalimite[LHORALIMITE];
        long    intervalo;
        long    fecarranque;
        long    fecultejec;
        char    horaultejec[LHORAULTEJEC];
        long    fecejec;
        char    horaejec[LHORAEJEC];
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    codcomen;
    } vdservicioss;

// Prototipos de funciones definidas en VDSERVICIOS.C
VDEXPORT diccionario *SERdamediccionario(void);
VDEXPORT int SERselcodservicio(char *codgruposerv,char *codservicio,vdservicioss *ser);
VDEXPORT int SERselpid(long pid,vdservicioss *ser);
VDEXPORT int SERbuscacodgruposerv(char *codgruposerv,vdservicioss *ser);
VDEXPORT int SERnextcodgruposerv(vdservicioss *ser);
VDEXPORT int SERselvdservicios(char *codgruposerv,char *codservicio,vdservicioss *ser);
VDEXPORT int SERactualizasid(vdservicioss *ser,int error);
VDEXPORT int SERactualizadescinmediata(vdservicioss *ser,int error);
VDEXPORT int SERactualizaestado(vdservicioss *ser,int error);
VDEXPORT int SERactualizaplanif(vdservicioss *ser,int error);
VDEXPORT char *SERlog(vdservicioss *ser);
char * SERdebug(vdservicioss *ser);
