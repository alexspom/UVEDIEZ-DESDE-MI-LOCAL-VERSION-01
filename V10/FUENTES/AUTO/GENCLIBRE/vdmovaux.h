// Fichero generado automaticamente a partir de VDMOVAUX.DEF

VDEXPORT diccionario dmovaux;
#ifndef LLIMPIAR
#define LLIMPIAR 2
#endif

typedef struct {
        long    ret;
        long    stfinalizado;
        long    strevision;
        long    stpdteinter;
        long    stsininter;
        long    stdemlmvfinal;
        long    stdemcmvfinal;
        long    nuevomov;
        char    limpiar[LLIMPIAR];
        long    avanza;
        double  reservado;
        long    codmov;
        double  cantidad;
        long    status;
} vdmovauxs; 


VDEXPORT diccionario *MOVAUXdamediccionario(void);
VDEXPORT int MOVAUXprocpartemov(long codmov,double cantidad,long nuevomov,char *limpiar,vdmovauxs *movaux);
VDEXPORT int MOVAUXprocanulamov(long codmov,long ret,vdmovauxs *movaux);
VDEXPORT int MOVAUXprocfinalizamov(long codmov,long stfinalizado,long stdemlmvfinal,long stdemcmvfinal,long ret,vdmovauxs *movaux);
VDEXPORT int MOVAUXprocinterfasamov(long codmov,long strevision,long stpdteinter,long stsininter,long ret,vdmovauxs *movaux);
VDEXPORT int MOVAUXprocavanzapdtestock(long codmov,long avanza,vdmovauxs *movaux);
VDEXPORT int MOVAUXprocreservamov(long codmov,long status,double reservado,vdmovauxs *movaux);
VDEXPORT char * MOVAUXdebug(vdmovauxs *movaux);

//Codigo incluido explicitamente en el DEF
VDEXPORT int MOVfinalizamov(void *ptr, long stfinalizado, long stdemlmvfinal, long stdemcmvfinal);
VDEXPORT int MOVinterfasamov(void *ptr,long strevision, long stpdteinter, long stsininter);
VDEXPORT int MOVanulamov(void *ptr);

