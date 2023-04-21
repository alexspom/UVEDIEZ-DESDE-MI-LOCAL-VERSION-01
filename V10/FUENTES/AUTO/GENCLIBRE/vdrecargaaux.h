// Fichero generado automaticamente a partir de VDRECARGAAUX.DEF

VDEXPORT diccionario drecarga;
#ifndef LLISTAALMAS
#define LLISTAALMAS 1025
#endif

#ifndef LLISTAAREAS
#define LLISTAAREAS 1025
#endif

#ifndef LCODUBI
#define LCODUBI 13
#endif

#ifndef LRECARGAR
#define LRECARGAR 13
#endif

#ifndef LUNIAGRUPAE
#define LUNIAGRUPAE 2
#endif

#ifndef LUNICAPAC
#define LUNICAPAC 2
#endif

#ifndef LUNIAGRUPADEML
#define LUNIAGRUPADEML 2
#endif

#ifndef LCODART
#define LCODART 41
#endif

#ifndef LTIPOREDONDEO
#define LTIPOREDONDEO 2
#endif

typedef struct {
        char    listaalmas[LLISTAALMAS];
        char    listaareas[LLISTAAREAS];
        char    codubi[LCODUBI];
        char    recargar[LRECARGAR];
        char    uniagrupae[LUNIAGRUPAE];
        char    unicapac[LUNICAPAC];
        char    uniagrupademl[LUNIAGRUPADEML];
        long    stkmax;
        long    stkmin;
        long    stkurg;
        char    codart[LCODART];
        long    stock;
        long    ordenado;
        long    cantidad;
        char    tiporedondeo[LTIPOREDONDEO];
} vdrecargas; 


VDEXPORT diccionario *RECARGAdamediccionario(void);
VDEXPORT int RECARGAbuscaubis(char *listaareas,char *listaalmas,vdrecargas *recarga);
VDEXPORT int RECARGAnextubis(vdrecargas *recarga);
VDEXPORT char * RECARGAdebug(vdrecargas *recarga);
