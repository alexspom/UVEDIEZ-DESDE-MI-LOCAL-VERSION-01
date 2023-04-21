/*
* Módulo : V10COMBO.C                                              
* Objeto:  Tratamiento de combo box
* 
* 
* Autor	 : Eduardo Alsina Alvarez
* Fecha  : 10-10-2007

* MODIFICACIONES
* ---------------------------
*/
#include "v10.h"

static int selindice;
static int tx,ty;
static int pun;
static char bufferinput[80];

static char *arrptro(void *opcciones,int selindice)
{
  return(((char **)opcciones)[selindice]);
}

static void termina_selinp(v10inputs *v,int selindice)
{ switch (v->tipo) {        
	 case V10INT    :*(int *)v->dato=(int)selindice;
                      break;
	 case V10UINT    :*(unsigned int *)v->dato=(unsigned int)selindice;
                      break;
	 case V10SHORT    :*(short *)v->dato=(short)selindice;
                      break;
	 case V10USHORT  :*(unsigned short *)v->dato=(unsigned short)selindice;
                      break;
	 case V10LONG    :*(long *)v->dato=(long)selindice;
                      break;
	 case V10ULONG   :*(unsigned long *)v->dato=(unsigned long)selindice;
                      break;
	 case V10FLOAT  :*(float *)v->dato=(float)selindice;
                      break;
	 case V10DOUBLE :*(double *)v->dato=(double)selindice;
                      break;
    case V10BYTE   :
	 case V10CHAR   :*(char *)v->dato=(char)selindice;
                      break;
	 case V10CADENA :{strcopia(v->dato,v->lista[selindice],v->lvar);
                      break;
                      }
         default     :final(("Sin implementar en V10COMBO"));
                      break;
      }
}

static void selllpresenta(v10inputs *v,char normal,int selindice,int tx,int ty,char *bufferinput,int activo)
{
   if (activo) {
      strcpy(bufferinput,v->lista[selindice]);
   } else *bufferinput=0;
   pad(bufferinput,v->lpan);
   if (normal) poncolorv(v->w,CINPUTINAC);
      else     poncolorv(v->w,CINPUTACT);
   imprimev(v->w,v->posx+tx,v->posy+ty,bufferinput);
   poncolorv(v->w,CNORMAL);
}

static void presenta(v10inputs *v,char normal)
{
  selllpresenta(v,normal,selindice,tx,ty,bufferinput,1);
  if ((v->triger!=NULL)) {
     termina_selinp(v,selindice);
     v->vtriger=(*v->triger)(v->trigerdatos,v);
   }
  v->w->cursorx=v->posx;v->w->cursory=v->posy;
  pon_curf(v->w);
}

static void inicializa_selinp(v10inputs *v,int *selindice)
{
  switch (v->tipo) {
	 case V10INT    :*selindice=*(int *)v->dato;
                      break;
	 case V10UINT    :*selindice=*(unsigned int *)v->dato;
                      break;
	 case V10SHORT    :*selindice=*(short *)v->dato;
                      break;
	 case V10USHORT    :*selindice=*(unsigned short *)v->dato;
                      break;
	 case V10LONG   :*selindice=(int)*(long *)v->dato;
                      break;   
	 case V10ULONG   :*selindice=(int)*(unsigned long *)v->dato;
                      break;
	 case V10FLOAT  :*selindice=(int)*(float *)v->dato;
                      break;
	 case V10DOUBLE :*selindice=(int)*(double *)v->dato;
                      break;
     case V10BYTE   :
	 case V10CHAR   :*selindice=*(char *)v->dato;
                      break;
     case V10CADENA :{int unico;
		              *selindice=v10busca(v->lista,arrptro,v->dato,&unico);
		              if (*selindice==-1) *selindice=0;
                      break;
                      }
     default     :final(("Sin implementar en V10COMBO"));
                  break;
      }
}

static void inicializa(v10inputs *v)
{
  inicializa_selinp(v,&selindice);
}

static void primero(v10inputs *v)
{ 
  selindice=0;
  pun=0;*bufferinput=0;
  presenta(v,0);
}

static void ultimo(v10inputs *v)
{ 
  for (selindice=0;v->lista[selindice];selindice++);
  if (selindice) selindice--;
  pun=0;*bufferinput=0;
  presenta(v,0);
}

static void anterior(v10inputs *v)
{
   if (selindice>0) {
      selindice--;
      pun=0;*bufferinput=0;
      presenta(v,0);
    } else       ultimo(v);
}

static void posterior(v10inputs *v)
{
  selindice++;
  if (v->lista[selindice]==NULL) selindice=0;
  pun=0;*bufferinput=0;
  presenta(v,0);
}

static int buscainp(v10inputs *v,int *unico)
{
  int auxind;
  trim(bufferinput);
  if ((auxind=v10busca(v->lista,arrptro,bufferinput,unico))!=-1) {
     selindice=auxind;
     return(selindice);
    }
  return(-1);
}

int selecinp(v10inputs *v,int despx,int despy)
{ int c=0;
  int salir=0;
  if (v->activa==1) return(0);
  v->activa=1;
  tx=despx,ty=despy;
  pun=0;
  inicializa(v);
  presenta(v,0);
  while (!salir) {
    c=tecla();
    switch(c) {
        case home:primero(v);
                  break;
        case end:ultimo(v);
                 break;
        default :if (ESFUNC(c)) {
                    salir=-1;break;
                   }
                 switch(c) {
                    case  cr:
                    case tab:
                    case esc: salir=-1;
                              break;
                    case ' ':
                    case '+':posterior(v);
                             break;
                    case '-':anterior(v);
                             break;
                    case back:{int aux,unico;
                            if (pun>0) bufferinput[--pun]=0;
                            presenta(v,0);
                            if (pun) if ((aux=buscainp(v,&unico))>=0) {
			       selindice=aux;
                              }
                            }
                           break;
                  default:c=pasacarmay(c);
                          {int aux,unico;
                           if (pun<v->lvar) {
                               bufferinput[pun++]=(char)c;
                               bufferinput[pun]=0;
                               if ((aux=buscainp(v,&unico))>=0) {
				  selindice=aux;presenta(v,0);
                                  if (unico) {salir=-1;c=cr;}
                                 } else bufferinput[--pun]=0;
                             }
                          }
           }
      }
  }
  presenta(v,1);
  termina_selinp(v,selindice);
  v->activa=-1;
  return(c);
}

void presinp(v10inputs *v,int despx,int despy)
{ int selindice;
  char bufferinput[80];
  if (v->activa==1) return;
  v->activa=1;
  inicializa_selinp(v,&selindice);
  termina_selinp(v,selindice);
  selllpresenta(v,1,selindice,despx,despy,bufferinput,!(v->formato&4));
  v->activa=-1;
}