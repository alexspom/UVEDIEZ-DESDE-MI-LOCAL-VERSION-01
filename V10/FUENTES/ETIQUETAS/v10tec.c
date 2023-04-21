//Módulo con driver de impresora TEC
#include "v10etiqueta.h"

#define CODABRELLAVE    123  //Código del carácter '{'
#define CODBARRA        124  //Código del carácter '|'
#define CODCIERRALLAVE  125  //Código del carácter '}'

#define ITF        2 //Código de barras Interleaved 2 of 5
#define Code39Std  3
#define Code39Full 4

typedef struct {
          int  font;
          int  fx;
          int  bold;
          char ch;
        } tecfonts;
static tecfonts tec[]={{0,12,0,'A'},
                       {1,15,0,'B'},
                       {2,15,7,'C'},
                       {3,18,7,'D'},
                       {4,21,7,'E'},
                       {5, 9,0,'G'},
                       {6,15,0,'H'},
                       {7,18,0,'I'},
                       {8,18,7,'J'},
                       {9,21,0,'K'},
                       {10,27,7,'M'},
                       {11,14,0,'N'},
                       {12,10,0,'O'},
                       {13,15,7,'P'},
                       {14,15,0,'Q'},
                       {15,18,7,'R'}};

static void buscamejorfont(idrivers *id,int *font,int *fx,int *fy)
{
  int i,posible=-1;
  for (i=0;i<sizeof(tec)/sizeof(tec[0]);i++) {
      if (tec[i].font==id->font) {
         if (posible==-1) {
            posible=i;
          } else {
            if (tec[i].fx<id->fx && tec[i].fx<id->fy) posible=i;
          }
       }
   }
  if (posible==-1) posible=0;
  *font=tec[posible].ch;
  *fx=((id->fx*10)/tec[posible].fx)/5*5;
  if (*fx==0) *fx=5;
  *fy=((id->fy*10)/tec[posible].fx)/5*5;
  if (*fy==0) *fy=5;
}

static void imprimecadenatec(idrivers *id,char *cadena,char *fin,char *ptrsal)
{
  int  angulo;
  int font,fx,fy;
  char *ptr;

  if (id->angulo<90) angulo=0;
     else if (id->angulo<180) angulo=11;
             else if (id->angulo<270) angulo=22;
                     else         angulo=33;
  id->numcad++;
  ptr=strchr(cadena,'"');
  while (ptr!=NULL) {
        *ptr='\'';
        ptr=strchr(ptr+1,'"');
   }
  ptr=strchr(cadena,'$');
  while (ptr!=NULL && ptr<fin) {
        *ptr='/';
        ptr=strchr(ptr+1,'$');
   }
  buscamejorfont(id,&font,&fx,&fy);
  sprintf(ptrsal,"%cPC%03d;%04d,%04d,%02d,%02d,%c,%02d,%c=%-*.*s%c%c\n",
                 CODABRELLAVE,id->numcad,id->px,id->py,fx,fy,font,angulo,id->color,fin-cadena,fin-cadena,cadena,CODBARRA,CODCIERRALLAVE);
}

static void imprimebarrastec(idrivers *id,char *cadena,char *fin,char **ptrsal)
{
  int  angulo;
  int  ancho,anchogrande;
  char destino[MAXCADENA];
  char *ptr=cadena,*ptr1=destino;

  if (id->angulo<90) angulo=0;
     else if (id->angulo<180) angulo=1;
             else if (id->angulo<270) angulo=2;
                     else         angulo=3;
  while (ptr<fin) {
        if (*ptr=='¿') {
           *ptr1++='>';
           *ptr1++='8';
           ptr++;
         } else *ptr1++=*ptr++;
    }

  id->numcb++;
  ancho=(id->ancb*10)/110;
  anchogrande=ancho*id->ratiocb;

  switch (id->tipocb)
  {
     case ITF:
     {
        sprintf(*ptrsal,"%cXB%02d;%04d,%04d,%d,1,%02d,%02d,%02d,%02d,00,%d,%04d=%-*.*s%c%c\n",
                        CODABRELLAVE,id->numcb,id->px,id->py,id->tipocb,ancho,ancho,anchogrande,anchogrande,angulo,id->alcb,ptr1-destino,ptr1-destino,destino,CODBARRA,CODCIERRALLAVE);
     }
     break;
     case Code39Std:
     {
        sprintf(*ptrsal,"%cXB%02d;%04d,%04d,3,1,%02d,%02d,%02d,%02d,02,%d,%04d=%-*.*s%c%c\n",
                        CODABRELLAVE,id->numcb,id->px,id->py,ancho,ancho,anchogrande,anchogrande,angulo,id->alcb,ptr1-destino,ptr1-destino,destino,CODBARRA,CODCIERRALLAVE);
     }
     break;

     case Code39Full:
     {
        sprintf(*ptrsal,"%cXB%02d;%04d,%04d,B,1,%02d,%02d,%02d,%02d,02,%d,%04d=%-*.*s%c%c\n",
                        CODABRELLAVE,id->numcb,id->px,id->py,ancho,ancho,anchogrande,anchogrande,angulo,id->alcb,ptr1-destino,ptr1-destino,destino,CODBARRA,CODCIERRALLAVE);
     }
     break;

     default:
     {
        sprintf(*ptrsal,"%cXB%02d;%04d,%04d,9,1,%02d,%d,%04d=%-*.*s%c%c\n",
                        CODABRELLAVE,id->numcb,id->px,id->py,ancho,angulo,id->alcb,ptr1-destino,ptr1-destino,destino,CODBARRA,CODCIERRALLAVE);
     }
  }

  *ptrsal+=strlen(*ptrsal);
}

static void imprimelineatec(idrivers *id,char **ptrsal,int lx,int ly,int ancho,int tipo)
{
  sprintf(*ptrsal,"%cLC;%04d,%04d,%04d,%04d,%d,%d%c%c\n",
                   CODABRELLAVE,id->px,id->py,id->px+lx,id->py+ly,tipo,ancho/10,CODBARRA,CODCIERRALLAVE);
  *ptrsal+=strlen(*ptrsal);
}

static void tiraetiqtec(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"%cXS;I,0001,0002C6200%c%c",
                  CODABRELLAVE,CODBARRA,CODCIERRALLAVE);
  *ptrsal+=strlen(*ptrsal);
}

static void initetiqtec(idrivers *id,char **ptrsal)
{
  sprintf(*ptrsal,"%cC%c%c\n",
                  CODABRELLAVE,CODBARRA,CODCIERRALLAVE);
  *ptrsal+=strlen(*ptrsal);
}

void pondrivertec(idrivers *id)
{
  id->imprimecadena=imprimecadenatec;
  id->imprimebarras=imprimebarrastec;
  id->imprimelinea=imprimelineatec;
  id->cambiamaxetiq=NULL;
  id->tiraetiq=tiraetiqtec;
  id->initetiq=initetiqtec;
  id->repiteetiq=0;
}
