/*
* Módulo : V10FORBLOQUE.C
* Objeto:  Tratamiento de bloques en formularios
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"

#define MAXTBLOQUES  1000
static bloques *todobloques[MAXTBLOQUES];
static unsigned numbloques=0;
char ultimoerrorbloque[MAXCADENA];



#ifndef __LINUX__
static BOOL CALLBACK enumlibera(HWND hwnd,LPARAM lparam)
{
  SendMessage(hwnd,WM_LIBERABLOQUE,0,lparam);
  return(TRUE);
}

static void comunica_liberacion(bloques *b)
{       
  DWORD htask;
  htask=GetCurrentThreadId();
  EnumThreadWindows(htask,enumlibera,(LPARAM)b);
}
#endif


char  *dameultimoerrorbloque(void)
{
	return(ultimoerrorbloque);

}

int damenumbloque(bloques *b)
{
    int nbloque;
    for (nbloque=0;nbloque<numbloques;nbloque++) {
        if (todobloques[nbloque]==b) break;
    }
    return(nbloque);
}

void ponultimoerrorbloque(char *formato,...)
{
	va_list arg;
	va_start(arg,formato);
	vsprintf(ultimoerrorbloque,formato,arg);
	va_end(arg);

}

int asignacolorbloque(bloques *b,char *color)
{
     int i=damepaleta(color);
     b->vi.w.t=defvent[i].t;
	 poncolorv(&b->vi.w,CNORMAL);
     if (b->s) b->s->v.t=b->vi.w.t;
	 return(0);
}

int poncolorbloque(bloques *b,char *color)
{
	 strcpy(b->color,color);
	 return(asignacolorbloque(b,color));
}

bloques *creabloque(void)
{
  bloques *ret;
  if (numbloques>=MAXTBLOQUES) final(("Maximo numero de bloque alcanzado %d",MAXTBLOQUES));
  ret=calloc(1,sizeof(bloques));
  todobloques[numbloques++]=ret;
  return(ret);
}

bloques *damebloque(forms *f,char *nombre)
{
  int i;
  for (i=0;i<numbloques;i++) {
      if (strcmp(nombre,todobloques[i]->fichero)==0 && f==todobloques[i]->form) return(todobloques[i]);
    }
  return(NULL);
}

fcampos *primerinvalido(bloques *b)
{
  int nc;
  if (esnuloregistro(b)) return(0);
  for (nc=0;nc<b->ncamp;nc++) {
      if (validocampo(b,b->c+nc) && b->c[nc].virtual==0) {
         return(b->c+nc);
       }
    }
  return(NULL);
}

int validobloque(bloques *b,ftrigers *ft)
{
  fcampos *c;
  if ((c=primerinvalido(b))!=NULL) return(*FERROR(b,c));
  return(0);
}

int borraregistro(bloques *b, ftrigers *ft)
{
  pordefectoregistro(b);
  posicionadialog(&b->vi,NULL);
  borraregistroaux(b);
  FORM(b)->nivel=NIVEL_BLOQUE;
  FORM(b)->validar=0;
  return(0);
}

int borrabloque(bloques *b, ftrigers *ft)
{
  int ret=0;
  if (b->modif) {
     if ((ret=commitsino(FORM(b)))!=0) return(ret);
   }
  abreficheroaux(b);
  b->s->numero=b->s->numlin=1;
  b->s->plin=b->s->ulin=b->s->clin=0;
  b->quedan=0;
  b->enquery=0;
  posicionadialog(&b->vi,NULL);
  if (b->invisible==0) representapagina(b->s);
  FORM(b)->nivel=NIVEL_FORM;
  FORM(b)->validar=0;
  b->modif=0;
  mirasimodif(FORM(b));
  FORM(b)->preguntar=1;
  return(ret);
}

int countquery(bloques *b, ftrigers *ft)
{
  int ret;
  gencount(b);
  ret=ejefetchcursor(b->count);
  if (ret) {
     cursordebug(b->count);
     return(ret);
   }
  mensajeform(FORM(b),"Registros en la query %ld",b->total);
  return(0);
}

void liberabloque(bloques *b)
{
  int i;
#ifndef __LINUX__
  comunica_liberacion(b);
#endif
  for (i=0;i<numbloques;i++) if (todobloques[i]==b) break;
  if (i==numbloques) final(("Intentando liberar bloque no creado"));
  for (;i<numbloques-1;i++) todobloques[i]=todobloques[i+1];
  todobloques[--numbloques]=NULL;
  liberacursor(b->insert);
  liberacursor(b->delete);
  liberacursor(b->update);
  liberacursor(b->select);
  liberacursor(b->lock);
  liberacursor(b->reload);
  if (b->fcur) {
     for (i=0;i<b->ncur;i++) {
         if (b->fcur[i].cur) liberacursor(b->fcur[i].cur);
         free(b->fcur[i].sql);
       }
     free(b->fcur);
     b->fcur=NULL;
   }
  liberadialog(&b->vi);
  for (i=0;i<b->ncamp;i++) {
      liberacampo(b->c+i);
    }
  free(b->buffer);
  free(b->ant);
  free(b->bufuquery);
  b->buffer=b->ant=b->bufuquery=NULL;
  if (b->c) free(b->c);
  b->c=NULL;
  for (i=0;i<b->nteclas;i++) {
      liberatriger(b->teclas[i].trig);
    }
  if (b->teclas) free(b->teclas);
  for (i=0;i<b->ntrigers;i++) {
      liberatriger(b->ftriger[i]);
    }
  free(b->ftriger);
  free(b->vi.titulo);
  free(b->ayuda);
  free(b->online);
  free(b->s);
  for (i=0;i<b->numbotones;i++) {
      fbotones *fb=b->fb+i;
      free(fb->texto);
	  if (fb->grupo) free(fb->grupo);
      free(fb->image);
      free(fb->nombre);
      if (fb->tooltip) free(fb->tooltip);
  }
  for (i=0;i<b->numbotoneras;i++) {
      fbotoneras *fb=b->fbot+i;
      free(fb->nombre);
  }
  if (b->frames) free(b->frames);
  free(b->fb);
  free(b->fbot);
  free(b->framesfile);
  for (i=0;i<b->nbstats;i++) free((b->stats+i)->nombre);
  free(b->stats);
  for (i=0;i<b->nbajax;i++) {
	v10ajax *aj = b->ajax+i;
	free(aj->id);
	free(aj->objetojs);
	free(aj->tipo);
	free(aj->modulo);
	free(aj->nombre);
	free(aj->params);
 //   if (aj->sock) v10sockssllibera(aj->sock);
  }
  free(b->ajax);
  for (i=0;i<b->nformtabs;i++) free(b->ftab[i].nombre);
  if (b->ftab) free(b->ftab);

  for (i=0;i<b->nbcomphtml;i++) {
	v10comphtml *co = b->comphtml+i;
	free(co->id);
	free(co->tipo);
	free(co->modulo);
	free(co->nombre);
	free(co->params);
  }  
  free(b->comphtml);
  free(b->where);
  free(b->orderby);
  free(b->groupby);
  free(b->having);
  free(b->extraselect);
  cierraficheroaux(b);
  liberatriger(b->ftimeout);
  liberatriger(b->fpreinsert);
  liberatriger(b->fpostinsert);
  liberatriger(b->fpreupdate);
  liberatriger(b->fpostupdate);
  liberatriger(b->fpredelete);
  liberatriger(b->fpostdelete);
  liberatriger(b->fprequery);
  liberatriger(b->fpostquery);
  liberatriger(b->ffinquery);
  liberatriger(b->fpreregistro);
  liberatriger(b->fpostregistro);
  liberatriger(b->fprebloque);
  liberatriger(b->fpostbloque);
  liberatriger(b->fprecommit);
  liberatriger(b->fpostcommit);
  liberatriger(b->fprerollback);
  liberatriger(b->fpostrollback);
  liberatriger(b->fprepinta);
  liberatriger(b->fpostpinta);
  liberatriger(b->fonpinta);
  liberatriger(b->feventos.onclick);
  liberatriger(b->feventos.onrightclick);
  liberatriger(b->feventos.oncenterclick);
  liberatriger(b->feventos.ondbclick);
  liberatriger(b->feventos.onmouseover);
  liberatriger(b->feventos.onmouseout);
  liberatriger(b->feventos.onmousemove);
  liberatriger(b->contextual);
  free(b);
}
