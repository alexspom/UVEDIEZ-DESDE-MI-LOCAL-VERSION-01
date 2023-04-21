// Fichero generado automaticamente a partir de VDCONTEAUX.DEF

VDEXPORT diccionario dcntaux;
#ifndef LVERIFICAUBI
#define LVERIFICAUBI 2
#endif

#ifndef LCONCEPTOENT
#define LCONCEPTOENT 11
#endif

#ifndef LCONCEPTOSAL
#define LCONCEPTOSAL 11
#endif

#ifndef LFUENTE
#define LFUENTE 13
#endif

#ifndef LSUMIDERO
#define LSUMIDERO 13
#endif

#ifndef LPATRONBLOQUEOSORI
#define LPATRONBLOQUEOSORI 21
#endif

#ifndef LOBSERV
#define LOBSERV 4097
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 513
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

#ifndef LTIPOCONTE
#define LTIPOCONTE 11
#endif

typedef struct {
        long    ret;
        char    verificaubi[LVERIFICAUBI];
        char    conceptoent[LCONCEPTOENT];
        char    conceptosal[LCONCEPTOSAL];
        char    fuente[LFUENTE];
        char    sumidero[LSUMIDERO];
        char    patronbloqueosori[LPATRONBLOQUEOSORI];
        char    observ[LOBSERV];
        char    codmat[LCODMAT];
        char    codubi[LCODUBI];
        long    codmov;
        char    comentario[LCOMENTARIO];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        char    bloqueos[LBLOQUEOS];
        double  cantidad;
        char    tipoconte[LTIPOCONTE];
} vdcntauxs; 


VDEXPORT diccionario *CNTAUXdamediccionario(void);
VDEXPORT int CNTAUXprocdametemporal(long ret,char *codubi,char *codmat,vdcntauxs *cntaux);
VDEXPORT int CNTAUXprocreenganchaconte(long codmov,char *codmat,char *verificaubi,char *comentario,long ret,vdcntauxs *cntaux);
VDEXPORT int CNTAUXprocbloqueosstkconte(char *codmat,char *codart,char *codlot,char *conceptoent,char *fuente,char *conceptosal,char *sumidero,char *patronbloqueosori,char *bloqueos,char *observ,double cantidad,char *comentario,long ret,vdcntauxs *cntaux);
VDEXPORT int CNTAUXprocusaconte(char *codmat,char *codubi,char *tipoconte,char *comentario,long ret,vdcntauxs *cntaux);
VDEXPORT int CNTAUXbuscadamecntnomovible(char *codubi,vdcntauxs *cntaux);
VDEXPORT int CNTAUXnextdamecntnomovible(vdcntauxs *cntaux);
VDEXPORT char * CNTAUXdebug(vdcntauxs *cntaux);
