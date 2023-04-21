/*
* Módulo : V10FORBOTON.C
* Objeto:  Tratamiento de botones y botoneras en formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

static fbotones sfb[MAXBOTONES];
static int numbotones;
static fbotoneras sfbot[MAXBOTONERAS];
static int numbotoneras;
static int init=0;

static void liberabotones(void)
{
    int i;
    for (i=0;i<numbotones;i++) {
        fbotones *fb=sfb+i;
        free(fb->nombre);
        free(fb->texto);
        free(fb->image);
    }
    for (i=0;i<numbotoneras;i++) {
        fbotoneras *fbot=sfbot+i;
        free(fbot->nombre);
        free(fbot->b);
    }
}

fbotones *buscaboton(char *nombre)
{
    int i;
    for (i=0;i<numbotones;i++) {
        if (strcmp(nombre,sfb[i].nombre)==0) return(sfb+i);
    }
    return(NULL);
}

int duplicaboton(char *nombre,fbotones *b)
{
    fbotones *fb;
    fb=buscaboton(nombre);
    if (fb==NULL) return(1);
    *b=*fb;
    b->nombre=strdup(fb->nombre);
    b->texto=strdup(fb->texto);
    b->image=strdup(fb->image);
    return(0);
}

void declaraboton(char *nombre,int posx,int posy,int lonx,int lony,char *texto,char *image,int tec)
{
    fbotones *fb;
    if (init==0) atexit(liberabotones);
    init=1;
    if ((fb=buscaboton(nombre))!=NULL) {
        free(fb->nombre);
        free(fb->image);
        free(fb->texto);
    } else {
        if (numbotones+1>=MAXBOTONES) final(("Demasiados botones"));  
        fb=sfb+numbotones++;
    }
    fb->nombre=strdup(nombre); 
    fb->posx=posx;
    fb->posy=posy;
    fb->lonx=lonx;
    fb->lony=lony;
    fb->texto=strdup(texto);
    fb->image=strdup(image);
    fb->tecla=tec; 
}

fbotoneras *buscabotonera(char *nombre)
{
    int i;
    for (i=0;i<numbotoneras;i++) {
        if (strcmp(nombre,sfbot[i].nombre)==0) return(sfbot+i);
    }
    return(NULL);
}


void declarabotonera(char *nombre,int posx,int posy,int lonx,int lony,...)
{
    fbotoneras *fbot;
    va_list arg;
    char *nomboton;
    int numbot=0; 
    if (init==0) atexit(liberabotones);
    init=1;
    if ((fbot=buscabotonera(nombre))!=NULL) {
        free(fbot->nombre);
        free(fbot->b);
    } else {
        if (numbotoneras+1>=MAXBOTONERAS) final(("Demasiadas botoneras"));
        fbot=sfbot+numbotoneras++;
    }
    fbot->posx=posx;
    fbot->posy=posy;
    fbot->lonx=lonx;
    fbot->lony=lony;
    fbot->nombre=strdup(nombre);
    fbot->numbotones=0;
    va_start(arg,lony);
    while (va_arg(arg,char *)!=NULL) numbot++;
    va_end(arg);
    fbot->b=calloc(numbot,sizeof(fbotones *));
    va_start(arg,lony);
    while ((nomboton=va_arg(arg,char *))!=NULL) {
        fbotones *fb=buscaboton(nomboton);
        if (fb!=NULL) {
            fbot->b[fbot->numbotones++]=fb;
        }
    }
} 

int duplicabotonera(char *nombre,fbotoneras *b)
{
    fbotoneras *fb;
    fb=buscabotonera(nombre);
    if (fb==NULL) return(1);
    *b=*fb;
    b->nombre=strdup(fb->nombre);
    b->b=calloc(b->numbotones,sizeof(fbotones *));
    memcpy(b->b,fb->b,b->numbotones*sizeof(fbotones *));
    return(0);
}

fbotones *damebotonbloque(bloques *b,char *nombre)
{
    int i;
    for (i=0;i<b->numbotones;i++) {
        fbotones *fb=b->fb+i;
        if (strcmp(fb->nombre,nombre)==0) return(fb);
    }
    return(buscaboton(nombre));
}