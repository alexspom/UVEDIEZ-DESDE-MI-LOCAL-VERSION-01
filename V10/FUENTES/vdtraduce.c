#include "vd.h"

#define MAXTRADUCCIONES 10000


#define CSELTRADUCE "SELECT TEXTOORIG,IDIOMA,TRADUCCION FROM VDTRADUCE"
static v10cursors *v10seltraduce;

typedef struct {
             char textoorig[LTEXTOORIG];
             char idioma[LIDIOMA];
             char traduccion[LTEXTOORIG];
} traducciones;

static traducciones trad;

typedef struct {
               char *textoorig;
               char *idioma;
               char *traduccion;
} eltrads;

static eltrads arrtrad[MAXTRADUCCIONES];
static int numtrads;
static char bufftrad[MAXCADENA];


static void inittraducciones(void)
{
    v10seltraduce=abrecursor(CSELTRADUCE);
    definetodo(v10seltraduce,trad.textoorig,sizeof(trad.textoorig),V10CADENA,
                                trad.idioma,sizeof(trad.idioma),V10CADENA,
                                trad.traduccion,sizeof(trad.traduccion),V10CADENA,
                                NULL);
    ejecutacursor(v10seltraduce);
    while (fetchcursor(v10seltraduce)==0) {
        if (!es_blanco(trad.traduccion)) {
            arrtrad[numtrads].idioma=strdup(trad.idioma);
            if (v10usaansi) {
                v10ansitooem(trad.textoorig,trad.textoorig);
                v10ansitooem(trad.traduccion,trad.traduccion);
            }
            arrtrad[numtrads].textoorig=strdup(trad.textoorig);
            arrtrad[numtrads].traduccion=strdup(trad.traduccion);
            numtrads++;
        }
    }
    liberacursor(v10seltraduce);
}

static char *vdtraduce(char *cadena)
{
    int i;
    char *ptr;
    if (v10seltraduce==NULL) inittraducciones();
    for (ptr=cadena;*ptr==' ';ptr++);
    for (i=0;i<numtrads;i++) {
        if (strcmp(arrtrad[i].textoorig,ptr)==0 && strcmp(arrtrad[i].idioma,idiomav10)==0) {
            if (ptr==cadena) return(arrtrad[i].traduccion);
            sprintf(bufftrad,"%-*.*s%s",ptr-cadena,ptr-cadena,"",arrtrad[i].traduccion);
            return(bufftrad);
        }
    }
    return(cadena);
}

static char *vduntrans(char *cadena)
{
    int i;
    if (v10seltraduce==NULL) inittraducciones();
    for (i=0;i<numtrads;i++) {
        if (strcmp(arrtrad[i].traduccion,cadena)==0 && strcmp(arrtrad[i].idioma,idiomav10)==0) return(arrtrad[i].textoorig);
    }
    return(cadena);
}

static char *vdtraducecr(char *cadena)
{
    static char micad[MAXCADENA],copia[MAXCADENA];
    char *aux=copia,*fin;
    int lineas=0;
    *micad=0;
    strcpy(copia, cadena);
    while ((fin=strchr(aux,'\n'))!=NULL) {
        *fin=0;
        sprintf(micad+strlen(micad),"%s\n",vdtraduce(aux));
        *fin='\n';
        aux=fin+1;
        lineas++;
    }
    if (lineas==0 && *cadena!=' ') return(vdtraduce(aux));
    sprintf(micad+strlen(micad),"%s",vdtraduce(aux));
    return(micad);
}

VDEXPORT int ponv10traduce(void)
{
	ejecutaimmediatoparam("BEGIN VDUSER.SETIDIOMA(\'%s\');END;",idiomav10);
    setv10trans(vdtraducecr,vduntrans);
    return(0);
}
