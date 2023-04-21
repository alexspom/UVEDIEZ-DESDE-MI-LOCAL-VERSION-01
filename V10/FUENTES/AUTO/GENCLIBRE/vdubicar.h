// Fichero generado automaticamente a partir de VDUBICAR.DEF

VDEXPORT diccionario dubicar;
#ifndef LVERIFICACOMP
#define LVERIFICACOMP 3
#endif

#ifndef LVEFIFICAFLP
#define LVEFIFICAFLP 3
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LCODALM
#define LCODALM 5
#endif

#ifndef LTAREA
#define LTAREA 33
#endif

#ifndef LCODAREA
#define LCODAREA 21
#endif

#ifndef LUNIAGRUPAE
#define LUNIAGRUPAE 2
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LCODLOT
#define LCODLOT 21
#endif

#ifndef LBLOQUEOS
#define LBLOQUEOS 11
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODCONCE
#define LCODCONCE 11
#endif

#ifndef LCODRECURSO
#define LCODRECURSO 11
#endif

#ifndef LCODMATDEST
#define LCODMATDEST 19
#endif

typedef struct {
        long    cuantos;
        char    verificacomp[LVERIFICACOMP];
        char    vefificaflp[LVEFIFICAFLP];
        char    codmat[LCODMAT];
        char    codalm[LCODALM];
        char    tarea[LTAREA];
        long    codmov;
        char    codarea[LCODAREA];
        long    pasillo;
        char    uniagrupae[LUNIAGRUPAE];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  uniemb;
        char    bloqueos[LBLOQUEOS];
        double  cantidad;
        char    codubi[LCODUBI];
        char    codconce[LCODCONCE];
        long    priomov;
        long    status;
        char    codrecurso[LCODRECURSO];
        char    codmatdest[LCODMATDEST];
        long    idquery;
        long    compatible;
} vdubicars; 


VDEXPORT diccionario *UBICARdamediccionario(void);
VDEXPORT int UBICARbuscaconteaubicar(char *codalm,vdubicars *ubicar);
VDEXPORT int UBICARnextconteaubicar(vdubicars *ubicar);
VDEXPORT int UBICARprocreubiconte(char *codmat,char *tarea,long codmov,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar);
VDEXPORT int UBICARprocreubistk(char *codmat,char *tarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,long codmov,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar);
VDEXPORT int UBICARproccambioubiconte(char *codmat,char *codubi,char *tarea,long codmov,char *vefificaflp,char *verificacomp,char *codconce,long priomov,long status,char *codrecurso,vdubicars *ubicar);
VDEXPORT int UBICARproccambioubistk(char *codmat,char *codubi,char *codmatdest,char *tarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,long codmov,char *vefificaflp,char *verificacomp,char *codconce,long priomov,long status,char *codrecurso,vdubicars *ubicar);
VDEXPORT int UBICARproccreaidquery(char *codmat,char *codarea,long idquery,vdubicars *ubicar);
VDEXPORT int UBICARbuscaconteparcial(char *codubi,vdubicars *ubicar);
VDEXPORT int UBICARnextconteparcial(vdubicars *ubicar);
VDEXPORT int UBICARbuscaubilibre(long idquery,char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,long pasillo,char *uniagrupae,vdubicars *ubicar);
VDEXPORT int UBICARnextubilibre(vdubicars *ubicar);
VDEXPORT int UBICARbuscaubicompatible(char *codmat,char *codubi,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,vdubicars *ubicar);
VDEXPORT int UBICARnextubicompatible(vdubicars *ubicar);
VDEXPORT char * UBICARdebug(vdubicars *ubicar);

//Codigo incluido explicitamente en el DEF
VDEXPORT int UBIdameubiarealibre(char *codmat,char *codarea,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,int pasillo,char *uniagrupa,vdubicars *ubicar);
VDEXPORT int UBIdameubiareaconte(char *codmat,char *codarea,int pasillo, char uniagrupa, char *codubi);
VDEXPORT int UBIdameubiareastk(char *codmat,char *codart,char *codlot,double uniemb,char *bloqueos,double cantidad,char *codarea,int pasillo, char uniagrupa,char *codubi);

