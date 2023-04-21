// Fichero generado automaticamente a partir de VDVERIF.DEF

VDEXPORT diccionario dverif;
#ifndef LMSJERROR
#define LMSJERROR 1025
#endif

#ifndef LCODBULTO
#define LCODBULTO 19
#endif

typedef struct {
        long    ret;
        char    msjerror[LMSJERROR];
        long    concmensaje;
        long    anularprecintos;
        long    llevaalbaran;
        char    codbulto[LCODBULTO];
} vdverifs; 


VDEXPORT diccionario *VERIFdamediccionario(void);
VDEXPORT int VERIFprocponverificar(char *codbulto,long ret,char *msjerror,long concmensaje,vdverifs *verif);
VDEXPORT int VERIFprocverificapeso(char *codbulto,long ret,char *msjerror,vdverifs *verif);
VDEXPORT int VERIFprocverificatpc(char *codbulto,long ret,char *msjerror,vdverifs *verif);
VDEXPORT int VERIFprocverificaestado(char *codbulto,long ret,char *msjerror,vdverifs *verif);
VDEXPORT int VERIFbuscacllevaalbaran(char *codbulto,vdverifs *verif);
VDEXPORT int VERIFnextcllevaalbaran(vdverifs *verif);
VDEXPORT int VERIFbuscacanularprecintos(char *codbulto,vdverifs *verif);
VDEXPORT int VERIFnextcanularprecintos(vdverifs *verif);
VDEXPORT char * VERIFdebug(vdverifs *verif);
