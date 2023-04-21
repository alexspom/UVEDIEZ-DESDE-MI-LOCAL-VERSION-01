// Modulo generado automaticamente a partir de VDRECURSO.DEF

VDEXPORT diccionario drec;
#define RECNUMCOL	35
typedef struct {
        char    rowid[ROWIDLON];
        char    codrecurso[LCODRECURSO];
        char    desrecurso[LDESRECURSO];
        char    activo[LACTIVO];
        char    dirrecurso[LDIRRECURSO];
        char    privilegioslogin[LPRIVILEGIOSLOGIN];
        char    codubi[LCODUBI];
        char    codmat[LCODMAT];
        char    ultcodubi[LULTCODUBI];
        char    conectado[LCONECTADO];
        char    terminal[LTERMINAL];
        long    sid;
        long    serialnum;
        char    contenedores[LCONTENEDORES];
        char    embalajes[LEMBALAJES];
        char    unidadessueltas[LUNIDADESSUELTAS];
        char    codope[LCODOPE];
        long    status;
        char    codperfil[LCODPERFIL];
        char    npantalla[LNPANTALLA];
        char    codimpre[LCODIMPRE];
        long    maxalt;
        long    minalt;
        char    tecleo[LTECLEO];
        char    driver[LDRIVER];
        char    libplanificador[LLIBPLANIFICADOR];
        char    planificador[LPLANIFICADOR];
        char    paramplanif[LPARAMPLANIF];
        char    vdextra[LVDEXTRA];
        long    codcomen;
        char    codopemodif[LCODOPEMODIF];
        long    fecmodif;
        char    horamodif[LHORAMODIF];
        long    fecultcom;
        char    horaultcom[LHORAULTCOM];
    } vdrecursos;

// Prototipos de funciones definidas en VDRECURSO.C
VDEXPORT diccionario *RECdamediccionario(void);
VDEXPORT int RECselcodrecurso(char *codrecurso,vdrecursos *rec);
VDEXPORT int RECbuscadirrecurso(char *dirrecurso,vdrecursos *rec);
VDEXPORT int RECnextdirrecurso(vdrecursos *rec);
VDEXPORT int RECbuscastatus(long status,vdrecursos *rec);
VDEXPORT int RECnextstatus(vdrecursos *rec);
VDEXPORT int RECselvdrecurso(char *codrecurso,vdrecursos *rec);
VDEXPORT int RECactualizastatus(vdrecursos *rec,int error);
VDEXPORT int RECactualizanpantalla(vdrecursos *rec,int error);
VDEXPORT int RECactualizaconectado(vdrecursos *rec,int error);
VDEXPORT int RECactualizacodope(vdrecursos *rec,int error);
VDEXPORT char *REClog(vdrecursos *rec);
char * RECdebug(vdrecursos *rec);
