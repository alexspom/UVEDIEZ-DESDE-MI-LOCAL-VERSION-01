// Modulo generado automaticamente a partir de VDIMPRESPOOL.DEF

VDEXPORT diccionario dimsp;
#define IMSPNUMCOL	28
//#define LGRUPOIMPRE 16
//#define LCOMENTARIO 513
typedef struct {
        char    rowid[ROWIDLON];
        long    seqimpre;
        char    ordenador[LORDENADOR];
        char    tipoimpre[LTIPOIMPRE];
        char    codimpre[LCODIMPRE];
        char    fichero[LFICHERO];
        char    documento[LDOCUMENTO];
        char    params[LPARAMS];
        long    numcopias;
        long    prioridad;
        long    status;
        char    codopeins[LCODOPEINS];
        long    fecins;
        char    horains[LHORAINS];
        long    fecplanif;
        char    horaplanif[LHORAPLANIF];
        long    fecimp;
        char    horaimp[LHORAIMP];
        char    impprograma[LIMPPROGRAMA];
        char    impmodulo[LIMPMODULO];
        char    impaccion[LIMPACCION];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        char    grupoimpre[LGRUPOIMPRE];
        char    comentario[LCOMENTARIO];
    } vdimprespools;

// Prototipos de funciones definidas en VDIMPRESPOOL.C
VDEXPORT diccionario *IMSPdamediccionario(void);
VDEXPORT int IMSPbuscapendiente(long status,char *grupoimpre,vdimprespools *imsp);
VDEXPORT int IMSPnextpendiente(vdimprespools *imsp);
VDEXPORT int IMSPselvdimprespool(long seqimpre,vdimprespools *imsp);
VDEXPORT int IMSPactualizaimpreso(vdimprespools *imsp,int error);
VDEXPORT int IMSPactualizadocumento(vdimprespools *imsp,int error);
VDEXPORT int IMSPselvdsecimprespool(long *donde);
VDEXPORT int IMSPinsert(vdimprespools *imsp,int error);
VDEXPORT char *IMSPlog(vdimprespools *imsp);
char * IMSPdebug(vdimprespools *imsp);
