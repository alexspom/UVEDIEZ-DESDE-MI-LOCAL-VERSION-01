// Fichero generado automaticamente a partir de VDRUTAS.DEF

VDEXPORT diccionario drutas;
#ifndef LCODAREAORI
#define LCODAREAORI 21
#endif

#ifndef LTRAMOFINAL
#define LTRAMOFINAL 3
#endif

#ifndef LCODMAT
#define LCODMAT 19
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LCODAREA
#define LCODAREA 21
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

#ifndef LCODAREADEST
#define LCODAREADEST 21
#endif

#ifndef LFUERZAPALET
#define LFUERZAPALET 2
#endif

#ifndef LMOVMUEVEPALET
#define LMOVMUEVEPALET 2
#endif

#ifndef LTRMMUEVEPALET
#define LTRMMUEVEPALET 2
#endif

#ifndef LTRMMUEVEPARCIAL
#define LTRMMUEVEPARCIAL 2
#endif

#ifndef LVALIDEZ
#define LVALIDEZ 21
#endif

#ifndef LCOMENTARIO
#define LCOMENTARIO 257
#endif

#ifndef LUNICAPAC
#define LUNICAPAC 2
#endif

typedef struct {
        char    codareaori[LCODAREAORI];
        double  cantidadtotal;
        char    tramofinal[LTRAMOFINAL];
        char    codmat[LCODMAT];
        long    codmov;
        char    codubi[LCODUBI];
        long    codflujo;
        char    codarea[LCODAREA];
        char    codart[LCODART];
        char    codlot[LCODLOT];
        double  uniemb;
        char    bloqueos[LBLOQUEOS];
        long    priotramo;
        char    codareadest[LCODAREADEST];
        char    fuerzapalet[LFUERZAPALET];
        char    movmuevepalet[LMOVMUEVEPALET];
        char    trmmuevepalet[LTRMMUEVEPALET];
        char    trmmueveparcial[LTRMMUEVEPARCIAL];
        char    validez[LVALIDEZ];
        char    comentario[LCOMENTARIO];
        long    codcamino;
        long    status;
        long    cantidad;
        char    unicapac[LUNICAPAC];
} vdrutass; 


VDEXPORT diccionario *RUTASdamediccionario(void);
VDEXPORT int RUTASbuscastkdisponible(char *codmat,long codmov,vdrutass *rutas);
VDEXPORT int RUTASnextstkdisponible(vdrutass *rutas);
VDEXPORT int RUTASbuscacontesflujos(long codmov,long codflujo,char *codarea,vdrutass *rutas);
VDEXPORT int RUTASnextcontesflujos(vdrutass *rutas);
VDEXPORT int RUTASbuscastkareapicking(char *codarea,char *codart,double uniemb,long codflujo,char *codlot,vdrutass *rutas);
VDEXPORT int RUTASnextstkareapicking(vdrutass *rutas);
VDEXPORT int RUTASbuscasgtetramo(long codmov,vdrutass *rutas);
VDEXPORT int RUTASnextsgtetramo(vdrutass *rutas);
VDEXPORT int RUTASbuscaareaspicking(long codcamino,char *codareaori,vdrutass *rutas);
VDEXPORT int RUTASnextareaspicking(vdrutass *rutas);
VDEXPORT int RUTASprocasignaflujo(long codmov,long status,vdrutass *rutas);
VDEXPORT int RUTASbuscaubicapacidad(char *codubi,char *unicapac,vdrutass *rutas);
VDEXPORT int RUTASnextubicapacidad(vdrutass *rutas);
VDEXPORT char * RUTASdebug(vdrutass *rutas);
