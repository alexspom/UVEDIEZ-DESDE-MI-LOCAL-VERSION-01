/*
* Módulo : V10MENUS.C
* Objeto:  Tratamiento de menus basado en virtsels
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

#define MENMSUP 1
#define MENMINF 1
#define MENMIZQ 1
#define MENMDER 1

int MENUHLP = 0;



static void pintamenu(virtsels *s,int real)
{
  menustructs *d = (menustructs *)s->dato;

  if (real) poncolorv(&s->v,CINPUTACT);
     else   poncolorv(&s->v,CINPUTINAC);
  if (d->pinta) d->pinta(s,real);
     else       v10printf(&s->v,"%-*.*s",s->colreg,s->colreg,(*d->indexa)(d->opciones,VIRTPOS(s)));
  poncolorv(&s->v,CNORMAL);
}


static int teclamenu(virtsels *s)
{
  int ret,leng;
  menustructs *d = (menustructs *)s->dato;

  if (MENUHLP) {
    char *total,*titulo,*subtitulo;
    int opcion;

    opcion=VIRTPOS(s);
    titulo=strdup((d->indexa)(d->opciones,-1));
    eliminasp(titulo);
    subtitulo=strdup((d->indexa)(d->opciones,opcion));
    eliminasp(subtitulo);
    total=calloc(strlen(titulo)+strlen(subtitulo)+3,1);
    total=strcpy(total,titulo);
    strcat(total,". ");
    strcat(total,subtitulo);
    v10ponayuda(total);
    free(total);
    free(subtitulo);
    free(titulo);
  }

  leng=strlen(d->buffer);
  if (d->tecla) ret=(*d->tecla)(s);
  else ret=tecla();

  if (MENUHLP) v10quitaayuda();

  if ((ret==cuu || ret==cua) && *d->buffer!='\0') {
    *d->buffer='\0';
    mensajev(s->v1,d->buffer);
  }

  if (!ESFUNC(ret)) {
    switch (ret) {
      case esc:
      case  cr: *d->buffer='\0';
                break;

      case back: if (leng) {
                   d->buffer[leng-1]='\0';
                   mensajev(s->v1,d->buffer);
                 }
                 ret=0;
                 break;

      default: if (ret>=' ') {
                 if (leng < s->colreg) {
                   int posible,unico;

                   d->buffer[leng]=(char)ret;
                   d->buffer[leng+1]='\0';
                   posible=d->busca(d->opciones,d->indexa,d->buffer,&unico);
                   if (posible==-1) d->buffer[leng]='\0';
                   else {
                     reposiciona(s,posible);
                     mensajev(s->v1,d->buffer);
                   }
                 }
                 ret=0;
               }
               break;
      }
  }
  ult_pul=ret;
  return(ret);
}


static char *indexa_por_defecto(char **opciones,int indice)
{
  return(opciones[indice+1]);
}

static int menutecla(virtsels *s)
{
  return(tecla());
}


int menucabecera(void *opciones,int primera,int centrar,int margensup,char *textosup,int x1,int y1,int x2,int y2,int salvar,
			     char *(*indexa)(void *dato,int indice),int (*buscar)(virtsels *s),
			     void (*pinta)(virtsels *s,int indice),int (*sutecla)(virtsels *s),
			     void *dato)
{
  menustructs d;
  unsigned nopciones,leng_titulo,ret;
  char *titulo,*ptr;
  windows w; 
  short *copia=NULL;
  unsigned alto = 1;
  unsigned leng_cursor = 0;

  alto+=MENMSUP+MENMINF;
  d.opciones=opciones;
  d.dato=dato;
  if (indexa) d.indexa=indexa;
  else d.indexa=(void *)indexa_por_defecto;
  if (sutecla) d.tecla=sutecla;
  else d.tecla=menutecla;
  d.pinta=pinta;
  d.busca=(void *)buscar;

  titulo=strdup((d.indexa)(opciones,-1));
  leng_titulo=strlen(titulo)+2;

  for (nopciones=0;(ptr=(*d.indexa)(opciones,nopciones))!=NULL;nopciones++) {
    alto++;
    if (strlen(ptr)>leng_titulo) leng_titulo=strlen(ptr);
    if (strlen(ptr)>leng_cursor) leng_cursor=strlen(ptr);
  }
  if (nopciones==0) {
    free(titulo);
    return(0);
  }
  leng_cursor+=MENMDER+MENMIZQ;
  if (leng_cursor>leng_titulo) leng_titulo=leng_cursor;
  d.buffer=(char *)calloc(1,leng_cursor+1);

  if (x1+leng_titulo >= COLUMNASPANTALLA) {
    leng_titulo=COLUMNASPANTALLA-1-(x1+2);
    if (x1+leng_cursor+1 >= COLUMNASPANTALLA) leng_cursor=leng_titulo;
  }
  if (x2==-1) x2=x1+leng_titulo-1;
  else {
    leng_titulo=x2-x1+1;
    if (leng_cursor > leng_titulo) leng_cursor=leng_titulo;
  }

  if (y1+alto > LINEASPANTALLA-2) alto=LINEASPANTALLA-2-y1+1;
  if (y2==-1) y2=alto+y1-2;

  initvn(&w,x1,y1,x2,y2,"MENUS");

  if (salvar) copia=salvavd(&w);

  clv(&w);
  v10printf(&w,"%-*.*s%s",MENMIZQ,MENMIZQ,"",textosup);

  if (leng_titulo>leng_cursor && centrar) {
    ret=selecciona((leng_titulo-leng_cursor+1)/2,margensup,0,MENMINF,1,&w,nopciones,1,1,leng_cursor,titulo,pintamenu,teclamenu,primera,&d);
  }
  else {
    leng_cursor-=(MENMDER+MENMIZQ);
    ret=selecciona(MENMIZQ,margensup,MENMDER,MENMINF,1,&w,nopciones,1,1,leng_cursor,titulo,pintamenu,teclamenu,primera,&d);
  }

  if (salvar) recuperavd(&w,copia);
  free(titulo);
  free(d.buffer);
  return(ret);
}

int menutotal(void *opciones,int primera,int x1,int y1,int x2,int y2,int salvar,
			     char *(*indexa)(void *dato,int indice),int (*buscar)(virtsels *s),
			     void (*pinta)(virtsels *s,int indice),int (*sutecla)(virtsels *s),
			     void *dato)
{
    return(menucabecera(opciones,primera,1,MENMSUP,"",x1,y1,x2,y2,salvar,indexa,buscar,pinta,sutecla,dato));
}

int menugenerico(void *opciones,int primera,int x1,int y1,int x2,int y2,int salvar,char *(indexa)(void *s,int indice),int (*sutecla)(virtsels *s),void *dato)
{
  int ret;
  ret=menutotal(opciones,primera,x1,y1,x2,y2,salvar,indexa,(int (*)(virtsels *s))v10busca,NULL,sutecla,dato);
  return(ret);
}


int menu(char **opciones,int primera,int x,int y)
{
  return(menugenerico(opciones,primera,x,y,-1,-1,1,NULL,NULL,NULL));
}


static int teclamenuanidado(virtsels *s)
{
  menustructs *d = (menustructs *)s->dato;
  union {va_list *lista;void *ptr;} lista;
  int ret,opcion;
  int (*funcion)(virtsels *);

  ret=tecla();
  lista.ptr=d->dato;
  if (ret==cr) {
    opcion=VIRTPOS(s);
    do {
      funcion=va_arg(*lista.lista,void *);
    } while (opcion-- && funcion!=NULL);
    if (funcion) ret=(*funcion)(s);
       else   {
           lista.ptr=d->dato;
           funcion=va_arg(*lista.lista,void *);
           if (funcion==NULL) final(("Menu anidado sin funcion"));
           ret=(*funcion)(s);
        }
    *d->buffer=0;
    mensajev(s->v1,d->buffer);
  }
  return(ret);
}


int menuanidado(char **opciones,int primera,int x,int y,...)
{
  va_list lista;
  int ret;

  va_start(lista,y);
  ret=menugenerico(opciones,primera,x,y,-1,-1,1,NULL,teclamenuanidado,&lista);
  va_end(lista);
  return(ret);
}


