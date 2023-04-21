/*
* Módulo : V10FORCONTEXT.C
* Objeto:  Tratamiento de menus contextuales
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10form.h"


void liberaforcontext(formenus*f)
{
  int i;
  if (f==NULL) return;
  for (i=0;i<f->nopciones;i++) {
      opcionesmenu *op=f->op+i;
      if (op->opcion) free(op->opcion);
      liberatriger(op->ft);
   }
  free(f->titulo);
  free(f->op);
  free(f);
}

static int teclacontex(virtsels *s)
{
    int ret,salir=0;
    menustructs *d=s->dato;
    formenus *f=d->dato;
    int op=VIRTPOS(s);
    char *fichero=*(char **)d->opciones;
    while (!salir) {
          ret=tecla();
          if (ret==C_F(10)) {
              char destino[MAXPATH];
              damenombrecompleto(fichero,destino);
              invocaeditor(destino,NULL);
              ret=0;
          } else {
              switch (ret) {
                  case cuu:if (op>0) {
                              int nop;
                              if (f->op[op-1].ft) return(ret);
                              for (nop=op-1;nop>=0;nop--) {
                                  if (f->op[nop].ft!=NULL) {
                                      encolatecla(cuu);
                                      return(cuu);
                                  }
                              }
                              return(0);
                           }
                           salir=1;
                           break;
                  case cua:if (op<f->nopciones-1) {
                              int nop;
                              if (f->op[op+1].ft) return(ret);
                              for (nop=op+1;nop<f->nopciones;nop++) {
                                  if (f->op[nop].ft!=NULL) {
                                      encolatecla(cua);
                                      return(cua);
                                  }
                              }
                              return(0);
                           }
                           salir=1;
                           break;
                  default: salir=1;
              }
          }
    }
    return(ret);
}

static void pintamenucontex(virtsels *s,int real)
{
    menustructs *d = (menustructs *)s->dato;
    int op=VIRTPOS(s);
    formenus *f=d->dato;
    if (f->op[op].ft) {
       if (real) poncolorv(&s->v,CINPUTACT);
       else   poncolorv(&s->v,CINPUTINAC);
    } else {
       if (real) poncolorv(&s->v,CMARCA);
       else   poncolorv(&s->v,CNOENTER);
    }
    v10printf(&s->v,"%-*.*s",s->colreg,s->colreg,(*d->indexa)(d->opciones,VIRTPOS(s)));
    poncolorv(&s->v,CNORMAL);
}

int STDpresentamenucontex(formenus *f)
{
  char **opciones;
  int ret=0;
  int i,primera=-1;
  opciones=calloc(f->nopciones+2,sizeof(char *));
  opciones[0]=f->titulo;
  for (i=0;i<f->nopciones;i++) {
      opciones[i+1]=strdup(v10translate(f->op[i].opcion));
      if (f->op[i].ft!=NULL && primera==-1) primera=i;
   }
  opciones[i+1]=NULL;
  if (primera>=0) ret=menutotal(opciones,primera,10,2,-1,-1,1,NULL,(int (*)(virtsels *s))v10busca,pintamenucontex,teclacontex,f);
  else ult_pul=esc;
  for (i=0;i<f->nopciones;i++) {
      free(opciones[i+1]);
   }
  free(opciones);
  return(ret);
}

int fleemenucontextual(bloques *b,ftrigers *ft)
{
  formenus *f;
  char menu[MAXPATH];
  int ret;
  dameparametro(b, ft, 0, V10CADENA, menu);
  f=leemenu(b,menu);
  if (f) {
     ret=presentamenucontex(f);
	 if (ult_pul==cr) {
       if (f->op[ret].ft) ejecutaftriger(b,0,f->op[ret].ft,NULL);
     }
	 liberaforcontext(f);
   }
  return(0);
}

