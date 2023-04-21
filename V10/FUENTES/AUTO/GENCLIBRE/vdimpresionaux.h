// Fichero generado automaticamente a partir de VDIMPRESIONAUX.DEF

VDEXPORT diccionario dimpre;
#ifndef LORDENADOR
#define LORDENADOR 33
#endif

#ifndef LTIPOIMPRE
#define LTIPOIMPRE 13
#endif

#ifndef LDOCUMENTO
#define LDOCUMENTO 257
#endif

#ifndef LCODIMPRE
#define LCODIMPRE 16
#endif

#ifndef LFICHERO
#define LFICHERO 257
#endif

#ifndef LPARAMS
#define LPARAMS 1025
#endif

#ifndef LHORAPLANIF
#define LHORAPLANIF 9
#endif

typedef struct {
        long    ret;
        long    numasig;
        char    ordenador[LORDENADOR];
        char    tipoimpre[LTIPOIMPRE];
        char    documento[LDOCUMENTO];
        char    codimpre[LCODIMPRE];
        char    fichero[LFICHERO];
        char    params[LPARAMS];
        long    numcopias;
        long    fecplanif;
        char    horaplanif[LHORAPLANIF];
} vdimpres; 


VDEXPORT diccionario *IMPREdamediccionario(void);
VDEXPORT int IMPREbuscaccuentaasiguser(char *ordenador,char *tipoimpre,char *documento,vdimpres *impre);
VDEXPORT int IMPREnextccuentaasiguser(vdimpres *impre);
VDEXPORT int IMPREbuscaccuentaasig(char *ordenador,char *tipoimpre,char *documento,vdimpres *impre);
VDEXPORT int IMPREnextccuentaasig(vdimpres *impre);
VDEXPORT int IMPREprocspool(char *ordenador,char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif,long ret,vdimpres *impre);
VDEXPORT int IMPREprocaudita(char *ordenador,char *tipoimpre,char *codimpre,char *fichero,char *documento,char *params,long numcopias,long fecplanif,char *horaplanif,long ret,vdimpres *impre);
VDEXPORT char * IMPREdebug(vdimpres *impre);
