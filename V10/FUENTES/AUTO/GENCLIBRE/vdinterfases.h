// Fichero generado automaticamente a partir de VDINTERFASES.DEF

VDEXPORT diccionario dintlaux;
#ifndef LROWIDAUX
#define LROWIDAUX 19
#endif

#ifndef LVALOR
#define LVALOR 256
#endif

#ifndef LTABLAORIG
#define LTABLAORIG 34
#endif

#ifndef LFORMATOPADRE
#define LFORMATOPADRE 21
#endif

#ifndef LFECHAENT
#define LFECHAENT 32
#endif

#ifndef LFECHASAL
#define LFECHASAL 32
#endif

#ifndef LFMTOENT
#define LFMTOENT 32
#endif

#ifndef LFMTOSAL
#define LFMTOSAL 32
#endif

#ifndef LTABLA
#define LTABLA 33
#endif

#ifndef LTIPOINTERFASE
#define LTIPOINTERFASE 21
#endif

#ifndef LFORMATO
#define LFORMATO 21
#endif

#ifndef LREGISTRO
#define LREGISTRO 2049
#endif

#ifndef LCAMPO
#define LCAMPO 33
#endif

typedef struct {
        char    rowidaux[LROWIDAUX];
        char    valor[LVALOR];
        char    tablaorig[LTABLAORIG];
        long    statuscab;
        char    formatopadre[LFORMATOPADRE];
        char    fechaent[LFECHAENT];
        char    fechasal[LFECHASAL];
        char    fmtoent[LFMTOENT];
        char    fmtosal[LFMTOSAL];
        long    longreg;
        char    tabla[LTABLA];
        char    tipointerfase[LTIPOINTERFASE];
        char    formato[LFORMATO];
        char    registro[LREGISTRO];
        char    campo[LCAMPO];
        long    status;
} vdintlauxs; 


VDEXPORT diccionario *INTLAUXdamediccionario(void);
VDEXPORT int INTLAUXbuscadameroid(char *tabla,char *tablaorig,char *tipointerfase,char *formato,char *registro,vdintlauxs *intlaux);
VDEXPORT int INTLAUXnextdameroid(vdintlauxs *intlaux);
VDEXPORT int INTLAUXbuscavalorcampo(char *tipointerfase,char *formato,char *registro,char *campo,char *tabla,vdintlauxs *intlaux);
VDEXPORT int INTLAUXnextvalorcampo(vdintlauxs *intlaux);
VDEXPORT int INTLAUXbuscareggral(long status,long statuscab,vdintlauxs *intlaux);
VDEXPORT int INTLAUXnextreggral(vdintlauxs *intlaux);
VDEXPORT int INTLAUXseltransfecha(char *fechaent,char *fmtoent,char *fmtosal,vdintlauxs *intlaux);
VDEXPORT char * INTLAUXdebug(vdintlauxs *intlaux);
